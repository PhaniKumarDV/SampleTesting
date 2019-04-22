/*************************************************************/
/* Purpose : This file is intended to capture and handle the */
/*           TCP socket events from Mobile application.      */
/*  Author : KeyWest Networks                                */
/*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uci.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/ether.h>
#include <fcntl.h>
#include <endian.h>
#include <linux/wireless.h>
#include "socketevent.h"

#include <endian.h>
#if __BYTE_ORDER == __BIG_ENDIAN
#define _BYTE_ORDER _BIG_ENDIAN
#elif __BYTE_ORDER == __LITTLE_ENDIAN
#define _BYTE_ORDER _LITTLE_ENDIAN
#else
#error "__BYTE_ORDER undefined"
#endif
#define EXTERNAL_USE_ONLY

#ifndef __packed
#define __packed    __attribute__((__packed__))
#endif
#include "_ieee80211.h"
#include "ieee80211_defines.h"
#include "ieee80211.h"
#include "ieee80211_ioctl.h"

void kwn_get_assoclist( kwn_wireless_stats *list );
void kwn_get_wireless_stats( kwn_pkt *buf );
void kwn_req_type( int socketfd, kwn_pkt *buf );
void kwn_get_config_data( kwn_pkt *buf );
void kwn_get_config_from_device( kwn_cfg_data *dev_cfg );
uint8_t commit_in_progress = 0;

void kwn_conv_str_to_ip( int8_t* conv_ip, uint8_t* byte )
{
    uint32_t ip_addr=0,val;
    int8_t  *tok,*ptr;

    if( conv_ip[0] == '\0' )
    {
        return;
    }
    tok=strtok(conv_ip,".");

    while( tok != NULL)
    {
        val=strtoul(tok,&ptr,0);
        ip_addr=(ip_addr << 8) + val;
        tok=strtok(NULL,".");
    }

    /*printf(" Equivalent 32-bit int is : %u\n",ip_addr);*/

    byte[0] = ((ip_addr >> 24) & 0xFF);
    byte[1] = ((ip_addr >> 16) & 0xFF);
    byte[2] = ((ip_addr >> 8) & 0xFF);
    byte[3] = (ip_addr & 0xFF);

    /*printf("IP: %d.%d.%d.%d \n",byte[0],byte[1],byte[2],byte[3]);*/
    return;
}

void kwn_dhcp_inet_handle( const char* cmd, uint8_t* cmd_buf )
{
    FILE *fp;
    char *tok, *p;
    short int len;
    char ip[20];
    char a[100];
    int i = 0;

    memset( a, '\0', sizeof( a ) );
    memset( ip, '\0', sizeof( ip ) );
    strcpy(ip,"0.0.0.0");

    fp = popen( cmd, "r" );
    while( fgets( a, sizeof( a ), fp ) != NULL )
    {       
        /*printf("%s\n", a);*/
        if( i == 1 )
            break;
        i++;
    } 
    pclose( fp );

    /*printf("%s", a);*/
    p = strstr(a,"Bcast");

    if( p == NULL )
    {   
        printf("No occurance of inet\n");
    }   
    else
    {   
        tok = strtok(a,"inet addr:");
        len = strlen( tok );
        memcpy( ip, tok, len );
    }   
    /*printf("DHCP IP : %s\n",ip);*/
    len = strlen( ip );
    memcpy(cmd_buf, ip, len);
    return;
}

void kwn_dhcp_mask_handle( const char* cmd, uint8_t* cmd_buf )
{
    FILE *fp;
    char *tok, *p;
    short int len;
    char ip[20];
    char a[100];
    int i = 0;

    memset( a, '\0', sizeof( a ) );
    memset( ip, '\0', sizeof( ip ) );
    strcpy(ip,"0.0.0.0");

    fp = popen( cmd, "r" );
    while( fgets( a, sizeof( a ), fp ) != NULL )
    {       
        /*printf("%s\n", a);*/
        if( i == 1 )
            break;
        i++;
    } 
    pclose( fp );

    /*printf("%s", a);*/
    p = strstr(a,"Bcast");

    if( p == NULL )
    {   
        printf("No occurance of inet\n");
    }   
    else
    {
        tok = strtok(a,": \n");
        while( tok != NULL)
        {
            memset( ip, '\0', sizeof( ip ) );
            len = strlen(tok);
            memcpy(ip,tok,len);
            tok = strtok(NULL, ": \n");
        }
    }   
    /*printf("DHCP Mask : %s\n",ip);*/
    len = strlen( ip );
    memcpy(cmd_buf, ip, len);
    return;
}

void kwn_dhcp_gateway_handle( const char* cmd, uint8_t* cmd_buf )
{
    FILE *fp;
    char *tok, *p;
    short int len;
    char gip[20];
    char a[100];
    int i = 0, j = 0;

    memset( a, '\0', sizeof( a ) );
    memset( gip, '\0', sizeof( gip ) );
    strcpy(gip,"0.0.0.0");

    fp = popen( cmd, "r" );
    while( fgets( a, sizeof( a ), fp ) != NULL )
    {
        /*printf("%s\n", a);*/
        if( i == 1 )
            break;
        i++;
    }
    pclose( fp );

    p = strstr(a,"default");

    if( p == NULL )
    {
        printf("No occurance of default in ip route\n");
    }
    else
    {
        tok = strtok(a," ");

        while( tok != NULL)
        {
            printf( " %s\n", tok );
            if( j == 2 )
            {
                len = strlen(tok);
                memcpy(gip,tok,len);
                break;
            }
            j++;
            tok = strtok(NULL," ");
        }
    }
    printf("%s",gip);
    len = strlen( gip );
    memcpy(cmd_buf, gip, len);
    return;
}

void kwn_str_to_mac(uint8_t* cmd_buf, uint8_t *local_mac )
{
    sscanf( cmd_buf, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",&local_mac[0], &local_mac[1], &local_mac[2],&local_mac[3], &local_mac[4], &local_mac[5]); 
    return;
}

void kwn_sys_cmd_imp( const char* cmd, uint8_t* cmd_buf )
{
    FILE *fp = NULL;
    uint8_t  a[KWN_SOCK_BUF_LEN]={0};
    uint8_t  *token;
    uint16_t len;

    memset( a, '\0', sizeof(a) );
    fp = popen(cmd,"r");
    if( fp == NULL )
        return;
    while( fgets(a, sizeof(a), fp) != NULL)
    {
        /*printf("%s",a);*/
    }
    pclose(fp);

    if( a[0] == '\0' ) {
        len = strlen(a);
        memcpy(cmd_buf,a,len);
    }
    else {
        token = strtok(a,"\n");
        len = strlen(token);
        memcpy(cmd_buf,token,len);
    }
    return;
}

void kwn_cmdbuf_to_trunkarray(uint8_t* cmd_buf, uint16_t* trunk_vlan)
{
    uint8_t *tok;
    int i=0,j=0;

    tok=strtok(cmd_buf," ");

    while( tok != NULL)
    {
        printf( " %s\n", tok );
        trunk_vlan[i] = atoi(tok);
        i++;
        tok = strtok(NULL, " ");
    }
    return;
}

uint8_t kwn_dev_radio_mode( uint8_t* dev_radio_mode, uint16_t radio_mode_len )
{
    uint8_t  radio_mode = 0;
    uint8_t  wds_mode = 0;
    uint8_t  cmd_wds[50];
    uint16_t i = 0;
    uint16_t lent = ( sizeof(kwn_dev_mode)/sizeof(kwn_dev_mode[0]) );

    memset(cmd_wds, '\0', sizeof(cmd_wds));
    sprintf(cmd_wds,"uci get wireless.@wifi-iface[1].wds");
    kwn_sys_cmd_imp(&cmd_wds[0], &wds_mode);

    /*printf("Length of kwn_dev_mode[] : %d\n",lent);
      printf("MODE_LEN : %d\n",radio_mode_len);
      printf("DEV Radio Mode : %s\n",dev_radio_mode);
      printf("WDS_MODE : %d\n",wds_mode);*/

    for( i=0; i<lent; i++ )
    {
        if( strncmp( dev_radio_mode, *(kwn_dev_mode+i), radio_mode_len ) == 0 )
            radio_mode = i;
    }

    if( wds_mode == 1 )
    {
        if( radio_mode == 1 )
            return KWN_OUTDOOR_BASE;
        else if( radio_mode == 2 )
            return KWN_OUTDOOR_SUBSCRIBER;
        else
            return KWN_ERROR;
    }
    else
    {
        if( radio_mode == 1 )
            return KWN_OUTDOOR_BASE;
        else if( radio_mode == 2 )
            return KWN_OUTDOOR_SUBSCRIBER;
        else if( radio_mode == 3 )
            return KWN_ADHOC;
        else if( radio_mode == 4 )
            return KWN_STATIC_WDS;
        else
            return KWN_ERROR;
    }
    return KWN_ERROR;
}

uint8_t kwn_iptype_to_enum( uint8_t* ipaddr_type, uint16_t ipaddr_type_len)
{
    uint8_t  ip_type=0;
    uint16_t i;
    uint16_t lent = (sizeof(kwn_ip_type)/sizeof(kwn_ip_type[0]));

    /*printf("Length of kwn_ip_type[] : %d\n",lent);
      printf("IP_TYPE_LEN : %d\n",ipaddr_type_len);
      printf("IP_TYPE : %s\n",ipaddr_type);*/

    for( i=0; i<lent; i++ )
    {
        if( strncmp( ipaddr_type, *(kwn_ip_type+i), ipaddr_type_len ) == 0 )
        {
            ip_type = i;
            break;
        }
    }
    /*printf("Value of ip_type: %d\n",ip_type);*/
    return ip_type;

}

uint8_t kwn_opmode_to_enum( uint8_t* dev_opmode, uint16_t opmode_len )
{
    uint8_t  op_mode=0;
    uint16_t i;
    uint16_t lent = (sizeof(kwn_opmode)/sizeof(kwn_opmode[0]));

    /*printf("Length of kwn_opmode[] : %d\n",lent);
      printf("OPMODE_LEN : %d\n",opmode_len);
      printf("DEV opmode Mode : %s\n",dev_opmode);*/

    for( i=0; i<lent; i++ )
    {
        if( strncmp( dev_opmode, *(kwn_opmode+i), opmode_len ) == 0 )
        {
            op_mode = i;
            break;
        }
    }
    /*printf("Value of op_mode: %d\n",op_mode);*/
    return op_mode;
}

uint8_t kwn_bwidth_to_enum( uint8_t* dev_bwidth, uint16_t bwidth_len )
{
    uint8_t  bwidth=0;
    uint16_t i;
    uint16_t lent = (sizeof(kwn_bandwidth)/sizeof(kwn_bandwidth[0]));

    /*printf("Length of kwn_bandwidth[] : %d\n",lent);
      printf("Bwidth_LEN : %d\n",bwidth_len);
      printf("DEV Bandwidth : %s\n",dev_bwidth);*/

    for( i=0; i<lent; i++ )
    {
        if( strncmp( dev_bwidth, *(kwn_bandwidth+i), bwidth_len ) == 0 )
            bwidth = i;
    }
    /*printf("Value of bandwidth: %d\n",bwidth);*/
    return bwidth;
}

uint8_t kwn_enctype_to_enum( uint8_t* dev_enctype, uint16_t enc_type_len)
{
    uint8_t  enc_type=0;
    uint16_t i;
    uint16_t lent = (sizeof(kwn_enc_type)/sizeof(kwn_enc_type[0]));

    for( i=0; i<lent; i++ )
    {
        if( strncmp( dev_enctype, *(kwn_enc_type+i), enc_type_len ) == 0 )
        {
            enc_type = i;
            break;
        }
    }
    return enc_type;
}

void kwn_get_config_from_device( kwn_cfg_data *dev_cfg )
{
    uint8_t  cmd[100];
    uint8_t  cmd_buf[KWN_SOCK_BUF_LEN];
    uint16_t len = 0;
    uint8_t  ip_byte[4] = {0};
    uint8_t  gip_byte[4] = {0};
    uint8_t  netmask_byte[4] = {0};
    uint8_t  l_mac[6] = {0};
    uint8_t  d_ip_byte[4] = {0};
    uint8_t  d_gip_byte[4] = {0};
    uint8_t  d_netmask_byte[4] = {0};
    uint16_t trunk_vlan[100]={0};
    uint16_t j = 0;

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get network.lan.proto");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    len=strlen(cmd_buf);
    dev_cfg->ip_type = kwn_iptype_to_enum(&cmd_buf[0], len);
    printf("dev_cfg->ip_type IP_TYPE: %d\n",dev_cfg->ip_type);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get network.lan.ipaddr");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    kwn_conv_str_to_ip(&cmd_buf[0],&ip_byte[0]);
    len = strlen(ip_byte);
    memcpy(dev_cfg->ip, ip_byte, len);
    printf("dev_cfg->ip: %d.%d.%d.%d\n",dev_cfg->ip[0],dev_cfg->ip[1],dev_cfg->ip[2],dev_cfg->ip[3]);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get wireless.@wifi-iface[1].ssid");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    len=strlen(cmd_buf);
    memcpy(dev_cfg->ssid, cmd_buf, len);
    printf("dev_cfg->ssid SSID: %s ssid len : %d\n",dev_cfg->ssid, len);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get wireless.wifi1.hwmode");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    len=strlen(cmd_buf);
    dev_cfg->opmode = kwn_opmode_to_enum(&cmd_buf[0], len);
    printf("dev_cfg->opmode OPMODE: %d\n",dev_cfg->opmode);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get wireless.wifi1.htmode");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    len=strlen(cmd_buf);
    dev_cfg->bandwidth = kwn_bwidth_to_enum(&cmd_buf[0], len);
    printf("dev_cfg->bandwidth Bandwidth: %d\n",dev_cfg->bandwidth);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get wireless.wifi1.channel");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->channel = (uint8_t)atoi(cmd_buf);
    printf("dev_cfg->Channel : %d\n",dev_cfg->channel);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get wireless.@wifi-iface[1].mode");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    len=strlen(cmd_buf);
    dev_cfg->mode = kwn_dev_radio_mode(&cmd_buf[0],len);
    printf("dev_cfg->mode : %d\n",dev_cfg->mode);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get wireless.wifi1.macaddr");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    len=KWN_MAC_ADDR_LEN;
    kwn_str_to_mac(&cmd_buf[0],&l_mac[0]);    
    memcpy(dev_cfg->local_mac, l_mac, len);
    printf("dev_cfg->local_mac = %2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X\n",dev_cfg->local_mac[0],dev_cfg->local_mac[1],dev_cfg->local_mac[2],
      dev_cfg->local_mac[3],dev_cfg->local_mac[4],dev_cfg->local_mac[5]);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get wireless.wifi1.country");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->country = (uint16_t)atoi(cmd_buf);
    printf("dev_cfg->country : %d\n",dev_cfg->country);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get network.lan.gateway");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    kwn_conv_str_to_ip(&cmd_buf[0],&gip_byte[0]);
    len = strlen(gip_byte);
    memcpy(dev_cfg->gip, gip_byte, len);
    printf("dev_cfg->gip : %d.%d.%d.%d\n",dev_cfg->gip[0],dev_cfg->gip[1],dev_cfg->gip[2],dev_cfg->gip[3]);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get network.lan.netmask");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    kwn_conv_str_to_ip(&cmd_buf[0],&netmask_byte[0]);
    len = strlen(netmask_byte);
    memcpy(dev_cfg->netmask, netmask_byte, len);
    printf("dev_cfg->netmask : %d.%d.%d.%d\n",dev_cfg->netmask[0],dev_cfg->netmask[1],dev_cfg->netmask[2],dev_cfg->netmask[3]);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get wireless.wifi1.customername");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    len=strlen(cmd_buf);
    memcpy(dev_cfg->cust_name, cmd_buf, len);
    printf("dev_cfg->cust_name : %s - Len of custname : %d \n",dev_cfg->cust_name,len);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get wireless.wifi1.linkid");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    len=strlen(cmd_buf);
    memcpy(dev_cfg->linkid, cmd_buf, len);
    printf("dev_cfg->Link_id : %s - Len of Linkid : %d \n",dev_cfg->linkid, len);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get wireless.wifi1.ddrsstatus");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->ddrs_status = atoi(cmd_buf);
    printf("dev_cfg->DDRS Status : %d\n",dev_cfg->ddrs_status);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get wireless.wifi1.spatialstream");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->stream = atoi(cmd_buf);
    printf("dev_cfg->Spatial Stream : %d\n",dev_cfg->stream);   

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get wireless.wifi1.ddrsrate");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->modindex = atoi(cmd_buf);
    printf("dev_cfg->Modulation Index : %d\n",dev_cfg->modindex);   

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get wireless.wifi1.ddrsminrate");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->min_modindex = atoi(cmd_buf);
    printf("dev_cfg->Min Modulation Index : %d\n",dev_cfg->min_modindex);   

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get wireless.wifi1.ddrsmaxrate");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->max_modindex = atoi(cmd_buf);
    printf("dev_cfg->Max Modulation Index : %d\n",dev_cfg->max_modindex);   

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get wireless.wifi1.atpcstatus");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->atpc_status = atoi(cmd_buf);
    printf("dev_cfg->ATPC Status : %d\n",dev_cfg->atpc_status);   

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get wireless.wifi1.atpcpower");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->txpower = atoi(cmd_buf);
    printf("dev_cfg->TX Power : %d\n",dev_cfg->txpower);   

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd, "ifconfig br-lan" );
    kwn_dhcp_inet_handle( &cmd[0], &cmd_buf[0] );
    kwn_conv_str_to_ip(&cmd_buf[0],&d_ip_byte[0]);
    len = strlen(d_ip_byte);
    memcpy(dev_cfg->dyn_ip, d_ip_byte, len);
    printf("dev_cfg->dyn_ip: %d.%d.%d.%d\n",dev_cfg->dyn_ip[0],dev_cfg->dyn_ip[1],dev_cfg->dyn_ip[2],dev_cfg->dyn_ip[3]);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"ip route | grep default" );
    kwn_dhcp_gateway_handle( &cmd[0], &cmd_buf[0] );
    kwn_conv_str_to_ip(&cmd_buf[0],&d_gip_byte[0]);
    len = strlen(d_gip_byte);
    memcpy(dev_cfg->dyn_gip, d_gip_byte, len);
    printf("dev_cfg->dyn_gip: %d.%d.%d.%d\n",dev_cfg->dyn_gip[0],dev_cfg->dyn_gip[1],dev_cfg->dyn_gip[2],dev_cfg->dyn_gip[3]);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd, "ifconfig br-lan" );
    kwn_dhcp_mask_handle( &cmd[0], &cmd_buf[0] );
    kwn_conv_str_to_ip(&cmd_buf[0],&d_netmask_byte[0]);
    len = strlen(d_netmask_byte);
    memcpy(dev_cfg->dyn_netmask, d_netmask_byte, len);
    printf("dev_cfg->dyn_netmask: %d.%d.%d.%d\n",dev_cfg->dyn_netmask[0],dev_cfg->dyn_netmask[1],dev_cfg->dyn_netmask[2],dev_cfg->dyn_netmask[3]);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get wireless.wifi1.distance");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->distance = atoi(cmd_buf);
    printf("dev_cfg->Distance : %d\n",dev_cfg->distance);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get vlan.vlan.status");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->vlanstatus = atoi(cmd_buf);
    printf("dev_cfg->VLAN Status : %d\n",dev_cfg->vlanstatus);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get vlan.vlan.mode");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->vlanmode= atoi(cmd_buf);
    printf("dev_cfg->VLAN Mode : %d\n",dev_cfg->vlanmode);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get vlan.vlan.mgmtvlan");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->vlanmgmtid = atoi(cmd_buf);
    printf("dev_cfg->VLAN Mgmt ID : %d\n",dev_cfg->vlanmgmtid);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get vlan.vlan.accessvlan");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->vlanaccid = atoi(cmd_buf);
    printf("dev_cfg->VLAN Access ID : %d\n",dev_cfg->vlanaccid);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get vlan.vlan.trunkoption");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->vlantrnkopt = atoi(cmd_buf);
    printf("dev_cfg->VLAN Trunk Option : %d\n",dev_cfg->vlantrnkopt);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get vlan.vlan.trunkvlan");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    kwn_cmdbuf_to_trunkarray(&cmd_buf[0],trunk_vlan);
    printf("dev_cfg->VLAN Trunk ID : ");
    for(j=0;trunk_vlan[j]!=0;j++){
        /*printf("vlanid : %d ",trunk_vlan[j]);*/
        dev_cfg->vlantrnkid[j] = trunk_vlan[j];
        printf("%d ",dev_cfg->vlantrnkid[j]);
    }
    printf("\n"); 
    printf("valid trunkvlan length: %d\n",j);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get vlan.vlan.svlan");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    dev_cfg->svlanid = atoi(cmd_buf);
    printf("dev_cfg->SVLAN ID : %d\n",dev_cfg->svlanid);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get vlan.vlan.svlanethertype");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    len=strlen(cmd_buf);
    memcpy(dev_cfg->svlanethtype, cmd_buf, len);
    printf("dev_cfg->svlan ethertype: %s len : %d\n",dev_cfg->svlanethtype, len);
 
    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get wireless.@wifi-iface[1].encryption");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    len=strlen(cmd_buf);
    dev_cfg->encrypttype = kwn_enctype_to_enum(&cmd_buf[0], len);
    printf("dev_cfg->encrypttype Encryption Type : %d\n",dev_cfg->encrypttype);
   
    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get wireless.@wifi-iface[1].key");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    len=strlen(cmd_buf);
    memcpy(dev_cfg->enckey, cmd_buf, len);
    printf("dev_cfg->enckey: %s enckey len : %d\n",dev_cfg->enckey, len);

    /*printf("Executed uci commands to get the config\n");*/   
    return;
}

void kwn_get_config_data( kwn_pkt* buf)
{
    uint16_t len = 0;
    uint8_t  type = 0;
    uint16_t llen = 0;
    uint16_t j = 0;

    kwn_cfg_data data;
    memset(&data,'\0', sizeof(kwn_cfg_data)); 
    kwn_get_config_from_device(&data);

    buf->hdr.type = KWN_TYPE_GET_RESPONSE;
    buf->hdr.sub_type = KWN_SUBTYPE_CONFIG_DATA;
    buf->hdr.ptmp = 0;

    /* IP_TYPE */
    printf("IP_TYPE : %d\n",data.ip_type);
    llen = sizeof(data.ip_type); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_IP_TYPE; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.ip_type,llen); /* value */
    len += llen;

    /* IP_ADDRESS */
    if( data.ip[0] != '\0' )
        printf("Static IP: %d.%d.%d.%d \n",data.ip[0],data.ip[1],data.ip[2],data.ip[3]);
    llen = sizeof(data.ip); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_IP; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.ip,llen); /* value */
    len += llen;

    /* SSID */
    printf("SSID : %s\n",data.ssid);
    llen = strlen(data.ssid); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_SSID; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.ssid,llen); /* value */
    len += llen;

    /* OPMODE */
    printf("OPMODE: %d\n",data.opmode);
    llen = sizeof(data.opmode); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_OPMODE; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.opmode,llen); /* value */
    len += llen;

    /* BANDWIDTH */
    printf("Bandwidth: %d\n",data.bandwidth);
    llen = sizeof(data.bandwidth); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_BANDWIDTH; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.bandwidth,llen); /* value */
    len += llen;

    /* CHANNEL */
    printf("Channel: %d\n",data.channel);
    llen = sizeof(data.channel); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_CHANNEL; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.channel,llen); /* value */
    len += llen;

    /* RADIO_MODE */
    printf("Mode: %d\n",data.mode);
    llen = sizeof(data.mode); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_DEV_MODE; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.mode,llen); /* value */
    len += llen;

    /* LOCAL_MAC */
    printf("MAC = %2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X\n",data.local_mac[0],data.local_mac[1],data.local_mac[2],
            data.local_mac[3],data.local_mac[4],data.local_mac[5]);
    llen = KWN_MAC_ADDR_LEN; /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_MAC; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.local_mac,llen); /* value */
    len += llen;

    /* RADIO_MODE */
    printf("Country: %u\n",data.country);
    llen = sizeof(data.country); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_CTRY; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.country,llen); /* value */
    len += llen;

    /* GATEWAY_IP_ADDRESS */
    if( data.gip[0] != '\0' )
        printf("Static Gateway IP: %d.%d.%d.%d \n",data.gip[0],data.gip[1],data.gip[2],data.gip[3]);
    llen = sizeof(data.gip); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_GIP; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.gip,llen); /* value */
    len += llen;

    /* NETMASK_IP_ADDRESS */
    if( data.netmask[0] != '\0' )
        printf("Static Mask IP: %d.%d.%d.%d \n",data.netmask[0],data.netmask[1],data.netmask[2],data.netmask[3]);
    llen = sizeof(data.netmask); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_NETMASK; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.netmask,llen); /* value */
    len += llen;   

    /* CUSTOMER NAME*/
    printf("CUSTOMER ID: %s - ",data.cust_name);
    llen = strlen(data.cust_name); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_CUST_NAME; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.cust_name,llen); /* value */
    len += llen;

    /* LINKID */
    printf("LinkID: %s\n",data.linkid);
    llen = strlen(data.linkid); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_LINKID; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.linkid,llen); /* value */
    len += llen;

    /* DDRS STATUS */
    printf("DDRS Status: %d\n",data.ddrs_status);
    llen = sizeof(data.ddrs_status); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_DDRS_STATUS; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.ddrs_status,llen); /* value */
    len += llen;  

    /* SPATIAL STREAM */
    printf("Spatial Stream: %d\n",data.stream);
    llen = sizeof(data.stream); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_SPATIAL_STREAM; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.stream,llen); /* value */
    len += llen;   

    /* MODULATION INDEX */
    printf("Modulation index: %d\n",data.modindex);
    llen = sizeof(data.modindex); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_MOD_INDEX; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.modindex,llen); /* value */
    len += llen;   

    /* MIN MODULATION INDEX */
    printf("Min Modulation index: %d\n",data.min_modindex);
    llen = sizeof(data.min_modindex); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_MIN_MOD_INDEX; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.min_modindex,llen); /* value */
    len += llen;   

    /* MAX MODULATION INDEX */
    printf("Max Modulation index: %d\n",data.max_modindex);
    llen = sizeof(data.max_modindex); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_MAX_MOD_INDEX; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.max_modindex,llen); /* value */
    len += llen;   

    /* ATPC STATUS */
    printf("ATPC Status: %d\n",data.atpc_status);
    llen = sizeof(data.atpc_status); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_ATPC_STATUS; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.atpc_status,llen); /* value */
    len += llen;

    /* TRANSMIT POWER */
    printf("Transmit Power: %d\n",data.txpower);
    llen = sizeof(data.txpower); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_TX_POWER; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.txpower,llen); /* value */
    len += llen;

    /* DHCP_IP_ADDRESS */
    if( data.dyn_ip[0] != '\0' )
        printf("Dynamic IP: %d.%d.%d.%d \n",data.dyn_ip[0],data.dyn_ip[1],data.dyn_ip[2],data.dyn_ip[3]);
    llen = sizeof(data.dyn_ip); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_DYN_IP; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.dyn_ip,llen); /* value */
    len += llen;

    /* DHCP_GATEWAY_IP_ADDRESS */
    if( data.dyn_gip[0] != '\0' )
        printf("Dynamic Gateway IP: %d.%d.%d.%d \n",data.dyn_gip[0],data.dyn_gip[1],data.dyn_gip[2],data.dyn_gip[3]);
    llen = sizeof(data.dyn_gip); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_DYN_GIP; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.dyn_gip,llen); /* value */
    len += llen;

    /* DHCP_NETMASK_IP_ADDRESS */
    if( data.dyn_netmask[0] != '\0' )
        printf("Dynamic Mask IP: %d.%d.%d.%d\n",data.dyn_netmask[0],data.dyn_netmask[1],data.dyn_netmask[2],data.dyn_netmask[3]);
    llen = sizeof(data.dyn_netmask); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_DYN_NETMASK; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.dyn_netmask,llen); /* value */
    len += llen;

    /* DISTANCE */
    printf("Distance : %d\n",data.distance);
    llen = sizeof(data.txpower); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_DISTANCE; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.distance,llen); /* value */
    len += llen;   

    /* VLAN STATUS */
    printf("VLAN Status: %d\n",data.vlanstatus);
    llen = sizeof(data.vlanstatus); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_VLAN_STATUS; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.vlanstatus,llen); /* value */
    len += llen;

    /* VLAN MODE */
    printf("VLAN Mode: %d\n",data.vlanmode);
    llen = sizeof(data.vlanmode); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_VLAN_MODE; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.vlanmode,llen); /* value */
    len += llen;

    /* VLAN MANAGEMENT ID */
    printf("VLAN Mgmtid: %d\n",data.vlanmgmtid);
    llen = sizeof(data.vlanmgmtid); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_VLAN_MGMTID; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.vlanmgmtid,llen); /* value */
    len += llen;

    /* VLAN ACCESS IS */
    printf("VLAN Access ID: %d\n",data.vlanaccid);
    llen = sizeof(data.vlanaccid); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_VLAN_ACCID; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.vlanaccid,llen); /* value */
    len += llen;

    /* VLAN TRUNK OPTION */
    printf("VLAN Trunk Option: %d\n",data.vlantrnkopt);
    llen = sizeof(data.vlantrnkopt); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_VLAN_TRNKOPT; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.vlantrnkopt,llen); /* value */
    len += llen;

    /* VLAN TRUNK ID */
    printf("VLAN TrunkID: ");
    for(j=0;data.vlantrnkid[j]!=0;j++){
        /*printf("vlanid : %d ",trunk_vlan[j]);*/
        printf("%d ",data.vlantrnkid[j]);
    }
    printf("\n");
    llen = (j*sizeof(uint16_t)); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_VLAN_TRNKID; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.vlantrnkid,llen); /* value */
    len += llen;

    /* SVLAN ID */
    printf("SVLAN ID: %d\n",data.svlanid);
    llen = sizeof(data.svlanid); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_VLAN_SVLANID; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.svlanid,llen); /* value */
    len += llen;

    /* SVLAN ETHERTYPE */
    printf("Svlan Ethertype: %s\n",data.svlanethtype);
    llen = strlen(data.svlanethtype); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_VLAN_SVLANETHTYPE; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.svlanethtype,llen); /* value */
    len += llen;

    /* ENCRYPTION TYPE */
    printf("ENCRYPTION TYPE: %d\n",data.encrypttype);
    llen = sizeof(data.encrypttype); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_ENCRYPTION; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.encrypttype,llen); /* value */
    len += llen;
    
    /* ENCRYPTION KEY */
    printf("ENCRYPTION KEY : %s\n",data.enckey);
    llen = strlen(data.enckey); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_CFG_ENCKEY; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.enckey,llen); /* value */
    len += llen;

    buf->hdr.length = len;
    printf("\n Get config Data length: %d\n",buf->hdr.length);

    return;
}

void kwn_set_config_data( kwn_pkt* buf )
{
    uint16_t total_len = buf->hdr.length;
    uint16_t len = 0;
    uint8_t  type = 0;
    uint16_t llen = 0;
    uint8_t  res = 0;
    uint8_t  cmd[100] = {0};

    printf("Total Length : %d \n",total_len);

    while( len < total_len )
    {
        memset(&cmd, '\0', sizeof(cmd));
        memcpy(&llen, buf->data+len, sizeof(uint16_t));
        printf("\nLength %d - ",llen);
        len += sizeof(uint16_t);
        memcpy(&type, buf->data+len, sizeof(uint8_t));
        printf("Type %d - ",type);
        len += sizeof(uint8_t);
        printf("LLEN of data %d - ",llen);
        switch( type )
        {
            uint8_t ip_type;
            case KWN_CFG_IP_TYPE:
            {
                memcpy(&ip_type,buf->data+len,llen);
                printf("IP_TYPE: %d : %s \n",ip_type,*(kwn_ip_type+ip_type));
                sprintf(cmd, "uci set network.lan.proto='%s'", *(kwn_ip_type+ip_type));
                system(cmd);
                break;
            }
            case KWN_CFG_IP:
            {
                uint8_t  bytes[4]={0};

                /* check to handle dhcp case */
                if( ip_type == 2 )
                    break;

                memcpy(&bytes,buf->data+len,llen);
                printf("IP Address: %d.%d.%d.%d\n", bytes[0], bytes[1], bytes[2], bytes[3]); 
                sprintf(cmd, "uci set network.lan.ipaddr='%d.%d.%d.%d'", bytes[0], bytes[1], bytes[2], bytes[3]);
                system(cmd);
                break;
            }
            case KWN_CFG_SSID:
            {
                uint8_t ssid[33]={'\0'};
                memcpy(&ssid,buf->data+len,llen);
                printf("SSID: %s\n",ssid);
                sprintf(cmd, "uci set wireless.@wifi-iface[1].ssid='%s'",ssid);
                system(cmd);
                break;
            }
            case KWN_CFG_OPMODE:
            {
                uint8_t opmode;
                memcpy(&opmode,buf->data+len,llen);
                printf("OPMODE: %d : %s\n",opmode,*(kwn_opmode+opmode));
                sprintf(cmd, "uci set wireless.wifi1.hwmode='%s'", *(kwn_opmode+opmode));
                system(cmd);
                break;
            }
            case KWN_CFG_BANDWIDTH:
            {
                uint8_t bandwidth;
                memcpy(&bandwidth,buf->data+len,llen);
                printf("BANDWIDTH:%d: %s\n",bandwidth,*(kwn_bandwidth+bandwidth));
                sprintf(cmd, "uci set wireless.wifi1.htmode='%s'", *(kwn_bandwidth+bandwidth));
                system(cmd);
                break;
            }
            case KWN_CFG_CHANNEL:
            {
                uint8_t channel;
                memcpy(&channel,buf->data+len,llen);
                printf("channel: %d\n",channel);
                if( channel == 0 )
                    sprintf(cmd, "uci set wireless.wifi1.channel='auto'");
                else
                    sprintf(cmd, "uci set wireless.wifi1.channel='%d'",channel );
                system(cmd);
                break;
            }
            case KWN_CFG_DEV_MODE:
            {
                uint8_t mode;
                memcpy(&mode, buf->data+len,llen);
                printf("Mode: %d : %s \n",mode, *(kwn_dev_mode+mode));
                sprintf(cmd, "uci set wireless.@wifi-iface[1].mode='%s'",*(kwn_dev_mode+mode));
                system(cmd);
                break;
            }
            case KWN_CFG_CTRY:
            {
                uint16_t country;
                memcpy(&country, buf->data+len,llen);
                printf("Country : %d \n",country);
                sprintf(cmd, "uci set wireless.wifi1.country='%d'",country);
                system(cmd);
                break;
            }
            case KWN_CFG_GIP:
            {
                uint8_t  gbytes[4]={0};

                /* check to handle dhcp case */
                if( ip_type == 2 )
                    break;

                memcpy(&gbytes,buf->data+len,llen);
                printf("GIP Address: %d.%d.%d.%d\n", gbytes[0], gbytes[1], gbytes[2], gbytes[3]); 
                sprintf(cmd,"uci set network.lan.gateway='%d.%d.%d.%d'", gbytes[0], gbytes[1], gbytes[2], gbytes[3]);
                system(cmd);
                break;
            }
            case KWN_CFG_NETMASK:
            {
                uint8_t  maskip[4]={0};

                /* check to handle dhcp case */
                if( ip_type == 2 )
                    break;

                memcpy(&maskip,buf->data+len,llen);
                printf("MASKIP Address: %d.%d.%d.%d\n", maskip[0], maskip[1], maskip[2], maskip[3]); 
                sprintf(cmd,"uci set network.lan.netmask='%d.%d.%d.%d'", maskip[0], maskip[1], maskip[2], maskip[3]);
                system(cmd);
                break;
            }
            case KWN_CFG_CUST_NAME:
            {
                uint8_t cust_name[33]={'\0'};
                memcpy(&cust_name,buf->data+len,llen);
                printf("CUSTOMER NAME: %s\n",cust_name);
                sprintf(cmd, "uci set wireless.wifi1.customername='%s'",cust_name);
                system(cmd);
                break;
            }
            case KWN_CFG_LINKID:
            {
                uint8_t linkid[16]={'\0'};
                memcpy(&linkid, buf->data+len,llen);
                printf("Linkid: %s \n",linkid);
                sprintf(cmd, "uci set wireless.wifi1.linkid='%s'",linkid);
                system(cmd);
                break;
            }
            case KWN_CFG_DDRS_STATUS:
            {
                uint8_t ddrs_status;
                memcpy(&ddrs_status,buf->data+len,llen);
                printf("DDRS Status : %d\n",ddrs_status);
                sprintf(cmd, "uci set wireless.wifi1.ddrsstatus='%d'", ddrs_status);
                system(cmd);
                break;
            }
            case KWN_CFG_SPATIAL_STREAM:
            {
                uint8_t spatialstream;
                memcpy(&spatialstream,buf->data+len,llen);
                printf("Spatial Stream : %d\n",spatialstream);
                sprintf(cmd, "uci set wireless.wifi1.spatialstream='%d'", spatialstream);
                system(cmd);
                break;
            }
            case KWN_CFG_MOD_INDEX:
            {
                uint8_t mod_index;
                memcpy(&mod_index,buf->data+len,llen);
                printf("Modulation Index : %d\n",mod_index);
                sprintf(cmd, "uci set wireless.wifi1.ddrsrate='%d'", mod_index);
                system(cmd);
                break;
            }
            case KWN_CFG_MIN_MOD_INDEX:
            {
                uint8_t min_mod_index;
                memcpy(&min_mod_index,buf->data+len,llen);
                printf("Min Modulation Index : %d\n",min_mod_index);
                sprintf(cmd, "uci set wireless.wifi1.ddrsminrate='%d'", min_mod_index);
                system(cmd);
                break;
            }
            case KWN_CFG_MAX_MOD_INDEX:
            {
                uint8_t max_mod_index;
                memcpy(&max_mod_index,buf->data+len,llen);
                printf("Max Modulation Index : %d\n",max_mod_index);
                sprintf(cmd, "uci set wireless.wifi1.ddrsmaxrate='%d'", max_mod_index);
                system(cmd);
                break;
            }
            case KWN_CFG_ATPC_STATUS:
            {
                uint8_t atpc_status;
                memcpy(&atpc_status,buf->data+len,llen);
                printf("ATPC Status : %d\n",atpc_status);
                sprintf(cmd, "uci set wireless.wifi1.atpcstatus='%d'", atpc_status);
                system(cmd);
                break;
            }
            case KWN_CFG_TX_POWER:
            {
                uint8_t tx_power;
                memcpy(&tx_power,buf->data+len,llen);
                printf("TX Power : %d\n",tx_power);
                sprintf(cmd, "uci set wireless.wifi1.atpcpower='%d'", tx_power);
                system(cmd);
                break;
            }
            case KWN_CFG_DISTANCE:
            {
                uint8_t dist;
                memcpy(&dist,buf->data+len,llen);
                printf("Distance : %d\n",dist);
                sprintf(cmd, "uci set wireless.wifi1.distance='%d'", dist);
                system(cmd);
                break;
            }
            case KWN_CFG_VLAN_STATUS:
            {
                uint8_t vlan_status;
                memcpy(&vlan_status,buf->data+len,llen);
                printf("VLAN Status : %d\n",vlan_status);
                sprintf(cmd, "uci set vlan.vlan.status='%d'", vlan_status);
                system(cmd);
                break;
            }
            case KWN_CFG_VLAN_MODE:
            {
                uint8_t vlan_mode;
                memcpy(&vlan_mode,buf->data+len,llen);
                printf("VLAN Mode : %d\n",vlan_mode);
                sprintf(cmd, "uci set vlan.vlan.mode='%d'", vlan_mode);
                system(cmd);
                break;
            }
            case KWN_CFG_VLAN_MGMTID:
            {
                uint16_t vlan_mgmtid;
                memcpy(&vlan_mgmtid,buf->data+len,llen);
                printf("VLAN Mgmtid : %d\n",vlan_mgmtid);
                sprintf(cmd, "uci set vlan.vlan.mgmtvlan='%d'", vlan_mgmtid);
                system(cmd);
                break;
            }
            case KWN_CFG_VLAN_ACCID:
            {
                uint16_t vlan_accid;
                memcpy(&vlan_accid,buf->data+len,llen);
                printf("VLAN Accessid : %d\n",vlan_accid);
                sprintf(cmd, "uci set vlan.vlan.accessvlan='%d'", vlan_accid);
                system(cmd);
                break;
            }
            case KWN_CFG_VLAN_TRNKOPT:
            {
                uint8_t vlan_trunkopt;
                memcpy(&vlan_trunkopt,buf->data+len,llen);
                printf("VLAN Trunkopt : %d\n",vlan_trunkopt);
                sprintf(cmd, "uci set vlan.vlan.trunkoption='%d'", vlan_trunkopt);
                system(cmd);
                break;
            }
            case KWN_CFG_VLAN_TRNKID:
            {
                uint16_t vlan_trunkid[100]={0};
                uint8_t  cmd[KWN_SOCK_BUF_LEN]={'\0'}, a[5]={'\0'};
                uint8_t  str[KWN_SOCK_BUF_LEN]={'\0'};
                uint16_t j;

                printf("VLAN TrunkID : ");
                memcpy(&vlan_trunkid,buf->data+len,llen);
                for( j=0; vlan_trunkid[j]!=0; j++ )
                {   
                    printf( "%d ", vlan_trunkid[j] );
                    sprintf(a,"%d ",vlan_trunkid[j]);
                    strcat(str,a);
                    memset(a,'\0',sizeof(a));
                }
                printf("\n");
                str[strlen(str)-1] = '\0';
                printf("final str:%s\n",str);
                sprintf(cmd, "uci set vlan.vlan.trunkvlan='%s'", str);
                system(cmd);
                break;
            }
            case KWN_CFG_VLAN_SVLANID:
            {
                uint16_t svlanid;
                memcpy(&svlanid,buf->data+len,llen);
                printf("SVLAN ID : %d\n",svlanid);
                sprintf(cmd, "uci set vlan.vlan.svlan='%d'", svlanid);
                system(cmd);
                break;
            }
            case KWN_CFG_VLAN_SVLANETHTYPE:
            {
                uint8_t svlanethtype[7]={'\0'};
                memcpy(&svlanethtype, buf->data+len,llen);
                printf("SVLAN ethertype: %s \n",svlanethtype);
                sprintf(cmd, "uci set vlan.vlan.svlanethertype='%s'",svlanethtype);
                system(cmd);
                break;
            }
            case KWN_CFG_ENCRYPTION:
            {
                uint8_t enctype;
                memcpy(&enctype,buf->data+len,llen);
                printf("Encryption Type : %d\n", *(kwn_enc_type+enctype));
                sprintf(cmd, "uci set wireless.@wifi-iface[1].encryption='%s'", *(kwn_enc_type+enctype));
                system(cmd);
                break;
            }
            case KWN_CFG_ENCKEY:
            {
                uint8_t enckey[64]={'\0'};
                memcpy(&enckey,buf->data+len,llen);
                printf("Encryption Key: %s\n",enckey);
                sprintf(cmd, "uci set wireless.@wifi-iface[1].key='%s'",enckey);
                system(cmd);
                break;
            }
            default:
            break;
        }
        len += llen;
    }
    len = 0;
    type = 0;
    llen = 0;
    memset(buf->data,'\0',KWN_PKT_DATA_SIZE);
    buf->hdr.type = KWN_TYPE_SET_RESPONSE;
    buf->hdr.sub_type = KWN_SUBTYPE_CONFIG_DATA;
    buf->hdr.ptmp = 0;

    /* Response */
    res = KWN_SUCCESS;
    llen = sizeof(res); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_RESPONSE_STATUS; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &res,llen); /* value */
    len += llen;

    buf->hdr.length = len;
    printf("Data length: %d\n",buf->hdr.length);
    system("uci commit");
    system("reload_config");

    sleep(20);
    commit_in_progress = 0;

    return;
}

void kwn_set_link_test( kwn_pkt *buf )
{
    uint16_t total_len = buf->hdr.length;
    uint16_t len = 0;
    uint8_t  type = 0;
    uint16_t llen = 0;
    uint8_t  res = 0;
    uint8_t  cmd[100] = {0};
    uint8_t  start_stop;

    printf("Total Length : %d \n",total_len);

    while( len < total_len )
    {
        memset(&cmd, '\0', sizeof(cmd));
        memcpy(&llen, buf->data+len, sizeof(uint16_t));
        printf("Length %d ",llen);
        len += sizeof(uint16_t);
        memcpy(&type, buf->data+len, sizeof(uint8_t));
        printf("Type %d ",type);
        len += sizeof(uint8_t);
        printf(" LLEN: %d\n",llen);
        switch( type )
        {
            case KWN_LT_START_STOP:
                {
                    memcpy(&start_stop,buf->data+len,llen);
                    printf("Start_Stop: %d\n",start_stop);
                    break;
                }
            case KWN_LT_R_MAC:
                {
                    uint8_t mac[KWN_MAC_ADDR_LEN];
                    memcpy(&mac,buf->data+len,llen);
                    system("iwpriv ath1 kwn_flag 1");
                    printf("MAC = %2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X\n",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
                    sprintf( cmd, "iwpriv ath1 addmac %2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5] );
                    system( cmd );
                    break;
                }
            case KWN_LT_DIRECTION:
                {
                    uint8_t dir;
                    memcpy(&dir,buf->data+len,llen);
                    printf("Direction: %d\n",dir);
                    sprintf( cmd, "iwpriv ath1 kwn_tput_dir %d", dir );
                    system(cmd);
                    break;
                }
            case KWN_LT_DURATION:
                {
                    uint8_t dur;
                    memcpy(&dur,buf->data+len,llen);
                    printf("Duration: %d\n",dur);
                    sprintf( cmd, "iwpriv ath1 kwn_tput_dur %d", dur );
                    system(cmd);
                    break;
                }
            default:
                break;
        }
        len += llen;
    }

    len = 0;
    type = 0;
    llen = 0;
    memset(buf->data,'\0',KWN_PKT_DATA_SIZE);
    buf->hdr.type = KWN_TYPE_SET_RESPONSE;
    buf->hdr.sub_type = KWN_SUBTYPE_LINK_TEST;
    buf->hdr.ptmp = 0;

    /* Response */
    res = KWN_SUCCESS;
    llen = sizeof(res); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_RESPONSE_STATUS; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &res,llen); /* value */
    len += llen;

    buf->hdr.length = len;
    printf("Data length: %d\n",buf->hdr.length);

    system("iwpriv ath1 kwn_tput_cnt 1");
    system("iwpriv ath1 kwn_tput_size 1400");

    if( start_stop == 1 ) 
    {
        system("iwpriv ath1 kwn_tput_test 1");
    }
    else 
    {
        system("iwpriv ath1 kwn_tput_test 0");
    }

    return;
}

void kwn_get_assoclist( kwn_wireless_stats *list )
{
    int sk_fd = -1;
    struct ieee80211req_sta_info *si;
    struct iwreq iwr;
    unsigned char *cp = NULL;
    unsigned char buf[ 24 * 1024 ]  ={ 0 };
    int len = 0;
    int num = 0;

    list->no_of_links = num;
    (void) memset( &iwr, 0, sizeof(iwr) );
    (void) strncpy( iwr.ifr_name, "ath1", sizeof( iwr.ifr_name ) );
    iwr.u.data.pointer = ( void * ) buf;
    iwr.u.data.length = sizeof( buf );
    sk_fd = socket( AF_INET, SOCK_DGRAM, 0 );
    if( sk_fd < 0 ) {
        sk_fd = -1;
        return;
    }
    if( ioctl( sk_fd, IEEE80211_IOCTL_STA_INFO, &iwr ) < 0 ) {
        close( sk_fd );
        return;
    }
    len = iwr.u.data.length;
    if( len < sizeof( struct ieee80211req_sta_info ) ) {
        close( sk_fd );
        return;
    }
    cp = buf;
    do {
        si = ( struct ieee80211req_sta_info * ) cp;
        list->sta[num].link_id = num;
        memcpy( list->sta[num].mac, si->isi_macaddr, KWN_MAC_ADDR_LEN );
        memcpy( list->sta[num].l_latitude, si->isi_l_latitude+5, sizeof(list->sta[num].l_latitude) );
        memcpy( list->sta[num].l_longitude, si->isi_l_longitude+5, sizeof(list->sta[num].l_longitude) );
        memcpy( list->sta[num].r_latitude, si->isi_r_latitude+5, sizeof(list->sta[num].r_latitude) );
        memcpy( list->sta[num].r_longitude, si->isi_r_longitude+5, sizeof(list->sta[num].r_longitude) );
        list->sta[num].tx_tput = (uint16_t)(si->isi_tx_tput / (1000 * 1000) );
        list->sta[num].rx_tput = (uint16_t)(si->isi_rx_tput / (1000 * 1000) );
        list->sta[num].tx_ratekbps = (uint16_t)(si->isi_txratekbps / (1000) );
        list->sta[num].rx_ratekbps = (uint16_t)(si->isi_rxratekbps / (1000) );
        list->sta[num].local_snr_a1 = si->isi_local_snr_a1;
        list->sta[num].remote_snr_a1 = si->isi_remote_snr_a1;
        list->sta[num].local_snr_a2 = si->isi_local_snr_a2;
        list->sta[num].remote_snr_a2 = si->isi_remote_snr_a2;
        kwn_conv_str_to_ip( &si->isi_ip_addr[0], &list->sta[num].r_ip[0] );
        printf("local_ret:%d\n",si->isi_l_rtx);
        list->sta[num].local_link_qindex = ( 100 - si->isi_l_rtx );
        printf("remote_ret:%d\n",si->isi_r_rtx);
        list->sta[num].remote_link_qindex = ( 100 - si->isi_r_rtx );
        /* Local Signal A1 Calculation */
        list->sta[num].local_signal_a1 = ( list->sta[num].local_snr_a1 > 128 ) ? si->isi_l_noise_floor : ( (int16_t)list->sta[num].local_snr_a1 + si->isi_l_noise_floor );
        /* Local Signal A2 Calculation */
        list->sta[num].local_signal_a2 = ( list->sta[num].local_snr_a2 > 128 ) ? si->isi_l_noise_floor : ( (int16_t)list->sta[num].local_snr_a2 + si->isi_l_noise_floor );
        /* Remote Signal A1 Calculation */
        list->sta[num].remote_signal_a1 = ( list->sta[num].remote_snr_a1 > 128 ) ? si->isi_r_noise_floor : ( (int16_t)list->sta[num].remote_snr_a1 + si->isi_r_noise_floor );
        /* Remote Signal A2 Calculation */
        list->sta[num].remote_signal_a2 = ( list->sta[num].remote_snr_a2 > 128 ) ? si->isi_r_noise_floor : ( (int16_t)list->sta[num].remote_snr_a2 + si->isi_r_noise_floor );

#if 0
        printf(" station mac = %2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X\n",
                list->sta[num].mac[0],
                list->sta[num].mac[1],
                list->sta[num].mac[2],
                list->sta[num].mac[3],
                list->sta[num].mac[4],
                list->sta[num].mac[5]);
        printf("L_Lat_Long %s %s, R_Lat_Long %s %s \n",list->sta[num].l_latitude,list->sta[num].l_longitude,list->sta[num].r_latitude,list->sta[num].r_longitude);
        printf("Tx Tput %llu Rx Tput %llu \n",list->sta[num].tx_tput,list->sta[num].rx_tput);
        printf("Local SNR A1 %d SNR A2 %d \n",list->sta[num].local_snr_a1,list->sta[num].local_snr_a2);
        printf("Remote SNR A1 %d SNR A2 %d \n",list->sta[num].remote_snr_a1,list->sta[num].remote_snr_a2);
        printf("IP: %d.%d.%d.%d \n",
                (list->sta[num].ip & 0xFF), (list->sta[num].ip >> 8) & 0xFF,
                (list->sta[num].ip >> 16 ) & 0xFF,(list->sta[num].ip >> 24) & 0xFF);
#endif
        num ++;
        cp += si->isi_len, len -= si->isi_len;
    } while( len >= sizeof( struct ieee80211req_sta_info ) );
    close( sk_fd );
    list->no_of_links = num;

    return;
}

void kwn_get_wireless_stats( kwn_pkt *buf )
{
    uint16_t len = 0;
    uint8_t  type=0;
    uint16_t llen;
    uint32_t num;
    uint8_t  i = 0;

    kwn_wireless_stats wireless_list;
    memset(&wireless_list,'\0', sizeof(kwn_wireless_stats)); 

    kwn_get_assoclist( &wireless_list );

    num = wireless_list.no_of_links;
    printf("Number of links : %d\n",num);

    buf->hdr.type = KWN_TYPE_GET_RESPONSE;
    buf->hdr.sub_type = KWN_SUBTYPE_WIRELESS_STAT;
    buf->hdr.ptmp = 0;

    /* NO_OF_LINKS */
    llen = sizeof(wireless_list.no_of_links); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_WLAN_NO_LINKS; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &wireless_list.no_of_links,llen); /* value */
    len += llen;

    for( i=0; i<num ;i++ )
    {
        /* SU_ID */
        llen = sizeof(wireless_list.sta[i].link_id); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_ID; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].link_id,llen); /* value */
        len += llen;

        printf(" station mac = %2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X\n",
                wireless_list.sta[i].mac[0],
                wireless_list.sta[i].mac[1],
                wireless_list.sta[i].mac[2],
                wireless_list.sta[i].mac[3],
                wireless_list.sta[i].mac[4],
                wireless_list.sta[i].mac[5]);
        /* MAC_ADDRESS */
        llen = KWN_MAC_ADDR_LEN; /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_MAC; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].mac,llen); /* value */
        len += llen;

        printf("Remote IP: %d.%d.%d.%d \n",wireless_list.sta[i].r_ip[0], wireless_list.sta[i].r_ip[1],
                wireless_list.sta[i].r_ip[2], wireless_list.sta[i].r_ip[3]);
        /* IP_ADDRESS */
        llen = sizeof(wireless_list.sta[i].r_ip); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_R_IP; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].r_ip,llen); /* value */
        len += llen;

        printf("L_Lat_Long %s %s, R_Lat_Long %s %s \n",wireless_list.sta[i].l_latitude,wireless_list.sta[i].l_longitude,
                wireless_list.sta[i].r_latitude,wireless_list.sta[i].r_longitude);
        /* REMOTE_LATITUDE */
        llen = (uint16_t)strlen(wireless_list.sta[i].r_latitude); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_R_LAT; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].r_latitude,llen); /* value */
        len += llen;

        /* REMOTE_LONGITUDE */
        llen = (uint16_t)strlen(wireless_list.sta[i].r_longitude); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_R_LONG; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].r_longitude,llen); /* value */
        len += llen;

        /* LOCAL_LATITUDE */
        llen = (uint16_t)strlen(wireless_list.sta[i].l_latitude); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_L_LAT; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].l_latitude,llen); /* value */
        len += llen;

        /* LOCAL_LONGITUDE */
        llen = (uint16_t)strlen(wireless_list.sta[i].l_longitude); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_L_LONG; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].l_longitude,llen); /* value */
        len += llen;

        /* TX_TUPT */
        printf("Tx Tput %u Rx Tput %u \n",wireless_list.sta[i].tx_tput,wireless_list.sta[i].rx_tput);
        llen = sizeof(wireless_list.sta[i].tx_tput); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_TX_TPUT; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].tx_tput,llen); /* value */
        len += llen;

        /* RX_TPUT */
        llen = sizeof(wireless_list.sta[i].rx_tput); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_RX_TPUT; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].rx_tput,llen); /* value */
        len += llen;

        /* LOCAL_SNR_A1 */
        printf("Local SNR A1 %d SNR A2 %d \n",wireless_list.sta[i].local_snr_a1,wireless_list.sta[i].local_snr_a2);
        llen = sizeof(wireless_list.sta[i].local_snr_a1); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_L_SNR_A1; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].local_snr_a1,llen); /* value */
        len += llen;

        /* LOCAL_SNR_A2 */
        llen = sizeof(wireless_list.sta[i].local_snr_a2); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_L_SNR_A2; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].local_snr_a2,llen); /* value */
        len += llen;

        /* REMOTE_SNR_A1 */
        printf("Remote SNR A1 %d SNR A2 %d \n",wireless_list.sta[i].remote_snr_a1,wireless_list.sta[i].remote_snr_a2);
        llen = sizeof(wireless_list.sta[i].remote_snr_a1); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_R_SNR_A1; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].remote_snr_a1,llen); /* value */
        len += llen;

        /* Remote_SNR_A2 */
        llen = sizeof(wireless_list.sta[i].remote_snr_a2); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_R_SNR_A2; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].remote_snr_a2,llen); /* value */
        len += llen;

        /* LOCAL_RATE */
        printf("Local Rate %u Remote Rate %u \n",wireless_list.sta[i].tx_ratekbps,wireless_list.sta[i].rx_ratekbps);
        llen = sizeof(wireless_list.sta[i].tx_ratekbps); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_L_RATE; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].tx_ratekbps,llen); /* value */
        len += llen;

        /* REMOTE_RATE */
        llen = sizeof(wireless_list.sta[i].rx_ratekbps); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_R_RATE; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].rx_ratekbps,llen); /* value */
        len += llen;

        /* LOCAL_SIGNAL_A1 */
        printf("Local Signal A1 %d \n",wireless_list.sta[i].local_signal_a1);
        llen = sizeof(wireless_list.sta[i].local_signal_a1); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_L_SIGNAL_A1; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].local_signal_a1,llen); /* value */
        len += llen;

        /* LOCAL_SIGNAL_A2 */
        printf("Local Signal A2 %d \n",wireless_list.sta[i].local_signal_a2);
        llen = sizeof(wireless_list.sta[i].local_signal_a2); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_L_SIGNAL_A2; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].local_signal_a2,llen); /* value */
        len += llen;

        /* REMOTE_SIGNAL_A1 */
        printf("Remote Signal A1 %d \n",wireless_list.sta[i].remote_signal_a1);
        llen = sizeof(wireless_list.sta[i].remote_signal_a1); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_R_SIGNAL_A1; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].remote_signal_a1,llen); /* value */
        len += llen;

        /* REMOTE_SIGNAL_A2 */
        printf("Remote Signal A2 %d \n",wireless_list.sta[i].remote_signal_a2);
        llen = sizeof(wireless_list.sta[i].remote_signal_a2); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_R_SIGNAL_A2; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].remote_signal_a2,llen); /* value */
        len += llen;

        /* LOCAL LINK QUALITY INDEX */
        printf("Local Link Quality Index %d \n",wireless_list.sta[i].local_link_qindex);
        llen = sizeof(wireless_list.sta[i].local_link_qindex); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_L_LINK_QINDEX; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].local_link_qindex,llen); /* value */
        len += llen;

        /* REMOTE LINK QUALITY INDEX */
        printf("Remote Link Quality Index %d \n",wireless_list.sta[i].remote_link_qindex);
        llen = sizeof(wireless_list.sta[i].remote_link_qindex); /* length */
        memcpy(buf->data+len, &llen,sizeof(uint16_t));
        len += sizeof(uint16_t);
        type = KWN_WLAN_R_LINK_QINDEX; /* type */
        memcpy(buf->data+len, &type,sizeof(uint8_t));
        len += sizeof(uint8_t);
        memcpy(buf->data+len, &wireless_list.sta[i].remote_link_qindex,llen); /* value */
        len += llen;
    }
    buf->hdr.length = len;
    printf("Data length: %d\n",buf->hdr.length);

    return;
}

void kwn_get_ethernet_stats( kwn_pkt* buf)
{
    uint16_t len = 0;
    uint8_t  type=0;
    uint16_t llen;

    kwn_eth_stats data;

    data.tx_packets = 323455647;
    data.rx_packets = 234256456;
    data.tx_bytes   = 457869873;
    data.rx_bytes   = 456576570;
    data.tx_errors  = 493;
    data.rx_errors  = 513;

    buf->hdr.type = KWN_TYPE_GET_RESPONSE;
    buf->hdr.sub_type = KWN_SUBTYPE_ETHERNET_STAT;
    buf->hdr.ptmp = 0;

    /* TX_PACKETS */
    llen = sizeof(data.tx_packets); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_ETH_TX_PACKETS; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.tx_packets,llen); /* value */
    len += llen;

    /* RX_PACKETS */
    llen = sizeof(data.rx_packets); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_ETH_RX_PACKETS; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.rx_packets,llen); /* value */
    len += llen;

    /* TX_BYTES */
    llen = sizeof(data.tx_bytes); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_ETH_TX_BYTES; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.tx_bytes,llen); /* value */
    len += llen;

    /* RX_BYTES */
    llen = sizeof(data.rx_bytes); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_ETH_RX_BYTES; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.rx_bytes,llen); /* value */
    len += llen;

    /* TX_ERRORS */
    llen = sizeof(data.tx_errors); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_ETH_TX_ERRORS; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.tx_errors,llen); /* value */
    len += llen;

    /* RX_ERRORS */
    llen = sizeof(data.rx_errors); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_ETH_RX_ERRORS; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &data.rx_errors,llen); /* value */
    len += llen;

    /*printf("Data length: %d\n",len);*/
    buf->hdr.length = len;
    printf("Data length: %d\n",buf->hdr.length);
}

void kwn_auth_user( kwn_pkt* buf )
{
    uint16_t total_len = buf->hdr.length;
    uint16_t len = 0;
    uint8_t  type = 0;
    uint16_t llen = 0;
    uint8_t  res = 0;
    int cmd_len;
    uint8_t  cmd[100] = {'\0'};
    uint8_t  cmd_buf[33] = {'\0'};
    uint8_t  user[33]={'\0'};
    uint8_t  paswrd[33]={'\0'};

    
    kwn_auth_pkt data;
    memset(&data,'\0', sizeof(kwn_auth_pkt)); 
    
    printf("Total Length : %d \n",total_len);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get system.@system[0].appuser");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    cmd_len = strlen(cmd_buf);
    memcpy(data.usr_name, cmd_buf, cmd_len);
    printf("Struct Username : %s, len: %d\n",data.usr_name, cmd_len);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get system.@system[0].apppass");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    cmd_len = strlen(cmd_buf);
    memcpy(data.passwd, cmd_buf, cmd_len);
    printf("Struct password : %s, len: %d\n",data.passwd, cmd_len);
   
    while( len < total_len )
    {
        memset(&cmd, '\0', sizeof(cmd));
        memcpy(&llen, buf->data+len, sizeof(uint16_t));
        printf("Length %d ",llen);
        len += sizeof(uint16_t);
        memcpy(&type, buf->data+len, sizeof(uint8_t));
        printf("Type %d ",type);
        len += sizeof(uint8_t);
        printf(" LLEN: %d\n",llen);
        switch( type )
        {
            case KWN_AUTH_USERNAME:
                {
                    memcpy(&user,buf->data+len,llen);
                    printf("Username: %s\n",user);
                    break;
                }
            case KWN_AUTH_PASSWORD:
                {
                    memcpy(&paswrd,buf->data+len,llen);
                    printf("Password: %s\n",paswrd);
                    break;
                }
            default:
                break;
        }
        len += llen;
    }

    len = 0;
    type = 0;
    llen = 0;
    memset(buf->data,'\0',KWN_PKT_DATA_SIZE);
    buf->hdr.type = KWN_TYPE_SET_RESPONSE;
    buf->hdr.sub_type = KWN_SUBTYPE_AUTH_LINK;
    buf->hdr.ptmp = 0;

    /* Response */
    if( (strncmp( data.usr_name, user, strlen(user)) == 0) &&
            (strncmp( data.passwd, paswrd, strlen(paswrd)) == 0) ) {
        printf("comparision success");
        res = KWN_SUCCESS;
    }
    else {
        printf("comparision Failure");
        res = KWN_FAILURE;
    } 
    llen = sizeof(res); /* length */
    memcpy(buf->data+len, &llen,sizeof(uint16_t));
    len += sizeof(uint16_t);
    type = KWN_RESPONSE_STATUS; /* type */
    memcpy(buf->data+len, &type,sizeof(uint8_t));
    len += sizeof(uint8_t);
    memcpy(buf->data+len, &res,llen); /* value */
    len += llen;

    buf->hdr.length = len;
    printf("Data length: %d\n",buf->hdr.length);

    return;
}

void kwn_req_type( int peer_sock, kwn_pkt *buf )
{
    int rv;

    /*printf("\n %s : %d \n",__func__,__LINE__);*/
    switch(buf->hdr.type)
    {
        case KWN_TYPE_GET_REQUEST:
            {
                switch(buf->hdr.sub_type)
                {
                    case KWN_SUBTYPE_CONFIG_DATA:
                        {
                            kwn_get_config_data( buf );
                            break;
                        }
                    case KWN_SUBTYPE_WIRELESS_STAT:
                        {
                            kwn_get_wireless_stats( buf );
                            break;
                        }
                    case KWN_SUBTYPE_ETHERNET_STAT:
                        {
                            kwn_get_ethernet_stats( buf );
                            break;
                        }
                    case KWN_SUBTYPE_AUTH_LINK:
                        {
                            kwn_auth_user( buf );
                            break;
                        }
                    default:
                        printf("\n Doesn't match any of the interface sub types \n");
                        break;
                }
                break;
            }
        case KWN_TYPE_SET_REQUEST:
            {
                switch(buf->hdr.sub_type)
                {
                    case KWN_SUBTYPE_CONFIG_DATA:
                        {
                            if( commit_in_progress == 0 )
                            {
                                commit_in_progress = 1;
                                kwn_set_config_data(buf);
                            }
                            break;
                        }
                    case KWN_SUBTYPE_LINK_TEST:
                        {
                            kwn_set_link_test(buf);
                            break;
                        }
                    default:
                        printf("\n Doesn't match any of the interface sub types \n");
                        break;
                }
                break;
            }
        default:
            printf("\n Doesn't match any of the interface types Get/Set \n");
            break;
    }

    printf("Data length: %d\n",buf->hdr.length);
    /**********************************************/
    /* Response data is sent back to the client   */
    /**********************************************/
    rv = send(peer_sock, (void*)buf, sizeof(kwn_pkt), 0);
    if( rv < 0 )
    {
        fprintf(stderr, "Error on send --> %s, errno : %d\n", strerror(errno), errno);
        return;
    }
    printf("\n message sent : %d bytes \n",rv);
    return;
}


int main()
{
    int server_socket, peer_sock;
    int len, opt=1, max_sd, i, close_conn, flag, max_sdl;
    struct sockaddr_in server_addr;
    struct sockaddr_in peer_addr;
    int sock_len = sizeof(peer_addr), rv, flags;
    char cmd[100],cmd_buf[50];
    fd_set master_set,working_set;

    kwn_pkt kwn_server_recv_buf;
    memset(&kwn_server_recv_buf,'\0', sizeof(kwn_pkt)); 

    /*******************************************************************/
    /* Create an AF_INET stream socket to receive incoming connections */
    /*******************************************************************/
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if( server_socket < 0 )
    {
        fprintf(stderr, "Error creating socket --> %s, errno : %d", strerror(errno), errno);
        exit(EXIT_FAILURE);
    }

    /*************************************************************/
    /* Allow socket descriptor to be reuseable                   */
    /*************************************************************/
    rv = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
    if( rv < 0 )
    {
        fprintf(stderr, "Error setsockopt --> %s, errno : %d", strerror(errno), errno);
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get system.@system[0].tcpcnt");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    flags = (uint8_t)atoi(cmd_buf);
    printf("tcp_cnt value = %d\n",flags);
    
    rv = setsockopt( server_socket, SOL_TCP, TCP_KEEPCNT, (void *)&flags, sizeof(flags) );
    if( rv < 0 )
    {
        fprintf(stderr, "Error setsockopt --> %s, errno : %d", strerror(errno), errno);
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get system.@system[0].tcpintvl");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    flags = (uint8_t)atoi(cmd_buf);
    printf("tcp_intvl value = %d\n",flags);
    
    rv = setsockopt( server_socket, SOL_TCP, TCP_KEEPINTVL, (void *)&flags, sizeof(flags) );
    if( rv < 0 )
    {
        fprintf(stderr, "Error setsockopt --> %s, errno : %d", strerror(errno), errno);
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    /*************************************************************/
    /* Set socket to be nonblocking. All of the sockets for      */
    /* the incoming connections will also be nonblocking since   */
    /* they will inherit that state from the listening socket.   */
    /*************************************************************/
    /* Get Socket Flag */
    flag = fcntl(server_socket, F_GETFL, 0);
    if( flag < 0 )
    {
        fprintf(stderr, "Error get fcntl --> %s, errno : %d", strerror(errno), errno);
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    /* Set Socket Flag to Non-Blocking Mode */
    rv = fcntl(server_socket, F_SETFL, flag | O_NONBLOCK);
    if( rv < 0 )
    {
        fprintf(stderr, "Error set fcntl --> %s, errno : %d", strerror(errno), errno);
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    /* Zeroing server_addr struct */
    memset(&server_addr, 0, sizeof(server_addr));
    /* Construct server_addr struct */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(KWN_PORT);

    /*************************************************************/
    /* Bind the socket                                           */
    /*************************************************************/
    rv = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if( rv < 0 )
    {
        fprintf(stderr, "Error binding --> %s, errno : %d", strerror(errno), errno);
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    /*************************************************************/
    /* Set the listen back log                                   */
    /*************************************************************/
    rv = listen(server_socket, 10);
    if( rv < 0 )
    {
        fprintf(stderr, "Error listening --> %s, errno : %d", strerror(errno), errno);
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    /*************************************************************/
    /* Initialize the master fd_set                              */
    /*************************************************************/
    FD_ZERO(&master_set);
    max_sd = server_socket;
    FD_SET(server_socket, &master_set);

    /*************************************************************/
    /* Loop waiting for incoming connects or for incoming data   */
    /* on any of the connected sockets.                          */
    /*************************************************************/
    while(KWN_TRUE)
    {
        /**********************************************************/
        /* Copy the master fd_set over to the working fd_set.     */
        /**********************************************************/
        memcpy(&working_set, &master_set, sizeof(master_set));

        /****************************************************************/
        /* Call select() and block indefinitely since timeout is NULL   */
        /****************************************************************/
        rv = select(max_sd + 1, &working_set, NULL, NULL, NULL);
        if( rv < 0 )
        {
            fprintf(stderr, "Error select call --> %s, errno : %d", strerror(errno), errno);
            break;
        }
        //printf("file descriptors ready for reading : %d\n",rv);
        /* update max_sdl*/
        max_sdl = max_sd;

        /**********************************************************/
        /* One or more descriptors are readable.  Need to         */
        /* determine which ones they are.                         */
        /**********************************************************/
        for( i=0; i <= max_sd  ; i++ )
        {
            /*******************************************************/
            /* Check to see if this descriptor is ready            */
            /*******************************************************/
            if( FD_ISSET( i, &working_set ) )
            {
                /****************************************************/
                /* Check to see if this is the listening socket     */
                /****************************************************/
                if( i == server_socket )
                {
                    peer_sock = accept( server_socket, (struct sockaddr *)&peer_addr, &sock_len );
                    if( peer_sock < 0 )
                    {
                        /************************************************************************/
                        /* If accept fails with EWOULDBLOCK, then we have accepted all of them. */
                        /* Any other failure on accept will cause us to end the server          */
                        /************************************************************************/
                        if (errno != EWOULDBLOCK)
                        {
                            fprintf(stderr, "Error on accept --> %s, errno : %d", strerror(errno), errno);
                            close_conn = KWN_TRUE;
                        }
                    }

                    flags = 1;
                    rv = setsockopt( peer_sock, SOL_SOCKET, SO_KEEPALIVE, (void *)&flags, sizeof(flags) );
                    if( rv < 0 )
                    {
                        fprintf(stderr, "Error setsockopt --> %s, errno : %d", strerror(errno), errno);
                    }

                    /**********************************************/
                    /* Add the new incoming connection to the     */
                    /* master read set                            */
                    /**********************************************/
                    printf(" New incoming connection - %d : %s\n", peer_sock, inet_ntoa(peer_addr.sin_addr));
                    FD_SET(peer_sock, &master_set);
                    max_sdl = peer_sock;
                }
                /****************************************************/
                /* This is not the listening socket, therefore an   */
                /* existing connection must be readable             */
                /****************************************************/
                else
                {
                    /*printf("  Descriptor %d is readable\n", i);*/
                    close_conn = KWN_FALSE;
                    /*************************************************************/
                    /* Receive data on this connection until the  recv fails.    */
                    /* If any other failure occurs, we will close the connection */
                    /*************************************************************/
                    rv = recv( i, &kwn_server_recv_buf, sizeof(kwn_pkt), 0 );
                    if( rv < 0 )
                    {
                        /*************************************************************/
                        /* If no messages are available at the socket and O_NONBLOCK */ 
                        /* is set on the socket's file descriptor, recv() shall fail */
                        /* and set errno to [EAGAIN] or [EWOULDBLOCK]                */
                        /*************************************************************/
                        if( errno != EWOULDBLOCK )
                        {
                            fprintf(stderr, "Error on recv --> %s, errno : %d\n", strerror(errno), errno);
                            close_conn = KWN_TRUE;
                        }
                    }

                    /****************************************************************/
                    /* Check to see if the connection has been closed by the client */
                    /****************************************************************/
                    if( rv == 0 )
                    {
                        /* printf("  Connection closed\n"); */
                        close_conn = KWN_TRUE;
                    }

                    /**********************************************/
                    /* Data was received                          */
                    /**********************************************/
                    len = rv;
                    if( len > 0 )
                    {
                        printf("  %d bytes received\n", len);        
                        printf("Received ID:%d, Intf type:%d, Type:%d, Subtype:%d\n",
                                kwn_server_recv_buf.hdr.id, kwn_server_recv_buf.hdr.interface_type,
                                kwn_server_recv_buf.hdr.type, kwn_server_recv_buf.hdr.sub_type);

                        switch(kwn_server_recv_buf.hdr.id)
                        {
                            case SIFY_ID:
                            case KEYWEST_ID:
                                {
                                    switch(kwn_server_recv_buf.hdr.interface_type)
                                    {
                                        case KWN_MOBILE_APP:
                                        case KWN_NMS_APP:
                                            {
                                                kwn_req_type(i, &kwn_server_recv_buf);
                                                printf(" close_conn value : %d \n",close_conn);
                                                if( close_conn )
                                                {
                                                    printf("Doesn't match any of the subtypes or a send error\n");
                                                }
                                                break;
                                            }
                                        default:
                                            {
                                                printf("\n Doesn't match any of the interface types \n");
                                                break;
                                            }
                                    }
                                    break;
                                }
                            default:
                                {
                                    printf("Doesn't match any of the ID's\n");
                                    break;
                                }
                        }
                        memset(&kwn_server_recv_buf,'\0', sizeof(kwn_pkt));
                    }

                    /*********************************************************************************************/
                    /* If the close_conn flag was turned on, clear the active connection which includes removing */ 
                    /* the descriptor from the master set and determining the new maximum descriptor value based */
                    /* on the bits that are still turned on in the master set.                                   */
                    /*********************************************************************************************/
                    if( close_conn )
                    {
                        close(i);
                        FD_CLR(i, &master_set);
                        if( i == max_sd )
                        {
                            max_sd -= 1;
                        }
                        max_sdl = max_sd;
                        close_conn = KWN_FALSE;
                    }
                } /* End of existing connection is readable */
            } /* End of if ( FD_ISSET( i, &working_set ) ) */
        } /* End of loop through selectable descriptors */
        if( max_sdl > max_sd )
            max_sd = max_sdl;
    } /* End of while loop */

    /*************************************************************/
    /* Clean up all of the sockets that are open                 */
    /*************************************************************/
    for( i=0; i <= max_sd; i++ )
    {
        close(i);
    }
    return 0;
}

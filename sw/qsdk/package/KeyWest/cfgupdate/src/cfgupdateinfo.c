

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/types.h>
#include <linux/if.h>
#include <linux/wireless.h>
#include <linux/if_arp.h>
#include <string.h>


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <sys/ioctl.h> 
#include <sys/time.h>
#include <signal.h>
#include <linux/ioctl.h>
#include <uci.h>
#include "cfgupdate.h"

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

#define GET_CFG_FILE "/tmp/getcfgfile.txt"
#define SET_CFG_FILE "/tmp/setcfgfile.txt"

void set_cfgtxtfile();
void set_linktest();
void get_assoclist();

int main()
{
//	get_assoclist();
	set_cfgtxtfile();
//	set_linktest();
	return 0;
}

void kwn_sys_cmd_imp( const char* cmd, uint8_t* cmd_buf )
{
    FILE *fp = NULL;
    uint8_t  a[33]={0};
    uint8_t  *token;
    uint16_t len;

    fp = popen(cmd,"r");
    if( fp == NULL )
        return;
    while( fgets(a, sizeof(a), fp) != NULL)
    {
        /*printf("%s",a);*/
    }
    pclose(fp);

    token = strtok(a,"\n");
    len = strlen(token);
    memcpy(cmd_buf,token,len);
    return;
}

void kwn_bw_change()
{
    char cmd[50];
    uint8_t cmd_buf[50];
    long ullmt, dllmt;

    /* Get Bandwidth */
    memset(cmd, '\0', sizeof(cmd));
    memset( cmd_buf, '\0', sizeof( cmd_buf ) );
    sprintf(cmd,"uci get wireless.wifi1.htmode");
    kwn_sys_cmd_imp( cmd, &cmd_buf[0] );

    if( !strcmp( cmd_buf, "HT20" )  ) {
        ullmt = 192000;
        dllmt = 192000;
    }
    else if( !strcmp( cmd_buf, "HT40+" ) || !strcmp( cmd_buf, "HT40-") ) {
        ullmt = 400000;
        dllmt = 400000;
    }
    else if( !strcmp( cmd_buf, "HT80" )  ) {
        ullmt = 867000;
        dllmt = 867000;
    }
    else {
        ullmt = 73000;
        dllmt = 73000;
    }
    sprintf( cmd, "uci set wireless.@wifi-iface[1].ullmt='%d'", ullmt );
    system( cmd );
    sprintf( cmd, "uci set wireless.@wifi-iface[1].dllmt='%d'", dllmt );
    system( cmd );
}

void kwn_reset_channel()
{
#define RUSSIA   5011
#define INDIA_UL 5016
#define INDIA_L  5017
    
    char cmd[100];
    uint8_t cmd_buf[50];
    int def_chan = 165;
    int coun;

    /* Get Country */
    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get wireless.wifi1.country");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    coun = atoi( cmd_buf );

    /* Get Radio Mode */
    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get wireless.@wifi-iface[1].mode");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 

    if( !strcmp( cmd_buf, "sta" ) ) {
        system("uci set wireless.wifi1.channel='auto'");
        return;
    }
    switch( coun )
    {
        case RUSSIA:
            def_chan = 100; /* 200 to 183 */
            break;
        case INDIA_UL:
            def_chan = 170; /* 165 to 175 */
            break;
        case INDIA_L:
            def_chan = 160; /* 145 to 175 */
            break;
        default:
            break;
    }
    memset( cmd, '\0', sizeof( cmd ) );
    sprintf( cmd, "uci set wireless.wifi1.channel='%d'",def_chan );
    system( cmd );
}

void kwn_reset_datarate( int stream )
{
    char cmd[100];
    uint8_t cmd_buf[50];
    uint8_t min_srate = 0, max_srate = 9, min_drate = 10, max_drate = 19;
    uint8_t srate = 3, drate = 13;

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get wireless.wifi1.hwmode");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    if( !strcmp( cmd_buf, "11a" ) ) {
        drate = 3;
        stream = 1;
        min_srate = 0;
        max_srate = 7;
        min_drate = 0;
        max_drate = 7;
    }
    if( !strcmp( cmd_buf, "11na" ) ) {
        drate = 11;
        min_srate = 0;
        max_srate = 7;
        min_drate = 8;
        max_drate = 15;
    }
    sprintf(cmd,"uci set wireless.wifi1.spatialstream='%d'",stream);
    system(cmd);
    if( stream == 1 ) {
        sprintf(cmd,"uci set wireless.wifi1.ddrsrate='%d'",srate);
        system(cmd);
        sprintf(cmd,"uci set wireless.wifi1.ddrsminrate='%d'",min_srate);
        system(cmd);
        sprintf(cmd,"uci set wireless.wifi1.ddrsmaxrate='%d'",max_srate);
        system(cmd);
    }
    else if( stream == 2 ) {
        sprintf(cmd,"uci set wireless.wifi1.ddrsrate='%d'",drate);
        system(cmd);
        sprintf(cmd,"uci set wireless.wifi1.ddrsminrate='%d'",min_drate);
        system(cmd);
        sprintf(cmd,"uci set wireless.wifi1.ddrsmaxrate='%d'",max_drate);
        system(cmd);
    }
    else {
        sprintf(cmd,"uci set wireless.wifi1.ddrsrate='3'");
        system(cmd);
        sprintf(cmd,"uci set wireless.wifi1.ddrsminrate='%d'",min_srate);
        system(cmd);
        sprintf(cmd,"uci set wireless.wifi1.ddrsmaxrate='%d'",max_drate);
        system(cmd);
    }
}

void kwn_reset_tx_params()
{
    int stream = 1; /* Single */

    system("uci set wireless.wifi1.ddrsstatus='1'");
    kwn_reset_datarate( stream );
}

void kwn_reset_nwkmode_params()
{
    char cmd[100];
    uint8_t cmd_buf[50];
    uint8_t rad_mode[10];

    /* Get Radio Mode */
    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get wireless.@wifi-iface[1].mode");
    kwn_sys_cmd_imp( &cmd[0], &rad_mode[0] );

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get network.param.networkmode");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 

    if( ( strcmp(rad_mode,"sta") == 0 ) && ( strcmp(cmd_buf,"2") == 0 ) ) {
        sprintf(cmd,"uci set network.lan.proto='static'");
        system(cmd);
        sprintf(cmd,"uci set network.lan.ipaddr='192.168.3.1'");
        system(cmd);
        sprintf(cmd,"uci set network.lan.netmask='255.255.255.0'");
        system(cmd);
        sprintf(cmd,"uci set network.lan.gateway='192.168.3.1'");
        system(cmd);
    }
    else {
        sprintf(cmd,"uci set network.lan.proto='static'");
        system(cmd);
        sprintf(cmd,"uci set network.lan.ipaddr='192.168.1.1'");
        system(cmd);
        sprintf(cmd,"uci set network.lan.netmask='255.255.255.0'");
        system(cmd);
        sprintf(cmd,"uci set network.lan.gateway='192.168.1.1'");
        system(cmd);
    }
}

void kwn_reset_radioparams()
{
    kwn_reset_channel();
    kwn_reset_nwkmode_params();
}

void cfg_set( char *type, char *value )
{
    char cmd[500];
    char cmd1[500];
    int type2 = atoi( type );

    memset(cmd, '\0', sizeof(cmd) );
    memset(cmd1, '\0', sizeof(cmd1) );
    printf("Type %s Value %s \n",type, value);

    switch( type2 )
    {
        case UCI_ID_RADIO1_MODE:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].mode='%s'",value);
            system( cmd );
            kwn_reset_radioparams();
            break;
        case UCI_ID_RADIO1_SSID:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].ssid='%s'",value);
            break;
        case UCI_ID_RADIO1_COUNTRY:
            sprintf(cmd,"uci set wireless.wifi1.country='%s'",value);
            system(cmd);
            kwn_reset_channel();
            break;
        case UCI_ID_RADIO1_OPMODE:
            sprintf(cmd,"uci set wireless.wifi1.hwmode='%s'",value);
            system( cmd );
            /* Reset Tx params */
            kwn_reset_tx_params();
            break;
        case UCI_ID_RADIO1_BANDWIDTH:
            sprintf(cmd,"uci set wireless.wifi1.htmode='%s'",value);
            system( cmd );
            kwn_bw_change();
            break;
        case UCI_ID_RADIO1_CHANNEL:
            sprintf(cmd,"uci set wireless.wifi1.channel='%s'",value);
            break;
        case UCI_ID_RADIO1_RATE:
            sprintf(cmd,"uci set wireless.wifi1.rate='%s'",value);
            break;
        case UCI_ID_RADIO1_POWER:
            sprintf(cmd,"uci set wireless.wifi1.TXPowLim5G='%s'",value);
            break;
        case UCI_ID_RADIO1_AMSDU:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].amsdu='%s'",value);
            break;
        case UCI_ID_RADIO1_UPLINK_LMT:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].ullmt='%s'",value);
            break;
        case UCI_ID_RADIO1_DOWNLINK_LMT:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].dllmt='%s'",value);
            break;
        case UCI_ID_RADIO1_HIDE_ESSID:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].hidden='%s'",value);
            break;
        case UCI_ID_RADIO1_CUSTOMER_NAME:
            sprintf(cmd,"uci set wireless.wifi1.customername='%s'",value);
            break;
        case UCI_ID_RADIO1_LINK_ID:
            sprintf(cmd,"uci set wireless.wifi1.linkid='%s'",value);
            break;
        case UCI_ID_RADIO2_MODE:
            sprintf(cmd,"uci set wireless.@wifi-iface[0].mode='%s'",value);
            break;
        case UCI_ID_RADIO2_SSID:
            sprintf(cmd,"uci set wireless.@wifi-iface[0].ssid='%s'",value);
            break;
        case UCI_ID_RADIO2_COUNTRY:
            sprintf(cmd,"uci set wireless.wifi0.country='%s'",value);
            break;
        case UCI_ID_RADIO2_OPMODE:
            sprintf(cmd,"uci set wireless.wifi0.hwmode='%s'",value);
            break;
        case UCI_ID_RADIO2_BANDWIDTH:
            sprintf(cmd,"uci set wireless.wifi0.htmode='%s'",value);
            break;
        case UCI_ID_RADIO2_CHANNEL:
            sprintf(cmd,"uci set wireless.wifi0.channel='%s'",value);
            break;
        case UCI_ID_RADIO2_POWER:
            sprintf(cmd,"uci set wireless.wifi0.TXPowLim2G='%s'",value);
            break;
        case UCI_ID_RADIO2_HIDE_ESSID:
            sprintf(cmd,"uci set wireless.@wifi-iface[0].hidden='%s'",value);
            break;
        case UCI_ID_IP:
            sprintf(cmd,"uci set network.lan.ipaddr='%s'",value);
            break;
        case UCI_ID_ADDR_TYPE:
            sprintf(cmd,"uci set network.lan.proto='%s'",value);
            break;
        case UCI_ID_MASK:
            sprintf(cmd,"uci set network.lan.netmask='%s'",value);
            break;
        case UCI_ID_GATEWAY:
            sprintf(cmd,"uci set network.lan.gateway='%s'",value);
            break;
        case UCI_ID_DNS_IP:
            sprintf(cmd,"uci set network.lan.dns='%s'",value);
            break;
        case UCI_ID_RADIO1_SECURITY_ENC:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].encryption='%s'",value);
            break;
        case UCI_ID_RADIO1_SECURITY_KEY:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].key='%s'",value);
            break;
        case UCI_ID_RADIO2_SECURITY_ENC:
            sprintf(cmd,"uci set wireless.@wifi-iface[0].encryption='%s'",value);
            break;
        case UCI_ID_RADIO2_SECURITY_KEY:
            sprintf(cmd,"uci set wireless.@wifi-iface[0].key='%s'",value);
            break;
        case UCI_ID_RADIUS_STATUS:
            {
                int val = atoi(value);
                if( val == 0 )
                    sprintf(cmd,"uci delete wrt-radauth.sys.enableRadAuth");
                else
                    sprintf(cmd,"uci set wrt-radauth.sys.enableRadAuth='%s'",value);
            }
            break;
        case UCI_ID_RADIUS_PRI_SERVER:
            sprintf(cmd,"uci set wrt-radauth.sys.primaryServer='%s'",value);
            break;
        case UCI_ID_RADIUS_PRI_PORT:
            sprintf(cmd,"uci set wrt-radauth.sys.primaryPort='%s'",value);
            break;
        case UCI_ID_RADIUS_PRI_SECRET:
            sprintf(cmd,"uci set wrt-radauth.sys.primarySecret='%s'",value);
            break;
        case UCI_ID_RADIUS_SEC_SERVER:
            sprintf(cmd,"uci set wrt-radauth.sys.secondaryServer='%s'",value);
            break;
        case UCI_ID_RADIUS_SEC_PORT:
            sprintf(cmd,"uci set wrt-radauth.sys.secondaryPort='%s'",value);
            break;
        case UCI_ID_RADIUS_SEC_SECRET:
            sprintf(cmd,"uci set wrt-radauth.sys.secondarySecret='%s'",value);
            break;
        case UCI_ID_RADIUS_REAUTH_TIME:
            sprintf(cmd,"uci set wrt-radauth.sys.reauthTime='%s'",value);
            break;
        case UCI_ID_RADIUS_RETRY_TIME:
            sprintf(cmd,"uci set wrt-radauth.sys.retryTime='%s'",value);
            break;
        case UCI_ID_RADIUS_RETRY_COUNT:
            sprintf(cmd,"uci set wrt-radauth.sys.requestRetries='%s'",value);
            break;
        case UCI_ID_RADIUS_RETRY_COUNT_PERIOD:
            sprintf(cmd,"uci set wrt-radauth.sys.requestTimeout='%s'",value);
            break;
        case UCI_ID_ETHERNET_SPEED:
            sprintf(cmd,"uci set ethernet.ethernet.mode='%s'",value);
            break;
        case UCI_ID_DHCP_SERVER:
            sprintf(cmd,"uci set dhcp.lan.ignore='%s'",value);
            break;
        case UCI_ID_DHCP_START:
            sprintf(cmd,"uci set dhcp.lan.start='%s'",value);
            break;
        case UCI_ID_DHCP_LIMIT:
            sprintf(cmd,"uci set dhcp.lan.limit='%s'",value);
            break;
        case UCI_ID_DHCP_LEASE_TIME:
            sprintf(cmd,"uci set dhcp.lan.leasetime='%s'",value);
            break;
        case UCI_ID_RADIO1_MACFILTER:
            {
                if( !strcmp( value, "disable" ) ) {
                    sprintf(cmd,"uci delete wireless.@wifi-iface[1].macfilter");
                    system( cmd );
                    sprintf(cmd,"uci delete wireless.@wifi-iface[1].maclist");
                }
                else {
                    sprintf(cmd,"uci set wireless.@wifi-iface[1].macfilter='%s'",value);
                }
            }
            break;
        case UCI_ID_RADIO1_MACLIST:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].maclist='%s'",value);
            break;
        case UCI_ID_RADIO2_MACFILTER:
            {
                if( !strcmp( value, "disable" ) ) {
                    sprintf(cmd,"uci delete wireless.@wifi-iface[0].macfilter");
                    system( cmd );
                    sprintf(cmd,"uci delete wireless.@wifi-iface[0].maclist");
                }
                else {
                    sprintf(cmd,"uci set wireless.@wifi-iface[0].macfilter='%s'",value);
                }
            }
            break;
        case UCI_ID_RADIO2_MACLIST:
            sprintf(cmd,"uci set wireless.@wifi-iface[0].maclist='%s'",value);
            break;
        case UCI_ID_VLAN_STATUS:
            sprintf(cmd,"uci set vlan.vlan.status='%s'",value);
            break;
        case UCI_ID_VLAN_MODE:
            sprintf(cmd,"uci set vlan.vlan.mode='%s'",value);
            break;
        case UCI_ID_VLAN_MGMT_VLAN:
            sprintf(cmd,"uci set vlan.vlan.mgmtvlan='%s'",value);
            break;
        case UCI_ID_VLAN_ACCESS_VLAN:
            sprintf(cmd,"uci set vlan.vlan.accessvlan='%s'",value);
            break;
        case UCI_ID_VLAN_TRUNK_OPTION:
            sprintf(cmd,"uci set vlan.vlan.trunkoption='%s'",value);
            break;
        case UCI_ID_VLAN_TRUNK_VLAN:
            sprintf(cmd,"uci set vlan.vlan.trunkvlan='%s'",value);
            break;
        case UCI_ID_VLAN_SVLAN:
            sprintf(cmd,"uci set vlan.vlan.svlan='%s'",value);
            break;
        case UCI_ID_VLAN_SVLAN_ETHER_TYPE:
            sprintf(cmd,"uci set vlan.vlan.svlanethertype='%s'",value);
            break;
        case UCI_ID_HOSTNAME:
            sprintf(cmd,"uci set system.@system[0].hostname='%s'",value);
            break;
        case UCI_ID_TIMEZONE:
            sprintf(cmd,"uci set system.@system[0].timezone='%s'",value);
            break;
        case UCI_ID_GPS:
            sprintf(cmd,"uci set system.gps.status='%s'",value);
            break;
        case UCI_ID_GPS_INT:
            sprintf(cmd,"uci set system.gps.interval='%s'",value);
            break;
        case UCI_ID_DYING_GASP:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].dyinggasp='%s'",value);
            break;
        case UCI_ID_LEDS:
            sprintf(cmd,"uci set system.led.status='%s'",value);
            break;
        case UCI_ID_SYSLOG_SERVER:
            sprintf(cmd,"uci set system.@system[0].log_ip='%s'",value);
            break;
        case UCI_ID_SYSLOG_SERVER_PORT:
            sprintf(cmd,"uci set system.@system[0].log_port='%s'",value);
            break;
        case UCI_ID_TEMP_LOG:
            sprintf(cmd,"uci set system.@system[0].templogstatus='%s'",value);
            break;
        case UCI_ID_TEMP_LOG_INT:
            sprintf(cmd,"uci set system.@system[0].temploginterval='%s'",value);
            break;
        case UCI_ID_ZONENAME:
            sprintf(cmd,"uci set system.@system[0].zonename='%s'",value);
            break;
        case UCI_ID_NTP_SERVER:
            sprintf(cmd,"uci set system.ntp.server='%s'",value);
            break;
        case UCI_ID_NTP:
            sprintf(cmd,"uci set system.ntp.enabled='%s'",value);
            break;
        case UCI_ID_DISTANCE:
            sprintf(cmd,"uci set wireless.wifi1.distance='%s'",value);
            break;
        case UCI_ID_RADIO1_SHORTGI:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].shortgi='%s'",value);
            break;
        case UCI_ID_RADIO1_TXCHAINMASK:
            sprintf(cmd,"uci set wireless.wifi1.txchainmask='%s'",value);
            break;
        case UCI_ID_RADIO1_RXCHAINMASK:
            sprintf(cmd,"uci set wireless.wifi1.rxchainmask='%s'",value);
            break;
        case UCI_ID_ETHERNET_INACTIVITY:
            sprintf(cmd,"uci set ethernet.ethernet.ethtimer='%s'",value);
            break;
        case UCI_ID_LINK_TEST_SIZE:
            sprintf(cmd,"uci set tool.tool.size='%s'",value);
            break;
        case UCI_ID_LINK_TEST_DUR:
            sprintf(cmd,"uci set tool.tool.dur='%s'",value);
            break;
        case UCI_ID_LINK_TEST_DIR:
            sprintf(cmd,"uci set tool.tool.dir='%s'",value);
            break;
        case UCI_ID_VLAN_BDA:
            sprintf(cmd,"uci set vlan.vlan.bda='%s'",value);
            break;
        case UCI_ID_VLAN_BSA:
            sprintf(cmd,"uci set vlan.vlan.bsa='%s'",value);
            break;
        case UCI_ID_VLAN_BVID:
            sprintf(cmd,"uci set vlan.vlan.bvid='%s'",value);
            break;
        case UCI_ID_VLAN_BISID:
            sprintf(cmd,"uci set vlan.vlan.bisid='%s'",value);
            break;
        case UCI_ID_DG_DISABLE_ACK:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].dgackdisable='%s'",value);
            break;
        case UCI_ID_SNMP_STATUS:
            sprintf(cmd,"uci set snmpd.public_access.version='%s'",value);
            break;
        case UCI_ID_SNMP_VERSION:
            sprintf(cmd,"uci set snmpd.public_access.version='%s'",value);
            break;
        case UCI_ID_SNMP_RW_PASWD:
            sprintf(cmd,"uci set snmpd.public.community='%s'",value);
            break;
        case UCI_ID_SNMP_TRPA_HOST_IP:
            sprintf(cmd,"uci set snmpd.trapaddress.host='%s'",value);
            break;
        case UCI_ID_SNMP_TRAP_HOST_PWD:
            sprintf(cmd,"uci set snmpd.trapaddress.paswd='%s'",value);
            break;
        case UCI_ID_HTTP_STATUS:
            {
                int val = atoi(value);
                if( val == 0 ) {
                    sprintf(cmd,"uci delete uhttpd.main.listen_http");
                }
                else {
                    sprintf(cmd,"uci set uhttpd.main.listen_http='0.0.0.0:80'");
                }
            }
            break;
        case UCI_ID_HTTP_ADMIN_PWD:
            system("uci set uhttpd.main.pwdmodified='1'");
            sprintf(cmd,"uci set uhttpd.main.adminpwd='%s'",value);
            break;
        case UCI_ID_HTTP_USER_PWD:
            system("uci set uhttpd.main.pwdmodified='1'");
            sprintf(cmd,"uci set uhttpd.main.userpwd='%s'",value);
            break;
        case UCI_ID_HTTP_SUPER_PWD:
            system("uci set uhttpd.main.pwdmodified='1'");
            sprintf(cmd,"uci set uhttpd.main.superpwd='%s'",value);
            break;
        case UCI_ID_HTTP_PORT:
            sprintf(cmd,"uci set uhttpd.main.listen_http='0.0.0.0:%s'",value);
            break;
        case UCI_ID_HTTPS_STATUS:
            {
                int val = atoi(value);
                if( val == 0 ) {
                    sprintf(cmd,"uci delete uhttpd.main.listen_https");
                }
                else {
                    sprintf(cmd,"uci set uhttpd.main.listen_https='0.0.0.0:443'");
                }
            }
            break;
        case UCI_ID_HTTPS_PORT:
            sprintf(cmd,"uci set uhttpd.main.listen_https='0.0.0.0:%s'",value);
            break;
        case UCI_ID_TELNET_STATUS:
            sprintf(cmd,"uci set telnetssh.telnet.status='%s'",value);
            break;
        case UCI_ID_TELNET_PORT:
            sprintf(cmd,"uci set telnetssh.telnet.port='%s'",value);
            break;
        case UCI_ID_TELNET_SESSIONS:
            sprintf(cmd,"uci set telnetssh.telnet.sessions='%s'",value);
            break;
        case UCI_ID_SSH_STATUS:
            sprintf(cmd,"uci set telnetssh.ssh.status='%s'",value);
            break;
        case UCI_ID_SSH_PORT:
            sprintf(cmd,"uci set telnetssh.ssh.port='%s'",value);
            break;
        case UCI_ID_SSH_SESSIONS:
            sprintf(cmd,"uci set telnetssh.ssh.sessions='%s'",value);
            break;
        case UCI_ID_RADIO1_AMPDU:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].ampdu='%s'",value);
            break;
        case UCI_ID_RADIO1_DDRS_STATUS:
            {
                int val = atoi(value);
                int stream = 1;
                if( val == 1 ) {
                    stream = 1;
                }
                kwn_reset_datarate( stream );
                sprintf(cmd,"uci set wireless.wifi1.ddrsstatus='%s'",value);
            }
            break;
        case UCI_ID_RADIO1_DDRS_RATE:
            sprintf(cmd,"uci set wireless.wifi1.ddrsrate='%s'",value);
            break;
        case UCI_ID_RADIO1_DDRS_MIN_RATE:
            sprintf(cmd,"uci set wireless.wifi1.ddrsminrate='%s'",value);
            break;
        case UCI_ID_RADIO1_DDRS_MAX_RATE:
            sprintf(cmd,"uci set wireless.wifi1.ddrsmaxrate='%s'",value);
            break;
        case UCI_ID_RADIO1_DDRS_STREAM:
            {
                int val = atoi(value);

                kwn_reset_datarate( val );
                sprintf(cmd,"uci set wireless.wifi1.spatialstream='%s'",value);
            }
            break;
        case UCI_ID_RADIO1_DDRS_RATE_INC_TIMER:
            sprintf(cmd,"uci set wireless.wifi1.ddrsinctimer='%s'",value);
            break;
        case UCI_ID_RADIO1_DDRS_RATE_DEC_TIMER:
            sprintf(cmd,"uci set wireless.wifi1.ddrsdectimer='%s'",value);
            break;
        case UCI_ID_RADIO1_ATPC_STATUS:
            sprintf(cmd,"uci set wireless.wifi1.atpcstatus='%s'",value);
            break;
        case UCI_ID_RADIO1_ATPC_POWER:
            sprintf(cmd,"uci set wireless.wifi1.atpcpower='%s'",value);
            break;
        case UCI_ID_ETHERNET_MTU:
            sprintf(cmd,"uci set network.lan.mtu='%s'",value);
            break;
        case UCI_ID_RADIO1_ANTENNA_GAIN:
            sprintf(cmd,"uci set wireless.wifi1.antennagain='%s'",value);
            break;
        case UCI_ID_VLAN_ALLOW_TAGGED_MGMT:
            sprintf(cmd,"uci set vlan.vlan.tagmgmt='%s'",value);
            break;
        case UCI_ID_TFTP_FILENAME:
            sprintf(cmd,"uci set tftp.tftp.filename='%s'",value);
            break;
        case UCI_ID_TFTP_FILETYPE:
            sprintf(cmd,"uci set tftp.tftp.filetype='%s'",value);
            break;
        case UCI_ID_TFTP_SERVERIP:
            sprintf(cmd,"uci set tftp.tftp.serverip='%s'",value);
            break;
        case UCI_ID_TFTP_OPTYPE:
            {
                sprintf(cmd,"uci set tftp.tftp.optype='%s'",value);
                system( cmd );
                system("/usr/sbin/kwn_tftp");
                sprintf(cmd,"uci set tftp.tftp.optype='0'");
                break;
            }
        case UCI_ID_TFTP_KEEPSET:
            sprintf(cmd,"uci set tftp.tftp.keepset='%s'",value);
            break;
        case UCI_ID_RADIO1_DDRS_INCR_THRLD:
            sprintf(cmd,"uci set wireless.wifi1.ddrsincthrld='%s'",value);
            break;
        case UCI_ID_RADIO1_TRAFFIC_SHAPING:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].shaping='%s'",value);
            break;
        case UCI_ID_RADIO1_DCS_STATUS:
            sprintf(cmd,"uci set wireless.wifi1.dcsstatus='%s'",value);
            break;
        case UCI_ID_RADIO1_DCS_THRLD:
            sprintf(cmd,"uci set wireless.wifi1.dcsthrld='%s'",value);
            break;
        case UCI_ID_RADIO1_DDRS_RTX_INC:
            sprintf(cmd,"uci set wireless.wifi1.ddrsrtxinc='%s'",value);
            break;
        case UCI_ID_RADIO1_DDRS_RTX_DEC:
            sprintf(cmd,"uci set wireless.wifi1.ddrsrtxdec='%s'",value);
            break;
        case UCI_ID_FILTERING_STATUS:
            sprintf(cmd,"uci set filter.filter.status='%s'",value);
            break;
        case UCI_ID_FILTERING_L2MCAST:
            sprintf(cmd,"uci set filter.filter.l2mcast='%s'",value);
            break;
        case UCI_ID_FILTERING_L3MCAST:
            sprintf(cmd,"uci set filter.filter.l3mcast='%s'",value);
            break;
        case UCI_ID_FILTERING_L2BCAST:
            sprintf(cmd,"uci set filter.filter.l2bcast='%s'",value);
            break;
        case UCI_ID_FILTERING_L3BCAST:
            sprintf(cmd,"uci set filter.filter.l3bcast='%s'",value);
            break;
        case UCI_ID_RADIO1_WIRELESS_INACT:
            sprintf(cmd,"uci set wireless.wifi1.wifitimer='%s'",value);
            break;
        case UCI_ID_RADIO1_LINK_INACT:
            sprintf(cmd,"uci set wireless.wifi1.linktimer='%s'",value);
            break;
        case UCI_ID_RADIO1_MAX_EIRP:
            sprintf(cmd,"uci set wireless.wifi1.maxeirp='%s'",value);
            break;
        case UCI_ID_RADIO2_RATE:
            sprintf(cmd,"uci set wireless.wifi0.rate='%s'",value);
            break;
        case UCI_ID_RADIO2_DISABLE_LEGACY:
            sprintf(cmd,"uci set wireless.@wifi-iface[0].dis_legacy='%s'",value);
            break;
        case UCI_ID_RADIO2_STATUS:
            sprintf(cmd,"uci set wireless.@wifi-iface[0].disabled='%s'",value);
            break;
        case UCI_ID_SYSTEM_LOCATION:
            sprintf(cmd,"uci set system.@system[0].location='%s'",value);
            break;
        case UCI_ID_SYSTEM_CONTACT:
            sprintf(cmd,"uci set system.@system[0].contact='%s'",value);
            break;
        case UCI_ID_SYSTEM_EMAIL:
            sprintf(cmd,"uci set system.@system[0].email='%s'",value);
            break;
        case UCI_ID_NETWORK_MODE:
            sprintf(cmd,"uci set network.param.networkmode='%s'",value);
            system( cmd );
            kwn_reset_nwkmode_params();
            break;
        case UCI_ID_NAT_STATUS:
            sprintf(cmd,"uci set network.param.natstatus='%s'",value);
            break;
        case UCI_ID_ROUTE_ETH_IP:
            sprintf(cmd,"uci set network.kweth.ipaddr='%s'",value);
            break;
        case UCI_ID_ROUTE_ETH_ADDR_TYPE:
            sprintf(cmd,"uci set network.kweth.proto='%s'",value);
            break;
        case UCI_ID_ROUTE_ETH_NETMASK:
            sprintf(cmd,"uci set network.kweth.netmask='%s'",value);
            break;
        default:
            break;
    }
    sprintf(cmd1,"echo %s >> /tmp/cmds.txt",cmd);
    system( cmd1 );
    printf("cmd = %s\n",cmd);
    system( cmd );
}

void set_cfgtxtfile()
{
    char str[255];
    char *ptr;
    char *end_str;
    FILE* fp;

    fp = fopen( SET_CFG_FILE, "r" );

    while( fgets( str, 255, (FILE*) fp ) ) {
    }
    fclose( fp );

    ptr = strtok_r( str, "~", &end_str );

    system("echo ############################################## >> /tmp/cmds.txt");
    while( ptr != NULL )
    {
        char *end_token;
        char *type, *value;
        char *ptr2;
        int len , x = 0;

        if( strlen(ptr) < 2 )
        {
            ptr = strtok_r( NULL, "~", &end_str );
            continue;
        }
        ptr2 = strtok_r( ptr, "=", &end_token );

        len = strlen( ptr2 );
        type = malloc( len );
        memset( type,'\0', sizeof( type ) );
        strncpy( type, ptr2, len );
        while( ptr2 != NULL )
        {
            len = strlen( ptr2 );
            value = malloc( len );
            memset( value,'\0',sizeof( value ) );
            if( x == 1 ) {
                strncpy( value, ptr2, len );
                value[len] = '\0';
            }
            ptr2 = strtok_r( NULL, "=", &end_token );
            x++;
        }
        cfg_set( type, value );
        free( type );
        free( value );
        ptr = strtok_r( NULL, "~", &end_str );
    }
}

void set_linktest()
{
	kwn_link_test test;
	char cmd[255];

	test.direction = 1;
	test.duration = 120;
	test.start_stop = 1;
	//memcpy( test.mac, "00:D0:41:E0:1C:10",  sizeof(test.mac) );

	//sprintf( cmd, "uci set tool.tool.mac=%s", test.mac );
	//system( cmd );
	sprintf( cmd, "uci set tool.tool.dur=%d", test.duration );
	system( cmd );
	sprintf( cmd, "uci set tool.tool.dir=%d", test.direction );
	system( cmd );
	system("/etc/init.d/KWtool start");

	if( test.start_stop == 1 ) {
		system("iwpriv ath1 kwn_tput_test 1");
	}
	else {
		system("iwpriv ath1 kwn_tput_test 0");
	}	
}

void get_assoclist()
{
	int sk_fd = -1;
        struct ieee80211req_sta_info *si;
        kwn_wireless_stats list;
        struct iwreq iwr;
        unsigned char *cp = NULL;
        unsigned char buf[ 24 * 1024 ]  ={ 0 };
        int len = 0;
        int num = 0;

        (void) memset( &iwr, 0, sizeof(iwr) );
        (void) strncpy( iwr.ifr_name, "ath1", sizeof( iwr.ifr_name ) );
        iwr.u.data.pointer = ( void * ) buf;
        iwr.u.data.length = sizeof( buf );
	sk_fd = socket( AF_INET, SOCK_DGRAM, 0 );

	if( sk_fd < 0 ) {
		sk_fd = -1;
		return;
	}
        if( ioctl( sk_fd, IEEE80211_IOCTL_STA_INFO, &iwr) < 0 ) {
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
		memcpy( list.sta[num].mac, &si->isi_macaddr, KWN_MAC_ADDR_LEN );
		memcpy( list.sta[num].l_latitude, si->isi_l_latitude+5, sizeof(list.sta[num].l_latitude) );
		memcpy( list.sta[num].l_longitude, si->isi_l_longitude+5, sizeof(list.sta[num].l_longitude) );
		memcpy( list.sta[num].r_latitude, si->isi_r_latitude+5, sizeof(list.sta[num].r_latitude) );
		memcpy( list.sta[num].r_longitude, si->isi_r_longitude+5, sizeof(list.sta[num].r_longitude) );
		list.sta[num].tx_tput = si->isi_tx_tput;
		list.sta[num].rx_tput = si->isi_rx_tput;
		list.sta[num].local_snr_a1 = si->isi_local_snr_a1;
		list.sta[num].remote_snr_a1 = si->isi_remote_snr_a1;
		list.sta[num].local_snr_a2 = si->isi_local_snr_a2;
		list.sta[num].remote_snr_a2 = si->isi_remote_snr_a2;
		list.sta[num].ip = si->isi_ip_addr;
#if 1
		printf(" station mac = %2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X\n",
                           list.sta[num].mac[0],
                           list.sta[num].mac[1],
                           list.sta[num].mac[2],
			   list.sta[num].mac[3],
			   list.sta[num].mac[4],
			   list.sta[num].mac[5]);
		printf("L_Lat_Long %s %s, R_Lat_Long %s %s \n",list.sta[num].l_latitude,list.sta[num].l_longitude,list.sta[num].r_latitude,list.sta[num].r_longitude);
		printf("Tx Tput %llu Rx Tput %llu \n",list.sta[num].tx_tput,list.sta[num].rx_tput);
		printf("Local SNR A1 %d SNR A2 %d \n",list.sta[num].local_snr_a1,list.sta[num].local_snr_a2);
		printf("Remote SNR A1 %d SNR A2 %d \n",list.sta[num].remote_snr_a1,list.sta[num].remote_snr_a2);
		printf("IP: %d.%d.%d.%d \n",
                                (list.sta[num].ip & 0xFF), (list.sta[num].ip >> 8) & 0xFF,
                                (list.sta[num].ip >> 16 ) & 0xFF,(list.sta[num].ip >> 24) & 0xFF);
#endif
		num ++;
		cp += si->isi_len, len -= si->isi_len;
	} while( len >= sizeof( struct ieee80211req_sta_info ) );
	close( sk_fd );
	list.no_of_links = num;
    printf("Number of links %d \n",num);
}


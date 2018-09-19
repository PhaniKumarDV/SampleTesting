

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
            break;
        case UCI_ID_RADIO1_SSID:
            sprintf(cmd,"uci set wireless.@wifi-iface[1].ssid='%s'",value);
            break;
        case UCI_ID_RADIO1_COUNTRY:
            sprintf(cmd,"uci set wireless.wifi1.country='%s'",value);
            break;
        case UCI_ID_RADIO1_OPMODE:
            sprintf(cmd,"uci set wireless.wifi1.hwmode='%s'",value);
            system( cmd );
            sprintf(cmd,"uci set wireless.wifi1.rate='auto'",value);
            break;
        case UCI_ID_RADIO1_BANDWIDTH:
            sprintf(cmd,"uci set wireless.wifi1.htmode='%s'",value);
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
            sprintf(cmd,"uci set wireless.@wifi-iface[1].kwnamsdu='%s'",value);
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
            sprintf(cmd,"uci set wireless.wifi0.txpower='%s'",value);
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
            {
                int val = atoi(value);
                if( val == 0 ) {
                    sprintf(cmd,"uci delete dhcp.lan");
                }
                else {
                    sprintf(cmd,"uci set dhcp.lan=dhcp");
                    system( cmd );
                    sprintf(cmd,"uci set dhcp.lan.interface='lan'");
                    system( cmd );
                    sprintf(cmd,"uci set dhcp.lan.start='100'");
                    system( cmd );
                    sprintf(cmd,"uci set dhcp.lan.limit='150'");
                    system( cmd );
                    sprintf(cmd,"uci set dhcp.lan.leasetime='12h'");
                    system( cmd );
                    sprintf(cmd,"uci set dhcp.lan.dhcpv6='server'");
                    system( cmd );
                    sprintf(cmd,"uci set dhcp.lan.ra='server'");
                }
            }
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


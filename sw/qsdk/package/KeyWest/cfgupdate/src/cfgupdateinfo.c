

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

#define GET_CFG_FILE "/lib/getcfgfile.txt"
#define SET_CFG_FILE "/lib/setcfgfile.txt"

void set_cfgtxtfile();
void set_linktest();
void get_assoclist();

int main()
{
	get_assoclist();
	set_cfgtxtfile();
	set_linktest();
	return 0;
}

void set_cfgtxtfile()
{
	FILE* fp;
	char buffer[255];
	char cmd[255];

	if( access( SET_CFG_FILE, F_OK ) != -1 ) {
		fp = fopen(SET_CFG_FILE, "r");

		while(fgets(buffer, 255, (FILE*) fp)) {
			printf("%s", buffer);
			sprintf(cmd, "uci set %s", buffer);
			system(cmd);
		}

		system("reload_config");
		fclose(fp);
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
#if 0
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
}


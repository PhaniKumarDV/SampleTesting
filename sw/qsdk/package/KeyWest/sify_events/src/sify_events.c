/*
Sify Events
*/

#include <time.h>
#include <string.h>
#include <sys/time.h>
#include "sify_events.h"
#include <math.h>
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

static void handle_newlink(struct ifinfomsg *ifi, unsigned char *buf, size_t len);
static void handle_ifla_wireless ( char *data, int len);
static int iwpriv80211(int op, void *data, int len);
struct sockaddr_nl local;
int myindex;
char prev_mac[25]={0};
int ifd,isock_fd;
int se_daemon = -1;
#define IEEE80211_EV_DISASSOC_IND_AP 20
#define IEEE80211_EV_DISASSOC_COMPLETE_AP 33
#define IEEE80211_EV_DYING_GASP       45
#define IEEE80211_EV_BASE_DYING_GASP  46
#define IEEE80211_EV_SU_DYING_GASP    47
#define IEEE80211_EV_DCS_TRIGGERED    48
#define IEEE80211_EV_DCS_BEST_CHANNEL 49
#define IEEE80211_EV_SA_START         50
#define IEEE80211_EV_SA_STOP          51
#define IEEE80211_EV_ACS_START        52
#define IEEE80211_EV_ACS_BEST_CHANNEL 53 
#define IEEE80211_EV_SCAN_IN_PROGRESS 54

#define pi 3.14159265358979323846
#define KWN_DISTANCE_MIN              1
#define KWN_DISTANCE_MAX              25
#define KWN_CFG_BUF_LEN               650
#define KWN_CMD_IMP_LEN               100
#define KWN_CMD_OUT_LEN               50

enum kwn_radiomode {
    KWN_RADIOMODE_AP = 1,
    KWN_RADIOMODE_SU = 2
};

enum kwn_linktype {
    KWN_LINKTYPE_PTP = 1,
    KWN_LINKTYPE_BH = 2,
    KWN_LINKTYPE_PTMP_SMAC3 = 3,
    KWN_LINKTYPE_PTMP_SMAC2 = 4
};

#define PRINTF(fmt, ...)\
do\
{\
	if(se_daemon < 0)printf("\r\n");\
	if(se_daemon < 0)printf(fmt, ##__VA_ARGS__);\
	if(se_daemon < 0)printf("\r\n");\
}while(0)
/* Sify Specific */
void sify_file_write(char *,int,int,uint8_t);
double deg2rad(double);
double rad2deg(double);
void get_assoclist( int );

int distance(double lat1, double lon1, double lat2, double lon2) {
    double theta, dist;
    if ((lat1 == lat2) && (lon1 == lon2)) {
        return 0;
    }
    else {
        theta = lon1 - lon2;
        dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
        dist = acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515;
        dist = dist * 1.609344;
        return (dist);
    }
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts decimal degrees to radians             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double deg) {
    return (deg * pi / 180);
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts radians to decimal degrees             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double rad2deg(double rad) {
    return (rad * 180 / pi);
}

void sify_file_write(char *sify_buf,int status, int reason, uint8_t value)
{
	time_t rawtime;
	struct tm *timeinfo;
	FILE *sify_fp;
    int len;
    char t[50];
    char cmd[100];
    char trap_cmd[100];

	/* Get current time */
	time( &rawtime );
    timeinfo = localtime( &rawtime );
    len = strlen( asctime( timeinfo ) ) - 1;
    memcpy( t, asctime( timeinfo ), len );
    t[len] = '\0';

	if (sify_buf == NULL)
	{
		PRINTF("[%s:%d] !mac is null\r\n",__func__,__LINE__);
		return;
	}

	/*Open file for writting */
	sify_fp = fopen("/tmp/wifi_packet_logs", "a+");

	if (sify_fp == NULL) {
		PRINTF("File opening error\n");
		return;
	}
	PRINTF("[%s:%d] status = %d, mac = %s\r\n",__func__,__LINE__,status,sify_buf);

	if(status)
	{
		fprintf(sify_fp, "%s: Associated ( MAC: %s )\n",t,sify_buf);
		syslog(LOG_INFO, " Associated ( MAC: %s )\n",sify_buf);		       
        sprintf( trap_cmd, "/usr/sbin/snmptrap.sh 1 %s  > /dev/null 2>&1", sify_buf);
        system( trap_cmd );
        //system("/usr/sbin/link.sh > /dev/null 2>&1");
                //int rc=system("/usr/sbin/sify_senddata.sh '1'"); 
	}
	else
    {
        switch( reason )
        {
            case IEEE80211_EV_BASE_DYING_GASP:
                sprintf(cmd,"echo %s: Reboot initiated due to Dying Gasp >> /etc/reboot_logs",t);
                system(cmd);
                fprintf(sify_fp, "%s: Outdoor Base( MAC : %s) Power Off \n",t,sify_buf);
                syslog(LOG_INFO, " Outdoor Base ( MAC : %s )Power Off \n",sify_buf);		       
                sprintf( trap_cmd, "/usr/sbin/snmptrap.sh 4 %s  > /dev/null 2>&1", sify_buf);
                system( trap_cmd );
                break;
            case IEEE80211_EV_SU_DYING_GASP:
                sprintf(cmd,"echo %s: Reboot initiated due to Dying Gasp >> /etc/reboot_logs",t);
                system(cmd);
                break;
            case IEEE80211_EV_DYING_GASP:
                fprintf(sify_fp, "%s: Disassociated ( MAC : %s, Reason: Power Off )\n",t,sify_buf);
                syslog(LOG_INFO, " Disassociated ( MAC : %s, Reason: Power Off )\n",sify_buf);		       
                sprintf( trap_cmd, "/usr/sbin/snmptrap.sh 3 %s  > /dev/null 2>&1", sify_buf);
                system( trap_cmd );
                break;
            case IEEE80211_EV_DISASSOC_IND_AP:
                fprintf(sify_fp, "%s: Disassociated ( MAC: %s, Reason: Remote Terminated )\n",t,sify_buf);
                syslog(LOG_INFO, " Disassociated ( MAC: %s, Reason: Remote Terminated )\n",sify_buf);		       
                sprintf( trap_cmd, "/usr/sbin/snmptrap.sh 2 %s  > /dev/null 2>&1", sify_buf);
                system( trap_cmd );
                break;
            case IEEE80211_EV_DISASSOC_COMPLETE_AP:
                fprintf(sify_fp, "%s: Disassociated ( MAC: %s, Reason: Local Terminated )\n",t,sify_buf);
                syslog(LOG_INFO, " Disassociated ( MAC: %s, Reason: Local Terminated )\n",sify_buf);		       
                sprintf( trap_cmd, "/usr/sbin/snmptrap.sh 2 %s  > /dev/null 2>&1", sify_buf);
                system( trap_cmd );
                break;
            case IEEE80211_EV_DCS_TRIGGERED:
                fprintf(sify_fp, "%s: DCS triggered\n",t,sify_buf);
                syslog(LOG_INFO, " DCS triggered\n",sify_buf);		       
                system("spectraltool -i wifi1 startscan");
                break;
            case IEEE80211_EV_DCS_BEST_CHANNEL:
                fprintf(sify_fp, "%s: DCS selected best channel\n",t,sify_buf);
                syslog(LOG_INFO, " DCS selected best channel\n",sify_buf);		       
                system("spectraltool -i wifi1 stopscan");
                break;
            case IEEE80211_EV_SA_START:
                fprintf(sify_fp, "%s: Spectrum Analyzer started\n",t,sify_buf);
                syslog(LOG_INFO, " Spectrum Analyzer started\n",sify_buf);		       
                system("spectraltool -i wifi1 startscan");
                break;
            case IEEE80211_EV_SA_STOP:
                fprintf(sify_fp, "%s: Spectrum Analyzer stopped\n",t,sify_buf);
                syslog(LOG_INFO, " Spectrum Analyzer stopped\n",sify_buf);		       
                system("spectraltool -i wifi1 stopscan");
                break;
            case IEEE80211_EV_ACS_START:
                fprintf(sify_fp, "%s: ACS started\n",t,sify_buf);
                syslog(LOG_INFO, " ACS started\n",sify_buf);		       
                system("spectraltool -i wifi1 startscan");
                break;
            case IEEE80211_EV_ACS_BEST_CHANNEL:
                fprintf(sify_fp, "%s: ACS selected best channel\n",t,sify_buf);
                syslog(LOG_INFO, " ACS selected best channel\n",sify_buf);		       
                system("spectraltool -i wifi1 stopscan");
                break;
            case IEEE80211_EV_SCAN_IN_PROGRESS:
                fprintf(sify_fp, "%s: Scanning is already in progress\n",t,sify_buf);
                syslog(LOG_INFO, " Scanning is already in progress\n",sify_buf);		       
                break;
            default:
                fprintf(sify_fp, "%s: Disassociated ( MAC: %s )\n",t,sify_buf);
                syslog(LOG_INFO, " Disassociated ( MAC: %s )\n",sify_buf);		       
                sprintf( trap_cmd, "/usr/sbin/snmptrap.sh 2 %s  > /dev/null 2>&1", sify_buf);
                system( trap_cmd );
                break;
        }
    }
	fclose(sify_fp); /* close file */
}
/*end of sify */

void kwn_sys_cmd_imp( const char* cmd, uint8_t* cmd_buf )
{
    FILE *fp = NULL;
    uint8_t  a[KWN_CFG_BUF_LEN]={0};
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

void kwn_sta_kickout()
{
    char cmd[KWN_CMD_IMP_LEN];
    uint8_t cmd_buf[KWN_CMD_OUT_LEN];
    uint8_t linktype;

    /* Get Link Type */
    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get wireless.wifi1.linktype");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
    linktype = atoi( cmd_buf );
    if( linktype == 3 ) {
        system("iwpriv wifi1 sta_kickout 0");
    }
}

/*track wireless events*/
int init_wireless_tracking(int sock_fd)
{
	/*declarations*/
	char cur_mac[35]={0};
	struct sockaddr_in addr, to_addr, from_addr;
	char buf[8192];
	int left;
	struct sockaddr_nl from;
	socklen_t fromlen;
	struct nlmsghdr *h;
	int max_events = 10;
	fd_set socks_time;
	struct timeval t_id;

#if 0
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, "ath0" , sizeof(ifr.ifr_name));
	if (ioctl(fd, SIOCGIFINDEX, &ifr) == -1) 
	{
		int k=0;
	}
	else
	{
		myindex=ifr.ifr_ifindex;
	}

	/*to set time out=1 sec for recvfrom*/	
	FD_ZERO(&socks_time);
	FD_SET(sock_fd, &socks_time);
	t_id.tv_sec = 1;
	t_id.tv_usec = 0;
	fromlen = sizeof(from);
	if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&t_id,sizeof(struct timeval))!=-1)
	{	
		left = recvfrom(sock_fd, buf, sizeof(buf),0,(struct sockaddr *) &from, &fromlen);
		if(left==-1)
			return -1;

	}
	else	
	{
		//syslog(LOG_ALERT,"error in timeout");
	}
	/*process event--if found*/
	h = (struct nlmsghdr *) buf;
	while (NLMSG_OK(h, left)) {
		PRINTF("[%s:%d] nlmsg_type = %d\r\n",__func__,__LINE__,h->nlmsg_type);
		switch (h->nlmsg_type) {
			case RTM_NEWLINK:
				handle_newlink (NLMSG_DATA(h), NLMSG_DATA(h) + NLMSG_ALIGN(sizeof(struct ifinfomsg)),
								NLMSG_PAYLOAD(h, sizeof(struct ifinfomsg)));
				break;
			case RTM_DELLINK:
				break;
		}

		h = NLMSG_NEXT(h, left);
	}

#else

	while((left = recvfrom(sock_fd, buf, sizeof(buf),0,(struct sockaddr *) &from, &fromlen)) > 0)
	{
		/*process event--if found*/
		h = (struct nlmsghdr *) buf;
		while (NLMSG_OK(h, left)) {
			PRINTF("[%s:%d] nlmsg_type = %d\r\n",__func__,__LINE__,h->nlmsg_type);
			switch (h->nlmsg_type) {
				case RTM_NEWLINK:
					handle_newlink (NLMSG_DATA(h), NLMSG_DATA(h) + NLMSG_ALIGN(sizeof(struct ifinfomsg)),
									NLMSG_PAYLOAD(h, sizeof(struct ifinfomsg)));
					break;
				case RTM_DELLINK:
					break;
			}
			PRINTF("[%s:%d] h = %p, l = %ld\r\n",__func__,__LINE__,h,left);

			h = NLMSG_NEXT(h, left);
		}
		PRINTF("[%s:%d] recvfrom done \r\n",__func__,__LINE__);
	}
#endif
	return -1;
}
int main (int argc, char** argv)
{

	pid_t pid, sid;
	int timer=1;
	struct ifreq ifr;
	if (argc==2 && (strcmp(argv[1],"-d") == 0)) 
	{
		pid = fork();
		if (pid < 0) {
			exit(EXIT_FAILURE);
		}
		if (pid > 0) {
			exit(EXIT_SUCCESS);
		}
		umask(0);
		sid = setsid();
		if (sid < 0) {
			exit(EXIT_FAILURE);
		}
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		se_daemon = 1;
	}
	else
	{
		umask (0);
	}
	PRINTF("\r\n[%s:%d] se_daemon = %d\r\n",__func__,__LINE__,se_daemon);
/*	
	if ((chdir("/")) < 0) {
		exit(EXIT_FAILURE);
	}
*/	
	/*socket creation and binding*/		
	ifd=socket(AF_INET, SOCK_DGRAM, 0);
	isock_fd=socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	if(isock_fd < 0 || ifd < 0)
	{
		//	syslog(LOG_ALERT,"error in creating sockets");
		exit(0);
	}
	memset(&local, 0, sizeof(local));
	local.nl_family = AF_NETLINK;
	local.nl_groups = RTMGRP_LINK;
	if (bind(isock_fd, (struct sockaddr *) &local, sizeof(local)) < 0)
	{
		exit(1);
	}
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, "ath0" , sizeof(ifr.ifr_name));
	if (ioctl(ifd, SIOCGIFINDEX, &ifr) == 0) 
	{
		myindex=ifr.ifr_ifindex;
	}

	while(1)/*initialize an infinite process*/
	{
		init_wireless_tracking(isock_fd);	/*AP registration/deregistration event*/
		sleep(1);
	}
	exit (0);
}

static void handle_newlink(struct ifinfomsg *ifi, unsigned char *buf, size_t len)
{
	int attrlen, rta_len;
	struct rtattr *attr;
#if 0
	if (ifi->ifi_index != myindex)
	{	
		PRINTF("\r\n[%s:%d] ifindex mismatch %d, %d",__func__,__LINE__,ifi->ifi_index,myindex);
		return;
	}
#endif
	attrlen = len;
	attr = (struct rtattr *) buf;
	rta_len = RTA_ALIGN(sizeof(struct rtattr));
	while (RTA_OK(attr, attrlen)) {
		PRINTF("[%s:%d] attr->rta_type = %d\r\n",__func__,__LINE__,attr->rta_type);
		if (attr->rta_type == IFLA_WIRELESS) {
			handle_ifla_wireless (((char *) attr) + rta_len, attr->rta_len - rta_len);
		}

		attr = RTA_NEXT(attr, attrlen);
	}

}
static void handle_ifla_wireless ( char *data, int len)
{
	struct iw_event iwe_buf, *iwe = &iwe_buf;
	char *pos, *end, *custom, *buf;
	char str[15];
	int ix=0;
	char mac[25]={0};
	char tm_mac[3]={0};
	int mac_status=0;
	static int registered = -1;

	pos = data;
	end = data + len;
	while (pos + IW_EV_LCP_LEN <= end) 
	{
		/* Event data may be unaligned, so make a local, aligned copy
		 *                  *          * before processing. */
		memcpy(&iwe_buf, pos, IW_EV_LCP_LEN);
		if (iwe->len <= IW_EV_LCP_LEN)
		{
			PRINTF("[%s:%d] iwe->len <= IW_EV_LCP_LEN %d, %d\r\n",__func__,__LINE__,iwe->len,IW_EV_LCP_LEN);
			return;
		}
		custom = pos + IW_EV_POINT_LEN;
		if (iwe->cmd == IWEVMICHAELMICFAILURE || iwe->cmd == IWEVASSOCREQIE || iwe->cmd == IWEVCUSTOM) 
		{
			/* WE-19 removed the pointer from struct iw_point */
			char *dpos = (char *) &iwe_buf.u.data.length;
			int dlen = dpos - (char *) &iwe_buf;
			memcpy(dpos, pos + IW_EV_LCP_LEN,
				   sizeof(struct iw_event) - dlen);
		} else {
			memcpy(&iwe_buf, pos, sizeof(struct iw_event));
			custom += IW_EV_POINT_OFF;
		}
		PRINTF("\r\n[%s:%d] iwe->cmd = %04X\r\n",__func__,__LINE__, iwe->cmd);

		switch (iwe->cmd) {
			case IWEVEXPIRED:
				PRINTF("[%s:%d] IWEVEXPIRED\r\n",__func__,__LINE__);
				for (ix = 0; ix < 6; ++ix)
				{
					if(ix<5)
						sprintf(tm_mac,"%02x:",(unsigned char) iwe->u.addr.sa_data[ix]);
					else
						sprintf(tm_mac,"%02x",(unsigned char) iwe->u.addr.sa_data[ix]);
					strcat(mac,tm_mac);

					memset(tm_mac,'\0',3);
				}
				//syslog(LOG_INFO,"Wireless SU Expired:%s",mac);		       
				sify_file_write(mac,0,iwe->u.addr.sa_data[6],iwe->u.addr.sa_data[7]);
                //kwn_set_distance( KWN_DISTANCE_MAX );
                break;
			case IWEVREGISTERED:
				PRINTF("[%s:%d] IWEVREGISTERED\r\n",__func__,__LINE__);
				for (ix = 0; ix < 6; ++ix)
				{
					if(ix<5)
						sprintf(tm_mac,"%02x:",(unsigned char) iwe->u.addr.sa_data[ix]);
					else
						sprintf(tm_mac,"%02x",(unsigned char) iwe->u.addr.sa_data[ix]);
					strcat(mac,tm_mac);
					memset(tm_mac,'\0',3);
				}
				//syslog(LOG_INFO,"New Wireless SU Registered:%s",mac);
                sify_file_write(mac,1,0,0);
                kwn_sta_kickout();
                //get_assoclist( KWN_RADIOMODE_AP );
				break;
			case IWEVASSOCREQIE:
				break;
			case IWEVCUSTOM:
				PRINTF("[%s:%d] IWEVCUSTOM\r\n",__func__,__LINE__);
				if (custom + iwe->u.data.length > end)
					return;
				buf = malloc(iwe->u.data.length + 1);
				if (buf == NULL)
					return;
				memcpy(buf, custom, iwe->u.data.length);
				buf[iwe->u.data.length] = '\0';
				free(buf);
				break;
// for SU				
			case SIOCGIWAP:
				PRINTF("[%s:%d] SIOCGIWAP\r\n",__func__,__LINE__);
				for (ix = 0; ix < 6; ++ix)
				{
					if(iwe->u.ap_addr.sa_data[ix]==0x00)
						mac_status++;

					if(ix<5)
						sprintf(tm_mac,"%02x:",(unsigned char) iwe->u.ap_addr.sa_data[ix]);
					else
						sprintf(tm_mac,"%02x",(unsigned char) iwe->u.ap_addr.sa_data[ix]);
					strcat(mac,tm_mac);
					memset(tm_mac,'\0',3);

				}
				if(mac_status == 6) // no mac address received
				{
					//if((registered  == 1) || (registered == -1))
					{
						//syslog(LOG_ALERT,"Wireless Device Unegistered Successfully:%s",prev_mac);
						sify_file_write(prev_mac,0,0,0);
						registered = 0;
                        //kwn_set_distance( KWN_DISTANCE_MAX );
					}
				}
				else
				{
					//if ((registered == 0) || (registered == -1))
					{
						strcpy(prev_mac,mac);
						//syslog(LOG_ALERT,"Wireless Device Registered Successfully:%s",mac);
						sify_file_write(mac,1,0,0);
						registered = 1;
                        system("/usr/sbin/link.sh > /dev/null 2>&1");
                        //get_assoclist( KWN_RADIOMODE_SU );
					}
				}
				break;

		}

		pos += iwe->len;
	}
	PRINTF("\r\n[%s:%d] handle_ifla_wireless return \r\n",__func__,__LINE__);
}

void kwn_set_distance( int dist )
{
    char cmd[100];

    dist = ( dist < KWN_DISTANCE_MIN ) ? KWN_DISTANCE_MIN : dist;
    dist = ( dist > KWN_DISTANCE_MAX ) ? KWN_DISTANCE_MAX : dist;
#if 0
    sprintf(cmd,"iwpriv wifi1 distance %d",dist);
    system( cmd );
    system("iwpriv wifi1 pdev_reset 3");
#endif
}

void get_assoclist( int radiomode )
{
    int sk_fd = -1;
    struct ieee80211req_sta_info *si;
    struct iwreq iwr;
    unsigned char *cp = NULL;
    unsigned char buf[ 24 * 1024 ]  ={ 0 };
    int len, num = 0;
    char lat1[16], lon1[16], lat2[16], lon2[16];
    char *st;
    double l1, o1, l2, o2;
    int dist;
    char cmd[KWN_CMD_IMP_LEN];
    uint8_t cmd_buf[KWN_CMD_OUT_LEN];
    uint8_t linktype;

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
        memcpy( lat1, si->isi_l_latitude+5, sizeof( lat1 ) );
        memcpy( lon1, si->isi_l_longitude+5, sizeof( lon1 ) );
        memcpy( lat2, si->isi_r_latitude+5, sizeof( lat2 ) );
        memcpy( lon2, si->isi_r_longitude+5, sizeof( lon2 ) );

        l1 = strtod(lat1,&st);
        o1 = strtod(lon1,&st);
        l2 = strtod(lat2,&st);
        o2 = strtod(lon2,&st);

        dist = distance( l1, o1, l2, o2 );
        printf("Distance : %d \n",dist);
        num ++;
        cp += si->isi_len, len -= si->isi_len;
    } while( len >= sizeof( struct ieee80211req_sta_info ) );
    close( sk_fd );
    printf("Number of links %d \n",num);

    if( num > 0 ) {
        if( radiomode == KWN_RADIOMODE_SU ) {
            kwn_set_distance( dist );
        }
        else {
            /* Get Link Type */
            memset(cmd, '\0', sizeof(cmd));
            memset(cmd_buf, '\0', sizeof(cmd_buf));
            sprintf(cmd,"uci get wireless.wifi1.linktype");
            kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] ); 
            linktype = atoi( cmd_buf );
            if( linktype == KWN_LINKTYPE_PTP || linktype == KWN_LINKTYPE_BH ) {
                kwn_set_distance( dist );
            }
            else {
                kwn_set_distance( KWN_DISTANCE_MAX );
            }
        }
    }
    else {
        kwn_set_distance( KWN_DISTANCE_MAX );
    }
}


/*
Author: viji 
Sify Events
*/

#include <time.h>
#include <string.h>
#include <sys/time.h>
#include "sify_events.h"
#include <math.h>

static void handle_newlink(struct ifinfomsg *ifi, unsigned char *buf, size_t len);
static void handle_ifla_wireless ( char *data, int len);
static int iwpriv80211(int op, void *data, int len);
struct sockaddr_nl local;
int myindex;
char prev_mac[25]={0};
int ifd,isock_fd;
int se_daemon = -1;
#define IEEE80211_EV_DYING_GASP 45
#define IEEE80211_EV_DISASSOC_IND_AP 20
#define IEEE80211_EV_DISASSOC_COMPLETE_AP 33
#define PRINTF(fmt, ...)\
do\
{\
	if(se_daemon < 0)printf("\r\n");\
	if(se_daemon < 0)printf(fmt, ##__VA_ARGS__);\
	if(se_daemon < 0)printf("\r\n");\
}while(0)
/* Sify Specific */
void sify_file_write(char *,int,int);
void sify_file_write(char *sify_buf,int status, int reason)
{
	time_t rawtime;
	struct tm *timeinfo;
	FILE *sify_fp;
    int len;
    char t[50];

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
	sify_fp = fopen("/etc/wifi_packet_logs", "a+");

	if (sify_fp == NULL) {
		PRINTF("File opening error\n");
		return;
	}
	PRINTF("[%s:%d] status = %d, mac = %s\r\n",__func__,__LINE__,status,sify_buf);

	if(status)
	{
		fprintf(sify_fp, "%s: Associated ( MAC: %s )\n",t,sify_buf);
		syslog(LOG_INFO, " Associated ( MAC: %s )\n",sify_buf);		       
                //int rc=system("/usr/sbin/sify_senddata.sh '1'"); 
	}
	else
    {
        switch( reason )
        {
            case IEEE80211_EV_DYING_GASP:
                fprintf(sify_fp, "%s: Disassociated ( MAC : %s, Reason: Power Off )\n",t,sify_buf);
                syslog(LOG_INFO, " Disassociated ( MAC : %s, Reason: Power Off )\n",sify_buf);		       
                break;
            case IEEE80211_EV_DISASSOC_IND_AP:
                fprintf(sify_fp, "%s: Disassociated ( MAC: %s, Reason: Remote Terminated )\n",t,sify_buf);
                syslog(LOG_INFO, " Disassociated ( MAC: %s, Reason: Remote Terminated )\n",sify_buf);		       
                break;
            case IEEE80211_EV_DISASSOC_COMPLETE_AP:
                fprintf(sify_fp, "%s: Disassociated ( MAC: %s, Reason: Local Terminated )\n",t,sify_buf);
                syslog(LOG_INFO, " Disassociated ( MAC: %s, Reason: Local Terminated )\n",sify_buf);		       
                break;
            default:
                fprintf(sify_fp, "%s: Disassociated ( MAC: %s )\n",t,sify_buf);
                syslog(LOG_INFO, " Disassociated ( MAC: %s )\n",sify_buf);		       
                break;
        }
    }
	fclose(sify_fp); /* close file */
}
/*end of sify */

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
				sify_file_write(mac,0,iwe->u.addr.sa_data[6]);
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
				sify_file_write(mac,1,0);
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
					if((registered  == 1) || (registered == -1))
					{
						//syslog(LOG_ALERT,"Wireless Device Unegistered Successfully:%s",prev_mac);
						sify_file_write(prev_mac,0,0);
						registered = 0;
					}
				}
				else
				{
					if ((registered == 0) || (registered == -1))
					{
						strcpy(prev_mac,mac);
						//syslog(LOG_ALERT,"Wireless Device Registered Successfully:%s",mac);
						sify_file_write(mac,1,0);
						registered = 1;
					}
				}
				break;

		}

		pos += iwe->len;
	}
	PRINTF("\r\n[%s:%d] handle_ifla_wireless return \r\n",__func__,__LINE__);
}



/* Really simple radius authenticator
 *
 * Copyright (c) 2004 Michael Gernoth <michael@gernoth.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ethernet.h"
#include "common.h"
#include "wireless.h"
#include "wrt-radauth.h"

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

static void 
handle_newlink(struct ifinfomsg *ifi, unsigned char *buf, size_t len);
static void handle_ifla_wireless ( char *data, int len );
static int iwpriv80211(int op, void *data, int len);
int init_driver ( )
{
	struct ifreq ifr;
	struct sockaddr_nl local;
	struct sockaddr_in addr, to_addr, from_addr;

	config.ioctl_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (config.ioctl_sock < 0) {
		wrtlog_crit("socket(SOCK_DRAGM-ioctl)");
		goto handle_fail_ioctl;
	}

	config.netlink_sock = socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	if (config.netlink_sock < 0) {
		wrtlog_crit("socket(SOCK_DRAGM-netlink)");
		goto handle_fail_netlink;
	}

	memset(&local, 0, sizeof(local));
	local.nl_family = AF_NETLINK;
	local.nl_groups = RTMGRP_LINK;
	if (bind(config.netlink_sock, (struct sockaddr *) &local, sizeof(local)) < 0)
	{
		wrtlog_crit ("netlink: Failed to bind netlink ");
		goto handle_fail_netlink;
	}
	config.radius_sock = socket(PF_INET, SOCK_DGRAM, 0);
	if ( config.radius_sock < 0 )
	{
		wrtlog_crit("socket");
		exit(1);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = PF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(config.radius_sock, (struct sockaddr *) &addr, sizeof(addr)) <0)
	{
		wrtlog_crit("bind");
		goto handle_fail_radius;
	}
	wrtlog_debug("config.ioctl_sock %d\n",config.ioctl_sock);
	wrtlog_debug("config.netlink_sock %d\n", config.netlink_sock);
	wrtlog_debug("config.radius_sock %d\n", config.radius_sock);



	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, config.iface, sizeof(ifr.ifr_name));
	if (ioctl(config.ioctl_sock, SIOCGIFINDEX, &ifr) != 0) {
		wrtlog_crit("ioctl(SIOCGIFINDEX)");
		goto handle_fail_radius;
	}
	config.ifindex = ifr.ifr_ifindex;

	wrtlog_info("ifindex for %s is %d\n",config.iface,config.ifindex);

	enable_deny_acl (config.iface);
	flush_deny_acl (config.iface);
	return 0;
handle_fail_radius:
	close (config.radius_sock);
	config.radius_sock=0;
handle_fail_netlink:
	close (config.netlink_sock);
	config.netlink_sock = 0;
handle_fail_ioctl:
	close (config.ioctl_sock);
	config.ioctl_sock = 0;
	return -1;
}
void deinit_driver ()
{	close (config.radius_sock);
	config.radius_sock=0;
	close (config.netlink_sock);
	config.netlink_sock = 0;
	close (config.ioctl_sock);
	config.ioctl_sock = 0;
	disable_deny_acl (config.iface);
}
int getassoclist(unsigned char *list)
{
	struct ieee80211req_sta_info *si;
	struct iwreq iwr;
	unsigned char *cp = NULL; 
	unsigned char buf[24*1024]={0};
	int s=0;
	int len=0;
	int num=0;
	(void) memset(&iwr, 0, sizeof(iwr));
	(void) strncpy(iwr.ifr_name, config.iface, sizeof(iwr.ifr_name));
	iwr.u.data.pointer = (void *) buf;
	iwr.u.data.length = sizeof(buf);
	if (ioctl(config.ioctl_sock, IEEE80211_IOCTL_STA_INFO, &iwr) < 0){
		wrtlog_crit("unable to get station information\n");
		return -1;
	}
	len = iwr.u.data.length;
	if (len < sizeof(struct ieee80211req_sta_info))
		return;
	cp = buf;
	do {
		si = (struct ieee80211req_sta_info *) cp;
		wrtlog_debug(" station mac = %2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X\n",
			   si->isi_macaddr[0],
			   si->isi_macaddr[1],
			   si->isi_macaddr[2],
			   si->isi_macaddr[3],
			   si->isi_macaddr[4],
			   si->isi_macaddr[5]);
		memcpy((&list[4]+num*6), si->isi_macaddr, 6);
		num ++;
		cp += si->isi_len, len -= si->isi_len;
	} while (len >= sizeof(struct ieee80211req_sta_info));
   	memcpy(list,&num,4);
	wrtlog_debug(" number of stations = %d\n", num);
	return num;
}
int kick_station (unsigned char *mac)
{
	struct ieee80211req_mlme mlme;
	int ret;

	wrtlog_debug("%s: addr=%s kick off \n",
			   __func__, ether_sprintf(mac));
	mlme.im_op = IEEE80211_MLME_DISASSOC;
	mlme.im_reason = 0;
	memcpy(mlme.im_macaddr, mac, IEEE80211_ADDR_LEN);
	ret = iwpriv80211(IEEE80211_IOCTL_SETMLME, &mlme, sizeof(mlme));
	if (ret < 0) {
		wrtlog_debug("%s: Failed to kick STA %s \n", __func__,ether_sprintf(mac));
	}
	return ret;
}
int add_station_acl (char *ifname, unsigned char *mac)
{
	struct sockaddr sa;
	int ret;
	wrtlog_debug("%s: addr=%s add to ACL \n",
			   __func__, ether_sprintf(mac));
	memset (&sa, 0x00, sizeof(struct sockaddr));
	memcpy (sa.sa_data,mac,IEEE80211_ADDR_LEN);
	sa.sa_family = ARPHRD_ETHER;

	ret = iwpriv80211(IEEE80211_IOCTL_ADDMAC, &sa, 1);
	if (ret < 0) {
		wrtlog_debug("%s: Failed to add to ACL %s STA \n", __func__,ether_sprintf(mac));
	}
	return ret;

}
int remove_station_acl (char *ifname, unsigned char *mac)
{
	struct sockaddr sa;
	int ret;
	wrtlog_debug("%s: addr=%s remove from ACL \n",
			   __func__, ether_sprintf(mac));
	memset(&sa,0x00, sizeof(struct sockaddr));
	memcpy (sa.sa_data,mac,IEEE80211_ADDR_LEN);
	sa.sa_family = ARPHRD_ETHER;
	ret = iwpriv80211(IEEE80211_IOCTL_DELMAC, &sa, 1);
	if (ret < 0) {
		wrtlog_debug("%s: Failed to add to ACL %s STA \n", __func__,ether_sprintf(mac));
	}
	return ret;
}
int flush_deny_acl (char *ifname)
{
	struct iwreq iwr;
	int arg = 3;

	wrtlog_debug("%s: flush deny ACL \n",
			   __func__);
	memset(&iwr, 0, sizeof(iwr));
	strncpy(iwr.ifr_name, config.iface, IFNAMSIZ);
	iwr.u.mode = IEEE80211_PARAM_MACCMD;
	memcpy(iwr.u.name+sizeof(__u32), &arg, sizeof(arg));

	if (ioctl(config.ioctl_sock, IEEE80211_IOCTL_SETPARAM, &iwr) < 0) {
		wrtlog_debug("%s: Failed to flush deny ACL\n",__func__);
		return -1;
	}
	sleep(1);
	return 0;
}
int enable_deny_acl (char *ifname)
{
	struct iwreq iwr;
	int arg = 2;

	wrtlog_debug("%s: enable deny ACL \n",
			   __func__);
	memset(&iwr, 0, sizeof(iwr));
	strncpy(iwr.ifr_name, config.iface, IFNAMSIZ);
	iwr.u.mode = IEEE80211_PARAM_MACCMD;
	memcpy(iwr.u.name+sizeof(__u32), &arg, sizeof(arg));

	if (ioctl(config.ioctl_sock, IEEE80211_IOCTL_SETPARAM, &iwr) < 0) {
		wrtlog_debug("%s: Failed to enable deny ACL\n",__func__);
		return -1;
	}
	sleep(5);
	return 0;
}
int disable_deny_acl (char *ifname)
{	
	struct iwreq iwr;
	int arg = 0;

	wrtlog_debug("%s: disable deny ACL \n",
			   __func__);
	memset(&iwr, 0, sizeof(iwr));
	strncpy(iwr.ifr_name, config.iface, IFNAMSIZ);
	iwr.u.mode = IEEE80211_PARAM_MACCMD;
	memcpy(iwr.u.name+sizeof(__u32), &arg, sizeof(arg));

	if (ioctl(config.ioctl_sock, IEEE80211_IOCTL_SETPARAM, &iwr) < 0) {
		wrtlog_debug("%s: Failed to disable deny ACL\n",__func__);
		return -1;
	}
	return 0;
}
void handle_netlink_receive ()
{
	char buf[8192];
	int left;
	struct sockaddr_nl from;
	socklen_t fromlen;
	struct nlmsghdr *h;
	int max_events = 10;

try_again:
	fromlen = sizeof(from);
	left = recvfrom(config.netlink_sock, buf, sizeof(buf), MSG_DONTWAIT,
					(struct sockaddr *) &from, &fromlen);
	if (left < 0) {
		wrtlog_crit( "netlink: recvfrom failed\n");
		return;
	}

	h = (struct nlmsghdr *) buf;
	while (NLMSG_OK(h, left)) {
		switch (h->nlmsg_type) {
			case RTM_NEWLINK:
				wrtlog_debug("RTM_NEWLINK\n");
				handle_newlink (NLMSG_DATA(h), NLMSG_DATA(h) + NLMSG_ALIGN(sizeof(struct ifinfomsg)),
								NLMSG_PAYLOAD(h, sizeof(struct ifinfomsg)));
				break;
			case RTM_DELLINK:
				wrtlog_debug("RTM_DELLINK\n");
				break;
		}

		h = NLMSG_NEXT(h, left);
	}

	if (left > 0) {
		wrtlog_debug("netlink: %d extra bytes in the end of netlink message\n", left);
	}
    if (--max_events > 0) {
		goto try_again;
	}
}
static void 
handle_newlink(struct ifinfomsg *ifi, unsigned char *buf, size_t len)
{
	int attrlen, rta_len;
	struct rtattr *attr;
	if (ifi->ifi_index != config.ifindex)
		return;
	attrlen = len;
	attr = (struct rtattr *) buf;

	rta_len = RTA_ALIGN(sizeof(struct rtattr));
	while (RTA_OK(attr, attrlen)) {
		if (attr->rta_type == IFLA_WIRELESS) {
			handle_ifla_wireless (((char *) attr) + rta_len,
								  attr->rta_len - rta_len);
		}
		attr = RTA_NEXT(attr, attrlen);
	}

}
static void handle_ifla_wireless ( char *data, int len )
{
	struct iw_event iwe_buf, *iwe = &iwe_buf;
	char *pos, *end, *custom, *buf;

	pos = data;
	end = data + len;

	while (pos + IW_EV_LCP_LEN <= end) {
		/* Event data may be unaligned, so make a local, aligned copy
		 *          * before processing. */
		memcpy(&iwe_buf, pos, IW_EV_LCP_LEN);
		wrtlog_debug("Wireless event: cmd=0x%x len=%d\n",
				   iwe->cmd, iwe->len);
		if (iwe->len <= IW_EV_LCP_LEN)
			return;

		custom = pos + IW_EV_POINT_LEN;
		if (iwe->cmd == IWEVMICHAELMICFAILURE ||
			 iwe->cmd == IWEVASSOCREQIE ||
			 iwe->cmd == IWEVCUSTOM) {
			/* WE-19 removed the pointer from struct iw_point */
			char *dpos = (char *) &iwe_buf.u.data.length;
			int dlen = dpos - (char *) &iwe_buf;
			memcpy(dpos, pos + IW_EV_LCP_LEN,
				   sizeof(struct iw_event) - dlen);
		} else {
			memcpy(&iwe_buf, pos, sizeof(struct iw_event));
			custom += IW_EV_POINT_OFF;
		}

		switch (iwe->cmd) {
			case IWEVEXPIRED:
				/* do nothing */
				wrtlog_debug("wireless event IWEVEXPIRED ..\n");
				break;
			case IWEVREGISTERED:
				wrtlog_debug("wireless event IWEVREGISTERED\n");
				handle_new_sta ((unsigned char *) iwe->u.addr.sa_data);
				break;
			case IWEVASSOCREQIE:
				wrtlog_debug("wireless event IWEVASSOCREQIE\n");
			case IWEVCUSTOM:
				wrtlog_debug("wireless event IWEVCUSTOM\n");
				if (custom + iwe->u.data.length > end)
					return;
				buf = malloc(iwe->u.data.length + 1);
				if (buf == NULL)
					return;
				memcpy(buf, custom, iwe->u.data.length);
				buf[iwe->u.data.length] = '\0';
				free(buf);
				break;
		}

		pos += iwe->len;
	}
}
void set_sta_authorized (unsigned char *addr, unsigned char authorized)
{
	struct ieee80211req_mlme mlme;
	int ret;

	if (authorized)
	{
		remove_station_acl (config.iface,addr);
		/* wait for SU fo get associated */
		mlme.im_op = IEEE80211_MLME_AUTHORIZE;
	}
	else
		mlme.im_op = IEEE80211_MLME_UNAUTHORIZE;
	mlme.im_reason = 0;
	memcpy(mlme.im_macaddr, addr, IEEE80211_ADDR_LEN);
	wrtlog_debug("%s: addr=%s authorized=%d\n",
			   __func__, ether_sprintf(addr), authorized);

	ret = iwpriv80211(IEEE80211_IOCTL_SETMLME, &mlme, sizeof(mlme));
	if (ret < 0) {
		wrtlog_debug("%s: Failed to %sauthorize STA \n" MACSTR,
				   __func__, authorized ? "" : "un", MAC2STR(addr));
	}
	if (authorized == 0)
	{
		/* add to acl and kick */
		add_station_acl (config.iface,addr);
		kick_station (addr);
	}
	return ;
}
int is_sta_present (unsigned char *addr)
{
	unsigned char list[24*1024]={0};
	unsigned char *pos = NULL;
	int num = 0;
	int i=0;
	getassoclist(list);
	pos=list;
	memcpy(&num,pos,4); 
	pos+=4;
	for (i=0;i<num;i++)
	{
		if(memcmp(addr,pos,6) == 0) return 1;
		pos += 6;
	}
	return 0;
}
static int
iwpriv80211(int op, void *data, int len)
{
	struct iwreq iwr;
	int do_inline = len < IFNAMSIZ;

	/* Certain ioctls must use the non-inlined method */
	if (op == IEEE80211_IOCTL_SET_APPIEBUF ||
		op == IEEE80211_IOCTL_FILTERFRAME)
		do_inline = 0;

	memset(&iwr, 0, sizeof(iwr));
	strncpy(iwr.ifr_name, config.iface, IFNAMSIZ);
	if (do_inline) {
		memcpy(iwr.u.name, data, IFNAMSIZ);
	} else {
		iwr.u.data.pointer = data;
		iwr.u.data.length = len;
	}
	if (ioctl(config.ioctl_sock, op, &iwr) < 0) {
		int first = IEEE80211_IOCTL_SETPARAM;
		static const char *opnames[] = {
			"ioctl[IEEE80211_IOCTL_SETPARAM]",
			"ioctl[IEEE80211_IOCTL_GETPARAM]",
			"ioctl[IEEE80211_IOCTL_SETKEY]",
			"ioctl[IEEE80211_IOCTL_SETWMMPARAMS]",
			"ioctl[IEEE80211_IOCTL_DELKEY]",
			"ioctl[IEEE80211_IOCTL_GETWMMPARAMS]",
			"ioctl[IEEE80211_IOCTL_SETMLME]",
			"ioctl[IEEE80211_IOCTL_GETCHANINFO]",
			"ioctl[IEEE80211_IOCTL_SETOPTIE]",
			"ioctl[IEEE80211_IOCTL_GETOPTIE]",
			"ioctl[IEEE80211_IOCTL_ADDMAC]",
			NULL,
			"ioctl[IEEE80211_IOCTL_DELMAC]",
			"ioctl[IEEE80211_IOCTL_GETCHANLIST]",
			"ioctl[IEEE80211_IOCTL_SETCHANLIST]",
			"ioctl[IEEE80211_IOCTL_KICKMAC]",
			"ioctl[IEEE80211_IOCTL_CHANSWITCH]",
			"ioctl[IEEE80211_IOCTL_GETMODE]",
			"ioctl[IEEE80211_IOCTL_SETMODE]",
			"ioctl[IEEE80211_IOCTL_GET_APPIEBUF]",
			"ioctl[IEEE80211_IOCTL_SET_APPIEBUF]",
			NULL,
			"ioctl[IEEE80211_IOCTL_FILTERFRAME]",
		};
		int idx = op - first;
		if (first <= op &&
			idx < (int) (sizeof(opnames) / sizeof(opnames[0])) &&
			opnames[idx])
			wrtlog_crit(opnames[idx]);
		else {
			wrtlog_crit("ioctl[unknown???]");
			wrtlog_debug("Failed ioctl: 0x%x\n", op);
		}
		return -1;
	}
	return 0;
}
const char *
ether_sprintf(const unsigned char *addr)
{
	static char buf[sizeof(MACSTR)];

	if (addr != NULL)
		snprintf(buf, sizeof(buf), MACSTR, MAC2STR(addr));
	else
		snprintf(buf, sizeof(buf), MACSTR, 0,0,0,0,0,0);
	return buf;
}

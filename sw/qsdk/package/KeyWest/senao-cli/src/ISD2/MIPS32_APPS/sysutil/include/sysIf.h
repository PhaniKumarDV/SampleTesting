/*****************************************************************************
;
;   (C) Unpublished Work of Senao Networks, Inc.  All Rights Reserved.
;
;       THIS WORK IS AN UNPUBLISHED WORK AND CONTAINS CONFIDENTIAL,
;       PROPRIETARY AND TRADESECRET INFORMATION OF SENAO INCORPORATED.
;       ACCESS TO THIS WORK IS RESTRICTED TO (I) SENAO EMPLOYEES WHO HAVE A
;       NEED TO KNOW TO PERFORM TASKS WITHIN THE SCOPE OF THEIR ASSIGNMENTS
;       AND (II) ENTITIES OTHER THAN SENAO WHO HAVE ENTERED INTO APPROPRIATE
;       LICENSE AGREEMENTS.  NO PART OF THIS WORK MAY BE USED, PRACTICED,
;       PERFORMED, COPIED, DISTRIBUTED, REVISED, MODIFIED, TRANSLATED,
;       ABBRIDGED, CONDENSED, EXPANDED, COLLECTED, COMPILED, LINKED, RECAST,
;       TRANSFORMED OR ADAPTED WITHOUT THE PRIOR WRITTEN CONSENT OF SENAO.
;       ANY USE OR EXPLOITATION OF THIS WORK WITHOUT AUTHORIZATION COULD
;       SUBJECT THE PERPERTRATOR TO CRIMINAL AND CIVIL LIABILITY.
;
;------------------------------------------------------------------------------
;
;    Project : 
;    Creator : 
;    File    : sysIf.h
;    Abstract: include file of the Interface APIs.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2006-0825       Newly Create
;*****************************************************************************/
#ifndef _SYSUTIL_IF_H_
#define _SYSUTIL_IF_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sap_ostypes.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <linux/if_ether.h> /* out of habit, I use a SOCK_PACKET socket*/


/* IPv6 WAN DNS resolv.conf */
#define RESOLV_IPV6_CONF_PATH     "/etc/resolv_ipv6.conf"

enum
{
    PPP_DISCONNECTED=0,
    PPP_CONNECTED,
    PPP_CONNECTING,
};

#define PPP_FAKE_ISP_IP  "10.64.64.68" //"10.112.112.113"
#define PPP_FAKE_WAN_IP  "10.64.64.64" //"10.112.112.112"

#if HAS_WAN_L2TP
#define PPP_FAKE_L2TP_ISP_IP "10.64.64.68"
#define PPP_FAKE_L2TP_WAN_IP "10.64.64.64"
#endif

#if HAS_WAN_3G
#define PPP_FAKE_3G_ISP_IP  "10.64.64.68"
#define PPP_FAKE_3G_WAN_IP  "10.64.64.64"
#define PPP_FAKE_3G_WAN_DNS_IP_1  "10.11.12.13"
#define PPP_FAKE_3G_WAN_DNS_IP_2  "10.11.12.14"
#endif

struct user_net_device_stats {
    unsigned long long rx_packets;  /* total packets received       */
    unsigned long long tx_packets;  /* total packets transmitted    */
    unsigned long long rx_bytes;    /* total bytes received         */
    unsigned long long tx_bytes;    /* total bytes transmitted      */
    unsigned long rx_errors;        /* bad packets received         */
    unsigned long tx_errors;        /* packet transmit problems     */
    unsigned long rx_dropped;       /* no space in linux buffers    */
    unsigned long tx_dropped;       /* no space available in linux  */
    unsigned long rx_multicast;     /* multicast packets received   */
    unsigned long rx_compressed;
    unsigned long tx_compressed;
    unsigned long collisions;
    
    /* detailed rx_errors: */
    unsigned long rx_length_errors;
    unsigned long rx_over_errors;   /* receiver ring buff overflow  */
    unsigned long rx_crc_errors;    /* recved pkt with crc error    */
    unsigned long rx_frame_errors;  /* recv'd frame alignment error */
    unsigned long rx_fifo_errors;   /* recv'r fifo overrun          */
    unsigned long rx_missed_errors; /* receiver missed packet     */
    /* detailed tx_errors */
    unsigned long tx_aborted_errors;
    unsigned long tx_carrier_errors;
    unsigned long tx_fifo_errors;
    unsigned long tx_heartbeat_errors;
    unsigned long tx_window_errors;
};


#ifdef __cplusplus
extern "C" {
#endif 

int sysIPIsReady(const T_CHAR *interface);
int sysGetIfIndex(const T_CHAR *interface);
int sysGetIfStatus(const T_CHAR *interface);
T_BOOL sysIfGetHwAddr(const T_CHAR *interface, T_CHAR hwaddr[]);
const char *sysIfGetIP(const T_CHAR *interface);
const char *sysIfGetDstIP(const T_CHAR *interface);
const char *sysIfGetMask(const T_CHAR *interface);
const char *sysIfGetSubnet(const T_CHAR *interface);
const char *sysIfGetGateway(const T_CHAR *gatewayInterface);
const char *sysIfGetDefaultGateway();
const char *sysIfDns();
const char *sysMultiIfGetDns(int index, char *iface);
const char *sysIfv6Dns(int index);
T_BOOL isIfExisted(const T_CHAR *interface);
T_VOID sysIfSetHostName(T_CHAR *hostname);
unsigned long sysIfGetPacketsInfo(const T_CHAR *interface, int method);
T_BOOL sysIfGetDevStats(const T_CHAR *interface,
                        struct user_net_device_stats *stats);
T_BOOL sysDelVlanIf(T_CHAR *prefix);
T_BOOL sysCheckValidIp(T_IPADDR sevIp,T_IPADDR lanIp,T_IPADDR maskIp);
int sysIfGetPhyId(const T_CHAR *interface);
int sysIfGetMTU(const T_CHAR *interface);

#ifdef __cplusplus
}
#endif 

#endif



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
;    Project : SI-688
;    Creator : 
;    File    : sysMii.c
;    Abstract: API for read MII status of ethernet device
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2007-0104       Newly Create
;*****************************************************************************/
#ifndef _SYSUTIL_MII_H_
#define _SYSUTIL_MII_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
//#include <netinet/in.h>
#include <sap_ostypes.h>
//#include <netinet/in.h>
#include <net/if.h>
//#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if_ether.h> /* out of habit, I use a SOCK_PACKET socket*/
#define SYS_MII_SPEED_10MBPS      (1<<0)
#define SYS_MII_SPEED_100MBPS     (1<<1)  
#define SYS_MII_SPEED_1000MBPS    (1<<2) 
#define SYS_MII_SPEED_10MBPS_HD   (1<<3)
#define SYS_MII_SPEED_100MBPS_HD  (1<<4)   
#define SYS_MII_SPEED_1000MBPS_HD (1<<5)
#define SYS_MII_SPEED_AUTO        (1<<6)   

#ifdef __cplusplus
extern "C" {
#endif 

T_BOOL sysMiiCheckLink(const T_CHAR *ifname, T_INT *result, int isForce);
T_BOOL sysMiiGetLinkPartnerSpeed(const T_CHAR *ifname, T_UINT32 *speed);
T_BOOL sysMiiCheckLinkEx(const T_CHAR *ifname, T_INT *status, int isForce, int phy_id);
T_BOOL sysMiiGetLinkPartnerSpeedEx(const T_CHAR *ifname, T_UINT32 *speed, int phy_id);
T_BOOL sysSetMiiPower(T_UINT32 port , T_UINT32 up);
T_BOOL sysMiiSetPortLinkSpeed(const T_CHAR *ifname, T_UINT32 linkspeed, int port);
#ifdef __cplusplus
}
#endif 

#endif



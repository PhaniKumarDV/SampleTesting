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
;    File    : sysArp.h
;    Abstract: include file of the Interface APIs.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2008-0625       Newly Create
;*****************************************************************************/
#ifndef _SYSUTIL_ARP_H_
#define _SYSUTIL_ARP_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sap_ostypes.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <linux/if_ether.h> /* out of habit, I use a SOCK_PACKET socket*/

T_CHAR* sysArpGetIfNameByIP(T_CHAR* ipstr);
T_CHAR* sysArpGetMacByIP(T_CHAR* ipstr);
T_CHAR* sysArpGetMacByIP2(T_CHAR* ipstr);
T_CHAR* sysArpGetIpByMac(T_CHAR* macstr);
T_INT arpping(T_UINT32 yiaddr, T_UINT32 ip, T_UINT8 *mac, T_CHAR *interface);

#ifdef __cplusplus
}
#endif 

#endif



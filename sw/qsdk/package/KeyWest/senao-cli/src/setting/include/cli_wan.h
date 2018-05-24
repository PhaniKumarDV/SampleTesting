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
;    Creator : Norkay
;    File    : cwan.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       Norkay            2007-0326       Create
;*****************************************************************************/
#ifndef _CLI_WAN_H_
#define _CLI_WAN_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <cli.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*                           FUNCTIONS                                     */
/*-------------------------------------------------------------------------*/
CliStatus cmdWanInfo(T_VOID* priv, CliData* cliData);
CliStatus cmdWanDhcpInfo(T_VOID* priv, CliData* cliData);
CliStatus cmdWanPppoeInfo(T_VOID* priv, CliData* cliData);
CliStatus cmdWanPptpInfo(T_VOID* priv, CliData* cliData);
CliStatus cmdWanPppoeReconn(T_VOID* priv, CliData* cliData);
CliStatus cmdWanStaticInfo(T_VOID* priv, CliData* cliData);
CliStatus cmdWanStaticMask(T_VOID* priv, CliData* cliData);
CliStatus cmdWanEnRouter(T_VOID* priv, CliData* cliData);
CliStatus cmdWanDNSInfo(T_VOID* priv, CliData* cliData);
#if HAS_WAN_PPTP
CliStatus cmdWanPPTPIFType(T_VOID* priv, CliData* cliData);
#endif
CliStatus cmdWanconnTypesetting(T_VOID* priv, CliData* cliData);
#endif

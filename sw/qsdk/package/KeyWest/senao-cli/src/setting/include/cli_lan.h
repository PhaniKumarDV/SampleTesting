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
;    File    : clan.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       Norkay            2007-0326       Create
;*****************************************************************************/
#ifndef _CLI_LAN_H_
#define _CLI_LAN_H_

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
CliStatus cmdLanInfo(T_VOID* priv, CliData* cliData);
CliStatus cmdLanDhcpRangeInfo(T_VOID* priv, CliData* cliData);
CliStatus cmdLanDhcpRange(T_VOID* priv, CliData* cliData);
CliStatus cmdLanDhcpClientList(T_VOID* priv, CliData* cliData);
CliStatus cmdStaticDhcpList(T_VOID* priv, CliData* cliData);
CliStatus cmdStaticDhcpNew(T_VOID* priv, CliData* cliData);
CliStatus cmdStaticDhcpEdit(T_VOID* priv, CliData* cliData);
CliStatus cmdStaticDhcpDelete(T_VOID* priv, CliData* cliData);
CliStatus cmdLanConnectType(T_VOID* priv, CliData* cliData);
CliStatus cmdStatistics(T_VOID* priv, CliData* cliData);
CliStatus cmdDHCP1(T_VOID* priv, CliData* cliData);
CliStatus cmdDHCP2(T_VOID* priv, CliData* cliData);
CliStatus cmdLanLeaseTime(T_VOID* priv, CliData* cliData);
#endif

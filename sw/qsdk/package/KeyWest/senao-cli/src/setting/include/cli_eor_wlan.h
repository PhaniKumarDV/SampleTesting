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
;    File    : cwireless.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       Norkay            2007-0328       Create
;*****************************************************************************/
#ifndef _CLI_WIRELESS_H_
#define _CLI_WIRELESS_H_

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
CliStatus cmdEORWirelessInfo(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessFragment(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessthreshold(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessDistance(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessbeacon(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessdtim(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessDataRate(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessNDataRate(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessChBandwidth(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessPreamble(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessCtsProtect(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessTxPwr(T_VOID* priv, CliData* cliData);
#ifdef SUPPORT_RALINK_WLAN
CliStatus cmdWirelessRABand(T_VOID* priv, CliData* cliData);
#endif
#if HAS_VLAN_SUPPORT
CliStatus cmdEORWirelessVlanStatus(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessVlanTag(T_VOID* priv, CliData* cliData);
#endif
CliStatus cmdWirelessATHBand(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessEnSsidNum(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessSsidSetting(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessChannel(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessWdsMacSetting(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessWdsSecurity(T_VOID* priv, CliData* cliData);
CliStatus cmdEORWirelessclist(T_VOID* priv, CliData* cliData);

#endif

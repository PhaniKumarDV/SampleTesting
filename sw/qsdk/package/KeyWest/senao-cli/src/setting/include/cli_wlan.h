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
CliStatus cmdWirelessInfo(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessDataRate(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessNDataRate(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessChBandwidth(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessPreamble(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessCtsProtect(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessTxPwr(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessMode(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessBasicTable(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessBand(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessEnSsidNum(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessSsidSetting(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessChannel(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessWdsMacSetting(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessWdsDatarateSetting(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessWdsSecurity(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessSiteSurvey(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessAPRPSecurity(T_VOID* priv, CliData* cliData);
#if HAS_VLAN_SUPPORT
CliStatus cmdWirelessVlanStatus(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessVlanTag(T_VOID* priv, CliData* cliData);
#if HAS_LAN_VLAN_MGMT
CliStatus cmdWirelessVlanMGMT(T_VOID* priv, CliData* cliData);
#endif
#endif
CliStatus cmdclientListInfo(T_VOID* priv, CliData* cliData);
CliStatus cmdWLANStatistics(T_VOID* priv, CliData* cliData);
CliStatus cmdWirelessThreshold(T_VOID* priv, CliData* cliData);
#endif


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
;    Creator : cfho
;    File    : dummy.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2008-0521       Create
;*****************************************************************************/
#ifndef _CLI_COMMON_H_
#define _CLI_COMMON_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <cli.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
#define CLI_CMD_NAME        "%10s -- %s\n"
#define CLI_CMD_USAGE       "%s%s\n", CLI_TITLE_SPACE

/*-------------------------------------------------------------------------*/
/*                           FUNCTIONS                                     */
/*-------------------------------------------------------------------------*/

/*engenius*/
//CliStatus cmducihandle(T_VOID* priv, CliData* cliData);
T_VOID cmducihandle(T_VOID);
CliStatus cmdsave(T_VOID* priv, CliData* cliData);
CliStatus cmdreboot(T_VOID* priv, CliData* cliData);
CliStatus cmdrevert(T_VOID* priv, CliData* cliData);
CliStatus cmdexit(T_VOID* priv, CliData* cliData);

/*ct_net.c*/

/*ct_nat.c*/
CliStatus cmdmvlanswitch(T_VOID* priv, CliData* cliData);
CliStatus cmdmvlanswitchexit(T_VOID* priv, CliData* cliData);

CliStatus cmdtimes(T_VOID* priv, CliData* cliData);


CliStatus cmdtip(T_VOID* priv, CliData* cliData);
CliStatus cmdpsize(T_VOID* priv, CliData* cliData);
CliStatus cmdnumber(T_VOID* priv, CliData* cliData);
CliStatus cmdpingaccept(T_VOID* priv, CliData* cliData);
CliStatus cmdpingexit(T_VOID* priv, CliData* cliData);


//ct_wless.c

CliStatus cmdssid1p(T_VOID* priv, CliData* cliData);
CliStatus cmdssid2p(T_VOID* priv, CliData* cliData);
CliStatus cmdssid3p(T_VOID* priv, CliData* cliData);
CliStatus cmdssid4p(T_VOID* priv, CliData* cliData);


CliStatus cmddisable(T_VOID* priv, CliData* cliData);

CliStatus cmdautht(T_VOID* priv, CliData* cliData);

CliStatus cmdencry(T_VOID* priv, CliData* cliData);

CliStatus cmdencry(T_VOID* priv, CliData* cliData);

CliStatus cmdaggr(T_VOID* priv, CliData* cliData);
CliStatus cmdtraffic(T_VOID* priv, CliData* cliData);

CliStatus cmdmac1(T_VOID* priv, CliData* cliData);
CliStatus cmdmac2(T_VOID* priv, CliData* cliData);
CliStatus cmdmac3(T_VOID* priv, CliData* cliData);
CliStatus cmdmac4(T_VOID* priv, CliData* cliData);

//CliStatus cmdDummy(T_VOID* priv, CliData* cliData);
CliStatus cmdHelp(T_VOID* priv, CliData* cliData);
//CliStatus cmdExit(T_VOID* priv, CliData* cliData);

CliStatus cmdapsecuexit(T_VOID* priv, CliData* cliData);
CliStatus cmdssidpexit(T_VOID* priv, CliData* cliData);


CliStatus cmdApply(T_VOID* priv, CliData* cliData);
CliStatus cmdTree(T_VOID* priv, CliData* cliData);
#if FOR_ZYXEL_CLI
CliStatus cmdSetDefCfg(T_VOID* priv, CliData* cliData);
CliStatus cmdReset2def(T_VOID* priv, CliData* cliData);
CliStatus cmdUploadStatus(T_VOID* priv, CliData* cliData);
CliStatus cmdInfo(T_VOID* priv, CliData* cliData);
extern CliStatus cmdSimplePing(T_VOID* priv, CliData* cliData);
#endif
#endif

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
;    File    : csystem.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       Norkay            2007-0323       Create
;*****************************************************************************/
//#ifndef _CLI_SYSTEM_H_
//#define _CLI_SYSTEM_H_

#define CLI_STATUS        "%25s -- %s"

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
//stat main
CliStatus cmdSystemmain(T_VOID* priv, CliData* cliData);

//stat client list
//CliStatus cmdsystemclient(T_VOID* priv, CliData* cliData);
CliStatus cmdwdslist(T_VOID* priv, CliData* cliData);
CliStatus cmdkickclient(T_VOID* priv, CliData* cliData);

//stat info
CliStatus cmdsysuptime(T_VOID* priv, CliData* cliData);
CliStatus cmdcpuinfo(T_VOID* priv, CliData* cliData);
CliStatus cmdmeminfo(T_VOID* priv, CliData* cliData);
CliStatus cmdwlanint(T_VOID* priv, CliData* cliData);
CliStatus cmdwlaninfo(T_VOID* priv, CliData* cliData);
CliStatus cmdetherinfo(T_VOID* priv, CliData* cliData);
CliStatus cmdchannel2(T_VOID* priv, CliData* cliData);
CliStatus cmdchannel5(T_VOID* priv, CliData* cliData);

//stat syslog
CliStatus cmdloginfo(T_VOID* priv, CliData* cliData);

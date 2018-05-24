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
;    File    : nat.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       Norkay            2007-0326       Create
;*****************************************************************************/
#ifndef _CLI_NAT_H_
#define _CLI_NAT_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <cli.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
typedef struct _alg_confg
{
	T_CHAR	*name;
	T_INT32 mask;
} alg_confg_t;
/*-------------------------------------------------------------------------*/
/*                           FUNCTIONS                                     */
/*-------------------------------------------------------------------------*/
T_BOOL __cliGetPrefixLanIp(T_CHAR *buf);
T_INT32 __natVsGetProtocolStr(T_CHAR *buf);
CliStatus cmdNatPmNew(T_VOID* priv, CliData* cliData);
CliStatus cmdNatPmEdit(T_VOID* priv, CliData* cliData);
CliStatus cmdNatPmDel(T_VOID* priv, CliData* cliData);
CliStatus cmdNatPmList(T_VOID* priv, CliData* cliData);
CliStatus cmdNatVsNew(T_VOID* priv, CliData* cliData);
CliStatus cmdNatVsEdit(T_VOID* priv, CliData* cliData);
CliStatus cmdNatVsDel(T_VOID* priv, CliData* cliData);
CliStatus cmdNatVsList(T_VOID* priv, CliData* cliData);
CliStatus cmdNatPtNew(T_VOID* priv, CliData* cliData);
CliStatus cmdNatPtEdit(T_VOID* priv, CliData* cliData);
CliStatus cmdNatPtDel(T_VOID* priv, CliData* cliData);
CliStatus cmdNatPtList(T_VOID* priv, CliData* cliData);
CliStatus cmdNatAlgEdit(T_VOID* priv, CliData* cliData);
CliStatus cmdNatAlgList(T_VOID* priv, CliData* cliData);
CliStatus cmdNatQosStatus(T_VOID* priv, CliData* cliData);
CliStatus cmdNatPriList(T_VOID* priv, CliData* cliData);
CliStatus cmdNatPriEdit(T_VOID* priv, CliData* cliData);
CliStatus cmdNatBandAllocList(T_VOID* priv, CliData* cliData);
CliStatus cmdNatBandAllocNew(T_VOID* priv, CliData* cliData);
CliStatus cmdNatBandAllocDel(T_VOID* priv, CliData* cliData);
CliStatus cmdNatStRouteList(T_VOID* priv, CliData* cliData);
CliStatus cmdNatStRouteNew(T_VOID* priv, CliData* cliData);
CliStatus cmdNatStRouteDel(T_VOID* priv, CliData* cliData);
CliStatus cmdRoutingTable(T_VOID* priv, CliData* cliData);

#endif

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
;    Creator : Joey
;    File    : fw.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       Joey            2008-0710       Create
;*****************************************************************************/
#ifndef _CLI_FW_H_
#define _CLI_FW_H_

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
//engenius


CliStatus cmdconntype(T_VOID* priv, CliData* cliData);
CliStatus cmddisping(T_VOID* priv, CliData* cliData);

CliStatus cmdaccname(T_VOID* priv, CliData* cliData);
CliStatus cmddomname(T_VOID* priv, CliData* cliData);
CliStatus cmdmtumode(T_VOID* priv, CliData* cliData);
CliStatus cmdmtulen(T_VOID* priv, CliData* cliData);
CliStatus cmddnsmode(T_VOID* priv, CliData* cliData);
CliStatus cmdconntypeexit(T_VOID* priv, CliData* cliData);

CliStatus cmdwanipaddr(T_VOID* priv, CliData* cliData);
CliStatus cmdwanipsubn(T_VOID* priv, CliData* cliData);
CliStatus cmdwangateway(T_VOID* priv, CliData* cliData);
CliStatus cmdwanipsetaccept(T_VOID* priv, CliData* cliData);
CliStatus cmdwanipsetexit(T_VOID* priv, CliData* cliData);

CliStatus cmdpppoemtulen(T_VOID* priv, CliData* cliData);
CliStatus cmdlogin(T_VOID* priv, CliData* cliData);
CliStatus cmdpppoepassw(T_VOID* priv, CliData* cliData);
CliStatus cmdsname(T_VOID* priv, CliData* cliData);
CliStatus cmdconmode(T_VOID* priv, CliData* cliData);
CliStatus cmdidle(T_VOID* priv, CliData* cliData);
CliStatus cmdperiod(T_VOID* priv, CliData* cliData);

CliStatus cmdpptpmtulen(T_VOID* priv, CliData* cliData);
CliStatus cmdpptps(T_VOID* priv, CliData* cliData);
CliStatus cmdpptpusername(T_VOID* priv, CliData* cliData);
CliStatus cmdpptppassw(T_VOID* priv, CliData* cliData);


CliStatus cmddhcpset(T_VOID* priv, CliData* cliData);

CliStatus cmdpptp(T_VOID* priv, CliData* cliData);
CliStatus cmdl2tp(T_VOID* priv, CliData* cliData);
CliStatus cmdipsec(T_VOID* priv, CliData* cliData);

CliStatus cmdpflist(T_VOID* priv, CliData* cliData);
CliStatus cmdpfact(T_VOID* priv, CliData* cliData);
CliStatus cmdpfadd(T_VOID* priv, CliData* cliData);
CliStatus cmdpfdel(T_VOID* priv, CliData* cliData);
CliStatus cmdpfenable(T_VOID* priv, CliData* cliData);
CliStatus cmdpfdisable(T_VOID* priv, CliData* cliData);
CliStatus cmdportforwardser(T_VOID* priv, CliData* cliData);
CliStatus cmdportforwardsetpro(T_VOID* priv, CliData* cliData);
CliStatus cmdportforwardsetsport(T_VOID* priv, CliData* cliData);
CliStatus cmdportforwardseteport(T_VOID* priv, CliData* cliData);
CliStatus cmdportforwardsetipaddr(T_VOID* priv, CliData* cliData);
CliStatus cmdportforwardaccept(T_VOID* priv, CliData* cliData);
CliStatus cmdportforwardexit(T_VOID* priv, CliData* cliData);

CliStatus cmdptlist(T_VOID* priv, CliData* cliData);
CliStatus cmdptact(T_VOID* priv, CliData* cliData);
CliStatus cmdptadd(T_VOID* priv, CliData* cliData);
CliStatus cmdptdel(T_VOID* priv, CliData* cliData);
CliStatus cmdporttriggerser(T_VOID* priv, CliData* cliData);
CliStatus cmdporttriggersetsport(T_VOID* priv, CliData* cliData);
CliStatus cmdporttriggerseteport(T_VOID* priv, CliData* cliData);
CliStatus cmdporttriggersettgtype(T_VOID* priv, CliData* cliData);
CliStatus cmdporttriggersetfport(T_VOID* priv, CliData* cliData);
CliStatus cmdporttriggersetpbtype(T_VOID* priv, CliData* cliData);
CliStatus cmdporttriggeraccept(T_VOID* priv, CliData* cliData);
CliStatus cmdporttriggerexit(T_VOID* priv, CliData* cliData);

CliStatus cmddmzact(T_VOID* priv, CliData* cliData);
CliStatus cmddmzaddr(T_VOID* priv, CliData* cliData);

CliStatus cmdmaclist(T_VOID* priv, CliData* cliData);
CliStatus cmdmacact(T_VOID* priv, CliData* cliData);
CliStatus cmdmacmode(T_VOID* priv, CliData* cliData);
CliStatus cmdmacadd(T_VOID* priv, CliData* cliData);
CliStatus cmdmacdel(T_VOID* priv, CliData* cliData);
CliStatus cmdmacser(T_VOID* priv, CliData* cliData);
CliStatus cmdmacaddr(T_VOID* priv, CliData* cliData);
CliStatus cmdmacaccept(T_VOID* priv, CliData* cliData);
CliStatus cmdroutermacfilterexit(T_VOID* priv, CliData* cliData);

CliStatus cmdipact(T_VOID* priv, CliData* cliData);
CliStatus cmdipmode(T_VOID* priv, CliData* cliData);
CliStatus cmdipadd(T_VOID* priv, CliData* cliData);
CliStatus cmdipdel(T_VOID* priv, CliData* cliData);
CliStatus cmdipser(T_VOID* priv, CliData* cliData);
CliStatus cmdipsetpro(T_VOID* priv, CliData* cliData);
CliStatus cmdipsetsip(T_VOID* priv, CliData* cliData);
CliStatus cmdipseteip(T_VOID* priv, CliData* cliData);
CliStatus cmdipsetsport(T_VOID* priv, CliData* cliData);
CliStatus cmdipseteport(T_VOID* priv, CliData* cliData);
CliStatus cmdipaccept(T_VOID* priv, CliData* cliData);
CliStatus cmdipfilterexit(T_VOID* priv, CliData* cliData);

CliStatus cmdurlact(T_VOID* priv, CliData* cliData);
CliStatus cmdurladd(T_VOID* priv, CliData* cliData);
CliStatus cmdurldel(T_VOID* priv, CliData* cliData);

CliStatus cmdlanipaddress(T_VOID* priv, CliData* cliData);
CliStatus cmdlanipsubnet(T_VOID* priv, CliData* cliData);
CliStatus cmdlanipaccept(T_VOID* priv, CliData* cliData);
CliStatus cmdlanipsetexit(T_VOID* priv, CliData* cliData);

CliStatus cmddhcpsip(T_VOID* priv, CliData* cliData);
CliStatus cmddhcpeip(T_VOID* priv, CliData* cliData);
CliStatus cmddhcpwip(T_VOID* priv, CliData* cliData);
CliStatus cmddhcpsetaccept(T_VOID* priv, CliData* cliData);
CliStatus cmddhcpsetexit(T_VOID* priv, CliData* cliData);


















//---------------------------------------------------------------------------
CliStatus cmdNatDmzIp(T_VOID* priv, CliData* cliData);
CliStatus cmdNatMacFilterNew(T_VOID* priv, CliData* cliData);
CliStatus cmdNatMacFilterDel(T_VOID* priv, CliData* cliData);
CliStatus cmdNatMacFilterList(T_VOID* priv, CliData* cliData);
CliStatus cmdNatIPFilterNew(T_VOID* priv, CliData* cliData);
CliStatus cmdNatIPFilterDel(T_VOID* priv, CliData* cliData);
CliStatus cmdNatIPFilterList(T_VOID* priv, CliData* cliData);
CliStatus cmdWlanFilterNew(T_VOID* priv, CliData* cliData);
CliStatus cmdWlanFilterDel(T_VOID* priv, CliData* cliData);
CliStatus cmdWlanFilterList(T_VOID* priv, CliData* cliData);

#endif


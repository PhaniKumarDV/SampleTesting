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

//#define CLI_STATUS        "%20s -- %s"

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
//wless2 wdslink
CliStatus cmdwdssecu(T_VOID* priv, CliData* cliData);
CliStatus cmdwdswepk(T_VOID* priv, CliData* cliData);
CliStatus cmdwdssecurityexit(T_VOID* priv, CliData* cliData);
CliStatus cmdwdsaesp(T_VOID* priv, CliData* cliData);
CliStatus cmdwdsenable(T_VOID* priv, CliData* cliData);
CliStatus cmdwdsdisable(T_VOID* priv, CliData* cliData);
CliStatus cmdwdsmacadd(T_VOID* priv, CliData* cliData);
CliStatus cmdwdsmacdel(T_VOID* priv, CliData* cliData);

//wless2 network mesh meshact
CliStatus cmdmeshact(T_VOID* priv, CliData* cliData);
CliStatus cmdmeshssid(T_VOID* priv, CliData* cliData);
CliStatus cmdmeshsecu(T_VOID* priv, CliData* cliData);
CliStatus cmdmeshpassp(T_VOID* priv, CliData* cliData);

//wless2 network wlmode
CliStatus cmdwlmode(T_VOID* priv, CliData* cliData);

//wless2 network htmode
CliStatus cmdhtmode(T_VOID* priv, CliData* cliData);

//wless2 network extch
CliStatus cmdextch(T_VOID* priv, CliData* cliData);

//wless2 network ch
CliStatus cmdchannel(T_VOID* priv, CliData* cliData);

//wless2 network ssidp ssidact
//wless2 network ssidp isoact
//wless2 network ssidp ssid
//wless2 network ssidp vid
//wless2 network ssidp supssid
//wless2 network ssidp sepa
CliStatus cmdssidp(T_VOID* priv, CliData* cliData);
CliStatus cmdssidact(T_VOID* priv, CliData* cliData);
CliStatus cmdisoact(T_VOID* priv, CliData* cliData);
CliStatus cmdssid(T_VOID* priv, CliData* cliData);
CliStatus cmdvid(T_VOID* priv, CliData* cliData);
CliStatus cmdsupssid(T_VOID* priv, CliData* cliData);
CliStatus cmdsepa(T_VOID* priv, CliData* cliData);


//wless2 network ssidp apsecu cli_table_wep
CliStatus cmdapsecu(T_VOID* priv, CliData* cliData);
CliStatus cmdssidpexit(T_VOID* priv, CliData* cliData);
CliStatus cmddkey(T_VOID* priv, CliData* cliData);
CliStatus cmdkey1(T_VOID* priv, CliData* cliData);
CliStatus cmdkey2(T_VOID* priv, CliData* cliData);
CliStatus cmdkey3(T_VOID* priv, CliData* cliData);
CliStatus cmdkey4(T_VOID* priv, CliData* cliData);
CliStatus cmdwepaccept(T_VOID* priv, CliData* cliData);
CliStatus cmdapsecuexit(T_VOID* priv, CliData* cliData);

//wless2 network ssidp apsecu cli_table_wpapsk
CliStatus cmdpassp(T_VOID* priv, CliData* cliData);
CliStatus cmdgroupk(T_VOID* priv, CliData* cliData);
CliStatus cmdwpapskaccept(T_VOID* priv, CliData* cliData);

//wless2 network ssidp apsecu cli_table_wpa
CliStatus cmdradserver(T_VOID* priv, CliData* cliData);
CliStatus cmdradp(T_VOID* priv, CliData* cliData);
CliStatus cmdradsecret(T_VOID* priv, CliData* cliData);
CliStatus cmdradaccount(T_VOID* priv, CliData* cliData);
CliStatus cmdradaccser(T_VOID* priv, CliData* cliData);
CliStatus cmdradaccp(T_VOID* priv, CliData* cliData);
CliStatus cmdradaccsec(T_VOID* priv, CliData* cliData);
CliStatus cmdinterval(T_VOID* priv, CliData* cliData);
CliStatus cmdwpaaccept(T_VOID* priv, CliData* cliData);

//wless2 network ssidp captive
CliStatus cmdcaptive(T_VOID* priv, CliData* cliData);

//wless2 network ssidp cli_table_traffic_c600
CliStatus cmdtsact_c600(T_VOID* priv, CliData* cliData);
CliStatus cmddwlimit_c600(T_VOID* priv, CliData* cliData);
CliStatus cmduplimit_c600(T_VOID* priv, CliData* cliData);

//wless2 network ssidp roaming
CliStatus cmdfract(T_VOID* priv, CliData* cliData);
CliStatus cmdadvsch(T_VOID* priv, CliData* cliData);


//wless2 network secu cli_table_wpa_supplicant
CliStatus cmdeapmtd(T_VOID* priv, CliData* cliData);
CliStatus cmdeapauth(T_VOID* priv, CliData* cliData);
CliStatus cmdauthid(T_VOID* priv, CliData* cliData);
CliStatus cmdauthpwd(T_VOID* priv, CliData* cliData);
CliStatus cmdwpasupaccept(T_VOID* priv, CliData* cliData);

//wless2 network stassid
CliStatus cmdstassid(T_VOID* priv, CliData* cliData);

//wless2 network bssidact
CliStatus cmdbssidact(T_VOID* priv, CliData* cliData);

//wless2 network bssid
CliStatus cmdbssid(T_VOID* priv, CliData* cliData);

//wless2 network apscan
CliStatus cmdapscan(T_VOID* priv, CliData* cliData);

//wless2 network secu
CliStatus cmdsecu(T_VOID* priv, CliData* cliData);


//wless2 guest guestact
CliStatus cmdgnact(T_VOID* priv, CliData* cliData);

//wless2 guest gnssid
CliStatus cmdgnssid(T_VOID* priv, CliData* cliData);

//wless2 guest gnsupssid
CliStatus cmdgnsupssid(T_VOID* priv, CliData* cliData);

//wless2 guest gnsepa
CliStatus cmdgnsepa(T_VOID* priv, CliData* cliData);


//wless2 guest gnip gnipaddr
CliStatus cmdgnipaddr(T_VOID* priv, CliData* cliData);

//wless2 guest gnip gnipsubn
CliStatus cmdgnipsubn(T_VOID* priv, CliData* cliData);

//wless2 guest gnip accept
CliStatus cmdgnipsetaccept(T_VOID* priv, CliData* cliData);


//wless2 guest gndhcp gnsip
CliStatus cmdgndhcpsip(T_VOID* priv, CliData* cliData);

//wless2 guest gndhcp gneip
CliStatus cmdgndhcpeip(T_VOID* priv, CliData* cliData);


//wless2 guest gndhcp gnwip
CliStatus cmdgndhcpwip(T_VOID* priv, CliData* cliData);

//wless2 guest gndhcp accept
CliStatus cmdgndhcpsetaccept(T_VOID* priv, CliData* cliData);

CliStatus cmdgnapsecu(T_VOID* priv, CliData* cliData);


//wless2 macfilter
CliStatus cmdacl(T_VOID* priv, CliData* cliData);
CliStatus cmdadd(T_VOID* priv, CliData* cliData);
CliStatus cmddel(T_VOID* priv, CliData* cliData);

//wless2 advset drate
CliStatus cmddrate(T_VOID* priv, CliData* cliData);

//wless2 advset regpower
CliStatus cmdregpower(T_VOID* priv, CliData* cliData);

//wless2 advset txpower
CliStatus cmdtxpower(T_VOID* priv, CliData* cliData);

//wless2 advset rts
CliStatus cmdrts(T_VOID* priv, CliData* cliData);

//wless2 advset dist
CliStatus cmddist(T_VOID* priv, CliData* cliData);

//wless2 advset antenna 
CliStatus cmdantenna(T_VOID* priv, CliData* cliData);

//wless2 advset aggr
CliStatus cmdaggract(T_VOID* priv, CliData* cliData);
CliStatus cmdfram(T_VOID* priv, CliData* cliData);
CliStatus cmdbyte(T_VOID* priv, CliData* cliData);

//wless2 advset traffic
CliStatus cmdtsact(T_VOID* priv, CliData* cliData);
CliStatus cmdinlimit(T_VOID* priv, CliData* cliData);
CliStatus cmdoutlimit(T_VOID* priv, CliData* cliData);

//wless2 advset traffic tsratio
CliStatus cmdwdsratio(T_VOID* priv, CliData* cliData);
CliStatus cmdssidratio(T_VOID* priv, CliData* cliData);

//wless2 fhandover fhact
CliStatus cmdfhact(T_VOID* priv, CliData* cliData);

//wless2 fhandover fhrssi
CliStatus cmdfhrssi(T_VOID* priv, CliData* cliData);

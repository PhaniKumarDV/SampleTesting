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
#ifndef _CLI_SYSTEM_H_
#define _CLI_SYSTEM_H_

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

//sys opmode
CliStatus cmddevname(T_VOID* priv, CliData* cliData);
CliStatus cmdctry(T_VOID* priv, CliData* cliData);
CliStatus cmdopmode(T_VOID* priv, CliData* cliData);

//sys ip
CliStatus cmddhcpact(T_VOID* priv, CliData* cliData);

CliStatus cmdpdns(T_VOID* priv, CliData* cliData);
CliStatus cmdsdns(T_VOID* priv, CliData* cliData);
CliStatus cmdipaddr(T_VOID* priv, CliData* cliData);
CliStatus cmdipsubn(T_VOID* priv, CliData* cliData);
CliStatus cmdgateway(T_VOID* priv, CliData* cliData);
CliStatus cmdipsetaccept(T_VOID* priv, CliData* cliData);
CliStatus cmdipsetexit(T_VOID* priv, CliData* cliData);

//sys ipv6
CliStatus cmdlink6(T_VOID* priv, CliData* cliData);
CliStatus cmdipaddr6(T_VOID* priv, CliData* cliData);
CliStatus cmdsublen6(T_VOID* priv, CliData* cliData);
CliStatus cmdgateway6(T_VOID* priv, CliData* cliData);
CliStatus cmdpdns6(T_VOID* priv, CliData* cliData);
CliStatus cmdsdns6(T_VOID* priv, CliData* cliData);

//sys stp
CliStatus cmdstpstat(T_VOID* priv, CliData* cliData);
CliStatus cmdhtime(T_VOID* priv, CliData* cliData);
CliStatus cmdmage(T_VOID* priv, CliData* cliData);
CliStatus cmdfdelay(T_VOID* priv, CliData* cliData);
CliStatus cmdprio(T_VOID* priv, CliData* cliData);


/*engenius*/
CliStatus cmdSystemsave(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemmain(T_VOID* priv, CliData* cliData);
CliStatus cmdsystemclient(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemsyslog(T_VOID* priv, CliData* cliData);

CliStatus cmdSystemconn(T_VOID* priv, CliData* cliData);

CliStatus cmdSystemdhcpcli(T_VOID* priv, CliData* cliData);
CliStatus cmdsystime(T_VOID* priv, CliData* cliData);

CliStatus cmdfwversion(T_VOID* priv, CliData* cliData);

CliStatus cmdethermac(T_VOID* priv, CliData* cliData);


CliStatus cmdapscan(T_VOID* priv, CliData* cliData);

CliStatus cmdkickclient(T_VOID* priv, CliData* cliData);


CliStatus cmdSystemTimeInfo(T_VOID* priv, CliData* cliData);
#if HAS_HW_RTC
CliStatus cmdSystemTimeRtcDate(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemTimeRtcTime(T_VOID* priv, CliData* cliData);
#endif
#if HTTPD_REMOTEPORT_FUNCTION
CliStatus cmdSystemAdminInfo(T_VOID* priv, CliData* cliData);
#endif
CliStatus cmdSystemAdminChangePw(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemSchList(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemSchNew(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemSchEdit(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemSchDelete(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemNtpServer(T_VOID* priv, CliData* cliData);
CliStatus cmdSysFwInfo(T_VOID* priv, CliData* cliData);
CliStatus cmdSysFtpUpgrade(T_VOID* priv, CliData* cliData);
CliStatus cmdSysConfRestoreDefault(T_VOID* priv, CliData* cliData);
#ifdef WAN_DEV /* cfho 2008-1226 */
CliStatus cmdSystemStatusWan(T_VOID* priv, CliData* cliData);
#endif
CliStatus cmdSystemStatusLan(T_VOID* priv, CliData* cliData);
#if HAS_PBX
CliStatus cmdSystemStatusPbx(T_VOID* priv, CliData* cliData);
#endif
CliStatus cmdSystemStatusFxs(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemStatusInfo(T_VOID* priv, CliData* cliData);

CliStatus cmdSystemMode(T_VOID* priv, CliData* cliData);
CliStatus cmdEORSystemMode(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemReboot(T_VOID* priv, CliData* cliData);
CliStatus cmdTelnet(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemSnmp(T_VOID* priv, CliData* cliData);
CliStatus cmdsnmpversion(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemEventlog(T_VOID* priv, CliData* cliDat);
CliStatus cmdSystemIntegrity(T_VOID* priv, CliData* cliDat);
CliStatus cmdSystemTimeNTPServer1(T_VOID* priv, CliData* cliDat);
CliStatus cmdDDNSServerType(T_VOID* priv, CliData* cliDat);
CliStatus cmdSystemCheckfreememory(T_VOID* priv, CliData* cliDat);
#if HAS_LED_CONTROL
CliStatus cmdLedPower(T_VOID* priv, CliData* cliData);
CliStatus cmdLedLan(T_VOID* priv, CliData* cliData);
CliStatus cmdLedWlan(T_VOID* priv, CliData* cliData);
CliStatus cmdLedInfo(T_VOID* priv, CliData* cliData);
#endif
#if HAS_AP_PROFILE
CliStatus cmdSystemAPprofileList(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemAPprofileDel(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemAPprofileNew(T_VOID* priv, CliData* cliData);
CliStatus cmdSystemAPprofileEdit(T_VOID* priv, CliData* cliData);
#endif
T_INT32 __schListShow(T_VOID);
#endif

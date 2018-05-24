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
//mgmt admin
CliStatus cmdnewname(T_VOID* priv, CliData* cliData);
CliStatus cmdoldpwd(T_VOID* priv, CliData* cliData);
CliStatus cmdnewpwd(T_VOID* priv, CliData* cliData);
CliStatus cmdconfirmpwd(T_VOID* priv, CliData* cliData);
CliStatus cmdadminaccept(T_VOID* priv, CliData* cliData);
CliStatus cmdadminexit(T_VOID* priv, CliData* cliData);

CliStatus cmdrmgmt(T_VOID* priv, CliData* cliData);
CliStatus cmdrupgrade(T_VOID* priv, CliData* cliData);
CliStatus cmdrmport(T_VOID* priv, CliData* cliData);

//mgmt vlan2 / vlan5
CliStatus cmdvlanp(T_VOID* priv, CliData* cliData);
CliStatus cmdvlanpexit(T_VOID* priv, CliData* cliData);

//mgmt vlan2 ssidact
//mgmt vlan2 isoact
//mgmt vlan2 vid


//mgmt mvlan
CliStatus cmdmvlan(T_VOID* priv, CliData* cliData);


//Add on 2013-06-06 by Philips to support WLAN VLAN Pass-Through for eap900 which is requested by Jacy
//mgmt mvlan
CliStatus cmdvdisable(T_VOID* priv, CliData* cliData);
CliStatus cmdv2to5(T_VOID* priv, CliData* cliData);
CliStatus cmdv5to2(T_VOID* priv, CliData* cliData);


//mgmt clientc bsteer
CliStatus cmdbsteeract(T_VOID* priv, CliData* cliData);
CliStatus cmdthreshold(T_VOID* priv, CliData* cliData);

//mgmt clientc ratec2 or ratec5
CliStatus cmddrateenable(T_VOID* priv, CliData* cliData);
CliStatus cmdratecontrol(T_VOID* priv, CliData* cliData, T_INT32 enable, T_INT32 data);
CliStatus cmddratedisable(T_VOID* priv, CliData* cliData);
CliStatus cmdbrateenable(T_VOID* priv, CliData* cliData);
CliStatus cmdbratedisable(T_VOID* priv, CliData* cliData);

//mgmt clientc climit2 or climit5
CliStatus cmdclimit2act(T_VOID* priv, CliData* cliData);
CliStatus cmdclimit2max(T_VOID* priv, CliData* cliData);
CliStatus cmdclimit5act(T_VOID* priv, CliData* cliData);
CliStatus cmdclimit5max(T_VOID* priv, CliData* cliData);

//mgmt cloud
CliStatus cmdcloudact(T_VOID* priv, CliData* cliData);
CliStatus cmdpserver(T_VOID* priv, CliData* cliData);
CliStatus cmdpport(T_VOID* priv, CliData* cliData);
CliStatus cmdpusername(T_VOID* priv, CliData* cliData);
CliStatus cmdppasswd(T_VOID* priv, CliData* cliData);

//mgmt capser
CliStatus cmdcapser(T_VOID* priv, CliData* cliData);

//mgmt snmp
CliStatus cmdsnmpact(T_VOID* priv, CliData* cliData);
CliStatus cmdcont(T_VOID* priv, CliData* cliData);
CliStatus cmdloca(T_VOID* priv, CliData* cliData);

//Add on 2013-05-09 by Philips to support SNMP for eap600 which is requested by Jackey
CliStatus cmdport(T_VOID* priv, CliData* cliData);


CliStatus cmdrcom(T_VOID* priv, CliData* cliData);
CliStatus cmdwcom(T_VOID* priv, CliData* cliData);
CliStatus cmdtrapaddr(T_VOID* priv, CliData* cliData);

//Add on 2013-05-09 by Philips to support SNMP for eap600 which is requested by Jackey
CliStatus cmdtrapport(T_VOID* priv, CliData* cliData);


CliStatus cmdtrapcom(T_VOID* priv, CliData* cliData);

CliStatus cmdsnmpv3act(T_VOID* priv, CliData* cliData);
CliStatus cmdusername(T_VOID* priv, CliData* cliData);
CliStatus cmdauthp(T_VOID* priv, CliData* cliData);
CliStatus cmdauthk(T_VOID* priv, CliData* cliData);
CliStatus cmdprivp(T_VOID* priv, CliData* cliData);
CliStatus cmdprivk(T_VOID* priv, CliData* cliData);
CliStatus cmdengineid(T_VOID* priv, CliData* cliData);


//Add on 2013-06-17 by Philips to support Email Alert for eap900 which is requested by Jacy
//mgmt email
CliStatus cmdmailact(T_VOID* priv, CliData* cliData);
CliStatus cmdaddrto(T_VOID* priv, CliData* cliData);
CliStatus cmdaddrfrom(T_VOID* priv, CliData* cliData);
CliStatus cmdmailauth(T_VOID* priv, CliData* cliData);
CliStatus cmdmailusr(T_VOID* priv, CliData* cliData);
CliStatus cmdmailpwd(T_VOID* priv, CliData* cliData);
CliStatus cmdsmtpsvr(T_VOID* priv, CliData* cliData);
CliStatus cmdsmtport(T_VOID* priv, CliData* cliData);
CliStatus cmdmailsec(T_VOID* priv, CliData* cliData);
CliStatus cmdalert(T_VOID* priv, CliData* cliData);
CliStatus cmdsubject(T_VOID* priv, CliData* cliData);
CliStatus cmdmessage(T_VOID* priv, CliData* cliData);



//Add on 2013-06-06 by Philips to support SSH and HTTPS for eap900 which is requested by Jacy
//mgmt ssh
CliStatus cmdssh(T_VOID* priv, CliData* cliData);
//mgmt hact
CliStatus cmdhact(T_VOID* priv, CliData* cliData);
//mgmt hfwd
CliStatus cmdhfwd(T_VOID* priv, CliData* cliData);


//mgmt backup
CliStatus cmdsavecp(T_VOID* priv, CliData* cliData);
CliStatus cmdrestore(T_VOID* priv, CliData* cliData);
CliStatus cmdrevertfac(T_VOID* priv, CliData* cliData);


//Add on 2013-06-06 by Philips to support Reset User Default for eap900 which is requested by Jacy
CliStatus cmdsaveuser(T_VOID* priv, CliData* cliData);
CliStatus cmdrestoreuser(T_VOID* priv, CliData* cliData);


//mgmt autorb
CliStatus cmdrbact(T_VOID* priv, CliData* cliData);
CliStatus cmdrbfreq(T_VOID* priv, CliData* cliData);
CliStatus cmdrbamt(T_VOID* priv, CliData* cliData);

//mgmt autorb
CliStatus cmdarbact(T_VOID* priv, CliData* cliData);
CliStatus cmdarbday(T_VOID* priv, CliData* cliData);
CliStatus cmdarbtime(T_VOID* priv, CliData* cliData);

//mgmt fwgrade
CliStatus cmdfwup(T_VOID* priv, CliData* cliData);

//mgmt time
CliStatus cmdauto(T_VOID* priv, CliData* cliData);
CliStatus cmddate(T_VOID* priv, CliData* cliData);
CliStatus cmdtz(T_VOID* priv, CliData* cliData);
CliStatus cmdntpact(T_VOID* priv, CliData* cliData);
CliStatus cmdntpip(T_VOID* priv, CliData* cliData);
CliStatus cmdautoexit(T_VOID* priv, CliData* cliData);

//mgmt time dlsave
CliStatus cmddlsact(T_VOID* priv, CliData* cliData);
CliStatus cmdmonthtime(T_VOID* priv, CliData* cliData);
CliStatus cmdweektime(T_VOID* priv, CliData* cliData);
CliStatus cmddaytime(T_VOID* priv, CliData* cliData);
CliStatus cmdhourtime(T_VOID* priv, CliData* cliData);

//mgmt wifisch
CliStatus cmdwslist(T_VOID* priv, CliData* cliData);
CliStatus cmdwsact(T_VOID* priv, CliData* cliData);
CliStatus cmdwsdel(T_VOID* priv, CliData* cliData);

CliStatus cmdsetwsname(T_VOID* priv, CliData* cliData);
CliStatus cmdsetwswp(T_VOID* priv, CliData* cliData);
CliStatus cmdsetwsday(T_VOID* priv, CliData* cliData);
CliStatus cmdsetwshour(T_VOID* priv, CliData* cliData);
CliStatus cmdsetwsmin(T_VOID* priv, CliData* cliData);
CliStatus cmdwsaccept(T_VOID* priv, CliData* cliData);
CliStatus cmdwifischeduleexit(T_VOID* priv, CliData* cliData);

//Modify for function alignment of Wifi schedule to dual radio models on 2012-11-30
CliStatus cmddualwslist(T_VOID* priv, CliData* cliData);
CliStatus cmddualwsdel(T_VOID* priv, CliData* cliData);
CliStatus cmdsetwssvc(T_VOID* priv, CliData* cliData);
CliStatus cmdsetdualwsday(T_VOID* priv, CliData* cliData);
CliStatus cmdsetdualwshour(T_VOID* priv, CliData* cliData);
CliStatus cmdsetdualwsmin(T_VOID* priv, CliData* cliData);
CliStatus cmddualwsaccept(T_VOID* priv, CliData* cliData);
CliStatus cmddualwifischeduleexit(T_VOID* priv, CliData* cliData);

//Add new Wifi schedule for EAP900 on 2013-07-10
CliStatus cmdnewwsact(T_VOID* priv, CliData* cliData);
CliStatus cmdwsradio(T_VOID* priv, CliData* cliData);
CliStatus cmdwsssid(T_VOID* priv, CliData* cliData);
CliStatus cmdwstemp(T_VOID* priv, CliData* cliData);
CliStatus cmddisplay(T_VOID* priv, CliData* cliData);
CliStatus cmdsetavail(T_VOID* priv, CliData* cliData);
CliStatus cmdsettime(T_VOID* priv, CliData* cliData);
CliStatus cmdnewdualwsaccept(T_VOID* priv, CliData* cliData);

//mgmt log
CliStatus cmdsyslog(T_VOID* priv, CliData* cliData);
CliStatus cmdlogip(T_VOID* priv, CliData* cliData);
CliStatus cmdllog(T_VOID* priv, CliData* cliData);

//mgmt diag or diagv6
CliStatus cmdping(T_VOID* priv, CliData* cliData);
CliStatus cmdtrace(T_VOID* priv, CliData* cliData);
CliStatus cmdroute(T_VOID* priv, CliData* cliData);
CliStatus cmdarp(T_VOID* priv, CliData* cliData);
CliStatus cmdtelnet(T_VOID* priv, CliData* cliData);
CliStatus cmdsptest(T_VOID* priv, CliData* cliData);

CliStatus cmdping6(T_VOID* priv, CliData* cliData);
CliStatus cmdtrace6(T_VOID* priv, CliData* cliData);
CliStatus cmdtelnet6(T_VOID* priv, CliData* cliData);
CliStatus cmdsptest6(T_VOID* priv, CliData* cliData);

//mgmt disc
CliStatus cmddisc(T_VOID* priv, CliData* cliData);

//mgmt led
CliStatus cmdpled(T_VOID* priv, CliData* cliData);
CliStatus cmdlled(T_VOID* priv, CliData* cliData);
CliStatus cmdwled(T_VOID* priv, CliData* cliData);
CliStatus cmd2led(T_VOID* priv, CliData* cliData);
CliStatus cmd5led(T_VOID* priv, CliData* cliData);
CliStatus cmdwpsled(T_VOID* priv, CliData* cliData);
CliStatus cmd2wpsled(T_VOID* priv, CliData* cliData);
CliStatus cmd5wpsled(T_VOID* priv, CliData* cliData);

//mgmt radio2 or radio5
CliStatus cmdradioup(T_VOID* priv, CliData* cliData);
CliStatus cmdradiodown(T_VOID* priv, CliData* cliData);

//mgmt logout
CliStatus cmdlogout(T_VOID* priv, CliData* cliData);

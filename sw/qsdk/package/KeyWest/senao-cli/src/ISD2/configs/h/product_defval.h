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
;    Creator : 
;    File    : product_banner.h
;    Abstract: include file of the application profile.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2009-0304       Newly Create
;*****************************************************************************/

#ifndef _PRODUCT_BANNER_CONFIG_H_

 
/********************************************************/
/*          UPNPD                                       */
#define UPNPD_FIRENDLY_NAME     "Sitecom 802.11n Wireless Broadband Router"
#define UPNPD_MANUFACTURE       "Sitecom Europe BV"
#define UPNPD_MANUFACTURE_URL   "http://www.sitecom.com"
#define UPNPD_MODEL_DESC        "802.11n 300Mbps Wireless Router 300N X3"
#define UPNPD_MODEL_DESC2       "802.11n 300Mbps Wireless Router 300N X2"
#define UPNPD_MODEL_NAME        "Sitecom Wireless Router 300N X3"
#define UPNPD_MODEL_NAME2       "Sitecom Wireless Router 300N X2"
#define UPNPD_MODEL_NUMBER      "300N"
#define UPNPD_MODEL_URL         "http://www.sitecom.com/"
/********************************************************/
/********************************************************/

/********************************************************/
/*          NTPD                                        */
#define NTPD_TIME_SERV_ADDR     "europe.pool.ntp.org"
/********************************************************/

/*ApCfg Default Value*/
#define APCFG_DEF_LAN_IPADDR            "192.168.0.1"
#define APCFG_DEF_DHCPD_START_1         "192.168.0.100"
#define APCFG_DEF_DHCPD_END_1           "192.168.0.200"
#define APCFG_DEF_DHCPD_STATUS			"1"

#undef APCFG_DEF_PASSPHRASEKEY         
#undef APCFG_DEF_WAN1_HOST             
#undef APCFG_DEF_WAN1_PPTP_HOSTNAME    
#undef APCFG_DEF_HOSTNAME              

#define APCFG_DEF_SYS_OP_MODE           "0" /*2*/
#define APCFG_DEF_PASSPHRASEKEY         ""
#define APCFG_DEF_WAN1_HOST             ""
#define APCFG_DEF_WAN1_PPTP_HOSTNAME    ""
#define APCFG_DEF_HOSTNAME              "sitecomrouter"
#define APCFG_DEF_DOMAINNAME            ""
#define APCFG_DEF_WAN1_ISP_MTU                  "1492"  
#define APCFG_DEF_WAN1_PPTP_MTU                 "1462"
#define APCFG_DEF_WAN1_IPADDR                   "172.1.1.1"
#define APCFG_DEF_WAN1_MASK                     "255.255.0.0"
#define APCFG_DEF_WAN1_GATEWAYIP                "172.1.1.254"
#define APCFG_DEF_SNMPD_REMOTE_WAN_IP   "192.168.0.100"
#define APCFG_DEF_DMZ_IP                "192.168.1.1"

#define APCFG_DEF_URLFILTER_ENABLE         "0"
#define APCFG_DEF_TRIGGER_PORT_ENABLE      "0"
#define APCFG_DEF_FIREWALL_ENABLE          "1"
#define APCFG_DEF_DMZ_ENABLE               "0"
#define APCFG_DEF_DMZ_MULTI_ENABLE         "0"
#define APCFG_DEF_NAT_PORT_FORWARD_ENABLE  "0"
#define APCFG_DEF_WLAN11G_RADIO            "1"
#define APCFG_DEF_WLAN11G_AUTO_CH_SEL      "0"   
#define APCFG_DEF_WLAN11G_AUTO_CH_CHK_TIME "3"
#define APCFG_DEF_WLAN_WPS_ENABLE          "1"
#define APCFG_DEF_UPNPD_ENABLE             "0"
#define APCFG_DEF_UPNPD_PORT_MAP_ENABLE    "1"
#define APCFG_DEF_DHCPD_MINLEASE_TIME      "8" /*forever*/
#define APCFG_DEF_SYS_POWERSAVING_MODE     "0"
#define APCFG_DEF_TIME_ZONE                "26"
#define APCFG_DEF_SYS_ROUTE_ENABLE_TOK     "0"
#define APCFG_DEF_WLAN_WPS_STATUS		    "1"
#define APCFG_DEF_WAN1_CONNECTION_TYPE	    "2"
#define APCFG_DEF_WAN1_DEV                 WAN1_DEV
#define APCFG_DEF_WLAN11G_THRESHOLD        "2347"
#define APCFG_DEF_ALG_SUPPORT		           "0"
#define APCFG_DEF_WLAN11G_MODE		        "9"
#define APCFG_DEF_WLAN11G_PREAMBLE          "1"

#define APCFG_DEF_WLAN_ATH1_MODE	            "9" /*2.4G bgn*/
#define APCFG_DEF_ATH1_RTS_THRESHOLD        "2347"
/*joey ECB serial will use DNS Server and set the default value to "User Define"*/
/*default should be DNS-Relay*/
#define APCFG_DEF_DNS_SERV_TYPE_1	"2"

/*SNMPD*/
#define APCFG_DEF_SNMPD_ENABLE          "0"
#define APCFG_DEF_SNMPD_SYS_LOCATION    "EnGenius Technologies, Inc."
#define APCFG_DEF_SNMPD_SYS_CONTACT     "SENAO Networks, Inc."
#define APCFG_DEF_SNMPD_SYS_NAME        "EnGenius DB120"
#define APCFG_DEF_SNMPD_TRAP_ENABLE             "1"
#define APCFG_DEF_SNMPD_TRAP_IP                 "192.168.1.100"

/*Radio Default Vale*/
#define APCFG_DEF_MODE_RADIO_1                     "0"/*for atheros*/
#define APCFG_DEF_MODE_RADIO_2                     "8"/*for atheros*/
#define APCFG_DEF_SELECTED_RADIO                   "0"
#define APCFG_DEF_ATH_COUNTRYCODE                  "840"
/*WPS*/
#define APCFG_DEF_ATH1_WPS_STATUS       "0" /*0(for GUI)1 unconfigure, 1(for GUI)2 configured*/
#define APCFG_DEF_ATH1_WPS_ENABLE       "1"

/************************/
/* WLAN default setting */
/************************/
/*0: None 1: WEP 2:WPA-PSK 3:WPA-EAP*/
/*First SSID Security*/
#define APCFG_DEF_WLAN11G_ENC_TYPE  	   "3" //"0"
#define APCFG_DEF_WLAN11G_AUTH			   "5" //"0"
/*Second SSID Security*/
#define APCFG_DEF_WLAN2_ENC_TYPE           "0"
#define APCFG_DEF_WLAN2_AUTH			   "1"
/*Third SSID Security*/
#define APCFG_DEF_WLAN3_ENC_TYPE           "0"
#define APCFG_DEF_WLAN3_AUTH			   "1"
/*Forth SSID Security*/
#define APCFG_DEF_WLAN4_ENC_TYPE           "0"
#define APCFG_DEF_WLAN4_AUTH			   "1"
/*0,64,128*/
#define APCFG_DEF_WLAN11G_WEP       "64"
/*0:HEX 1:ASCII*/
#define APCFG_DEF_WLAN11G_KEYTYPE   "1"
/*Set WEP Key default value to empty*/
#define APCFG_DEF_WLAN11G_WEP_KEY   ""
/*Set WDS WEP Key default value to empty*/
#define APCFG_DEF_WLAN_WDS_WEP_KEY  ""
/*Set WDS WPA Key default value to empty*/
#define APCFG_DEF_WDS_PASSPHRASEKEY ""
/*1T1R==>set bw to 20(0),otherwise bw to 40(1) */
#define APCFG_DEF_BW40_ENABLE	"1"
/*Set HWNAT default value to 0*/
#define APCFG_DEF_HWNAT_EN      "0"
/* Netbios */
#define	APCFG_DEF_HTTP_SYSTEM_NAME  "SITECOM"

//check!!
#define APCFG_DEF_WLAN_RADIO_1			"1"
#define APCFG_DEF_WLAN_RADIO_2			"0" /*1221AN has no Radio 2*/
#define APCFG_DEF_ATH1_CHANNEL			"11" //"40"
/************************/
/* Mangement setting    */
/************************/
#define APCFG_DEF_HTTP_LOGIN_USERNAME      "admin"
#define APCFG_DEF_HTTP_REMOTE_PW           "admin"    
#define APCFG_DEF_HTTP_REMOTE_IPADDR    "0.0.0.0"
#define APCFG_DEF_HTTP_IDLETIME         "10"
#define APCFG_DEF_HTTP_REMOTE_EN        "0"
#define APCFG_DEF_HTTP_REMOTE_PORT		"8080"

/* access method *//* BitMap 0: disable, 1: LAN, 2:WAN */
#define APCFG_DEF_TELNETD_ACCESS		"1"
#define APCFG_DEF_SSHD_ACCESS			"1"
#define APCFG_DEF_FTPD_ACCESS			"1"

//check!!
#define APCFG_DEF_ETH_PURPOSE			"1" /*0 LAN, 1: WAN*/

/* 20090930 Nelson : for pass Win 7 logo */
/* IGMP Proxy */
#define APCFG_DEF_IGMP_PROXY_EN         "1"

#endif

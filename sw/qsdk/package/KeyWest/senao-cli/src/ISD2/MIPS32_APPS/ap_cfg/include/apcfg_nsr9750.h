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
;    Project : SI-688H
;    Creator : 
;    File    : 
;    Abstract: This file should accord to project! So not synchonize
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       
;*****************************************************************************/
#ifndef _APCFG_EX_H
#define _APCFG_EX_H
#include <gconfig.h>
#include <opmodes.h>
/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/

//mhchen:2007-0202 VOIP Information,web use 
#define CALL_MONITOR_FILE 		"/var/log/asterisk/monitor/channels"
#define SIP_REGISTRY_FILE		"/var/log/asterisk/monitor/registry"
#define SIP_PEERS_FILE			"/var/log/asterisk/monitor/peers"
#define SIP_STATUS_FILE			"/var/log/asterisk/monitor/status"
#define SIP_CDR_FILELIST_NAME 	"cdrlist"
//#define SIP_CDR_FILE_PATH     "/storage/"
#define SIP_CDR_FILE_PATH     	"/var/log/asterisk/cdr-custom/"
#define CSVCUT_FILE_PATH      	"/var/cvscut/"


#define DHCPDItemListMax 	1 //only one dhcp pool is supported in Rt28xx
#define NUM_WAN_DNS		 	2

#define MACFILTER_PATTERN 			"%d,%d,%02X%02X%02X%02X%02X%02X,%d,%s"
#define MACFILTER_PATTERN_ITEMS 	10

#define L7FILTER_PATTERN 			"%d,%d"
#define L7FILTER_PATTERN_ITEMS 		2

/*jaykung 20060823 blacklist for grpinfo*/
// #define BLACKLIST_PATTERN "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d"
// #define BLACKLIST_PATTERN "%d,%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,%ss"
#define BLACKLIST_PATTERN_ITEM 		10

/* day time mask */
#define IS_DT_MON   0x1000000
#define IS_DT_TUE   0x0100000
#define IS_DT_WED   0x0010000
#define IS_DT_THR   0x0001000
#define IS_DT_FRI   0x0000100
#define IS_DT_SAT   0x0000010
#define IS_DT_SUN   0x0000001

/*WLAN11b g channel list num*/
#define WLANCHMAXUMN 				14

//#define WLAN_CLIENTINFO_PATH    		"/proc/net/madwifi/ath0/associated_sta"

#define NAT_VSERVER_PATTERN 			"%d,%d,%d,%d,%d,%d,"
#define NAT_VSERVER_PATTERN_ITEMS 		7
#define NUM_NAT_SERVER 				NUM_NAT_VSERVER
#define NUM_NAT_PORT_FORWARD			NUM_PORT_FORWARD
#define URL_CONTENT_MAX             		40

#define MAX_SCHEDULE_LIST 			NUM_SCHEDULE_LIST
#define MAX_SCHED_DES   			25

//#define MAX_TIME_INFO_LIST 			8
#define MAX_TIME_INFO_DES   			25

#define MAX_DATABASE_LIST 			32
#define MAX_DATABASE_DES   			20

#define ISENABLE_PATTERN    			"%d,"

#define NUM_APPLICATION_FILTER  		2

#define MAX_DHCP_MACTOIP                        NUM_DHCPD_MACTOIP

#define IPFILTER_PATTERN 			"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s"
#define IPFILTER_PATTERN_ITEMS  		11
#define DAYTIME_PATTERN 			"%d,%02d,%02d,%02d,%02d,0x%07x"
#define DAYTIME_PATTERN_ITEMS  			6

#define MAX_WEPKEY_LEN 				33
#define MAX_MAC_ADDR_LEN_IN_BYTE 		6
#define MAX_MAC_ADDR_LEN_IN_STR			20
#define NUM_SNMP        			5
#define NUM_COUNTRY    				97
#define NUM_STATIC_ASSIGN_IPS     		10
/*smtp*/
#define STMP_MAX_ID     			128
#define STMP_MIN_ID     			1
#define STMP_MAX_PWD				64
#define STMP_MIN_PWD    			1

#define MAX_LENGTH_TELNUM 			32

//static routing
#define MAX_STATIC_ROUTING      		NUM_STATICROUTING
#define MAX_STATICROUTING_NAME  		24

//max num of sntp server
#define NTP_SERVER_MAX 				3

//max num of dmz host
#define NUM_DMZ_HOSTS				5

/*jaykung 20061027 getFileInfo will produce this file to web_cgi*/
#define PARSE_FILEINFO_PATH 		"/var/tmp/info" 

/************************************************/
/*jaykung 20070503                              */
/*define output file path for different files   */
#define PARSE_DHCP_LEASE            "/var/tmp/p_dhcpInfo"
#define PARSE_SIP_CDR               "/var/tmp/p_sipCdr"
#define PARSE_SIP_CALLMONITOR       "/var/tmp/p_sipCallMonitor"
#define PARSE_SIP_PEER              "/var/tmp/p_sipPeer"
#define PARSE_SIP_REG              	"/var/tmp/p_sipReg"
/**************************************************/
/**Victor 20070507 path to store transcoding_list
The path will affect processes 
(1) "vm_file_check_gen" and 
(2) "trans_coding_check"*/
//Record if there were any vm_file needs to transcoding
#define TRANSCODING_LIST 			"/storage/transcoding_list"
//copy from transcoding_list in /storage, under transcoding proccess
#define TEMP_TRANSCODING_LIST 		"/tmp/transcoding_list"
/**backup from transcoding_list in /storage, it can be worked(recover) whether the transcoding proccess
was shut down un-expectly*/
#define BACKUP_TRANSCODING_LIST 	"/storage/backup_transcoding_list"
#define TRANSCODING_PROCESS_NAME 	"transcoder"
#define TRANS_CODING_CHECK_NAME 	"trans_coding_check"
/**************************************************/

/*jaykung 20070515 max number for followme function*/
#define MAX_FOLLOWME_NUM    		3

/*mhchen,2007-0303 resverd number for pbx*/
#define PBX_RESERVED_NUMBER 		"777,770,771,700,900,9,888"
#define PBX_RESERVED_NUMBER_RANGE 	"701,720,900,999"

#define CHECK_VERSION_LANG_FILE     "/var/%s_xml.txt"

/* cfho 2006-0824 */
/* Group for restarting setting */
#define G_NO          0   /* no group, or group is not assigned yet */
#define G_DUMMY       (1<<1) 	/* Dummy group. Don't store in ap_cfg_new and ap_cfg. Don't handle change */
#define G_LAN         (1<<2)
#define G_WAN         (1<<3)
#define G_WLAN        (1<<4)
#define G_AST         (1<<5)
#define G_FW          (1<<6)
#define G_QOS         (1<<7)
#define G_TIMEZONE    (1<<8)
#define G_WANDNS      (1<<9)
#define G_HOST_DOMAIN_NAME (1<<10)
#define G_SCH         (1<<11)
#define G_DHCPD       (1<<12)
#define G_WLANFW      (1<<13)
#define G_AUTO_PROV   (1<<14)
#define G_NTPD        (1<<15)
#define G_URL         (1<<16)
#define G_FILTER      (1<<17)
#define G_DDNS        (1<<18)
#define G_UPNPD       (1<<19)
#define G_HTTPD       (1<<20)
#define G_FWMD        (1<<21)
#define G_DNSPROXY    (1<<22)
#define G_TELENTD     (1<<23)
#define G_TFTPD       (1<<24)
#define G_LOG         (1<<25)
#define G_PPTPD       (1<<26)
#define G_SMTP        (1<<27)
#define G_ROUTING     (1<<28)
#define G_ALG         (1<<29)
// #define G_BUTTON      (1<<30)
#define G_KCODES	 (1<<30)
#define G_SNMPD	     ((T_UINT64) 1<<31)
#define G_USB        ((T_UINT64) 1<<32)
#define G_ATH1       ((T_UINT64) 1<<33)
#define G_ATH2       ((T_UINT64) 1<<34)
#define G_LLTD	     ((T_UINT64) 1<<35)
#define G_EBTABLES	 ((T_UINT64) 1<<36)
#define G_RA1        ((T_UINT64) 1<<37)
#define G_RA2        ((T_UINT64) 1<<38)
#define G_IGMPPROXY  ((T_UINT64) 1<<39)
#define G_RA2WLANFW  ((T_UINT64) 1<<40)   
#define G_NETBIOSD   ((T_UINT64) 1<<41)
#define G_TR         ((T_UINT64) 1<<42)
#define G_HTTPSD     ((T_UINT64) 1<<43)
#define G_MACBRIDGE  ((T_UINT64) 1<<44)
#define G_ACCOUNT    ((T_UINT64) 1<<45)
#define G_MACBRIDGING ((T_UINT64) 1<<46)
#define G_FTPD       ((T_UINT64) 1<<47)
#define G_HWNAT      ((T_UINT64) 1<<48)
#define G_VPN        ((T_UINT64) 1<<49)
#define G_AIRPORT    ((T_UINT64) 1<<50)
#define G_JP_STATICROUTING    ((T_UINT64) 1<<51)
#define G_WLAN_RADIO1    ((T_UINT64) 1<<52)
#define G_WLAN_RADIO2    ((T_UINT64) 1<<53)
#define G_HOSTAPD1       ((T_UINT64) 1<<54)
#define G_HOSTAPD2       ((T_UINT64) 1<<55)
#define G_IPV6           ((T_UINT64) 1<<56)
#define G_FIREWALLMD     ((T_UINT64) 1<<57)
#define G_NPH            ((T_UINT64) 1<<58)
#if HAS_SC_UTMPROXY_FUNCTION
#define	G_SCUTM	         ((T_UINT64) 1<<59)
#endif
#define G_DLNA      ((T_UINT64) 1<<60)
#define G_DHCPRELAY ((T_UINT64) 1<<61)
#define G_LED ((T_UINT64) 1<<62)
#define G_FIREWALL_V6 ((T_UINT64) 1<<63)


#if HASNT_NORMAL_SCHEDULE
#define G_SCHEDULE   (G_SCH|G_WLAN)
#else
#define G_SCHEDULE   (G_SCH|G_FW|G_WLAN|G_LAN)
#endif

#if HAS_SCHEDULED_FIREWALL
#define G_FIREWALL (G_FW|G_SCH)
#else
#define G_FIREWALL (G_FW)
#endif

#if DUAL_BAND_CONCURRENT_ONLY_SUPPORT_ONE_WLAN_LED
/* 2011-07-29 Norkay, Only support one WLAN LED, so reload two Radio when 2.4G/5G disable or enable. */
#define G_WLAN11G_RADIO (G_WLAN|G_RA2|G_SCHEDULE)
#define G_RA2_RADIO     (G_WLAN|G_RA2|G_SCHEDULE)
#else
#define G_WLAN11G_RADIO (G_WLAN|G_SCHEDULE)
#define G_RA2_RADIO     (G_RA2)
#endif

/*for AP profile*/
#define MAX_AP_PROFILE_ITEMS    3
#define MAX_MAC_ADDR_LENGTH     18
#define MAX_SSID_LEN            32
#define MAX_KEY_LEN             64
#define MAX_PASSPHRASE_LEN      64 //jaykung

/*jaykung 20080826 for WEB init page*/
typedef enum
{
	WEB_PAGE_NONE=0,
	WEB_PAGE_INDEX=1,
	WEB_PAGE_DUPLICATED,
	WEB_PAGE_REMOTE,
	WEB_PAGE_MANUFACTURER,
	WEB_PAGE_LOGOUT,
	WEB_PAGE_REPEATER_EASYSETUP
} WEB_INIT_PAGE_NUM;
/*-------------------------------------------------------------------------*/
/*                           enum                                          */
/*-------------------------------------------------------------------------*/
/*jaykung 20061017 blacklist status*/
enum
{
	BLKLIST_FIXED_VALUE=1,
	BLKLIST_TMP_VALUE 
};

enum
{
	PROTOCOL_TCP=0, PROTOCOL_UDP,PROTOCOL_BOTH,PROTOCOL_ICMP=3,PROTOCOL_ANY=4
};

enum
{
	PROTOCOL_TCP_BIT  = 1<<0,  /* Bit 0 */
	PROTOCOL_UDP_BIT  = 1<<1,  /* Bit 1 */
	PROTOCOL_BOTH_BIT = 0x3,   /* TCP+UDP, Bit 0,1 */
    PROTOCOL_ICMP_BIT = 1<<2,
	PROTOCOL_ANY_BIT  = 1<<3,
};

/*first byte 0:nouse, 1:enable:Aceept, 2: edit, 3:disable, 4:enable:reject*/

#if 0
/*macfilter disable allow reject*/
/*jaykung 20060725*/
enum
{
	FILTER_NONUSED=0, FILTER_ACCEPT, FILTER_EDIT, FILTER_DISABLE_ACCEPT, FILTER_DENY, FILTER_DISABLE_DENY
};
#else
/*jaykung 20070502 TYPE FOR FILTER*/
typedef enum
{
	FILTER_NONUSED=0,
	FILTER_ENABLE,
	FILTER_EDIT,
	FILTER_DISABLE
} FILTER_TYPE;
#endif
/*jaykung 20060808 firstbyte status*/
enum
{
	STATUS_NONUSED=0,STATUS_ENABLE,STATUS_EDIT,STATUS_DISABLE
};

/*Joeyli 20080820 EAP Method
	0:PEAP, 1:TLS, 2:TTLS, 3:FAST, 4:MD5*/
enum
{
	EAP_PEAP=0,
	EAP_TLS,
	EAP_TTLS,
	EAP_FAST,
	EAP_MD5
};

/*0:half hour 1:one hour 2:two hour 3:half day 4:one day
  5:two day 6:one week 7:two weeks 8:forever     */
/*dhcp lease time*/
/*Wlan AutoChannel selection */
enum
{
	HALF_HOUR=0, ONE_HOUR, TWO_HOUR, HALF_DAY, ONE_DAY, TWO_DAY,
	ONE_WEEK, TWO_WEEK, FOREVER_TEN_YEAR, EIGHT_HOUR
};


/*jaykung 20070509 QoS for port(priority)*/
typedef enum
{
	PORT_PRIORITY_LOW=0,
	PORT_PRIORITY_HIGH
} PORT_PRIORITY_TYPE;

/*joey 20081212 qos type based*/
typedef enum {
APPS_BASED_QOS=0,
PORT_BASED_QOS,
IP_BASED_QOS
} QOS_BASED;

#if HAS_WAN_3G
/*joey 20081223 3g isp list*/
typedef enum {
CHINA_MOBILE_CHINA=0,
CHT_TAIWAN,
TAIWANMOBILE_TAIWAN,
FETNET_TAIWAN,
TWN_GSM,
ISP_OTHER=100
} WAN_3G_ISP_LIST;

/* Mook 2009-0930 3G band list */
#if HAS_WAN_3G_BAND_SELECTION
typedef enum {
    BAND_AUTO = 0,
    BAND_2G_900_1800,
    BAND_3G_2100,
    BAND_3G_2100_2G_900_1800
} WAN_3G_BAND_LIST;
#endif
#endif /* HAS_WAN_3G */

#if HAS_SC_AUTO_FW_CHECK
typedef enum {
    ACTIOIN_INITIAL = 0,
    ACTIOIN_INSTALL,
    ACTIOIN_REMIND_LATER,
    ACTIOIN_NOT_REMIND_THIS_VERSION,
    ACTIOIN_NOT_REMIND_EVER
} FW_CHECK_ACTION;
#endif

/*interface for static routing*/
typedef enum
{
	SROUTING_LAN=0,
	SROUTING_WAN,
	SROUTING_MAX
} STATIC_ROUTING_INTERFACE;


/* WAN connection type */
/* cfho 2006-0712 */
enum {  WAN_CONNECTION_TYPE_STATICIP=0, 
        WAN_CONNECTION_TYPE_PPPOE=1,
        WAN_CONNECTION_TYPE_DHCP=2,
        WAN_CONNECTION_TYPE_PPTP=3,
        WAN_CONNECTION_TYPE_PPPOE_RU=4,
        WAN_CONNECTION_TYPE_PPTP_RU=5,
        WAN_CONNECTION_TYPE_PPPOE_JP=6,
        WAN_CONNECTION_TYPE_3G=7,
        WAN_CONNECTION_TYPE_WIMAX=8,
        WAN_CONNECTION_TYPE_L2TP=9,
        WAN_CONNECTION_TYPE_XGP=10,
        WAN_CONNECTION_TYPE_NULL=11,
};

#if SUPPORT_IPV6
enum {
    IPV6_TYPE_LINK_LOCAL=0,
    IPV6_TYPE_STATIC,
	IPV6_TYPE_DHCP,
	IPV6_TYPE_PPPOE,
	IPV6_TYPE_6IN4_TUNNEL,
	IPV6_TYPE_6TO4,
	IPV6_TYPE_STATELESS_AUTO,
	IPV6_TYPE_AUTO_CONFIG,
    IPV6_TYPE_6RD,
    IPV6_TYPE_MAX
};
#endif

#if HAS_VPN
enum VPN_CONNECTION_TYPE {
    VPN_CONNECTION_TYPE_DISABLED = 0,
    VPN_CONNECTION_TYPE_PPTP = 1,
    VPN_CONNECTION_TYPE_L2TP = 2,
    VPN_CONNECTION_TYPE_IPSEC = 3,
    VPN_CONNECTION_TYPE_L2TP_IPSEC = 4,
    VPN_CONNECTION_TYPE_MAX
};
#endif

#if HAS_PPPOE_JAPAN
enum WAN_PPPOE_TYPE
{
    TYPE_NORMAL = 0,
    TYPE_UNNUMBER_IP,
    TYPE_UNNUMBER_PRIVATE_IP,
};
#endif

/* DDNS connection type */
enum
{
	DDNS_TYPE_3322=0,
	DDNS_TYPE_DHS,
	DDNS_TYPE_DYNDNS,
	DDNS_TYPE_ODS,
	DDNS_TYPE_TZO,
	DDNS_TYPE_GNUDIP,
	DDNS_TYPE_DYNS,
	DDNS_TYPE_ZONEEDIT,
	DDNS_TYPE_DHIS,
	DDNS_TYPE_CYBERGATE,
	DDNS_TYPE_DYNDNS_C,
	DDNS_TYPE_NO_IP,
	DDNS_TYPE_EURODNS,
	DDNS_TYPE_REGFISH,
	DDNS_TYPE_IOBB,
	DDNS_TYPE_DLINK
};

typedef enum{
    ACL_TYPE_ALLOW= 0,
    ACL_TYPE_DENY
}ACL_TYPE;

/*joey 20071107 type for web submit */
typedef enum{
    SUBMIT_DEL= 0,
    SUBMIT_ADD,
    SUBMIT_APPLY,
	SUBMIT_EDIT,
	SUBMIT_ACTIVE
}WEB_SUBMIT;

/*jaykung 20060809 sipGetAuthTyep*/
typedef enum
{
	SIP_GETAUTH_TYPE_INPUTBYUSER=1,
	SIP_GETAUTH_TYPE_SAMEASID,
	SIP_GETAUTH_TYPE_AUTOPROVISION
} SIP_GETAUTH_TYPE;

/*jaykung 20060823 Blacklist type for grpinfo*/
typedef enum
{
	GRP_BLACKLIST_NONUSED=0,GRP_BLACKLIST_FULLMATCH,GRP_BLACKLIST_PARTIALMATCH
} BLACKLIST_TYPE;

/*jaykung 20070515 fowarding type*/
typedef enum
{
	FW_DISABLE=0,
	FW_UNCONDITIONAL,
	FW_SPECIAL_CASE,//no answer, on busy
	FW_FOLLOWME 
} FORWARDING_TYPE;

/* wlan and lan type*/
typedef enum
{
	LAN_TYPE= 0,
	WAN_TYPE,
	ATHEROS_11A_TYPE,
	ATHEROS_11G_TYPE,
	INTERSIL_11B_TYPE
}INTERFACE_TYPE;

#if 0
typedef enum
{
	WLAN_ENC_NONE, WLAN_ENC_WEP, 
	WLAN_ENC_WPA_TKIP, WLAN_ENC_WPA_AES, 
	WLAN_ENC_WPA2_TKIP, WLAN_ENC_WPA2_AES, 
	WLAN_ENC_WPA_EAP
}WLAN_ENC_TYPE;
#endif
typedef enum
{
	S_AP_GATEWAY=0,
	S_AP_ROUTER
} SCD_APMODE; 

/*jaykung 20071012 WscMode*/
typedef enum { 
    WSC_MODE_PIN=1,
    WSC_MODE_PBC
    } WLAN_WSCMODE;

/* 20090817 jerry: WdsPhyMode */
typedef enum {
	WDS_PHYMODE_CCK=0,
	WDS_PHYMODE_OFDM,
	WDS_PHYMODE_HTMIX,
	WDS_PHYMODE_GREENFIELD
}WDS_PHYMODE;


typedef enum {
REGDOMAIN_FCC=0,
REGDOMAIN_IC,
REGDOMAIN_ETSI,
REGDOMAIN_SPAIN,
REGDOMAIN_FR,
REGDOMAIN_MKK,
REGDOMAIN_MKK1,
REGDOMAIN_ISRAEL
} REGULAR_DOMAIN;

typedef enum {
WIRELESSMODE_24G_BG=0,
WIRELESSMODE_24G_B,
WIRELESSMODE_5G_A,
// WIRELESSMODE_ABG,
WIRELESSMODE_24G_G=4,
//WIRELESSMODE_5G_ABGN // both band   5
WIRELESSMODE_24G_N=6, //2.4G n
WIRELESSMODE_24G_GN,
WIRELESSMODE_5G_AN, //5G
WIRELESSMODE_24G_BGN, // if check 802.11b.      9
// WIRELESSMODE_24G_AGN,// if check 802.11b.      10
WIRELESSMODE_5G_N=11 // 11n-only with 5G band		11
} WIRELESS_MODE;

#if HAS_SUPPORT_ATHEROS_WLAN
typedef enum {
ATHEROS_WDS_ROOTAP=0,
ATHEROS_WDS_CLIENT
} ATHEROS_WDS_TYPE;
#endif

#if 0
typedef enum _RT_802_11_PHY_MODE {
	PHY_11BG_MIXED = 0,
	PHY_11B,
	PHY_11A,
	PHY_11ABG_MIXED,
	PHY_11G,
	PHY_11ABGN_MIXED,	// both band   5
	PHY_11N_2_4G,		// 11n-only with 2.4G band   	6
	PHY_11GN_MIXED,	// 2.4G band      7
	PHY_11AN_MIXED,	// 5G  band       8
	PHY_11BGN_MIXED,	// if check 802.11b.      9
	PHY_11AGN_MIXED,	// if check 802.11b.      10
	PHY_11N_5G,			// 11n-only with 5G band		11
} RT_802_11_PHY_MODE;
#endif

typedef enum{
PWR_SAVE_DISABLE=0,
PWR_SAVE_WLAN_ONLY,
PWR_SAVE_ETH_ONLY,
PWR_SAVE_ALL
}POWER_SAVE_MODE;

#if FOR_ZYXEL
typedef enum {
    LANGUAGE_ENG=0,
	LANGUAGE_GER,
	LANGUAGE_FRE,
	LANGUAGE_SPA,
	LANGUAGE_BIG5,
	LANGUAGE_ITA,
	LANGUAGE_CN,
	LANGUAGE_TURKEY,
	LANGUAGE_THAI,
	LANGUAGE_POLISH,
	LANGUAGE_CZECH,
	LANGUAGE_SLOVENE
} LANGUAGE_SET;
#else
typedef enum {
    LANGUAGE_ENG=0,
	LANGUAGE_BIG5
} LANGUAGE_SET;
#endif

typedef enum {
AP_MODE_AP=0,
// AP_MODE_AP_CLIENT=1,
AP_MODE_REPEATER=2,
AP_MODE_WDS=5,
AP_MODE_AP_CLIENT=6
} AP_MODE;

typedef enum {
SNMP_VER_ALL=0,
SNMP_VER1,
SNMP_VER2C,
SNMP_VER3
} SNMP_VER;

typedef enum {
SNMP_LAN=0,
SNMP_WAN,
SNMP_LANWAN,
} SNMP_CONN_MODE;

#if HAS_RADIO_SETTING
typedef enum {
ETH_PURPOSE_LAN,
ETH_PURPOSE_WAN,
} _ETH_PURPOSE_TYPE;
#endif


typedef enum {
LAN_CONNECTION_STATIC=0,
LAN_CONNECTION_DHCP,
} LAN_CONNECTION_TYPE;

//enum {WPS_OFF=0,WPS_ON=1};

/* bad site filter */
enum {
	BSFLT_STATUS_OK = 0,
	BSFLT_STATUS_STOP, 
	BSFLT_STATUS_END,
	BSFLT_STATUS_NG
};

#if SUPPORT_SX_USB_MODE
enum {
	SX_USB_DISABLE_MODE = 0,
	SX_USB_NAS_MODE,
	SX_USB_NET_USB_MODE
};
#endif
#if HAS_KCODES_FUNCTION
enum {
	KC_USB_DISABLE_MODE = 0,
	KC_USB_SMB_MODE,	/*samba server*/
	KC_USB_NET_USB_MODE /*support printer server and storage*/
};
#endif

#if HAS_ADVANCED_ECO_SETTINGS
//20110419 Jason: [echo status bitmap table]
//---------------------------------------------------------------------------------------------------------------
// eco_status = 0b  | H       | G 		      | F 	      | E 	   	    | D 	 | C   	 | B 		 | A      |
//  		 status	| WAN     | 5G   WLAN LOW | 5G   WLAN | WLAN LOW    | WLAN   | LAN 	 | LAN Giga  | LED	  |
//  			1/0	| off/on  | [3x3]/[1x1]   | on/off    | [2x2]/[1x1] | on/off | on/off| on/off 	 | on/off |
//---------------------------------------------------------------------------------------------------------------

/* ECO default status 
 * bitmap: 0bGFEDCBA
 * A: LED - on/off
 * B: LAN Giga - on/off
 * C: LAN - on/off
 * D: WLAN - on/off
 * E: WLAN LOW - [1x1]/[2x2]
 * F: 5G WLAN - on/off
 * G: 5G WLAN LOW - [1x1]/[2x2]
 * H: WAN - off/on
 */
#define ECO_SETTINGS_LED_MASK 			(1 << 0)
#define ECO_SETTINGS_LAN_RATE_MASK 		(1 << 1)
#define ECO_SETTINGS_LAN_STATUS_MASK 	(1 << 2)
#define ECO_SETTINGS_WLAN_MASK 			(1 << 3)
#define ECO_SETTINGS_WLAN_RATE_MASK		(1 << 4)
#define ECO_SETTINGS_5G_WLAN_MASK       (1 << 5)
#define ECO_SETTINGS_5G_WLAN_RATE_MASK  (1 << 6)
#define ECO_SETTINGS_WAN_STATUS_MASK    (1 << 7)
#endif
/*-------------------------------------------------------------------------*/
/*                           struct                                        */
/*-------------------------------------------------------------------------*/

/* ------------------------------------------------------------------------------------------------------*/
/*     DATA TYPE                         TYPE ID                                                         */
/*     T_INT32                     TYPE_IP, TYPE_NETMASK, TYPE_GATEWAY, TYPE_INT, TYPE_COUNTRYCODE       */
/*     T_UCHAR[6]                  TYPE_MACADDR                                                          */
/*     T_UCHAR[MAX_AP_VALUE_LEN]   TYPE_WEPKEY, TYPE_STR                                                 */
/* ------------------------------------------------------------------------------------------------------*/

typedef enum
{
	TYPE_BOOL=0,	  /* BOOL, 0-1 */
	TYPE_INT,		  /* INT */
	TYPE_UINT,		  /* unsigned INT */
	TYPE_STR,		  /* STR */
    TYPE_STR_32,      /*STR length is 32*/
    TYPE_DOMAINSTR,   /*Domain Str*/
	TYPE_IP,		  /* IP */
#if SUPPORT_IPV6	
	TYPE_IPV6,
#endif	
	TYPE_BLANK_IP,	  /* Blank Ip */
	TYPE_MASK,		  /* MASK*/
    TYPE_BLANK_MASK,  /*BLANK MASK*/
	TYPE_PORT,		  /* Port Number */
	TYPE_SIP_PORT,	  /*Sip Port*/
	TYPE_MACADDR,	  /* MACADDR */
	TYPE_SSID,		  /* SSID, 0-32 length */
#if HAS_SUPPORT_ATHEROS_WLAN
	TYPE_ATH_SSID,		  /* SSID, 0-32 length */
	TYPE_ATH_WDS_TYPE,   /*0: ROOTAP, 1:WDS CLIENT*/
#endif
    TYPE_VLANTAG,      /*vlanid 1~4096*/
	TYPE_WEPKEY,	  /* WEPKEY, Hex code */
	TYPE_KEYID,		  /* Default Key Id, 1-4 */
    TYPE_BEACON,      /* Beacon Interval, 20-1024 */
	TYPE_ATHEROS_BEACON, /*Beacon Interval, 20-1024*/
	TYPE_DTIM,		  /* DTIM Period, 1-255 */
	TYPE_FRAGMENT,	  /* Wireless Fragment threshold, 256-2346 */
	TYPE_RTS_THRESHOLD,	/* 0-2346*/
	TYPE_24G_CHANNEL, /* 11b Channel */
	TYPE_11M_DATARATE,	   /* 11Mbits Data Rate, */
	TYPE_5G_CHANNEL,	   /* 5G Channel */
	TYPE_11A_DATARATE,	   /* 0,6,9,12,18,24,36,48,54 */
	TYPE_11G_DATARATE,	   /*0,1,2,5,11,6,9,12,18,24,36,48,54*/
	TYPE_INTERSIL_AUTH,	   /* 11b auth mode, 0:open 1:share 3:dot1x ?? */
	TYPE_INTERSIL_WEP_TYPE,/* 11b wep type, 0, 64, 128bits*/
	TYPE_INTERSIL_POWER_LV,/* 11b power level, 0:Normal 1:20dBm 2:17dBm 3:13dBm*/
	TYPE_ATHEROS_11AMODE,  /* 54, 108M */
	TYPE_PREAMBLE_TYPE,		/*1:short 2:long*/
	TYPE_RT2860_AUTH,	   /**/
	TYPE_ATHEROS_WEP_TYPE, /* 0 64 128 152bits */
	TYPE_ATHEROS_TXPOWER,  /*unit:percentage*/
	TYPE_COUNTRYCODE, /* COUNTRYCODE */
	TYPE_APMODE,			/*AP or simple WDS*/
    TYPE_SYSOPMODE,         /*AP, AP Bridge-Point to Point, ... , AP Bridge_WDS*/
#if HAS_RADIO_SETTING
	TYPE_RADIOOPMODE,		/*AP, CB, CR, WPS Bridge, Universal Repeater, disable*/
	TYPE_ETH_PURPOSE,		/*what purpose the Eth port is*/
#endif
    TYPE_PWRSAVEMODE,       /*0: disable, 1: WLAN only, 2:Ethernet Only, 3: WLAN+Ethernet */
#if FOR_COREGA || FOR_ZYXEL
	TYPE_LANGUAGE,			/*Language for WEB*/
#endif
    TYPE_WDS_SEC_TYPE,  /*wds sec mode*/
	TYPE_PAE_AUTHTYPE,	   /* 0:PEAP, 1:TLS, 2:TTLS, 3:EAP-FAST, 4:MD5*/
	TYPE_PAE_REKEY_SEC,	   /* 100-3600 */
	TYPE_DHCP_LEASE_TIME,  /*0-8  */
	TYPE_FILTER_TYPE,  /*0:disable, 1:Aceept, 2: Reject */
	TYPE_FILTER_MODE, /*0:whitelist 1:blacklist*/
#if HAS_HTTP_PROXY
	TYPE_URLFILTER_MODE,/*0:whitelist 1:blacklist*/
#endif
	TYPE_SNMP_ACCESS,	   /* SNMP Access, 0:read, 1:write */
	TYPE_SNMP_VER,		   /* SNMP Version 0: all, 1:v1, 2:v2 3:usm*/
	TYPE_WAN_CONN,		   /*WAN connection type, 0: Static, 1:PPPoE, 2: DHCPc*/
	TYPE_WANINTERFACE,
	TYPE_DDNS,				/*DDNS operator, e.g. dyndns.org, toz.com */
	TYPE_IP_FILTER,		   /* ip pairs for IP filtering rule*/
	TYPE_MAC_FILTER,		/* MAC address for IP filtering rule*/
	TYPE_NAT_VSERVER,		/*NAT Virtual server*/
	TYPE_URL_FILTER,		/* URL filter */
#if HAS_MAC_PASSTHROUGH
	TYPE_MAC_BRIDGING,		/* MAC bridging */
#endif
#if HAS_PRIORITY_WEB_ACCOUNT
	TYPE_WEB_ACCOUNT,       /* WEB Account */
#endif
	TYPE_L7_FILTER,			/*L7 filter*/
#if HAS_WLAN_WMM_QOS
	TYPE_WMMQOS_RULE,		/* WLAN QoS (using WMM) */
#endif
	TYPE_PORT_QOS,
	TYPE_PORT_QOS_B,
#if HAS_QOS_HWPORT
	TYPE_QOS_HWPORT,       /* HW Port Based Qos*/
#endif
	TYPE_RT2860_ENC_TYPE,  /*0: None, 1: WEP 2: WPA-PSK TKIP 3: WPA-EAP... */
	TYPE_WPA_PASSPHRASE,	   /* WPA Pre-Shared Key, between 8 and 63 char of ASCII text,or a 64 character Hex string, start with "0x" (total size is 2+64=66)*/
	TYPE_RT2860_MODE,	/*bg=0,b,a,abg,g,abgn,n,gn,an,bgn,agn*/
	TYPE_ATH11ABG_MODE,
	TYPE_DOMAIN,
	TYPE_MTU,
	TYPE_IDLETIME,
	TYPE_AST_MAXCALL,	   /* Asterisk Max calls 4-20 */
	/** VOIP TYPE
    TYPE_USER,
    TYPE_USERCFNUM,
    TYPE_GROUP,
    TYPE_GROUPBLACKLIST,
    TYPE_OUTBOUNDSIPCONF,
    TYPE_DIALPLANCONF,
    **/
#if HAS_SYSTEM_SCHEDULE_FUNCTION
	TYPE_SCH,
#if HAS_SCHEDULE_EXTEND
	TYPE_SCH_B,
#endif
#endif
	TYPE_BANDWIDTH,
	TYPE_DHCP_MACTOIP,
	TYPE_STATICROUTING,
	TYPE_TIMEZONE,
    TYPE_DAYLIGHTMONTH,
    TYPE_DAYLIGHTDAY,
#if HAS_MANUAL_TIME_SETTING || HAS_WAN_CONNECT_TIME
	TYPE_TIME_INFO,
#endif
	TYPE_SYSINFO,
	TYPE_POLLING,/*SNTP 1 - 4*/
	TYPE_KEY_LIFETIME,/*Range from 0 to 86400 */
#if HAS_TOS_DIFFSERV
	TYPE_TOS_DIFFSERV,
#endif
#if HAS_SIP_CDR
	TYPE_CDR_RESERVE_DAYS,
#endif
	TYPE_ISP_CONN,
	TYPE_WLAN_CHANNEL,
#if HAS_SUPPORT_CHANNEL_11ABG
	TYPE_WLAN11ABG_CHANNEL,
#endif
	//TYPE_SCH_FOR_PBX,
	//TYPE_LOGEVENT,
    TYPE_REGDOMAIN,
#if HAS_SMTP
	TYPE_SMTP_AUTE,
#endif
	TYPE_RIP_MODE,
	TYPE_ALG_SUPPORT,
	TYPE_DOS_FEATURE,
	TYPE_DOS_PORT_SCAN,
	TYPE_DMZ,
	TYPE_SPEC_APP,
    TYPE_AUTOCH_CHKTIME,
#if HAS_AP_PROFILE
//    TYPE_AP_PROFILE,
#endif
	TYPE_WMM,
#ifdef HAS_PPPOE_JAPAN	
	TYPE_DUALWANROUTING,
#endif
#if HAS_IMQ_SUPPORT
    TYPE_QOS_BASED,
#endif
#if HAS_WAN_3G
    TYPE_3G_ISP,
#if HAS_WAN_3G_AUTOMOUNT
    TYPE_3G_AUTO_MOUNT,
#endif
#if HAS_WAN_3G_BAND_SELECTION
    TYPE_3G_BAND, /* 2G 900/1800, 3G 2100, 3G 2100 2G 900/1800 */
#endif
#endif
#if HAS_VPN
    TYPE_VPN,
#if HAS_VPN_IPSEC
    TYPE_IPSEC,
    TYPE_IPSEC_CONN_BAS,
    TYPE_IPSEC_CONN_ADV,
#endif
#if HAS_VPN_L2TP
    TYPE_L2TP,
#endif
#if HAS_VPN_PPTP /* [20101222 Andy Yu] */
	TYPE_PPTP,
#endif
#if HAS_VPN_L2TP || HAS_VPN_PPTP
	TYPE_VPN_USER,
#endif
#endif /* HAS_VPN */
#if GEN_ADMIN_PASSWORD_BY_MACADDR
    TYPE_ADMIN_PWD,
#endif
#if HAS_BAD_SITE_FILTER
    TYPE_BSFLT_USR,
	TYPE_BSFLT_GRP,
#endif
#if HAS_WAN_LINKCHECK
    TYPE_WAN_CHECK,
#endif
#if HAS_SC_AUTO_FW_CHECK
    TYPE_AUTO_FW_ACTION,
#endif
#if HAS_DOMAIN_ROUTING	
	TYPE_DOMAINROUTING,
#endif
#if HAS_HTTP_SYSTEM_NAME
	TYPE_HTTP_SYS_NAME,
#endif
#if HAS_NAT_SESSIONS_CTRL
    TYPE_NAT_SESSION,		/* NAT Sessions */
#endif
#if HAS_WAN_TO_WAN_ACL
    TYPE_WAN_TO_WAN_ACL,		/* WAN to WAN ACL */
#endif
#if HAS_TR_AGENT
	TYPE_TR069_OUI,
#endif
#if SUPPORT_IPV6
	TYPE_IPV6_CONN,
#endif
#if HAS_ADV_NAT
	TYPE_ADV_PORT_FORWARDING,
	TYPE_ADV_PORT_FORWARDING_EXT,
#endif
#if HAS_ACCESS_CONTROL
	TYPE_ACCESS_CONTROL,		/* access control */
	TYPE_ACCESS_CONTROL_IP,		/* access control IP */
	TYPE_ACCESS_CONTROL_MAC,		/* access control MAC */
#endif
#if HAS_INBOUND_FILTER
	TYPE_INBOUND_FILTER_SETTING,
	TYPE_INBOUND_FILTER_IP_ADDRESS,
#endif
#if HAS_NPH_MODULE
	TYPE_NPH,
#endif
#if HAS_ACCESS_CONTROL_BELKIN
	TYPE_ACCESS_CONTROL_BELKIN,		/* access control for BELKIN*/
	TYPE_ACCESS_CONTROL_SERVICE,	/* access control Service */
	TYPE_ACCESS_CONTROL_URL,		/* access control URL Filter */
#endif
#if HAS_PARENTAL_CONTROL
	TYPE_PARENTAL_CONTROL,
	TYPE_PARENTAL_CONTROL_IP,
	TYPE_PARENTAL_CONTROL_MAC,
	TYPE_PARENTAL_CONTROL_SERVICE,
	TYPE_PARENTAL_CONTROL_URL,
#endif
#if HAS_SUPPORT_UBICOM_STREAMENGINE
	TYPE_STREAMENGINE_QOS,
#endif
#if SUPPORT_WPS_GENERATE_NEW_PIN
	TYPE_WPS_PIN,
#endif
#if SUPPORT_DEF_CAFE_PSK
	TYPE_CAFE_PSK,
#endif
#if HAS_RTL_VLAN_SUPPORT
	TYPE_RTL_VLAN,
#endif
	TYPE_MAX_TYPE		  /* !!! DO NOT ADD ANY ITEM BELOW THIS ID !!! */
} AP_CFG_TYPE;
#define TYPE_NONE TYPE_MAX_TYPE

//TYPE_WLAN_MODE,	  /* Wlan IF running mode, AP, STA, WDS (need two cards)*/
#endif


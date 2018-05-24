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
;    Project : SI-688
;    Creator : 
;    File    : wlanParameter.h
;    Abstract: include file of the application profile.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2006-0907       Newly Create
;*****************************************************************************/

#ifndef _WLAN_PARAMETER_H_
#define _WLAN_PARAMETER_H_

#include <sap_ostypes.h>

#define siteSurveyFilePath  "/var/tmp/siteSurvey"
#define MAX_APINFO			20

#define PRIORITY_MAX 21
#if HAS_BACKUP_RADIUS_SERVER
#define RADIUS_SERVER_NUMBER 2
#else
#define RADIUS_SERVER_NUMBER 1
#endif
#if 0/*ap_scan*/
# AP scanning/selection
# By default, wpa_supplicant requests driver to perform AP scanning and then
# uses the scan results to select a suitable AP. Another alternative is to
# allow the driver to take care of AP scanning and selection and use
# wpa_supplicant just to process EAPOL frames based on IEEE 802.11 association
# information from the driver.
# 1: wpa_supplicant initiates scanning and AP selection
# 0: driver takes care of scanning, AP selection, and IEEE 802.11 association
#    parameters (e.g., WPA IE generation); this mode can also be used with
#    non-WPA drivers when using IEEE 802.1X mode; do not try to associate with
#    APs (i.e., external program needs to control association). This mode must
#    also be used when using wired Ethernet drivers.
# 2: like 0, but associate with APs using security policy and SSID (but not
#    BSSID); this can be used, e.g., with ndiswrapper and NDIS drivers to
#    enable operation with hidden SSIDs and optimized roaming; in this mode,
#    the network blocks in the configuration file are tried one by one until
#    the driver reports successful association; each network block should have
#    explicit security policy (i.e., only one option in the lists) for
#    key_mgmt, pairwise, group, proto variables
ap_scan=1
#endif
#define WPA_SUPPLICANT_GLOBAL "/var/run/wpa_supplicant-global"
#define WPA_SUPPLICANT "/var/run/wpa_supplicant"
//jaykung 20061130 for wpa_supplicant config file
#define WPA_SUPPLICANT_CONFIG_FILE  "/var/tmp/wpa_supp_config"
#define WPASUPP_CONFIG_HEAD "\
ctrl_interface=%s\n\
update_config=%d\n\
ap_scan=%d\n\
"

#define HOSTAPD_INTERFACE   "/var/run/hostapd/"

#if FOR_ATHEROS_PLATFORM
#define MAX_ALLOWASSOCIATED_STA  128
#else
#define MAX_ALLOWASSOCIATED_STA  32
#endif

#if 0
#none
network={
        ssid="RD2D-Link"
        scan_ssid=1
        key_mgmt=NONE
        priority=20
}
#wep
network={
        ssid="RD2D-Link"
        scan_ssid=1
        key_mgmt=NONE
        wep_key0=1234567890
        wep_tx_keyidx=0
        auth_alg=OPEN
        priority=20
}

# Only WPA-PSK is used. Any valid cipher combination is accepted.
network={
    ssid="example"
    proto=WPA
    key_mgmt=WPA-PSK
    pairwise=CCMP TKIP
    group=CCMP TKIP WEP104 WEP40
    psk=06b4be19da289f475aa46a33cb793029d4ab3db7a23ee92382eb0106c72ac7bb
    priority=2
}
#endif

/* Joey 20090110 Fix the MAC address to connect AP*/
#if HAS_WPA_SUPPLICANT_FIXED_MAC
#define WPASUPP_CONFIG_NONE_ENC2 "\
network={\n\
        ssid=\"%s\"\n\
        bssid=%s\n\
        scan_ssid=%d\n\
        key_mgmt=NONE\n\
        priority=%d\n\
}\n\
"

#define WPASUPP_CONFIG_WEP2 "\
network={\n\
        ssid=\"%s\"\n\
        bssid=%s\n\
        scan_ssid=%d\n\
        key_mgmt=NONE\n\
        wep_key%d=%s\n\
        wep_tx_keyidx=%d\n\
        auth_alg=%s\n\
        priority=%d\n\
}\n\
"
#define WPASUPP_CONFIG_WEP_ASCII2 "\
network={\n\
        ssid=\"%s\"\n\
        bssid=%s\n\
        scan_ssid=%d\n\
        key_mgmt=NONE\n\
        wep_key%d=\"%s\"\n\
        wep_tx_keyidx=%d\n\
        auth_alg=%s\n\
        priority=%d\n\
}\n\
"


#define WPASUPP_CONFIG_WPA_PSK2 "\
network={\n\
    ssid=\"%s\"\n\
    bssid=%s\n\
    scan_ssid=%d\n\
    proto=%s\n\
    key_mgmt=WPA-PSK\n\
    pairwise=%s\n\
    group=CCMP TKIP WEP104 WEP40\n\
    psk=%s\n\
    auth_alg=OPEN\n\
    priority=%d\n\
}\n\
"

#define WPASUPP_CONFIG_IEEE8021X2 "\
network={\n\
    ssid=\"%s\"\n\
    bssid=%s\n\
    scan_ssid=%d\n\
    key_mgmt=IEEE8021X\n\
	eap=%s\n\
	phase2=\"auth=MSCHAPV2\"\n\
	identity=\"%s\"\n\
	password=\"%s\"\n\
	auth_alg=OPEN\n\
    priority=%d\n\
}\n\
"
#define WPASUPP_CONFIG_IEEE8021X_NONE2 "\
network={\n\
    ssid=\"%s\"\n\
    bssid=%s\n\
    scan_ssid=%d\n\
    key_mgmt=IEEE8021X\n\
	eap=%s\n\
	phase2=\"auth=MSCHAPV2\"\n\
	identity=\"%s\"\n\
	password=\"%s\"\n\
	auth_alg=OPEN\n\
	eapol_flags=0\n\
    priority=%d\n\
}\n\
"

#define WPASUPP_CONFIG_WPA_EAP2 "\
network={\n\
    ssid=\"%s\"\n\
    bssid=%s\n\
    scan_ssid=%d\n\
    key_mgmt=WPA-EAP\n\
	eap=%s\n\
	pairwise=%s\n\
	group=CCMP TKIP\n\
	identity=\"%s\"\n\
	password=\"%s\"\n\
    priority=%d\n\
}\n\
"
//Joey
#endif
//jaykung 20061213 create different type of encyption
#define WPASUPP_CONFIG_NONE_ENC "\
network={\n\
        ssid=\"%s\"\n\
        scan_ssid=%d\n\
        key_mgmt=NONE\n\
        priority=%d\n\
}\n\
"

#define WPASUPP_CONFIG_WEP "\
network={\n\
        ssid=\"%s\"\n\
        scan_ssid=%d\n\
        key_mgmt=NONE\n\
        wep_key%d=%s\n\
        wep_tx_keyidx=%d\n\
        auth_alg=%s\n\
        priority=%d\n\
}\n\
"
#define WPASUPP_CONFIG_WEP_ASCII "\
network={\n\
        ssid=\"%s\"\n\
        scan_ssid=%d\n\
        key_mgmt=NONE\n\
        wep_key%d=\"%s\"\n\
        wep_tx_keyidx=%d\n\
        auth_alg=%s\n\
        priority=%d\n\
}\n\
"


#define WPASUPP_CONFIG_WPA_PSK "\
network={\n\
    ssid=\"%s\"\n\
    scan_ssid=%d\n\
    proto=%s\n\
    key_mgmt=WPA-PSK\n\
    pairwise=%s\n\
    group=CCMP TKIP WEP104 WEP40\n\
    psk=%s\n\
    auth_alg=OPEN\n\
    priority=%d\n\
}\n\
"

#define WPASUPP_CONFIG_IEEE8021X "\
network={\n\
    ssid=\"%s\"\n\
    scan_ssid=%d\n\
    key_mgmt=IEEE8021X\n\
	eap=%s\n\
	phase2=\"auth=MSCHAPV2\"\n\
	identity=\"%s\"\n\
	password=\"%s\"\n\
	auth_alg=OPEN\n\
    priority=%d\n\
}\n\
"
#define WPASUPP_CONFIG_IEEE8021X_NONE "\
network={\n\
    ssid=\"%s\"\n\
    scan_ssid=%d\n\
    key_mgmt=IEEE8021X\n\
	eap=%s\n\
	phase2=\"auth=MSCHAPV2\"\n\
	identity=\"%s\"\n\
	password=\"%s\"\n\
	auth_alg=OPEN\n\
	eapol_flags=0\n\
    priority=%d\n\
}\n\
"

#define WPASUPP_CONFIG_WPA_EAP "\
network={\n\
    ssid=\"%s\"\n\
    scan_ssid=%d\n\
    key_mgmt=WPA-EAP\n\
	eap=%s\n\
	pairwise=%s\n\
	group=CCMP TKIP\n\
	identity=\"%s\"\n\
	password=\"%s\"\n\
    priority=%d\n\
}\n\
"
//~jay
// 2008-0723 joey add frequency <-> channel
#define     MAP_CHANNEL_ID_TO_KHZ(ch, khz)  {               \
                switch (ch)                                 \
                {                                           \
                    case 1:     khz = 2412000;   break;     \
                    case 2:     khz = 2417000;   break;     \
                    case 3:     khz = 2422000;   break;     \
                    case 4:     khz = 2427000;   break;     \
                    case 5:     khz = 2432000;   break;     \
                    case 6:     khz = 2437000;   break;     \
                    case 7:     khz = 2442000;   break;     \
                    case 8:     khz = 2447000;   break;     \
                    case 9:     khz = 2452000;   break;     \
                    case 10:    khz = 2457000;   break;     \
                    case 11:    khz = 2462000;   break;     \
                    case 12:    khz = 2467000;   break;     \
                    case 13:    khz = 2472000;   break;     \
                    case 14:    khz = 2484000;   break;     \
                    case 36:  /* UNII */  khz = 5180000;   break;     \
                    case 40:  /* UNII */  khz = 5200000;   break;     \
                    case 44:  /* UNII */  khz = 5220000;   break;     \
                    case 48:  /* UNII */  khz = 5240000;   break;     \
                    case 52:  /* UNII */  khz = 5260000;   break;     \
                    case 56:  /* UNII */  khz = 5280000;   break;     \
                    case 60:  /* UNII */  khz = 5300000;   break;     \
                    case 64:  /* UNII */  khz = 5320000;   break;     \
                    case 149: /* UNII */  khz = 5745000;   break;     \
                    case 153: /* UNII */  khz = 5765000;   break;     \
                    case 157: /* UNII */  khz = 5785000;   break;     \
                    case 161: /* UNII */  khz = 5805000;   break;     \
                    case 165: /* UNII */  khz = 5825000;   break;     \
                    case 100: /* HiperLAN2 */  khz = 5500000;   break;     \
                    case 104: /* HiperLAN2 */  khz = 5520000;   break;     \
                    case 108: /* HiperLAN2 */  khz = 5540000;   break;     \
                    case 112: /* HiperLAN2 */  khz = 5560000;   break;     \
                    case 116: /* HiperLAN2 */  khz = 5580000;   break;     \
                    case 120: /* HiperLAN2 */  khz = 5600000;   break;     \
                    case 124: /* HiperLAN2 */  khz = 5620000;   break;     \
                    case 128: /* HiperLAN2 */  khz = 5640000;   break;     \
                    case 132: /* HiperLAN2 */  khz = 5660000;   break;     \
                    case 136: /* HiperLAN2 */  khz = 5680000;   break;     \
                    case 140: /* HiperLAN2 */  khz = 5700000;   break;     \
                    case 34:  /* Japan MMAC */   khz = 5170000;   break;   \
                    case 38:  /* Japan MMAC */   khz = 5190000;   break;   \
                    case 42:  /* Japan MMAC */   khz = 5210000;   break;   \
                    case 46:  /* Japan MMAC */   khz = 5230000;   break;   \
                    case 184: /* Japan */   khz = 4920000;   break;   \
                    case 188: /* Japan */   khz = 4940000;   break;   \
                    case 192: /* Japan */   khz = 4960000;   break;   \
                    case 196: /* Japan */   khz = 4980000;   break;   \
                    case 208: /* Japan, means J08 */   khz = 5040000;   break;   \
                    case 212: /* Japan, means J12 */   khz = 5060000;   break;   \
                    case 216: /* Japan, means J16 */   khz = 5080000;   break;   \
                    default:    khz = 2412000;   break;     \
                }                                           \
            }

#define     MAP_KHZ_TO_CHANNEL_ID(khz, ch)  {               \
                switch (khz)                                \
                {                                           \
                    case 2412000:    ch = 1;     break;     \
                    case 2417000:    ch = 2;     break;     \
                    case 2422000:    ch = 3;     break;     \
                    case 2427000:    ch = 4;     break;     \
                    case 2432000:    ch = 5;     break;     \
                    case 2437000:    ch = 6;     break;     \
                    case 2442000:    ch = 7;     break;     \
                    case 2447000:    ch = 8;     break;     \
                    case 2452000:    ch = 9;     break;     \
                    case 2457000:    ch = 10;    break;     \
                    case 2462000:    ch = 11;    break;     \
                    case 2467000:    ch = 12;    break;     \
                    case 2472000:    ch = 13;    break;     \
                    case 2484000:    ch = 14;    break;     \
                    case 5180000:    ch = 36;  /* UNII */  break;     \
                    case 5200000:    ch = 40;  /* UNII */  break;     \
                    case 5220000:    ch = 44;  /* UNII */  break;     \
                    case 5240000:    ch = 48;  /* UNII */  break;     \
                    case 5260000:    ch = 52;  /* UNII */  break;     \
                    case 5280000:    ch = 56;  /* UNII */  break;     \
                    case 5300000:    ch = 60;  /* UNII */  break;     \
                    case 5320000:    ch = 64;  /* UNII */  break;     \
                    case 5745000:    ch = 149; /* UNII */  break;     \
                    case 5765000:    ch = 153; /* UNII */  break;     \
                    case 5785000:    ch = 157; /* UNII */  break;     \
                    case 5805000:    ch = 161; /* UNII */  break;     \
                    case 5825000:    ch = 165; /* UNII */  break;     \
                    case 5500000:    ch = 100; /* HiperLAN2 */  break;     \
                    case 5520000:    ch = 104; /* HiperLAN2 */  break;     \
                    case 5540000:    ch = 108; /* HiperLAN2 */  break;     \
                    case 5560000:    ch = 112; /* HiperLAN2 */  break;     \
                    case 5580000:    ch = 116; /* HiperLAN2 */  break;     \
                    case 5600000:    ch = 120; /* HiperLAN2 */  break;     \
                    case 5620000:    ch = 124; /* HiperLAN2 */  break;     \
                    case 5640000:    ch = 128; /* HiperLAN2 */  break;     \
                    case 5660000:    ch = 132; /* HiperLAN2 */  break;     \
                    case 5680000:    ch = 136; /* HiperLAN2 */  break;     \
                    case 5700000:    ch = 140; /* HiperLAN2 */  break;     \
                    case 5170000:    ch = 34;  /* Japan MMAC */   break;   \
                    case 5190000:    ch = 38;  /* Japan MMAC */   break;   \
                    case 5210000:    ch = 42;  /* Japan MMAC */   break;   \
                    case 5230000:    ch = 46;  /* Japan MMAC */   break;   \
                    case 4920000:    ch = 184; /* Japan */  break;   \
                    case 4940000:    ch = 188; /* Japan */  break;   \
                    case 4960000:    ch = 192; /* Japan */  break;   \
                    case 4980000:    ch = 196; /* Japan */  break;   \
                    case 5040000:    ch = 208; /* Japan, means J08 */  break;   \
                    case 5060000:    ch = 212; /* Japan, means J12 */  break;   \
                    case 5080000:    ch = 216; /* Japan, means J16 */  break;   \
                    default:         ch = 1;     break;     \
                }                                           \
            }
//joey

//jay 20070215 for si 688 wlan security mode
typedef enum { WPA_PSK_TKIP=2, WPA_PSK_AES, WPA2_PSK_TKIP,WPA2_PSK_AES} WlanSecurityMode;
//~jay

typedef enum { ENC_NONE, ENC_WEP64, ENC_WEP128, ENC_TKIP, ENC_AES, ENC_AESTKIP } WlanEncryption;
typedef enum { AUTH_OPEN, AUTH_SHARE, AUTH_WPA_PSK, AUTH_WPA_EAP } WlanAuth;
typedef enum { WLAN_MODE_11B, WLAN_MODE_11G } WlanMode;
typedef enum { OP_ADHOC, OP_AP } OperationMode;

//#ifdef FOR_RT2880
#define WPA_SUPPLICANT_INTERFACE "/var/run/wpa_supplicant/ra0"
/*This is for RT2860*/
typedef enum{
WLAN_AUTH_OPEN=0,
WLAN_AUTH_WEPAUTO,
WLAN_AUTH_SHARED,
WLAN_AUTH_WPAPSK,
WLAN_AUTH_WPA,
WLAN_AUTH_WPA2PSK,
WLAN_AUTH_WPA2,
WLAN_AUTH_WPA1WPA2,
WLAN_AUTH_WPA1PSKWPA2PSK,
#if HAS_WLAN_STA_FUNCTION
WLAN_AUTH_8021X_NONE,
WLAN_AUTH_8021X_WEP,
#endif
MAX_WLAN_AUTH
} Rt2860WLAuth;

typedef enum{
WLAN_ENC_NONE=0,
WLAN_ENC_WEP,
WLAN_ENC_TKIP,
WLAN_ENC_AES,
WLAN_ENC_TKIPAES,
MAX_WLAN_ENC
} Rt2860WLEnc;
//#endif //FOR_RT2880

/** @brief Get the WLAN RSSI raw value */
typedef enum {
	RSSI_LEVEL0=0,
	RSSI_LEVEL1,
	RSSI_LEVEL2,
	RSSI_LEVEL3,
	RSSI_LEVEL4,
	RSSI_LEVEL5,
	MAX_RSSI_LEVEL = RSSI_LEVEL5/*always the last*/
} rssiLevel;

/*Joey 2010-0723 For Multi-Platform and Dual-Radio*/
typedef enum {
    RADIO_DISABLE_WLAN=0,
    RADIO_RALINK_WLAN,
    RADIO_ATHEROS_WLAN,
    RADIO_REALTEK_WLAN,
    RADIO_PLATFORM_MAX
} RADIO_SUPPORT_WLAN_TYPE;

/*Adonn 08-0812: Modify ApInfo for EOR7550*/
typedef struct _ApInfo
{
    char essid[32+1];
    char macAddress[17+1];
	char encStr[20];
    Rt2860WLEnc encryption;
	char authStr[20];
    Rt2860WLAuth auth;                                                        
    int rssi;
    int channel;
    WlanMode wlanMode;
} ApInfo;

typedef struct _WLANKeyTokInfo
{
//     T_CHAR *KeyType;
    T_CHAR *KeyStr;
}WLANKeyTokInfo;

typedef struct _WLAN8021TokInfo
{
    T_CHAR *Enable;
    T_CHAR *IP;
    T_CHAR *Port;
    T_CHAR *Password;
}WLAN8021TokInfo;

/*Jaykung 20081105 this structure is for multiple ssid*/
typedef struct _WLANTokInfo
{
    T_CHAR *isEnable;
    T_CHAR *SSID;
    T_CHAR *AuthMode;
    T_CHAR *EncrypType;
    T_CHAR *WpaPsk;
    T_CHAR *WpaPskType;
    T_CHAR *DefaultKeyId;
    T_CHAR *keyLength;
    T_CHAR *KeyType;
    WLANKeyTokInfo  Key[4];
    T_CHAR *Isolated;
    T_CHAR *BroadcastSSID;
    T_CHAR *WmmCapable;
    WLAN8021TokInfo ieee8021x[RADIUS_SERVER_NUMBER];
    T_CHAR *ACLEnabled;
    T_CHAR *ACLContent;
#if HAS_VLAN_SUPPORT
    T_CHAR *VLANID;
#endif
#if L2_CONTROL_ACCESS
	T_CHAR *WLAN2LAN;
#endif /*L2_CONTROL_ACCESS*/
#if HAS_WAN_ACL
	T_CHAR *WLAN2WAN;
#endif /*HAS_WAN_ACL*/
//TODO ACL WDS
}WLANTokInfo;

/*jaykung 20081105*/
typedef struct _WLANCommonTokInfo
{
	T_CHAR *wirelessMode;/*wireless mode,a b g n*/
    T_CHAR *apMode;/*WDS AP_CLI*/
	T_CHAR	*apRadio;
#if HAS_WLAN_STA_FUNCTION
	T_CHAR	*staMode;
	T_CHAR	*staRadio;
#endif
	T_CHAR	*Channel;
    T_CHAR *BeaconPeriod;
	T_CHAR *DtimPeriod;
	T_CHAR *TxPower;
	T_CHAR *BGProtection;
	T_CHAR *TxRate;
	T_CHAR *TxPreamble;
	T_CHAR *RTSThreshold;
	T_CHAR *FragThreshold;
	T_CHAR *TxBurst;
	T_CHAR *WscConfStatus;
	T_CHAR *WscConfMode;
	T_CHAR *is40BwEnabled;
	T_CHAR *nTxRate;
#if HAS_AUTO_CHANNEL_SELECTION
	T_CHAR *autoChannel;
	T_CHAR *autoChChkTime;
#endif
	T_CHAR *wdsMacPrefix;
	T_CHAR *wdsPhyMode;
	T_CHAR *wdsSecType;
	T_CHAR *wdsPassphrase;
	T_CHAR *wdsEncType;
	T_CHAR *wdsKeyType;
	T_CHAR *wdsWep;
 	T_CHAR *wdsKeyId;
 	T_CHAR *wdsWepKeyPrefix;
}WLANCommonTokInfo;

/* 2009/11/13 jerry chen: WPA/WPA Rekey Method, this structure is for multiple ssid */
typedef struct _WLANRekeyMethodTokInfo
{
    T_CHAR *WpaPskLiftEnabled;
    T_CHAR *WpaPskLiftTime;
}WLANRekeyMethodTokInfo;


typedef struct _WLANClientListInfo
{
    T_UCHAR    CLInterface;	
    T_CHAR      CLMac[17+1];
    T_UINT64      CLRx_Bytes;
    T_UINT64      CLTx_Bytes;
    T_ULONG      CLIRx_Pkts;
    T_ULONG      CLITx_Pkts;
    T_BOOL       CLIPowerSaved;
    T_INT        CLSignal;
    T_ULONG      CLConnectedtime;
    T_ULONG     CLIdletime;
    T_INT     CLITx_DataRate;
    T_INT     CLIRx_DataRate;
} WLANClientListInfo;
#endif

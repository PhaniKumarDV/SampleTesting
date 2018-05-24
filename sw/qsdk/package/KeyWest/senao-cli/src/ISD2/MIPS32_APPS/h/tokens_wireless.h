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
;    Project : EOR7550
;    Creator : 
;    File    : 
;    Abstract: This file should accord to project! So not synchonize
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2008-0722
;*****************************************************************************/ 
#ifndef _TOKEN_WIRELESS_H_
#define _TOKEN_WIRELESS_H_

/* ------ Commons parts for Wireless settings -------- */
#define _ENABLE_TOK               "enable"
#define _RADIO_TOK                "radio"
#define _SSID_TOK                 "ssid"
#define _AUTO_CH_SEL_TOK          "autochsel"
#define _AUTO_CH_CHK_TIME_TOK     "autochtime"
#define _CHANNEL_TOK              "channel"
#define _CH_SET_TOK               "channel_set"
#define _COUNTRYCODE_TOK          "countrycode"
#define _USE_APCFG_COUNTRYCODE_TOK	"apcfg_ctcode"
#define _WEP_TOK                  "wep"
#define _KEYID_TOK                "wepkeyid"
#define _KEYTYPE_TOK              "wepkeytype"
#define _WEPKEY_TOK               "wepkey"
#define _WEPKEY_0_TOK             "wepkey0"
#define _WEPKEY_1_TOK             "wepkey1"
#define _WEPKEY_2_TOK             "wepkey2"
#define _WEPKEY_3_TOK             "wepkey3"
#define _DATARATE_TOK             "datarate"
#define _TXPOWER_TOK              "txpower"
#if HAS_TX_POWER_DBM_SETTING
#define _TXPOWER_DBM_TOK          "txpower_dbm"
#endif
#define _BEACON_TOK               "beacon"
#define _DATABEACON_TOK           "databeacon"
#define _FRAGMENT_TOK             "fragment"
#define _DISTANCE_TOK             "distance"
#define _ACKTIME_TOK              "acktime"
#define _THRESHOLD_TOK            "threshold"
#define _MODE_TOK                 "mode"
#define _PREAMBLE_TOK             "preamble"
#define _AUTH_TOK                 "auth"
#define _ENC_TYPE_TOK             "enctype"
#define _ENC_SSID_SEL_TOK         "enc_sel_ssid"
#define _WPAPASSPHRASE_TOK        "wpapassphase"
#define _HIDESSID_TOK             "hidessid"
#define _WPAPSK_LIFETIME_TOK      "wpapsk_lt"
#define _WPAPSK_LIFETIME_EN_TOK   "wpapsk_lt_en"
#define _WPAPSK_KEYTYPE_TOK       "wpapsk_keytype"
#define _WMM_ENABLE_TOK           "wmm_enable"
#define _11N_BW40_ENABLE_TOK      "11n_bw40"
#define _11N_BW40PLUS_ENABLE_TOK  "11n_bw40plus"
#define _11N_DATERATE_TOK         "11n_daterate"
#define _DEV_TOK                  "device" 
#define _WPS_PIN_TOK              "wps_pin"
#define _WPS_STATUS_TOK           "wps_status"
#define _WPS_ENABLE_TOK           "wps"
#if HAS_WPS_BUTTON_CONTROL
#define _WPS_BUTTON_ENABLE_TOK           "wps_button"
#endif
#define _SSID_NUM_TOK             "ssid_num"
#define _TXBURST_TOK              "txburst"
#define _TURBO_MODE_ENABLE_TOK    "turbo_enable"
#define _BGPROTECTION_TOK         "BGprotection"
#define _8021X_ENABLE_TOK         "8021x_enable"
#define _8021X_SERVIP_TOK         "8021x_servip"
#define _8021X_SERVPORT_TOK       "8021x_servport"
#define _8021X_SERVPW_TOK         "8021x_servpw"
#define _8021X_METHOD_TOK         "8021x_method"
#define _8021X_IDENTITY_TOK       "8021x_identity"
#define _8021X_PWD_TOK            "8021x_password"
#if HAS_BACKUP_RADIUS_SERVER
/*Backup Radius*/
#define _8021X_BACKUP_ENABLE_TOK  "8021x_bk_en"
#define _8021X_SERVIP_2_TOK       "8021x_ip_2"
#define _8021X_SERVPORT_2_TOK     "8021x_port_2"
#define _8021X_SERVPW_2_TOK       "8021x_pw_2"
#define _8021X_MACAUTH_2_TOK      "8021x_mac_2"
#endif
#define _AP_MODE_TOK              "ap_mode"
#define _WDS_SEC_TYPE_TOK         "wds_sec"
#define _WDS_TYPE_TOK			  "wds_type"
#define _WDS_WPAPASSPHRASE_TOK    "wds_passphrase"
#define _WDS_MAC_TOK              "bridge_mac_"
#define _WDS_MAC_1_TOK            "bridge_mac_1"
#define _WDS_MAC_2_TOK            "bridge_mac_2"
#define _WDS_MAC_3_TOK            "bridge_mac_3"
#define _WDS_MAC_4_TOK            "bridge_mac_4"
#define _WDS_CLIENT_MAC_TOK       "wds_client_mac"
#define _WDS_ENC_TYPE_TOK         "wds_enc"
#define _WDS_AUTH_TOK             "wds_auth"
#define _WDS_WEP_TOK              "wds_wep"
#define _WDS_KEYTYPE_TOK		  "wds_keytype"
#define _WDS_KEYID_TOK            "wds_keyid"
#define _WDS_WEPKEY_TOK           "wds_key_"
#define _WDS_WEPKEY_0_TOK         "wds_key_0"
#define _WDS_WEPKEY_1_TOK         "wds_key_1"
#define _WDS_WEPKEY_2_TOK         "wds_key_2"
#define _WDS_WEPKEY_3_TOK         "wds_key_3"
#define _WDS_PHYMODE_TOK          "wds_phymode"
#define _STA_ISOLATED_ENABLE_TOK  "sta_isolated"
#define _ISOLATED_ENABLE_TOK      "isolated"
#define _AUTO_TXPOWER_TOK         "autotxp"
#define _POWERSAVING_MODE_TOK     "powersaving"
#define _VLAN_ENABLE_TOK          "vlan_enable" 
#define _VLANTAG_TOK              "vlanid"
#define _VLANTAG_ENABLE_TOK       "vlantag_en"
#define _ACCESS_WLAN2LAN_TOK      "wlan2lan"
#define _ACCESS_WLAN2WAN_TOK      "wlan2wan"
#define _MAX_AID_NUM_TOK          "aid_num"
#define _NTP_SERVER_TOK           "ntpserv"

#define _STA_TOK 				  "S" 

#define RADIO_PREFIX_TOK		  "radio_"
#define _OP_MODE_TOK			  "opmode_"
#define _BR_NAME_TOK			  "br_"
#define RADIO_1_OP_MODE_TOK		  RADIO_PREFIX_TOK _OP_MODE_TOK "1"
#define RADIO_2_OP_MODE_TOK		  RADIO_PREFIX_TOK _OP_MODE_TOK "2"

#ifdef HAS_RA2_SETTINGS
/** ------------------   RALINK 5G Token   -----------------------*/
/** 					Common Token -----------------------------*/
#define		RA2_1_TOK               "ra2_"
#define 	RA2_1_                  RA2_1_TOK

// #define 	RA2_TOK                 "ra2_"
// #define 	RA2_                    RA2_TOK
#define 	RA2_AP_MODE_TOK			RA2_1_ _AP_MODE_TOK
#define 	RA2_STA_				RA2_1_TOK"sta"
#define		RA2_MODE_TOK			RA2_1_ _MODE_TOK
#define		RA2_RADIO_TOK			RA2_1_ _RADIO_TOK
#if HAS_WLAN_STA_FUNCTION
#define		RA2_STA_MODE_TOK		RA2_STA_ _MODE_TOK   
#define		RA2_STA_RADIO_TOK		RA2_STA_ _RADIO_TOK    
#endif
#define     RA2_AUTO_CH_SEL_TOK     RA2_1_ _AUTO_CH_SEL_TOK
#define     RA2_AUTO_CH_CHK_TIME_TOK     RA2_1_ _AUTO_CH_CHK_TIME_TOK
#define		RA2_CHANNEL_TOK			RA2_1_ _CHANNEL_TOK
#define		RA2_BEACON_TOK			RA2_1_ _BEACON_TOK
#define		RA2_DATABEACON_TOK		RA2_1_ _DATABEACON_TOK
#define		RA2_TXPOWER_TOK			RA2_1_ _TXPOWER_TOK
#define		RA2_BGPROTECTION_TOK	RA2_1_ _BGPROTECTION_TOK
#define		RA2_DATARATE_TOK		RA2_1_ _DATARATE_TOK
#define		RA2_PREAMBLE_TOK		RA2_1_ _PREAMBLE_TOK
#define		RA2_THRESHOLD_TOK		RA2_1_ _THRESHOLD_TOK
#define		RA2_FRAGMENT_TOK		RA2_1_ _FRAGMENT_TOK
#define		RA2_TXBURST_TOK			RA2_1_ _TXBURST_TOK
#define		RA2_11N_BW40_ENABLE_TOK	RA2_1_ _11N_BW40_ENABLE_TOK
#define		RA2_11N_DATERATE_TOK	RA2_1_ _11N_DATERATE_TOK
#define		RA2_WPS_STATUS_TOK	 	RA2_1_ _WPS_STATUS_TOK
#define 	RA2_WPS_ENABLE_TOK		RA2_1_ _WPS_ENABLE_TOK
#if HAS_WPS_BUTTON_CONTROL
#define 	RA2_WPS_BUTTON_ENABLE_TOK		RA2_1_ _WPS_BUTTON_ENABLE_TOK
#endif
#define     RA2_SSID_NUM_TOK		RA2_1_ _SSID_NUM_TOK
#define 	RA2_COUNTRYCODE_TOK	    RA2_1_ _COUNTRYCODE_TOK
#define     RA2_USE_APCFG_COUNTRYCODE_TOK     RA2_1_ _USE_APCFG_COUNTRYCODE_TOK
/**						SSID(1)									  */

#define RA2_1_ENABLE_TOK                 RA2_1_ _ENABLE_TOK
#define RA2_1_SSID_TOK                   RA2_1_ _SSID_TOK
#define RA2_1_WEP_TOK                    RA2_1_ _WEP_TOK
#define RA2_1_KEYID_TOK                  RA2_1_ _KEYID_TOK
#define RA2_1_KEYTYPE_TOK                RA2_1_ _KEYTYPE_TOK
#define RA2_1_WEPKEY_TOK                 RA2_1_ _WEPKEY_TOK
#define RA2_1_WEPKEY_0_TOK               RA2_1_ _WEPKEY_0_TOK
#define RA2_1_WEPKEY_1_TOK               RA2_1_ _WEPKEY_1_TOK
#define RA2_1_WEPKEY_2_TOK               RA2_1_ _WEPKEY_2_TOK
#define RA2_1_WEPKEY_3_TOK               RA2_1_ _WEPKEY_3_TOK
#define RA2_1_ENC_TYPE_TOK               RA2_1_ _ENC_TYPE_TOK
#define RA2_1_WPAPASSPHRASE_TOK          RA2_1_ _WPAPASSPHRASE_TOK
#define RA2_1_HIDESSID_TOK               RA2_1_ _HIDESSID_TOK
#define RA2_1_WPAPSK_LIFETIME_TOK        RA2_1_ _WPAPSK_LIFETIME_TOK
#define RA2_1_WPAPSK_LIFETIME_EN_TOK     RA2_1_ _WPAPSK_LIFETIME_EN_TOK
#define RA2_1_WPAPSK_KEYTYPE_TOK         RA2_1_ _WPAPSK_KEYTYPE_TOK
#define RA2_1_WMM_ENABLE_TOK             RA2_1_ _WMM_ENABLE_TOK
#define RA2_1_AUTH_TOK                   RA2_1_ _AUTH_TOK
#define RA2_1_8021X_ENABLE_TOK           RA2_1_ _8021X_ENABLE_TOK
#define RA2_1_8021X_SERVIP_TOK           RA2_1_ _8021X_SERVIP_TOK
#define RA2_1_8021X_SERVPORT_TOK         RA2_1_ _8021X_SERVPORT_TOK
#define RA2_1_8021X_SERVPW_TOK           RA2_1_ _8021X_SERVPW_TOK
#define RA2_1_WDS_SEC_TYPE_TOK           RA2_1_ _WDS_SEC_TYPE_TOK
#define RA2_1_WDS_WPAPASSPHRASE_TOK      RA2_1_ _WDS_WPAPASSPHRASE_TOK
#define RA2_1_WDS_MAC_TOK                RA2_1_ _WDS_MAC_TOK
#define RA2_1_WDS_MAC_1_TOK              RA2_1_ _WDS_MAC_1_TOK
#define RA2_1_WDS_MAC_2_TOK              RA2_1_ _WDS_MAC_2_TOK
#define RA2_1_WDS_MAC_3_TOK              RA2_1_ _WDS_MAC_3_TOK
#define RA2_1_WDS_MAC_4_TOK              RA2_1_ _WDS_MAC_4_TOK
#define RA2_1_WDS_ENC_TYPE_TOK           RA2_1_ _WDS_ENC_TYPE_TOK
#define RA2_1_WDS_WEP_TOK                RA2_1_ _WDS_WEP_TOK
#define RA2_1_WDS_KEYTYPE_TOK            RA2_1_ _WDS_KEYTYPE_TOK
#define RA2_1_WDS_KEYID_TOK              RA2_1_ _WDS_KEYID_TOK
#define RA2_1_WDS_WEPKEY_TOK             RA2_1_ _WDS_WEPKEY_TOK
#define RA2_1_WDS_WEPKEY_0_TOK           RA2_1_ _WDS_WEPKEY_0_TOK
#define RA2_1_WDS_WEPKEY_1_TOK           RA2_1_ _WDS_WEPKEY_1_TOK
#define RA2_1_WDS_WEPKEY_2_TOK           RA2_1_ _WDS_WEPKEY_2_TOK
#define RA2_1_WDS_WEPKEY_3_TOK           RA2_1_ _WDS_WEPKEY_3_TOK
#define RA2_1_ISOLATED_ENABLE_TOK        RA2_1_ _ISOLATED_ENABLE_TOK
#if HAS_ADVANCED_ISOLATED
#define RA2_1_STA_ISOLATED_ENABLE_TOK    RA2_1_ _STA_ISOLATED_ENABLE_TOK
#endif
#if L2_CONTROL_ACCESS
#if HAS_WAN_ACL
#define RA2_1_ACCESS_WLAN2WAN_TOK		 RA2_1_ _ACCESS_WLAN2WAN_TOK
#endif /*HAS_WAN_ACL*/
#endif /*L2_CONTROL_ACCESS*/

#endif /*HAS_RA2_SETTINGS*/

#if defined (HAS_RA2_SETTINGS) || defined (SUPPORT_MULTI_WLAN_PLATFORM_RADIO2)
/**                      Mac Filter                              */
/* ------------------   ap ra2_acl tokens   -----------------------*/
#define RA2_MACFILTER_PRE_TOK                "ra2_acl"
#define RA2_MACFILTER_TYPE_TOK           "ra2_acl_type"
#define RA2_MACFILTER_ENABLE_TOK             "ra2_acl_en"
#define RA2_MACFILTER_TOK                    "ra2_acl_"  
#define RA2_MACFILTER_01_TOK                 "ra2_acl_1"
#define RA2_MACFILTER_02_TOK                 "ra2_acl_2"
#define RA2_MACFILTER_03_TOK                 "ra2_acl_3"
#define RA2_MACFILTER_04_TOK                 "ra2_acl_4"
#define RA2_MACFILTER_05_TOK                 "ra2_acl_5"
#define RA2_MACFILTER_06_TOK                 "ra2_acl_6"
#define RA2_MACFILTER_07_TOK                 "ra2_acl_7"
#define RA2_MACFILTER_08_TOK                 "ra2_acl_8"
#define RA2_MACFILTER_09_TOK                 "ra2_acl_9"
#define RA2_MACFILTER_10_TOK                 "ra2_acl_10"
#if NUM_MAC_FILTERS > 10
#define RA2_MACFILTER_11_TOK                 "ra2_acl_11"
#define RA2_MACFILTER_12_TOK                 "ra2_acl_12"
#define RA2_MACFILTER_13_TOK                 "ra2_acl_13"
#define RA2_MACFILTER_14_TOK                 "ra2_acl_14"
#define RA2_MACFILTER_15_TOK                 "ra2_acl_15"
#define RA2_MACFILTER_16_TOK                 "ra2_acl_16"
#define RA2_MACFILTER_17_TOK                 "ra2_acl_17"
#define RA2_MACFILTER_18_TOK                 "ra2_acl_18"
#define RA2_MACFILTER_19_TOK                 "ra2_acl_19"
#define RA2_MACFILTER_20_TOK                 "ra2_acl_20"
#if NUM_MAC_FILTERS > 20
#define RA2_MACFILTER_21_TOK                 "ra2_acl_21"
#define RA2_MACFILTER_22_TOK                 "ra2_acl_22"
#define RA2_MACFILTER_23_TOK                 "ra2_acl_23"
#define RA2_MACFILTER_24_TOK                 "ra2_acl_24"
#define RA2_MACFILTER_25_TOK                 "ra2_acl_25"
#define RA2_MACFILTER_26_TOK                 "ra2_acl_26"
#define RA2_MACFILTER_27_TOK                 "ra2_acl_27"
#define RA2_MACFILTER_28_TOK                 "ra2_acl_28"
#define RA2_MACFILTER_29_TOK                 "ra2_acl_29"
#define RA2_MACFILTER_30_TOK                 "ra2_acl_30"
#define RA2_MACFILTER_31_TOK                 "ra2_acl_31"
#define RA2_MACFILTER_32_TOK                 "ra2_acl_32"
#if NUM_MAC_FILTERS > 32
#define RA2_MACFILTER_33_TOK                 "ra2_acl_33"
#define RA2_MACFILTER_34_TOK                 "ra2_acl_34"
#define RA2_MACFILTER_35_TOK                 "ra2_acl_35"
#define RA2_MACFILTER_36_TOK                 "ra2_acl_36"
#define RA2_MACFILTER_37_TOK                 "ra2_acl_37"
#define RA2_MACFILTER_38_TOK                 "ra2_acl_38"
#define RA2_MACFILTER_39_TOK                 "ra2_acl_39"
#define RA2_MACFILTER_40_TOK                 "ra2_acl_40"
#define RA2_MACFILTER_41_TOK                 "ra2_acl_41"
#define RA2_MACFILTER_42_TOK                 "ra2_acl_42"
#define RA2_MACFILTER_43_TOK                 "ra2_acl_43"
#define RA2_MACFILTER_44_TOK                 "ra2_acl_44"
#define RA2_MACFILTER_45_TOK                 "ra2_acl_45"
#define RA2_MACFILTER_46_TOK                 "ra2_acl_46"
#define RA2_MACFILTER_47_TOK                 "ra2_acl_47"
#define RA2_MACFILTER_48_TOK                 "ra2_acl_48"
#define RA2_MACFILTER_49_TOK                 "ra2_acl_49"
#define RA2_MACFILTER_50_TOK                 "ra2_acl_50"
#endif
#endif
#endif

#endif

#ifdef HAS_RA2_SETTINGS
/**						SSID(2)									  */
#define RA2_2_TOK                      "ra2_2"
#define RA2_2_                         RA2_2_TOK
#define RA2_2_ENABLE_TOK                 RA2_2_ _ENABLE_TOK
#define RA2_2_SSID_TOK                   RA2_2_ _SSID_TOK
#define RA2_2_WEP_TOK                    RA2_2_ _WEP_TOK
#define RA2_2_KEYID_TOK                  RA2_2_ _KEYID_TOK
#define RA2_2_KEYTYPE_TOK                RA2_2_ _KEYTYPE_TOK
#define RA2_2_WEPKEY_TOK                 RA2_2_ _WEPKEY_TOK
#define RA2_2_WEPKEY_0_TOK               RA2_2_ _WEPKEY_0_TOK
#define RA2_2_WEPKEY_1_TOK               RA2_2_ _WEPKEY_1_TOK
#define RA2_2_WEPKEY_2_TOK               RA2_2_ _WEPKEY_2_TOK
#define RA2_2_WEPKEY_3_TOK               RA2_2_ _WEPKEY_3_TOK
#define RA2_2_ENC_TYPE_TOK               RA2_2_ _ENC_TYPE_TOK
#define RA2_2_WPAPASSPHRASE_TOK          RA2_2_ _WPAPASSPHRASE_TOK
#define RA2_2_HIDESSID_TOK               RA2_2_ _HIDESSID_TOK
#define RA2_2_WPAPSK_LIFETIME_TOK        RA2_2_ _WPAPSK_LIFETIME_TOK
#define RA2_2_WPAPSK_LIFETIME_EN_TOK     RA2_2_ _WPAPSK_LIFETIME_EN_TOK
#define RA2_2_WPAPSK_KEYTYPE_TOK         RA2_2_ _WPAPSK_KEYTYPE_TOK
#define RA2_2_WMM_ENABLE_TOK             RA2_2_ _WMM_ENABLE_TOK
#define RA2_2_AUTH_TOK                   RA2_2_ _AUTH_TOK
#define RA2_2_8021X_ENABLE_TOK           RA2_2_ _8021X_ENABLE_TOK
#define RA2_2_8021X_SERVIP_TOK           RA2_2_ _8021X_SERVIP_TOK
#define RA2_2_8021X_SERVPORT_TOK         RA2_2_ _8021X_SERVPORT_TOK
#define RA2_2_8021X_SERVPW_TOK           RA2_2_ _8021X_SERVPW_TOK
#define RA2_2_WDS_SEC_TYPE_TOK           RA2_2_ _WDS_SEC_TYPE_TOK
#define RA2_2_WDS_WPAPASSPHRASE_TOK      RA2_2_ _WDS_WPAPASSPHRASE_TOK
#define RA2_2_WDS_MAC_TOK                RA2_2_ _WDS_MAC_TOK
#define RA2_2_WDS_MAC_1_TOK              RA2_2_ _WDS_MAC_1_TOK
#define RA2_2_WDS_MAC_2_TOK              RA2_2_ _WDS_MAC_2_TOK
#define RA2_2_WDS_MAC_3_TOK              RA2_2_ _WDS_MAC_3_TOK
#define RA2_2_WDS_MAC_4_TOK              RA2_2_ _WDS_MAC_4_TOK
#define RA2_2_WDS_WEP_TOK                RA2_2_ _WDS_WEP_TOK
#define RA2_2_WDS_KEYID_TOK              RA2_2_ _WDS_KEYID_TOK
#define RA2_2_WDS_WEPKEY_0_TOK           RA2_2_ _WDS_WEPKEY_0_TOK
#define RA2_2_WDS_WEPKEY_1_TOK           RA2_2_ _WDS_WEPKEY_1_TOK
#define RA2_2_WDS_WEPKEY_2_TOK           RA2_2_ _WDS_WEPKEY_2_TOK
#define RA2_2_WDS_WEPKEY_3_TOK           RA2_2_ _WDS_WEPKEY_3_TOK
#define RA2_2_ISOLATED_ENABLE_TOK        RA2_2_ _ISOLATED_ENABLE_TOK
#if HAS_ADVANCED_ISOLATED
#define RA2_2_STA_ISOLATED_ENABLE_TOK    RA2_2_ _STA_ISOLATED_ENABLE_TOK
#endif
#if L2_CONTROL_ACCESS
#if HAS_WAN_ACL
#define RA2_2_ACCESS_WLAN2WAN_TOK		 RA2_2_ _ACCESS_WLAN2WAN_TOK
#endif /*HAS_WAN_ACL*/
#endif /*L2_CONTROL_ACCESS*/
/**						SSID(3)									  */
#define RA2_3_TOK                      "ra2_3"
#define RA2_3_                         RA2_3_TOK
#define RA2_3_ENABLE_TOK                 RA2_3_ _ENABLE_TOK
#define RA2_3_SSID_TOK                   RA2_3_ _SSID_TOK
#define RA2_3_WEP_TOK                    RA2_3_ _WEP_TOK
#define RA2_3_KEYID_TOK                  RA2_3_ _KEYID_TOK
#define RA2_3_KEYTYPE_TOK                RA2_3_ _KEYTYPE_TOK
#define RA2_3_WEPKEY_TOK                 RA2_3_ _WEPKEY_TOK
#define RA2_3_WEPKEY_0_TOK               RA2_3_ _WEPKEY_0_TOK
#define RA2_3_WEPKEY_1_TOK               RA2_3_ _WEPKEY_1_TOK
#define RA2_3_WEPKEY_2_TOK               RA2_3_ _WEPKEY_2_TOK
#define RA2_3_WEPKEY_3_TOK               RA2_3_ _WEPKEY_3_TOK
#define RA2_3_ENC_TYPE_TOK               RA2_3_ _ENC_TYPE_TOK
#define RA2_3_WPAPASSPHRASE_TOK          RA2_3_ _WPAPASSPHRASE_TOK
#define RA2_3_HIDESSID_TOK               RA2_3_ _HIDESSID_TOK
#define RA2_3_WPAPSK_LIFETIME_TOK        RA2_3_ _WPAPSK_LIFETIME_TOK
#define RA2_3_WPAPSK_LIFETIME_EN_TOK     RA2_3_ _WPAPSK_LIFETIME_EN_TOK
#define RA2_3_WPAPSK_KEYTYPE_TOK         RA2_3_ _WPAPSK_KEYTYPE_TOK
#define RA2_3_WMM_ENABLE_TOK             RA2_3_ _WMM_ENABLE_TOK
#define RA2_3_AUTH_TOK                   RA2_3_ _AUTH_TOK
#define RA2_3_8021X_ENABLE_TOK           RA2_3_ _8021X_ENABLE_TOK
#define RA2_3_8021X_SERVIP_TOK           RA2_3_ _8021X_SERVIP_TOK
#define RA2_3_8021X_SERVPORT_TOK         RA2_3_ _8021X_SERVPORT_TOK
#define RA2_3_8021X_SERVPW_TOK           RA2_3_ _8021X_SERVPW_TOK
#define RA2_3_WDS_SEC_TYPE_TOK           RA2_3_ _WDS_SEC_TYPE_TOK
#define RA2_3_WDS_WPAPASSPHRASE_TOK      RA2_3_ _WDS_WPAPASSPHRASE_TOK
#define RA2_3_WDS_MAC_TOK                RA2_3_ _WDS_MAC_TOK
#define RA2_3_WDS_MAC_1_TOK              RA2_3_ _WDS_MAC_1_TOK
#define RA2_3_WDS_MAC_2_TOK              RA2_3_ _WDS_MAC_2_TOK
#define RA2_3_WDS_MAC_3_TOK              RA2_3_ _WDS_MAC_3_TOK
#define RA2_3_WDS_MAC_4_TOK              RA2_3_ _WDS_MAC_4_TOK
#define RA2_3_WDS_WEP_TOK                RA2_3_ _WDS_WEP_TOK
#define RA2_3_WDS_KEYID_TOK              RA2_3_ _WDS_KEYID_TOK
#define RA2_3_WDS_WEPKEY_0_TOK           RA2_3_ _WDS_WEPKEY_0_TOK
#define RA2_3_WDS_WEPKEY_1_TOK           RA2_3_ _WDS_WEPKEY_1_TOK
#define RA2_3_WDS_WEPKEY_2_TOK           RA2_3_ _WDS_WEPKEY_2_TOK
#define RA2_3_WDS_WEPKEY_3_TOK           RA2_3_ _WDS_WEPKEY_3_TOK
#define RA2_3_ISOLATED_ENABLE_TOK        RA2_3_ _ISOLATED_ENABLE_TOK
#if HAS_ADVANCED_ISOLATED
#define RA2_3_STA_ISOLATED_ENABLE_TOK    RA2_3_ _STA_ISOLATED_ENABLE_TOK
#endif
#if L2_CONTROL_ACCESS
#if HAS_WAN_ACL
#define RA2_3_ACCESS_WLAN2WAN_TOK		 RA2_3_ _ACCESS_WLAN2WAN_TOK
#endif /*HAS_WAN_ACL*/
#endif /*L2_CONTROL_ACCESS*/
/**						SSID(4)									  */

#define RA2_4_TOK                      "ra2_4"
#define RA2_4_                         RA2_4_TOK
#define RA2_4_ENABLE_TOK                 RA2_4_ _ENABLE_TOK
#define RA2_4_SSID_TOK                   RA2_4_ _SSID_TOK
#define RA2_4_WEP_TOK                    RA2_4_ _WEP_TOK
#define RA2_4_KEYID_TOK                  RA2_4_ _KEYID_TOK
#define RA2_4_KEYTYPE_TOK                RA2_4_ _KEYTYPE_TOK
#define RA2_4_WEPKEY_TOK                 RA2_4_ _WEPKEY_TOK
#define RA2_4_WEPKEY_0_TOK               RA2_4_ _WEPKEY_0_TOK
#define RA2_4_WEPKEY_1_TOK               RA2_4_ _WEPKEY_1_TOK
#define RA2_4_WEPKEY_2_TOK               RA2_4_ _WEPKEY_2_TOK
#define RA2_4_WEPKEY_3_TOK               RA2_4_ _WEPKEY_3_TOK
#define RA2_4_ENC_TYPE_TOK               RA2_4_ _ENC_TYPE_TOK
#define RA2_4_WPAPASSPHRASE_TOK          RA2_4_ _WPAPASSPHRASE_TOK
#define RA2_4_HIDESSID_TOK               RA2_4_ _HIDESSID_TOK
#define RA2_4_WPAPSK_LIFETIME_TOK        RA2_4_ _WPAPSK_LIFETIME_TOK
#define RA2_4_WPAPSK_LIFETIME_EN_TOK     RA2_4_ _WPAPSK_LIFETIME_EN_TOK
#define RA2_4_WPAPSK_KEYTYPE_TOK         RA2_4_ _WPAPSK_KEYTYPE_TOK
#define RA2_4_WMM_ENABLE_TOK             RA2_4_ _WMM_ENABLE_TOK
#define RA2_4_AUTH_TOK                   RA2_4_ _AUTH_TOK
#define RA2_4_8021X_ENABLE_TOK           RA2_4_ _8021X_ENABLE_TOK
#define RA2_4_8021X_SERVIP_TOK           RA2_4_ _8021X_SERVIP_TOK
#define RA2_4_8021X_SERVPORT_TOK         RA2_4_ _8021X_SERVPORT_TOK
#define RA2_4_8021X_SERVPW_TOK           RA2_4_ _8021X_SERVPW_TOK
#define RA2_4_WDS_SEC_TYPE_TOK           RA2_4_ _WDS_SEC_TYPE_TOK
#define RA2_4_WDS_WPAPASSPHRASE_TOK      RA2_4_ _WDS_WPAPASSPHRASE_TOK
#define RA2_4_WDS_MAC_TOK                RA2_4_ _WDS_MAC_TOK
#define RA2_4_WDS_MAC_1_TOK              RA2_4_ _WDS_MAC_1_TOK
#define RA2_4_WDS_MAC_2_TOK              RA2_4_ _WDS_MAC_2_TOK
#define RA2_4_WDS_MAC_3_TOK              RA2_4_ _WDS_MAC_3_TOK
#define RA2_4_WDS_MAC_4_TOK              RA2_4_ _WDS_MAC_4_TOK
#define RA2_4_WDS_WEP_TOK                RA2_4_ _WDS_WEP_TOK
#define RA2_4_WDS_KEYID_TOK              RA2_4_ _WDS_KEYID_TOK
#define RA2_4_WDS_WEPKEY_0_TOK           RA2_4_ _WDS_WEPKEY_0_TOK
#define RA2_4_WDS_WEPKEY_1_TOK           RA2_4_ _WDS_WEPKEY_1_TOK
#define RA2_4_WDS_WEPKEY_2_TOK           RA2_4_ _WDS_WEPKEY_2_TOK
#define RA2_4_WDS_WEPKEY_3_TOK           RA2_4_ _WDS_WEPKEY_3_TOK
#define RA2_4_ISOLATED_ENABLE_TOK        RA2_4_ _ISOLATED_ENABLE_TOK
#if HAS_ADVANCED_ISOLATED
#define RA2_4_STA_ISOLATED_ENABLE_TOK    RA2_4_ _STA_ISOLATED_ENABLE_TOK
#endif
#if L2_CONTROL_ACCESS
#if HAS_WAN_ACL
#define RA2_4_ACCESS_WLAN2WAN_TOK		 RA2_4_ _ACCESS_WLAN2WAN_TOK
#endif /*HAS_WAN_ACL*/
#endif /*L2_CONTROL_ACCESS*/



#define RA2_1_ACCESS_WLAN2LAN_TOK          RA2_1_ _ACCESS_WLAN2LAN_TOK
#define RA2_2_ACCESS_WLAN2LAN_TOK         RA2_2_ _ACCESS_WLAN2LAN_TOK
#define RA2_3_ACCESS_WLAN2LAN_TOK         RA2_3_ _ACCESS_WLAN2LAN_TOK
#define RA2_4_ACCESS_WLAN2LAN_TOK         RA2_4_ _ACCESS_WLAN2LAN_TOK


#define RA2_1_VLANTAG_TOK               RA2_1_ _VLANTAG_TOK
#define RA2_2_VLANTAG_TOK              RA2_2_ _VLANTAG_TOK
#define RA2_3_VLANTAG_TOK              RA2_3_ _VLANTAG_TOK
#define RA2_4_VLANTAG_TOK              RA2_4_ _VLANTAG_TOK

#endif /*HAS_RA2_SETTINGS*/


#endif //_TOKEN_WIRELESS_H_


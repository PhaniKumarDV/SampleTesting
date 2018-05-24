/**
 * $Id: config.h,v 1.1.1.1 2003/06/22 02:40:00 cfho Exp $
 * $Author: cfho $
 * $Date: 2003/06/22 02:40:00 $
 * $Locker:  $
 * $Revision: 1.1.1.1 $
 *
 * Send comments to: 
 *
 * Copyright (C) , SENAO INTERNATIONAL CO., LTD All rights reserved.
 * No part of this document may be reproduced in any form or by any 
 * means or used to make any derivative work (such as translation,
 * transformation, or adaptation) without permission from Senao
 * Corporation.
 */

#ifndef _GCONFIG_H_
#define _GCONFIG_H_

/**
 * IMPORTANT NOTE:
 * DO NOT modify any part of this file for board-specific customization. That
 * should be done in the 'board_xxx.h' file, where xxx="name of the board".
 */


/* #include "supportwlan.h" */



#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------*/
/* Linux Kernel Version Information */
/*-------------------------------------------------------------------------*/
#define KERNEL_VERSION_NUM(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define LINUX_VER_CODE KERNEL_VERSION_NUM(2,6,34)

#define IPTABLES_VERSION_NUM(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define IPTABLES_VER_CODE IPTABLES_VERSION_NUM(1,3,8)
/*-------------------------------------------------------------------------*/
/*                        HW Features                                      */
/*-------------------------------------------------------------------------*/
#define HAS_IXP_NPE         0
#define HAS_MII_CMD         0
#define HAS_PBX             0
#define HAS_DNS_PROXY       1
#define HAS_HW_DSP          0
#define HAS_HW_CPLD         0
#define HAS_HW_GPIO_BUTTONS      1       /* We should either use CPLD or GPIO */
#define HAS_HW_FXS          0
#define HAS_HW_RTC          0
#define HAS_HW_USB          0
#define HAS_MAC_CLONE       1
#define HAS_IGMPPROXY       1
/*#define HAS_POWER_SAVING        1*/
#define HAS_BANDWIDTH_MONITOR   0
#define HAS_SWITCH_5_VLAN       0
#define SUPPORT_ART 1
/*-------------------------------------------------------------------------*/
/*                        Partition Info                                   */
/*-------------------------------------------------------------------------*/
/********* MTD partition numbers *******************************/
#define BOOTLOADER_PARTITION_NAME           "Bootloader"
#define FACTORY_PARTITION_NAME              "manufacture"
#define KERNEL_PARTITION_NAME               "Kernel"
#define APP_STORAGE_PARTITION_NAME          "apps"
//#define APP_STORAGE_PARTITION_NAME          "app"
#define APPSCORE_PARTITION_NAME             "appscore"
#define COMBINED_APP_PARTITION_NAME         "cb-app"
#define SOUNDS_STORAGE_PARTITION_NAME       "sounds"
//#define MTD_STORAGE_PARTITION_NAME          "apcfg-storage"
#define MTD_STORAGE_PARTITION_NAME          "storage"
#define MTD_VOICE_PARTITION_NAME            "voice"
#define TINY_APP_STORAGE_PARTITION_NAME     "littleapp"
#define FACTORY_APP_STORAGE_PARTITION_NAME  "manufacture"
#define MTD_BACKUP_PARTITION_NAME           "backup"
#define CONFIG_PARTITION_NAME               "Config"
#define AR92XX_RF_PARTITION_NAME            "caldata" /* TODO: define a suitable name for all Atheros RF(used in config_init.c) */
#define APP_DIR                             "/apps"
#define STORAGE_DIR                         "/storage"
#define SOUNDS_DIR                          "/sounds"
//#define USBDISK_DEV                         "/dev/sda1"
//#define USBDISK_PATH                        "/mnt/usb"
#define FACTORY_DIR                         "/factory"
#define MAXIMUM_DISKSPACE_FOR_FW_UPGRADE    (1024*2)
#define FW_UPGRADE_IN_PROGRESS_FILE         FIRMWARE_UPAGRADE_TAG_FILE
#define MAX_TMPFS_NODES                     "64"

/*-------------------------------------------------------------------------*/
/*                        Interface name                                   */
/*-------------------------------------------------------------------------*/

/**
 * Now, we need to override potential destructive defines that were not correctly
 * setup in the include directive above.
 */

/**
 * The following variables define which logical linux nexwork devices
 * are to be assigned the function of LAN/WAN/WLAN, etc.
 *
 * WAN_DEV: WAN port network device.
 * ETHER_DEV:   LAN (802.1d) ethernet device.
 * WLAN_A_DEV:  802.11a wireless device.
 * WLAN_B_DEV:  802.11b wireless device.
 */
/* define the device interface name */
#define LOOP_DEV        "lo"         /* The loop-back device */
#define BRG_DEV         "br0"        /* There is ALWAYS a bridge device on the ISD */
#define WANBRG_DEV      "br1"        /* There is ALWAYS a bridge device on the ISD */
#define ETH_GMMI_1_DEV  "eth0"       /* There is only one RGMII in AR8327N*/
#define ETHER_A_DEV     "eth0.1"     /* LAN interface, configed by vconfig*/
#define ETHER_B_DEV     "eth0.2"     /* WAN interface, configed by vconfig*/
#define ETHER_C_DEV     "eth0.3"     /* DMZ interface, configed by vconfig*/
//#define ETHER_D_DEV     "eth0.4"     /* LAN interface, configed by vconfig*/
//#define ETHER_E_DEV     "eth0.5"     /* LAN interface, configed by vconfig*/


#define PPP_DEV     "ppp0"
#define ATH_DEV     "ath0"
#define ATH2_DEV     "ath4" /* todo: check and remove */
#define ATH_REPEATER_DEV  "ath10" /* todo: check and remove */
#define ATH2_REPEATER_DEV "ath11" /* todo: check and remove */
#define WLAN_G_DEV  ATH_DEV
#define MAX_VLAN_DEV_NUM  4
/* 2010-01-26 use WLAN_SSID_NUM to replace MAX_SSID_NUM */
/* #define MAX_SSID_NUM  4 */


#define WDS_DEV_NUM  4  /* support 4 WSD */
#define WDS_DEV     "wds"
#define WDS_0_DEV   "wds0"
#define WDS_1_DEV   "wds1"
#define WDS_2_DEV   "wds2"
#define WDS_3_DEV   "wds3"

#define APCLI_DEV   "apcli0"

//#define SUPPORT_AG7100
#define AGING_TIME  "0x0065"

/* define HAS_LOADBALANCE_FUNCTION 0 */

/* #define SUPPORT_TWO_BOTTON  1*/

#ifdef HAS_LOADBALANCE_FUNCTION

#define WAN1_DEV    ETHER_B_DEV
#define ETHER_DEV   ETHER_A_DEV
#define LAN_DEV		WLAN_G_DEV //ETHER_A_DEV  
#define DMZ_DEV     ETHER_C_DEV  

/* Has Second WAN */
//#define HAS_WAN2_DEV 0

/* Has Third WAN */
//#define HAS_WAN3_DEV

/* Has fourth WAN */
//#define HAS_WAN4_DEV 1

#else

#define WAN1_DEV    ETHER_B_DEV
#define ETHER_DEV   ETHER_A_DEV 
#define LAN_DEV     ETHER_A_DEV  
#define DMZ_DEV     ETHER_C_DEV  

#endif

#define WAN_DEV WAN1_DEV

/*-------------------------------------------------------------------------*/
/*                        Normal define                                    */
/*-------------------------------------------------------------------------*/
/* marklin 20070525 : flash size = 256MB */
//#define FLASH_SIZE_256MB 1 //no use; to check

#define TEMP_RAMDISK_SIZE  (1700)

/* TODO!!!!!*/
#define WLAN_PUREG 1 /* cfho 2006-0314, for cli, get back and check it!*/
#define G_TYPE 1
/* END TODO!!!***/

/*************Router *****************/
#define CONFIG_TARGET //for what?? to check! 
#define ROUTER_SUPPORT

/* cfho 2007-1011, it is used by config_init, mmi and httpd */
#define G_MIN_START_YEAR    2009
#define G_MAX_END_YEAR      2037



/* kenny 2007-01-31 ,Firmware Upgrade :display time to web UI */

#define G_WEB_FWD_APP_NEED_TIME 100
#define G_WEB_FWD_KERNEL_NEED_TIME 60
#define G_WEB_FWD_NEED_KERNELAPP_TIME 30
#define WEB_APPLY_TIME 10
#undef TMP_DIR_SIZE

/* cfho 2007-1113, this file is used for firmware upgrade,
    when the fwmanager or web starts to erase the flash, they should
    write the mtd number to this file. When the whole firmware upgarde
    process has been completed (erase, write and check); they should 
    delete this File.
    The config_init will mount the /storage and check this file,
    if it finds this file, it will start the udhcpd, and backup web server
    for firmware upgrade. Once the firmware upgrade has been completed (OK),
    the config_init should delete this file and reboot the board  */
#define FIRMWARE_UPAGRADE_TAG_FILE "/storage/firmware_upg_tag.txt"
#define FIRMWARE_UPAGRADE_CHECKSUM_FILE "/storage/firmware_upg_chksum.txt"

/* web daemon port */
#define HTTP_PRIVATE_PORT  (8080)
#define HTTP_PRIVATE_PORT6 (80)
/*-------------------------------------------------------------------------*/
/*                        Has Functions                                    */
/*-------------------------------------------------------------------------*/
/**
 * Here, we include the file for "board_xxx.h" that defines default values for
 * each specific board.
 */

/**
 * SI-690B is an AP+Router+VOIP box

 */
/*jay 20070620*/
#define HAS_ADVANCED_ROUTE  1
/* cfho 2007-0329, support L7 filtering in iptables, and WEB UI.
    we do not use L7 filtering because the IXP425 is not fast enough */
#define HAS_L7_FILTERING 0 
/* cfho 2007-0514, support PPTP server? */
#define HAS_PPTP_SERVER 0

/*jaykung20070704 support multiple ssid*/
#define HAS_MULTIPLE_SSID   1

/*jaykung 20070705 mac schedule function */
#define HAS_SCHEDULE_MACACL 0
/*jaykung 20070705 scroll in help datebase*/
#define HAS_SCROLL_FUNCTION 0

/* cfho 2007-1008 support PPTP */
#define HAS_WAN_PPTP   1
#define HAS_WAN_WLAN   0
#define HAS_WAN_PPPOE  1
#define HAS_DMZ_IF_FUNCTION 0
#define DMZ_ELEMENTS 5

/* cfho 2008-0409 Maximum NAT session for ip conntrack table.
   Must be multiplier of 8 */
//#define MAX_NAT_SESSION_NUM 2248
#define MAX_NAT_SESSION_NUM 10000
#define SUPPORT_LLMNR	1
#define HAS_HTTP_SYSTEM_NAME	1
/* 2010/10/13 Jerry : It needs update RT2860.dat manually at unConfigured of WPS status for wireless driver 2.5 (SDK 3500) */
//#define SYSCONF_UPDATE_WLAN_DAT 1
/*-------------------------------------------------------------------------*/
/*                        Specific Function Definition                     */
/*-------------------------------------------------------------------------*/
/* Support IPv6 */
#define SUPPORT_IPV6   0 
/* Support IPv6 6RD */
#define HAS_IPV6_6RD    0

#define HAS_FANCY_PING 1

#define HAS_SYSTEM_SCHEDULE_FUNCTION 1
#define HAS_SCHEDULE_FUNCTION   0
#if HAS_ADVANCED_ROUTE
#define HAS_DYNAMIC_ROUTE 0
#define HAS_STATIC_ROUTE  1
#endif

/**************************/
/* Radio related settings */
/**************************/
#define RADIO_CARD_NUM  1
#define MAX_RADIO_NUM   RADIO_CARD_NUM

/* WLAN related settings */
#define HAS_SUPPORT_ATHEROS_WLAN 1

#if HAS_SUPPORT_ATHEROS_WLAN
#define ATH_WLAN_SSID_NUM  4
#define ATH_WLAN_DEV       "ath"
#endif

#define WLAN_SSID_NUM 4
#define WLAN_DEV    "ath"
#if HAS_MULTIPLE_SSID

#if HAS_SUPPORT_ATHEROS_WLAN
/* second SSID */
#define HAS_ATH1_2_DEV  1
/* Third SSID */
#define HAS_ATH1_3_DEV   1
/* Fourth SSID */
#define HAS_ATH1_4_DEV   1

#if HAS_ATH1_2_DEV
#undef  ATH_WLAN_SSID_NUM
#define ATH_WLAN_SSID_NUM     2 /* Atheros WLAN device numbers */
#endif

#if HAS_ATH1_3_DEV
#undef  ATH_WLAN_SSID_NUM
#define ATH_WLAN_SSID_NUM     3 /* Atheros WLAN device numbers */
#endif

#if HAS_ATH1_4_DEV
#undef  ATH_WLAN_SSID_NUM
#define ATH_WLAN_SSID_NUM     4 /* Atheros WLAN device numbers */
#endif

#endif /*HAS_SUPPORT_ATHEROS_WLAN*/

#define HAS_SUPPORT_ATHEROS_RADIO2_WLAN 0

#if HAS_SUPPORT_ATHEROS_RADIO2_WLAN
#define ATH2_WLAN_SSID_NUM  1
/*#define ATH2_WLAN_DEV       "ath2"*/:
#else
#define ATH2_WLAN_SSID_NUM  0
#endif

#if HAS_SUPPORT_ATHEROS_RADIO2_WLAN
/* second SSID */
#define HAS_ATH2_2_DEV  1
/* Third SSID */
#define HAS_ATH2_3_DEV   1
/* Fourth SSID */
#define HAS_ATH2_4_DEV   1

#if HAS_ATH2_2_DEV
#undef  ATH2_WLAN_SSID_NUM
#define ATH2_WLAN_SSID_NUM     2 /* Atheros WLAN device numbers */
#endif

#if HAS_ATH2_3_DEV
#undef  ATH2_WLAN_SSID_NUM
#define ATH2_WLAN_SSID_NUM     3 /* Atheros WLAN device numbers */
#endif

#if HAS_ATH2_4_DEV
#undef  ATH2_WLAN_SSID_NUM
#define ATH2_WLAN_SSID_NUM     4 /* Atheros WLAN device numbers */
#endif

#endif /*HAS_SUPPORT_ATHEROS_RADIO2_WLAN*/

#endif /* HAS_MULTIPLE_SSID */

#ifdef ETHER_DEV 
#define HAS_ETHER_DEV 1 
#else        
#define HAS_ETHER_DEV 0
#endif

#ifdef WAN_DEV 
#define HAS_WAN_DEV 1 
#else        
#define HAS_WAN_DEV 0
#endif

#define WAN_DEV_NUM 1

#if HAS_WAN_DEV
#define HAS_MULTI_WAN_DEV 1
#endif

#if HAS_MULTI_WAN_DEV

#ifdef HAS_WAN2_DEV
#define WAN2_DEV        ETHER_B_DEV
#undef  WAN_DEV_NUM
#define WAN_DEV_NUM     2 /* WAN device numbers */
#endif

#ifdef HAS_WAN3_DEV
#define WAN3_DEV        ETHER_C_DEV
#define WAN_DEV_NUM     3 /* WAN device numbers */
#ifndef HAS_WAN2_DEV
#error "define HAS_WAN2_DEV needed"
#endif
#endif

#ifdef HAS_WAN4_DEV
#define WAN4_DEV        ETHER_D_DEV
#define WAN_DEV_NUM     4 /* WAN device numbers */
#ifndef HAS_WAN3_DEV
#error "define HAS_WAN3_DEV needed"
#endif
#endif

#define WAN_MAX_NUM   WAN_DEV_NUM


#endif
#ifdef WLAN_G_DEV 
#define HAS_WLAN_G_DEV 1 
#else        
#define HAS_WLAN_G_DEV 0
#endif



#ifdef WLAN_A_DEV
#define HAS_WLAN_A_DEV 1
#else
#define HAS_WLAN_A_DEV 0
#endif

#ifdef WLAN_B_DEV
#define HAS_WLAN_B_DEV 1
#else
#define HAS_WLAN_B_DEV 0
#endif

#ifndef USE_UDHCPD
#define USE_ISC_DHCPD
#endif

#ifdef ROUTER_SUPPORT
#define HAS_ROUTER_SUPPORT 1
#define HAVE_ROUTER_FUNCTION 1
#define HAS_WAN_DEV        1
#define HAS_DNS_PROXY      1
#define PPTPD_SUPPORT  1
#define HAS_MEDIA_SUPPORT  0
#define WLAN_ACL_APCFG     1
#define IMQ_SUPPORT        1
#else
#define HAS_ROUTER_SUPPORT 0
#endif

#ifdef PRINTER_SUPPORT
#define HAS_PRINTER_SUPPORT 1
#else
#define HAS_PRINTER_SUPPORT 0
#endif

#ifdef PPTPD_SUPPORT
#define HAS_PPTPD_SUPPORT 1
#else
#define HAS_PPTPD_SUPPORT 0
#endif

#ifdef RADIUS_SUPPORT
#define HAS_RADIUS_SUPPORT 1
#else
#define HAS_RADIUS_SUPPORT 0
#endif

#ifdef MEDIA_SUPPORT
#define HAS_MEDIA_SUPPORT 1
#else
#define HAS_MEDIA_SUPPORT 0
#endif

#ifdef IMQ_SUPPORT
#define HAS_IMQ_SUPPORT 1
#else
#define HAS_IMQ_SUPPORT 0
#endif

#define HAS_WAN_STATUS_LED  0

#define HAS_QOS_HWPORT     0
#define HAS_QOS_PRIO_QUEUE 1 
#define HAS_QOS_IP_LIMIT_QUEUE 0
#define QOS_BANDWIDTH_RATE_MAX  43000
#define NETPKT_PASSME_UNIT 100

#define HAS_APCLI_WPS      0
#define HAS_MULTI_OPMODE   0

#define HAS_NTP_USED_INDEX 0
#define HAS_MANUAL_TIME_SETTING 1

#define HAS_SPECIAL_PASS_THROUGH	0

#if 0 // to check!!!
#define SUPPORT_DETAILED_TIMEINFO 		1
#define HAS_ADVANCED_PRIORITY_QUEUE		1

/* 2009/2/11 jerry: support total bandwidth setting for bandwidth allocation */
#define HAS_QOS_TOTAL_BANDWIDTH_SETTING 1

/* AP Mode support dhcp client  */
/*#define HAS_DHCP_CLIENT_IN_AP_MODE  1*/

#define HAS_LOG_SERVER_DATE_START 1
#endif
#define HAS_KERNEL_PPTP 1
/*-------------------------------------------------------------------------*/
/*                        Vendor (Unique)                                  */
/*-------------------------------------------------------------------------*/
#define FOR_SMC          0
#define FOR_SITECOM      1
#define FOR_EG	         0
#define FOR_EG_ESR9750   0 /* Model Name ESR-9750 for EG */
/*-------------------------------------------------------------------------*/
/*                        Vendor Specials                                  */
/*-------------------------------------------------------------------------*/
/* 20110518 Jason: Use for sending trap in different vendor */
//#define ENTERPRISE_TRAP_OID ".1.3.6.1.4.1.14125.100" //to check!!!
#define DEF_REGULAR_DOMAIN      1
#define HAS_HOTEL_FUNCTION      0
/*regular domain
0:1-11  1:1-13 2:10-11 3:10-13 4:14 5:1-14 6:3-9 7:5-13
*/
/*-------------------------------------------------------------------------*/
/*                        GPIO Definition                                  */
/*-------------------------------------------------------------------------*/
/*RESET Button Function*/
#if 0
#define GPIO_WPS_BUTTON         2
#define GPIO_WPS_24G_LED        3
#define GPIO_WPS_5G_LED         4
/* #define GPIO_USB_LED         5*/
#define GPIO_STATUS_LED         5
#define GPIO_HW_RESET           6
#define GPIO_RESET_BUTTON       7
#define GPIO_POWER_LED          8
#define GPIO_HW_WATCHDOG        11
#define GPIO_LED_FREQ           (HZ/10)
#define RESET_DEFAULT_TIME      3 /* >3 seconds reset 2 default*/
#define WPS_TRIGGER_5G_TIME     10 /*<10 trigger 24G, > 10 trigger 5G*/
/*#define SUPPORT_HARDWARE_RESET  1*/
#endif
/*-------------------------------------------------------------------------*/
/*                       Atheros Max Txpower                               */
/*-------------------------------------------------------------------------*/
#define ATH_MAX_TX_POWER	25
/*-------------------------------------------------------------------------*/
/*                        Factory Test                                  */
/*-------------------------------------------------------------------------*/
#define USE_ENGENIUS_GPIO_LED

/*
 * LED
 */
/* Led gpio definition is arranged from panel left to right. */
#if 0
#define SENAO_GPIO_LED_POWER        8
#define SENAO_GPIO_LED_USB          5    /* Status Led */
#define SENAO_GPIO_LED_5G_WPS       4
#define SENAO_GPIO_LED_24G_WPS      3
#endif
/*---------------------------------------------*/
/*           APCFG_DEF_NUMBER VALUE            */
/*---------------------------------------------*/
#define NUM_PORT_QOS                            16
#define NUM_LAN_MAC_FILTERS                     32
#define NUM_IP_FILTERS                          32
#define NUM_URL_FILTER                          20
#define NUM_DHCPD_MACTOIP                       10
#define NUM_STATICROUTING                       20

#define NUM_MAC_FILTERS                         NUM_LAN_MAC_FILTERS
#define NUM_PORT_FORWARD                        32
#define NUM_NAT_VSERVER                         32
#define NUM_TRIGGER_PORT                        16
#define NAT_VSERVER_NAME_MAX                    25
#define NUM_SCHEDULE_LIST                       10
#define NUM_SPEC_APP_PUBLIC_PORT_LIST           10 /* 5 Pairs */
#define NUM_NTP_SERVER							1

/*---------------------------------------------*/
/*           APCFG_DEF_VALUE                  */
/*-------------------------------------------*/
#define APCFG_HAS_WARNINGS  1

/*** Engenius: not for this project ***/
/*
#if FOR_EG
#define VENDOR_NAME "EnGenius"
#define VENDOR_MODE "Wireless Network Broadband Router"
#define MODEL_NAME  "ESR-9753"
#define MODEL_NAME_FORHOSTNAME  "esr9753"
#define WEB_TITLE_NAME  "EnGenius Wireless 11n Broadband Router"

#define AP_WSC_MANUFACTURE     VENDOR_NAME" Technologies, Inc."
#define AP_WSC_MODEL_NAME      VENDOR_NAME" Wireless AP Router"
#define AP_WSC_DEVICE_NAME     VENDOR_NAME" 802.11n AP Router"
#define CLI_WSC_MODEL_NAME     VENDOR_NAME" Wireless Client"
#define CLI_WSC_DEVICE_NAME    VENDOR_NAME" Client"
#define CLI_WSC_DEVICE_NAME_R  VENDOR_NAME" EX-Registrar"
#endif
*/

/*FOR_Sitecom*/
#if FOR_SITECOM
/*old WSC method in Sitecom doesn't support trigger WSC by interface, add new function to support that function*/
#define SITECOM_SUPPORT_TRIGGER_WSC_INF 1


/*Vendor Specials*/
#undef VENDOR_NAME
#undef VENDOR_MODE
#undef MODEL_NAME
#undef WEB_TITLE_NAME
#define VENDOR_NAME "Sitecom"
#define VENDOR_MODE "Wireless Gigabit Broadband Router"
#define MODEL_NAME  "WLR-4000"
#define MODEL_NAME_FORHOSTNAME  "wlr4000"
#define WEB_TITLE_NAME  "Sitecom Wireless Gigabit Router 300N X4 WLR-4000"
#define MODEL_SUBNAME  "v1002"
#define NEW_MODEL_SUBNAME  "v1002"
#define HAS_MODEL_NAME_EXTEND 0
#if HAS_MODEL_NAME_EXTEND
#define MODEL_NAME2 "WLR-4000"
#define MODEL_NAME2_FORHOSTNAME "wlr4000"
#define WEB_TITLE_NAME2 "Sitecom Wireless Gigabit Router 300N X4 WLR-4000"
#endif

#define AP_WSC_MANUFACTURE     VENDOR_NAME" Europe BV"
#define AP_WSC_MODEL_NAME      VENDOR_NAME" Wireless AP Router 300N"
#define AP_WSC_DEVICE_NAME     VENDOR_NAME" 802.11n AP Router"
#define CLI_WSC_MODEL_NAME     VENDOR_NAME" Wireless Client"
#define CLI_WSC_DEVICE_NAME    VENDOR_NAME" Client"
#define CLI_WSC_DEVICE_NAME_R  VENDOR_NAME" EX-Registrar"
/*--------------------*/
/*default APCFG value*/
#ifdef HAS_WAN2_DEV
#undef  APCFG_DEF_WAN2_HOST
#undef  APCFG_DEF_WAN2_PPTP_HOSTNAME
#define APCFG_DEF_WAN2_HOST             "sitecom_router"
#define APCFG_DEF_WAN2_PPTP_HOSTNAME    "sitecom_router"
#endif
/*------------------*/
/*#define FW_NOTIFY_FOR_SITECOM   1*/
/*------------------*/
/*#define FORCE_SET_REGULARDOMAIN 1*/

/*#generate wpa2psk as default WLAN secutiry*/
#define USE_WPA2PSK_AS_DEFAULT_SECURITY 1

/*remove 0,O,1,I in passowrd*/
#define USE_WPA2PSK_AS_DEFAULT_SECURITY_2	1
#define FORCE_USE_WPA2PSK_AS_DEFAULT_SECURITY_2 1
/*Sitecom request login passowrd should be same as wpa2 key*/
#define GEN_ADMIN_PASSWORD_BY_MACADDR 1

/*don't show admin/admin in GUI*/
#define DISABLE_HTTP_LOGIN_HINT 1

#endif
/*FOR_Sitecom*/


#define LANMAC_HASCHANGED_TAG "/storage/lanMACChanged.tag"

#define SYSLOG_MESSAGE_SIZE 16000

/*joey 2009-1009 define log level for system_log*/
/*0: Nornal, 1: Advance, 2: Detail*/
#define DEFAULT_LOG_LEVEL 1
/***************************************************************************/

/*-------------------------------------------------------------------------*/
/*                        Web OPMode List                                  */
/*-------------------------------------------------------------------------*/
//#define WEB_OPMODE_LIST "0011101"
#define WEB_OPMODE_LIST "0000001"
/* opmode list
   Definition: [SYS_OPM_ARRP][SYS_OPM_WDSB][SYS_OPM_CBRT][SYS_OPM_CB][SYS_OPM_AP][SYS_OPM_APRP][SYS_OPM_AR]
   Example:
        "0000011" : AR, APRP
        "0001101" : AR, AP, CB
*/
/***************************************************************************/

/*-------------------------------------------------------------------------*/
/*                        Web Function List                                */
/*-------------------------------------------------------------------------*/
#define WEB_HAS_DUAL_PPPOE				0
#define WEB_HAS_PASS_THROUGH			1
#define WEB_HAS_PORTBASED_QOS			0
#define WEB_HAS_WLAN_CONNECTION_CONTROL		1
#define WEB_HAS_SAFARI4_AUTH_SETTING		1

/* 20090929 Nelson: support release WPS configuration */
#define WEB_SUPPORT_DTM_TEST_SETTINGS   1
/* 20090317 jerry chen: get vendor information from sysProductInfo.h */
#define WEB_GET_VENDOR_INFO_FROM_SYS	1

/*-------------------------------------------------------------------------*/
/*                        RMGMT Settings                                   */
/*-------------------------------------------------------------------------*/
#define RMGMT_INTERFACE_BRG						BRG_DEV
#define RMGMT_INTERFACE_LAN						ETHER_A_DEV
#define RMGMT_INTERFACE_WLAN					WLAN_G_DEV

/* 20080908 jerry chen: rmgmt */
#define RMGMT_FW_BOOTLOADER_FILENAME              "u-bootWLR-4000v1002.bin"
#define RMGMT_FW_KERNEL_FILENAME                  "uImageWLR-4000v1002"
#define RMGMT_FW_APP_FILENAME                     "appsWLR-4000v1002.sqsh"
#define RMGMT_FW_FACTORY_FILENAME                 "factoryappsWLR-4000v1002.sqsh"

/* marklin 20090303 : configure mtd partition */
#if LINUX_VER_CODE > KERNEL_VERSION_NUM(2,6,0)
#define UBOOT_ENV_PARTITION "/dev/mtd2"
#define RF_DATA_PARTITION "/dev/mtd7"
#define BACKUP_PARTITION "/dev/mtd5"
#else
#define UBOOT_ENV_PARTITION "/dev/mtd/2"
#define RF_DATA_PARTITION "/dev/mtd/7"
#define BACKUP_PARTITION "/dev/mtd/5"
#endif



#define APPS_PATH   "/apps.sqsh"


#ifdef __KERNEL__

/* cfho 2009-0730, TODO, need to check where should we define the HAVE_EXTERNAL_FLASH_MAP, hardcode here */
/*define it in kernel/ar_7100_flash*/
/* #define HAVE_EXTERNAL_FLASH_MAP 1 */
#ifdef HAVE_EXTERNAL_FLASH_MAP
#if 0
/***************************************************************************/

#define USER_DEFINITION_SN_FLASH_MAP
/*-------------------------------------------------------------------------*/
/*                        AR7100 SOC Flash map                             */
/*                                              cfho 2009-0730             */
/*-------------------------------------------------------------------------*/
//#define USER_DEFINITION_FLASH_MAP
//#define MTD_WRITEABLE		0x400

#if 0 /* One FW, 16 MB */
struct mtd_partition_t {
        char *name;              /* identifier string */
        unsigned int size;       /* partition size */
        unsigned int offset;     /* offset within the master MTD space */
        unsigned int mask_flags; /* master MTD flags to mask out for this partition */
        unsigned int reserved1;  /* pointer address for struct nand_ecclayout *ecclayout */
        unsigned int reserved2;  /* pointer address for struct mtd_info **mtdp;	 */
};
static struct mtd_partition_t physmap_partitions_t[] = {
        {
                name:           "Bootloader", 
                size:           0x30000,
                offset:         0,
        }, {
                name:           "Config ",
                size:           0x10000,
                offset:         0x30000,
        }, {
                name:           "caldata",
                size:           0x10000,
                offset:         0x40000,
        }, {
                name:           "Kernel",
                size:           0x500000,      /* 5 MB */
                offset:         0x50000,
        }, {
                name:           "app",        
                size:           0x500000,      /* 5 MB */
                offset:         0x550000,
        }, {
                name:           "backup",
                size:           0x10000,
                offset:         0xA50000,
        }, {
                name:           "Key",
                size:           0x10000,
                offset:         0xA60000,
        }, {
                name:           "manufacture",
                size:           0x90000,
                offset:         0xA70000,
        }, {
                name:           "reserved",    /* 4.4375 MB */
                size:           0x470000,
                offset:         0xB00000,
        }, {
                name:           "storage",  
                size:           0x90000,       
                offset:         0xF70000,
        }

};
#else /* Support 8 MB */

#define CP_APPSCORE_TO_SDRAM    1
#if 0
struct mtd_partition_t {
        char *name;              /* identifier string */
        unsigned int size;       /* partition size */
        unsigned int offset;     /* offset within the master MTD space */
        unsigned int mask_flags; /* master MTD flags to mask out for this partition */
        unsigned int reserved1;  /* pointer address for struct nand_ecclayout *ecclayout */
        unsigned int reserved2;  /* pointer address for struct mtd_info **mtdp;	 */
};

static struct mtd_partition_t physmap_partitions_t[] = {
        {
                name:           "Bootloader",  /* mtdblock0 */
                size:           0x30000,       /* 192KB */
                offset:         0,
        }, {
                name:           "Config",     /* mtdblock1 */
                size:           0xD000,       /* 52KB */
                offset:         0x30000,
        }, {
                name:           "caldata",
                size:           0x10000,
                offset:         0x3D000,
        }, {
                name:           "Kernel",        
                size:           0x133000,
                offset:         0x4D000,
        }, {
#if 0
#ifdef CP_APPSCORE_TO_SDRAM
                name:           "app", 
                size:           0x1EF000,
                offset:         0x188000,
#else
#error "Plase check!"
#endif
        }, {
                name:           "manufacture", 
                size:           0x73000,
                offset:         0x377000,
        }, {
                name:           "backup", 
                size:           0x9000,
                offset:         0x3EA000,
        }, {
#else
#ifdef CP_APPSCORE_TO_SDRAM
                name:           "app", 
                size:           0x1ED000,
                offset:         0x180000,
#else
#error "Plase check!"
#endif

        }, {
                 name:           "manufacture", 
                 size:           0x86000,
                 offset:         0x36D000,
        }, {
#endif
                name:           "storage", 
                size:           0xD000,
                offset:         0x3F3000,
        }
};
#else
struct mtd_partition_t {
        char *name;              /* identifier string */
        unsigned int size;       /* partition size */
        unsigned int offset;     /* offset within the master MTD space */
        unsigned int mask_flags; /* master MTD flags to mask out for this partition */
        unsigned int reserved1;  /* pointer address for struct nand_ecclayout *ecclayout */
        unsigned int reserved2;  /* pointer address for struct mtd_info **mtdp;	 */
};

static struct mtd_partition_t physmap_partitions_t[] = {
        {
                name:           "Bootloader",  /* mtdblock0 */
                size:           0x30000,       /* 192KB */
                offset:         0,
        }, {
                name:           "Config",     /* mtdblock1 */
                size:           0xD000,       /* 52KB */
                offset:         0x30000,
        }, {
                name:           "caldata",
                size:           0x10000,
                offset:         0x3D000,
        }, {
                name:           "Kernel",        
                size:           0x180000,
                offset:         0x4D000,
        }, {
#ifdef CP_APPSCORE_TO_SDRAM
                name:           "app", 
                size:           0x563000,
                offset:         0x1CD000,
#else
#error "Plase check!"
#endif

        }, {
                 name:           "manufacture", 
                 size:           0xA0000,
                 offset:         0x730000,
        }, {
                name:           "Reser_Back",        
                size:           0x10000,
                offset:         0x7D0000,
        }, {
                name:           "storage", 
                size:           0x20000,
                offset:         0x7E0000,
        }
};
#endif
#endif

#define NUM_PARTITIONS  (sizeof(physmap_partitions_t)/sizeof(struct mtd_partition_t))
#endif
#endif/*#if 0*/
#ifdef __cplusplus
}
#endif
#endif
#define tr(x) x


#endif

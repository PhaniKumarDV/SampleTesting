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
;    File    : 
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       
;*****************************************************************************/
#ifndef _APCFG_LIB_H
#define _APCFG_LIB_H

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <sap_ostypes.h>
#include <unistd.h>  //cfho 2006-0906
#include <gconfig.h>
#include <apcfg_product.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/

/**** Basic Define ****/
#define SHMKEY_APCFG        	((key_t) 7001)
#define SHMKEY_BACKUPAPCFG  	((key_t) 9001)

#define APCFG_WORK_DIR		"/storage/"
#define APCFG_WORK2_DIR		"/storage2/"

#if HAS_ODM_APPS
#define APCFG_ODM_DIR		"/odmapps/"
#define AP_CFG_ODM_FILE 	APCFG_ODM_DIR"odm_cfg.txt"
#endif

#if SUPPORT_CUSTOMIZED_DEF_VALUE
#define AP_CFG_CUSTOMIZED_DEF_FILE 		APCFG_WORK_DIR"ap_cfg_defval"
#endif

#define AP_CFG_FILE 		APCFG_WORK_DIR"ap_cfg"
#define AP_CFG_BAKUP_FILE 	APCFG_WORK_DIR"ap_cfg_bakup"
#define AP_CFG_NEW_FILE 	APCFG_WORK_DIR"ap_cfg_new"

#define AP_CFG_FILE_2 		APCFG_WORK2_DIR"ap_cfg"
#define AP_CFG_BAKUP_FILE_2 APCFG_WORK2_DIR"ap_cfg_bakup"
#define AP_CFG_NEW_FILE_2	APCFG_WORK2_DIR"ap_cfg_new"

#define AP_CFG_DEF_FILE 	"/tmp/ap_cfg_def"

#if HAS_LANGUAGE_PACK_UPGRADE
#define LANGUAGE_PACK_FILE 	LANGUAGE_DIR"/language.sqsh"
#endif

#define MAX_AP_VALUE_LEN 		100
#define MAX_AP_TOKEN_LEN 		20
#define MAX_READ_BUFF	 		1000

#define AP_CFG_FILE_DATA_PATTERN "%s:%s\n"
#define SET_END_TAG 			(-0x7fffffff)

/* cfho 2006-0824 whether a item is checked */
#define S_UNCHK         0x0000001   /* The item is not checked */
#define S_CHKED         0x0000010   /* The item is checked */
#define S_CHANGED       0x0000100   /* The item is changed */
#define S_TEMPORARY     0x0001000   /* The item is temporary, autochannel use it. */

/**** Custom Define ****/
#define NUM_SIP_CODEC 			4
#define WEB_RESET_TIME 			10

#define TIME_ZONE_DATE_PATTERN  "%d,%d,%d,%d"
#define MAC_PATTERN   			"%02X%02X%02X%02X%02X%02X"
#define MAC_PATTERN_WITH_COLON 	"%02X:%02X:%02X:%02X:%02X:%02X"
#define MAX_MAC_ADDR_LEN 		12

#define IP_PATTERN 				"%d.%d.%d.%d"
#define MAX_IP_BUF_LEN 			32

#define TEMP_ACCOUNT_PATTREN 	"%d,%d,%s"

#define APPS_PASSWORD_MIN_SIZE  0
#define APPS_PASSWORD_MAX_SIZE	30
#define APPS_IP_MAX_SIZE		16

/* System Log File */
#define LOG_MSG_FILE            "/tmp/logmsg.log"
#define LOG_MSG_FILE2           "/tmp/logmsg2.log"
#if HAS_PARENTAL_CONTROL
#define LOG_MSG_FILE_PC            "/tmp/logmsg_pc.log"
#define LOG_MSG_FILE2_PC           "/tmp/logmsg2_pc.log"
#endif
#define SITE_SURVEY_FILE 			"/mnt/sitesurvey"
#define DIAG_NOSIS_FILE 			"/mnt/pingresult"
#define TRACEROUTE_FILE 			"/mnt/tracerouteresult"
#define WPS_STATUS_PATH				"/mnt/wps_status"
#define WPS_STA_STATUS_PATH     	"/mnt/wps_sta_status"
#define WSC_PROFILE_INFO_PATH		"/mnt/wsc_profile_info"
#define WSC_INIC_PROFILE_INFO_PATH	"/mnt/wsc_inic_profile_info"
#define WPS_BUTTON_PATH				"/mnt/trigger_wps_pbc"
#define TR069_LOG_PATH				"/tmp/agent.log"
#define BSF_LOG_MSG_FILE        	"/tmp/bsfUrlBlock.log"
#define WLS_24G_CHANNEL_FILE        "/tmp/wls_24g_chanlist"
#define WLS_5G_CHANNEL_FILE        	"/tmp/wls_5g_chanlist"

#if HAS_LLD2_CLIENT
#define LLTD_PATH			"/var/lltd_"
#define LLTD_MAC_PATH		LLTD_PATH"mac"
#define LLTD_NUM_PATH		LLTD_PATH"num"
#define LLTD_LAN_NUM_PATH	LLTD_PATH"lan_num"
#define LLTD_WLAN_NUM_PATH	LLTD_PATH"wlan_num"
#define LLTD_LAN_PATH		LLTD_PATH"lan_dev"
#define LLTD_WLAN_PATH		LLTD_PATH"wlan_dev"
#endif

#if HAS_WEATHER_SUPPORT
#define WEATHER_STATUS_PATH	   "/var/weather"
#endif

/* HAS_IODATA_FILE_CONFIG - IODATA Style */ 
#define IODATA_CONFIG_FILE     "/tmp/iodata_config" 
#define IODATA_CONFIG_RESULT   "/tmp/config_result"
/* HAS_MACFILTER_IMPORT - IODATA Style */ 
#define MACFILTER_EXPORT_FILE  "/tmp/macfilter.txt"
#define MACFILTER_IMPORT_FILE  MACFILTER_EXPORT_FILE


#if HAS_BANDWIDTH_MONITOR
#define IF_INFO_FILE_LOCK_WAITING_TIME  (5)
#define IF_INFO_FILE_LOCK_NAME  "ifInfoLock"
#define IF_INFO_PATH   "/mnt/ifInfo.log"
#endif

#if HAS_WAN_FAILOVER
#define PRE_WAN_TYPE_PATH APCFG_WORK_DIR"prewantype.txt"
#endif

/*to identify old mp mac, we create a tag for old mp mac*/
#define SITECOM_OLD_MP_FILE "/mnt/sitecom_old_mp"
/**** Macro define ****/
#define APCFG_HTONS(a, buff) { \
								*((T_UCHAR*)buff+1) = a&0xff;\
								*((T_UCHAR*)buff) = (a>>8)&0xff;\
							 }
#define APCFG_HTONL(a, buff) {\
							    *((T_UCHAR*)buff+3) = a&0xff;\
								*((T_UCHAR*)buff+2) = (a>>8)&0xff;\
								*((T_UCHAR*)buff+1) = (a>>16)&0xff;\
								*((T_UCHAR*)buff)   = (a>>24)&0xff;\
							 }
#define HTOI(ch) ((tolower(ch)-'a'>=0)?(tolower(ch)-'a'+10):(tolower(ch)-'0'))


/* access level */
/* BitMap 0: disable, 1: LAN, 2:WAN */
#define ACCESS_LEVEL_NO         0
#define ACCESS_LEVEL_LAN        (1<<0)
#define ACCESS_LEVEL_WAN        (1<<1)

/*-------------------------------------------------------------------------*/
/*                           enum & struct                                 */
/*-------------------------------------------------------------------------*/
typedef struct __apCfgItemNameSet
{
    T_INT32 id;
    const T_CHAR* text;
} apCfgItemNameSet;


typedef struct _ap_cfg_item
{
    T_CHAR token[MAX_AP_TOKEN_LEN]      __ATTRIBUTE_PACKED__;
    T_CHAR memvalue[MAX_AP_VALUE_LEN]   __ATTRIBUTE_PACKED__;
    T_INT32 type                        __ATTRIBUTE_PACKED__;
    T_UINT32 status                     __ATTRIBUTE_PACKED__; /* indicate the status of this item. */
    T_UINT64 group                      __ATTRIBUTE_PACKED__; 
} __S_ATTRIBUTE_PACKED__ ap_cfg_item_t;

typedef struct _ap_setting
{
	T_BOOL isModified;    /* is anything modified ?*/
	T_INT32 itemCount;    /* cfg item len */
	T_INT32 refCount;	  /* create share mem num*/
	ap_cfg_item_t* items; /* point to large database */
} ap_setting_t;

/*cfho 06-0422 day and time, for iptable 'time' filter module */
typedef struct _daytime
{
    T_UINT8 bAlways;    /* if TRUE, then we don't use the following variables*/
    T_UINT32 starthr; /* 0 ~23 */
    T_UINT32 startmm; /* 0 ~59*/
    T_UINT32 endhr;   /* 0 ~23*/
    T_UINT32 endmm;   /* 0 ~59*/
    T_UINT32 daysmask;    /* a HEX mask, the B0 -> Sunday, B1-> Satuarday, ..., B7->Monday */
} daytime_t;

typedef struct _sysclock
{
  T_INT32 hour;
  T_INT32 min;  
} sysclock_t;

typedef struct _sysdate
{
  T_INT32 yy;
  T_INT32 mm;
  T_INT32 dd;  
} sysdate_t;

/*----------------------------- TYPE CHECKING --------------------------------*/
typedef struct _cfg_item_func
{
	/* cfho 2006-0416 for extra checking */
	AP_CFG_TYPE type; 
    /* private field mainly for checking */
	T_VOID* priv;
	/* copy the cfg value to void* dst */
	T_BOOL (*getValue)(struct _cfg_item_func* self, const ap_cfg_item_t* item, T_VOID* dst);
    /* check and set the cfg value from void* src */
	T_BOOL (*setValue)(struct _cfg_item_func* self, ap_cfg_item_t* item, const T_VOID* src);
    /* convert the internal value to readable value */
    const T_CHAR* (*toText)(struct _cfg_item_func* self, ap_cfg_item_t* item);
    /* Load the default value into hex format string*/
    T_BOOL (*defValue)(ap_cfg_item_t* item);
} cfg_item_func_t;

typedef struct _cfg_item_warning
{
	AP_CFG_TYPE type;
    const T_CHAR* warningMsg;
} cfg_item_warning;

/*-------------------------------------------------------------------------*/
/*                           Parameter                                     */
/*-------------------------------------------------------------------------*/
extern cfg_item_func_t CFGITEM_OP[];
extern cfg_item_warning CFGITEM_OP_WARNINGS[];

/*-------------------------------------------------------------------------*/
/*                           AP CFG API                                    */
/*-------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/**** Basic Functions ****/
T_VOID initApShareMem(T_VOID);
T_VOID destroyApShareMem(T_VOID);
T_BOOL apCfgSetValueByStr(const T_CHAR* token, const T_CHAR* strvalue);
T_BOOL apCfgSetValue(const T_CHAR* token, const T_VOID* val);
T_BOOL apCfgSetIntValue(const T_CHAR* token, const T_INT32 val);
T_BOOL apCfgGetValue(const T_CHAR* token, T_VOID* dst);
T_BOOL apCfgGetValueEx(const T_CHAR* token, T_VOID* dst);
T_CHAR* apCfgGetStrValue(T_CHAR *format, ...);
T_INT32 apCfgGetIntValue(T_CHAR *format, ...);
T_CHAR* apCfgGetWebStrValue(T_CHAR *format, ...);

T_BOOL apCfgSetValue2(const T_VOID* val, T_CHAR *format, ...);
T_BOOL apCfgSetValueByStr2(const T_CHAR* strvalue, T_CHAR *format, ...);
T_BOOL apCfgSetIntValue2(const T_INT32 val, T_CHAR *format, ...);
T_BOOL apCfgGetValue2(T_VOID* dst, T_CHAR *format, ...);

/**** Update & Modified ****/
T_BOOL __apCfgUpdateFile(const T_CHAR *fileName, const ap_setting_t* cfg);
T_BOOL apCfgUpdateFile(T_VOID);
T_VOID apCfgUpdateModifiedData(T_VOID);
T_UINT32 apCfgIsModified(T_VOID);
T_UINT64 apCfgGetBeModifiedGroupValue(T_UINT32 isClearChangedFlag);
T_UINT64 apCfgGetModGrpVal(T_VOID);
T_VOID apCfgRemoveModGrpVal(T_UINT64 grp);
T_VOID apCfgRollback(T_CHAR *format, ...);
T_VOID apCfgRestoreDefault(T_VOID);
T_VOID apCfgReload(T_VOID);
T_UINT32 apCfgCheckStatusChanged(const T_CHAR* token);
T_INT32 apCfgSetStatusUnChanged(const T_CHAR* token);

/**** Advance Functions ****/
T_INT32 apCfgGetFirstByte(const T_CHAR *format, ...);
T_INT32 apCfgGetIndex(const T_CHAR* token);
T_INT32 apCfgFindFirstAvailable(const T_CHAR* tokenPrefix, const T_INT32 numofTokens);
T_BOOL apCfgGetMacStrValue(const T_CHAR* token, T_VOID* dst);
T_BOOL apCfgGetMacAddStrValue(const T_CHAR* macAddr,T_CHAR* op,T_VOID* dst);
const T_CHAR* apCfgGetItemText(const T_CHAR* token);
T_BOOL apCfgTestValue(const AP_CFG_TYPE type, const T_VOID* src);
T_BOOL apCfgTestTextValue(const AP_CFG_TYPE type, const T_CHAR* src);
AP_CFG_TYPE apCfgGetItemType(const T_CHAR* token);
T_INT32 apCfgGetMaxValue(const T_CHAR *format, ...);
T_INT32 apCfgGetMinValue(const T_CHAR *format, ...);
T_INT32 apCfgGetStructListCount(const T_CHAR* tokenPrefix, const T_INT32 numofTokens);
T_INT32 apCfgGetAvailableWlanChMaxNum(const T_CHAR* token);
T_CHAR* apCfgGetAvailableWlanChItem(const T_CHAR* token,int maxChNum);
T_BOOL apCfgChangeTokenGroup(const T_CHAR* token, const T_UINT64 group, int type);

/**** Enum Functions ****/
size_t apCfgGetEnumDataSize(const T_CHAR* token);
T_INT32 apCfgGetEnumType(const T_CHAR* token);
const apCfgItemNameSet* apCfgGetEnumData(const T_CHAR* token, int idx);
T_INT32 apCfgGetEnumDataIdx(const T_CHAR* token, int val);
apCfgItemNameSet* __getEnumData(AP_CFG_TYPE type, int idx);
int __getEnumDataIdxByType(AP_CFG_TYPE type, int val);
size_t __getEnumDataSize(AP_CFG_TYPE type);

/**** Warning Functions ****/
const T_CHAR* apCfgGetWarnings(const T_CHAR* token);
const T_CHAR* __getOpWarnings(AP_CFG_TYPE type);

/**** Internal Functions ****/
T_BOOL checkpApCfg(ap_setting_t* cfg, const ap_setting_t* rollBackCfg);
T_VOID assertModule(T_VOID);
T_VOID sortItemTable(ap_cfg_item_t *cfg, T_INT32 len);
T_BOOL fixItemTable(ap_cfg_item_t* cfg, T_INT32 len);
T_BOOL readApCfgFile(const T_CHAR* fileName, ap_setting_t* cfg);
T_BOOL apCfgUpdateByPrefix(const T_CHAR* prefix_token);

const T_INT32 apCfgGetCfgTableSize(void);
const ap_cfg_item_t* apCfgGetCfgTableList(void);


#ifdef __cplusplus
}
#endif

#endif

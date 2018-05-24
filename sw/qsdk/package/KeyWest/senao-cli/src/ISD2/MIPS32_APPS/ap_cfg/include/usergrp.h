#ifndef _USERGRP_H
#define _USERGRP_H

#include <sap_ostypes.h>
#include <apcfg.h>

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------------------*/
#define MAX_LOGIN_ID       20
#define MAX_LOGIN_PWD      20
#define MIN_LOGIN_PWD       3
#define MAX_USER_NAME       20
#define MAX_USER_DESC      20
#define MAX_SIP_AUTH_ID     20
#define MAX_SIP_AUTH_PWD    20
#define MIN_SIP_AUTH_PWD    1
#define MAX_EMAIL           25
#define MAX_PHONE_DIGITALS  3
#define VENDORID_LEN       15
/*---------------------------------------*/
#define MAX_GRP_NAME        20
#define MAX_GRP_DESC        20
/*---------------------------------------*/
//mhchen:2007-0227;modify MAX_USER_NUM;PBX default is 10
#define MAX_USER_NUM          10
#define MAX_GROUP_NUM         6
#define MAX_CODECS            3
/*---------------------------------------*/

#define USRFT_MAX   3


#define USRFT_HAS_VOICEMAIL   (1 << 0)
#define USRFT_HAS_PARKCALLS   (1 << 1)
// #define USRFT_HAS_DIALOUT     (1 << 2)


/*-----------------------------------------------*/
//#define USERINFO_PATTERN "\"%d\",\"%d\",\"%s\",\"%s\",\"%s\",\"%s\","
//#define USERINFOSIP_PATTERN "\"%s\",\"%s\",\"%d\","
//#define USERINFOBELONG_GROUP_PATTERN "\"%d,%d,%d,%d,%d,%d\","
//#define USERINFO_CODECS_PATTERN "\"%d,%d,%d,%d,%d,%d\","
//#define USERINFOCALL_PATTERN "\"%03d\",\"%03d\",\"%03d\",\"%s\",\"0x%03x\""

/*-----------------------------------------------*/
//#define GROUPINFO_PATTERN  "\"%d\",\"%d\",\"%s\",\"%s\","
//#define GROUPINFO_MEMBERS_PATTERN "\"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\","
//#define GROUPINFO_FUNCTION_PATTRTN "\"0x%03x\""
/*-----------------------------------------------*/
#define TEMP_FUNCTION_PATTRTN "0x%03x"

/*-----------------------------------------------*/
#define USERINFO_PATTERN_ITEMS                  6
#define USERINFOSIP_PATTERN_ITEMS               3
#define USERINFOBELONG_GROUP_PATTERN_ITEMS      6
#define USERINFO_CODECS_PATTERN_ITEMS           6
#define USERINFOCALL_PATTERN_ITEMS              5

/*jaykung 20060817 for block list*/
#define MAX_BLACK_LIST 10
#define MAX_BLOCK_NUMBER 10

typedef struct _userinfo
{
    T_UINT8     isEnable                   __ATTRIBUTE_PACKED__;
    T_UINT8     uId                        __ATTRIBUTE_PACKED__;    /* user ID, 1~MAX_USER_NUM*/
    T_CHAR      sLoginId[MAX_LOGIN_ID+1]   __ATTRIBUTE_PACKED__;    /* user login name*/
    T_CHAR      sLoginPwd[MAX_LOGIN_PWD+1] __ATTRIBUTE_PACKED__;    /* user login password*/
    T_CHAR      sUserName[MAX_USER_NAME+1] __ATTRIBUTE_PACKED__;    /*calling User Name */
    T_CHAR      sDiscription[MAX_USER_DESC+1]      __ATTRIBUTE_PACKED__;    /* user discription*/
    T_CHAR      sSipAuthName[MAX_SIP_AUTH_ID+1]    __ATTRIBUTE_PACKED__;    /* SIP authentication Name */
    T_CHAR      sSipAuthPasswd[MAX_SIP_AUTH_PWD+1] __ATTRIBUTE_PACKED__;    /* SIP authentication password */
    //jaykung 20060809 for auto-provision
    SIP_GETAUTH_TYPE iSipGetAuthType               __ATTRIBUTE_PACKED__;    /* way of getting auth password*/
    //T_CHAR      mac[12]                            __ATTRIBUTE_PACKED__;    /*for auto-provision*/
    T_UINT8      mac[MAX_MAC_ADDR_LEN_IN_BYTE]     __ATTRIBUTE_PACKED__;    /*for auto-provision*/
    T_CHAR      sVendorID[VENDORID_LEN+1]          __ATTRIBUTE_PACKED__;    /*for auto-provision*/
    T_UINT8     uBelong2Group                      __ATTRIBUTE_PACKED__;    /* belong to group number 0 ~ 8 */
    T_UINT8     uPreferCodecs[MAX_CODECS]          __ATTRIBUTE_PACKED__;  
    T_UINT16    uSipExtNumber                      __ATTRIBUTE_PACKED__;    /*000 to 999, three digits */
    /*foward type please refer apcfg_si688h enum FORWARDING_TYPE */
    FORWARDING_TYPE isEnableForward                __ATTRIBUTE_PACKED__;    /* forward type*/
#if 0
    T_CHAR    sBlindForwardNumber[MAX_LENGTH_TELNUM]  __ATTRIBUTE_PACKED__;    /*000 to 999, three digits */
    T_CHAR    sForwardNumberOnBusy[MAX_LENGTH_TELNUM] __ATTRIBUTE_PACKED__;    /*000 to 999, three digits */
    T_CHAR    sAllForwardNumber[MAX_LENGTH_TELNUM]    __ATTRIBUTE_PACKED__;    /*000 to 999, three digits */
    T_CHAR    sFollowmeNumber[MAX_FOLLOWME_NUM][MAX_LENGTH_TELNUM] __ATTRIBUTE_PACKED__;  /*000 to 999, three digits */
#else
    //T_UINT16    uBlindForwardNumber                   __ATTRIBUTE_PACKED__;    /*000 to 999, three digits */
    //T_UINT16    uForwardNumberOnBusy                  __ATTRIBUTE_PACKED__;    /*000 to 999, three digits */
 	//T_UINT16	uAllForwardNumber                     __ATTRIBUTE_PACKED__;	   /*000 to 999, three digits */
    //T_UINT16    uFollowmeNumber[MAX_FOLLOWME_NUM]     __ATTRIBUTE_PACKED__;    /*000 to 999, three digits */
#endif
    T_CHAR      email[MAX_EMAIL]                      __ATTRIBUTE_PACKED__;    /* User's email */
    //T_UINT8    uFunctions                             __ATTRIBUTE_PACKED__;    /* ref to USRFT_HAS_XXX */
}__S_ATTRIBUTE_PACKED__ userinfo_t;

/*jaykung 20070521 forwarding number*/
typedef struct _fw_number_for_user
{
    FORWARDING_TYPE isEnableForward                   __ATTRIBUTE_PACKED__;    /* forward type*/
    T_CHAR    sBlindForwardNumber[MAX_LENGTH_TELNUM]  __ATTRIBUTE_PACKED__;
    T_CHAR    sForwardNumberOnBusy[MAX_LENGTH_TELNUM] __ATTRIBUTE_PACKED__;
    T_CHAR    sAllForwardNumber[MAX_LENGTH_TELNUM]    __ATTRIBUTE_PACKED__;
    T_CHAR    sFollowmeNumber[MAX_FOLLOWME_NUM][MAX_LENGTH_TELNUM] __ATTRIBUTE_PACKED__;
}__S_ATTRIBUTE_PACKED__ fw_number_for_user_t;

/*jaykung 20060817 for block list*/
typedef struct _blacklist_for_group
{
     T_UINT8   isEnable                         __ATTRIBUTE_PACKED__;
     BLACKLIST_TYPE   matchType[MAX_BLACK_LIST] __ATTRIBUTE_PACKED__; /*match type*/
     T_CHAR    number[MAX_BLACK_LIST][MAX_BLOCK_NUMBER] __ATTRIBUTE_PACKED__;      /* block number */
}__S_ATTRIBUTE_PACKED__ blacklist_for_group_t;

typedef struct _grpinfo
{
    T_BOOL      isEnable                     __ATTRIBUTE_PACKED__;
    T_UINT8     uId                          __ATTRIBUTE_PACKED__;     /* group ID , 1~MAX_GROUP_NUM*/
    T_CHAR      sName[MAX_GRP_NAME+1]        __ATTRIBUTE_PACKED__;     /* group name*/
    T_CHAR      sDiscription[MAX_GRP_DESC+1] __ATTRIBUTE_PACKED__;     /* group discription*/
    T_UINT8     uMembers[MAX_USER_NUM]       __ATTRIBUTE_PACKED__;     /* who is in this group */
    T_UINT16    uSipExtNumber                __ATTRIBUTE_PACKED__;     /*000 to 999, three digits */    
    T_UINT8     uFunctions                   __ATTRIBUTE_PACKED__;     /* ref to USRFT_HAS_XXX */
    /*jaykung 20060817 for block list*/
    T_BOOL      isEnableBlackList            __ATTRIBUTE_PACKED__;     /*enable Block list*/
}__S_ATTRIBUTE_PACKED__ grpinfo_t;



/*Function*/
T_BOOL userLoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL getUserValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setUserValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defUserValue(ap_cfg_item_t* item);

T_BOOL groupLoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL getGroupValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setGroupValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defGrpValue(ap_cfg_item_t* item);

/*forwarding function*/
T_BOOL userCFLoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL getUserCFValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setUserCFValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defUserCFValue(ap_cfg_item_t* item);


/*jaykung 20060822 blacklist for each group*/
T_BOOL getGroupBlackListValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setGroupBlackListValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defGrpBlacklistValue(ap_cfg_item_t* item);

T_BOOL usergrpDelUser(T_INT32 idx);
T_BOOL usergrpDelGroup(T_INT32 idx);
T_BOOL usergrpSetUserBelongGroups(userinfo_t *userinfo, T_CHAR *grpIdx);
T_BOOL usergrpSetUserBelongGroup(userinfo_t *userinfo, T_INT32 grpIdx);
T_BOOL usergrpCheckExt(T_INT32 ext);

#ifdef __cplusplus
}
#endif

#endif

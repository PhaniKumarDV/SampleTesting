#ifndef _WEB_ACCOUNT_H_
#define _WEB_ACCOUNT_H_

#include <sap_ostypes.h>
#include <apcfg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_WEB_ACCOUNTS_NUM	5
#define MAX_ACCOUNT_NAME_LEN 10
#define MAX_ACCOUNT_PW_LEN 31

enum {
	LEVEL_GUEST=1,
	LEVEL_MANUFACTURE,
	LEVEL_NORMAL_USER,
	LEVEL_ADMINISTRATOR,
	LEVEL_VENDOR_ADMINISTRATOR,
	LEVEL_SYSTEM_MAINTAINER
};

/*adam 2009-04-23, for WEB accounts*/
typedef struct _webAccount
{
    T_UINT8	isEnable                        __ATTRIBUTE_PACKED__;
    T_UINT8	uId                             __ATTRIBUTE_PACKED__;
    T_CHAR	name[MAX_ACCOUNT_NAME_LEN+1]    __ATTRIBUTE_PACKED__;
    T_CHAR	password[MAX_ACCOUNT_PW_LEN+1] 	__ATTRIBUTE_PACKED__;
    T_UINT8	level                           __ATTRIBUTE_PACKED__;
    T_CHAR  padding[1]                      __ATTRIBUTE_PACKED__;
}__S_ATTRIBUTE_PACKED__ webAccount_t;

T_BOOL webAccountLoadDefault(T_VOID* dst, T_INT32 index);
T_BOOL webAccountDoCheck(T_VOID* dst, T_INT32 index);
T_BOOL getWebAccount(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setWebAccount(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defWebAccountValue(ap_cfg_item_t* item);

#ifdef __cplusplus
}
#endif

#endif

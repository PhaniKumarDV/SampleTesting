#ifndef _SYSTEM_INFO_H
#define _SYSTEM_INFO_H

#include <sap_ostypes.h>
#include <apcfg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_RADIO_VALUE	8
#define MAX_ETH_PURPOSE	2

typedef struct _systemInfo_t 
{
    //T_UINT8  isEnable __ATTRIBUTE_PACKED__;
    //T_UINT8  dummy    __ATTRIBUTE_PACKED__;
    /*It is updated by fwmanager and referenced by webup/MMI */
    T_UINT32 ifwupgResult __ATTRIBUTE_PACKED__;
     
}__S_ATTRIBUTE_PACKED__ systemInfo_t ;


T_BOOL getSysInfoValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setSysInfoValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defSysInfoValue(ap_cfg_item_t* item);
int getSysOperationMode();
void setSysOperationModeInfo(T_INT32 sysmode);

#if HAS_RADIO_SETTING
T_INT32  Radio2SysOpmode(T_VOID);
T_VOID	setMultipleRadioSysOperationMode(T_VOID);
#endif

#ifdef __cplusplus
}
#endif

#endif


#ifndef _DHCP_MAC_TO_IP_H_
#define _DHCP_MAC_TO_IP_H_

#include <sap_ostypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/*jaykung 20060810 for dhpc fixed ip to specific mac*/
typedef struct _dhcpMacToIp
{
    T_UINT8  	isEnable                        __ATTRIBUTE_PACKED__;
    T_UINT8 	uId                             __ATTRIBUTE_PACKED__;
    T_UINT32 	ip                              __ATTRIBUTE_PACKED__;
    //T_CHAR  	mac[12] __ATTRIBUTE_PACKED__;
    T_UINT8 	mac[MAX_MAC_ADDR_LEN_IN_BYTE]   __ATTRIBUTE_PACKED__;
    T_CHAR      padding[1]                      __ATTRIBUTE_PACKED__;

	T_CHAR		pcName[20+1]                    __ATTRIBUTE_PACKED__;
	T_UINT8		iframe                          __ATTRIBUTE_PACKED__;
} __S_ATTRIBUTE_PACKED__ dhcpMacToIp_t;


T_BOOL dhcpMacToIpLoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL dhcpMacToIpDoCheck(T_VOID* dst,T_INT32 index);
T_BOOL getMacToIpValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setMacToIpValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defDhcpdMacToIp(ap_cfg_item_t* item);
T_BOOL checkPoolRangeOverlap(T_INT32 startIP,T_INT32 endIP,T_INT32 index);
T_BOOL checkPoolRangeWasChanged(T_INT32 index,T_INT32 startIP,T_INT32 endIP);
#ifdef __cplusplus
}
#endif

#endif

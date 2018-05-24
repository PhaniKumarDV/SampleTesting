#ifndef _ROUTINGINFO_H
#define _ROUTINGINFO_H

#include <sap_ostypes.h>
#include <apcfg.h>

#ifdef __cplusplus
extern "C" {
#endif

enum
{
	ROUTE_NONE=0,
	ROUTE_ADD,
	ROUTE_DEL,
	ROUTE_DONE,
};

typedef struct _routingInfo
{
	T_UINT8     isEnable                       __ATTRIBUTE_PACKED__;
#if HAS_FLETS_PPPOE
	T_UINT8     isActive                       __ATTRIBUTE_PACKED__;
#endif
	T_UINT8     uId                            __ATTRIBUTE_PACKED__;
	T_UINT8     isDefaultRule                  __ATTRIBUTE_PACKED__; //if this entry is for default gateway, what we need is gateway address.
	T_UINT8     hops                           __ATTRIBUTE_PACKED__;
#if HAS_STATICROUTING_METRIC
	T_UINT8     metric                         __ATTRIBUTE_PACKED__;
#endif
#if HAS_STATICROUTING_NAME	
	T_CHAR      name[MAX_STATICROUTING_NAME+1] __ATTRIBUTE_PACKED__;
#endif	
	T_UINT32    lanAddr                        __ATTRIBUTE_PACKED__;
	T_UINT32    mask                           __ATTRIBUTE_PACKED__;
	T_UINT32    gatewayAddr                    __ATTRIBUTE_PACKED__;
	T_UINT8     interface                      __ATTRIBUTE_PACKED__;
	T_UINT8     type                           __ATTRIBUTE_PACKED__;
}__S_ATTRIBUTE_PACKED__ routingInfo_t;

T_BOOL staticRoutingLoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL staticRoutingDoCheck(T_VOID* dst,T_INT32 index);
T_BOOL getStaticRoutingValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setStaticRoutingValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defStaticRouting(ap_cfg_item_t* item);

#ifdef HAS_PPPOE_JAPAN

typedef struct _DualWanRoutingInfo
{
	T_UINT8     uId                            __ATTRIBUTE_PACKED__;	
	T_UINT8     isEnable                       __ATTRIBUTE_PACKED__;	
	T_UINT8     sessionNum                     __ATTRIBUTE_PACKED__;
	T_CHAR      domainname[20+1]               __ATTRIBUTE_PACKED__;
	T_UINT32    startIP                        __ATTRIBUTE_PACKED__;
	T_UINT32    endIP                          __ATTRIBUTE_PACKED__;
	T_UINT32    mask                           __ATTRIBUTE_PACKED__;
	T_UINT16    startPort                      __ATTRIBUTE_PACKED__;
	T_UINT16    endPort                        __ATTRIBUTE_PACKED__;
	T_UINT8     protocol                       __ATTRIBUTE_PACKED__;
    T_CHAR   	padding[1]                     __ATTRIBUTE_PACKED__;
}__S_ATTRIBUTE_PACKED__ DualWanRoutingInfo_t;

T_BOOL DualWanRoutingLoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL DualWanRoutingDoCheck(T_VOID* dst,T_INT32 index);
T_BOOL getDualWanRoutingValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setDualWanRoutingValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defDualWanRouting(ap_cfg_item_t* item);

#endif // HAS_PPPOE_JAPAN

#if HAS_DOMAIN_ROUTING

typedef struct _DomainRoutingInfo
{
	T_UINT8     uId                            __ATTRIBUTE_PACKED__;	
	T_UINT8     isEnable                       __ATTRIBUTE_PACKED__;	
	T_UINT8     isActive                       __ATTRIBUTE_PACKED__;	
	T_CHAR      domainname[32+1]               __ATTRIBUTE_PACKED__;
}__S_ATTRIBUTE_PACKED__ DomainRoutingInfo_t;

T_BOOL DomainRoutingLoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL DomainRoutingDoCheck(T_VOID* dst,T_INT32 index);
T_BOOL getDomainRoutingValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setDomainRoutingValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defDomainRouting(ap_cfg_item_t* item);

#endif // HAS_DOMAIN_ROUTING

#ifdef __cplusplus
}
#endif

#endif

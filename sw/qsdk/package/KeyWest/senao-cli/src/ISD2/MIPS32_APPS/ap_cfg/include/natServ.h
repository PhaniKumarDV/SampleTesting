#ifndef _NAT_SERVER_H_
#define _NAT_SERVER_H_

#include <sap_ostypes.h>
#include <apcfg.h>

#ifdef __cplusplus
extern "C" {
#endif

#if HAS_ADV_NAT
#define NAT_VSERVER_TCP_PORT_LIST_MAX 12
#define NAT_VSERVER_UDP_PORT_LIST_MAX 12
#endif

/*jaykung 1006-05-08, for NAT Virtual server*/
typedef struct _natvserver
{
//0,Virtual Server01,100,200,0,10,80,0,09,00,17,00,0x1111111"
    T_UINT8  isEnable                      __ATTRIBUTE_PACKED__;
    T_UINT8  isActive                      __ATTRIBUTE_PACKED__;
    T_UINT8  uId                           __ATTRIBUTE_PACKED__;
    T_UINT8  protocolType                  __ATTRIBUTE_PACKED__;
	T_CHAR   serName[NAT_VSERVER_NAME_MAX] __ATTRIBUTE_PACKED__;
    T_UINT16 lowerBound                    __ATTRIBUTE_PACKED__;
    T_UINT16 upperBound                    __ATTRIBUTE_PACKED__;
    T_UINT32 ipAddr                        __ATTRIBUTE_PACKED__;
    T_UINT16 lowerFwPort                   __ATTRIBUTE_PACKED__;
    T_UINT16 upperFwPort                   __ATTRIBUTE_PACKED__;
    T_UINT8  scheduleId                    __ATTRIBUTE_PACKED__;
    T_UINT8  inboundFilterId               __ATTRIBUTE_PACKED__; // For no inbound filter case, this parameter is a padding.
    T_UINT8  otherProtocol                 __ATTRIBUTE_PACKED__; //protocoltype:number(0~255)
    T_UINT8  padding[1]                    __ATTRIBUTE_PACKED__;
}__S_ATTRIBUTE_PACKED__ natvserver_t;

#if HAS_ADV_NAT
/* Nelson 2010-0920, for Adv NAT port forwarding */
typedef struct _natvserver_adv
{
//0,Virtual Server01,100,200,0,10,80,0,09,00,17,00,0x1111111"
    T_UINT8  isEnable                                          __ATTRIBUTE_PACKED__;
    T_UINT8  isActive                                          __ATTRIBUTE_PACKED__;
    T_UINT8  uId                                               __ATTRIBUTE_PACKED__;
	T_UINT8  protocolType                                      __ATTRIBUTE_PACKED__;
    T_CHAR   serName[NAT_PORTFORWARD_NAME_MAX]                 __ATTRIBUTE_PACKED__;
    T_UINT32 ipAddr                                            __ATTRIBUTE_PACKED__;
	T_UINT8  scheduleId                                        __ATTRIBUTE_PACKED__;
	T_UINT8  inboundFilterId                                   __ATTRIBUTE_PACKED__;
}__S_ATTRIBUTE_PACKED__ natvserver_adv_t;

typedef struct _natvserver_adv_ext
{
	T_UINT16 tcpPortList[NAT_VSERVER_TCP_PORT_LIST_MAX]     __ATTRIBUTE_PACKED__;/* TCP port pairwise : 1000-1002, 2010-2050, ...*/
    T_UINT16 udpPortList[NAT_VSERVER_UDP_PORT_LIST_MAX]     __ATTRIBUTE_PACKED__;/* UDP Port pairwise : 1000-1002, 2010-2050, ...*/
}__S_ATTRIBUTE_PACKED__ natvserver_adv_ext_t;
#endif

T_BOOL natVServerLoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL natVServerDoCheck(T_VOID* dst,T_INT32 index);
T_BOOL getNatVServer(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setNatVServer(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defNatServValue(ap_cfg_item_t* item);
#if HAS_ADV_NAT
T_BOOL advNatVServerLoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL advNatVServerDoCheck(T_VOID* dst,T_INT32 index);
T_BOOL getAdvNatVServer(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setAdvNatVServer(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defAdvNatServValue(ap_cfg_item_t* item);
T_BOOL advNatVServerExtLoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL advNatVServerExtDoCheck(T_VOID* dst,T_INT32 index);
T_BOOL getAdvNatVServerExt(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setAdvNatVServerExt(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defAdvNatServExtValue(ap_cfg_item_t* item);
#endif


#ifdef __cplusplus
}
#endif

#endif

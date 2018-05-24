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
;    File    : filter.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;      
;*****************************************************************************/
#ifndef _APCFG_FILTER_H_
#define _APCFG_FILTER_H_


/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <sap_ostypes.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
#define MAC_FILTER_COMMAND_LENGTH	16
#define IP_FILTER_DESCRIPTION_MAX	16
#if HAS_ACCESS_CONTROL
#define ACCESS_CONTROL_DESCRIPTION_MAX	16
#endif
#if HAS_ACCESS_CONTROL_BELKIN
#define ACCESS_CONTROL_DEVICENAME_MAX	24
#endif
#if HAS_PARENTAL_CONTROL
#define PARENTAL_CONTROL_DESCRIPTION_MAX	15
#define PARENTAL_CONTROL_DEVICENAME_MAX		17
#endif

/* MAC filter work on serval SSID by using BitMap  */
#define MAC_FLT_SSIDMAP_1    (1<<0)
#define MAC_FLT_SSIDMAP_2    (1<<1)
#define MAC_FLT_SSIDMAP_3    (1<<2)
#define MAC_FLT_SSIDMAP_4    (1<<3)
#define MAC_FLT_SSIDMAP_5    (1<<4)
#define MAC_FLT_SSIDMAP_6    (1<<5)
#define MAC_FLT_SSIDMAP_7    (1<<6)
#define MAC_FLT_SSIDMAP_8    (1<<7)
#define MAC_FLT_SSIDMAP_9    (1<<8)
#define MAC_FLT_SSIDMAP_10   (1<<9)
#define MAC_FLT_SSIDMAP_11   (1<<10)
#define MAC_FLT_SSIDMAP_12   (1<<11)
#define MAC_FLT_SSIDMAP_13   (1<<12)
#define MAC_FLT_SSIDMAP_14   (1<<13)
#define MAC_FLT_SSIDMAP_15   (1<<14)
#define MAC_FLT_SSIDMAP_16   (1<<15)
#define MAC_FLT_SSIDMAP_ALL  (0xFFFF)

#if HAS_ACCESS_CONTROL_BELKIN
/* 0:None 1:DNS 2:Ping 3:HTTP 4:HTTPS 5:FTP 6:POP3 7:IMAP 8:SMTP 9:NNTP 10:Telnet 11:SNMP 12:TFTP 13:IKE 14:User-define */
#define AC_SERVICE_NONE 		0
#define AC_SERVICE_DNS          1
#define AC_SERVICE_PING         2
#define AC_SERVICE_HTTP         3
#define AC_SERVICE_HTTPS        4
#define AC_SERVICE_FTP          5
#define AC_SERVICE_POP3         6
#define AC_SERVICE_IMAP         7
#define AC_SERVICE_SMTP         8
#define AC_SERVICE_NNTP         9
#define AC_SERVICE_TELNET       10
#define AC_SERVICE_SNMP         11
#define AC_SERVICE_TFTP         12
#define AC_SERVICE_IKE          13
#define AC_SERVICE_USERDEFINE   14
/* 0:TCP 1:UDP 2:TCP&UDP 3:ICMP 4:IGMP 5:None */
#define AC_PROTOCOL_TCP      16
#define AC_PROTOCOL_UDP      17
#define AC_PROTOCOL_TCPUDP   254
#define AC_PROTOCOL_ICMP     1
#define AC_PROTOCOL_IGMP     2
#define AC_PROTOCOL_NONE     0
#endif
/*-------------------------------------------------------------------------*/
/*                           enum & struct                                 */
/*-------------------------------------------------------------------------*/
/*jaykung for l7 filtering*/
typedef struct _l7filtering
{
    T_BOOL  isEnable;
    T_INT32 scheduleId;
} l7filtering_t;

/*cfho 03-0716, for IP filtering*/
typedef struct _ipfiltering
{
    T_UINT8  isEnable       __ATTRIBUTE_PACKED__;
    T_UINT8  isActive       __ATTRIBUTE_PACKED__;
    T_UINT8  uId            __ATTRIBUTE_PACKED__;
    T_UINT8  protocolType   __ATTRIBUTE_PACKED__;
    T_UINT16 lowerBound     __ATTRIBUTE_PACKED__;
    T_UINT16 upperBound     __ATTRIBUTE_PACKED__;
    T_UINT8  isPortEnable   __ATTRIBUTE_PACKED__;
    T_UINT16 lowerBoundPort __ATTRIBUTE_PACKED__; /*if 0 means all ports*/
    T_UINT16 upperBoundPort __ATTRIBUTE_PACKED__;
    T_UINT8  scheduleId     __ATTRIBUTE_PACKED__;
    T_UINT32 serviceIdx     __ATTRIBUTE_PACKED__;
    T_CHAR   description[IP_FILTER_DESCRIPTION_MAX+1] __ATTRIBUTE_PACKED__;
    T_UINT32 type           __ATTRIBUTE_PACKED__;
} __S_ATTRIBUTE_PACKED__ ipfiltering_t;


/*cfho 2006-0427, for MAC filtering*/
typedef struct _macfiltering
{
    T_UINT8 isEnable        __ATTRIBUTE_PACKED__;
    T_UINT16 uId            __ATTRIBUTE_PACKED__;
    T_UINT8 mac[MAX_MAC_ADDR_LEN_IN_BYTE]        __ATTRIBUTE_PACKED__;
    T_UINT8 scheduleId      __ATTRIBUTE_PACKED__;
	T_CHAR  command[MAC_FILTER_COMMAND_LENGTH+1] __ATTRIBUTE_PACKED__;
    T_UINT16 ssidmap        __ATTRIBUTE_PACKED__;
	//T_UINT8 mac[MAX_MAC_ADDR_LEN];
	//daytime_t dt;
} __S_ATTRIBUTE_PACKED__ macfiltering_t;

#ifdef HAS_ACCESS_CONTROL
/*Nelson 2010-0924, for Access Control (D-Link)*/
typedef struct _access_control
{
	T_UINT8  isEnable                                          __ATTRIBUTE_PACKED__;
	T_UINT8  uId                                               __ATTRIBUTE_PACKED__;
	T_UINT8  ipfilterId                                        __ATTRIBUTE_PACKED__; /* first ipfilter id */
	T_UINT8  otherMachine                                      __ATTRIBUTE_PACKED__; /* other machine */
	T_UINT8  otherMachineIdx                                   __ATTRIBUTE_PACKED__; /* other machine index*/
	T_CHAR   policyName[ACCESS_CONTROL_DESCRIPTION_MAX+1]      __ATTRIBUTE_PACKED__; /* ploicy name */
	T_UINT8  filterType                                        __ATTRIBUTE_PACKED__; /* filtering method */
	T_UINT8  webFilter                                         __ATTRIBUTE_PACKED__; /* web filter */
	T_UINT8  portFilter                                        __ATTRIBUTE_PACKED__; /* port filter */
	T_UINT8  logging                                           __ATTRIBUTE_PACKED__; /* web access logging */
	T_UINT8  scheduleId                                        __ATTRIBUTE_PACKED__; /* schedule */
} __S_ATTRIBUTE_PACKED__ access_control_t;

typedef struct _ipfiltering_ac
{
    T_UINT8  isEnable       __ATTRIBUTE_PACKED__;
    T_UINT8  isActive       __ATTRIBUTE_PACKED__;
    T_UINT8  uId            __ATTRIBUTE_PACKED__;
    T_UINT8  protocolType   __ATTRIBUTE_PACKED__;
    T_UINT8  scheduleId     __ATTRIBUTE_PACKED__;
    T_CHAR   description[IP_FILTER_DESCRIPTION_MAX+1] __ATTRIBUTE_PACKED__;
    T_UINT32 type           __ATTRIBUTE_PACKED__;
	T_UINT32 clientIp     		 __ATTRIBUTE_PACKED__;
	T_UINT32 dst_lowerBoundIP	 __ATTRIBUTE_PACKED__;
	T_UINT32 dst_upperBoundIP	 __ATTRIBUTE_PACKED__;
	T_UINT16 dst_lowerBoundPort  __ATTRIBUTE_PACKED__;
	T_UINT16 dst_upperBoundPort  __ATTRIBUTE_PACKED__;
} __S_ATTRIBUTE_PACKED__ ipfiltering_ac_t;

typedef struct _access_control_ip
{
    T_UINT32 ip_list[NUM_ENTRY_PER_RULE] 	__ATTRIBUTE_PACKED__;
} __S_ATTRIBUTE_PACKED__ access_control_ip_t;

typedef struct _access_control_mac
{
    T_UINT8 mac_list[NUM_ENTRY_PER_RULE][MAX_MAC_ADDR_LEN_IN_BYTE]        __ATTRIBUTE_PACKED__;
} __S_ATTRIBUTE_PACKED__ access_control_mac_t;
#endif

#if HAS_ACCESS_CONTROL_BELKIN
/*Jason 2011-0304, for Access Control (BELKIN)*/
typedef struct _access_control_bk
{
	T_UINT8 isEnable                                          __ATTRIBUTE_PACKED__; /* display in web */
	T_UINT8 uId                                               __ATTRIBUTE_PACKED__;
	T_UINT8 isActive                                          __ATTRIBUTE_PACKED__; /* this rule is work or not */
	T_CHAR  deviceName[ACCESS_CONTROL_DEVICENAME_MAX+1]       __ATTRIBUTE_PACKED__; /* device name */
    T_UINT8	mac[MAX_MAC_ADDR_LEN_IN_BYTE]        			  __ATTRIBUTE_PACKED__; /* device mac */
	T_UINT8 restriction                                       __ATTRIBUTE_PACKED__; /* 0:allow 1:deny  */
	T_UINT8 scheduleId                                        __ATTRIBUTE_PACKED__; /* crossponding to SCHEDULE tok */
	T_UINT8 blockAllService                                   __ATTRIBUTE_PACKED__; /* 0:disable 1:enable */
	T_UINT8 blockAllURL                                       __ATTRIBUTE_PACKED__; /* 0:disable 1:enable */
	T_UINT8 landingPage                                       __ATTRIBUTE_PACKED__; /* 0:disable 1:enable */
	T_CHAR  padding[1]   									  __ATTRIBUTE_PACKED__;
} __S_ATTRIBUTE_PACKED__ access_control_bk_t;

typedef struct _access_control_service
{
    T_UINT8 service_list[NUM_AC_SERVICE_PER_RULE] 			  __ATTRIBUTE_PACKED__; /* 0:None 1:DNS 2:Ping 3:HTTP 4:HTTPS 5:FTP 6:POP3 7:IMAP 8:SMTP 9:NNTP 10:Telnet 11:SNMP 12:TFTP 13:IKE 14:User-define */
    T_UINT8 protocolType[NUM_AC_SERVICE_PER_RULE] 			  __ATTRIBUTE_PACKED__; /* 0:TCP 1:UDP 2:TCP&UDP 3:ICMP 4:IGMP 5:None */
	T_UINT16 lowerBoundPort[NUM_AC_SERVICE_PER_RULE]  		  __ATTRIBUTE_PACKED__; 
	T_UINT16 upperBoundPort[NUM_AC_SERVICE_PER_RULE]  	  	  __ATTRIBUTE_PACKED__;
} __S_ATTRIBUTE_PACKED__ access_control_service_t;

#endif

#if HAS_PARENTAL_CONTROL
typedef struct _parental_control
{
	T_UINT8  uId     										  __ATTRIBUTE_PACKED__;
	T_UINT8  isEnable                                         __ATTRIBUTE_PACKED__;
	T_UINT8  urlEnable                                      __ATTRIBUTE_PACKED__; /* 0:diable 1:enable  */
	T_UINT8  ipfilterEnable                                      __ATTRIBUTE_PACKED__; /* 0:diable 1:enable  */
	T_UINT8  logEnable                                      __ATTRIBUTE_PACKED__; /* 0:diable 1:enable  */
	T_UINT8  serviceEnable                                      __ATTRIBUTE_PACKED__; /* 0:diable 1:enable  */
	T_UINT8  filter_type                                       __ATTRIBUTE_PACKED__;
    T_UINT8  sch_restriction                                  __ATTRIBUTE_PACKED__;
	T_UINT8  url_restriction                                  __ATTRIBUTE_PACKED__; /* 0:allow 1:deny  */
    T_UINT8  service_restriction                              __ATTRIBUTE_PACKED__; /* 0:allow 1:deny  */
	T_CHAR  policyName[PARENTAL_CONTROL_DESCRIPTION_MAX+1]    __ATTRIBUTE_PACKED__; /* ploicy name */
	T_UINT8  logging                                          __ATTRIBUTE_PACKED__; /* web access logging */
	T_UINT8  isDefRule                                         __ATTRIBUTE_PACKED__; /* default rule */
} __S_ATTRIBUTE_PACKED__ parental_control_t;

typedef struct _parental_control_service
{
    T_UINT8 protocolType[NUM_PC_SERVICE_PER_TOKEN] 			__ATTRIBUTE_PACKED__; 
	T_UINT16 lowerBoundPort[NUM_PC_SERVICE_PER_TOKEN]  		__ATTRIBUTE_PACKED__; 
	T_UINT16 upperBoundPort[NUM_PC_SERVICE_PER_TOKEN]  	  	__ATTRIBUTE_PACKED__;
} __S_ATTRIBUTE_PACKED__ parental_control_service_t;

typedef struct _parental_control_ip
{
	T_CHAR  description[NUM_PC_IP_PER_TOKEN] [PARENTAL_CONTROL_DESCRIPTION_MAX+1]      __ATTRIBUTE_PACKED__;
	T_UINT32 lowerBoundIP[NUM_PC_IP_PER_TOKEN]  		__ATTRIBUTE_PACKED__; 
	T_UINT32 upperBoundIP[NUM_PC_IP_PER_TOKEN]  	  	__ATTRIBUTE_PACKED__;
} __S_ATTRIBUTE_PACKED__ parental_control_ip_t;

typedef struct _parental_control_mac
{
	T_CHAR  deviceName[NUM_PC_MAC_PER_TOKEN] [PARENTAL_CONTROL_DEVICENAME_MAX+1]      __ATTRIBUTE_PACKED__;
	T_UINT8 mac[NUM_PC_MAC_PER_TOKEN] [MAX_MAC_ADDR_LEN_IN_BYTE]        __ATTRIBUTE_PACKED__;
} __S_ATTRIBUTE_PACKED__ parental_control_mac_t;
#endif

/*-------------------------------------------------------------------------*/
/*                           FUNCTIONS                                     */
/*-------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

T_BOOL getIpFilter(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setIpFilter(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defIpFilterValue(ap_cfg_item_t* item);
T_BOOL getMacFilter(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setMacFilter(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defMacFilterValue(ap_cfg_item_t* item);
T_BOOL getL7Filter(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setL7Filter(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL checkWlanMacFilterValid(const T_CHAR *sMac, T_INT32 uId);
T_BOOL checkLanMacFilterValid(const T_CHAR *sMac, T_INT32 uId);
T_BOOL macFilterLoadDefault(T_VOID* dst, T_INT32 index);
T_BOOL ipFilterLoadDefault(T_VOID* dst, T_INT32 index);
#ifdef HAS_ACCESS_CONTROL
T_BOOL accCtrlIpFilterLoadDefault(T_VOID* dst, T_INT32 index);
T_BOOL accCtrlIpFilterDoCheck(T_VOID* dst, T_INT32 index);
T_BOOL getAccCtrlIpFilter(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setAccCtrlIpFilter(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defAccCtrlIpFilterValue(ap_cfg_item_t* item);

T_BOOL accessControlLoadDefault(T_VOID* dst, T_INT32 index);
T_BOOL accessControlDoCheck(T_VOID* dst, T_INT32 index);
T_BOOL getAccessControl(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setAccessControl(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defAccessControl(ap_cfg_item_t* item);
/* Access control IP */
T_BOOL getAccessControlIp(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setAccessControlIp(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defAccessControlIp(ap_cfg_item_t* item);
/* Access control MAC */
T_BOOL getAccessControlMac(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setAccessControlMac(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defAccessControlMac(ap_cfg_item_t* item);
#endif

#if HAS_ACCESS_CONTROL_BELKIN
T_BOOL accessControlLoadDefault_BK(T_VOID* dst, T_INT32 index);
T_BOOL accessControlDoCheck_BK(T_VOID* dst, T_INT32 index);
T_BOOL getAccessControl_BK(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setAccessControl_BK(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defAccessControl_BK(ap_cfg_item_t* item);
/* Access control Service */
T_BOOL accessControlServiceLoadDefault_BK(T_VOID* dst, T_INT32 index);
T_BOOL accessControlServiceDoCheck_BK(T_VOID* dst, T_INT32 index);
T_BOOL getAccessControlService_BK(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setAccessControlService_BK(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defAccessControlService_BK(ap_cfg_item_t* item);
#endif

#if HAS_PARENTAL_CONTROL
T_BOOL parentalControlLoadDefault(T_VOID* dst, T_INT32 index);
T_BOOL parentalControlDoCheck(T_VOID* dst, T_INT32 index);
T_BOOL getParentalControl(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setParentalControl(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defParentalControl(ap_cfg_item_t* item);
/* Parental control Service */
T_BOOL parentalControlServiceLoadDefault(T_VOID* dst, T_INT32 index);
T_BOOL parentalControlServiceDoCheck(T_VOID* dst, T_INT32 index);
T_BOOL getParentalControlService(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setParentalControlService(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defParentalControlService(ap_cfg_item_t* item);
/* Parental control IP */
T_BOOL parentalControlIpLoadDefault(T_VOID* dst, T_INT32 index);
T_BOOL ParentalControlIpDoCheck(T_VOID* dst, T_INT32 index);
T_BOOL getParentalControlIp(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setParentalControlIp(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defParentalControlIp(ap_cfg_item_t* item);
/* Parental control MAC */
T_BOOL parentalControlMacLoadDefault(T_VOID* dst, T_INT32 index);
T_BOOL ParentalControlMacDoCheck(T_VOID* dst, T_INT32 index);
T_BOOL getParentalControlMac(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setParentalControlMac(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defParentalControlMac(ap_cfg_item_t* item);
#endif

#ifdef __cplusplus
}
#endif

#endif

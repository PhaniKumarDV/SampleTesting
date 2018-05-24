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
;    Project : SI-688
;    Creator : 
;    File    : qossetting.h
;    Abstract: include file of the application profile.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       jay            2006-1226       Newly Create
;       Norkay         2007-11-13      Modify portQos struct
;*****************************************************************************/
#ifndef _QOSSETTING_H_
#define _QOSSETTING_H_
#include <sap_osapi.h>
#include <apcfg.h>
#include <tokens.h>
#include <gconfig.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
#define QOS_PORT_LIST_MAX           10
#if FOR_SITECOM
#define QOS_PORT_NAME_LENGTH        15
#elif HAS_ENGENIUS_STYLE_QOS
#define QOS_PORT_NAME_LENGTH        11
#else
#define QOS_PORT_NAME_LENGTH        11
#endif
#define NUM_QOS_PORT				16
#define QOS_PORT_STRING_BUFF_LENGTH 60

#if HAS_SUPPORT_UBICOM_STREAMENGINE
#define QOS_RULE_NAME_LENGTH        15
#endif
/*-------------------------------------------------------------------------*/
/*                           enum & struct                                 */
/*-------------------------------------------------------------------------*/

// because struct's total size > MAX_AP_VALUE_LEN = 100, we divid to A and B.
typedef struct _QosPort_A
{
    T_UINT8   isEnable      __ATTRIBUTE_PACKED__;
    T_UINT8   isActive 		__ATTRIBUTE_PACKED__;
    T_UINT8   uId           __ATTRIBUTE_PACKED__;
    T_UINT8   priority      __ATTRIBUTE_PACKED__;
    T_UINT8   bwType        __ATTRIBUTE_PACKED__;   // Upload, Download
    T_UINT32  bandwidth_min __ATTRIBUTE_PACKED__;   // kbps Guarantee
    T_UINT32  bandwidth_max __ATTRIBUTE_PACKED__;   // kbps Max
    T_UINT8   trafficType   __ATTRIBUTE_PACKED__;   // None, SMTP, HTTP, POP3, FTP
    T_UINT8   protocol      __ATTRIBUTE_PACKED__;   // TCP, UDP
    T_UINT32  localIpFrom   __ATTRIBUTE_PACKED__;   // Local IP Start
    T_UINT32  localIpTo     __ATTRIBUTE_PACKED__;   // Local IP End or Mask
    T_UINT32  remoteIpFrom  __ATTRIBUTE_PACKED__;   // Remote IP Start
    T_UINT32  remoteIpTo    __ATTRIBUTE_PACKED__;   // Remote IP End or Mask
#if HAS_ENGENIUS_STYLE_QOS || HAS_ZYXEL_STYLE_QOS
    T_UINT8   bandwidthType  __ATTRIBUTE_PACKED__;
    T_UINT16  remotePortFrom __ATTRIBUTE_PACKED__;
    T_UINT16  remotePortTo   __ATTRIBUTE_PACKED__;
#endif
    T_CHAR    ruleName[QOS_PORT_NAME_LENGTH+1] __ATTRIBUTE_PACKED__;

}__S_ATTRIBUTE_PACKED__ QosPort_A;

typedef struct _QosPort_B
{
    T_UINT8   mac[MAX_MAC_ADDR_LEN_IN_BYTE]      __ATTRIBUTE_PACKED__; // 20
    T_UINT16  localPortRange[QOS_PORT_LIST_MAX]  __ATTRIBUTE_PACKED__; // 20
    T_UINT16  remotePortRange[QOS_PORT_LIST_MAX] __ATTRIBUTE_PACKED__; // 20
}__S_ATTRIBUTE_PACKED__ QosPort_B;

T_BOOL portQosALoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL getPortQosA(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setPortQosA(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defPortQosAValue(ap_cfg_item_t* item);

T_BOOL portQosBLoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL getPortQosB(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setPortQosB(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defPortQosBValue(ap_cfg_item_t* item);

#include "netDevInfo.h"

struct qosElement
{
    int                enable;          /* enable or disable */
    int                type;            /* traffic type */
    int                number;          /* rule numbers */
    int                mark;            /* mark tag */
    int                protocol;        /* TCP or UDP */
    int                min;             /* bandwidth min */
    int                max;             /* bandwidth max */
    int                direct;          /* uplink or downlink */
    struct ipElement   localip;         /* local ip */
    struct ipElement   remoteip;        /* remote ip */
    struct portElement localport[5];    /* port numbers */
    struct portElement remoteport[5];   /* port numbers */
};

enum
{
    QOS_BANDWIDTH_TYPE_MIN=0,    /* min */
    QOS_BANDWIDTH_TYPE_MAX      /* max */
};

#if HAS_QOS_HWPORT

typedef struct _QosHwPort
{
    T_UINT8   isEnable      __ATTRIBUTE_PACKED__;
    T_UINT8   uId           __ATTRIBUTE_PACKED__;
    T_UINT8   priority      __ATTRIBUTE_PACKED__;
    T_UINT8   flow_control  __ATTRIBUTE_PACKED__;
    T_UINT32  ingress_rate  __ATTRIBUTE_PACKED__;
    T_UINT32  egress_rate   __ATTRIBUTE_PACKED__;
    
}__S_ATTRIBUTE_PACKED__ QosHwPort;

T_BOOL getQosHwPort(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setQosHwPort(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defQosHwPortValue(ap_cfg_item_t* item);
#if 0
enum
{
    QOS_HWPORT_PRIO0=0,  /* Reserved */
    QOS_HWPORT_PRIO1,    /* High */
    QOS_HWPORT_PRIO2,    /* Meduim */
    QOS_HWPORT_PRIO3     /* Low */
};
#else
enum
{
    QOS_HWPORT_PRIO3=0, /* Low */
    QOS_HWPORT_PRIO2,   /* Medium */
    QOS_HWPORT_PRIO1,   /* High */
    QOS_HWPORT_PRIO0,   /*Highest*/
};
#endif

#define QOS_HWPORT_PRIO_HIGH      QOS_HWPORT_PRIO1
#define QOS_HWPORT_PRIO_MEDIUM    QOS_HWPORT_PRIO2
#define QOS_HWPORT_PRIO_LOW       QOS_HWPORT_PRIO3

#endif /* HAS_QOS_HWPORT */

#if HAS_QOS_PRIO_QUEUE

enum
{
    QOS_APPS_PRIO0=0,    /* Reserved */
    QOS_APPS_PRIO1,      /* Reserved */
    QOS_APPS_PRIO2,      /* High */
    QOS_APPS_PRIO3,      /* Meduim */
    QOS_APPS_PRIO4,      /* Low */
    QOS_APPS_PRIO5
};

#define QOS_APPS_PRIO_HIGHEST   QOS_APPS_PRIO1
#define QOS_APPS_PRIO_HIGH      QOS_APPS_PRIO2
#define QOS_APPS_PRIO_MEDIUM    QOS_APPS_PRIO3
#define QOS_APPS_PRIO_LOW       QOS_APPS_PRIO4
 
#endif /* HAS_QOS_PRIO_QUEUE */

/* 2011/03/16 jason: support UBICOM Qos StreamEngine support(BELKIN first use)*/
#if HAS_SUPPORT_UBICOM_STREAMENGINE
typedef struct _QosStreamEngine
{
    T_UINT8   isEnable     	 	__ATTRIBUTE_PACKED__;
    T_UINT8   isActive 	   	 	__ATTRIBUTE_PACKED__;
    T_UINT8   uId          	 	__ATTRIBUTE_PACKED__;
	T_CHAR    ruleName[QOS_RULE_NAME_LENGTH+1] __ATTRIBUTE_PACKED__;    
    T_UINT8   priority      	__ATTRIBUTE_PACKED__;  // 1~255 , 255 is the lowest priority
	T_UINT16  protocol      	__ATTRIBUTE_PACKED__;  // Any, TCP, UDP, Both, ICMP, Other
    T_UINT32  localIpFrom   	__ATTRIBUTE_PACKED__;  // Local IP Start
    T_UINT32  localIpTo     	__ATTRIBUTE_PACKED__;  // Local IP End or Mask
    T_UINT16  localPortFrom 	__ATTRIBUTE_PACKED__;  // Local Port start
    T_UINT16  localPortTo   	__ATTRIBUTE_PACKED__;  // Local Port End
    T_UINT32  remoteIpFrom  	__ATTRIBUTE_PACKED__;  // Remote IP Start
    T_UINT32  remoteIpTo    	__ATTRIBUTE_PACKED__;  // Remote IP End or Mask
    T_UINT16  remotePortFrom 	__ATTRIBUTE_PACKED__;  // Remote Port start
    T_UINT16  remotePortTo   	__ATTRIBUTE_PACKED__;  // Remote Port End
	//T_CHAR    padding[1]   		__ATTRIBUTE_PACKED__;    
}__S_ATTRIBUTE_PACKED__ QosStreamEngine;

T_BOOL getStreamEngineQos(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setStreamEngineQos(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defStreamEngineQos(ap_cfg_item_t* item);
#endif

#if HAS_SUPPORT_UBICOM_WISH
typedef struct _QosWish
{
    T_UINT8   isEnable     	 	__ATTRIBUTE_PACKED__;
    T_UINT8   isActive 	   	 	__ATTRIBUTE_PACKED__;
    T_UINT8   uId          	 	__ATTRIBUTE_PACKED__;
    T_CHAR    ruleName[QOS_RULE_NAME_LENGTH+1] __ATTRIBUTE_PACKED__;    
    T_UINT8   priority      	__ATTRIBUTE_PACKED__;  // 1~255 , 255 is the lowest priority
    T_UINT16  protocol      	__ATTRIBUTE_PACKED__;  // Any, TCP, UDP, Both, ICMP, Other
    T_UINT32  localIpFrom   	__ATTRIBUTE_PACKED__;  // Local IP Start
    T_UINT32  localIpTo     	__ATTRIBUTE_PACKED__;  // Local IP End or Mask
    T_UINT16  localPortFrom 	__ATTRIBUTE_PACKED__;  // Local Port start
    T_UINT16  localPortTo   	__ATTRIBUTE_PACKED__;  // Local Port End
    T_UINT32  remoteIpFrom  	__ATTRIBUTE_PACKED__;  // Remote IP Start
    T_UINT32  remoteIpTo    	__ATTRIBUTE_PACKED__;  // Remote IP End or Mask
    T_UINT16  remotePortFrom 	__ATTRIBUTE_PACKED__;  // Remote Port start
    T_UINT16  remotePortTo   	__ATTRIBUTE_PACKED__;  // Remote Port End
	//T_CHAR    padding[1]   		__ATTRIBUTE_PACKED__;    
}__S_ATTRIBUTE_PACKED__ QosWish;

#endif
#endif

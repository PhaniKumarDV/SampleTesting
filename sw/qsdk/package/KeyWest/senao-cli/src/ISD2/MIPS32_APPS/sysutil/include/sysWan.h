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
;    File    : sysWan.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       	            2008-08-15       Newly Create
;*****************************************************************************/
#ifndef _SYSUTIL_WAN_H_
#define _SYSUTIL_WAN_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif 

#if HAS_WAN_MANAGER
#define PPPOE1_PIDFILE	"pppoe0"
#define PPTP1_PIDFILE	"pptp0"
#define PPPOE2_PIDFILE	"pppoe1"
#define PPTP2_PIDFILE	"pptp1"
#define M3G_PIDFILE     "m3g0"
#define L2TP1_PIDFILE   "l2tp0"
#define L2TP2_PIDFILE   "l2tp1"
#else
#define PPPOE1_PIDFILE	"pppoe0.conf-adsl0"
#define PPTP1_PIDFILE	"pptp0.conf-adsl0"
#define PPPOE2_PIDFILE	"pppoe1.conf-adsl1"
#define PPTP2_PIDFILE	"pptp1.conf-adsl1"
#define M3G_PIDFILE     "m3g.conf"
#define L2TP1_PIDFILE	"ppp-l2tp0"
#define L2TP2_PIDFILE	"ppp-l2tp1"
#endif


#define PPTP_DETECTOR_PATH  "/tmp/detector.pptp"
#define PPPOE_DETECTOR_PATH "/tmp/detector.pppoe"
#define DHCP_DETECTOR_PATH  "/tmp/detector.dhcp"

const char *sysGetPPPoEStatus(const T_CHAR *pidFile, const T_CHAR *interface);
int sysGetPppStatus(const T_CHAR *pidFile, const T_CHAR *interface);
T_INT32 sysWanDetection();
void sysDhcpEnable(int enable);

#if HAS_WAN_3G || HAS_WAN_XGP
enum PIN_STATUS
{
    PIN_STATUS_INIT = 0,
    PIN_STATUS_CODE,
    PIN_STATUS_OK,
    PIN_STATUS_FAIL,
    PIN_STATUS_NO_SIM,
    PIN_STATUS_WRONG,
    PIN_STATUS_PUK 
};
#endif

#if HAS_WAN_3G
enum NETWORK_MODE_TRANSLATION {
    NMT_UNKNOWN = 0,
    NMT_DONTCARE,
    NMT_GENERAL,
    NMT_ALPHA,
    NMT_ZTE,
    NMT_HUAWEI,
    NMT_NOVATEL,
    NMT_OPTION,
    NMT_SONY,
    NMT_SIERRA,
    NMT_ALCATEL,   /* [20100630 Andy Yu]: Alcatel has specified AT command for network type */
    NMT_EUSKALTEL, /* [20100707 Andy Yu]: Euskaltel has specified AT command for network type */
    NMT_NOVATEL_SP,
};

typedef enum {
    NETWORK_SYS_NOT_SUPPORT  = -1,
    NETWORK_SYS_NO_SERVICE   = 0,
    NETWORK_SYS_GSM          = 1,
    NETWORK_SYS_GPRS         = 2,
    NETWORK_SYS_EGPRS        = 3,
    NETWORK_SYS_WCDMA        = 4,
    NETWORK_SYS_HSDPA        = 5,
    NETWORK_SYS_HSUPA        = 6,
    NETWORK_SYS_HSDPA_HSUPA  = 7,

    /* HUAWEI HSPA+ */
    NETWORK_SYS_HSPA_PLUS    = 9,

    /* HITACHI DATA03 */
    NETWORK_SYS_IS_95A_95B   = 10,
    NETWORK_SYS_CDMA_1X      = 11,
    NETWORK_SYS_CDMA_EVDO_RO = 12,
    NETWORK_SYS_CDMA_EVDO_RA = 13,

    /* end of value */
    NETWORK_SYS_END

} NETWORK_SYS_MODE;

int sysWan3gStatus(void);
int sysWan3gSignal2(void);
int sysWan3gSignal(void);
int sysWan3gPinStatus(void);
#if !HAS_WAN_HIFULL_3G
int sysWan3gRssiToDbm(void);
const char *sysWan3gPinErrStr(int status);
int sysWan3gSpeed(void);
int sysWan3gCardDesc(T_CHAR *);
int sysWan3gNetReg(void);
#if HAS_KCODES_NETUSB
typedef enum {
    USB_OPM_AUTO = 0,
    USB_OPM_3G,
    USB_OPM_NETUSB
} USB_OP_MODE;
#define USBMODE_3G_FLAG "/tmp/usbmode.3g"
int sysWanUsb3gMode(void);
#endif /* HAS_KCODES_NETUSB */
#endif /* HAS_WAN_HIFULL_3G */

#define WAN_3G_STATUS_FILE        "/var/3gstatus"
#define WAN_3G_ISP_FILE           "/var/3gisp"
#define WAN_3G_SIGNAL_FILE        "/var/3gsignal"
#define WAN_3G_SPEED_FILE         "/var/3gdbps"
#define WAN_3G_PIN_FILE           "/var/pin.log"
#define WAN_3G_LED                "/var/3g.led"

#endif /* HAS_WAN_3G */

#if HAS_WAN_WIMAX
#define WAN_WIMAX_LOG  "/var/wimax%d.log"
#define WAN_WIMAX_LED  "/var/wimax.led"
int sysWanWimaxStatus(int index, int *signal, int *status);
#endif
#ifdef SUPPORT_WAN_SPEED_TEST
#define	WANSPEEDFILE	"/tmp/wan_uplink_speed.txt"
#define	WANSPEEDFILE_OLD	"/tmp/wan_uplink_speed_old.txt"
int sysWanSpeedTest(void);
int sysWanUplinkSpeed(void);
#endif
#ifdef __cplusplus
}
#endif 

#endif



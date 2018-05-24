#ifndef _USER_SCHEDULE_SETTING_H
#define _USER_SCHEDULE_SETTING_H

#include "sap_ostypes.h"

#if HAS_SCHEDULE_COREGA
#include <schedulesetting_cg.h>
#else

#ifdef __cplusplus
extern "C" {
#endif
 
/*web schedule setting function*/
T_BOOL scheduleCheck(T_VOID);
T_BOOL scheduleOpen(T_VOID);
T_BOOL scheduleClose(T_VOID);
T_BOOL scheduleReload(T_VOID);
T_INT32 ScheduleGetStatus(T_VOID);
T_VOID scheduleSetNtpTime(T_VOID);
T_VOID scheduleSetManualTime(T_VOID);

T_INT32 scheduleServiceState(T_VOID);
T_INT32 scheduleGetServiceEnable(T_VOID);
/*
T_BOOL IsScheduleHaveNum(T_VOID);
T_BOOL AddDefaultSchedule(T_VOID);
*/

enum
{
    SERVICE_POWER_SAVING=0,
    SERVICE_FIREWALL=1,
    SERVICE_WIRELESS_RADIO=2,
	SERVICE_WIRELESS_RADIO_ON=3,
    SERVICE_WIRELESS_RADIO_OFF=4,
	SERVICE_5G_WIRELESS_RADIO_ON=5,
    SERVICE_5G_WIRELESS_RADIO_OFF=6,
    SERVICE_EMAIL_ALERT=7,
    SERVICE_REBOOT=8,
	SERVICE_LED_OFF=9, 			// LAN, WLAN
	SERVICE_LAN_OFF=10,			// 
	SERVICE_LAN_LOW_RATE=11,	// 1000, 10/100 Mbps
	SERVICE_POWER_LED=12,	    // Power LED : ECO/NORMAL
	SERVICE_WLAN_LOW_RATE=13,	    // WLAN 1: [1x1] 0:[2x2]
    SERVICE_ACCESS_CONTROL=14,
	SERVICE_5G_WLAN_LOW_RATE=15,
	SERVICE_WAN_OFF=16,			// WAN OFF
    /* Count service number, do not add service below */
    SERVICE_NUMBERS
};

enum
{
    SCHEDULE_DISABLE=0x0,
    SCHEDULE_ENABLE=1,
    SCHEDULE_NTP_OK=2,
};


#ifdef __cplusplus
}
#endif

#endif /* HAS_SCHEDULE_COREGA */

#endif

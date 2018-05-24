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
;    File    : systime.c
;    Abstract: include file of the share memory APIs.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2006-0811       Newly Create
;*****************************************************************************/
#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_
/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sap_ostypes.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <time.h>
/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
#define TZ_ENV 		"TZ"
#define TZ_NAME 	"XYZ"
#define TZ_FILE 		"/etc/tz_file"          /*Save tz env*/
#define TZ_DATA_FILE 	"/etc/tz_data_file"		/*Save tz data*/

typedef enum {
		TYPE_UTC,
		TYPE_LOCALTIME
}TIME_TYPE;

typedef enum {TIMEFORMAT_STRING=0,TIMEFORMAT_SEMICOLON} TIMEFORMAT_TYPE;

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct _systime_t
{
    T_UINT16    year;
    T_UINT8     month;
    T_UINT8     day;
    T_UINT8     hour;
    T_UINT8     minute;
    T_UINT8     sec;
} systime_t;

int sysGettimeofday(struct timeval *tv, struct timezone *tz);
T_CHAR* getSystemUpTimeText(T_VOID);
T_CHAR* sysGetLocaltimeByItem(T_CHAR name);// jaykung 20060919
T_BOOL sysGetLocalSystime(systime_t *systime);

int systimeIsLeapYear(int y);
int systimeGetDaysInMonth(int year, int mon);
const char* systimeStringGet(time_t t, const char *fmt, char *dest, size_t len);

const char* systimeGetLocalTime(void);
void systimeSetDate(int year, int month, int day);
void systimeSetTime(int hour, int minute);
#if HAS_HW_RTC
void syncTimeToRTC();
#endif
T_BOOL sysTimeZoneSet(int id, int isDayLightSaving);
T_BOOL sysGetTimeZoneName(int id, T_CHAR* timezone);
int sysComputeDaysInMonth(int year, int month, int weeksInMonth, int daysInWeek);
time_t sysTimeGetWithTimeZone(time_t t, int id, int isDayLightSaving);
time_t sysTimeGetWithSimpleDaylightSaving(time_t t, int isDayLightSaving, int sm, int sd, int sh, int em, int ed, int eh);
time_t sysTimeGetWithStandardDaylightSaving(time_t t, int isDayLightSaving,
										  int sm, int sd, int sw, int sh, 
										  int em, int ed, int ew, int eh);
int sysGetDbiasWithDaylightSaving(time_t t, int id, int isDayLightSaving);
int sysGetBiasWithTimeZone(int id);
time_t sysTimeGetWithTimeZoneFromFile(time_t t);
int sysGetSecondsLocaltimeToUTC(time_t t, int hr, int mm, int id, int isDayLightSaving);
T_CHAR* transferTimeFormat(int second,TIMEFORMAT_TYPE timeFormat); //jaykung 20061018 ,add timeFormat 20080417
int schCalNextAvailableUpdateTime(int nextWday,int nextHour, int nextMin, int nextSec);//jaykung 20070305
struct timeval *sysTvsub(struct timeval *tv1, struct timeval *tv2); 
#ifdef __cplusplus
}
#endif 

#endif


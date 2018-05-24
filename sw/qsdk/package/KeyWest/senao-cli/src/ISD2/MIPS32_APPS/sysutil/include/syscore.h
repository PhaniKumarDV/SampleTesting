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
;    File    : system.c
;    Abstract: include file of the share memory APIs.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2006-0811       Newly Create
;*****************************************************************************/
#ifndef SYSCORE_H
#define SYSCORE_H

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <gconfig.h>
#include <sap_ostypes.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <time.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
#ifdef FOR_ATMEL902
#define MAX_COMMAND_LEN 256
#else
#define MAX_COMMAND_LEN 1024  /* cfho 2006-1205, change from 4096*/
#endif

#define TEST_SURVEY 0 /*kenny:2006-1219 ,to get information(pid memory stack)*/

#define PROC_NAME_MAX 20

#if HAS_LOG_LEVEL
#define SYSLOG_CONFIG_LEVEL_FILE "/tmp/loglevel"
#endif
enum {
        PROC_SYSCONFD,  /* sysconfd */
        PROC_MMI,       /* mmi */
        PROC_WPA_SUP     /* wpa_supplicant */
};

typedef struct _proc_name
{
    T_INT32 proc;                     /* process enum */
    T_CHAR procName[PROC_NAME_MAX];   /* process name */
} proc_name_t;

#ifdef TEST_SURVEY
typedef enum {
		STATUS_NAME,
		STATUS_MEM,
		STATUS_STACK,
		STATUS_ALL
}STATUS_INFORM;
#endif

typedef enum {
		LOGLEVEL_NORMAL=0,
		LOGLEVEL_ADVANCE,
		LOGLEVEL_DETAIL
}LOG_LEVEL;

#if HAS_ALERT_MAIL
enum alertmail_type {
	ALERT_RADIO_24G_OFF	   = 1,
	ALERT_RADIO_24G_ON     = (1<<1),
	ALERT_RADIO_5G_OFF     = (1<<2),
	ALERT_RADIO_5G_ON      = (1<<3),
	ALERT_MAIL_NOTIFY      = (1<<4),
	ALERT_SYSTEM_RESTART   = (1<<5),
	ALERT_SYSTEM_FAIL      = (1<<6),
	ALERT_SCHEDULE_TRIGGER = (1<<7),
	ALERT_MAIL_TEST	       = (1<<10)
};
#endif

#if defined (FOR_DLINK) || defined (FOR_BELKIN) || defined(HAS_PARENTAL_CONTROL)
enum LOG_FILTER
{
	SYSLOG_FILTER_SYSTEM	=1<<0,
	SYSLOG_FILTER_DEBUG 	=1<<1,
	SYSLOG_FILTER_ATTACK	=1<<2,
	SYSLOG_FILTER_DROP_PKTS	=1<<3,
	SYSLOG_FILTER_NOTICE	=1<<4
};
#endif

#ifdef __cplusplus
extern "C" {
#endif 

#if SYSUTIL_HAS_NO_SUPPORT_KERNEL_MODULES
#define MODPROBE(...)
#define INSMOD(...)
#define RMMOD(...)
#define FindKernModule(...)
#else
T_BOOL MODPROBE(const T_CHAR *inMod);
T_BOOL INSMOD(const T_CHAR *inMod);
T_BOOL RMMOD(const T_CHAR *modName);
T_BOOL FindKernModule(const T_CHAR *inMod);
#endif
T_INT32 SYSTEM(T_CHAR *format, ...);
T_VOID setSYSTEMFp(FILE *fp);
FILE *getSYSTEMFp(T_VOID);
T_INT32 SYSTEM_DBG(T_INT32 onOff);
T_VOID SYSTEM_DEEP_DBG(T_VOID);
T_INT32 sysinteract(T_CHAR *output, T_INT32 outputlen, T_CHAR *fmt, ...);
#if SYSUTIL_HAS_NO_TPRINTF
#define T_PRINTF(...)
#else
T_INT32 T_PRINTF(T_CHAR *format, ...);
#endif
T_INT32 SystemLog(int loglevel, T_CHAR *format, ...);
T_INT32 SnmpLog(T_CHAR *format, ...);


#ifdef __cplusplus
}
#endif 

#endif


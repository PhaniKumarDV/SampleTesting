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
;    File    : sysCommon.h
;    Abstract: include file of the share memory APIs.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2006-0825       Newly Create
;*****************************************************************************/
#ifndef _SYS_COMMON_H_
#define _SYS_COMMON_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sap_ostypes.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/

#define T_NUM_OF_ELEMENTS(x) (sizeof(x)/sizeof(x[0]))

#define MSG_MSGDUMP     (1<<1)
#define MSG_DBG         (1<<2)
#define MSG_INFO        (1<<3)
#define MSG_WARNING     (1<<4)
#define MSG_ERR         (1<<5)

#define MOD_WEB         (MSG_ERR<<1)
#define MOD_APCFG       (MSG_ERR<<2)
#define MOD_SYSCONFD    (MSG_ERR<<3)
#define MOD_ASTGEN      (MSG_ERR<<4)
#define MOD_SYSUTIL     (MSG_ERR<<5)

typedef struct __msgNameSet
{
    T_UINT32     id;
    const T_CHAR* text;
} msgNameSet;

#ifdef __cplusplus
extern "C" {
#endif 

T_VOID TRACE(T_INT32 level, T_CHAR *fmt, ...);

#ifdef __cplusplus
}
#endif 

#endif



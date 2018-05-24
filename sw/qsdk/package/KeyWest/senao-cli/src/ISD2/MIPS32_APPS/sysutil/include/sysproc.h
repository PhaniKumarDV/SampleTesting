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
;    File    : sysproc.h
;    Abstract: include file of the share memory APIs.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2006-0811       Newly Create
;*****************************************************************************/
#ifndef SYSPROC_H
#define SYSPROC_H

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <gconfig.h>
#include <stdio.h>
#include <stdlib.h>
#include <sap_ostypes.h>


#ifdef __cplusplus
extern "C" {
#endif 

T_BOOL KILLALL(const T_CHAR *proc);
T_BOOL TERMINATEPROC(const T_CHAR *proc);

#if 0 // 2010-01-29, Not Used. If your want to use it, please define nice
T_BOOL sendSignaltoPidFile(T_CHAR *pidFile, T_INT32 signal);
#endif

#if SYSUTIL_HAS_NO_TPRINTF
#define TPRINTF_TERMINATEPROC(proc)  TERMINATEPROC(proc)
#else
#define TPRINTF_TERMINATEPROC(proc)  T_PRINTF("%s\n",(TERMINATEPROC(proc))?"OK":"FAILED");
#endif

#ifdef TEST_SURVEY
void FindProcInform(const T_CHAR *proc,STATUS_INFORM inform) ;
#endif
T_INT32 FINDPROCID(const T_CHAR *proc);
T_INT32 FINDPROC(const T_CHAR *proc);
T_INT32 FINDCMDPROCID(const T_CHAR *proc);

#ifdef __cplusplus
}
#endif 

#endif


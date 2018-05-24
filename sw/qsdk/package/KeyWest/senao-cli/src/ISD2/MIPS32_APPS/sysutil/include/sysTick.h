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
;    File    : sysOther.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       	            2008-08-15       Newly Create
;*****************************************************************************/
#ifndef _SYSUTIL_OTHER_H_
#define _SYSUTIL_OTHER_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif 

#if defined(_WIN32) || defined(WIN32)
#define sysTickGet() GetTickCount()
#define sysFastTickGet() GetTickCount()
#define sysTickRate() 1000
#elif defined(__linux__) || defined(__uClinux__) || defined(Linux)
unsigned long sysTickGet(void);
unsigned long sysFastTickGet(void);
#define sysTickRate() 100 // always is 100 
#elif defined(VxWorks)
#define sysTickGet() tickGet()
#define sysFastTickGet() tickGet()
#define sysTickRate() sysClkRateGet()
#endif

void sysSleep(int dwMilliseconds);


#ifdef __cplusplus
}
#endif 

#endif



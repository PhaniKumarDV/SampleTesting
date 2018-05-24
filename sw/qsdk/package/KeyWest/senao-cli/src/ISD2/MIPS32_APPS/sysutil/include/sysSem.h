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
;    File    : sysSem.h
;    Abstract: include file of the application profile.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2006-0811       Newly Create
;*****************************************************************************/
#ifndef _SYS_SEM_H_
#define _SYS_SEM_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sap_ostypes.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
#if 0
#define SEM_LOCK(X) printf("---SEM_LOCK---%s-----------\n",__FUNCTION__); __SEM_LOCK(X);
#define SEM_UNLOCK(X) printf("---SEM_UNLOCK---%s-----------\n",__FUNCTION__); __SEM_UNLOCK(X);
#else
#define SEM_LOCK(X) __SEM_LOCK(X)
#define SEM_UNLOCK(X) __SEM_UNLOCK(X)
#endif

#ifdef __cplusplus
extern "C" {
#endif 
T_INT32 SEM_CREATE(const T_CHAR  *pSemName);
T_INT32 SEM_DELETE(const T_INT32 semid);
T_INT32 SEM_GETID(const T_CHAR *pSemName);
T_INT32 __SEM_LOCK(const T_INT32 semid);
T_INT32 __SEM_UNLOCK(const T_INT32 semid);
#ifdef __cplusplus
}
#endif 

#endif


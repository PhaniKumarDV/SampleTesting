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
;    File    : msgq.h
;    Abstract: include file of the application profile.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2006-0907       Newly Create
;*****************************************************************************/
#ifndef _SYS_MSGQ_H_
#define _SYS_MSGQ_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <sap_ostypes.h>
/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/

#define PERMS   0666
#define MAX_MSGQLEN 512

typedef struct _message {
    T_UINT32 mtype;
    T_CHAR mtext[MAX_MSGQLEN];
} message_t;

#ifdef __cplusplus /* C only */
extern "C" {
#endif 

T_BOOL MSGQ_CREATE(const T_CHAR  *pName, T_INT32 *pId);
T_INT32 MSGQ_DELETE(const T_INT32 msgqId);
T_INT32 MSGQ_SEND(T_INT32 msgqId, void *pMsg, T_INT32 nBytes);
T_INT32 MSGQ_RECV(T_INT32 msgqId, void *pMsg, T_INT32 nBytes, T_BOOL isWait);
T_INT32 MSGQ_GETID(const T_CHAR  *pName);

#ifdef __cplusplus /* C only */
}
#endif 

#endif


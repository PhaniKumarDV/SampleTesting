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
;    File    : sysFile.h
;    Abstract: include file of the Interface APIs.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2006-0830       Newly Create
;*****************************************************************************/
#ifndef SYSFILE_H
#define SYSFILE_H

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sap_ostypes.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/

#define LOCK_FILE_DIR   "/var"

enum flashInfo {
	FILE_SYSTEM=0,
	TOTAL_SIZE,
	USED,
	AVAILABLE,
	USED_IN_PERCENT,
	MOUNTED_ON
};

enum SYS_KERNEL_INFO {
	SYS_KERNEL_VERSION=0,
	SYS_KERNEL_DATE,
	SYS_NET_HANDLER_VER,
	SYS_KERNEL_VERSION_FULL
};

#define KNLAPPVER_FILE   "/var/knlappver.txt"

#ifdef __cplusplus
extern "C" {
#endif 

#define RM(x) do{ remove(x);}while(0);


T_BOOL sysIsFileExisted(const T_CHAR *filename);
T_BOOL sysIsProcPidExisted(const T_CHAR *filename);
T_UINT32 sysGetFileSize(const T_CHAR *filename);
T_UINT32 sysGetFileChkSum(const T_CHAR *filename);
T_INT32 getNumOfRecord(const T_CHAR *File,int stripLine);//Jaykung 20061031 
#if HAS_PBX
T_CHAR *getFlashInfo(T_CHAR *filePath, enum flashInfo type, T_CHAR *outputStr);
T_INT32 sysGetTextFileNofLine(const T_CHAR *filename);
T_INT32 sysTailFile(const T_CHAR *filename, T_INT32 reservedPercentage, T_INT32 inLine);
#endif
T_INT32 sysFileLock(const T_CHAR *filename, const T_CHAR *owner, T_INT32 waitCount);
T_INT32 sysFileUnLock(const T_CHAR *filename);
char * sysGetKernelInfo(int type);


#ifdef __cplusplus
}
#endif

#endif



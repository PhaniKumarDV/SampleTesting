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
;    File    : sysDevice.h
;    Abstract: include file of the Interface APIs.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2006-0830       Newly Create
;*****************************************************************************/
#ifndef SYSDEVICE_H
#define SYSDEVICE_H

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


#ifdef __cplusplus
extern "C" {
#endif 

T_CHAR *sysGetMountPoint(const T_CHAR *devName);
T_INT32 sysGetRamdiskFreeSpace();
T_INT32 sysGetMountedFileSystemFreeSpace(T_CHAR *fsName);
T_INT32 sysGetMountedFileSystemTotalSpace(T_CHAR *fsName);
T_BOOL sysGetMtdNumByName(const T_CHAR *inMtdName, T_INT32 *iMtdNum, T_UINT32 *iMtdSize);
T_BOOL checkIsMounted(T_CHAR *mountName);
int getAppsMtd();
void setAppsMtd();
#if HAS_PBX
T_BOOL sysIsUSBMounted(T_VOID);
#endif
int isDevMounted(const char *devName);
unsigned short sysGetMtdData(int id, unsigned char *pdata, char *ptoken, unsigned int offset, int len);
unsigned char * sysGetUbootVersion(void);
void *memstr(void *m, const char *s, size_t n);

#if HAS_FW1_FW2
int setKeysMtd(int knl_flag);
#define TEMP_FILE            "/var/key_config"
#define CFG_ENV_SIZE         0x10000
#if LINUX_VER_CODE > KERNEL_VERSION_NUM(2,6,0)
#define MTD_DEF "/dev/mtd"
#else
#define MTD_DEF "/dev/mtd/"
#endif

typedef struct key_partition_info {
	unsigned long	knl_flag;    /* knl_flag= 0 boot from KENEL1 ; knl_flag = 1 boot from KERNEL2 */
	unsigned long	knl_size;
	unsigned long	knl_offset;
	unsigned long   knl_magic;   /* KERNEL 1 Magic Number */
	unsigned long   knl_dcrc;     /* KERNEL 1 CRC Checksum */
	unsigned long	knl2_size;
	unsigned long	knl2_offset;
	unsigned long   knl2_magic;  /* KERNEL 2 Magic Number */
	unsigned long   knl2_dcrc;   /* KERNEL 2 CRC Checksum */
	unsigned long	knl3_size;
	unsigned long	knl3_offset;
	unsigned long   knl3_magic;  /* KERNEL 2 Magic Number */
	unsigned long   knl3_dcrc;   /* KERNEL 2 CRC Checksum */
} key_partition_t;

enum {
SET_TO_KERNEL1=0,
SET_TO_KERNEL2,
SET_TO_KERNEL3,
GET_KEY_NUM
};
#endif

#ifdef __cplusplus
}
#endif

#endif



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
;    File    : sysUtilMisc.h
;    Abstract: include file.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2006-0811       Newly Create
;*****************************************************************************/
#ifndef _SYS_UTIL_MISC_H_
#define _SYS_UTIL_MISC_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sap_ostypes.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
#define DEF_ONE_SECOND          sysTickRate()
#define DEF_ONE_MINUTE          60*DEF_ONE_SECOND
#define DEF_ONE_HOUR            60*DEF_ONE_MINUTE
#define DEF_ONE_DAY             24*DEF_ONE_HOUR

/*jaykung 20070508*/
#define USB_STATUS              "/tmp/isUSBMounted"

#if HAS_BATTERY_HOLTEK
enum battery_level {
    BAT_LEVEL_INITIAL      = 0,
    BAT_LEVEL_NO_BATTERY   = (1 << 0),
    BAT_LEVEL_OUT_OF_POWER = (1 << 1),
    BAT_LEVEL_LOW          = (1 << 2),
    BAT_LEVEL_MEDIUM       = (1 << 3),
    BAT_LEVEL_HIGH         = (1 << 4),
    BAT_LEVEL_FULL         = (1 << 2 | 1 << 3 | 1 << 4)
};

#define BATTERY_LEVEL_FILE "/tmp/battery_level"
#endif /* HAS_BATTERY_HOLTEK */

#ifdef __cplusplus
extern "C" {
#endif 

T_INT32 sysGenKeyFromString(const T_CHAR *pString);
T_INT32 CHKSUM(T_CHAR *pBuf, T_INT32 len);
int generateAuthPassWords(T_CHAR *macAddr, T_CHAR *outputPassword);//victor 200609xx
T_VOID generateRandomSeek(const T_CHAR* interface);
char* generateRandomAscii(char* var, int len);
char* generateRandomHexNum(char* var, int len);
char* getHwVer();
char* getSerNum();
int portRangeStringToList(const char* str, unsigned short *portList, int listMax);
int portRangeListToString(unsigned short *portList, int listMax, char* str, int len);
T_BOOL lecho(T_CHAR *pText, T_CHAR *fName);
T_CHAR *sysDotted2Number(T_CHAR *maskStr);
T_BOOL checkSameSubnet(T_IPADDR scrIpAddr,T_IPADDR desIpAddr,T_IPADDR mask);
int getFirmwareHeaderCheck(char *filename);
int getFirmwareHeaderCheckEx(char *filename, unsigned int magickey);
void sysCheckStringOnWeb(const char *srcStr, char *destStr);
void sysCheckStringForRepeater(const char *srcStr, char *destStr);
int sysconf_util_cmd(char* cmdStr, char* replyStr);
int sysCharToInt(char c);
int sysIsValidMacAddr(T_CHAR *mac);
char* sysHex2Ascii(T_CHAR *hexStr);
char* sysAscii2Hex(T_CHAR *asciiStr);
char* sysStrToupper(char *str);
char* sysStrTolower(char *str);
#if SUPPORT_IPV6
char* sysGetpeername(int sock);
#endif
#if SUPPORT_HW_DSCP
void sysEnableHwDscp();
void sysDisableHwDscp();
#endif
#ifdef __cplusplus
}
#endif

#endif


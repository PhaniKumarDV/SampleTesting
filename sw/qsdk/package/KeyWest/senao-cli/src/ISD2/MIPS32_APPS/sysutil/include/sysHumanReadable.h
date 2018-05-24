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
;    File    : sysHumanreadable.h
;    Abstract: include file of the Interface APIs.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2007-0123       Newly Create
;*****************************************************************************/
#ifndef _SYS_HUMAN_READABLE_IF_H_
#define _SYS_HUMAN_READABLE_IF_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sap_ostypes.h>
 
/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
enum {
    KILOBYTE = 1024,
    MEGABYTE = (KILOBYTE*1024),
    GIGABYTE = (MEGABYTE*1024)
};

#ifdef __cplusplus
extern "C" {
#endif 

//T_CHAR *sysMakeHumanReadableStr(T_UINT32 val, T_UINT32 display_unit);
const char *sysMakeHumanReadableStr(T_UINT64 val, T_UINT64 display_unit);
const char *sysByteToTimeFormatStr(T_UINT32 availBytes);
const char *sysByteToHumanReadableStr(T_UINT32 Bytes);
int strMacStrToMacAddr(T_CHAR dst[6], const char *macStr);
int strMacAddrToMacStr(char macStr[18], const unsigned char bin[6]);
int sysStrToMacAddr(char macStr[18], const char* srcStr);
void miscHexDump(unsigned int offset, const unsigned char *data,int buf_siz);
T_CHAR* transferQuoteStringFormat(const T_CHAR* string);//jaykung 20070514
int replaceCharByString(const T_CHAR* stringSrc,const T_CHAR* beReplacedChar,const T_CHAR* replaceStr,T_CHAR* stringDest);//jaykung 20070515
#ifdef COUNT_EACH_STA
const char *sysParsePktUnit(const unsigned long long int Bytes);//Joey 20090319
#endif

#ifdef __cplusplus
}
#endif 

#endif



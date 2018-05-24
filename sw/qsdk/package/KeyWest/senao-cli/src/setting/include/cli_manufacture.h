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
;    Creator : marklin
;    File    : manufacture.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       marklin            2007-1027       Create
;*****************************************************************************/
#ifndef _CLI_MANUFACTURE_H_
#define _CLI_MANUFACTURE_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <cli.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
#define MAC_ADDR_STRING_LEN 		17
#define SERIAL_NUMBER_LEN               9
#define a_A_OFFSET    			0x20     // 'a' - 'A' = 0x20 
#define a_9_OFFSET    			0x28     // 'a' - '9' = 0x28
/*-------------------------------------------------------------------------*/
/*                           FUNCTIONS                                     */
/*-------------------------------------------------------------------------*/
CliStatus cmdReadMAC(T_VOID* priv, CliData* cliData);
CliStatus cmdAutoWriteMAC(T_VOID* priv, CliData* cliData);
CliStatus cmdReadSerial(T_VOID* priv, CliData* cliData);
char *mac_increase_1(char *mac_str);
#endif

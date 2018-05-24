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
;    File    : specApp.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;      Norkay			2007-11-08
;*****************************************************************************/
#ifndef _APCFG_SPECIAL_APPS_H_
#define _APCFG_SPECIAL_APPS_H_


/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <sap_ostypes.h>
#include <apcfg.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
#define SPEC_APP_TRIGGER_PORT_LIST_MAX 	        2
#define SPEC_APP_PUBLIC_PORT_LIST_MAX	        10
#define SPEC_APP_COMMAND_LENGTH 		16
#define SPEC_APP_STRING_BUFF_LENGTH		60
/*-------------------------------------------------------------------------*/
/*                           enum & struct                                 */
/*-------------------------------------------------------------------------*/
typedef struct _SpecAppSetting
{
	T_UINT8  isEnabled                                       __ATTRIBUTE_PACKED__;
	T_UINT8  isActive                                        __ATTRIBUTE_PACKED__;
	T_UINT8  uId                                             __ATTRIBUTE_PACKED__;
	T_UINT16 triggerPortList[SPEC_APP_TRIGGER_PORT_LIST_MAX] __ATTRIBUTE_PACKED__;
	T_UINT8  triggerPortType                                 __ATTRIBUTE_PACKED__;
	T_UINT16 publicPortList[SPEC_APP_PUBLIC_PORT_LIST_MAX]   __ATTRIBUTE_PACKED__;
	T_UINT8  publicPortType                                  __ATTRIBUTE_PACKED__;
	T_CHAR   command[SPEC_APP_COMMAND_LENGTH+1]              __ATTRIBUTE_PACKED__;
	T_UINT8  serviceId                                       __ATTRIBUTE_PACKED__;
	T_UINT8  scheduleId                                      __ATTRIBUTE_PACKED__;
}__S_ATTRIBUTE_PACKED__ SpecAppSetting;


/*-------------------------------------------------------------------------*/
/*                           FUNCTIONS                                     */
/*-------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

T_BOOL getSpecAppValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setSpecAppValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defSpecAppValue(ap_cfg_item_t* item);
T_BOOL specAppPortStringToList(const char* str, SpecAppSetting *app);
T_BOOL specAppPortListToString(SpecAppSetting app, char* str, int len);
T_BOOL specAppLoadDefault(T_VOID* dst, T_INT32 index);
#ifdef __cplusplus
}
#endif

#endif


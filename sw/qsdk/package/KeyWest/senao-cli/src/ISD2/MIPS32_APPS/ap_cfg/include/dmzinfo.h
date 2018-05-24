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
;    File    : dmzSetting.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;      Norkay			2007-11-08
;*****************************************************************************/
#ifndef _APCFG_DMZ_SETTING_H_
#define _APCFG_DMZ_SETTING_H_


/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <sap_ostypes.h>
#include <apcfg.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*                           enum & struct                                 */
/*-------------------------------------------------------------------------*/
typedef struct _DmzSetting
{
	T_UINT8  isEnabled    __ATTRIBUTE_PACKED__;
	T_UINT8  uId          __ATTRIBUTE_PACKED__;
	T_UINT8  type         __ATTRIBUTE_PACKED__;
	T_CHAR   publicIP[APPS_IP_MAX_SIZE] __ATTRIBUTE_PACKED__;
	T_CHAR   hostIP[APPS_IP_MAX_SIZE]   __ATTRIBUTE_PACKED__;
	T_UINT16 hostPort     __ATTRIBUTE_PACKED__;
    T_CHAR   padding[1]   __ATTRIBUTE_PACKED__;
}__S_ATTRIBUTE_PACKED__ DmzSetting;


/*-------------------------------------------------------------------------*/
/*                           FUNCTIONS                                     */
/*-------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

T_BOOL getDmzValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setDmzValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defDmzValue(ap_cfg_item_t* item);

#ifdef __cplusplus
}
#endif

#endif

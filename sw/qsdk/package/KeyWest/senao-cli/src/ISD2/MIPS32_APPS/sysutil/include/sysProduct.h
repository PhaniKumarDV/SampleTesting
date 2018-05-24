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
;    File    : sysProduct.h
;    Abstract: include file of the share memory APIs.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       
;*****************************************************************************/

#ifndef SYSPRODUCT_H
#define SYSPRODUCT_H

#include <gconfig.h>
#include <sap_ostypes.h>

#ifdef __cplusplus
extern "C" {
#endif 

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
#define NUM_SUPPORT_LANGUAGE    10

typedef struct _sysProduct
{
    unsigned int hardwareid;
    char *vendor;
    char *description;
    char *model;
    char *domain;
    char *web_title;
    char *logo;
    char *titlelogo;
    char *bannerlogo;
    char *ap_wsc_manufacture;
    char *ap_wsc_model_name;
    char *ap_wsc_device_name;
    char *cli_wsc_model_name;
    char *cli_wsc_device_name;
    char *cli_wsc_device_name_r;
    char *title_bg_color;
    char *title_font_color;
    char *menu_bg_color;
    char *menu_font_color;
    char *label_bg_color;
    char *label_font_color;
    char *sublabel_bg_color;
    char *sublabel_font_color;
    char *item_bg_color;
    char *item_font_color;
	char *selection_color;
    char *support_language[NUM_SUPPORT_LANGUAGE];
    char *upnpd_friendly_name;
    char *upnpd_manufacture;
    char *upnpd_manufacture_url;
    char *upnpd_model_desc;
    char *upnpd_model_name;
    char *upnpd_model_number;
    char *upnpd_model_url;
}sysProduct;

#if !HAS_USE_PRODUCT_ID
#include <product_defval.h>
#endif

/*-------------------------------------------------------------------------*/
/*                           FUNCTION                                      */
/*-------------------------------------------------------------------------*/

unsigned short sysGetProductIndex(void);
char * sysGetVendorName(void);
char * sysGetVendorMode(void);
char * sysGetModelName(void);
char * sysGetDomainName(void);
char * sysGetVendorLogo(void);
char * sysGetBannerLogo(void);
char * sysGetApWscManufacture(void);
char * sysGetApWscModelName(void);
char * sysGetApWscDeviceName(void);
char * sysGetCliWscModelName(void);
char * sysGetCliWscDeviceName(void);
char * sysGetCliWscDeviceNameR(void);
char * sysGetTitleBGColor(void);
char * sysGetTitleFontColor(void);
char * sysGetMenuBGColor(void);
char * sysGetMenuFontColor(void);
char * sysGetLabelBGColor(void);
char * sysGetLabelFontColor(void);
char * sysGetSubLabelBGColor(void);
char * sysGetSubLabelFontColor(void);
char * sysGetItemBGColor(void);
char * sysGetItemFontColor(void);
char * sysGetSelectionColor(void);
char * sysGetSupportLangugae(int);
char * sysGetUPNPDFriendlyName(void);
char * sysGetUPNPDManufacture(void);
char * sysGetUPNPDManufactureUrl(void);
char * sysGetUPNPDModelDesc(void);
char * sysGetUPNPDModelName(void);
char * sysGetUPNPDModelNum(void);
char * sysGetUPNPDModelUrl(void);
char * sysGetBoardHardwareID(void);
unsigned int sysGetFWUGVendorID(void);
unsigned int sysGetFWUGProductID(void);
char * sysGetFWVersion(void);
char * sysGetFWBuildDate(void);
char * sysGetModuleName(void);
T_BOOL sysCheckFWNofity(void);
char * sysGetWebTitleName(void);

#ifdef __cplusplus
}
#endif 

#endif

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
;    File    : sysWlan.h
;    Abstract: include file of the WLAN APIs.
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       Adonn           2006-1121       Newly Create
;*****************************************************************************/
#ifndef _SYSWLAN_H_
#define _SYSWLAN_H_
/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <wlanParameter.h>

#ifdef __cplusplus
extern "C" {
#endif 


typedef struct __sysWlanStatus_t
{
    T_INT32     linkQuality;
    T_INT32     signalLevel;
    T_INT32     noiseLevel;
    T_BOOL      isLevelinDbm;

    T_INT32     bitRate; /* Mbps */ 
	T_CHAR 		Mac[20];
    /* Channel (AP) or Frequenct (Sta) */
    T_INT32     channel;
    T_INT32     frequency; /* Mhz */

 
} sysWlanStatus_t;

typedef struct __sysWlanStatusEntry_t
{
    T_CHAR  pattern[32];
    T_CHAR  scanPattern[32];
    T_VOID  *data1;
    T_VOID  *data2;
} sysWlanStatusEntry_t;

enum {WPS_OFF=0,WPS_ON=1};


#if FOR_ATHEROS_PLATFORM || HAS_ATHEROS_WLAN_AR9K || (FOR_REALTEK_PLATFORM && REALTEK_5G_SUPPORT)
#define CHANNEL_11NA_LOWER_BAND_MIN 36 /*W52: 36,40,44,48*/
#define CHANNEL_11NA_LOWER_BAND_MAX 48 /*W52: 36,40,44,48*/
#define CHANNEL_11NA_MID_BAND_MIN 52 /*W53: 52,56,60,64*/
#define CHANNEL_11NA_MID_BAND_MAX 64 /*W53: 52,56,60,64*/
#define CHANNEL_11NA_H_BAND_MIN 100 /*W56: 100,104,108,112,116,120,124,128,132,136,140*/
#define CHANNEL_11NA_H_BAND_MAX 140 /*W56: 100,104,108,112,116,120,124,128,132,136,140*/
#define CHANNEL_11NA_UPPER_BAND_MIN 149 /*149,153,157,161*/
#define CHANNEL_11NA_UPPER_BAND_MAX 161 /*149,153,157,161*/
#define CHANNEL_11NA_ISM_BAND 165 	/*165*/
#define CHANNEL_11NA_DEFAULT_HT40PLUS_CH	36
#define CHANNEL_11NA_DEFAULT_HT40MINUS_CH	40
#if (FOR_REALTEK_PLATFORM && REALTEK_5G_SUPPORT)
#if 0
enum SECONDARY_CHANNEL_OFFSET {
	HT_2NDCH_OFFSET_DONTCARE = 0,
	HT_2NDCH_OFFSET_BELOW    = 1,	// secondary channel is below primary channel, ex. primary:5 2nd:1
	HT_2NDCH_OFFSET_ABOVE    = 2	// secondary channel is above primary channel, ex. primary:5 2nd:9
};
#endif
enum {
  HT40_NONE=0, HT40MINUS, HT40PLUS
};
#else
enum {
  HT40_NONE=0, HT40PLUS, HT40MINUS	
};
#endif
typedef enum {
RADIO_24G=0,
RADIO_5G
} RADIO_WIRELESS_MODE;

int channelTo5G11nHTtype(int channel);
#endif

int sysWlanGetClientList(WLANClientListInfo *clientList, size_t size);

int sysWlanGetSiteSurveyResult(ApInfo apinfo[], size_t infoArraySize);
int getRssiValue(char* interface);
int sysWlanGenWpsPinCodeByMac(T_CHAR* macAddr);
int sysWlanGenWpsPinCodeByLANMac();
void sysWlanDisconnect();
char* sysWlanGetSsid();
char* sysWlanGetState();
char* sysWlanGetBssid();
char* sysWlanGetCipher();
char* sysWlanGetKeyMgmt();
rssiLevel wlanRssiConvert2Level(int rssi);
char* sysWlanGetPassphrase(const T_CHAR *ssid,const T_CHAR *psk);
void sysCheckWEPKeyForIwconfig(const char *srcStr, char *destStr);
int checkBGNValidChannel(int regularDomain, int channel);
int parseApInfo(ApInfo *apData, const char *buf);
T_BOOL  sysGetWlanStatus(T_CHAR *dev_name, sysWlanStatus_t *stat);
int sysWlanParseEncType(const T_CHAR *encStr);
int sysWlanParseAuthType(const T_CHAR *authStr);
#ifdef FOR_RALINK_PLATFORM
unsigned short sysGetRFConfig(unsigned int offset);
int sysIsApCliConnected(const char *interface,const char *ssid);
T_VOID sysReGenRalinkPinCode(const char *interface);
int sysWlanGetClinetNums(const char *interface);
int sysWlanGetRadioStatus(const char *interface);
unsigned int sysGetAPPincode(char *interface);
unsigned int sysGetAPPincodeFromFile(char *path);
T_BOOL sysCheckWlanClient(T_CHAR* mac);
T_VOID sysPrintWlanStatus(sysWlanStatus_t *stat);
#if GEN_ADMIN_PASSWORD_BY_MACADDR
char* new_generateADMINPWDbyMac(char* var, char* smac,int keylen);
#endif
#ifdef HAS_EACH_SSID_CLINUM
int sysWlanGetClinetNumsByBssid(int idx);
int _sysWlanGetClinetNumsByBssid(int idx, char* ifName);
#endif
#endif
#if USE_WPA2PSK_AS_DEFAULT_SECURITY
char* generateWPA2PSKbyMac(char* var, char* mac,int keylen);
char* new_generateWPA2PSKbyMac(char* var, char* smac,int keylen);
char* __new_generateWPA2PSKbyMac(char* var, char* smac,int keylen,int flag);
char* generateWPA2PSKbySN(char* var, char* sn,int keylen);
#endif
char* generateWPA2PSKbyRandom(char* var,int keylen);

#if HAS_TELEFONICA_3G_FUNCTION
int new_generateWPA2PSKbyZyxel(char *var, char* mac, int data_len);
#endif

#if defined (FOR_ATMEL902) || defined (FOR_RALINK_PLATFORM) || defined (FOR_ATHEROS_PLATFORM)
void sysWlanCheckSsidOnPassphrase(const char *srcSSid, char *detSSid);
#endif

#ifdef __cplusplus
}
#endif 

#endif



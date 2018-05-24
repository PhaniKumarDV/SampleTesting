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
;    Creator : Philips
;    File    : cli_wless.c
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       Philips         2012-10-16      Create
;*****************************************************************************/

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <cli_wless.h>
#include <opmodes.h>
#include <uci.h>

/*-------------------------------------------------------------------------*/
/*                           GLOBAL VARIABLE                               */
/*-------------------------------------------------------------------------*/
T_INT32 SSIDProfileIndex=0;
T_INT32 channelCount=0;
T_INT32 security_set=0;

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
typedef struct __CliDatarateEntry
{
    const T_INT32 item;	
    const T_CHAR* datarateDisplayName;
    const T_CHAR* datarateName;
    const T_CHAR* ratecode;
    const T_INT32 rateorder;

}CliDatarateEntry;

CliDatarateEntry CliDatarateTable[] = {
	//B only
	{0, "auto", "auto", "00", 0},	
	{1, "1M", "1M", "1B", 1},
	{2, "2M", "2M", "1A", 2},
	{3, "5.5M", "5.5M", "19", 3},
	{4, "11M", "11M", "18", 6},
	//G and A only
	{5, "6M", "6M", "0B", 4},
	{6, "9M", "9M", "0F", 5},
	{7, "12M", "12M", "0A", 7},
	{8, "18M", "18M", "0E", 8},
	{9, "24M", "24M", "09", 9},
	{10, "36M", "36M", "0D", 10},
	{11, "48M", "48M", "08", 11},
	{12, "54M", "54M", "0C", 12},
	//N only with 1 antenna
	{13, "MCS0", "MCS0", "80", 13},
	{14, "MCS1", "MCS1", "81", 14},
	{15, "MCS2", "MCS2", "82", 15},
	{16, "MCS3", "MCS3", "83", 16},	  
	{17, "MCS4", "MCS4", "84", 17},
	{18, "MCS5", "MCS5", "85", 18},
	{19, "MCS6", "MCS6", "86", 19},
	{20, "MCS7", "MCS7", "87", 20},
	//N only with 2 antenna	  
	{21, "MCS8", "MCS8", "88", 21}, 		
	{22, "MCS9", "MCS9", "89", 22}, 		
	{23, "MCS10", "MCS10", "8A", 23}, 		
	{24, "MCS11", "MCS11", "8B", 24}, 		
	{25, "MCS12", "MCS12", "8C", 25}, 		
	{26, "MCS13", "MCS13", "8D", 26}, 		
	{27, "MCS14", "MCS14", "8E", 27}, 		
	{28, "MCS15", "MCS15", "8F", 28},
	
//Add on 2013-06-11 by Philips to support Data Rate of 3 antenna for eap900H which is requested by Jacy	
	//N only with 3 antenna	  
	{29, "MCS16", "MCS16", "90", 29}, 		
	{30, "MCS17", "MCS17", "91", 30}, 		
	{31, "MCS18", "MCS18", "92", 31}, 		
	{32, "MCS19", "MCS19", "93", 32}, 		
	{33, "MCS20", "MCS20", "94", 33}, 		
	{34, "MCS21", "MCS21", "95", 34}, 		
	{35, "MCS22", "MCS22", "96", 35}, 		
	{36, "MCS23", "MCS23", "97", 36},

//Add on 2013-08-19 by Philips to support Data Rate of AC for eap1750H which is requested by Jacy		
	//802.11AC
	{37, "MCS0(AC)", "VHTMCS0", "98", 37},
	{38, "MCS1(AC)", "VHTMCS1", "99", 38},
	{39, "MCS2(AC)", "VHTMCS2", "9A", 39},
	{40, "MCS3(AC)", "VHTMCS3", "9B", 40},	  
	{41, "MCS4(AC)", "VHTMCS4", "9C", 41},
	{42, "MCS5(AC)", "VHTMCS5", "9D", 42},
	{43, "MCS6(AC)", "VHTMCS6", "9E", 43},
	{44, "MCS7(AC)", "VHTMCS7", "9F", 44},  
	{45, "MCS8(AC)", "VHTMCS8", "A0", 45}, 		
	{46, "MCS9(AC)", "VHTMCS9", "A1", 46}, 
};

typedef struct __CliMACfilterEntry
{
    T_INT32 item;	
    T_CHAR macaddress[32];

}CliMACfilterEntry;

typedef struct __CliMACfilterlist
{
	T_INT32 count;
	CliMACfilterEntry CliMACfilterTable[50];

}CliMACfilterlist;

CliMACfilterlist MACfilterData;

typedef struct __CliHTmodeEntry
{
    const T_INT32 item;
    const T_CHAR* HTmodeName;

}CliHTmodeEntry;

CliHTmodeEntry CliHTmodeTable[] = {

	{1, "20"}, 	//"20MHz"
	{2, "40"}, 	//"40MHz"
	{3, "20-40"}, 	//"20/40MHz"

//Modify on 2013-07-24 for EAP1750 to support 802.11AC
	{4, "80"}, 	//"80MHz"

};

typedef struct __CliWDSsecurityEntry
{
    const T_INT32 item; 
    //const T_CHAR* wirelessmode;
    const T_CHAR* wdssecurityName;

}CliWDSsecurityEntry;

CliWDSsecurityEntry CliWDSsecurityTable[] = {

	{1, "none"},
	{2, "aes"},
	{3, "wep"},	//wds

};

typedef struct __CliAPsecurityEntry
{
    const T_INT32 item; 
    const T_CHAR* wirelessmode;
    const T_CHAR* apsecurityName;

}CliAPsecurityEntry;

CliAPsecurityEntry CliAPsecurityTable[] = {
	
	{1, "11na" , "none"},
	{2, "11na" , "wep open"},
	{3, "11na" , "wep shared"},
	{4, "11na" , "psk tkip+aes"},
	{5, "11na" , "psk tkip"},
	{6, "11na" , "psk aes"},
	{7, "11na" , "psk2 tkip+aes"},
	{8, "11na" , "psk2 tkip"},
	{9, "11na" , "psk2 aes"},
	{10, "11na" , "psk-mixed tkip+aes"},
	{11, "11na" , "psk-mixed tkip"},
	{12, "11na" , "psk-mixed aes"},
	{13, "11na" , "wpa tkip+aes"},
	{14, "11na" , "wpa tkip"},
	{15, "11na" , "wpa aes"},
	{16, "11na" , "wpa2 tkip+aes"},
	{17, "11na" , "wpa2 tkip"},
	{18, "11na" , "wpa2 aes"},
	{19, "11na" , "wpa-mixed tkip+aes"},
	{20, "11na" , "wpa-mixed tkip"},
	{21, "11na" , "wpa-mixed aes"},
	
	{22, "11n_pure" , "none"},
	{23, "11n_pure" , "psk aes"},
	{24, "11n_pure" , "psk2 aes"},
	{25, "11n_pure" , "psk-mixed aes"},
	{26, "11n_pure" , "wpa aes"},
	{27, "11n_pure" , "wpa2 aes"},
	{28, "11n_pure" , "wpa-mixed aes"}
};

typedef struct __CliCBsecurityEntry
{
    const T_INT32 item; 
    const T_CHAR* wirelessmode;
    const T_CHAR* cbsecurityName;

}__CliCBsecurityEntry;

__CliCBsecurityEntry CliCBsecurityTable[] = {
	
	{1, "11na" , "none"},
	{2, "11na" , "wep open"},
	{3, "11na" , "wep shared"},
	{4, "11na" , "psk tkip"},
	{5, "11na" , "psk aes"},
	{6, "11na" , "psk2 tkip"},
	{7, "11na" , "psk2 aes"},
	
	{8, "11na" , "wpa tkip"},
	{9, "11na" , "wpa aes"},
	{10, "11na" , "wpa2 tkip"},
	{11, "11na" , "wpa2 aes"},

};


typedef struct __CliMeshmodeEntry
{
    const T_INT32 item;
    const T_CHAR* MeshmodeName;

}CliMeshmodeEntry;

CliMeshmodeEntry CliMeshmodeTable[] = {

	{1, "none-mesh"},
	{2, "mesh-only"},
	{3, "mesh-ap"},

};

typedef struct __CliWirelessmodeEntry
{
    const T_INT32 item;
    const T_CHAR* band;
    const T_CHAR* wirelessmodeName;
    const T_CHAR* wirelessmodeDescription;

}CliWirelessmodeEntry;

CliWirelessmodeEntry CliWirelessmodeTable[] = {

	{1, "2.4G", "11b" , "802.11 B Only"},		//Single Radio and Dual Radio
	{2, "2.4G", "11g_pure" , "802.11 G Only"},
	{3, "2.4G", "11g" , "802.11 B/G Mixed"},
	{4, "2.4G", "11ng" , "802.11 B/G/N Mixed"},
	{5, "2.4G", "11n_pure" , "802.11 N Only"},
	
	{6, "5G", "11n_pure" , "802.11 N Only"},	//"11na_pure" for Dual Radio
	{7, "5G", "11a_pure" , "802.11 A Only"},	//"11a" for Dual Radio
	{8, "5G", "11na" , "802.11 A/N Mixed"},

//Modify on 2013-07-24 for EAP1750 to support 802.11AC
	{9, "5G", "11naac" , "802.11 AC"},

//Modify for AP100 on 2012-11-08	
	{10, "2.4G", "11b" , "802.11 B Only"},		//2.4G
	{11, "2.4G", "11g_pure" , "802.11 G Only"},
	{12, "2.4G", "11g" , "802.11 B/G Mixed"},
	{13, "2.4G", "11ng" , "802.11 B/G/N Mixed"},
	{14, "2.4G", "11n_pure" , "802.11 N Only (2.4G)"},
	
	{15, "5G", "11na_pure" , "802.11 N Only (5G)"},	//5G
	{16, "5G", "11a" , "802.11 A Only"},
	{17, "5G", "11na" , "802.11 A/N Mixed"},
	
	{18, "5G", "11abgn" , "802.11 A/B/G/N Mixed"},	//For CB and WDSSTA mode

};

typedef struct __CliChannelFreqEntry
{
    T_INT32 item;	
    T_CHAR channel[32];

}CliChannelFreqEntry;

typedef struct __CliChannelFreqlist
{
	T_INT32 count;
	//Modify on 2013-01-07 by Philips to reserve enough memory space to save all channels
	CliChannelFreqEntry CliChannelFreqTable[128];

}CliChannelFreqlist;

CliChannelFreqlist ChannelFreqData;

//Jacy ask to keep wepkey and use keylength to set wepkeylength and inputtype
//const T_INT32 CliWEPkeyLength[2][3]={ {10, 26, 32}, {5, 13, 16} };
typedef struct __CliWEPsetEntry
{
	T_INT32 keyset[4];
	
	T_CHAR inputtype[2];
	T_CHAR keylength[4];
	T_CHAR defaultkey[2];
	
	T_CHAR key[4][128];

}CliWEPsetEntry;
static CliWEPsetEntry CliWEPset={ {0, 0, 0, 0}, "1", "64", "1", {"", "", "", ""} };

typedef struct __CliWPAPSKsetEntry
{
	T_INT32 passphraseset;

	T_CHAR passphrase[128];
	T_CHAR interval[5];

}CliWPAPSKsetEntry;
static CliWPAPSKsetEntry CliWPAPSKset={ 0, "", "3600" };


typedef struct __CliWPAsetEntry
{
	T_INT32 serveripset;
	T_INT32 secretset;

	T_INT32 accserveripset;
	T_INT32 accsecretset;

	T_CHAR serverip[16];
	T_CHAR port[6];
	T_CHAR secret[128];
	T_CHAR interval[5];
	
	T_CHAR accserverip[16];
	T_CHAR accport[6];
	T_CHAR accsecret[128];
	T_CHAR accinterval[5];
	
}CliWPAsetEntry;
static CliWPAsetEntry CliWPAset={ 0, 0, 0, 0, "", "1812", "", "3600", "", "1813", "", "600" };

//Modify on 2012-11-13 for supplicant in CB, WDSSTA and CR mode
typedef struct __CliWPASUPsetEntry
{
	T_INT32 eap_typeset;
	T_INT32 authset;
	T_INT32 identityset;
	T_INT32 passwordset;

	T_CHAR eap_type[16];
	T_CHAR auth[16];
	T_CHAR identity[64];
	T_CHAR password[64];

	
}CliWPASUPsetEntry;
static CliWPASUPsetEntry CliWPASUPset={ 0, 0, 0, 0, "", "", "", "" };

typedef struct __CliCountryEntry
{
    const T_CHAR* item;	
    const T_CHAR* countryName;
    const T_CHAR* countryCode;
    const T_INT32 htmodeAllow; // 0: 20/40=N/N, 2: 20/40=Y/N, 3: 20/40=Y/Y

}CliCountryEntry;
extern CliCountryEntry CliCountryTable[];
extern CliCountryEntry CliCountryTableETSI[];

//Add on 2013-06-07 by Philips to support Guest Network for eap900 which is requested by Jacy
typedef struct __CliguestnetworkipsetEntry{	
	T_INT32 ipset;		//use to decide whether get data from Config file or Cliguestnetworkipset
	T_INT32 maskset;	//use to decide whether get data from Config file or Cliguestnetworkipset	
			
	T_CHAR ip[16];
	T_CHAR subnetmask[16];		
					
}CliguestnetworkipsetEntry;

CliguestnetworkipsetEntry Cliguestnetworkipset={0, 0, "", ""};

typedef struct __ClilguestnetworkdhcpsetEntry
{	
	T_INT32 startipset;
	T_INT32 endipset;
	T_INT32 winsipset;
	
	T_CHAR startip[32];	
	T_CHAR endip[32];
	T_CHAR winsip[32];		

}ClilguestnetworkdhcpsetEntry;
ClilguestnetworkdhcpsetEntry Clilguestnetworkdhcpset={0, 0, 0, "", "", ""};

/*-------------------------------------------------------------------------*/
/*                           Parameter                                     */
/*-------------------------------------------------------------------------*/
extern T_CHAR model_name[];
extern CliEntry cli_table_wdswep[];
extern CliEntry cli_table_wdsaes[];

extern CliEntry cli_table_ssidp[];

extern CliEntry cli_table_wep[];
extern CliEntry cli_table_wpapsk[];
extern CliEntry cli_table_wpa[];

//Modify on 2012-11-13 for supplicant in CB, WDSSTA and CR mode
extern CliEntry cli_table_wpa_supplicant[];

extern T_CHAR globalCommandLine[1024];

extern T_INT32 cmdtreelevel;

extern T_CHAR current_radio_flag[5];
extern T_UINT32 current_opmode;
extern T_UINT32 current_opmode_2;
extern T_UINT32 current_opmode_5;
extern T_INT32 model_radio;

//extern T_INT32 model_ID;

//Modify on 2013-09-05 to extend the number of Model to 64
extern long long model_ID;

T_INT32 apsecusetbridge=-1;
T_INT32 cbsecusetbridge=-1;
T_INT32 wdssecusetbridge=-1;
T_INT32 ssidpsetbridge=-1;

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 wdslink wdssecu                 */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_WDSAP,   	"wdslink",	cli_table_wdslink,	getNextTable,	"WDS link settings",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,   	"network",	cli_table_network,	getNextTable,	"Wireless network",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP,	"macfilter",	cli_table_mac_filter,	getNextTable,	"Wireless mac filter",		"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,   	"advset",	cli_table_advset,	getNextTable,	"Wireless advanced settings",   "", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,   	"help",		cli_table_wless,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,   	"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

//CliEntry cli_table_wdslink[]= {
//	{OPM_ALL,	"wdssecu",	NULL,			cmdwdssecu,	"WDS security",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"links",	cli_table_links,	getNextTable,	"Link setting",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_wdslink,	cmdHelp,	"Help",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",		"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

//CliEntry cli_table_wdswep[]= {
//	{OPM_ALL,	"wepk",		NULL,			cmdwdswepk,		"WEP key",	"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_wdswep,       cmdHelp,		"Help",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdwdssecurityexit,	"Exit",		"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

//CliEntry cli_table_wdsaes[]= {
//	{OPM_ALL,	"aesp",		NULL,			cmdwdsaesp,		"AES passphrase",	"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_wdsaes,	cmdHelp,		"Help",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdwdssecurityexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: displaywdssecurity
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID displaywdssecurity(T_CHAR* wirelessmode, T_INT32 operationeMode) {

int i;
T_INT32 start=1;
T_INT32 stop=3;

	//There is not WEP in wdslink encryption when N only mode or WDSAP mode
	if (strcmp(wirelessmode, "11n_pure")==0 || strcmp(wirelessmode, "11na_pure")==0 || operationeMode==OPM_WDSAP)
		stop=2;
	for (i=start; i<=stop; i++)
		printf("%d - %s\n", CliWDSsecurityTable[i-1].item, CliWDSsecurityTable[i-1].wdssecurityName);
	
}

/*****************************************************************
* NAME: cmdwdssecu
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwdssecu(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR wifiinterface[128]="wireless.wifi0.hwmode";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
//T_CHAR uci_set_buf1[128];
T_INT32 i;
T_INT32 count=3;
T_CHAR wirelessmode[128];
T_INT32 ssidCount;
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
T_INT32 nawds_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(wifiinterface, "wireless.wifi1.hwmode");
		
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	
	//get 4 (if ssidcount is 4) or 16 (if ssidcount is 8) for single-radio and 16 (if radio is 2.4G) or 42 (if radio is 5G) for dual-radio
	//nawds_index=get_nawds_index(ssidCount);

	//Modify on 2013-08-07 by Philips to get the correct nawds_index
	nawds_index=get_nawds_index(ssidCount, operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].encryption", nawds_index);

	if ( model_radio==7 && operationeMode==OPM_WDSB)
		sprintf(func_buf, "wireless.@wifi-iface[%d].encryption", wifi_index);

		
	strcpy(wirelessmode, getWirelessmode(wifiinterface));
	//N only or WDSAP can only support 2 kind security -->none, aes
	if (strcmp(wirelessmode, "11n_pure")==0 || strcmp(wirelessmode, "11na_pure")==0 || operationeMode==OPM_WDSAP)
		count=2;
	
	if(cliData->argc==0){

		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displaywdssecurity(wirelessmode, operationeMode);
		tprintf("Current setting: %s\n", uci_get_buf);
		
    		tprintf("Recognized input format: ");
    		for (i=1; i<count; i++)
    			tprintf("%d, ", i);
    		tprintf("%d\n", i);

		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

		if (wdssecusetbridge==-1){
			//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
			if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
				sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
			
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, count, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
			}

			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
			
			switch(atoi(uci_set_buf)){
				case 1:
					cli_set_uci(func_buf, "none");
					cliData->tokenLen-=2;
					return CLI_NOTHING;
				case 2:					
					cli_set_uci(func_buf, "aes");
					cliData->tokenLen--;
					//Handle the command --> wless2/wdslink>wdssecu 2
					if (cmdtreelevel==2){
						wdssecusetbridge=2;
						//prompt will be --> wless2/wdslink/wdssecu>
						cmdtreelevel=cliData->tokenLen;
					}
					return cmdHelp(cli_table_wdsaes, cliData);
				case 3:
					cli_set_uci(func_buf, "wep");
					cliData->tokenLen--;
					//Handle the command --> wless2/wdslink>wdssecu 3
					if (cmdtreelevel==2){
						wdssecusetbridge=3;
						//prompt will be --> wless2/wdslink/wdssecu>
						cmdtreelevel=cliData->tokenLen;
					}
					return cmdHelp(cli_table_wdswep, cliData);
				default:
					return CLI_PARAMS_ERR;
			}
		}
		if ( wdssecusetbridge==2 )
			return getNextTable(cli_table_wdsaes, cliData);
		else if ( wdssecusetbridge==3 )
			return getNextTable(cli_table_wdswep, cliData);

	}
	else if(cliData->argc>1){
		//handle 2 or more argument for wdssecu after set wdssecusetbridge --> wless2/wdslink/wdssecu>aesp 12345678
		if ( wdssecusetbridge==2 )
			return getNextTable(cli_table_wdsaes, cliData);
		else if ( wdssecusetbridge==3 )
			return getNextTable(cli_table_wdswep, cliData);

		///Handle the command --> wless2 wdslink wdssecu 2 aesp 12345678
		if (!errorcheckValidDecimal(cliData->tokens[3].token) || !errorcheckIntRange( 1, count, atoi(cliData->tokens[3].token)) )
	  			return CLI_PARAMS_ERR;
		
		strcpy(uci_set_buf, cliData->tokens[3].token);
			
		switch(atoi(uci_set_buf)){
			case 1:	
				//handle too many argument --> wless2/wdslink>wdssecu 1 asda ttttt
				if (cliData->tokenLen>=5)
					return CLI_PARAMS_ERR;
				cli_set_uci(func_buf, "none");
				return CLI_NOTHING;
			case 2:					
				cli_set_uci(func_buf, "aes");
				//Skip "2" when handling "wless2 wdslink wdssecu 2 aesp"
				cliData->argc--;
				return getNextTable(cli_table_wdsaes, cliData);
			case 3:
				cli_set_uci(func_buf, "wep");
				//Skip "3" when handling "wless2 wdslink wdssecu 3 wepk"
				cliData->argc--;
				return getNextTable(cli_table_wdswep, cliData);
			default:
				return CLI_PARAMS_ERR;
		}

	}
}

//Jacy ask to keep wepkey but to take off wepkeylength
/*****************************************************************
* NAME: initialWEPtable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
/*
T_VOID initialWDSWEPtable(T_VOID)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_INT32 i;
T_INT32 ssidCount=getModelssidCount();

	if (ssidCount==4)
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSWEPKey", ssidCount);
	if (ssidCount==8)
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSWEPKey", 16);


	strcpy(uci_get_buf, cli_get_uci(func_buf));
	if (strcmp(uci_get_buf, "")!=0){
		strcpy(CliWDSWEPkeyset.wdswepkey, uci_get_buf);
		CliWDSWEPkeyset.wdswepkeylength=strlen(uci_get_buf);
		//CliWDSWEPkeyset.wdswepkeyset=1;
	}
	//else
		//CliWDSWEPkeyset.wdswepkeyset=0;
}
*/

/*****************************************************************
* NAME: cmdwdswepk
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwdswepk(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 ssidCount;
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
T_INT32 nawds_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	ssidCount=getModelssidCount(operationeMode);

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	
	//get 4 (if ssidcount is 4) or 16 (if ssidcount is 8) for single-radio and 16 (if radio is 2.4G) or 42 (if radio is 5G) for dual-radio
	//nawds_index=get_nawds_index(ssidCount);

	//Modify on 2013-08-07 by Philips to get the correct nawds_index
	nawds_index=get_nawds_index(ssidCount, operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSWEPKey", nawds_index);

	if ( model_radio==7 && operationeMode==OPM_WDSB)
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSWEPKey", wifi_index);

	if(cliData->argc==0){

		strcpy(uci_get_buf, cli_get_uci(func_buf));
			
		tprintf("Current setting: %s (10, 26 or 32 hex digits)\n", uci_get_buf);
		//tprintf("Recognized input format: Please fill (10, 26, 32 hex digits)\n");

		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		
		if ( !errorcheckValidHex(cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("WEP key is not valid Hex digit\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		if ( strlen(cliData->tokens[cliData->tokenLen-1].token)!=10 && strlen(cliData->tokens[cliData->tokenLen-1].token)!=26 && strlen(cliData->tokens[cliData->tokenLen-1].token)!=32 ){
			tprintf("Key length should be (10, 26, 32 Hex digits)\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	
	
	
/*	else if(cliData->argc==1){
		
		if ( !errorcheckValidHex(cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("WEP key is not valid Hex digit\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		//if ( CliWDSWEPkeyset.wdswepkeylength!=strlen(cliData->tokens[cliData->tokenLen-1].token) )
		//	tprintf("WEP key length is incorrect! Please fill %d hex digits WEP Key\n", CliWDSWEPkeyset.wdswepkeylength);
		//else
		//	strcpy(CliWDSWEPkeyset.wdswepkey, cliData->tokens[cliData->tokenLen-1].token);
		switch ( strlen(cliData->tokens[cliData->tokenLen-1].token) ){		
			case 10:
				CliWDSWEPkeyset.wdswepkeylength=10;
				break;
			case 26:
				CliWDSWEPkeyset.wdswepkeylength=26;
				break;
			case 32:
				CliWDSWEPkeyset.wdswepkeylength=32;
				break;
			default:
				tprintf("Key length should be (10, 26, 32 Hex)\n");
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
		}

		strcpy(CliWDSWEPkeyset.wdswepkey, cliData->tokens[cliData->tokenLen-1].token);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}*/
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

//Jacy ask to keep wepkey but to take off wepkeylength
/*****************************************************************
* NAME: cmdwdswepklen
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
/*
CliStatus cmdwdswepklen(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 ssidCount=getModelssidCount();

	if (ssidCount==4)
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSWEPKey", ssidCount);
	if (ssidCount==8)
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSWEPKey", 16);

	if(cliData->argc==0){		
		tprintf("1 - 40/64-bit (10 hex digits)\n");
		tprintf("2 - 104/128-bit (26 hex digits)\n");
		tprintf("3 - 128/152-bit (32 hex digits)\n");
		
		
		//if (CliWDSWEPkeyset.wdswepkeyset==1){
		//	strcpy(uci_get_buf, cli_get_uci(func_buf));
		//	tprintf("Current setting: (%d hex digits)\n", strlen(uci_get_buf));
		//}
		//else
		tprintf("Current setting: (%d hex digits) \n", CliWDSWEPkeyset.wdswepkeylength);

		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//CliWDSWEPkeyset.wdswepkeylengthset=1;
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		if (!errorcheckValidDecimal(uci_set_buf) || !errorcheckIntRange( 1, 3, atoi(uci_set_buf)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		if ( atoi(uci_set_buf)==1 )
			CliWDSWEPkeyset.wdswepkeylength=10;
		if ( atoi(uci_set_buf)==2 )
			CliWDSWEPkeyset.wdswepkeylength=26;
		if ( atoi(uci_set_buf)==3 )
			CliWDSWEPkeyset.wdswepkeylength=32;

//printf("CliWDSWEPkeyset.wdswepkeylength=%d\n", CliWDSWEPkeyset.wdswepkeylength);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}
*/
//Jacy ask to keep wepkey but to take off wepkeylength
/*****************************************************************
* NAME: cmdwdswepaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
/*
CliStatus cmdwdswepaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_INT32 ssidCount=getModelssidCount();

	if (ssidCount==4)
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSWEPKey", ssidCount);
	if (ssidCount==8)
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSWEPKey", 16);

	if(cliData->argc==0){
		
		if ( CliWDSWEPkeyset.wdswepkeylength!=strlen(CliWDSWEPkeyset.wdswepkey) ){
			tprintf("Please fill %d hex digits WEP Key\n", CliWDSWEPkeyset.wdswepkeylength);
			
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		else {
			cli_set_uci(func_buf, CliWDSWEPkeyset.wdswepkey);
			
			//CliWDSWEPkeyset.wdswepkeyset=0;
			//CliWDSWEPkeyset.wdswepkeylengthset=0;

			cliData->tokenLen--;
			return CLI_OK;
		}
    		
	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}
*/

/*****************************************************************
* NAME: cmdwdswepexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwdssecurityexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	wdssecusetbridge=-1;
	//CliWDSWEPkeyset.wdswepkeyset=0;
	//CliWDSWEPkeyset.wdswepkeylengthset=0;
	
	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}

/*****************************************************************
* NAME: cmdwdsaesp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwdsaesp(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 ssidCount;
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
T_INT32 nawds_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	ssidCount=getModelssidCount(operationeMode);	

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	
	//get 4 (if ssidcount is 4) or 16 (if ssidcount is 8) for single-radio and 16 (if radio is 2.4G) or 42 (if radio is 5G) for dual-radio
	//nawds_index=get_nawds_index(ssidCount);

	//Modify on 2013-08-07 by Philips to get the correct nawds_index
	nawds_index=get_nawds_index(ssidCount, operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSAESKey", nawds_index);

	if ( model_radio==7 && operationeMode==OPM_WDSB)
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSAESKey", wifi_index);

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (8-63 characters) or (64 Hexadecimal characters)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

		if ( strlen(cliData->tokens[cliData->tokenLen-1].token)==64 && (!errorcheckValidHex(cliData->tokens[cliData->tokenLen-1].token)) ){
			tprintf("Passphrase is not valid Hex digit\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		if (strlen(cliData->tokens[cliData->tokenLen-1].token)!=64 && (!errorcheckIntRange( 8, 63, strlen(cliData->tokens[cliData->tokenLen-1].token) )) ){
			tprintf("The length of passphrase should be between 8 and 63\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 wdslink links                   */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_WDSAP,   	"wdslink",	cli_table_wdslink,	getNextTable,	"WDS link settings",		"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_wdslink[]= {
//	{OPM_ALL,	"links",	cli_table_links,	getNextTable,	"Link setting",	"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_links[]= {
//	{OPM_ALL,	"macadd",	NULL,			cmdwdsmacadd,	"Add Link MAC address",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"enable",	NULL,			cmdwdsenable,	"Enable link MAC address",	"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"disable",	NULL,			cmdwdsdisable,	"Disable Link MAC address",	"", AUTH_ADMIN, MODEL_ALL}, 
//	{OPM_ALL,	"macdel",	NULL,			cmdwdsmacdel,	"Delete Link MAC address",      "", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_links,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: displaywdslink
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID displaywdslink(T_CHAR* func_buf) {
T_INT32 i;
T_CHAR uci_get_buf[128];
T_CHAR buf[128];
T_CHAR enable[12];
T_INT32 count;

	strcpy(uci_get_buf, cli_get_uci(func_buf));
	count=strlen(uci_get_buf)/13;
	
	if (count==0)
		printf("No WDS link exists\n");
			
	for (i=1; i<=count; i++){
		strncpy(buf, uci_get_buf+(i-1)*13, 13);
		buf[13]='\0';
		if (buf[12]=='v')
			strcpy(enable, "Enable");
		else
			strcpy(enable, "Disable");
		
    		tprintf("%d - %c%c:%c%c:%c%c:%c%c:%c%c:%c%c - %s\n", i, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], buf[8], buf[9], buf[10], buf[11], enable);
    	}
}

/*****************************************************************
* NAME: cmdwdsenable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwdsenable(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 count;
T_INT32 ssidCount;
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
T_INT32 nawds_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	
	//get 4 (if ssidcount is 4) or 16 (if ssidcount is 8) for single-radio and 16 (if radio is 2.4G) or 42 (if radio is 5G) for dual-radio
	//nawds_index=get_nawds_index(ssidCount);

	//Modify on 2013-08-07 by Philips to get the correct nawds_index
	nawds_index=get_nawds_index(ssidCount, operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSPeer", nawds_index);
	sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANEnable", nawds_index);

	if ( model_radio==7 && operationeMode==OPM_WDSB){
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSPeer", wifi_index);
		sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANEnable", wifi_index);
	}
	
	if(cliData->argc==0){		
		displaywdslink(func_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
				
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		count=strlen(uci_get_buf)/13;
		if ( !errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange(1, count, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		uci_get_buf[(atoi(uci_set_buf)*13)-1]='v';
		cli_set_uci(func_buf, uci_get_buf);
		cli_set_uci(func_buf1, "1");

if ( operationeMode==OPM_WDSAP ){
T_CHAR func_buf2[128]="wireless.wifi0.WLANHTMode";
T_CHAR uci_get_buf2[128];
if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
	strcpy(func_buf2, "wireless.wifi1.WLANHTMode");

//get the htmode
strcpy(uci_get_buf2, cli_get_uci(func_buf2));
//If htmode is 20-40			
if ( strcmp(uci_get_buf2, CliHTmodeTable[2].HTmodeName)==0 )		
//set default value of htmode into wireless.wifi0.WLANHTMode or wifi1
	cli_set_uci(func_buf2, CliHTmodeTable[1].HTmodeName);		
}		
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwdsdisable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwdsdisable(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 count;
T_INT32 ssidCount;
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
T_INT32 nawds_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	
	//get 4 (if ssidcount is 4) or 16 (if ssidcount is 8) for single-radio and 16 (if radio is 2.4G) or 42 (if radio is 5G) for dual-radio
	//nawds_index=get_nawds_index(ssidCount);

	//Modify on 2013-08-07 by Philips to get the correct nawds_index
	nawds_index=get_nawds_index(ssidCount, operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSPeer", nawds_index);
	sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANEnable", nawds_index);

	if ( model_radio==7 && operationeMode==OPM_WDSB){
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSPeer", wifi_index);
		sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANEnable", wifi_index);
	}

	if(cliData->argc==0){		
		displaywdslink(func_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );	

		strcpy(uci_get_buf, cli_get_uci(func_buf));
		count=strlen(uci_get_buf)/13;
		
		if ( !errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange(1, count, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		uci_get_buf[(atoi(uci_set_buf)*13)-1]='x';
		cli_set_uci(func_buf, uci_get_buf);
		
		if ( !checkwdsEnable(count, atoi(uci_set_buf), uci_get_buf) )
			cli_set_uci(func_buf1, "0");
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: convertwdsmac
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_CHAR * convertwdsmac(T_CHAR * wdsmac){
T_INT32 i;
T_CHAR result[20];
T_CHAR* token;

	strcpy(result , "");
	
	token = strtok(wdsmac, ":");
	strcat(result , token);
	token = strtok(NULL, ":");
	strcat(result , token);
	token = strtok(NULL, ":");
	strcat(result , token);
	token = strtok(NULL, ":");
	strcat(result , token);
	token = strtok(NULL, ":");
	strcat(result , token);
	token = strtok(NULL, ":");
	strcat(result , token);

	return (T_CHAR*)result;
}

/*****************************************************************
* NAME: cmdwdsmacadd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwdsmacadd(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR buf_Redundancycheck[128];
//T_INT32 count;
T_INT32 ssidCount;
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
T_INT32 nawds_index;
T_INT32 wdslinkCount;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	
	//get 4 (if ssidcount is 4) or 16 (if ssidcount is 8) for single-radio and 16 (if radio is 2.4G) or 42 (if radio is 5G) for dual-radio
	//nawds_index=get_nawds_index(ssidCount);

	//Modify on 2013-08-07 by Philips to get the correct nawds_index
	nawds_index=get_nawds_index(ssidCount, operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSPeer", nawds_index);
	sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANEnable", nawds_index);

	if ( model_radio==7 && operationeMode==OPM_WDSB){
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSPeer", wifi_index);
		sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANEnable", wifi_index);
	}

	if(cliData->argc==0){		
		displaywdslink(func_buf);
		tprintf("Recognized input format: XX:XX:XX:XX:XX:XX    EX: 00:02:6F:BE:F0:7A\n");
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//check the number of mac can not be larger than 4
		strcpy(uci_get_buf, cli_get_uci(func_buf));

		wdslinkCount = getModelwdslinkCount(operationeMode);

		if ( strlen(uci_get_buf) >= wdslinkCount*13 ){
			tprintf("The most number of data set is %d\n", wdslinkCount);
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		if (!errorcheckValidMACaddess( cliData->tokens[cliData->tokenLen-1].token )){
			tprintf("The input is not valid MAC address\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		strcpy(buf_Redundancycheck, uci_set_buf);

		lower2upperMacAddress( uci_set_buf );
		lower2upperMacAddress( buf_Redundancycheck );

		if (!checkRedundancyMACfilterlist( uci_get_buf, convertwdsmac(buf_Redundancycheck) )){
			cliData->tokenLen-=2;
			printf("The input MAC address has already existed\n");
	  		return CLI_PARAMS_ERR;	
		}
				
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		strcat(uci_get_buf, convertwdsmac(uci_set_buf) );
		strcat(uci_get_buf, "v");

		cli_set_uci(func_buf, uci_get_buf);
		cli_set_uci(func_buf1, "1");

if ( operationeMode==OPM_WDSAP ){
T_CHAR func_buf2[128]="wireless.wifi0.WLANHTMode";
T_CHAR uci_get_buf2[128];
if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
	strcpy(func_buf2, "wireless.wifi1.WLANHTMode");

//get the htmode
strcpy(uci_get_buf2, cli_get_uci(func_buf2));

//If htmode is 20-40		
if ( strcmp(uci_get_buf2, CliHTmodeTable[2].HTmodeName)==0 )		
//set default value of htmode into wireless.wifi0.WLANHTMode or wifi1
	cli_set_uci(func_buf2, CliHTmodeTable[1].HTmodeName);		
}		
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwdsmacdel
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwdsmacdel(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 count;
T_CHAR buf[64];
T_INT32 ssidCount;
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
T_INT32 nawds_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	ssidCount=getModelssidCount(operationeMode);

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	
	//get 4 (if ssidcount is 4) or 16 (if ssidcount is 8) for single-radio and 16 (if radio is 2.4G) or 42 (if radio is 5G) for dual-radio
	//nawds_index=get_nawds_index(ssidCount);

	//Modify on 2013-08-07 by Philips to get the correct nawds_index
	nawds_index=get_nawds_index(ssidCount, operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSPeer", nawds_index);
	sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANEnable", nawds_index);

	if ( model_radio==7 && operationeMode==OPM_WDSB){
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSPeer", wifi_index);
		sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANEnable", wifi_index);
	}

	if(cliData->argc==0){		
		displaywdslink(func_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );		

		strcpy(uci_get_buf, cli_get_uci(func_buf));
		count=strlen(uci_get_buf)/13;
		
		if ( !errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange(1, count, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		strcpy(buf, rebuildwdspeer(count, atoi(uci_set_buf), uci_get_buf));

		cli_set_uci(func_buf, buf);
		
		if ( !checkwdsEnable(count, atoi(uci_set_buf), uci_get_buf) )
			cli_set_uci(func_buf1, "0");
	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 network mesh meshact            */
/*                   CLI Command -- wless2 network mesh cmdmeshssid        */
/*                   CLI Command -- wless2 network mesh cmdmeshsecu        */
/*                   CLI Command -- wless2 network mesh cmdmeshpassp       */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"network",	cli_table_network,	getNextTable,	"Wireless network",		"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_network[]= {
//	{OPM_AP,	"mesh",		cli_table_meshset,	getNextTable,	"Mesh settings",	"", AUTH_ANY, C600_ID},
//};

//Modify on 2013-07-04 to add Mesh setting for C600 which is requested by Sam
//CliEntry cli_table_meshset[]= {
//	{OPM_AP,	"meshact",	NULL,			cmdmeshact,	"Mesh active",		"", AUTH_ADMIN, C600_ID},
//	{OPM_AP,	"meshssid",	NULL,			cmdmeshssid,	"Mesh SSID",		"", AUTH_ADMIN, C600_ID},
//	{OPM_AP,	"meshsecu",	NULL,			cmdmeshsecu,	"Mesh security",	"", AUTH_ADMIN, C600_ID},
//	{OPM_AP,	"meshpassp",	NULL,			cmdmeshpassp,	"Mesh passphrase",	"", AUTH_ADMIN, C600_ID},
//};

/*****************************************************************
* NAME: displaymeshMode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 displaymeshMode(T_INT32 argCount) {
T_CHAR func_buf[128]="wireless.w1_index23.MESHEnable";
T_CHAR uci_get_buf[128];
T_INT32 i;
T_INT32 start=0;
T_INT32 stop=2;


	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w0_index23.MESHEnable");

	strcpy(uci_get_buf, cli_get_uci(func_buf));
	
	if ( strcmp(uci_get_buf, "none-mesh")!=0 )
		stop=0;
		
	if (argCount == 0)			
		for (i=start; i<=stop; i++)
			printf("%d - %s\n", CliMeshmodeTable[i].item, CliMeshmodeTable[i].MeshmodeName);
	
	if (argCount == 1)
		return (stop+1);

}


/*****************************************************************
* NAME: cmdmeshact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-04-30
* Modify:   
****************************************************************/
CliStatus cmdmeshact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.w0_index23.MESHEnable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR band[32];
T_INT32 range;
T_INT32 operationeMode=current_opmode;

	
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w1_index23.MESHEnable");

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displaymeshMode(cliData->argc);
		tprintf("Current setting: %s\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		range=displaymeshMode(cliData->argc);
	
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, range, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);			
	
		cli_set_uci(func_buf, CliMeshmodeTable[atoi(uci_set_buf)-1].MeshmodeName);

		
//Modify for C600 on 2013-04-30 when mesh-only or mesh-ap is enabled
if ( strcmp(model_name, "c600")==0 ){
T_INT32 i, start = 0, stop = 7, mesh = 23;

	if ( ( strcmp(CliMeshmodeTable[atoi(uci_set_buf)-1].MeshmodeName, "mesh-only")==0 ) || ( strcmp(CliMeshmodeTable[atoi(uci_set_buf)-1].MeshmodeName, "mesh-ap")==0 ) ){
		if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 ){
			cli_set_uci("wireless.wifi0.hwmode", "11ng");
			cli_set_uci("wireless.wifi0.WLANHTMode", "20");
			cli_set_uci("clientcontrol.clientlimit_2g.enable", "0");
			cli_set_uci("clientcontrol.clientlimit_2g.maxclient", "127");
		}
		if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 ){
			cli_set_uci("wireless.wifi1.hwmode", "11na");
			cli_set_uci("clientcontrol.clientlimit_5g.enable", "0");
			cli_set_uci("clientcontrol.clientlimit_5g.maxclient", "127");
		}
		
		if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 ){
			start += 26;
			stop += 26;
			mesh += 26;
		}
		for (i=start; i<=stop; i++){
			sprintf(func_buf, "wireless.@wifi-iface[%d].rate", i);
			cli_set_uci(func_buf, "auto");
		}
		sprintf(func_buf, "wireless.@wifi-iface[%d].rate", mesh);
		cli_set_uci(func_buf, "auto");

	}
}
		
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdmeshssid
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-04
* Modify:   
****************************************************************/
CliStatus cmdmeshssid(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];

	//Get the information of "mesh enable"
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "wireless.w0_index23.MESHEnable");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w1_index23.MESHEnable");

	strcpy(uci_get_buf, cli_get_uci(func_buf));

	//If mesh is disabled, please enable mesh first
	if( strcmp(uci_get_buf, "none-mesh")==0 ){
		printf("Mesh is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "wireless.w0_index23.ssid");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w1_index23.ssid");
	
	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (32 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 32, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of SSID should not be larger than 32\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		cli_set_uci(func_buf, uci_set_buf);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdmeshsecu
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-04
* Modify:   
****************************************************************/
CliStatus cmdmeshsecu(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	//Get the information of "mesh enable"
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "wireless.w0_index23.MESHEnable");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w1_index23.MESHEnable");

	strcpy(uci_get_buf, cli_get_uci(func_buf));

	//If mesh is disabled, please enable mesh first
	if( strcmp(uci_get_buf, "none-mesh")==0 ){
		printf("Mesh is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "wireless.w0_index23.encryption");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w1_index23.encryption");

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:WPA2-PSK AES, 0:None)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		if ( atoi(uci_set_buf)==0 )
			cli_set_uci(func_buf, "none");
		if ( atoi(uci_set_buf)==1 )
			cli_set_uci(func_buf, "mesh aes");
					
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdmeshpassp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-04
* Modify:   
****************************************************************/
CliStatus cmdmeshpassp(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	//Get the information of "mesh enable"
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "wireless.w0_index23.MESHEnable");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w1_index23.MESHEnable");

	strcpy(uci_get_buf, cli_get_uci(func_buf));

	//If mesh is disabled, please enable mesh first
	if( strcmp(uci_get_buf, "none-mesh")==0 ){
		printf("Mesh is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "wireless.w0_index23.AESKey");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w1_index23.AESKey");
	
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (8-63 characters) or (64 Hexadecimal characters)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		
		if ( strlen(cliData->tokens[cliData->tokenLen-1].token)==64 && (!errorcheckValidHex(cliData->tokens[cliData->tokenLen-1].token)) ){
			tprintf("Passphrase is not valid Hex digit\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		if (strlen(cliData->tokens[cliData->tokenLen-1].token)!=64 && (!errorcheckIntRange( 8, 63, strlen(cliData->tokens[cliData->tokenLen-1].token) )) ){
			tprintf("The length of passphrase should be between 8 and 63\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		strcpy(CliWPAPSKset.passphrase, uci_set_buf);
		CliWPAPSKset.passphraseset=1;

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}


/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 network wlmode                  */
/*                   CLI Command -- wless2 network htmode                  */
/*                   CLI Command -- wless2 network extch                   */
/*                   CLI Command -- wless2 network ch                      */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"network",	cli_table_network,	getNextTable,	"Wireless network",		"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_network[]= {
//	{OPM_ALL,	"wlmode",	NULL,   		cmdwlmode,	"Wireless mode",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP,	"htmode",	NULL,   		cmdhtmode,	"Channel ht mode",		"", AUTH_ANY,	MODEL_ALL},
//	{OPM_AP,	"extch",	NULL,   		cmdextch,	"Extension channel",		"", AUTH_ADMIN, MODEL_2G},
//	{OPM_AP,	"ch",    	NULL,    		cmdchannel,	"Channel/Frequency",		"", AUTH_ADMIN, MODEL_ALL},
//};


/*****************************************************************
* NAME: checksecurity_wep_tkip
* ---------------------------------------------------------------
* FUNCTION: If the encryption of wdslink or ssid includes WEP or TKIP then return "wep_tkip_exist=1"
* INPUT:    
* OUTPUT:   
* Author:   Philips modified on 2012-11-27 to check whether the encrytion is wep ,tkip or not
* Modify:   
****************************************************************/
T_INT32 checksecurity_wep_tkip(T_INT32 operationeMode) {
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_INT32 wep_tkip_exist=0;
T_INT32 wifi_index;
T_INT32 nawds_index;
T_INT32 ssidCount=getModelssidCount(operationeMode);
T_INT32 i;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	
	//get 4 (if ssidcount is 4) or 16 (if ssidcount is 8) for single-radio and 16 (if radio is 2.4G) or 42 (if radio is 5G) for dual-radio
	//nawds_index=get_nawds_index(ssidCount);

	//Modify on 2013-08-07 by Philips to get the correct nawds_index
	nawds_index=get_nawds_index(ssidCount, operationeMode);
	
	//check whether wdslink encryption is wep or not
	if (operationeMode==OPM_WDSB){
		//get wdslink encryption
		sprintf(func_buf, "wireless.@wifi-iface[%d].encryption", nawds_index);
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		if (strstr(uci_get_buf, "wep")!=NULL)
			wep_tkip_exist=1;
//printf("WDSB Check WEP --- wireless.@wifi-iface[%d].encryption=%s, wep_tkip_exist=%d\n", nawds_index, uci_get_buf, wep_tkip_exist);			
	}
	//check whether wireless encryption is wep, tkip or not
	if (operationeMode==OPM_CB||operationeMode==OPM_WDSSTA||operationeMode==OPM_AR||operationeMode==OPM_RP){
		//get wireless encryption
		sprintf(func_buf, "wireless.@wifi-iface[%d].encryption", wifi_index);		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		if (strstr(uci_get_buf, "tkip")!=NULL||strstr(uci_get_buf, "wep")!=NULL)
			wep_tkip_exist=1;
//printf("CB, WDSSTA, CR and RP Check WEP and TKIP --- wireless.@wifi-iface[%d].encryption=%s, wep_tkip_exist=%d\n", wifi_index, uci_get_buf, wep_tkip_exist);
	}
	//check whether wireless encryption of all SSID is wep, tkip or not
	if (operationeMode==OPM_AP||operationeMode==OPM_WDSAP||operationeMode==OPM_AR){
		for (i=wifi_index; i<wifi_index+ssidCount; i++){
			//get wireless encryption
			sprintf(func_buf, "wireless.@wifi-iface[%d].encryption", i);
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			
			if (strstr(uci_get_buf, "tkip")!=NULL||strstr(uci_get_buf, "wep")!=NULL)
				wep_tkip_exist=1;
				
//printf("AP, WDSAP, and AR Check WEP and TKIP --- wireless.@wifi-iface[%d].encryption=%s, wep_tkip_exist=%d\n", i, uci_get_buf, wep_tkip_exist);
		}
	}

	return wep_tkip_exist;
}

/*****************************************************************
* NAME: displaywirelessmode
* ---------------------------------------------------------------
* FUNCTION: 
*	Display wirelessmode according to "band" and "operation Mode".
*	1 - 802.11 B Only
*	2 - 802.11 G Only
*	3 - 802.11 B/G Mixed
*		:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID displaywirelessmode(T_CHAR* band, T_INT32 operationeMode)
{
int i;
T_INT32 wep_tkip_exist=0;

	//Philips modified on 2012-11-27 to check whether the encrytion is wep ,tkip or not
	wep_tkip_exist = checksecurity_wep_tkip(operationeMode);

	//display 8 kinds of wireless mode
	//{1, "2.4G", "11b" , "802.11 B Only"},		//Single Radio and Dual Radio
	//{2, "2.4G", "11g_pure" , "802.11 G Only"},
	//{3, "2.4G", "11g" , "802.11 B/G Mixed"},
	//{4, "2.4G", "11ng" , "802.11 B/G/N Mixed"},
	//{5, "2.4G", "11n_pure" , "802.11 N Only"},
	
	//{6, "5G", "11n_pure" , "802.11 N Only"},	//"11na_pure" for Dual Radio
	//{7, "5G", "11a_pure" , "802.11 A Only"},	//"11a" for Dual Radio
	//{8, "5G", "11na" , "802.11 A/N Mixed"}
	
	//{9, "5G", "11naac" , "802.11 AC"},

//Modify for AP100 on 2012-11-08
if ( strcmp(model_name, "ap100")!=0 ){


	for (i=0; i<9; i++){				
		if (strcmp(band, CliWirelessmodeTable[i].band)==0){
			if (strcmp(band, "2.4G")==0){	
				//while opmode=ap, wdsap, wdsbr, ar display 1~5 
				if ( operationeMode==OPM_AP || operationeMode==OPM_WDSAP || operationeMode==OPM_WDSB || operationeMode==OPM_AR){
					// Does not display 802.11 N Only mode while security=wep or tkip
					if ( wep_tkip_exist==1 && i==4 ) 
						break;

					printf("%d - %s\n", CliWirelessmodeTable[i].item, CliWirelessmodeTable[i].wirelessmodeDescription);
				}

				//Wireless mode should be 802.11 B/G/N Mixed mode while opmode=cb, wdssta, cr, rp
				if ( operationeMode==OPM_CB || operationeMode==OPM_WDSSTA || operationeMode==OPM_CBRT || operationeMode==OPM_RP){
					//Only display B/G/N Mixed mode
					if (i==3){
						printf("%d - %s\n", CliWirelessmodeTable[i].item-3, CliWirelessmodeTable[i].wirelessmodeDescription);
						break;
					}
				}

			}
			
			if (strcmp(band, "5G")==0){
				//while opmode=ap, wdsap, wdsbr, ar display 6~8
				//Modify on 2013-07-24 for EAP1750 to support 802.11AC --- while opmode=ap, wdsap, wdsbr, ar display 6~9
				if ( operationeMode==OPM_AP || operationeMode==OPM_WDSAP || operationeMode==OPM_WDSB || operationeMode==OPM_AR){

					if ( wep_tkip_exist==1 ){
						//while security is wep or tkip then doesn't display 802.11 N Only mode
						if (i==6 || i==7)
							printf("%d - %s\n", CliWirelessmodeTable[i].item-6, CliWirelessmodeTable[i].wirelessmodeDescription);
						
						//Modify on 2013-07-24 for EAP1750 to support 802.11AC --- while opmode=ap, wdsap, wdsbr, ar display 6~9
						if ( (i==8) && (model_ID & MODEL_AC) )
							printf("%d - %s\n", CliWirelessmodeTable[i].item-6, CliWirelessmodeTable[i].wirelessmodeDescription);

					}
					//while security isn't wep or tkip then display 6~8
					else{
						if (i==5 || i==6 || i==7)
							printf("%d - %s\n", CliWirelessmodeTable[i].item-5, CliWirelessmodeTable[i].wirelessmodeDescription);

						//Modify on 2013-07-24 for EAP1750 to support 802.11AC --- while opmode=ap, wdsap, wdsbr, ar display 6~9
						if ( (i==8) && (model_ID & MODEL_AC) )
							printf("%d - %s\n", CliWirelessmodeTable[i].item-5, CliWirelessmodeTable[i].wirelessmodeDescription);
						
					}
				
				}				 
				 
				//Wireless mode should be 802.11 A/N Mixed mode while opmode=cb, wdssta, cr, rp
				if ( (operationeMode==OPM_CB || operationeMode==OPM_WDSSTA || operationeMode==OPM_CBRT || operationeMode==OPM_RP) ){
					//Only display 802.11 A/N Mixed mode 
					//if (i==7){
					//	printf("%d - %s\n", CliWirelessmodeTable[i].item-7, CliWirelessmodeTable[i].wirelessmodeDescription);
					//	break;
					//}

					//Modify on 2013-07-24 for EAP1750 to support 802.11AC --- while opmode=ap, wdsap, wdsbr, ar display 6~9
					if ( model_ID & MODEL_AC )
						//Only display 802.11 AC mode
						if (i==8)
							printf("%d - %s\n", CliWirelessmodeTable[i].item-8, CliWirelessmodeTable[i].wirelessmodeDescription);
					
						//Only display 802.11 A/N Mixed mode 
					else 	if (i==7){
							printf("%d - %s\n", CliWirelessmodeTable[i].item-7, CliWirelessmodeTable[i].wirelessmodeDescription);
							break;
						}

				}
			
			}/*if (strcmp(band, "5G")==0)*/
		}

	}//for loop
	
}

	//Modify for AP100 on 2012-11-08
	//display 9 kinds of wireless mode	
	//{10, "2.4G",	"11b" ,		"802.11 B Only"},		//2.4G
	//{11, "2.4G",	"11g_pure" ,	"802.11 G Only"},
	//{12, "2.4G",	"11g" ,		"802.11 B/G Mixed"},
	//{13, "2.4G",	"11ng" ,	"802.11 B/G/N Mixed"},
	//{14, "2.4G",	"11n_pure" ,	"802.11 N Only (2.4G)"},
	
	//{15, "5G"	"11na_pure" , 	"802.11 N Only (5G)"},		//5G
	//{16, "5G", 	"11a" , 	"802.11 A Only"},
	//{17, "5G"	"11na" , 	"802.11 A/N Mixed"},
	
	//{18, "5G", 	"11abgn" , 	"802.11 A/B/G/N Mixed"},	//For CB and WDSSTA mode

	if ( (strcmp(model_name, "ap100")==0) ){
		//Modify for AP100 on 2012-11-08
		for (i=9; i<18; i++){
			//while opmode=ap, wdsap, wdsbr display 9~16 
			if ( operationeMode==OPM_AP || operationeMode==OPM_WDSAP || operationeMode==OPM_WDSB ){
				//While security is wep or tkip doesn't display 802.11 N Only mode
				if ( wep_tkip_exist==1 && (i==13 || i==14) ) 
					continue;
				//Display wireless mode for 2.4G
				if ( i<=13 )
					printf("%d - %s\n", CliWirelessmodeTable[i].item-9, CliWirelessmodeTable[i].wirelessmodeDescription);
				//Display wireless mode for 5G
				if ( i>13 ){
					//Don't display A/B/G/N mode
					if (i==17)
						continue;
					if ( wep_tkip_exist==1 )
						printf("%d - %s\n", CliWirelessmodeTable[i].item-11, CliWirelessmodeTable[i].wirelessmodeDescription);
					else
						printf("%d - %s\n", CliWirelessmodeTable[i].item-9, CliWirelessmodeTable[i].wirelessmodeDescription);
				}
			}

			//Wireless mode should be 802.11 A/B/G/N Mixed mode while opmode=cb, wdssta
			if ( operationeMode==OPM_CB || operationeMode==OPM_WDSSTA ){
				//Only display A/B/G/N mode
				if (i==17)
					printf("%d - %s\n", CliWirelessmodeTable[i].item-17, CliWirelessmodeTable[i].wirelessmodeDescription);
			}
			//Skip the following code
			continue;
		}
	}

}

/*****************************************************************
* NAME: searchwirelessmode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_CHAR* searchwirelessmode(T_CHAR* code)
{
int i;
//T_INT32 ssidCount=0;
//T_INT32 operationeMode=current_opmode;
	
//	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
//		operationeMode=current_opmode_2;
//	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
//		operationeMode=current_opmode_5;			
//	ssidCount=getModelssidCount(operationeMode);

//Modify for AP100 on 2012-11-08			
if ( (strcmp(model_name, "ap100")==0) ){
	for (i=9; i<18; i++){
		if ( strcmp(code, CliWirelessmodeTable[i].wirelessmodeName)==0 )
			break;			
	}
	return CliWirelessmodeTable[i].wirelessmodeDescription;
}
	//11na_pure of dual-radio is changed to 11n_pure of single-radio for search
	if  ( model_radio==7 && (strcmp(current_radio_flag, "5G")==0) && (strcmp(code, "11na_pure")==0) )
			strcpy(code, "11n_pure");
	//11a of dual-radio is changed to 11a_pure of single-radio for search	
	if  ( model_radio==7 && (strcmp(current_radio_flag, "5G")==0) && (strcmp(code, "11a")==0) )
			strcpy(code, "11a_pure");

	//Modify on 2012-12-24 by Philips which is requested by Jacy for ENS500 and ENS500EXT("802.11 N Only" is "11na_pure" not "11n_pure")
	if ( (strcmp(model_name, "ens500")==0 || strcmp(model_name, "ens500ext")==0) && (strcmp(code, "11na_pure")==0) )
		strcpy(code, "11n_pure");
	
	//Modify on 2012-12-25 by Philips which is requested by Jacy for ENS500 and ENS500EXT("802.11 A" is "11a" not "11a_pure")
	if ( (strcmp(model_name, "ens500")==0 || strcmp(model_name, "ens500ext")==0) && (strcmp(code, "11a")==0) )
		strcpy(code, "11a_pure");
		
	for (i=0; i<9; i++){
		if ( strcmp(code, CliWirelessmodeTable[i].wirelessmodeName)==0 )
			break;			
	}
	
	return CliWirelessmodeTable[i].wirelessmodeDescription;
}

/*****************************************************************
* NAME: findrangeWirelessMode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 findrangeWirelessMode(T_CHAR* band, T_INT32 operationeMode)
{
//T_INT32 wep=0;
//T_CHAR encry_buf[128];
//T_CHAR encry_buf1[128];
T_INT32 range;

T_INT32 wep_tkip_exist=0;

	//Philips modified on 2012-11-27 to check whether the encrytion is wep ,tkip or not
	wep_tkip_exist = checksecurity_wep_tkip(operationeMode);
/*
	if (operationeMode==OPM_AP){
		strcpy(encry_buf, cli_get_uci("wireless.@wifi-iface[0].encryption"));
		if (strstr(encry_buf, "wep")!=NULL )
			wep=1;
	}
	else if (operationeMode==OPM_WDSAP){
		strcpy(encry_buf, cli_get_uci("wireless.@wifi-iface[0].encryption"));
		strcpy(encry_buf1, cli_get_uci("wireless.@wifi-iface[4].encryption"));
		if (strstr(encry_buf, "wep")!=NULL || strstr(encry_buf1, "wep")!=NULL)
			wep=1;
	}
	else if (operationeMode==OPM_WDSB){
		strcpy(encry_buf1, cli_get_uci("wireless.@wifi-iface[4].encryption"));
		if (strstr(encry_buf1, "wep")!=NULL )
			wep=1;		
	}
*/
	
	//Modify for AP100 on 2012-11-08
	//display 9 kinds of wireless mode	
	//{10, "2.4G",	"11b" ,		"802.11 B Only"},		//2.4G
	//{11, "2.4G",	"11g_pure" ,	"802.11 G Only"},
	//{12, "2.4G",	"11g" ,		"802.11 B/G Mixed"},
	//{13, "2.4G",	"11ng" ,	"802.11 B/G/N Mixed"},
	//{14, "2.4G",	"11n_pure" ,	"802.11 N Only (2.4G)"},
	
	//{15, "5G"	"11na_pure" , 	"802.11 N Only (5G)"},		//5G
	//{16, "5G", 	"11a" , 	"802.11 A Only"},
	//{17, "5G"	"11na" , 	"802.11 A/N Mixed"},
	
	//{18, "5G", 	"11abgn" , 	"802.11 A/B/G/N Mixed"},	//For CB and WDSSTA mode
				
if ( (strcmp(model_name, "ap100")==0) ){
	//display "802.11 A/B/G/N Mixed" while opmode=cb, wdssta	
	if ( operationeMode==OPM_CB || operationeMode==OPM_WDSSTA ){
		return 1;
	}
	else{
		//display 9~16 while security is wep or tkip
		if ( wep_tkip_exist==1 )
			return 6;
		else
			return 8;
	}
}
	//display 8 kinds of wireless mode
	//{1, "2.4G", "11b" , "802.11 B Only"},		//Single Radio and Dual Radio
	//{2, "2.4G", "11g_pure" , "802.11 G Only"},
	//{3, "2.4G", "11g" , "802.11 B/G Mixed"},
	//{4, "2.4G", "11ng" , "802.11 B/G/N Mixed"},
	//{5, "2.4G", "11n_pure" , "802.11 N Only"},
	
	//{6, "5G", "11n_pure" , "802.11 N Only"},	//"11na_pure" for Dual Radio
	//{7, "5G", "11a_pure" , "802.11 A Only"},	//"11a" for Dual Radio
	//{8, "5G", "11na" , "802.11 A/N Mixed"}
	//{9, "5G", "11naac" , "802.11 AC"},
	
	if (strcmp(band, "2.4G")==0){
		 //display 4 while opmode=cb, wdssta, cr, rp	
		if ( operationeMode==OPM_CB || operationeMode==OPM_WDSSTA || operationeMode==OPM_CBRT || operationeMode==OPM_RP ){
			return 1;
		}
		else{
			 //display 1~4 while security is wep or tkip
			if ( wep_tkip_exist==1 )
				return 4;
			else
				return 5;
		}
	}
	if (strcmp(band, "5G")==0){
		 //display 8 while opmode=cb, wdssta, cr, rp
		if ( (operationeMode==OPM_CB || operationeMode==OPM_WDSSTA || operationeMode==OPM_CBRT || operationeMode==OPM_RP) ){
			return 1;
		}
		else{
			 //display 7~8 while security is wep or tkip
			if ( wep_tkip_exist==1 )
				//Modify on 2013-07-24 for EAP1750 to support 802.11AC --- while opmode=ap, wdsap, wdsbr, ar display 6~9
				if ( model_ID & MODEL_AC )
					return 3;
				else
					return 2;
			else
				//Modify on 2013-07-24 for EAP1750 to support 802.11AC --- while opmode=ap, wdsap, wdsbr, ar display 6~9
				if ( model_ID & MODEL_AC )
					return 4;
				else
					return 3;
		}
	}

}

/*****************************************************************
* NAME: convertWirelessmodeIndex
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 convertWirelessmodeIndex(T_CHAR* band, T_INT32 operationeMode, T_INT32 index)
{
//T_INT32 wep=0;
T_CHAR encry_buf[128];
T_CHAR encry_buf1[128];
T_INT32 range;

T_INT32 wep_tkip_exist=0;

	//Philips modified on 2012-11-27 to check whether the encrytion is wep ,tkip or not
	wep_tkip_exist = checksecurity_wep_tkip(operationeMode);

/*	
	if (operationeMode==OPM_AP){
		strcpy(encry_buf, cli_get_uci("wireless.@wifi-iface[0].encryption"));
		if (strstr(encry_buf, "wep")!=NULL )
			wep=1;
	}
	else if (operationeMode==OPM_WDSAP){
		strcpy(encry_buf, cli_get_uci("wireless.@wifi-iface[0].encryption"));
		strcpy(encry_buf1, cli_get_uci("wireless.@wifi-iface[4].encryption"));
		if (strstr(encry_buf, "wep")!=NULL || strstr(encry_buf1, "wep")!=NULL)
			wep=1;
	}
	else if (operationeMode==OPM_WDSB){
		strcpy(encry_buf1, cli_get_uci("wireless.@wifi-iface[4].encryption"));
		if (strstr(encry_buf1, "wep")!=NULL )
			wep=1;		
	}
*/

	//Modify for AP100 on 2012-11-08
	//display 9 kinds of wireless mode	
	//{10, "2.4G",	"11b" ,		"802.11 B Only"},		//2.4G
	//{11, "2.4G",	"11g_pure" ,	"802.11 G Only"},
	//{12, "2.4G",	"11g" ,		"802.11 B/G Mixed"},
	//{13, "2.4G",	"11ng" ,	"802.11 B/G/N Mixed"},
	//{14, "2.4G",	"11n_pure" ,	"802.11 N Only (2.4G)"},
	
	//{15, "5G"	"11na_pure" , 	"802.11 N Only (5G)"},		//5G
	//{16, "5G", 	"11a" , 	"802.11 A Only"},
	//{17, "5G"	"11na" , 	"802.11 A/N Mixed"},
	
	//{18, "5G", 	"11abgn" , 	"802.11 A/B/G/N Mixed"},	//For CB and WDSSTA mode

//Modify for AP100 on 2012-11-09			
if ( (strcmp(model_name, "ap100")==0) ){
	//display 18 while opmode=cb, wdssta	
	if ( operationeMode==OPM_CB || operationeMode==OPM_WDSSTA ){
		return index+17;
	}
	else{
		//display 10~17 but no 14, 15 while security is wep
		if ( wep_tkip_exist==1 )
			if (index>=5)
				return index+11;
			else
				return index+9;
		
		//display 10~17 while security is not wep
		return index+9;
	}
}

	if (strcmp(band, "2.4G")==0){
		//display 4 while opmode=cb, wdssta, cr, rp	
		if ( operationeMode==OPM_CB || operationeMode==OPM_WDSSTA || operationeMode==OPM_CBRT || operationeMode==OPM_RP ){
			return index+3;
		}
		else{
			//display 1~4 while security=wep
			if ( wep_tkip_exist==1 )
				return index;
			else
				return index;
		}
	}
	else if (strcmp(band, "5G")==0){
		 //display 8 while opmode=cb, wdssta, cr, rp
		if ( (operationeMode==OPM_CB || operationeMode==OPM_WDSSTA || operationeMode==OPM_CBRT || operationeMode==OPM_RP) ){
			//Modify on 2013-07-24 for EAP1750 to support 802.11AC --- while opmode=ap, wdsap, wdsbr, ar display 6~9
			if ( model_ID & MODEL_AC )
				return index+8;
			else
				return index+7;
			
		}
		else{
			//display 7~8 while security=wep
			if ( wep_tkip_exist==1 )
				return index+6;
			else
				return index+5;
		}
	}/*else if (strcmp(band, "5G")==0)*/
}

/*****************************************************************
* NAME: cmdwlmode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   ###check the input band should be correct
****************************************************************/
CliStatus cmdwlmode(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.wifi0.hwmode";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR band[32];
T_INT32 retval_int;
T_INT32 range;
T_INT32 operationeMode=current_opmode;


//Modify for C600 on 2013-04-30 when mesh-only is enabled
if ( strcmp(model_name, "c600")==0 ){
T_CHAR func_buf1[128]="wireless.w0_index23.MESHEnable";


	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf1, "wireless.w1_index23.MESHEnable");
	strcpy(uci_get_buf, cli_get_uci(func_buf1));

	
	if ( (strcmp(uci_get_buf, "mesh-only")==0) && (cliData->argc==1) ){
		printf("Wireless Mode can't be set when mesh-only is enabled.\n");
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
}

	
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.wifi1.hwmode");
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
	
	//Get the current band information --- 2.4G or 5G		
	if ( model_radio==2 ) 
  		strcpy(band, "2.4G");
	if ( model_radio==5 ) 
  		strcpy(band, "5G");
  	if ( model_radio==7 ) 
  		strcpy(band, current_radio_flag);

	if(cliData->argc==0){
		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displaywirelessmode(band, operationeMode);
		tprintf("Current setting: %s\n", searchwirelessmode(uci_get_buf));
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		range=findrangeWirelessMode(band, operationeMode);
	
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, range, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);			
		
		retval_int=convertWirelessmodeIndex(band, operationeMode, atoi(uci_set_buf));
	
		//dual-radio is 11na_pure; single-radio is 11n_pure
		if  (model_radio==7 && (strcmp(current_radio_flag, "5G")==0) && retval_int==6)
			cli_set_uci(func_buf, "11na_pure");
		
		//dual-radio is 11a; single-radio is 11a_pure
		else if  (model_radio==7 && (strcmp(current_radio_flag, "5G")==0) && retval_int==7)
			cli_set_uci(func_buf, "11a");
		
		//Modify on 2012-12-24 by Philips which is requested by Jacy for ENS500 and ENS500EXT("802.11 N Only" is "11na_pure" not "11n_pure")
		else if ( (strcmp(model_name, "ens500")==0 || strcmp(model_name, "ens500ext")==0) && retval_int==6 )
			cli_set_uci(func_buf, "11na_pure");
		
		//Modify on 2012-12-25 by Philips which is requested by Jacy for ENS500 and ENS500EXT("802.11 A" is "11a" not "11a_pure")
		else if ( (strcmp(model_name, "ens500")==0 || strcmp(model_name, "ens500ext")==0) && retval_int==7 )
			cli_set_uci(func_buf, "11a");
			
		else 
			cli_set_uci(func_buf, CliWirelessmodeTable[retval_int-1].wirelessmodeName);

//Modify for AP100 on 2012-11-09
if ( strcmp(model_name, "ap100")==0 ){			
	if ( retval_int>=9 && retval_int<=13 ){
	//	printf("ap100 Change to 2.4G\n");
		strcpy(current_radio_flag, "2.4G");
	}			
	if ( retval_int>=14 && retval_int<=16 ){
	//	printf("ap100 Change to 5G\n");
		strcpy(current_radio_flag, "5G");
	}			
}
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: displayHTmode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 displayHTmode(T_INT32 argCount, T_CHAR* wlmode) {
T_INT32 i;
T_CHAR func_buf[128]="wireless.wifi0.country";
T_CHAR uci_get_buf[128];
T_INT32 retval_int;
T_CHAR band[32];

//Modify on 2012-12-13 by Philips which requested by Jacy to display and set HT mode to be 40 when WDSB and WDSAP with NAWDS enabled
T_CHAR func_buf1[128];
T_INT32 ht40=0;
T_INT32 ssidCount;
T_INT32 wdslinkCount;
T_INT32 nawds_index;
T_INT32 operationeMode=current_opmode;
T_CHAR * ptr;


	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
	
	if ( operationeMode==OPM_WDSAP ){	
		//Get the number of the WDS link EX:uci get wireless.@wifi-iface[16].WLANWDSPeer --> "00026F371667v00026F371666v"
		ssidCount=getModelssidCount(operationeMode);
		//nawds_index=get_nawds_index(ssidCount);

		//Modify on 2013-08-07 by Philips to get the correct nawds_index		
		nawds_index=get_nawds_index(ssidCount, operationeMode);
		
		sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANWDSPeer", nawds_index);
		strcpy(uci_get_buf, cli_get_uci(func_buf1));
		//Check whether if one of NAWDS is enabled 
		ptr = strchr(uci_get_buf, 'v');
		if ( ptr != NULL )
			ht40=1; 
	}

	if ( operationeMode==OPM_WDSB )
		ht40=1;	

	//get the country code EX.the code of "Colombia" is 170
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	
	//get the index for the country code EX.the index of "Colombia"(170) is 20
	retval_int=atoi(searchcountrytable(uci_get_buf, "INT"));

	if ( model_radio==2 ) 
  		strcpy(band, "2.4G");
	if ( model_radio==5 ) 
  		strcpy(band, "5G");
  	if ( model_radio==7 ) 
  		strcpy(band, current_radio_flag);	
	
	//CliHTmodeTable[0]="20", CliHTmodeTable[1]="40", CliHTmodeTable[2]="20-40"
	for (i=0; i<3; i++){

		//check whether this country only allow HTmode to be set to 20 in 5G
		if ( (i>0) && ( (strcmp(band, "5G")==0) && (CliCountryTable[retval_int].htmodeAllow==2) ) )
			break;

		//Modify on 2013-03-04 by Philips which requested by Jacy to display and set HT mode to be 20 or 40 (20/40 is not allowed) in 5G
		if ( (i==2) && (strcmp(band, "5G")==0) )
			break;

		//Modify on 2012-12-13 by Philips which requested by Jacy to display and set HT mode to be 20 or 40 (20/40 is not allowed) when WDSB and WDSAP with NAWDS enabled
		if (argCount==0){
			if ( ht40==1 && i==2 )
				break;
			else
				printf("%d - %s\n", CliHTmodeTable[i].item, CliHTmodeTable[i].HTmodeName);
		}
	}
	
	//Modify on 2013-07-25 for EAP1750 to support 802.11AC --- display HT mode = 20, 40, 80 while wlmode=11naac 
	if ( (argCount==0) && (strcmp(wlmode, "11naac")==0) && (CliCountryTable[retval_int].htmodeAllow!=2) )
		printf("%d - %s\n", CliHTmodeTable[3].item-1, CliHTmodeTable[3].HTmodeName);
	if ( (argCount==1) && (strcmp(wlmode, "11naac")==0) && (CliCountryTable[retval_int].htmodeAllow!=2) )
		return 3;
		
	if ( argCount==1 && ht40==1 )
		return 2;
	else	
		//retun option range when argc==1
		return i;
}


/*****************************************************************
* NAME: cmdhtmode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdhtmode(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.wifi0.WLANHTMode";
T_CHAR func_buf1[128]="wireless.wifi0.hwmode";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;
T_INT32 stop;


//Modify for C600 on 2013-04-30 when mesh-only is enabled
if ( (strcmp(model_name, "c600")==0) && (strcmp(current_radio_flag, "2.4G")==0) ){
T_CHAR func_buf2[128]="wireless.w0_index23.MESHEnable";

	strcpy(uci_get_buf, cli_get_uci(func_buf2));
	
	if ( (strcmp(uci_get_buf, "mesh-only")==0) && (cliData->argc==1) ){
		printf("Channel HT Mode can't be set when mesh-only is enabled.\n");
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
}


	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 ){
		strcpy(func_buf, "wireless.wifi1.WLANHTMode");
		strcpy(func_buf1, "wireless.wifi1.hwmode");
	}
	
	//get the wireless mode
	strcpy(uci_get_buf1, getWirelessmode(func_buf1));
	
	if(cliData->argc==0){
		//when wireless mode is N, B/G/N or A/N
		if ( strcmp(uci_get_buf1, "11b")!=0 && strcmp(uci_get_buf1, "11g_pure")!=0 && strcmp(uci_get_buf1, "11g")!=0 && strcmp(uci_get_buf1, "11a_pure")!=0 && strcmp(uci_get_buf1, "11a")!=0 ){
			//display the htmode
			displayHTmode(cliData->argc, uci_get_buf1);
			//get the htmode
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s MHz\n", uci_get_buf);		
    		}
    		//when wireless mode is B, G, B/G or A
    		else
    			tprintf("No HT mode to be set\n");
    		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//when wireless mode is B, G, B/G or A
		if ( strcmp(uci_get_buf1, "11b")==0 || strcmp(uci_get_buf1, "11g_pure")==0 || strcmp(uci_get_buf1, "11g")==0 || strcmp(uci_get_buf1, "11a_pure")==0 || strcmp(uci_get_buf1, "11a")==0 ){
			tprintf("No HT mode to be set\n");
			cliData->tokenLen-=2;
			return CLI_PARAMS_ERR;
		}
		//when wireless mode is N, B/G/N or A/N
		else{	
			//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
			if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
				sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );			
			
			//error check for htmode selection
			stop = displayHTmode(cliData->argc, uci_get_buf1);
			
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, stop, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
				cliData->tokenLen-=2;
		  		return CLI_PARAMS_ERR;	
			}

			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

			retval_int=atoi(uci_set_buf)-1;
			
			//Modify on 2013-08-29 for EAP1750 to support 802.11AC --- set HT mode = 20, 40, 80 while wlmode=11naac 
			if ( strcmp(uci_get_buf1, "11naac")==0  && (retval_int==2) )
				retval_int=3;
			
			//set htmode selection into wireless.wifi0.WLANHTMode or wifi1
			cli_set_uci(func_buf, CliHTmodeTable[retval_int].HTmodeName);
			cliData->tokenLen-=2;
			return CLI_NOTHING;
		}
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdextch
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdextch(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.wifi0.WLANExtChannel";
T_CHAR func_buf1[128]="wireless.wifi0.hwmode";
T_CHAR func_buf2[128]="wireless.wifi0.WLANHTMode";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_get_buf2[128];
T_CHAR uci_set_buf[128];

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 ){
		strcpy(func_buf, "wireless.wifi1.WLANExtChannel");
		strcpy(func_buf1, "wireless.wifi1.hwmode");
		strcpy(func_buf2, "wireless.wifi1.WLANHTMode");
	}

	if(cliData->argc==0){
		strcpy(uci_get_buf1, getWirelessmode(func_buf1));//WLmode
		if ( strcmp(uci_get_buf1, "11b")!=0 && strcmp(uci_get_buf1, "11g_pure")!=0 && strcmp(uci_get_buf1, "11g")!=0 && strcmp(uci_get_buf1, "11a_pure")!=0 && strcmp(uci_get_buf1, "11a")!=0 ){
				
			strcpy(uci_get_buf2, cli_get_uci(func_buf2));//HTmode
			if ( strcmp(uci_get_buf2, "20")!=0 ){
				strcpy(uci_get_buf, cli_get_uci(func_buf));
				tprintf("Current setting: %s (1:Lower Channel, 0:Upper Channel)\n", uci_get_buf);
			}
			else
				tprintf("No Extension Channel to be set\n");
   		}
		else
			tprintf("No Extension Channel to be set\n");

		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
		
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		strcpy(uci_get_buf1, getWirelessmode(func_buf1));//WLmode
		//ExtChannel only for 2.4G(model_radio==2 and model_radio==7)
		//if ( (strcmp(uci_get_buf1, "11b")!=0 && strcmp(uci_get_buf1, "11g_pure")!=0 && strcmp(uci_get_buf1, "11g")!=0) && (model_radio==2 || ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )) ){	
		//ExtChannel only for 2.4G(model_radio==2 and model_radio==7)
		if (model_radio==2 || ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )){
			
			if (strcmp(uci_get_buf1, "11b")!=0 && strcmp(uci_get_buf1, "11g_pure")!=0 && strcmp(uci_get_buf1, "11g")!=0){
				strcpy(uci_get_buf2, cli_get_uci(func_buf2));//HTmode
				if ( strcmp(uci_get_buf2, "20")!=0 ){
					cli_set_uci(func_buf, uci_set_buf);
				}
				else
					tprintf("No Extension Channel to be set\n");
   			}
   			else//if wlmode==11b or 11g_pure or 11g
   				tprintf("No Extension Channel to be set\n");
   		}
   		else//if model_radio=5 or ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
    			tprintf("No Extension Channel to be set\n");

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: checkchannelvalid
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/

//Modify by Philips on 2012-07-11
//channel might become invalid when wlmode, htmode or extch changes for 2.4G or 5G
T_CHAR* checkchannelvalid(T_CHAR* currentChannel, T_INT32 no_auto) {
//wifi0 for 2.4G, 5G of Single Radio and 2.4G of Dual Radio
T_CHAR func_buf[128]="wireless.wifi0.channel";
T_INT32 i;

	//wifi1 for 5G of Dual Radio
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.wifi1.channel");

	//Use CliChannelFreqTable to check whether the currentChannel is valid or not
	for (i=0; i<ChannelFreqData.count; i++){
		if ( strcmp(currentChannel, ChannelFreqData.CliChannelFreqTable[i].channel)==0 )
				break;
	}

	//currentChannel is invalid
//	if ( ( i==ChannelFreqData.count ) || (no_auto == 1) ){
		//write correct channel into configuration file
//		cli_set_uci(func_buf, ChannelFreqData.CliChannelFreqTable[1].channel);
//		return ChannelFreqData.CliChannelFreqTable[1].channel;
//	}
	//Modify on 2013-01-04 by Philips to allow channel to be set under WDSAP and WDSB mode which is requested by Jackey for ENS500EXT
	//currentChannel is invalid
	if ( ( i==ChannelFreqData.count ) || ( (i==0)&&(no_auto==1) ) ){
		//write correct channel into configuration file
		cli_set_uci(func_buf, ChannelFreqData.CliChannelFreqTable[1].channel);
		return ChannelFreqData.CliChannelFreqTable[1].channel;
	}
	//currentChannel is valid
	else
		return currentChannel;
}

/*****************************************************************
* NAME: createChannelfreqTable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 createChannelfreqTable(T_CHAR* band) {
//wifi0 for 2.4G, 5G of Single Radio and 2.4G of Dual Radio
T_CHAR func_buf[128]="wireless.wifi0.WLANExtChannel";
T_CHAR func_buf1[128]="wireless.wifi0.hwmode";
T_CHAR func_buf2[128]="wireless.wifi0.WLANHTMode";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_get_buf2[128];
T_INT32 i;
//T_INT32 start;
//T_INT32 stop;
FILE* fp;
char tbuf[32];
T_CHAR buf[512];
T_CHAR variable_wlmode[64];
T_CHAR variable_extch[32];

	//wifi1 for 5G of Dual Radio
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 ){
		strcpy(func_buf, "wireless.wifi1.WLANExtChannel");
		strcpy(func_buf1, "wireless.wifi1.hwmode");
		strcpy(func_buf2, "wireless.wifi1.WLANHTMode");
	}

	strcpy(uci_get_buf, cli_get_uci(func_buf)); 	//EXTch : lower, upper
	strcpy(uci_get_buf1, cli_get_uci(func_buf1)); 	//wlmode : b/g/n, a/n, ...
	strcpy(uci_get_buf2, cli_get_uci(func_buf2)); 	//HTmdoe : 20, 40, 20-40

	//5G channel variable
	if ( strcmp(band,"5G")==0 ){
		strcpy(variable_wlmode, "|grep -E \"^ath[^ ]+.*(11a|11na)\" ");
		//get channel with CU&CL
		//The wlmode is "11a_pure" in 5G for single-radio , but "11a" in 5G for dual-radio
		if ( (strcmp(uci_get_buf1,"11a_pure")!=0 && strcmp(uci_get_buf1,"11a")!=0) && (strcmp(uci_get_buf2,"20")!=0) )
			strcpy(variable_extch, "|grep -E \"CU|CL\" ");
		//get all channel
		else
			strcpy(variable_extch, " ");
	}
	//2.4G channel variable
	if ( strcmp(band,"2.4G")==0 ){
		strcpy(variable_wlmode, "|grep -E \"^ath[^ ]+.*(11b|11g|11ng)\" ");
		//get channel with CU|CL when htmode==40 or htmode==20/40
		if ( (strcmp(uci_get_buf1,"11ng")==0 || strcmp(uci_get_buf1,"11n_pure")==0) && (strcmp(uci_get_buf2,"40")==0 || strcmp(uci_get_buf2,"20-40")==0) ){
			//get lower extchannel
			if (atoi(uci_get_buf)==1)
				strcpy(variable_extch, "|grep -E \"CL\" ");
			//get upper extchannel
			else
				strcpy(variable_extch, "|grep -E \"CU\" ");
		}
		//get all channel when htmode==20
		else
			strcpy(variable_extch, " ");	
	}

	//sprintf(buf, "chan2c=\"$(wlanconfig `iwconfig 2>/dev/null %s |head -n 1|cut -d \' \' -f 1` list chan)\";chan=$(echo \"$chan2c\"|cut -c -37;echo \"$chan2c \"|cut -c 39- |grep ^Chan);unset chan2c; echo \"$chan\" %s |awk -F\" \" \'{print $1 \" \" $2 \" -- \" $4 $5}\' | sed \'s/*~//g\' | sed \'s/*//g\' | sed \'s/~//g\' > /tmp/channelfreq ", variable_wlmode, variable_extch);
	
	//Modify on 2013-08-07 by Philips to make 2.4G and 5G channel can be shown correctly
	sprintf(buf, "chan2c=\"$(wlanconfig `iwconfig 2>/dev/null %s |head -n 1|cut -d \' \' -f 1` list chan)\";chan=$(echo \"$chan2c\"|cut -c -38;echo \"$chan2c \"|cut -c 39- |grep Chan);unset chan2c; echo \"$chan\" %s |awk -F\" \" \'{print $2}\'| sed \'s/*~//g\' | sed \'s/*//g\' | sed \'s/~//g\' > /tmp/channelfreqTable ", variable_wlmode, variable_extch);
	system(buf);

	if((fp = fopen("/tmp/channelfreqTable", "r"))==NULL){
		printf("Can't open file\n");
		return -1;
	}
	
	i=0;
	ChannelFreqData.CliChannelFreqTable[i].item=i;
	strcpy(ChannelFreqData.CliChannelFreqTable[i].channel, "auto");

	i=1;
	while(fgets(tbuf,sizeof(tbuf),fp)){


//Modify on 2013-02-25 by Philips to make channel 14 can only be shown when country is "Japan" and wlessmode is "B Only"	
if ( atoi(tbuf)==14 && strcmp(uci_get_buf1,"11b")!=0 )
	continue;

		ChannelFreqData.CliChannelFreqTable[i].item=i;
		strcpy(ChannelFreqData.CliChannelFreqTable[i].channel, tbuf);
		ChannelFreqData.CliChannelFreqTable[i].channel[strlen(ChannelFreqData.CliChannelFreqTable[i].channel)-1]='\0';
		i++;
	}
	
	ChannelFreqData.count=i;
	fclose(fp);

	return ChannelFreqData.count;
}

/*****************************************************************
* NAME: displaychannelfreq
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 displaychannelfreq(T_CHAR* band, T_INT32 no_auto) {
//wifi0 for 2.4G, 5G of Single Radio and 2.4G of Dual Radio
T_CHAR func_buf[128]="wireless.wifi0.WLANExtChannel";
T_CHAR func_buf1[128]="wireless.wifi0.hwmode";
T_CHAR func_buf2[128]="wireless.wifi0.WLANHTMode";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_get_buf2[128];
T_INT32 i;
FILE* fp;
T_CHAR tbuf[32];
T_CHAR buf[512];
T_CHAR variable_wlmode[64];
T_CHAR variable_extch[32];
T_CHAR variable_cut[32];
T_INT32 operationeMode=current_opmode;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//wifi1 for 5G of Dual Radio
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 ){
		strcpy(func_buf, "wireless.wifi1.WLANExtChannel");
		strcpy(func_buf1, "wireless.wifi1.hwmode");
		strcpy(func_buf2, "wireless.wifi1.WLANHTMode");
	}

	strcpy(uci_get_buf, cli_get_uci(func_buf)); 	//EXTch : lower, upper
	strcpy(uci_get_buf1, cli_get_uci(func_buf1)); 	//wlmode : b/g/n, a/n, ...
	strcpy(uci_get_buf2, cli_get_uci(func_buf2)); 	//HTmdoe : 20, 40, 20-40

//printf("wlmode=%s, htmode=%s, extch=%s\n", uci_get_buf1, uci_get_buf2, uci_get_buf);

	//5G channel variable
	if ( strcmp(band,"5G")==0 ){
		strcpy(variable_wlmode, "|grep -E \"^ath[^ ]+.*(11a|11na)\" ");
		//get channel with CU&CL
		//The wlmode is "11a_pure" in 5G for single-radio , but "11a" in 5G for dual-radio
		if ( (strcmp(uci_get_buf1,"11a_pure")!=0 && strcmp(uci_get_buf1,"11a")!=0) && (strcmp(uci_get_buf2,"20")!=0) )
			strcpy(variable_extch, "|grep -E \"CU|CL\" ");
		//get all channel
		else
			strcpy(variable_extch, " ");
	}
	
	//2.4G channel variable
	if ( strcmp(band,"2.4G")==0 ){
		strcpy(variable_wlmode, "|grep -E \"^ath[^ ]+.*(11b|11g|11ng)\" ");
		//get channel with CU|CL when htmode==40 or htmode==20/40
		if ( (strcmp(uci_get_buf1,"11ng")==0 || strcmp(uci_get_buf1,"11n_pure")==0) && (strcmp(uci_get_buf2,"40")==0 || strcmp(uci_get_buf2,"20-40")==0) ){
			//get lower extchannel
			if (atoi(uci_get_buf)==1)
				strcpy(variable_extch, "|grep -E \"CL\" ");
			//get upper extchannel
			else
				strcpy(variable_extch, "|grep -E \"CU\" ");
		}
		//get all channel when htmode==20
		else
			strcpy(variable_extch, " ");
	}
	
//printf("variable_wlmode=%s, variable_extch=%s\n", variable_wlmode, variable_extch);	
	
	//sprintf(buf, "chan2c=\"$(wlanconfig `iwconfig 2>/dev/null %s |head -n 1|cut -d \' \' -f 1` list chan)\";chan=$(echo \"$chan2c\"|cut -c -37;echo \"$chan2c \"|cut -c 39- |grep ^Chan);unset chan2c; echo \"$chan\" %s |awk -F\" \" \'{print $1 \" \" $2 \" -- \" $4 $5}\' | sed \'s/*~//g\' | sed \'s/*//g\' | sed \'s/~//g\' > /tmp/channelfreq ", variable_wlmode, variable_extch);

	//Modify on 2013-08-19 by Philips to make 2.4G and 5G channel can be shown correctly for EAP1750H
if ( model_ID & MODEL_AC ){
	//Modify on 2013-08-30 by Philips to 5G channel can be shown correctly for EAP1750H when wlmode is "11naac" and HT mode is 80
	if ( (strcmp(uci_get_buf1,"11naac")==0) && (strcmp(uci_get_buf2,"80")==0) ){
	sprintf(buf, "chan2c=\"$(wlanconfig `iwconfig 2>/dev/null %s |head -n 1|cut -d \' \' -f 1` list chan)\";chan=$(echo \"$chan2c\"|cut -c -50|grep -v \"~\"|grep -E \"V80\";echo \"$chan2c \"|cut -c 53- |grep Chan|grep -v \"~\"|grep -E \"V80\");unset chan2c; echo \"$chan\" | sed \'s/*~//g\' | sed \'s/*//g\' | sed \'s/~//g\' |awk -F\" \" \'{print $1 \" \" $2 \" -- \" $4 $5}\'  > /tmp/channelfreq ", variable_wlmode);
	}			
	//get all channel
	else
	sprintf(buf, "chan2c=\"$(wlanconfig `iwconfig 2>/dev/null %s |head -n 1|cut -d \' \' -f 1` list chan)\";chan=$(echo \"$chan2c\"|cut -c -50;echo \"$chan2c \"|cut -c 53- |grep Chan);unset chan2c; echo \"$chan\" %s | sed \'s/*~//g\' | sed \'s/*//g\' | sed \'s/~//g\' |awk -F\" \" \'{print $1 \" \" $2 \" -- \" $4 $5}\'  > /tmp/channelfreq ", variable_wlmode, variable_extch);

}
else{
	//Modify on 2013-08-07 by Philips to make 2.4G and 5G channel can be shown correctly for EAP900H
	sprintf(buf, "chan2c=\"$(wlanconfig `iwconfig 2>/dev/null %s |head -n 1|cut -d \' \' -f 1` list chan)\";chan=$(echo \"$chan2c\"|cut -c -38;echo \"$chan2c \"|cut -c 39- |grep Chan);unset chan2c; echo \"$chan\" %s |awk -F\" \" \'{print $1 \" \" $2 \" -- \" $4 $5}\' | sed \'s/*~//g\' | sed \'s/*//g\' | sed \'s/~//g\' > /tmp/channelfreq ", variable_wlmode, variable_extch);
}

//printf("\nbuf=%s\n\n", buf);

	system(buf);
	
	if((fp = fopen("/tmp/channelfreq", "r"))==NULL){
		printf("Can't open file\n");
		return -1;
	}

//Modify on 2012-10-18 by Philips to make channel can't be "auto" on OPM_WDSB or OPM_WDSAP mode
	if (no_auto != 1)
		printf(" 0 - Auto\n");

	i=1;
	while(fgets(tbuf,sizeof(tbuf),fp)){

//Modify on 2013-02-25 by Philips to make channel 14 can only be shown when country is "Japan" and wlessmode is "B Only"	
if ( strcmp(band,"2.4G")==0 && strstr(tbuf, "Channel 14")!=NULL && strcmp(uci_get_buf1,"11b")!=0 )
	continue;
	
		
		printf("%2d - %s", i++, tbuf);	
	}
	fclose(fp);
	
	return i;
}

/*****************************************************************
* NAME: cmdchannel
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdchannel(T_VOID* priv, CliData* cliData)
{
//wifi0 for 2.4G, 5G of Single Radio and 2.4G of Dual Radio
T_CHAR func_buf[128]="wireless.wifi0.channel";
T_CHAR func_buf1[128]="wireless.wifi0.WLANExtChannel";
T_CHAR uci_get_buf[128];
//T_CHAR uci_get_buf1[128];
T_CHAR uci_set_buf[128];
T_CHAR band[32];

//Modify on 2012-10-18 by Philips to make channel can't be "auto" on OPM_WDSB or OPM_WDSAP mode
T_INT32 operationeMode=current_opmode;
T_INT32 ssidCount;
T_INT32 wifi_index;
T_INT32 nawds_index;
T_CHAR func_buf2[128];
T_CHAR uci_get_buf2[128];
T_INT32 no_auto=0;
T_INT32 start = 0;

	//Modify on 2012-10-18 by Philips to get the WDSlink according ssidCount, wifi_index, nawds_index
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	ssidCount=getModelssidCount(operationeMode);

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	//get 4 (if ssidcount is 4) or 16 (if ssidcount is 8) for single-radio and 16 (if radio is 2.4G) or 42 (if radio is 5G) for dual-radio
	//nawds_index=get_nawds_index(ssidCount);

	//Modify on 2013-08-07 by Philips to get the correct nawds_index
	nawds_index=get_nawds_index(ssidCount, operationeMode);

	sprintf(func_buf2, "wireless.@wifi-iface[%d].WLANWDSPeer", nawds_index);  
	strcpy(uci_get_buf2, cli_get_uci(func_buf2));

	//Modify on 2012-10-18 by Philips to make channel can't be "auto" on OPM_WDSB mode
	if ( (operationeMode==OPM_WDSB) )
		no_auto = 1;
	//Modify on 2012-10-18 by Philips to make channel can't be "auto" on OPM_WDSAP mode and at least one wdslink is enabled
	if ( (operationeMode==OPM_WDSAP) && ((uci_get_buf2[12] == 'v')||(uci_get_buf2[25]=='v')||(uci_get_buf2[38]=='v')||(uci_get_buf2[51]=='v')) )
		no_auto = 1;

	
	//wifi1 for 5G of Dual Radio
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 ){
		strcpy(func_buf, "wireless.wifi1.channel");
		strcpy(func_buf1, "wireless.wifi1.WLANExtChannel");
	}

	if ( model_radio==2 ) 
  		strcpy(band, "2.4G");
	if ( model_radio==5 ) 
  		strcpy(band, "5G");
  	if ( model_radio==7 ) 
  		strcpy(band, current_radio_flag);

  	//put channel list into ChannelfreqTable for 2.4G and 5G
  	channelCount=createChannelfreqTable(band);
			
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
	
		//display channel list for 2.4G and 5G
		channelCount=displaychannelfreq(band, no_auto);
		
		//Can't open /tmp/channelfreq file
		if (channelCount==-1){
			cliData->tokenLen--;
			return CLI_NOTHING;		
		}

		//Modify by Philips on 2012-07-11
		//channel might become invalid when wlmode, htmode or extch changes for 2.4G or 5G
		strcpy(uci_get_buf, checkchannelvalid(uci_get_buf, no_auto));
		
		tprintf("Current setting: Channel %s\n", uci_get_buf);
		cliData->tokenLen--;
		
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
	
if (no_auto == 1)
	start = 1;
	
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
						
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( start, channelCount-1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		strcpy(uci_set_buf, ChannelFreqData.CliChannelFreqTable[atoi(uci_set_buf)].channel );

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 network ssidp ssidact           */
/*                   CLI Command -- wless2 network ssidp isoact            */
/*                   CLI Command -- wless2 network ssidp ssid              */
/*                   CLI Command -- wless2 network ssidp vid               */
/*                   CLI Command -- wless2 network ssidp supssid           */
/*                   CLI Command -- wless2 network ssidp sepa              */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"network",	cli_table_network,	getNextTable,	"Wireless network",		"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_network[]= {
//	{OPM_AP,	"ssidp",	NULL,   		cmdssidp,	"SSID Profile",			"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_ssidp[]= {
//	{OPM_AP,	"ssidact",	NULL,			cmdssidact,	"SSID active",		"", AUTH_ANY,	MODEL_SINGLE},
//	{OPM_AP,	"isoact",	NULL,			cmdisoact,	"Isolation active",	"", AUTH_ANY,	MODEL_SINGLE},
//	{OPM_AP,	"ssid",		NULL,			cmdssid,	"SSID",			"", AUTH_ANY,	MODEL_ALL},
//	{OPM_AP,	"vid",		NULL,			cmdvid,		"VLAN ID",		"", AUTH_ANY,	MODEL_SINGLE},
//	{OPM_AP,	"supssid",	NULL,			cmdsupssid,	"Suppressed SSID",	"", AUTH_ANY,	MODEL_ALL},
//	{OPM_AP,	"sepa",		NULL,			cmdsepa,	"Station separation",	"", AUTH_ANY,	MODEL_ALL},
//	{OPM_AP,	"apsecu",       NULL,			cmdapsecu,	"Station security",     "", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_ssidp,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdssidpexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdssidp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   ### leaf node and then non-leaf node
****************************************************************/
CliStatus cmdssidp(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
//T_CHAR c1[255];
T_INT32 ssidCount;
T_INT32 i;
T_INT32 j=1;
T_INT32 wifi_index;
T_INT32 operationeMode=current_opmode;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	//only use 1-4 interface when dual-radio in APWDS
	if (model_radio==7 && operationeMode==4)
		ssidCount=4;

	if(cliData->argc==0){
		
		for (i=wifi_index; i<wifi_index+ssidCount; i++){
			sprintf(func_buf, "wireless.@wifi-iface[%d].ssid", i);
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			
			tprintf("%d - SSID%d: %s\n", j, j, uci_get_buf);
			j++;	
		}

		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
		
		//handle 1 argument for ssidp before set ssidpsetbridge  EX: ...network>ssidp 1
		if ( ssidpsetbridge==-1 ){

//printf("In cmdssidp ... (cliData->argc==1) and (ssidpsetbridge==-1)\n");
		
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, ssidCount, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
			}

			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

			SSIDProfileIndex=atoi(uci_set_buf);
			cliData->tokenLen--;
				
			//Handle the command --> wless2/network>ssidp 2
			if (cmdtreelevel==2){
				ssidpsetbridge=1;
				//prompt will be --> wless2/network/ssidp>
				cmdtreelevel=cliData->tokenLen;
			}
				
			return cmdHelp(cli_table_ssidp, cliData);

		}
		//handle 1 argument for ssidp after set ssidpsetbridge  EX: ...network/ssidp>vid
		else{
		
//printf("In cmdssidp ... (cliData->argc==1) and (ssidpsetbridge!=-1)\n");
		
			return getNextTable(cli_table_ssidp, cliData);
		}

	}
	else if(cliData->argc>1){
	
		//handle relative path --> wless2/network/ssidp>vid
		if ( ssidpsetbridge==1 ){
		
//printf("In cmdssidp ... (cliData->argc>1) and (ssidpsetbridge==1)\n");
		
			return getNextTable(cli_table_ssidp, cliData);
		}

		if (!errorcheckValidDecimal(cliData->tokens[3].token) || ! errorcheckIntRange( 1, ssidCount, atoi(cliData->tokens[3].token)) )
	  		return CLI_PARAMS_ERR;

		//handle absolute path --> wless2>network ssidp 2 vid
		else{
		
//printf("In cmdssidp ... (cliData->argc>1) and (ssidpsetbridge!=1) ... cliData->curLv=%d\n", cliData->curLv);
		
			SSIDProfileIndex=atoi(cliData->tokens[3].token);
			//Skip "2" when handling "wless2 network ssidp 2 vid"
			cliData->argc--;
		
			return getNextTable(cli_table_ssidp, cliData);
		}

	}

}

/*****************************************************************
* NAME: cmdssidact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdssidact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	
	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", wifi_index+SSIDProfileIndex-1);

	if(cliData->argc==0){
		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		//if ( SSIDProfileIndex==1 )
		//Modify on 2013-08-07 by Philips to support Disable for the first SSID for new web which is requested by Jacy
		if ( (SSIDProfileIndex==1) && ( (model_ID & MODEL_NEW_WEB) == 0 ) )
			tprintf("Current setting: Always Enable\n");
		else
			tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		//cliData->tokenLen--;
		cliData->tokenLen=cmdtreelevel;

		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
	
		//if ( SSIDProfileIndex==1 )
		//Modify on 2013-08-07 by Philips to support Disable for the first SSID for new web which is requested by Jacy			
		if ( (SSIDProfileIndex==1) && ( (model_ID & MODEL_NEW_WEB) == 0 ) )
			return CLI_PARAMS_ERR;/*Always Enable*/

		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
			
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);

if( model_radio==7 )
	vlan_dual_radio_process();
else
	vlanProccess(wifi_index+SSIDProfileIndex);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdisoact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdisoact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128]="wireless.wifi0.WLANSSIDIsolation";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.wifi1.WLANSSIDIsolation");

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANEnable", wifi_index+SSIDProfileIndex-1);

	if(cliData->argc==0){
		
		strcpy(uci_get_buf, cli_get_uci(func_buf));

		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );		

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);
		
		if ( atoi(uci_set_buf)==1 )
			cli_set_uci(func_buf1, "2");
		if ( atoi(uci_set_buf)==0 )
			checkIsolationDisable(wifi_index);

if( model_radio==7 )
	vlan_dual_radio_process();
else
	vlanProccess(wifi_index+SSIDProfileIndex);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdssid
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdssid(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
int i;
T_CHAR* token;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "wireless.@wifi-iface[%d].ssid", wifi_index+SSIDProfileIndex-1);
	
	if(cliData->argc==0){

//printf("globalCommandLine=%s, length=%d\n", globalCommandLine, strlen(globalCommandLine));
	
token = strstr(globalCommandLine, "ssid ");
if (token){
	token += strlen("ssid ");
	printf("token=%s, length=%d\n", token, strlen(token));
	if (strlen(token) > 0){
		if (!errorcheckStrLength( 32, token) ){
			tprintf("The length of SSID should not be larger than 32\n");
			cliData->tokenLen-=2;
		  	return CLI_PARAMS_ERR;
		}
		strcpy(uci_set_buf, token);
		cli_set_uci(func_buf, uci_set_buf);
	}
}

		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (32 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
	
token = strstr(globalCommandLine, "ssid ");
if (token){
	token += strlen("ssid ");
	printf("token=%s, length=%d\n", token, strlen(token));
	if (strlen(token) > 0){
		if (!errorcheckStrLength( 32, token) ){
			tprintf("The length of SSID should not be larger than 32\n");
			cliData->tokenLen-=2;
		  	return CLI_PARAMS_ERR;
		}
		strcpy(uci_set_buf, token);
		cli_set_uci(func_buf, uci_set_buf);
	}
}	
	
//		if (!errorcheckStrLength( 32, cliData->tokens[cliData->tokenLen-1].token) ){
//			tprintf("The length of SSID should not be larger than 32\n");
//			cliData->tokenLen-=2;
//	  		return CLI_PARAMS_ERR;
//		}
		
//		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
//		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
token = strstr(globalCommandLine, "ssid ");
if (token){
	token += strlen("ssid ");
	printf("token=%s, length=%d\n", token, strlen(token));
	if (strlen(token) > 0){
		if (!errorcheckStrLength( 32, token) ){
			tprintf("The length of SSID should not be larger than 32\n");
			cliData->tokenLen-=2;
		  	return CLI_PARAMS_ERR;
		}
		strcpy(uci_set_buf, token);
		cli_set_uci(func_buf, uci_set_buf);
	}
}
		//Get SSID name from global command line
//		token =strtok(globalCommandLine, " ");
//		while ( strcmp(token, "ssid")!=0 ){
//			token =strtok(NULL, " ");
//		}
//		strcpy(uci_set_buf, token+5);
		
//printf("uci_set_buf=%s, length=%d\n", uci_set_buf, strlen(uci_set_buf));
//		if (!errorcheckStrLength( 32, uci_set_buf) ){
//			tprintf("The length of SSID should not be larger than 32\n");
//			cliData->tokenLen-=(cliData->argc+1);
//	  		return CLI_PARAMS_ERR;
//		}
		//Set the SSID name into configuration file
//		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=(cliData->argc+1);
		return CLI_NOTHING;
//		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdvid
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdvid(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANID", wifi_index+SSIDProfileIndex-1);
	
	if(cliData->argc==0){
		
		strcpy(uci_get_buf, cli_get_uci(func_buf));

		tprintf("Current setting: %s (1-4094)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 4094, atoi(cliData->tokens[cliData->tokenLen-1].token) )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}
		if ( ( model_radio != 7 ) && (!errorcheckSameVID(cliData->tokens[cliData->tokenLen-1].token, SSIDProfileIndex)) ){
		//if ( (model_radio==2 || model_radio==5) && (!errorcheckSameVID(uci_set_buf, SSIDProfileIndex))  ){
			cliData->tokenLen-=2;
			tprintf("The VLAN ID value is already assigned to other SSID Profile. Please set another one.\n");
	  		return CLI_PARAMS_ERR;	
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		cli_set_uci(func_buf, uci_set_buf);

if( model_radio==7 )
	vlan_dual_radio_process();
else
	vlanProccess(wifi_index+SSIDProfileIndex);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsupssid
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsupssid(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "wireless.@wifi-iface[%d].hidden", wifi_index+SSIDProfileIndex-1);

	if(cliData->argc==0){
		
		strcpy(uci_get_buf, cli_get_uci(func_buf));	
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );	

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsepa
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsepa(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "wireless.@wifi-iface[%d].isolate", wifi_index+SSIDProfileIndex-1);

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));	
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );			

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*         CLI Command -- wless2 network ssidp apsecu cli_table_wep        */
/*         CLI Command -- wless2 network ssidp apsecu cli_table_wpapsk     */
/*         CLI Command -- wless2 network ssidp apsecu cli_table_wpa        */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"network",	cli_table_network,	getNextTable,	"Wireless network",		"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_network[]= {
//	{OPM_AP,	"ssidp",	NULL,   		cmdssidp,	"SSID Profile",			"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_ssidp[]= {
//	{OPM_AP,	"apsecu",       NULL,			cmdapsecu,	"Station security",     "", AUTH_ANY,	MODEL_ALL},
//};

//CliEntry cli_table_wep[]= {
//	{OPM_ALL,	"dkey",		NULL,		cmddkey,	"Default Key",		"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"key1",		NULL,		cmdkey1,	"Key1",			"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"key2",		NULL,		cmdkey2,	"Key2",			"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"key3",		NULL,		cmdkey3,	"Key3",			"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"key4",		NULL,		cmdkey4,	"Key4",			"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"accept",  	NULL, 	   	cmdwepaccept,	"Accept WEP setting",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_wep,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,		cmdapsecuexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: displayapsecurity
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID displayapsecurity(T_CHAR* wirelessmode, T_INT32 ssidnumber) {
int i;
T_INT32 start;
T_INT32 stop;
	//11n_pure only display 22~28
	//{22, "11n_pure" , "none"},
	//{23, "11n_pure" , "psk aes"},
	//{24, "11n_pure" , "psk2 aes"},
	//{25, "11n_pure" , "psk-mixed aes"},
	//{26, "11n_pure" , "wpa aes"},
	//{27, "11n_pure" , "wpa2 aes"},
	//{28, "11n_pure" , "wpa-mixed aes"}
	if ( strcmp(wirelessmode, "11n_pure")==0 || strcmp(wirelessmode, "11na_pure")==0 ){
		start=21;
		stop=27;

		
		//Modify on 2013-06-14 by Philips to support Guest Network for eap900 which is requested by Jacy
		if (ssidnumber==25)
			stop=24;
		
		for (i=start; i<=stop; i++)
		printf("%d - %s\n", CliAPsecurityTable[i].item-21, CliAPsecurityTable[i].apsecurityName);
	}
	if (strcmp(wirelessmode, "11n_pure")!=0 && strcmp(wirelessmode, "11na_pure")!=0){
		 //1st SSID has wep security
		 if (ssidnumber==1){
			start=0;
			stop=20;
			for (i=start; i<=stop; i++)
			printf("%d - %s\n", CliAPsecurityTable[i].item, CliAPsecurityTable[i].apsecurityName);
		}
		//other SSID doesn't have wep security
		else {
			start=3;
			stop=20;

			
			//Modify on 2013-06-14 by Philips to support Guest Network for eap900 which is requested by Jacy
			if (ssidnumber==25)
				stop=11;
			
			
			printf("%d - %s\n", CliAPsecurityTable[0].item, CliAPsecurityTable[0].apsecurityName);
			for (i=start; i<=stop; i++)
			printf("%d - %s\n", CliAPsecurityTable[i].item-2, CliAPsecurityTable[i].apsecurityName);
		}
	}
}

/*****************************************************************
* NAME: errorcheckapsecurity
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 errorcheckapsecurity(T_CHAR* wirelessmode, T_INT32 ssidnumber, T_INT32 input) {

	if ( strcmp(wirelessmode, "11n_pure")==0 || strcmp(wirelessmode, "11na_pure")==0 )
		//return errorcheckIntRange( 1, 7, input);

		//Modify on 2013-06-14 by Philips to support Guest Network for eap900 which is requested by Jacy
		if (ssidnumber==25)
			return errorcheckIntRange( 1, 4, input);
		else
			return errorcheckIntRange( 1, 7, input);
	
	else 	if (ssidnumber==1)/*ssid1*/
			return errorcheckIntRange( 1, 21, input);
		
		else
			//return errorcheckIntRange( 1, 19, input);
			
			//Modify on 2013-06-14 by Philips to support Guest Network for eap900 which is requested by Jacy
			if (ssidnumber==25)
				return errorcheckIntRange( 1, 10, input);
			else 
				return errorcheckIntRange( 1, 19, input);
}

/*****************************************************************
* NAME: searchapsecuritytable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_CHAR* searchapsecuritytable(T_CHAR* wirelessmode, T_INT32 ssidnumber, T_INT32 index) {

	if ( strcmp(wirelessmode, "11n_pure")==0 || strcmp(wirelessmode, "11na_pure")==0 )
		return CliAPsecurityTable[index+20].apsecurityName;

	else if (ssidnumber==1)/*ssid1*/
			return CliAPsecurityTable[index-1].apsecurityName;
		else {
			if (index==1)
				return CliAPsecurityTable[index-1].apsecurityName;
			else 
				return CliAPsecurityTable[index+1].apsecurityName;
		}
}

/*****************************************************************
* NAME: searchapsecuritymode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 searchapsecuritymode(T_CHAR* wirelessmode, T_INT32 ssidnumber, T_INT32 index) {

	if ( strcmp(wirelessmode, "11n_pure")==0 || strcmp(wirelessmode, "11na_pure")==0 ){
		if ( index>=2 && index<=4 )
			return 2;
		if ( index>=5 && index<=7 )
			return 3;
	}
	else {
		if (ssidnumber==1){/*ssid1*/
			if ( index>=2 && index<=3 )
				return 1;
			if ( index>=4 && index<=12 )
				return 2;
			if ( index>=13 && index<=21 )
				return 3;
		}
		else {
			if ( index>=2 && index<=11 )
				return 2;
			if ( index>=12 && index<=19 )
				return 3;
		}
	}

}

/*****************************************************************
* NAME: cmdapsecu
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdapsecu(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR wifiinterface[128]="wireless.wifi0.hwmode";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR uci_set_buf1[128];
T_CHAR wirelessmode[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(wifiinterface, "wireless.wifi1.hwmode");

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "wireless.@wifi-iface[%d].encryption", wifi_index+SSIDProfileIndex-1);

	strcpy(wirelessmode, getWirelessmode(wifiinterface));
	if(cliData->argc==0){
		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//display wep, psk, wpa security mode
		displayapsecurity(wirelessmode, SSIDProfileIndex);
		tprintf("Current setting: %s\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		//handle 1 argument for apsecu before set apsecusetbridge  EX: ...ssidp>apsecu 2
		if (apsecusetbridge==-1){
			
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckapsecurity(wirelessmode, SSIDProfileIndex, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
			}

			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
			//convert index to name EX: 6 -> psk aes; 17 -> wpa2 tkip
			strcpy(uci_set_buf1, searchapsecuritytable(wirelessmode, SSIDProfileIndex, atoi(uci_set_buf)));
				
			cli_set_uci(func_buf, uci_set_buf1);
		
			if ( strcmp(uci_set_buf1, "none")==0){
				cliData->tokenLen-=2;
				return CLI_NOTHING;		
			
			}
			else{
				//convert index to wep, psk or wpa table
				switch(searchapsecuritymode(wirelessmode, SSIDProfileIndex, atoi(uci_set_buf))){
					case 1:
						initialWEPtable();
						cliData->tokenLen--;
						//Handle the command --> wless2/network/ssidp>apsecu 2
						if (cmdtreelevel==3){
							apsecusetbridge=1;
							//prompt will be -->  wless2/network/ssidp/apsecu>
							cmdtreelevel=cliData->tokenLen;
						}

						return cmdHelp(cli_table_wep, cliData);
					case 2:

						initialWPAPSKtable();
						cliData->tokenLen--;
						//Handle the command --> wless2/network/ssidp>apsecu 4
						if (cmdtreelevel==3){
							apsecusetbridge=2;
							//prompt will be -->  wless2/network/ssidp/apsecu>
							cmdtreelevel=cliData->tokenLen;
						}
						
						return cmdHelp(cli_table_wpapsk, cliData);
					case 3:
						initialWPAtable();
						cliData->tokenLen--;
						//Handle the command --> wless2/network/ssidp>apsecu 18
						if (cmdtreelevel==3){
							apsecusetbridge=3;
							//prompt will be -->  wless2/network/ssidp/apsecu>
							cmdtreelevel=cliData->tokenLen;
						}
						
						return cmdHelp(cli_table_wpa, cliData);
				}
			}
		}
		
		//handle 1 argument for apsecu after set apsecusetbridge EX:...ssidp/apsecu>dkey
		if ( apsecusetbridge==1 )
			return getNextTable(cli_table_wep, cliData);
		else if ( apsecusetbridge==2 )
			return getNextTable(cli_table_wpapsk, cliData);
		else if ( apsecusetbridge==3 )
			return getNextTable(cli_table_wpa, cliData);

	}
	else if(cliData->argc>1){
		//handle 2 or more argument for apsecu after set apsecusetbridge EX:...ssidp/apsecu>dkey 3
		if ( apsecusetbridge==1 )
			return getNextTable(cli_table_wep, cliData);
		else if ( apsecusetbridge==2 )
			return getNextTable(cli_table_wpapsk, cliData);
		else if ( apsecusetbridge==3 )
			return getNextTable(cli_table_wpa, cliData);
		
		///Handle the command --> wless2 network ssidp 3 apsecu 3 X ...
		if (!errorcheckValidDecimal(cliData->tokens[5].token) || !errorcheckapsecurity(wirelessmode, SSIDProfileIndex, atoi(cliData->tokens[5].token)) ){
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[5].token);
		//convert index to name EX: 6 -> psk aes; 17 -> wpa2 tkip
		strcpy(uci_set_buf1, searchapsecuritytable(wirelessmode, SSIDProfileIndex, atoi(uci_set_buf)));
				
		cli_set_uci(func_buf, uci_set_buf1);

		if ( strcmp(uci_set_buf1, "none")==0){
			return CLI_NOTHING;		
			
		}
		else{
			//convert index to wep, psk or wpa table
			switch(searchapsecuritymode(wirelessmode, SSIDProfileIndex, atoi(uci_set_buf))){

				case 1:	//initial WEP, WPAPSK, WPA table only once
					if (security_set==0){
						initialWEPtable();
						security_set=1;
					}
					cliData->argc--;
					return getNextTable(cli_table_wep, cliData);
				case 2:
					if (security_set==0){
						initialWPAPSKtable();
						security_set=1;
					}
					cliData->argc--;
					return getNextTable(cli_table_wpapsk, cliData);
				case 3:
					if (security_set==0){
						initialWPAtable();		
						security_set=1;
					}
					cliData->argc--;
					return getNextTable(cli_table_wpa, cliData);
			}
		}

	}
}


/*-------------------------------------------------------------------------*/
/*         CLI Command -- wless2 network ssidp captive        		   */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   		"network",	cli_table_network,	getNextTable,	"Wireless network",		"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_network[]= {
//	{OPM_AP,		"ssidp",	NULL,   		cmdssidp,	"SSID Profile",			"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_ssidp[]= {
//	{OPM_AP|OPM_WDSAP,   	"captive",	NULL,			cmdcaptive,	"Captive Portal active",	"", AUTH_ANY, C600_ID|EAP900_ID},
//};

/*****************************************************************
* NAME: cmdcaptive
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0424
* Modify:   
****************************************************************/
CliStatus cmdcaptive(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
//T_INT32 operationeMode=current_opmode;
//T_INT32 wifi_index;
T_INT32 ath_base=0;

//	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
//		operationeMode=current_opmode_2;

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
//		operationeMode=current_opmode_5;
		ath_base=50;
		
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
//	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "eccaptive.ath%d.enable", ath_base+SSIDProfileIndex-1);

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));	
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );			

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}


/*-------------------------------------------------------------------------*/
/*         CLI Command -- wless2 network ssidp traffic        		   */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"network",	cli_table_network,	getNextTable,	"Wireless network",		"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_network[]= {
//	{OPM_AP,	"ssidp",	NULL,   		cmdssidp,	"SSID Profile",			"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_ssidp[]= {
//	{OPM_AP,	"traffic",	cli_table_traffic_c600,	getNextTable,	"Traffic shaping",		"", AUTH_ADMIN, C600_ID|EAP900_ID},
//};

//CliEntry cli_table_traffic_c600[]= {
//	{OPM_AP,	"tsact",	NULL,			cmdtsact_c600,		"Traffic Shaping active",	"", AUTH_ADMIN, C600_ID},
//	{OPM_AP,	"dwlimit",	NULL,			cmddwlimit_c600,	"Download limit",		"", AUTH_ANY, C600_ID},
//	{OPM_AP,	"uplimit",	NULL,			cmduplimit_c600,	"Upload limit",			"", AUTH_ADMIN, C600_ID},
//	{OPM_ALL,	"help",		cli_table_traffic_c600,	cmdHelp,		"Help",				"", AUTH_ADMIN, C600_ID},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,		"Exit",				"", AUTH_ADMIN, C600_ID},  
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdtsact_c600
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdtsact_c600(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 ath_base=0;

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		ath_base=50;
	
	sprintf(func_buf, "eccaptive.ath%d.globallimit", ath_base+SSIDProfileIndex-1);
	sprintf(func_buf1, "eccaptive.ath%d.uploadlimit", ath_base+SSIDProfileIndex-1);
	//Get the information of "traffic shaping enable"
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	
	if(cliData->argc==0){
		//If traffic shaping is disabled
		if( atoi(uci_get_buf) == -1 )
			tprintf("Current setting: %d (1:Enable, 0:Disable)\n", 0);	
		else
			tprintf("Current setting: %d (1:Enable, 0:Disable)\n", 1);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		//If traffic shaping is disabled
		if( atoi(uci_set_buf) == 0 ){
			cli_set_uci(func_buf, "-1");
			cli_set_uci(func_buf1, "-1");	
		}
		//If traffic shaping is enabled and globallimit = -1 
		else if( atoi(uci_get_buf) == -1 ){
			cli_set_uci(func_buf, "100");
			cli_set_uci(func_buf1, "100");	
		}
			
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmddwlimit_c600
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddwlimit_c600(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 ath_base=0;

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		ath_base=50;
	
	sprintf(func_buf, "eccaptive.ath%d.globallimit", ath_base+SSIDProfileIndex-1);
	//Get the information of "traffic shaping enable"
	strcpy(uci_get_buf, cli_get_uci(func_buf));

	//If traffic shaping is disabled, please enable traffic shaping first
	if( atoi(uci_get_buf) == -1 ){
		printf("Traffic Shaping is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s Mbps (1-999)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 999, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmduplimit_c600
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmduplimit_c600(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 ath_base=0;

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		ath_base=50;
	
	sprintf(func_buf, "eccaptive.ath%d.uploadlimit", ath_base+SSIDProfileIndex-1);
	//Get the information of "traffic shaping enable"
	strcpy(uci_get_buf, cli_get_uci(func_buf));


	//If traffic shaping is disabled, please enable traffic shaping first
	if( atoi(uci_get_buf) == -1 ){
		printf("Traffic Shaping is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s Mbps (1-999)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
		
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token)){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}/*the input is not numberic*/
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 999, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}


/*-------------------------------------------------------------------------*/
/*         CLI Command -- wless2 network ssidp roaming        		   */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"network",	cli_table_network,	getNextTable,	"Wireless network",		"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_network[]= {
//	{OPM_AP,	"ssidp",	NULL,   		cmdssidp,	"SSID Profile",			"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_ssidp[]= {
//	{OPM_AP,	"roaming",	cli_table_fast_roaming,	getNextTable,	"Fast Roaming",			"", AUTH_ANY, EAP900_ID},
//};

//CliEntry cli_table_fast_roaming[]= {
//	{OPM_AP,	"fract",	NULL,			cmdfract,	"Fast roaming active",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP,	"advsch",	NULL,			cmdadvsch,	"Advanced search",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_fast_roaming,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};	

/*****************************************************************
* NAME: cmdfract
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0613
* Modify:   
****************************************************************/
CliStatus cmdfract(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	//Get Encryption information
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "wireless.w0_index0.encryption");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w1_index0.encryption");

	strcpy(uci_get_buf, cli_get_uci(func_buf));

	//If Encryption is not disabled, please enable daylightsaving first
	if ( strstr(uci_get_buf, "wpa")==NULL ){
		printf("Encrytion is not WPA, WPA2, or WPA Mixed, please set the encryption first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "fastroaming.fastroaming_2G.enable");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "fastroaming.fastroaming_5G.enable");

	if(cliData->argc==0){

		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
			
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		cli_set_uci(func_buf, uci_set_buf);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdadvsch
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0613
* Modify:   
****************************************************************/
CliStatus cmdadvsch(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	//Get Fast roaming enable information
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "fastroaming.fastroaming_2G.enable");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "fastroaming.fastroaming_5G.enable");

	strcpy(uci_get_buf, cli_get_uci(func_buf));

	//If Fast roaming is disabled, please enable Fast roaming first
	if( atoi(uci_get_buf) == 0 ){
		printf("Fast roaming is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "fastroaming.fastroaming_2G.adv_search");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "fastroaming.fastroaming_5G.adv_search");

	if(cliData->argc==0){

		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
			
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		cli_set_uci(func_buf, uci_set_buf);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}	

/*****************************************************************
* NAME: cmdssidpexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdssidpexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	ssidpsetbridge=-1;

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}


/*****************************************************************
* NAME: initialWEPtable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID initialWEPtable(T_VOID)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR func_buf2[128];
T_CHAR func_buf3[128];
T_CHAR uci_get_buf[128];
T_INT32 i;
//T_INT32 index=convertSSIDProfileIndex(SSIDProfileIndex);
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WepInputMethod", wifi_index+SSIDProfileIndex-1);
	sprintf(func_buf1, "wireless.@wifi-iface[%d].WepKeyLen", wifi_index+SSIDProfileIndex-1);
	sprintf(func_buf2, "wireless.@wifi-iface[%d].WepKeyIdx", wifi_index+SSIDProfileIndex-1);


	strcpy(uci_get_buf, cli_get_uci(func_buf));
	if (strcmp(uci_get_buf, "")!=0)
		strcpy(CliWEPset.inputtype, uci_get_buf);

	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	if (strcmp(uci_get_buf, "")!=0)
		strcpy(CliWEPset.keylength, uci_get_buf);

	strcpy(uci_get_buf, cli_get_uci(func_buf2));
	if (strcmp(uci_get_buf, "")!=0)
		strcpy(CliWEPset.defaultkey, uci_get_buf);

	for (i=1; i<5; i++){
		sprintf(func_buf3, "wireless.@wifi-iface[%d].key%d", wifi_index+SSIDProfileIndex-1, i);	
		strcpy(uci_get_buf, cli_get_uci(func_buf3));
		CliWEPset.keyset[i-1]=0;
		if (strcmp(uci_get_buf, "")!=0){
			strcpy(CliWEPset.key[i-1], uci_get_buf);
			CliWEPset.keyset[i-1]=1;
		}
	}/*initial key1~4*/
}

//Jacy ask to keep wepkey and use keylength to set wepkeylength and inputtype
/*****************************************************************
* NAME: cmdinputt
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
/*
CliStatus cmdinputt(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	sprintf(func_buf, "wireless.@wifi-iface[%d].WepInputMethod", convertSSIDProfileIndex(SSIDProfileIndex)-1);
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Hex, 2:ASCII)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		if (!errorcheckValidDecimal(uci_set_buf) || !errorcheckIntRange( 1, 2, atoi(uci_set_buf)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(CliWEPset.inputtype, uci_set_buf);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}
*/

//Jacy ask to keep wepkey and use keylength to set wepkeylength and inputtype
/*****************************************************************
* NAME: cmdkeylen
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
/*
CliStatus cmdkeylen(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	sprintf(func_buf, "wireless.@wifi-iface[%d].WepKeyLen", convertSSIDProfileIndex(SSIDProfileIndex)-1);
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("1 - 40/64-bit (10 hex digits or 5 ASCII char)\n");
		tprintf("2 - 104/128-bit (26 hex digits or 13 ASCII char)\n");
		tprintf("3 - 128/152-bit (32 hex digits or 16 ASCII char)\n");
		if ( atoi(uci_get_buf)==64 )
			tprintf("Current setting: 1 - 40/64-bit (10 hex digits or 5 ASCII char)\n");
		if ( atoi(uci_get_buf)==128 )
			tprintf("Current setting: 2 - 104/128-bit (26 hex digits or 13 ASCII char)\n");
		if ( atoi(uci_get_buf)==152 )
			tprintf("Current setting: 3 - 128/152-bit (32 hex digits or 16 ASCII char)\n");
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		if (!errorcheckValidDecimal(uci_set_buf) || !errorcheckIntRange( 1, 3, atoi(uci_set_buf)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		if ( atoi(uci_set_buf)==1 )
			strcpy(uci_set_buf, "64");
		if ( atoi(uci_set_buf)==2 )
			strcpy(uci_set_buf, "128");
		if ( atoi(uci_set_buf)==3 )
			strcpy(uci_set_buf, "152");
			
		strcpy(CliWEPset.keylength, uci_set_buf);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}
*/
/*****************************************************************
* NAME: cmddkey
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddkey(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "wireless.@wifi-iface[%d].WepKeyIdx", wifi_index+SSIDProfileIndex-1);

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if (strcmp(uci_get_buf, "")!=0)
			tprintf("Current setting: %s (1-4)\n", uci_get_buf);
		else 
			tprintf("Current setting: %s (1-4)\n", CliWEPset.defaultkey);
			
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 4, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		strcpy(CliWEPset.defaultkey, uci_set_buf);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdkey1
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdkey1(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	

	//sprintf(func_buf, "wireless.@wifi-iface[%d].key1", wifi_index+SSIDProfileIndex-1);
	
	//Modify on 2013-09-29 by Philips to fix the bug about the mapping of wifi interface is not 19 when CB mode or WDS STA mode	
	if ( model_radio==7 && (operationeMode==OPM_CB || operationeMode==OPM_WDSSTA) )
		SSIDProfileIndex=1;
	sprintf(func_buf, "wireless.@wifi-iface[%d].key1", wifi_index+SSIDProfileIndex-1);


	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (5, 13, 16 ASCII) or (10, 26, 32 Hex)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Jacy ask to keep wepkey and use keylength to set wepkeylength and inputtype
		switch ( strlen(cliData->tokens[cliData->tokenLen-1].token) ){
			case 5:	
				strcpy(CliWEPset.keylength, "64");
				strcpy(CliWEPset.inputtype, "2");
				break;	
			case 13:
				strcpy(CliWEPset.keylength, "128");
				strcpy(CliWEPset.inputtype, "2");
				break;	
			case 16:
				strcpy(CliWEPset.keylength, "152");
				strcpy(CliWEPset.inputtype, "2");
				break;
			
			case 10:
				if (!errorcheckValidHex(uci_set_buf)) {
					tprintf("Key is not valid Hex digit\n");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				strcpy(CliWEPset.keylength, "64");
				strcpy(CliWEPset.inputtype, "1");
				break;
			case 26:
				if (!errorcheckValidHex(uci_set_buf)) {
					tprintf("Key is not valid Hex digit\n");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				strcpy(CliWEPset.keylength, "128");
				strcpy(CliWEPset.inputtype, "1");
				break;
			case 32:
				if (!errorcheckValidHex(uci_set_buf)) {
					tprintf("Key is not valid Hex digit\n");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				strcpy(CliWEPset.keylength, "152");
				strcpy(CliWEPset.inputtype, "1");
				break; 
		
			default:
				tprintf("Key length should be (5, 13, 16 ASCII) or (10, 26, 32 Hex)\n");
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		strcpy(CliWEPset.key[0], uci_set_buf);
		CliWEPset.keyset[0]=1;

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdkey2
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdkey2(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	
	//sprintf(func_buf, "wireless.@wifi-iface[%d].key2", wifi_index+SSIDProfileIndex-1);
	
	//Modify on 2013-09-29 by Philips to fix the bug about the mapping of wifi interface is not 19 when CB mode or WDS STA mode	
	if ( model_radio==7 && (operationeMode==OPM_CB || operationeMode==OPM_WDSSTA) )
		SSIDProfileIndex=1;
	sprintf(func_buf, "wireless.@wifi-iface[%d].key2", wifi_index+SSIDProfileIndex-1);

	
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (5, 13, 16 ASCII) or (10, 26, 32 Hex)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

		//Jacy ask to keep wepkey and use keylength to set wepkeylength and inputtype
		switch ( strlen(cliData->tokens[cliData->tokenLen-1].token) ){
			case 5:	
				strcpy(CliWEPset.keylength, "64");
				strcpy(CliWEPset.inputtype, "2");
				break;	
			case 13:
				strcpy(CliWEPset.keylength, "128");
				strcpy(CliWEPset.inputtype, "2");
				break;	
			case 16:
				strcpy(CliWEPset.keylength, "152");
				strcpy(CliWEPset.inputtype, "2");
				break;
			
			case 10:
				if (!errorcheckValidHex(uci_set_buf)) {
					tprintf("Key is not valid Hex digit\n");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				strcpy(CliWEPset.keylength, "64");
				strcpy(CliWEPset.inputtype, "1");
				break;
			case 26:
				if (!errorcheckValidHex(uci_set_buf)) {
					tprintf("Key is not valid Hex digit\n");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				strcpy(CliWEPset.keylength, "128");
				strcpy(CliWEPset.inputtype, "1");
				break;
			case 32:
				if (!errorcheckValidHex(uci_set_buf)) {
					tprintf("Key is not valid Hex digit\n");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				strcpy(CliWEPset.keylength, "152");
				strcpy(CliWEPset.inputtype, "1");
				break; 
		
			default:
				tprintf("Key length should be (5, 13, 16 ASCII) or (12, 26, 32 Hex)\n");
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		strcpy(CliWEPset.key[1], uci_set_buf);
		CliWEPset.keyset[1]=1;
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdkey3
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdkey3(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);


	//sprintf(func_buf, "wireless.@wifi-iface[%d].key3", wifi_index+SSIDProfileIndex-1);

	//Modify on 2013-09-29 by Philips to fix the bug about the mapping of wifi interface is not 19 when CB mode or WDS STA mode	
	if ( model_radio==7 && (operationeMode==OPM_CB || operationeMode==OPM_WDSSTA) )
		SSIDProfileIndex=1;
	sprintf(func_buf, "wireless.@wifi-iface[%d].key3", wifi_index+SSIDProfileIndex-1);
	

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (5, 13, 16 ASCII) or (10, 26, 32 Hex)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

		//Jacy ask to keep wepkey and use keylength to set wepkeylength and inputtype
		switch ( strlen(cliData->tokens[cliData->tokenLen-1].token) ){
			case 5:	
				strcpy(CliWEPset.keylength, "64");
				strcpy(CliWEPset.inputtype, "2");
				break;	
			case 13:
				strcpy(CliWEPset.keylength, "128");
				strcpy(CliWEPset.inputtype, "2");
				break;	
			case 16:
				strcpy(CliWEPset.keylength, "152");
				strcpy(CliWEPset.inputtype, "2");
				break;
			
			case 10:
				if (!errorcheckValidHex(uci_set_buf)) {
					tprintf("Key is not valid Hex digit\n");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				strcpy(CliWEPset.keylength, "64");
				strcpy(CliWEPset.inputtype, "1");
				break;
			case 26:
				if (!errorcheckValidHex(uci_set_buf)) {
					tprintf("Key is not valid Hex digit\n");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				strcpy(CliWEPset.keylength, "128");
				strcpy(CliWEPset.inputtype, "1");
				break;
			case 32:
				if (!errorcheckValidHex(uci_set_buf)) {
					tprintf("Key is not valid Hex digit\n");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				strcpy(CliWEPset.keylength, "152");
				strcpy(CliWEPset.inputtype, "1");
				break; 
		
			default:
				tprintf("Key length should be (5, 13, 16 ASCII) or (12, 26, 32 Hex)\n");
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		strcpy(CliWEPset.key[2], uci_set_buf);
		CliWEPset.keyset[2]=1;
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdkey4
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdkey4(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);


	//sprintf(func_buf, "wireless.@wifi-iface[%d].key4", wifi_index+SSIDProfileIndex-1);

	//Modify on 2013-09-29 by Philips to fix the bug about the mapping of wifi interface is not 19 when CB mode or WDS STA mode	
	if ( model_radio==7 && (operationeMode==OPM_CB || operationeMode==OPM_WDSSTA) )
		SSIDProfileIndex=1;
	sprintf(func_buf, "wireless.@wifi-iface[%d].key4", wifi_index+SSIDProfileIndex-1);


	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (5, 13, 16 ASCII) or (10, 26, 32 Hex)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

		//Jacy ask to keep wepkey and use keylength to set wepkeylength and inputtype
		switch ( strlen(cliData->tokens[cliData->tokenLen-1].token) ){
			case 5:	
				strcpy(CliWEPset.keylength, "64");
				strcpy(CliWEPset.inputtype, "2");
				break;	
			case 13:
				strcpy(CliWEPset.keylength, "128");
				strcpy(CliWEPset.inputtype, "2");
				break;	
			case 16:
				strcpy(CliWEPset.keylength, "152");
				strcpy(CliWEPset.inputtype, "2");
				break;
			
			case 10:
				if (!errorcheckValidHex(uci_set_buf)) {
					tprintf("Key is not valid Hex digit\n");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				strcpy(CliWEPset.keylength, "64");
				strcpy(CliWEPset.inputtype, "1");
				break;
			case 26:
				if (!errorcheckValidHex(uci_set_buf)) {
					tprintf("Key is not valid Hex digit\n");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				strcpy(CliWEPset.keylength, "128");
				strcpy(CliWEPset.inputtype, "1");
				break;
			case 32:
				if (!errorcheckValidHex(uci_set_buf)) {
					tprintf("Key is not valid Hex digit\n");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				strcpy(CliWEPset.keylength, "152");
				strcpy(CliWEPset.inputtype, "1");
				break; 
		
			default:
				tprintf("Key length should be (5, 13, 16 ASCII) or (12, 26, 32 Hex)\n");
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		strcpy(CliWEPset.key[3], uci_set_buf);
		CliWEPset.keyset[3]=1;
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

//Jacy ask to keep wepkey and use keylength to set wepkeylength and inputtype
/*****************************************************************
* NAME: cmdwepaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwepaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR func_buf2[128];
T_CHAR func_buf3[128];
T_CHAR func_buf4[128];
T_CHAR func_buf5[128];
T_CHAR func_buf6[128];
//T_CHAR uci_get_buf[128];
T_INT32 i;
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	//Modify on 2013-09-29 by Philips to fix the bug about the mapping of wifi interface is not 19 when CB mode or WDS STA mode	
	if ( model_radio==7 && (operationeMode==OPM_CB || operationeMode==OPM_WDSSTA) )
		SSIDProfileIndex=1;
	
	sprintf(func_buf, "wireless.@wifi-iface[%d].WepInputMethod", wifi_index+SSIDProfileIndex-1);
	sprintf(func_buf1, "wireless.@wifi-iface[%d].WepKeyLen", wifi_index+SSIDProfileIndex-1);
	sprintf(func_buf2, "wireless.@wifi-iface[%d].WepKeyIdx", wifi_index+SSIDProfileIndex-1);
	sprintf(func_buf3, "wireless.@wifi-iface[%d].key1", wifi_index+SSIDProfileIndex-1);
	sprintf(func_buf4, "wireless.@wifi-iface[%d].key2", wifi_index+SSIDProfileIndex-1);
	sprintf(func_buf5, "wireless.@wifi-iface[%d].key3", wifi_index+SSIDProfileIndex-1);
	sprintf(func_buf6, "wireless.@wifi-iface[%d].key4", wifi_index+SSIDProfileIndex-1);
	
	if(cliData->argc==0){
		
		if (CliWEPset.keyset[ atoi(CliWEPset.defaultkey)-1 ]==0){
			tprintf("Key %d can't be empty\n", atoi(CliWEPset.defaultkey));
			cliData->tokenLen-=1;
	  		return CLI_PARAMS_ERR;
		}
/*		type=atoi(CliWEPset.inputtype)-1; // 0:Hex, 1:ASCII 
		length=atoi(CliWEPset.keylength)/76;// 64/76=0, 128/76=1, 152/76=2 
		
		if (type==0 && (!errorcheckValidHex(CliWEPset.key[ atoi(CliWEPset.defaultkey)-1 ])) ){
			tprintf("Key %d is not valid Hex digit\n", atoi(CliWEPset.defaultkey));
			cliData->tokenLen-=1;
	  		return CLI_PARAMS_ERR;
		}
		
		for (i=0; i<4; i++){
			if ( (CliWEPset.keyset[i]==1) && ((strlen(CliWEPset.key[i]) != CliWEPkeyLength[type][length])) ){
				tprintf("Key %d : Please fill %d characters\n", i+1, CliWEPkeyLength[type][length]);
				errorflag=1;
			}
				
		
		}
		if (errorflag==1){
			cliData->tokenLen-=1;
	  		return CLI_PARAMS_ERR;
		}*/
		//if (strlen(CliWEPset.key[ atoi(CliWEPset.defaultkey)-1 ]) != CliWEPkeyLength[type][length] ){
		//	tprintf("Key %d : Please fill %d characters\n", atoi(CliWEPset.defaultkey), CliWEPkeyLength[type][length]);
		//	cliData->tokenLen-=1;
	  	//	return CLI_PARAMS_ERR;
		//}
		
		//Jacy ask to check other keys' length according to default key's length
		//if other keys' length is not the same with default key's length, key is set to be NULL
		for (i=1; i<5; i++){
			if ( i==atoi(CliWEPset.defaultkey) )			
				continue;

			if ( strlen(CliWEPset.key[i-1])!=strlen(CliWEPset.key[ atoi(CliWEPset.defaultkey)-1 ]) )
				strcpy( CliWEPset.key[i-1], "");

		}
	
		cli_set_uci(func_buf, CliWEPset.inputtype);
		cli_set_uci(func_buf1, CliWEPset.keylength);
		cli_set_uci(func_buf2, CliWEPset.defaultkey);
		cli_set_uci(func_buf3, CliWEPset.key[0]);
		cli_set_uci(func_buf4, CliWEPset.key[1]);
		cli_set_uci(func_buf5, CliWEPset.key[2]);
		cli_set_uci(func_buf6, CliWEPset.key[3]);
		
		if ( operationeMode==OPM_RP ){
//printf("wifi_index=%d_current_opmode=%d_SSIDProfileIndex=%d\n", wifi_index, current_opmode, SSIDProfileIndex);
			sprintf(func_buf, "wireless.@wifi-iface[%d].WepInputMethod", wifi_index+SSIDProfileIndex);
			sprintf(func_buf1, "wireless.@wifi-iface[%d].WepKeyLen", wifi_index+SSIDProfileIndex);
			sprintf(func_buf2, "wireless.@wifi-iface[%d].WepKeyIdx", wifi_index+SSIDProfileIndex);
			sprintf(func_buf3, "wireless.@wifi-iface[%d].key1", wifi_index+SSIDProfileIndex);
			sprintf(func_buf4, "wireless.@wifi-iface[%d].key2", wifi_index+SSIDProfileIndex);
			sprintf(func_buf5, "wireless.@wifi-iface[%d].key3", wifi_index+SSIDProfileIndex);
			sprintf(func_buf6, "wireless.@wifi-iface[%d].key4", wifi_index+SSIDProfileIndex);
			
			cli_set_uci(func_buf, CliWEPset.inputtype);
			cli_set_uci(func_buf1, CliWEPset.keylength);
			cli_set_uci(func_buf2, CliWEPset.defaultkey);
			cli_set_uci(func_buf3, CliWEPset.key[0]);
			cli_set_uci(func_buf4, CliWEPset.key[1]);
			cli_set_uci(func_buf5, CliWEPset.key[2]);
			cli_set_uci(func_buf6, CliWEPset.key[3]);
		}/*If Operation mode==OPM_RP*/
		cliData->tokenLen--;
		return CLI_OK;
	
	}
	else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}


/*****************************************************************
* NAME: cmdapsecuexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdapsecuexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	apsecusetbridge=-1;
	cbsecusetbridge=-1;
	wdssecusetbridge=-1;

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}

/*-------------------------------------------------------------------------*/
/*         CLI Command -- wless2 network ssidp apsecu cli_table_wpapsk     */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"network",	cli_table_network,	getNextTable,	"Wireless network",		"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_network[]= {
//	{OPM_AP,	"ssidp",	NULL,   		cmdssidp,	"SSID Profile",			"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_ssidp[]= {
//	{OPM_AP,	"apsecu",       NULL,			cmdapsecu,	"Station security",     "", AUTH_ANY,	MODEL_ALL},
//};

//CliEntry cli_table_wpapsk[]= {
//	{OPM_ALL,	"passp",	NULL,			cmdpassp,		"Passphrase",			"", AUTH_ANY,	MODEL_ALL},
//	{OPM_AP,	"groupk",	NULL,			cmdgroupk,		"Group Key Update Interval",	"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"accept",  	NULL,			cmdwpapskaccept,	"Accept WPA-PSK setting",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_wpapsk,	cmdHelp,		"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,			cmdapsecuexit,		"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: initialWPAPSKtable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID initialWPAPSKtable(T_VOID)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR uci_get_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].key", wifi_index+SSIDProfileIndex-1);	
	sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANWpaGroupKeyUpdateInterval", wifi_index+SSIDProfileIndex-1);	
	
	CliWPAPSKset.passphraseset=0;
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	if (strcmp(uci_get_buf, "")!=0){
		strcpy(CliWPAPSKset.passphrase, uci_get_buf);
		CliWPAPSKset.passphraseset=1;
	}
	//printf("CliWEPset.passphrase=%s\n", uci_get_buf);
	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	if (strcmp(uci_get_buf, "")!=0)
		strcpy(CliWPAPSKset.interval, uci_get_buf);
}

/*****************************************************************
* NAME: cmdpassp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpassp(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].key", wifi_index+SSIDProfileIndex-1);
	
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (8-63 characters) or (64 Hexadecimal characters)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		
		if ( strlen(cliData->tokens[cliData->tokenLen-1].token)==64 && (!errorcheckValidHex(cliData->tokens[cliData->tokenLen-1].token)) ){
			tprintf("Passphrase is not valid Hex digit\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		if (strlen(cliData->tokens[cliData->tokenLen-1].token)!=64 && (!errorcheckIntRange( 8, 63, strlen(cliData->tokens[cliData->tokenLen-1].token) )) ){
			tprintf("The length of passphrase should be between 8 and 63\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		strcpy(CliWPAPSKset.passphrase, uci_set_buf);
		CliWPAPSKset.passphraseset=1;

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdgroupk
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdgroupk(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWpaGroupKeyUpdateInterval", wifi_index+SSIDProfileIndex-1);
	
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s seconds (30-3600, 0:disabled)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if ( !errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || atoi(cliData->tokens[cliData->tokenLen-1].token)!=0 && !errorcheckIntRange( 30, 3600, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwpapskaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwpapskaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
//T_CHAR uci_get_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].key", wifi_index+SSIDProfileIndex-1);

	if(cliData->argc==0){
		
		if (CliWPAPSKset.passphraseset==0){
			tprintf("Passphrase can't be empty\n");
			cliData->tokenLen-=1;
	  		return CLI_PARAMS_ERR;
		}
		
		if ( strlen(CliWPAPSKset.passphrase)==64 && (!errorcheckValidHex(CliWPAPSKset.passphrase)) ){
			tprintf("Passphrase is not valid Hex digit\n");
			cliData->tokenLen-=1;
	  		return CLI_PARAMS_ERR;
		}
		
		if (strlen(CliWPAPSKset.passphrase)!=64 && (!errorcheckIntRange( 8, 63, strlen(CliWPAPSKset.passphrase) )) ){
			tprintf("The length of passphrase should be between 8 and 63\n");
			cliData->tokenLen-=1;
	  		return CLI_PARAMS_ERR;
		}
		
		cli_set_uci(func_buf, CliWPAPSKset.passphrase);
		
		if ( operationeMode==OPM_RP ){
			sprintf(func_buf, "wireless.@wifi-iface[%d].key", wifi_index+SSIDProfileIndex);
			cli_set_uci(func_buf, CliWPAPSKset.passphrase);
		}/*If Operation mode==OPM_RP*/
		cliData->tokenLen--;
		return CLI_OK;
	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*         CLI Command -- wless2 network ssidp apsecu cli_table_wpa        */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"network",	cli_table_network,	getNextTable,	"Wireless network",		"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_network[]= {
//	{OPM_AP,	"ssidp",	NULL,   		cmdssidp,	"SSID Profile",			"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_ssidp[]= {
//	{OPM_AP,	"apsecu",       NULL,			cmdapsecu,	"Station security",     "", AUTH_ANY,	MODEL_ALL},
//};

//CliEntry cli_table_wpa[]= {
//	{OPM_ALL,	"radserver",	NULL,		cmdradserver,	"Radius Server",		"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"radp",		NULL,		cmdradp,	"Radius Port",			"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"radsecret",	NULL,		cmdradsecret,	"Radius Secret",		"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"groupk",	NULL,		cmdgroupk,      "Group Key Update Interval",	"", AUTH_ANY, MODEL_ALL},
//Modify on 2012-10-11 to add Radius Accounting field    
//	{OPM_ALL,	"radaccount",	NULL,		cmdradaccount,	"Radius Accounting",		"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"radaccser",	NULL,		cmdradaccser,	"Radius Accounting Server",	"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"radaccp",	NULL,		cmdradaccp,	"Radius Accounting Port",	"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"radaccsec",	NULL,		cmdradaccsec,	"Radius Accounting Secret",	"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"interval",	NULL,		cmdinterval,	"Interim Accounting Interval",	"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"accept",	NULL, 	   	cmdwpaaccept,	"Accept WPA setting",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_wpa,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,		cmdapsecuexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: initialWPAtable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID initialWPAtable(T_VOID)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR func_buf2[128];
T_CHAR func_buf3[128];
T_CHAR func_buf4[128];
T_CHAR func_buf5[128];
T_CHAR func_buf6[128];
T_CHAR func_buf7[128];
T_CHAR uci_get_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	//Get the values of Radius
	sprintf(func_buf, "wireless.@wifi-iface[%d].server", wifi_index+SSIDProfileIndex-1);
	sprintf(func_buf1, "wireless.@wifi-iface[%d].port", wifi_index+SSIDProfileIndex-1);
	sprintf(func_buf2, "wireless.@wifi-iface[%d].WLANWpaRadiusSrvSecret", wifi_index+SSIDProfileIndex-1);
	sprintf(func_buf3, "wireless.@wifi-iface[%d].WLANWpaGroupKeyUpdateInterval", wifi_index+SSIDProfileIndex-1);

	CliWPAset.serveripset=0;
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	if (strcmp(uci_get_buf, "")!=0){
		strcpy(CliWPAset.serverip, uci_get_buf);
		CliWPAset.serveripset=1;
	}

	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	if (strcmp(uci_get_buf, "")!=0)
		strcpy(CliWPAset.port, uci_get_buf);

	CliWPAset.secretset=0;
	strcpy(uci_get_buf, cli_get_uci(func_buf2));
	if (strcmp(uci_get_buf, "")!=0){
		strcpy(CliWPAset.secret, uci_get_buf);
		CliWPAset.secretset=1;
	}
	
	strcpy(uci_get_buf, cli_get_uci(func_buf3));
	if (strcmp(uci_get_buf, "")!=0)
		strcpy(CliWPAset.interval, uci_get_buf);

//Get the values of Radius Accounting	
sprintf(func_buf4, "wireless.@wifi-iface[%d].WLANWpaRadiusAccSrvIP", wifi_index+SSIDProfileIndex-1);
sprintf(func_buf5, "wireless.@wifi-iface[%d].WLANWpaRadiusAccSrvPort", wifi_index+SSIDProfileIndex-1);
sprintf(func_buf6, "wireless.@wifi-iface[%d].WLANWpaRadiusAccSrvSecret", wifi_index+SSIDProfileIndex-1);
sprintf(func_buf7, "wireless.@wifi-iface[%d].WLANWpaRadiusAccInterimInterval", wifi_index+SSIDProfileIndex-1);
	
CliWPAset.accserveripset=0;
strcpy(uci_get_buf, cli_get_uci(func_buf4));
if (strcmp(uci_get_buf, "")!=0){
	strcpy(CliWPAset.accserverip, uci_get_buf);
	CliWPAset.accserveripset=1;
}
		
strcpy(uci_get_buf, cli_get_uci(func_buf5));
if (strcmp(uci_get_buf, "")!=0)
		strcpy(CliWPAset.accport, uci_get_buf);
			
CliWPAset.accsecretset=0;
strcpy(uci_get_buf, cli_get_uci(func_buf6));
if (strcmp(uci_get_buf, "")!=0){
	strcpy(CliWPAset.accsecret, uci_get_buf);
	CliWPAset.accsecretset=1;
}
		
strcpy(uci_get_buf, cli_get_uci(func_buf7));
if (strcmp(uci_get_buf, "")!=0)
	strcpy(CliWPAset.accinterval, uci_get_buf);
}


/*****************************************************************
* NAME: cmdradserver
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdradserver(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].server", wifi_index+SSIDProfileIndex-1);

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);
		tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
	
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		strcpy(CliWPAset.serverip, uci_set_buf);
		CliWPAset.serveripset=1;

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdradp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdradp(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].port", wifi_index+SSIDProfileIndex-1);
	
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1-65535)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 65535, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		strcpy(CliWPAset.port, uci_set_buf);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdradsecret
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdradsecret(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWpaRadiusSrvSecret", wifi_index+SSIDProfileIndex-1);

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1-64 characters)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

		if (!errorcheckIntRange( 1, 64, strlen(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
	
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);	
		
		strcpy(CliWPAset.secret, uci_set_buf);
		CliWPAset.secretset=1;

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdradaccount
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdradaccount(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWpaAccEnable", wifi_index+SSIDProfileIndex-1);
	
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		cli_set_uci(func_buf, uci_set_buf);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdradaccser
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdradaccser(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWpaRadiusAccSrvIP", wifi_index+SSIDProfileIndex-1);
	
	//Get the value of Radius Accounting from /etc/config/wireless
	sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANWpaAccEnable", wifi_index+SSIDProfileIndex-1);
	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	//Enable Radius Accounting first
	if( atoi(uci_get_buf) == 0 ){
		printf("Radius Accounting is disabled, please enable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}
	
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);
		tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
	
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		strcpy(CliWPAset.accserverip, uci_set_buf);
		CliWPAset.accserveripset=1;

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdradaccp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdradaccp(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWpaRadiusAccSrvPort", wifi_index+SSIDProfileIndex-1);

	//Get the value of Radius Accounting from /etc/config/wireless
	sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANWpaAccEnable", wifi_index+SSIDProfileIndex-1);
	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	//Enable Radius Accounting first
	if( atoi(uci_get_buf) == 0 ){
		printf("Radius Accounting is disabled, please enable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}
		
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1-65535)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 65535, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		strcpy(CliWPAset.accport, uci_set_buf);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdradaccsec
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdradaccsec(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWpaRadiusAccSrvSecret", wifi_index+SSIDProfileIndex-1);

	//Get the value of Radius Accounting from /etc/config/wireless
	sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANWpaAccEnable", wifi_index+SSIDProfileIndex-1);
	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	//Enable Radius Accounting first
	if( atoi(uci_get_buf) == 0 ){
		printf("Radius Accounting is disabled, please enable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}
	
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1-64 characters)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

		if (!errorcheckIntRange( 1, 64, strlen(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
	
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);	
		strcpy(CliWPAset.accsecret, uci_set_buf);
		CliWPAset.accsecretset=1;

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdinterval
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdinterval(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWpaRadiusAccInterimInterval", wifi_index+SSIDProfileIndex-1);

	//Get the value of Radius Accounting from /etc/config/wireless
	sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANWpaAccEnable", wifi_index+SSIDProfileIndex-1);
	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	//Enable Radius Accounting first
	if( atoi(uci_get_buf) == 0 ){
		printf("Radius Accounting is disabled, please enable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s seconds (60-600)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if ( !errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || atoi(cliData->tokens[cliData->tokenLen-1].token)!=0 && !errorcheckIntRange( 60, 600, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		strcpy(CliWPAset.accinterval, uci_set_buf);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwpaaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwpaaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR func_buf2[128];
T_CHAR func_buf3[128];
T_CHAR func_buf4[128];
T_CHAR func_buf5[128];
T_CHAR func_buf6[128];
T_CHAR func_buf7[128];
T_CHAR uci_get_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].server", wifi_index+SSIDProfileIndex-1);
	sprintf(func_buf1, "wireless.@wifi-iface[%d].port", wifi_index+SSIDProfileIndex-1);
	sprintf(func_buf2, "wireless.@wifi-iface[%d].WLANWpaRadiusSrvSecret", wifi_index+SSIDProfileIndex-1);

	//Get the value of Radius Accounting from /etc/config/wireless
	sprintf(func_buf3, "wireless.@wifi-iface[%d].WLANWpaAccEnable", wifi_index+SSIDProfileIndex-1);
	strcpy(uci_get_buf, cli_get_uci(func_buf3));

//Get the values of Radius Accounting	
sprintf(func_buf4, "wireless.@wifi-iface[%d].WLANWpaRadiusAccSrvIP", wifi_index+SSIDProfileIndex-1);
sprintf(func_buf5, "wireless.@wifi-iface[%d].WLANWpaRadiusAccSrvPort", wifi_index+SSIDProfileIndex-1);
sprintf(func_buf6, "wireless.@wifi-iface[%d].WLANWpaRadiusAccSrvSecret", wifi_index+SSIDProfileIndex-1);
sprintf(func_buf7, "wireless.@wifi-iface[%d].WLANWpaRadiusAccInterimInterval", wifi_index+SSIDProfileIndex-1);
	
	if(cliData->argc==0){
		
		if (CliWPAset.serveripset==0){
			tprintf("Radius server can't be empty\n");
			cliData->tokenLen-=1;
	  		return CLI_PARAMS_ERR;
		}
		
		if (CliWPAset.secretset==0){
			tprintf("Radius secret can't be empty\n");
			cliData->tokenLen-=1;
	  		return CLI_PARAMS_ERR;
		}
		
if ( (CliWPAset.accserveripset==0) && (atoi(uci_get_buf)==1) ) {
	tprintf("Radius accounting server can't be empty\n");
	cliData->tokenLen-=1;
	  return CLI_PARAMS_ERR;
}
		
if ( (CliWPAset.accsecretset==0) && (atoi(uci_get_buf)==1) ){
	tprintf("Radius accounting secret can't be empty\n");
	cliData->tokenLen-=1;
	  return CLI_PARAMS_ERR;
}
				
		cli_set_uci(func_buf, CliWPAset.serverip);
		cli_set_uci(func_buf1, CliWPAset.port);
		cli_set_uci(func_buf2, CliWPAset.secret);
		
		cli_set_uci(func_buf4, CliWPAset.accserverip);
		cli_set_uci(func_buf5, CliWPAset.accport);
		cli_set_uci(func_buf6, CliWPAset.accsecret);
		cli_set_uci(func_buf7, CliWPAset.accinterval);
				
		cliData->tokenLen--;
		return CLI_OK;
	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 network secu                    */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"network",	cli_table_network,	getNextTable,	"Wireless network",		"", AUTH_ADMIN, MODEL_ALL},
//};

//	{OPM_CB,	"secu",		NULL,			cmdsecu,	"Security Mode",		"", AUTH_ADMIN, MODEL_ALL},

//CliEntry cli_table_wpa_supplicant[]= {
//	{OPM_ALL,	"eapmtd",	NULL,				cmdeapmtd,	"EAP Method",			"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"eapauth",	NULL,				cmdeapauth,	"EAP Authentication",		"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"authid",	NULL,				cmdauthid,	"Authentication Identity",	"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"authpwd",	NULL,				cmdauthpwd,      "Authentication Password",	"", AUTH_ANY, MODEL_ALL},  
//	{OPM_ALL,	"accept",	NULL, 	   			cmdwpasupplicantaccept,	"Accept WPA setting",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_wpa_supplicant,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,				cmdapsecuexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: initialWPASUPtable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID initialWPASUPtable(T_VOID)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR func_buf2[128];
T_CHAR func_buf3[128];
T_CHAR uci_get_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	
	sprintf(func_buf, "wireless.@wifi-iface[%d].eap_type", wifi_index);
	sprintf(func_buf1, "wireless.@wifi-iface[%d].auth", wifi_index);
	sprintf(func_buf2, "wireless.@wifi-iface[%d].identity", wifi_index);
	sprintf(func_buf3, "wireless.@wifi-iface[%d].password", wifi_index);
	
	CliWPASUPset.eap_typeset==0;
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	if (strcmp(uci_get_buf, "")!=0){
		strcpy(CliWPASUPset.eap_type, uci_get_buf);
		CliWPASUPset.eap_typeset=1;
	}
	CliWPASUPset.authset==0;
	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	if (strcmp(uci_get_buf, "")!=0){
		strcpy(CliWPASUPset.auth, uci_get_buf);
		CliWPASUPset.authset=1;
	}		
	CliWPASUPset.identityset==0;
	strcpy(uci_get_buf, cli_get_uci(func_buf2));
	if (strcmp(uci_get_buf, "")!=0){
		strcpy(CliWPASUPset.identity, uci_get_buf);
		CliWPASUPset.identityset=1;
	}		
	CliWPASUPset.passwordset==0;
	strcpy(uci_get_buf, cli_get_uci(func_buf3));
	if (strcmp(uci_get_buf, "")!=0){
		strcpy(CliWPASUPset.password, uci_get_buf);
		CliWPASUPset.passwordset=1;
	}
}

/*****************************************************************
* NAME: cmdeapmtd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdeapmtd(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].eap_type", wifi_index);
	
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if (strcmp(uci_get_buf, "")!=0)
			tprintf("Current setting: %s (1.PEAP,2:TTLS)\n", uci_get_buf);
		else
			tprintf("Current setting: None (1.PEAP,2:TTLS)\n");
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if ( !errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || atoi(cliData->tokens[cliData->tokenLen-1].token)!=0 && !errorcheckIntRange( 1, 2, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		if ( atoi(cliData->tokens[cliData->tokenLen-1].token)==1 )
			strcpy(uci_set_buf, "PEAP");
		if ( atoi(cliData->tokens[cliData->tokenLen-1].token)==2 )
			strcpy(uci_set_buf, "TTLS");
			
		strcpy(CliWPASUPset.eap_type, uci_set_buf);
		CliWPASUPset.eap_typeset=1;

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}	
}

/*****************************************************************
* NAME: cmdeapauth
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdeapauth(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].auth", wifi_index);
	
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if (strcmp(uci_get_buf, "")!=0)
			tprintf("Current setting: %s (1.MSCHAP,2:MSCHAPV2)\n", uci_get_buf);
		else
			tprintf("Current setting: None (1.MSCHAP,2:MSCHAPV2)\n");		
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if ( !errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || atoi(cliData->tokens[cliData->tokenLen-1].token)!=0 && !errorcheckIntRange( 1, 2, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		if ( atoi(cliData->tokens[cliData->tokenLen-1].token)==1 )
			strcpy(uci_set_buf, "MSCHAP");
		if ( atoi(cliData->tokens[cliData->tokenLen-1].token)==2 )
			strcpy(uci_set_buf, "MSCHAPV2");
			
		strcpy(CliWPASUPset.auth, uci_set_buf);
		CliWPASUPset.authset=1;

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdauthid
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdauthid(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
	
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].identity", wifi_index);
	
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if (strcmp(uci_get_buf, "")!=0)
			tprintf("Current setting: %s (1-32 characters)\n", uci_get_buf);
		else
			tprintf("Current setting: None (1-32 characters)\n");
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		
		if (!errorcheckIntRange( 1, 32, strlen(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
			
		strcpy(CliWPASUPset.identity, uci_set_buf);
		CliWPASUPset.identityset=1;

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdauthpwd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdauthpwd(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].password", wifi_index);
	
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if (strcmp(uci_get_buf, "")!=0)
			tprintf("Current setting: %s (1-32 characters)\n", uci_get_buf);
			else
			tprintf("Current setting: None (1-32 characters)\n");			
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		
		if (!errorcheckIntRange( 1, 32, strlen(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
			
		strcpy(CliWPASUPset.password, uci_set_buf);
		CliWPASUPset.passwordset=1;

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwpasupplicantaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwpasupaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR func_buf2[128];
T_CHAR func_buf3[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
	
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	
	sprintf(func_buf, "wireless.@wifi-iface[%d].eap_type", wifi_index);
	sprintf(func_buf1, "wireless.@wifi-iface[%d].auth", wifi_index);
	sprintf(func_buf2, "wireless.@wifi-iface[%d].identity", wifi_index);
	sprintf(func_buf3, "wireless.@wifi-iface[%d].password", wifi_index);
	
	if(cliData->argc==0){
		
		if (CliWPASUPset.eap_typeset==0){
			tprintf("EAP Method can't be empty\n");
			cliData->tokenLen-=1;
	  		return CLI_PARAMS_ERR;
		}
		if (CliWPASUPset.authset==0){
			tprintf("EAP Authentication can't be empty\n");
			cliData->tokenLen-=1;
	  		return CLI_PARAMS_ERR;
		}		
		if (CliWPASUPset.identityset==0){
			tprintf("Authentication Identity can't be empty\n");
			cliData->tokenLen-=1;
	  		return CLI_PARAMS_ERR;
		}		
		if (CliWPASUPset.passwordset==0){
			tprintf("Authentication Password can't be empty\n");
			cliData->tokenLen-=1;
	  		return CLI_PARAMS_ERR;
		}
		
		cli_set_uci(func_buf, CliWPASUPset.eap_type);
		cli_set_uci(func_buf1, CliWPASUPset.auth);
		cli_set_uci(func_buf2, CliWPASUPset.identity);
		cli_set_uci(func_buf3, CliWPASUPset.password);
		
		cliData->tokenLen--;
		return CLI_OK;
	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 network stassid                 */
/*                   CLI Command -- wless2 network bssidact                */
/*                   CLI Command -- wless2 network bssid                   */
/*                   CLI Command -- wless2 network apscan                  */
/*                   CLI Command -- wless2 network secu                    */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"network",	cli_table_network,	getNextTable,	"Wireless network",		"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_network[]= {
//	{OPM_CB,	"stassid",    	NULL,    		cmdstassid,	"Static SSID  ",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_CB,	"bssidact",    	NULL,   		cmdbssidact,	"Prefered BSSID active",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_CB,	"bssid",    	NULL,			cmdbssid,	"Prefered BSSID",		"", AUTH_ADMIN, MODEL_ALL},
//2012-09-24 Add for TRUE Project
//	{OPM_ALL,	"apscan",	NULL,			cmdapscan,	"Site survey",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_CB,	"secu",		NULL,			cmdsecu,	"Security Mode",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,   	"help",		cli_table_network,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,   	"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdstassid
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdstassid(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.@wifi-iface[0].ssid";
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
//T_INT32 nawds_index;
		
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "wireless.@wifi-iface[%d].ssid", wifi_index);

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (32 characters at most)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		if (!errorcheckStrLength( 32, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of static SSID should not be larger than 32\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		cli_set_uci(func_buf, uci_set_buf);
		if ( operationeMode==OPM_RP ){
			sprintf(func_buf, "wireless.@wifi-iface[%d].ssid", wifi_index+1);
			cli_set_uci(func_buf, uci_set_buf);
		}/*If Operation mode==OPM_RP*/
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdbssidact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdbssidact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.@wifi-iface[0].PreferBSSIDEnable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
//T_INT32 nawds_index;
		
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "wireless.@wifi-iface[%d].PreferBSSIDEnable", wifi_index);

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );


		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdbssid
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdbssid(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.@wifi-iface[0].bssid";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
//T_INT32 nawds_index;
		
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "wireless.@wifi-iface[%d].bssid", wifi_index);

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);
		tprintf("Recognized input format: XX:XX:XX:XX:XX:XX    EX: 00:02:6F:BE:F0:7A\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		

		if (!errorcheckValidMACaddess(cliData->tokens[cliData->tokenLen-1].token)){
			tprintf("The input is not valid MAC address\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		lower2upperMacAddress( uci_set_buf );
		
		cli_set_uci(func_buf, uci_set_buf);
		if ( operationeMode==OPM_RP ){
			sprintf(func_buf, "wireless.@wifi-iface[%d].bssid", wifi_index+1);
			cli_set_uci(func_buf, uci_set_buf);
		}/*If Operation mode==OPM_RP*/
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdapscan
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdapscan(T_VOID* priv, CliData* cliData)
{
T_CHAR buf[128];
FILE *pp;

	if(cliData->argc==0){
		if ( (model_radio==2) || (model_radio==5) || (model_radio==7 && strcmp(current_radio_flag, "2.4G")==0) ){
			if ( model_radio==5 )
				printf("5G Scanning\n");
			else
				printf("2.4G Scanning\n");
			printf("Please wait...\n");
			system("iwlist ath0 scan > /tmp/apscan2");
			printf("       BSSID                 SSID        Channel    Signal    Type      Security\n");
			printf("================================================================================\n");
			system("awk -F\" \" \'{ printf \"%17s %22s %5s %8sdBm %8s %12s %20s\\n\", $1, $2, $5, $6, $8, $7}\' /tmp/apscan2 | tail -n +3");
		}
		if (  model_radio==7 && (strcmp(current_radio_flag, "5G")==0) ){
			printf("5G Scanning\n");
			printf("Please wait...\n");
			system("iwlist ath50 scan > /tmp/apscan5");
			printf("       BSSID                 SSID        Channel    Signal    Type      Security\n");
			printf("=================================================================================\n");
			system("awk -F\" \" \'{ printf \"%17s %22s %5s %8sdBm %8s %12s %20s\\n\", $1, $2, $5, $6, $8, $7}\' /tmp/apscan5 | tail -n +3");
		}
    		cliData->tokenLen--;
		return CLI_NOTHING;

	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}

/*****************************************************************
* NAME: displaycbsecurity
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID displaycbsecurity(T_VOID) {
int i;
T_INT32 start=0;
T_INT32 stop;
T_INT32 operationeMode=current_opmode;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
	
//Modify on 2012-11-13 for supplicant in CB, WDSSTA and CR mode
//if ( (strcmp(model_name, "eap350")==0) || (strcmp(model_name, "eap600")==0) || (strcmp(model_name, "era150")==0))

//Modify on 2013-02-23 by Philips to make sure that only CB, WDSSTA and CR modes have supplicant but RP mode doesn't have
if ( operationeMode==OPM_RP )
	stop=6;
else
	stop=10;
	for (i=start; i<=stop; i++)
	printf("%d - %s\n", CliCBsecurityTable[i].item, CliCBsecurityTable[i].cbsecurityName);

}

/*****************************************************************
* NAME: searchcbsecuritymode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 searchcbsecuritymode(T_INT32 index) {
	//WEP
	if ( index==2 || index==3 )
		return 1;
	//WPA-PSK
	if ( index>3 && index<=7 )
		return 2;
	//WPA
	if ( index>7 && index<=11 )
		return 3;
}

/*****************************************************************
* NAME: searchcbsecuritytable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/

T_CHAR* searchcbsecuritytable(T_INT32 index) {

	return CliWirelessmodeTable[index-1].wirelessmodeDescription;
}

/*****************************************************************
* NAME: cmdsecu
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsecu(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.@wifi-iface[0].encryption";

T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR uci_set_buf1[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
//T_INT32 nawds_index;
		
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "wireless.@wifi-iface[%d].encryption", wifi_index);

	if(cliData->argc==0){

		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displaycbsecurity();
		tprintf("Current setting: %s\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

		if (cbsecusetbridge==-1){
			//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
			if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
				sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

//Modify on 2012-11-13 for supplicant in CB, WDSSTA and CR mode
//if ( (strcmp(model_name, "eap350")==0) || (strcmp(model_name, "eap600")==0) || (strcmp(model_name, "era150")==0)){

//Modify on 2013-02-23 by Philips to make sure that only CB, WDSSTA and CR modes have supplicant but RP mode doesn't have
if ( operationeMode==OPM_RP ){
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 7, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
			}
}			
else {
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 11, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
			}
}
			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
			strcpy(uci_set_buf1, CliCBsecurityTable[atoi(uci_set_buf)-1].cbsecurityName);

			cli_set_uci(func_buf, uci_set_buf1);
			if ( operationeMode==OPM_RP ){
				sprintf(func_buf, "wireless.@wifi-iface[%d].encryption", wifi_index+1);
				cli_set_uci(func_buf, uci_set_buf1);
			}/*If Operation mode==OPM_RP*/
			
			if ( strcmp(uci_set_buf1, "none")==0){
				cliData->tokenLen-=2;
				return CLI_NOTHING;		
			}
			else{
				switch(searchcbsecuritymode(atoi(uci_set_buf))){
					case 1:	
						initialWEPtable();
						cliData->tokenLen--;
						//Handle the command --> wless2/network>secu 2
						if (cmdtreelevel==2){
							cbsecusetbridge=1;
							//prompt will be --> wless2/network/secu>
							cmdtreelevel=cliData->tokenLen;
						}
						return cmdHelp(cli_table_wep, cliData);
					case 2:
						initialWPAPSKtable();
						cliData->tokenLen--;
						//Handle the command --> wless2/network>secu 5
						if (cmdtreelevel==2){
							cbsecusetbridge=2;
							//prompt will be --> wless2/network/secu>
							cmdtreelevel=cliData->tokenLen;
						}
						return cmdHelp(cli_table_wpapsk, cliData);
//Modify on 2012-11-13 for supplicant in CB, WDSSTA and CR mode						
					case 3:
						initialWPASUPtable();
						cliData->tokenLen--;
						//Handle the command --> wless2/network>secu 5
						if (cmdtreelevel==2){
							cbsecusetbridge=3;
							//prompt will be --> wless2/network/secu>
							cmdtreelevel=cliData->tokenLen;
						}
						return cmdHelp(cli_table_wpa_supplicant, cliData);
				}
			}
		}
		if ( cbsecusetbridge==1 )
			return getNextTable(cli_table_wep, cliData);
		else if ( cbsecusetbridge==2 )
			return getNextTable(cli_table_wpapsk, cliData);
//Modify on 2012-11-13 for supplicant in CB, WDSSTA and CR mode			
		else if ( cbsecusetbridge==3 )
			return getNextTable(cli_table_wpa_supplicant, cliData);
			
	}
	else if(cliData->argc>1){
		if ( cbsecusetbridge==1 )
			return getNextTable(cli_table_wep, cliData);
		else if ( cbsecusetbridge==2 )
			return getNextTable(cli_table_wpapsk, cliData);
//Modify on 2012-11-13 for supplicant in CB, WDSSTA and CR mode			
		else if ( cbsecusetbridge==3 )
			return getNextTable(cli_table_wpa_supplicant, cliData);
			
//Modify on 2012-11-13 for supplicant in CB, WDSSTA and CR mode
//if ( (strcmp(model_name, "eap350")==0) || (strcmp(model_name, "eap600")==0) || (strcmp(model_name, "era150")==0))

//Modify on 2013-02-23 by Philips to make sure that only CB, WDSSTA and CR modes have supplicant but RP mode doesn't have
if ( operationeMode==OPM_RP )
		//Handle the command --> wless2 network secu 2 X ...
		if (!errorcheckValidDecimal(cliData->tokens[3].token) || !errorcheckIntRange( 1, 7, atoi(cliData->tokens[3].token)) )
	  			return CLI_PARAMS_ERR;
else
		if (!errorcheckValidDecimal(cliData->tokens[3].token) || !errorcheckIntRange( 1, 11, atoi(cliData->tokens[3].token)) )
	  			return CLI_PARAMS_ERR;
	  			
		strcpy(uci_set_buf, cliData->tokens[3].token);
		strcpy(uci_set_buf1, CliCBsecurityTable[atoi(uci_set_buf)-1].cbsecurityName);

		cli_set_uci(func_buf, uci_set_buf1);
		if ( operationeMode==OPM_RP ){
			sprintf(func_buf, "wireless.@wifi-iface[%d].encryption", wifi_index+1);
			cli_set_uci(func_buf, uci_set_buf1);
		}/*If Operation mode==OPM_RP*/
			
		if ( strcmp(uci_set_buf1, "none")==0){
			//handle too many argument --> wless2/network>secu 1 X X ...
			if (cliData->tokenLen>=5)
				return CLI_PARAMS_ERR;
		
			return CLI_NOTHING;		
		}
		else{
			switch(searchcbsecuritymode(atoi(uci_set_buf))){
				case 1:	//initial WEP, WPAPSK, WPA table only once
					if (security_set==0){
						initialWEPtable();
						security_set=1;
					}
					cliData->argc--;
					return getNextTable(cli_table_wep, cliData);
				case 2:
					if (security_set==0){
						initialWPAPSKtable();
						security_set=1;
					}
					cliData->argc--;
					return getNextTable(cli_table_wpapsk, cliData);						
//Modify on 2012-11-13 for supplicant in CB, WDSSTA and CR mode						
				case 3:
					if (security_set==0){
						initialWPASUPtable();
						security_set=1;
					}
					cliData->argc--;
					return getNextTable(cli_table_wpa_supplicant, cliData);					
			}
		}
	
	
	}
}


/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 guest gnact                     */
/*                   CLI Command -- wless2 guest gnssid                    */
/*                   CLI Command -- wless2 guest gnsupssid                 */
/*                   CLI Command -- wless2 guest gnsepa                    */
/*                   CLI Command -- wless2 guest gnapsecu                  */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_AP|OPM_WDSAP,	"guest",	cli_table_guestnetwork,	getNextTable,	"Wireless guest network",	"", AUTH_ADMIN, EAP900_ID},
//};

//Add on 2013-06-07 by Philips to support Guest Network for eap900 which is requested by Jacy
//CliEntry cli_table_guestnetwork[]= {
//	{OPM_AP|OPM_WDSAP,	"gnact",	NULL,			cmdgnact,	"Guest network active",		"", AUTH_ANY, MODEL_ALL},
//	{OPM_AP|OPM_WDSAP,	"gnssid",	NULL,			cmdgnssid,	"Guest network SSID",		"", AUTH_ANY, MODEL_ALL},
//	{OPM_AP|OPM_WDSAP,	"gnsupssid",	NULL,			cmdgnsupssid,	"Suppressed SSID",		"", AUTH_ANY, MODEL_ALL},
//	{OPM_AP|OPM_WDSAP,	"gnsepa",	NULL,			cmdgnsepa,	"Station separation",		"", AUTH_ANY, MODEL_ALL},
//	{OPM_AP|OPM_WDSAP,	"apsecu",	NULL,			cmdapsecu,	"Station security",		"", AUTH_ANY, MODEL_ALL},
//	{OPM_AP|OPM_WDSAP,	"guestip",	cli_table_guestipset,	getNextTable,	"Guest network IP settings",	"", AUTH_ANY, MODEL_ALL},
//	{OPM_AP|OPM_WDSAP,	"guestdhcp",   	cli_table_guestdhcpset,	getNextTable,	"Guest network As DHCP Server",	"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,		"help",		cli_table_guestnetwork,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,		"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdgnact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0607
* Modify:   
****************************************************************/
CliStatus cmdgnact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "wireless.w0_index25.WLANEnable");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w1_index25.WLANEnable");

	if(cliData->argc==0){

		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
			
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		cli_set_uci(func_buf, uci_set_buf);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdgnssid
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0607
* Modify:   
****************************************************************/
CliStatus cmdgnssid(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "wireless.w0_index25.ssid");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w1_index25.ssid");
	
	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (32 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 32, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of SSID should not be larger than 32\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		cli_set_uci(func_buf, uci_set_buf);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdgnsupssid
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0607
* Modify:   
****************************************************************/
CliStatus cmdgnsupssid(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "wireless.w0_index25.hidden");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w1_index25.hidden");

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));	
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );	

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		cli_set_uci(func_buf, uci_set_buf);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdgnsepa
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0607
* Modify:   
****************************************************************/
CliStatus cmdgnsepa(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "wireless.w0_index25.isolate");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w1_index25.isolate");

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));	
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );			

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		cli_set_uci(func_buf, uci_set_buf);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdgnapsecu
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdgnapsecu(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR wifiinterface[128]="wireless.wifi0.hwmode";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR uci_set_buf1[128];
T_CHAR wirelessmode[128];
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(wifiinterface, "wireless.wifi1.hwmode");

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "wireless.w0_index25.encryption");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.w1_index25.encryption");

	strcpy(wirelessmode, getWirelessmode(wifiinterface));
	
	SSIDProfileIndex=26;
	
	if(cliData->argc==0){
		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//display wep, psk, wpa security mode
		
		displayapsecurity(wirelessmode, SSIDProfileIndex);
		tprintf("Current setting: %s\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		//handle 1 argument for apsecu before set apsecusetbridge  EX: ...guest>gnapsecu 2
		if (apsecusetbridge==-1){			
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckapsecurity(wirelessmode, SSIDProfileIndex, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
			}

			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
			//convert index to name EX: 1 -> none; 6 -> psk2 tkip; 10 -> psk-mixed aes
			strcpy(uci_set_buf1, searchapsecuritytable(wirelessmode, SSIDProfileIndex, atoi(uci_set_buf)));
				
			cli_set_uci(func_buf, uci_set_buf1);
		
			if ( strcmp(uci_set_buf1, "none")==0){
				cliData->tokenLen-=2;
				return CLI_NOTHING;		
			
			}
			else{		
				//convert index to wep, psk or wpa table
				switch(searchapsecuritymode(wirelessmode, SSIDProfileIndex, atoi(uci_set_buf))){
					case 1:					
						initialWEPtable();
						cliData->tokenLen--;
						//Handle the command --> wless2/guest>gnapsecu 2
						if (cmdtreelevel==2){
							apsecusetbridge=1;
							//prompt will be -->  wless2/guest/gnapsecu>
							cmdtreelevel=cliData->tokenLen;
						}

						return cmdHelp(cli_table_wep, cliData);
					case 2:
						initialWPAPSKtable();
						cliData->tokenLen--;
						//Handle the command --> wless2/guest>gnapsecu 4
						if (cmdtreelevel==2){
							apsecusetbridge=2;
							//prompt will be -->  wless2/guest/gnapsecu>
							cmdtreelevel=cliData->tokenLen;
						}
						
						return cmdHelp(cli_table_wpapsk, cliData);
					case 3:					
						initialWPAtable();
						cliData->tokenLen--;
						//Handle the command --> wless2/guest>gnapsecu 18
						if (cmdtreelevel==2){
							apsecusetbridge=3;
							//prompt will be -->  wless2/guest/gnapsecu>
							cmdtreelevel=cliData->tokenLen;
						}
						
						return cmdHelp(cli_table_wpa, cliData);
				}
			}
		}
		
		//handle 1 argument for gnapsecu after set apsecusetbridge EX:...guest/gnapsecu>dkey
		if ( apsecusetbridge==1 )
			return getNextTable(cli_table_wep, cliData);
		else if ( apsecusetbridge==2 )
			return getNextTable(cli_table_wpapsk, cliData);
		else if ( apsecusetbridge==3 )
			return getNextTable(cli_table_wpa, cliData);

	}
	else if(cliData->argc>1){
		//handle 2 or more argument for gnapsecu after set apsecusetbridge EX:...guest/gnapsecu>dkey 3
		if ( apsecusetbridge==1 )
			return getNextTable(cli_table_wep, cliData);
		else if ( apsecusetbridge==2 )
			return getNextTable(cli_table_wpapsk, cliData);
		else if ( apsecusetbridge==3 )
			return getNextTable(cli_table_wpa, cliData);
		
		///Handle the command --> wless2 guest gnapsecu 3 X ...
		if ( !errorcheckValidDecimal(cliData->tokens[3].token)||!errorcheckapsecurity(wirelessmode, SSIDProfileIndex, atoi(cliData->tokens[3].token)) ){
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[3].token);
		//convert index to name EX: 1 -> none; 6 -> psk2 tkip; 10 -> psk-mixed aes
		strcpy(uci_set_buf1, searchapsecuritytable(wirelessmode, SSIDProfileIndex, atoi(uci_set_buf)));
				
		cli_set_uci(func_buf, uci_set_buf1);

		if ( strcmp(uci_set_buf1, "none")==0){
			return CLI_NOTHING;		
			
		}
		else{
			//convert index to wep, psk or wpa table
			switch(searchapsecuritymode(wirelessmode, SSIDProfileIndex, atoi(uci_set_buf))){

				case 1:	//initial WEP, WPAPSK, WPA table only once
					if (security_set==0){
						initialWEPtable();
						security_set=1;
					}
					cliData->argc--;
					return getNextTable(cli_table_wep, cliData);
				case 2:
					if (security_set==0){
						initialWPAPSKtable();
						security_set=1;
					}
					cliData->argc--;
					return getNextTable(cli_table_wpapsk, cliData);
				case 3:
					if (security_set==0){
						initialWPAtable();		
						security_set=1;
					}
					cliData->argc--;
					return getNextTable(cli_table_wpa, cliData);
			}
		}

	}
}


/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 guest gnip                   */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_AP|OPM_WDSAP,	"guest",	cli_table_guestnetwork,	getNextTable,	"Wireless guest network",	"", AUTH_ADMIN, EAP900_ID},
//};

//CliEntry cli_table_guestnetwork[]= {
//	{OPM_AP|OPM_WDSAP,	"gnip",		cli_table_guestipset,	getNextTable,	"Guest network IP settings",	"", AUTH_ANY, MODEL_ALL},
//};

//CliEntry cli_table_guestipset[]= {
//	{OPM_AP|OPM_WDSAP,	"gnipaddr",	NULL,			cmdgnipaddr,	"Guest network IP address",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP|OPM_WDSAP,	"gnipsubn",	NULL,			cmdgnipsubn,	"Guest network IP subnet mask",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP|OPM_WDSAP,	"accept",  	NULL,			cmdgnipsetaccept, "Accept Guest network IP setting",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,		"help",		cli_table_guestipset,	cmdHelp,	"Help",					"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,		"exit",		NULL,			cmdipsetexit,	"Exit",					"", AUTH_ADMIN, MODEL_ALL},    
//	{ CMD_END_TAG }
//};

/*****************************************************************
* NAME: cmdgnipaddr
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0607
* Modify:   
****************************************************************/
CliStatus cmdgnipaddr(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.guest.ipaddr";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Cliguestnetworkipset.ipset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		else{
			strcpy(uci_get_buf, Cliguestnetworkipset.ip);
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid segmentation fault when the length of input > 128
		//strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);				
		strcpy(Cliguestnetworkipset.ip, uci_set_buf);
		Cliguestnetworkipset.ipset=1;

		cliData->tokenLen-=2;		
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdgnipsubn
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0607
* Modify:   
****************************************************************/
CliStatus cmdgnipsubn(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.guest.netmask";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Cliguestnetworkipset.maskset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf);
		}
		else{
			strcpy(uci_get_buf, Cliguestnetworkipset.subnetmask);
			tprintf("Current setting: %s\n", uci_get_buf);
		}

    		cliData->tokenLen--;	
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid segmentation fault when the length of input > 128
		//strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		if (!errorcheckValidSubnetMask( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);	
		
		strcpy(Cliguestnetworkipset.subnetmask, uci_set_buf);
		Cliguestnetworkipset.maskset=1;

		cliData->tokenLen-=2;	
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdgnipsetaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0607
* Modify:   
****************************************************************/
CliStatus cmdgnipsetaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.guest.ipaddr";
T_CHAR func_buf1[128]="network.guest.netmask";
T_CHAR func_buf2[128]="network.lan.ipaddr";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_get_buf2[128];

	if(cliData->argc==0){
		//Get guest network ipv4 address
		if (Cliguestnetworkipset.ipset==0)
			strcpy(uci_get_buf, cli_get_uci(func_buf));
		else
			strcpy(uci_get_buf, Cliguestnetworkipset.ip);
		
		//Get guest network subnet mask
		if (Cliguestnetworkipset.maskset==0)
			strcpy(uci_get_buf1, cli_get_uci(func_buf1));
		else
			strcpy(uci_get_buf1, Cliguestnetworkipset.subnetmask);
		
		//Get lan ipv4 address
		strcpy(uci_get_buf2, cli_get_uci(func_buf2));
		
		if (!errorcheckValidIPandMask(uci_get_buf, uci_get_buf1)){
			cliData->tokenLen-=1;
			tprintf("Invalid IP address\n");
	  		return CLI_PARAMS_ERR;
		}	

		if (errorcheckSameDomain(uci_get_buf, uci_get_buf2, uci_get_buf1 )){
			cliData->tokenLen-=1;
			tprintf("The IP address of Guest Network and LAN should not be in the same subnet.\n");
	  		return CLI_PARAMS_ERR;
		}
		cli_set_uci(func_buf, uci_get_buf);
		cli_set_uci(func_buf1, uci_get_buf1);

		cliData->tokenLen--;
		return CLI_OK;
	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 guest guestdhcp                 */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_AP|OPM_WDSAP,	"guest",	cli_table_guestnetwork,	getNextTable,	"Wireless guest network",	"", AUTH_ADMIN, EAP900_ID},
//};

//CliEntry cli_table_guestnetwork[]= {
//	{OPM_AP|OPM_WDSAP,	"gndhcp",   	cli_table_guestdhcpset,	getNextTable,	"Guest network As DHCP Server",	"", AUTH_ANY, MODEL_ALL},
//};

//CliEntry cli_table_guestdhcpset[]= {
//	{OPM_AP|OPM_WDSAP,	"gnsip",	NULL,			cmdgndhcpsip,		"Starting IP Address",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP|OPM_WDSAP,	"gneip",	NULL,        		cmdgndhcpeip,		"Ending IP Address",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP|OPM_WDSAP,	"gnwip",	NULL,        		cmdgndhcpwip,		"WINS Server IP",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP|OPM_WDSAP,	"accept",	NULL, 	   		cmddhcpsetaccept,	"Accept DHCP setting",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,		"help",		cli_table_guestdhcpset,	cmdHelp,		"Help",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,		"exit",		NULL,			cmddhcpsetexit,		"Exit",			"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

/*****************************************************************
* NAME: cmdgndhcpsip
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdgndhcpsip(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="dhcp.guest.start";
T_CHAR uci_get_buf[32];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Clilguestnetworkdhcpset.startipset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		else{
			strcpy(uci_get_buf, Clilguestnetworkdhcpset.startip);
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		Clilguestnetworkdhcpset.startipset=1;
		strcpy(Clilguestnetworkdhcpset.startip, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdgndhcpeip
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdgndhcpeip(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="dhcp.guest.dhcp_stop_addr";
T_CHAR uci_get_buf[32];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Clilguestnetworkdhcpset.endipset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		else{
			strcpy(uci_get_buf, Clilguestnetworkdhcpset.endip);
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		Clilguestnetworkdhcpset.endipset=1;
		strcpy(Clilguestnetworkdhcpset.endip, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdgndhcpwip
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdgndhcpwip(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="dhcp.guest.dhcp_option";
T_CHAR uci_get_buf[32];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Clilguestnetworkdhcpset.winsipset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf+3);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		else{
			strcpy(uci_get_buf, Clilguestnetworkdhcpset.winsip);
			tprintf("Current setting: %s\n", uci_get_buf+3);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		Clilguestnetworkdhcpset.winsipset=1;
		strcpy(Clilguestnetworkdhcpset.winsip, "44,");
		strcat(Clilguestnetworkdhcpset.winsip, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}


/*****************************************************************
* NAME: cmdgndhcpsetaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/

CliStatus cmdgndhcpsetaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="dhcp.guest.start";
T_CHAR func_buf1[128]="dhcp.guest.dhcp_stop_addr";
T_CHAR func_buf2[128]="dhcp.guest.dhcp_option";
T_CHAR func_lanip[128]="network.guest.ipaddr";	
T_CHAR func_lanmask[128]="network.guest.netmask";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_get_buf2[128];
T_CHAR uci_get_lanip[128];
T_CHAR uci_get_lanmask[128];
T_CHAR c1[255];

	strcpy(uci_get_lanip, cli_get_uci(func_lanip));
	strcpy(uci_get_lanmask, cli_get_uci(func_lanmask));

	if(cliData->argc==0){
				
		if (Clilguestnetworkdhcpset.startipset==0)
			strcpy(uci_get_buf, cli_get_uci(func_buf));
		else
			strcpy(uci_get_buf, Clilguestnetworkdhcpset.startip);
		
		if (Clilguestnetworkdhcpset.endipset==0)
			strcpy(uci_get_buf1, cli_get_uci(func_buf1));
		else
			strcpy(uci_get_buf1, Clilguestnetworkdhcpset.endip);
		
		if (Clilguestnetworkdhcpset.winsipset==0)
			strcpy(uci_get_buf2, cli_get_uci(func_buf2));
		else
			strcpy(uci_get_buf2, Clilguestnetworkdhcpset.winsip);
		
		
		if (!errorcheckSameDomain(uci_get_lanip, uci_get_buf, uci_get_lanmask )){
			cliData->tokenLen-=1;
			tprintf("DHCP start IP address and LAN IP address should be in the same subnet\n");
	  		return CLI_PARAMS_ERR;
		}
		if (!errorcheckSameDomain(uci_get_lanip, uci_get_buf1, uci_get_lanmask )){
			cliData->tokenLen-=1;
			tprintf("DHCP end IP address and LAN IP address should be in the same subnet\n");
	  		return CLI_PARAMS_ERR;
		}
		if (!errorcheckDHCPRange(uci_get_buf, uci_get_buf1 )){
			cliData->tokenLen-=1;
			tprintf("DHCP end IP address is less than DHCP start IP address\n");
	  		return CLI_PARAMS_ERR;
		}
		
		if (!checkValidDHCPRegionLANIP(uci_get_lanip, uci_get_buf, uci_get_buf1 )){
			cliData->tokenLen-=1;
			tprintf("LAN IP address should not be inside DHCP server range\n");
	  		return CLI_PARAMS_ERR;
		}

		cli_set_uci(func_buf, uci_get_buf);
		cli_set_uci(func_buf1, uci_get_buf1);
		cli_set_uci(func_buf2, uci_get_buf2);
		
		tprintf("Currunt start IP setting: %s\n", uci_get_buf);
		tprintf("Currunt end IP setting: %s\n", uci_get_buf1);
		tprintf("Currunt WINS IP setting: %s\n", uci_get_buf2+3);
		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 macfilter                       */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_AP,	"macfilter",	cli_table_mac_filter,	getNextTable,	"Wireless mac filter",		"", AUTH_ANY,	MODEL_ALL},
//};

//CliEntry cli_table_mac_filter[]= {
//	{OPM_AP,	"acl",		NULL,    		cmdacl,		"ACL mode",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP,	"add",		NULL,			cmdadd,		"MAC address add",      "", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP,	"del",		NULL,			cmddel,		"MAC address delete",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_mac_filter,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: getMACfilterdata
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID getMACfilterdata(T_CHAR* buf, T_INT32 argCount) {
T_INT32 i=0;
T_CHAR* token;

	token =strtok(buf, " ");
	while(token)
	{
		if (argCount==0){
			MACfilterData.CliMACfilterTable[i].item=i+1;
			strcpy(MACfilterData.CliMACfilterTable[i].macaddress, token);
		}
		token = strtok(NULL, " ");
		i++;
	}
	MACfilterData.count=i;
}

/*****************************************************************
* NAME: putMACfilterdata
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID putMACfilterdata(T_INT32 index, T_INT32 wifi_index, T_INT32 operationeMode) {
T_INT32 i=0;
T_INT32 j=0;
T_CHAR c1[255];
T_CHAR c0[255];
T_INT32 ssidCount;
	
	ssidCount=getModelssidCount(operationeMode);
	
	for (i=0; i<MACfilterData.count; i++){
		if ( i==(index-1) )
			continue;

//Modify for C600 on 2013-04-29 to add MAC filter per SSID for C600
if ( strcmp(model_name, "c600")==0 ){
	printf("cmddel -- putMACfilterdata for c600\n");
	sprintf(c0, "wireless.@wifi-iface[%d].maclist", wifi_index+SSIDProfileIndex-1);
	sprintf(c1, "uci add_list %s=%s", c0, MACfilterData.CliMACfilterTable[i].macaddress);

	system(c1);
}
else{
		
		for (j=wifi_index; j<wifi_index+ssidCount; j++){
		
			sprintf(c0, "wireless.@wifi-iface[%d].maclist", j);
			sprintf(c1, "uci add_list %s=%s", c0, MACfilterData.CliMACfilterTable[i].macaddress);

			system(c1);
			
			if ( operationeMode==OPM_RP && j==1 )
				break;
		}

}

	}
	system("uci commit");

}

/*****************************************************************
* NAME: displayMACfilterdata
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID displayMACfilterdata(T_VOID) {
T_INT32 i;
	for (i=0; i<MACfilterData.count; i++)
		printf("%d - %s\n", MACfilterData.CliMACfilterTable[i].item, MACfilterData.CliMACfilterTable[i].macaddress );
}

/*****************************************************************
* NAME: lower2upperMacAddress
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID lower2upperMacAddress(char* mac) 
{
	 while (*mac) {
		if (isxdigit(*mac) && ( (*mac)>=97 && (*mac)<=102 )  ) {
			(*mac)-=32;
		}
	++mac;
	}
}

/*****************************************************************
* NAME: checkRedundancyMACfilterlist
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 checkRedundancyMACfilterlist(T_CHAR* maclist, T_CHAR* input) {

	if (strstr(maclist, input)!=NULL ){
		return 0;/*exist*/
	}else{
		return 1;/*not exist*/
	}
}

/*****************************************************************
* NAME: cmdacl
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdacl(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.@wifi-iface[0].macpolicy";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR c1[64];
T_INT32 retval_int;
T_INT32 ssidCount;
T_INT32 i;
T_INT32 wifi_index;
T_INT32 operationeMode=current_opmode;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);
	
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "wireless.@wifi-iface[%d].macpolicy", wifi_index+SSIDProfileIndex-1);

	if(cliData->argc==0){	
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if ( strcmp(uci_get_buf, "")==0 || strcmp(uci_get_buf, " ")==0 )
			strcpy(uci_get_buf, "disable");
		tprintf("Current setting: %s (0:Disable, 1:Deny, 2:Allow)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 2, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		retval_int=atoi(uci_set_buf);
		if (retval_int==0)
			strcpy(uci_set_buf, " ");
		else if (retval_int==1)
			strcpy(uci_set_buf, "deny");
		else if (retval_int==2)
			strcpy(uci_set_buf, "allow");


//Modify for C600 on 2013-04-29 to add MAC filter per SSID for C600
if ( strcmp(model_name, "c600")==0 || strcmp(model_name, "eap900h")==0 || strcmp(model_name, "eap900")==0 ){
	//(0:Disable, 1:Deny, 2:Allow) but acl= 0(disable), 1(allow), 2(deny)
	if (retval_int==1)
		retval_int = 2;
	else if (retval_int==2)
		retval_int = 1;	
	//Modify on 2013-06-25 using API which is provided by Sam to set ACL of MAC filter per SSID for eap900 and C600
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		// ath0 - ath7
		sprintf(c1, "/usr/sbin/macfilter_api.lua set ath%d %d", 0+SSIDProfileIndex-1, retval_int);
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		// ath50 - ath57
		sprintf(c1, "/usr/sbin/macfilter_api.lua set ath%d %d", 50+SSIDProfileIndex-1, retval_int);
	system(c1);
	//synchronize the /etc/config/filter to /etc/config/wireless
	system("/usr/sbin/macfilter_api.lua sync");
	system("uci commit");
}
else{
		
		for (i=wifi_index; i<wifi_index+ssidCount; i++){
		
			sprintf(func_buf, "wireless.@wifi-iface[%d].macpolicy", i);
			cli_set_uci(func_buf, uci_set_buf);
			if ( operationeMode==OPM_RP && i==1 )
				break;
		}	

}

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdadd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0516
* Modify:   
****************************************************************/
CliStatus cmdadd(T_VOID* priv, CliData* cliData)
{
//T_CHAR func_buf[128]="wireless.@wifi-iface[0].maclist";
T_CHAR uci_get_buf[1024];
T_CHAR uci_set_buf[128];
//T_INT32 retval_int;
//T_CHAR c1[255];
FILE *pp;
T_INT32 ssidCount;
T_INT32 i;
T_INT32 wifi_index;
T_INT32 operationeMode=current_opmode;
T_CHAR buf[128];
T_CHAR maclist_buf[1024];


	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);
	
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	//redirect error message "uci: Entry not found"
	sprintf(buf, "uci get wireless.@wifi-iface[%d].maclist 2> /dev/null", wifi_index);


//Modify for C600 on 2013-04-29 to add MAC filter per SSID for C600
if ( strcmp(model_name, "c600")==0 || strcmp(model_name, "eap900h")==0 || strcmp(model_name, "eap900")==0 ){
	//Modify on 2013-06-25 using API which is provided by Sam to get mac list of MAC filter per SSID for eap900 and C600
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		sprintf(buf, "/usr/sbin/macfilter_api.lua get ath%d list", 0+SSIDProfileIndex-1);
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		sprintf(buf, "/usr/sbin/macfilter_api.lua get ath%d list", 50+SSIDProfileIndex-1);
}


	if(cliData->argc==0){

		if( (pp = popen(buf, "r")) == NULL )
		{
			printf("popen() error!\n");
			exit(1);
		}
		
		if ( fgets(uci_get_buf, sizeof uci_get_buf, pp)!=0 ){
			uci_get_buf[strlen(uci_get_buf)-1]='\0';
    			//to put maclist into MACfilterdata when cliData->argc==0
    			getMACfilterdata(uci_get_buf, cliData->argc);
    			displayMACfilterdata();
		}

		pclose(pp);
//printf("%d_%s\n", MACfilterData.count, MACfilterData.CliMACfilterTable[40].macaddress);		
    		tprintf("Recognized input format: XX:XX:XX:XX:XX:XX    EX: 00:02:6F:BE:F0:7A\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		

		if( (pp = popen(buf, "r")) == NULL )
		{
			printf("popen() error!\n");
			exit(1);
		}
		
		if ( fgets(uci_get_buf, sizeof uci_get_buf, pp)!=0 ){
			uci_get_buf[strlen(uci_get_buf)-1]='\0';
    			//to get MACfilterData.count when cliData->argc==1
    			strcpy(maclist_buf, uci_get_buf);
    			getMACfilterdata(maclist_buf, cliData->argc);
		}

		pclose(pp);
		
		if (MACfilterData.count>=50){
			tprintf("Table is full. The maximal value of table size is 50.\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		if (!errorcheckValidMACaddess( cliData->tokens[cliData->tokenLen-1].token )){
			tprintf("The input is not valid MAC address\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		lower2upperMacAddress( uci_set_buf );

		if (!checkRedundancyMACfilterlist( uci_get_buf, uci_set_buf )){
			cliData->tokenLen-=2;
			printf("The input MAC address has already existed\n");
	  		return CLI_PARAMS_ERR;	
		}


//Modify for C600 on 2013-04-29 to add MAC filter per SSID for C600
if ( strcmp(model_name, "c600")==0 || strcmp(model_name, "eap900h")==0 || strcmp(model_name, "eap900")==0 ){
	//Modify on 2013-06-25 using API which is provided by Sam to add mac list of MAC filter per SSID for eap900 and C600
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		//ath0 - ath7
		sprintf(buf, "/usr/sbin/macfilter_api.lua add ath%d %s", 0+SSIDProfileIndex-1, uci_set_buf);
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		//ath50 - ath57
		sprintf(buf, "/usr/sbin/macfilter_api.lua add ath%d %s", 50+SSIDProfileIndex-1, uci_set_buf);
	system(buf);
	//synchronize the /etc/config/filter to /etc/config/wireless
	system("/usr/sbin/macfilter_api.lua sync");
	system("uci commit");	
}
else{

		//add input mac address into the buttom of configuration file 
		for (i=wifi_index; i<wifi_index+ssidCount; i++){
		
			sprintf(buf, "uci add_list wireless.@wifi-iface[%d].maclist=%s", i, uci_set_buf);
			system(buf);
			if ( operationeMode==OPM_RP && i==1 )
				break;
		}
		system("uci commit");

}		


		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmddel
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddel(T_VOID* priv, CliData* cliData)
{
//T_CHAR func_buf[128]="wireless.@wifi-iface[0].maclist";
T_CHAR uci_get_buf[1024];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;
T_INT32 i;
//T_CHAR c1[255];
FILE *pp;
T_INT32 ssidCount;
T_INT32 wifi_index;
T_INT32 operationeMode=current_opmode;
T_CHAR buf[128];


	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);
	
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(buf, "uci get wireless.@wifi-iface[%d].maclist 2> /dev/null", wifi_index);


//Modify for C600 on 2013-04-29 to add MAC filter per SSID for C600
if ( strcmp(model_name, "c600")==0 || strcmp(model_name, "eap900h")==0 || strcmp(model_name, "eap900")==0 ){
	//Modify on 2013-06-25 using API which is provided by Sam to get mac list of MAC filter per SSID for eap900 and C600
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		sprintf(buf, "/usr/sbin/macfilter_api.lua get ath%d list", 0+SSIDProfileIndex-1);
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		sprintf(buf, "/usr/sbin/macfilter_api.lua get ath%d list", 50+SSIDProfileIndex-1);
}


	if(cliData->argc==0){

		if( (pp = popen(buf, "r")) == NULL )
		{
			printf("popen() error!\n");
			exit(1);
		}

		if ( fgets(uci_get_buf, sizeof uci_get_buf, pp)!=0 ){
			uci_get_buf[strlen(uci_get_buf)-1]='\0';
			
			getMACfilterdata(uci_get_buf, cliData->argc);
    			displayMACfilterdata();
    			if (MACfilterData.count>0){
    				tprintf("Recognized input format: ");
    				for (i=1; i<MACfilterData.count; i++)
    					tprintf("%d, ", i);
    				tprintf("%d\n", i);
    			}
		}

		pclose(pp);
			
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if( (pp = popen(buf, "r")) == NULL )
		{
			printf("popen() error!\n");
			exit(1);
		}
		//maclist is empty
		if ( fgets(uci_get_buf, sizeof uci_get_buf, pp)==0 ){
			cliData->tokenLen-=2;
			return CLI_PARAMS_ERR;
		}
		//maclist is not empty
		else{
			//check delete item is valid
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, MACfilterData.count, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
			}

			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
			retval_int=atoi(uci_set_buf);
		
			uci_get_buf[strlen(uci_get_buf)-1]='\0';
			//get maclist from configuration file into MACtable
    			getMACfilterdata(uci_get_buf, cliData->argc-1);


//Modify for C600 on 2013-04-29 to add MAC filter per SSID for C600
if ( strcmp(model_name, "c600")==0 || strcmp(model_name, "eap900h")==0 || strcmp(model_name, "eap900")==0 ){
	//Modify on 2013-06-25 using API which is provided by Sam to delete mac list of MAC filter per SSID for eap900 and C600
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		sprintf(buf, "/usr/sbin/macfilter_api.lua del ath%d %s", 0+SSIDProfileIndex-1, MACfilterData.CliMACfilterTable[retval_int-1].macaddress);
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		sprintf(buf, "/usr/sbin/macfilter_api.lua del ath%d %s", 50+SSIDProfileIndex-1, MACfilterData.CliMACfilterTable[retval_int-1].macaddress);
	system(buf);
	system("uci commit");
	//synchronize the /etc/config/filter to /etc/config/wireless
	system("/usr/sbin/macfilter_api.lua sync");
	system("uci commit");
}
else{
    		
    			for (i=wifi_index; i<wifi_index+ssidCount; i++){
		
				sprintf(buf, "uci delete wireless.@wifi-iface[%d].maclist", i);
				system(buf);
				if ( operationeMode==OPM_RP && i==1 )
					break;
			}
			system("uci commit");
			//put maclist from MACtable into configuration file
			putMACfilterdata(retval_int, wifi_index, operationeMode);
}			
			
		}
		pclose(pp);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 advset drate                    */
/*                   CLI Command -- wless2 advset regpower                 */
/*                   CLI Command -- wless2 advset txpower                  */
/*                   CLI Command -- wless2 advset rts                      */
/*                   CLI Command -- wless2 advset dist                     */
/*                   CLI Command -- wless2 advset antenna                  */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"advset",	cli_table_advset,	getNextTable,	"Wireless advanced settings",   "", AUTH_ANY,	MODEL_ALL},
//};

//CliEntry cli_table_advset[]= {
//	{OPM_ALL,	"drate",	NULL,			cmddrate,	"Datarate",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"regpower",	NULL,			cmdregpower,	"Obey regulatory power",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"txpower",	NULL,			cmdtxpower,	"Transmit power",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"rts", 		NULL,			cmdrts,		"RTS/CTS threshold",		"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"dist",		NULL,			cmddist,	"Distance",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"antenna",	NULL,			cmdantenna,	"Antenna Selection",		"", AUTH_ADMIN, ENH200_ID},
//	{OPM_ALL,	"aggr", 	cli_table_aggr,		getNextTable,	"Aggregation",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"traffic",	cli_table_traffic,	getNextTable,	"Traffic shaping",		"", AUTH_ADMIN, MODEL_SINGLE},
//	{OPM_ALL,	"help",		cli_table_advset,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",  	NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: displayandcheckvaliddatarate
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 displayandcheckvaliddatarate(T_CHAR* wirelessmode, T_INT32 antenna, T_CHAR* currentDatarate, T_INT32 displayauto, T_INT32 wep_tkip_exist) {
T_INT32 i;
T_INT32 start;
T_INT32 stop;
//Data rate maybe need to be changed
T_INT32 datarate_change=1;

	if (displayauto==1)
		printf("%d - %s\n", CliDatarateTable[0].item, CliDatarateTable[0].datarateName);
	//Data rate doesn't need to be changed if data rate is "auto"
	if (strcmp(currentDatarate,"auto")==0)
		datarate_change = 0;
		
	//Display Data rate from 6M - 54M if wireless mode is A or G only
	if ( strcmp(wirelessmode,"11a_pure")==0 || strcmp(wirelessmode,"11a")==0 || strcmp(wirelessmode,"11g_pure")==0 ){
		start=5;
		stop=12;
		for (i=start; i<=stop; i++){
			printf("%d - %s\n", CliDatarateTable[i].item-4, CliDatarateTable[i].datarateName);
			//Data rate doesn't need to be changed if data rate is in the display list
			if ( strcmp(currentDatarate, CliDatarateTable[i].datarateName)==0 )
				datarate_change = 0;	
		}
	}
	//Display Data rate from 1M - 11M if wireless mode is B only
	if ( strcmp(wirelessmode,"11b")==0 ){
		start=1;
		stop=4;
		for (i=start; i<=stop; i++){
			printf("%d - %s\n", CliDatarateTable[i].item, CliDatarateTable[i].datarateName);
			//check whether currentDatarate is in datarate list or not
			if ( strcmp(currentDatarate, CliDatarateTable[i].datarateName)==0 )
				datarate_change = 0;
		}
	}
	//Display Data rate from 1M - 11M and 6M - 54M if wireless mode is B/G Mixed
	if ( strcmp(wirelessmode,"11g")==0 ){
		start=1;
		stop=12;
		for (i=start; i<=stop; i++){
			printf("%d - %s\n", CliDatarateTable[i].item, CliDatarateTable[i].datarateName);
			//Data rate doesn't need to be changed if data rate is in the display list
			if ( strcmp(currentDatarate, CliDatarateTable[i].datarateName)==0 )
				datarate_change = 0;
		}
	}
	//Display Data rate from MCS0 - MCS7 or MCS15 if wireless mode is N only
	if ( strcmp(wirelessmode,"11n_pure")==0 || strcmp(wirelessmode,"11na_pure")==0 ){
		start=13;
		if (antenna==1)
			stop=20;
		else if (antenna==2)
			stop=28;
		else if (antenna==3)
			stop=36;

		if (wep_tkip_exist==1)
			stop=12;
		
		for (i=start; i<=stop; i++){
			printf("%d - %s\n", CliDatarateTable[i].item-12, CliDatarateTable[i].datarateName);
			//Data rate doesn't need to be changed if data rate is in the display list
			if ( strcmp(currentDatarate, CliDatarateTable[i].datarateName)==0 )
				datarate_change = 0;
		}
	}
	//Display Data rate from 1M - 11M and 6M - 54M and MCS0 - MCS7 or MCS15 if wireless mode is B/G/N Mixed
	if ( strcmp(wirelessmode,"11ng")==0 ){
		start=1;
		if (antenna==1)
			stop=20;
		else if (antenna==2)
			stop=28;
		else if (antenna==3)
			stop=36;

		//if (wep_tkip_exist==1)
		//	stop=12;
		
		for (i=start; i<=stop; i++){
			printf("%d - %s\n", CliDatarateTable[i].item, CliDatarateTable[i].datarateName);
			//Data rate doesn't need to be changed if data rate is in the display list
			if ( strcmp(currentDatarate, CliDatarateTable[i].datarateName)==0 )
				datarate_change = 0;
		}
	}
	//Display Data rate from 6M - 54M and MCS0 - MCS7 or MCS15 if wireless mode is A/N Mixed
	if ( strcmp(wirelessmode,"11na")==0 ){
		start=5;
		if (antenna==1)
			stop=20;
		else if (antenna==2)
			stop=28;
		else if (antenna==3)
			stop=36;
			
		//if (wep_tkip_exist==1)
		//	stop=12;	

		for (i=start; i<=stop; i++){
			printf("%d - %s\n", CliDatarateTable[i].item-4, CliDatarateTable[i].datarateName);
			//Data rate doesn't need to be changed if data rate is in the display list
			if ( strcmp(currentDatarate, CliDatarateTable[i].datarateName)==0 )
				datarate_change = 0;
		}
	}

	//Display Data rate from MCS0 - MCS9 if wireless mode is AC
	if ( strcmp(wirelessmode,"11naac")==0 ){
		start=37;
		stop=46;	

		for (i=start; i<=stop; i++){
			printf("%d - %s\n", CliDatarateTable[i].item-36, CliDatarateTable[i].datarateDisplayName);
			//Data rate doesn't need to be changed if data rate is in the display list
			if ( strcmp(currentDatarate, CliDatarateTable[i].datarateName)==0 )
				datarate_change = 0;
		}
	}

	return datarate_change;

}

/*****************************************************************
* NAME: convertcode2ratetable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_CHAR* convertcode2ratetable(T_CHAR* ratecode) {
int i;
int ratecontrolCount=28;

	for (i=1; i<=ratecontrolCount; i++){
		if ( strcmp(ratecode, CliDatarateTable[i].ratecode)==0 )
			break;			
	}
	return CliDatarateTable[i].datarateName;
}

/*****************************************************************
* NAME: convertcode2itemtable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 convertcode2itemtable(T_CHAR* ratecode) {
int i;
int ratecontrolCount=28;

	for (i=1; i<=ratecontrolCount; i++){
		if ( strcmp(ratecode, CliDatarateTable[i].ratecode)==0 )
			break;			
	}
	return CliDatarateTable[i].item;
}

/*****************************************************************
* NAME: errorcheckDatarate
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 errorcheckDatarate(T_CHAR* wirelessmode, T_INT32 antenna, T_INT32 input, T_INT32 wep_tkip_exist) {

	//Data rate is from 6M - 54M if wireless mode is A or G only
	if ( strcmp(wirelessmode,"11a_pure")==0 || strcmp(wirelessmode,"11g_pure")==0 ){
		return errorcheckIntRange( 0, 8, input);
	}
	//Data rate is from 1M - 11M if wireless mode is B only
	if ( strcmp(wirelessmode,"11b")==0 ){
		return errorcheckIntRange( 0, 4, input);
	}
	//Data rate is from 1M - 11M and 6M - 54M if wireless mode is B/G Mixed
	if ( strcmp(wirelessmode,"11g")==0 ){
		return errorcheckIntRange( 0, 12, input);
	}
	//Data rate is from MCS0 - MCS7 or MCS15 if wireless mode is N only
	if ( strcmp(wirelessmode,"11n_pure")==0 || strcmp(wirelessmode,"11na_pure")==0 ){
		if (antenna==1)
			return errorcheckIntRange( 0, 8, input);
		else if (antenna==2)
			return errorcheckIntRange( 0, 16, input);
		else if (antenna==3)
			return errorcheckIntRange( 0, 24, input);

	}
	//Data rate is from 1M - 11M and 6M - 54M and MCS0 - MCS7 or MCS15 if wireless mode is B/G/N Mixed
	if ( strcmp(wirelessmode,"11ng")==0 ){

//Modify on 2012-11-27 by Philips to check whether the security is wep or tkip	
if (wep_tkip_exist==1)
	return errorcheckIntRange( 0, 12, input);
	
		if (antenna==1)
			return errorcheckIntRange( 0, 20, input);
		else if (antenna==2)
			return errorcheckIntRange( 0, 28, input);		
		else if (antenna==3)
			return errorcheckIntRange( 0, 36, input);		
		
	}
	//Data rate is from 6M - 54M and MCS0 - MCS7 or MCS15 if wireless mode is A/N Mixed
	if ( strcmp(wirelessmode,"11na")==0 ){

//Modify on 2012-11-27 by Philips to check whether the security is wep or tkip
if (wep_tkip_exist==1)
	return errorcheckIntRange( 0, 8, input);

		if (antenna==1)
			return errorcheckIntRange( 0, 16, input);
		else if (antenna==2)
			return errorcheckIntRange( 0, 24, input);
		else if (antenna==3)
			return errorcheckIntRange( 0, 32, input);
			
	}
	
	//Modify on 2013-08-19 by Philips to check whether Data rate is from MCS0 - MCS9 if wireless mode is AC
	if ( strcmp(wirelessmode,"11naac")==0 ){
		return errorcheckIntRange( 0, 10, input);
	}
}

/*****************************************************************
* NAME: displaytxpower
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID displaytxpower(T_INT32 maxpower) {
T_INT32 i;
T_INT32 start;
T_INT32 stop;

//Add on 2013-10-18 by Philips to define MODEL_GREEN for models to support SKU control
//if ( model_ID & MODEL_GREEN )


if ( ( model_ID & MODEL_GREEN ) || ( model_ID & MODEL_OLD_WEB_GREEN ) )
	printf("0 - Auto\n");

	start=11;
	stop=maxpower;
	for (i=start; i<=stop; i++)
		printf("%d - %d (dBm)\n", i-10, i);
}

/*****************************************************************
* NAME: cmddrate
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddrate(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.@wifi-iface[0].rate";
T_CHAR wifiinterface[128]="wireless.wifi0.hwmode";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR wirelessmode[128];
T_INT32 antenna=getHostantenna();
T_INT32 ssidCount;
T_INT32 datarate_change;
T_INT32 i;
T_INT32 set_index;
T_INT32 wifi_index;
T_INT32 operationeMode=current_opmode;

T_INT32 wep_tkip_exist=0;


//Modify for C600 on 2013-04-30 when mesh-only is enabled
if ( strcmp(model_name, "c600")==0 ){
T_CHAR func_buf1[128]="wireless.w0_index23.MESHEnable";

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf1, "wireless.w1_index23.MESHEnable");
	strcpy(uci_get_buf, cli_get_uci(func_buf1));

	
	if ( (strcmp(uci_get_buf, "mesh-only")==0) && (cliData->argc==1) ){
		printf("Data Rate can't be set when mesh-only is enabled.\n");
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
}


	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(wifiinterface, "wireless.wifi1.hwmode");
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);
	
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].rate", wifi_index);

	strcpy(wirelessmode, getWirelessmode(wifiinterface));
	
//Modify on 2012-11-27 by Philips to check whether the security is wep or tkip
wep_tkip_exist = checksecurity_wep_tkip(operationeMode);	

	if(cliData->argc==0){
		//Get the data rate	
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		//display and check whether data rate is valid or not according to the return value "datarate_change"
		datarate_change=displayandcheckvaliddatarate(wirelessmode, antenna, uci_get_buf, 1, wep_tkip_exist);
		
		//change data rate to be "auto" if data rate is invlid
		if (datarate_change==1){
			for (i=wifi_index; i<=wifi_index+ssidCount; i++){
		
				sprintf(func_buf, "wireless.@wifi-iface[%d].rate", i);
				cli_set_uci(func_buf, "auto");
				if ( operationeMode==OPM_CB && i==0 )
					break;
				if ( operationeMode==OPM_RP && i==1 )
					break;
			}
			//Get the changed data rate --- "auto"
			strcpy(uci_get_buf, cli_get_uci(func_buf));
		}
		
		tprintf("Current setting: %s\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckDatarate(wirelessmode, antenna, atoi(cliData->tokens[cliData->tokenLen-1].token), wep_tkip_exist) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		set_index=atoi(uci_set_buf);
		
		//11a_pure, 11a, 11g_pure, 11na start==5
		if ( strcmp(wirelessmode,"11a_pure")==0 || strcmp(wirelessmode,"11a")==0 || strcmp(wirelessmode,"11g_pure")==0 || strcmp(wirelessmode,"11na")==0 )
			set_index+=4;
		//11n_pure, 11na_pure start==13
		if ( strcmp(wirelessmode,"11n_pure")==0 || strcmp(wirelessmode,"11na_pure")==0 )
			set_index+=12;

//Modify on 2013-08-19 by Philips to check whether Data rate is from MCS0 - MCS9 if wireless mode is AC
//AC start==13
if ( strcmp(wirelessmode,"11naac")==0 ){
	set_index+=36;
}
			
		for (i=wifi_index; i<=wifi_index+ssidCount; i++){
		
			sprintf(func_buf, "wireless.@wifi-iface[%d].rate", i);
			cli_set_uci(func_buf, CliDatarateTable[set_index].datarateName);
			if ( operationeMode==OPM_CB && i==0 )
				break;
			if ( operationeMode==OPM_RP && i==1 )
				break;
		}

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdregpower
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdregpower(T_VOID* priv, CliData* cliData)
{
//wifi0 for 2.4G, 5G of Single Radio and 2.4G of Dual Radio
T_CHAR func_buf[128]="wireless.wifi0.obeyregpower";
T_CHAR func_buf1[128]="wireless.wifi0.txpower";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 maxpower;

	//wifi1 for 5G of Dual Radio
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 ){
		strcpy(func_buf, "wireless.wifi1.obeyregpower");
		strcpy(func_buf1, "wireless.wifi1.txpower");
	}

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token) )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}		

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		//cli_set_uci(func_buf, uci_set_buf);


//Add on 2013-11-20 by Philips to define MODEL_OLD_WEB_GREEN for models to support SKU control
if ( model_ID & MODEL_OLD_WEB_GREEN )
	//set the same value into obeyregpower of both wifi0 and wifi1 for Dual Radio
	if ( model_radio==7 ){
		cli_set_uci("wireless.wifi0.obeyregpower", uci_set_buf);
		cli_set_uci("wireless.wifi1.obeyregpower", uci_set_buf);
	}
else
	cli_set_uci(func_buf, uci_set_buf);


//Add on 2013-10-18 by Philips to define MODEL_GREEN for models to support SKU control
//if ( model_ID & MODEL_GREEN )


if ( model_ID & MODEL_GREEN ){
	//if Green power has been selected, set txpower to be 0(Auto)
	if ( atoi(uci_set_buf)==1 )
		cli_set_uci(func_buf1, "0");
}


//Add on 2013-11-20 by Philips to define MODEL_OLD_WEB_GREEN for models to support SKU control	
else if (  model_ID & MODEL_OLD_WEB_GREEN ){
	//if Green power has been selected, set txpower of wifi0 or wifi1 to be 0(Auto) for Single Radio
	if ( atoi(uci_set_buf)==1 ){
		cli_set_uci(func_buf1, "0");
		//if Green power has been selected, set txpower of both wifi0 and wifi1 to be 0(Auto) for Dual Radio
		if ( model_radio==7 ){		
			cli_set_uci("wireless.wifi0.txpower", "0");
			cli_set_uci("wireless.wifi1.txpower", "0");
		}
	}
}
else
{
		
//if currunt txpower is greater than maxpower, set txpower to be maxpower
		strcpy(uci_get_buf, cli_get_uci(func_buf1));
		maxpower=getHosttxpower();
		
		if (atoi(uci_get_buf)>maxpower){
			sprintf(uci_set_buf, "%d", maxpower);
			cli_set_uci(func_buf1, uci_set_buf);
		}

}
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdtxpower
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdtxpower(T_VOID* priv, CliData* cliData)
{
//wifi0 for 2.4G, 5G of Single Radio and 2.4G of Dual Radio
T_CHAR func_buf[128]="wireless.wifi0.txpower";
T_CHAR func_buf1[128]="wireless.wifi0.obeyregpower";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 maxpower;
T_INT32 start=1;

	//wifi1 for 5G of Dual Radio
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.wifi1.txpower");


//Add on 2013-10-18 by Philips to define MODEL_GREEN for models to support SKU control
	//wifi1 for 5G of Dual Radio
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf1, "wireless.wifi1.obeyregpower");


	maxpower=getHosttxpower();
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		displaytxpower(maxpower);

	//the initail value of txpower is 0
	//tprintf("Current setting: %s dBm\n", (atoi(uci_get_buf)==0) ? "11" : uci_get_buf);


//Add on 2013-10-18 by Philips to define MODEL_GREEN for models to support SKU control
//if ( model_ID & MODEL_GREEN ){


if ( ( model_ID & MODEL_GREEN ) || ( model_ID & MODEL_OLD_WEB_GREEN ) ){
	if (atoi(uci_get_buf)==0)
		tprintf("Current setting: %s\n", "Auto");
	else
		tprintf("Current setting: %s dBm\n", uci_get_buf);
}
else
	//the initail value of txpower is 0
	tprintf("Current setting: %s dBm\n", (atoi(uci_get_buf)==0) ? "11" : uci_get_buf);
				
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){


//Add on 2013-10-18 by Philips to define MODEL_GREEN for models to support SKU control
//if ( model_ID & MODEL_GREEN ){


if ( ( model_ID & MODEL_GREEN ) || ( model_ID & MODEL_OLD_WEB_GREEN ) ){
	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	//Green Power has been selected
	if (atoi(uci_get_buf)==1){
		printf(" Green power is enabled, please disable it first!\n");
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
}

		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		//if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, maxpower-10, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){


//Add on 2013-10-18 by Philips to define MODEL_GREEN for models to support SKU control
//if ( model_ID & MODEL_GREEN )


if ( ( model_ID & MODEL_GREEN ) || ( model_ID & MODEL_OLD_WEB_GREEN ) )
	start=0;
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( start, maxpower-10, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
		
		
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		//sprintf(uci_set_buf, "%d", atoi(uci_set_buf)+10);


//Add on 2013-10-18 by Philips to define MODEL_GREEN for models to support SKU control
//if ( model_ID & MODEL_GREEN )


if ( ( model_ID & MODEL_GREEN ) || ( model_ID & MODEL_OLD_WEB_GREEN ) )
	sprintf(uci_set_buf, "%d", (atoi(uci_set_buf)==0) ? 0 : atoi(uci_set_buf)+10);
else
	sprintf(uci_set_buf, "%d", atoi(uci_set_buf)+10);


		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdrts
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdrts(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.@wifi-iface[0].rts";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 ssidCount;
T_INT32 i;
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
T_INT32 nawds_index=0;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);

	if (operationeMode==OPM_WDSAP)
		//get 4 (if ssidcount is 4) or 16 (if ssidcount is 8) for single-radio and 16 (if radio is 2.4G) or 42 (if radio is 5G) for dual-radio
		//nawds_index=get_nawds_index(ssidCount);

		//Modify on 2013-08-07 by Philips to get the correct nawds_index
		nawds_index=get_nawds_index(ssidCount, operationeMode);

	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	sprintf(func_buf, "wireless.@wifi-iface[%d].rts", wifi_index);
//printf("operationeMode=%d_wifi_index=%d_nawds_index=%d\n", operationeMode, wifi_index, nawds_index);
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s bytes (1-2346)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 2346, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
	
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		if (operationeMode==OPM_CB || operationeMode==OPM_WDSB || operationeMode==OPM_WDSSTA || operationeMode==OPM_CBRT){
			sprintf(func_buf, "wireless.@wifi-iface[%d].rts", wifi_index);
			cli_set_uci(func_buf, uci_set_buf);
		}
		if (operationeMode==OPM_AP || operationeMode==OPM_WDSAP || operationeMode==OPM_AR){
			
			for (i=wifi_index; i<=wifi_index+ssidCount; i++){
		
				sprintf(func_buf, "wireless.@wifi-iface[%d].rts", i);
				cli_set_uci(func_buf, uci_set_buf);
				if ( operationeMode==OPM_CB && i==0 )
					break;
				if ( operationeMode==OPM_RP && i==1 )
					break;
			}
		}
		if (operationeMode==OPM_RP){
			sprintf(func_buf, "wireless.@wifi-iface[%d].rts", wifi_index);
			cli_set_uci(func_buf, uci_set_buf);
			sprintf(func_buf, "wireless.@wifi-iface[%d].rts", wifi_index+1);
			cli_set_uci(func_buf, uci_set_buf);
		}
		//set rts in nawds interface
		if (operationeMode==OPM_WDSAP){
			sprintf(func_buf, "wireless.@wifi-iface[%d].rts", nawds_index);
			cli_set_uci(func_buf, uci_set_buf);
		}
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmddist
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddist(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.wifi0.distance";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR distance[128];

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.wifi1.distance");

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %d km (1-30)\n", atoi(uci_get_buf)/1000);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 30, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		sprintf(distance, "%d", atoi(uci_set_buf)*1000);
		cli_set_uci(func_buf, distance);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdantenna
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdantenna(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.wifi0.WLANAntSwitch";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Horizontal, 0:Vertical)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 advset aggr                     */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"advset",	cli_table_advset,	getNextTable,	"Wireless advanced settings",   "", AUTH_ANY,	MODEL_ALL},
//};

//CliEntry cli_table_advset[]= {
//	{OPM_ALL,	"aggr", 	cli_table_aggr,		getNextTable,	"Aggregation",			"", AUTH_ADMIN, MODEL_ALL},
//};

//CliEntry cli_table_aggr[]= {
//	{OPM_ALL,	"aggract",	NULL,    	cmdaggract,	"Aggregation active",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"fram",		NULL,		cmdfram,	"Frames",		"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"byte",    	NULL,		cmdbyte,	"Bytes(Max)",		"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_aggr,	cmdHelp,    	"Help",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,		cmdexit,    	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdaggract
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdaggract(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.wifi0.WLANAggreEnable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.wifi1.WLANAggreEnable");

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdfram
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdfram(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.wifi0.WLANAggreFrames";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.wifi1.WLANAggreFrames");

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s Frames (1-32)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 32, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdbyte
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdbyte(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.wifi0.WLANAggreBytes";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.wifi1.WLANAggreBytes");

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s Max_Bytes (2304-65535)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 2304, 65535, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 advset traffic                  */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"advset",	cli_table_advset,	getNextTable,	"Wireless advanced settings",   "", AUTH_ANY,	MODEL_ALL},
//};

//CliEntry cli_table_advset[]= {
//	{OPM_ALL,	"traffic",	cli_table_traffic,	getNextTable,	"Traffic shaping",		"", AUTH_ADMIN, MODEL_SINGLE},
//};

//CliEntry cli_table_traffic[]= {
//	{OPM_ALL,	"tsact",	NULL,    		cmdtsact,      	"Traffic Shaping active",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"inlimit",	NULL,        		cmdinlimit,	"Incoming traffic limit",	"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"outlimit",	NULL,			cmdoutlimit,	"Outgoing traffic limit",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_traffic,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdtsact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdtsact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="tc.1.TcEnable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdinlimit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdinlimit(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="tc.1.TcInRate";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	//Get the information of "traffic shaping enable"
	strcpy(uci_get_buf, cli_get_uci("tc.1.TcEnable"));

	//If traffic shaping is disabled, please enable traffic shaping first
	if( atoi(uci_get_buf) == 0 ){
		printf("Traffic Shaping is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s kbit/s (512-99999999)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 512, 99999999, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdoutlimit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdoutlimit(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="tc.1.TcOutRate";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	//Get the information of "traffic shaping enable"
	strcpy(uci_get_buf, cli_get_uci("tc.1.TcEnable"));

	//If traffic shaping is disabled, please enable traffic shaping first
	if( atoi(uci_get_buf) == 0 ){
		printf("Traffic Shaping is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "tc.wifi0.TcOutRate");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "tc.wifi1.TcOutRate");

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s kbit/s (512-99999999)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
		
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token)){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}/*the input is not numberic*/
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 512, 99999999, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*              CLI Command -- wless2 advset traffic tsratio               */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,   	"advset",	cli_table_advset,	getNextTable,	"Wireless advanced settings",   "", AUTH_ANY,	MODEL_ALL},
//};

//CliEntry cli_table_advset[]= {
//	{OPM_ALL,	"traffic",	cli_table_traffic,	getNextTable,	"Traffic shaping",		"", AUTH_ADMIN, MODEL_SINGLE},
//};

//CliEntry cli_table_traffic[]= {
//	{OPM_ALL,	"wdsratio",	NULL,			cmdwdsratio,	"WDS rate ratio",	"",	AUTH_ADMIN,	MODEL_SINGLE},
//	{OPM_ALL,	"ssidratio",    NULL,        		cmdssidratio,	"SSID rate ratio",	"",	AUTH_ANY,	MODEL_SINGLE},
//};

/*****************************************************************
* NAME: setRateRatio
* ---------------------------------------------------------------
* FUNCTION: Set the rate ratio of SSID or WDS for TC per SSID of function alignment
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-20 for TC per SSID in AP, WDSAP and WDSB mode
* Modify:   
****************************************************************/
T_VOID setRateRatio(T_CHAR* wireless_type, T_CHAR* no, T_CHAR* ratio){
T_CHAR func_buf[128]="tc.1.TcOutRateRatio";
T_CHAR uci_get_buf[128];
T_CHAR ratio_buf[128];
T_CHAR wds_ratio_buf[128];
//T_CHAR ratio_write[8];
T_CHAR uci_set_buf[128];
T_CHAR* token;
T_INT32 length=0;
T_INT32 i;
T_INT32 wds_length=1;
T_INT32 ssid_length=0;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "tc.wifi0.TcOutRateRatio");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "tc.wifi1.TcOutRateRatio");
		
	//Set uci_set_buf to be NULL string
	strcpy(uci_set_buf , "");
	//Keep tc.1.TcOutRateRatio=5/5/5/5/5/5/5/5,10,10,10,10,20,30,40,50 in the "ratio_buf"
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	strcpy(ratio_buf, uci_get_buf);
	
	//Find the number of WDS and SSID ratio number EX. WDS is 4 and SSID is 8 for "5/5/5/5,10,10,10,10,20,30,40,50"
	for (i=0; i<=strlen(ratio_buf); i++){
		if ( ratio_buf[i]=='/' )
			wds_length++;
		if ( ratio_buf[i]==',' )
			ssid_length++;
	}

//printf("func_buf=%s, ratio_buf=%s, wds_length=%d, ssid_length=%d\n", func_buf, ratio_buf, wds_length, ssid_length);

	//Set the WDS Ratio for CLI command --- mgmt traffic ratio2 wdsr2 3 75
	if ( strcmp(wireless_type, "wds")==0 ){
		//Get the length of first part of tc.1.TcOutRateRatio  Ex. <<5/>>5/5/5/5/5/5/5,10,10,10,10,20,30,40,50
		//Write the first part of tc.1.TcOutRateRatio into uci_set_buf
		token = strtok(uci_get_buf, "/");
		if ( atoi(no)==1 )
			strcat(uci_set_buf, ratio);
		else
			strcat(uci_set_buf, token);
		strcat(uci_set_buf , "/");
		length+=(strlen(token)+1);
				
		if ( atoi(no)>1 ) {	
			for (i=2; i<atoi(no); i++){
				//Get the length of middel part of tc.1.TcOutRateRatio Ex. 5/<<5/5/5/5>>/5/5/5,10,10,10,10,20,30,40,50
				token = strtok(NULL, "/");
				length+=(strlen(token)+1);
				//Write the middle part of tc.1.TcOutRateRatio into uci_set_buf
				strcat(uci_set_buf , token);
				strcat(uci_set_buf , "/");				
			}
			//Write the user-specific of tc.1.TcOutRateRatio into uci_set_buf
			strcat(uci_set_buf , ratio);
			//Get the length of user-specific part of tc.1.TcOutRateRatio Ex. 5/5/5/5/5<</5>>/5/5,10,10,10,10,20,30,40,50
			if ( atoi(no)==wds_length ){
				token = strtok(NULL, ",");
				strcat(uci_set_buf , ",");
			}
			else{
				token = strtok(NULL, "/");
				strcat(uci_set_buf , "/");
			}
			length+=(strlen(token)+1);				
		}
		//Write the last part of tc.1.TcOutRateRatio into uci_set_buf
		strcat(uci_set_buf , ratio_buf+length);		
	}
	
	//Set the SSID Ratio for CLI command --- mgmt traffic ratio2 ssidr2 3 75
	if ( strcmp(wireless_type, "ssid")==0 ){
		//Get the length of first part of tc.1.TcOutRateRatio Ex. <<5/5/5/5/5/5/5/5,10,10,10>>,10,20,30,40,50
		token = strtok(uci_get_buf, ",");
		length+=(strlen(token)+1);
		for (i=1; i<atoi(no); i++){
			token = strtok(NULL, ",");
			length+=(strlen(token)+1);	
		}
		//Write the last part of tc.1.TcOutRateRatio into uci_set_buf
		strncpy(uci_set_buf, ratio_buf, length);
		uci_set_buf[length]='\0';
		
		//Write the user-specific of tc.1.TcOutRateRatio into uci_set_buf
		strcat(uci_set_buf , ratio);
		
		if ( atoi(no)!=ssid_length ){
			strcat(uci_set_buf , ",");
			//Get the length of user-specific part of tc.1.TcOutRateRatio Ex. 5/5/5/5/5<</5>>/5/5,10,10,10,10,20,30,40,50	
			token = strtok(NULL, ",");
			length+=(strlen(token)+1);
			//Write the tail part of tc.1.TcOutRateRatio inot uci_set_buf
			strcat(uci_set_buf , ratio_buf+length);
		}
	}	
	cli_set_uci(func_buf, uci_set_buf);
}

/*****************************************************************
* NAME: cmdwdsratio
* ---------------------------------------------------------------
* FUNCTION: Display the rate ratio of WDS for TC per SSID of function alignment
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-20 for TC per SSID in AP, WDSAP and WDSB mode
* Modify:   
****************************************************************/
CliStatus cmdwdsratio(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="tc.1.TcOutRateRatio";
T_CHAR func_buf1[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_set_buf_No[128];
T_CHAR uci_set_buf_Ratio[128];

T_CHAR wds_ratio[64];
T_INT32 i;
T_INT32 count;
T_INT32 ssidCount;
T_INT32 wdslinkCount;
T_INT32 operationeMode=current_opmode;
T_INT32 nawds_index;
T_CHAR buf[128];
T_CHAR enable[12];	
T_CHAR* token;

T_CHAR ratio_buf[128];
T_INT32 wds_length=1;
T_CHAR uci_set_buf[128];
T_INT32 length=0;

	//Get the information of "traffic shaping enable"
	strcpy(uci_get_buf, cli_get_uci("tc.1.TcEnable"));

	//If traffic shaping is disabled, please enable traffic shaping first
	if( atoi(uci_get_buf) == 0 ){
		printf("Traffic Shaping is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

strcpy(ratio_buf, cli_get_uci(func_buf));	
//Find the count of WDS ratio number EX. WDS is 4 for "5/5/5/5,10,10,10,10,20,30,40,50"
for (i=0; i<=strlen(ratio_buf); i++)
	if ( ratio_buf[i]=='/' )
		wds_length++;
//If the count of WDS ratio is 4, extends the count fromm 4 to 8	
if ( wds_length==4 ){
	token = strtok(ratio_buf, ",");
	strcat(uci_set_buf, token);
	length+=(strlen(token)+1);
	strcat(uci_set_buf , "/5/5/5/5,");
	strcat(uci_set_buf , ratio_buf+length);
	cli_set_uci(func_buf, uci_set_buf);
}

	//Get wds count information
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "tc.wifi0.TcOutRateRatio");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "tc.wifi1.TcOutRateRatio");

	ssidCount=getModelssidCount(operationeMode);
	wdslinkCount = getModelwdslinkCount(operationeMode);
	
	//get 4 (if ssidcount is 4) or 16 (if ssidcount is 8) for single-radio and 16 (if radio is 2.4G) or 42 (if radio is 5G) for dual-radio
	//nawds_index=get_nawds_index(ssidCount);

	//Modify on 2013-08-07 by Philips to get the correct nawds_index
	nawds_index=get_nawds_index(ssidCount, operationeMode);
		
	if(cliData->argc==0){
		tprintf("Current setting: \n");	
		//Get WDS ratio information
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		token = strtok(uci_get_buf, ",");
		strcpy(wds_ratio, token);
		
		//Get WDS link information
		sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANWDSPeer", nawds_index);
		strcpy(uci_get_buf1, cli_get_uci(func_buf1));
		count=strlen(uci_get_buf1)/13;
		
		//Display WDS ratio			
		for (i=1; i<=wdslinkCount; i++){
			strcpy(enable, "Disable");
			if ( i<=count )
				if ( uci_get_buf+((i)*13-1)=='v' )
					strcpy(enable, "Enable");
			if ( i==1 )
				token = strtok(wds_ratio, "/");
			else
				token = strtok(NULL, "/");
    			tprintf(" WDS #%d : %2s %% --- %s\n", i, token, enable);
		}

		tprintf("Recognized input format:  a pair of \"WDS_No\" and \"Rate_Ratio\"    EX: 1 15\n");
		tprintf("The range of \"WDS_No\" is from 1 to %d\n", wdslinkCount);
		tprintf("The range of \"Rate_Ratio\" is from 0 to 100\n");
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, wdslinkCount, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			tprintf("The range of \"WDS_No\" is from 1 to %d\n", wdslinkCount);
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		tprintf("You forget to set Rate_Ratio\n");
		cliData->tokenLen-=2;
		return CLI_PARAMS_ERR;
	}
	else if(cliData->argc==2){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-2].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-2].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-2].token, "%d", atoi(cliData->tokens[cliData->tokenLen-2].token) );
			
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-2].token) || !errorcheckIntRange( 1, wdslinkCount, atoi(cliData->tokens[cliData->tokenLen-2].token)) ){
			tprintf("The range of \"WDS_No\" is from 1 to %d\n", wdslinkCount);
			cliData->tokenLen-=3;
	  		return CLI_PARAMS_ERR;
		}
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 100, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			tprintf("The range of \"Rate_Ratio\" is from 0 to 100\n");
			cliData->tokenLen-=3;
	  		return CLI_PARAMS_ERR;
		}
		//Get the WDS_no
		strcpy(uci_set_buf_No, cliData->tokens[cliData->tokenLen-2].token);
		//Get the Rate_Ratio
		strcpy(uci_set_buf_Ratio, cliData->tokens[cliData->tokenLen-1].token);
		setRateRatio("wds", uci_set_buf_No, uci_set_buf_Ratio);
		
		cliData->tokenLen-=3;
		return CLI_NOTHING;
	}
	else if(cliData->argc>2){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdssidratio
* ---------------------------------------------------------------
* FUNCTION: Display the rate ratio of SSID for TC per SSID of function alignment
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-20 for TC per SSID in AP, WDSAP and WDSB mode
* Modify:   
****************************************************************/
CliStatus cmdssidratio(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="tc.1.TcOutRateRatio";
T_CHAR func_buf1[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_set_buf_No[128];
T_CHAR uci_set_buf_Ratio[128];

T_INT32 i;
T_INT32 ssidCount;
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
T_CHAR* token;
	
	//Get the information of "traffic shaping enable"
	strcpy(uci_get_buf, cli_get_uci("tc.1.TcEnable"));

	//If traffic shaping is disabled, please enable traffic shaping first
	if( atoi(uci_get_buf) == 0 ){
		printf("Traffic Shaping is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}
	
	//Get ssid count information
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		strcpy(func_buf, "tc.wifi0.TcOutRateRatio");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "tc.wifi1.TcOutRateRatio");
	
	ssidCount=getModelssidCount(operationeMode);
	
	//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
	wifi_index=get_wifi_iface(operationeMode);
	
	if(cliData->argc==0){
		tprintf("Current setting: \n");	
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		token = strtok(uci_get_buf, ",");
//Display SSID ratio
if ( operationeMode==OPM_AP || operationeMode==OPM_WDSAP){
	for (i=wifi_index; i<wifi_index+ssidCount; i++){
		sprintf(func_buf1, "wireless.@wifi-iface[%d].WLANEnable", i);
		strcpy(uci_get_buf1, cli_get_uci(func_buf1));
		
		token = strtok(NULL, ",");
	
		if ( atoi(uci_get_buf1)==0 ){
			strcpy(uci_get_buf1, "N/A");
		}
		else{
			sprintf(func_buf1, "wireless.@wifi-iface[%d].ssid", i);
			strcpy(uci_get_buf1, cli_get_uci(func_buf1));
		}
		tprintf("SSID #%d : %2s %% --- %s\n", i+1, token, uci_get_buf1);	
	}
}

		tprintf("Recognized input format:  a pair of \"SSID_No\" and \"Rate_Ratio\"    EX: 1 15\n");
		tprintf("The range of \"SSID_No\" is from 1 to %d\n", ssidCount);
		tprintf("The range of \"Rate_Ratio\" is from 0 to 100\n");
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, ssidCount, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		tprintf("You forget to set Rate_Ratio\n");
		cliData->tokenLen-=2;
		return CLI_PARAMS_ERR;
	}
	else if(cliData->argc==2){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-2].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-2].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-2].token, "%d", atoi(cliData->tokens[cliData->tokenLen-2].token) );
			
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-2].token) || !errorcheckIntRange( 1, ssidCount, atoi(cliData->tokens[cliData->tokenLen-2].token)) ){
			tprintf("The range of \"SSID_No\" is from 1 to %d\n", ssidCount);
			cliData->tokenLen-=3;
	  		return CLI_PARAMS_ERR;
		}
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 100, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			tprintf("The range of \"Rate_Ratio\" is from 0 to 100\n");
			cliData->tokenLen-=3;
	  		return CLI_PARAMS_ERR;
		}
		//Get the WDS_no
		strcpy(uci_set_buf_No, cliData->tokens[cliData->tokenLen-2].token);
		//Get the Rate_Ratio
		strcpy(uci_set_buf_Ratio, cliData->tokens[cliData->tokenLen-1].token);
		setRateRatio("ssid", uci_set_buf_No, uci_set_buf_Ratio);
		
		cliData->tokenLen-=3;
		return CLI_NOTHING;
	}
	else if(cliData->argc>2){
		return CLI_NO_MATCH;
	}
}


/*-------------------------------------------------------------------------*/
/*                   CLI Command -- wless2 fhandover traffic               */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_wless[]= {
//	{OPM_ALL,		"fhandover",	cli_table_fasthandover,	getNextTable,	"Fast handover",		"", AUTH_ADMIN, EAP900_ID},
//};

//Add on 2013-06-06 by Philips to support Fast Handover for eap900 which is requested by Jacy
//static CliEntry cli_table_fasthandover[]= {
//	{OPM_ALL,	"fhact",	NULL,				cmdfhact,	"Fast handover active",	"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"fhrssi",	NULL, 	   			cmdfhrssi,	"Fast handover rssi",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_fasthandover,		cmdHelp,	"Help",			"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,				cmdexit,	"Exit",			"",	AUTH_ADMIN, MODEL_ALL},

//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdfhact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdfhact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="fasthandover.fasthandover.Enable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdfhrssi
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdfhrssi(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="fasthandover.fasthandover.RSSI";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];


	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (-60 ~ -90)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( -90, -60, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

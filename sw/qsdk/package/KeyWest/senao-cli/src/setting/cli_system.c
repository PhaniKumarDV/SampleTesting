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
;    File    : cli_system.c
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
#include <sap_osapi.h>
#include <sap_ostypes.h>
#include <gconfig.h>
#include <tokens.h>
#include <apcfg.h>
#include <cli.h>
#include <cli_system.h>
#include <netDevInfo.h>
#include <appsver.h>
#include <knlappsver.h>
#include <knlver.h>
#include <sysWlan.h>
#include <systime.h>
#include <schedule.h>
#include <syscore.h> //SYSTEM
#include <system.h>
#include <usergrp.h>
#include <string.h>
#include <systeminfo.h>
#include <sysFile.h>
#include <sysUtilMisc.h>
#include <sysProduct.h>
#include <sysFile.h>
#include <cli_wlan.h>
#include <sysMii.h>
#include <regx.h>
#include <sys/sysinfo.h>
#include "../sysconfig/setting/include/schedulesetting.h"

#include <uci.h>


/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/

#define SYS_SCH_DESCRIP  " Idx |       Description      |  Schedule \n"
#define SYS_SCH_PATTERN  "  %d  |%24s| %s\n"
#define WLAN_APPROFILE_DESCRIP  "   Idx |        SSID        |           MAC           |  Authentication  | Encryption | Priority \n"

//#define outOfcountryRange "134"


//Add on 2013-10-21 by Philips to support SKU control for all models
//#define outOfcountryRangeETSI "46"


typedef struct __CliOperationModeEntry{
    const T_INT32 item;
    const T_CHAR* operationmode;
    const T_CHAR* operationmodeName;
}CliOperationModeEntry;

CliOperationModeEntry CliOperationModeTable[] = {
	{1, "ap", "Access Point"},
	{2, "sta", "Client Bridge"},
	{3, "apwds", "WDS Access Point"},
	{4, "br", "WDS Bridge"},
	{5, "stawds", "WDS Station"},
	{6, "apr", "Access Point Router"},
	{7, "cr", "Client Router"},
	{8, "rp", "Repeater"}
};


typedef struct __CliCountryEntry{
    const T_CHAR* item;	
    const T_CHAR* countryName;
    const T_CHAR* countryCode;
    const T_INT32 htmodeAllow; // 0: 20/40=N/N, 2: 20/40=Y/N, 3: 20/40=Y/Y
}CliCountryEntry;

CliCountryEntry CliCountryTable[] = {

	{"0", "N/A"	,	"0", 3},
	{"1", "Albania",	"8", 0},
	{"2", "Algeria",	"12", 0},
	{"3", "Argentina",	"32", 3},
	{"4", "Armenia",	"51", 2},
	{"5", "Australia",	"36", 3},
	{"6", "Austria",	"40", 3},
	{"7", "Azerbaijan",	"31", 3},
 
	{"8", "Bahrain",	"48", 2},
	{"9", "Belarus",	"112", 3},
	{"10", "Belgium",	"56", 3},
	{"11", "Belize",	"84", 3},
	{"12", "Bolivia",	"68", 3},
	{"13", "Bosnia and Herzegovina",	"70", 3},
	{"14", "Brazil",	"76", 3},
	{"15", "Brunei Darussalam",	"96", 3},
	{"16", "Bulgaria",	"100", 3},
  
	{"17", "Canada",	"124", 3},
	{"18", "Chile",	"152", 3},
	{"19", "People's Republic of China",	"156", 3},
	{"20", "Colombia",	"170", 3},
	{"21", "Compliance Band",	"827", 3},
	{"22", "Compliance Band 2",	"828", 3},
	{"23", "Costa Rica",	"188", 2},
	{"24", "Croatia",	"191", 3},
	{"25", "Cyprus",	"196", 3},
	{"26", "Czech Republic",	"203", 3},
        
	{"27", "Denmark",	"208", 3},
	{"28", "Dominican Republic",	"214", 3},
        
 	{"29", "Ecuador",	"218", 2},
	{"30", "Egypt",	"818", 2},
	{"31", "El Salvador",	"222", 2},
	{"32", "Estonia",	"233", 3},
        
	{"33", "Finland",	"246", 3},
	{"34", "France",	"250", 3},
        
  	{"35", "Georgia",	"268", 3},
	{"36", "Germany",	"276", 3},
	{"37", "Greece",	"300", 3},
	{"38", "Guatemala",	"320", 3},
        
	{"39", "Honduras",	"340", 3},
	{"40", "Hong Kong S.A.R., P.R.C.",	"344", 3},
	{"41", "Hungary",	"348", 3},
        
  	{"42", "Iceland",	"352", 3},
	{"43", "India",		"356", 3},
	{"44", "Indonesia",	"360", 2},
	{"45", "Iran",	"364", 3},
	{"46", "Ireland",	"372", 3},
	{"47", "Israel",	"376", 2},
	{"48", "Italy",		"380", 3},
         
	{"49", "Japan",		"392", 3},
	{"50", "Japan (JP1)",	"393", 3},
	{"51", "Japan (JP0)",	"394", 3},
	{"52", "Japan (JP1-1)",	"395", 3},
	{"53", "Japan (JE1)",	"396", 3},
	{"54", "Japan (JE2)",	"397", 3},
	{"55", "Japan (JP6)",	"399", 3},
	{"56", "Japan (J7)",	"4007", 3},
	{"57", "Japan (J8)",	"4008", 3},              
	{"58", "Japan (J9)",	"4009", 3},
	{"59", "Japan (J10)",	"4010", 3},		
	{"60", "Japan (J11)",	"4011", 3},		
	{"61", "Japan (J12)",	"4012", 3},		
	{"62", "Japan (J13)",	"4013", 3},
	{"63", "Japan (J14)",	"4014", 3},              
	{"64", "Japan (J15)",	"4015", 3},
	{"65", "Japan (J16)",	"4016", 3},		
	{"66", "Japan (J17)",	"4017", 3},		
	{"67", "Japan (J18)",	"4018", 3},	
	{"68", "Japan (J19)",	"4019", 3},
	{"69", "Japan (J20)",	"4020", 3},              
	{"70", "Japan (J21)",	"4021", 3},
	{"71", "Japan (J22)",	"4022", 3},		
	{"72", "Japan (J23)",	"4023", 3},		
	{"73", "Japan (J24)",	"4024", 3},	
	{"74", "Jordan",	"400", 3},

	{"75", "Kazakhstan",	"398", 0},
	{"76", "Kenya",	"404", 3},		
	{"77", "North Korea",	"408", 2},		
	{"78", "South Korea",	"410", 3},
	
	{"79", "South Korea",	"412", 2},

	{"80", "Kuwait",	"414", 3},	

	{"81", "Latvia",	"428", 3},
	{"82", "Lebanon",	"422", 3},		
	{"83", "Liechtenstein",	"438", 3},		
	{"84", "Lithuania",	"440", 3},	
	{"85", "Luxembourg",	"442", 3},

	{"86", "Macau",	"446", 3},
	{"87", "The Former Yugoslav Republic of Macedonia",	"807", 3},		
	{"88", "Malaysia",	"458", 3},		
	{"89", "Malta",	"470", 3},	
	{"90", "Mexico",	"484", 3},
	{"91", "Principality of Monaco",	"492", 3},		
	{"92", "Morocco",	"504", 3},	

	{"93", "Netherlands",	"528", 3},
	{"94", "New Zealand",	"554", 2},		
	{"95", "Norway",	"578", 3},	
	{"96", "Oman",	"512", 3},

	{"97", "Islamic Republic of Pakistan",	"586", 3},
	{"98", "Panama",	"591", 3},		
	{"99", "Peru",	"604", 3},	
	{"100", "Republic of the Philippines",	"608", 3},
	{"101", "Poland",	"616", 3},
	{"102", "Portugal",	"620", 3},		
	{"103", "Puerto Rico",	"630", 3},	
	{"104", "Qatar",	"634", 3},
	{"105", "Romania",	"642", 3},		
	{"106", "Russia",	"643", 2},

	{"107", "Saudi Arabia",	"682", 2},
	{"108", "Singapore",	"702", 3},		
	{"109", "Slovak Republic",	"703", 3},	
	{"110", "Slovenia",	"705", 3},
	{"111", "South Africa",	"710", 3},		
	{"112", "Spain",	"724", 3},
	{"113", "Sri Lanka",	"144", 2},	
	{"114", "Sweden",	"752", 3},
	{"115", "Switzerland",	"756", 3},		
	{"116", "Syria",	"760", 0},

	{"117", "Taiwan",	"158", 3},
	{"118", "Thailand",	"764", 3},		
	{"119", "Trinidad and Tobago",	"780", 3},
	{"120", "Tunisia",	"788", 2},
	{"121", "Turkey",	"792", 2},

	{"122", "U.A.E.",	"784", 3},
	{"123", "Ukraine",	"804", 3},		
	{"124", "United Kingdom",	"826", 3},

//Jacy asks the following two items only for 5G not for 2.4G on 2012-10-17	
	{"125", "United Kingdom Band B",	"829", 3},
	{"126", "United Kingdom Band C",	"830", 3},
			
	{"127", "United States",	"840", 3},
	{"128", "Uruguay",	"858", 3},
	{"129", "Uzbekistan",	"860", 3},

	{"130", "Venezuela",	"862", 3},
	{"131", "Vietnam",	"704", 3},
	{"132", "Yemen",	"887", 0},
	{"133", "Zimbabwe",	"716", 3}

};


//const int countrycount=134;
//Add on 2013-11-19 by Philips to calculate the number of countries in the country list for all models
const int countrycount=sizeof(CliCountryTable)/sizeof(CliCountryEntry);
T_CHAR outOfcountryRange[8];


CliCountryEntry CliCountryTableETSI[] = {

	{"0", "N/A"	,	"0", 3},
	{"1", "Albania",	"8", 0},
	{"2", "Armenia",	"51", 2},
	{"3", "Austria",	"40", 3},
	{"4", "Azerbaijan",	"31", 3},
	{"5", "Belarus",	"112", 3},
	{"8", "Belgium",	"56", 3},
	{"7", "Bosnia and Herzegovina",	"70", 3},
	{"8", "Bulgaria",	"100", 3},
	{"9", "Croatia",	"191", 3},
	{"10", "Cyprus",	"196", 3},
	{"11", "Czech Republic",	"203", 3},
	{"12", "Denmark",	"208", 3},
	{"13", "Estonia",	"233", 3},
	{"14", "Finland",	"246", 3},
	{"15", "France",	"250", 3},
  	{"16", "Georgia",	"268", 3},
	{"17", "Germany",	"276", 3},
	{"18", "Greece",	"300", 3},
	{"19", "Hungary",	"348", 3},
  	{"20", "Iceland",	"352", 3},
	{"21", "Ireland",	"372", 3},
	{"22", "Italy",		"380", 3},

	
//Add on 2013-11-19 by Philips to insert "Kazakhstan" into the country list in ETSI sku for all models	
	{"23", "Kazakhstan",	"398", 0},

	
	{"24", "Latvia",	"428", 3},		
	{"25", "Liechtenstein",	"438", 3},		
	{"26", "Lithuania",	"440", 3},	
	{"27", "Luxembourg",	"442", 3},
	{"28", "The Former Yugoslav Republic of Macedonia",	"807", 3},				
	{"29", "Malta",	"470", 3},
	{"30", "Principality of Monaco",	"492", 3},
	{"31", "Netherlands",	"528", 3},		
	{"32", "Norway",	"578", 3},	
	{"33", "Poland",	"616", 3},
	{"34", "Portugal",	"620", 3},		
	{"35", "Romania",	"642", 3},		
	{"36", "Russia",	"643", 2},	
	{"37", "Slovenia",	"705", 3},	
	{"38", "Spain",	"724", 3},	
	{"39", "Sweden",	"752", 3},
	{"40", "Switzerland",	"756", 3},		
	{"41", "Turkey",	"792", 2},
	{"42", "Ukraine",	"804", 3},		
	{"43", "United Kingdom",	"826", 3},
	{"44", "United Kingdom Band B",	"829", 3},
	{"45", "United Kingdom Band C",	"830", 3},


};


//Add on 2013-10-21 by Philips to support SKU control for all models
//const int countrycountETSI=46;
//Add on 2013-11-19 by Philips to calculate the number of countries in the country list for all models
const int countrycountETSI=sizeof(CliCountryTableETSI)/sizeof(CliCountryEntry);
T_CHAR outOfcountryRangeETSI[8];


typedef struct __ClilanipsetEntry{	
	T_INT32 ipset;		//use to decide whether get data from Config file or Clilanipset
	T_INT32 gatewayset;	//use to decide whether get data from Config file or Clilanipset
	T_INT32 maskset;	//use to decide whether get data from Config file or Clilanipset
	T_INT32 pdnsset;	//use to decide whether get data from Config file or Clilanipset
	T_INT32 sdnsset;	//use to decide whether get data from Config file or Clilanipset	
			
	T_CHAR ip[16];
	T_CHAR gateway[16];
	T_CHAR subnetmask[16];		
	T_CHAR pdns[16];
	T_CHAR sdns[16];

	//Modify on 2012-10-26 to add IPV6 fields
	T_INT32 link6set;	//use to decide whether get data from Config file or Clilanipset	
	T_INT32 ipv6set;	//use to decide whether get data from Config file or Clilanipset
	T_INT32 sublen6set;	//use to decide whether get data from Config file or Clilanipset	
	T_INT32 gatewayv6set;	//use to decide whether get data from Config file or Clilanipset
	T_INT32 pdnsv6set;	//use to decide whether get data from Config file or Clilanipset
	T_INT32 sdnsv6set;	//use to decide whether get data from Config file or Clilanipset
		
	T_CHAR link6[50];
	T_CHAR ipv6[50];
	T_CHAR gatewayv6[50];	
	T_CHAR pdnsv6[50];
	T_CHAR sdnsv6[50];
	
			
}ClilanipsetEntry;

ClilanipsetEntry Clilanipset={0, 0, 0, 0, 0, "", "", "", "", "", 0, 0, 0, 0, 0, 0, "", "", "", "", ""};

/*-------------------------------------------------------------------------*/
/*                           Parameter                                     */
/*-------------------------------------------------------------------------*/

extern ScheduleDayMaskEntry dayMask[];
extern T_INT32 g_term_width; 
#if HAS_VLAN_SUPPORT
int changeVlan=0;
#endif
int sysmodeChanged=0;
static signed int dateNum;
typedef enum{
    WEB_WLAN_ENC_NONE= 0,
    WEB_WLAN_ENC_WEP,
    WEB_WLAN_ENC_WPAPSK,
	WEB_WLAN_ENC_WPARADIUS
}WEB_WLAN_ENC;
int enflag=0;

/*engenius*/
extern T_CHAR model_name[];

//extern T_INT32 model_ID;

//Modify on 2013-09-05 to extend the number of Model to 64
extern long long model_ID;

extern T_INT32 model_radio;

extern T_UINT32 current_opmode;
extern T_UINT32 current_opmode_2;
extern T_UINT32 current_opmode_5;
extern T_CHAR current_radio_flag[5];

extern T_INT32 cmdtreelevel;
extern CliEntry cli_table_ipset[];
T_INT32 landhcpsetbridge=-1;

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- sys opmode                             */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_sys[]= {
//	{OPM_ALL,	"opmode",	cli_table_opmode,	getNextTable,	"Operation mode",		"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP,	"ip",		cli_table_ip,		getNextTable,	"IP settings",                  "",     AUTH_ANY, MODEL_ALL},
//	{OPM_AP,	"ipv6",		cli_table_ipv6set,	getNextTable,	"IPv6 settings",		"",     AUTH_ANY, ENS202EXT_ID},    
//	{OPM_AP,	"stp",		cli_table_stp,		getNextTable,	"Spanning tree settings",	"",     AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,   	"help",		cli_table_sys,		cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,   	"exit",		NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

//CliEntry cli_table_opmode[]= {
//	{OPM_ALL,	"devname",	NULL,			cmddevname,	"Device name",		"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"ctry",		NULL,			cmdctry,	"Country/Region",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"opmode",	NULL,			cmdopmode,	"Operation mode",	"",	AUTH_ADMIN, MODEL_SINGLE},
//	{OPM_ALL,	"opmode2",	NULL,			cmdopmode,	"2.4G Operation mode",	"",	AUTH_ADMIN, MODEL_DUAL},
//	{OPM_ALL,	"opmode5",	NULL,			cmdopmode,	"5G Operation mode",	"",	AUTH_ADMIN, MODEL_DUAL},
//	{OPM_ALL,	"help",		cli_table_opmode,	cmdHelp,	"Help",			"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",			"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

/*****************************************************************
* NAME: cmddevname
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddevname(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.@system[0].SystemName";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (32 characters at most)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 32, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of device name should not be larger than 32\n");
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
* NAME: displaycountry
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID displaycountry(T_CHAR* sku) {
int i;
T_CHAR band[32];

//Add on 2013-10-29 by Philips to support SKU control for all models
//wifi0 for 2.4G, 5G of Single Radio and 2.4G of Dual Radio
T_CHAR func_buf[128]="wireless.wifi0.obeyregpower";
T_CHAR func_buf1[128]="wireless.wifi1.obeyregpower";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];

strcpy(uci_get_buf, cli_get_uci(func_buf));
//wifi1 for 5G of Dual Radio
if ( model_radio==7  )
	strcpy(uci_get_buf1, cli_get_uci(func_buf1));

	if ( model_radio==2 ) 
  		strcpy(band, "2.4G");
	if ( model_radio==5 ) 
  		strcpy(band, "5G");
  	if ( model_radio==7 ) 
  		strcpy(band, current_radio_flag);


//Add on 2013-10-21 by Philips to support SKU control for all models
if ( strcmp(sku, "FCC")==0 ){
	//Check whether Green option of 2.4G or 5G is enabled
	if ( (model_radio==7  && (atoi(uci_get_buf)==1 || atoi(uci_get_buf1)==1)) ||  ((model_radio==2||model_radio==5) && atoi(uci_get_buf)==1) ){
		//{"127", "United States", "840", 3},
		printf("%s - %s\n", CliCountryTable[127].countryCode, CliCountryTable[127].countryName );
	}
	else{
		for (i=0; i<countrycount; i++){



			//2.4G will skip United Kingdom Band B(125) and United Kingdom Band C(126)
			//if ( (i==125 || i==126) && (model_radio==2) )


//Modify on 2013-11-20 by Philips to make 2.4G skip United Kingdom Band B(125) and United Kingdom Band C(126)
if ( (strcmp(CliCountryTable[i].countryCode, "829") == 0 || strcmp(CliCountryTable[i].countryCode, "830") == 0) && (model_radio==2) )			
				continue;

					
			//Modify on 2013-02-23 by Philips to define MODEL_INDOOR which will skip Compliance Band(21) and Compliance Band 2(22)	
			//if ( (i==21 || i==22) && ( model_ID & MODEL_INDOOR ) )

			
//Modify on 2013-11-20 by Philips to define MODEL_INDOOR which will skip Compliance Band(21) and Compliance Band 2(22)	
if ( (strcmp(CliCountryTable[i].countryCode, "827") == 0 || strcmp(CliCountryTable[i].countryCode, "828") == 0) && ( model_ID & MODEL_INDOOR ) )
				continue;

		
			//this country will not appear in 5G
			//if ( (strcmp(band, "5G")==0) && (CliCountryTable[i].htmodeAllow==0) )
			if ( (model_radio==5 || model_radio==7) && (CliCountryTable[i].htmodeAllow==0) )
				continue;
		
			printf("%s - %s\n", CliCountryTable[i].countryCode, CliCountryTable[i].countryName );

		}
	
	}
}
else if ( strcmp(sku, "ETSI")==0 ){

	for (i=0; i<countrycountETSI; i++){

		//2.4G will skip United Kingdom Band B(43) and United Kingdom Band C(44)
		//if ( (i==43 || i==44) && (model_radio==2) )


//Modify on 2013-11-20 by Philips to make 2.4G will skip United Kingdom Band B(125) and United Kingdom Band C(126)		
if ( (strcmp(CliCountryTableETSI[i].countryCode, "829") == 0 || strcmp(CliCountryTableETSI[i].countryCode, "830") == 0) && (model_radio==2) )
			continue;

		
		//this country will not appear in 5G
		//if ( (strcmp(band, "5G")==0) && (CliCountryTable[i].htmodeAllow==0) )


//Modify on 2013-11-20 by Philips to make this country will not appear in 5G	
//if ( (strcmp(band, "5G")==0) && (CliCountryTableETSI[i].htmodeAllow==0) )
if ( (model_radio==5 || model_radio==7) && (CliCountryTable[i].htmodeAllow==0) )	
			continue;
		
		printf("%s - %s\n", CliCountryTableETSI[i].countryCode, CliCountryTableETSI[i].countryName );

	}

}
else if ( strcmp(sku, "INT")==0 ){
	
	
	for (i=0; i<countrycount; i++){

		//2.4G will skip United Kingdom Band B(125) and United Kingdom Band C(126)
		//if ( (i==125 || i==126) && (model_radio==2) )


//Modify on 2013-11-20 by Philips to make 2.4G skip United Kingdom Band B(125) and United Kingdom Band C(126)
if ( (strcmp(CliCountryTable[i].countryCode, "829") == 0 || strcmp(CliCountryTable[i].countryCode, "830") == 0) && (model_radio==2) )	
			continue;

					
		//Modify on 2013-02-23 by Philips to define MODEL_INDOOR which will skip Compliance Band(21) and Compliance Band 2(22)	
		//if ( (i==21 || i==22) && ( model_ID & MODEL_INDOOR ) )

			
//Modify on 2013-11-20 by Philips to define MODEL_INDOOR which will skip Compliance Band(21) and Compliance Band 2(22)	
if ( (strcmp(CliCountryTable[i].countryCode, "827") == 0 || strcmp(CliCountryTable[i].countryCode, "828") == 0) && ( model_ID & MODEL_INDOOR ) )
			continue;

		
		//this country will not appear in 5G
		//if ( (strcmp(band, "5G")==0) && (CliCountryTable[i].htmodeAllow==0) )
		if ( (model_radio==5 || model_radio==7) && (CliCountryTable[i].htmodeAllow==0) )
			continue;
		
		printf("%s - %s\n", CliCountryTable[i].countryCode, CliCountryTable[i].countryName );

	}


}


}

/*****************************************************************
* NAME: searchcountrytable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_CHAR* searchcountrytable(T_CHAR* code, T_CHAR* sku) {
int i;
T_CHAR band[32];


//Add on 2013-10-29 by Philips to support SKU control for all models
//wifi0 for 2.4G, 5G of Single Radio and 2.4G of Dual Radio
T_CHAR func_buf[128]="wireless.wifi0.obeyregpower";
T_CHAR func_buf1[128]="wireless.wifi1.obeyregpower";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];

strcpy(uci_get_buf, cli_get_uci(func_buf));
//wifi1 for 5G of Dual Radio
if ( model_radio==7  )
	strcpy(uci_get_buf1, cli_get_uci(func_buf1));


	if ( model_radio==2 ) 
  		strcpy(band, "2.4G");
	if ( model_radio==5 ) 
  		strcpy(band, "5G");
  	if ( model_radio==7 ) 
  		strcpy(band, current_radio_flag);

	//Modify on 2013-02-23 by Philips to define MODEL_INDOOR which will skip Compliance Band(21) and Compliance Band 2(22)
	if ( (strcmp(code, "827")==0 || strcmp(code, "828")==0) && ( model_ID & MODEL_INDOOR ) )
		return outOfcountryRange;



//Add on 2013-10-21 by Philips to support SKU control for all models
if ( strcmp(sku, "FCC")==0 ){

	//{"127", "United States", "840", 3},
	//if ( strcmp(code, "840")==0 )
	//	return CliCountryTable[127].item;
	//else
	//	return outOfcountryRange;
	
	
	//Add on 2013-10-29 by Philips to support SKU control for all models
	//Check whether Green option of 2.4G or 5G is enabled
	if ( (model_radio==7  && (atoi(uci_get_buf)==1 || atoi(uci_get_buf1)==1)) ||  ((model_radio==2||model_radio==5) && atoi(uci_get_buf)==1) ){
		//{"127", "United States", "840", 3},
		if ( strcmp(code, "840")==0 )
			return CliCountryTable[127].item;
		else
			return outOfcountryRange;
	}
	else{
		for (i=0; i<countrycount; i++){

			if ( strcmp(code, CliCountryTable[i].countryCode)==0 )
				break;			
		}

	
		//return value is 134 when the country code is error
		if ( i==atoi(outOfcountryRange) )
			return outOfcountryRange;

		//this country will not appear in 5G
		//if ( (strcmp(band, "5G")==0) && (CliCountryTable[i].htmodeAllow==0) )
		if ( (model_radio==5 || model_radio==7) && (CliCountryTable[i].htmodeAllow==0) )
			return outOfcountryRange;
	
		return CliCountryTable[i].item;
	}
}
else if ( strcmp(sku, "ETSI")==0 ){


	for (i=0; i<countrycountETSI; i++){

		if ( strcmp(code, CliCountryTableETSI[i].countryCode)==0 )
			break;			
	}

	
	//return value is 45 when the country code is error
	if ( i==atoi(outOfcountryRangeETSI) )
		return outOfcountryRangeETSI;

	//this country will not appear in 5G
	//if ( (strcmp(band, "5G")==0) && (CliCountryTableETSI[i].htmodeAllow==0) )
	if ( (model_radio==5 || model_radio==7) && (CliCountryTable[i].htmodeAllow==0) )
		return outOfcountryRangeETSI;
	
	return CliCountryTableETSI[i].item;


}
else if ( strcmp(sku, "INT")==0 ){


	for (i=0; i<countrycount; i++){

		if ( strcmp(code, CliCountryTable[i].countryCode)==0 )
			break;			
	}

	
	//return value is 134 when the country code is error
	if ( i==atoi(outOfcountryRange) )
		return outOfcountryRange;

	//this country will not appear in 5G
	//if ( (strcmp(band, "5G")==0) && (CliCountryTable[i].htmodeAllow==0) )
	if ( (model_radio==5 || model_radio==7) && (CliCountryTable[i].htmodeAllow==0) )
		return outOfcountryRange;
	
	return CliCountryTable[i].item;
	
	
}


}

/*****************************************************************
* NAME: cmdctry
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdctry(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.wifi0.countryName";
T_CHAR func_buf1[128]="wireless.wifi0.country";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_set_buf[128];
//T_CHAR retval[128];
//T_CHAR code_retval[128];
int retval_int;


//Add on 2013-10-21 by Philips to support SKU control for all models
FILE *pp;
T_CHAR sku[10];


//Add on 2013-11-19 by Philips to calculate the number of countries to be the boundary condition
sprintf(outOfcountryRange, "%d", sizeof(CliCountryTable)/sizeof(CliCountryEntry));
sprintf(outOfcountryRangeETSI, "%d", sizeof(CliCountryTableETSI)/sizeof(CliCountryEntry));
	
	
	//There is no /etc/sku file!
	if( system("test -e /etc/sku") ){
 		//printf("There is no /etc/sku file!\n");
 		strcpy(sku, "INT");
 		//printf("sku=%s, strlen(sku)=%d\n", sku, strlen(sku));
 	}
 	//Get SKU information from the file --- "/etc/sku"
	else 	if( (pp = popen("cat /etc/sku", "r")) == NULL ){
 			printf("popen() error!\n");
 			exit(1);
 		}
		else{
			fgets(sku, sizeof sku, pp);

		
//Add on 2013-11-19 by Philips for all models to delete the following command which is used to take off newline character			
			//sku[strlen(sku)-1]='\0';

			
			//printf("sku=%s, strlen(sku)=%d\n", sku, strlen(sku));
		}
	
	pclose(pp);

	if(cliData->argc==0){
		//get the country Code
		strcpy(uci_get_buf1, cli_get_uci(func_buf1));
		retval_int=atoi(searchcountrytable(uci_get_buf1, sku));
		

//Add on 2013-10-21 by Philips to support SKU control for all models
if ( strcmp(sku, "FCC")==0 ){


    		//retval_int is 134 when the country code is error
		if ( retval_int==atoi(outOfcountryRange) ){
			
			//Transfer Country Name from Country Code
			retval_int=atoi(searchcountrytable(uci_get_buf1, "INT"));
			strcpy(uci_get_buf, CliCountryTable[retval_int].countryName);
			
			displaycountry(sku);
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("\nWarning : The current country is not United States\nPlease set the country code to be 840.\n\n");
			cliData->tokenLen--;
			return CLI_NOTHING;
		}

}
else if ( strcmp(sku, "ETSI")==0 ){


    		//retval_int is 45 when the country code is error
		if ( retval_int==atoi(outOfcountryRangeETSI) ){
			
			//Transfer Country Name from Country Code
			retval_int=atoi(searchcountrytable(uci_get_buf1, "INT"));
			strcpy(uci_get_buf, CliCountryTable[retval_int].countryName);
			
			displaycountry(sku);
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("\nWarning : The current country is not in the ETSI country list\nPlease set the country code to be 528.\n\n");
			cliData->tokenLen--;
			return CLI_NOTHING;
		}


}


		//Transfer Country Name from Country Code
		//strcpy(uci_get_buf, CliCountryTable[retval_int].countryName);


//Add on 2013-10-21 by Philips to support SKU control for all models
if ( strcmp(sku, "ETSI")==0 )
	strcpy(uci_get_buf, CliCountryTableETSI[retval_int].countryName);
else
	strcpy(uci_get_buf, CliCountryTable[retval_int].countryName);


		//display all country list
		//displaycountry();


//Add on 2013-10-21 by Philips to support SKU control for all models
		displaycountry(sku);

		
		tprintf("Current setting: %s\n", uci_get_buf);
		//tprintf("(System will reload wireless driver if you set country code).\n\n");


		tprintf("\n(System will reload wireless driver if you set country code).\n\n");


    		//tprintf("(System will reboot if you set country code).\n\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

		
		//Modify on 2012-08-01 to avoid segmentation fault when the length of input > 128 
		if (!errorcheckStrLength( 4, cliData->tokens[cliData->tokenLen-1].token) || !errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		//get the index for the country code EX.the index of "Colombia"(170) is 20
		//retval_int=atoi(searchcountrytable(uci_set_buf));


//Add on 2013-10-21 by Philips to support SKU control for all models
		retval_int=atoi(searchcountrytable(uci_set_buf, sku));


//Add on 2013-10-21 by Philips to support SKU control for all models
if ( strcmp(sku, "ETSI")==0 ){


		//retval_int is 45 when the country code is error
		if ( retval_int==atoi(outOfcountryRangeETSI) ){
			cliData->tokenLen-=2;
			return CLI_PARAMS_ERR;
		}

		//set the country name and country code into wifi0 when single radio
		cli_set_uci(func_buf, CliCountryTableETSI[retval_int].countryName);
		cli_set_uci(func_buf1, CliCountryTableETSI[retval_int].countryCode);
		
		//set the country name and country code into wifi0 and wifi1 when dual radio
		if ( model_radio==7 ){
			strcpy(func_buf, "wireless.wifi1.countryName");
			cli_set_uci(func_buf, CliCountryTableETSI[retval_int].countryName);
			strcpy(func_buf1, "wireless.wifi1.country");
			cli_set_uci(func_buf1, CliCountryTableETSI[retval_int].countryCode);
		}

		//change htmode to be 20 if this country only allow HTmdoe to be set to 20
		if (model_radio==7 && strcmp(current_radio_flag, "5G")==0 && CliCountryTableETSI[retval_int].htmodeAllow==2)
			cli_set_uci("wireless.wifi1.WLANHTMode", "20");

		if (model_radio==5 && CliCountryTableETSI[retval_int].htmodeAllow==2)
			cli_set_uci("wireless.wifi0.WLANHTMode", "20");
			
		cliData->tokenLen-=2;
		tprintf("\nSystem is reloading the wireless driver ... please wait a moment!\n\n");
		system(" /sbin/luci-reload wireless dhcp lanip > /dev/null 2>&1");
		//system("reboot");
		return CLI_NOTHING;

}
else if ( strcmp(sku, "FCC")==0 || strcmp(sku, "INT")==0 ){


		//retval_int is 134 when the country code is error
		if ( retval_int==atoi(outOfcountryRange) ){
			cliData->tokenLen-=2;
			return CLI_PARAMS_ERR;
		}


}


		//set the country name and country code into wifi0 when single radio
		cli_set_uci(func_buf, CliCountryTable[retval_int].countryName);
		cli_set_uci(func_buf1, CliCountryTable[retval_int].countryCode);
		
		//set the country name and country code into wifi0 and wifi1 when dual radio
		if ( model_radio==7 ){
			strcpy(func_buf, "wireless.wifi1.countryName");
			cli_set_uci(func_buf, CliCountryTable[retval_int].countryName);
			strcpy(func_buf1, "wireless.wifi1.country");
			cli_set_uci(func_buf1, CliCountryTable[retval_int].countryCode);
		}

		//change htmode to be 20 if this country only allow HTmdoe to be set to 20
		if (model_radio==7 && strcmp(current_radio_flag, "5G")==0 && CliCountryTable[retval_int].htmodeAllow==2)
			cli_set_uci("wireless.wifi1.WLANHTMode", "20");

		if (model_radio==5 && CliCountryTable[retval_int].htmodeAllow==2)
			cli_set_uci("wireless.wifi0.WLANHTMode", "20");
		
		cliData->tokenLen-=2;
		tprintf("\nSystem is reloading the wireless driver ... please wait a moment!\n\n");
		system(" /sbin/luci-reload wireless dhcp lanip > /dev/null 2>&1");
		//system("reboot");
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: opmodeProcess
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
int opmodeProcess(T_INT32 switch_opmode, T_INT32 current_mode) {
T_CHAR func_buf[128]="network.lan.ipaddr";
T_CHAR buf[255];
T_CHAR ipaddr[128];
T_INT32 ssidCount;
T_INT32 i;
T_INT32 nawds_index;
T_INT32 start;
T_INT32 stop;
T_INT32 operationeMode=current_opmode;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

//printf("switch_opmode=%d, current_mode=%d, operationeMode=%d\n", switch_opmode, current_mode, operationeMode);

	ssidCount=getModelssidCount(operationeMode);
	
	if (model_radio==2 || model_radio==5){
		//backup ipaddress
		strcpy(ipaddr, cli_get_uci(func_buf));
		//backup files
		switch (current_mode){
		
		case OPM_AP:
			system("tar -cz -f /etc/cfg_profile/ap.tar.gz -C /etc/config network wireless");
			break;
		case OPM_CB:
			system("tar -cz -f /etc/cfg_profile/sta.tar.gz -C /etc/config network wireless");
			break;
		case OPM_WDSAP:
			system("tar -cz -f /etc/cfg_profile/ap.tar.gz -C /etc/config network wireless");
			break;
		case OPM_WDSB:
			system("tar -cz -f /etc/cfg_profile/br.tar.gz -C /etc/config network wireless");
			break;
		case OPM_WDSSTA:
			system("tar -cz -f /etc/cfg_profile/sta.tar.gz -C /etc/config network wireless");
			break;
		case OPM_AR:
			system("tar -cz -f /etc/cfg_profile/apr.tar.gz -C /etc/config network wireless dhcp");
			break;
		case OPM_CBRT:
			system("tar -cz -f /etc/cfg_profile/cr.tar.gz -C /etc/config network wireless dhcp");
			break;
		case OPM_RP:
			system("tar -cz -f /etc/cfg_profile/rp.tar.gz -C /etc/config network wireless");
			break;
		}
	}
	
	nawds_index=get_nawds_index(ssidCount, operationeMode);
	
	switch (switch_opmode-1){
	case SYS_OPM_AP: //switch to AP
		if (model_radio==2 || model_radio==5)
			system("tar -C /etc/config -zvxf /etc/cfg_profile/ap.tar.gz > /dev/null 2>&1");
		
		start=get_wifi_iface(OPM_AP);
		stop=start+ssidCount;
		
		if (current_mode==OPM_CBRT){

			system("uci set dhcp.lan.ignore=1");	
		}

		for (i=start; i<stop; i++){	
			sprintf(buf, "uci set wireless.@wifi-iface[%d].wds=0", i);
			system(buf);
		}
		sprintf(buf, "uci set wireless.@wifi-iface[%d].nawds=0", nawds_index);
		system(buf);
		
		//Modify for AP100 on 2012-11-09 to set wireless to be B/G/N Mixed(11ng) when CB or WDSSTA switch to AP, WDSAP or WDSB	
		if ( strcmp(model_name, "ap100")==0  && ( current_mode==2 || current_mode==16 ) )	
			cli_set_uci("wireless.wifi0.hwmode", "11ng");

		break;
	case SYS_OPM_CB: //switch to CB
		if (model_radio==2 || model_radio==5)
			system("tar -C /etc/config -zvxf /etc/cfg_profile/sta.tar.gz > /dev/null 2>&1");
		
		start=get_wifi_iface(OPM_CB);
		
		if (current_mode==OPM_CBRT){
			system("uci set dhcp.lan.ignore=1");
			sprintf(buf, "uci set wireless.@wifi-iface[%d].network=wan", start);
			system(buf);	
		}
		
		sprintf(buf, "uci set wireless.@wifi-iface[%d].wds=0", start);
		system(buf);

		//Modify for AP100 on 2012-11-09 to set wireless to be A/B/G/N Mixed(11abgn)	
		if ( strcmp(model_name, "ap100")==0  )	
			cli_set_uci("wireless.wifi0.hwmode", "11abgn");
	
		if ( strcmp(model_name, "ap100")!=0  ) {			
			//Modify on 2012-11-09 to set wireless to be B/G/N Mixed(11ng) for Dual radio 2.4G
			if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
				cli_set_uci("wireless.wifi0.hwmode", "11ng");
			//Modify on 2012-11-09 to set wireless to be A/N Mixed(11na) for Dual radio 5G	
			if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
				cli_set_uci("wireless.wifi1.hwmode", "11na");
		}	

		
		break;
	case SYS_OPM_WDSAP: //switch to WDSAP

		if (model_radio==2 || model_radio==5)
			system("tar -C /etc/config -zvxf /etc/cfg_profile/ap.tar.gz > /dev/null 2>&1");
		
		start=get_wifi_iface(OPM_WDSAP);
		stop=start+ssidCount;

		if (current_mode==OPM_CBRT){

			system("uci set dhcp.lan.ignore=1");
			system("uci set wireless.@wifi-iface[0].network=wan");	
		}

		for (i=start; i<stop; i++){	

			sprintf(buf, "uci set wireless.@wifi-iface[%d].wds=1", i);
			system(buf);
		}
		sprintf(buf, "uci set wireless.@wifi-iface[%d].nawds=1", nawds_index);
		system(buf);
		
		//Modify for AP100 on 2012-11-09 to set wireless to be B/G/N Mixed(11ng) when CB or WDSSTA switch to AP, WDSAP or WDSB	
		if ( strcmp(model_name, "ap100")==0  && ( current_mode==2 || current_mode==16 ) )	
			cli_set_uci("wireless.wifi0.hwmode", "11ng");
	
		break;
	case SYS_OPM_WDSB: //switch to WDSBR
		if (model_radio==2 || model_radio==5)
			system("tar -C /etc/config -zvxf /etc/cfg_profile/br.tar.gz > /dev/null 2>&1");
		
		start=get_wifi_iface(OPM_WDSB);
		stop=start+ssidCount;
	   
		if (current_mode==OPM_CBRT){

			system("uci set dhcp.lan.ignore=1");
			system("uci set wireless.@wifi-iface[0].network=wan");	
		}

		for (i=start; i<stop; i++){	
			sprintf(buf, "uci set wireless.@wifi-iface[%d].wds=0", i);
			system(buf);
		}
		sprintf(buf, "uci set wireless.@wifi-iface[%d].nawds=1", nawds_index);
		system(buf);
		
		//Modify for AP100 on 2012-11-09 to set wireless to be B/G/N Mixed(11ng) when CB or WDSSTA switch to AP, WDSAP or WDSB	
		if ( strcmp(model_name, "ap100")==0  && ( current_mode==2 || current_mode==16 ) )	
			cli_set_uci("wireless.wifi0.hwmode", "11ng");
		
		//Modify on 2012-12-26 to set htmode to be 40 when switch to WDSB for dual-radio	
		if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
			cli_set_uci("wireless.wifi0.WLANHTMode", "40");
		if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
			cli_set_uci("wireless.wifi1.WLANHTMode", "40");
		
		break;
	case SYS_OPM_WDSSTA: //switch to WDSSTA
		if (model_radio==2 || model_radio==5)
			system("tar -C /etc/config -zvxf /etc/cfg_profile/sta.tar.gz > /dev/null 2>&1");
		
		start=get_wifi_iface(OPM_WDSSTA);
		
		if (current_mode==OPM_CBRT){
			system("uci set dhcp.lan.ignore=1");
			sprintf(buf, "uci set wireless.@wifi-iface[%d].network=wan", start);
			system(buf);	
		}
		
		sprintf(buf, "uci set wireless.@wifi-iface[%d].wds=1", start);
		system(buf);
		
		//Modify for AP100 on 2012-11-09 to set wireless to be A/B/G/N Mixed(11abgn)	
		if ( strcmp(model_name, "ap100")==0  )	
			cli_set_uci("wireless.wifi0.hwmode", "11abgn");
	
		if ( strcmp(model_name, "ap100")!=0  ) {			
			//Modify on 2012-11-09 to set wireless to be B/G/N Mixed(11ng) for Dual radio 2.4G
			if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
				cli_set_uci("wireless.wifi0.hwmode", "11ng");
			//Modify on 2012-11-09 to set wireless to be A/N Mixed(11na) for Dual radio 5G	
			if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
				cli_set_uci("wireless.wifi1.hwmode", "11na");
		}
		
		break;
	case SYS_OPM_AR: //switch to AR
		if (model_radio==2 || model_radio==5)
			system("tar -C /etc/config -zvxf /etc/cfg_profile/apr.tar.gz > /dev/null 2>&1");
		
		start=get_wifi_iface(OPM_AR);
		stop=start+ssidCount;

		for (i=start; i<stop; i++){	
			sprintf(buf, "uci set wireless.@wifi-iface[%d].wds=0", i);
			system(buf);
		}
		sprintf(buf, "uci set wireless.@wifi-iface[%d].nawds=0", nawds_index);
		system(buf);
		
		system("uci set dhcp.wan.ignore=1");
		system("uci set network.wan.ifname=\"eth0 eth1\"");
		system("uci set network.lan.type=bridge");
		system("uci set network.lan.ifname=\"\"");
		
		sprintf(buf, "uci set wireless.@wifi-iface[%d].network=lan", start);
		system(buf);
		
		break;
	case SYS_OPM_CBRT: //switch to CR
		if (model_radio==2 || model_radio==5)
			system("tar -C /etc/config -zvxf /etc/cfg_profile/cr.tar.gz > /dev/null 2>&1");
		
		start=get_wifi_iface(OPM_CBRT);
		
		if (current_mode==OPM_CBRT){
			system("uci set dhcp.lan.ignore=0");
			sprintf(buf, "uci set wireless.@wifi-iface[%d].network=wan", start);
			system(buf);	
		}
		
		sprintf(buf, "uci set wireless.@wifi-iface[%d].wds=0", start);
		system(buf);
		
		break;
	case SYS_OPM_RP: //switch to RP
		if (model_radio==2 || model_radio==5)
			system("tar -C /etc/config -zvxf /etc/cfg_profile/rp.tar.gz > /dev/null 2>&1");
		
		start=get_wifi_iface(OPM_RP);
		
		sprintf(buf, "uci set wireless.@wifi-iface[%d].wds=0", start);
		system(buf);
		
		break;	
	}	

	if (model_radio==2 || model_radio==5){
		
		cli_set_uci(func_buf, ipaddr);
		system("/etc/init.d/factory_ssid start > /dev/null 2>&1");
	}
}

/*****************************************************************
* NAME: displayopmode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 displayopmode(T_INT32 argCount) {
T_INT32 i;
T_INT32 j=1;
T_INT32 Modelopmode;

	//model_name=enh500, Modelopmode=ENH500_OPM (OPM_AP|OPM_CB|OPM_WDSAP|OPM_WDSB|OPM_WDSSTA|OPM_CBRT)
	Modelopmode=getModelopmode();
	
	for (i=1; i<=SYS_OPM_COUNT; i++){
		//check every kind of operation mode for the model
		if ( (Modelopmode & (1<<(i-1)))==0 )
			continue;
		
//Modify for AP100 on 2012-11-09			
if ( (strcmp(model_name, "ap100")==0) ){
	if (argCount==0)
		printf("%d - %s\n", j++, CliOperationModeTable[i-1].operationmodeName );
		
	if (argCount==1)
		j++;
}
		
//Modify for AP100 on 2012-11-09			
if ( (strcmp(model_name, "ap100")!=0) ){


	//Modify for CAP4200 on 2013-05-23 to release the constraint of both 2.4G and 5G operation modes
	if ( (strcmp(model_name, "cap4200ag")!=0) ){


		//2.4G opmode is constrained by 5G opmode
		if ( strcmp(current_radio_flag, "2.4G")==0 && ( current_opmode_5==OPM_WDSB || current_opmode_5==OPM_RP || current_opmode_5==OPM_CB || current_opmode_5==OPM_WDSSTA || current_opmode_5==OPM_AR || current_opmode_5==OPM_CBRT ) ) {
			if ( ((1<<(i-1)) & OPM_WDSB)!=0 || ((1<<(i-1)) & OPM_RP)!=0 || ((1<<(i-1)) & OPM_CB)!=0 || ((1<<(i-1)) & OPM_WDSSTA)!=0 || ((1<<(i-1)) & OPM_AR)!=0 || ((1<<(i-1)) & OPM_CBRT)!=0 )
				continue;
		}
		
		//5G opmode is constrained by 2.4G opmode
		if ( strcmp(current_radio_flag, "5G")==0 && ( current_opmode_2==OPM_WDSB || current_opmode_2==OPM_RP || current_opmode_2==OPM_CB || current_opmode_2==OPM_WDSSTA || current_opmode_2==OPM_AR || current_opmode_2==OPM_CBRT) ) {
			if ( ((1<<(i-1)) & OPM_WDSB)!=0 || ((1<<(i-1)) & OPM_RP)!=0 || ((1<<(i-1)) & OPM_CB)!=0 || ((1<<(i-1)) & OPM_WDSSTA)!=0 || ((1<<(i-1)) & OPM_AR)!=0 || ((1<<(i-1)) & OPM_CBRT)!=0 )
				continue;
		}


	}

		//List every possible operation mode
		if (argCount==0)
			printf("%d - %s\n", j++, CliOperationModeTable[i-1].operationmodeName );
		
		if (argCount==1)
			j++;
}
	}
	return j-1;
}

/*****************************************************************
* NAME: cmdopmode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdopmode(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.sys.opmode";
T_CHAR func_buf1[128]="wireless.wifi0.opmode";
T_CHAR func_buf2[128]="wireless.wifi1.opmode";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 opmodeget; 
T_INT32 convertIndex;
T_INT32 i;
T_INT32 opmodeRange;

	if(cliData->argc==0){
		if (model_radio==7 && ( strcmp(current_radio_flag, "2.4G")==0 ) )
			strcpy(uci_get_buf, cli_get_uci(func_buf1));
		
		if (model_radio==7 && ( strcmp(current_radio_flag, "5G")==0 ) )
			strcpy(uci_get_buf, cli_get_uci(func_buf2));
		
		if (model_radio==2 || model_radio==5)
			strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		//for display
		displayopmode(cliData->argc);
		//Jacy ask to display full name of operation mode
		
		for (i=0; i<SYS_OPM_COUNT; i++){
		
			if ( strcmp(uci_get_buf, CliOperationModeTable[i].operationmode)==0 )
				break;			
		}
		strcpy(uci_get_buf, CliOperationModeTable[i].operationmodeName);
		tprintf("Current setting: %s\n", uci_get_buf);
		if (model_radio==2 || model_radio==5)
			tprintf("(System will reboot if you set operation mode).\n\n");
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//for find opmodeRange
		opmodeRange=displayopmode(cliData->argc);
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
		
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, opmodeRange, atoi(cliData->tokens[cliData->tokenLen-1].token) )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		if (model_radio==2 || model_radio==5){	
			//the current opmode
			opmodeget=current_opmode;
		}
		else if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
			opmodeget=current_opmode_2;
		else if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
			opmodeget=current_opmode_5;
		
		//the opmode to be set 
		convertIndex=convertOpmodeIndex(atoi(uci_set_buf));	
		
		opmodeProcess( convertIndex, opmodeget );		
		strcpy(uci_set_buf, CliOperationModeTable[convertIndex-1].operationmode);
		
		if (model_radio==2 || model_radio==5){	
			cli_set_uci(func_buf, uci_set_buf);
			printf("Rebooting, please wait ...\n");
			system("uci commit; reboot");
			exit(1);
		}
		else if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 ){
//tprintf("2-uci_set_buf=%s\n", uci_set_buf);
			cli_set_uci(func_buf1, uci_set_buf);
			system("uci commit");
			getSysOperationMode();
		}
		else if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 ){
//tprintf("5-uci_set_buf=%s\n", uci_set_buf);
			cli_set_uci(func_buf2, uci_set_buf);

			system("uci commit");
			getSysOperationMode();

		}
			
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- sys ip                                 */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_sys[]= {
//	{OPM_ALL,	"opmode",	cli_table_opmode,	getNextTable,	"Operation mode",		"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP,	"ip",		cli_table_ip,		getNextTable,	"IP settings",                  "",     AUTH_ANY, MODEL_ALL},
//	{OPM_AP,	"ipv6",		cli_table_ipv6set,	getNextTable,	"IPv6 settings",		"",     AUTH_ANY, ENS202EXT_ID},    
//	{OPM_AP,	"stp",		cli_table_stp,		getNextTable,	"Spanning tree settings",	"",     AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,   	"help",		cli_table_sys,		cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,   	"exit",		NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

//CliEntry cli_table_ip[]= {
//	{OPM_ALL,	"dhcpact",	NULL,			cmddhcpact,	"DHCP active",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,   	"help",		cli_table_ip,		cmdHelp,	"Help",		"",	AUTH_ADMIN, MODEL_ALL},
//   	{OPM_ALL,   	"exit",		NULL,			cmdexit,	"Exit",		"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

//CliEntry cli_table_ipset[]= {
//	{OPM_ALL,	"ipaddr",	NULL,			cmdipaddr,      "IP address",			"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"ipsubn",	NULL,			cmdipsubn,	"IP subnet mask",		"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"gateway",	NULL,			cmdgateway,	"Default gateway",		"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"pdns",		NULL,			cmdpdns,        "Primary dns",			"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"sdns",		NULL,			cmdsdns,        "Secondary dns",		"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"accept",  	NULL,			cmdipsetaccept,	"Accept LAN IP setting",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_ipset,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdipsetexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

/*****************************************************************
* NAME: cmddhcpact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddhcpact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.proto";
T_CHAR func_buf1[128]="network.lan.accept_ra";
T_CHAR func_buf2[128]="dhcp6c.basic.enabled";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	//Handle the command --> sys ip dhcpact
	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:DHCP, 2:Static)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	//Handle the command --> sys ip dhcpact 2
	else if(cliData->argc==1){

		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if ( landhcpsetbridge==-1 ){
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 2, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
				cliData->tokenLen-=2;
				return CLI_PARAMS_ERR;
			}
		
			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);	
	
			//set DHCP active or static IP		
			if ( strcmp(uci_set_buf, "1")==0 ){
				//set DHCP active
				cli_set_uci(func_buf, "dhcp");


//Modify on 2013-02-05 for ENS500 to support IPV6
//#define MODEL_IPV6	(ENS202_ID|ENS202EXT_ID|EAP600_ID|ECB600_ID|ENS500_ID|ENS500EXT_ID|ENH510_ID)			
				//Modify by Philips on 2012-10-05 for IPV6 of ens202ext
				//if ( strcmp(model_name, "ens202ext")==0 || strcmp(model_name, "ens202")==0 || strcmp(model_name, "ecb600")==0 || strcmp(model_name, "eap600")==0 ){
				if( model_ID & MODEL_IPV6 ){
//					printf("I am ens202ext --- DHCP\n");
					cli_set_uci(func_buf1, "1");
					cli_set_uci(func_buf2, "1");
				}
				
				cliData->tokenLen-=2;
				return CLI_NOTHING;
			}
			if ( strcmp(uci_set_buf, "2")==0 ) {
				//set static IP
				cli_set_uci(func_buf, "static");


//Modify on 2013-02-05 for ENS500 to support IPV6
//#define MODEL_IPV6	(ENS202_ID|ENS202EXT_ID|EAP600_ID|ECB600_ID|ENS500_ID|ENS500EXT_ID|ENH510_ID)				
				//Modify by Philips on 2012-10-05 for IPV6 of ens202ext
				//if ( strcmp(model_name, "ens202ext")==0 || strcmp(model_name, "ens202")==0 || strcmp(model_name, "ecb600")==0 || strcmp(model_name, "eap600")==0 ){
				if( model_ID & MODEL_IPV6 ){
//					printf("I am ens202ext --- STATIC IP\n");
					cli_set_uci(func_buf1, "0");
					cli_set_uci(func_buf2, "0");
				}
				
				cliData->tokenLen--;
				
				//Handle the command --> sys/ip>dhcpact 2
				if (cmdtreelevel==2){
					landhcpsetbridge=1;
					//prompt will be --> sys/ip/dhcpact>
					cmdtreelevel=cliData->tokenLen;
				}
				
				return cmdHelp(cli_table_ipset,cliData);
			}
		}
		else if ( landhcpsetbridge==1 )
			return getNextTable(cli_table_ipset, cliData);
	}
	//Handle the command --> "sys ip dhcpact 2 X X ..." or "sys ip dhcpact 1 X X ..."
	else if(cliData->argc>1){
		
		//handle too many argument --> sys/ip>dhcpact 1 X X ...
		if (strcmp(cliData->tokens[3].token, "1")==0 && cliData->tokenLen>=5)
			return CLI_PARAMS_ERR;

		//handle relative path --> sys/ip/dhcpact>ipaddr
		if ( landhcpsetbridge==1 )
			return getNextTable(cli_table_ipset, cliData);
		
		//handle absolute path --> sys ip dhcpact 2 ipaddr
		if ( strcmp(cliData->tokens[3].token, "2")==0 ){
			cli_set_uci(func_buf, "static");


//Modify on 2013-02-05 for ENS500 to support IPV6
//#define MODEL_IPV6	(ENS202_ID|ENS202EXT_ID|EAP600_ID|ECB600_ID|ENS500_ID|ENS500EXT_ID|ENH510_ID)			
			//Modify by Philips on 2012-10-05 for IPV6 of ens202ext
			//if ( strcmp(model_name, "ens202ext")==0 || strcmp(model_name, "ens202")==0 || strcmp(model_name, "ecb600")==0 || strcmp(model_name, "eap600")==0 ){
			if( model_ID & MODEL_IPV6 ){
//				printf("I am ens202ext --- STATIC IP\n");
				cli_set_uci(func_buf1, "0");
				cli_set_uci(func_buf2, "0");
			}
				
			//Skip "2" when handling "sys ip dhcpact 2 ipaddr"
			cliData->argc--;
			return getNextTable(cli_table_ipset, cliData);
		}
	}

}

/*****************************************************************
* NAME: cmdipaddr
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipaddr(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.ipaddr";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Clilanipset.ipset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		else{
			strcpy(uci_get_buf, Clilanipset.ip);
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
		strcpy(Clilanipset.ip, uci_set_buf);
		Clilanipset.ipset=1;

		cliData->tokenLen-=2;		
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdipsubn
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipsubn(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.netmask";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Clilanipset.maskset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf);
		}
		else{
			strcpy(uci_get_buf, Clilanipset.subnetmask);
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
		
		strcpy(Clilanipset.subnetmask, uci_set_buf);
		Clilanipset.maskset=1;

		cliData->tokenLen-=2;
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdgateway
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdgateway(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.gateway";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Clilanipset.gatewayset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		else{
			strcpy(uci_get_buf, Clilanipset.gateway);
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
		
		strcpy(Clilanipset.gateway, uci_set_buf);
		Clilanipset.gatewayset=1;

		cliData->tokenLen-=2;

		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdpdns
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpdns(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.dns";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
const char *del = " ";
T_CHAR* pdns;
T_CHAR* sdns;
T_INT32 operationeMode=current_opmode;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	if(cliData->argc==0){

		if (Clilanipset.pdnsset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			pdns = strtok(uci_get_buf, del);
			if ( pdns != NULL )
				tprintf("Current setting: %s\n", pdns);
			else
				tprintf("Current setting: NULL\n");
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		else{
			strcpy(uci_get_buf, Clilanipset.pdns);
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid segmentation fault when the length of input > 128
		//strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		//if (!errorcheckValidIP( uci_set_buf )){
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		//set value into configuration file if operationeMode is CR or AR
		if ( (operationeMode==OPM_CBRT || operationeMode==OPM_AR) ){
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			sdns = strtok(uci_get_buf, del);
			sdns = strtok(NULL, del);
			strcat(uci_set_buf, " ");
			strcat(uci_set_buf, sdns);
			cli_set_uci(func_buf, uci_set_buf);	
		}
		//set value into Clilanipset Table if operationeMode is not CR or AR
		else{
			strcpy(Clilanipset.pdns, uci_set_buf);
			Clilanipset.pdnsset=1;
		}

		cliData->tokenLen-=2;

		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsdns
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsdns(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.dns";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
const T_CHAR *del = " ";
T_CHAR* pdns;
T_CHAR* sdns;
T_INT32 operationeMode=current_opmode;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	if(cliData->argc==0){
		//Modify on 2012-10-30 by Philips
		if (Clilanipset.sdnsset==0){
			strcpy(uci_get_buf, cli_get_uci(func_buf));		
			pdns = strtok(uci_get_buf, del);
			sdns = strtok(NULL, del);
				
			if ( sdns != NULL )
				tprintf("Current setting: %s\n", sdns);
			else
				tprintf("Current setting: NULL\n");
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		else{
			strcpy(uci_get_buf, Clilanipset.sdns);
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid segmentation fault when the length of input > 128
		//strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		//if (!errorcheckValidIP( uci_set_buf )){
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		//set value into configuration file if operationeMode is CR or AR
		if ( (operationeMode==OPM_CBRT || operationeMode==OPM_AR) ){
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			pdns = strtok(uci_get_buf, del);
			strcat(pdns, " ");
			strcat(pdns, uci_set_buf);
			strcpy(uci_set_buf, pdns);
			cli_set_uci(func_buf, uci_set_buf);	
		}
		//set value into Clilanipset Table if operationeMode is not CR or AR
		else{
			strcpy(Clilanipset.sdns, uci_set_buf);
			Clilanipset.sdnsset=1;
		}

		cliData->tokenLen-=2;

		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdipsetaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipsetaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.ipaddr";
T_CHAR func_buf1[128]="network.lan.netmask";
T_CHAR func_buf2[128]="network.lan.gateway";
T_CHAR func_buf3[128]="network.lan.dns";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_get_buf2[128];
T_CHAR uci_get_buf3[128];

T_CHAR func_buf4[128]="network.lan.ip6addr";
T_CHAR func_buf5[128]="network.lan.ip6gw";
T_CHAR func_buf6[128]="network.lan.ip6LinkLocalEn";
T_CHAR half_uci_get_buf3[128];
T_CHAR uci_get_buf4[128];
T_CHAR uci_get_buf5[128];
T_CHAR uci_get_buf6[128];
T_CHAR uci_get_buf7[128];

const T_CHAR *del = " ";
T_CHAR* pdns;
static T_CHAR* sdns;
T_CHAR sdnsarray[16];
T_CHAR dns[128];
static T_CHAR* dns1, * dns2, * dns3, * dns4;
T_CHAR pdns4[40], sdns4[40], pdns6[40], sdns6[40];

	if(cliData->argc==0){
		//Get ipv4 address
		if (Clilanipset.ipset==0)
			strcpy(uci_get_buf, cli_get_uci(func_buf));
		else
			strcpy(uci_get_buf, Clilanipset.ip);
		//Get subnet mask
		if (Clilanipset.maskset==0)
			strcpy(uci_get_buf1, cli_get_uci(func_buf1));
		else
			strcpy(uci_get_buf1, Clilanipset.subnetmask);
		//Get gateway
		if (Clilanipset.gatewayset==0)
			strcpy(uci_get_buf2, cli_get_uci(func_buf2));
		else
			strcpy(uci_get_buf2, Clilanipset.gateway);

		
		if (!errorcheckValidIPandMask(uci_get_buf, uci_get_buf1)){
			cliData->tokenLen-=1;
			tprintf("Invalid IP address\n");
	  		return CLI_PARAMS_ERR;
		}
		if (!errorcheckValidIPandMask(uci_get_buf2, uci_get_buf1)){
			cliData->tokenLen-=1;
			tprintf("Invalid Gateway IP address\n");
	  		return CLI_PARAMS_ERR;
		}
		if (!errorcheckSameDomain(uci_get_buf, uci_get_buf2, uci_get_buf1 )){
			cliData->tokenLen-=1;
			tprintf("Gateway address and IP address should be in the same subnet\n");
	  		return CLI_PARAMS_ERR;
		}
		//The correct value of dns should be "0.0.0.0  0.0.0.0"		
		if (Clilanipset.pdnsset==0){
			strcpy(uci_get_buf3, cli_get_uci(func_buf3));
			//network.lan.dns is null
			if ( strcmp(uci_get_buf3, "")==0 ){
				cliData->tokenLen-=1;
				tprintf("Invalid primary DNS address\n");
	  			return CLI_PARAMS_ERR;	
			}
		}
		if (Clilanipset.sdnsset==0){
			strcpy(uci_get_buf3, cli_get_uci(func_buf3));
			//network.lan.dns is null
			if ( strcmp(uci_get_buf3, "")==0 ){
				cliData->tokenLen-=1;
				tprintf("Invalid secondary DNS address\n");
	  			return CLI_PARAMS_ERR;
	  		}	
		}

//Modify on 2010-10-29 for IPV6 relative fields
//Get the value of pdns4, sdns4, pdns6 and sdns6 from network.lan.dns
strcpy(uci_get_buf3, cli_get_uci(func_buf3));

dns1 = strtok(uci_get_buf3, del);
dns2 = strtok(NULL, del);


//Modify on 2013-02-05 for ENS500 to support IPV6
//#define MODEL_IPV6	(ENS202_ID|ENS202EXT_ID|EAP600_ID|ECB600_ID|ENS500_ID|ENS500EXT_ID|ENH510_ID)
//if ( strcmp(model_name, "ens202ext")==0 || strcmp(model_name, "ens202")==0 || strcmp(model_name, "ecb600")==0 || strcmp(model_name, "eap600")==0 ){
if( model_ID & MODEL_IPV6 ){		
	dns3 = strtok(NULL, del); 		
	dns4 = strtok(NULL, del); 		
}

( dns1 != NULL ) ? strcpy(pdns4, dns1) : strcpy(pdns4, "");
( dns2 != NULL ) ? strcpy(sdns4, dns2) : strcpy(sdns4, "");


//Modify on 2013-02-05 for ENS500 to support IPV6
//#define MODEL_IPV6	(ENS202_ID|ENS202EXT_ID|EAP600_ID|ECB600_ID|ENS500_ID|ENS500EXT_ID|ENH510_ID)
//if ( strcmp(model_name, "ens202ext")==0 || strcmp(model_name, "ens202")==0 || strcmp(model_name, "ecb600")==0 || strcmp(model_name, "eap600")==0 ){
if( model_ID & MODEL_IPV6 ){
	( dns3 != NULL ) ? strcpy(pdns6, dns3) : strcpy(pdns6, "");
	( dns4 != NULL ) ? strcpy(sdns6, dns4) : strcpy(sdns6, "");
}
				
		//prepare DNS data to write into configuration file
		if (Clilanipset.pdnsset==1 && Clilanipset.sdnsset==1){
			strcpy(uci_get_buf3, Clilanipset.pdns);
			strcat(uci_get_buf3, " ");
			strcat(uci_get_buf3, Clilanipset.sdns);
		}
		else if (Clilanipset.pdnsset==1 && Clilanipset.sdnsset==0){
			strcpy(uci_get_buf3, Clilanipset.pdns);
			strcat(uci_get_buf3, " ");
			strcat(uci_get_buf3, sdns4);
		}	
		else if (Clilanipset.pdnsset==0 && Clilanipset.sdnsset==1){
			strcpy(uci_get_buf3, pdns4);
			strcat(uci_get_buf3, " ");
			strcat(uci_get_buf3, Clilanipset.sdns);
		}
		else if (Clilanipset.pdnsset==0 && Clilanipset.sdnsset==0){
			strcpy(uci_get_buf3, pdns4);
			strcat(uci_get_buf3, " ");
			strcat(uci_get_buf3, sdns4);
		}


//Modify on 2013-02-05 for ENS500 to support IPV6
//#define MODEL_IPV6	(ENS202_ID|ENS202EXT_ID|EAP600_ID|ECB600_ID|ENS500_ID|ENS500EXT_ID|ENH510_ID)
//if ( strcmp(model_name, "ens202ext")==0 || strcmp(model_name, "ens202")==0 || strcmp(model_name, "ecb600")==0 || strcmp(model_name, "eap600")==0 ){
if( model_ID & MODEL_IPV6 ){		
	//Write new pdns, new sdns, old pdns6 and old sdns6 for recovery when link6 is set to be "1"	
	strcpy(half_uci_get_buf3, uci_get_buf3);
	if ( dns3 != NULL ){
		strcat(half_uci_get_buf3, " ");
		strcat(half_uci_get_buf3, pdns6);
	}
	if ( dns3 != NULL ){
		strcat(half_uci_get_buf3, " ");
		strcat(half_uci_get_buf3, sdns6);
	}

	//Prepare pdns6 and sdns6 value for DNS
	if (Clilanipset.pdnsv6set==1 && Clilanipset.sdnsv6set==1){
		strcat(uci_get_buf3, " ");
		strcat(uci_get_buf3, Clilanipset.pdnsv6);
		strcat(uci_get_buf3, " ");
		strcat(uci_get_buf3, Clilanipset.sdnsv6);
	}
	if (Clilanipset.pdnsv6set==1 && Clilanipset.sdnsv6set==0){
		strcat(uci_get_buf3, " ");
		strcat(uci_get_buf3, Clilanipset.pdnsv6);
		if ( strcmp(sdns6, "")!=0 ) {
			strcat(uci_get_buf3, " ");
			strcat(uci_get_buf3, sdns6);
		}
	}
	if (Clilanipset.pdnsv6set==0 && Clilanipset.sdnsv6set==1){
		if ( strcmp(pdns6, "")!=0 ) {
			strcat(uci_get_buf3, " ");
			strcat(uci_get_buf3, pdns6);
			strcat(uci_get_buf3, " ");
			strcat(uci_get_buf3, Clilanipset.sdnsv6);
		}
		else {
			cliData->tokenLen-=1;
			tprintf("Invalid primary DNSV6 address\n");
		  	return CLI_PARAMS_ERR;	
		}
	}
	if (Clilanipset.pdnsv6set==0 && Clilanipset.sdnsv6set==0){
		if ( strcmp(pdns6, "")!=0 ) {
			strcat(uci_get_buf3, " ");
			strcat(uci_get_buf3, pdns6);
		}
		if ( strcmp(sdns6, "")!=0 ) {
			strcat(uci_get_buf3, " ");
			strcat(uci_get_buf3, sdns6);
		}
	}
}		
		cli_set_uci(func_buf, uci_get_buf);
		cli_set_uci(func_buf1, uci_get_buf1);
		cli_set_uci(func_buf2, uci_get_buf2);
		cli_set_uci(func_buf3, uci_get_buf3);


//Modify on 2013-02-05 for ENS500 to support IPV6
//#define MODEL_IPV6	(ENS202_ID|ENS202EXT_ID|EAP600_ID|ECB600_ID|ENS500_ID|ENS500EXT_ID|ENH510_ID)
//if ( strcmp(model_name, "ens202ext")==0 || strcmp(model_name, "ens202")==0 || strcmp(model_name, "ecb600")==0 || strcmp(model_name, "eap600")==0 ){
if( model_ID & MODEL_IPV6 ){
	//Modify on 2010-10-29 for IPV6 relative fields
	//Get link6 information
	if (Clilanipset.link6set==0)
		strcpy(uci_get_buf6, cli_get_uci(func_buf6));
	else
		strcpy(uci_get_buf6, Clilanipset.link6);
	//IPv6 address is set by system
	if ( atoi(uci_get_buf6)==1 ) {
		//Get IPv6 address from network.lan.ip6addr
		strcpy(uci_get_buf4, cli_get_uci(func_buf4));	
		if ( strcmp(uci_get_buf4, "")!=0 ) {	
			//Step 1. Copy IPv6 address from network.lan.ip6addr to network.lan.orig_ip6addr
			cli_set_uci("network.lan.orig_ip6addr", uci_get_buf4);		
			//Step 2. Set the IPv6 address of network.lan.ip6addr to be null string
			strcpy(uci_get_buf4, "");
			cli_set_uci(func_buf4, uci_get_buf4);
		}
		//Write 1 into network.lan.ip6LinkLocalEn
		cli_set_uci(func_buf6, uci_get_buf6);
		//Recovery original pdns6 and sdns6 when link6 is set to be "1"	
		cli_set_uci(func_buf3, half_uci_get_buf3);
	}
	//IPv6 address is set by user
	else {
		//Get orig_ip6addr information
		strcpy(uci_get_buf7, cli_get_uci("network.lan.orig_ip6addr"));
	
		//Check whether the orig_ip6addr information is NULL -- factory default state
		if ( uci_get_buf7[0]==0 ) {
			if (Clilanipset.ipv6set==0){
				cliData->tokenLen-=1;
				tprintf("Invalid IPV6 address\n");
		  		return CLI_PARAMS_ERR;
		  	}
		  	if (Clilanipset.sublen6set==0) {
		  		cliData->tokenLen-=1;
				tprintf("Invalid IPV6 subnet prefix length\n");
		  		return CLI_PARAMS_ERR;
		  	}
		  	if (Clilanipset.gatewayv6set==0) {
		  		cliData->tokenLen-=1;
				tprintf("Invalid Gateway IPV6 address\n");
		  		return CLI_PARAMS_ERR;
		  	}
		}

		//Get IPV6 information
		if (Clilanipset.ipv6set==0)
			strcpy(uci_get_buf4, cli_get_uci(func_buf4));
		else
			strcpy(uci_get_buf4, Clilanipset.ipv6);
	
		if ( strcmp(uci_get_buf4, "")!=0 ) {
			//Write into network.lan.ip6addr and network.lan.orig_ip6addr
			cli_set_uci(func_buf4, uci_get_buf4);
			cli_set_uci("network.lan.orig_ip6addr", uci_get_buf4);
		}
		else{
			//Step 1. Get IPv6 address from network.lan.orig_ip6addr
			strcpy(uci_get_buf4, cli_get_uci("network.lan.orig_ip6addr"));
			//Step 2. Write into network.lan.ip6addr		
			cli_set_uci(func_buf4, uci_get_buf4);
		}
	
		//Get gatewayv6 information	
		if (Clilanipset.gatewayv6set==0)
			strcpy(uci_get_buf5, cli_get_uci(func_buf5));
		else
			strcpy(uci_get_buf5, Clilanipset.gatewayv6);
		//Write into network.lan.orig_ip6gw
		cli_set_uci(func_buf5, uci_get_buf5);
	
		//Write 0 into network.lan.ip6LinkLocalEn
		cli_set_uci(func_buf6, uci_get_buf6);

	}
}
		//handle absolute path --> sys ip dhcp 2 accept
		if ( strcmp(cliData->tokens[3].token, "2")==0 )
			cliData->tokenLen=cmdtreelevel;
		else
			cliData->tokenLen--;

		return CLI_OK;

	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}

/*****************************************************************
* NAME: cmdipsetexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipsetexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;
		
	landhcpsetbridge=-1;
	
	Clilanipset.ipset=0;
	Clilanipset.gatewayset=0;
	Clilanipset.maskset=0;
	Clilanipset.pdnsset=0;
	Clilanipset.sdnsset=0;

//Modify on 2010-10-29 for IPV6 relative fields
Clilanipset.link6set=0;		
Clilanipset.ipv6set=0;
Clilanipset.sublen6set=0;
Clilanipset.gatewayv6set=0;
Clilanipset.pdnsv6set=0;
Clilanipset.sdnsv6set=0;
	
	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}


/*-------------------------------------------------------------------------*/
/*                   CLI Command -- sys ipv6                               */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_ipv6set[]= {
//	{OPM_ALL,	"link6",	NULL,			cmdlink6,	"Use link-local address",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"ipaddr6",	NULL,			cmdipaddr6,	"IPv6 address",			"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"sublen6",	NULL,			cmdsublen6,	"IPV6 subnet prefix length",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"gateway6",	NULL,			cmdgateway6,	"IPv6 gateway",			"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"pdns6",	NULL,			cmdpdns6,	"IPv6 Primary dns",		"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"sdns6",	NULL,			cmdsdns6,	"IPv6 Secondary dns",		"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_ipv6set,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

/*****************************************************************
* NAME: cmdlink6
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdlink6(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.ip6LinkLocalEn";
T_CHAR func_buf1[128]="network.lan.ip6addr";
T_CHAR func_buf2[128]="network.lan.orig_ip6addr";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
	
		if (Clilanipset.link6set==0){
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		}
		else {
			strcpy(uci_get_buf, Clilanipset.link6);
			tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		}

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
		//Write into network.lan.ip6LinkLocalEn
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);

		strcpy(Clilanipset.link6, uci_set_buf);
		Clilanipset.link6set=1;
				
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdipaddr6
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipaddr6(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.ip6addr";
T_CHAR func_buf1[128]="network.lan.orig_ip6addr";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR* ip6addr;
T_CHAR* sublen6;
T_CHAR *del = "/";

	//Get link6 information
	if (Clilanipset.link6set==0)
		strcpy(uci_get_buf, cli_get_uci("network.lan.ip6LinkLocalEn"));
	else
		strcpy(uci_get_buf, Clilanipset.link6);
		
	//If Link-Local Address is enabled, please disable Link-Local Address first
	if( atoi(uci_get_buf) == 1 ){
		printf(" Link-Local Address is enabled, please disable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}
	
	if(cliData->argc==0){
	
		if (Clilanipset.ipv6set==0){
			strcpy(uci_get_buf, cli_get_uci(func_buf));			
			ip6addr = strtok(uci_get_buf, del);
			if ( ip6addr != NULL )			
				tprintf("Current setting: %s\n", ip6addr);
			else
				tprintf("Current setting: %s\n", "None");
			tprintf("Recognized input format:  IPv6 address   EX: 8E4A::4B\n");
		}
		else{
			strcpy(uci_get_buf, Clilanipset.ipv6);
			ip6addr = strtok(uci_get_buf, del);
			tprintf("Current setting: %s\n", ip6addr);
			tprintf("Recognized input format:  IPv6 address   EX: 8E4A::4B\n");
		}
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		

		if (!errorcheckValidIPv6( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		//Get the IPv6 Subnet Prefix Length
		if (Clilanipset.ipv6set==0)
			strcpy(uci_get_buf, cli_get_uci(func_buf));
		else
			strcpy(uci_get_buf, Clilanipset.ipv6);

		//Check whether IPV6 address is NULL or not
		if (uci_get_buf[0] == 0)
			//Append the default length 32 into IPv6 address
			strcat(uci_set_buf , "/32");
		else {	
			sublen6 = strtok(uci_get_buf, del);
			sublen6 = strtok(NULL, del);
			//Append the length into IPv6 address
			strcat(uci_set_buf , "/");
			strcat(uci_set_buf , sublen6);
		}

		strcpy(Clilanipset.ipv6, uci_set_buf);
		Clilanipset.ipv6set=1;
				
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsublen6
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsublen6(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.ip6addr";
T_CHAR func_buf1[128]="network.lan.orig_ip6addr";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR* sublen6;
T_CHAR* ip6addr;
const T_CHAR* del = "/";

	//Get link6 information
	if (Clilanipset.link6set==0)
		strcpy(uci_get_buf, cli_get_uci("network.lan.ip6LinkLocalEn"));
	else
		strcpy(uci_get_buf, Clilanipset.link6);
		
	//If Link-Local Address is enabled, please disable Link-Local Address first
	if( atoi(uci_get_buf) == 1 ){
		printf(" Link-Local Address is enabled, please disable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){
		if (Clilanipset.ipv6set==0)
			strcpy(uci_get_buf, cli_get_uci(func_buf));
		else
			strcpy(uci_get_buf, Clilanipset.ipv6);
		
		if ( uci_get_buf[0] != 0 ) {
				
			tprintf("Current setting: %s (0-128)\n", sublen6);
		}
		else
			tprintf("Current setting: %s (0-128)\n", "None");
		

    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		

		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
		
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 128, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		//Get IPv6 address from network.lan.ip6addr
		if (Clilanipset.ipv6set==0)
			strcpy(uci_get_buf, cli_get_uci(func_buf));
		else
			strcpy(uci_get_buf, Clilanipset.ipv6);
			
		ip6addr = strtok(uci_get_buf, del);

		//Append the length into IPv6 address
		strcat(ip6addr , "/");
		strcat(ip6addr , uci_set_buf);
		
		strcpy(Clilanipset.ipv6, ip6addr);
		Clilanipset.ipv6set=1;
		Clilanipset.sublen6set=1;
				
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdgateway6
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdgateway6(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.ip6gw";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	//Get link6 information
	if (Clilanipset.link6set==0)
		strcpy(uci_get_buf, cli_get_uci("network.lan.ip6LinkLocalEn"));
	else
		strcpy(uci_get_buf, Clilanipset.link6);
		
	//If Link-Local Address is enabled, please disable Link-Local Address first
	if( atoi(uci_get_buf) == 1 ){
		printf(" Link-Local Address is enabled, please disable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){

		if (Clilanipset.gatewayv6set==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  IPv6 address   EX: 8E4A::4B\n");
		}
		else{
			strcpy(uci_get_buf, Clilanipset.gatewayv6);
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  IPv6 address   EX: 8E4A::4B\n");
		}
			
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		
		//Modify on 2012-08-01 to avoid segmentation fault when the length of input > 128
		//strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		if (!errorcheckValidIPv6( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		//Write into network.lan.ip6gw
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		strcpy(Clilanipset.gatewayv6, uci_set_buf);
		Clilanipset.gatewayv6set=1;

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdpdns6
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpdns6(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.dns";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
const char *del = " ";
T_CHAR* pdns;
char dns[128];
char* dns1, * dns2, * dns3, * dns4;

T_INT32 operationeMode=current_opmode;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//Get link6 information
	if (Clilanipset.link6set==0)
		strcpy(uci_get_buf, cli_get_uci("network.lan.ip6LinkLocalEn"));
	else
		strcpy(uci_get_buf, Clilanipset.link6);
		
	//If Link-Local Address is enabled, please disable Link-Local Address first
	if( atoi(uci_get_buf) == 1 ){
		printf(" Link-Local Address is enabled, please disable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){
		
		if (Clilanipset.pdnsv6set==0) {
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			pdns = strtok(uci_get_buf, del);
			pdns = strtok(NULL, del);
			pdns = strtok(NULL, del);
			if ( pdns != NULL )
				tprintf("Current setting: %s\n", pdns);
			else
				tprintf("Current setting: NULL\n");
			tprintf("Recognized input format:  IPv6 address   EX: 8E4A::4B\n");
		}
		else{
			strcpy(uci_get_buf, Clilanipset.pdnsv6);
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  IPv6 address   EX: 8E4A::4B\n");	
		}

    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		

		if (!errorcheckValidIPv6( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		//set value into configuration file if operationeMode is CR or AR		
		if ( (operationeMode==OPM_CBRT || operationeMode==OPM_AR) ){
			//Get DNS from network.lan.dns and Combine DNS
			strcpy(uci_get_buf, cli_get_uci(func_buf));
	
			dns1 = strtok(uci_get_buf, del);
			dns2 = strtok(NULL, del);
			dns3 = strtok(NULL, del);
			dns4 = strtok(NULL, del);

			//Combine DNS
			if ( dns4 != NULL )
				sprintf(dns, "%s %s %s %s", dns1, dns2, uci_set_buf, dns4);
			else
				sprintf(dns, "%s %s %s", dns1, dns2, uci_set_buf);

			//Write DNS into network.lan.dns
			cli_set_uci(func_buf, dns);	
		}
		//set value into Clilanipset Table if operationeMode is not CR or AR
		else{
			strcpy(Clilanipset.pdnsv6, uci_set_buf);
			Clilanipset.pdnsv6set=1;
		}	

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsdns6
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsdns6(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.dns";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
const T_CHAR *del = " ";
T_CHAR* sdns;
char dns[128];
char* dns1, *dns2, *dns3;

T_INT32 operationeMode=current_opmode;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	//Get link6 information
	if (Clilanipset.link6set==0)
		strcpy(uci_get_buf, cli_get_uci("network.lan.ip6LinkLocalEn"));
	else
		strcpy(uci_get_buf, Clilanipset.link6);
		
	//If Link-Local Address is enabled, please disable Link-Local Address first
	if( atoi(uci_get_buf) == 1 ){
		printf(" Link-Local Address is enabled, please disable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){
		if (Clilanipset.sdnsv6set==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			sdns = strtok(uci_get_buf, del);
			sdns = strtok(NULL, del);
			sdns = strtok(NULL, del);
			sdns = strtok(NULL, del);
			if ( sdns != NULL )
				tprintf("Current setting: %s\n", sdns);
			else
				tprintf("Current setting: NULL\n");
			tprintf("Recognized input format:  IPv6 address   EX: 8E4A::4B\n");
		}
		else{
			strcpy(uci_get_buf, Clilanipset.sdnsv6);
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  IPv6 address   EX: 8E4A::4B\n");
		}

    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		

		if (!errorcheckValidIPv6( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		//set value into configuration file if operationeMode is CR or AR
		if ( (operationeMode==OPM_CBRT || operationeMode==OPM_AR) ){
			//Get DNS from network.lan.dns
			strcpy(uci_get_buf, cli_get_uci(func_buf));
	
			dns1 = strtok(uci_get_buf, del);
			dns2 = strtok(NULL, del);
			dns3 = strtok(NULL, del);	

			if ( dns3 != NULL ) {
				//Combine DNS and write DNS into network.lan.dns
				sprintf(dns, "%s %s %s %s", dns1, dns2, dns3, uci_set_buf);
				cli_set_uci(func_buf, dns);
			}
			else {
				cliData->tokenLen-=2;
				tprintf("Invalid primary DNSV6 address\n");
	  			return CLI_PARAMS_ERR;
			}
		}
		//set value into Clilanipset Table if operationeMode is not CR or AR
		else{
			strcpy(Clilanipset.sdnsv6, uci_set_buf);
			Clilanipset.sdnsv6set=1;
		}	

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}


/*-------------------------------------------------------------------------*/
/*                   CLI Command -- sys stp                                */
/*-------------------------------------------------------------------------*/

//static CliEntry cli_table_stp[]= {
//	{OPM_ALL,	"stpstat",	NULL,		cmdstpstat,	"Spanning tree status",	"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"htime",	NULL,		cmdhtime,	"Bridge hello time",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"mage",		NULL,		cmdmage,	"Bridge max age",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"fdelay",	NULL,  		cmdfdelay,      "Bridge forward delay",	"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"prio",		NULL,		cmdprio, 	"Priority",		"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,   	"help",		cli_table_stp,	cmdHelp,	"Help",			"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,   	"exit",		NULL,		cmdexit,	"Exit",			"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

/*****************************************************************
* NAME: cmdstpstat
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdstpstat(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.stp";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:ON, 0:OFF)\n", uci_get_buf);
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
* NAME: cmdhtime
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdhtime(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.hellotime";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s seconds (1-10)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 10, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
* NAME: cmdmage
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmage(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.maxage";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s seconds (6-40)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 6, 40, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
* NAME: cmdfdelay
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdfdelay(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.fwdelay";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s seconds (4-30)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 4, 30, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
* NAME: cmdprio
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdprio(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.priority";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (0-65535)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 65535, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
* NAME: cmdSystemsave
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdSystemsave(T_VOID* priv, CliData* cliData)
{

  if(cliData->argc==0){
    printf("Called %s\n ",__func__);
  
    cliData->tokenLen--;
	return CLI_NOTHING;
  }else{
  
  	return CLI_NO_MATCH;
  }
}

/*****************************************************************
* NAME: getphywifi
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_INT32 getphywifi(T_CHAR* radio_flag){

	if ( (strcmp(model_name, "ap200")==0 || strcmp(model_name, "eap600")==0 || strcmp(model_name, "all02860nd")==0 || strcmp(model_name, "eap600true")==0 || strcmp(model_name, "ecb600")==0 || strcmp(model_name, "all02880nd")==0) ){
		if ( strcmp(radio_flag, "2.4G")==0 )
			return 1;
		if ( strcmp(radio_flag, "5G")==0 )
			return 0;
	}
	else{
		if ( strcmp(radio_flag, "2.4G")==0 )
			return 0;
		if ( strcmp(radio_flag, "5G")==0 )
			return 1;
	}
}





/*****************************************************************
* NAME: cmdSystemsyslog
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdSystemsyslog(T_VOID* priv, CliData* cliData)
{
int ret;
T_CHAR buf[1024];
//    printf("Called %s\n",__func__);
  cliData->tokenLen--;

//printf("Please enter syslog name: ");
//scanf("%s", buf);
ret = cmdedit_read_input("Please enter syslog name: ", buf);
//printf("cmdSystemsyslog ret=%d\n", ret);
//printf("cmdSystemsyslog buf=%s\n", buf);
	return CLI_NOTHING;
}

/*****************************************************************
* NAME: cmdSystemconn
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdSystemconn(T_VOID* priv, CliData* cliData)
{

  if(cliData->argc==0){
    printf("Called %s\n ",__func__);
  
    cliData->tokenLen--;
	return CLI_NOTHING;
  }else{
  
  	return CLI_NO_MATCH;
  }
}

/*****************************************************************
* NAME: cmdSystemdhcpcli
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdSystemdhcpcli(T_VOID* priv, CliData* cliData)
{

  if(cliData->argc==0){
    printf("Called %s\n ",__func__);
  
    cliData->tokenLen--;
	return CLI_NOTHING;
  }else{
  
  	return CLI_NO_MATCH;
  }
}

/*****************************************************************
* NAME: cmdsystime
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsystime(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){
		
		system("date");
		printf("\n");		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}


/*****************************************************************
* NAME: cmdfwversion
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdfwversion(T_VOID* priv, CliData* cliData)
{
T_CHAR buf[128];
FILE* fp;


	if(cliData->argc==0){
/*
		system("cat /etc/version_ui > /dev/null 2>&1 > /tmp/fwversion");
		if((fp = fopen("/tmp/fwversion", "r"))!=NULL){
printf("1\n");
	fgets(buf,sizeof(buf),fp);
	fclose(fp);
	buf[strlen(buf)-1]='\0';
	
	printf("%s\n", buf);		

    			cliData->tokenLen--;
			return CLI_NOTHING;

		}
		else{
printf("2\n");
			system("cat /etc/version | awk -F \".\" \'{print $1\".\"$2\".\"$3}\'");
			printf("\n");	
    			cliData->tokenLen--;
			return CLI_NOTHING;

		
		}


*/		
		system("cat /etc/version | awk -F \".\"cmdfwversion \'{print $1\".\"$2\".\"$3}\'");
		printf("\n");	
    		cliData->tokenLen--;
		return CLI_NOTHING;

	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}

/*****************************************************************
* NAME: cmdethermac
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdethermac(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){
		
		system("ifconfig eth0 | grep HWaddr | awk \'{print $5}\'");
		printf("\n");	
    		cliData->tokenLen--;
		return CLI_NOTHING;

	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}

/*****************************************************************
* NAME: cmdSystemTimeInfo
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdSystemTimeInfo(T_VOID* priv, CliData* cliData)
{
	T_CHAR tok[40];
	T_INT32 i;
T_CHAR final_value[80];
#if 0 //cfho 2008-0515 TODO
	sysTzCheck();
	sysTzSet();
#endif

	tprintf(CLI_BODY_TITLE, "Time");
	//test=sysGetLocaltimeByItem('a');
	strcpy(final_value,sysGetLocaltimeByItem('a'));	
	tprintf(CLI_BODY_STR_CONTEXT, "Local Date Time", final_value); /*sysGetLocaltimeByItem('a')*/
	tprintf(CLI_BODY_STR_CONTEXT, "NTP Status", apCfgGetItemText("ntpclient.@ntpclient[0].NTPSrvMode"));

	tprintf(CLI_BODY_TITLE, "Time Zone Setting");
	tprintf(CLI_BODY_STR_CONTEXT, "Time Zone", apCfgGetItemText("system.@system[0].timezone"));
	tprintf(CLI_BODY_STR_CONTEXT, "Day Saving", NULL);

	tprintf(CLI_BODY_TITLE, "NTP Setting");
#if NUM_NTP_SERVER > 1
	tprintf(CLI_BODY_STR_CONTEXT, "Polling Time", apCfgGetItemText(NTP_POLLIING_TIME_TOK));
#endif

tprintf(CLI_BODY_STR_CONTEXT, "Server IP", apCfgGetItemText("ntpclient.@ntpserver[0].hostname"));
#if 0
	for (i = 1; i <= NUM_NTP_SERVER; ++i)
	{
		sprintf(tok,"%s%d",NTP_SERVER_TOK, i);

		tprintf("%19s%d: %s\n", "Server", i, apCfgGetStrValue(tok));
	}
#endif
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSystemTimeRtcDate
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-04-03
* Modify:   
****************************************************************/
#if HAS_HW_RTC
CliStatus cmdSystemTimeRtcDate(T_VOID* priv, CliData* cliData)
{
	const T_CHAR *p_year, *p_mon, *p_day;
	T_INT32 i_year, i_mon, i_day;

	if (cliData->argc==0)
	{
		tprintf("Date: %s", sysGetLocaltimeByItem('y'));
		tprintf("/%s", sysGetLocaltimeByItem('m'));
		tprintf("/%s\n", sysGetLocaltimeByItem('d'));
		return CLI_CURRENT_OK;
	}

	if (cliData->argc != 3)
	{
		return CLI_PARAMS_ERR;
	}
	p_year = getNextToken(cliData, 0);
	p_mon = getNextToken(cliData, 1);
	p_day = getNextToken(cliData, 2);

	i_year = atoi(p_year);
	i_mon = atoi(p_mon);
	i_day = atoi(p_day);

	if (i_mon > 0 && i_mon <= 12 && i_day > 0 && i_day <= 31 && i_year >= 1900)
	{
#if TARGET
		systimeSetDate(i_year, i_mon, i_day);
#endif
		tprintf("Set Date: %04d/%02d/%02d\n", i_year, i_mon, i_day);
	}
	else
	{
		return CLI_PARAMS_ERR;
	}

	return CLI_NOTHING;
}
#endif
/*****************************************************************
* NAME: cmdSystemTimeRtcTime
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-04-03
* Modify:   
****************************************************************/
#if HAS_HW_RTC
CliStatus cmdSystemTimeRtcTime(T_VOID* priv, CliData* cliData)
{
    /*2009-0713 remove second setting*/
	const T_CHAR *p_hour, *p_minute;
	T_INT32 i_hour, i_minute;

	p_hour = getNextToken(cliData, 0);
	p_minute = getNextToken(cliData, 1);
	//p_sec = getNextToken(cliData, 2);

	if (cliData->argc==0)
	{
		tprintf("Time: %s", sysGetLocaltimeByItem('h'));
		tprintf(":%s\n", sysGetLocaltimeByItem('i'));
		return CLI_CURRENT_OK;
	}
	if (cliData->argc != 2)
	{
		return CLI_PARAMS_ERR;
	}

	i_hour = atoi(p_hour);
	i_minute = atoi(p_minute);

	if (i_hour >= 0 && i_hour <= 24 && i_minute >= 0 && i_minute <= 59)
	{
#if TARGET
		systimeSetTime(i_hour, i_minute);
#else
		tprintf("Set Time: %02d:%02d\n", i_hour, i_minute);
#endif
	}
	else
	{
		return CLI_PARAMS_ERR;
	}

	return CLI_NOTHING;
}
#endif
/*****************************************************************
* NAME: cmdSystemAdminInfo
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
#if HTTPD_REMOTEPORT_FUNCTION
CliStatus cmdSystemAdminInfo(T_VOID* priv, CliData* cliData)
{
	tprintf(CLI_BODY_TITLE, "Idle Time Setting");
	tprintf(CLI_BODY_STR_CONTEXT, "Idle Time Out", apCfgGetStrValue(HTTP_REMOTE_IDLETIME_TOK));

	tprintf(CLI_BODY_TITLE, "Remote Management");
	tprintf(CLI_BODY_STR_CONTEXT, "Status", apCfgGetItemText(HTTP_REMOTE_ENABLE_TOK));
	tprintf(CLI_BODY_STR_CONTEXT, "IP", apCfgGetItemText(HTTP_REMOTE_IPADDR_TOK));
#if 0 // USE HTTP_REMOTE_ENABLE_TOK replace
	tprintf(CLI_BODY_STR_CONTEXT, "Allow Access From WAN", apCfgGetItemText(HTTP_ACCESS_FROM_WAN_TOK));
#endif
	return CLI_NOTHING;
}
#endif
/*****************************************************************
* NAME: cmdSystemAdminChangePw
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdSystemAdminChangePw(T_VOID* priv, CliData* cliData)
{
	T_CHAR buf[128];
	T_CHAR pw[128];

	tprintf("Current Password: ");

	if (getStdInCommand(buf, sizeof(buf)))
	{
		if (strcmp(buf, apCfgGetStrValue(HTTP_REMOTE_PW_TOK))!=0)
		{
			tprintf("Sorry, Password Error!\n");
			return CLI_NOTHING;
		}
	}

	tprintf("New Password: ");
	getStdInCommand(pw, sizeof(pw));

	tprintf("Re-type Password: ");
	getStdInCommand(buf, sizeof(buf));

	if (strcmp(buf, pw) == 0)
	{
		apCfgSetValueByStr(HTTP_REMOTE_PW_TOK, pw);
		return CLI_OK;
	}
	else
	{
		tprintf("Sorry, Password Error!\n");
		return CLI_NOTHING;
	}
}
/*****************************************************************
* NAME: __schListCount
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay            2007-04-03
* Modify:   Norkay            2007-04-10
****************************************************************/
static T_INT32 __schListCount(T_VOID)
{
	return apCfgGetStructListCount(SCHEDULE_TOK, MAX_SCHEDULE_LIST);
}
/*****************************************************************
* NAME: __schListShow
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay            2007-04-03
* Modify:   Norkay            2007-04-10
****************************************************************/
T_INT32 __schListShow(T_VOID)
{
	return getApCfgStructureListShow("Schedule List", SCHEDULE_TOK, MAX_SCHEDULE_LIST);
}
/*****************************************************************
* NAME: __schListEdit
* ---------------------------------------------------------------
* FUNCTION: edit schedule 
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-04-02
* Modify:   
****************************************************************/
static T_VOID __schListEdit(schedule_t *schedule)
{
	T_UINT32 starthr, startmm, endhr, endmm;
	T_UINT32 i;
	T_CHAR buf[128];
    unsigned int service=0x0;
	int enable_pwr=1;

	tprintf("Description(Max %d Characters): [%s] ", MAX_SCHED_DES, schedule->cSchDes);

	if (getStdInCommand(buf, MAX_SCHED_DES))
	{
		strcpy(schedule->cSchDes, buf);
	}

	if(enable_pwr)
	{
		service |= 0x1<<SERVICE_POWER_SAVING;
	}
	schedule->type=service;
	tprintf("Service : Power Saving\n");

	tprintf("Is All Day(y or n)? [%s] ", schedule->bAlways ? "y" : "n");
	if (getStdInCommand(buf, sizeof(buf)))
	{
		if (strcmp(buf, "YES")==0 || strcmp(buf, "yes")==0 || strcmp(buf, "y")==0 || strcmp(buf, "Y")==0)
		{
			schedule->bAlways = 1;
		}
		else
		{
			schedule->bAlways = 0;
		}
	}

	if (schedule->bAlways == 0)
	{
		tprintf("From(xx:xx): [%02d:%02d] ", schedule->starthr, schedule->startmm);
		if (getStdInCommand(buf, sizeof(buf)))
		{
			sscanf(buf, "%d:%d", &starthr, &startmm);
			schedule->starthr = starthr;
			schedule->startmm = startmm;
		}

		tprintf("To(xx:xx): [%02d:%02d] ", schedule->endhr, schedule->endmm);
		if (getStdInCommand(buf, sizeof(buf)))
		{
			sscanf(buf, "%d:%d", &endhr, &endmm);
			schedule->endhr = endhr;
			schedule->endmm = endmm;
		}
	}
	tprintf("Day Mask:\n");

	for (i=0; i<SCHEDULE_DAY_MASK_SIZE;++i)
	{
		tprintf("%s(y or n)? [%s] ", dayMask[i].dstr, (schedule->daysmask & dayMask[i].mask) ? "y" : "n");
		if (getStdInCommand(buf, sizeof(buf)))
		{
			if (strcmp(buf, "YES")==0 || strcmp(buf, "yes")==0 || strcmp(buf, "y")==0 || strcmp(buf, "Y")==0)
			{
				schedule->daysmask |= dayMask[i].mask;
			}
			else
			{
				schedule->daysmask &= ~dayMask[i].mask;
			}
		}
	}

	return;
}
/*****************************************************************
* NAME: cmdSystemSchList
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdSystemSchList(T_VOID* priv, CliData* cliData)
{
	T_CHAR tok[40];
	T_INT32 i;

	tprintf(CLI_BODY_TITLE, "Schedule List");

	if (__schListCount() == 0)
	{
		tprintf(CLI_LIST_EMPTY, "Schedule List");
		return CLI_NOTHING;
	}
	tprintf(SYS_SCH_DESCRIP);
	tprintf(CLI_BODY_HR);
	for (i = 1; i <= MAX_SCHEDULE_LIST; i++)
	{
		sprintf(tok,"%s%d",SCHEDULE_TOK, i);

		if (apCfgGetFirstByte(tok))
		{
			schedule_t schedule;

			apCfgGetValue(tok, &schedule);
			tprintf(SYS_SCH_PATTERN, i, schedule.cSchDes, scheduleGetDescription(schedule)); 
		}
	}
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSystemSchNew
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-0402
* Modify:   
****************************************************************/
CliStatus cmdSystemSchNew(T_VOID* priv, CliData* cliData)
{
	T_CHAR tok[40];
	T_INT32 i;

	if (cliData->argc > 0)
	{
		return CLI_PARAMS_ERR;
	}

	if (__schListCount() == MAX_SCHEDULE_LIST)
	{
		tprintf(CLI_LIST_NEW_FULL, "Schedule List");
		return CLI_NOTHING;
	}
	for (i = 1; i <= MAX_SCHEDULE_LIST; i++)
	{
		sprintf(tok,"%s%d",SCHEDULE_TOK, i);

		if (apCfgGetFirstByte(tok)==0)
		{
			schedule_t schedule;

			apCfgGetValue(tok, &schedule);
			scheduleLoadDefault(&schedule, i);
			schedule.isEnable = STATUS_EDIT;
			__schListEdit(&schedule);
			schedule.isEnable = STATUS_ENABLE;
			if (apCfgSetValue(tok, &schedule))
			{
				tprintf(SYS_SCH_DESCRIP);
				tprintf(CLI_BODY_HR);
				tprintf(SYS_SCH_PATTERN, i, schedule.cSchDes, scheduleGetDescription(schedule)); 
				return CLI_OK;
			}
			else
			{
				return CLI_PARAMS_ERR;
			}
		}
	}
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSystemSchEdit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-0402
* Modify:   
****************************************************************/
CliStatus cmdSystemSchEdit(T_VOID* priv, CliData* cliData)
{
	const T_CHAR* idxStr;
	T_INT32 idx;

	idxStr = getNextToken(cliData, 0);
	idx = atoi(idxStr);

	if (cliData->argc==0)
	{
		T_CHAR buf[40];

		__schListShow();
		tprintf(CLI_LIST_EDIT_QUESTION);
		getStdInCommand(buf, sizeof(buf));
		idx = atoi(buf);
	}

	if (cliData->argc > 1)
	{
		return CLI_PARAMS_ERR;
	}

	if (idx > 0 && idx <= MAX_SCHEDULE_LIST)
	{
		T_CHAR tok[40];

		sprintf(tok,"%s%d",SCHEDULE_TOK, idx);

		if (apCfgGetFirstByte(tok))
		{
			schedule_t schedule;

			apCfgGetValue(tok, &schedule);
			tprintf(SYS_SCH_DESCRIP);
			tprintf(CLI_BODY_HR);
			tprintf(SYS_SCH_PATTERN, idx, schedule.cSchDes, scheduleGetDescription(schedule));
			schedule.isEnable = STATUS_EDIT;
			__schListEdit(&schedule);
			schedule.isEnable = STATUS_ENABLE;
			if (apCfgSetValue(tok, &schedule))
			{
				tprintf(SYS_SCH_DESCRIP);
				tprintf(CLI_BODY_HR);
				tprintf(SYS_SCH_PATTERN, idx, schedule.cSchDes, scheduleGetDescription(schedule)); 
				return CLI_OK;
			}
			else
			{
				return CLI_PARAMS_ERR;
			}
		}
	}
	tprintf(CLI_LIST_NOT_EXISTED, "Schedule", idx);
	return CLI_NOTHING;
}

/*****************************************************************
* NAME: cmdSystemSchDelete
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-0402
* Modify:   Norkay            2007-05-08
****************************************************************/
CliStatus cmdSystemSchDelete(T_VOID* priv, CliData* cliData)
{
	const T_CHAR* idxStr;
	T_INT32 idx;

	idxStr = getNextToken(cliData, 0);
	idx = atoi(idxStr);

	if (cliData->argc==0)
	{
		T_CHAR buf[40];

		__schListShow();
		tprintf(CLI_LIST_DELETE_QUESTION);
		getStdInCommand(buf, sizeof(buf));
		idx = atoi(buf);
	}
#if 0
	// protect 1th schedule
	if (idx == 1)
	{
		tprintf(CLI_LIST_DELETE_REJECT, "Schedule");
		return CLI_NOTHING;
	}
#endif
	if (cliData->argc > 1)
	{
		return CLI_PARAMS_ERR;
	}

	if (idx >= 1 && idx <= MAX_SCHEDULE_LIST)
	{
		T_CHAR tok[40];

		sprintf(tok,"%s%d",SCHEDULE_TOK, idx);
		if (apCfgGetFirstByte(tok))
		{
			schDoDelete(idx);
			tprintf(CLI_LIST_DELETE_OK, "Schedule", idx);
			return CLI_OK;
		}
	}
	tprintf(CLI_LIST_NOT_EXISTED, "Schedule", idx);

	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSystemNtpServer
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdSystemNtpServer(T_VOID* priv, CliData* cliData)
{
	tprintf(CLI_BODY_TITLE, "NTP Server");
	tprintf(CLI_BODY_STR_CONTEXT, "Status", apCfgGetItemText(NTP_SERVER_ENABLE_TOK));

	return CLI_NOTHING;
}

/*****************************************************************
* NAME: checkFwUpgradeStatus
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
T_VOID checkFwUpgradeStatus(T_VOID)
{
	T_INT32 i, ifwupgResult;
	for(i=0;i<10;i++)
	{
		sleep(10);
		apCfgGetValue(SYSTEM_INFO_FWUPG_TOK, &(ifwupgResult));
		tprintf("{%s}...\n", apcfgGetFwmStatusInText(ifwupgResult));
		if(ifwupgResult & SI_FWUPG_ERROR || ifwupgResult & SI_FWUPG_OK)
		{
			tprintf("Please reboot the system manually.\n");
			break;
		}
	}
	return;
}
/*****************************************************************
* NAME: cmdSysFwInfo
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdSysFwInfo(T_VOID* priv, CliData* cliData)
{
	tprintf(CLI_BODY_TITLE, "Current Firmware infomation");
#if HAS_SHOW_ONE_VERSION
	tprintf("%20s: %s (%s)\n", "Firmware Version", APPS_CODE_VERSION__, APPS_CODE_DATE__);
#else
	tprintf("%20s: %s (%s)\n", "Kernel Version", KNL_CODE_VERSION__, KNL_CODE_DATE__);
	tprintf("%20s: %s (%s)\n", "BasicApps Version", KNLAPPS_CODE_VERSION__, KNLAPPS_CODE_DATE__);
	tprintf("%20s: %s (%s)\n", "Apps Version", APPS_CODE_VERSION__, APPS_CODE_DATE__);
#endif
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSysFtpUpgrade
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdSysFtpUpgrade(T_VOID* priv, CliData* cliData)
{
	const T_CHAR *serverIp, *port, *userName, *password, *fileName;

	/*ip value*/
	serverIp = getNextToken(cliData, 0);
	/*port file name*/
	port = getNextToken(cliData, 1);
	/*user name*/
	userName = getNextToken(cliData, 2);
	/*password*/
	password = getNextToken(cliData, 3);
	/*file name*/
	fileName = getNextToken(cliData, 4);

	//tprintf("%s %s %s %s %s\n", serverIp, port, userName, password, fileName);
	if (cliData->argc==0)
	{
		cmdSysFwInfo(priv, cliData);
		return CLI_CURRENT_OK;
	}

	if (cliData->argc != 5)
	{
		return CLI_PARAMS_ERR;
	}

	if (apCfgTestTextValue(TYPE_IP, serverIp) && apCfgTestTextValue(TYPE_PORT, port))
	{
		tprintf("ftp downloading file %s from %s, please wait...\n", fileName, serverIp);

		apCfgSetValueByStr(FTP_HOST_TOK, serverIp);
		apCfgSetIntValue(FTP_PORT_TOK,atoi(port));
		apCfgSetValueByStr(FTP_USERID_TOK, userName);
		apCfgSetValueByStr(FTP_USERPWD_TOK, password);
		apCfgSetValueByStr(FTP_FILENAME_TOK, fileName);
#if TARGET
		system("sysconf_cli fwupg ftp");
#endif
		checkFwUpgradeStatus();
	}
	else
	{
		return CLI_PARAMS_ERR;
	}

	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSysConfRestoreDefault
* ---------------------------------------------------------------
* FUNCTION: Restore factory default configuration
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-0402
* Modify:   
****************************************************************/
CliStatus cmdSysConfRestoreDefault(T_VOID* priv, CliData* cliData)
{
	T_CHAR buf[40];

	tprintf("Do you want to restore factory default configuration?\n");
	tprintf("Please comfirm (y or n): ");

	getStdInCommand(buf, sizeof(buf));
	if (strcmp(buf, "YES")==0 || strcmp(buf, "yes")==0 || strcmp(buf, "y")==0 || strcmp(buf, "Y")==0)
	{

		tprintf("Reset to default and reboot, please wait ");
#if TARGET
		SYSTEM("sysconf_cli restore2def &");
#endif
	}
	return CLI_NOTHING;
}
#ifdef WAN_DEV /* cfho 2008-1226 */
/*****************************************************************
* NAME: cmdSystemStatusWan
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-0403
* Modify:   
****************************************************************/
CliStatus cmdSystemStatusWan(T_VOID* priv, CliData* cliData)
{
	tprintf(CLI_BODY_TITLE, "WAN");
	tprintf(CLI_BODY_STR_CONTEXT, "IP", getWanIP());
	tprintf(CLI_BODY_STR_CONTEXT, "MAC Address", getWanMac());
	tprintf(CLI_BODY_STR_CONTEXT, "Subnet Mask", getWanMask());
	tprintf(CLI_BODY_STR_CONTEXT, "DNS Address", getWanDNS());
	tprintf(CLI_BODY_STR_CONTEXT, "Gateway address", getWanGateway());
	tprintf(CLI_BODY_STR_CONTEXT, "WAN mode", apCfgGetItemText(WAN_CONNECTION_TYPE_TOK));

	return CLI_NOTHING;
}
#endif
/*****************************************************************
* NAME: cmdSystemStatusLan
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-0403
* Modify:   
****************************************************************/
CliStatus cmdSystemStatusLan(T_VOID* priv, CliData* cliData)
{
	tprintf(CLI_BODY_TITLE, "LAN");
	tprintf(CLI_BODY_STR_CONTEXT, "IP", getLanIP());
	tprintf(CLI_BODY_STR_CONTEXT, "MAC Address", getLanMac());
	tprintf(CLI_BODY_STR_CONTEXT, "Subnet Mask", getLanMask());
	tprintf(CLI_BODY_STR_CONTEXT, "DHCP Server", apCfgGetItemText(DHCPD_ENABLE_TOK));
	tprintf(CLI_BODY_STR_CONTEXT, "WLAN SSID", apCfgGetStrValue(WLAN11G_SSID_TOK));
	tprintf(CLI_BODY_STR_CONTEXT, "WLAN MAC Address", getWlanMac());
	tprintf(CLI_BODY_STR_CONTEXT, "WLAN Mode", apCfgGetItemText(WLAN11G_MODE_TOK));
	tprintf(CLI_BODY_STR_CONTEXT, "WLAN Channel", apCfgGetStrValue(WLAN11G_CHANNEL_TOK));

	return CLI_NOTHING;
}
#if defined(FOR_EG_EOR7550)
/*****************************************************************
* NAME: SystemStatusEORWlanshow
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Joey 2007-1015
* Modify:   
****************************************************************/
CliStatus SystemStatusEORWlanshow(T_INT32 radioIdx, T_INT32 radioMode)
{
	char status[40]={0};
	char prefix[40]={0};
	char strTmp[40]={0};
	int i,ssidNum;

	strcpy(prefix,(radioIdx==1)?ATH_TOK:WLAN_TOK);
	if (radioMode==RADIO_OPM_CB||radioMode==RADIO_OPM_REPEATER_STA)	 //CB or CR mode
	{
		sysWlanStatus_t stat;

		memset(&stat, 0, sizeof(stat));
		sysGetWlanStatus(((strcmp(prefix,ATH_TOK)==0)?ATH_DEV:WLAN_G_DEV), &stat);
		strcpy(status,(strcmp((char *)sysWlanGetState(),"COMPLETED")==0)?"Successful":"Fail");
		tprintf(CLI_BODY_STR_CONTEXT, "Connection Status", status);
		tprintf(CLI_BODY_STR_CONTEXT, "ESSID", strcmp(status,"Fail")==0?"---":sysWlanGetSsid());
		tprintf(CLI_BODY_STR_CONTEXT, "BSSID", strcmp(status,"Fail")==0?"---":sysWlanGetBssid());
	}
	else	//other mode will show 1~4 ssid but wds mode only has one ssid 
	{
		ssidNum=(strcmp(prefix,ATH_TOK)==0)?ATH_WLAN_SSID_NUM:WLAN_SSID_NUM;
		tprintf(CLI_BODY_STR_CONTEXT, "Channel", apCfgGetStrValue("%s%d"_CHANNEL_TOK,prefix,1));
		for (i=1;i<=ssidNum;i++)
		{
			if (radioMode==RADIO_OPM_WDSB||radioMode==RADIO_OPM_WDSR)
			{
				tprintf(CLI_BODY_TITLE, "SSID_1");
				tprintf(CLI_BODY_STR_CONTEXT, "ESSID", apCfgGetStrValue("%s%s%d", prefix, 1, _SSID_TOK));
				tprintf(CLI_BODY_STR_CONTEXT, "BSSID", (char *)getWlanxMac(1,(strcmp(prefix,ATH_TOK)==0)?ATH_WLAN_DEV:WLAN_DEV));
			}
			else
			{
				if (apCfgGetIntValue("%s%d"_ENABLE_TOK,prefix,i)==1)
				{
					sprintf(strTmp,"SSID_%d",i);
					tprintf(CLI_BODY_TITLE, strTmp);
					tprintf(CLI_BODY_STR_CONTEXT, "ESSID", apCfgGetStrValue("%s%d"_SSID_TOK,prefix,i));
					tprintf(CLI_BODY_STR_CONTEXT, "BSSID", (char *)getWlanxMac(i,(strcmp(prefix,ATH_TOK)==0)?ATH_WLAN_DEV:WLAN_DEV));
				}
			}

		}
	}

	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSystemStatusWlan
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Joey 2008-1015
* Modify:   
****************************************************************/
CliStatus cmdSystemStatusEORWlan(T_VOID* priv, CliData* cliData)
{
	int r1,r2;
	r1=apCfgGetIntValue(RADIO_1_OP_MODE_TOK);
	r2=apCfgGetIntValue(RADIO_2_OP_MODE_TOK);
	tprintf(CLI_BODY_TITLE, "WLAN");
	if (r1!=RADIO_OPM_DISABLE)
	{
		tprintf(CLI_BODY_TITLE, "Radio 1");
		SystemStatusEORWlanshow(1,r1);
	}
	if (r2!=RADIO_OPM_DISABLE)
	{
		tprintf(CLI_BODY_TITLE, "Radio 2");
		SystemStatusEORWlanshow(2,r2);
	}

	return CLI_NOTHING;
}
#endif
#if HAS_PBX
/*****************************************************************
* NAME: cmdSystemStatusPbx
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay	2007-04-03
* Modify:   
****************************************************************/
CliStatus cmdSystemStatusPbx(T_VOID* priv, CliData* cliData)
{
	FILE *fp;
	char buf[256];
	char fdisName[24];
	char fExt[24];
	char fStatus[24];

#if TARGET
	/*create sip status file*/
	SYSTEM("asterisk -r -x 'sip dump status'");
#endif

	fp = fopen(SIP_STATUS_FILE, "r");

	if (!fp)
	{
		return CLI_NOTHING;
	}
	tprintf(CLI_BODY_TITLE, "PBX");
	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		if (3 == sscanf(buf, "%s %s %s", fdisName, fExt, fStatus))
		{
			if (atoi(fExt)>0)
			{
				printf("%20s %s\n", fdisName, fStatus);
			}
		}
	}
	fclose(fp);

	return CLI_NOTHING;
}
#endif
/*****************************************************************
* NAME: cmdSystemStatusInfo
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-0403
* Modify:   Joey   2008-1015
****************************************************************/
CliStatus cmdSystemStatusInfo(T_VOID* priv, CliData* cliData)
{
	//FILE *fp;
    //char buf[30];
#if 0
    int firstByte,secondByte,thirdByte;

    char *p;
    
    p=sysGetKernelInfo(SYS_KERNEL_VERSION);

    if(p)
    {
        sscanf(p,"%d.%d.%d",&firstByte,&secondByte,&thirdByte);
    }else
    {
        printf("Err: %s: %s does not exist!\n", __FUNCTION__, KNLAPPVER_FILE);
    }
#endif
	tprintf(CLI_BODY_TITLE, "System Information");
	tprintf(CLI_BODY_STR_CONTEXT, "Operation Mode", (char *)apCfgGetEnumData(SYS_OP_MODE_TOK,apCfgGetIntValue(SYS_OP_MODE_TOK))->text);
	tprintf(CLI_BODY_STR_CONTEXT, "System Up Time", getSystemUpTimeText());
	tprintf(CLI_BODY_STR_CONTEXT, "Hardware Version", getHwVer());
	tprintf(CLI_BODY_STR_CONTEXT, "Serial Number", apCfgGetStrValue(SYS_SN_TOK));
	tprintf("%20s: %s \n", "Kernel Version", KNL_CODE_VERSION__);
	///tprintf("%20s: %d.%d.%d\n", "Kernel Version",firstByte,secondByte,thirdByte);
	tprintf(CLI_BODY_STR_CONTEXT, "Apps Version", sysGetFWVersion());
	

	return CLI_NOTHING;
}


#if defined(FOR_EG_EOR7550)
/*****************************************************************
* NAME: cmdEORSystemMode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   joey 2008-1002
* Modify:   
****************************************************************/
CliStatus cmdEORSystemMode(T_VOID* priv, CliData* cliData)
{
	int i;
	T_CHAR r1buf[128],r2buf[128],ethbuf[128];
	char sysmodeList[SYS_OPM_COUNT][50]={{0}};
	char nextRadio[MAX_RADIO_VALUE][50]={{0}};
	char ethList[MAX_ETH_PURPOSE][50]={{0}};
	int new_opmode,ret=CLI_OK;

	int old_opmode = apCfgGetIntValue(SYS_OP_MODE_TOK);
	int radio1_mode = apCfgGetIntValue(RADIO_1_OP_MODE_TOK);
	int radio2_mode = apCfgGetIntValue(RADIO_2_OP_MODE_TOK);
	int eth_purposed = apCfgGetIntValue(ETH_PURPOSE_TOK);

	for (i=0;i<SYS_OPM_COUNT;i++)
	{
		strcpy(sysmodeList[i],(char *)apCfgGetEnumData(SYS_OP_MODE_TOK,i)->text);
	}

	tprintf("%10s: \n", "Radio 1(11a/b/g)");
	showOption(RADIO_1_OP_MODE_TOK);
	tprintf(" --------------------------\n");
	tprintf("%10s: %d\n", "Old Value", radio1_mode);
	tprintf("%10s: ", "New Value");
	getStdInCommand(r1buf, sizeof(r1buf));

	parseRadioList(atoi(r1buf),nextRadio,ethList);
	tprintf("\n\n\n");
	tprintf("%10s: \n", "Radio 2(11b/g/n)");
	tprintf(" --------------------------\n");

	int msgLen=0,breakpt=0;
	get_terminal_width_height(0, &g_term_width, NULL);
	g_term_width = g_term_width > CLI_DEFAULT_WIDTH ? g_term_width : CLI_DEFAULT_WIDTH;
	for (i=0;i<MAX_RADIO_VALUE;i++)
	{
		if (strlen(nextRadio[i])!=0)
		{
			msgLen = tprintf("%s%d:%s", CLI_TITLE_SPACE, i, nextRadio[i]);
			breakpt=i;
			break;
		}
	}

	for (i=breakpt+1; i<MAX_RADIO_VALUE; ++i)
	{
		if (strlen(nextRadio[i])!=0)
		{
			if (msgLen + strlen(nextRadio[i]) > g_term_width-CLI_RESERVE_WIDTH)
			{
				// jump line --> msgLen > g_term_width-CLI_RESERVE_WIDTH 
				tprintf("\n");
				msgLen = tprintf("%s%d:%s", CLI_TITLE_SPACE, i, nextRadio[i]);
			}
			else
			{
				// add ", "
				msgLen += tprintf(", %d:%s", i, nextRadio[i]);
			}
		}
	}
	tprintf("\n");
	tprintf("%10s: %d\n", "Old Value", radio2_mode);
	tprintf("%10s: ", "New Value");
	getStdInCommand(r2buf, sizeof(r2buf));

	tprintf("\n\n\n");
	tprintf("%10s: \n", "Ethernet");
	tprintf(" --------------------------\n");
	parseRadioList(atoi(r2buf),nextRadio,ethList);
	if (strlen(ethList[0])!=0)
		tprintf("%s%d:%s", CLI_TITLE_SPACE, 0, ethList[0]);
	if (strlen(ethList[1])!=0)
		tprintf(", %d:%s", 1, ethList[1]);
	tprintf("\n%10s: %d\n", "Old Value", eth_purposed);
	tprintf("%10s: ", "New Value");
	getStdInCommand(ethbuf, sizeof(ethbuf));
	if (!apCfgSetValueByStr(RADIO_1_OP_MODE_TOK,r1buf))
	{
		tprintf("Set radio 1 value ERROR!\n");
		ret=CLI_PARAMS_ERR;
	}
	if (!apCfgSetValueByStr(RADIO_2_OP_MODE_TOK,r2buf))
	{
		tprintf("Set radio 2 value ERROR!\n");
		ret=CLI_PARAMS_ERR;
	}
	if (!apCfgSetValueByStr(ETH_PURPOSE_TOK,ethbuf))
	{
		tprintf("Set ethernet type value ERROR!\n");
		ret=CLI_PARAMS_ERR;
	}
	if (ret == CLI_OK)
	{

		new_opmode = Radio2SysOpmode();
		if (old_opmode != new_opmode)
		{
			//apCfgSetIntValue(SYS_ROUTE_ENABLE_TOK, (new_opmode==0||new_opmode==4)?1:0);
			//setMultipleRadioSysOperationMode();

			tprintf("\n Attention: This device will change from [%s] to [%s] \n \n",sysmodeList[old_opmode],sysmodeList[new_opmode]);
			tprintf("**********************************************************************\n");
			tprintf("*                                                                    *\n");
			tprintf("* You should reboot the device to take this setting effect *\n");
			tprintf("*                                                                    *\n");
			tprintf("**********************************************************************\n");
		}
		else
		{
			tprintf("\n Attention: The system mode you set is the same\n \n");
		}
		ret=CLI_NOTHING;
	}
	return ret;
}
#endif
/*****************************************************************
* NAME: cmdSystemMode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   joey 2008-0730
* Modify:   Norkay 2008-08-21
****************************************************************/
CliStatus cmdSystemMode(T_VOID* priv, CliData* cliData)
{
printf("cli_sys cmdSystemMode start");
	int ret;
	int new_opmode;
	int old_opmode = apCfgGetIntValue(SYS_OP_MODE_TOK);
printf("cli_sys cmdSystemMode priv=%s\n",priv);
printf("cli_sys cmdSystemMode cliData1curlv=%d\n",cliData->curLv);
printf("cli_sys cmdSystemMode cliData2argc=%d\n",cliData->argc);
printf("cli_sys cmdSystemMode cliData3tokenLen=%d\n",cliData->tokenLen);
printf("cli_sys cmdSystemMode cliData4mode=%d\n",cliData->mode);


	ret = setApCfgValue(priv, cliData);
ret = CLI_OK;
	if (ret == CLI_OK)
	{
		new_opmode = apCfgGetIntValue(SYS_OP_MODE_TOK);
		if (old_opmode != new_opmode)
		{
			sysmodeChanged=1;
			apCfgSetIntValue(SYS_ROUTE_ENABLE_TOK, (new_opmode==0||new_opmode==4)?1:0);
			apCfgSetIntValue(SYS_OP_MODE_TOK,new_opmode);
			//setSysOperationModeInfo(new_opmode);

			tprintf("**********************************************************************\n");
			tprintf("*                                                                    *\n");
			tprintf("* You should reboot the device to take this setting effect *\n");
			tprintf("*                                                                    *\n");
			tprintf("**********************************************************************\n");
		}
		ret=CLI_NOTHING;
tprintf("*cli nothing*\n");
	}
	return ret;
}

/*****************************************************************
* NAME: cmdSystemReboot
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdSystemReboot(T_VOID* priv, CliData* cliData)
{
#if TARGET
	if(sysmodeChanged==1)
	{
#if HAS_RADIO_SETTING
		setMultipleRadioSysOperationMode();
#else
		setSysOperationModeInfo(apCfgGetIntValue(SYS_OP_MODE_TOK));
#endif
		sysmodeChanged=0;
	}
	if(apCfgIsModified())
	{
		apCfgUpdateModifiedData();
	}
	SYSTEM("sysconf_cli inform reboot &");
#else
    tprintf("Reboot the system\n");
#endif
        /* marklin 20071027 : save temp file to flash then delete temp file */
    if (sysIsFileExisted("/storage/redboot_config"))
    {
        SYSTEM("setconfig -a 2 -s 6 -d 03 ; setconfig -a 5 ; rm /storage/redboot_config ");
    }
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdTelnet
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdTelnet(T_VOID* priv, CliData* cliData)
{
	const T_CHAR *ip;
	char port[10] = "23";

	/*ip value*/
	ip = getNextToken(cliData, 0);

	if (cliData->argc == 2 )
	{
		/*port file name*/
		sprintf(port, "%s", getNextToken(cliData, 1));
	}

	//tprintf("%s %s\n", ip, port);
	if (cliData->argc==0)
	{
		return CLI_CURRENT_OK;
	}

	if (cliData->argc != 1 && cliData->argc != 2 )
	{
		return CLI_PARAMS_ERR;
	}

	//if ((apCfgTestTextValue(TYPE_IP, ip) || regxMatch(HOST_NAME1_REGX, ip)) && 
	//	 apCfgTestTextValue(TYPE_PORT, port))
	if (apCfgTestTextValue(TYPE_PORT, port))
	{
		SYSTEM("telnet %s %s", ip, port);
	}
	else
	{
		return CLI_PARAMS_ERR;
	}

	return CLI_NOTHING;
}
#if HAS_LED_CONTROL
/*****************************************************************
* NAME: cmdLedPower
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdLedPower(T_VOID* priv, CliData* cliData)
{
	T_CHAR buf[128];
	int index = 0;	

	tprintf("Power LED(0:off, 1:on ): [%d] ",
		(apCfgGetIntValue(SYS_LED_PWR_CONTROL_TOK) == 1)? 1 : 0);
	if(getStdInCommand(buf, sizeof(buf)))
	{
		index = atoi(buf);
		if (index >= 0 && index <= 1)
		{
			apCfgSetIntValue(SYS_LED_PWR_CONTROL_TOK, index);
			SYSTEM("sysconf_cli inform led_control &");
		}
	}
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdLedLan
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdLedLan(T_VOID* priv, CliData* cliData)
{
	T_CHAR buf[128];
	int index = 0;	

	tprintf("Lan LED(0:off, 1:on ): [%d] ",
		(apCfgGetIntValue(SYS_LED_LAN_CONTROL_TOK) == 1)? 1 : 0);
	if(getStdInCommand(buf, sizeof(buf)))
	{
		index = atoi(buf);
		if (index >= 0 && index <= 1)
		{
			apCfgSetIntValue(SYS_LED_LAN_CONTROL_TOK, index);
			SYSTEM("sysconf_cli inform led_control &");
		}
	}
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdLedWlan
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdLedWlan(T_VOID* priv, CliData* cliData)
{
	T_CHAR buf[128];
	int index = 0;	

	tprintf("WLAN LED(0:off, 1:on ): [%d] ",
		(apCfgGetIntValue(SYS_LED_WLAN_CONTROL_TOK) == 1)? 1 : 0);
	if(getStdInCommand(buf, sizeof(buf)))
	{
		index = atoi(buf);
		if (index >= 0 && index <= 1)
		{
			apCfgSetIntValue(SYS_LED_WLAN_CONTROL_TOK, index);
			SYSTEM("sysconf_cli inform led_control &");
		}
	}
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdLedInfo
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdLedInfo(T_VOID* priv, CliData* cliData)
{
	tprintf(CLI_BODY_TITLE, "LED Info (0:off, 1:on )");
	tprintf(CLI_BODY_STR_CONTEXT, "Power LED", apCfgGetStrValue(SYS_LED_PWR_CONTROL_TOK));
	tprintf(CLI_BODY_STR_CONTEXT, "LAN LED", apCfgGetStrValue(SYS_LED_LAN_CONTROL_TOK));
	tprintf(CLI_BODY_STR_CONTEXT, "WLAN LED", apCfgGetStrValue(SYS_LED_WLAN_CONTROL_TOK));

	return CLI_NOTHING;
}
#endif
/*****************************************************************
* NAME: cmdsnmpversion
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdsnmpversion(T_VOID* priv, CliData* cliData)
{
	T_CHAR buf[128];
	int index = 0;
	
	tprintf("SNMP Version (0:All, 1:V1, 2:V2c): [%d] ",
			apCfgGetIntValue(SNMPD_COMMUNITY_VER_1_TOK));
	if(getStdInCommand(buf, sizeof(buf)))
	{
		index = atoi(buf);
		if (index >= 0 && index <=2 )
		{
			apCfgSetIntValue(SNMPD_COMMUNITY_VER_1_TOK, index);
		}
	}		
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSystemEventlog
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdSystemEventlog(T_VOID* priv, CliData* cliDat)
{
	FILE *fp;
	char buf[80];

	if (!sysIsFileExisted(LOG_MSG_FILE))
    {
        printf("Err: %s: %s does not exist!\n", __FUNCTION__, LOG_MSG_FILE);   
        dateNum=0;
    }
    else
    {
	    dateNum=getNumOfRecord(LOG_MSG_FILE,0);
		dateNum--;
		tprintf(CLI_BODY_TITLE, "View the system operation information.");
		if (dateNum == 0)
		{
			tprintf(CLI_LIST_EMPTY, "Client List");
			return CLI_NOTHING;
		}
		fp = fopen(LOG_MSG_FILE, "r");
		while(fgets(buf, sizeof(buf), fp) != NULL)
		{
			tprintf("%s", buf);
		}
		fclose(fp);
    }
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSystemIntegrity
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdSystemIntegrity(T_VOID* priv, CliData* cliDat)
{
	int WanMiiStatus;
	sysMiiCheckLink(ETH_GMMI_1_DEV,&WanMiiStatus,0);
	tprintf("Link Integrity (0:Ethernet down, 1:Ethernet up): [%d] ",
		(WanMiiStatus==0 ? 0:1));

	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSystemTimeNTPServer1
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdSystemTimeNTPServer1(T_VOID* priv, CliData* cliDat)
{
	T_CHAR buf[128];
	int opmode;
    opmode = current_opmode;


	if((OPM_AR==opmode)||(OPM_CBRT==opmode))
	{
		tprintf("NTP Time Sever: [%s] ",
				apCfgGetStrValue(NTP_SERVER_01_TOK));
		if(getStdInCommand(buf, sizeof(buf))){
				apCfgSetValueByStr(NTP_SERVER_01_TOK, buf);
		}
	}
	else
	{
#if HAS_LOCAL_NTP_SERVER
		tprintf("NTP Time Sever: [%s] ",
				apCfgGetStrValue(NTP_LOCAL_SERVER_TOK));
		if(getStdInCommand(buf, sizeof(buf))){
				apCfgSetValueByStr(NTP_LOCAL_SERVER_TOK, buf);
		}
#endif
	}
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdDDNSServerType
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:  
* Modify:   
****************************************************************/
CliStatus cmdDDNSServerType(T_VOID* priv, CliData* cliData)
{
	int i=0, j=0;
	T_CHAR buf[128];
	int index = 0;
	int ennum = 0; //total_enable_number
	struct
	{
		char *description;
		int type;
		int enabled;
	} servertypeset_table[] = 
	{
		{"3322(qdns)",       	DDNS_TYPE_3322, 	    1},
		{"DHS", 		        DDNS_TYPE_DHS, 	    	1},
		{"DynDNS", 		        DDNS_TYPE_DYNDNS,    	1},
		{"DDNS_TYPE_ODS",   	DDNS_TYPE_ODS, 	        0},
		{"DDNS_TYPE_TZO",   	DDNS_TYPE_TZO, 	        0},
		{"DDNS_TYPE_GNUDIP", 	DDNS_TYPE_GNUDIP,    	0},
		{"DDNS_TYPE_DYNS",      DDNS_TYPE_DYNS, 	    0},
		{"ZonEdit", 	        DDNS_TYPE_ZONEEDIT, 	1},
		{"DDNS_TYPE_DHIS",   	DDNS_TYPE_DHIS, 	    0},
		{"CyberGate",       	DDNS_TYPE_CYBERGATE, 	1},
		{"DDNS_TYPE_DYNDNS_C", 	DDNS_TYPE_DYNDNS_C, 	0},
		{"DDNS_TYPE_NO_IP", 	DDNS_TYPE_NO_IP, 	    0},
		{"DDNS_TYPE_EURODNS", 	DDNS_TYPE_EURODNS, 	    0},
		{"DDNS_TYPE_REGFISH", 	DDNS_TYPE_REGFISH,     	0},
		{"DDNS_TYPE_IOBB", 	    DDNS_TYPE_IOBB, 	    0},
		{"DDNS_TYPE_DLINK", 	DDNS_TYPE_DLINK, 	    0},
	};
/*print type of servers*/
	tprintf(CLI_BODY_TITLE,"servtype -- Server Address");
	for (i = 0; i < sizeof(servertypeset_table)/sizeof(servertypeset_table[0]); i++)
	{
		if (servertypeset_table[i].enabled == 1)
		{
			//tprintf("DEAN_type=%d\n",servertypeset_table[i].type);			
			tprintf("%d:%s\n", j, servertypeset_table[i].description);
			j++;
		}
	}
	ennum=j;
	j=0;
/*show old option*/
	index=apCfgGetIntValue(DDNS_TYPE_TOK); //index=15 for cyberGate
	for(i = 0; i < sizeof(servertypeset_table)/sizeof(servertypeset_table[0]);i++)
	{
		if (servertypeset_table[i].enabled == 1)
		{
			if(index==servertypeset_table[i].type)
			{
				tprintf(CLI_BODY_HR);
				tprintf("Server Address: [%d]",j);
				//tprintf("real_int=%d\n",apCfgGetIntValue(DDNS_TYPE_TOK));
			}
			j++;
		}
	}
/*set new option*/
	if(getStdInCommand(buf, sizeof(buf))){
		index = atoi(buf);
		j = 0;		//j is the enable number count
		for (i = 0; i < sizeof(servertypeset_table)/sizeof(servertypeset_table[0]); i++)
		{
			if (servertypeset_table[i].enabled == 1)
			{
				if(j == index && index>=0 && index<=ennum)
				{
					//tprintf("%d:%s\n", i, servertypeset_table[i]);
					//tprintf("index = %d", servertypeset_table[i].type);
					apCfgSetIntValue(DDNS_TYPE_TOK, servertypeset_table[i].type);
				}
				j++;
			}
		}
	}
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSystemAPprofileList
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
#if HAS_AP_PROFILE
	typedef struct
	{
		char *description;
		int type;
	} TABLE;

	TABLE enc_table[] = 
	{
		{"NONE",       0},
		{"WEP", 	   1},
		{"TKIP", 	   2},
		{"AES",        3},
		{"TKIP-AES",   4},
	};
	TABLE auth_table[] = 
	{
		{"Open System", 	 0},
		{"WEP Auto", 	     1},
		{"Shared Key", 	     2},
		{"WPA_PSK",     	 3},
		{"WPA",   			 4},
		{"WPA2_PSK",         5},
		{"WPA2", 	   		 6},
		{"WPA_WPA2", 	     7},
		{"WPA2_Mixed",       8},
		{"8021X NONE",	     9},
		{"8021X WEP",       10},
	};

CliStatus cmdSystemAPprofileList(T_VOID* priv, CliData* cliData)
{
	int j=0, index;
	int enable=0;
	int tmp_ecn=0;
	int tmp_auth=0;
	char ival[200]={0};
	static T_CHAR result[MAX_MAC_ADDR_LEN_IN_STR]={0};
	char detSSID[60]={0};
	T_MACADDR  mac;

    tprintf(WLAN_APPROFILE_DESCRIP);
    tprintf(CLI_BODY_HR);

	for(index=1;index<=MAX_AP_PROFILE_ITEMS;index++)
	{
    	apCfgGetValue2(mac, APPROFILE_"%d"_BSSID_TOK, index); 
    	sprintf(result,MAC_PATTERN_WITH_COLON,
                mac[0]&0xff,mac[1]&0xff,mac[2]&0xff,
                mac[3]&0xff,mac[4]&0xff,mac[5]&0xff);

    	sysCheckStringOnWeb(apCfgGetStrValue(APPROFILE_"%d"_SSID_TOK, index), detSSID); /* " and \ add escape character \ */


		tmp_ecn=atoi(apCfgGetStrValue(APPROFILE_"%d"_ENC_TYPE_TOK, index));
		tmp_auth=atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, index));
		enable=atoi(apCfgGetStrValue(APPROFILE_"%d"_ENABLE_TOK, index));
		if(enable==1)
		{
			//j+=sprintf(ival+j,"mac:\"%02X:%02X:%02X:%02X:%02X:%02X\",",pMac[0],pMac[1],pMac[2],pMac[3],pMac[4],pMac[5] );
			j=sprintf(ival,"%5d",index);
			j+=sprintf(ival+j,"%20s",detSSID);
			j+=sprintf(ival+j,"%25s",result);
			j+=sprintf(ival+j,"%15s",auth_table[tmp_auth].description);
			if(tmp_auth==4 || tmp_auth==6 || tmp_auth==7 || tmp_auth==9 || tmp_auth==10){
				j+=sprintf(ival+j,"%15s","802.1X");
			}
			else{
				j+=sprintf(ival+j,"%15s",enc_table[tmp_ecn].description);
			}
			j+=sprintf(ival+j,"%10s",apCfgGetStrValue(APPROFILE_"%d"_ORDER_TOK, index));
			//j+=sprintf(ival+j,"%s",(index1==MAX_AP_PROFILE_ITEMS)?"":",");
			printf("%s\n",ival);
		}
    }
return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSystemAPprofileDel
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus cmdSystemAPprofileDel(T_VOID* priv, CliData* cliData)
{
	int i, j, entrynum=0, enable=0;
	int pri, priTmp2, index=0;
	T_CHAR buf[128];

	tprintf("AP Profile List: ");
	for(i=1;i<=MAX_AP_PROFILE_ITEMS;i++)
	{
		enable=atoi(apCfgGetStrValue(APPROFILE_"%d"_ENABLE_TOK, i));
		if(enable==1){
			tprintf("%d. ",i);
			entrynum++;
		}
	}
	tprintf("\n");
	if(entrynum==0)
	{
		tprintf("No entry to delete!");
		return CLI_NOTHING;
	}
	tprintf("which one you want to delete: ");
	if(getStdInCommand(buf, sizeof(buf)))
	{
		index=atoi(buf);
		if(index >= 1 && index <=MAX_AP_PROFILE_ITEMS )
		{
			pri = apCfgGetIntValue(APPROFILE_"%d"_ORDER_TOK, index);
			for(j=1;j<=MAX_AP_PROFILE_ITEMS;++j)
			{
				if(apCfgGetIntValue(APPROFILE_"%d"_ENABLE_TOK, j)==FILTER_ENABLE)
				{
					if(apCfgGetIntValue(APPROFILE_"%d"_ORDER_TOK, j) > pri)
					{
						priTmp2=apCfgGetIntValue(APPROFILE_"%d"_ORDER_TOK, j);
						priTmp2--;
						apCfgSetIntValue2(priTmp2, APPROFILE_"%d"_ORDER_TOK, j);
					}
				}
			}
			apCfgSetIntValue2(0, APPROFILE_"%d"_ENABLE_TOK, index);
			apCfgRollback(APPROFILE_"%d"_SSID_TOK, index);
			apCfgRollback(APPROFILE_"%d"_ENC_TYPE_TOK, index);
			apCfgRollback(APPROFILE_"%d"_AUTH_TOK, index);
			apCfgRollback(APPROFILE_"%d"_BSSID_TOK, index);
			apCfgRollback(APPROFILE_"%d"_WPAKEY_TOK, index);
			apCfgRollback(APPROFILE_"%d"_WEPKEY_0_TOK, index);
			apCfgRollback(APPROFILE_"%d"_WEPKEY_1_TOK, index);
			apCfgRollback(APPROFILE_"%d"_WEPKEY_2_TOK, index);
			apCfgRollback(APPROFILE_"%d"_WEPKEY_3_TOK, index);
			apCfgRollback(APPROFILE_"%d"_8021X_ENABLE_TOK, index);
			apCfgRollback(APPROFILE_"%d"_8021X_IDENTITY_TOK, index);
			apCfgRollback(APPROFILE_"%d"_8021X_PWD_TOK, index);
			apCfgRollback(APPROFILE_"%d"_8021X_METHOD_TOK, index);
			apCfgSetIntValue2(0, APPROFILE_"%d"_ORDER_TOK, index); 
		}
	}
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: SystemAPprofileWepSetting
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Dean            2011-0520
* Modify:   
****************************************************************/
static CliStatus SystemAPprofileWepSetting(int Idx)
{	
	T_CHAR buf[128];
	int i, index=0;
	
	index=((atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx)) == WLAN_AUTH_OPEN)?0:1);
	//printf("DEAN_index=%d\n",index);
	tprintf("Authentication Type(1:Shared Key, 0:Open System): [%d] ", index);
	if(getStdInCommand(buf, sizeof(buf)))
	{
		switch(atoi(buf))
		{
			default:
			case 0: 
				apCfgSetIntValue2(WLAN_AUTH_OPEN, APPROFILE_"%d"_AUTH_TOK, Idx); 
				break;
			case 1:  
				apCfgSetIntValue2(WLAN_AUTH_SHARED, APPROFILE_"%d"_AUTH_TOK, Idx); 
				break;
		}
	}
	tprintf("Key Length(1:64-bit, 0:128-bit): [%d]", 
			(atoi(apCfgGetStrValue(APPROFILE_"%d"_WEP_TOK, Idx)) == 64) ? 1: 0);
	if(getStdInCommand(buf, sizeof(buf)))
	{
		index = atoi(buf);
		if (index >= 0 && index <= 1)
		{
			apCfgSetValueByStr2(((index==1)? "64" : "128" ), APPROFILE_"%d"_WEP_TOK, Idx);   
		}
	}
    if(atoi(apCfgGetStrValue(APPROFILE_"%d"_WEP_TOK, Idx)) == 64 ? 1 : 0)
    {
        tprintf("Key Type(1:ASCII(5 characters), 0:Hex(10 characters)): [%d] ", 
				(atoi(apCfgGetStrValue(APPROFILE_"%d"_KEYTYPE_TOK, Idx)) == 1)? 1 : 0);
        if(getStdInCommand(buf, sizeof(buf)))
        {
            index = atoi(buf);
            if (index >= 0 && index <= 1)
            {
				apCfgSetValueByStr2(buf , APPROFILE_"%d"_KEYTYPE_TOK, Idx);
            }
        }
    }
    else
    {
        tprintf("Key Type(1:ASCII(13 characters), 0:Hex(26 characters)): [%d] ",
                atoi(apCfgGetStrValue(APPROFILE_"%d"_KEYTYPE_TOK, Idx)) == 1? 1 : 0);
        if(getStdInCommand(buf, sizeof(buf)))
        {
            index = atoi(buf);
            if (index >= 0 && index <= 1)
            {
                apCfgSetValueByStr2(buf , APPROFILE_"%d"_KEYTYPE_TOK, Idx);
            }
        }
    }
    tprintf("Default Key(1~4): [%s] ", apCfgGetStrValue(APPROFILE_"%d"_KEYID_TOK, Idx));
    if(getStdInCommand(buf, sizeof(buf)))
    {
        index = atoi(buf);
        if (index >= 1 && index <= 4)
        {
			apCfgSetValueByStr2(buf , APPROFILE_"%d"_KEYID_TOK, Idx);
        }
    }
    for (i=0;i<4;i++)
    {
		apCfgGetValue2(buf , APPROFILE_"%d"_WEPKEY_TOK"%d", Idx, i);
        tprintf("Encryption Key %d: [%s] ", i+1, buf );
        if(getStdInCommand(buf, sizeof(buf)))
        {
            apCfgSetValueByStr2(buf , APPROFILE_"%d"_WEPKEY_TOK"%d", Idx, i);
        }
    }

    return CLI_NOTHING;
}
/*****************************************************************
* NAME: SystemAPprofileWpaSetting
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Dean            2011-0520
* Modify:   
****************************************************************/
static CliStatus SystemAPprofileWpaSetting(int Idx)
{
	T_CHAR buf[128];
	int  index;
	char passphrase[64+1];
	char detSSID[60];
	int  auth;
	
	auth = atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx));    
	if (auth == WLAN_AUTH_WPAPSK)
		index = 0;
	else if (auth == WLAN_AUTH_WPA2PSK)
		index = 1;
	else
		index = -1;

    if(index < 0)
    {
        tprintf("WPA Type(1:WPA2(AES), 0:WPA(TKIP)): [%s] ", "");
    }else{
        tprintf("WPA Type(1:WPA2(AES), 0:WPA(TKIP)): [%d] ", index);
    }
	
	if(getStdInCommand(buf, sizeof(buf)))
	{
		index = atoi(buf);
		if (index >= 0 && index <= 1)
		{
			if (index == 1) {
				apCfgSetIntValue2(WLAN_AUTH_WPA2PSK, APPROFILE_"%d"_AUTH_TOK, Idx);
				apCfgSetIntValue2(WLAN_ENC_AES, APPROFILE_"%d"_ENC_TYPE_TOK, Idx);
			} else {
				apCfgSetIntValue2(WLAN_AUTH_WPAPSK, APPROFILE_"%d"_AUTH_TOK, Idx);
				apCfgSetIntValue2(WLAN_ENC_TKIP, APPROFILE_"%d"_ENC_TYPE_TOK, Idx);
			}
		}
	}
	else
	{
		enflag++;
		tprintf("Please enter \"WPA Type\"");
		return CLI_NOTHING;
	}
#if 0
	tprintf("Pre-shared Key Type(0:Passphrase, 1:Hex(64 characters)): [%d] ", 
			apCfgGetIntValue(wlanToken->WpaPskType));
	if(getStdInCommand(buf, sizeof(buf)))
	{
		index = atoi(buf);
		if (index >= 0 && index <= 1)
		{
			apCfgSetIntValue(wlanToken->WpaPskType, index);
		}
	}
#endif
	tprintf("Pre-shared Key: [%s] ", apCfgGetStrValue(APPROFILE_"%d"_WPAKEY_TOK, Idx));
	if (getStdInCommand(buf, sizeof(buf)))
	{
		apCfgSetValueByStr2(buf , APPROFILE_"%d"_WPAKEY_TOK, Idx);
		if(strlen(apCfgGetStrValue(APPROFILE_"%d"_WPAKEY_TOK, Idx))!=64)
		{
			sysCheckStringOnWeb(apCfgGetStrValue(APPROFILE_"%d"_SSID_TOK, Idx), detSSID);
			strcpy(passphrase, (char *)sysWlanGetPassphrase(detSSID, buf));
			apCfgSetValueByStr2(passphrase, APPROFILE_"%d"_WPAPASSPHRASE_TOK, Idx);
		}
		else
		{
			apCfgSetValueByStr2(buf, APPROFILE_"%d"_WPAPASSPHRASE_TOK, Idx);
		}
	}
  return CLI_NOTHING;
}
/*****************************************************************
* NAME: SystemAPprofileRadiusSetting 
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Dean            2011-0523           
* Modify:   
****************************************************************/
static CliStatus SystemAPprofileRadiusSetting (int Idx)
{	
	T_CHAR buf[128];
	int index=-1, auth;
   
    auth = atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx)); 
  
	switch(auth)
	{
#if HAS_WLAN_STA_FUNCTION
		case WLAN_AUTH_8021X_NONE:
			index = 0;
			break;
		case WLAN_AUTH_8021X_WEP:
			index = 1;
			break;
#endif
		case WLAN_AUTH_WPA:
			index = 2;
			break;
		case WLAN_AUTH_WPA2:
			index = 3;
			break;
	}

    if(index < 0)
    {
        tprintf("Authentication Type(3:WPA2(AES), 2:WPA(TKIP), 1:WEP, 0:None): [%s] ", "");
    }else{
		tprintf("Authentication Type(3:WPA2(AES), 2:WPA(TKIP), 1:WEP, 0:None): [%d] ", index);
    }

	if(getStdInCommand(buf, sizeof(buf)))
	{
		index = atoi(buf);
		if (index >= 0 && index <= 3)
		{
#if HAS_WLAN_STA_FUNCTION
			if(index == 0)
			{			
				apCfgSetValueByStr2(buf, APPROFILE_"%d"_ENC_TYPE_TOK, Idx);
				apCfgSetIntValue2(WLAN_AUTH_8021X_NONE, APPROFILE_"%d"_AUTH_TOK, Idx);
			}
			if (index == 1) 
			{
				apCfgSetValueByStr2(buf, APPROFILE_"%d"_ENC_TYPE_TOK, Idx);
				apCfgSetIntValue2(WLAN_AUTH_8021X_WEP, APPROFILE_"%d"_AUTH_TOK, Idx);
			}
#endif
			if (index == 2)
			{
				apCfgSetValueByStr2(buf, APPROFILE_"%d"_ENC_TYPE_TOK, Idx);
				apCfgSetIntValue2(WLAN_AUTH_WPA, APPROFILE_"%d"_AUTH_TOK, Idx);
			}
			else
			{
				apCfgSetValueByStr2(buf, APPROFILE_"%d"_ENC_TYPE_TOK, Idx);
				apCfgSetIntValue2(WLAN_AUTH_WPA2, APPROFILE_"%d"_AUTH_TOK, Idx);
			}
		}
	}
	else
	{
		enflag++;
		tprintf("Please enter \"Authentication Type.\"");
		return CLI_NOTHING;
	}
/*set EAP method*/
    tprintf("EAP Method(1:TTLS 0:PEAP) : [%d] ", atoi(apCfgGetStrValue(APPROFILE_"%d"_8021X_METHOD_TOK, Idx))==0?0:1);
	if (getStdInCommand(buf, sizeof(buf))) {
		index = atoi(buf);
		if (index >=0 && index <=1)
		{
			buf[0]=((index==0)? '0':'2');
			apCfgSetValueByStr2(buf, APPROFILE_"%d"_8021X_METHOD_TOK, Idx);
		}
	}
/*set uthentication identity*/
    tprintf("Authentication Identity : [%s] ", apCfgGetStrValue(APPROFILE_"%d"_8021X_IDENTITY_TOK, Idx));
	if (getStdInCommand(buf, sizeof(buf))) {
		apCfgSetValueByStr2(buf , APPROFILE_"%d"_8021X_IDENTITY_TOK, Idx);
	}
/*setAuthentication Password*/
    tprintf("Authentication Password : [%s] ", apCfgGetStrValue(APPROFILE_"%d"_8021X_PWD_TOK, Idx));
	if(getStdInCommand(buf, sizeof(buf))) {
		apCfgSetValueByStr2(buf , APPROFILE_"%d"_8021X_PWD_TOK, Idx);
	}
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSystemAPprofileNew
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Dean            2011-0520   
* Modify:   
****************************************************************/
CliStatus cmdSystemAPprofileNew(T_VOID* priv, CliData* cliData)
{
	int i,enable=0;
	int firstAvailIdx=0 ,entrynum=0, priMax=0, method=0;
	char tok[30], detSSID[60];;
	T_CHAR buf[128];

	enflag=0;
	for(i=0;i<MAX_AP_PROFILE_ITEMS;i++)
	{
		enable=atoi(apCfgGetStrValue(APPROFILE_"%d"_ENABLE_TOK, i+1));
		if(enable==0)
		{
			firstAvailIdx=(i+1);
			break;
		}
	}
	//printf("DEAN_firstAvailIdx=%d\n",firstAvailIdx);
	for(i=1;i<=MAX_AP_PROFILE_ITEMS;i++)
	{
		enable=atoi(apCfgGetStrValue(APPROFILE_"%d"_ENABLE_TOK, i));
		if(enable)
		{
			entrynum++;
		}
	}
	//printf("DEAN_entrynum=%d\n",entrynum);
	if(entrynum>=3)
	{
		tprintf("Cannot add new entry because table is full!\n");
		return CLI_NOTHING;
	}

	if(apCfgGetIntValue(APPROFILE_"%d"_ENABLE_TOK, firstAvailIdx)==FILTER_NONUSED)
	{
		apCfgRollback(APPROFILE_"%d"_SSID_TOK, firstAvailIdx);
		apCfgRollback(APPROFILE_"%d"_ENC_TYPE_TOK, firstAvailIdx);
		apCfgRollback(APPROFILE_"%d"_AUTH_TOK, firstAvailIdx);
		apCfgRollback(APPROFILE_"%d"_BSSID_TOK, firstAvailIdx);
		apCfgRollback(APPROFILE_"%d"_WPAKEY_TOK, firstAvailIdx);
		apCfgRollback(APPROFILE_"%d"_WEPKEY_0_TOK, firstAvailIdx);
		apCfgRollback(APPROFILE_"%d"_WEPKEY_1_TOK, firstAvailIdx);
		apCfgRollback(APPROFILE_"%d"_WEPKEY_2_TOK, firstAvailIdx);
		apCfgRollback(APPROFILE_"%d"_WEPKEY_3_TOK, firstAvailIdx);
		apCfgRollback(APPROFILE_"%d"_8021X_ENABLE_TOK, firstAvailIdx);
		apCfgRollback(APPROFILE_"%d"_8021X_IDENTITY_TOK, firstAvailIdx);
		apCfgRollback(APPROFILE_"%d"_8021X_PWD_TOK, firstAvailIdx);
		apCfgRollback(APPROFILE_"%d"_8021X_METHOD_TOK, firstAvailIdx);
		apCfgSetIntValue2(0, APPROFILE_"%d"_ORDER_TOK, firstAvailIdx);  

	}
//	apCfgFindFirstAvailable(PORT_QOS_TOK,NUM_QOS_PORT);
	/*set pchangeindex to next page use*/
	sprintf(tok,"%d",firstAvailIdx);
	apCfgSetValueByStr(TEMP_01_TOK,tok);
	apCfgSetValueByStr(TEMP_02_TOK,"add");
/*set priority*/
	if(apCfgGetIntValue(APPROFILE_"%d"_ORDER_TOK, firstAvailIdx) == 0)
	{
		for(i=1;i<=MAX_AP_PROFILE_ITEMS;i++)
		{
			if(apCfgGetIntValue(APPROFILE_"%d"_ENABLE_TOK, i)==FILTER_ENABLE)
			{
				if(apCfgGetIntValue(APPROFILE_"%d"_ORDER_TOK, i) > priMax)
				{
					priMax=apCfgGetIntValue(APPROFILE_"%d"_ORDER_TOK, i);
				}
			}
		}
		apCfgSetIntValue2((priMax+1), APPROFILE_"%d"_ORDER_TOK, firstAvailIdx);
	}
/*set SSID*/
	sysCheckStringOnWeb(apCfgGetStrValue(APPROFILE_"%d"_SSID_TOK, firstAvailIdx), detSSID); /* " and \ add escape character \ */
	tprintf("Network Name (SSID) :[%s] ", detSSID);	
	if (getStdInCommand(buf, sizeof(buf)))
	{
		apCfgSetValueByStr2(buf, APPROFILE_"%d"_SSID_TOK, firstAvailIdx);
	}
/*set Encryption*/
/* Determine which method has been chosen. */
	if(atoi(apCfgGetStrValue(APPROFILE_"%d"_ENC_TYPE_TOK, firstAvailIdx))==WLAN_ENC_NONE 
#if HAS_WLAN_STA_FUNCTION
	   && atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, firstAvailIdx))!= WLAN_AUTH_8021X_NONE
#endif
	   ) 
	{
		method=WEB_WLAN_ENC_NONE;
	} else if (atoi(apCfgGetStrValue(APPROFILE_"%d"_ENC_TYPE_TOK, firstAvailIdx))==WLAN_ENC_WEP 
#if HAS_WLAN_STA_FUNCTION
			   && atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, firstAvailIdx))!= WLAN_AUTH_8021X_WEP
#endif
			   ) 
	{
		method=WEB_WLAN_ENC_WEP;
	} else if (atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, firstAvailIdx))==WLAN_AUTH_WPAPSK 
			   || atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, firstAvailIdx))==WLAN_AUTH_WPA2PSK 
			   || atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, firstAvailIdx))==WLAN_AUTH_WPA1PSKWPA2PSK) 
	{
		method=WEB_WLAN_ENC_WPAPSK;
	} else if(atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, firstAvailIdx))==WLAN_AUTH_WPA 
			   || atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, firstAvailIdx))==WLAN_AUTH_WPA2 
			   || atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, firstAvailIdx))==WLAN_AUTH_WPA1WPA2
#if HAS_WLAN_STA_FUNCTION
			   || atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, firstAvailIdx))==WLAN_AUTH_8021X_NONE
			   || atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, firstAvailIdx))==WLAN_AUTH_8021X_WEP
#endif
			  ) 
	{
		method=WEB_WLAN_ENC_WPARADIUS;
	}

	tprintf("Encryption(3:WPA RADIUS 2:WPA pre-shared key, 1:WEP, 0:Disable):[%d]",method);	
	if (getStdInCommand(buf, sizeof(buf)))
	{
		switch(atoi(buf))
		{
			default:
			case WEB_WLAN_ENC_NONE:
				apCfgSetIntValue2(WLAN_ENC_NONE, APPROFILE_"%d"_ENC_TYPE_TOK, firstAvailIdx);
				apCfgSetIntValue2(WLAN_AUTH_OPEN, APPROFILE_"%d"_AUTH_TOK, firstAvailIdx);
				break;
			case WEB_WLAN_ENC_WEP:
				apCfgSetIntValue2(WLAN_ENC_WEP, APPROFILE_"%d"_ENC_TYPE_TOK, firstAvailIdx);
				SystemAPprofileWepSetting(firstAvailIdx);
				break;
			case WEB_WLAN_ENC_WPAPSK:
				SystemAPprofileWpaSetting(firstAvailIdx);
				break;
			case WEB_WLAN_ENC_WPARADIUS:
				SystemAPprofileRadiusSetting(firstAvailIdx);
				break;
		}	
	}
/*For solve default value "WLAN_AUTH_WEPAUTO" */
	else if (atoi(apCfgGetStrValue(APPROFILE_"%d"_ENC_TYPE_TOK, firstAvailIdx))==WLAN_ENC_NONE && atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, firstAvailIdx))== WLAN_AUTH_WEPAUTO)
	{
		apCfgSetIntValue2(WLAN_ENC_NONE, APPROFILE_"%d"_ENC_TYPE_TOK, firstAvailIdx);
		apCfgSetIntValue2(WLAN_AUTH_OPEN, APPROFILE_"%d"_AUTH_TOK, firstAvailIdx);
	}
/*Enable*/
	//printf("DEAN_flag=%d\n",enflag);
	if(!enflag)
	{
		apCfgSetIntValue2(1, APPROFILE_"%d"_ENABLE_TOK, firstAvailIdx);
	}
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdSystemAPprofileEdit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Dean            2011-0520   
* Modify:   
****************************************************************/

CliStatus cmdSystemAPprofileEdit(T_VOID* priv, CliData* cliData)
{
	int i, entrynum=0, enable=0;
	int method=0 , Idx=0;
	T_CHAR buf[128];
	char tok[30], detSSID[60];

	tprintf("AP Profile List: ");
	for(i=1;i<=MAX_AP_PROFILE_ITEMS;i++)
	{
		enable=atoi(apCfgGetStrValue(APPROFILE_"%d"_ENABLE_TOK, i));
		if(enable==1){
			tprintf("%d. ",i);
			entrynum++;
		}
	}
	tprintf("\n");
	if(entrynum==0)
	{
		tprintf("No entry to Edit!");
		return CLI_NOTHING;
	}
	tprintf("which one you want to Edit: ");
	if(getStdInCommand(buf, sizeof(buf)))
	{
		Idx=atoi(buf);
		if(Idx >= 1 && Idx <=MAX_AP_PROFILE_ITEMS )
		{
			if(atoi(apCfgGetStrValue(APPROFILE_"%d"_ENABLE_TOK, Idx)))
			{
	/*set pchangeindex to next page use*/
				sprintf(tok,"%d",Idx);
				apCfgSetValueByStr(TEMP_01_TOK,tok);
				apCfgSetValueByStr(TEMP_02_TOK,"edit");
	/*set SSID*/
				sysCheckStringOnWeb(apCfgGetStrValue(APPROFILE_"%d"_SSID_TOK, Idx), detSSID); /* " and \ add escape character \ */
				tprintf("Network Name (SSID) : [%s]", detSSID);	
				if (getStdInCommand(buf, sizeof(buf)))
				{
					apCfgSetValueByStr2(buf, APPROFILE_"%d"_SSID_TOK, Idx);
				}
	/*set Encryption*/
	/* Determine which method has been chosen. */
				//printf("enc_=%s\n",apCfgGetStrValue(APPROFILE_"%d"_ENC_TYPE_TOK, Idx));
				//printf("auth_=%s\n",apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx));
			if(atoi(apCfgGetStrValue(APPROFILE_"%d"_ENC_TYPE_TOK, Idx))==WLAN_ENC_NONE 
#if HAS_WLAN_STA_FUNCTION
			   && atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx))!= WLAN_AUTH_8021X_NONE 
#endif
			   )
			{
				method=WEB_WLAN_ENC_NONE;
			} else if (atoi(apCfgGetStrValue(APPROFILE_"%d"_ENC_TYPE_TOK, Idx))==WLAN_ENC_WEP 
#if HAS_WLAN_STA_FUNCTION
					   && atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx))!= WLAN_AUTH_8021X_WEP
#endif
					   ) 
			{
				method=WEB_WLAN_ENC_WEP;
			} else if (atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx))==WLAN_AUTH_WPAPSK 
					   || atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx))==WLAN_AUTH_WPA2PSK 
					   || atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx))==WLAN_AUTH_WPA1PSKWPA2PSK) 
			{
				method=WEB_WLAN_ENC_WPAPSK;
			} else if(atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx))==WLAN_AUTH_WPA 
					   || atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx))==WLAN_AUTH_WPA2 
					   || atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx))==WLAN_AUTH_WPA1WPA2
#if HAS_WLAN_STA_FUNCTION
					   || atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx))==WLAN_AUTH_8021X_NONE
					   || atoi(apCfgGetStrValue(APPROFILE_"%d"_AUTH_TOK, Idx))==WLAN_AUTH_8021X_WEP
#endif
					  ) 
			{
				method=WEB_WLAN_ENC_WPARADIUS;
			}
				tprintf("Encryption(3:WPA RADIUS 2:WPA pre-shared key, 1:WEP, 0:Disable): [%d]",method);	
				if (getStdInCommand(buf, sizeof(buf)))
				{
					switch(atoi(buf))
					{
						default:
						case WEB_WLAN_ENC_NONE:
							apCfgSetIntValue2(WLAN_ENC_NONE, APPROFILE_"%d"_ENC_TYPE_TOK, Idx);
							apCfgSetIntValue2(WLAN_AUTH_OPEN, APPROFILE_"%d"_AUTH_TOK, Idx);
							break;
						case WEB_WLAN_ENC_WEP:
							apCfgSetIntValue2(WLAN_ENC_WEP, APPROFILE_"%d"_ENC_TYPE_TOK, Idx);
							SystemAPprofileWepSetting(Idx);
							break;
						case WEB_WLAN_ENC_WPAPSK:
							SystemAPprofileWpaSetting(Idx);
							break;
						case WEB_WLAN_ENC_WPARADIUS:
							SystemAPprofileRadiusSetting(Idx);
							break;
					}	
				}
			}
		}
	}
return CLI_NOTHING;
}
#endif

/*****************************************************************
* NAME: cmdSystemCheckfreememory
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Dean            2011-0614   
* Modify:   
****************************************************************/

CliStatus cmdSystemCheckfreememory(T_VOID* priv, CliData* cliData)
{
	/*move from sysconfig/setting/systemmonitor.c*/
    struct sysinfo info;
    //printf("-->%s\n",__FUNCTION__);
    sysinfo(&info);
    tprintf("Free memory: %ldKB \n",info.freeram/1024);
    
	return CLI_NOTHING;
}


T_CHAR* sysGetLocaltimeByItem(T_CHAR name) {

  unsigned char octetstr_value[255];  
  FILE *fp;
  char retval[255];
  int j=0;

  switch(name){
	case 'a':

    system("date > /tmp/uci_string.tmp");

    if ((fp = fopen("/tmp/uci_string.tmp", "r"))==NULL){
//      return SNMP_ERR_GENERR;
    }

    if (fgets(retval, sizeof(retval), fp)!=NULL){
      system("rm /tmp/uci_string.tmp");
    }
    sprintf(octetstr_value,retval);
    octetstr_value[strlen(retval)-1]='\0';
    fclose(fp);

    /*for (j=0; j< strlen(retval)-1; j++)
      octetstr_value[j]=retval[j];
    octetstr_value[strlen(retval)-1]='\0';
    */

	break;
  }

	return octetstr_value;

}



const T_CHAR* apCfgGetItemText(const T_CHAR* token){

  unsigned char octetstr_value[255];
  unsigned char token_tmp[255];
  FILE *fp;
  char retval[255];
  int j=0;
  char g1[255];
if (strcmp(token ,"ntpstatus")==0){
printf("y1\n");
//   memset(token, 0, sizeof(token));

   strcpy(token_tmp, "ntpclient.@ntpclient[0].NTPSrvMode");
printf("y2\n");
   printf("token_tmp in get item=%s\n",token_tmp);

    sprintf(g1, "uci get %s > /tmp/uci_string.tmp", token_tmp);
    system(g1);

}else{

    sprintf(g1, "uci get %s > /tmp/uci_string.tmp", token);
    system(g1);
}
    if ((fp = fopen("/tmp/uci_string.tmp", "r"))==NULL){

    }

    if (fgets(retval, sizeof(retval), fp)!=NULL){
      system("rm /tmp/uci_string.tmp");
    }
//printf("retval=%s\n",retval);

    if (strcmp(token, "ntpclient.@ntpclient[0].NTPSrvMode")==0 || strcmp(token_tmp, "ntpclient.@ntpclient[0].NTPSrvMode")==0){ /*NTPSrvMode*/
      if (atoi(retval)==0)
    	sprintf(octetstr_value, "Disable");
      else if (atoi(retval)==1)
    	sprintf(octetstr_value, "Enable");
    }
    else{
    
      for (j=0; j< strlen(retval)-1; j++)
        octetstr_value[j]=retval[j];
      octetstr_value[strlen(retval)-1]='\0';    
        
    }
    
    fclose(fp);

//printf("octetstr_value=%s\n",octetstr_value);
	return octetstr_value;


}

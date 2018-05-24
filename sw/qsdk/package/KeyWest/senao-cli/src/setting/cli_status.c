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
;    File    : cli_status.c
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
//#include <cli.h>
//#include <cli_status.h>
//#include <sysFile.h>
//#include <systeminfo.h>

#include <cli_status.h>
#include <opmodes.h>
#include <uci.h>

/*-------------------------------------------------------------------------*/
/*                           Parameter                                     */
/*-------------------------------------------------------------------------*/
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

typedef struct __CliOperationModeEntry{
    const T_INT32 item;
    const T_CHAR* operationmode;
    const T_CHAR* operationmodeName;
}CliOperationModeEntry;

extern CliOperationModeEntry CliOperationModeTable[];

typedef struct __CliWirelessmodeEntry
{
    const T_INT32 item;
    const T_CHAR* band;
    const T_CHAR* wirelessmodeName;
    const T_CHAR* wirelessmodeDescription;

}CliWirelessmodeEntry;

extern CliWirelessmodeEntry CliWirelessmodeTable[];

typedef struct __CliCountryEntry
{
    const T_CHAR* item;	
    const T_CHAR* countryName;
    const T_CHAR* countryCode;
    const T_INT32 htmodeAllow; // 0: 20/40=N/N, 2: 20/40=Y/N, 3: 20/40=Y/Y

}CliCountryEntry;
extern CliCountryEntry CliCountryTable[];
extern CliCountryEntry CliCountryTableETSI[];

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- stat main                              */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_stat[]= {
//	{OPM_ALL,	"main",		NULL,			cmdSystemmain,	"Main",				"",	AUTH_ANY, MODEL_ALL},
//	{OPM_AP,   	"client2",	cli_table_client,	getNextTable,	"2.4G Wireless client list",	"",	AUTH_ADMIN, MODEL_2G},
//	{OPM_AP,	"client5",	cli_table_client,	getNextTable,	"5G Wireless client list",	"",	AUTH_ADMIN, MODEL_5G},	
//	{OPM_ALL,	"info",		cli_table_info,		getNextTable,	"Status Information",		"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"syslog",	NULL,			cmdloginfo,	"System log",			"",     AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"help",		cli_table_stat,		cmdHelp,	"Help",				"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,   	"exit",		NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};


/*****************************************************************
* NAME: cmdsysteminfo
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID cmdsysteminfo(T_VOID)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR buf[128];
FILE *pp;
T_INT32 ssidCount;
T_INT32 i;
T_INT32 operationeMode=current_opmode;
T_INT32 nawds_index;


//Modify for C600 on 2013-05-03 to get mesh mode which is either "non-mesh" or "mesh-only"
T_CHAR func_buf2[128]="wireless.w0_index23.MESHEnable";
T_CHAR uci_get_buf2[128];
T_CHAR func_buf5[128]="wireless.w1_index23.MESHEnable";
T_CHAR uci_get_buf5[128];


//Add on 2013-10-21 by Philips to support SKU control for all models
//FILE *pp;
T_CHAR sku[10];
T_INT32 retval_int;


	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

//Display Device Name
	strcpy(func_buf, "system.@system[0].SystemName");
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	printf(CLI_STATUS, "Device Name", uci_get_buf);
	printf("\n");

//Display Ethernet MAC Address

	//Modified on 2013-04-16 by Philips for display Ethernet MAC which is requested by Jacy
	//if( (pp = popen("ifconfig | sed \'2,$d\' | awk \'{print $5}\'", "r")) == NULL ){
	if( (pp = popen("ifconfig eth0 | sed \'2,$d\' | awk \'{print $5}\'", "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	while(fgets(buf, sizeof buf, pp)){
		printf(CLI_STATUS, "Ethernet MAC", buf);
	}
	pclose(pp);

//Display 2.4G Wireless BSSID

//Modify for AP100 on 2012-11-06			
if ( strcmp(model_name, "ap100")!=0 || strcmp(current_radio_flag, "5G")!=0 )

	if (model_radio==2 || model_radio==7){
		//Get the operation mode
		operationeMode=current_opmode;
		if ( model_radio==7 )
			operationeMode=current_opmode_2;
		
		ssidCount=getModelssidCount(operationeMode);
		//Display 4 or 8 Wireless BSSID if operation mode is AP, WDSAP or AR
		if ( operationeMode==OPM_AP || operationeMode==OPM_WDSAP || operationeMode==OPM_AR){
		

//Modify for C600 on 2013-05-03 when mesh-only is enabled
strcpy(uci_get_buf2, cli_get_uci(func_buf2));
if ( (strcmp(model_name, "c600")==0) && (strcmp(uci_get_buf2, "mesh-only")==0) ){
	if( (pp = popen("ifconfig ath40 | sed \'2,$d\' | awk \'{print $5}\'", "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	while(fgets(buf, sizeof buf, pp)){
		printf(CLI_STATUS, "2.4G Wireless MAC", buf);
	}
	pclose(pp);
}
else{

		
			for (i=0; i<ssidCount; i++){		
				sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", i);
				strcpy(uci_get_buf, cli_get_uci(func_buf));
				if ( i==0 )
					printf("%25s -- %s%d ", "2.4G Wireless MAC", "BSSID", i+1);
				else
						printf("%25s -- %s%d ", " ", "BSSID", i+1);

//Modify for C600 on 2013-05-03 when mesh-only is enabled
strcpy(uci_get_buf2, cli_get_uci(func_buf2));
if ( (strcmp(model_name, "c600")==0) && (strcmp(uci_get_buf2, "mesh-ap")==0) )
	printf("%s \n", "N/A");
else {

						
				if ( atoi(uci_get_buf)==0 )
					printf("%s \n", "N/A");
				else{
					sprintf(func_buf, "ifconfig | grep ath%d | awk \'{print $5}\'", i);
					if( (pp = popen(func_buf, "r")) == NULL ){
						printf("popen() error!\n");
						exit(1);
					}
					if (fgets(uci_get_buf, sizeof uci_get_buf, pp) != 0)
						tprintf("%s", uci_get_buf);
					else
						printf("%s \n", "N/A");
					pclose(pp);
				}

				
}				

				
			}


}
			
		}
		//Display 1 Wireless BSSID if operation mode is one of the other five modes
//		if ( operationeMode==OPM_CB || operationeMode==OPM_WDSB || operationeMode==OPM_WDSSTA || operationeMode==OPM_CBRT || operationeMode==OPM_RP){
		if ( operationeMode==OPM_CB || operationeMode==OPM_WDSSTA || operationeMode==OPM_CBRT || operationeMode==OPM_RP){
			//Get the 2.4G wireless MAC of wifi0 for single radio
			sprintf(func_buf, "ifconfig -a | grep wifi%d | awk \'{print $5}\' | cut -c -17 | sed \'s/-/:/g\'", 0);
			//Get the 2.4G wireless MAC of wifi0 or wifi1 for dual radio
			if (model_radio==7)
				sprintf(func_buf, "ifconfig -a | grep wifi%d | awk \'{print $5}\' | cut -c -17 | sed \'s/-/:/g\'", getphywifi("2.4G"));
			if( (pp = popen(func_buf, "r")) == NULL ){
				printf("popen() error!\n");
				exit(1);
			}
			if (fgets(uci_get_buf, sizeof uci_get_buf, pp) != 0)
				printf(CLI_STATUS, "2.4G Wireless MAC", uci_get_buf);
			else
				printf(CLI_STATUS, "2.4G Wireless MAC", "N/A\n");
			pclose(pp);
		
		}

		//Display WDS MAC Address if operation mode is WDSBR
//		if ( operationeMode==OPM_WDSAP ){
		if ( operationeMode==OPM_WDSB || operationeMode==OPM_WDSAP ){
			//Get the MAC of br-lan
			if( (pp = popen("ifconfig | grep br-lan | awk '{print $5}'", "r")) == NULL ){
				printf("popen() error!\n");
				exit(1);
			}
			if (fgets(uci_get_buf, sizeof uci_get_buf, pp) != 0)
				printf(CLI_STATUS, "WDS MAC Address", uci_get_buf);
			else
				printf(CLI_STATUS, "WDS MAC Address", "N/A\n");
			pclose(pp);
		}

	}

//Display 5G Wireless BSSID

//Modify for AP100 on 2012-11-06			
if ( strcmp(model_name, "ap100")!=0 || strcmp(current_radio_flag, "2.4G")!=0 )

	if (model_radio==5 || model_radio==7 ){	
		//Get the operation mode
		operationeMode=current_opmode;
		if ( model_radio==7 )
			operationeMode=current_opmode_5;
			
		ssidCount=getModelssidCount(operationeMode);
		//Display 4 or 8 Wireless BSSID if operation mode is AP, WDSAP or AR
		if ( operationeMode==OPM_AP || operationeMode==OPM_WDSAP || operationeMode==OPM_AR){


//Modify for C600 on 2013-05-03 when mesh-only is enabled
strcpy(uci_get_buf5, cli_get_uci(func_buf5));
if ( (strcmp(model_name, "c600")==0) && (strcmp(uci_get_buf5, "mesh-only")==0) ){
	if( (pp = popen("ifconfig ath90 | sed \'2,$d\' | awk \'{print $5}\'", "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	while(fgets(buf, sizeof buf, pp)){
		printf(CLI_STATUS, "5G Wireless MAC", buf);
	}
	pclose(pp);
}
else{


			for (i=0; i<ssidCount; i++){
				//Modified on 2013-01-02 by Philips for display 5G MAC which is requested by Jackey
				//sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", 26+i);
				if ( model_radio==5 )		
					sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", i);
				if ( model_radio==7 )
					sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", 26+i);
				strcpy(uci_get_buf, cli_get_uci(func_buf));
				if ( i==0 )
					printf("%25s -- %s%d ", "5G Wireless MAC", "BSSID", i+1);
				else
					printf("%25s -- %s%d ", " ", "BSSID", i+1);


//Modify for C600 on 2013-05-03 when mesh-only is enabled
strcpy(uci_get_buf5, cli_get_uci(func_buf5));
if ( (strcmp(model_name, "c600")==0) && (strcmp(uci_get_buf5, "mesh-ap")==0) )
	printf("%s \n", "N/A");
else {


				if ( atoi(uci_get_buf)==0 )
					printf("%s \n", "N/A");
				else{
					//Modified on 2013-01-02 by Philips for display 5G MAC which is requested by Jackey
					//sprintf(func_buf, "ifconfig | grep ath%d | awk \'{print $5}\'", 50+i);
					if ( model_radio==5 )
						sprintf(func_buf, "ifconfig | grep ath%d | awk \'{print $5}\'", i);
					if ( model_radio==7 )	
						sprintf(func_buf, "ifconfig | grep ath%d | awk \'{print $5}\'", 50+i);
					if( (pp = popen(func_buf, "r")) == NULL ){
						printf("popen() error!\n");
						exit(1);
					}
					if (fgets(uci_get_buf, sizeof uci_get_buf, pp) != 0)
						tprintf("%s", uci_get_buf);
					else
						printf("%s \n", "N/A");
					pclose(pp);
				}

}

	
			}


}


		}
		//Display 1 Wireless BSSID if operation mode is one of the other five modes
		if ( operationeMode==OPM_CB || operationeMode==OPM_WDSB || operationeMode==OPM_WDSSTA || operationeMode==OPM_CBRT || operationeMode==OPM_RP){
			//Get the 5G wireless MAC of wifi0 for single radio
			sprintf(func_buf, "ifconfig | grep wifi%d | awk \'{print $5}\' | cut -c -17 | sed \'s/-/:/g\'", 0);
			//Get the 5G wireless MAC of wifi0 or wifi1 for dual radio
			if (model_radio==7)
				sprintf(func_buf, "ifconfig | grep wifi%d | awk \'{print $5}\' | cut -c -17 | sed \'s/-/:/g\'", getphywifi("5G"));
			if( (pp = popen(func_buf, "r")) == NULL ){
				printf("popen() error!\n");
				exit(1);
			}
			if (fgets(uci_get_buf, sizeof uci_get_buf, pp) != 0)
				printf(CLI_STATUS, "5G Wireless MAC", uci_get_buf);
			else
				printf(CLI_STATUS, "5G Wireless MAC", "N/A\n");
			pclose(pp);
		}
		
		//Display WDS MAC Address if operation mode is WDSBR
		if ( operationeMode==OPM_WDSB || operationeMode==OPM_WDSAP ){
			//Get the MAC of br-lan
			if( (pp = popen("ifconfig | grep br-lan | awk '{print $5}'", "r")) == NULL ){
				printf("popen() error!\n");
				exit(1);
			}
			if (fgets(uci_get_buf, sizeof uci_get_buf, pp) != 0)
				printf(CLI_STATUS, "WDS MAC Address", uci_get_buf);
			else
				printf(CLI_STATUS, "WDS MAC Address", "N/A\n");
			pclose(pp);
		}
	}
	
	
//Display Country
	//strcpy(func_buf, "wireless.wifi0.countryName");
	//strcpy(uci_get_buf, cli_get_uci(func_buf));
	//printf(CLI_STATUS, "Country", uci_get_buf);
	//printf("\n");


//Add on 2013-10-21 by Philips to support SKU control for all models
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
			sku[strlen(sku)-1]='\0';
			//printf("sku=%s, strlen(sku)=%d\n", sku, strlen(sku));
		}
	
	pclose(pp);


	//Modify for all models on 2013-09-27 to get country code from "wireless.wifi0.country"
	//get the country Code
	strcpy(func_buf, "wireless.wifi0.country");
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	retval_int=atoi(searchcountrytable(uci_get_buf, "INT"));
	
	//Transfer Country Name from Country Code
	strcpy(uci_get_buf, CliCountryTable[retval_int].countryName);	
	
	printf(CLI_STATUS, "Country", uci_get_buf);
	printf("\n");
	
//Display Current Time
	if( (pp = popen("date", "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	while(fgets(buf, sizeof buf, pp)){
		printf(CLI_STATUS, "Current Time", buf);
	}
	pclose(pp);
	
//Display Firmware Version
	//Get the firmware version from the file either "/etc/version_ui" or "/etc/version"
	if( (pp = popen("if [ -f /etc/version_ui ]; then cat /etc/version_ui; else cat /etc/version; fi|awk -F \".\" \'{print $1\".\"$2\".\"$3}\'", "r"))== NULL){
		printf("popen() error!\n");
		exit(1);
	}
	while(fgets(buf, sizeof buf, pp)){
		printf(CLI_STATUS, "Firmware Version", buf);
	}
	pclose(pp);

//Display Management VLAN ID
	if ( operationeMode==OPM_AP || operationeMode==OPM_WDSAP ){
		strcpy(func_buf, "network.sys.ManagementVLANID");
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if ( atoi(uci_get_buf)==4096 )
			printf(CLI_STATUS, "Management VID", "Untagged");
		else
			printf(CLI_STATUS, "Management VID", uci_get_buf);
		printf("\n");
	}
}

/*****************************************************************
* NAME: cmdlaninfo
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID cmdlaninfo(T_INT32 AR_CR)
{
T_CHAR func_buf[128];
T_CHAR buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR* ip6addr;
T_CHAR* pdns;
FILE *pp, *fp;

//Modify on 2013-03-21 for EAP300V2 to display LAN IP Setting from "dynamic runtime status" instead of "static configuration status"
//Display IP Address
//	strcpy(func_buf, "network.lan.ipaddr");
//	strcpy(uci_get_buf, cli_get_uci(func_buf));
//	printf(CLI_STATUS, "IP Address", uci_get_buf);
//	printf("\n");

//Display IP Address
	if( (pp = popen("ifconfig br-lan | grep \"inet addr\" | awk -F \" \" '{print $2}' | awk -F \":\" '{print $2}'", "r"))== NULL){
		printf("popen() error!\n");
		exit(1);
	}
	while(fgets(buf, sizeof buf, pp)){
		printf(CLI_STATUS, "IP Address", buf);
	}
	pclose(pp);

//Modify on 2013-03-21 for EAP300V2 to display LAN IP Setting from "dynamic runtime status" instead of "static configuration status"
//Display Subnet Mask
//	strcpy(func_buf, "network.lan.netmask");
//	strcpy(uci_get_buf, cli_get_uci(func_buf));
//	printf(CLI_STATUS, "Subnet Mask", uci_get_buf);
//	printf("\n");

//Display Subnet Mask
	if( (pp = popen("ifconfig br-lan | grep \"inet addr\" | awk -F \" \" '{print $4}' | awk -F \":\" '{print $2}'", "r"))== NULL){
		printf("popen() error!\n");
		exit(1);
	}
	while(fgets(buf, sizeof buf, pp)){
		printf(CLI_STATUS, "Subnet Mask", buf);
	}
	pclose(pp);

	//Determine the protocol is "dhcp" or "static" 
	strcpy(func_buf, "network.lan.proto");
	strcpy(uci_get_buf1, cli_get_uci(func_buf));
		
	if (AR_CR == 0){
	
	//Modify on 2013-03-21 for EAP300V2 to display LAN IP Setting from "dynamic runtime status" instead of "static configuration status"	
	//Display Default Gateway
	//	strcpy(func_buf, "network.lan.gateway");
	//	strcpy(uci_get_buf, cli_get_uci(func_buf));
	//	if ( strcmp(uci_get_buf1, "static")==0 ){
	//		printf(CLI_STATUS, "Default Gateway", uci_get_buf);
	//		printf("\n");
	//	}
	//	else {
	//		printf(CLI_STATUS, "Default Gateway", " ");
	//		printf("\n");
	//	}

//Display Default Gateway
//	if( (pp = popen("route | grep default | awk -F \" \" '{print $2}'", "r"))== NULL){


	//Modify on 2013-09-05 for EAP900H to display IPV6 when DHCP
	if( (pp = popen("route -n| grep UG | awk -F \" \" '{print $2}'", "r"))== NULL){
		printf("popen() error!\n");
		exit(1);
	}
	while(fgets(buf, sizeof buf, pp)){
		printf(CLI_STATUS, "Default Gateway", buf);
	}
	pclose(pp);
	
	//Modify on 2013-03-21 for EAP300V2 to display LAN IP Setting from "dynamic runtime status" instead of "static configuration status"			
	//Display Primary DNS
	//	strcpy(func_buf, "network.lan.dns");
	//	strcpy(uci_get_buf, cli_get_uci(func_buf));
	//	if ( strcmp(uci_get_buf1, "static")==0 ){
	//		printf(CLI_STATUS, "Primary DNS", strtok(uci_get_buf, " "));
	//		printf("\n");
	//	}
	//	else {
	//		printf(CLI_STATUS, "Primary DNS", " ");
	//		printf("\n");
	//	}
		
//Display Primary DNS
	//Get the DNS from the file either "/tmp/resolv.conf" or "/tmp/resolv.conf.auto"
	if ( strcmp(uci_get_buf1, "static")==0 )
		sprintf(buf, "cat %s | grep -E '^nameserver.*\.' | grep -v '127.0.0.1' | sed -n '1,1p' | cut -d ' ' -f 2", "/tmp/resolv.conf");
	else {
		if((fp = fopen("/tmp/resolv.conf.auto", "r"))==NULL)
			sprintf(buf, "cat %s | grep -E '^nameserver.*\.' | grep -v '127.0.0.1' | sed -n '1,1p' | cut -d ' ' -f 2", "/tmp/resolv.conf");
		else
			sprintf(buf, "cat %s | grep -E '^nameserver.*\.' | grep -v '127.0.0.1' | sed -n '1,1p' | cut -d ' ' -f 2", "/tmp/resolv.conf.auto");
	}
			
	if( (pp = popen(buf, "r"))== NULL){
		printf("popen() error!\n");
		exit(1);
	}
	while(fgets(buf, sizeof buf, pp)){
		printf(CLI_STATUS, "Primary DNS", buf);
	}
	pclose(pp);
		
	//Display Secondary DNS
	//	if ( strcmp(uci_get_buf1, "static")==0 ){
	//		printf(CLI_STATUS, "Secondary DNS", strtok(NULL, " "));
	//		printf("\n");
	//	}
	//	else {
	//		printf(CLI_STATUS, "Secondary DNS", " ");
	//		printf("\n");
	//	}
		
//Display Secondary DNS
	//Get the DNS from the file either "/tmp/resolv.conf" or "/tmp/resolv.conf.auto"		
	if ( strcmp(uci_get_buf1, "static")==0 )
		sprintf(buf, "cat %s | grep -E \"^nameserver.*\\.\" | grep -v \"127.0.0.1\" | sed -n \"2,2p\" | cut -d \" \" -f 2", "/tmp/resolv.conf");
	else {
		if((fp = fopen("/tmp/resolv.conf.auto", "r"))==NULL)
			sprintf(buf, "cat %s | grep -E \"^nameserver.*\\.\" | grep -v \"127.0.0.1\" | sed -n \"2,2p\" | cut -d \" \" -f 2", "/tmp/resolv.conf");
		else
			sprintf(buf, "cat %s | grep -E \"^nameserver.*\\.\" | grep -v \"127.0.0.1\" | sed -n \"2,2p\" | cut -d \" \" -f 2", "/tmp/resolv.conf.auto");
	}
	
	if( (pp = popen(buf, "r"))== NULL){
		printf("popen() error!\n");
		exit(1);
	}
	fgets(uci_get_buf, sizeof uci_get_buf, pp);
	pclose(pp);
	if( strlen(uci_get_buf)!=0 )
		printf(CLI_STATUS, "Secondary DNS", uci_get_buf);
	else{
		printf(CLI_STATUS, "Secondary DNS", uci_get_buf);
		printf("\n");
	}
	
	//Display DHCP Client
		if ( strcmp(uci_get_buf1, "static")==0 )
			printf(CLI_STATUS, "DHCP Client", "Disabled");
		else
			printf(CLI_STATUS, "DHCP Client", "Enabled");
		printf("\n");
	//Display Spanning Tree Protocol
		strcpy(func_buf, "network.lan.stp");
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if ( atoi(uci_get_buf)==0 )
			printf(CLI_STATUS, "Spanning Tree", "Disabled");
		else
			printf(CLI_STATUS, "Spanning Tree", "Enabled");
		printf("\n");
	}


//Modify on 2013-02-07 for EAP300V2, C600, EAP900 and ENH900EXT to display IPV6
//#define MODEL_IPV6	(ENS202_ID|ENS202EXT_ID|EAP600_ID|ECB600_ID|ENS500_ID|ENS500EXT_ID|ENH510_ID|EAP300V2_ID|C600_ID|EAP900_ID|ENH900EXT_ID)

	//Modify on 2012-10-24 for IPV6 of ENS202EXT
	//if ( strcmp(model_name, "ens202")==0 || strcmp(model_name, "ens202ext")==0 || strcmp(model_name, "eap600")==0 || strcmp(model_name, "ecb600")==0 || strcmp(model_name, "ens500")==0 || strcmp(model_name, "ens500ext")==0 || strcmp(model_name, "enh510")==0 ){
	
	if( model_ID & MODEL_IPV6 ){
	//Display IPv6 Address
		strcpy(func_buf, "network.lan.ip6addr");
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		ip6addr = strtok(uci_get_buf, "/");
		if ( strcmp(uci_get_buf1, "static")==0 ){
			printf(CLI_STATUS, "IPv6 Address", uci_get_buf);
			printf("\n");
		}
		else {
//			printf(CLI_STATUS, "IPv6 Address", "None");
//			printf("\n");


//Modify on 2013-09-05 for EAP900H to display IPV6 when DHCP		
			if( (pp = popen("ip -6 addr show br-lan | grep \'scope global\' | sed -n \'1p\' | sed \'s/^.*inet6 //g\' | sed \'s/\\/.*$//g\'", "r")) == NULL ){
				printf("popen() error!\n");
				exit(1);
			}
			while(fgets(buf, sizeof buf, pp)){
				printf(CLI_STATUS, "IPv6 Address", buf);
			}
			pclose(pp);
		
		}
	//Display IPv6 Link-Local Address
		if( (pp = popen("ifconfig br-lan| grep Scope:Link | awk '{print $3 }' | sed s#/[0-9]*##", "r")) == NULL ){
			printf("popen() error!\n");
			exit(1);
		}
		fgets(uci_get_buf, sizeof uci_get_buf, pp);
		pclose(pp);	
		printf(CLI_STATUS, "IPv6 Link-Local Address", uci_get_buf);
	//Display IPv6 Default Gateway
		strcpy(func_buf, "network.lan.ip6gw");
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if ( strcmp(uci_get_buf1, "static")==0 ){		
			printf(CLI_STATUS, "IPv6 Default Gateway", uci_get_buf);
			printf("\n");
		}
		else {
//			printf(CLI_STATUS, "IPv6 Default Gateway", " ");
//			printf("\n");


//Modify on 2013-09-05 for EAP900H to display IPV6 when DHCP		
			if( (pp = popen("ip -6 route show default | grep \'br-lan\' | sed -n \'1p\' | sed \'s/^.*via //g\' | sed \'s/ .*$//g\'", "r")) == NULL )
			{
				printf("popen() error!\n");
				exit(1);
			}
			while(fgets(buf, sizeof buf, pp)){
				printf(CLI_STATUS, "IPv6 Default Gateway", buf);
			}
			pclose(pp);
		
		}		
	//Display IPv6 Primary DNS
		strcpy(func_buf, "network.lan.dns");
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		pdns = strtok(uci_get_buf, " ");
		pdns = strtok(NULL, " ");
		pdns = strtok(NULL, " ");

		if ( strcmp(uci_get_buf1, "static")==0 ){
			printf(CLI_STATUS, "IPv6 Primary DNS", pdns);
			printf("\n");
		}
		else {
//			printf(CLI_STATUS, "IPv6 Primary DNS", " ");
//			printf("\n");	


//Modify on 2013-09-05 for EAP900H to display IPV6 when DHCP
			if( (pp = popen("cat /tmp/resolv.conf.auto | grep -E \'^nameserver.*:\' | grep -wv \'::1\' | sed -n \'1,1p\' | cut -d \' \' -f 2", "r")) == NULL ){
				printf("popen() error!\n");
				exit(1);
			}
			while(fgets(buf, sizeof buf, pp)){
				printf(CLI_STATUS, "IPv6 Primary DNS", buf);
			}
			pclose(pp);
	
		}			
	//Display "IPv6 Secondary DNS
		if ( strcmp(uci_get_buf1, "static")==0 ){	
			printf(CLI_STATUS, "IPv6 Secondary DNS", strtok(NULL, " "));
			printf("\n");
		}
		else {
//			printf(CLI_STATUS, "IPv6 Secondary DNS", " ");
//			printf("\n");

//Modify on 2013-09-05 for EAP900H to display IPV6 when DHCP
			if( (pp = popen("cat /tmp/resolv.conf.auto | grep -E \'^nameserver.*:\' | grep -wv \'::1\' | sed -n \'2,2p\' | cut -d \' \' -f 2", "r")) == NULL ){
				printf("popen() error!\n");
				exit(1);
			}
			while(fgets(buf, sizeof buf, pp)){
				printf(CLI_STATUS, "IPv6 Secondary DNS", buf);
			}
			pclose(pp);				

		}

	}
	
//Display RX(Packets)  581.409 KB (6671 PKts.) 
	if( (pp = popen("ifconfig br-lan | grep \"RX bytes\" | awk '{print $3 " " $4}' | sed s#\\(## | sed s#\\)## | sed s#i##", "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	fgets(uci_get_buf, sizeof uci_get_buf, pp);
	pclose(pp);
	if( (pp = popen("ifconfig br-lan | grep \"RX packets\" | awk '{print $2}' | sed s#packets:##", "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	fgets(uci_get_buf1, sizeof uci_get_buf1, pp);
	pclose(pp);
	uci_get_buf[strlen(uci_get_buf)-1]='\0';
	uci_get_buf1[strlen(uci_get_buf1)-1]='\0';
	printf("%25s -- %s (%s Packets)\n", "RX(Packets)", uci_get_buf, uci_get_buf1);

//Display TX(Packets)  581.409 KB (6671 PKts.) 
	if( (pp = popen("ifconfig br-lan | grep \"TX bytes\" | awk '{print $7 " " $8}' | sed s#\\(## | sed s#\\)## | sed s#i##", "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	fgets(uci_get_buf, sizeof uci_get_buf, pp);
	pclose(pp);
	if( (pp = popen("ifconfig br-lan | grep \"TX packets\" | awk '{print $2}' | sed s#packets:##", "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	fgets(uci_get_buf1, sizeof uci_get_buf1, pp);
	pclose(pp);
	uci_get_buf[strlen(uci_get_buf)-1]='\0';
	uci_get_buf1[strlen(uci_get_buf1)-1]='\0';
	printf("%25s -- %s (%s Packets)\n", "TX(Packets)", uci_get_buf, uci_get_buf1);
	
}

/*****************************************************************
* NAME: cmdwaninfo
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID cmdwaninfo(T_VOID)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];

//Display IP Address
	strcpy(func_buf, "network.wan.ipaddr");
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	printf(CLI_STATUS, "IP Address", uci_get_buf);
	printf("\n");
//Display Subnet Mask
	strcpy(func_buf, "network.wan.netmask");
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	printf(CLI_STATUS, "Subnet Mask", uci_get_buf);
	printf("\n");
//Display Default Gateway
	strcpy(func_buf, "network.wan.gateway");
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	printf(CLI_STATUS, "Default Gateway", uci_get_buf);
	printf("\n");
//Display Primary DNS
	strcpy(func_buf, "network.lan.dns");
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	printf(CLI_STATUS, "Primary DNS", strtok(uci_get_buf, " "));
	printf("\n");
//Display Secondary DNS
	printf(CLI_STATUS, "Secondary DNS", strtok(NULL, " "));
	printf("\n");
}

/*****************************************************************
* NAME: cmdwless2info
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID cmdwless2info(T_INT32 operationeMode)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR buf[128];
T_CHAR buf1[128];
T_CHAR buf2[128];
T_CHAR buf3[128];
T_CHAR buf4[128];
T_CHAR buf5[128];
FILE *pp;
T_INT32 ssidCount;
T_INT32 i;
T_INT32 ath_interface;
T_INT32 nawds_index;
T_CHAR * ptr;
T_CHAR * dummy="";


//Modify for C600 on 2013-05-03 to get mesh mode which is either "non-mesh" or "mesh-only"
T_CHAR func_buf2[128]="wireless.w0_index23.MESHEnable";
T_CHAR uci_get_buf2[128];

//printf("In 2.4G --- current_radio_flag=%s\n", current_radio_flag);
//printf("In 2.4G --- operationeMode=%d\n", operationeMode);

	ssidCount=getModelssidCount(operationeMode);
	
//Display Operation Mode

//Modify for C600 on 2013-05-03 when mesh-only is enabled
strcpy(uci_get_buf2, cli_get_uci(func_buf2));
if ( (strcmp(model_name, "c600")==0) && (strcmp(uci_get_buf2, "mesh-only")==0) ){
	printf(CLI_STATUS, "Operation Mode", uci_get_buf2);
	printf("\n");
}
else{


	if (model_radio==2)
		strcpy(func_buf, "network.sys.opmode");
	else
		strcpy(func_buf, "wireless.wifi0.opmode");
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	
	for (i=0; i<SYS_OPM_COUNT; i++)
		if ( strcmp(uci_get_buf, CliOperationModeTable[i].operationmode)==0 )
			break;			
	strcpy(uci_get_buf, CliOperationModeTable[i].operationmodeName);
	
	printf(CLI_STATUS, "Operation Mode", uci_get_buf);
	printf("\n");
}

	
//Display Wireless Mode
	strcpy(func_buf, "wireless.wifi0.hwmode");
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	
	for (i=0; i<8; i++)
		if ( strcmp(uci_get_buf, CliWirelessmodeTable[i].wirelessmodeName)==0 )
			break;			
	strcpy(uci_get_buf, CliWirelessmodeTable[i].wirelessmodeDescription);
	
	printf(CLI_STATUS, "Wireless Mode", uci_get_buf);
	printf("\n");
	
//Display Channel Bandwidth
	strcpy(func_buf, "wireless.wifi0.WLANHTMode");
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	printf(CLI_STATUS, "Channel Bandwidth", uci_get_buf);
	printf(" MHz\n");

/*		
//Display Frequency/Channel
		if( (pp = popen("iwlist ath0 channel | grep Current | awk '{print $2}'", "r")) == NULL ){
			printf("popen() error!\n");
			exit(1);
		}
		while(fgets(buf, sizeof buf, pp)){
			if ( atoi(buf)<10 )
				printf("atoi(buf)=%d\n", atoi(buf));
//			sprintf(buf1, "iwlist ath0 channel | grep \\\"Channel 0%s \\\" | awk \\\'{print $4 $5 \\\"(\\\"$1 $2\\\")\\\"}\\\'", buf);
sprintf(buf1, "iwlist ath0 channel | grep \"Channel 0%s \" | awk \'{print $4 $5 \"(\"$1 $2\")\"}\'", buf);
//			printf("buf1 = %s", buf1);
			printf(CLI_STATUS, "Frequency/Channel", system(buf1));
//printf(CLI_STATUS, "Frequency/Channel", system("iwlist ath0 channel | grep \"Channel 05 \" | awk \'{print $4 $5 \"(\"$1 $2\")\"}\'"));
		}
		
		pclose(pp);
*/

//Display Profile


//Modify for C600 on 2013-05-03 when mesh-only is enabled
if ( (strcmp(model_name, "c600")==0) && (strcmp(uci_get_buf2, "mesh-only")==0) ){
T_CHAR func_buf[128]="wireless.w0_index23.ssid";
T_CHAR func_buf1[128]="wireless.w0_index23.encryption";
	
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	printf(CLI_STATUS, "Mesh SSID", uci_get_buf);
	printf("\n");
		
	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	printf(CLI_STATUS, "Mesh Security", uci_get_buf);
	printf("\n");		
}
else{


	if ( operationeMode==OPM_AP || operationeMode==OPM_WDSAP || operationeMode==OPM_AR){
		for (i=0; i<ssidCount; i++){		
			sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", i);
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			if ( i==0 )
				printf("%25s -- %s%d ", "Profile settings", "ESSID", i+1);
			else
				printf("%25s -- %s%d ", " ", "ESSID", i+1);
			if ( atoi(uci_get_buf)==0 ){
				printf("%s \n", "N/A");
			}
			else{
				sprintf(func_buf, "wireless.@wifi-iface[%d].ssid", i);
				strcpy(uci_get_buf, cli_get_uci(func_buf));
				tprintf("%s\n", uci_get_buf);
			}	
		}
	}

}

//Display Distance


//Modify on 2013-07-02 by Philips to skip the distance display which is requested by Jacy for EAP600 and ECB600
//if ( strcmp(model_name, "eap600")==0 || strcmp(model_name, "ecb600")==0 )

//Modify on 2013-08-09 by Philips to skip the distance display which is requested by Jacy for all indoor models
if ( model_ID & MODEL_INDOOR )
	i=0;
else{


	strcpy(func_buf, "wireless.wifi0.distance");
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	printf("%25s -- %d Km\n", "Distance", atoi(uci_get_buf)/1000);
	
}


/*
	if ( operationeMode==OPM_AP || operationeMode==OPM_CB || operationeMode==OPM_WDSAP || operationeMode==OPM_AR || operationeMode==OPM_CBRT || operationeMode==OPM_WDSSTA || operationeMode==OPM_RP ){
			ath_interface = 0;
	}
	else if ( operationeMode==OPM_WDSB ) {
		//get 4 (if ssidcount is 4) or 16 (if ssidcount is 8) for single-radio and 16 (if radio is 2.4G) or 42 (if radio is 5G) for dual-radio
		nawds_index=get_nawds_index(ssidCount, operationeMode);
		
		//Get WDS link information
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSPeer", nawds_index);

		strcpy(uci_get_buf, cli_get_uci(func_buf));

		//Check whether all WDS links are disabled
		ptr = strchr(uci_get_buf, 'v');
		//AT LEASE ONE OF WDS LINKS IS ENABLED		
		if ( ptr != NULL ){
			ath_interface = 20;
		}
		//ALL WDS LINKS ARE DISABLED		
		else {
			if (model_radio==2){
				dummy="dummy";
				ath_interface = 0;
			}
			else
				ath_interface = 49;
		}
	}


//Modify for C600 on 2013-05-03 when mesh-only is enabled
if ( (strcmp(model_name, "c600")==0) && (strcmp(uci_get_buf2, "mesh-only")==0) ){
	ath_interface = 40;
}
		
	sprintf(buf2, "ifconfig ath%s%d | grep \"RX bytes\" | awk \'{print $3 \" \" $4}\' | sed s#\\(## | sed s#\\)## | sed s#i##", dummy, ath_interface);
	sprintf(buf3, "ifconfig ath%s%d | grep \"RX packets\" | awk \'{print $2}\' | sed s#packets:##", dummy, ath_interface);
	sprintf(buf4, "ifconfig ath%s%d | grep \"TX bytes\" | awk \'{print $7 \" \" $8}\' | sed s#\\(## | sed s#\\)## | sed s#i##", dummy, ath_interface);
	sprintf(buf5, "ifconfig ath%s%d | grep \"TX packets\" | awk \'{print $2}\' | sed s#packets:##", dummy, ath_interface);
		
	if( (pp = popen(buf2, "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	fgets(uci_get_buf, sizeof uci_get_buf, pp);
	pclose(pp);

	if( (pp = popen(buf3, "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	fgets(uci_get_buf1, sizeof uci_get_buf1, pp);
	pclose(pp);
	uci_get_buf[strlen(uci_get_buf)-1]='\0';
	uci_get_buf1[strlen(uci_get_buf1)-1]='\0';
	printf("%25s -- %s (%s Packets)\n", "RX(Packets)", uci_get_buf, uci_get_buf1);

		
//Display TX(Packets)  581.409 KB (6671 PKts.) 
	if( (pp = popen(buf4, "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	fgets(uci_get_buf, sizeof uci_get_buf, pp);
	pclose(pp);

	if( (pp = popen(buf5, "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	fgets(uci_get_buf1, sizeof uci_get_buf1, pp);
	pclose(pp);
	uci_get_buf[strlen(uci_get_buf)-1]='\0';
	uci_get_buf1[strlen(uci_get_buf1)-1]='\0';
	printf("%25s -- %s (%s Packets)\n", "TX(Packets)", uci_get_buf, uci_get_buf1);

*/


//Display RX(Packets)  581.409 KB (6671 PKts.) and TX(Packets)  581.409 KB (6671 PKts.)

//Modify on 2013-08-13 by Philips for c600 and eap900h to get correct wifi interface of 2.4G
sprintf(buf1, "iwconfig 2>/dev/null |grep -E \"^ath[^ ]+.*(11b|11g|11ng)\" |head -n 1 |awk \'{print $1}\'");
if( (pp = popen(buf1, "r")) == NULL ){
	printf("popen() error!\n");
	exit(1);
}
fgets(uci_get_buf, sizeof uci_get_buf, pp);
pclose(pp);	
uci_get_buf[strlen(uci_get_buf)-1]='\0';

sprintf(buf2, "ifconfig %s | grep \"RX bytes\" | awk \'{print $3 \" \" $4}\' | sed s#\\(## | sed s#\\)## | sed s#i##", uci_get_buf);
sprintf(buf3, "ifconfig %s | grep \"RX packets\" | awk \'{print $2}\' | sed s#packets:##", uci_get_buf);
sprintf(buf4, "ifconfig %s | grep \"TX bytes\" | awk \'{print $7 \" \" $8}\' | sed s#\\(## | sed s#\\)## | sed s#i##", uci_get_buf);
sprintf(buf5, "ifconfig %s | grep \"TX packets\" | awk \'{print $2}\' | sed s#packets:##", uci_get_buf);

//Display RX(Packets)  581.409 KB (6671 PKts.)

if( (pp = popen(buf2, "r")) == NULL ){
	printf("popen() error!\n");
	exit(1);
}
fgets(uci_get_buf, sizeof uci_get_buf, pp);
pclose(pp);

if( (pp = popen(buf3, "r")) == NULL ){
	printf("popen() error!\n");
	exit(1);
}
fgets(uci_get_buf1, sizeof uci_get_buf1, pp);
pclose(pp);

uci_get_buf[strlen(uci_get_buf)-1]='\0';
uci_get_buf1[strlen(uci_get_buf1)-1]='\0';
printf("%25s -- %s (%s Packets)\n", "RX(Packets)", uci_get_buf, uci_get_buf1);


//Display TX(Packets)  581.409 KB (6671 PKts.) 

if( (pp = popen(buf4, "r")) == NULL ){
	printf("popen() error!\n");
	exit(1);
}
fgets(uci_get_buf, sizeof uci_get_buf, pp);
pclose(pp);

if( (pp = popen(buf5, "r")) == NULL ){
	printf("popen() error!\n");
	exit(1);
}
fgets(uci_get_buf1, sizeof uci_get_buf1, pp);
pclose(pp);

uci_get_buf[strlen(uci_get_buf)-1]='\0';
uci_get_buf1[strlen(uci_get_buf1)-1]='\0';
printf("%25s -- %s (%s Packets)\n", "TX(Packets)", uci_get_buf, uci_get_buf1);

}

/*****************************************************************
* NAME: cmdwless5info
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID cmdwless5info(T_INT32 operationeMode)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR buf[128];
T_CHAR buf1[128];
T_CHAR buf2[128];
T_CHAR buf3[128];
T_CHAR buf4[128];
T_CHAR buf5[128];
FILE *pp;
T_INT32 ssidCount;
T_INT32 i;
T_INT32 ath_interface;
T_INT32 nawds_index;
T_CHAR * ptr;
T_CHAR * dummy="";


//Modify for C600 on 2013-05-03 to get mesh mode which is either "non-mesh" or "mesh-only"
T_CHAR func_buf5[128]="wireless.w1_index23.MESHEnable";
T_CHAR uci_get_buf5[128];

//printf("In 5G --- current_radio_flag=%s\n", current_radio_flag);
//printf("In 5G --- operationeMode=%d\n", operationeMode);


	ssidCount=getModelssidCount(operationeMode);

	
//Display Operation Mode


//Modify for C600 on 2013-05-03 when mesh-only is enabled
strcpy(uci_get_buf5, cli_get_uci(func_buf5));
if ( (strcmp(model_name, "c600")==0) && (strcmp(uci_get_buf5, "mesh-only")==0) ){
	printf(CLI_STATUS, "Operation Mode", uci_get_buf5);
	printf("\n");
}
else{


	if (model_radio==5)
		strcpy(func_buf, "network.sys.opmode");
	else
		strcpy(func_buf, "wireless.wifi1.opmode");
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	
	for (i=0; i<SYS_OPM_COUNT; i++)
		if ( strcmp(uci_get_buf, CliOperationModeTable[i].operationmode)==0 )
			break;			
	strcpy(uci_get_buf, CliOperationModeTable[i].operationmodeName);
	
	printf(CLI_STATUS, "Operation Mode", uci_get_buf);
	printf("\n");


}

//Display Wireless Mode
	//strcpy(func_buf, "wireless.wifi1.hwmode");
	//Modify on 2012-12-18 by Philips which is requested by Jackey for ENH500
	if (model_radio==5)
		strcpy(func_buf, "wireless.wifi0.hwmode");
	else
		strcpy(func_buf, "wireless.wifi1.hwmode");
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	
//	printf(CLI_STATUS, "Wireless Mode", uci_get_buf);
	printf(CLI_STATUS, "Wireless Mode", searchwirelessmode(uci_get_buf));	
	printf("\n");

//Display Channel Bandwidth
	//strcpy(func_buf, "wireless.wifi1.WLANHTMode");
	//Modify on 2012-12-18 by Philips which is requested by Jackey for ENH500
	if (model_radio==5)
		strcpy(func_buf, "wireless.wifi0.WLANHTMode");
	else
		strcpy(func_buf, "wireless.wifi1.WLANHTMode");	
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	printf(CLI_STATUS, "Channel Bandwidth", uci_get_buf);
	printf(" MHz\n");
/*		
//Display Frequency/Channel
		if( (pp = popen("iwlist ath50 channel | grep Current| awk '{print $2}'", "r")) == NULL ){
			printf("popen() error!\n");
			exit(1);
		}
		while(fgets(buf, sizeof buf, pp)){
			sprintf(buf1, "iwlist ath50 channel | grep \"Channel %s\" | awk \'{print $4 $5  $1 \" \" $2}\'", buf);
//			sprintf(buf1, "iwlist ath50 channel | grep \\\"Channel %s\\\" | awk \\\'{print $4 $5 \\\"(\\\"$1 \\\" \\\" $2\\\")\\\"}\\\'", buf);
//			printf("buf1 = %s", buf1);
//			printf(CLI_STATUS, "Frequency/Channel", system("iwlist ath50 channel | grep \"Channel 108\" | awk \'{print $4 $5 \"(\"$1 $2\")\"}\'"));
		}
		pclose(pp);
		printf("buf1=%s, length=%d\n", buf1, strlen(buf1));
//		if ( (pp = popen("iwlist ath50 channel | grep \"Channel 108\" | awk \'{print $4 $5 \"(\"$1 \" \" $2\")\"}\'", "r")) == NULL ){
		if ( (pp = popen("iwlist ath50 channel | grep \"Channel 108\" | awk \'{print $4 $5  $1 \" \" $2}\'", "r")) == NULL ){
			printf("popen() error!\n");
			exit(1);
		}
		while(fgets(buf, sizeof buf, pp)){
			printf(CLI_STATUS, "Frequency/Channel", buf);
		}		
		
		pclose(pp);

		if( (pp = popen(buf1, "r")) == NULL ){
			printf("popen() error!\n");
			exit(1);
		}
		while(fgets(buf, sizeof buf, pp)){
			printf(CLI_STATUS, "Frequency/Channel", buf);
		}		
		
		pclose(pp);
	*/
//Display Profile


//Modify for C600 on 2013-05-03 when mesh-only is enabled
if ( (strcmp(model_name, "c600")==0) && (strcmp(uci_get_buf5, "mesh-only")==0) ){
T_CHAR func_buf[128]="wireless.w1_index23.ssid";
T_CHAR func_buf1[128]="wireless.w1_index23.encryption";
	
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	printf(CLI_STATUS, "Mesh SSID", uci_get_buf);
	printf("\n");
		
	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	printf(CLI_STATUS, "Mesh Security", uci_get_buf);
	printf("\n");		
}
else{


	if ( operationeMode==OPM_AP || operationeMode==OPM_WDSAP || operationeMode==OPM_AR){
		for (i=0; i<ssidCount; i++){
			//Modified on 2013-01-02 by Philips for display 5G MAC which is requested by Jackey
			//sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", 26+i);
			if ( model_radio==5 )		
				sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", i);
			if ( model_radio==7 )
				sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", 26+i);
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			if ( i==0 )
				printf("%25s -- %s%d ", "Profile settings", "ESSID", i+1);
			else
				printf("%25s -- %s%d ", " ", "ESSID", i+1);
		
			if ( atoi(uci_get_buf)==0 ){
				printf("%s \n", "N/A");
			}
			else{
				//Modified on 2013-01-02 by Philips for display 5G MAC which is requested by Jackey
				//sprintf(func_buf, "wireless.@wifi-iface[%d].ssid", 26+i);
				if ( model_radio==5 )
					sprintf(func_buf, "wireless.@wifi-iface[%d].ssid", i);
				if ( model_radio==7 )
					sprintf(func_buf, "wireless.@wifi-iface[%d].ssid", 26+i);
				strcpy(uci_get_buf, cli_get_uci(func_buf));
				tprintf("%s\n", uci_get_buf);
			}	
		}
	}


}

//Display Distance


//Modify on 2013-07-02 by Philips to skip the distance display which is requested by Jacy for EAP600 and ECB600
//if ( strcmp(model_name, "eap600")==0 || strcmp(model_name, "ecb600")==0 )

//Modify on 2013-08-09 by Philips to skip the distance display which is requested by Jacy for all indoor models
if ( model_ID & MODEL_INDOOR )
	i=0;
else{


	//strcpy(func_buf, "wireless.wifi0.distance");
	//Modify on 2012-12-18 by Philips which is requested by Jackey for ENH500
	if (model_radio==5)
		strcpy(func_buf, "wireless.wifi0.distance");
	else
		strcpy(func_buf, "wireless.wifi1.distance");
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	printf("%25s -- %d Km\n", "Distance", atoi(uci_get_buf)/1000);


}	

/*

//Modify on 2012-12-18 by Philips which is requested by Jackey for ENH500
//Display RX(Packets)  581.409 KB (6671 PKts.)
	if ( operationeMode==OPM_AP || operationeMode==OPM_CB || operationeMode==OPM_WDSAP || operationeMode==OPM_AR || operationeMode==OPM_CBRT || operationeMode==OPM_WDSSTA || operationeMode==OPM_RP ){
		if (model_radio==5)
			ath_interface = 0;
		else
			ath_interface = 50;
	}
	else if ( operationeMode==OPM_WDSB ) {
		//get 4 (if ssidcount is 4) or 16 (if ssidcount is 8) for single-radio and 16 (if radio is 2.4G) or 42 (if radio is 5G) for dual-radio
		nawds_index=get_nawds_index(ssidCount, operationeMode);


//printf("In 5G --- nawds_index=%d\n", nawds_index);
		
		//Get WDS link information
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSPeer", nawds_index);
		
		strcpy(uci_get_buf, cli_get_uci(func_buf));

		//Check whether if one of NAWDS is enabled 
		ptr = strchr(uci_get_buf, 'v');
		//AT LEASE ONE OF WDS LINKS IS ENABLED
		if ( ptr != NULL ) {
			if (model_radio==5)
				ath_interface = 20;
			else
				ath_interface = 70;
		}
		//ALL WDS LINKS ARE DISABLED
		else {
			if (model_radio==5){
				dummy="dummy";
				ath_interface = 0;
			}
			else
				ath_interface = 99;
		}
		
	}

//printf("In 5G --- dummy=%s, ath_interface=%d\n", dummy, ath_interface);

//Modify for C600 on 2013-05-03 when mesh-only is enabled
if ( (strcmp(model_name, "c600")==0) && (strcmp(uci_get_buf5, "mesh-only")==0) ){
T_CHAR func_buf[128]="wireless.w1_index23.MESHEnable";
	ath_interface = 90;
}
	
	sprintf(buf2, "ifconfig ath%s%d | grep \"RX bytes\" | awk \'{print $3 \" \" $4}\' | sed s#\\(## | sed s#\\)## | sed s#i##", dummy, ath_interface);
	sprintf(buf3, "ifconfig ath%s%d | grep \"RX packets\" | awk \'{print $2}\' | sed s#packets:##", dummy, ath_interface);
	sprintf(buf4, "ifconfig ath%s%d | grep \"TX bytes\" | awk \'{print $7 \" \" $8}\' | sed s#\\(## | sed s#\\)## | sed s#i##", dummy, ath_interface);
	sprintf(buf5, "ifconfig ath%s%d | grep \"TX packets\" | awk \'{print $2}\' | sed s#packets:##", dummy, ath_interface);
	
	if( (pp = popen(buf2, "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	fgets(uci_get_buf, sizeof uci_get_buf, pp);
	pclose(pp);

	if( (pp = popen(buf3, "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	fgets(uci_get_buf1, sizeof uci_get_buf1, pp);
	pclose(pp);
	uci_get_buf[strlen(uci_get_buf)-1]='\0';
	uci_get_buf1[strlen(uci_get_buf1)-1]='\0';
	printf("%25s -- %s (%s Packets)\n", "RX(Packets)", uci_get_buf, uci_get_buf1);
		
//Display TX(Packets)  581.409 KB (6671 PKts.) 
	if( (pp = popen(buf4, "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	fgets(uci_get_buf, sizeof uci_get_buf, pp);
	pclose(pp);

	if( (pp = popen(buf5, "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}
	fgets(uci_get_buf1, sizeof uci_get_buf1, pp);
	pclose(pp);
	uci_get_buf[strlen(uci_get_buf)-1]='\0';
	uci_get_buf1[strlen(uci_get_buf1)-1]='\0';
	printf("%25s -- %s (%s Packets)\n", "TX(Packets)", uci_get_buf, uci_get_buf1);

*/


//Display RX(Packets)  581.409 KB (6671 PKts.) and TX(Packets)  581.409 KB (6671 PKts.)

//Modify on 2013-08-13 by Philips for c600 and eap900h to get correct wifi interface of 5G
sprintf(buf1, "iwconfig 2>/dev/null |grep -E \"^ath[^ ]+.*(11a|11na)\" |head -n 1 |awk \'{print $1}\'");
if( (pp = popen(buf1, "r")) == NULL ){
	printf("popen() error!\n");
	exit(1);
}
fgets(uci_get_buf, sizeof uci_get_buf, pp);
pclose(pp);	
uci_get_buf[strlen(uci_get_buf)-1]='\0';

sprintf(buf2, "ifconfig %s | grep \"RX bytes\" | awk \'{print $3 \" \" $4}\' | sed s#\\(## | sed s#\\)## | sed s#i##", uci_get_buf);
sprintf(buf3, "ifconfig %s | grep \"RX packets\" | awk \'{print $2}\' | sed s#packets:##", uci_get_buf);
sprintf(buf4, "ifconfig %s | grep \"TX bytes\" | awk \'{print $7 \" \" $8}\' | sed s#\\(## | sed s#\\)## | sed s#i##", uci_get_buf);
sprintf(buf5, "ifconfig %s | grep \"TX packets\" | awk \'{print $2}\' | sed s#packets:##", uci_get_buf);

//Display RX(Packets)  581.409 KB (6671 PKts.)

if( (pp = popen(buf2, "r")) == NULL ){
	printf("popen() error!\n");
	exit(1);
}
fgets(uci_get_buf, sizeof uci_get_buf, pp);
pclose(pp);

if( (pp = popen(buf3, "r")) == NULL ){
	printf("popen() error!\n");
	exit(1);
}
fgets(uci_get_buf1, sizeof uci_get_buf1, pp);
pclose(pp);

uci_get_buf[strlen(uci_get_buf)-1]='\0';
uci_get_buf1[strlen(uci_get_buf1)-1]='\0';
printf("%25s -- %s (%s Packets)\n", "RX(Packets)", uci_get_buf, uci_get_buf1);


//Display TX(Packets)  581.409 KB (6671 PKts.)

if( (pp = popen(buf4, "r")) == NULL ){
	printf("popen() error!\n");
	exit(1);
}
fgets(uci_get_buf, sizeof uci_get_buf, pp);
pclose(pp);

if( (pp = popen(buf5, "r")) == NULL ){
	printf("popen() error!\n");
	exit(1);
}
fgets(uci_get_buf1, sizeof uci_get_buf1, pp);
pclose(pp);

uci_get_buf[strlen(uci_get_buf)-1]='\0';
uci_get_buf1[strlen(uci_get_buf1)-1]='\0';
printf("%25s -- %s (%s Packets)\n", "TX(Packets)", uci_get_buf, uci_get_buf1);

}


/*****************************************************************
* NAME: cmdSystemmain
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdSystemmain(T_VOID* priv, CliData* cliData)
{
T_INT32 operationeMode=current_opmode;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	if(cliData->argc==0){
//Display System information
		printf("\n<<System Information>>\n");
		printf("----------------------------------------------------------\n");
		cmdsysteminfo();
		
//Display LAN information				
		printf("\n<<LAN Settings>> \n");
		printf("----------------------------------------------------------\n");
		//Display LAN information if operationeMode is CR or AR
		if ( (operationeMode==OPM_CBRT || operationeMode==OPM_AR) )
			cmdlaninfo(1);
		else
			cmdlaninfo(0);
			
//Display WAN information
		//Display WAN information if operationeMode is CR or AR
		if ( (operationeMode==OPM_CBRT || operationeMode==OPM_AR) ){
			printf("\n<<WAN Settings>> \n");
			printf("----------------------------------------------------------\n");
			cmdwaninfo();
		}

//Display 2.4G Wireless information

//Modify for AP100 on 2012-11-06
if ( strcmp(model_name, "ap100")!=0 || strcmp(current_radio_flag, "5G")!=0 )

		if (model_radio==2 || model_radio==7){						
			printf("\n<<Current 2.4G Wireless Settings>> \n");
			printf("----------------------------------------------------------\n");

			strcpy(current_radio_flag, "2.4G");
			
			if ( model_radio==2 )
				cmdwless2info(current_opmode);
			if ( model_radio==7 )
				cmdwless2info(current_opmode_2);
		}

//Display 5G Wireless information

//Modify for AP100 on 2012-11-06
if ( strcmp(model_name, "ap100")!=0 || strcmp(current_radio_flag, "2.4G")!=0 )

		if (model_radio==5 || model_radio==7){												
			printf("\n<<Current 5G Wireless Settings>> \n");
			printf("----------------------------------------------------------\n");

			strcpy(current_radio_flag, "5G");
			
			if ( model_radio==5 )
				cmdwless5info(current_opmode);
			if ( model_radio==7 )
				cmdwless5info(current_opmode_5);

			strcpy(current_radio_flag, "2.4G");

		}
									
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- stat client2 / client5                 */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_stat[]= {
//	{OPM_ALL,	"main",		NULL,			cmdSystemmain,	"Main",				"",	AUTH_ANY, MODEL_ALL},
//	{OPM_AP,   	"client2",	cli_table_client,	getNextTable,	"2.4G Wireless client list",	"",	AUTH_ADMIN, MODEL_2G},
//	{OPM_AP,	"client5",	cli_table_client,	getNextTable,	"5G Wireless client list",	"",	AUTH_ADMIN, MODEL_5G},	
//	{OPM_WDSAP,	"wdslist2",	NULL,	cmdwdslist,	"2.4G WDS Link Status",	"",	AUTH_ADMIN, MODEL_2G},
//	{OPM_WDSAP,	"wdslist5",	NULL,	cmdwdslist,	"5G WDS Link Status",	"",	AUTH_ADMIN, MODEL_5G},
//	{OPM_ALL,	"info",		cli_table_info,		getNextTable,	"Status Information",		"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"syslog",	NULL,			cmdloginfo,	"System log",			"",     AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"help",		cli_table_stat,		cmdHelp,	"Help",				"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,   	"exit",		NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

//CliEntry cli_table_client[]= {
//	{OPM_ALL,	"clientinfo",	NULL,			cmdsystemclient,	"Wireless client list",		"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"kickclient",	NULL,			cmdkickclient,		"Disconnect client",		"",     AUTH_ADMIN, MODEL_2G},	
//	{OPM_ALL,	"help",		cli_table_client,	cmdHelp,		"Help",				"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,   	"exit",		NULL,			cmdexit,		"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};


/*****************************************************************
* NAME: cmdwdslist
* ---------------------------------------------------------------
* FUNCTION: //Modify on 2012-11-13 for WDS link status in WDSAP mode and WDSB mode
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-13
* Modify:   
****************************************************************/
CliStatus cmdwdslist(T_VOID* priv, CliData* cliData)
{
#define WDS_STATUS		"%5d          %c%c:%c%c:%c%c:%c%c:%c%c:%c%c          "
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[8];
T_CHAR uci_get_buf2[8];
T_CHAR buf[128];
T_CHAR enable[4];
T_INT32 operationeMode=current_opmode;
T_INT32 ssidCount;
T_INT32 wdslinkCount;
T_INT32 nawds_index;
T_INT32 count;
T_INT32 i;
FILE *pp;

//WDS link status is DOWN
T_INT32 status=285;

T_INT32 rssi;
T_INT32 wdsEnablecount=0;


//Modify for EAP1750h on 2013-10-16 for WDS link status is DOWN
if ( strcmp(model_name, "eap1750h")==0 )
	status=120;


	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);
	wdslinkCount = getModelwdslinkCount(operationeMode);
	nawds_index=get_nawds_index(ssidCount, operationeMode);

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANWDSPeer", nawds_index);
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	
	//Get the number of the WDS link EX:uci get wireless.@wifi-iface[16].WLANWDSPeer --> "00026F371667v00026F371666v"
	count=strlen(uci_get_buf)/13;

	if(cliData->argc==0){
	
		tprintf("\n");
		tprintf("WDS Link ID        MAC Address         Link Status     RSSI(dBm)\n");
		tprintf("----------------------------------------------------------------\n");

		for (i=0; i<count; i++){
			//Get the MAC address of the WDS link
			strncpy(buf, uci_get_buf+(i)*13, 13);
			buf[13]='\0';
		
			//Determine the WDS link is enabled or disabled
			if ( uci_get_buf[(i)*13+12] == 'x')
			//	break;
			
			//Modify for EAP1750h on 2013-10-16 for WDS link status display
				continue;
			
			
			if ( uci_get_buf[(i)*13+12] == 'v'){


//Modify for EAP1750h on 2013-10-16 for WDS link status display
wdsEnablecount++;


//Modify on 2013-08-09 by Philips to display wdslink status for new web which is requested by Jacy
if ( (model_ID & MODEL_NEW_WEB) == 0 ){
		
				//Get WDS link list information
				//sprintf(func_buf, "wlanconfig ath2%d list sta| tail -n +2| awk \'{print $8}\'", i);
				sprintf(func_buf, "wlanconfig ath2%d list sta| tail -n +2| awk \'{print $8}\'", wdsEnablecount-1);
				if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
					//sprintf(func_buf, "wlanconfig ath7%d list sta| tail -n +2| awk \'{print $8}\'", i);
					sprintf(func_buf, "wlanconfig ath7%d list sta| tail -n +2| awk \'{print $8}\'", wdsEnablecount-1);

}
else{


	//Modify for EAP1750h on 2013-10-16 for WDS link status display
	if ( (model_ID & MODEL_AC) != 0 ){	
		sprintf(func_buf, "wlanconfig ath20 list sta| tail -n +%d| awk \'{print $9}\'", 2+wdsEnablecount-1);
		if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
		sprintf(func_buf, "wlanconfig ath70 list sta| tail -n +%d| awk \'{print $9}\'", 2+wdsEnablecount-1);

	}
	else {

//Get WDS link list information
//sprintf(func_buf, "wlanconfig ath2%d list sta| tail -n +2| awk \'{print $9}\'", i);
sprintf(func_buf, "wlanconfig ath2%d list sta| tail -n +2| awk \'{print $9}\'", wdsEnablecount-1);
if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
	//sprintf(func_buf, "wlanconfig ath7%d list sta| tail -n +2| awk \'{print $9}\'", i);
	sprintf(func_buf, "wlanconfig ath7%d list sta| tail -n +2| awk \'{print $9}\'", wdsEnablecount-1);

	}

}

				
				if( (pp = popen(func_buf, "r")) == NULL ){
					printf("popen() error!\n");
					exit(1);
				}
				if (fgets(uci_get_buf1, sizeof uci_get_buf1, pp) != 0)
					status = atoi(uci_get_buf1);
				pclose(pp);



//Modify on 2013-08-09 by Philips to display wdslink status for new web which is requested by Jacy
if ( (model_ID & MODEL_NEW_WEB) == 0 ){
				
				//Get the RSSI information
				//sprintf(func_buf, "wlanconfig ath2%d list sta| tail -n +2| awk \'{print $5}\'", i);
				sprintf(func_buf, "wlanconfig ath2%d list sta| tail -n +2| awk \'{print $5}\'", wdsEnablecount-1);
				if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
					//sprintf(func_buf, "wlanconfig ath7%d list sta| tail -n +2| awk \'{print $5}\'", i);
					sprintf(func_buf, "wlanconfig ath7%d list sta| tail -n +2| awk \'{print $5}\'", wdsEnablecount-1);
					
}
else{


	//Modify for EAP1750h on 2013-10-16 for WDS link status display
	if ( (model_ID & MODEL_AC) != 0 ){	
		sprintf(func_buf, "wlanconfig ath20 list sta| tail -n +%d| awk \'{print $6}\'", 2+wdsEnablecount-1);
		if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
		sprintf(func_buf, "wlanconfig ath70 list sta| tail -n +%d| awk \'{print $6}\'", 2+wdsEnablecount-1);

	}
	else {
	
//Get the RSSI information
//sprintf(func_buf, "wlanconfig ath2%d list sta| tail -n +2| awk \'{print $6}\'", i);
sprintf(func_buf, "wlanconfig ath2%d list sta| tail -n +2| awk \'{print $6}\'", wdsEnablecount-1);
if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
	//sprintf(func_buf, "wlanconfig ath7%d list sta| tail -n +2| awk \'{print $6}\'", i);
	sprintf(func_buf, "wlanconfig ath7%d list sta| tail -n +2| awk \'{print $6}\'", wdsEnablecount-1);

	}

}
					
				if( (pp = popen(func_buf, "r")) == NULL ){
					printf("popen() error!\n");
					exit(1);
				}
				if (fgets(uci_get_buf2, sizeof uci_get_buf2, pp) != 0)
					rssi = atoi(uci_get_buf2);
				pclose(pp);
			
				//Display the WDS link status
				//if ( status<128 ){
				
				//Modify for EAP1750h on 2013-10-16 for WDS link status display
				if ( status<120 ){
					tprintf(WDS_STATUS, i+1, buf[0],buf[1], buf[2],buf[3], buf[4],buf[5], buf[6],buf[7], buf[8],buf[9], buf[10],buf[11]);
					tprintf("%s             %d\n", "UP", rssi);
				}
				else{
					tprintf(WDS_STATUS, i+1, buf[0],buf[1], buf[2],buf[3], buf[4],buf[5], buf[6],buf[7], buf[8],buf[9], buf[10],buf[11]);
					tprintf("%s             %d\n", "DOWN", rssi);
				}
			}
		}
		tprintf("\n");
		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;
}


/*****************************************************************
* NAME: cmdkickclient
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdkickclient(T_VOID* priv, CliData* cliData)
{
T_CHAR macaddress[32];
T_CHAR func_buf[128];
T_CHAR func_buf1[128];
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];
T_CHAR uci_set_buf1[33];
T_INT32 ssidCount;
T_INT32 i;
T_INT32 wifi_index;
T_INT32 operationeMode=current_opmode;
T_CHAR maclist_buf[1024];
T_CHAR c0[255];
T_CHAR c1[255];
FILE *pp;
T_CHAR* token;
T_INT32 athNo=-1;
T_CHAR buf[128];
T_CHAR wifi2[8];
T_CHAR wifi5[8];

if ( strcmp(model_name, "c600")==0 || strcmp(model_name, "eap600")==0 || strcmp(model_name, "ecb600")==0){
	strcpy(wifi2, "wifi1");
	strcpy(wifi5, "wifi0");
}
else{
	strcpy(wifi2, "wifi0");
	strcpy(wifi5, "wifi1");
}

	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);

	if(cliData->argc==0){
		
		tprintf("SSID:#        MAC Address       Tx(Bytes)  Rx(Bytes)  RSSI(dBm)  RATE\n");
		tprintf("---------------------------------------------------------------------\n");

		for (i=0; i<ssidCount; i++){		
			sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", i);
			if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
				sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", 26+i);
			strcpy(uci_get_buf, cli_get_uci(func_buf));

//printf("func_buf=%s, uci_get_buf=%s\n", func_buf, uci_get_buf);
			
			if ( atoi(uci_get_buf)==0 )
				continue;
			//Create client information into /tmp/WLAN_STATION_LIST_FILE
			sprintf(func_buf, "wlanconfig ath%d list sta | tail -n +2 > /tmp/WLAN_STATION_LIST_FILE", i);
			if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
				sprintf(func_buf, "wlanconfig ath5%d list sta | tail -n +2 > /tmp/WLAN_STATION_LIST_FILE", i);

//printf("func_buf=%s\n", func_buf);
				
			system(func_buf);


//Modify on 2013-10-14 by Philips to display client status for eap1750h which is requested by Jacy

			//Print client information
			//sprintf(func_buf,"cat /tmp/WLAN_STATION_LIST_FILE | awk -F \" \" \'{print NR \"   \" $1 \"       \"$6 \"       \"$7 \"       \"$5 \"        \" $4}\'|sed \'s/^/SSID%d:#/g\'", i+1);
			//if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
			//sprintf(func_buf,"cat /tmp/WLAN_STATION_LIST_FILE | awk -F \" \" \'{print NR \"   \" $1 \"       \"$6 \"       \"$7 \"       \"$5 \"        \" $4}\'|sed \'s/^/SSID5%d:#/g\'", i+1);


if ( (model_ID & MODEL_AC) || ( strcmp(model_name, "eap900h")==0 ) || ( strcmp(model_name, "enh900ext")==0 )){
			//Print client information
			sprintf(func_buf,"cat /tmp/WLAN_STATION_LIST_FILE | awk -F \" \" \'{print NR \"   \" $1 \"       \"$7 \"       \"$8 \"       \"$6 \"        \" $5}\'|sed \'s/^/SSID%d:#/g\'", i+1);
			if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
			sprintf(func_buf,"cat /tmp/WLAN_STATION_LIST_FILE | awk -F \" \" \'{print NR \"   \" $1 \"       \"$7 \"       \"$8 \"       \"$6 \"        \" $5}\'|sed \'s/^/SSID5%d:#/g\'", i+1);
}
else{
			//Print client information
			sprintf(func_buf,"cat /tmp/WLAN_STATION_LIST_FILE | awk -F \" \" \'{print NR \"   \" $1 \"       \"$6 \"       \"$7 \"       \"$5 \"        \" $4}\'|sed \'s/^/SSID%d:#/g\'", i+1);
			if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
			sprintf(func_buf,"cat /tmp/WLAN_STATION_LIST_FILE | awk -F \" \" \'{print NR \"   \" $1 \"       \"$6 \"       \"$7 \"       \"$5 \"        \" $4}\'|sed \'s/^/SSID5%d:#/g\'", i+1);
}


//printf("func_buf=%s\n", func_buf);
		
			system(func_buf);
			tprintf("\n");	
		}
		tprintf("Recognized input format: XX:XX:XX:XX:XX:XX    EX: 00:02:6F:BE:F0:7A\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Check whether MAC is valid or not
		if (!errorcheckValidMACaddess(cliData->tokens[cliData->tokenLen-1].token)){
			tprintf("The input is not valid MAC address\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		//Convert MAC from lower-case to upper-case
		lower2upperMacAddress( uci_set_buf );
		
		for (i=0; i<ssidCount; i++){		
			sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", i);
			if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
				sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", 26+i);
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			if ( atoi(uci_get_buf)==0 ){
				continue;
			}	
			//Get the client mac
			sprintf(func_buf1, "wlanconfig ath%d list sta | tail -n +2 | awk '{print $1}'", i);
			if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
				sprintf(func_buf1, "wlanconfig ath%d list sta | tail -n +2 | awk '{print $1}'", 50+i);
			if( (pp = popen(func_buf1, "r")) == NULL ){
				printf("popen() error!\n");
				exit(1);
			}
			//Get athNo if input MAC is in Client MAC list 		
			while ( fgets(macaddress, sizeof macaddress, pp)!=0 ){
				lower2upperMacAddress( macaddress );
				macaddress[17]='\0';		
				if (strcmp(macaddress, uci_set_buf)==0){
					if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
						athNo=50+i;
					else
						athNo=i;
				}
			}
			pclose(pp);
		}	

		if (athNo == -1){
			printf("The input MAC is not in the Client MAC list\n");
			cliData->tokenLen-=2;
			return CLI_PARAMS_ERR;	
		}


//printf("athNo=%d\n", athNo);


		//2012-09-24 Add for TRUE Project Put MAC into ACL list according to macpolicy
		if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
			operationeMode=current_opmode_2;
		if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
			operationeMode=current_opmode_5;

		//get 0 for single-radio or wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24} for dual-radio
		wifi_index=get_wifi_iface(operationeMode);


//printf("wifi_index=%d, athNo=%d\n", wifi_index, athNo);

//Modify on 2013-08-08 by Philips to support Kick and Ban for each SSID for new web which is requested by Jacy
if ( (model_ID & MODEL_NEW_WEB) == 0 ){

		//Get the macpolicy
		sprintf(func_buf, "wireless.@wifi-iface[%d].macpolicy", wifi_index);
		strcpy(uci_get_buf, cli_get_uci(func_buf));
}
else {

//Get the macpolicy
if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
	sprintf(func_buf, "wireless.@wifi-iface[%d].macpolicy", wifi_index+athNo);
else
	sprintf(func_buf, "wireless.@wifi-iface[%d].macpolicy", wifi_index+athNo-50);
strcpy(uci_get_buf, cli_get_uci(func_buf));

//printf("1. Get the macpolicy --- %s\n", uci_get_buf);

}

if ( (model_ID & MODEL_NEW_WEB) == 0 ){
		//Get the maclist
		sprintf(func_buf1, "uci get wireless.@wifi-iface[%d].maclist 2> /dev/null", wifi_index);
}
else {

//Get the maclist
if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
	sprintf(func_buf1, "uci get wireless.@wifi-iface[%d].maclist 2> /dev/null", wifi_index+athNo);
else
	sprintf(func_buf1, "uci get wireless.@wifi-iface[%d].maclist 2> /dev/null", wifi_index+athNo-50);

}
		
		if( (pp = popen(func_buf1, "r")) == NULL ){
			printf("popen() error!\n");
			exit(1);
		}		
		if ( fgets(maclist_buf, sizeof maclist_buf, pp)!=0 ){
			maclist_buf[strlen(maclist_buf)-1]='\0';
		}
		pclose(pp);


//printf("2. Get the maclist --- %s\n", maclist_buf);

if ( (model_ID & MODEL_NEW_WEB) == 0 ){
		//When the macpolicy is Allow -- delmac
		if ( strcmp(uci_get_buf, "allow")==0 ){
			//Delete the whole mac list
    			for (i=wifi_index; i<wifi_index+ssidCount; i++){
				sprintf(c1, "uci delete wireless.@wifi-iface[%d].maclist", i);
				system(c1);
				if ( operationeMode==OPM_RP && i==1 )
					break;
			}
			system("uci commit");
			//Add each MAC except kick MAC into mac list
			token =strtok(maclist_buf, " ");
			while(token){
				if (strcmp(token, uci_set_buf)==0){
					token = strtok(NULL, " ");
					continue;
				}
				for (i=wifi_index; i<wifi_index+ssidCount; i++){
					sprintf(c0, "wireless.@wifi-iface[%d].maclist", i);
					sprintf(c1, "uci add_list %s=%s", c0, token);
					system(c1);
					if ( operationeMode==OPM_RP && i==1 )
						break;
				}
				system("uci commit");	
				token = strtok(NULL, " ");
			}

			//execute the KickAndBan script provided by Naying
			sprintf(func_buf, "KickAndBan.sh allow %d %s %s", athNo, uci_set_buf, wifi2);
			if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
				sprintf(func_buf, "KickAndBan.sh allow %d %s %s", athNo, uci_set_buf, wifi5);
			system(func_buf);
		}
		
		//When the macpolicy is Deny -- addmac
		if ( strcmp(uci_get_buf, "deny")==0 ){
			//If the mac is not in mac list
			if (checkRedundancyMACfilterlist( maclist_buf, uci_set_buf )){
	
				//add input mac address into the buttom of configuration file
				for (i=wifi_index; i<wifi_index+ssidCount; i++){
					sprintf(c1, "uci add_list wireless.@wifi-iface[%d].maclist=%s", i, uci_set_buf);
					system(c1);
					if ( operationeMode==OPM_RP && i==1 )
						break;
				}
				system("uci commit");
			}
	
			//execute the KickAndBan script provided by Naying 
			sprintf(func_buf, "KickAndBan.sh deny %d %s %s", athNo, uci_set_buf, wifi2);
			if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
				sprintf(func_buf, "KickAndBan.sh deny %d %s %s", athNo, uci_set_buf, wifi5);
			system(func_buf);
		}

		//When the macpolicy is Disable
		if ( strcmp(uci_get_buf, "")==0 || strcmp(uci_get_buf, " ")==0 ){
			//set policy to be deny	
			strcpy(uci_set_buf1, "deny");		
			for (i=wifi_index; i<wifi_index+ssidCount; i++){
		
				sprintf(func_buf, "wireless.@wifi-iface[%d].macpolicy", i);
				cli_set_uci(func_buf, uci_set_buf1);
				if ( operationeMode==OPM_RP && i==1 )
					break;
			}
			system("uci commit");
			//If the mac is not in mac list	
			if (checkRedundancyMACfilterlist( maclist_buf, uci_set_buf )){
				//add input mac address into the buttom of configuration file 
				for (i=wifi_index; i<wifi_index+ssidCount; i++){
					sprintf(c1, "uci add_list wireless.@wifi-iface[%d].maclist=%s", i, uci_set_buf);			
					system(c1);
					if ( operationeMode==OPM_RP && i==1 )
						break;
				}	
				system("uci commit");
			}
	
			//execute the KickAndBan script provided by Naying
			sprintf(func_buf, "KickAndBan.sh disable %d %s %s", athNo, uci_set_buf, wifi2);
			if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
				sprintf(func_buf, "KickAndBan.sh disable %d %s %s", athNo, uci_set_buf, wifi5);
			system(func_buf);
		}
}
else {

//When the macpolicy is Allow -- delmac
if ( strcmp(uci_get_buf, "allow")==0 ){
//	printf("3. When the macpolicy is Allow \n");
	//Modify on 2013-08-08 using API which is provided by Sam to delete mac list of MAC filter per SSID for eap900 and C600
	sprintf(buf, "/usr/sbin/macfilter_api.lua del ath%d %s", athNo, uci_set_buf);
	system(buf);
	system("uci commit");
	//synchronize the /etc/config/filter to /etc/config/wireless
	system("/usr/sbin/macfilter_api.lua sync");
	system("uci commit");

	//execute the KickAndBan script provided by Naying
	sprintf(func_buf, "KickAndBan.sh allow %d %s %s", athNo, uci_set_buf, wifi2);
	if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
		sprintf(func_buf, "KickAndBan.sh allow %d %s %s", athNo, uci_set_buf, wifi5);
	system(func_buf);
}

//When the macpolicy is Deny -- addmac
if ( strcmp(uci_get_buf, "deny")==0 ){
//	printf("3. When the macpolicy is Deny \n");
	//Modify on 2013-08-08 using API which is provided by Sam to add mac list of MAC filter per SSID for eap900 and C600
	sprintf(buf, "/usr/sbin/macfilter_api.lua add ath%d %s", athNo, uci_set_buf);
	system(buf);
	system("uci commit");
	//synchronize the /etc/config/filter to /etc/config/wireless
	system("/usr/sbin/macfilter_api.lua sync");
	system("uci commit");
	
	//execute the KickAndBan script provided by Naying
	sprintf(func_buf, "KickAndBan.sh deny %d %s %s", athNo, uci_set_buf, wifi2);
	if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
		sprintf(func_buf, "KickAndBan.sh deny %d %s %s", athNo, uci_set_buf, wifi5);
	system(func_buf);
}

//When the macpolicy is Disable
if ( strcmp(uci_get_buf, "")==0 || strcmp(uci_get_buf, " ")==0 ){
//	printf("3. When the macpolicy is Disable \n");
	//set policy to be deny	
	//acl= 0(disable), 1(allow), 2(deny)
	//Modify on 2013-08-08 using API which is provided by Sam to set ACL of MAC filter per SSID for eap900 and C600
	sprintf(c1, "/usr/sbin/macfilter_api.lua set ath%d %d", athNo, 2);	
	system(c1);
	system("uci commit");
	//synchronize the /etc/config/filter to /etc/config/wireless		
	system("/usr/sbin/macfilter_api.lua sync");	
	system("uci commit");
	
	//Modify on 2013-08-08 using API which is provided by Sam to add mac list of MAC filter per SSID for eap900 and C600
	sprintf(buf, "/usr/sbin/macfilter_api.lua add ath%d %s", athNo, uci_set_buf);
	system(buf);	
	system("uci commit");
	//synchronize the /etc/config/filter to /etc/config/wireless
	system("/usr/sbin/macfilter_api.lua sync");	
	system("uci commit");
		
	//execute the KickAndBan script provided by Naying 
	sprintf(func_buf, "KickAndBan.sh disable %d %s %s", athNo, uci_set_buf, wifi2);
	if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
		sprintf(func_buf, "KickAndBan.sh disable %d %s %s", athNo, uci_set_buf, wifi5);		
	system(func_buf);
	
}

}
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1)
		return CLI_NO_MATCH;

}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- stat info                              */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_stat[]= {
//	{OPM_ALL,	"main",		NULL,			cmdSystemmain,	"Main",				"",	AUTH_ANY, MODEL_ALL},
//	{OPM_AP,   	"client2",	cli_table_client,	getNextTable,	"2.4G Wireless client list",	"",	AUTH_ADMIN, MODEL_2G},
//	{OPM_AP,	"client5",	cli_table_client,	getNextTable,	"5G Wireless client list",	"",	AUTH_ADMIN, MODEL_5G},	
//	{OPM_ALL,	"info",		cli_table_info,		getNextTable,	"Status Information",		"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"syslog",	NULL,			cmdloginfo,	"System log",			"",     AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"help",		cli_table_stat,		cmdHelp,	"Help",				"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,   	"exit",		NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

//CliEntry cli_table_info[]= {
//	{OPM_ALL,	"sysuptime",	NULL,			cmdsysuptime,	"System up time",		"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"cpuinfo",	NULL,			cmdcpuinfo,	"CPU load",			"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"meminfo",	NULL,			cmdmeminfo,	"Memory usage",			"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"wlanint",	NULL,			cmdwlanint,	"WLAN interface status",	"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"wlaninfo",	NULL,			cmdwlaninfo,	"WLAN statistics",		"",     AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"etherinfo",	NULL,			cmdetherinfo,	"Ethernet statistics",		"",     AUTH_ADMIN, MODEL_5G},
//	{OPM_ALL,	"channel2",	NULL,			cmdchannel2,	"2.4G channel utilization",	"",     AUTH_ADMIN, MODEL_2G},
//	{OPM_ALL,	"channel5",	NULL,			cmdchannel5,	"5G channel utilization",	"",     AUTH_ADMIN, MODEL_5G},
//	{OPM_ALL,	"help",		cli_table_info,		cmdHelp,	"Help",				"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,   	"exit",		NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

/*****************************************************************
* NAME: cmdsysuptime
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsysuptime(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){
		
		system("uptime | awk -F \",\" \'{print $1}\'");
		printf("\n");		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}

/*****************************************************************
* NAME: cmdcpuinfo
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdcpuinfo(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){
		
		system("top");	
    		cliData->tokenLen--;
		return CLI_NOTHING;

	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}

/*****************************************************************
* NAME: cmdmeminfo
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdmeminfo(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){
		
		system("cat /proc/meminfo");
		printf("\n");	
    		cliData->tokenLen--;
		return CLI_NOTHING;

	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}

/*****************************************************************
* NAME: cmdwlanint
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdwlanint(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){
		
		system("for x in $(ifconfig |grep ath|awk \'{print $1}\');do iwconfig $x; done");
		printf("\n");	
    		cliData->tokenLen--;
		return CLI_NOTHING;

	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}

/*****************************************************************
* NAME: cmdwlaninfo
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdwlaninfo(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){
		
		system("for x in $(ifconfig |grep ath|awk \'{print $1}\');do ifconfig $x; done");
		printf("\n");	
    		cliData->tokenLen--;
		return CLI_NOTHING;

	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}

/*****************************************************************
* NAME: cmdetherinfo
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdetherinfo(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){
		
		system("for x in $(ifconfig |grep eth|awk \'{print $1}\');do ifconfig $x; done");
		printf("\n");	
    		cliData->tokenLen--;
		return CLI_NOTHING;

	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}

/*****************************************************************
* NAME: cmdchannel2
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdchannel2(T_VOID* priv, CliData* cliData)
{
	if(cliData->argc==0){
		//Modify on 2013-01-07 by Philips to display the channel information for 2.4G	
		system("iwlist `iwconfig 2>/dev/null|grep ath|grep -E \"(11b|11g|11ng)\"|head -n 1|cut -d \' \' -f 1` ch");	
		printf("\n");	
    		cliData->tokenLen--;
		return CLI_NOTHING;

	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;
}

/*****************************************************************
* NAME: cmdchannel5
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdchannel5(T_VOID* priv, CliData* cliData)
{
	if(cliData->argc==0){
		//Modify on 2013-01-07 by Philips to display the channel information for 5G
		system("iwlist `iwconfig 2>/dev/null|grep ath|grep -E \"(11a|11na)\"|head -n 1|cut -d \' \' -f 1` ch");
		printf("\n");	
    		cliData->tokenLen--;
		return CLI_NOTHING;

	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- stat syslog                            */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_stat[]= {
//	{OPM_ALL,	"main",		NULL,			cmdSystemmain,	"Main",				"",	AUTH_ANY, MODEL_ALL},
//	{OPM_AP,   	"client2",	cli_table_client,	getNextTable,	"2.4G Wireless client list",	"",	AUTH_ADMIN, MODEL_2G},
//	{OPM_AP,	"client5",	cli_table_client,	getNextTable,	"5G Wireless client list",	"",	AUTH_ADMIN, MODEL_5G},	
//	{OPM_ALL,	"info",		cli_table_info,		getNextTable,	"Status Information",		"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"syslog",	NULL,			cmdloginfo,	"System log",			"",     AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"help",		cli_table_stat,		cmdHelp,	"Help",				"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,   	"exit",		NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

/*****************************************************************
* NAME: cmdloginfo
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdloginfo(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){
		
		system("logread | sort -nr");
		printf("\n");	
    		cliData->tokenLen--;
		return CLI_NOTHING;

	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}



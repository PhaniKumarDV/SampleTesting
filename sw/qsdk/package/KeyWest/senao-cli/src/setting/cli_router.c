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
;    Creator : Joey
;    File    : fw.c
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       Joey            2008-0710       Create
;*****************************************************************************/

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <sap_osapi.h>
#include <sap_ostypes.h>
#include <gconfig.h>
#include <tokens.h>
#include <apcfg.h>
#include <filter.h>
#include <settings.h>
#include <system.h>
#include <string.h>
#include <stdlib.h>
#include <sysUtilMisc.h>
#include <dmzinfo.h>
#include <sysHumanReadable.h>
/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
#define NAT_MAC_DESCRIP  	" Idx |    Description   |		 LAN MAC Address \n"
#define NAT_MAC_PATTERN 	" %d   |   %12s    |  %s\n"
#define NAT_IP_DESCRIP  	" Idx  |     Description	|   Local IP Address  | Protocol | Port range \n"
#define NAT_IP_PATTERN 		" %2d  |   %12s  | %s%-3d ~ %s%-3d | %6s  |  %d ~ %d  \n"
#define WLAN_MAC_DESCRIP  	" Idx |    Description   |		 MAC Address \n"
#define WLAN_MAC_PATTERN 	" %d   |   %12s    |  %s\n"
#define NAT_URL_DESCRIP  	" Idx  |     URL/Keyword  \n"
#define NAT_URL_PATTERN 	" %2d  |   %s  \n"

/*-------------------------------------------------------------------------*/
/*                           Parameter                                     */
/*-------------------------------------------------------------------------*/
extern apCfgItemNameSet protocolTypeSet[];
extern CliEntry cli_table_dhcpset[];
extern CliEntry cli_table_wandhcp[];
extern CliEntry cli_table_wanstaticip[];
extern CliEntry cli_table_wanpppoe[];
extern CliEntry cli_table_wanpptp[];
T_INT32 dhcpsetbridge=-1;
T_INT32 contypesetbridge=-1;

extern T_CHAR model_name[];

extern T_INT32 cmdtreelevel;
/* ### 
typedef struct __ClilanipsetEntry
{	
	T_INT32 ipset;
	T_INT32 maskset;	
	
	T_CHAR ip[16];	
	T_CHAR subnetmask[16];		


}ClilanipsetEntry;
ClilanipsetEntry Clilanipset={0, 0, "", ""};
*/

typedef struct __ClilandhcpsetEntry
{	
	T_INT32 startipset;
	T_INT32 endipset;
	T_INT32 winsipset;
	
	T_CHAR startip[32];	
	T_CHAR endip[32];
	T_CHAR winsip[32];		

}ClilandhcpsetEntry;
ClilandhcpsetEntry Clilandhcpset={0, 0, 0, "", "", ""};


typedef struct __CliwanipsetEntry
{	
	T_INT32 ipset;
	T_INT32 gatewayset;
	T_INT32 maskset;	
	
	T_CHAR ip[16];
	T_CHAR gateway[16];
	T_CHAR subnetmask[16];		


}CliwanipsetEntry;
CliwanipsetEntry Cliwanipset={0, 0, 0, "", "", ""};


typedef struct __CliRouterPortforwardEntry
{	
	T_INT32 ipset;
	T_INT32 startportset;	
	
	T_CHAR servicename[32];	
	T_CHAR protocol[5];	
	T_CHAR startport[6];	
	T_CHAR endport[6];
	T_CHAR ip[16];

}CliRouterPortforwardEntry;
CliRouterPortforwardEntry CliRouterPortforward={0, 0, "", "both", "", "", ""};


typedef struct __CliRouterPorttriggerEntry
{	
	T_INT32 startportset;
	T_INT32 forwardedportset;
	
	T_CHAR servicename[32];	
	T_CHAR startport[6];	
	T_CHAR endport[6];
	T_CHAR triggertype[5];
	T_CHAR forwardedport[6];
	T_CHAR publictype[5];

}CliRouterPorttriggerEntry;
CliRouterPorttriggerEntry CliRouterPorttrigger={0, 0, "", "", "", "both", "", "both"};

typedef struct __CliRouterMACfilterEntry
{
	T_INT32 macset;
		
	T_CHAR servicename[128];
	T_CHAR macaddress[17];

}CliRouterMACfilterEntry;
CliRouterMACfilterEntry CliRouterMACfilter={0, "", ""};


typedef struct __CliRouterIPfilterEntry
{	
	T_INT32 startipset;
	
	T_CHAR servicename[32];	
	T_CHAR protocol[5];	
	T_CHAR startip[16];	
	T_CHAR endip[16];
	T_CHAR startport[6];	
	T_CHAR endport[6];

}CliRouterIPfilterEntry;
CliRouterIPfilterEntry CliRouterIPfilter={0, "", "both", "", "", "", ""};
//engenius
/*-------------------------------------------------------------------------*/
/*                           Errorcheck                                     */
/*-------------------------------------------------------------------------*/

/*****************************************************************
* NAME: errorcheckDHCPRange
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 errorcheckDHCPRange(const char * dhcpStartAddr, const char * dhcpEndAddr){

T_INT32 i;
unsigned int startip[4];
unsigned int endip[4];
	
	if(sscanf(dhcpStartAddr,"%u.%u.%u.%u", &startip[0], &startip[1], &startip[2], &startip[3]) != 4) return 0;
	if(sscanf(dhcpEndAddr,"%u.%u.%u.%u", &endip[0], &endip[1], &endip[2], &endip[3]) != 4) return 0;

	for(i=0; i<4; i++){
		if( (startip[i] == endip[i]) )
			continue;
		if( (startip[i] > endip[i]) )
			return 0;
	}
	return 1;
}


/*****************************************************************
* NAME: checkValidDHCPRegionLANIP
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 checkValidDHCPRegionLANIP(const char * lanip, const char * dhcpStartAddr, const char * dhcpEndAddr){

T_INT32 i;
unsigned int ip[4];
unsigned int startip[4];
unsigned int endip[4];
	
	if(sscanf(lanip,"%u.%u.%u.%u", &ip[0], &ip[1], &ip[2], &ip[3]) != 4) return 0;
	if(sscanf(dhcpStartAddr,"%u.%u.%u.%u", &startip[0], &startip[1], &startip[2], &startip[3]) != 4) return 0;
	if(sscanf(dhcpEndAddr,"%u.%u.%u.%u", &endip[0], &endip[1], &endip[2], &endip[3]) != 4) return 0;

	for(i=0; i<4; i++){
		if( (startip[i] == ip[i]) && (ip[i] == endip[i]) )
			continue;
		if( (startip[i] <= ip[i]) && (ip[i] <= endip[i]) )
			return 0;
	}
	return 1;
}

/*****************************************************************
* NAME: errorcheckPortforwardportrange
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 errorcheckPortforwardportrange(T_CHAR* inputstart, T_CHAR* inputend, T_INT32 portforwardnumber){
T_INT32 i;
T_CHAR uci_get_buf[128];
T_CHAR c1[255];
char tbuf[255];
T_CHAR* token1;
T_CHAR* IP;
T_CHAR* startport;
T_CHAR* endport;
FILE* fp;

	if (portforwardnumber>0){
		for (i=1; i<=portforwardnumber; i++){
			sprintf(c1, "ipnat.ipnat.PortForwardingList%d", i);
			strcpy(uci_get_buf, cli_get_uci(c1));

			token1 = strtok(uci_get_buf, " ");
			IP = strtok(NULL, " ");
			startport = strtok(NULL, " ");
			endport = strtok(NULL, " ");

			if ( atoi(inputend)>=atoi(startport+5) && atoi(inputstart)<=atoi(endport+6) )
				return 0;
		}
	}
	if (portforwardnumber==-1){
		//redirect error message "uci: Entry not found"
		system("uci get ipnat.ipnat.VirServerTable 2> /dev/null |sed \'s/enable:/\\\nenable:/g\'| sed \'1d\'  >/tmp/pfdata");
		if((fp = fopen("/tmp/pfdata", "r"))==NULL){
			printf("Can't open file\n");
			return -1;
		}
		
		while(fgets(tbuf,sizeof(tbuf),fp)){

			token1 = strtok(tbuf, " ");
			IP = strtok(NULL, " ");
			startport = strtok(NULL, " ");
			endport = strtok(NULL, " ");

			if ( atoi(inputend)>=atoi(startport+5) && atoi(inputstart)<=atoi(endport+6) )
				return 0;	
		}
		fclose(fp);
	
	}
	return 1;
}

/*****************************************************************
* NAME: errorcheckPorttriggerportrange
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 errorcheckPorttriggerportrange(T_CHAR* inputstart, T_CHAR* inputend, T_INT32 porttriggernumber){
T_INT32 i;
T_CHAR uci_get_buf[128];
T_CHAR c1[255];
T_CHAR* startport;
T_CHAR* endport;

	if (strcmp(inputend, "")==0)
		strcpy(inputend, inputstart);
		
	if (porttriggernumber>0){
		for (i=1; i<=porttriggernumber; i++){
			sprintf(c1, "ipnat.ipnat.PortTriggerList%d", i);
			strcpy(uci_get_buf, cli_get_uci(c1));

			startport = strtok(uci_get_buf, ",");
			endport = strtok(NULL, ",");
			if (strcmp(endport+9, "")==0)
				strcpy(endport+9, startport+9);
				
			if ( atoi(inputend)>=atoi(startport+9) && atoi(inputstart)<=atoi(endport+9) )
				return 0;
		}
	}
	return 1;
}

/*****************************************************************
* NAME: checkRedundancyMAClist
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 checkRedundancyMAClist(T_CHAR* input, T_INT32 macfilternumber) {
T_INT32 i;
T_CHAR uci_get_buf[128];
T_CHAR c1[255];
	
	if (macfilternumber>0){

		for (i=1; i<=macfilternumber; i++){
			sprintf(c1, "ipnat.ipnat.MACFilterList%d", i);
			strcpy(uci_get_buf, cli_get_uci(c1));
			
			if (strstr(uci_get_buf, input)!=NULL )
				return 0;/*exist*/
		}
	}
	return 1;
}

/*****************************************************************
* NAME: displayURLfilterdata
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID displayURLfilterdata(T_INT32 urlfilternumber) {
T_INT32 i;
//T_CHAR func_buf[128]="ipnat.ipnat.URLFilterNum";
T_CHAR uci_get_buf[128];
T_CHAR c1[255];

	for (i=1; i<=urlfilternumber; i++){
		sprintf(c1, "ipnat.ipnat.URLFilterList%d", i);
		strcpy(uci_get_buf, cli_get_uci(c1));
		tprintf("%d - %s\n", i, uci_get_buf+5);	
	}
}

/*****************************************************************
* NAME: displayPortforwarddata
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 displayPortforwarddata(T_INT32 portforwardnumber) {
T_CHAR uci_get_buf[128];
T_CHAR tbuf[1024];
T_CHAR c1[255];
T_CHAR* token1;
T_CHAR* token2;
T_CHAR* token3;
T_CHAR* token4;
T_CHAR* token5;
T_CHAR* token6;
FILE* fp;

T_INT32 count=0;
T_INT32 i=0;
T_INT32 j=0;
T_INT32 k=0;
T_CHAR c;
T_CHAR token[64];
T_CHAR enable[64];
T_CHAR proto[64];
T_CHAR sport[64];
T_CHAR eport[64];
T_CHAR ipaddr[64];
T_CHAR name[64];

	if (portforwardnumber>0){
		tprintf("Index - Protocol, Start Port, End Port, Server IP address,  Service Name\n");
		tprintf("------------------------------------------------------------------------\n");
		for (i=1; i<=portforwardnumber; i++){
			sprintf(c1, "ipnat.ipnat.PortForwardingList%d", i);
			strcpy(uci_get_buf, cli_get_uci(c1));

			token1 = strtok(uci_get_buf, " ");
			token2 = strtok(NULL, " ");
			token3 = strtok(NULL, " ");
			token4 = strtok(NULL, " ");
			token5 = strtok(NULL, " ");
			token6 = strtok(NULL, " ");

			tprintf("%5d -  %5s -   %5s    - %5s , %15s , %15s\n", i, token5+6, token3+5, token4+6, token2+6, token6+5);	
		}
		tprintf("\n");	
	}
	if (portforwardnumber==-1){
		tprintf("Index - Protocol, Start Port, End Port, Server IP address, Active,  Service Name\n");
		tprintf("-----------------------------------------------------------------------------------\n");	
/*
		system("uci get ipnat.ipnat.VirServerTable 2> /dev/null |sed \'s/enable:/\\\nenable:/g\'| sed \'1d\' >/tmp/pfdata");
		
		if((fp = fopen("/tmp/pfdata", "r"))==NULL){
			printf("Can't open file\n");
			return -1;
		}
		
		i=1;
		while(fgets(tbuf,sizeof(tbuf),fp)){

			token1 = strtok(tbuf, " ");
			token2 = strtok(NULL, " ");
			token3 = strtok(NULL, " ");
			token4 = strtok(NULL, " ");
			token5 = strtok(NULL, " ");
			token6 = strtok(NULL, " ");
printf("token6=%s_length=%d\n", token6, strlen(token6));			
			tprintf("%5d -  %5s -   %5s    - %5s , %15s , %10s, %16s\n", i++, token5+6, token3+5, token4+6, token2+6, token1+7, token6+5);
//tprintf("%5d -    %s -       %s    -      %s ,      %s ,         %s ,        %s\n", i++, token5+6, token3+5, token4+6, token2+6, token1+7, token6+5);

		}
		fclose(fp);	
*/
		//list 'VirServerTable' 'enable:1 lanip:192.168.1.0 port:70 eport:180 proto:udp name:1613'
		system("uci get ipnat.ipnat.VirServerTable 2> /dev/null > /tmp/pfdata");
		if((fp = fopen("/tmp/pfdata", "r"))==NULL){
			printf("Can't open file\n");
			return -1;
		}

		while ((c = fgetc(fp)) != EOF) {
			//Get token through read char one by one
			if (c != ' ')
				token[i++] = c;
			//Finish to get one token
			else{
				k++;
				token[i] = '\0';
				i=0;
				//k is the index of token
				switch (k){
					case 1:
						strcpy(enable, token);
					case 2:
						strcpy(ipaddr, token);
					case 3:
						strcpy(sport, token);
					case 4:
						strcpy(eport, token);
					case 5:
						strcpy(proto, token);
					case 6:
						strcpy(name, token);	
				}
				//6 tokens consist of one line of portforward list 
				if(k==6){
					tprintf("%5d -  %5s -   %5s    - %5s , %15s , %7s, %18s\n", ++j, proto+6, sport+5, eport+6, ipaddr+6, enable+7, name+5);
					
					count++;
					k=0;
				}

			}
			
		}
		//handle last line of portforward list
		if(k==5){
			token[i-1] = '\0';
			strcpy(name, token);
			tprintf("%5d -  %5s -   %5s    - %5s , %15s , %7s, %18s\n\n", ++j, proto+6, sport+5, eport+6, ipaddr+6, enable+7, name+5);
			
			count++;
		}
		
		fclose(fp);
		
	}
	
	return count;
}

/*****************************************************************
* NAME: displayPorttriggerdata
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID displayPorttriggerdata(T_INT32 porttriggernumber) {
T_INT32 i;
T_CHAR uci_get_buf[128];
T_CHAR c1[255];
T_CHAR* token1;
T_CHAR* token2;
T_CHAR* token3;
T_CHAR* token4;
T_CHAR* token5;
T_CHAR* token6;


	if (porttriggernumber>0){
		tprintf("Index -  Trigger Port ,  Trigger Type ,  Forwarded Port  , Public Type , Service Name\n");
		tprintf("------------------------------------------------------------------------------------------\n");
		
		for (i=1; i<=porttriggernumber; i++){
			sprintf(c1, "ipnat.ipnat.PortTriggerList%d", i);
			strcpy(uci_get_buf, cli_get_uci(c1));

			token1 = strtok(uci_get_buf, ",");
			token2 = strtok(NULL, ",");
			token3 = strtok(NULL, ",");
			//handle multiple port case for Forwarded port, EX:Forport:20,30-40,66-70,PublicType
			token4 = strtok(NULL, "P");
			token4[strlen(token4)-1]='\0';
			token5 = strtok(NULL, ",");
			token6 = strtok(NULL, ",");
			tprintf("%5d - %5s - %5s , %10s ,    %15s ,    %5s ,    %15s\n", i, token1+9, token2+9, token3+12, token4+8, token5+10, token6+5);	
		}
		tprintf("\n");
	}
}

/*****************************************************************
* NAME: errorcheckIPfilterrange
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 errorcheckIPfilterrange(T_CHAR* inputstart, T_CHAR* inputend, T_INT32 ipfilternumber){
T_INT32 i;
T_CHAR uci_get_buf[128];
T_CHAR c1[255];
T_CHAR* token1;
T_CHAR* startip;
T_CHAR* endip;
unsigned int startinput[4];
unsigned int endinput[4];
unsigned int ipstart[4];
unsigned int ipend[4];


	if (strcmp(inputend, "")==0)
		strcpy(inputend, inputstart);

	if(sscanf(inputstart,"%u.%u.%u.%u", &startinput[0], &startinput[1], &startinput[2], &startinput[3]) != 4) return 0;
	if(sscanf(inputend,"%u.%u.%u.%u", &endinput[0], &endinput[1], &endinput[2], &endinput[3]) != 4) return 0;

	startinput[0]=startinput[0]*256*256*256+startinput[1]*256*256+startinput[2]*256+startinput[3];
	endinput[0]=endinput[0]*256*256*256+endinput[1]*256*256+endinput[2]*256+endinput[3];

	if (ipfilternumber>0){
		for (i=1; i<=ipfilternumber; i++){
			sprintf(c1, "ipnat.ipnat.IPFilterList%d", i);
			strcpy(uci_get_buf, cli_get_uci(c1));

			token1 = strtok(uci_get_buf, ",");
			startip = strtok(NULL, ",");
			endip = strtok(NULL, ",");
	
			if (strcmp(endip+4, "")==0)
				strcpy(endip, startip);

			
			if(sscanf(startip+4,"%u.%u.%u.%u", &ipstart[0], &ipstart[1], &ipstart[2], &ipstart[3]) != 4) return 0;
			if(sscanf(endip+4,"%u.%u.%u.%u", &ipend[0], &ipend[1], &ipend[2], &ipend[3]) != 4) return 0;
			ipstart[0]=ipstart[0]*256*256*256+ipstart[1]*256*256+ipstart[2]*256+ipstart[3];
			ipend[0]=ipend[0]*256*256*256+ipend[1]*256*256+ipend[2]*256+ipend[3];

			if ( endinput[0]>=ipstart[0] && startinput[0]<=ipend[0] )
				return 0;
		}
	}
	return 1;
}

/*****************************************************************
* NAME: displayIPfilterdata
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID displayIPfilterdata(T_INT32 ipfilternumber) {
T_INT32 i;
//T_CHAR func_buf[128]="ipnat.ipnat.IPFilterNum";
T_CHAR uci_get_buf[128];
T_CHAR c1[255];
T_CHAR* token1;
T_CHAR* token2;
T_CHAR* token3;
T_CHAR* token4;
T_CHAR* token5;
T_CHAR* token6;


	if (ipfilternumber>0){
		tprintf("Index - Protocol   ,     Local IP Address    ,    Port Range   , Service Name\n");
		tprintf("---------------------------------------------------------------------------------\n");
		
		for (i=1; i<=ipfilternumber; i++){
			sprintf(c1, "ipnat.ipnat.IPFilterList%d", i);
			strcpy(uci_get_buf, cli_get_uci(c1));

			token1 = strtok(uci_get_buf, ",");
			token2 = strtok(NULL, ",");
			token3 = strtok(NULL, ",");
			token4 = strtok(NULL, ",");
			token5 = strtok(NULL, ",");
			token6 = strtok(NULL, ",");
			tprintf("%5d - %5s , %15s - %15s , %5s - %5s , %15s\n", i, token1+4, token2+4, token3+4, token4+6, token5+6, token6+5);	
		}
	tprintf("\n");
	}
}

/*****************************************************************
* NAME: displayRouterMACfilterdata
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID displayRouterMACfilterdata(T_INT32 macfilternumber) {
T_INT32 i;
T_CHAR uci_get_buf[128];
T_CHAR c1[255];
T_CHAR* token1;
T_CHAR* token2;

	if (macfilternumber>0){
		tprintf("Index -      Service Name ,           MAC address\n");
		tprintf("---------------------------------------------------\n");
		
		for (i=1; i<=macfilternumber; i++){
			sprintf(c1, "ipnat.ipnat.MACFilterList%d", i);
			strcpy(uci_get_buf, cli_get_uci(c1));

			token1 = strtok(uci_get_buf, ",");
			token2 = strtok(NULL, ",");
			tprintf("%5d - %15s , %25s\n", i, token2+5, token1+8);	
		}
		tprintf("\n");
	}
}



/*****************************************************************
* NAME: cmdconntype
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdconntype(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.wan.proto";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR c1[255];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:DHCP, 2:Static IP, 3:PPPoE, 4:PPTP)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );	
		
		if (contypesetbridge==-1 ){
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 4, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
			}
			
			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
			
			if ( strcmp(uci_set_buf, "1")==0){				
				cli_set_uci(func_buf, "dhcp");
				cliData->tokenLen--;
				//Handle the command --> rout/wan>conntype 1
				if (cmdtreelevel==2){
					contypesetbridge=1;
					//prompt will be --> rout/wan/conntype>
					cmdtreelevel=cliData->tokenLen;
				}
				return cmdHelp(cli_table_wandhcp,cliData);
			}	
			if ( strcmp(uci_set_buf, "2")==0 ) {
				cli_set_uci(func_buf, "static");
				cliData->tokenLen--;
				//Handle the command --> rout/wan>conntype 2
				if (cmdtreelevel==2){
					contypesetbridge=2;
					//prompt will be --> rout/wan/conntype>
					cmdtreelevel=cliData->tokenLen;
				}
				return cmdHelp(cli_table_wanstaticip,cliData);
			}	
			if ( strcmp(uci_set_buf, "3")==0 ) {
				cli_set_uci(func_buf, "pppoe-custom");
				cliData->tokenLen--;
				//Handle the command --> rout/wan>conntype 3
				if (cmdtreelevel==2){
					contypesetbridge=3;
					//prompt will be --> rout/wan/conntype>
					cmdtreelevel=cliData->tokenLen;
				}
				return cmdHelp(cli_table_wanpppoe,cliData);	
			}
			if ( strcmp(uci_set_buf, "4")==0 ) {
				cli_set_uci(func_buf, "pptp-custom");
				cliData->tokenLen--;
				//Handle the command --> rout/wan>conntype 4
				if (cmdtreelevel==2){
					contypesetbridge=4;
					//prompt will be --> rout/wan/conntype>
					cmdtreelevel=cliData->tokenLen;
				}
				return cmdHelp(cli_table_wanpptp,cliData);	
			}	
				
		}

		else if ( contypesetbridge==1 )
			return getNextTable(cli_table_wandhcp, cliData);
		else if ( contypesetbridge==2 )
			return getNextTable(cli_table_wanstaticip, cliData);
		else if ( contypesetbridge==3 )
			return getNextTable(cli_table_wanpppoe, cliData);
		else if ( contypesetbridge==4 )
			return getNextTable(cli_table_wanpptp, cliData);
	}
	else if(cliData->argc>1){
		//handle relative path --> rout/wan/conntype>accname
		if ( contypesetbridge==1 )
			return getNextTable(cli_table_wandhcp, cliData);
		else if ( contypesetbridge==2 )
			return getNextTable(cli_table_wanstaticip, cliData);
		else if ( contypesetbridge==3 )
			return getNextTable(cli_table_wanpppoe, cliData);
		else if ( contypesetbridge==4 )
			return getNextTable(cli_table_wanpptp, cliData);

		if (!errorcheckValidDecimal(cliData->tokens[3].token) || !errorcheckIntRange( 1, 4, atoi(cliData->tokens[3].token)) )
	  		return CLI_PARAMS_ERR;

		//handle absolute path --> rout wan conntype accname
		if ( strcmp(cliData->tokens[3].token, "1")==0 ){
			cli_set_uci(func_buf, "dhcp");
			//Skip "1" when handling "rout wan conntype 1 accname"
			cliData->argc--;
			return getNextTable(cli_table_wandhcp, cliData);
		}
		if ( strcmp(cliData->tokens[3].token, "2")==0 ){
			cli_set_uci(func_buf, "static");
			//Skip "2" when handling "rout wan conntype 2 accname"
			cliData->argc--;
			return getNextTable(cli_table_wanstaticip, cliData);
		}
		if ( strcmp(cliData->tokens[3].token, "3")==0 ){
			cli_set_uci(func_buf, "pppoe-custom");
			//Skip "3" when handling "rout wan conntype 3 accname"
			cliData->argc--;
			return getNextTable(cli_table_wanpppoe, cliData);
		}
		if ( strcmp(cliData->tokens[3].token, "4")==0 ){
			cli_set_uci(func_buf, "pptp-custom");
			//Skip "4" when handling "rout wan conntype 4 accname"
			cliData->argc--;
			return getNextTable(cli_table_wanpptp, cliData);
		}
	
	}
}

/*****************************************************************
* NAME: cmddisping
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddisping(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.WANPingEnable";
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
* NAME: cmdaccname
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdaccname(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.wan.WANGeneralAccount";
T_CHAR uci_get_buf[51];
T_CHAR uci_set_buf[51];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		tprintf("Current setting: %s (50 characters at most)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 50, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of account name should not be larger than 50\n");
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
* NAME: cmddomname
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddomname(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.wan.WANGeneralDomain";
T_CHAR uci_get_buf[51];
T_CHAR uci_set_buf[51];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (50 characters at most)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 50, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of domain name should not be larger than 50\n");
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
* NAME: cmdmtumode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmtumode(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.wan.WANMTUMode";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Manual, 0:Auto)\n", uci_get_buf);
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
* NAME: cmdmtulen
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmtulen(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.wan.mtu";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (576-1500) \n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 576, 1500, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
* NAME: cmddnsmode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddnsmode(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.wan.WANDNSSourc";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Use DNS servers, 0:Get automatically from ISP)\n", uci_get_buf);
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
* NAME: cmdconntypeexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdconntypeexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	contypesetbridge=-1;

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}

/*****************************************************************
* NAME: cmdwanipaddr
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwanipaddr(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.wan.ipaddr";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Cliwanipset.ipset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		else{
			strcpy(uci_get_buf, Cliwanipset.ip);
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

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		strcpy(Cliwanipset.ip, uci_set_buf);
		Cliwanipset.ipset=1;
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwanipsubn
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwanipsubn(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.wan.netmask";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Cliwanipset.maskset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf);
		}
		else{
			strcpy(uci_get_buf, Cliwanipset.subnetmask);
			tprintf("Current setting: %s\n", uci_get_buf);
		}
			
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
	
		if (!errorcheckValidSubnetMask( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}		

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		strcpy(Cliwanipset.subnetmask, uci_set_buf);
		Cliwanipset.maskset=1;
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwangateway
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwangateway(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.wan.gateway";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Cliwanipset.gatewayset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		else{
			strcpy(uci_get_buf, Cliwanipset.gateway);
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

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		strcpy(Cliwanipset.gateway, uci_set_buf);
		Cliwanipset.gatewayset=1;
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwanipsetaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwanipsetaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.wan.ipaddr";
T_CHAR func_buf1[128]="network.wan.netmask";
T_CHAR func_buf2[128]="network.wan.gateway";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_get_buf2[128];

	if(cliData->argc==0){
		
		if (Cliwanipset.ipset==0)
			strcpy(uci_get_buf, cli_get_uci(func_buf));
		else
			strcpy(uci_get_buf, Cliwanipset.ip);

		if (Cliwanipset.maskset==0)
			strcpy(uci_get_buf1, cli_get_uci(func_buf1));
		else
			strcpy(uci_get_buf1, Cliwanipset.subnetmask);

		if (Cliwanipset.gatewayset==0)
			strcpy(uci_get_buf2, cli_get_uci(func_buf2));
		else
			strcpy(uci_get_buf2, Cliwanipset.gateway);
		
		if (!errorcheckValidIPandMask(uci_get_buf, uci_get_buf1)){
			cliData->tokenLen-=1;
			tprintf("Invalid IP address\n");
	  		return CLI_PARAMS_ERR;
		}
		if (!errorcheckSameDomain(uci_get_buf, uci_get_buf2, uci_get_buf1 )){
			cliData->tokenLen-=1;
			tprintf("Gateway address and IP address should be in the same subnet\n");
	  		return CLI_PARAMS_ERR;
		}

		cli_set_uci(func_buf, uci_get_buf);
		cli_set_uci(func_buf1, uci_get_buf1);
		cli_set_uci(func_buf2, uci_get_buf2);
		
		cliData->tokenLen--;
		return CLI_OK;

	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}

/*****************************************************************
* NAME: cmdwanipsetexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwanipsetexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	Cliwanipset.ipset=0;
	Cliwanipset.gatewayset=0;
	Cliwanipset.maskset=0;

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}

/*****************************************************************
* NAME: cmdpppoemtulen
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpppoemtulen(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="pppoe.pppoe.PPPOEMTU";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (576-1492)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 576, 1492, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
* NAME: cmdlogin
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdlogin(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="pppoe.pppoe.WANPPPoELoginName";
T_CHAR uci_get_buf[65];
T_CHAR uci_set_buf[65];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (64 characters at most)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		if (!errorcheckStrLength( 64, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of login account should not be larger than 64\n");
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
* NAME: cmdpppoepassw
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpppoepassw(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="pppoe.pppoe.WANPPPoEPassword";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (64 characters at most)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		if (!errorcheckStrLength( 64, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of login account should not be larger than 64\n");
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
* NAME: cmdsname
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsname(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="pppoe.pppoe.WANPPPoEServiceName";
T_CHAR uci_get_buf[51];
T_CHAR uci_set_buf[51];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (50 characters at most)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		if (!errorcheckStrLength( 50, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of service name should not be larger than 50\n");
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
* NAME: cmdconmode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdconmode(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="pppoe.pppoe.WANPPPoEConnectType";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Connect on Demand, 0:Redial Period)\n", uci_get_buf);
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
* NAME: cmdidle
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdidle(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="pppoe.pppoe.WANPPPoEMaxIdleTime";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s Minutes (1-99)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 99, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
* NAME: cmdperiod
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdperiod(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="pppoe.pppoe.WANPPPoERedialPeriod";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s Seconds (30-180)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 30, 180, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
* NAME: cmdpptpmtulen
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpptpmtulen(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="pptp.pptp.PPTPMTU";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1200-1400)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1200, 1400, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
* NAME: cmdpptps
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpptps(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="pptp.pptp.PPTPServerIP";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);
		tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		

		if (!errorcheckValidIP( uci_set_buf )){
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
* NAME: cmdpptpusername
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpptpusername(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="pptp.pptp.PPTPUserName";
T_CHAR uci_get_buf[65];
T_CHAR uci_set_buf[65];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (64 characters at most)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		if (!errorcheckStrLength( 64, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of user name should not be larger than 64\n");
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
* NAME: cmdpptppassw
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpptppassw(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="pptp.pptp.PPTPPassword";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (64 characters at most)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		if (!errorcheckStrLength( 64, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of user name should not be larger than 64\n");
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
* NAME: cmddhcpset
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddhcpset(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="dhcp.lan.ignore";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR c1[255];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if (strcmp(uci_get_buf, "1")==0)
			strcpy(uci_get_buf, "0");
		else if (strcmp(uci_get_buf, "0")==0)
			strcpy(uci_get_buf, "1");
		tprintf("Current setting: %s (1:Enable, 0:Disable)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
		
		if ( dhcpsetbridge==-1 ){
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
				cliData->tokenLen-=2;
				return CLI_PARAMS_ERR;
			}
			
			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
			
			if ( strcmp(uci_set_buf, "0")==0 ){
				
				strcpy(uci_set_buf, "1");
				cli_set_uci(func_buf, uci_set_buf);
				cliData->tokenLen-=2;
				return CLI_NOTHING;
			}
			if ( strcmp(uci_set_buf, "1")==0 ) {
				
				strcpy(uci_set_buf, "0");
				cli_set_uci(func_buf, uci_set_buf);
				cliData->tokenLen--;
				
				//Handle the command --> rout/lan/>dhcpset 1
				if (cmdtreelevel==2){
					dhcpsetbridge=1;
					//prompt will be --> rout/lan/dhcpset>
					cmdtreelevel=cliData->tokenLen;
				}
				
				return cmdHelp(cli_table_dhcpset,cliData);
			}
		}
		else if ( dhcpsetbridge==1 )
			return getNextTable(cli_table_dhcpset, cliData);
	}
	else if(cliData->argc>1){
		//handle relative path --> rout/lan/dhcpset>sip
		if ( dhcpsetbridge==1 )
			return getNextTable(cli_table_dhcpset, cliData);
		
		//handle too many argument --> rout/lan>dhcpset 0 X X ...
		if (strcmp(cliData->tokens[3].token, "0")==0 && cliData->tokenLen>=5)
			return CLI_PARAMS_ERR;
		
		//handle absolute path --> rout>lan dhcpset 1 sip
		if ( strcmp(cliData->tokens[3].token, "1")==0 ){
			cli_set_uci(func_buf, "0");
			//Skip "1" when handling "rout lan dhcpset 1 sip"
			cliData->argc--;
			return getNextTable(cli_table_dhcpset, cliData);
		}
		
	}
}

/*****************************************************************
* NAME: cmdlanipaddress
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdlanipaddress(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.ipaddr";
T_CHAR func_buf1[128]="network.lan.netmask";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR mask[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);
		tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		strcpy(mask, cli_get_uci(func_buf1));
		
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		if (!errorcheckValidIPandMask(cliData->tokens[cliData->tokenLen-1].token, mask)){
			cliData->tokenLen-=2;
			tprintf("Invalid IP address\n");
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
/*{ ### multiple items to be set at the same time
T_CHAR func_buf[128]="network.lan.ipaddr";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		Clilanipset.ipset=1;
		strcpy(Clilanipset.ip, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}*/

/*****************************************************************
* NAME: cmdlanipsubnet
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdlanipsubnet(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.netmask";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		if (!errorcheckValidSubnetMask( cliData->tokens[cliData->tokenLen-1].token )){
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
/*{ ### multiple items to be set at the same time
T_CHAR func_buf[128]="network.lan.netmask";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		Clilanipset.maskset=1;
		strcpy(Clilanipset.subnetmask, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}*/

/*****************************************************************
* NAME: cmdlanipaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
/*
CliStatus cmdlanipaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.ipaddr";
T_CHAR func_buf1[128]="network.lan.netmask";
T_CHAR uci_get_buf[128];
T_CHAR c1[255];

	if(cliData->argc==0){
		
		if (Clilanipset.ipset==0){
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			strcpy(Clilanipset.ip, uci_get_buf);
		}
		if (Clilanipset.maskset==0){
			strcpy(uci_get_buf, cli_get_uci(func_buf1));
			strcpy(Clilanipset.subnetmask, uci_get_buf);
		}		
		cli_set_uci(func_buf, Clilanipset.ip);
		cli_set_uci(func_buf1, Clilanipset.subnetmask);
		
		tprintf("Currunt LAN IP setting: %s\n", Clilanipset.ip);
		tprintf("Currunt subnetmask setting: %s\n", Clilanipset.subnetmask);
		
		Clilanipset.ipset=0;
		Clilanipset.maskset=0;
		strcpy(Clilanipset.ip, "");
		strcpy(Clilanipset.subnetmask, "");
		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}
*/
/*****************************************************************
* NAME: cmdlanipsetexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
/*
CliStatus cmdlanipsetexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	Clilanipset.ipset=0;
	Clilanipset.maskset=0;
	strcpy(Clilanipset.ip, "");
	strcpy(Clilanipset.subnetmask, "");

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}
*/
/*****************************************************************
* NAME: cmddhcpsip
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddhcpsip(T_VOID* priv, CliData* cliData)
{
/*
T_CHAR func_buf[128]="dhcp.lan.start";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		if (!errorcheckValidIP( uci_set_buf )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}
*/
//{ ### multiple items to be set at the same time
T_CHAR func_buf[128]="dhcp.lan.start";
T_CHAR uci_get_buf[32];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Clilandhcpset.startipset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		else{
			strcpy(uci_get_buf, Clilandhcpset.startip);
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
		
		Clilandhcpset.startipset=1;
		strcpy(Clilandhcpset.startip, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmddhcpeip
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddhcpeip(T_VOID* priv, CliData* cliData)
{
/*
T_CHAR func_buf[128]="dhcp.lan.dhcp_stop_addr";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		if (!errorcheckValidIP( uci_set_buf )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}
*/
//{ ### multiple items to be set at the same time
T_CHAR func_buf[128]="dhcp.lan.dhcp_stop_addr";
T_CHAR uci_get_buf[32];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Clilandhcpset.endipset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		else{
			strcpy(uci_get_buf, Clilandhcpset.endip);
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
		
		Clilandhcpset.endipset=1;
		strcpy(Clilandhcpset.endip, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmddhcpwip
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddhcpwip(T_VOID* priv, CliData* cliData)
{
/*
T_CHAR func_buf[128]="dhcp.lan.dhcp_option";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf+3);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){	
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		strcpy(uci_set_buf, "44,");	
		strcat(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}
*/
//{ ### multiple items to be set at the same time
T_CHAR func_buf[128]="dhcp.lan.dhcp_option";
T_CHAR uci_get_buf[32];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		if (Clilandhcpset.winsipset==0){

			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("Current setting: %s\n", uci_get_buf+3);
			tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		}
		else{
			strcpy(uci_get_buf, Clilandhcpset.winsip);
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
		
		Clilandhcpset.winsipset=1;
		strcpy(Clilandhcpset.winsip, "44,");
		strcat(Clilandhcpset.winsip, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}


/*****************************************************************
* NAME: cmddhcpsetaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/

CliStatus cmddhcpsetaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="dhcp.lan.start";
T_CHAR func_buf1[128]="dhcp.lan.dhcp_stop_addr";
T_CHAR func_buf2[128]="dhcp.lan.dhcp_option";
T_CHAR func_lanip[128]="network.lan.ipaddr";	
T_CHAR func_lanmask[128]="network.lan.netmask";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_get_buf2[128];
T_CHAR uci_get_lanip[128];
T_CHAR uci_get_lanmask[128];
T_CHAR c1[255];

	strcpy(uci_get_lanip, cli_get_uci(func_lanip));
	strcpy(uci_get_lanmask, cli_get_uci(func_lanmask));

	if(cliData->argc==0){
				
		if (Clilandhcpset.startipset==0)
			strcpy(uci_get_buf, cli_get_uci(func_buf));
		else
			strcpy(uci_get_buf, Clilandhcpset.startip);
		
		if (Clilandhcpset.endipset==0)
			strcpy(uci_get_buf1, cli_get_uci(func_buf1));
		else
			strcpy(uci_get_buf1, Clilandhcpset.endip);
		
		if (Clilandhcpset.winsipset==0)
			strcpy(uci_get_buf2, cli_get_uci(func_buf2));
		else
			strcpy(uci_get_buf2, Clilandhcpset.winsip);
		
		
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


/*****************************************************************
* NAME: cmddhcpsetexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/

CliStatus cmddhcpsetexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	dhcpsetbridge=-1;
	
	Clilandhcpset.startipset=0;
	Clilandhcpset.endipset=0;
	Clilandhcpset.winsipset=0;
	strcpy(Clilandhcpset.startip, "");
	strcpy(Clilandhcpset.endip, "");
	strcpy(Clilandhcpset.winsip, "");
	
	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}

/*****************************************************************
* NAME: cmdpptp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpptp(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.VPNPassthroughPPTP";
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
* NAME: cmdl2tp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdl2tp(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.VPNPassthroughL2TP";
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
* NAME: cmdipsec
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipsec(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.VPNPassthroughIPSec";
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
* NAME: cmdpflist
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpflist(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortForwardingNum";
T_CHAR uci_get_buf[128];
T_INT32 pfCount;
T_INT32 i;

	if(cliData->argc==0){		
		//PortForwardingNum is only in ECB350
		if ( strcmp(model_name, "ecb350")==0 ){
			strcpy(uci_get_buf, cli_get_uci(func_buf));
		
			displayPortforwarddata( atoi(uci_get_buf) );
			
  			if (atoi(uci_get_buf)==0)
				tprintf("Port forwarding list is empty.\n\n");
		
		}
		//PortForwardingNum is not exist in ENH
		else{
		
			pfCount=displayPortforwarddata( -1 );

			if (pfCount==0)
	    			tprintf("Port forwarding list is empty.\n\n");  
    		
    		}
    		
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdpfact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpfact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortForwardingEnable";
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
* NAME: cmdpfadd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpfadd(T_VOID* priv, CliData* cliData)
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
* NAME: cmdpfdel
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpfdel(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortForwardingNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];
T_CHAR tbuf[128];
T_CHAR pfline[12];
T_INT32 retval_int;
T_CHAR c1[255];
FILE *fp;
T_INT32 i;
T_INT32 pfCount;
T_INT32 deleteline;
T_CHAR* pflinenumber;

	if(cliData->argc==0){
		
		//PortForwardingNum is only in ECB350
		if ( strcmp(model_name, "ecb350")==0 ){
			strcpy(uci_get_buf, cli_get_uci(func_buf));
		
			displayPortforwarddata( atoi(uci_get_buf) );
			
			if (atoi(uci_get_buf)>0){
    				tprintf("Recognized input format: ");
    				for (i=1; i<atoi(uci_get_buf); i++)
    					tprintf("%d, ", i);
    				tprintf("%d\n", i);
    			}
    			else
    				tprintf("Port forwarding list is empty.\n\n");
		
		}
		//PortForwardingNum is not exist in ENH
		else{
		
			pfCount=displayPortforwarddata( -1 );

			if (pfCount>=1){
    				tprintf("Recognized input format: ");
    				for (i=1; i<pfCount; i++)
    					tprintf("%d, ", i);
    				tprintf("%d\n", i);
    			}
    			else
    				tprintf("Port forwarding list is empty.\n\n");    		
    		
    		}

    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		
		//PortForwardingNum is only in ECB350
		if ( strcmp(model_name, "ecb350")==0 ){
			//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
			if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
				sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

			strcpy(uci_get_buf, cli_get_uci(func_buf));		
			
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, atoi(uci_get_buf), atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
				cliData->tokenLen-=2;
		  		return CLI_PARAMS_ERR;
			}
			
			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
			retval_int=atoi(uci_set_buf);

			sprintf(c1, "uci delete ipnat.ipnat.PortForwardingList%d", retval_int);
	  		system(c1);
	  		system("uci commit");
		
			for (i=retval_int+1; i<=atoi(uci_get_buf); i++){
 	  			sprintf(c1, "sed -i \'s/PortForwardingList%d/PortForwardingList%d/g\' /etc/config/ipnat", i, i-1);
				system(c1);
			}
			
			sprintf(c1, "uci set ipnat.ipnat.PortForwardingNum=\'%d\'", atoi(uci_get_buf)-1);
	  		system(c1);
  		}
  		//PortForwardingNum is not exist in ENH
  		else{
  			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
			
			//find pfdata start line number
 			system("cat /etc/config/ipnat |grep -n \'VirServerTable\' >/tmp/pflinenumber");
  		
  			if((fp = fopen("/tmp/pflinenumber", "r"))==NULL){
				printf("Can't open file\n");
				return -1;
			}
			
			//find pfCount
			pfCount=0;
			
			if ( fgets(tbuf,sizeof(tbuf),fp)!=0 ){
				
				pfCount++;
				pflinenumber = strtok(tbuf, ":");
				strcpy(pfline,pflinenumber);
			
				while(fgets(tbuf,sizeof(tbuf),fp)){
					pfCount++;
	
				}
			
			}
			fclose(fp);
			
			if (!errorcheckValidDecimal(uci_set_buf) || !errorcheckIntRange( 1, pfCount, atoi(uci_set_buf)) ){
				cliData->tokenLen-=2;
		  		return CLI_PARAMS_ERR;
			}
		
			retval_int=atoi(uci_set_buf);
  			
			deleteline=retval_int+( atoi(pfline)-1 );
		
			sprintf(c1, "sed -i \'%dd\' /etc/config/ipnat", deleteline);
			system(c1);
  		}
  		
  		system("uci commit");
  		cliData->tokenLen-=2;
		return CLI_NOTHING;

	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdpfenable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpfenable(T_VOID* priv, CliData* cliData)
{
T_CHAR uci_set_buf[128];
T_CHAR tbuf[128];
T_CHAR pfline[12];
T_INT32 retval_int;
T_CHAR c1[255];
FILE *fp;
T_INT32 i;
T_INT32 pfCount;
T_INT32 enableline;
T_CHAR* pflinenumber;
    
	if(cliData->argc==0){
		
			pfCount=displayPortforwarddata( -1 );

			if (pfCount>=1){
    				tprintf("Recognized input format: ");
    				for (i=1; i<pfCount; i++)
    					tprintf("%d, ", i);
    				tprintf("%d\n", i);
    			}
    			else
    				tprintf("Port forwarding list is empty.\n\n");    		

    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
			//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
			if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
				sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
 			
 			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
			
			//find pfdata start line number
 			system("cat /etc/config/ipnat |grep -n \'VirServerTable\' >/tmp/pflinenumber");
  		
  			if((fp = fopen("/tmp/pflinenumber", "r"))==NULL){
				printf("Can't open file\n");
				return -1;
			}

			//find pfCount
			pfCount=0;
			
			if ( fgets(tbuf,sizeof(tbuf),fp)!=0 ){
				
				pfCount++;
				pflinenumber = strtok(tbuf, ":");
				strcpy(pfline,pflinenumber);
			
				while(fgets(tbuf,sizeof(tbuf),fp)){
					pfCount++;
	
				}
			
			}
			fclose(fp);

			if (!errorcheckValidDecimal(uci_set_buf) || !errorcheckIntRange( 1, pfCount, atoi(uci_set_buf)) ){
				cliData->tokenLen-=2;
		  		return CLI_PARAMS_ERR;
			}
		
			retval_int=atoi(uci_set_buf);
  			
			enableline=retval_int+( atoi(pfline)-1 );
		
			sprintf(c1, "sed -i '%ds/enable:0/enable:1/g' /etc/config/ipnat", enableline);
			system(c1);
  		
  		system("uci commit");
  		cliData->tokenLen-=2;
		return CLI_NOTHING;

	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdpfdisable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpfdisable(T_VOID* priv, CliData* cliData)
{
T_CHAR uci_set_buf[128];
T_CHAR tbuf[128];
T_CHAR pfline[12];
T_INT32 retval_int;
T_CHAR c1[255];
FILE *fp;
T_INT32 i;
T_INT32 pfCount;
T_INT32 disableline;
T_CHAR* pflinenumber; 
    
	if(cliData->argc==0){
		
			pfCount=displayPortforwarddata( -1 );

			if (pfCount>=1){
    				tprintf("Recognized input format: ");
    				for (i=1; i<pfCount; i++)
    					tprintf("%d, ", i);
    				tprintf("%d\n", i);
    			}
    			else
    				tprintf("Port forwarding list is empty.\n\n");    		

    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
			//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
			if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
				sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
		
  			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
			
			//find pfdata start line number
 			system("cat /etc/config/ipnat |grep -n \'VirServerTable\' >/tmp/pflinenumber");
  		
  			if((fp = fopen("/tmp/pflinenumber", "r"))==NULL){
				printf("Can't open file\n");
				return -1;
			}

			//find pfCount
			pfCount=0;
			
			if ( fgets(tbuf,sizeof(tbuf),fp)!=0 ){
				
				pfCount++;
				pflinenumber = strtok(tbuf, ":");
				strcpy(pfline,pflinenumber);
			
				while(fgets(tbuf,sizeof(tbuf),fp)){
					pfCount++;
				}
			
			}
			fclose(fp);

			if (!errorcheckValidDecimal(uci_set_buf) || !errorcheckIntRange( 1, pfCount, atoi(uci_set_buf)) ){
				cliData->tokenLen-=2;
		  		return CLI_PARAMS_ERR;
			}
		
			retval_int=atoi(uci_set_buf);
  			
			disableline=retval_int+( atoi(pfline)-1 );
		
			sprintf(c1, "sed -i '%ds/enable:1/enable:0/g' /etc/config/ipnat", disableline);
			system(c1);
  		
  		system("uci commit");
  		cliData->tokenLen-=2;
		return CLI_NOTHING;

	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdportforwardser
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdportforwardser(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortForwardingNum";
T_CHAR uci_get_buf[17];
T_CHAR uci_set_buf[17];

	if(cliData->argc==0){
/*		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//PortForwardingNum is only in ECB350
		if ( strcmp(model_name, "ecb350")==0 )
			displayPortforwarddata( atoi(uci_get_buf) );
		//PortForwardingNum is not exist in ENH
		else
			displayPortforwarddata( -1 );
*/    		tprintf("Recognized input format:   (16 characters at most).  EX: John\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 16, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of service name should not be larger than 16\n");
			cliData->tokenLen-=2;
			return CLI_PARAMS_ERR;
		}
		
		strcpy(CliRouterPortforward.servicename, cliData->tokens[cliData->tokenLen-1].token);		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdportforwardsetpro
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdportforwardsetpro(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortForwardingNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;

	if(cliData->argc==0){
/*		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//PortForwardingNum is only in ECB350
		if ( strcmp(model_name, "ecb350")==0 )
			displayPortforwarddata( atoi(uci_get_buf) );
		//PortForwardingNum is not exist in ENH
		else
			displayPortforwarddata( -1 );
*/   		tprintf("Recognized input format: 1, 2, 3 (1:Both, 2:TCP, 3:UDP)\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 3, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
	
		retval_int=atoi(uci_set_buf);
		if (retval_int==1)
			strcpy(uci_set_buf, "both");
		else if (retval_int==2)
			strcpy(uci_set_buf, "tcp");
		else if (retval_int==3)
			strcpy(uci_set_buf, "udp");
		
		strcpy(CliRouterPortforward.protocol, uci_set_buf);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdportforwardsetsport
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdportforwardsetsport(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortForwardingNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
/*		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//PortForwardingNum is only in ECB350
		if ( strcmp(model_name, "ecb350")==0 )
			displayPortforwarddata( atoi(uci_get_buf) );
		//PortForwardingNum is not exist in ENH
		else
			displayPortforwarddata( -1 );
*/    		tprintf("Recognized input format:  (1-65535)    EX: 23\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 65535, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		CliRouterPortforward.startportset=1;
		strcpy(CliRouterPortforward.startport, cliData->tokens[cliData->tokenLen-1].token);
					
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdportforwardseteport
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdportforwardseteport(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortForwardingNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
/*		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//PortForwardingNum is only in ECB350
		if ( strcmp(model_name, "ecb350")==0 )
			displayPortforwarddata( atoi(uci_get_buf) );
		//PortForwardingNum is not exist in ENH
		else
			displayPortforwarddata( -1 );
*/    		tprintf("Recognized input format:  (1-65535)    EX: 23\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 65535, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(CliRouterPortforward.endport, cliData->tokens[cliData->tokenLen-1].token);
			
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdportforwardsetipaddr
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdportforwardsetipaddr(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortForwardingNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
/*		strcpy(uci_get_buf, cli_get_uci(func_buf));

		//PortForwardingNum is only in ECB350
		if ( strcmp(model_name, "ecb350")==0 )
			displayPortforwarddata( atoi(uci_get_buf) );
		//PortForwardingNum is not exist in ENH
		else
			displayPortforwarddata( -1 );
*/    		tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		CliRouterPortforward.ipset=1;
		strcpy(CliRouterPortforward.ip, cliData->tokens[cliData->tokenLen-1].token);
		
			
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdportforwardaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdportforwardaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortForwardingNum";
T_CHAR func_lanip[128]="network.lan.ipaddr";
T_CHAR func_lanmask[128]="network.lan.netmask";
T_CHAR uci_get_lanip[128];
T_CHAR uci_get_lanmask[128];
T_CHAR uci_get_buf[128];
T_CHAR c1[255];

	strcpy(uci_get_lanip, cli_get_uci(func_lanip));
	strcpy(uci_get_lanmask, cli_get_uci(func_lanmask));

	if(cliData->argc==0){
		
		if (CliRouterPortforward.ipset==0 && CliRouterPortforward.startportset==0){
			tprintf("You forget to set IP address and start port number\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		if (CliRouterPortforward.ipset==0){
			tprintf("You forget to set IP Address\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		if (CliRouterPortforward.startportset==0){
			tprintf("You forget to set start port number\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		if (strcmp(CliRouterPortforward.endport, "")!=0 && (atoi(CliRouterPortforward.startport) > atoi(CliRouterPortforward.endport)) ){
			tprintf("Invalid port range\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		
		if (!errorcheckValidIPandMask(CliRouterPortforward.ip, uci_get_lanmask)){
			cliData->tokenLen-=1;
			tprintf("Invalid Portforward IP address\n");
	  		return CLI_PARAMS_ERR;
		}
		if (!errorcheckSameDomain(uci_get_lanip, CliRouterPortforward.ip, uci_get_lanmask )){
			cliData->tokenLen-=1;
			tprintf("Portforward IP address and LAN IP address should be in the same subnet\n");
	  		return CLI_PARAMS_ERR;
		}
		
		//PortForwardingNum is only in ECB350
		if ( strcmp(model_name, "ecb350")==0 ){
		
			strcpy(uci_get_buf, cli_get_uci(func_buf));		
			
			if (strcmp(CliRouterPortforward.endport, "")==0)
				strcpy(CliRouterPortforward.endport, CliRouterPortforward.startport);

			if ( !errorcheckPortforwardportrange(CliRouterPortforward.startport, CliRouterPortforward.endport, atoi(uci_get_buf))){
				tprintf("Overlaped port range\n");
				cliData->tokenLen--;
				return CLI_PARAMS_ERR;
			}
		
		
			sprintf(c1,"uci set ipnat.ipnat.PortForwardingNum=%d", atoi(uci_get_buf)+1);
			system(c1);
			sprintf(c1,"uci set ipnat.ipnat.PortForwardingList%d=\'enable:1 lanip:%s port:%s eport:%s proto:%s name:%s\'"
	  		,atoi(uci_get_buf)+1
	  		,CliRouterPortforward.ip
	  		,CliRouterPortforward.startport
	  		,CliRouterPortforward.endport
	   		,CliRouterPortforward.protocol
	   		,CliRouterPortforward.servicename
	   		);

	   	}
	   	//PortForwardingNum is not exist in ENH
	   	else{
	   		if (strcmp(CliRouterPortforward.endport, "")==0)
				strcpy(CliRouterPortforward.endport, CliRouterPortforward.startport);

			if ( !errorcheckPortforwardportrange(CliRouterPortforward.startport, CliRouterPortforward.endport, -1 )){
				tprintf("Overlaped port range\n");
				cliData->tokenLen--;
				return CLI_PARAMS_ERR;
			}
	   	
			sprintf(c1,"uci add_list ipnat.ipnat.VirServerTable=\"enable:1 lanip:%s port:%s eport:%s proto:%s name:%s\""
	  		,CliRouterPortforward.ip
	  		,CliRouterPortforward.startport
	  		,CliRouterPortforward.endport
	   		,CliRouterPortforward.protocol
	   		,CliRouterPortforward.servicename
	   		);	   	
	   	}
	   	
	   	system(c1);
		system("uci commit");

		CliRouterPortforward.startportset=0;
		CliRouterPortforward.ipset=0;
		strcpy(CliRouterPortforward.servicename, "");
		strcpy(CliRouterPortforward.protocol, "both");
		strcpy(CliRouterPortforward.ip, "");
		strcpy(CliRouterPortforward.startport, "");
		strcpy(CliRouterPortforward.endport, "");
		
		//PortForwardingNum is only in ECB350
		if ( strcmp(model_name, "ecb350")==0 )
			displayPortforwarddata( atoi(uci_get_buf)+1 );
		//PortForwardingNum is not exist in ENH
		else
			displayPortforwarddata( -1 );
		
		cliData->tokenLen--;
		return CLI_OK;

	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}



/*****************************************************************
* NAME: cmdportforwardexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdportforwardexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	CliRouterPortforward.startportset=0;
	CliRouterPortforward.ipset=0;
	strcpy(CliRouterPortforward.servicename, "");
	strcpy(CliRouterPortforward.protocol, "both");
	strcpy(CliRouterPortforward.ip, "");
	strcpy(CliRouterPortforward.startport, "");
	strcpy(CliRouterPortforward.endport, "");

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}


/*****************************************************************
* NAME: cmdptlist
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdptlist(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortTriggerNum";
T_CHAR uci_get_buf[128];

	if(cliData->argc==0){		

		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		displayPorttriggerdata( atoi(uci_get_buf) );
			
		if (atoi(uci_get_buf)==0)
			tprintf("Port triggering list is empty.\n\n");
		
    		
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdptact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdptact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortTriggerEnable";
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
* NAME: cmdptadd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdptadd(T_VOID* priv, CliData* cliData)
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
* NAME: cmdptdel
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdptdel(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortTriggerNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;
T_CHAR c1[255];
FILE *pp;
T_INT32 i;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displayPorttriggerdata( atoi(uci_get_buf) );
    		
    		if (atoi(uci_get_buf)>0){
    			tprintf("Recognized input format: ");
    			for (i=1; i<atoi(uci_get_buf); i++)
    				tprintf("%d, ", i);
    			tprintf("%d\n", i);
    		}
    		else
    			tprintf("Port trigger list is empty.\n");

    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
		
		strcpy(uci_get_buf, cli_get_uci(func_buf));		
		
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, atoi(uci_get_buf), atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		retval_int=atoi(uci_set_buf);

		sprintf(c1, "uci delete ipnat.ipnat.PortTriggerList%d", retval_int);
  		system(c1);
  		system("uci commit");
	
		for (i=retval_int+1; i<=atoi(uci_get_buf); i++){
   			sprintf(c1, "sed -i \'s/PortTriggerList%d/PortTriggerList%d/g\' /etc/config/ipnat", i, i-1);
			system(c1);
		}
			
		sprintf(c1, "uci set ipnat.ipnat.PortTriggerNum=\'%d\'", atoi(uci_get_buf)-1);
  		system(c1);
  		system("uci commit");
  		cliData->tokenLen-=2;
		return CLI_NOTHING;

	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdporttriggerser
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdporttriggerser(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortTriggerNum";
T_CHAR uci_get_buf[17];
T_CHAR uci_set_buf[17];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//displayPorttriggerdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format:   (16 characters at most).  EX: John\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 16, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of service name should not be larger than 16\n");
			cliData->tokenLen-=2;
			return CLI_PARAMS_ERR;
		}
		
		strcpy(CliRouterPorttrigger.servicename, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdporttriggersetsport
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdporttriggersetsport(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortTriggerNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//displayPorttriggerdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format:  (1-65535)    EX: 23\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 65535, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		CliRouterPorttrigger.startportset=1;
		strcpy(CliRouterPorttrigger.startport, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdporttriggerseteport
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdporttriggerseteport(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortTriggerNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//displayPorttriggerdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format:  (1-65535)    EX: 23\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 65535, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
	
		strcpy(CliRouterPorttrigger.endport, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdporttriggersettgtype
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdporttriggersettgtype(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortTriggerNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//displayPorttriggerdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format: 1, 2, 3 (1:Both, 2:TCP, 3:UDP)\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		if (!errorcheckValidDecimal(uci_set_buf) || !errorcheckIntRange( 1, 3, atoi(uci_set_buf)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		retval_int=atoi(uci_set_buf);
		if (retval_int==1)
			strcpy(uci_set_buf, "both");
		else if (retval_int==2)
			strcpy(uci_set_buf, "tcp");
		else if (retval_int==3)
			strcpy(uci_set_buf, "udp");
		
		strcpy(CliRouterPorttrigger.triggertype, uci_set_buf);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdporttriggersetfport
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdporttriggersetfport(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortTriggerNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//displayPorttriggerdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format:  (1-65535)    EX: 23\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 65535, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		CliRouterPorttrigger.forwardedportset=1;
		strcpy(CliRouterPorttrigger.forwardedport, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdporttriggersetpbtype
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdporttriggersetpbtype(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortTriggerNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//displayPorttriggerdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format: 1, 2, 3 (1:Both, 2:TCP, 3:UDP)\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 3, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		retval_int=atoi(uci_set_buf);
		if (retval_int==1)
			strcpy(uci_set_buf, "both");
		else if (retval_int==2)
			strcpy(uci_set_buf, "tcp");
		else if (retval_int==3)
			strcpy(uci_set_buf, "udp");
		
		strcpy(CliRouterPorttrigger.publictype, uci_set_buf);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdporttriggeraccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdporttriggeraccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.PortTriggerNum";
T_CHAR uci_get_buf[128];
T_CHAR c1[255];

	if(cliData->argc==0){	
		
		if (CliRouterPorttrigger.startportset==0 && CliRouterPorttrigger.forwardedportset==0){
			tprintf("You forget to set start trigger port number and forwarded port number\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		else if (CliRouterPorttrigger.startportset==0){
			tprintf("You forget to set start trigger port number\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		else if (CliRouterPorttrigger.forwardedportset==0){
			tprintf("You forget to set forwarded port number\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		else if (strcmp(CliRouterPorttrigger.endport, "")!=0 && (atoi(CliRouterPorttrigger.startport) > atoi(CliRouterPorttrigger.endport)) ){
			tprintf("Invalid trigger port range\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		else {
			strcpy(uci_get_buf, cli_get_uci(func_buf));
						
			if ( !errorcheckPorttriggerportrange(CliRouterPorttrigger.startport, CliRouterPorttrigger.endport, atoi(uci_get_buf))){
				tprintf("Overlaped trigger port range\n");
				cliData->tokenLen--;
				return CLI_PARAMS_ERR;
			}		
					
			sprintf(c1,"uci set ipnat.ipnat.PortTriggerNum=%d", atoi(uci_get_buf)+1);
			system(c1);
			sprintf(c1,"uci set ipnat.ipnat.PortTriggerList%d=TriSport:\'%s\',TriEport:\'%s\',TriggerType:\'%s\',Forport:\'%s\',PublicType:\'%s\',name:\'%s\'"
		  	,atoi(uci_get_buf)+1
		   	,CliRouterPorttrigger.startport
		   	,CliRouterPorttrigger.endport
		   	,CliRouterPorttrigger.triggertype
		   	,CliRouterPorttrigger.forwardedport
		   	,CliRouterPorttrigger.publictype
		   	,CliRouterPorttrigger.servicename
		   	);
		   	system(c1);
			system("uci commit");

			CliRouterPorttrigger.startportset=0;
			CliRouterPorttrigger.forwardedportset=0;
			strcpy(CliRouterPorttrigger.servicename, "");
			strcpy(CliRouterPorttrigger.startport, "");
			strcpy(CliRouterPorttrigger.endport, "");
			strcpy(CliRouterPorttrigger.triggertype, "both");
			strcpy(CliRouterPorttrigger.forwardedport, "");
			strcpy(CliRouterPorttrigger.publictype, "both");
			
			displayPorttriggerdata( atoi(uci_get_buf)+1 );
			cliData->tokenLen--;
			return CLI_OK;
		}
    		cliData->tokenLen--;
		return CLI_NOTHING;
	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdporttriggerexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdporttriggerexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	CliRouterPorttrigger.startportset=0;
	CliRouterPorttrigger.forwardedportset=0;
	strcpy(CliRouterPorttrigger.servicename, "");
	strcpy(CliRouterPorttrigger.startport, "");
	strcpy(CliRouterPorttrigger.endport, "");
	strcpy(CliRouterPorttrigger.triggertype, "both");
	strcpy(CliRouterPorttrigger.forwardedport, "");
	strcpy(CliRouterPorttrigger.publictype, "both");

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}

/*****************************************************************
* NAME: cmddmzact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddmzact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.DMZMode";
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
* NAME: cmddmzaddr
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddmzaddr(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.DMZIP";
T_CHAR func_lanip[128]="network.lan.ipaddr";
T_CHAR func_lanmask[128]="network.lan.netmask";
T_CHAR uci_get_lanip[128];
T_CHAR uci_get_lanmask[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
	
	strcpy(uci_get_lanip, cli_get_uci(func_lanip));
	strcpy(uci_get_lanmask, cli_get_uci(func_lanmask));

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
		if (!errorcheckSameDomain(uci_get_lanip, cliData->tokens[cliData->tokenLen-1].token, uci_get_lanmask )){
			cliData->tokenLen-=1;
			tprintf("DMZ IP address and LAN IP address should be in the same subnet\n");
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
* NAME: cmdmaclist
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmaclist(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.MACFilterNum";
T_CHAR uci_get_buf[128];

	if(cliData->argc==0){		

		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		displayRouterMACfilterdata( atoi(uci_get_buf) );
			
		if (atoi(uci_get_buf)==0)
			tprintf("MAC filter list is empty.\n\n");
		
    		
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdmacact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmacact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.MACFilterEnable";
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
* NAME: cmdmacmode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmacmode(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.MACFilterMode";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:REJECT, 2:ACCEPT)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 2, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		retval_int=atoi(uci_set_buf);
		if ( retval_int==1 || retval_int==2 ){	
			if (retval_int==1)
				strcpy(uci_set_buf, "REJECT");
			else if (retval_int==2)
				strcpy(uci_set_buf, "ACCEPT");
			cli_set_uci(func_buf, uci_set_buf);
			cliData->tokenLen-=2;
			return CLI_NOTHING;
		}
		else{
		  	cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;		
		}
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdmacadd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmacadd(T_VOID* priv, CliData* cliData)
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
* NAME: cmdmacdel
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmacdel(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.MACFilterNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;
T_CHAR c1[255];
FILE *pp;
T_INT32 i;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displayRouterMACfilterdata( atoi(uci_get_buf) );
    		
    		if (atoi(uci_get_buf)>0){
    			tprintf("Recognized input format: ");
    			for (i=1; i<atoi(uci_get_buf); i++)
    				tprintf("%d, ", i);
    			tprintf("%d\n", i);
    		}
    		else
    			tprintf("MAC filter list is empty.\n");

    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
		
		strcpy(uci_get_buf, cli_get_uci(func_buf));		

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, atoi(uci_get_buf), atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		retval_int=atoi(uci_set_buf);
		
		sprintf(c1, "uci delete ipnat.ipnat.MACFilterList%d", retval_int);
  		system(c1);
  		system("uci commit");
	
		for (i=retval_int+1; i<=atoi(uci_get_buf); i++){
   			sprintf(c1, "sed -i \'s/MACFilterList%d/MACFilterList%d/g\' /etc/config/ipnat", i, i-1);
			system(c1);
		}
			
		sprintf(c1, "uci set ipnat.ipnat.MACFilterNum=\'%d\'", atoi(uci_get_buf)-1);
  		system(c1);
  		system("uci commit");
  		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdmacser
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmacser(T_VOID* priv, CliData* cliData)
{
	if(cliData->argc==0){
    		tprintf("Recognized input format:   (16 characters at most).  EX: John\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 16, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of service name should not be larger than 16\n");
			cliData->tokenLen-=2;
			return CLI_PARAMS_ERR;
		}
		
		strcpy(CliRouterMACfilter.servicename, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdmacaddr
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmacaddr(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.MACFilterNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//displayRouterMACfilterdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format: XX:XX:XX:XX:XX:XX    EX: 00:02:6F:BE:F0:7A\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckValidMACaddess( cliData->tokens[cliData->tokenLen-1].token )){
			tprintf("The input is not valid MAC address\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;	
		}
		lower2upperMacAddress( cliData->tokens[cliData->tokenLen-1].token );
	
		CliRouterMACfilter.macset=1;
		strcpy(CliRouterMACfilter.macaddress, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdmacaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmacaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.MACFilterNum";
T_CHAR uci_get_buf[128];
T_CHAR c1[255];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		if (CliRouterMACfilter.macset==0){
			tprintf("You forget to set MAC Address\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		if (!checkRedundancyMAClist( CliRouterMACfilter.macaddress, atoi(uci_get_buf) )){
			cliData->tokenLen-=2;
			printf("The input MAC address has already existed\n");
	  		return CLI_PARAMS_ERR;	
		}
						
		sprintf(c1,"uci set ipnat.ipnat.MACFilterNum=%d", atoi(uci_get_buf)+1);
		system(c1);
		sprintf(c1,"uci set ipnat.ipnat.MACFilterList%d=maclist:\'%s\',name:\'%s\'"
	  	,atoi(uci_get_buf)+1
	   	,CliRouterMACfilter.macaddress
	   	,CliRouterMACfilter.servicename
	   	);
	   	system(c1);
		system("uci commit");
		strcpy(CliRouterMACfilter.servicename, "");
		CliRouterMACfilter.macset=0;
		strcpy(CliRouterMACfilter.macaddress, "");
		displayRouterMACfilterdata( atoi(uci_get_buf)+1 );
		
		cliData->tokenLen--;
		return CLI_OK;

	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdroutermacfilterexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdroutermacfilterexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	strcpy(CliRouterMACfilter.servicename, "");
	CliRouterMACfilter.macset=0;
	strcpy(CliRouterMACfilter.macaddress, "");

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}

/*****************************************************************
* NAME: cmdipact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.IPFilterEnable";
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
* NAME: cmdipmode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipmode(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.IPFilterMode";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:REJECT, 2:ACCEPT)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 2, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		retval_int=atoi(uci_set_buf);
		if ( retval_int==1 || retval_int==2 ){	
			if (retval_int==1)
				strcpy(uci_set_buf, "REJECT");
			else if (retval_int==2)
				strcpy(uci_set_buf, "ACCEPT");
			cli_set_uci(func_buf, uci_set_buf);
			cliData->tokenLen-=2;
			return CLI_NOTHING;
		}
		else{
		  	cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;		
		}
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdipadd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipadd(T_VOID* priv, CliData* cliData)
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
* NAME: cmdipdel
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipdel(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.IPFilterNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;
T_CHAR c1[255];
FILE *pp;
T_INT32 i;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displayIPfilterdata( atoi(uci_get_buf) );
    		
    		if (atoi(uci_get_buf)>0){
    			tprintf("Recognized input format: ");
    			for (i=1; i<atoi(uci_get_buf); i++)
    				tprintf("%d, ", i);
    			tprintf("%d\n", i);
    		}
    		else
    			tprintf("IP filter list is empty.\n");

    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		strcpy(uci_get_buf, cli_get_uci(func_buf));		
		
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, atoi(uci_get_buf), atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		retval_int=atoi(uci_set_buf);
		if ( retval_int>=1 && retval_int<= atoi(uci_get_buf) ){
			sprintf(c1, "uci delete ipnat.ipnat.IPFilterList%d", retval_int);
	  		system(c1);
	  		system("uci commit");
		
			for (i=retval_int+1; i<=atoi(uci_get_buf); i++){
	   			sprintf(c1, "sed -i \'s/IPFilterList%d/IPFilterList%d/g\' /etc/config/ipnat", i, i-1);
				system(c1);
			}
			
			sprintf(c1, "uci set ipnat.ipnat.IPFilterNum=\'%d\'", atoi(uci_get_buf)-1);
	  		system(c1);
	  		system("uci commit");
	  		cliData->tokenLen-=2;
			return CLI_NOTHING;
	  	}
	  	else{
	  		cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
	  	}
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdipser
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipser(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.IPFilterNum";
T_CHAR uci_get_buf[17];
T_CHAR uci_set_buf[17];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displayIPfilterdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format:   (16 characters at most) EX: John\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 16, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of service name should not be larger than 16\n");
			cliData->tokenLen-=2;
			return CLI_PARAMS_ERR;
		}
		
		strcpy(CliRouterIPfilter.servicename, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdipsetpro
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipsetpro(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.IPFilterNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displayIPfilterdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format: 1, 2, 3 (1:Both, 2:TCP, 3:UDP)\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 3, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		retval_int=atoi(uci_set_buf);
		if (retval_int==1)
			strcpy(uci_set_buf, "both");
		else if (retval_int==2)
			strcpy(uci_set_buf, "tcp");
		else if (retval_int==3)
			strcpy(uci_set_buf, "udp");
		
		strcpy(CliRouterIPfilter.protocol, uci_set_buf);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdipsetsip
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipsetsip(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.IPFilterNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displayIPfilterdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		CliRouterIPfilter.startipset=1;
		strcpy(CliRouterIPfilter.startip, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdipseteip
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipseteip(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.IPFilterNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displayIPfilterdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(CliRouterIPfilter.endip, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdipsetsport
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipsetsport(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.IPFilterNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displayIPfilterdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format:  (1-65535)    EX: 23\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 65535, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(CliRouterIPfilter.startport, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdipseteport
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipseteport(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.IPFilterNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displayIPfilterdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format:  (1-65535)    EX: 23\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 65535, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(CliRouterIPfilter.endport, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdipaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.IPFilterNum";
T_CHAR func_lanip[128]="network.lan.ipaddr";
T_CHAR func_lanmask[128]="network.lan.netmask";
T_CHAR uci_get_lanip[128];
T_CHAR uci_get_lanmask[128];
T_CHAR uci_get_buf[128];
T_CHAR ip1[16];
T_CHAR ip2[16];
T_CHAR c1[255];

	strcpy(uci_get_lanip, cli_get_uci(func_lanip));
	strcpy(uci_get_lanmask, cli_get_uci(func_lanmask));
	
	if(cliData->argc==0){
		
		if (CliRouterIPfilter.startipset==0){
			tprintf("You forget to set start IP address\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		
		if (CliRouterIPfilter.startipset==0){
			tprintf("You forget to set start IP Address\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		
		if (!errorcheckSameDomain(uci_get_lanip, CliRouterIPfilter.startip, uci_get_lanmask )){
			cliData->tokenLen-=1;
			tprintf("Start IP address and LAN IP address should be in the same subnet\n");
	  		return CLI_PARAMS_ERR;
		}

		if ( (strcmp(CliRouterIPfilter.endip, "")!=0) && (!errorcheckSameDomain(uci_get_lanip, CliRouterIPfilter.endip, uci_get_lanmask )) ){
		
			cliData->tokenLen-=1;
			tprintf("End IP address and LAN IP address should be in the same subnet\n");
	  		return CLI_PARAMS_ERR;
		}
		
		if ( (strcmp(CliRouterIPfilter.endip, "")!=0) && (!errorcheckDHCPRange(CliRouterIPfilter.startip, CliRouterIPfilter.endip )) ){
			cliData->tokenLen-=1;
			tprintf("IP filter end IP address is less than IP filter start IP address\n");
	  		return CLI_PARAMS_ERR;
		}


		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		strcpy(ip1, CliRouterIPfilter.startip);
		strcpy(ip2, CliRouterIPfilter.endip);
		
		if (!errorcheckIPfilterrange(ip1, ip2, atoi(uci_get_buf) )){
			cliData->tokenLen-=1;
			tprintf("Overlap IP range.\n");
	  		return CLI_PARAMS_ERR;
		}
	
					
		sprintf(c1,"uci set ipnat.ipnat.IPFilterNum=%d", atoi(uci_get_buf)+1);
		system(c1);
		sprintf(c1,"uci set ipnat.ipnat.IPFilterList%d=pro:\'%s\',SIP:\'%s\',EIP:\'%s\',Sport:\'%s\',Eport:\'%s\',name:\'%s\'"
	  	,atoi(uci_get_buf)+1
	   	,CliRouterIPfilter.protocol
	   	,CliRouterIPfilter.startip
	   	,CliRouterIPfilter.endip
	   	,CliRouterIPfilter.startport
	   	,CliRouterIPfilter.endport
	   	,CliRouterIPfilter.servicename
	   	);
	   	system(c1);
		system("uci commit");

		CliRouterIPfilter.startipset=0;
		strcpy(CliRouterIPfilter.servicename, "");
		strcpy(CliRouterIPfilter.protocol, "both");
		strcpy(CliRouterIPfilter.startip, "");
		strcpy(CliRouterIPfilter.endip, "");
		strcpy(CliRouterIPfilter.startport, "");
		strcpy(CliRouterIPfilter.endport, "");
		
		displayIPfilterdata( atoi(uci_get_buf)+1 );
		cliData->tokenLen--;
		return CLI_OK;

	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdipfilterexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdipfilterexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	CliRouterIPfilter.startipset=0;
	strcpy(CliRouterIPfilter.servicename, "");
	strcpy(CliRouterIPfilter.protocol, "both");
	strcpy(CliRouterIPfilter.startip, "");
	strcpy(CliRouterIPfilter.endip, "");
	strcpy(CliRouterIPfilter.startport, "");
	strcpy(CliRouterIPfilter.endport, "");

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}

/*****************************************************************
* NAME: cmdurlact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdurlact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.URLFilterEnable";
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
* NAME: cmdurladd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdurladd(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.URLFilterNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[255];
T_INT32 retval_int;
T_CHAR c1[300];
//char * c1;
FILE *pp;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displayURLfilterdata( atoi(uci_get_buf) );
    		tprintf("Recognized input format: Website or Keyword    EX: www.facebook.com or facebook\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid segmentation fault when the length of input > 255 
		if (!errorcheckStrLength( 255, cliData->tokens[cliData->tokenLen-1].token)){
			tprintf("The length of URL should not be larger than 255\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}			
		strcpy(uci_get_buf, cli_get_uci(func_buf));		
		//strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		sprintf(c1,"uci set ipnat.ipnat.URLFilterNum=%d", atoi(uci_get_buf)+1);
		system(c1);

		sprintf(c1,"uci set ipnat.ipnat.URLFilterList%d=name:\'%s\'"
	  	,atoi(uci_get_buf)+1
	   	,cliData->tokens[cliData->tokenLen-1].token
	   	);

	   	system(c1);
		system("uci commit");

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdurldel
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdurldel(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.URLFilterNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;
T_CHAR c1[255];
FILE *pp;
T_INT32 i;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displayURLfilterdata( atoi(uci_get_buf) );
    		
    		if (atoi(uci_get_buf)>0){
    			tprintf("Recognized input format: ");
    			for (i=1; i<atoi(uci_get_buf); i++)
    				tprintf("%d, ", i);
    			tprintf("%d\n", i);
    		}
    		else
    			tprintf("URL filter list is empty.\n");

    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
			
		strcpy(uci_get_buf, cli_get_uci(func_buf));		
		
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, atoi(uci_get_buf), atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		retval_int=atoi(uci_set_buf);
		if ( retval_int>=1 && retval_int<= atoi(uci_get_buf) ){
			sprintf(c1, "uci delete ipnat.ipnat.URLFilterList%d", retval_int);
	  		system(c1);
	  		system("uci commit");
		
			for (i=retval_int+1; i<=atoi(uci_get_buf); i++){
	   			sprintf(c1, "sed -i \'s/URLFilterList%d/URLFilterList%d/g\' /etc/config/ipnat", i, i-1);
				system(c1);
			}
			
			sprintf(c1, "uci set ipnat.ipnat.URLFilterNum=\'%d\'", atoi(uci_get_buf)-1);
	  		system(c1);
	  		system("uci commit");
	  		cliData->tokenLen-=2;
			return CLI_NOTHING;
	  	}
	  	else{
	  		cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
	  	}
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}



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
;    Creator : cfho
;    File    : dummy.c
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       cfho            2008-0521       Create
;*****************************************************************************/

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <sap_osapi.h>
#include <sap_ostypes.h>
#include <gconfig.h>
#include <tokens.h>
#include <apcfg.h>
#include <sysUtil.h>
#include <schedule.h>
#include <system.h>
#include <common.h>
#include <uci.h>

#include <arpa/inet.h>

#if FOR_ZYXEL_CLI
#include <netDevInfo.h>
#include <sysProduct.h>
#include <webaccount.h>
#endif

T_INT32 bad_mask(T_UINT32 mask, T_UINT32 addr)
{
        if (addr & (mask = ~mask))
                return 1;
        mask = ntohl(mask);
        if (mask & (mask+1))
                return 1;
        return 0;
}

/*-------------------------------------------------------------------------*/
/*                           GLOBAL VARIABLE                               */
/*-------------------------------------------------------------------------*/

                    //AP, CB, WDSAP, WDSB, WDSSTA, AR, CR, RP, NAWDS, MESH
T_INT32 wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24};
T_INT32 radio_shift=26;

//diagnostics parameters
T_CHAR target_ip[64]="";
T_INT32 packet_size=64;
T_INT32 number_of_ping=4;

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/

typedef struct __CliHostnameEntry
{
    const T_INT32 hostAntenna;	//for datarate use
    const T_INT32 hostRadio;	//for single-radio or dual-radio use
    const T_INT32 ssidCount_ap;	//for AP wireless interface use
    const T_INT32 ssidCount_apwds;	//for APWDS wireless interface use
    const T_INT32 wdsCount_apwds;	//for APWDS nawds interface use
    const T_INT32 wdsCount_brwds;	//for BRWDS nawds interface use    
    const T_INT32 maxpower;	//for 2.4G txpower use
    const T_INT32 maxpower_5;	//for 5G txpower use
    const T_CHAR* hostName;	//for identify model and use to survey other fields
    const T_INT32 opmode;	//for list all the opmodes which the model offers
    const T_INT32 opmodeCount;	//for cmdopmode errorcheck range when we select the opmode
//    const T_INT32 modelID;	//for control the functions which the model offers

//Modify on 2013-09-05 to extend the number of Model to 64
    const long long modelID;
    

}CliHostnameEntry;
 
typedef struct __CliHostnamelist
{
	T_INT32 count;
	CliHostnameEntry CliHostnameTable[54];

}CliHostnamelist;
extern CliHostnamelist HostnameData;

typedef struct __CliTxpowerEntry
{
    const T_INT32 item;	
    const T_CHAR* txpowerName;

}CliTxpowerEntry;

CliTxpowerEntry CliTxpowerTable[] = {

	{1, "11"},
	{2, "12"},
	{3, "13"},
	{4, "14"},
	{5, "15"},
	{6, "16"},
	{7, "17"},
	{8, "18"},
	{9, "19"},
	{10, "20"},
	{11, "21"},
	{12, "22"},
	{13, "23"},
	{14, "24"},
	{15, "25"},
	{16, "26"},	  
	{17, "27"},
	{18, "28"},
	{19, "29"},

};

/*
//Jacy ask to keep wepkey but to take off wepkeylength
typedef struct __CliWDSWEPkeysetEntry
{
	//T_INT32 wdswepkeylengthset;
	//T_INT32 wdswepkeyset;

	T_INT32 wdswepkeylength;
	T_CHAR wdswepkey[32];

}CliWDSWEPkeysetEntry;
static CliWDSWEPkeysetEntry CliWDSWEPkeyset={10, ""};
*/


/*-------------------------------------------------------------------------*/
/*                           Parameter                                     */
/*-------------------------------------------------------------------------*/
extern CliEntry cmdBasicTable[];

extern CliEntry cli_table_vlanp[];
extern CliEntry cli_table_vlanp2[];
extern CliEntry cli_table_vlanp25[];
extern CliEntry cli_table_vlanp5[];

extern T_INT32 SSIDProfileIndex;
extern T_INT32 cmdtreelevel;

extern AuthStatus g_auth; // auth status
extern T_UINT32 g_opmode;

static struct uci_context *ctx;
static struct uci_ptr ptr;
extern T_CHAR model_name[];

//extern T_INT32 model_ID;

//Modify on 2013-09-05 to extend the number of Model to 64
extern long long model_ID;

extern T_CHAR current_radio_flag[5];
extern T_UINT32 current_opmode;
extern T_UINT32 current_opmode_2;
extern T_UINT32 current_opmode_5;
extern T_INT32 model_radio;


/*engenius*/


/*****************************************************************
* NAME: convert_Wifi_Index
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID convert_Wifi_Index(char * token){
#define	tagWIFI1	"wireless.wifi1."
#define	tagWIFI1_IFACE	"wireless.@wifi-iface["
char	*psz, *pszEnd;
	
//	printf("Before token=%s\n", token);
	
	psz = strstr(token, tagWIFI1);
	if ( psz ){
		psz[strlen(tagWIFI1) - 2] = '0';
	}
	else
	{
		int	iIndex;
		
		psz = strstr(token, tagWIFI1_IFACE);
		if (psz)
		{
			psz += strlen(tagWIFI1_IFACE);
			pszEnd = strstr(psz, "].");
			if (pszEnd)
			{
				iIndex = atoi(psz);
				if (iIndex >= 26)
				{
					iIndex -= 26;
					sprintf (psz, "%d%s", iIndex, pszEnd);
				}
			}
		}
	}
//	printf("After token=%s\n", token);
	
}

/*****************************************************************
* NAME: cli_get_uci
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
char *cli_get_uci(char * token){

//unsigned char octetstr_value[255];
//char tmp_token[255];
//Modify on 2013-08-07 by Philips to allow the length of value to be more than 255 which is requested by Jacy
unsigned char octetstr_value[1032];
char tmp_token[1032];

int j;
char * result="error!!";

//Modify for AP100 on 2012-11-06
if ( strcmp(model_name, "ap100")==0  )
	convert_Wifi_Index(token);

//printf("1.in cli_get_uci token=%s\n", token);
	for (j=0; j< strlen(token); j++)
	    tmp_token[j]=token[j];	  
	tmp_token[strlen(token)]='\0';

	ctx = uci_alloc_context();
                if (!ctx) {
                printf("----- Out of memory -----\n");
                return result;
        	}
//printf("2.in cli_get_uci token=%s\n", token);
	if (uci_lookup_ptr(ctx, &ptr, tmp_token, true) != UCI_OK) {
		printf("-----  get value false -----\n");		
		return result;
	}
//printf("3.in cli_get_uci token=%s\n", token);
	if (!(ptr.flags & UCI_LOOKUP_COMPLETE) || (ptr.o->v.string == NULL)) {   /*from cli.c line.275*/
	   //printf("-----  Entry not found -----\n");
//printf("4.in cli_get_uci token=%s\n", token);
	   memset(octetstr_value, 0, sizeof(octetstr_value)); 
	   strcpy(octetstr_value, ""); 	   
        }
	else{
//printf("5.in cli_get_uci token=%s\n", token);
	   memset(octetstr_value, 0, sizeof(octetstr_value)); 
	   strcpy(octetstr_value , ptr.o->v.string);
        }
//printf("6.in cli_get_uci token=%s\n", token);
	octetstr_value[strlen(octetstr_value)]='\0';   
//	uci_load_plugins(ctx, NULL);
	uci_free_context(ctx);
	return octetstr_value;
}

/*****************************************************************
* NAME: cli_set_uci
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
int cli_set_uci(char* token, char* token2){


//char setstring[255];
//char buf[255];
//Modify on 2013-08-07 by Philips to allow the length of value to be more than 255 which is requested by Jacy
char setstring[1032];
char buf[1032];

int j;
int ret;

//Modify for AP100 on 2012-11-06
if ( strcmp(model_name, "ap100")==0  )
	convert_Wifi_Index(token);

//printf("1.in cli_set_uci token=%s\ntoken2=%s\n", token, token2);
	memset(buf, 0, sizeof(buf));
	strcat(buf, token);  
	buf[strlen(token)]='\0';

	ctx = uci_alloc_context();
	if (!ctx) {
		printf("----- Out of memory -----\n");
		return 1;
	}

	strcat(buf, "=");
	for (j=0; j< strlen(token2); j++)
	    setstring[j]=token2[j];	  
	setstring[strlen(token2)]='\0';
	//strcat(buf, "\"");
	strcat(buf, setstring);
	//strcat(buf, "\"");

	if (uci_lookup_ptr(ctx, &ptr, buf, true) != UCI_OK) {
		printf("UCI search (set) failed\n");
		return 1;
	}

	ret = uci_set(ctx, &ptr);
	ret = uci_save(ctx, ptr.p); //we can use either uci_save or uci_commit

	if (uci_commit(ctx, &ptr.p, false) != UCI_OK)		 
		printf("----- Commit value false. -----\n");

	uci_unload(ctx, ptr.p);
//	uci_load_plugins(ctx, NULL);
	uci_free_context(ctx);

	return ret;
}


/*****************************************************************
* NAME: getSysOperationMode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID getSysOperationMode(T_VOID) {
T_CHAR func_buf[128]="network.sys.opmode";
T_CHAR func_buf1[128]="wireless.wifi0.opmode";
T_CHAR func_buf2[128]="wireless.wifi1.opmode";
T_CHAR uci_get_buf1[128];
T_CHAR uci_get_buf2[128];
	
	if (model_radio==2 || model_radio==5)	
		strcpy(uci_get_buf1, cli_get_uci(func_buf));
	if (model_radio==7){
		strcpy(uci_get_buf1, cli_get_uci(func_buf1));
		strcpy(uci_get_buf2, cli_get_uci(func_buf2));
	}

	//get operation mode for single-radio 
	if (model_radio==2 || model_radio==5){
	
		switch (uci_get_buf1[0]){
			
		case 'a':
			if (uci_get_buf1[2]=='r')
				current_opmode = OPM_AR;
			else if (uci_get_buf1[2]=='w')
				current_opmode = OPM_WDSAP;
			else 
				current_opmode = OPM_AP;
			break;
		case 'b':
			current_opmode = OPM_WDSB;
			break;
		case 'c':
			current_opmode = OPM_CBRT;
			break;
		case 'r':
			current_opmode = OPM_RP;
			break;
		case 's':
			if (uci_get_buf1[3]=='w')
				current_opmode = OPM_WDSSTA;
			else
				current_opmode = OPM_CB;
			break;	
		}

	}

	//get operation mode for dual-radio 2.4G
	if (model_radio==7){
	
		switch (uci_get_buf1[0]){
			
		case 'a':
			if (uci_get_buf1[2]=='r')
				current_opmode_2 = OPM_AR;
			else if (uci_get_buf1[2]=='w')
				current_opmode_2 = OPM_WDSAP;
			else 
				current_opmode_2 = OPM_AP;
			break;
		case 'b':
			current_opmode_2 = OPM_WDSB;
			break;
		case 'c':
			current_opmode_2 = OPM_CBRT;
			break;
		case 'r':
			current_opmode_2 = OPM_RP;
			break;
		case 's':
			if (uci_get_buf1[3]=='w')
				current_opmode_2 = OPM_WDSSTA;
			else
				current_opmode_2 = OPM_CB;
			break;	
		}
	}
	
	//get operation mode for dual-radio 5G
	if (model_radio==7){
	
		switch (uci_get_buf2[0]){
			
		case 'a':
			if (uci_get_buf2[2]=='r')
				current_opmode_5 = OPM_AR;
			else if (uci_get_buf2[2]=='w')
				current_opmode_5 = OPM_WDSAP;
			else 
				current_opmode_5 = OPM_AP;
			break;
		case 'b':
			current_opmode_5 = OPM_WDSB;
			break;
		case 'c':
			current_opmode_5 = OPM_CBRT;
			break;
		case 'r':
			current_opmode_5 = OPM_RP;
			break;
		case 's':
			if (uci_get_buf2[3]=='w')
				current_opmode_5 = OPM_WDSSTA;
			else
				current_opmode_5 = OPM_CB;
			break;	
		}
	}

}

/*-------------------------------------------------------------------------*/
/*                           Errorcheck                                     */
/*-------------------------------------------------------------------------*/

/*****************************************************************
* NAME: errorcheckValidDecimal
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_INT32 errorcheckValidDecimal(const char *hex)
{
	
	if (*hex == '-') {
//		tprintf("This is a negative number\n");
		++hex;
	}
	
	while (*hex) {
		if (!isdigit(*hex))
			return 0;
		++hex;
	}
	return 1;
}

/*****************************************************************
* NAME: errorcheckValidHex
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_INT32 errorcheckValidHex(const char *hex)
{
	while (*hex) {
		if (!isxdigit(*hex))
			return 0;
		++hex;
	}
	return 1;
}

/*****************************************************************
* NAME: errorcheckValidMACaddess
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_INT32 errorcheckValidMACaddess(const char *mac)
{
int digitalNumber = 0;
int colonNumber = 0;
T_CHAR m;

	//Check the second byte is not 1, 3, 5, 7, 9, B, D, F
	m = *(mac+1);
	if ( m=='1' || m=='3' || m=='5' || m=='7' || m=='9' )
		return 0;
	if ( m=='b' || m=='B' || m=='d' || m=='D' || m=='f' ||m=='F' )
		return 0;
	//Check the while MAC address
	while (*mac) {
		if (isxdigit(*mac)) {
			digitalNumber++;
		}
		else if ( *mac == ':' ) {
			if (digitalNumber == 0 || digitalNumber / 2 - 1 != colonNumber)
				break;
			
			++colonNumber;
		}
        	else {
			colonNumber = -1;
		}
		
		++mac;
	}

//	return (digitalNumber == 12 && (colonNumber == 5 || colonNumber == 0));
	//Modify by Philips on 2012-10-17 to avoid the MAC address without ":", such as 001122334455 
	return (digitalNumber == 12 && colonNumber == 5);
}

/*****************************************************************
* NAME: errorcheckValidIP
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_INT32 errorcheckValidIP(const char *ip_str)
{
/*
unsigned int n1,n2,n3,n4;
T_CHAR buf[64];

	if(sscanf(ip_str,"%u.%u.%u.%u", &n1, &n2, &n3, &n4) != 4) return 0;
	
	if ( (n1 < 0) || (n2 < 0) || (n3 < 0) || (n4 < 0) )
		return 0;
			
	if((n1 != 0) && (n1 != 127) && (n1 < 224) && (n2 < 256) && (n3 < 256) && (n4 < 256) ) {
		
		sprintf(buf,"%u.%u.%u.%u",n1,n2,n3,n4);
		if( strcmp(buf,ip_str)!=0 ) return 0;
		return 1;
	}
	return 0;
*/
	
T_INT32 rc;
struct in6_addr octetstr_ipv4;

//	rc = inet_pton(AF_INET, "192.168.1.100", &octetstr_ipv6);
//	rc = inet_pton(AF_INET6, "2001:0db8:85a3:08d3:1319:8a2e:0370:7344", &octetstr_ipv6);
	rc = inet_pton(AF_INET, ip_str, &octetstr_ipv4);
	if (rc == 0)
		printf("\n\"%s\" is a invalid IPv4 address.\n", ip_str);
	
	return rc;
}

/*****************************************************************
* NAME: errorcheckValidIPv6
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-29 to support checking function for IPV6 address
* Modify:   
****************************************************************/
T_INT32 errorcheckValidIPv6(const char *ip_str)
{
T_INT32 rc;
struct in6_addr octetstr_ipv6;

//	rc = inet_pton(AF_INET, "192.168.1.100", &octetstr_ipv6);
//	rc = inet_pton(AF_INET6, "2001:0db8:85a3:08d3:1319:8a2e:0370:7344", &octetstr_ipv6);
	rc = inet_pton(AF_INET6, ip_str, &octetstr_ipv6);
	if (rc == 0)
		printf("\n\"%s\" is a invalid IPv6 address.\n", ip_str);
	
	return rc;
}

/*****************************************************************
* NAME: errorcheckValidIPandMask
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/

T_INT32 errorcheckValidIPandMask(const char *ip_str, const char *mask_str)
{
unsigned int n1,n2,n3,n4;
unsigned int m1,m2,m3,m4;
unsigned int ip;
unsigned int mask;

	if(sscanf(ip_str,"%u.%u.%u.%u", &n1, &n2, &n3, &n4) != 4) return 0;
	if(sscanf(mask_str,"%u.%u.%u.%u", &m1, &m2, &m3, &m4) != 4) return 0;
	
	ip = ((((((n1<<8)|n2)<<8)|n3)<<8)|n4);
	mask = ((((((m1<<8)|m2)<<8)|m3)<<8)|m4);
	
	//printf("ip=%x, mask=%x\n", ip, mask);
	
	if ((ip & ~mask)==0) //Host id is all 0
		return 0;
	if ((ip & ~mask)==~mask) //Host id is all 1
		return 0;
	return 1;
}


/*****************************************************************
* NAME: errorcheckValidSubnetMask
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_INT32 errorcheckValidSubnetMask(const char *mask_str)
{
T_INT32 i;
unsigned int n[5];
char buf[64];

	
	if(sscanf(mask_str,"%u.%u.%u.%u", &n[1], &n[2], &n[3], &n[4]) != 4) return 0;
	sprintf(buf,"%u.%u.%u.%u",n[1],n[2],n[3],n[4]);
	if(strcmp(buf,mask_str)) return 0;
	
	for (i=1; i<5; i++){
		//Check n[1]
		if ( !(n[1]==224 || n[1]==240 || n[1]==248 || n[1]==252 || n[1]==254 || n[1]==255) )
			return 0;
		//Check n[i] and n[i-1] is not 255 
		if ( (i>1) && (n[i-1]!=255) && (n[i]!=0) )
			return 0;
		//Check n[i] and n[i-1] is 255
		if ( (i>1) && (n[i-1]==255) ){
			if (!(n[i]==0 || n[i]==128 || n[i]==192 || n[i]==224 || n[i]==240 || n[i]==248 || n[i]==252 || n[i]==254 || n[i]==255) )
				return 0;
		}
	}
	return 1;
}

/*****************************************************************
* NAME: errorcheckSameDomain
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_INT32 errorcheckSameDomain(const char *ip_str, const char *gateway_str, const char *mask_str)
{
T_INT32 i;
unsigned int ip[4];
unsigned int gateway[4];
unsigned int mask[4];
	
	if(sscanf(ip_str,"%u.%u.%u.%u", &ip[0], &ip[1], &ip[2], &ip[3]) != 4) return 0;
	if(sscanf(gateway_str,"%u.%u.%u.%u", &gateway[0], &gateway[1], &gateway[2], &gateway[3]) != 4) return 0;
	if(sscanf(mask_str,"%u.%u.%u.%u", &mask[0], &mask[1], &mask[2], &mask[3]) != 4) return 0;
	
	
	for (i=0; i<4; i++){
		if ( (ip[i] & mask[i]) != (gateway[i] & mask[i]) )
			return 0;
	}
	return 1;
}


/*****************************************************************
* NAME: errorcheckIntRange
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_INT32 errorcheckIntRange(T_INT32 min, T_INT32 max, T_INT32 index){

	if (index>=min && index <=max)
		return 1;
	else
		return 0;
}

/*****************************************************************
* NAME: errorcheckStrLength
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_INT32 errorcheckStrLength(T_INT32 length, T_CHAR* input){

	if (strlen(input) <= length)
		return 1;
	else
		return 0;
}


/*****************************************************************
* NAME: checkwdsEnable
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_INT32 checkwdsEnable(T_INT32 count, T_INT32 index, T_CHAR * wlanwdspeer){
T_INT32 i;

	for (i=1; i<=count; i++){
		if (i == index)
			continue;
		if ( wlanwdspeer[(i*13)-1]=='v' )
			break;
	}
	if (i<=count)
		return 1;
	else
		return 0;
}

/*****************************************************************
* NAME: rebuildwdspeer
* ---------------------------------------------------------------
* FUNCTION:
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_CHAR * rebuildwdspeer(T_INT32 count, T_INT32 index, T_CHAR * wlanwdspeer){
T_INT32 i;
T_CHAR buf[16];
T_CHAR source[64];
T_CHAR result[64];

	strcpy(result, "");
	strcpy(source, wlanwdspeer);

	for (i=1; i<=count; i++){
		if (i == index)
			continue;
		strncpy(buf, source+(i-1)*13, 13);
		buf[13]='\0';	
		strcat(result , buf);
	}
	return result;
}

/*****************************************************************
* NAME: get_wifi_iface
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
//opmode should be OPM_AP(1)|OPM_CB(2)|OPM_WDSAP(4)|OPM_WDSB(8)|OPM_WDSSTA|OPM_AR|OPM_CBRT|OPM_RP(128)
T_INT32 get_wifi_iface(T_INT32 opmode) {
T_INT32 index=0;

	//single-radio
	if (model_radio==2 || model_radio==5)
		return 0;
	
	//change opmode to index. ex: AP(1), index(0); WDSAP(4), index(2); RP(128), index(7)
	while( (opmode >> 1)!=0 ){
		index++;
		opmode=opmode>>1;
	}
					//AP, CB, WDSAP, WDSB, WDSSTA, AR, CR, RP, NAWDS, MESH
	//dual-radio wifi_iface_shift[10]={0, 19, 0, 17, 19, 0, 20, 21, 16, 24};	 
	if  (model_radio==7 && (strcmp(current_radio_flag, "2.4G")==0) )
		return wifi_iface_shift[index];
	
	if  (model_radio==7 && (strcmp(current_radio_flag, "5G")==0) )
		return wifi_iface_shift[index]+radio_shift;

}


/*****************************************************************
* NAME: convertOpmodeIndex
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 convertOpmodeIndex(T_INT32 index) {
T_INT32 i;
T_INT32 j=0;
T_INT32 Modelopmode;
	
	//get Modelopmode
	Modelopmode=getModelopmode();
	for (i=1; i<=SYS_OPM_COUNT; i++){


//Modify for CAP4200 on 2013-05-23 to release the constraint of both 2.4G and 5G operation modes
if ( (strcmp(model_name, "cap4200ag")!=0) ){


//Philips modifies on 2012-12-10 for setting the correct opmode
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

	
		if ( (Modelopmode & (1<<(i-1)))!=0 )
			j++;

		if (j==index)
			break;
	}
	//the index of 8 modes
	return i;
}

/*****************************************************************
* NAME: get_nawds_index
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_INT32 get_nawds_index(T_INT32 ssidCount, T_INT32 operationMode) {
T_INT32 nawds_index;
	
	//single radio
	if (model_radio==2 || model_radio==5){
		if (ssidCount==4)
			nawds_index=4;
		if (ssidCount==8)
			nawds_index=16;
	}
	//dual radio
	if (model_radio==7){
		if  ( strcmp(current_radio_flag, "2.4G")==0 ){
			if (operationMode==OPM_WDSAP)
				nawds_index=wifi_iface_shift[8];
			if (operationMode==OPM_WDSB)
				nawds_index=wifi_iface_shift[3];
		}
		if  ( strcmp(current_radio_flag, "5G")==0 ){
			if (operationMode==OPM_WDSAP)
				nawds_index=wifi_iface_shift[8]+radio_shift;
			if (operationMode==OPM_WDSB)
				nawds_index=wifi_iface_shift[3]+radio_shift;
		}
	}
	
	return nawds_index;
}

/*****************************************************************
* NAME: getSSIDnumber
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 getSSIDnumber(T_VOID) {

T_CHAR buf[128];
FILE *pp;

	if( (pp = popen("cat /tmp/ssid", "r")) == NULL )
 	{
 		printf("popen() error!\n");
 		exit(1);
 	}

	fgets(buf, sizeof buf, pp);
	pclose(pp);
	buf[strlen(buf)-1]='\0';

	return atoi(buf);
}

/*****************************************************************
* NAME: convertSSIDProfileIndex
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
/*
T_INT32 convertSSIDProfileIndex(T_INT32 SSIDProfileIndex) {

T_CHAR buf[128];
FILE *pp;
T_INT32 opmode;
	
	opmode=current_opmode;
	
	if ( opmode==OPM_WDSAP || opmode==OPM_AP || opmode==OPM_AR){

		return SSIDProfileIndex;
	}
	else if ( opmode==OPM_WDSSTA || opmode==OPM_CB || opmode==OPM_CBRT || opmode==OPM_RP ){
	
		return 1;
	}
	
}
*/

/*****************************************************************
* NAME: getWirelessmode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_CHAR* getWirelessmode(T_CHAR* wifiinterface) {
T_CHAR uci_get_buf[128];

	strcpy(uci_get_buf, cli_get_uci(wifiinterface));
	return uci_get_buf;
}

/*****************************************************************
* NAME: getModelwdslinkCount
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 getModelwdslinkCount(T_INT32 operationeMode) {
T_INT32 i;

	for (i=0; i<HostnameData.count; i++){
		if ( strcmp(model_name, HostnameData.CliHostnameTable[i].hostName)==0 )
			break;			
	}
	if (operationeMode==OPM_WDSB)
		return HostnameData.CliHostnameTable[i].wdsCount_brwds;
	if (operationeMode==OPM_WDSAP)
		return HostnameData.CliHostnameTable[i].wdsCount_apwds;
}

/*****************************************************************
* NAME: getModelssidCount
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 getModelssidCount(T_INT32 operationeMode) {
T_INT32 i;

	for (i=0; i<HostnameData.count; i++){
		if ( strcmp(model_name, HostnameData.CliHostnameTable[i].hostName)==0 )
			break;			
	}	
	
	if (operationeMode==OPM_AP)
		return HostnameData.CliHostnameTable[i].ssidCount_ap;
	else
//	if (operationeMode==OPM_WDSAP)
		return HostnameData.CliHostnameTable[i].ssidCount_apwds;
//	return 0;
}

/*****************************************************************
* NAME: getModelopmodeCount
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 getModelopmodeCount(T_VOID) {
T_INT32 i;
	
	if (model_radio==2 || model_radio==5){
		for (i=0; i<HostnameData.count; i++){
			if ( strcmp(model_name, HostnameData.CliHostnameTable[i].hostName)==0 )
				break;			
		}
		return HostnameData.CliHostnameTable[i].opmodeCount;
	}
	
	if (model_radio==7){
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	}
	

}


/*****************************************************************
* NAME: getModelopmode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 getModelopmode(T_VOID) {
T_INT32 i;

	for (i=0; i<HostnameData.count; i++){
		if ( strcmp(model_name, HostnameData.CliHostnameTable[i].hostName)==0 )
			break;			
	}
	return HostnameData.CliHostnameTable[i].opmode;
}


/*****************************************************************
* NAME: getRadiomode
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
/*
T_INT32 getRadiomode(T_VOID) {
T_INT32 i;

	for (i=0; i<HostnameData.count; i++){
		if ( strcmp(model_name, HostnameData.CliHostnameTable[i].hostName)==0 )
			break;			
	}
	return HostnameData.CliHostnameTable[i].hostRadio;
}
*/
/*****************************************************************
* NAME: getHostantenna
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 getHostantenna(T_VOID) {
T_INT32 i;

	for (i=0; i<HostnameData.count; i++){
		if ( strcmp(model_name, HostnameData.CliHostnameTable[i].hostName)==0 )
			break;			
	}
	return HostnameData.CliHostnameTable[i].hostAntenna;
}

/*****************************************************************
* NAME: getHosttxpower
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 getHosttxpower(T_VOID) {
//wifi0 for 2.4G, 5G of Single Radio and 2.4G of Dual Radio
T_CHAR func_buf[128]="wireless.wifi0.obeyregpower";
//wifi0 for 2.4G, 5G of Single Radio, 2.4G of ENH700 and 5G of EAP600
T_CHAR buf[128]="cat /proc/sys/dev/wifi0/maxallowpower";
T_CHAR uci_get_buf[128];
T_INT32 i;
FILE *pp;
	//Modify by Philips on 2012-07-10
	//wifi1 for 5G of Dual Radio
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.wifi1.obeyregpower");

	strcpy(uci_get_buf, cli_get_uci(func_buf));
	
	//Obey Regulatory Power hasn't been selected
	if (atoi(uci_get_buf)==0){
		//Find the maxpower from HostnameData
		for (i=0; i<HostnameData.count; i++){
			if ( strcmp(model_name, HostnameData.CliHostnameTable[i].hostName)==0 )
				break;			
		}

		//Modify by Philips on 2012-07-10
		//maxpower is used in 2.4G for both single-radio and dual-radio
		//maxpower_5 is used in 5G for both single-radio and dual-radio
		if ( ( model_radio==5 ) || ((model_radio==7) && (strcmp(current_radio_flag, "5G")==0)) )
			return HostnameData.CliHostnameTable[i].maxpower_5;
		else
			return HostnameData.CliHostnameTable[i].maxpower;

	}
	
	//Obey Regulatory Power has been selected	
	else{
		//Modify by Philips on 2012-07-10
		//wifi1 for 2.4G of Dual Radio - EAP600
//		if ( strcmp(model_name, "eap600")==0 && strcmp(current_radio_flag, "2.4G")==0 )

		//Modify by Philips on 2012-11-07 to add three new models -- "eap600true", "ap200" and "cap4200ag"
		if ( (strcmp(model_name, "eap600")==0 || strcmp(model_name, "all02860nd")==0 || strcmp(model_name, "eap600true")==0 || strcmp(model_name, "ap200")==0 ||strcmp(model_name, "cap4200ag")==0) && strcmp(current_radio_flag, "2.4G")==0 )
			strcpy(buf, "cat /proc/sys/dev/wifi1/maxallowpower");
	
		if( (pp = popen(buf, "r")) == NULL )
		{
			printf("popen() error!\n");
			exit(1);
		}
		fgets(uci_get_buf, sizeof uci_get_buf, pp);
		pclose(pp);
		uci_get_buf[strlen(uci_get_buf)-1]='\0';
		return atoi(uci_get_buf);
	}
}

/*****************************************************************
* NAME: errorcheckSameVID
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_INT32 errorcheckSameVID(T_CHAR* VID, T_INT32 ssidnumber){
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_INT32 i;
T_INT32 ssidCount;
T_INT32 operationeMode=current_opmode;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
	ssidCount=getModelssidCount(operationeMode);	

if ( model_radio==2 || model_radio==5 ){
	for (i=1; i<=ssidCount; i++){
	
		if (i==ssidnumber)
			continue;
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANID", i-1);
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if ( strcmp(VID, uci_get_buf)==0 )
			break;
	}
	
	if ( i>ssidCount )/*All 1~8 VID are different*/
		return 1;
	else 
		return 0;
}

if ( model_radio==7 ){
	if (strcmp(current_radio_flag, "5G")==0)
		ssidnumber+=radio_shift;

	for (i=1; i<=ssidCount; i++){
	
		if (i==ssidnumber)
			continue;
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANID", i-1);
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if ( strcmp(VID, uci_get_buf)==0 )
			break;
	}
	if ( i<=ssidCount )/*All 1~8 VID are not different*/
		return 0;
	
	for (i=radio_shift+1; i<=radio_shift+ssidCount; i++){
	
		if (i==ssidnumber)
			continue;
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANID", i-1);
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if ( strcmp(VID, uci_get_buf)==0 )
			break;
	}
	if ( i>radio_shift+ssidCount )/*All 27~34 VID are different*/
		return 1;
	else 
		return 0;
	
}


}

/*****************************************************************
* NAME: vlanProccess
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID vlanProccess(T_INT32 ssidnumber)
{
//printf("Called %s\n",__func__);
//printf("ssidnumber=%d\n", ssidnumber);

T_CHAR func_buf[128];
T_CHAR isolation[128];
T_CHAR wlanenable[128];
T_CHAR MVID[128];
T_CHAR VID[128];
//T_CHAR br0_enable[32];
//FILE* fp;

if (model_radio==7){

//printf("Dual-radio vlanProccess\n");
}
	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", ssidnumber-1);
	strcpy(isolation, cli_get_uci(func_buf));

	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANEnable", ssidnumber-1);
	strcpy(wlanenable, cli_get_uci(func_buf));
	
	sprintf(func_buf, "network.sys.ManagementVLANID");
	strcpy(MVID, cli_get_uci(func_buf));
	
	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANID", ssidnumber-1);
	strcpy(VID, cli_get_uci(func_buf));

	//strcpy(br0_enable, cli_get_uci("network.0"));	
//printf("2. cli_get_uci_network.0=%s\n", cli_get_uci("network.0"));	


	if ( atoi(isolation)==1 && atoi(wlanenable)==1 )
		setVLANbridge(ssidnumber);
	else
		revertVLANbridge(ssidnumber);

	if ( atoi(MVID) != 4096){
		setMVLANbridge();
		
		if ( atoi(MVID)==atoi(VID) )
			revertVLANbridge(ssidnumber);
			
		setLANtoZero(ssidnumber, MVID, VID);

	}
	else{
		revertMVLANbridge();
		
		setZerotoLAN(ssidnumber);
		
	}



}

/*****************************************************************
* NAME: setVLANbridge
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID setVLANbridge(T_INT32 ssidnumber)
{
//printf("Called %s\n",__func__);
//printf("ssidnumber=%d\n", ssidnumber);
T_CHAR func_buf[128];
T_CHAR data_buf[128];
//T_CHAR uci_set_buf[128];
T_CHAR VID[128];
T_CHAR br_enable[32];
FILE* fp;

	if (model_radio==7){
		//printf("Dual-radio setVLANbridge\n");	
		
		//check one of br9~br16 exist
		if (ssidnumber>8)
			sprintf(func_buf, " cat /etc/config/network |grep \"\'interface\' \'%d\'\" > /tmp/br ", ssidnumber-18);
		//check one of br1~br8 exist
		else
			sprintf(func_buf, " cat /etc/config/network |grep \"\'interface\' \'%d\'\" > /tmp/br ", ssidnumber);	
		system(func_buf);
		
		if((fp = fopen("/tmp/br", "r"))==NULL){
			printf("Can't open file\n");
			exit;
		}

		fgets(br_enable,sizeof(br_enable),fp);
		fclose(fp);
		system("rm /tmp/br");
		
		if (strstr(br_enable, "interface")==NULL){
			//create one of br9~br16
			if (ssidnumber>8)
				sprintf(func_buf, "br=$(uci add network interface); uci rename network.$br=%d", ssidnumber-18);
			//create one of br1~br8
			else
				sprintf(func_buf, "br=$(uci add network interface); uci rename network.$br=%d", ssidnumber);
			
			system(func_buf);
		}
	}
	
	
	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANID", ssidnumber-1);
	strcpy(VID, cli_get_uci(func_buf));

	//set ath in br-ssidnumber
	sprintf(func_buf, "wireless.@wifi-iface[%d].network", ssidnumber-1);
	
	if (ssidnumber>8)
		sprintf(data_buf, "%d", ssidnumber-18);
	else
		sprintf(data_buf, "%d", ssidnumber);
		
	cli_set_uci(func_buf, data_buf);

	if (ssidnumber>8)
		ssidnumber-=18;

	sprintf(func_buf, "network.%d.proto", ssidnumber);
	cli_set_uci(func_buf, "none");

	sprintf(func_buf, "network.%d.type", ssidnumber);
	cli_set_uci(func_buf, "bridge");
	
	sprintf(func_buf, "network.%d.auto", ssidnumber);
	cli_set_uci(func_buf, "1");
	
	//set eth0.VID in br-ssidnumber
	sprintf(func_buf, "network.%d.ifname", ssidnumber);
	sprintf(data_buf, "eth0.%d", atoi(VID));
	//sprintf(data_buf, "eth0.%d eth1.%d", atoi(VID), atoi(VID));
	cli_set_uci(func_buf, data_buf);




}

/*****************************************************************
* NAME: revertVLANbridge
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID revertVLANbridge(T_INT32 ssidnumber)
{
//printf("Called %s\n",__func__);
//printf("ssidnumber=%d\n", ssidnumber);
T_CHAR func_buf[128];
//T_CHAR data_buf[128];
//T_CHAR uci_set_buf[128];
T_CHAR br_enable[32];
FILE* fp;


	if (model_radio==7){
		//printf("Dual-radio setVLANbridge\n");	
		//check one of br9~br16 exist
		if (ssidnumber>8)
			sprintf(func_buf, " cat /etc/config/network |grep \"\'interface\' \'%d\'\" > /tmp/br ", ssidnumber-18);
		//check one of br1~br8 exist
		else
			sprintf(func_buf, " cat /etc/config/network |grep \"\'interface\' \'%d\'\" > /tmp/br ", ssidnumber);
		
		system(func_buf);
		
		if((fp = fopen("/tmp/br", "r"))==NULL){
			printf("Can't open file\n");
			exit;
		}

		fgets(br_enable,sizeof(br_enable),fp);
		fclose(fp);
		system("rm /tmp/br");
		
		if (strstr(br_enable, "interface")!=NULL){
			//delete one of br9~br16
			if (ssidnumber>8)
				sprintf(func_buf, "uci delete network.%d", ssidnumber-18);
			//delete one of br1~br8
			else
				sprintf(func_buf, "uci delete network.%d", ssidnumber);
				
			system(func_buf);
		}	

	}
	//set ath in br-lan
	sprintf(func_buf, "wireless.@wifi-iface[%d].network", ssidnumber-1);
	cli_set_uci(func_buf, "lan");

	if (ssidnumber>8)
		ssidnumber-=18;

	sprintf(func_buf, "network.%d.proto", ssidnumber);
	cli_set_uci(func_buf, "none");

	sprintf(func_buf, "network.%d.type", ssidnumber);
	cli_set_uci(func_buf, "bridge");
	
	sprintf(func_buf, "network.%d.auto", ssidnumber);
	cli_set_uci(func_buf, "0");
	
	sprintf(func_buf, "network.%d.ifname", ssidnumber);
	cli_set_uci(func_buf, "");

}

/*****************************************************************
* NAME: setMVLANbridge
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID setMVLANbridge(T_VOID)
{
//printf("Called %s\n",__func__);
T_CHAR func_buf[128]="network.sys.ManagementVLANID";
T_CHAR MVID[128];
T_CHAR data_buf[128];
//T_CHAR uci_set_buf[128];

	strcpy(MVID, cli_get_uci(func_buf));

	//set mvid in br-lan
	sprintf(func_buf, "network.lan.ifname");
	sprintf(data_buf, "eth0.%s", MVID);
	//sprintf(data_buf, "eth0.%s eth1.%s", MVID, MVID);
	
	cli_set_uci(func_buf, data_buf);
	
	sprintf(func_buf, "network.0.proto");
	cli_set_uci(func_buf, "none");
	
	sprintf(func_buf, "network.0.type");
	cli_set_uci(func_buf, "bridge");

	sprintf(func_buf, "network.0.auto");
	cli_set_uci(func_buf, "1");
	
	//set eth0 in br-lan
	sprintf(func_buf, "network.0.ifname");
	cli_set_uci(func_buf, "eth0");
	//cli_set_uci(func_buf, "eth0 eth1");
	
//	sprintf(func_buf, "network.sys.ManagementVLANID");
//	cli_set_uci(func_buf, MVID);



}

/*****************************************************************
* NAME: revertMVLANbridge
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID revertMVLANbridge(T_VOID)
{
//printf("Called %s\n",__func__);
T_CHAR func_buf[128];

	//set eth0 in br-lan
	sprintf(func_buf, "network.lan.ifname");
	cli_set_uci(func_buf, "eth0");
	//cli_set_uci(func_buf, "eth0 eth1");
	
	sprintf(func_buf, "network.0.proto");
	cli_set_uci(func_buf, "none");
	
	sprintf(func_buf, "network.0.type");
	cli_set_uci(func_buf, "bridge");
	
	sprintf(func_buf, "network.0.auto");
	cli_set_uci(func_buf, "0");
	
	sprintf(func_buf, "network.0.ifname");
	cli_set_uci(func_buf, "");
	
//	sprintf(func_buf, "network.sys.ManagementVLANID");
//	cli_set_uci(func_buf, "4096");
	

  
}

/*****************************************************************
* NAME: setLANtoZero
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID setLANtoZero(T_INT32 i, T_CHAR* MVID, T_CHAR* VID)
{
//printf("Called %s\n",__func__);
T_CHAR func_buf[128];
T_CHAR wlanEnable[128];
T_CHAR network[128];


		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", i-1);
		strcpy(wlanEnable, cli_get_uci(func_buf));
		
		sprintf(func_buf, "wireless.@wifi-iface[%d].network", i-1);
		strcpy(network, cli_get_uci(func_buf));

		//set ath from br-lan to br-0
		if (strcmp(MVID, VID)!=0 && atoi(wlanEnable)==1 && strcmp(network, "lan")==0 ){
			sprintf(func_buf, "wireless.@wifi-iface[%d].network", i-1);
			cli_set_uci(func_buf, "0");
		}



}

/*****************************************************************
* NAME: setZerotoLAN
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID setZerotoLAN(T_INT32 i)
{
//printf("Called %s\n",__func__);
T_CHAR func_buf[128];
T_CHAR wlanEnable[128];
T_CHAR network[128];


		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", i-1);
		strcpy(wlanEnable, cli_get_uci(func_buf));
		
		sprintf(func_buf, "wireless.@wifi-iface[%d].network", i-1);
		strcpy(network, cli_get_uci(func_buf));
		
		//set ath from br-0 to br-lan
		if ( atoi(wlanEnable)==1 && strcmp(network, "0")==0 ){
			sprintf(func_buf, "wireless.@wifi-iface[%d].network", i-1);
			cli_set_uci(func_buf, "lan");
		}
	
}

/*****************************************************************
* NAME: checkIsolationDisable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
T_VOID checkIsolationDisable(T_INT32 wifi_index)
{
//printf("Called %s\n",__func__);
T_CHAR func_buf[128];
T_CHAR func_buf1[128]="wireless.wifi0.WLANSSIDIsolation";
T_CHAR func_buf2[128]="network.sys.ManagementVLANID";
T_CHAR uci_get_buf[128];	
T_INT32 i;
T_INT32 ssidCount;
T_INT32 operationeMode=current_opmode;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
	ssidCount=getModelssidCount(operationeMode);
	
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf, "wireless.wifi1.WLANSSIDIsolation");

	for (i=1; i<=ssidCount; i++){
		sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANEnable", i-1);
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		if ( atoi(uci_get_buf)==1 )
			break;
	}
	
	//if ( (i>ssidCount) ){ /*All isolations are disable*/
	if ( (i>ssidCount) && (model_radio==2 || model_radio==5) ){ /*All isolations are disable*/
		cli_set_uci(func_buf1, "0");
		cli_set_uci(func_buf2, "4096");
	}

	if ( (i>ssidCount) && (model_radio==7) ){
		for (i=wifi_index+1; i<=wifi_index+ssidCount; i++){
//2012-08-15 ssidCount should be change to ssidCount_apwds
//for (i=wifi_index+1; i<=wifi_index+ssidCount; i++){
			sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANEnable", i-1);
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			if ( atoi(uci_get_buf)==1 )
				break;
		}
		if ( (i>ssidCount) ) /*All isolations are disable*/
			cli_set_uci(func_buf2, "4096");

	}
}

/*****************************************************************
* NAME: cmducihandle
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
//CliStatus cmducihandle(T_VOID* priv, CliData* cliData)
T_VOID cmducihandle(T_VOID)
{
T_INT32 ret;
T_CHAR buf[1024];

	while(1){
		ret = cmdedit_read_input("uci>", buf);
		if( (buf[0] == 'e' && buf[1] == 'x' && buf[2] == 'i' && buf[3] == 't' && buf[4] == 0x0a) ){

			return ;
		}
		else
			system(buf);		
	}

}

/*****************************************************************
* NAME: cmdsave
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsave(T_VOID* priv, CliData* cliData)
{
	if(cliData->argc==0){
		
		system("uci commit");
		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}


/*****************************************************************
* NAME: cmdreboot
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdreboot(T_VOID* priv, CliData* cliData)
{
	if(cliData->argc==0){
		
		system("reboot");
		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdrevert
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdrevert(T_VOID* priv, CliData* cliData)
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
* NAME: cmdexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;

	return CLI_NOTHING;
}

/*****************************************************************
* NAME: cmdmvlanswitch
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   ### leaf node and then non-leaf node
****************************************************************/
CliStatus cmdmvlanswitch(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
//T_CHAR uci_set_buf[128];
//T_CHAR c1[255];
T_INT32 i;
T_INT32 ssidCount;
T_INT32 operationeMode=current_opmode;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
	ssidCount=getModelssidCount(operationeMode);
	
	if(cliData->argc==0){
		
		for (i=1; i<=ssidCount; i++){
			sprintf(func_buf, "wireless.@wifi-iface[%d].ssid", i-1);
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			tprintf("%d - SSID%d: %s\n", i, i, uci_get_buf);
		
		}

		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0)
		return getNextTable(cli_table_vlanp, cliData);
}



/*****************************************************************
* NAME: cmdmvlanswitchexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmvlanswitchexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	//vlanpsetbridge=-1;

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}


/*****************************************************************
* NAME: cmdtimes
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdtimes(T_VOID* priv, CliData* cliData)
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
* NAME: cmdtip
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdtip(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){

		tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
    		cliData->tokenLen--;
    		
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid segmentation fault when the length of input > 128
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(target_ip, cliData->tokens[cliData->tokenLen-1].token);
		cliData->tokenLen-=2;
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdpsize
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpsize(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){

		tprintf("Current setting: %d bytes (64~20480)\n", packet_size);
    		cliData->tokenLen--;
    		
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
				
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 64, 20480, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
  			return CLI_PARAMS_ERR;
		}
	
		packet_size=atoi(cliData->tokens[cliData->tokenLen-1].token);
		cliData->tokenLen-=2;
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdnumber
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdnumber(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){

		tprintf("Current setting: %d (1~9999)\n", number_of_ping);
    		cliData->tokenLen--;
    		
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
				
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 9999, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
  			return CLI_PARAMS_ERR;
		}
	
		number_of_ping=atoi(cliData->tokens[cliData->tokenLen-1].token);
		cliData->tokenLen-=2;
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdpingaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpingaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR c1[255];

	if(cliData->argc==0){
		
		if ( strcmp(target_ip, "")==0 ){
			tprintf("Target IP address can't be empty. Please enter again\n");
			cliData->tokenLen-=1;
	  		return CLI_PARAMS_ERR;
		}
		
		sprintf(c1, "ping %s -s %d -c %d", target_ip, packet_size, number_of_ping);
		system(c1);		
		
		//initail parameter
		strcpy(target_ip, "");
		packet_size=64;
		number_of_ping=4;
		
		cliData->tokenLen--;
		return CLI_NOTHING;
	
	}
	else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdpingexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpingexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	//initail parameter
	strcpy(target_ip, "");
	packet_size=64;
	number_of_ping=4;

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}




/*****************************************************************
* NAME: cmdmonth
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmonth(T_VOID* priv, CliData* cliData)
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
* NAME: cmdday
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdday(T_VOID* priv, CliData* cliData)
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
* NAME: cmdhour
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdhour(T_VOID* priv, CliData* cliData)
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
* NAME: cmdminute
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdminute(T_VOID* priv, CliData* cliData)
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
* NAME: cmddisable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddisable(T_VOID* priv, CliData* cliData)
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
* NAME: cmdautht
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdautht(T_VOID* priv, CliData* cliData)
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
* NAME: cmdaggr
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdaggr(T_VOID* priv, CliData* cliData)
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
* NAME: cmdtraffic
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdtraffic(T_VOID* priv, CliData* cliData)
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
* NAME: cmdmac1
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmac1(T_VOID* priv, CliData* cliData)
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
* NAME: cmdmac2
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmac2(T_VOID* priv, CliData* cliData)
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
* NAME: cmdmac3
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmac3(T_VOID* priv, CliData* cliData)
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
* NAME: cmdmac4
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmac4(T_VOID* priv, CliData* cliData)
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
* NAME: cmdssid1iso
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdssid1iso(T_VOID* priv, CliData* cliData)
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
* NAME: cmdssid2iso
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdssid2iso(T_VOID* priv, CliData* cliData)
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
* NAME: cmdssid3iso
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdssid3iso(T_VOID* priv, CliData* cliData)
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
* NAME: cmdssid4iso
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdssid4iso(T_VOID* priv, CliData* cliData)
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
* NAME: cmdHelp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-26
* Modify:   
****************************************************************/
CliStatus cmdHelp(T_VOID* priv, CliData* cliData)
{
//printf("Called %s\n",__func__);
	CliEntry* pTable = (CliEntry*) priv;
	T_INT32 i=0;
	T_INT32 j=0;
	T_INT32 help_exist=0;
	
	//Check whether there is "help" in the command  EX:ecb350>wless2 network help ttt
	for (j=0; j<cliData->tokenLen; j++)
		if ( strcmp(cliData->tokens[j].token, "help")==0 )
			help_exist=1;
    
//printf("cliData->argc=%d\n", cliData->argc);
//printf("cliData->tokenLen=%d\n", cliData->tokenLen);

	//There should be no any argument behind "help" command  EX:ecb350>wless2 network help ttt
	if (cliData->argc>0 && help_exist){
		printf("There should be no any argument behind \"help\" command\n");
		return CLI_NO_MATCH;	
	}

//Block command "help" with argument after setbridge when using relative path. EX:ecb350/sys/ip/dhcpact>help ttt
//if ( cliData->argc>0 && 
//	(
//	(strcmp(cliData->tokens[2].token, "ssidp")==0 && strcmp(cliData->tokens[3].token, "help")==0) ||
//	(strcmp(cliData->tokens[3].token, "apsecu")==0 && strcmp(cliData->tokens[4].token, "help")==0) ||
//	(strcmp(cliData->tokens[2].token, "auto")==0 && strcmp(cliData->tokens[3].token, "help")==0) ||
//	(strcmp(cliData->tokens[2].token, "dhcpset")==0 && strcmp(cliData->tokens[3].token, "help")==0) ||
//	(strcmp(cliData->tokens[2].token, "conntype")==0 && strcmp(cliData->tokens[3].token, "help")==0) ||
//	(strcmp(cliData->tokens[2].token, "secu")==0 && strcmp(cliData->tokens[3].token, "help")==0) ||
//	(strcmp(cliData->tokens[2].token, "wdssecu")==0 && strcmp(cliData->tokens[3].token, "help")==0) ||
//	(strcmp(cliData->tokens[2].token, "dhcpact")==0 && strcmp(cliData->tokens[3].token, "help")==0) ||
//	(strcmp(cliData->tokens[2].token, "vlanp")==0 && strcmp(cliData->tokens[3].token, "help")==0)
//	)
//)
//	return CLI_NO_MATCH;
	
/*
if ( cliData->argc!=0 && strcmp(cliData->tokens[2].token, "ssidp")!=0 && strcmp(cliData->tokens[2].token, "auto")!=0 && strcmp(cliData->tokens[2].token, "dhcpset")!=0 && strcmp(cliData->tokens[2].token, "conntype")!=0 && strcmp(cliData->tokens[3].token, "apsecu")!=0 && strcmp(cliData->tokens[2].token, "secu")!=0 && strcmp(cliData->tokens[2].token, "wdssecu")!=0 && strcmp(cliData->tokens[2].token, "dhcpact")!=0 && strcmp(cliData->tokens[2].token, "vlanp")!=0 )
	return CLI_NO_MATCH;
*/
	//cliData->tokenLen--;

	tprintf("---========= Commands Help =========---\n");

	while(pTable[i].opMode!=CMD_END_TAG)
	{

		if(pTable[i].authority <= g_auth) // Check authority for Auth control
		{
			if(cliData != NULL)
			{
#if HAS_VLAN_SUPPORT
				else if(strcmp(pTable[i].cmdName, "vlan")==0)
				{
					if(!(g_opmode&OPM_AP))
					{
						i++;
						continue;
					}
				}
#endif
			}
//printf("---(pTable[i].cmdName=%s)---\n", pTable[i].cmdName);
//tprintf("---if (pTable[i].opMode=%d & cliData->mode=%d)---\n", pTable[i].opMode, cliData->mode);

			//vlan2 and client2 can not be display when current opmode is current_opmode_5
			if ( model_radio==7 && ( strcmp(pTable[i].cmdName, "vlan2")==0 || strcmp(pTable[i].cmdName, "ratec2")==0 || strcmp(pTable[i].cmdName, "climit2")==0 || strcmp(pTable[i].cmdName, "client2")==0 || strcmp(pTable[i].cmdName, "wdslist2")==0 || strcmp(pTable[i].cmdName, "radio2")==0) )
				cliData->mode= current_opmode_2;

			//vlan5 and client5 can not be display when current opmode is current_opmode_2 
			if ( model_radio==7 && ( strcmp(pTable[i].cmdName, "vlan5")==0 || strcmp(pTable[i].cmdName, "ratec5")==0 || strcmp(pTable[i].cmdName, "climit5")==0 || strcmp(pTable[i].cmdName, "client5")==0 || strcmp(pTable[i].cmdName, "wdslist5")==0 || strcmp(pTable[i].cmdName, "radio5")==0 ) )
				cliData->mode= current_opmode_5;

			//mvlan can not be display when current_opmode_5 is not AP or WDSAP
			if ( model_radio==7 && strcmp(pTable[i].cmdName, "mvlan")==0 && ( current_opmode_2==1 || current_opmode_2==4 ) )
				cliData->mode = current_opmode_2;

			//mvlan can not be display when current_opmode_2 is not AP or WDSAP
			if (  model_radio==7 && strcmp(pTable[i].cmdName, "mvlan")==0 && ( current_opmode_5==1 || current_opmode_5==4 ) )
				cliData->mode = current_opmode_5;

			//Modify on 2012-11-28 by Philips for TC which ratio2 can not be display when current_opmode_2 is AP, WDSAP and WDSB
			if (  model_radio==7 && strcmp(pTable[i].cmdName, "ratio2")==0 )
				cliData->mode = current_opmode_2;
			
			//Modify on 2012-11-28 by Philips for TC which ratio5 can not be display when current_opmode_5 is not AP, WDSAP and WDSB
			if (  model_radio==7 && strcmp(pTable[i].cmdName, "ratio5")==0 )
				cliData->mode = current_opmode_5;			

			//Modify on 2013-08-07 by Philips to support roaming only for the first SSID which is requested by Jacy
			if (  model_radio==7 && SSIDProfileIndex!=1 && strcmp(pTable[i].cmdName, "roaming")==0 ){
				i++;
				continue;
			}
				
//printf("---if (cliData->mode=%d)---\n", cliData->mode);	
//printf("---if (pTable[i].modelID=%d & model_ID=%d)---\n", pTable[i].modelID , model_ID);		

			if ( (pTable[i].opMode & cliData->mode) && (pTable[i].modelID & model_ID) ){

//printf Commands Help options
//tprintf("pTable[%d].cmdName=%s---\n", i, pTable[i].cmdName);
//tprintf("---if (pTable[i].opMode & cliData->mode)---\n");
			
				//Modify by Philips and Yenger on 20120904 to let band steer only work under AP/AP or APWDS/APWDS
				if ( strcmp(pTable[i].cmdName, "bsteer")==0 && current_opmode_2!=current_opmode_5 ){
					i++;
					continue;
				}
			
				//Modify for AP100 on 2012-11-09
				if ( strcmp(model_name, "ap100")==0  ){
					//Disable the command belong to MODEL_5G when current_radio_flag is 2.4G
					if ((strcmp(current_radio_flag,"2.4G")==0)&&((pTable[i].modelID==MODEL_5G)||(strcmp(pTable[i].cmdName,"opmode5")==0))){
						i++;
						continue;
					}
					//Disable the command belong to MODEL_2G when current_radio_flag is 5G			
					if ((strcmp(current_radio_flag,"5G")==0)&&((pTable[i].modelID==MODEL_2G)||(strcmp(pTable[i].cmdName,"opmode2")==0))){
						i++;
						continue;
					}	
				}
				//Modify for function alignment of Client Control for EAP600 on 2012-12-04
				//Disable the command belong to MODEL_5G when current_radio_flag is 2G
				if (  model_radio==7 && (strcmp(current_radio_flag, "2.4G")==0) && strcmp(pTable[i].cmdName, "climit5")==0 ){
					i++;
					continue;
				}
				if (  model_radio==2 && strcmp(pTable[i].cmdName, "climit5")==0 ){
					i++;
					continue;
				}				
				//Modify for function alignment of Client Control for EAP600 on 2012-12-04
				//Disable the command belong to MODEL_2G when current_radio_flag is 5G
				if (  model_radio==7 && strcmp(current_radio_flag, "5G")==0 && strcmp(pTable[i].cmdName, "climit2")==0 ){
					i++;
					continue;
				}
				if (  model_radio==5 && strcmp(pTable[i].cmdName, "climit2")==0 ){
					i++;
					continue;
				}
				
				//Modify for EAP1750 on 2013-10-23
				//wless5 advset aggr can not be executed for EAP1750H
				if ( (strcmp(model_name, "eap1750h")==0) && (strcmp(cliData->tokens[0].token, "wless5")==0) && (strcmp(pTable[i].cmdName, "aggr")==0) ){
					i++;
					continue;
				}
							
				//Display menu
				tprintf(CLI_CMD_NAME, pTable[i].cmdName, pTable[i].description);
				
				// pritf Usage
				if ( strlen(pTable[i].usage) )
					tprintf(CLI_CMD_USAGE, pTable[i].usage);
			}
			// pritf Options
			if(pTable[i].handler == setApCfgValue)
			{

				showOption(pTable[i].priv);

			}
		}
        	i++;
	}
	return CLI_NOTHING;
}
/*****************************************************************
* NAME: cmdTree
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   Norkay 2009-07-21
****************************************************************/
CliStatus cmdTree(T_VOID* priv, CliData* cliData)
{
    CliEntry* pTable = (CliEntry*) priv;
    T_INT32 i=0, j;

if(cliData->argc > 0)
   return CLI_NO_MATCH;


	//printf("cliData->curLv %d\n", cliData->curLv);
    while(pTable[i].opMode!=CMD_END_TAG)
    {
        if(pTable[i].authority <= g_auth) // Check authority for Auth control
        {
			if(cliData != NULL)
			{
				if( ((pTable[i].opMode & cliData->mode) == 0) || !(pTable[i].modelID & model_ID) )
				{
				//printf("pTable[i].modelID=%d\n", pTable[i].model_ID);
					i++;
					continue;
				}
			}
			switch(cliData->curLv%100)
			{
			case 0:
				tprintf("|-%-8s", pTable[i].cmdName);
				break;
			case 1:
				printf("|          %s%-8s", pTable[i+1].opMode != CMD_END_TAG ? "|-" : "\\-", pTable[i].cmdName);
				break;
			case 2:
				printf("|          %s          %s%-8s", 
					   ((cliData->curLv/100) & 2) ? " " : "|", 
					   pTable[i+1].opMode != CMD_END_TAG ? "|-" : "\\-",
					   pTable[i].cmdName);
				break;
			case 3:
				printf("|          %s          %s          %s%-8s", 
					   ((cliData->curLv/100) & 2) ? " " : "|",  
					   ((cliData->curLv/100) & 4) ? " " : "|", 
					   pTable[i+1].opMode != CMD_END_TAG ? "|-" : "\\-",
					   pTable[i].cmdName);
				break;
			case 4:
				printf("|          %s          %s          %s          %s%-8s", 
					   ((cliData->curLv/100) & 2) ? " " : "|",  
					   ((cliData->curLv/100) & 4) ? " " : "|", 
					   ((cliData->curLv/100) & 8) ? " " : "|", 
					   pTable[i+1].opMode != CMD_END_TAG ? "|-" : "\\-",
					   pTable[i].cmdName);
				break;
			case 5:
				printf("|          %s          %s          %s          %s          %s%-8s", 
					   ((cliData->curLv/100) & 2) ? " " : "|",  
					   ((cliData->curLv/100) & 4) ? " " : "|", 
					   ((cliData->curLv/100) & 8) ? " " : "|", 
					   ((cliData->curLv/100) & 16) ? " " : "|", 
					   pTable[i+1].opMode != CMD_END_TAG ? "|-" : "\\-",
					   pTable[i].cmdName);
				break;
			default:
				break;
			}

			if( (pTable[i].handler == getNextTable) /*|| (pTable[i].handler == cmdssidp)*/ )
			{
				tprintf("-\\");

                /* description */
				for(j = cliData->curLv%100; j < 6; ++j)
				{
					tprintf("        ");
				}
				tprintf("%s", pTable[i].description);

				tprintf("\n");
				if(pTable[i+1].opMode == CMD_END_TAG)
				{
					cliData->curLv += (1<<(cliData->curLv%100))*100;
				}

				cliData->curLv++;
/*				
if( pTable[i].handler == cmdssidp ){
				
	cmdTree(cli_table_ssidp, cliData);
				
}else{
	cmdTree(pTable[i].priv, cliData);
}				
*/
				cmdTree(pTable[i].priv, cliData);
				cliData->curLv--;
				if(pTable[i+1].opMode == CMD_END_TAG)
				{
					cliData->curLv -= (1<<(cliData->curLv%100))*100;
				}
			}
			else
			{
                /* description */
				for(j = cliData->curLv%100; j < 6; ++j)
				{
					tprintf("        ");
				}
				tprintf(" %s", pTable[i].description);

				tprintf("\n");
			}

        }
        i++;
    }
    return CLI_NOTHING;
}


void vlan_dual_radio_process(void){
//char opmode_2G[20];
//char opmode_5G[20];
int ssidCount_2G;
int ssidCount_5G;
int i;
int enable[16];
int venable[16];
int vlanid[16];
int vlan_num_dual;
int mvid;
char got_value[10];
char tmp_data[128];
char output_value[128];
char output_string[128];

T_CHAR func_buf[128];
T_INT32 wifi_index_2G = get_wifi_iface(current_opmode_2);
T_INT32 wifi_index_5G = get_wifi_iface(current_opmode_5);

	//Get wifi_index of 2G and 5G
	strcpy(current_radio_flag, "2.4G");
	wifi_index_2G = get_wifi_iface(current_opmode_2);
	strcpy(current_radio_flag, "5G");
	wifi_index_5G = get_wifi_iface(current_opmode_5);

	//Get ssidCount of 2G and 5G
	ssidCount_2G = ( current_opmode_2==OPM_AP ) ? 8 : 4;
	ssidCount_5G = ( current_opmode_5==OPM_AP ) ? 8 : 4;

system("echo wifi_num=\\\"2\\\" > /tmp/vlancfg.sh");

//----------------------------------------------------------------------------------------------------------

strcpy(output_value, "enable=\\\"");
for (i=0; i<ssidCount_2G; i++){
	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", wifi_index_2G+i);
	strcpy(got_value, cli_get_uci(func_buf));
	strcat(output_value, got_value);
	strcat(output_value, ",");
}

for (i=0; i<ssidCount_5G; i++){
	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", wifi_index_5G+i);
	strcpy(got_value, cli_get_uci(func_buf));
	strcat(output_value, got_value);
	strcat(output_value, ",");
}                                                                         

output_value[strlen(output_value)-1]='\0';

sprintf(output_string, "echo %s\\\" >> /tmp/vlancfg.sh", output_value);

system(output_string);

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

strcpy(output_value, "venable=\\\"");

for (i=0; i<ssidCount_2G; i++){
	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANEnable", wifi_index_2G+i);
	strcpy(got_value, cli_get_uci(func_buf));
	strcat(output_value, got_value);
	strcat(output_value, ",");
}

for (i=0; i<ssidCount_5G; i++){
	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANEnable", wifi_index_5G+i);
	strcpy(got_value, cli_get_uci(func_buf));
	strcat(output_value, got_value);
	strcat(output_value, ",");
}                                                                         

output_value[strlen(output_value)-1]='\0';

sprintf(output_string, "echo %s\\\" >> /tmp/vlancfg.sh", output_value);
system(output_string);

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

strcpy(output_value, "vlanid=\\\"");

for (i=0; i<ssidCount_2G; i++){
	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANID", wifi_index_2G+i);
	strcpy(got_value, cli_get_uci(func_buf));
	strcat(output_value, got_value);
	strcat(output_value, ",");
}

for (i=0; i<ssidCount_5G; i++){
	sprintf(func_buf, "wireless.@wifi-iface[%d].WLANVLANID", wifi_index_5G+i);
	strcpy(got_value, cli_get_uci(func_buf));
	strcat(output_value, got_value);
	strcat(output_value, ",");
}                                                                         

output_value[strlen(output_value)-1]='\0';

sprintf(output_string, "echo %s\\\" >> /tmp/vlancfg.sh", output_value);

system(output_string);

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

strcpy(output_value, "wifiIndex=\\\"");

for (i=0; i<ssidCount_2G; i++){
strcat(output_value, "0");
strcat(output_value, ",");
}

for (i=0; i<ssidCount_5G; i++){
strcat(output_value, "1");
strcat(output_value, ",");
}                                                                         

output_value[strlen(output_value)-1]='\0';

sprintf(output_string, "echo %s\\\" >> /tmp/vlancfg.sh", output_value);

system(output_string);

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

strcpy(output_value, "wirelessIndex=\\\"");

for (i=0; i<ssidCount_2G; i++){
	sprintf(tmp_data, "%d", i);
	strcat(output_value, tmp_data);
	strcat(output_value, ",");
}

for (i=0; i<ssidCount_5G; i++){
	sprintf(tmp_data, "%d", i);
	strcat(output_value, tmp_data);
	strcat(output_value, ",");
}                                                                         

output_value[strlen(output_value)-1]='\0';

sprintf(output_string, "echo %s\\\" >> /tmp/vlancfg.sh", output_value);
system(output_string);

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

sprintf(output_string, "echo vlan_num_dual=\\\"%d\\\" >> /tmp/vlancfg.sh", ssidCount_2G+ssidCount_5G);
//printf("output_string: %s\n", output_string);
system(output_string);

//----------------------------------------------------------------------------------------------------------

strcpy(got_value, cli_get_uci("network.sys.ManagementVLANID"));
sprintf(output_string, "echo mvid=\\\"%s\\\" >> /tmp/vlancfg.sh", got_value);

system(output_string);

//----------------------------------------------------------------------------------------------------------

system("/usr/sbin/set_vlan_dual.sh 2>/dev/null");
system("uci commit");
                                                               
}



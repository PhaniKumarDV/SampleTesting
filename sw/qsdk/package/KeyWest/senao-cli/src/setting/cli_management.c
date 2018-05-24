
/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <cli.h>
#include <cli_management.h>
#include <sysFile.h>
#include <systeminfo.h>

#include <arpa/inet.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/

typedef struct __CliAdministrationEntry
{
	T_INT32 nameset;
	T_INT32 oldpwdset;
	T_INT32 newpwdset;
	T_INT32 confirmpwdset;
		
	T_CHAR username[33];
	T_CHAR oldpwd[13];
	T_CHAR newpwd[13];
	T_CHAR confirmpwd[13];

}CliAdministrationEntry;

CliAdministrationEntry CliAdministration={0, 0, 0, 0, "", "", "", ""};

typedef struct __CliTimezoneEntry
{
    const T_CHAR* item;
    const T_CHAR* timezoneCode;
    const T_CHAR* timezoneName;

}CliTimezoneEntry;

CliTimezoneEntry CliTimezoneTable[] = {

	{"0","UTC12",	"UTC-12:00 Kwajalein"},
	{"1","UTC11",	"UTC-11:00 Midway Island, Samoa"},
	{"2","UTC10",	"UTC-10:00 Hawaii"},
	{"3","NAST9NADT,M3.2.0/2,M11.1.0/2",	"UTC-09:00 Alaska"}, 
	{"4","PST8PDT,M3.2.0/2,M11.1.0/2",	"UTC-08:00 Pacific Time"},
	{"5","UTC7",	"UTC-07:00 Arizona"},
	{"6","MST7MDT,M3.2.0/2,M11.1.0/2",	"UTC-07:00 Mountain Time"},
	{"7","UTC6",	"UTC-06:00 Mexico"},
	{"8","CST6CDT,M3.2.0/2,M11.1.0/2",	"UTC-06:00 Central Time"},
	{"9","UTC5",	"UTC-05:00 Colombia, Panama"},
	{"10","EST5EDT,M3.2.0/2,M11.1.0/2",	"UTC-05:00 Eastern Time"},
	{"11","UTC4",	"UTC-04:00 Bolivia, Venezuela"},
	{"12","AST4ADT,M3.2.0/2,M11.1.0/2",	"UTC-04:00 Atlantic Time"},
	{"13","AST4ADT,M3.2.0/2,M11.1.0/2",	"UTC-04:00 Brazil West"},
	{"14","NST3:30NDT,M3.2.0/0:01,M11.1.0/0:01",	"UTC-03:30 Newfoundland"},
	{"15","WGST3WGDT,M3.5.6/22,M10.5.6/23",	"UTC-03:00 Greenland"},
	{"16","BRST3BRDT,M10.3.0/0,M2.5.0/0",	"UTC-03:00 Brazil East"},
	{"17","UTC3",	"UTC-03:00 Guyana"},
	{"18","UTC2",	"UTC-02:00 Mid-Atlantic"},
	{"19","STD1DST,M3.5.0/2,M10.5.0/2",	"UTC-01:00 Azores"},
	{"20","UTC0",	"UTC+00:00 Gambia, Liberia, Morocco"},
	{"21","GMT0BST,M3.5.0/2,M10.5.0/2",	"UTC+00:00 England"},
	{"22","UTC-1",	"UTC+01:00 Tunisia"},
	{"23","STD-1DST,M3.5.0/2,M10.5.0/2",	"UTC+01:00 France, Germany, Italy"},
	{"24","UTC-2",	"UTC+02:00 South Africa"},
	{"25","STD-2DST,M3.5.0/2,M10.5.0/2",	"UTC+02:00 Greece, Ukraine, Romania, Turkey"},
	{"26","UTC-3",	"UTC+03:00 Iraq, Jordan, Kuwait"},
	{"27","EET-2EEST-3,M3.5.0/3,M10.5.0/4",	"UTC+03:00 Finland"},
	{"28","UTC-4",	"UTC+04:00 Armenia"},
	{"29","UTC-5",	"UTC+05:00 Pakistan, Russia"},
	{"30","UTC-5:30",	"UTC+05:30 Bombay, Calcutta, Madras, New Delhi"},
	{"31","UTC-6",	"UTC+06:00 Bangladesh, Russia"},
	{"32","UTC-7",	"UTC+07:00 Thailand, Russia"},
	{"33","UTC-8",	"UTC+08:00 China, Hong Kong, Western Australia, Singapore, Taiwan, Russia"},
	{"34","UTC-9",	"UTC+09:00 Japan, Korea"},
	{"35","CST-9:30CST,M10.5.0/2,M3.5.0/3",	"UTC+09:30 South Australia"},
	{"36","UTC-10",	"UTC+10:00 Guam, Russia"},
	{"37","STD-10DST,M10.5.0/2,M3.5.0/2",	"UTC+10:00 Australia"},
	{"38","UTC-11",	"UTC+11:00 Solomon Islands"},
	{"39","UTC-12",	"UTC+12:00 Fiji"},
	{"40","NZST-12NZDT,M9.5.0/2,M4.1.0/3",	"UTC+12:00 New Zealand"},

};

//Modify for function alignment of Wifi schedule to all models on 2012-11-15
typedef struct __CliWifiScheduleEntry
{

	T_INT32 hourset;
	T_INT32 minuteset;
		
	T_CHAR servicename[17];
	T_CHAR wirelesspower[8];
	T_CHAR day[8];
	T_CHAR hour[8];
	T_CHAR minute[8];

//Modify for function alignment of Wifi schedule to dual radio models on 2012-11-30
T_INT32 dualdaysset;
T_INT32 shourset;
T_INT32 ehourset;
T_INT32 sminuteset;
T_INT32 eminuteset;

T_CHAR service[17];	
T_INT32 dualdays[32];
T_CHAR shour[8];
T_CHAR sminute[8];
T_CHAR ehour[8];
T_CHAR eminute[8];
	
}CliWifiScheduleEntry;
CliWifiScheduleEntry CliWifiSchedule={0, 0, "", "1", "Mon", "", "", 0, 0, 0, 0, 0, "reboot", {0, 0, 0, 0, 0, 0, 0}, "", "", "", ""};

//Add on 2013-07-18 for new Wifi schedule to C600 and EAP900H
typedef struct __NewCliWifiScheduleEntry
{

	T_INT32 availableOfdays[7];
	T_CHAR stimeOfdays[7][8];
	T_CHAR etimeOfdays[7][8];
	
}NewCliWifiScheduleEntry;
NewCliWifiScheduleEntry NewCliWifiSchedule={{1,1,1,1,1,1,1}, {"08:00","08:00","08:00","08:00","08:00","08:00","08:00"}, {"17:00","17:00","17:00","17:00","17:00","17:00","17:00"}};


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

extern T_INT32 cmdtreelevel;
extern T_INT32 radio_shift;

extern CliEntry cli_table_manuallydate[];
extern CliEntry cli_table_automaticallydate[];
extern CliEntry cli_table_vlanp[];

typedef struct __CliDatarateEntry
{
    const T_INT32 item;	
    const T_CHAR* datarateName;
    const T_CHAR* ratecode;
    const T_INT32 rateorder;
    

}CliDatarateEntry;
extern CliDatarateEntry CliDatarateTable[];

extern T_INT32 SSIDProfileIndex;

T_INT32 autosetbridge=-1;
T_INT32 vlanpsetbridge=-1;

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt  admin                            */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"admin",	cli_table_login_remote,	getNextTable,	"Administration",		"", AUTH_ADMIN,	MODEL_ALL},
//	{OPM_AP,	"vlan2",	cli_table_vlan2,	getNextTable,	"2.4G Management vlan",		"", AUTH_ANY,	MODEL_DUAL},
//	{OPM_AP,	"vlan5",	cli_table_vlan5,	getNextTable,	"5G Management vlan",		"", AUTH_ANY,	MODEL_DUAL},
//	{OPM_AP,	"mvlan",	NULL,			cmdmvlan,	"Management VLAN settings",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"traffic",	cli_table_traffic,	getNextTable,	"Traffic shaping",		"", AUTH_ADMIN, MODEL_DUAL},
//	{OPM_AP,	"clientc",	cli_table_clientc,	getNextTable,	"Client control",		"", AUTH_ANY,	MODEL_TRUE},	
//	{OPM_ALL,	"snmp",		cli_table_snmp,		getNextTable,	"SNMP settings",		"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"backup",	cli_table_bk,		getNextTable,	"Backup/Restore settings",	"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"fwgrade",	cli_table_fwupgrade,	getNextTable,	"Firmware upgrade",		"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"time",		cli_table_time,		getNextTable,	"Time settings",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"log",		cli_table_log,		getNextTable,	"Log",				"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"diag",		cli_table_diag,		getNextTable,	"Diagnostics",			"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"diagv6",	cli_table_diagv6,	getNextTable,	"Diagnostics for IPV6",		"", AUTH_ANY,	ENS202EXT_ID},
//	{OPM_ALL,	"disc",		NULL,			cmddisc,	"Device Discovery",		"", AUTH_ANY,	MODEL_ALL},	
//	{OPM_ALL,	"led",		cli_table_led,		getNextTable,	"Led control",			"", AUTH_ANY,	MODEL_EAP_ECB},
//	{OPM_ALL,	"radio2",	cli_table_radio,	getNextTable,	"2.4G radio control",		"", AUTH_ADMIN, MODEL_2G},
//	{OPM_ALL,	"radio5",	cli_table_radio,	getNextTable,	"5G radio control",		"", AUTH_ADMIN, MODEL_5G},		
//	{OPM_ALL,	"logout",	NULL,			cmdlogout,	"Logout",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_mgmt,		cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

//static CliEntry cli_table_login_remote[]= {
//	{OPM_ALL,		"login",	cli_table_admin,	getNextTable,	"Login Setting",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AR | OPM_CBRT,	"remote",	cli_table_remote,	getNextTable,	"Remote Access",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,		"help",		cli_table_login_remote,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,		"exit",		NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

//static CliEntry cli_table_admin[]= {
//	{OPM_ALL,	"nname",	NULL,			cmdnewname,	"New Name",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"opw",		NULL,			cmdoldpwd,	"Old Password",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"npw",		NULL,			cmdnewpwd,      "New Password",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"cpw",		NULL,			cmdconfirmpwd,	"Confirm Password",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"accept",	NULL,			cmdadminaccept,	"Accept administration setting",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_admin,	cmdHelp,	"Help",					"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdadminexit,	"Exit",					"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

//static CliEntry cli_table_remote[]= {
//	{OPM_AR | OPM_CBRT,	"rmgmt",	NULL,			cmdrmgmt,	"Remote Management",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AR | OPM_CBRT,	"rupgrade",	NULL,			cmdrupgrade,	"remote Upgrade",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AR | OPM_CBRT,	"rmport",	NULL,			cmdrmport,	"Remote Management Port",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,		"help",		cli_table_remote,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,		"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},	
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdnewname
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdnewname(T_VOID* priv, CliData* cliData)
{
T_CHAR uci_get_buf[33];
FILE *pp;

	if(cliData->argc==0){
		
		if (CliAdministration.nameset==0){
			if( (pp = popen("/lib/auth.sh get_username", "r")) == NULL )
			{
				printf("popen() error!\n");
				exit(1);
			}
			fgets(uci_get_buf, sizeof uci_get_buf, pp);
			pclose(pp);
			uci_get_buf[strlen(uci_get_buf)-1]='\0';
			tprintf("Current setting: %s\n", uci_get_buf);
		}
		else{
			strcpy(uci_get_buf, CliAdministration.username);
			tprintf("Current setting: %s \n", uci_get_buf);
		}
		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

		if ( strlen(cliData->tokens[cliData->tokenLen-1].token)>32 ){
			tprintf("Name: Length must between 1 to 32!!\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		
		CliAdministration.nameset=1;
		strcpy(CliAdministration.username, cliData->tokens[cliData->tokenLen-1].token);	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdoldpwd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdoldpwd(T_VOID* priv, CliData* cliData)
{
T_CHAR uci_get_buf[13];
T_CHAR pwdold[33];
T_CHAR pwdnew[33];
T_CHAR buf[128];
FILE* fp1;
FILE* fp2;

	if(cliData->argc==0){
		
		if (CliAdministration.oldpwdset==0){

			tprintf("Current setting: (12 characters at most)\n");
		}
		else{
			strcpy(uci_get_buf, CliAdministration.oldpwd);
			tprintf("Current setting: %s (12 characters at most)\n", uci_get_buf);
		}
		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		
		if (strlen(cliData->tokens[cliData->tokenLen-1].token)>12){
			tprintf("The length of password should not be larger than 12\n");
			cliData->tokenLen-=2;
			return CLI_NOTHING;
		}
		
		system("/lib/auth.sh get_password > /tmp/checkoldpwd1");
		sprintf(buf,"/lib/auth.sh psencry %s > /tmp/checkoldpwd2", cliData->tokens[cliData->tokenLen-1].token);
		system(buf);
		
		if((fp1 = fopen("/tmp/checkoldpwd1", "r"))==NULL){
			printf("Can't open file\n");
			cliData->tokenLen-=2;
			return CLI_NOTHING;
		}
		
		fgets(pwdold,sizeof(pwdold),fp1);
		fclose(fp1);

		if((fp2 = fopen("/tmp/checkoldpwd2", "r"))==NULL){
			printf("Can't open file\n");
			cliData->tokenLen-=2;
			return CLI_NOTHING;
		}

		fgets(pwdnew,sizeof(pwdnew),fp2);	
		fclose(fp2);
		
		if ( strcmp(pwdold, pwdnew)!=0 ){
			tprintf("Invalid old password\n");
			cliData->tokenLen-=2;
			return CLI_NOTHING;
		}

		CliAdministration.oldpwdset=1;
		strcpy(CliAdministration.oldpwd, cliData->tokens[cliData->tokenLen-1].token);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
		
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdnewpwd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdnewpwd(T_VOID* priv, CliData* cliData)
{
T_CHAR uci_get_buf[13];
//FILE *pp;

	if(cliData->argc==0){
		
		if (CliAdministration.newpwdset==0){

			tprintf("Current setting: (12 characters at most)\n");
		}
		else{
			strcpy(uci_get_buf, CliAdministration.newpwd);
			tprintf("Current setting: %s (12 characters at most)\n", uci_get_buf);
		}
		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		
		if (strlen(cliData->tokens[cliData->tokenLen-1].token)>12){
			tprintf("The length of password should not be larger than 12\n");
			cliData->tokenLen-=2;
			return CLI_NOTHING;
		}
		
		CliAdministration.newpwdset=1;
		strcpy(CliAdministration.newpwd, cliData->tokens[cliData->tokenLen-1].token);	

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdconfirmpwd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdconfirmpwd(T_VOID* priv, CliData* cliData)
{
T_CHAR uci_get_buf[13];
//FILE *pp;

	if(cliData->argc==0){
		
		if (CliAdministration.confirmpwdset==0)
			tprintf("Current setting: (12 characters at most)\n");
		else{
			strcpy(uci_get_buf, CliAdministration.confirmpwd);
			tprintf("Current setting: %s (12 characters at most)\n", uci_get_buf);
		}
		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		
		if (strlen(cliData->tokens[cliData->tokenLen-1].token)>12){
			tprintf("The length of password should not be larger than 12\n");
			cliData->tokenLen-=2;
			return CLI_NOTHING;
		}
		
		CliAdministration.confirmpwdset=1;
		strcpy(CliAdministration.confirmpwd, cliData->tokens[cliData->tokenLen-1].token);	
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdadminaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdadminaccept(T_VOID* priv, CliData* cliData)
{
//T_CHAR uci_get_buf[128];
T_CHAR c1[255];

	if(cliData->argc==0){
		
		if ( CliAdministration.nameset==0 ){
			tprintf("Name: Length must between 1 to 32\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		if ( CliAdministration.oldpwdset==0 ){
			tprintf("Old password: Length must between 1 to 12\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		if ( CliAdministration.newpwdset==0 ){
			tprintf("New password: Length must between 1 to 12\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		if ( CliAdministration.confirmpwdset==0 ){
			tprintf("Confirm password: Length must between 1 to 12\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}	
		
		if ( strcmp(CliAdministration.newpwd, CliAdministration.confirmpwd)!=0 ){
			tprintf("The new password and confirm password are not the same\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		else {		
			sprintf(c1,"/lib/auth.sh set_auth %s %s", CliAdministration.username, CliAdministration.newpwd);
			system(c1);
					
			
			strcpy(CliAdministration.username, "");
			CliAdministration.nameset=0;
			strcpy(CliAdministration.oldpwd, "");
			CliAdministration.oldpwdset=0;
			strcpy(CliAdministration.newpwd, "");
			CliAdministration.newpwdset=0;
			strcpy(CliAdministration.confirmpwd, "");
			CliAdministration.confirmpwdset=0;
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
    		
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdadminexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdadminexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	strcpy(CliAdministration.username, "");
	CliAdministration.nameset=0;
	strcpy(CliAdministration.oldpwd, "");
	CliAdministration.oldpwdset=0;
	strcpy(CliAdministration.newpwd, "");
	CliAdministration.newpwdset=0;
	strcpy(CliAdministration.confirmpwd, "");
	CliAdministration.confirmpwdset=0;

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}

/*****************************************************************
* NAME: cmdrmgmt
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdrmgmt(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.RemoteManagementEnable";
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
* NAME: cmdrupgrade
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdrupgrade(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.RemoteUpgradeEnable";
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
* NAME: cmdrmport
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdrmport(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ipnat.ipnat.RemoteManagementPort";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

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

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt vlan2 / vlan5                     */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_AP,	"vlan2",	cli_table_vlan2,	getNextTable,	"2.4G Management vlan",		"", AUTH_ANY,	MODEL_DUAL},
//	{OPM_AP,	"vlan5",	cli_table_vlan5,	getNextTable,	"5G Management vlan",		"", AUTH_ANY,	MODEL_DUAL},
//};

//static CliEntry cli_table_vlan2[]= {
//	{OPM_AP | OPM_WDSAP,	"vlanp",	NULL,			cmdvlanp,	"2.4G VLAN profile settings",	"", AUTH_ADMIN, MODEL_DUAL},
//	{OPM_ALL,		"help",   	cli_table_vlan2,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,		"exit",   	NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

//static CliEntry cli_table_vlan5[]= {
//	{OPM_AP | OPM_WDSAP,	"vlanp",	NULL,			cmdvlanp,	"5G VLAN profile settings",	"", AUTH_ADMIN, MODEL_DUAL},
//	{OPM_ALL,		"help",   	cli_table_vlan5,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,		"exit",   	NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

//CliEntry cli_table_vlanp[]= {
//	{OPM_AP,	"ssidact",	NULL,			cmdssidact,	"SSID active",		"", AUTH_ANY,	MODEL_DUAL},
// 	{OPM_AP,	"isoact",	NULL,			cmdisoact,	"Isolation active",	"", AUTH_ANY,	MODEL_DUAL},
//	{OPM_AP,	"vid",		NULL,			cmdvid,		"VLAN ID",		"", AUTH_ANY,	MODEL_DUAL},
//  	{OPM_ALL,	"help",   	cli_table_vlanp,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdvlanpexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
//  	{ CMD_END_TAG}  
//};

/*****************************************************************
* NAME: cmdvlanp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   ### leaf node and then non-leaf node
****************************************************************/
CliStatus cmdvlanp(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 ssidCount;
T_INT32 i;
T_INT32 j=1;
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
	ssidCount=getModelssidCount(operationeMode);
	
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
		
		if ( vlanpsetbridge==-1 ){
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, ssidCount, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
			}

			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
				
			SSIDProfileIndex=atoi(uci_set_buf);

			cliData->tokenLen--;
			//Handle the command -->mgmt/vlan2>vlanp 2
			if (cmdtreelevel==2){
				vlanpsetbridge=1;
				//prompt will be --> mgmt/vlan2/vlanp>
				cmdtreelevel=cliData->tokenLen;
			}
			return cmdHelp(cli_table_vlanp,cliData);
		}
		else 
			return getNextTable(cli_table_vlanp, cliData);
	}
	else if(cliData->argc>1)
		//handle relative path --> mgmt/vlan2/vlanp>
		if ( vlanpsetbridge==1 )
			return getNextTable(cli_table_vlanp, cliData);
			
		if (!errorcheckValidDecimal(cliData->tokens[3].token) || ! errorcheckIntRange( 1, ssidCount, atoi(cliData->tokens[3].token)) )
	  		return CLI_PARAMS_ERR;
	  		
	  	//handle absolute path --> mgmt>vlan2 vlanp 2 vid
		else{
			SSIDProfileIndex=atoi(cliData->tokens[3].token);
			//Skip "2" when handling "mgmt vlan2 vlanp 2 vid"
			cliData->argc--;
			return getNextTable(cli_table_vlanp, cliData);
		}

}

/*****************************************************************
* NAME: cmdvlanpexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdvlanpexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	vlanpsetbridge=-1;

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt mvlan                             */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_AP,	"mvlan",	NULL,			cmdmvlan,	"Management VLAN settings",	"", AUTH_ADMIN, MODEL_ALL},
//};


/*****************************************************************
* NAME: cmdmvlan
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdmvlan(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.sys.ManagementVLANID";
T_CHAR func_buf1[128]="wireless.wifi0.WLANSSIDIsolation";
T_CHAR func_buf2[128];
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 ssidCount;

//Get ssidCount of 2G and 5G
T_INT32 ssidCount_2G = ( current_opmode_2==OPM_AP ) ? 8 : 4;
T_INT32 ssidCount_5G = ( current_opmode_5==OPM_AP ) ? 8 : 4;

T_INT32 i;
//T_INT32 j;
T_INT32 operationeMode=current_opmode;
T_INT32 wifi_index;
T_CHAR br0_enable[32];
FILE* fp;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);

//printf("ssidCount=%d, ssidCount_2G=%d, ssidCount_5G=%d\n", ssidCount, ssidCount_2G, ssidCount_5G);	
	
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(func_buf1, "wireless.wifi1.WLANSSIDIsolation");

	wifi_index=get_wifi_iface(operationeMode);

	if(cliData->argc==0){
		
		strcpy(uci_get_buf, cli_get_uci(func_buf));

		tprintf("Current setting: %s (1~4094:MVLAN ID, 4096:No VLAN tag)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
		
		strcpy(uci_get_buf, cli_get_uci(func_buf1));
		
		//if ( atoi(uci_get_buf)==0 )
		//WLANSSIDIsolation==0, all isoact are disable for single-radio
		if ( (atoi(uci_get_buf)==0) && (model_radio==2 || model_radio==5) ){
			printf("Can not set MVID! Please enable the Profile Isolation first\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		//all isoact are disable for dual-radio
		if (model_radio==7){	
			for (i=1; i<=ssidCount_2G; i++){
				sprintf(func_buf2, "wireless.@wifi-iface[%d].WLANVLANEnable", i-1);
				strcpy(uci_get_buf, cli_get_uci(func_buf2));
				if ( atoi(uci_get_buf)==1 )
					break;
			}
			//1~8 isoact are disable
			if (i>ssidCount_2G){		
				for (i=radio_shift+1; i<=radio_shift+ssidCount_5G; i++){
					sprintf(func_buf2, "wireless.@wifi-iface[%d].WLANVLANEnable", i-1);
					strcpy(uci_get_buf, cli_get_uci(func_buf2));
//printf("func_buf2=%s, i=%d\n", func_buf2, i);
					if ( atoi(uci_get_buf)==1 )
						break;
				}
				//26~33 isoact are disable
				if (i>radio_shift+ssidCount_5G){
					printf("Can not set MVID! Please enable the Profile Isolation first\n");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
			}
		}

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || atoi(cliData->tokens[cliData->tokenLen-1].token)!=4096 && !errorcheckIntRange( 1, 4094, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
  			return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
			
		cli_set_uci(func_buf, uci_set_buf);

if (model_radio==2 || model_radio==5){
		system(" cat /etc/config/network |grep \"\'interface\' \'0\'\" > /tmp/br0 ");
		
		if((fp = fopen("/tmp/br0", "r"))==NULL){
			printf("Can't open file\n");
			exit;
		}

		fgets(br0_enable,sizeof(br0_enable),fp);
		fclose(fp);
	
		if (strstr(br0_enable, "interface")==NULL && atoi(uci_set_buf)!=4096 )
			system("br0=$(uci add network interface); uci rename network.$br0=0");	

		if (strstr(br0_enable, "interface")!=NULL && atoi(uci_set_buf)==4096 ){
			system("uci delete network.0");
			system("uci commit");
		}

		for (i=1; i<=ssidCount; i++)
			vlanProccess(i);
		//dual-radio 5G vlanprocess
		if (model_radio==7){
			for (i=radio_shift+1; i<=radio_shift+ssidCount; i++)
				vlanProccess(i);
		}
}
else
	vlan_dual_radio_process();
			
		cliData->tokenLen-=2;
		return CLI_NOTHING;
			
	}
	else if(cliData->argc>1){
//printf("mvlan cliData->argc=%d\n", cliData->argc);
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt wvlanpt                           */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_AP|OPM_WDSAP|OPM_WDSB,	"wvlanpt",	cli_table_wvlanp,	getNextTable,	"WLAN VLAN pass through",	"", AUTH_ADMIN, EAP900_ID},
//};

//Add on 2013-06-06 by Philips to support WLAN VLAN Pass-Through for eap900 which is requested by Jacy
//static CliEntry cli_table_wvlanp[]= {
//	{OPM_ALL,	"vdisable",	NULL,			cmdvdisable,	"WLAN VLAN pass through inactive",	"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"v2to5",	NULL, 	   		cmdv2to5,	"2G to 5G VLAN pass through",		"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"v5to2",	NULL, 	   		cmdv5to2,	"5G to 2G VLAN pass through",		"",	AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"help",   	cli_table_wvlanp,	cmdHelp,	"Help",					"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",					"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdvdisable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdvdisable(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.wifi0.WLANVLANPass";
T_CHAR func_buf1[128]="wireless.wifi1.WLANVLANPass";
T_CHAR uci_set_buf[128]="0";
T_CHAR uci_set_buf1[128]="0";


	if(cliData->argc==0){
		tprintf("\nWLAN VLAN Pass-Through has been disabled.\n\n");
		//Set the information of "WLAN VLAN Pass Through" to be 0
		cli_set_uci(func_buf, uci_set_buf);
		cli_set_uci(func_buf1, uci_set_buf1);
		
		cliData->tokenLen--;
		
//		system("/etc/init.d/network restart > /dev/null 2>&1");
//		system("/etc/init.d/wlan_vlanpass start > /dev/null 2>&1");
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdv2to5
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdv2to5(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.wifi0.WLANVLANPass";
T_CHAR func_buf1[128]="wireless.wifi1.WLANVLANPass";
T_CHAR uci_set_buf[128]="0";
T_CHAR uci_set_buf1[128]="1";

	if(cliData->argc==0){
		tprintf("\n2G to 5G VLAN Pass-Through has been enabled.\n\n");
		//Set the information of "WLAN VLAN Pass Through" to be 0
		cli_set_uci(func_buf, uci_set_buf);
		cli_set_uci(func_buf1, uci_set_buf1);
		
		cliData->tokenLen--;
		
//		system("/etc/init.d/network restart > /dev/null 2>&1");
//		system("/etc/init.d/wlan_vlanpass start > /dev/null 2>&1");
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdv5to2
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdv5to2(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wireless.wifi0.WLANVLANPass";
T_CHAR func_buf1[128]="wireless.wifi1.WLANVLANPass";
T_CHAR uci_set_buf[128]="1";
T_CHAR uci_set_buf1[128]="0";

	if(cliData->argc==0){	
		tprintf("\n5G to 2G VLAN Pass-Through has been enabled.\n\n");
		//Set the information of "WLAN VLAN Pass Through" to be 0
		cli_set_uci(func_buf, uci_set_buf);
		cli_set_uci(func_buf1, uci_set_buf1);
		
		cliData->tokenLen--;
		
//		system("/etc/init.d/network restart > /dev/null 2>&1");
//		system("/etc/init.d/wlan_vlanpass start > /dev/null 2>&1");
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}


/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt traffic                           */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt clientc bsteer                    */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_AP,	"clientc",	cli_table_clientc,	getNextTable,	"Client control",		"", AUTH_ANY,	MODEL_TRUE},	
//	{ CMD_END_TAG}
//};

//static CliEntry cli_table_clientc[]= {
//	{OPM_AP,	"bsteer",	cli_table_bsteer,	getNextTable,	"Band steering",		"", AUTH_ADMIN,	EAP600TRUE_ID},
//	{ CMD_END_TAG}
//};

//CliEntry cli_table_bsteer[]= {
//	{OPM_AP,	"bsteeract",    NULL,			cmdbsteeract,	"Band steering active",		"", AUTH_ANY,	EAP600TRUE_ID},
//	{OPM_AP,	"threshold",    NULL,			cmdthreshold,	"Band steering threshold",	"", AUTH_ANY,	EAP600TRUE_ID},
//  	{OPM_ALL,	"help",		cli_table_bsteer,	cmdHelp,	"Help",				"", AUTH_ADMIN, EAP600TRUE_ID},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, EAP600TRUE_ID},
//  	{ CMD_END_TAG}  
//};

/*****************************************************************
* NAME: cmdbsteeract
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdbsteeract(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="clientcontrol.bandsteer.enable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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
* NAME: cmdthreshold
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdthreshold(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="clientcontrol.bandsteer.threshold";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s %% (1~100)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 100, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
/*                   CLI Command -- mgmt clientc ratec2 or ratec5          */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_AP,	"clientc",	cli_table_clientc,	getNextTable,	"Client control",		"", AUTH_ANY,	MODEL_TRUE},	
//	{ CMD_END_TAG}
//};

//static CliEntry cli_table_clientc[]= {
//	{OPM_AP,	"ratec2",	cli_table_ratec2,	getNextTable,	"2.4G rate control",		"", AUTH_ANY,	MODEL_TRUE},
//	{OPM_AP,	"ratec5",	cli_table_ratec5,	getNextTable,	"5G rate control",		"", AUTH_ANY,	EAP600TRUE_ID},
//	{ CMD_END_TAG}
//};

//CliEntry cli_table_ratec2[]= {
//	{OPM_AP,	"drate",	cli_table_drate,	getNextTable,	"Data rate",	"", AUTH_ANY,	MODEL_TRUE},
// 	{OPM_AP,	"brate",	cli_table_brate,	getNextTable,	"Basic rate",	"", AUTH_ANY,	MODEL_TRUE},
//  	{OPM_ALL,	"help",   	cli_table_ratec2,	cmdHelp,	"Help",		"", AUTH_ADMIN, MODEL_TRUE},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",		"", AUTH_ADMIN, MODEL_TRUE},
//  	{ CMD_END_TAG}  
//};

//CliEntry cli_table_ratec5[]= {
//	{OPM_AP,	"drate",	cli_table_drate,	getNextTable,	"Data rate",	"", AUTH_ANY,	EAP600TRUE_ID},
// 	{OPM_AP,	"brate",	cli_table_brate,	getNextTable,	"Basic rate",	"", AUTH_ANY,	EAP600TRUE_ID},
//  	{OPM_ALL,	"help",   	cli_table_ratec5,	cmdHelp,	"Help",		"", AUTH_ADMIN, EAP600TRUE_ID},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",		"", AUTH_ADMIN, EAP600TRUE_ID},
//  	{ CMD_END_TAG}  
//};

//CliEntry cli_table_drate[]= {
//	{OPM_AP,	"enable",	NULL,			cmddrateenable,		"Data rate enable",	"", AUTH_ANY,	MODEL_TRUE},
// 	{OPM_AP,	"disable",	NULL,			cmddratedisable,	"Data rate disable",	"", AUTH_ANY,	MODEL_TRUE},
//  	{OPM_ALL,	"help",   	cli_table_drate,	cmdHelp,		"Help",			"", AUTH_ADMIN, MODEL_TRUE},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,		"Exit",			"", AUTH_ADMIN, MODEL_TRUE},
//  	{ CMD_END_TAG}  
//};

//CliEntry cli_table_brate[]= {
//	{OPM_AP,	"enable",	NULL,			cmdbrateenable,		"Basic rate enable",	"", AUTH_ANY,	MODEL_TRUE},
// 	{OPM_AP,	"disable",	NULL,			cmdbratedisable,	"Basic rate disable",	"", AUTH_ANY,	MODEL_TRUE},
//  	{OPM_ALL,	"help",		cli_table_brate,	cmdHelp,		"Help",			"", AUTH_ADMIN, MODEL_TRUE},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,		"Exit",			"", AUTH_ADMIN, MODEL_TRUE},
//  	{ CMD_END_TAG}  
//};

/*****************************************************************
* NAME: cmdratecontrol
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdratecontrol(T_VOID* priv, CliData* cliData, T_INT32 enable, T_INT32 data)
{
T_CHAR func_buf[128]="clientcontrol.ratectrl_2g.data";
T_CHAR func_buf1[128]="wireless.@wifi-iface[0].rate";
T_CHAR wifiinterface[128]="wireless.wifi0.hwmode";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_set_buf[128];
T_CHAR wirelessmode[128];
T_INT32 antenna=getHostantenna();
T_INT32 ssidCount;
T_INT32 datarate_change;
T_INT32 i;
T_INT32 set_index;
T_INT32 wifi_index;
T_INT32 operationeMode=current_opmode;
T_CHAR buf[128];
T_INT32 rate_display_list[29];
T_INT32 rate_control_list[29];
T_INT32 rate_control_output[29];
T_INT32	start;
T_INT32	stop;
T_CHAR* token;

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;
		
	ssidCount=getModelssidCount(operationeMode);
		
	wifi_index=get_wifi_iface(operationeMode);

	sprintf(func_buf1, "wireless.@wifi-iface[%d].rate", wifi_index);

	strcpy(uci_get_buf1, cli_get_uci(func_buf1));
	
	if ( strcmp(uci_get_buf1, "auto")!=0 ){
		tprintf("Current data rate is fixed (%s), you can't execute rate control command!\n\n", uci_get_buf1);
		
		if (cliData->argc==0)
			cliData->tokenLen-=1;
		if (cliData->argc==1)
			cliData->tokenLen-=2;
		if (cliData->argc>1)
			return CLI_NO_MATCH;
			
		return CLI_NOTHING;
	}
//Initial rateDisplayList and rateControlList
for (i=0; i<=28; i++){
	rate_display_list[i] = rate_control_list[i] = rate_control_output[i] = 0;
}
	
	if (model_radio==2 && data==0)
		strcpy(func_buf, "clientcontrol.ratectrl_2g.basic");
	if (model_radio==2 && data==1)
		strcpy(func_buf, "clientcontrol.ratectrl_2g.data");

	if (model_radio==5 && data==0)
		strcpy(func_buf, "clientcontrol.ratectrl_5g.basic");
	if (model_radio==5 && data==1)
		strcpy(func_buf, "clientcontrol.ratectrl_5g.data");	
		

	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 && data==0 )
		strcpy(func_buf, "clientcontrol.ratectrl_2g.basic");
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 && data==1 )
		strcpy(func_buf, "clientcontrol.ratectrl_2g.data");
	
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 && data==0 )
		strcpy(func_buf, "clientcontrol.ratectrl_5g.basic");
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 && data==1 )
		strcpy(func_buf, "clientcontrol.ratectrl_5g.data");
	
	
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		strcpy(wifiinterface, "wireless.wifi1.hwmode");

	
	strcpy(wirelessmode, getWirelessmode(wifiinterface));

	if(cliData->argc==0){
		//Get the data rate	
		strcpy(uci_get_buf, cli_get_uci(func_buf));

//Set rateControlList
if ( strlen(uci_get_buf)>6 ){
	i=4;
	strncpy( buf, uci_get_buf+i, 2);
	buf[ 2 ] = '\0';

	while(strcmp(buf, "FF")!=0){
		rate_control_list[convertcode2itemtable(buf)] = 1;
		i+=2;

		strncpy( buf, uci_get_buf+i, 2);
		buf[ 2 ] = '\0';		
	}
			
}

//Set rateDisplayList
if ( strcmp(wirelessmode,"11a_pure")==0 || strcmp(wirelessmode,"11a")==0 || strcmp(wirelessmode,"11g_pure")==0 ){
	start=5;
	stop=12;
	for (i=start; i<=stop; i++){
		printf("%d - %s\n", CliDatarateTable[i].item-4, CliDatarateTable[i].datarateName);
		rate_display_list[i] = 1;	
	}
}
if ( strcmp(wirelessmode,"11b")==0 ){
	start=1;
	stop=4;
	for (i=start; i<=stop; i++){
		printf("%d - %s\n", CliDatarateTable[i].item, CliDatarateTable[i].datarateName);
		rate_display_list[i] = 1;
	}
}
if ( strcmp(wirelessmode,"11g")==0 ){
	start=1;
	stop=12;
	for (i=start; i<=stop; i++){
		printf("%d - %s\n", CliDatarateTable[i].item, CliDatarateTable[i].datarateName);
		rate_display_list[i] = 1;
	}
}
if ( strcmp(wirelessmode,"11n_pure")==0 || strcmp(wirelessmode,"11na_pure")==0 ){
	start=13;
	if (antenna==1)
		stop=20;
	else
		stop=28;
		
	for (i=start; i<=stop; i++){
		printf("%d - %s\n", CliDatarateTable[i].item-12, CliDatarateTable[i].datarateName);
		rate_display_list[i] = 1;
	}
}
if ( strcmp(wirelessmode,"11ng")==0 ){
	start=1;
	if (antenna==1)
		stop=20;
	else
		stop=28;
		
	for (i=start; i<=stop; i++){
		printf("%d - %s\n", CliDatarateTable[i].item, CliDatarateTable[i].datarateName);
		rate_display_list[i] = 1;
	}
}
if ( strcmp(wirelessmode,"11na")==0 ){
	start=5;
	if (antenna==1)
		stop=20;
	else
		stop=28;
		
	for (i=start; i<=stop; i++){
		printf("%d - %s\n", CliDatarateTable[i].item-4, CliDatarateTable[i].datarateName);
		rate_display_list[i] = 1;
	}
}
tprintf("Current enabled rate: ");
//Change rate_control_list[i] according rate_display_list[i])
for (i=0; i<=28; i++){

	if( (rate_display_list[i] & rate_control_list[i]) == 0)
		rate_control_list[i] = 0;
	else{
		printf("%s, ", CliDatarateTable[i].datarateName );
	
	}

}		
printf("\n");
tprintf("Recognized input format:  1,3,... \n");


for (i=0; i<=28; i++){
	if (rate_control_list[i] == 1)
		rate_control_output[CliDatarateTable[i].rateorder] = 1;
}


strcpy(uci_set_buf, "0xF1");

for (i=0; i<=28; i++){
	if (rate_control_output[i] == 1){
		
		if (i==4)
			strcat(uci_set_buf, "0B");
		else if (i==5)
			strcat(uci_set_buf, "0F");
		else if (i==6)
			strcat(uci_set_buf, "18");
		else
			strcat(uci_set_buf, CliDatarateTable[i].ratecode);

		
	}
}
strcat(uci_set_buf, "FF");

cli_set_uci(func_buf, uci_set_buf);

		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

//Set rateDisplayList
if ( strcmp(wirelessmode,"11a_pure")==0 || strcmp(wirelessmode,"11a")==0 || strcmp(wirelessmode,"11g_pure")==0 ){
	start=5;
	stop=12;
	for (i=start; i<=stop; i++){
		rate_display_list[i] = 1;	
	}
}
if ( strcmp(wirelessmode,"11b")==0 ){
	start=1;
	stop=4;
	for (i=start; i<=stop; i++){
		rate_display_list[i] = 1;
	}
}
if ( strcmp(wirelessmode,"11g")==0 ){
	start=1;
	stop=12;
	for (i=start; i<=stop; i++){
		rate_display_list[i] = 1;
	}
}
if ( strcmp(wirelessmode,"11n_pure")==0 || strcmp(wirelessmode,"11na_pure")==0 ){
	start=13;
	if (antenna==1)
		stop=20;
	else
		stop=28;
		
	for (i=start; i<=stop; i++){
		rate_display_list[i] = 1;
	}
}
if ( strcmp(wirelessmode,"11ng")==0 ){
	start=1;
	if (antenna==1)
		stop=20;
	else
		stop=28;
		
	for (i=start; i<=stop; i++){
		rate_display_list[i] = 1;
	}
}
if ( strcmp(wirelessmode,"11na")==0 ){
	start=5;
	if (antenna==1)
		stop=20;
	else
		stop=28;
		
	for (i=start; i<=stop; i++){
		rate_display_list[i] = 1;
	}
}

//Set rateControlList
if ( strlen(uci_get_buf)>6 ){
	i=4;
	strncpy( buf, uci_get_buf+i, 2);
	buf[ 2 ] = '\0';

	while(strcmp(buf, "FF")!=0){
		rate_control_list[convertcode2itemtable(buf)] = 1;
		i+=2;

		strncpy( buf, uci_get_buf+i, 2);
		buf[ 2 ] = '\0';		
	}
			
}

//Change rate_control_list[i] according rate_display_list[i])
for (i=0; i<=28; i++){

	if( (rate_display_list[i] & rate_control_list[i]) == 0)
		rate_control_list[i] = 0;

}				

		//Modify on 2012-08-01 to avoid segmentation fault when the length of input > 128 
		if (!errorcheckStrLength( 75, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of input data should not be larger than 75\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);



	token =strtok(uci_set_buf, ",");
	while(token)
	{

		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( token[0]=='0' && strlen(token)>1 )
			sprintf(token, "%d", atoi(token) );

		if (atoi(token)==0 || !errorcheckValidDecimal(token) || !errorcheckDatarate(wirelessmode, antenna, atoi(token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

	
	
		i = atoi(token);
		//11a_pure, 11a, 11g_pure, 11na start==5
		if ( strcmp(wirelessmode,"11a_pure")==0 || strcmp(wirelessmode,"11a")==0 || strcmp(wirelessmode,"11g_pure")==0 || strcmp(wirelessmode,"11na")==0 )
			i+=4;
		//11n_pure, 11na_pure start==13
		if ( strcmp(wirelessmode,"11n_pure")==0 || strcmp(wirelessmode,"11na_pure")==0 )
			i+=12;
		if (enable==1)	
			rate_control_list[i] = 1;
		else
			rate_control_list[i] = 0;
		
		token = strtok(NULL, ",");

	}


		
for (i=0; i<=28; i++){
	if (rate_control_list[i] == 1)
		rate_control_output[CliDatarateTable[i].rateorder] = 1;
}


strcpy(uci_set_buf, "0xF1");

for (i=0; i<=28; i++){
	if (rate_control_output[i] == 1){
		
		if (i==4)
			strcat(uci_set_buf, "0B");
		else if (i==5)
			strcat(uci_set_buf, "0F");
		else if (i==6)
			strcat(uci_set_buf, "18");
		else
			strcat(uci_set_buf, CliDatarateTable[i].ratecode);

		
	}
}
strcat(uci_set_buf, "FF");

cli_set_uci(func_buf, uci_set_buf);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}

}

/*****************************************************************
* NAME: cmddrateenable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddrateenable(T_VOID* priv, CliData* cliData)
{
T_INT32 enable = 1;
T_INT32 data = 1;
return cmdratecontrol(priv, cliData, enable, data);

}

/*****************************************************************
* NAME: cmddratedisable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddratedisable(T_VOID* priv, CliData* cliData)
{
T_INT32 disable = 0;
T_INT32 data = 1;
return cmdratecontrol(priv, cliData, disable, data);

}

/*****************************************************************
* NAME: cmdbrateenable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdbrateenable(T_VOID* priv, CliData* cliData)
{
T_INT32 enable = 1;
T_INT32 basic = 0;
return cmdratecontrol(priv, cliData, enable, basic);

}

/*****************************************************************
* NAME: cmdbratedisable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdbratedisable(T_VOID* priv, CliData* cliData)
{
T_INT32 disable = 0;
T_INT32 basic = 0;
return cmdratecontrol(priv, cliData, disable, basic);

}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt clientc climit2 or climit5        */
/*-------------------------------------------------------------------------*/
	
//CliEntry cli_table_mgmt[]= {
//	{OPM_AP,	"clientc",	cli_table_clientc,	getNextTable,	"Client control",		"", AUTH_ANY,	MODEL_TRUE},	
//	{ CMD_END_TAG}
//};

//static CliEntry cli_table_clientc[]= {
//	{OPM_AP,	"climit2",	cli_table_climit2,	getNextTable,	"2.4G client limitation",	"", AUTH_ANY,	MODEL_TRUE},
//	{OPM_AP,	"climit5",	cli_table_climit5,	getNextTable,	"5G client limitation",		"", AUTH_ANY,	EAP600TRUE_ID},
//	{ CMD_END_TAG}
//};

//CliEntry cli_table_climit2[]= {
//	{OPM_AP,	"limitact",	NULL,			cmdclimit2act,	"Client limit active",	"", AUTH_ANY,	MODEL_TRUE},
// 	{OPM_AP,	"max",		NULL,			cmdclimit2max,	"Maxmuim client limit",	"", AUTH_ANY,	MODEL_TRUE},
//  	{OPM_ALL,	"help",		cli_table_climit2,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_TRUE},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_TRUE},
//  	{ CMD_END_TAG}  
//};

//CliEntry cli_table_climit5[]= {
//	{OPM_AP,	"limitact",	NULL,			cmdclimit5act,	"Client limit active",	"", AUTH_ANY,	EAP600TRUE_ID},
// 	{OPM_AP,	"max",		NULL,			cmdclimit5max,	"Maxmuim client limit",	"", AUTH_ANY,	EAP600TRUE_ID},
//  	{OPM_ALL,	"help",		cli_table_climit5,	cmdHelp,	"Help",			"", AUTH_ADMIN, EAP600TRUE_ID},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,	 "Exit",		"", AUTH_ADMIN, EAP600TRUE_ID},
//  	{ CMD_END_TAG}  
//};

/*****************************************************************
* NAME: cmdclimit2act
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdclimit2act(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="clientcontrol.clientlimit_2g.enable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];


//Modify for C600 on 2013-04-30 when mesh-only is enabled
if ( strcmp(model_name, "c600")==0 ){
T_CHAR func_buf1[128]="wireless.w0_index23.MESHEnable";

	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	
	if ( (strcmp(uci_get_buf, "mesh-only")==0) && (cliData->argc==1) ){
		printf("Client limit active can't be set when mesh-only is enabled.\n");
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
}


	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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
* NAME: cmdclimit2max
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdclimit2max(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="clientcontrol.clientlimit_2g.maxclient";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];


//Modify for C600 on 2013-04-30 when mesh-only is enabled
if ( strcmp(model_name, "c600")==0 ){
T_CHAR func_buf1[128]="wireless.w0_index23.MESHEnable";

	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	
	if ( (strcmp(uci_get_buf, "mesh-only")==0) && (cliData->argc==1) ){
		printf("Maximum client limit can't be set when mesh-only is enabled.\n");
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
}


	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1~127)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 127, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
* NAME: cmdclimit5act
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdclimit5act(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="clientcontrol.clientlimit_5g.enable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];


//Modify for C600 on 2013-04-30 when mesh-only is enabled
if ( strcmp(model_name, "c600")==0 ){
T_CHAR func_buf1[128]="wireless.w1_index23.MESHEnable";

	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	
	if ( (strcmp(uci_get_buf, "mesh-only")==0) && (cliData->argc==1) ){
		printf("Client limit active can't be set when mesh-only is enabled.\n");
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
}


	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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
* NAME: cmdclimit5max
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdclimit5max(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="clientcontrol.clientlimit_5g.maxclient";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];


//Modify for C600 on 2013-04-30 when mesh-only is enabled
if ( strcmp(model_name, "c600")==0 ){
T_CHAR func_buf1[128]="wireless.w1_index23.MESHEnable";

	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	
	if ( (strcmp(uci_get_buf, "mesh-only")==0) && (cliData->argc==1) ){
		printf("Maximum client limit can't be set when mesh-only is enabled.\n");
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
}


	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1~127)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 127, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
/*                   CLI Command -- mgmt  cloud                             */
/*-------------------------------------------------------------------------*/

//Add on 2013-05-02 by Philips to support cloud setting for C600
//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"cloud",	cli_table_cloud,	getNextTable,	"Cloud settings",		"", AUTH_ANY, C600_ID},
//};

//static CliEntry cli_table_cloud[]= {
//	{OPM_ALL,	"cloudact",	NULL,		cmdcloudact,	"Cloud Management active",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"pserver",	NULL,		cmdpserver,	"Proxy Server",			"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"pport",	NULL,		cmdpport,	"Proxy Port",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"pusername",	NULL,		pusername,	"User Name",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"ppasswd",	NULL,		cmdppasswd,	"Password",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_cloud,cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,		cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},	
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdcloudact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-03-22
* Modify:   
****************************************************************/
CliStatus cmdcloudact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ectclient.system.enable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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
		//Modify by Mars on 2010-07-19 to reload snmp
		//if (atoi(uci_set_buf)==1) {
		//	system("/etc/init.d/snmpd enable > /dev/null 2>&1");
		//	system("/etc/init.d/snmpd reload > /dev/null 2>&1");
		//	system("/etc/init.d/trapdaemon enable > /dev/null 2>&1");
		//	system("/etc/init.d/trapdaemon start > /dev/null 2>&1");
		//}
		//else {
		//	system("/etc/init.d/snmpd disable > /dev/null 2>&1");
		//	system("/etc/init.d/snmpd stop > /dev/null 2>&1");
		//	system("/etc/init.d/trapdaemon disable > /dev/null 2>&1");
		//	system("/etc/init.d/trapdaemon start > /dev/null 2>&1");
		//}
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdpserver
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-03-22
* Modify:   
****************************************************************/
CliStatus cmdpserver(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ectclient.system.proxyAddress";
T_CHAR func_buf1[128]="ectclient.system.enable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	//If Cloud Management is disabled, please enable it first
	if( atoi(uci_get_buf) == 0 ){
		printf("Cloud Management is disabled, please enable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}
	
//Modify on 2012-12-14 by Philips which is requested by Jackey to support IPV4 and IPV6 address
T_INT32 rc4;
struct in6_addr octetstr_ipv6;
T_INT32 rc6;
struct in6_addr octetstr_ipv4;

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);

	
if( model_ID & MODEL_IPV6 )
	tprintf("Recognized input format:  IPv4 or IPv6 address    EX: 192.168.1.35 or 8E4A::4B\n");
else
	tprintf("Recognized input format:  IPv4 address    EX: 192.168.1.35\n");
		
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){


if( model_ID & MODEL_IPV6 ){
	//Modify on 2012-12-14 by Philips which is requested by Jackey to support IPV4 and IPV6 address
	rc4 = inet_pton(AF_INET, cliData->tokens[cliData->tokenLen-1].token, &octetstr_ipv4);
	rc6 = inet_pton(AF_INET6, cliData->tokens[cliData->tokenLen-1].token, &octetstr_ipv6);
	if( (rc4==0)&&(rc6==0) ){
		printf("\n\"%s\" is a invalid IPv4 or IPv6 address.\n", cliData->tokens[cliData->tokenLen-1].token);
	
//		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
	}
}
else{

	if( !errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token ) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
	}
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
* NAME: cmdpport
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-03-22
* Modify:   
****************************************************************/
CliStatus cmdpport(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ectclient.system.proxyPort";
T_CHAR func_buf1[128]="ectclient.system.enable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	//If Cloud Management is disabled, please enable it first
	if( atoi(uci_get_buf) == 0 ){
		printf("Cloud Management is disabled, please enable it first!\n");
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

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdpusername
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-03-22
* Modify:   
****************************************************************/
CliStatus cmdpusername(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ectclient.system.proxyUsername";
T_CHAR func_buf1[128]="ectclient.system.enable";
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];

	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	//If Cloud Management is disabled, please enable it first
	if( atoi(uci_get_buf) == 0 ){
		printf("Cloud Management is disabled, please enable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}
	
	if(cliData->argc==0){	
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (32 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 32, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of user name should not be larger than 32\n");
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
* NAME: cmdppasswd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-03-22
* Modify:   
****************************************************************/
CliStatus cmdppasswd(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ectclient.system.proxyPassword";
T_CHAR func_buf1[128]="ectclient.system.enable";
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];

	strcpy(uci_get_buf, cli_get_uci(func_buf1));
	//If Cloud Management is disabled, please enable it first
	if( atoi(uci_get_buf) == 0 ){
		printf("Cloud Management is disabled, please enable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}
	
	if(cliData->argc==0){	
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (32 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 32, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of password should not be larger than 32\n");
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
/*                   CLI Command -- mgmt  capser                             */
/*-------------------------------------------------------------------------*/

//Add on 2013-05-02 by Philips to support captive auth server for C600
//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"capser",	NULL,                   cmdcapser,	"Captive server settings",		"",	AUTH_ANY, C600_ID},
//};

/*****************************************************************
* NAME: cmdcapser
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-05-02
* Modify:   
****************************************************************/
CliStatus cmdcapser(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="eccaptive.server.host";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	
//Modify on 2012-12-14 by Philips which is requested by Jackey to support IPV4 and IPV6 address
T_INT32 rc4;
struct in6_addr octetstr_ipv6;
T_INT32 rc6;
struct in6_addr octetstr_ipv4;

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);

	
if( model_ID & MODEL_IPV6 )
	tprintf("Recognized input format:  IPv4 or IPv6 address    EX: 192.168.1.35 or 8E4A::4B\n");
else
	tprintf("Recognized input format:  IPv4 address    EX: 192.168.1.35\n");
		
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){


if( model_ID & MODEL_IPV6 ){
	//Modify on 2012-12-14 by Philips which is requested by Jackey to support IPV4 and IPV6 address
	rc4 = inet_pton(AF_INET, cliData->tokens[cliData->tokenLen-1].token, &octetstr_ipv4);
	rc6 = inet_pton(AF_INET6, cliData->tokens[cliData->tokenLen-1].token, &octetstr_ipv6);
	if( (rc4==0)&&(rc6==0) ){
		printf("\n\"%s\" is a invalid IPv4 or IPv6 address.\n", cliData->tokens[cliData->tokenLen-1].token);
	
//		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
	}
}
else{

	if( !errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token ) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
	}
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
/*                   CLI Command -- mgmt  snmp                             */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"snmp",		cli_table_snmp,		getNextTable,	"SNMP settings",		"", AUTH_ANY,	MODEL_ALL},
//};

//static CliEntry cli_table_snmp[]= {
//	{OPM_ALL,	"snmpact",	NULL,		cmdsnmpact,	"SNMP active",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"cont",		NULL,		cmdcont,	"Contact",				"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"loca",		NULL,		cmdloca,        "Location",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"rcom",		NULL,		cmdrcom,	"Community name (read only)",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"wcom",		NULL,		cmdwcom,	"Community name (read/write)",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"trapaddr",	NULL,		cmdtrapaddr,	"Trap destination address",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"trapcom",	NULL,		cmdtrapcom,	"Trap destination community name",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"snmpv3act",	NULL,		cmdsnmpv3act,   "SNMPv3 active",			"", AUTH_ADMIN, MODEL_SNMPv3},
//	{OPM_ALL,	"username",	NULL,		cmdusername,    "User name",				"", AUTH_ANY,	MODEL_SNMPv3},
//	{OPM_ALL,	"authp",	NULL,		cmdauthp,       "Auth protocol",			"", AUTH_ADMIN, MODEL_SNMPv3},
//	{OPM_ALL,	"authk",	NULL,		cmdauthk,       "Auth key",				"", AUTH_ADMIN, MODEL_SNMPv3},
//	{OPM_ALL,	"privp",	NULL,		cmdprivp,       "Priv protocol",			"", AUTH_ADMIN, MODEL_SNMPv3},
//	{OPM_ALL,	"privk",	NULL,		cmdprivk,       "Priv key",				"", AUTH_ADMIN, MODEL_SNMPv3},
//	{OPM_ALL,	"engineid",	NULL,		cmdengineid,	"Engine ID",				"", AUTH_ADMIN, MODEL_SNMPv3},	
//	{OPM_ALL,	"help",   	cli_table_snmp,	cmdHelp,	"Help",					"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,		cmdexit,	"Exit",					"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdsnmpact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsnmpact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@system[0].SnmpEnable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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
		//Modify by Mars on 2010-07-19 to reload snmp
		if (atoi(uci_set_buf)==1) {
			system("/etc/init.d/snmpd enable > /dev/null 2>&1");
			system("/etc/init.d/snmpd reload > /dev/null 2>&1");
			system("/etc/init.d/trapdaemon enable > /dev/null 2>&1");
			system("/etc/init.d/trapdaemon start > /dev/null 2>&1");
		}
		else {
			system("/etc/init.d/snmpd disable > /dev/null 2>&1");
			system("/etc/init.d/snmpd stop > /dev/null 2>&1");
			system("/etc/init.d/trapdaemon disable > /dev/null 2>&1");
			system("/etc/init.d/trapdaemon start > /dev/null 2>&1");
		}
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}
/*****************************************************************
* NAME: cmdcont
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdcont(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@system[0].sysContact";
T_CHAR uci_get_buf[256];
T_CHAR uci_set_buf[256];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (255 characters at most)\n", uci_get_buf);
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 255, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of snmp contact should not be larger than 255\n");
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
* NAME: cmdloca
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdloca(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@system[0].sysLocation";
T_CHAR uci_get_buf[256];
T_CHAR uci_set_buf[256];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (255 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 255, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of snmp location should not be larger than 255\n");
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
* NAME: cmdport
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0509
* Modify:   
****************************************************************/
CliStatus cmdport(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@agent[0].agentaddress";
T_CHAR func_buf1[128]="snmpd.@agent6[0].agentaddress";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128]="UDP:";
T_CHAR uci_set_buf1[128]="UDP6:";

	if(cliData->argc==0){	
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1-65535)\n", uci_get_buf+4);
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


		//strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		strcat(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		strcat(uci_set_buf1, cliData->tokens[cliData->tokenLen-1].token);

		//cli_set_uci(func_buf, uci_set_buf);
		cli_set_uci(func_buf, uci_set_buf);
		cli_set_uci(func_buf1, uci_set_buf1);
			
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}


/*****************************************************************
* NAME: cmdrcom
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdrcom(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@com2sec[0].community";
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];

	if(cliData->argc==0){		

		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (32 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 32, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of community name for read only should not be larger than 32\n");
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
* NAME: cmdwcom
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwcom(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@com2sec[1].community";
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (32 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 32, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of community name for read/write should not be larger than 32\n");
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
* NAME: cmdtrapaddr
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdtrapaddr(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@system[0].SnmpTrapDstIP";
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

		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
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
* NAME: cmdtrapport
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0509
* Modify:   
****************************************************************/
CliStatus cmdtrapport(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@system[0].SnmpTrapDstPort";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

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

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdtrapcom
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdtrapcom(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@system[0].SnmpTrapCmnty";
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (32 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 32, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of trap destination community name should not be larger than 32\n");
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
* NAME: cmdsnmpv3act
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsnmpv3act(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@snmpv3[0].snmpv3enable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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
* NAME: cmdusername
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdusername(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@snmpv3[0].username";
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];

	if(cliData->argc==0){	
		strcpy(uci_get_buf, cli_get_uci(func_buf));
//Modify on 2013-01-28 for the length of user name which is requested by Jacy
//		tprintf("Current setting: %s (32 characters at most)\n", uci_get_buf);
		tprintf("Current setting: %s (31 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
//Modify on 2013-01-28 for the length of user name which is requested by Jacy	
//		if (!errorcheckStrLength( 32, cliData->tokens[cliData->tokenLen-1].token) ){
		if (!errorcheckStrLength( 31, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of user name should not be larger than 32\n");
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
* NAME: cmdauthp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdauthp(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@snmpv3[0].authprotocol";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (2:None, 1:SHA, 0:MD5)\n", uci_get_buf);
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
		
		cli_set_uci(func_buf, uci_set_buf);
		
		//If snmpv3 auth protocol is None, then also set snmpv3 private protocol to be None
		if ( atoi(uci_set_buf)==2 )
			cli_set_uci("snmpd.@snmpv3[0].privprotocol", "1");

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdauthk
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdauthk(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@snmpv3[0].authkey";
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (8-32 characters)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckIntRange( 8, 32, strlen(cliData->tokens[cliData->tokenLen-1].token)) ){
			tprintf("The length of auth key should not be 8 ~ 32 characters\n");
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
* NAME: cmdprivp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdprivp(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@snmpv3[0].privprotocol";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:None, 0:DES)\n", uci_get_buf);
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
* NAME: cmdprivk
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdprivk(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@snmpv3[0].privkey";
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];


	//Get snmpv3 private protocol information
	strcpy(uci_get_buf, cli_get_uci("snmpd.@snmpv3[0].privprotocol"));
		
	//If snmpv3 private protocol is None, please set private protocol first
	if( atoi(uci_get_buf) == 1 ){
		printf(" Snmpv3 private protocol is None, please set it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (8-32 characters)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckIntRange( 8, 32, strlen(cliData->tokens[cliData->tokenLen-1].token)) ){
			tprintf("The length of priv key should not be 8 ~ 32 characters\n");
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
* NAME: cmdengineid
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdengineid(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="snmpd.@snmpv3[0].EngineID";
T_CHAR uci_get_buf[33];
T_CHAR uci_set_buf[33];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (32 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 32, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of Engine ID should not be larger than 32\n");
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
/*                   CLI Command -- mgmt email                             */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"email",	cli_table_email,	getNextTable,	"SNMP settings",			"", AUTH_ANY,	MODEL_ALL},
//};

//Add on 2013-06-17 by Philips to support Email Alert for eap900 which is requested by Jacy
//static CliEntry cli_table_email[]= {
//	{OPM_ALL,	"mailact",	NULL,			cmdmailact,	"Email alert active",			"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"addrto",	NULL, 	   		cmdaddrto,	"Email Address to recipients",		"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"addrfrom",	NULL,			cmdaddrfrom,	"Email Address from Administrator",	"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"mailauth",	NULL,			cmdmailauth,	"Email authentication",			"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"mailpwd",	NULL, 	   		cmdmailpwd,	"Email password",			"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"smtpsvr",	NULL,			cmdsmtpsvr,	"SMTP server",				"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"smtport",	NULL, 	   		cmdsmtport,	"SMTP port",				"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"mailsec",	NULL, 	   		cmdmailsec,	"Security mode",			"",	AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"alert",	NULL,			cmdalert,	"System event alert",			"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"subject",	NULL,			cmdsubject,	"Subject of system event alert",	"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"message",	NULL, 	   		cmdmessage,	"Message of system event alert",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_email,	cmdHelp,	"Help",					"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",					"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdmailact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-06-17
* Modify:   
****************************************************************/
CliStatus cmdmailact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.email.alert_enable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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
* NAME: cmdaddrto
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-06-17
* Modify:   
****************************************************************/
CliStatus cmdaddrto(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.email.alert_to";
T_CHAR uci_get_buf[1032];
T_CHAR uci_set_buf[1032];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1024 characters at most)\n", uci_get_buf);
		tprintf("Recognized input format:  at least one Email address    EX: a@example.com;b@example.net\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 1024, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of email destination address should not be larger than 1024\n");
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
* NAME: cmdaddrfrom
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-06-17
* Modify:   
****************************************************************/
CliStatus cmdaddrfrom(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.email.from";
T_CHAR uci_get_buf[264];
T_CHAR uci_set_buf[264];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (256 characters at most)\n", uci_get_buf);
		tprintf("Recognized input format:  one Email address    EX: a@example.com\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 256, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of email source address should not be larger than 256\n");
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
* NAME: cmdmailauth
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-06-17
* Modify:   
****************************************************************/
CliStatus cmdmailauth(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.email.auth";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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
* NAME: cmdmailusr
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-08-06
* Modify:   
****************************************************************/
CliStatus cmdmailusr(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.email.user";
T_CHAR uci_get_buf[264];
T_CHAR uci_set_buf[264];

	//Get email alert authentication information
	strcpy(uci_get_buf, cli_get_uci("system.email.auth"));
		
	//If email alert authentication is disabled, please set private protocol first
	if( atoi(uci_get_buf) == 0 ){
		printf("Email authentucation is disabled, please enable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){	
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		//tprintf("Current setting: %s (256 characters at most)\n", uci_get_buf);
//Modify on 2013-08-30 by Philips to change the length of username from 256 to 64 which is requested by Jacy		
		tprintf("Current setting: %s (64 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//if (!errorcheckStrLength( 256, cliData->tokens[cliData->tokenLen-1].token) ){
//Modify on 2013-08-30 by Philips to change the length of username from 256 to 64 which is requested by Jacy
		if (!errorcheckStrLength( 64, cliData->tokens[cliData->tokenLen-1].token) ){	
			tprintf("The length of password should not be larger than 64\n");
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
* NAME: cmdmailpwd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-06-17
* Modify:   
****************************************************************/
CliStatus cmdmailpwd(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.email.password";
T_CHAR uci_get_buf[264];
T_CHAR uci_set_buf[264];

	//Get email alert authentication information
	strcpy(uci_get_buf, cli_get_uci("system.email.auth"));
		
	//If email alert authentication is disabled, please set private protocol first
	if( atoi(uci_get_buf) == 0 ){
		printf("Email authentucation is disabled, please enable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){	
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (256 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 256, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of password should not be larger than 256\n");
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
* NAME: cmdsmtpsvr
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-06-17
* Modify:   
****************************************************************/
CliStatus cmdsmtpsvr(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.email.smtpaddr";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);
		
		//tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
		
		//Modify on 2013-08-07 by Philips to support domain name for SMTP server which is requested by Jacy
		tprintf("Recognized input format:  Domain name or IPv4 address    EX: smtp.gmail.com or 192.168.1.35\n");
		
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

//Modify on 2013-08-07 by Philips to support domain name for SMTP server which is requested by Jacy
//		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
//			cliData->tokenLen-=2;
//	  		return CLI_PARAMS_ERR;
//		}

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
* NAME: cmdsmtport
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-06-17
* Modify:   
****************************************************************/
CliStatus cmdsmtport(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.email.smtpport";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

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

		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdmailsec
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-06-17
* Modify:   
****************************************************************/
CliStatus cmdmailsec(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.email.security";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (0:None,1:SSL/TLS,2:STARTTLS)\n", uci_get_buf);
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
		
		cli_set_uci(func_buf, uci_set_buf);
		
		//The port should be 25 when security is None
		if ( atoi(cliData->tokens[cliData->tokenLen-1].token)==0 )
			cli_set_uci("system.email.smtpport", "25");
		//The port should be 465 when security is SSL/TLS
		if ( atoi(cliData->tokens[cliData->tokenLen-1].token)==1 )
			cli_set_uci("system.email.smtpport", "465");
		//The port should be 587 when security is STARTTLS
		if ( atoi(cliData->tokens[cliData->tokenLen-1].token)==2 )
			cli_set_uci("system.email.smtpport", "587");
			
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdalert
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-06-17
* Modify:   
****************************************************************/
CliStatus cmdalert(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.email.alert_event_config";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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
* NAME: cmdsubject
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-06-17
* Modify:   
****************************************************************/
CliStatus cmdsubject(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.email.alert_event_config_subject";
T_CHAR uci_get_buf[264];
T_CHAR uci_set_buf[264];

	//Get system event alert information
	strcpy(uci_get_buf, cli_get_uci("system.email.alert_event_config"));
		
	//If email alert is disabled, please enable it first
	if( atoi(uci_get_buf) == 0 ){
		printf("System event alert is disabled, please enable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (256 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 256, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of email alert subject should not be larger than 256\n");
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
* NAME: cmdmessage
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-06-17
* Modify:   
****************************************************************/
CliStatus cmdmessage(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.email.alert_event_config_message";
T_CHAR uci_get_buf[264];
T_CHAR uci_set_buf[264];

	//Get system event alert information
	strcpy(uci_get_buf, cli_get_uci("system.email.alert_event_config"));
		
	//If email alert is disabled, please enable it first
	if( atoi(uci_get_buf) == 0 ){
		printf("System event alert is disabled, please enable it first!\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}
	
	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (256 characters at most)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 256, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of email alert message should not be larger than 256\n");
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
/*                   CLI Command -- mgmt ssh                               */
/*                   CLI Command -- mgmt hact                              */
/*                   CLI Command -- mgmt hfwd                              */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"ssh",		NULL,			cmdssh,		"SSH settings",		"", AUTH_ADMIN, EAP900_ID},	
//	{OPM_ALL,	"https",	cli_table_https,	getNextTable,	"HTTPS settings",	"", AUTH_ADMIN, EAP900_ID},
//};

//Add on 2013-06-06 by Philips to support HTTPS for eap900 which is requested by Jacy
//static CliEntry cli_table_https[]= {
//	{OPM_ALL,	"hact",		NULL,			cmdhact,	"Https active",		"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"hfwd",		NULL, 	   		cmdhfwd,	"Https forward",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_https,	cmdHelp,	"Help",			"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",			"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdssh
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdssh(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="secureshell.ssh.enable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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
		
		system("/etc/init.d/secureshellctrl restart > /dev/null 2>&1");
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdhact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdhact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="secureshell.https.enable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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
		
		system("/etc/init.d/httpd restart > /dev/null 2>&1");
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdhfwd
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdhfwd(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="secureshell.https.forward";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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

		system("/etc/init.d/httpd restart > /dev/null 2>&1");

		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt  backup                           */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"backup",	cli_table_bk,		getNextTable,	"Backup/Restore settings",	"", AUTH_ANY,	MODEL_ALL},
//};

//static CliEntry cli_table_bk[]= {
//	{OPM_ALL,	"savecp",	NULL,		cmdsavecp,      "Save a copy of current settings",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"restore",	NULL,		cmdrestore,	"Restore saved settings from a file",	"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"revertfac",	NULL,		cmdrevertfac,	"Revert to factory default settings",	"", AUTH_ADMIN, MODEL_ALL},


//Add on 2013-06-06 by Philips to support Reset User Default for eap900 which is requested by Jacy	
//	{OPM_ALL,	"saveuser",	NULL,		cmdsaveuser,	"Save to user default",			"", AUTH_ADMIN, EAP900_ID},	
//	{OPM_ALL,	"restoreuser",	NULL,		cmdrestoreuser,	"Restore to user default",		"", AUTH_ADMIN, EAP900_ID},


//	{OPM_ALL,	"help",   	cli_table_bk,	cmdHelp,	"Help",					"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,		cmdexit,	"Exit",					"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};


/*****************************************************************
* NAME: cmdsavecp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsavecp(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="network.lan.ipaddr";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR c1[300];

	if(cliData->argc==0){
		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Download URL:\n");		
		tprintf("  http://%s/cgi-bin/luci/html/CM_BackupRestore?backup=1\n", uci_get_buf);
		tprintf("  ftp://name:password@192.168.1.100/backup-EAP600TRUE-2012-09-10.tar.gz\n");
		tprintf("  tftp://name:password@192.168.1.100/backup-EAP600TRUE-2012-09-10.tar.gz\n\n");
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

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		sprintf(c1, "/bin/cli.sh config_backup_upload %s ", uci_set_buf);
		system(c1);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdrestore
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdrestore(T_VOID* priv, CliData* cliData)
{
T_CHAR uci_set_buf[128];
T_CHAR c1[300];

	if(cliData->argc==0){		
		tprintf("Upload URL:\n");
		tprintf("  http://192.168.1.100:8080/backup-ECB350-2012-05-31.tar.gz\n");
		tprintf("  ftp://name:password@192.168.1.100/backup-EAP600TRUE-2012-09-10.tar.gz\n");
		tprintf("  tftp://name:password@192.168.1.100/backup-EAP600TRUE-2012-09-10.tar.gz\n\n");
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

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		sprintf(c1, "/bin/cli.sh config_restore %s ", uci_set_buf);
		system(c1);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdrevertfac
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdrevertfac(T_VOID* priv, CliData* cliData)
{
	if(cliData->argc==0){
				
    		cliData->tokenLen--;
    		printf("Rebooting, please wait ...\n");
    		system(". /etc/functions.sh; jffs2_mark_erase rootfs_data");
    		system("sync; sync; reboot");
		return CLI_NOTHING;
	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}


/*****************************************************************
* NAME: cmdsaveuser
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdsaveuser(T_VOID* priv, CliData* cliData)
{
	if(cliData->argc==0){
				
    		cliData->tokenLen--;
    		printf("This will save all settings to USER defaults.\n");    		
      		system("/etc/save_user_default.sh > /dev/null 2>&1");
		return CLI_NOTHING;
	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdrestoreuser
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-0606
* Modify:   
****************************************************************/
CliStatus cmdrestoreuser(T_VOID* priv, CliData* cliData)
{
	if(cliData->argc==0){
				
    		cliData->tokenLen--;
    		printf("This will reset all settings back to USER defaults. All of your settings will be erased.\n");
		printf("Rebooting, please wait ...\n");
    		system("/etc/cfg_user_restore.sh > /dev/null 2>&1");
		return CLI_NOTHING;
	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}


/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt autoreboot                        */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"autoreboot",	cli_table_autoreboot,	getNextTable,	"Auto reboot settings",	"",	AUTH_ANY, MODEL_ALL},
//};

//static CliEntry cli_table_autoreboot[]= {
//	{OPM_ALL,	"autorb",	NULL,			cmdautorb,	"Auto Reboot Setting",		"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"rbfreq",	NULL,			cmdrbfreq,	"Frequency of Auto Reboot",	"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"rbamt",	NULL,			cmdrbamt,	"Amount of Auto Reboot",	"",     AUTH_ADMIN, MODEL_ALL},		
//	{OPM_ALL,	"help",   	cli_table_autoreboot,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_TRUE},
//	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_TRUE},
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdrbact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-12
* Modify:   
****************************************************************/
CliStatus cmdrbact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="autoreboot.autoreboot.enable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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
* NAME: cmdrbfreq
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-12
* Modify:   
****************************************************************/
CliStatus cmdrbfreq(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="autoreboot.autoreboot.frequency";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	//Get autoreboot enable information
	strcpy(uci_get_buf, cli_get_uci("autoreboot.autoreboot.enable"));

	//If autoreboot is disabled, please enable autoreboot first
	if( atoi(uci_get_buf) == 0 ){
		printf("Autoreboot is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
//		printf("1. Minute\n");
//		printf("2. Hour\n");
//		printf("3. Day\n");
//		printf("4. Week\n");
		tprintf("Current setting: %s (1:Min,2:Hour,3:Day,4:Week)\n", uci_get_buf);
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

		if ( atoi(cliData->tokens[cliData->tokenLen-1].token)==1 )
			strcpy(uci_set_buf, "Min");
		if ( atoi(cliData->tokens[cliData->tokenLen-1].token)==2 )
			strcpy(uci_set_buf, "Hour");
		if ( atoi(cliData->tokens[cliData->tokenLen-1].token)==3 )
			strcpy(uci_set_buf, "Day");
		if ( atoi(cliData->tokens[cliData->tokenLen-1].token)==4 )
			strcpy(uci_set_buf, "Week");
			
		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdrbamt
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-12
* Modify:   
****************************************************************/
CliStatus cmdrbamt(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR func_buf1[128]="autoreboot.autoreboot.frequency";
T_CHAR uci_get_buf[128];
T_CHAR uci_get_buf1[128];
T_CHAR uci_set_buf[128];
T_CHAR range_buf[128];
T_INT32 stop;

	//Get autoreboot enable information
	strcpy(uci_get_buf, cli_get_uci("autoreboot.autoreboot.enable"));
	
	//If autoreboot is disabled, please enable autoreboot first
	if( atoi(uci_get_buf) == 0 ){
		printf("Autoreboot is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}
	
	//Get autoreboot frequency information
	strcpy(uci_get_buf1, cli_get_uci(func_buf1));
	if (strcmp(uci_get_buf1, "Min")==0){
		strcpy(func_buf, "autoreboot.autoreboot.min_amount");
		strcpy(range_buf, "(1:10,2:20,3:30,4:40,5:50,6:60)");
		stop=6;
	}
	if (strcmp(uci_get_buf1, "Hour")==0){
		strcpy(func_buf, "autoreboot.autoreboot.hour_amount");
		strcpy(range_buf, "(1-24 hour)");
		stop=24;
	}
	if (strcmp(uci_get_buf1, "Day")==0){
		strcpy(func_buf, "autoreboot.autoreboot.day_amount");
		strcpy(range_buf, "(1-31 day)");
		stop=31;				
	}
	if (strcmp(uci_get_buf1, "Week")==0){
		strcpy(func_buf, "autoreboot.autoreboot.week_amount");
		strcpy(range_buf, "(1-5 week)");
		stop=5;				
	}
		
	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s %s\n", uci_get_buf, range_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, stop, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

	if (strcmp(uci_get_buf1, "Min")==0)
		sprintf(uci_set_buf, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token)*10);
	else	
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
/*                   CLI Command -- mgmt autoreboot                        */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"autorb",	cli_table_newautoreboot, getNextTable,	"Auto reboot settings",		"", AUTH_ANY, EAP900_ID},
//};

//Modify on 2013-07-01 by Philips to support auto reboot for eap900 which is requested by Jacy
//static CliEntry cli_table_newautoreboot[]= {
//	{OPM_ALL,	"arbact",	NULL,				cmdarbact,	"Auto reboot active",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"arbday",	NULL,				cmdarbday,	"Days of auto reboot",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"arbtime",	NULL,				cmdarbtime,	"Time of auto reboot",		"", AUTH_ADMIN, MODEL_ALL},		
//	{OPM_ALL,	"help",   	cli_table_newautoreboot,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,				cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdarbact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-01
* Modify:   
****************************************************************/
CliStatus cmdarbact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wirelessAvailability.reboot.status";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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

		system("/etc/init.d/wirelessAvailability start > /dev/null 2>&1");
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdarbday
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-02
* Modify:   
****************************************************************/
CliStatus cmdarbday(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wirelessAvailability.reboot.day";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 length;
T_INT32 i;
T_CHAR buf[8];
T_INT32 low_bound=-1;

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (0:Sun, 1:Mon, 2:Tue, 3:Wed, 4:Thu, 5:Fri, 6:Sat)\n", uci_get_buf);		
		tprintf("Recognized input format: (7:None) or (A list of days)   EX: 7 or 0,1,3,5,6\n");
	
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		length = strlen(cliData->tokens[cliData->tokenLen-1].token);
		//Handle the input -- 7:None
		if ( length==1 && atoi(cliData->tokens[cliData->tokenLen-1].token)==7 ){
			cli_set_uci(func_buf, "");
			cliData->tokenLen-=2;
			system("/etc/init.d/wirelessAvailability start > /dev/null 2>&1");
			return CLI_NOTHING;
		}
		
		if(  length%2==0 ){
			cliData->tokenLen-=2;
  			return CLI_PARAMS_ERR;
		}

		for ( i=0; i<length; i++ ){
			//Handle the ',' partion of input Ex: 1,3,4,5
			if( (i%2==1) && (cliData->tokens[cliData->tokenLen-1].token[i]!=',') )
			{
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
			}
			//Handle the number partion of input Ex: 1,3,4,5
			if( i%2==0 ){
				buf[0] = cliData->tokens[cliData->tokenLen-1].token[i];
				buf[1] = '\0';		
				if ( !errorcheckValidDecimal(buf) || !errorcheckIntRange( 0, 6, atoi(buf)) ){
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				if ( low_bound >= atoi(buf) ){
					printf("The input decimal digits should be ascending, Ex: 1,3,4,6");
					cliData->tokenLen-=2;
	  				return CLI_PARAMS_ERR;
				}
				low_bound = atoi(buf);
			}
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		
		system("/etc/init.d/wirelessAvailability start > /dev/null 2>&1");
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdarbtime
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-02
* Modify:   
****************************************************************/
CliStatus cmdarbtime(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wirelessAvailability.reboot.time";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 i;
T_INT32 length;
T_INT32 hourlength=0;
T_INT32 minutelength;
T_CHAR hour[16];
T_CHAR minute[16];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));

		tprintf("Current setting: %s \n", uci_get_buf);
		tprintf("Recognized input format: (0-23 Hour):(0-59 Minute)   EX: 9:55\n");		
			
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Get the length of hour and minute
		length = strlen(cliData->tokens[cliData->tokenLen-1].token);
		while ( i<=length && cliData->tokens[cliData->tokenLen-1].token[hourlength]!=':' )
			hourlength++;
		minutelength=length-hourlength-1;
		
		if ( !errorcheckIntRange( 3, 5, length ) || !errorcheckIntRange( 1, 2, hourlength ) || !errorcheckIntRange( 1, 2, minutelength ) ){
			cliData->tokenLen-=2;
			return CLI_PARAMS_ERR;
		}
		//Get the hour
		for (i=0; i<hourlength; i++)
			hour[i] = cliData->tokens[cliData->tokenLen-1].token[i];
		hour[i] = '\0';
		//Get the minute
		for (i=0; i<minutelength; i++)
			minute[i] = cliData->tokens[cliData->tokenLen-1].token[i+hourlength+1];
		minute[i] = '\0';	
		
		//The range of hour shoule be 0-23
		if ( !errorcheckValidDecimal(hour) || !errorcheckIntRange( 0, 23, atoi(hour)) ){
			printf("The range of hour should be 0-23\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		//The range of minute shoule be 0-59
		if ( !errorcheckValidDecimal(minute) || !errorcheckIntRange( 0, 59, atoi(minute)) ){
			printf("The range of minute should be 0-59\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		//Handle the leading zero in hour or minute
		if ( (hourlength==2 && hour[0]=='0') || (minutelength==2 && minute[0]=='0') )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d:%d", atoi(hour), atoi(minute) );
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		cli_set_uci(func_buf, uci_set_buf);
		cliData->tokenLen-=2;
		
		system("/etc/init.d/wirelessAvailability start > /dev/null 2>&1");		
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}


/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt  fwgrade                          */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"fwgrade",	cli_table_fwupgrade,	getNextTable,	"Firmware upgrade",		"", AUTH_ANY,	MODEL_ALL},
//};

//static CliEntry cli_table_fwupgrade[]= {
//	{OPM_ALL,	"fwup",	NULL,			cmdfwup,	"Firmware upgrade",	"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"help",	cli_table_fwupgrade,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",	NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},	
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdfwup
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdfwup(T_VOID* priv, CliData* cliData)
{
T_CHAR uci_set_buf[128];
T_CHAR c1[300];

	if(cliData->argc==0){		
		tprintf("Recognized URL format:  string    EX: http://192.168.1.101:8080/backup-ECB350-2012-05-31.tar.gz\n");
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

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		sprintf(c1, "/bin/cli.sh fwupgrade %s ", uci_set_buf);
		system(c1);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt time                              */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"time",		cli_table_time,		getNextTable,	"Time settings",		"", AUTH_ADMIN, MODEL_ALL},
//};

//static CliEntry cli_table_time[]= {
//	{OPM_ALL,	"auto",		NULL,   	cmdauto,	"Automatically get date and time",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"dlsave",	cli_table_daylight,	getNextTable,	"Daylight saving settings",
//	{OPM_ALL,	"help",		cli_table_time,	cmdHelp,	"Help",					"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,		cmdexit,	"Exit",					"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

//CliEntry cli_table_manuallydate[]= {
//	{OPM_ALL,	"date",		NULL,			cmddate,	"Date and time",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_manuallydate,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,			cmdautoexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

//CliEntry cli_table_automaticallydate[]= {
//	{OPM_ALL,	"tz",		NULL,				cmdtz,		"Time zone",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"ntpact",	NULL,				cmdntpact,	"NTP server active",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"ntpip",	NULL,				cmdntpip,	"NTP server IP",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_automaticallydate,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,				cmdautoexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdauto
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   ### leaf node and then non-leaf node
****************************************************************/
CliStatus cmdauto(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ntpclient.@ntpclient[0].TimeSettingMode";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Automatic, 0:Manual)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
		
		
		if (autosetbridge==-1 ){
			if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 1, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
				cliData->tokenLen-=2;
	  			return CLI_PARAMS_ERR;
			}
			
			strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
			
			if ( strcmp(uci_set_buf, "0")==0){
				
				cli_set_uci(func_buf, uci_set_buf);
				cliData->tokenLen--;
				
				//Handle the command --> mgmt/time>auto 0
				if (cmdtreelevel==2){
					autosetbridge=0;
					//prompt will be --> mgmt/time/auto>
					cmdtreelevel=cliData->tokenLen;
				}			
			
				return cmdHelp(cli_table_manuallydate,cliData);
			}
			if ( strcmp(uci_set_buf, "1")==0) {
				
				cli_set_uci(func_buf, uci_set_buf);
				cliData->tokenLen--;
				
				//Handle the command --> mgmt/time>auto 1
				if (cmdtreelevel==2){
					autosetbridge=1;
					//prompt will be --> mgmt/time/auto>
					cmdtreelevel=cliData->tokenLen;
				}
								
				return cmdHelp(cli_table_automaticallydate,cliData);	
			}
		}

		else if ( autosetbridge==1 )
			return getNextTable(cli_table_automaticallydate, cliData);
		else if ( autosetbridge==0 )
			return getNextTable(cli_table_manuallydate, cliData);
	}
	else if(cliData->argc>1){
		//handle absolute path
		if ( strcmp(cliData->tokens[3].token, "0")==0 ){
			cli_set_uci(func_buf, "0");

			cliData->argc--;
	
			return getNextTable(cli_table_manuallydate, cliData);
		}
		if ( strcmp(cliData->tokens[3].token, "1")==0 ){
			cli_set_uci(func_buf, "1");

			cliData->argc--;
	
			return getNextTable(cli_table_automaticallydate, cliData);
		}		

		if ( autosetbridge==1 )
			return getNextTable(cli_table_automaticallydate, cliData);
		else if ( autosetbridge==0 )
			return getNextTable(cli_table_manuallydate, cliData);
	}
}


/*****************************************************************
* NAME: cmddate
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddate(T_VOID* priv, CliData* cliData)
{
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_CHAR c1[255];
FILE *pp;

	if(cliData->argc==0){		
		if( (pp = popen("date", "r")) == NULL )
		{
			printf("popen() error!\n");
			exit(1);
		}
		fgets(uci_get_buf, sizeof uci_get_buf, pp);
		pclose(pp);
		uci_get_buf[strlen(uci_get_buf)-1]='\0';
		tprintf("Current setting: %s\n", uci_get_buf);
		tprintf("Recognized input format: YYYY.MM.DD-hh:mm    EX: 2012.05.20-09:55\n");
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid segmentation fault when the length of input > 255 
		if (!errorcheckStrLength( 20, cliData->tokens[cliData->tokenLen-1].token)){
			tprintf("The length of URL should not be larger than 20\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		sprintf(c1, "date -s %s", uci_set_buf);
		system(c1);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: displaytimezone
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_VOID displaytimezone(T_VOID) {
int i;
	for (i=0; i<41; i++){
		printf("%s - %s\n", CliTimezoneTable[i].item, CliTimezoneTable[i].timezoneName );

	}
}

/*****************************************************************
* NAME: searchtimezonetable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0515
* Modify:   
****************************************************************/
T_CHAR* searchtimezonetable(T_CHAR* code) {
int i;
int timezoneCount=41;
	for (i=0; i<timezoneCount; i++){
		if ( strcmp(code, CliTimezoneTable[i].timezoneCode)==0 )
			break;			
	}
	return CliTimezoneTable[i].timezoneName;
}

/*****************************************************************
* NAME: cmdtz
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdtz(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.@system[0].timezone";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
//T_CHAR retval[128];
//T_CHAR code_retval[128];
int retval_int;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displaytimezone();
		tprintf("Current setting: %s\n", searchtimezonetable(uci_get_buf));		
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 40, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		retval_int=atoi(uci_set_buf);
		cli_set_uci(func_buf, CliTimezoneTable[retval_int].timezoneCode);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdntpact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdntpact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ntpclient.@ntpclient[0].NTPSrvMode";
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
* NAME: cmdntpip
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdntpip(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ntpclient.@ntpserver[0].hostname";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

//Modify on 2012-12-14 by Philips which is requested by Jackey to support IPV4 and IPV6 address
T_INT32 rc4;
struct in6_addr octetstr_ipv6;
T_INT32 rc6;
struct in6_addr octetstr_ipv4;


	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);

//Modify on 2012-12-19 for IPV6 information of EAP600TRUE which is requested by Jacy
if ( strcmp(model_name, "ens202")==0 || strcmp(model_name, "ens202ext")==0 || strcmp(model_name, "eap600")==0 || strcmp(model_name, "all02860nd")==0 || strcmp(model_name, "ecb600")==0 || strcmp(model_name, "all02880nd")==0 || strcmp(model_name, "ens500")==0 || strcmp(model_name, "ens500ext")==0 || strcmp(model_name, "enh510")==0 )
	tprintf("Recognized input format:  IPv4 or IPv6 address    EX: 192.168.1.35 or 8E4A::4B\n");
else
	tprintf("Recognized input format:  IPv4 address    EX: 192.168.1.35\n");		

		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-10-26 requested by Talor to support IPV6 address
//		if( (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token ))&&(!errorcheckValidIPv6( cliData->tokens[cliData->tokenLen-1].token )) ){
//Modify on 2012-12-19 for IPV6 information of EAP600TRUE which is requested by Jacy
if ( strcmp(model_name, "ens202")==0 || strcmp(model_name, "ens202ext")==0 || strcmp(model_name, "eap600")==0 || strcmp(model_name, "all02860nd")==0 || strcmp(model_name, "ecb600")==0 || strcmp(model_name, "all02880nd")==0 || strcmp(model_name, "ens500")==0 || strcmp(model_name, "ens500ext")==0 || strcmp(model_name, "enh510")==0 ){
	//Modify on 2012-12-14 by Philips which is requested by Jackey to support IPV4 and IPV6 address
	rc4 = inet_pton(AF_INET, cliData->tokens[cliData->tokenLen-1].token, &octetstr_ipv4);
	rc6 = inet_pton(AF_INET6, cliData->tokens[cliData->tokenLen-1].token, &octetstr_ipv6);
	if( (rc4==0)&&(rc6==0) ){
		printf("\n\"%s\" is a invalid IPv4 or IPv6 address.\n", cliData->tokens[cliData->tokenLen-1].token);
	
//		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
	}
}
else{

	if( !errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token ) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
	}
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
* NAME: cmdautoexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdautoexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	autosetbridge=-1;
	
	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt time dlsave                       */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"time",		cli_table_time,		getNextTable,	"Time settings",		"", AUTH_ADMIN, MODEL_ALL},
//};

//static CliEntry cli_table_time[]= {
//	{OPM_ALL,	"auto",		NULL,   	cmdauto,	"Automatically get date and time",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"dlsave",	cli_table_daylight,	getNextTable,	"Daylight saving settings",
//	{OPM_ALL,	"help",		cli_table_time,	cmdHelp,	"Help",					"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,		cmdexit,	"Exit",					"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

//static CliEntry cli_table_daylight[]= {
//	{OPM_ALL,	"dlsact",	NULL,			cmddlsact,	"Daylight saving active",	"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"monthstart",	NULL,			cmdmonthstart,	"Month start time",		"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"weekstart",	NULL,			cmdweekstart,	"Week start time",		"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"daystart",	NULL,			cmddaystart,	"Day start time",		"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"hourstart",	NULL,			cmdhourstart,	"Hour start time",		"",     AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"monthend",	NULL,			cmdmonthend,	"Month end time",		"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"weekend",	NULL,			cmdweekend,	"Week end time",		"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"dayend",	NULL,			cmddayend,	"Day end time",			"",     AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"hourend",	NULL,			cmdhourend,	"Hour end time",		"",     AUTH_ADMIN, MODEL_ALL},		
//	{OPM_ALL,	"help",   	cli_table_daylight,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_TRUE},
//	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_TRUE},
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmddlsact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-12
* Modify:   
****************************************************************/
CliStatus cmddlsact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ntpclient.daylightsaving.DayLightEnable";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:Enable,0:Disable)\n", uci_get_buf);
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
* NAME: cmdmonthtime
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-12
* Modify:   
****************************************************************/
CliStatus cmdmonthtime(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ntpclient.daylightsaving.startMonth";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	//Get daylightsaving enable information
	strcpy(uci_get_buf, cli_get_uci("ntpclient.daylightsaving.DayLightEnable"));

	//If daylightsaving is disabled, please enable daylightsaving first
	if( atoi(uci_get_buf) == 0 ){
		printf("Daylight saving is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){
		//Check whether the command is "monthend" or not
		if ( strcmp(cliData->tokens[cliData->tokenLen-1].token, "monthend")==0 )
			strcpy(func_buf, "ntpclient.daylightsaving.endMonth");
			
		strcpy(uci_get_buf, cli_get_uci(func_buf));
/*		
		printf(" 1. January\n");
		printf(" 2. February\n");
		printf(" 3. March\n");
		printf(" 4. April\n");
		printf(" 5. May\n");
		printf(" 6. June\n");
		printf(" 7. July\n");
		printf(" 8. August\n");
		printf(" 9. September\n");
		printf("10. October\n");
		printf("11. November\n");
		printf("12. December\n");
*/						
		tprintf("Current setting: %s (1-12 Month)\n", uci_get_buf);
		tprintf("Recognized input format: (1:January,2:Feburary,...,11:November,12:December)\n");
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Check whether the command is "monthend" or not
		if ( strcmp(cliData->tokens[cliData->tokenLen-2].token, "monthend")==0 )
			strcpy(func_buf, "ntpclient.daylightsaving.endMonth");
			
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 12, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
* NAME: cmdweektime
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-12
* Modify:   
****************************************************************/
CliStatus cmdweektime(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ntpclient.daylightsaving.startWeek";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	//Get daylightsaving enable information
	strcpy(uci_get_buf, cli_get_uci("ntpclient.daylightsaving.DayLightEnable"));

	//If daylightsaving is disabled, please enable daylightsaving first
	if( atoi(uci_get_buf) == 0 ){
		printf("Daylight saving is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){
		//Check whether the command is "monthend" or not
		if ( strcmp(cliData->tokens[cliData->tokenLen-1].token, "weekend")==0 )
			strcpy(func_buf, "ntpclient.daylightsaving.endWeek");
			
		strcpy(uci_get_buf, cli_get_uci(func_buf));				
		tprintf("Current setting: %s (1-6 Week)\n", uci_get_buf);
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Check whether the command is "monthend" or not
		if ( strcmp(cliData->tokens[cliData->tokenLen-2].token, "weekend")==0 )
			strcpy(func_buf, "ntpclient.daylightsaving.endWeek");
			
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 6, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
* NAME: cmddaytime
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-12
* Modify:   
****************************************************************/
CliStatus cmddaytime(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ntpclient.daylightsaving.startDay";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	//Get daylightsaving enable information
	strcpy(uci_get_buf, cli_get_uci("ntpclient.daylightsaving.DayLightEnable"));

	//If daylightsaving is disabled, please enable daylightsaving first
	if( atoi(uci_get_buf) == 0 ){
		printf("Daylight saving is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){
		//Check whether the command is "monthend" or not
		if ( strcmp(cliData->tokens[cliData->tokenLen-1].token, "dayend")==0 )
			strcpy(func_buf, "ntpclient.daylightsaving.endDay");
			
		strcpy(uci_get_buf, cli_get_uci(func_buf));
/*		
		printf(" 0. Sun\n");
		printf(" 1. Mon\n");
		printf(" 2. Tue\n");
		printf(" 3. Wed\n");
		printf(" 4. Thu\n");
		printf(" 5. Fri\n");
		printf(" 6. Sat\n");				
*/
		tprintf("Current setting: %s (0-6 Day)\n", uci_get_buf);
		tprintf("Recognized input format: (0:Sun,1:Mon,2:Tue,3:Wed,4:Thu,5:Fri,6:Sat)\n");		
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Check whether the command is "monthend" or not
		if ( strcmp(cliData->tokens[cliData->tokenLen-2].token, "dayend")==0 )
			strcpy(func_buf, "ntpclient.daylightsaving.endDay");
			
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 6, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
* NAME: cmdhourtime
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-12
* Modify:   
****************************************************************/
CliStatus cmdhourtime(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="ntpclient.daylightsaving.startHour";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	//Get daylightsaving enable information
	strcpy(uci_get_buf, cli_get_uci("ntpclient.daylightsaving.DayLightEnable"));

	//If daylightsaving is disabled, please enable daylightsaving first
	if( atoi(uci_get_buf) == 0 ){
		printf("Daylight saving is disabled, please enable it first!\n\n");
		if(cliData->argc==0){
			cliData->tokenLen--;
			return CLI_NOTHING;
		}
		if(cliData->argc>1)
			return CLI_NO_MATCH;
	}

	if(cliData->argc==0){
		//Check whether the command is "monthend" or not
		if ( strcmp(cliData->tokens[cliData->tokenLen-1].token, "hourend")==0 )
			strcpy(func_buf, "ntpclient.daylightsaving.endHour");
			
		strcpy(uci_get_buf, cli_get_uci(func_buf));
/*		
		printf(" 0. 12 am\n");
		printf(" 1.  1 am\n");
		printf(" 2.  2 am\n");
		printf(" 3.  3 am\n");
		printf(" 4.  4 am\n");
		printf(" 5.  5 am\n");
		printf(" 6.  6 am\n");
		printf(" 7.  7 am\n");
		printf(" 8.  8 am\n");
		printf(" 9.  9 am\n");
		printf("10. 10 am\n");
		printf("11. 11 am\n");
		printf("12. 12 pm\n");
		printf("13.  1 pm\n");
		printf("14.  2 pm\n");
		printf("15.  3 pm\n");
		printf("16.  4 pm\n");
		printf("17.  5 pm\n");
		printf("18.  6 pm\n");
		printf("19.  7 pm\n");
		printf("20.  8 pm\n");
		printf("21.  9 pm\n");
		printf("22. 10 pm\n");
		printf("23. 11 pm\n");
*/									
		tprintf("Current setting: %s (0-23 Hour)\n", uci_get_buf);
		tprintf("Recognized input format: (0:12am,1:1am,...,11:11am,12:12pm,13:1pm,...,22:10pm,23:11pm)\n");
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Check whether the command is "monthend" or not
		if ( strcmp(cliData->tokens[cliData->tokenLen-2].token, "hourend")==0 )
			strcpy(func_buf, "ntpclient.daylightsaving.endHour");
			
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 23, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
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
/*                   CLI Command -- mgmt wifisch                           */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"wifisch",	cli_table_wifischedule,	getNextTable,	"Wfi schedule",	"",	AUTH_ANY, MODEL_ALL},
//};

//static CliEntry cli_table_wifischedule[]= {
//	{OPM_ALL,	"wslist",	NULL,			cmdwslist,	"Display wifi schedule list",	"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"wsact",	NULL, 	   		cmdwsact,	"wifi schedule active",		"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"wsadd",	cli_table_wsadd,     	getNextTable,	"wifi schedule add",		"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL, 	"wsdel",	NULL,                   cmdwsdel,	"wifi schedule delete",		"", 	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_wifischedule,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_TRUE},
//	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_TRUE},
//	{ CMD_END_TAG}
//};

//static CliEntry cli_table_wsadd[]= {
//	{OPM_ALL,	"setname",	NULL,			cmdsetwsname,		"Set wifi schedule name",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"setwp",  	NULL,			cmdsetwswp,		"Set wireless power",		"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"setday",  	NULL,			cmdsetwsday,		"Set day",			"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"setmin",  	NULL,			cmdsetwsmin,		"Set minute",			"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"setsec",  	NULL,			cmdsetwssec,		"Set second",			"", 	AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"accept",  	NULL,			cmdwsaccept,		"Accept wifi schedule setting",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_wsadd,	cmdHelp,		"Help",				"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdwifischeduleexit,    "Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

/*****************************************************************
* NAME: displayWifiScheduledata
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-15
* Modify:   
****************************************************************/
T_VOID displayWifiScheduledata(T_INT32 wifischedulenumber) {
T_INT32 i;
T_CHAR uci_get_buf[128];
T_CHAR c1[255];
T_CHAR power[32];
T_CHAR on[8];
T_CHAR* token1;
T_CHAR* token2;
T_CHAR* token3;
T_CHAR* token4;
T_CHAR* token5;

	if (wifischedulenumber>0){
		tprintf("Index -        Name           Service       Schedule   \n");
		tprintf("-------------------------------------------------------\n");
		
		for (i=1; i<=wifischedulenumber; i++){
			sprintf(c1, "schedule.wifi.ScheduleList%d", i);
			strcpy(uci_get_buf, cli_get_uci(c1));

			token1 = strtok(uci_get_buf, ",");
			token2 = strtok(NULL, ",");
			token3 = strtok(NULL, ",");
			token4 = strtok(NULL, ",");
			token5 = strtok(NULL, ",");
			
			sprintf(on, "%s", token1+6);
			
			if( atoi(on)==1 )
				strcpy(power, "Wireless Power ON");
			else
				strcpy(power, "Wireless Power OFF");
					
			tprintf("%5d - %10s , %20s,   %s:%s--%s\n", i, token5+5, power, token3+5, token4+4, token2+4);	
		}
		tprintf("\n");
	}
}

/*****************************************************************
* NAME: cmdwslist
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-15
* Modify:   
****************************************************************/
CliStatus cmdwslist(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="schedule.wifi.ScheduleNum";
T_CHAR uci_get_buf[128];

	if(cliData->argc==0){		

		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		displayWifiScheduledata( atoi(uci_get_buf) );
			
		if (atoi(uci_get_buf)==0)
			tprintf("Wifi Schedule list is empty.\n\n");
		
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwsact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-15
* Modify:   
****************************************************************/
CliStatus cmdwsact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="schedule.wifi.ScheduleEnable";
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
		
printf("schedule.wifi.ScheduleEnable=%s\n", uci_set_buf);		
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwsdel
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-15
* Modify:   
****************************************************************/
CliStatus cmdwsdel(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="schedule.wifi.ScheduleNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;
T_CHAR c1[255];
FILE *pp;
T_INT32 i;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displayWifiScheduledata( atoi(uci_get_buf) );
    		
    		if (atoi(uci_get_buf)>0){
    			tprintf("Recognized input format: ");
    			for (i=1; i<atoi(uci_get_buf); i++)
    				tprintf("%d, ", i);
    			tprintf("%d\n", i);
    		}
    		else
    			tprintf("Wifi Schedule list is empty.\n");

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
		
		sprintf(c1, "uci delete schedule.wifi.ScheduleList%d", retval_int);
  		system(c1);
  		system("uci commit");
	
		for (i=retval_int+1; i<=atoi(uci_get_buf); i++){
   			sprintf(c1, "sed -i \'s/ScheduleList%d/ScheduleList%d/g\' /etc/config/schedule", i, i-1);
			system(c1);
		}
			
		sprintf(c1, "uci set schedule.wifi.ScheduleNum=\'%d\'", atoi(uci_get_buf)-1);
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
* NAME: cmdsetwsname
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-15
* Modify:   
****************************************************************/
CliStatus cmdsetwsname(T_VOID* priv, CliData* cliData)
{
	if(cliData->argc==0){
    		tprintf("Recognized input format:    (16 characters at most).  EX: John\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		if (!errorcheckStrLength( 16, cliData->tokens[cliData->tokenLen-1].token) ){
			tprintf("The length of service name should not be larger than 16\n");
			cliData->tokenLen-=2;
			return CLI_PARAMS_ERR;
		}
		
		strcpy(CliWifiSchedule.servicename, cliData->tokens[cliData->tokenLen-1].token);

//printf("CliWifiSchedule.servicename=%s\n", CliWifiSchedule.servicename);
			
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsetwswp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-15
* Modify:   
****************************************************************/
CliStatus cmdsetwswp(T_VOID* priv, CliData* cliData)
{
	if(cliData->argc==0){
		tprintf("Recognized input format: (1:Power ON, 0:Power OFF)\n");
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
	
		strcpy(CliWifiSchedule.wirelesspower, cliData->tokens[cliData->tokenLen-1].token);

//printf("CliWifiSchedule.wirelesspower=%s\n", CliWifiSchedule.wirelesspower);
	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsetwsday
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-15
* Modify:   
****************************************************************/
CliStatus cmdsetwsday(T_VOID* priv, CliData* cliData)
{
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){
		tprintf("Recognized input format: (0:Sun,1:Mon,2:Tue,3:Wed,4:Thu,5:Fri,6:Sat)\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 6, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
	
		switch( atoi(cliData->tokens[cliData->tokenLen-1].token) ){
			case 0:
				strcpy(CliWifiSchedule.day, "Sun");
				break;
			case 1:
				strcpy(CliWifiSchedule.day, "Mon");
				break;
			case 2:
				strcpy(CliWifiSchedule.day, "Tue");
				break;
			case 3:
				strcpy(CliWifiSchedule.day, "Wed");
				break;
			case 4:
				strcpy(CliWifiSchedule.day, "Thu");
				break;
			case 5:
				strcpy(CliWifiSchedule.day, "Fri");
				break;
			case 6:
				strcpy(CliWifiSchedule.day, "Sat");
				break;											
		}

//printf("CliWifiSchedule.day=%s\n", CliWifiSchedule.day);
	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsetwshour
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-15
* Modify:   
****************************************************************/
CliStatus cmdsetwshour(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){
		tprintf("Recognized input format: (00-23 Hour)\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 23, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		if ( strlen(cliData->tokens[cliData->tokenLen-1].token)==1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "0%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );
	
		CliWifiSchedule.hourset=1;
		strcpy(CliWifiSchedule.hour, cliData->tokens[cliData->tokenLen-1].token);
//printf("CliWifiSchedule.hour=%s\n", CliWifiSchedule.hour);
	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsetwsmin
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-15
* Modify:   
****************************************************************/
CliStatus cmdsetwsmin(T_VOID* priv, CliData* cliData)
{
	if(cliData->argc==0){
		tprintf("Recognized input format: (00-59 Minute)\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 59, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
	
		
		if ( strlen(cliData->tokens[cliData->tokenLen-1].token)==1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "0%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		CliWifiSchedule.minuteset=1;
		strcpy(CliWifiSchedule.minute, cliData->tokens[cliData->tokenLen-1].token);
//printf("CliWifiSchedule.minute=%s\n", CliWifiSchedule.minute);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwsaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-15
* Modify:   
****************************************************************/
CliStatus cmdwsaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="schedule.wifi.ScheduleNum";
T_CHAR uci_get_buf[128];
T_CHAR c1[255];

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		if (CliWifiSchedule.hourset==0){
			tprintf("You forget to set hour\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		if (CliWifiSchedule.minuteset==0){
			tprintf("You forget to set minute\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
						
		sprintf(c1,"uci set schedule.wifi.ScheduleNum=%d", atoi(uci_get_buf)+1);
		system(c1);
		sprintf(c1,"uci set schedule.wifi.ScheduleList%d=power:%s,day:%s,hour:%s,min:%s,name:%s"
	  	,atoi(uci_get_buf)+1
	  	,CliWifiSchedule.wirelesspower
	  	,CliWifiSchedule.day
	  	,CliWifiSchedule.hour
	   	,CliWifiSchedule.minute
	   	,CliWifiSchedule.servicename
	   	);
	   	system(c1);
		system("uci commit");
		

		CliWifiSchedule.hourset=0;
		CliWifiSchedule.minuteset=0;
		strcpy(CliWifiSchedule.servicename, "");
		strcpy(CliWifiSchedule.wirelesspower, "1");
		strcpy(CliWifiSchedule.day, "Mon");		
		strcpy(CliWifiSchedule.hour, "");		
		strcpy(CliWifiSchedule.minute, "");
						
		displayWifiScheduledata( atoi(uci_get_buf)+1 );
		
		cliData->tokenLen--;
		return CLI_OK;

	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwifischeduleexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2012-11-15
* Modify:   
****************************************************************/
CliStatus cmdwifischeduleexit(T_VOID* priv, CliData* cliData)
{
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;

	CliWifiSchedule.hourset=0;
	CliWifiSchedule.minuteset=0;
	strcpy(CliWifiSchedule.servicename, "");
	strcpy(CliWifiSchedule.wirelesspower, "1");
	strcpy(CliWifiSchedule.day, "Mon");		
	strcpy(CliWifiSchedule.hour, "");		
	strcpy(CliWifiSchedule.minute, "");

	//go back to previous level of directory EX:eap600/sys/ip>exit -> eap600/sys>
	//eap600/sys/ip>exit (cliData->tokenLen is 3)
	//eap600/sys> (cliData->tokenLen is 1)
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt wifisch                           */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"wsch",	cli_table_wifischedule,	getNextTable,	"Wfi schedule",	"",	AUTH_ANY, MODEL_ALL},
//};

//static CliEntry cli_table_dualwifischedule[]= {
//	{OPM_ALL,	"wslist",	NULL,				cmddualwslist,	"Display wifi schedule list",	"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"wsact",	NULL, 	   			cmdwsact,	"wifi schedule active",		"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"wsadd",	cli_table_dualwsadd,     	getNextTable,	"wifi schedule add",		"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL, 	"wsdel",	NULL,                   	cmddualwsdel,	"wifi schedule delete",		"", 	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_dualwifischedule,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,				cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

//static CliEntry cli_table_dualwsadd[]= {
//	{OPM_ALL,	"setname",	NULL,			cmdsetwsname,		"Set wifi schedule name",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"setsvc",  	NULL,			cmdsetwssvc,		"Set service",			"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"setdays",  	NULL,			cmdsetdualwsday,	"Set day",			"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"setshour",  	NULL,			cmdsetdualwshour,	"Set start hour",		"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"setsmin",  	NULL,			cmdsetdualwsmin,	"Set start minute",		"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"setehour",  	NULL,			cmdsetdualwshour,	"Set end hour",			"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"setemin",  	NULL,			cmdsetdualwsmin,	"Set end minute",		"", 	AUTH_ADMIN, MODEL_ALL},		
//	{OPM_ALL,	"accept",  	NULL,			cmddualwsaccept,	"Accept wifi schedule setting",	"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_dualwsadd,	cmdHelp,		"Help",				"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmddualwifischeduleexit,    "Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG }
//};

/*****************************************************************
* NAME: cmddualwslist
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Modifyby Philips on 2012-12-03 for function alignment of Wifi schedule to dual radio models 
* Modify:   
****************************************************************/
CliStatus cmddualwslist(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="schedule.wifi.ScheduleNum";
T_CHAR uci_get_buf[128];

	if(cliData->argc==0){		

		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		displaydualWifiScheduledata( atoi(uci_get_buf) );
			
		if (atoi(uci_get_buf)==0)
			tprintf("Wifi Schedule list is empty.\n\n");
		
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmddualwsdel
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Modifyby Philips on 2012-12-03 for function alignment of Wifi schedule to dual radio models 
* Modify:   
****************************************************************/
CliStatus cmddualwsdel(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="schedule.wifi.ScheduleNum";
T_CHAR uci_get_buf[16];
T_CHAR uci_set_buf[128];
T_INT32 retval_int;
T_CHAR c1[255];
FILE *pp;
T_INT32 i;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		displaydualWifiScheduledata( atoi(uci_get_buf) );
    		
    		if (atoi(uci_get_buf)>0){
    			tprintf("Recognized input format: ");
    			for (i=1; i<atoi(uci_get_buf); i++)
    				tprintf("%d, ", i);
    			tprintf("%d\n", i);
    		}
    		else
    			tprintf("Wifi Schedule list is empty.\n");

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
		
		sprintf(c1, "uci delete schedule.wifi.ScheduleList%d", retval_int);
  		system(c1);
  		system("uci commit");
	
		for (i=retval_int+1; i<=atoi(uci_get_buf); i++){
   			sprintf(c1, "sed -i \'s/ScheduleList%d/ScheduleList%d/g\' /etc/config/schedule", i, i-1);
			system(c1);
		}
			
		sprintf(c1, "uci set schedule.wifi.ScheduleNum=\'%d\'", atoi(uci_get_buf)-1);
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
* NAME: cmdsetwssvc
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Modifyby Philips on 2012-12-03 for function alignment of Wifi schedule to dual radio models 
* Modify:   
****************************************************************/
CliStatus cmdsetwssvc(T_VOID* priv, CliData* cliData)
{
	if(cliData->argc==0){


//Modifyby Po-yao on 2013-10-28 for function alignment of Wifi schedule to EAP300V2, EAP350 and ECB350
if ( strcmp(model_name, "eap300v2")==0 || strcmp(model_name, "eap350")==0 || strcmp(model_name, "ecb350")==0 ){
	tprintf("1. Reboot\n2. Wireless Active (2G)\n");
	tprintf("Recognized input format: 1, 2\n");
}
else{
			tprintf("1. Reboot\n2. Wireless Active (2G)\n3. Wireless Active (5G)\n4. Wireless Active (Both)\n");
			tprintf("Recognized input format: 1, 2, 3, 4\n");
}


    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

			
//Modifyby Po-yao on 2013-10-28 for function alignment of Wifi schedule to EAP300V2, EAP350 and ECB350
if ( strcmp(model_name, "eap300v2")==0 || strcmp(model_name, "eap350")==0 || strcmp(model_name, "ecb350")==0 ){
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 2, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
}
else{
		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 4, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
}

		switch( atoi(cliData->tokens[cliData->tokenLen-1].token) ){
			case 1:
				strcpy(CliWifiSchedule.service, "reboot");
				break;
			case 2:
				strcpy(CliWifiSchedule.service, "wifi_2G");
				break;
			case 3:
				strcpy(CliWifiSchedule.service, "wifi_5G");
				break;
			case 4:
				strcpy(CliWifiSchedule.service, "wifi_both");
				break;
								
		}	

//printf("CliWifiSchedule.service=%s\n", CliWifiSchedule.service);
	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsetdualwsday
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Modifyby Philips on 2012-12-03 for function alignment of Wifi schedule to dual radio models 
* Modify:   
****************************************************************/
CliStatus cmdsetdualwsday(T_VOID* priv, CliData* cliData)
{
T_CHAR uci_set_buf[128];
T_INT32 i;

	if(cliData->argc==0){
	
		tprintf("Current setting: ");
		for (i=0; i<7; i++)
			switch( i ){
			case 0:
				if ( CliWifiSchedule.dualdays[i]==1)
					printf("Mon, ");
				break;
			case 1:
				if ( CliWifiSchedule.dualdays[i]==1)
					printf("Tue, ");
				break;
			case 2:
				if ( CliWifiSchedule.dualdays[i]==1)
					printf("Wed, ");
				break;
			case 3:
				if ( CliWifiSchedule.dualdays[i]==1)
					printf("Thu, ");
				break;
			case 4:
				if ( CliWifiSchedule.dualdays[i]==1)
					printf("Fri, ");
				break;
			case 5:
				if ( CliWifiSchedule.dualdays[i]==1)
					printf("Sat, ");
				break;
			case 6:
				if ( CliWifiSchedule.dualdays[i]==1)
					printf("Sun");
				break;											
		}
		tprintf("\n");
	 	tprintf("0. Every Day\n1. Mon\n2. Tue\n3. Wed\n4. Thu\n5. Fri\n6. Sat\n7. Sun\n");
		tprintf("Recognized input format: 0, 1, 2, 3, 4, 5, 6, 7\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 7, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
	
		switch( atoi(cliData->tokens[cliData->tokenLen-1].token) ){
			case 0:
				for (i=0; i<7; i++)
					CliWifiSchedule.dualdays[i]=1;
				CliWifiSchedule.dualdaysset=1;
				break;
			case 1:
				CliWifiSchedule.dualdays[0]=1;
				CliWifiSchedule.dualdaysset=1;
				break;
			case 2:
				CliWifiSchedule.dualdays[1]=1;
				CliWifiSchedule.dualdaysset=1;
				break;
			case 3:
				CliWifiSchedule.dualdays[2]=1;
				CliWifiSchedule.dualdaysset=1;
				break;
			case 4:
				CliWifiSchedule.dualdays[3]=1;
				CliWifiSchedule.dualdaysset=1;
				break;
			case 5:
				CliWifiSchedule.dualdays[4]=1;
				CliWifiSchedule.dualdaysset=1;
				break;
			case 6:
				CliWifiSchedule.dualdays[5]=1;
				CliWifiSchedule.dualdaysset=1;
				break;
			case 7:
				CliWifiSchedule.dualdays[6]=1;
				CliWifiSchedule.dualdaysset=1;
				break;											
		}

//for(i=0; i<7; i++)
//	printf("CliWifiSchedule.dualdays[%d]=%d\n", i, CliWifiSchedule.dualdays[i]);
	
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsetdualwshour
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Modifyby Philips on 2012-12-03 for function alignment of Wifi schedule to dual radio models 
* Modify:   
****************************************************************/
CliStatus cmdsetdualwshour(T_VOID* priv, CliData* cliData)
{

if ( strcmp(CliWifiSchedule.service, "reboot")==0 )
	if ( strcmp(cliData->tokens[cliData->tokenLen-1].token, "setehour")==0 || strcmp(cliData->tokens[cliData->tokenLen-2].token, "setehour")==0 ){	
		printf("You don't need to set end hour when Service is reboot\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;	
	}
	if(cliData->argc==0){
		tprintf("Recognized input format: (00-23 Hour)\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 23, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		if ( strlen(cliData->tokens[cliData->tokenLen-1].token)==1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "0%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

if ( strcmp(cliData->tokens[cliData->tokenLen-2].token, "setshour")==0 ){	
	CliWifiSchedule.shourset=1;
	strcpy(CliWifiSchedule.shour, cliData->tokens[cliData->tokenLen-1].token);
//printf("CliWifiSchedule.shour=%s\n", CliWifiSchedule.shour);
	
	if ( strcmp(CliWifiSchedule.service, "reboot")==0 ){
		CliWifiSchedule.ehourset=1;
		strcpy(CliWifiSchedule.ehour, cliData->tokens[cliData->tokenLen-1].token);
//printf("CliWifiSchedule.ehour=%s\n", CliWifiSchedule.ehour);
	}
}
if ( strcmp(cliData->tokens[cliData->tokenLen-2].token, "setehour")==0 ){	
		CliWifiSchedule.ehourset=1;
		strcpy(CliWifiSchedule.ehour, cliData->tokens[cliData->tokenLen-1].token);
//printf("CliWifiSchedule.ehour=%s\n", CliWifiSchedule.ehour);
}

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsetdualwsmin
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Modifyby Philips on 2012-12-03 for function alignment of Wifi schedule to dual radio models 
* Modify:   
****************************************************************/
CliStatus cmdsetdualwsmin(T_VOID* priv, CliData* cliData)
{

if ( strcmp(CliWifiSchedule.service, "reboot")==0 )
	if ( strcmp(cliData->tokens[cliData->tokenLen-1].token, "setemin")==0 || strcmp(cliData->tokens[cliData->tokenLen-2].token, "setemin")==0 ){
		printf("You don't need to set end minute when Service is reboot\n");
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
		
	if(cliData->argc==0){
		tprintf("Recognized input format: (00-59 Minute)\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){
		//Modify on 2012-08-01 to avoid leading zero in input EX:00016->16
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='0' && strlen(cliData->tokens[cliData->tokenLen-1].token)>1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 0, 59, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
	
		
		if ( strlen(cliData->tokens[cliData->tokenLen-1].token)==1 )
			sprintf(cliData->tokens[cliData->tokenLen-1].token, "0%d", atoi(cliData->tokens[cliData->tokenLen-1].token) );

if ( strcmp(cliData->tokens[cliData->tokenLen-2].token, "setsmin")==0 ){	
	CliWifiSchedule.sminuteset=1;
	strcpy(CliWifiSchedule.sminute, cliData->tokens[cliData->tokenLen-1].token);
//printf("CliWifiSchedule.sminute=%s\n", CliWifiSchedule.sminute);
	
	if ( strcmp(CliWifiSchedule.service, "reboot")==0 ){
		CliWifiSchedule.eminuteset=1;
		strcpy(CliWifiSchedule.eminute, cliData->tokens[cliData->tokenLen-1].token);
//printf("CliWifiSchedule.ehour=%s\n", CliWifiSchedule.ehour);
	}
}
if ( strcmp(cliData->tokens[cliData->tokenLen-2].token, "setemin")==0 ){	
	CliWifiSchedule.eminuteset=1;
	strcpy(CliWifiSchedule.eminute, cliData->tokens[cliData->tokenLen-1].token);
//printf("CliWifiSchedule.eminute=%s\n", CliWifiSchedule.eminute);
}

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: displaydualWifiScheduledata
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Modifyby Philips on 2012-12-03 for function alignment of Wifi schedule to dual radio models 
* Modify:   
****************************************************************/
T_VOID displaydualWifiScheduledata(T_INT32 wifischedulenumber) {
T_INT32 i;
T_CHAR uci_get_buf[128];
T_CHAR c1[255];
T_CHAR power[32];
T_CHAR* token1;
T_CHAR* token2;
T_CHAR* token3;
T_CHAR* token4;
T_CHAR* token5;
T_CHAR* token6;
T_CHAR* token7;

	if (wifischedulenumber>0){
		tprintf("Index -        Name     Service             Schedule   \n");
		tprintf("--------------------------------------------------------------\n");
		
		for (i=1; i<=wifischedulenumber; i++){
			sprintf(c1, "schedule.wifi.ScheduleList%d", i);
			strcpy(uci_get_buf, cli_get_uci(c1));

			token1 = strtok(uci_get_buf, ",");
			token2 = strtok(NULL, ",");
			token3 = strtok(NULL, ",");
			token4 = strtok(NULL, ",");
			token5 = strtok(NULL, ",");
			token6 = strtok(NULL, ",");
			token7 = strtok(NULL, ",");
					
			tprintf("%5d - %10s , %11s,   %s:%s to %s:%s--%s\n", i, token7+5, token1+8, token3+7, token4+6, token5+7, token6+6, token2+4);	
		}
		tprintf("\n");
	}
}

/*****************************************************************
* NAME: cmddualwsaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Modifyby Philips on 2012-12-03 for function alignment of Wifi schedule to dual radio models 
* Modify:   
****************************************************************/
CliStatus cmddualwsaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="schedule.wifi.ScheduleNum";
T_CHAR uci_get_buf[128];
T_CHAR days_buf[128]="";
T_CHAR c1[255];
T_INT32 i;
T_INT32 head=0;

	if(cliData->argc==0){
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		
		if (CliWifiSchedule.dualdaysset==0){
			tprintf("Please select at least one day\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		if (CliWifiSchedule.shourset==0){
			tprintf("You forget to set start hour\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		if (CliWifiSchedule.sminuteset==0){
			tprintf("You forget to set start minute\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		if (CliWifiSchedule.ehourset==0){
			tprintf("You forget to set end hour\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		if (CliWifiSchedule.eminuteset==0){
			tprintf("You forget to set end minute\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}
		if ( (atoi(CliWifiSchedule.shour)>atoi(CliWifiSchedule.ehour)) ||
			((atoi(CliWifiSchedule.shour)==atoi(CliWifiSchedule.ehour)) && (atoi(CliWifiSchedule.sminute)>atoi(CliWifiSchedule.eminute))) ){
			tprintf("Start time should be less than end time\n");
			cliData->tokenLen--;
			return CLI_PARAMS_ERR;
		}				
		sprintf(c1,"uci set schedule.wifi.ScheduleNum=%d", atoi(uci_get_buf)+1);
		system(c1);
		
		for(i=0; i<7; i++)
			switch( i ){
			case 0:
				if ( CliWifiSchedule.dualdays[i]==1 ){
					strcat(days_buf, "Mon");
					head=1;
				}
				break;
			case 1:
				if ( CliWifiSchedule.dualdays[i]==1 )
					if ( head==0 ){
						strcat(days_buf, "Tue");
						head=1;
					}
					else
						strcat(days_buf, " Tue");
				break;
			case 2:
				if ( CliWifiSchedule.dualdays[i]==1 )
					if ( head==0 ){
						strcat(days_buf, "Wed");
						head=1;
					}
					else
						strcat(days_buf, " Wed");
				break;
			case 3:
				if ( CliWifiSchedule.dualdays[i]==1 )
					if ( head==0 ){
						strcat(days_buf, "Thu");
						head=1;
					}
					else
						strcat(days_buf, " Thu");
				break;
			case 4:
				if ( CliWifiSchedule.dualdays[i]==1 )
					if ( head==0 ){
						strcat(days_buf, "Fri");
						head=1;
					}
					else
						strcat(days_buf, " Fri");
				break;
			case 5:
				if ( CliWifiSchedule.dualdays[i]==1 )
					if ( head==0 ){
						strcat(days_buf, "Sat");
						head=1;
					}
					else
						strcat(days_buf, " Sat");
				break;
			case 6:
				if ( CliWifiSchedule.dualdays[i]==1 )
					if ( head==0 ){
						strcat(days_buf, "Sun");
						head=1;
					}
					else
						strcat(days_buf, " Sun");											
		}
			
		sprintf(c1,"uci set schedule.wifi.ScheduleList%d=\"Service:%s,day:%s,s_hour:%s,s_min:%s,e_hour:%s,e_min:%s,name:%s\""
	  	,atoi(uci_get_buf)+1
	  	,CliWifiSchedule.service
	  	,days_buf
	  	,CliWifiSchedule.shour
	   	,CliWifiSchedule.sminute
	  	,CliWifiSchedule.ehour
	   	,CliWifiSchedule.eminute
	   	,CliWifiSchedule.servicename
	   	);

	   	system(c1);
		system("uci commit");
		
		CliWifiSchedule.dualdaysset=0;
		CliWifiSchedule.shourset=0;
		CliWifiSchedule.sminuteset=0;
		CliWifiSchedule.ehourset=0;
		CliWifiSchedule.eminuteset=0;
		strcpy(CliWifiSchedule.servicename, "");
		strcpy(CliWifiSchedule.service, "reboot");
		for(i=0; i<7; i++)
			CliWifiSchedule.dualdays[i]=0;
		
		strcpy(CliWifiSchedule.shour, "");		
		strcpy(CliWifiSchedule.sminute, "");
		strcpy(CliWifiSchedule.ehour, "");		
		strcpy(CliWifiSchedule.eminute, "");
								
		displaydualWifiScheduledata( atoi(uci_get_buf)+1 );
		
		cliData->tokenLen--;
		return CLI_OK;

	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmddualwifischeduleexit
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Modifyby Philips on 2012-12-03 for function alignment of Wifi schedule to dual radio models 
* Modify:   
****************************************************************/
CliStatus cmddualwifischeduleexit(T_VOID* priv, CliData* cliData)
{
T_INT32 i;
	//Modify on 2012-08-03 to prevent "exit" command having any argument
	if (cliData->argc>0)
		return CLI_NO_MATCH;


	CliWifiSchedule.dualdaysset=0;
	CliWifiSchedule.shourset=0;
	CliWifiSchedule.sminuteset=0;
	CliWifiSchedule.ehourset=0;
	CliWifiSchedule.eminuteset=0;
	
	strcpy(CliWifiSchedule.servicename, "");
	strcpy(CliWifiSchedule.service, "reboot");
	for(i=0; i<7; i++)
		CliWifiSchedule.dualdays[i]=0;
	strcpy(CliWifiSchedule.shour, "");		
	strcpy(CliWifiSchedule.sminute, "");
	strcpy(CliWifiSchedule.ehour, "");		
	strcpy(CliWifiSchedule.eminute, "");
		
	cliData->tokenLen -= 2;
  	
	return CLI_NOTHING;
}


/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt wifisch                           */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"wifisch",	cli_table_newwifischedule, 	getNextTable, "Wifi schedule",	"", AUTH_ANY, EAP900H_ID|EAP900H_ID|EAP900_ID|C600_ID},	
//};

//static CliEntry cli_table_newwifischedule[]= {
//	{OPM_ALL,	"wsact",	NULL,				cmdnewwsact,	"Wifi Schedule active",		"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"wsradio",	NULL, 	   			cmdwsradio,	"Wireless Radio",		"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"wsssid",	NULL,     			cmdwsssid,	"SSID selection",		"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL, 	"wstemp",	NULL,                   	cmdwstemp,	"Schedule templates",		"", 	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL, 	"wscustom",	cli_table_customerschedule,    	getNextTable,	"Customer Schedule",		"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_newwifischedule,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,				cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};


/*****************************************************************
* NAME: cmdnewwsact
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-10
* Modify:   
****************************************************************/
CliStatus cmdnewwsact(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wirelessAvailability.wireless.ScheduleEnable";
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
* NAME: cmdwsradio
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-10
* Modify:   
****************************************************************/
CliStatus cmdwsradio(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wirelessAvailability.wireless.radio";
T_CHAR func_buf1[128]="wirelessAvailability.wireless.iface";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s (1:5GHz, 0:2.4GHz)\n", uci_get_buf);
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

		//Get the information of ath interface
		strcpy(uci_get_buf, cli_get_uci(func_buf1));
		//Make sure that interface of 2.4G is ath0 - ath7
		if ( atoi(uci_set_buf)==0 && atoi(uci_get_buf+3) > 50)
			cli_set_uci(func_buf1, "ath0");
		//Make sure that interface of 5G is ath50 - ath57
		if ( atoi(uci_set_buf)==1 && atoi(uci_get_buf+3) < 8)
			cli_set_uci(func_buf1, "ath50");
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwsssid
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-10
* Modify:   
****************************************************************/
CliStatus cmdwsssid(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wirelessAvailability.wireless.radio";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

T_INT32 radio;
T_INT32 i;
T_INT32 j=1;
T_INT32 wifi_index=0;
T_INT32 ssidCount=8;

	//Get the information of radio (1:5GHz, 0:2.4GHz)
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	radio = atoi(uci_get_buf);
	if ( radio==1 )
		wifi_index=26;
	
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

		if (!errorcheckValidDecimal(cliData->tokens[cliData->tokenLen-1].token) || !errorcheckIntRange( 1, 8, atoi(cliData->tokens[cliData->tokenLen-1].token)) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		strcpy(uci_set_buf, cliData->tokens[cliData->tokenLen-1].token);
		
		//Make sure that interface of 2.4G is ath0 - ath7
		if ( radio==0 )
			sprintf(uci_set_buf, "ath%d", 0+atoi(uci_set_buf)-1);
		//Make sure that interface of 5G is ath50 - ath57
		if ( radio==1 )
			sprintf(uci_set_buf, "ath%d", 50+atoi(uci_set_buf)-1);
			
		cli_set_uci("wirelessAvailability.wireless.iface", uci_set_buf);		
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: WifiTemplatesProcess
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-18
* Modify:   
****************************************************************/
T_VOID WifiTemplatesProcess(T_INT32 item)
{
T_CHAR func_buf[128]="wirelessAvailability.wireless.iface";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];
T_INT32 day;

	//Get the information of ath interface
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	
	if (item == 1) { //1 - Always available
		sprintf(uci_set_buf, "schedule -t 5 -m wirelessAvailability.wifitbl -v \"'','','','','','%s'\" -d  > /dev/null 2>&1", uci_get_buf);
		system(uci_set_buf);
	}
	else if (item == 2) { //2 - Available 8-5 Daily
		for ( day=0; day<7; day++ ){
			sprintf(uci_set_buf, "schedule -t 3 -m wirelessAvailability.wifitbl -v \"'','%d','08:00','17:00','1','%s'\" > /dev/null 2>&1", day, uci_get_buf);
			system(uci_set_buf);
		}
	}
	else if (item == 3) { //3 - Available 8-5 Daily except weekends
		for ( day=0; day<7; day++ ){
			if ( day == 0 || day == 6 ){
				sprintf(uci_set_buf, "schedule -t 3 -m wirelessAvailability.wifitbl -v \"'','%d','00:00','24:00','0','%s'\" > /dev/null 2>&1", day, uci_get_buf);
				system(uci_set_buf);			}
			else {
				sprintf(uci_set_buf, "schedule -t 3 -m wirelessAvailability.wifitbl -v \"'','%d','08:00','17:00','1','%s'\" > /dev/null 2>&1", day, uci_get_buf);
				system(uci_set_buf);
			}
		}
	}
	else if (item == 4) { //4 - Customer schedule
		for ( day=0; day<7; day++ ){
			sprintf(uci_set_buf, "schedule -t 3 -m wirelessAvailability.wifitbl -v \"'','%d','%s','%s','%d','%s'\" > /dev/null 2>&1", 
				day,
				NewCliWifiSchedule.stimeOfdays[day],
				NewCliWifiSchedule.etimeOfdays[day],
				NewCliWifiSchedule.availableOfdays[day],
				uci_get_buf
			);
			system(uci_set_buf);
		}
	}
	system("uci commit");
	system("/etc/init.d/wirelessAvailability start > /dev/null 2>&1");
}

/*****************************************************************
* NAME: cmdwstemp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-10
* Modify:   
****************************************************************/
CliStatus cmdwstemp(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wirelessAvailability.wireless.templates";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

	if(cliData->argc==0){				
//		tprintf("1 - Choose a template\n");
		tprintf("1 - Always available\n");
		tprintf("2 - Available 8-5 Daily\n");
		tprintf("3 - Available 8-5 Daily except weekends\n");
//		tprintf("5 - Customer Schedule\n");				
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
		//Make sure that the value of template is 0 - 4
		sprintf(uci_set_buf, "%d", atoi(uci_set_buf));	
		cli_set_uci(func_buf, uci_set_buf);
		
		WifiTemplatesProcess(atoi(uci_set_buf));
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}


/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt wifisch wscustom                  */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"wifisch",	cli_table_newwifischedule, 	getNextTable, "Wifi schedule",	"", AUTH_ANY, EAP900H_ID|EAP900H_ID|EAP900_ID|C600_ID},	
//};

//static CliEntry cli_table_newwifischedule[]= {
//	{OPM_ALL, 	"wscustom",	cli_table_customerschedule,    	getNextTable,	"Customer Schedule",		"", 	AUTH_ADMIN, MODEL_ALL},
//};

//static CliEntry cli_table_customerschedule[]= {
//	{OPM_ALL,	"display",	NULL,			cmddisplay,			"Display wifi schedule table",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"setavail",  	NULL,			cmdsetavail,			"Set availability",		"", AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"setstime",  	NULL,			cmdsetstime,			"Set start time",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"setetime",  	NULL,			cmdsetetime,			"Set end time",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"accept",  	NULL,			cmdnewdualwsaccept,		"Accept wifi schedule setting",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_customerschedule,	cmdHelp,		"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmddualwifischeduleexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//};

/*****************************************************************
* NAME: displaynewdualWifiScheduledata
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Modifyby Philips on 2013-07-19 for new Wifi schedule to dual radio models 
* Modify:   
****************************************************************/
T_VOID displaynewdualWifiScheduledata(T_CHAR interface[8]) {
T_CHAR func_buf[128]="wirelessAvailability.wireless.radio";
T_CHAR uci_get_buf[8];
T_INT32 wifi_index=0;
T_INT32 ssidIndex;

	tprintf("\nDay         Availability         Start Tme      Stop Time   \n");
	tprintf("--------------------------------------------------------------\n");
	tprintf("Sunday       %s           %s          %s\n", (NewCliWifiSchedule.availableOfdays[0]?" available ":"unavailable"), NewCliWifiSchedule.stimeOfdays[0], NewCliWifiSchedule.etimeOfdays[0]);
	tprintf("Monday       %s           %s          %s\n", (NewCliWifiSchedule.availableOfdays[1]?" available ":"unavailable"), NewCliWifiSchedule.stimeOfdays[1], NewCliWifiSchedule.etimeOfdays[1]);
	tprintf("Tuesday      %s           %s          %s\n", (NewCliWifiSchedule.availableOfdays[2]?" available ":"unavailable"), NewCliWifiSchedule.stimeOfdays[2], NewCliWifiSchedule.etimeOfdays[2]);
	tprintf("Wednesday    %s           %s          %s\n", (NewCliWifiSchedule.availableOfdays[3]?" available ":"unavailable"), NewCliWifiSchedule.stimeOfdays[3], NewCliWifiSchedule.etimeOfdays[3]);
	tprintf("Thursday     %s           %s          %s\n", (NewCliWifiSchedule.availableOfdays[4]?" available ":"unavailable"), NewCliWifiSchedule.stimeOfdays[4], NewCliWifiSchedule.etimeOfdays[4]);
	tprintf("Friday       %s           %s          %s\n", (NewCliWifiSchedule.availableOfdays[5]?" available ":"unavailable"), NewCliWifiSchedule.stimeOfdays[5], NewCliWifiSchedule.etimeOfdays[5]);
	tprintf("Saturday     %s           %s          %s\n", (NewCliWifiSchedule.availableOfdays[6]?" available ":"unavailable"), NewCliWifiSchedule.stimeOfdays[6], NewCliWifiSchedule.etimeOfdays[6]);	
	tprintf("\n");

	//Get the information of radio -- 2.4G or 5G
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	tprintf("RADIO is %s, and ", ( atoi(uci_get_buf) ? "5GHz" : "2.4GHz" ) );
	
	//Get the information of ssid -- ath0-ath7 for 2.4G, ath50-ath57 for 5G
	ssidIndex = ( atoi(uci_get_buf) ? atoi(interface+3)-50 : atoi(interface+3) );
	
	if ( atoi(uci_get_buf) ==1 )
		wifi_index=26;
	
	sprintf(func_buf, "wireless.@wifi-iface[%d].ssid", wifi_index+ssidIndex);
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	tprintf("SSID is SSID%d : %s\n\n", ssidIndex+1, uci_get_buf);
	
}

/*****************************************************************
* NAME: cmddisplay
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-18
* Modify:   
****************************************************************/
CliStatus cmddisplay(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wirelessAvailability.wireless.iface";
T_CHAR uci_get_buf[128];


	//Get the information of ath interface
	strcpy(uci_get_buf, cli_get_uci(func_buf));
	
	if(cliData->argc==0){
		if (strlen(uci_get_buf)==0)
			printf("Please select a SSID first\n");
		else
			displaynewdualWifiScheduledata(uci_get_buf);
		
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsetavail
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-19
* Modify:   
****************************************************************/
CliStatus cmdsetavail(T_VOID* priv, CliData* cliData)
{
T_CHAR buf[2];
T_INT32 i;

	if(cliData->argc==0){
		buf[0] = cliData->tokens[cliData->tokenLen-1].token[2];
		buf[1] ='\0';
		i = atoi(buf);
		
		tprintf("Current setting: %d (1:available, 0:unavailable)\n", NewCliWifiSchedule.availableOfdays[i]);
		
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

		buf[0] = cliData->tokens[cliData->tokenLen-2].token[2];
		buf[1] ='\0';
		i = atoi(buf);
		
		NewCliWifiSchedule.availableOfdays[i]=atoi(cliData->tokens[cliData->tokenLen-1].token);
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsettime
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Philips 2013-07-19
* Modify:   
****************************************************************/
CliStatus cmdsettime(T_VOID* priv, CliData* cliData)
{
T_CHAR buf[2];
T_CHAR hour[3];
T_CHAR minute[3];
T_INT32 i;

	if(cliData->argc==0){
	
		buf[0] = cliData->tokens[cliData->tokenLen-1].token[2];
		buf[1] ='\0';
		i = atoi(buf);
		
		//mgmt wifisch custom setst stx
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='s' )
			tprintf("Current setting: %s \n", NewCliWifiSchedule.stimeOfdays[i]);
		//mgmt wifisch custom setet etx
		if ( cliData->tokens[cliData->tokenLen-1].token[0]=='e' )
			tprintf("Current setting: %s \n", NewCliWifiSchedule.etimeOfdays[i]);
			
		tprintf("Recognized input format: (00-23 Hour):(00-59 Minute)   EX: 09:55\n");		
			
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

		//Modify on 2013-07-22 to check whether start time is valid or not
		if ( cliData->tokens[cliData->tokenLen-1].token[2]!=':' || strlen(cliData->tokens[cliData->tokenLen-1].token)!=5 )
		{
			printf("Recognized input format: (00-23 Hour):(00-59 Minute)\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		hour[0] = cliData->tokens[cliData->tokenLen-1].token[0];
		hour[1] = cliData->tokens[cliData->tokenLen-1].token[1];
		hour[2] ='\0';
		minute[0] = cliData->tokens[cliData->tokenLen-1].token[3];
		minute[1] = cliData->tokens[cliData->tokenLen-1].token[4];
		minute[2] ='\0';

		if ( !errorcheckValidDecimal(hour) || !errorcheckIntRange( 0, 23, atoi(hour)) ){
			printf("The valid value of hour should be 00-23\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		if ( !errorcheckValidDecimal(minute) || !errorcheckIntRange( 0, 59, atoi(minute)) ){
			printf("The valid value of minute should be 00-59\n");
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		buf[0] = cliData->tokens[cliData->tokenLen-2].token[2];
		buf[1] ='\0';
		i = atoi(buf);
		
		//mgmt wifisch custom setst stx 08:45
		if ( cliData->tokens[cliData->tokenLen-2].token[0]=='s' )
			strcpy(NewCliWifiSchedule.stimeOfdays[i], cliData->tokens[cliData->tokenLen-1].token);
		//mgmt wifisch custom setet etx 08:45
		if ( cliData->tokens[cliData->tokenLen-2].token[0]=='e' )
			strcpy(NewCliWifiSchedule.etimeOfdays[i], cliData->tokens[cliData->tokenLen-1].token);
			
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdnewdualwsaccept
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Modifyby Philips on 2012-12-03 for function alignment of Wifi schedule to dual radio models 
* Modify:   
****************************************************************/
CliStatus cmdnewdualwsaccept(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="wirelessAvailability.wireless.iface";
T_CHAR uci_get_buf[128];
T_CHAR shour[3];
T_CHAR sminute[3];
T_CHAR ehour[3];
T_CHAR eminute[3];
T_INT32 day;

	//Get the information of ath interface
	strcpy(uci_get_buf, cli_get_uci(func_buf));

	if(cliData->argc==0){

		if (strlen(uci_get_buf)==0)
			printf("Please select a SSID first\n");
		else {
		
			for ( day=0; day<7; day++ ){
				shour[0] = NewCliWifiSchedule.stimeOfdays[day][0];
				shour[1] = NewCliWifiSchedule.stimeOfdays[day][1];
				shour[2] ='\0';
				sminute[0] = NewCliWifiSchedule.stimeOfdays[day][3];
				sminute[1] = NewCliWifiSchedule.stimeOfdays[day][4];
				sminute[2] ='\0';
				
				ehour[0] = NewCliWifiSchedule.etimeOfdays[day][0];
				ehour[1] = NewCliWifiSchedule.etimeOfdays[day][1];
				ehour[2] ='\0';
				eminute[0] = NewCliWifiSchedule.etimeOfdays[day][3];
				eminute[1] = NewCliWifiSchedule.etimeOfdays[day][4];
				eminute[2] ='\0';
				
				if ( (atoi(shour)>atoi(ehour)) || ((atoi(shour)==atoi(ehour)) && (atoi(sminute)>=atoi(eminute))) ){
					tprintf("Start time should be less than end time\n");
					cliData->tokenLen--;
					return CLI_PARAMS_ERR;
				}
			}
							
			displaynewdualWifiScheduledata(uci_get_buf);
			WifiTemplatesProcess(4);
		}
		
		cliData->tokenLen--;
		return CLI_OK;

	
	}else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt log                               */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"log",		cli_table_log,		getNextTable,	"Log",				"", AUTH_ANY,	MODEL_ALL},
//};

//static CliEntry cli_table_log[]= {
//	{OPM_ALL,	"syslog",	NULL,    	cmdsyslog,	"syslog active",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"logip",	NULL,           cmdlogip,       "Log server IP address",	"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"llog",		NULL,           cmdllog,	"Local log active",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_log,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,		cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};


/*****************************************************************
* NAME: cmdsyslog
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsyslog(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.log.LogServerEnable";
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
* NAME: cmdlogip
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdlogip(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.@system[0].log_ip";
T_CHAR uci_get_buf[128];
T_CHAR uci_set_buf[128];

//Modify on 2012-12-14 by Philips which is requested by Jackey to support IPV4 and IPV6 address
T_INT32 rc4;
struct in6_addr octetstr_ipv6;
T_INT32 rc6;
struct in6_addr octetstr_ipv4;

	if(cliData->argc==0){		
		strcpy(uci_get_buf, cli_get_uci(func_buf));
		tprintf("Current setting: %s\n", uci_get_buf);


//Modify on 2012-12-19 for IPV6 information of EAP600TRUE which is requested by Jacy
//Modify on 2013-02-21 by Philips which is requested by Jackey to support IPV4 and IPV6 address for EAP300V2 
//if ( strcmp(model_name, "ens202")==0 || strcmp(model_name, "ens202ext")==0 || strcmp(model_name, "eap600")==0 || strcmp(model_name, "ecb600")==0 || strcmp(model_name, "ens500")==0 || strcmp(model_name, "ens500ext")==0 || strcmp(model_name, "enh510")==0 )
	
if( model_ID & MODEL_IPV6 )
	tprintf("Recognized input format:  IPv4 or IPv6 address    EX: 192.168.1.35 or 8E4A::4B\n");
else
	tprintf("Recognized input format:  IPv4 address    EX: 192.168.1.35\n");
		
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){

		//Modify on 2012-10-26 requested by Talor to support IPV6 address
//		if( (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token ))&&(!errorcheckValidIPv6( cliData->tokens[cliData->tokenLen-1].token )) ){


//Modify on 2012-12-19 for IPV6 information of EAP600TRUE which is requested by Jacy
//Modify on 2013-02-21 by Philips which is requested by Jackey to support IPV4 and IPV6 address for EAP300V2
//if ( strcmp(model_name, "ens202")==0 || strcmp(model_name, "ens202ext")==0 || strcmp(model_name, "eap600")==0 || strcmp(model_name, "ecb600")==0 || strcmp(model_name, "ens500")==0 || strcmp(model_name, "ens500ext")==0 || strcmp(model_name, "enh510")==0 ){

if( model_ID & MODEL_IPV6 ){
	//Modify on 2012-12-14 by Philips which is requested by Jackey to support IPV4 and IPV6 address
	rc4 = inet_pton(AF_INET, cliData->tokens[cliData->tokenLen-1].token, &octetstr_ipv4);
	rc6 = inet_pton(AF_INET6, cliData->tokens[cliData->tokenLen-1].token, &octetstr_ipv6);
	if( (rc4==0)&&(rc6==0) ){
		printf("\n\"%s\" is a invalid IPv4 or IPv6 address.\n", cliData->tokens[cliData->tokenLen-1].token);
	
//		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
	}
}
else{

	if( !errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token ) ){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
	}
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
* NAME: cmdllog
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdllog(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="system.log.LogLocalEnable";
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

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt diag or diagv6                    */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"diag",		cli_table_diag,		getNextTable,	"Diagnostics",			"", AUTH_ANY,	MODEL_ALL},
//};

//static CliEntry cli_table_diag[]= {
//	{OPM_ALL,	"ping",		NULL,           cmdping,	"Ping testing",			"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"trace",	NULL,           cmdtrace,       "Traceroute testing",		"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"route",	NULL,           cmdroute,	"Route information",		"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"arp",		NULL,           cmdarp,		"ARP information",		"",	AUTH_ADMIN, MODEL_ALL},
//2012-09-24 Add for TRUE Project
//	{OPM_ALL,	"telnet",	NULL,		cmdtelnet,	"Telnet to destination",	"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"sptest",	NULL,		cmdsptest,	"Speed test",			"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_diag,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,		cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdping
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdping(T_VOID* priv, CliData* cliData)
{
T_CHAR c1[255];

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
		
		sprintf(c1, "ping -c 4 %s", cliData->tokens[cliData->tokenLen-1].token);
		system(c1);

		cliData->tokenLen-=2;
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdtrace
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdtrace(T_VOID* priv, CliData* cliData)
{
T_CHAR c1[255];

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
		
		sprintf(c1, "traceroute %s", cliData->tokens[cliData->tokenLen-1].token);
		system(c1);

		cliData->tokenLen-=2;
		
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdroute
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdroute(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){
		//printf("Called %s\n ",__func__);
		
		system("route -n");
  
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0){
  
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdarp
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdarp(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){
		//printf("Called %s\n ",__func__);
		
		system("cat /proc/net/arp");
  
		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0){
  
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdtelnet
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdtelnet(T_VOID* priv, CliData* cliData)
{
T_CHAR buf[128];

	if(cliData->argc==0){
		tprintf("Recognized input format:  (0-255).(0-255).(0-255).(0-255)    EX: 192.168.1.35\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		if (!errorcheckValidIP( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		sprintf(buf,"telnet %s", cliData->tokens[cliData->tokenLen-1].token);
		system(buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}


/*****************************************************************
* NAME: cmdsptest
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsptest(T_VOID* priv, CliData* cliData)
{
T_CHAR c1[255];

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
		sprintf(c1, "iperf -c %s -t 20 -i 5", cliData->tokens[cliData->tokenLen-1].token);
		system(c1);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt diag or diagv6                    */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"diagv6",	cli_table_diagv6,	getNextTable,	"Diagnostics for IPV6",		"", AUTH_ANY,	ENS202EXT_ID},
//};

//static CliEntry cli_table_diagv6[]= {
//	{OPM_ALL,	"ping6",	NULL,           	cmdping6,	"Ping testing for IPV6",		"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"trace6",	NULL,			cmdtrace6,       "Traceroute testing for IPV6",		"", AUTH_ANY,	MODEL_ALL},
//	{OPM_ALL,	"telnet6",	NULL,			cmdtelnet6,	"Telnet to destination for IPV6",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"sptest6",	NULL,			cmdsptest6,	"Speed test for IPV6",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",   	cli_table_diagv6,	cmdHelp,	"Help",					"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",					"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdping6
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdping6(T_VOID* priv, CliData* cliData)
{
T_CHAR c1[255];

	if(cliData->argc==0){

		tprintf("Recognized input format:  IPV6 Address    EX: fe80::7\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid segmentation fault when the length of input > 128
		if (!errorcheckValidIPv6( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		sprintf(c1, "ping -c 4 %s", cliData->tokens[cliData->tokenLen-1].token);
		system(c1);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdtrace6
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdtrace6(T_VOID* priv, CliData* cliData)
{
T_CHAR c1[255];

	if(cliData->argc==0){

		tprintf("Recognized input format:  IPV6 Address    EX: fe80::7\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid segmentation fault when the length of input > 128
		if (!errorcheckValidIPv6( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		
		sprintf(c1, "traceroute %s", cliData->tokens[cliData->tokenLen-1].token);
		system(c1);

		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdtelnet6
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdtelnet6(T_VOID* priv, CliData* cliData)
{
T_CHAR buf[128];

	if(cliData->argc==0){
		tprintf("Recognized input format:  IPV6 Address    EX: fe80::7\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		if (!errorcheckValidIPv6( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}

		sprintf(buf,"telnet %s %%br-lan", cliData->tokens[cliData->tokenLen-1].token);
		system(buf);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdsptest6
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdsptest6(T_VOID* priv, CliData* cliData)
{
T_CHAR c1[255];

	if(cliData->argc==0){

		tprintf("Recognized input format:  IPV6 Address    EX: fe80::7\n");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc==1){		
		//Modify on 2012-08-01 to avoid segmentation fault when the length of input > 128
		if (!errorcheckValidIPv6( cliData->tokens[cliData->tokenLen-1].token )){
			cliData->tokenLen-=2;
	  		return CLI_PARAMS_ERR;
		}
		sprintf(c1, "iperf -V -c %s %%br-lan -t 20 -i 5 -p 5002", cliData->tokens[cliData->tokenLen-1].token);
		system(c1);
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt disc                              */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"disc",		NULL,			cmddisc,	"Device Discovery",		"", AUTH_ANY,	MODEL_ALL},	
//};

/*****************************************************************
* NAME: cmddisc
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmddisc(T_VOID* priv, CliData* cliData)
{
	if(cliData->argc==0){
		
		system("/usr/sbin/discover");
		printf("\nDevice Discovery ...\n\n");
		printf("  Device Name     IP Address   System MAC Address   Firmware   OPeration Mode\n");
		printf("=============================================================================\n");
		//Modify on 2013-01-07 by Philips to display the information of other device by using discovery utility
		//system("sed \"s/\t/|/g\" | awk -F \" \" \'{ printf \"%10s %15s %20s %8s   %s \\n\", $1, $3, $4, $5, $2}\' /tmp/device_list | tail -n +2");	
		system("cat /tmp/device_list | grep [:xdigit:] | sed -e \"s/\t/|/g\" | sed -e \"s/  //g\" | awk -F \"|\" \'{ printf \"%13s %15s %20s %8s   %s \\n\", $1, $3, $4, $5, $2}\'");
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt led                               */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {	
//	{OPM_ALL,	"led",		cli_table_led,		getNextTable,	"Led control",			"", AUTH_ANY,	MODEL_EAP_ECB},
//};

//static CliEntry cli_table_led[]= {
//	{OPM_ALL,	"pled",		NULL,		cmdpled,	"Power led",	"", AUTH_ADMIN, MODEL_EAP_ECB},
//	{OPM_ALL,	"lled",		NULL,		cmdlled,	"LAN led",	"", AUTH_ANY,	MODEL_EAP_ECB},
//	{OPM_ALL,	"wled",		NULL,		cmdwled,        "WLAN led",     "", AUTH_ADMIN, EAP350_ID|ECB350_ID|ECB350TRUE_ID},
//	{OPM_ALL,	"2led",		NULL,		cmd2led,        "2.4G led",     "", AUTH_ADMIN, EAP600_ID|EAP600TRUE_ID},
//	{OPM_ALL,	"5led",		NULL,		cmd5led,        "5G led",	"", AUTH_ADMIN, EAP600_ID|EAP600TRUE_ID},
//	{OPM_ALL,	"wpsled",	NULL,		cmdwpsled,	"WPS led",	"", AUTH_ADMIN, MODEL_DUAL},		
//	{OPM_ALL,	"help",   	cli_table_led,	cmdHelp,	"Help",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",   	NULL,		cmdexit,	"Exit",		"", AUTH_ADMIN, MODEL_ALL},
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdpled
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdpled(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="led.led.PowerLED";
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
		
		system("/etc/init.d/ledctrl reload > /dev/null 2>&1");		
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdlled
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdlled(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="led.led.LANLED";
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
		
		system("/etc/init.d/ledctrl reload > /dev/null 2>&1");		
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwled
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwled(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="led.led.WLANLED";
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
		
		system("/etc/init.d/ledctrl reload > /dev/null 2>&1");		
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmd2led
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmd2led(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="led.led.WLAN0LED";
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
		
		system("/etc/init.d/ledctrl reload > /dev/null 2>&1");
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmd5led
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmd5led(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="led.led.WLAN1LED";
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
		
		system("/etc/init.d/ledctrl reload > /dev/null 2>&1");		
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdwpsled
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdwpsled(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="led.led.WPSLED";
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
		
		system("/etc/init.d/ledctrl reload > /dev/null 2>&1");		
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmd2wpsled
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmd2wpsled(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="led.led.WPS0LED";
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
		
		system("/etc/init.d/ledctrl reload > /dev/null 2>&1");		
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmd5wpsled
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmd5wpsled(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128]="led.led.WPS1LED";
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
		
		system("/etc/init.d/ledctrl reload > /dev/null 2>&1");		
		
		cliData->tokenLen-=2;
		return CLI_NOTHING;
	}
	else if(cliData->argc>1){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt radio2 or radio5                  */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {
//	{OPM_ALL,	"radio2",	cli_table_radio,	getNextTable,	"2.4G radio control",		"", AUTH_ADMIN, MODEL_2G},
//	{OPM_ALL,	"radio5",	cli_table_radio,	getNextTable,	"5G radio control",		"", AUTH_ADMIN, MODEL_5G},
//};

//static CliEntry cli_table_radio[]= {
//	{OPM_ALL,	"up",		NULL,			cmdradioup,	"Turn on radio",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"down",		NULL,			cmdradiodown,	"Turn off radio",	"", AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"help",		cli_table_radio,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_TRUE},
//	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_TRUE},
//	{ CMD_END_TAG}
//};

/*****************************************************************
* NAME: cmdradioup
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdradioup(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[33];
T_INT32 ssidCount;
T_INT32 i;
T_INT32 operationeMode=current_opmode;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);
	
	if(cliData->argc==0){
		printf("Radio Up List :%s\n");
		for (i=0; i<ssidCount; i++){		
			//Get the value of WLANEnable
			sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", i);
			if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
				sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", 26+i);
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			//Up ath interface if the value of WLANEnable is 1
			if ( atoi(uci_get_buf)!=0 ){
				sprintf(func_buf, "ifconfig ath%d up", i);
				if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
					sprintf(func_buf, "ifconfig ath%d up", 50+i);
				printf("%s\n", func_buf);					
				system(func_buf);
			} 
		}
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*****************************************************************
* NAME: cmdradiodown
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0918
* Modify:   
****************************************************************/
CliStatus cmdradiodown(T_VOID* priv, CliData* cliData)
{
T_CHAR func_buf[128];
T_CHAR uci_get_buf[33];
T_INT32 ssidCount;
T_INT32 i;
T_INT32 operationeMode=current_opmode;
	
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		operationeMode=current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		operationeMode=current_opmode_5;

	ssidCount=getModelssidCount(operationeMode);
	
	if(cliData->argc==0){
		printf("Radio Down List :%s\n");
		for (i=0; i<ssidCount; i++){		
			//Get the value of WLANEnable
			sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", i);
			if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
				sprintf(func_buf, "wireless.@wifi-iface[%d].WLANEnable", 26+i);
			strcpy(uci_get_buf, cli_get_uci(func_buf));
			//Down ath interface if the value of WLANEnable is 1
			if ( atoi(uci_get_buf)!=0 ){
				sprintf(func_buf, "ifconfig ath%d down", i);
				if (model_radio==7 && strcmp(current_radio_flag, "5G")==0)
					sprintf(func_buf, "ifconfig ath%d down", 50+i);
				printf("%s\n", func_buf);					
				system(func_buf);
			} 
		}
    		cliData->tokenLen--;
		return CLI_NOTHING;
	}
	else if(cliData->argc>0){
		return CLI_NO_MATCH;
	}
}

/*-------------------------------------------------------------------------*/
/*                   CLI Command -- mgmt logout                              */
/*-------------------------------------------------------------------------*/

//CliEntry cli_table_mgmt[]= {		
//	{OPM_ALL,	"logout",	NULL,			cmdlogout,	"Logout",			"", AUTH_ADMIN, MODEL_ALL},
//};

/*****************************************************************
* NAME: cmdlogout
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Yenger, Philips 2012-0420
* Modify:   
****************************************************************/
CliStatus cmdlogout(T_VOID* priv, CliData* cliData)
{

	if(cliData->argc==0){
		printf("System logout\n\n");
		exit(1);
	}
	else if(cliData->argc>0)
		return CLI_NO_MATCH;

}





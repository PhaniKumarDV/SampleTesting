#include <sap_osapi.h>
#include <sap_ostypes.h>
#include <gconfig.h>
#include <cli.h>
#include <sysUtil.h>
#include <tokens.h>
#include <apcfg.h>
#include <cmdedit.h>
#include <settings.h>
#include <cli_status.h>

#define OPM_ALL             (OPM_WDSAP|OPM_WDSSTA|OPM_RP|OPM_AP|OPM_AR|OPM_CB|OPM_CBRT|OPM_WDSB)
/*********************************************/
/****************** Level 5 ******************/
/*********************************************/


/*********************************************/
/****************** Level 4 ******************/
/*********************************************/


/*********************************************/
/****************** Level 3 ******************/
/*********************************************/

CliEntry cli_table_client[]= {
//	{OPM_ALL,	"clientinfo",	NULL,			cmdsystemclient,	"Wireless client list",		"",     AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"kickclient",	NULL,			cmdkickclient,		"Disconnect client",		"",     AUTH_ADMIN, MODEL_2G},	
	{OPM_ALL,	"kickclient",	NULL,			cmdkickclient,		"Disconnect client",		"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",		cli_table_client,	cmdHelp,		"Help",				"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,   	"exit",		NULL,			cmdexit,		"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
	{ CMD_END_TAG }
};

CliEntry cli_table_info[]= {

	{OPM_ALL,	"sysuptime",	NULL,			cmdsysuptime,	"System up time",		"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"cpuinfo",	NULL,			cmdcpuinfo,	"CPU load",			"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"meminfo",	NULL,			cmdmeminfo,	"Memory usage",			"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"wlanint",	NULL,			cmdwlanint,	"WLAN interface status",	"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"wlaninfo",	NULL,			cmdwlaninfo,	"WLAN statistics",		"",     AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"etherinfo",	NULL,			cmdetherinfo,	"Ethernet statistics",		"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"channel2",	NULL,			cmdchannel2,	"2.4G channel utilization",	"",     AUTH_ADMIN, MODEL_2G},
	{OPM_ALL,	"channel5",	NULL,			cmdchannel5,	"5G channel utilization",	"",     AUTH_ADMIN, MODEL_5G},
	{OPM_ALL,	"help",		cli_table_info,		cmdHelp,	"Help",				"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,   	"exit",		NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
	{ CMD_END_TAG }
};

/*********************************************/
/****************** Level 2 ******************/
/*********************************************/


CliEntry cli_table_stat[]= {

	{OPM_ALL,			"main",		NULL,			cmdSystemmain,	"Main",				"",	AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_AR|OPM_RP|OPM_WDSAP, "client2",	cli_table_client,	getNextTable,	"2.4G Wireless client list",	"",	AUTH_ADMIN, MODEL_2G},
	{OPM_AP|OPM_AR|OPM_RP|OPM_WDSAP, "client5",	cli_table_client,	getNextTable,	"5G Wireless client list",	"",	AUTH_ADMIN, MODEL_5G},

//Modify on 2012-11-13 for WDS link status in WDSAP mode and WDSB mode	
	{OPM_WDSAP|OPM_WDSB,		"wdslist2",	NULL,			cmdwdslist,	"2.4G WDS link status",		"",	AUTH_ADMIN, MODEL_2G},
	{OPM_WDSAP|OPM_WDSB,		"wdslist5",	NULL,			cmdwdslist,	"5G WDS link status",		"",	AUTH_ADMIN, MODEL_5G},
	
	{OPM_ALL,			"info",		cli_table_info,		getNextTable,	"Status information",		"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,			"syslog",	NULL,			cmdloginfo,	"System log",			"",     AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,			"help",		cli_table_stat,		cmdHelp,	"Help",				"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,   			"exit",		NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG }
};

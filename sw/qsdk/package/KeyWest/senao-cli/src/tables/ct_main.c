#include <sap_osapi.h>
#include <sap_ostypes.h>
#include <gconfig.h>
#include <cli.h>
#include <sysUtil.h>
#include <tokens.h>
#include <apcfg.h>
#include <cmdedit.h>
#include <settings.h>

#define OPM_ALL             (OPM_WDSAP|OPM_WDSSTA|OPM_RP|OPM_AP|OPM_AR|OPM_CB|OPM_CBRT|OPM_WDSB)

extern CliEntry cli_table_stat[];
extern CliEntry cli_table_netcomm_system[];
extern CliEntry cli_table_eor_net[];
extern CliEntry cli_table_netcomm_net[];
extern CliEntry cli_table_sys[];
extern CliEntry cli_table_mgmt[];
extern CliEntry cli_table_wless[];
extern CliEntry cli_table_upgrade[];
extern CliEntry cli_table_tools[];
extern CliEntry cli_table_diag[];
extern CliEntry cli_table_rout[];

/*********************************************/
/****************** Level 1 ******************/
/*********************************************/

CliEntry cmdBasicTable[] = {
	{OPM_ALL,	"stat",		cli_table_stat,		getNextTable,	"Status",		"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"sys",		cli_table_sys,		getNextTable,	"System",		"",	AUTH_ANY, MODEL_ALL},
	{WAN_OPM,	"rout",		cli_table_rout,		getNextTable,	"Router",		"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"wless2",	cli_table_wless,	getNextTable,	"2.4G-Wireless",	"",	AUTH_ANY, MODEL_2G},
	{OPM_ALL,	"wless5",	cli_table_wless,	getNextTable,	"5G-Wireless",		"",	AUTH_ANY, MODEL_5G},
	{OPM_ALL,	"mgmt",		cli_table_mgmt,		getNextTable,	"Management",		"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"tree",		cmdBasicTable,		cmdTree,	"Tree",			"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"help",		cmdBasicTable,		cmdHelp,	"Help",			"",	AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"save",		NULL,			cmdsave,	"Save",			"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"reboot",	NULL,			cmdreboot,	"Reboot",		"",	AUTH_ANY, MODEL_ALL},	
	{OPM_ALL,	"exit",		NULL,			cmdlogout,	"Logout",		"",	AUTH_ANY, MODEL_TRUE},
//Modify on 2013-08-27 by Philips to support logout command which is requested by SQA
	{OPM_ALL,	"logout",	NULL,			cmdlogout,	"Logout",		"",	AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"revert",	NULL,			cmdrevert,	"Revert",		"",	AUTH_ANY, MODEL_ALL},
	{CMD_END_TAG}
};


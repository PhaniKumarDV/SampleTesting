#include <cli.h>
#include <settings.h>
#include <opmodes.h>

#include <cli_management.h>

extern CliEntry cli_table_traffic[];
/*********************************************/
/****************** Level 5 ******************/
/*********************************************/

CliEntry cli_table_drate[]= {
	{OPM_AP | OPM_AR | OPM_WDSAP,   "enable",    NULL,	cmddrateenable,      "Data rate enable",     "", AUTH_ANY, MODEL_TRUE},
 	{OPM_AP | OPM_AR | OPM_WDSAP,   "disable",     NULL,	cmddratedisable,       "Data rate disable",     "", AUTH_ANY, MODEL_TRUE},

  	{OPM_ALL,   "help",   	cli_table_drate,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_TRUE},
	{OPM_ALL,   "exit",    	 NULL,    cmdexit,	 "Exit", "", AUTH_ADMIN, MODEL_TRUE},
  	{ CMD_END_TAG}  
};

CliEntry cli_table_brate[]= {
	{OPM_AP | OPM_AR | OPM_WDSAP,   "enable",    NULL,	cmdbrateenable,      "Basic rate enable",     "", AUTH_ANY, MODEL_TRUE},
 	{OPM_AP | OPM_AR | OPM_WDSAP,   "disable",     NULL,	cmdbratedisable,       "Basic rate disable",     "", AUTH_ANY, MODEL_TRUE},

  	{OPM_ALL,   "help",   	cli_table_drate,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_TRUE},
	{OPM_ALL,   "exit",    	 NULL,    cmdexit,	 "Exit", "", AUTH_ADMIN, MODEL_TRUE},
  	{ CMD_END_TAG}  
};

//Add on 2013-07-19 for Wifi schedule to EAP900H model 
static CliEntry cli_table_customeravail[]= {
	{OPM_ALL,	"av0",		NULL,				cmdsetavail,	"Set availability of Sunday",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"av1",  	NULL,				cmdsetavail,	"Set availability of Monday",	"", AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"av2",  	NULL,				cmdsetavail,	"Set availability of Tuesday",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"av3",  	NULL,				cmdsetavail,	"Set availability of Wednesday","", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"av4",  	NULL,				cmdsetavail,	"Set availability of Thursday",	"", AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"av5",  	NULL,				cmdsetavail,	"Set availability of Friday",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"av6",  	NULL,				cmdsetavail,	"Set availability of Saturday",	"", AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"help",		cli_table_customeravail,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",		NULL,				cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG }
};

//Add on 2013-07-19 for Wifi schedule to EAP900H model 
static CliEntry cli_table_customerstime[]= {
	{OPM_ALL,	"st0",		NULL,				cmdsettime,	"Set start time of Sunday",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"st1",  	NULL,				cmdsettime,	"Set start time of Monday",	"", AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"st2",  	NULL,				cmdsettime,	"Set start time of Tuesday",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"st3",  	NULL,				cmdsettime,	"Set start time of Wednesday",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"st4",  	NULL,				cmdsettime,	"Set start time of Thursday",	"", AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"st5",  	NULL,				cmdsettime,	"Set start time of Friday",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"st6",  	NULL,				cmdsettime,	"Set start time of Saturday",	"", AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"help",		cli_table_customerstime,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",		NULL,				cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG }
};

//Add on 2013-07-19 for Wifi schedule to EAP900H model 
static CliEntry cli_table_customeretime[]= {
	{OPM_ALL,	"et0",		NULL,				cmdsettime,	"Set end time of Sunday",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"et1",  	NULL,				cmdsettime,	"Set end time of Monday",	"", AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"et2",  	NULL,				cmdsettime,	"Set end time of Tuesday",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"et3",  	NULL,				cmdsettime,	"Set end time of Wednesday",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"et4",  	NULL,				cmdsettime,	"Set end time of Thursday",	"", AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"et5",  	NULL,				cmdsettime,	"Set end time of Friday",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"et6",  	NULL,				cmdsettime,	"Set end time of Saturday",	"", AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"help",		cli_table_customeretime,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",		NULL,				cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG }
};

/*********************************************/
/****************** Level 4 ******************/
/*********************************************/
static CliEntry cli_table_admin[]= {
	{OPM_ALL,   "nname",	NULL,			cmdnewname,		"New Name",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "opw",	NULL,			cmdoldpwd,		"Old Password",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "npw",	NULL,			cmdnewpwd,		"New Password",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "cpw",	NULL,			cmdconfirmpwd,		"Confirm Password",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "accept",	NULL,			cmdadminaccept,		"Accept administration setting",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,    "help",   	cli_table_admin,	cmdHelp,		"Help",					"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,    "exit",   	NULL,			cmdadminexit,		"Exit",					"", AUTH_ADMIN, MODEL_ALL},
	
	{ CMD_END_TAG}
};

static CliEntry cli_table_remote[]= {
	{OPM_AR | OPM_CBRT,	"rmgmt",	NULL,			cmdrmgmt,	"Remote Management",		"",	AUTH_ADMIN, MODEL_ALL},
//Modify on 2013-01-28 for disabling the function which is requested by Jacy
//	{OPM_AR | OPM_CBRT,	"rupgrade",	NULL,			cmdrupgrade,	"remote Upgrade",		"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_AR | OPM_CBRT,	"rmport",	NULL,			cmdrmport,	"Remote Management Port",	"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"help",		cli_table_remote,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"exit",		NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},
	
	{ CMD_END_TAG}
};

CliEntry cli_table_manuallydate[]= {
	{OPM_ALL,   "date",     NULL,     cmddate,      "Date and time",   "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,    "help",   	cli_table_manuallydate,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,    "exit",   	NULL,     cmdautoexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};

CliEntry cli_table_automaticallydate[]= {
	{OPM_ALL,   "tz", 	 NULL,	  cmdtz,   	 "Time zone",   "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "ntpact",    NULL,    cmdntpact,     "NTP server active",   "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "ntpip",     NULL,    cmdntpip,      "NTP server IP",   "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "help",   	cli_table_automaticallydate,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "exit",    	 NULL,    cmdautoexit,	 "Exit", "", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};

CliEntry cli_table_ping[]= {
	{OPM_ALL,   "pip", 	 NULL,	  cmdtip,   	 "Target IP",   "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "psize",    NULL,    cmdpsize,     "Ping packet size",   "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "pnum",     NULL,    cmdnumber,      "Number of ping",   "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "accept",     NULL,    cmdpingaccept,      "Accept ping test parameters",   "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "help",   	cli_table_ping,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "exit",    	 NULL,    cmdpingexit,	 "Exit", "", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};

CliEntry cli_table_vlanp[]= {
	{OPM_AP | OPM_AR | OPM_WDSAP,   "ssidact",    NULL,         cmdssidact,      "SSID active",     "", AUTH_ANY, MODEL_DUAL},
 	{OPM_AP | OPM_AR | OPM_WDSAP,   "isoact",     NULL,         cmdisoact,       "Isolation active",     "", AUTH_ANY, MODEL_DUAL},
	{OPM_AP | OPM_AR | OPM_WDSAP,   "vid",         NULL,        cmdvid,     	 "VLAN ID",     "", AUTH_ANY, MODEL_DUAL},
  	{OPM_ALL,   "help",   	cli_table_vlanp,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "exit",    	 NULL,    cmdvlanpexit,	 "Exit", "", AUTH_ADMIN, MODEL_ALL},
  	{ CMD_END_TAG}  
};

//Modify for function alignment of Band Steer for EAP600 on 2012-12-04
CliEntry cli_table_bsteer[]= {
	{OPM_AP|OPM_WDSAP,	"bsteeract",	NULL,			cmdbsteeract,	"Band steering active",		"", AUTH_ANY, MODEL_ALL},
//	{OPM_AP|OPM_WDSAP,	"threshold",	NULL,			cmdthreshold,	"Band steering threshold",	"", AUTH_ANY, EAP600TRUE_ID},
  	{OPM_ALL,		"help",   	cli_table_bsteer,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
  	{ CMD_END_TAG}  
};

CliEntry cli_table_ratec2[]= {
	{OPM_AP | OPM_AR | OPM_WDSAP,   "drate",    cli_table_drate,	getNextTable,      "Data rate",     "", AUTH_ANY, MODEL_TRUE},
 	{OPM_AP | OPM_AR | OPM_WDSAP,   "brate",     cli_table_brate,	getNextTable,       "Basic rate",     "", AUTH_ANY, MODEL_TRUE},
  	{OPM_ALL,   "help",   	cli_table_ratec2,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_TRUE},
	{OPM_ALL,   "exit",    	 NULL,    cmdexit,	 "Exit", "", AUTH_ADMIN, MODEL_TRUE},
  	{ CMD_END_TAG}  
};

CliEntry cli_table_ratec5[]= {
	{OPM_AP | OPM_AR | OPM_WDSAP,   "drate",    cli_table_drate,	getNextTable,      "Data rate",     "", AUTH_ANY, EAP600TRUE_ID},
 	{OPM_AP | OPM_AR | OPM_WDSAP,   "brate",     cli_table_brate,	getNextTable,       "Basic rate",     "", AUTH_ANY, EAP600TRUE_ID},

  	{OPM_ALL,   "help",   	cli_table_ratec5,         cmdHelp,    "Help", "", AUTH_ADMIN, EAP600TRUE_ID},
	{OPM_ALL,   "exit",    	 NULL,    cmdexit,	 "Exit", "", AUTH_ADMIN, EAP600TRUE_ID},
  	{ CMD_END_TAG}  
};

//Modify for function alignment of Client Control for EAP600 on 2012-12-04
CliEntry cli_table_climit2[]= {
	{OPM_AP|OPM_AR|OPM_WDSAP|OPM_RP,	"limitact",	NULL,			cmdclimit2act,	"Client limit active",	"", AUTH_ANY, MODEL_ALL},
 	{OPM_AP|OPM_AR|OPM_WDSAP|OPM_RP,	"max",		NULL,			cmdclimit2max,	"Maximum client limit",	"", AUTH_ANY, MODEL_ALL},
  	{OPM_ALL,				"help",		cli_table_climit2,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,				"exit",		NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
  	{ CMD_END_TAG}  
};

//Modify for function alignment of Client Control for EAP600 on 2012-12-04
CliEntry cli_table_climit5[]= {
	{OPM_AP|OPM_AR|OPM_WDSAP|OPM_RP,	"limitact",	NULL,			cmdclimit5act,	"Client limit active",	"", AUTH_ANY, MODEL_ALL},
 	{OPM_AP|OPM_AR|OPM_WDSAP|OPM_RP,	"max",		NULL,			cmdclimit5max,	"Maxmuim client limit",	"", AUTH_ANY, MODEL_ALL},
  	{OPM_ALL,				"help",   	cli_table_climit5,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,				"exit",		NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
  	{ CMD_END_TAG}  
};

//Modify for function alignment of Daylight Saving on to all models 2012-11-14
static CliEntry cli_table_daylight[]= {
	{OPM_ALL,	"dlsact",	NULL,			cmddlsact,	"Daylight saving active",	"",     AUTH_ADMIN, MODEL_ALL},
	
	{OPM_ALL,	"monthstart",	NULL,			cmdmonthtime,	"Month start time",		"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"weekstart",	NULL,			cmdweektime,	"Week start time",		"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"daystart",	NULL,			cmddaytime,	"Day start time",		"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"hourstart",	NULL,			cmdhourtime,	"Hour start time",		"",     AUTH_ADMIN, MODEL_ALL},
	
	{OPM_ALL,	"monthend",	NULL,			cmdmonthtime,	"Month end time",		"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"weekend",	NULL,			cmdweektime,	"Week end time",		"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"dayend",	NULL,			cmddaytime,	"Day end time",			"",     AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"hourend",	NULL,			cmdhourtime,	"Hour end time",		"",     AUTH_ADMIN, MODEL_ALL},
		
	{OPM_ALL,	"help",   	cli_table_daylight,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};

//Modify for function alignment of Wifi schedule to single radio models on 2012-11-15
static CliEntry cli_table_wsadd[]= {
	{OPM_ALL,	"setname",	NULL,			cmdsetwsname,		"Set wifi schedule name",	"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"setwp",  	NULL,			cmdsetwswp,		"Set wireless power",		"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"setday",  	NULL,			cmdsetwsday,		"Set day",			"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"sethour",  	NULL,			cmdsetwshour,		"Set hour",			"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"setmin",  	NULL,			cmdsetwsmin,		"Set minute",			"", 	AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"accept",  	NULL,			cmdwsaccept,		"Accept wifi schedule setting",	"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",		cli_table_wsadd,	cmdHelp,		"Help",				"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",		NULL,			cmdwifischeduleexit,    "Exit",				"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG }
};

//Modify for function alignment of Wifi schedule to dual radio models on 2012-11-30
static CliEntry cli_table_dualwsadd[]= {
	{OPM_ALL,	"setname",	NULL,			cmdsetwsname,			"Set wifi schedule name",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"setsvc",  	NULL,			cmdsetwssvc,			"Set service",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"setdays",  	NULL,			cmdsetdualwsday,		"Set day",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"setshour",  	NULL,			cmdsetdualwshour,		"Set start hour",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"setsmin",  	NULL,			cmdsetdualwsmin,		"Set start minute",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"setehour",  	NULL,			cmdsetdualwshour,		"Set end hour",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"setemin",  	NULL,			cmdsetdualwsmin,		"Set end minute",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"accept",  	NULL,			cmddualwsaccept,		"Accept wifi schedule setting",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",		cli_table_dualwsadd,	cmdHelp,			"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",		NULL,			cmddualwifischeduleexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG }
};

//Add on 2013-07-18 for Wifi schedule to EAP900 model 
static CliEntry cli_table_customerschedule[]= {
	{OPM_ALL,	"display",	NULL,			cmddisplay,			"Display wifi schedule table",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"setav",  	cli_table_customeravail, getNextTable,			"Set availability",		"", AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"setst",  	cli_table_customerstime, getNextTable,			"Set start time",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"setet",  	cli_table_customeretime, getNextTable,			"Set end time",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"accept",  	NULL,			cmdnewdualwsaccept,		"Accept wifi schedule setting",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",		cli_table_customerschedule, cmdHelp,			"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",		NULL,			cmddualwifischeduleexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG }
};

/*********************************************/
/****************** Level 3 ******************/
/*********************************************/

static CliEntry cli_table_login_remote[]= {
	{OPM_ALL,		"login",	cli_table_admin,	getNextTable,	"Login Setting",	"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_AR | OPM_CBRT,	"remote",	cli_table_remote,	getNextTable,	"Remote Access",	"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"help",		cli_table_login_remote,	cmdHelp,	"Help",			"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"exit",		NULL,			cmdexit,	"Exit",			"",	AUTH_ADMIN, MODEL_ALL},
	
	{ CMD_END_TAG}
};

static CliEntry cli_table_vlan2[]= {
	
	{OPM_AP | OPM_WDSAP,   "vlanp",  NULL,     cmdvlanp,      "2.4G VLAN profile settings",   "", AUTH_ADMIN, MODEL_DUAL},
	//{OPM_AP | OPM_WDSAP,   "mvlan",  NULL,     cmdmvlan,      "Management VLAN settings",   "", AUTH_ADMIN, MODEL_2G},
	{OPM_ALL,    "help",   	cli_table_vlan2,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,    "exit",   	NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};

static CliEntry cli_table_vlan5[]= {

	{OPM_AP | OPM_WDSAP,   "vlanp",  NULL,     cmdvlanp,      "5G VLAN profile settings",   "", AUTH_ADMIN, MODEL_DUAL},
	//{OPM_AP | OPM_WDSAP,   "mvlan",  NULL,     cmdmvlan,      "Management VLAN settings",   "", AUTH_ADMIN, MODEL_5G},
	{OPM_ALL,    "help",   	cli_table_vlan5,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,    "exit",   	NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};


//Add on 2013-03-22 by Philips to support cloud setting for C600
static CliEntry cli_table_cloud[]= {
	{OPM_ALL,	"cloudact",	NULL,			cmdcloudact,	"Cloud Management active",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"pserver",	NULL,			cmdpserver,	"Proxy Server",			"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"pport",	NULL,			cmdpport,	"Proxy Port",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"uname",	NULL,			cmdpusername,	"User Name",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"passwd",	NULL,			cmdppasswd,	"Password",			"", AUTH_ADMIN, MODEL_ALL},
	
	{OPM_ALL,	"help",   	cli_table_cloud,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
	
	{ CMD_END_TAG}
};


static CliEntry cli_table_snmp[]= {
	{OPM_ALL,	"snmpact",	NULL,		cmdsnmpact,	"SNMP active",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"cont",		NULL,		cmdcont,	"Contact",			"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"loca",		NULL,		cmdloca,        "Location",			"", AUTH_ADMIN, MODEL_ALL},
	
//Add on 2013-05-09 by Philips to support SNMP for eap600 which is requested by Jackey	
	{OPM_ALL,	"port",		NULL,		cmdport,	"Port",				"", AUTH_ADMIN, EAP600_ID|ALL02860ND_ID|EAP900H_ID|EWS320AP_ID|EWS321AP_ID|C900_ID|EAP600ROOTS_ID},
		
	{OPM_ALL,	"rcom",		NULL,		cmdrcom,	"Community name (read only)",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"wcom",		NULL,		cmdwcom,	"Community name (read/write)",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"trapaddr",	NULL,		cmdtrapaddr,	"Trap destination address",	"", AUTH_ADMIN, MODEL_ALL},

//Add on 2013-05-09 by Philips to support SNMP for eap600 which is requested by Jackey	
	{OPM_ALL,	"trapport",	NULL,		cmdtrapport,	"Trap destination port",	"", AUTH_ADMIN, EAP600_ID|ALL02860ND_ID|EAP900H_ID|EWS320AP_ID|EWS321AP_ID|C900_ID|EAP600ROOTS_ID},
	
	{OPM_ALL,	"trapcom",	NULL,		cmdtrapcom,	"Trap destination community name",	"", AUTH_ADMIN, MODEL_ALL},
		
	{OPM_ALL,	"snmpv3act",	NULL,		cmdsnmpv3act,   "SNMPv3 active",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"username",	NULL,		cmdusername,    "User name",			"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"authp",	NULL,		cmdauthp,       "Auth protocol",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"authk",	NULL,		cmdauthk,       "Auth key",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"privp",	NULL,		cmdprivp,       "Priv protocol",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"privk",	NULL,		cmdprivk,       "Priv key",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"engineid",	NULL,		cmdengineid,    "Engine ID",			"", AUTH_ADMIN, MODEL_ALL},	
	
	{OPM_ALL,	"help",   	cli_table_snmp,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,		cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
	
	{ CMD_END_TAG}
};

static CliEntry cli_table_bk[]= {
	{OPM_ALL,	"savecp",	NULL,		cmdsavecp,	"Save a copy of current settings",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"restore",	NULL,		cmdrestore,	"Restore saved settings from a file",	"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"revertfac",	NULL,		cmdrevertfac,	"Revert to factory default settings",	"", AUTH_ADMIN, MODEL_ALL},
	
//Add on 2013-06-06 by Philips to support Reset User Default for eap900 which is requested by Jacy	
//	{OPM_ALL,	"saveuser",	NULL,		cmdsaveuser,	"Save to user default",			"", AUTH_ADMIN, EAP900H_ID|C900_ID},	
//	{OPM_ALL,	"restoreuser",	NULL,		cmdrestoreuser,	"Restore to user default",		"", AUTH_ADMIN, EAP900H_ID|C900_ID},
	{OPM_ALL,	"saveuser",	NULL,		cmdsaveuser,	"Save to user default",			"", AUTH_ADMIN, MODEL_NEW_WEB},	
	{OPM_ALL,	"restoreuser",	NULL,		cmdrestoreuser,	"Restore to user default",		"", AUTH_ADMIN, MODEL_NEW_WEB},	
		
	{OPM_ALL,	"help",   	cli_table_bk,	cmdHelp,	"Help",					"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,		cmdexit,	"Exit",					"", AUTH_ADMIN, MODEL_ALL},
	
	{ CMD_END_TAG}
};

static CliEntry cli_table_time[]= {

	{OPM_ALL,	"auto",    	 NULL,			cmdauto,	"Automatically get date and time",	"",	AUTH_ADMIN, MODEL_ALL},
	//Modify for function alignment of Daylight Saving to all models on 2012-11-14
	{OPM_ALL,	"dlsave",	cli_table_daylight,	getNextTable,	"Daylight saving settings",		"",	AUTH_ANY, MODEL_ALL},
	
	{OPM_ALL,	"help",   	cli_table_time,         cmdHelp,	"Help",					"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",					"",	AUTH_ADMIN, MODEL_ALL},
	
	{ CMD_END_TAG}
};

static CliEntry cli_table_fwupgrade[]= {
	{OPM_ALL,	"fwup",		NULL,			cmdfwup,	"Firmware upgrade",     "", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"help",   	cli_table_fwupgrade,	cmdHelp,    	"Help",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
	
	{ CMD_END_TAG}
};

static CliEntry cli_table_led[]= {
	{OPM_ALL,	"pled",		NULL,		cmdpled,	"Power led",	"", AUTH_ADMIN, MODEL_EAP_ECB},
	{OPM_ALL,	"lled",		NULL,		cmdlled,	"LAN led",	"", AUTH_ANY, MODEL_EAP_ECB},

	{OPM_ALL,	"wled",		NULL,		cmdwled,        "WLAN led",     "", AUTH_ADMIN, EAP350_ID|ECB350_ID|ECB350TRUE_ID|EAP300V2_ID},


//	{OPM_ALL,	"2led",		NULL,		cmd2led,        "2.4G led",     "", AUTH_ADMIN, EAP600_ID|ALL02860ND_ID|EAP600TRUE_ID|ECB600_ID|ALL02880ND_ID|C600_ID|CAP4200AG_ID|TEW753DAP_ID|EAP900H_ID|C900_ID|EAP600ROOTS_ID|EAP1750H_ID},
	{OPM_ALL,	"2led",		NULL,		cmd2led,        "2.4G led",     "", AUTH_ADMIN, MODEL_2LED_5LED},


//	{OPM_ALL,	"5led",		NULL,		cmd5led,	"5G led",	"", AUTH_ADMIN, EAP600_ID|ALL02860ND_ID|EAP600TRUE_ID|ECB600_ID|ALL02880ND_ID|C600_ID|CAP4200AG_ID|TEW753DAP_ID|EAP900H_ID|C900_ID|EAP600ROOTS_ID|EAP1750H_ID},
	{OPM_ALL,	"5led",		NULL,		cmd5led,	"5G led",	"", AUTH_ADMIN, MODEL_2LED_5LED},


//	{OPM_ALL,	"wpsled",	NULL,		cmdwpsled,	"WPS led",	"", AUTH_ADMIN, EAP600_ID|ALL02860ND_ID|EAP600TRUE_ID|CAP4200AG_ID|EAP900H_ID|EWS320AP_ID|EWS321AP_ID|C900_ID|EAP600ROOTS_ID|EAP1750H_ID|EWS620AP_ID|EWS621AP_ID},
	{OPM_ALL,	"wpsled",	NULL,		cmdwpsled,	"WPS led",	"", AUTH_ADMIN, MODEL_WPSLED},


//Modify on 2013-07-02 by Philips for the led of ECB600 to cancel these two items 		
//	{OPM_ALL,	"2wpsled",	NULL,		cmd2wpsled,	"2.4G WPS led",	"", AUTH_ADMIN, ECB600_ID},
//	{OPM_ALL,	"5wpsled",	NULL,		cmd5wpsled,	"5G WPS led",	"", AUTH_ADMIN, ECB600_ID},

	{OPM_ALL,	"help",   	cli_table_led,	cmdHelp,	"Help",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,		cmdexit,	"Exit",		"", AUTH_ADMIN, MODEL_ALL},
	
	{ CMD_END_TAG}
};

static CliEntry cli_table_log[]= {
	{OPM_ALL,   "syslog",   NULL,    	cmdsyslog,          "syslog active",         "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,   "logip",    NULL,           cmdlogip,       "Log server IP address",     "", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,   "llog",     NULL,           cmdllog,        "Local log active",     "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,    "help",   	cli_table_log,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,    "exit",   	NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};

static CliEntry cli_table_diag[]= {
	{OPM_ALL,	"ping",		NULL,           cmdping,	"Ping testing",			"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"trace",	NULL,           cmdtrace,       "Traceroute testing",		"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"route",	NULL,           cmdroute,	"Route information",		"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"arp",		NULL,           cmdarp,		"ARP information",		"",	AUTH_ADMIN, MODEL_ALL},
	//2012-09-24 Add for TRUE Project
	{OPM_ALL,	"telnet",	NULL,		cmdtelnet,	"Telnet to destination",	"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"sptest",	NULL,		cmdsptest,	"Speed test",			"",     AUTH_ADMIN, MODEL_ALL},
	
	{OPM_ALL,	"help",   	cli_table_diag,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,		cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};

static CliEntry cli_table_diagv6[]= {
	{OPM_ALL,	"ping6",	NULL,           cmdping6,	"Ping testing for IPV6",			"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"trace6",	NULL,           cmdtrace6,       "Traceroute testing for IPV6",		"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"telnet6",	NULL,		cmdtelnet6,	"Telnet to destination for IPV6",	"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"sptest6",	NULL,		cmdsptest6,	"Speed test for IPV6",	"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",   	cli_table_diagv6,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,		cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};

static CliEntry cli_table_clientc[]= {
	{OPM_AP|OPM_WDSAP,			"bsteer",	cli_table_bsteer,  getNextTable,	"Band steering",	"", AUTH_ADMIN, MODEL_ALL},

	{OPM_AP|OPM_AR|OPM_WDSAP,		"ratec2",	cli_table_ratec2,  getNextTable,	"2.4G rate control",	"", AUTH_ANY, MODEL_TRUE},
	{OPM_AP|OPM_AR|OPM_WDSAP,		"ratec5",	cli_table_ratec5,  getNextTable,	"5G rate control",	"", AUTH_ANY, EAP600TRUE_ID},

	{OPM_AP|OPM_AR|OPM_WDSAP|OPM_RP,	"climit2",	cli_table_climit2, getNextTable,	"2.4G client limitation","", AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_AR|OPM_WDSAP|OPM_RP,	"climit5",	cli_table_climit5, getNextTable,	"5G client limitation",	"", AUTH_ANY, MODEL_ALL},

	{OPM_ALL,				"help",   	cli_table_clientc, cmdHelp,		"Help",			"", AUTH_ADMIN, MODEL_TRUE},
	{OPM_ALL,				"exit",   	NULL,		   cmdexit,		"Exit",			"", AUTH_ADMIN, MODEL_TRUE},

	{ CMD_END_TAG}
};

static CliEntry cli_table_radio[]= {
	{OPM_ALL,	"up",		NULL,			cmdradioup,	"Turn on radio",	"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"down",		NULL,			cmdradiodown,	"Turn off radio",	"",     AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"help",		cli_table_radio,	cmdHelp,	"Help",			"",	AUTH_ADMIN, MODEL_TRUE},
	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",			"",	AUTH_ADMIN, MODEL_TRUE},

	{ CMD_END_TAG}
};

//Modify for function alignment of auto reboot to all models on 2012-11-12
static CliEntry cli_table_autoreboot[]= {
	{OPM_ALL,	"rbact",	NULL,			cmdrbact,	"Auto reboot active",		"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"rbfreq",	NULL,			cmdrbfreq,	"Frequency of auto reboot",	"",     AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"rbamt",	NULL,			cmdrbamt,	"Amount of auto reboot",	"",     AUTH_ADMIN, MODEL_ALL},		
	{OPM_ALL,	"help",   	cli_table_autoreboot,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};


//Modify on 2013-07-01 by Philips to support auto reboot for eap900 which is requested by Jacy
static CliEntry cli_table_newautoreboot[]= {
	{OPM_ALL,	"arbact",	NULL,				cmdarbact,	"Auto reboot active",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"arbday",	NULL,				cmdarbday,	"Days of auto reboot",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"arbtime",	NULL,				cmdarbtime,	"Time of auto reboot",		"", AUTH_ADMIN, MODEL_ALL},		
	{OPM_ALL,	"help",   	cli_table_newautoreboot,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,				cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};


//Modify for function alignment of Wifi schedule to single radio models on 2012-11-15
static CliEntry cli_table_wifischedule[]= {
	{OPM_ALL,	"wslist",	NULL,			cmdwslist,	"Display wifi schedule list",	"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"wsact",	NULL, 	   		cmdwsact,	"wifi schedule active",		"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"wsadd",	cli_table_wsadd,     	getNextTable,	"wifi schedule add",		"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL, 	"wsdel",	NULL,                   cmdwsdel,	"wifi schedule delete",		"", 	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"help",   	cli_table_wifischedule,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};

//Modify for function alignment of Wifi schedule to dual radio models on 2012-11-30
static CliEntry cli_table_dualwifischedule[]= {
	{OPM_ALL,	"wslist",	NULL,				cmddualwslist,	"Display wifi schedule list",	"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"wsact",	NULL, 	   			cmdwsact,	"Wifi schedule active",		"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"wsadd",	cli_table_dualwsadd,     	getNextTable,	"Wifi schedule add",		"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL, 	"wsdel",	NULL,                   	cmddualwsdel,	"Wifi schedule delete",		"", 	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"help",   	cli_table_dualwifischedule,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,				cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};


//Modify for function alignment of Wifi schedule to dual radio models on 2012-11-30
static CliEntry cli_table_newwifischedule[]= {
	{OPM_ALL,	"wsact",	NULL,				cmdnewwsact,	"Wifi Schedule active",		"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"radio",	NULL, 	   			cmdwsradio,	"Wireless Radio",		"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"ssid",		NULL,     			cmdwsssid,	"SSID selection",		"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL, 	"template",	NULL,                   	cmdwstemp,	"Schedule templates",		"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL, 	"custom",	cli_table_customerschedule,    	getNextTable,	"Customer Schedule",		"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",   	cli_table_newwifischedule,	cmdHelp,	"Help",				"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,				cmdexit,	"Exit",				"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};


//Add on 2013-06-06 by Philips to support HTTPS for eap900 which is requested by Jacy
static CliEntry cli_table_https[]= {
	{OPM_ALL,	"hact",		NULL,			cmdhact,	"Https active",		"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"hfwd",		NULL, 	   		cmdhfwd,	"Https forward",	"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",   	cli_table_https,	cmdHelp,	"Help",			"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",			"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};

//Add on 2013-06-06 by Philips to support WLAN VLAN Pass-Through for eap900 which is requested by Jacy
static CliEntry cli_table_wvlanp[]= {
	{OPM_ALL,	"vdisable",	NULL,			cmdvdisable,	"WLAN VLAN pass through inactive",	"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"v2to5",	NULL, 	   		cmdv2to5,	"2G to 5G VLAN pass through",		"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"v5to2",	NULL, 	   		cmdv5to2,	"5G to 2G VLAN pass through",		"",	AUTH_ADMIN, MODEL_ALL},	
	{OPM_ALL,	"help",   	cli_table_wvlanp,	cmdHelp,	"Help",					"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",					"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};

//Add on 2013-06-17 by Philips to support Email Alert for eap900 which is requested by Jacy
static CliEntry cli_table_email[]= {
	{OPM_ALL,	"mailact",	NULL,			cmdmailact,	"Email alert active",			"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"addrto",	NULL, 	   		cmdaddrto,	"Email Address to recipients",		"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"addrfrom",	NULL,			cmdaddrfrom,	"Email Address from Administrator",	"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"mailauth",	NULL,			cmdmailauth,	"Email authentication",			"", 	AUTH_ADMIN, MODEL_ALL},
	
	//Add on 2013-08-07 by Philips to add a "email username" field for eap900 which is requested by Jacy
	{OPM_ALL,	"mailusr",	NULL, 	   		cmdmailusr,	"Email username",			"",	AUTH_ADMIN, MODEL_ALL},
	
	{OPM_ALL,	"mailpwd",	NULL, 	   		cmdmailpwd,	"Email password",			"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"smtpsvr",	NULL,			cmdsmtpsvr,	"SMTP server",				"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"smtport",	NULL, 	   		cmdsmtport,	"SMTP port",				"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"mailsec",	NULL, 	   		cmdmailsec,	"Security mode",			"",	AUTH_ADMIN, MODEL_ALL},	
//	{OPM_ALL,	"alert",	NULL,			cmdalert,	"System event alert",			"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"subject",	NULL,			cmdsubject,	"Subject of system event alert",	"", 	AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"message",	NULL, 	   		cmdmessage,	"Message of system event alert",	"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",   	cli_table_email,	cmdHelp,	"Help",					"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,			cmdexit,	"Exit",					"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};

/*********************************************/
/****************** Level 2 ******************/
/*********************************************/

CliEntry cli_table_mgmt[]= {
	{OPM_ALL,			"admin",	cli_table_login_remote,	getNextTable,	"Administration",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_AP|OPM_WDSAP,		"vlan2",	cli_table_vlan2,	getNextTable,	"2.4G Management vlan",		"", AUTH_ANY, MODEL_DUAL},
	{OPM_AP|OPM_WDSAP,		"vlan5",	cli_table_vlan5,	getNextTable,	"5G Management vlan",		"", AUTH_ANY, MODEL_DUAL},
	{OPM_AP|OPM_WDSAP,		"mvlan",	NULL,			cmdmvlan,	"Management VLAN settings",	"", AUTH_ADMIN, MODEL_ALL},	

//Add on 2013-06-06 by Philips to support WLAN VLAN Pass-Through for eap900 which is requested by Jacy
//Modify on 2013-08-07 by Philips to disable WLAN VLAN Pass-Through for eap900 which is requested by Jacy
//{OPM_AP|OPM_WDSAP|OPM_WDSB, "wvlanpt",	cli_table_wvlanp,	getNextTable,	"WLAN VLAN pass through",	"", AUTH_ADMIN, EAP900H_ID|C900_ID},

	{OPM_ALL,			"traffic",	cli_table_traffic,	getNextTable,	"Traffic shaping",	"", AUTH_ADMIN, MODEL_DUAL_TRAFFIC},
	{OPM_AP|OPM_AR|OPM_WDSAP|OPM_RP, "clientc",	cli_table_clientc,	getNextTable,	"Client control",	"", AUTH_ANY, MODEL_TRUE},	

//Add on 2013-03-22 by Philips to support cloud setting for C600
{OPM_ALL,	"cloud",	cli_table_cloud,	getNextTable,	"Cloud settings",	"", AUTH_ANY, C600_ID},

//Add on 2013-05-02 by Philips to support captive auth server for C600
//{OPM_ALL,	"capser",	NULL,                   cmdcapser,	"Captive auth server",	"", AUTH_ANY, C600_ID},


//Add two new models on 2013-11-04 which is asked by Po-Yao
//{OPM_ALL,	"capser",	NULL,                   cmdcapser,	"Captive auth server",	"", AUTH_ANY, C600_ID|EWS310AP_ID|EWS311AP_ID},

//Remove two models on 2013-12-04 which is asked by Jacy
{OPM_ALL,	"capser",	NULL,                   cmdcapser,	"Captive auth server",	"", AUTH_ANY, C600_ID},

	{OPM_ALL,			"snmp",		cli_table_snmp,		getNextTable,	"SNMP settings",	"", AUTH_ANY, MODEL_ALL},


//Modify by Jacky for ALL02860ND and ALL0288-ND on 2013-10-28 to disable Email Alert by using definition in macro time
#if CLI_EMAILALERT_SUPPORT
//Add on 2013-06-17 by Philips to support Email Alert for eap900 which is requested by Jacy	
	{OPM_ALL,			"email",	cli_table_email,	getNextTable,	"Email alert",		"", AUTH_ADMIN, MODEL_EMAIL},
#endif


//Modify by Jacky for ALL02860ND and ALL0288-ND on 2013-10-28 to disable SSH by using definition in macro time
#if CLI_SSH_SUPPORT
//Add on 2013-06-06 by Philips to support SSH for eap900 which is requested by Jacy	
	{OPM_ALL,			"ssh",		NULL,			cmdssh,		"SSH settings",		"", AUTH_ADMIN, MODEL_SSH},	
#endif


//Modify by Jacky for ALL02860ND and ALL0288-ND on 2013-10-28 to disable HTTPS by using definition in macro time
#if CLI_HTTPS_SUPPORT
//Add on 2013-06-06 by Philips to support HTTPS for eap900 which is requested by Jacy
	{OPM_ALL,			"https",	cli_table_https,	getNextTable,	"HTTPS settings",	"", AUTH_ADMIN, MODEL_HTTPS},
#endif

	
	{OPM_ALL,			"backup",	cli_table_bk,		getNextTable,	"Backup/Restore settings",	"", AUTH_ANY, MODEL_ALL},

//Modify for function alignment in auto reboot to all models on 2012-11-12	
//	{OPM_ALL,			"autorb",	cli_table_autoreboot,	getNextTable,	"Auto reboot settings",	"", AUTH_ANY, MODEL_SINGLE},


//Add on 2013-11-01 by Po-Yao todefine MODEL_AUTOREBOOT_SINGLE for all single-radio models to execute autoreboot command	
	{OPM_ALL,			"autorb",	cli_table_autoreboot,	getNextTable,	"Auto reboot settings",	"", AUTH_ANY, MODEL_AUTOREBOOT_SINGLE},


//Modify on 2013-07-01 by Philips to support auto reboot for eap900 which is requested by Jacy
//{OPM_ALL,	"autorb",	cli_table_newautoreboot, getNextTable,	"Auto reboot settings",	"", AUTH_ANY, EAP900H_ID|C900_ID},
{OPM_ALL,	"autorb",	cli_table_newautoreboot, getNextTable,	"Auto reboot settings",	"", AUTH_ANY, MODEL_NEW_WEB},

		
	{OPM_ALL,			"fwgrade",	cli_table_fwupgrade,	getNextTable,	"Firmware upgrade",	"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,			"time",		cli_table_time,		getNextTable,	"Time settings",	"", AUTH_ADMIN, MODEL_ALL},
	
	{OPM_AP,			"wifisch",	cli_table_wifischedule, getNextTable,	"Wifi schedule",	"", AUTH_ANY, MODEL_WIFISCH},
	
//Modify on 2013-03-04 by Philips to define MODEL_WIFISCH_CRONDJOB for new models which support wifi schedule
	{OPM_ALL,			"wifisch",	cli_table_dualwifischedule, getNextTable, "Wifi schedule",	"", AUTH_ANY, MODEL_WIFISCH_CRONDJOB},

		
//Modify on 2013-07-04 by Philips to support wifi schedule for EAP900 and C600
//{OPM_ALL,	"wifisch",	cli_table_newwifischedule, getNextTable, "Wifi schedule",	"", AUTH_ANY, EAP900H_ID|C900_ID|C600_ID},	
{OPM_ALL,	"wifisch",	cli_table_newwifischedule, getNextTable, "Wifi schedule",	"", AUTH_ANY, MODEL_NEW_WEB},

	
	{OPM_ALL,			"log",		cli_table_log,		getNextTable,	"Log",			"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,			"diag",		cli_table_diag,		getNextTable,	"Diagnostics",		"",	AUTH_ANY, MODEL_ALL},
	{OPM_ALL,			"diagv6",	cli_table_diagv6,	getNextTable,	"Diagnostics for IPV6",	"",	AUTH_ANY, MODEL_IPV6},


//Modify by Jacky for ALL02860ND and ALL0288-ND on 2013-10-29 to disable Device Discovery by using definition in macro time
#if CLI_DEVICEDISCOVERY_SUPPORT
	{OPM_ALL,			"disc",		NULL,			cmddisc,	"Device Discovery",	"",	AUTH_ANY, MODEL_ALL},
#endif


	{OPM_ALL,			"led",		cli_table_led,		getNextTable,	"Led control",		"",	AUTH_ANY, MODEL_EAP_ECB},
	{OPM_ALL,			"radio2",	cli_table_radio,	getNextTable,	"2.4G radio control",	"",	AUTH_ADMIN, MODEL_TRUE},
	{OPM_ALL,			"radio5",	cli_table_radio,	getNextTable,	"5G radio control",	"",	AUTH_ADMIN, MODEL_TRUE},	
	{OPM_ALL,			"logout",	NULL,			cmdlogout,	"Logout",		"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,			"help",   	cli_table_mgmt,         cmdHelp,	"Help",			"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,			"exit",   	NULL,			cmdexit,	"Exit",			"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};

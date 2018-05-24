#include <cli.h>
#include <settings.h>
#include <opmodes.h>

extern CliEntry cli_table_climit2[];
extern CliEntry cli_table_climit5[];

//Modify on 2013-01-03 for APSCAN doesn't support under WDSB mode which is requested by Jackey
#define OPM_APSCAN             (OPM_WDSAP|OPM_WDSSTA|OPM_RP|OPM_AP|OPM_AR|OPM_CB|OPM_CBRT)

/*********************************************/
/****************** Level 5 ******************/
/*********************************************/

CliEntry cli_table_wep[]= {
    //{OPM_ALL,   "inputt",      NULL,         cmdinputt,      "Input Type",            "", AUTH_ANY, MODEL_ALL},
    //{OPM_ALL,   "keylen",      NULL,          cmdkeylen,      "Key Length",     "", AUTH_ANY, MODEL_ALL},
    {OPM_ALL,	"dkey",		NULL,		cmddkey,	"Default Key",		"", AUTH_ANY, MODEL_ALL},
    {OPM_ALL,   "key1",		NULL,		cmdkey1,	"Key1",			"", AUTH_ANY, MODEL_ALL},
    {OPM_ALL,   "key2",		NULL,		cmdkey2,	"Key2",			"", AUTH_ANY, MODEL_ALL},
    {OPM_ALL,   "key3",		NULL,		cmdkey3,	"Key3",			"", AUTH_ANY, MODEL_ALL},
    {OPM_ALL,   "key4",		NULL,		cmdkey4,	"Key4",			"", AUTH_ANY, MODEL_ALL},
    {OPM_ALL,   "accept",	NULL, 	   	cmdwepaccept,	"Accept WEP setting",	"", AUTH_ADMIN, MODEL_ALL},
    {OPM_ALL,	"help",   	cli_table_wep,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
    {OPM_ALL,	"exit",   	NULL,		cmdapsecuexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},

    {CMD_END_TAG}
};

CliEntry cli_table_wpapsk[]= {

    {OPM_ALL,			"passp",	NULL,			cmdpassp,		"Passphrase",			"", AUTH_ANY, MODEL_ALL},
    {OPM_AP|OPM_WDSAP|OPM_AR,   "groupk",	NULL,			cmdgroupk,		"Group Key Update Interval",	"", AUTH_ANY, MODEL_ALL},
    {OPM_ALL,			"accept",  	NULL,			cmdwpapskaccept,	"Accept WPA-PSK setting",	"", AUTH_ADMIN, MODEL_ALL},
    {OPM_ALL,			"help",   	cli_table_wpapsk,	cmdHelp,		"Help",				"", AUTH_ADMIN, MODEL_ALL},
    {OPM_ALL,			"exit",   	NULL,			cmdapsecuexit,		"Exit",				"", AUTH_ADMIN, MODEL_ALL},

    {CMD_END_TAG}
};

CliEntry cli_table_wpa[]= {
	{OPM_ALL,	"radserver",	NULL,		cmdradserver,	"Radius Server",		"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"radp",		NULL,		cmdradp,	"Radius Port",			"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"radsecret",	NULL,		cmdradsecret,	"Radius Secret",		"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"groupk",	NULL,		cmdgroupk,      "Group Key Update Interval",	"", AUTH_ANY, MODEL_ALL},

//Modify on 2012-10-11 to add Radius Accounting fields   
	{OPM_ALL,	"radaccount",	NULL,		cmdradaccount,	"Radius Accounting",		"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"radaccser",	NULL,		cmdradaccser,	"Radius Accounting Server",	"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"radaccp",	NULL,		cmdradaccp,	"Radius Accounting Port",	"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"radaccsec",	NULL,		cmdradaccsec,	"Radius Accounting Secret",	"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"interval",	NULL,		cmdinterval,	"Interim Accounting Interval",	"", AUTH_ANY, MODEL_ALL},
    
	{OPM_ALL,	"accept",	NULL, 	   	cmdwpaaccept,	"Accept WPA setting",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",   	cli_table_wpa,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,		cmdapsecuexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},

    {CMD_END_TAG}
};

//Modify on 2012-11-13 for supplicant in CB, WDSSTA and CR mode
CliEntry cli_table_wpa_supplicant[]= {
	{OPM_CB|OPM_WDSSTA|OPM_CBRT,	"eapmtd",	NULL,				cmdeapmtd,	"EAP Method",			"", AUTH_ANY, MODEL_ALL},
	{OPM_CB|OPM_WDSSTA|OPM_CBRT,	"eapauth",	NULL,				cmdeapauth,	"EAP Authentication",		"", AUTH_ANY, MODEL_ALL},
	{OPM_CB|OPM_WDSSTA|OPM_CBRT,	"authid",	NULL,				cmdauthid,	"Authentication Identity",	"", AUTH_ANY, MODEL_ALL},
	{OPM_CB|OPM_WDSSTA|OPM_CBRT,	"authpwd",	NULL,				cmdauthpwd,	"Authentication Password",	"", AUTH_ANY, MODEL_ALL},
	{OPM_CB|OPM_WDSSTA|OPM_CBRT,	"accept",	NULL, 	   			cmdwpasupaccept,	"Accept WPA setting",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_CB|OPM_WDSSTA|OPM_CBRT,	"help",   	cli_table_wpa_supplicant,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_CB|OPM_WDSSTA|OPM_CBRT,	"exit",   	NULL,				cmdapsecuexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},

    {CMD_END_TAG}
};

//Modify on 2012-11-20 to add TC rate ratio 
CliEntry cli_table_tsratio2[]= {
	{OPM_WDSAP|OPM_WDSB,	"wdsr2",	NULL,			cmdwdsratio,	"2.4G WDS rate ratio",	"",	AUTH_ADMIN,	MODEL_RATIO2},
	{OPM_AP|OPM_WDSAP,	"ssidr2",	NULL,        		cmdssidratio,	"2.4G SSID rate ratio",	"",	AUTH_ANY,	MODEL_RATIO2},	
	{OPM_ALL,		"help",		cli_table_tsratio2,	cmdHelp,	"Help",			"",	AUTH_ADMIN,	MODEL_ALL},
	{OPM_ALL,		"exit",		NULL,			cmdexit,	"Exit",			"",	AUTH_ADMIN,	MODEL_ALL},
    
	{CMD_END_TAG}
};

CliEntry cli_table_tsratio5[]= {
	{OPM_WDSAP|OPM_WDSB,	"wdsr5",	NULL,			cmdwdsratio,	"5G WDS rate ratio",	"",	AUTH_ADMIN,	MODEL_RATIO5},
	{OPM_AP|OPM_WDSAP,	"ssidr5",	NULL,        		cmdssidratio,	"5G SSID rate ratio",	"",	AUTH_ANY,	MODEL_RATIO5},	
	{OPM_ALL,		"help",		cli_table_tsratio5,	cmdHelp,	"Help",			"",	AUTH_ADMIN,	MODEL_ALL},
	{OPM_ALL,		"exit",		NULL,			cmdexit,	"Exit",			"",	AUTH_ADMIN,	MODEL_ALL},
    
	{CMD_END_TAG}
};

//Modify on 2013-04-24 to add Traffic Shaping, Captive Portal and MAC filter per SSID for C600
//Modify on 2013-09-04 to add Traffic Shaping, Captive Portal and MAC filter per SSID for EAP900H and EAP1750H
CliEntry cli_table_traffic_c600[]= {
	{OPM_AP|OPM_WDSAP,	"tsact",	NULL,			cmdtsact_c600,		"Traffic Shaping active",	"", AUTH_ADMIN, MODEL_NEWTC},
	{OPM_AP|OPM_WDSAP,	"dwlimit",	NULL,			cmddwlimit_c600,	"Download limit",		"", AUTH_ADMIN, MODEL_NEWTC},
	{OPM_AP|OPM_WDSAP,	"uplimit",	NULL,			cmduplimit_c600,	"Upload limit",			"", AUTH_ADMIN, MODEL_NEWTC},
	{OPM_ALL,		"help",		cli_table_traffic_c600,	cmdHelp,		"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"exit",		NULL,			cmdexit,		"Exit",				"", AUTH_ADMIN,	MODEL_ALL},

	{CMD_END_TAG}
};

//Modify on 2013-04-24 to add Traffic Shaping, Captive Portal and MAC filter per SSID for C600
//CliEntry cli_table_mac_filter_c600[]= {
//	{OPM_AP,	"acl",	NULL,				cmdacl,		"ACL mode",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP,	"add",	NULL,				cmdadd,		"MAC address add",      "", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP,	"del",	NULL,				cmddel,		"MAC address delete",   "", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",	cli_table_mac_filter_c600,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",	NULL,				cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
//	{CMD_END_TAG}
//};
CliEntry cli_table_mac_filter[]= {
	{OPM_AP|OPM_AR|OPM_RP|OPM_WDSAP,	"acl",	NULL,			cmdacl,		"ACL mode",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_AP|OPM_AR|OPM_RP|OPM_WDSAP,	"add",	NULL,			cmdadd,		"MAC address add",      "", AUTH_ADMIN, MODEL_ALL},
	{OPM_AP|OPM_AR|OPM_RP|OPM_WDSAP,	"del",	NULL,			cmddel,		"MAC address delete",   "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,				"help",	cli_table_mac_filter,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,				"exit",	NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
    
	{CMD_END_TAG}
};

//Modify on 2013-06-13 to add Fast Roaming for the first SSID for EAP900
CliEntry cli_table_fast_roaming[]= {
	{OPM_AP|OPM_WDSAP,	"fract",	NULL,				cmdfract,	"Fast roaming active",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_AP|OPM_WDSAP,	"advsch",	NULL,				cmdadvsch,	"Advanced search",      "", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"help",		cli_table_fast_roaming,		cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"exit",		NULL,				cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
    
	{CMD_END_TAG}
};


/*********************************************/
/****************** Level 4 ******************/
/*********************************************/

CliEntry cli_table_ssidp[]= {
	{OPM_AP|OPM_AR|OPM_WDSAP,	"ssidact",	NULL,			cmdssidact,	"SSID active",			"", AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_AR|OPM_WDSAP,	"isoact",	NULL,			cmdisoact,	"Isolation active",		"", AUTH_ANY, MODEL_SINGLE},
	{OPM_AP|OPM_AR|OPM_WDSAP,	"ssid",		NULL,			cmdssid,	"SSID",				"", AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_AR|OPM_WDSAP,	"vid",		NULL,			cmdvid,		"VLAN ID",			"", AUTH_ANY, MODEL_SINGLE},
	{OPM_AP|OPM_AR|OPM_WDSAP,	"supssid",	NULL,			cmdsupssid,	"Suppressed SSID",		"", AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_AR|OPM_WDSAP,	"sepa",		NULL,			cmdsepa,	"Station separation",		"", AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_AR|OPM_WDSAP,	"apsecu",	NULL,			cmdapsecu,	"Station security",		"", AUTH_ANY, MODEL_ALL},

//Modify on 2013-04-24 to add Traffic Shaping, Captive Portal and MAC filter per SSID for C600	
//	{OPM_AP|OPM_WDSAP,   		"captive",	NULL,			cmdcaptive,	"Captive Portal active",	"", AUTH_ANY, C600_ID},
	{OPM_AP|OPM_WDSAP,		"traffic",	cli_table_traffic_c600,	getNextTable,	"Traffic shaping",		"", AUTH_ADMIN, MODEL_NEWTC},


//	{OPM_AP|OPM_WDSAP,		"macfilter",	cli_table_mac_filter,	getNextTable,	"Wireless mac filter",		"", AUTH_ANY, C600_ID|EAP900H_ID|C900_ID},


//Add two new model on 2013-11-04 which is asked by Po-Yao to support NEW MAC filter
	{OPM_AP|OPM_WDSAP,		"macfilter",	cli_table_mac_filter,	getNextTable,	"Wireless mac filter",		"", AUTH_ANY, MODEL_NEW_MACFILTER},



//Modify on 2013-06-13 to add Fast Roaming for the first SSID for EAP900
	{OPM_AP|OPM_WDSAP,		"roaming",	cli_table_fast_roaming,	getNextTable,	"Fast Roaming",			"", AUTH_ANY, EAP900H_ID|EWS320AP_ID|EWS321AP_ID|C900_ID},

	{OPM_ALL,			"help",		cli_table_ssidp,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,			"exit",		NULL,			cmdssidpexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
	{CMD_END_TAG}
};

CliEntry cli_table_aggr[]= {
	{OPM_ALL,	"aggract",	NULL,    	cmdaggract,	"Aggregation active",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"fram",    	NULL,		cmdfram,	"Frames",		"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"byte",    	NULL,		cmdbyte,	"Bytes(Max)",		"", AUTH_ANY, MODEL_ALL},
	
	{OPM_ALL,	"help",		cli_table_aggr,	cmdHelp,    	"Help",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,		cmdexit,    	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
    
	{CMD_END_TAG}
};

CliEntry cli_table_traffic[]= {
	{OPM_ALL,			"tsact",	NULL,			cmdtsact,	"Traffic Shaping active",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,			"inlimit",	NULL,			cmdinlimit,	"Incoming traffic limit",	"", AUTH_ANY, MODEL_ALL},
//Modify on 2012-11-20 to add TC rate ratio	
	{OPM_ALL,			"outlimit2",	NULL,			cmdoutlimit,	"2.4G Outgoing traffic limit",	"", AUTH_ADMIN, MODEL_2G},
	{OPM_ALL,			"outlimit5",	NULL,			cmdoutlimit,	"5G Outgoing traffic limit",	"", AUTH_ADMIN, MODEL_5G},
	{OPM_AP|OPM_WDSAP|OPM_WDSB,	"ratio2",	cli_table_tsratio2,	getNextTable,	"2.4G rate ratio",		"", AUTH_ADMIN, MODEL_RATIO2},
	{OPM_AP|OPM_WDSAP|OPM_WDSB,	"ratio5",	cli_table_tsratio5,	getNextTable,	"5G rate ratio",		"", AUTH_ANY, MODEL_RATIO5},
	{OPM_ALL,			"help",		cli_table_traffic,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,			"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},  
	{CMD_END_TAG}
};


CliEntry cli_table_links[]= {
	{OPM_ALL,	"macadd",	NULL,			cmdwdsmacadd,	"Add Link MAC address",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"enable",	NULL,			cmdwdsenable,	"Enable link MAC address",	"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"disable",	NULL,			cmdwdsdisable,	"Disable Link MAC address",	"", AUTH_ADMIN, MODEL_ALL}, 
	{OPM_ALL,	"macdel",	NULL,			cmdwdsmacdel,	"Delete Link MAC address",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",		cli_table_links,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
	{CMD_END_TAG}
};

CliEntry cli_table_wdswep[]= {
	{OPM_ALL,	"wepk",		NULL,			cmdwdswepk,		"WEP key",			"", AUTH_ANY, MODEL_ALL},
//	{OPM_ALL,	"wepklen",	NULL,			cmdwdswepklen,		"WEP key length",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"accept",  	NULL,			cmdwdswepaccept,	"Accept WDS WEP setting",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",		cli_table_wdswep,	cmdHelp,		"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",		NULL,			cmdwdssecurityexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
	{CMD_END_TAG}
};

CliEntry cli_table_wdsaes[]= {
	{OPM_ALL,	"aesp",		NULL,			cmdwdsaesp,		"AES passphrase",	"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,	"help",		cli_table_wdsaes,	cmdHelp,		"Help",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",		NULL,			cmdwdssecurityexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
	{CMD_END_TAG}
};


//Add on 2013-06-07 by Philips to support Guest Network for eap900 which is requested by Jacy
CliEntry cli_table_guestipset[]= {
	{OPM_AP|OPM_WDSAP,	"gnipaddr",	NULL,			cmdgnipaddr,	"Guest network IP address",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_AP|OPM_WDSAP,	"gnipsubn",	NULL,			cmdgnipsubn,	"Guest network IP subnet mask",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_AP|OPM_WDSAP,	"accept",  	NULL,			cmdgnipsetaccept, "Accept Guest network IP setting",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"help",		cli_table_guestipset,	cmdHelp,	"Help",					"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"exit",		NULL,			cmdexit,	"Exit",					"", AUTH_ADMIN, MODEL_ALL},    

	{ CMD_END_TAG }
};


//Add on 2013-06-07 by Philips to support Guest Network for eap900 which is requested by Jacy
CliEntry cli_table_guestdhcpset[]= {
	{OPM_AP|OPM_WDSAP,	"gnsip",	NULL,			cmdgndhcpsip,		"Starting IP Address",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_AP|OPM_WDSAP,	"gneip",	NULL,        		cmdgndhcpeip,		"Ending IP Address",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_AP|OPM_WDSAP,	"gnwip",	NULL,        		cmdgndhcpwip,		"WINS Server IP",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_AP|OPM_WDSAP,	"accept",	NULL, 	   		cmdgndhcpsetaccept,	"Accept DHCP setting",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"help",		cli_table_guestdhcpset,	cmdHelp,		"Help",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"exit",		NULL,			cmdexit,		"Exit",			"", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG }
};


//Modify on 2013-07-04 to add Mesh setting for C600 which is requested by Sam
CliEntry cli_table_meshset[]= {
	{OPM_AP,	"meshact",	NULL,			cmdmeshact,	"Mesh active",		"", AUTH_ADMIN, C600_ID},
	{OPM_AP,	"meshssid",	NULL,			cmdmeshssid,	"Mesh SSID",		"", AUTH_ADMIN, C600_ID},
	{OPM_AP,	"meshsecu",	NULL,			cmdmeshsecu,	"Mesh security",	"", AUTH_ADMIN, C600_ID},
	{OPM_AP,	"meshpassp",	NULL,			cmdmeshpassp,	"Mesh passphrase",	"", AUTH_ADMIN, C600_ID},
	{OPM_ALL,	"help",		cli_table_meshset,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG }
};


/*********************************************/
/****************** Level 3 ******************/
/*********************************************/
CliEntry cli_table_wdslink[]= {
	{OPM_ALL,	"wdssecu",	NULL,			cmdwdssecu,	"WDS security",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"links",	cli_table_links,	getNextTable,	"Link setting",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",		cli_table_wdslink,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
    
	{CMD_END_TAG}
};

//CliEntry cli_table_mac_filter[]= {
//	{OPM_AP|OPM_AR|OPM_RP|OPM_WDSAP,	"acl",	NULL,			cmdacl,		"ACL mode",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP|OPM_AR|OPM_RP|OPM_WDSAP,	"add",	NULL,			cmdadd,		"MAC address add",      "", AUTH_ADMIN, MODEL_ALL},
//	{OPM_AP|OPM_AR|OPM_RP|OPM_WDSAP,	"del",	NULL,			cmddel,		"MAC address delete",   "", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,				"help",	cli_table_mac_filter,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,				"exit",	NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
    
//	{CMD_END_TAG}
//};

CliEntry cli_table_advset[]= {
	{OPM_ALL,			"drate",	NULL,			cmddrate,	"Datarate",			"", AUTH_ADMIN, MODEL_ALL},
	

	//{OPM_ALL,			"regpower",	NULL,			cmdregpower,	"Obey regulatory power",	"", AUTH_ADMIN, MODEL_OLD_WEB},


//Add on 2013-11-20 by Philips to define MODEL_OBEY_REG_POWER for ODM models to support SKU control	
	{OPM_ALL,		"regpower",	NULL,			cmdregpower,	"Obey regulatory power",	"", AUTH_ADMIN, MODEL_OBEY_REG_POWER},

	
//Add on 2013-10-18 by Philips to define MODEL_GREEN for models to support SKU control		
	{OPM_ALL,			"green",	NULL,			cmdregpower,	"Green power",			"", AUTH_ADMIN, MODEL_GREEN},
	
	{OPM_ALL,			"txpower",	NULL,			cmdtxpower,	"Transmit power",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,			"rts", 		NULL,			cmdrts,		"RTS/CTS threshold",		"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,			"dist",		NULL,			cmddist,	"Distance",			"", AUTH_ADMIN, MODEL_OUTDOOR},
	{OPM_ALL,			"antenna",	NULL,			cmdantenna,	"Antenna Selection",		"", AUTH_ADMIN, ENH200_ID},
	{OPM_ALL,			"aggr", 	cli_table_aggr,		getNextTable,	"Aggregation",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,			"traffic",	cli_table_traffic,	getNextTable,	"Traffic shaping",		"", AUTH_ADMIN, MODEL_SINGLE},
    
	//2012-12-04 Add for models including EAP600 
	{OPM_AP|OPM_AR|OPM_WDSAP|OPM_RP,"climit2",	cli_table_climit2,	getNextTable,	"2.4G client limitation",	"", AUTH_ANY, MODEL_CLIMIT},
	{OPM_AP|OPM_AR|OPM_WDSAP|OPM_RP,"climit5",	cli_table_climit5,	getNextTable,	"5G client limitation",		"", AUTH_ANY, MODEL_CLIMIT},
	
	{OPM_ALL,			"help",		cli_table_advset,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,			"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
    
	{CMD_END_TAG}
};

CliEntry cli_table_network[]= {

//Modify on 2013-04-30 to add Mesh enable for C600
//	{OPM_AP,				"meshact",	NULL,			cmdmeshact,	"Mesh active",		"", AUTH_ADMIN, C600_ID},

//Modify on 2013-07-04 to add Mesh setting for C600 which is requested by Sam	
	{OPM_AP,				"mesh",		cli_table_meshset,	getNextTable,	"Mesh settings",	"", AUTH_ANY, C600_ID},

	
	{OPM_ALL,				"wlmode",	NULL,   		cmdwlmode,	"Wireless mode",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_AP|OPM_AR|OPM_WDSB|OPM_WDSAP,	"htmode",	NULL,   		cmdhtmode,	"Channel ht mode",	"", AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_AR|OPM_WDSB|OPM_WDSAP,	"extch",	NULL,   		cmdextch,	"Extension channel",	"", AUTH_ADMIN, MODEL_2G},
	{OPM_AP|OPM_AR|OPM_WDSB|OPM_WDSAP,	"ch",		NULL,    		cmdchannel,	"Channel/Frequency",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_AP|OPM_AR|OPM_WDSAP,		"ssidp",	NULL,   		cmdssidp,	"SSID Profile",		"", AUTH_ADMIN, MODEL_ALL},

	{OPM_CB|OPM_CBRT|OPM_RP|OPM_WDSSTA,	"stassid",    	NULL,    		cmdstassid,	"Static SSID",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_CB|OPM_CBRT|OPM_RP|OPM_WDSSTA,	"bssidact",    	NULL,   		cmdbssidact,	"Prefered BSSID active","", AUTH_ADMIN, MODEL_ALL},
	{OPM_CB|OPM_CBRT|OPM_RP|OPM_WDSSTA,	"bssid",    	NULL,   		cmdbssid,	"Prefered BSSID",	"", AUTH_ADMIN, MODEL_ALL},

	//2012-09-24 Add for TRUE Project
	{OPM_APSCAN,				"apscan",	NULL,			cmdapscan,	"Site survey",		"", AUTH_ADMIN, MODEL_ALL},

	{OPM_CB|OPM_CBRT|OPM_RP|OPM_WDSSTA,	"secu",		NULL,			cmdsecu,	"Security Mode",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,				"help",		cli_table_network,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,				"exit",		NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},

    {CMD_END_TAG}
};


//Add on 2013-06-07 by Philips to support Guest Network for eap900 which is requested by Jacy
CliEntry cli_table_guestnetwork[]= {
	{OPM_AP|OPM_WDSAP,	"gnact",	NULL,			cmdgnact,	"Guest network active",		"", AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_WDSAP,	"gnssid",	NULL,			cmdgnssid,	"Guest network SSID",		"", AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_WDSAP,	"gnsupssid",	NULL,			cmdgnsupssid,	"Suppressed SSID",		"", AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_WDSAP,	"gnsepa",	NULL,			cmdgnsepa,	"Station separation",		"", AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_WDSAP,	"gnapsecu",	NULL,			cmdgnapsecu,	"Station security",		"", AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_WDSAP,	"gnip",		cli_table_guestipset,	getNextTable,	"Guest network IP settings",	"", AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_WDSAP,	"gndhcp",   	cli_table_guestdhcpset,	getNextTable,	"Guest network As DHCP Server",	"", AUTH_ANY, MODEL_ALL},
	{OPM_ALL,		"help",		cli_table_guestnetwork,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},

	{CMD_END_TAG}
};


//Add on 2013-06-06 by Philips to support Fast Handover for eap900 which is requested by Jacy
static CliEntry cli_table_fasthandover[]= {
	{OPM_ALL,	"fhact",	NULL,				cmdfhact,	"Fast handover active",	"", 	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"fhrssi",	NULL, 	   			cmdfhrssi,	"Fast handover rssi",	"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",   	cli_table_fasthandover,		cmdHelp,	"Help",			"",	AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",   	NULL,				cmdexit,	"Exit",			"",	AUTH_ADMIN, MODEL_ALL},

	{ CMD_END_TAG}
};


/*********************************************/
/****************** Level 2 ******************/
/*********************************************/
CliEntry cli_table_wless[]= {
	{OPM_WDSB|OPM_WDSAP,	"wdslink",	cli_table_wdslink,	getNextTable,	"WDS link settings",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"network",	cli_table_network,	getNextTable,	"Wireless network",		"", AUTH_ADMIN, MODEL_ALL},


//Modify by Jacky for ALL02860ND and ALL0288-ND on 2013-10-28 to disable Guest Network by using definition in macro time
#if CLI_GUESTNETWORK_SUPPORT
//Add on 2013-06-07 by Philips to support Guest Network for eap900 which is requested by Jacy
	{OPM_AP|OPM_WDSAP,	"guest",	cli_table_guestnetwork,	getNextTable,	"Wireless guest network",	"", AUTH_ADMIN, MODEL_GUEST},
#endif

	
//Modify for C600 on 2013-05-02 to disable MAC filter	
//	{OPM_AP|OPM_AR|OPM_RP|OPM_WDSAP, "macfilter",	cli_table_mac_filter,	getNextTable,	"Wireless mac filter",	"", AUTH_ANY, MODEL_ALL},
	{OPM_AP|OPM_AR|OPM_RP|OPM_WDSAP,"macfilter",	cli_table_mac_filter,	getNextTable,	"Wireless mac filter",	"", AUTH_ANY, MODEL_ALL_MACFILTER},	
	
	{OPM_ALL,		"advset",	cli_table_advset,	getNextTable,	"Wireless advanced settings",	"", AUTH_ANY, MODEL_ALL},

//Add on 2013-06-06 by Philips to support Fast Handover for eap900 which is requested by Jacy	
	{OPM_ALL,		"fhandover",	cli_table_fasthandover,	getNextTable,	"Fast handover",		"", AUTH_ADMIN, EAP900H_ID|EWS320AP_ID|EWS321AP_ID|C900_ID},
	
	{OPM_ALL,		"help",		cli_table_wless,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},
	
	{CMD_END_TAG}
};


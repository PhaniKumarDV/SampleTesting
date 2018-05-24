#include <cli.h>
#include <settings.h>
#include <opmodes.h>

#define OPM_IP			(OPM_AP | OPM_CB | OPM_RP | OPM_WDSAP | OPM_WDSSTA | OPM_WDSB)
#define OPM_IPV6		(OPM_AP | OPM_CB | OPM_WDSAP | OPM_WDSSTA | OPM_WDSB)
#define OPM_STP			(OPM_AP | OPM_CB | OPM_RP | OPM_WDSAP | OPM_WDSSTA | OPM_WDSB)

extern CliEntry cli_table_bsteer[];

/*********************************************/
/****************** Level 4 ******************/
/*********************************************/
CliEntry cli_table_ipset[]= {
	{OPM_ALL,	"ipaddr",	NULL,			cmdipaddr,	"IP address",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"ipsubn",	NULL,			cmdipsubn,	"IP subnet mask",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"gateway",	NULL,			cmdgateway,	"Default gateway",		"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"pdns",		NULL,			cmdpdns,        "Primary dns",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"sdns",		NULL,			cmdsdns,        "Secondary dns",		"", AUTH_ADMIN, MODEL_ALL},

//Modify on 2012-10-26 to add IPV6 fields    
	{OPM_ALL,	"link6",	NULL,			cmdlink6,	"Use link-local address",	"", AUTH_ADMIN, MODEL_IPV6},
	{OPM_ALL,	"ipaddr6",	NULL,			cmdipaddr6,	"IPv6 address",			"", AUTH_ADMIN, MODEL_IPV6},
	{OPM_ALL,	"sublen6",	NULL,			cmdsublen6,	"IPV6 subnet prefix length",	"", AUTH_ADMIN, MODEL_IPV6},
	{OPM_ALL,	"gateway6",	NULL,			cmdgateway6,	"IPv6 gateway",			"", AUTH_ADMIN, MODEL_IPV6},
	{OPM_ALL,	"pdns6",	NULL,			cmdpdns6,	"IPv6 Primary dns",		"", AUTH_ADMIN, MODEL_IPV6},
	{OPM_ALL,	"sdns6",	NULL,			cmdsdns6,	"IPv6 Secondary dns",		"", AUTH_ADMIN, MODEL_IPV6},
	
	{OPM_ALL,	"accept",  	NULL,			cmdipsetaccept,	"Accept LAN IP setting",	"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"help",		cli_table_ipset,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,	"exit",		NULL,			cmdipsetexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},    
	{ CMD_END_TAG }
};	
	
/*********************************************/
/****************** Level 3 ******************/
/*********************************************/
CliEntry cli_table_ip[]= {
	{OPM_ALL,	"dhcpact",	NULL,		cmddhcpact,	"DHCP active",	"", AUTH_ADMIN,	MODEL_ALL},
	{OPM_ALL,   	"help",		cli_table_ip,	cmdHelp,	"Help",		"", AUTH_ADMIN,	MODEL_ALL},
   	{OPM_ALL,   	"exit",		NULL,		cmdexit,	"Exit",		"", AUTH_ADMIN,	MODEL_ALL},
	{ CMD_END_TAG }
};

static CliEntry cli_table_stp[]= {
	{OPM_ALL,	"stpstat",	NULL,		cmdstpstat,	"Spanning tree status",	"", AUTH_ANY,	MODEL_ALL},
	{OPM_ALL,	"htime",	NULL,		cmdhtime,	"Bridge hello time",	"", AUTH_ADMIN,	MODEL_ALL},
	{OPM_ALL,	"mage",		NULL,		cmdmage,	"Bridge max age",	"", AUTH_ADMIN,	MODEL_ALL},
	{OPM_ALL,	"fdelay",	NULL,  		cmdfdelay,      "Bridge forward delay",	"", AUTH_ANY,	MODEL_ALL},
	{OPM_ALL,	"prio",		NULL,		cmdprio, 	"Priority",		"", AUTH_ANY,	MODEL_ALL},
	{OPM_ALL,	"help",		cli_table_stp,	cmdHelp,	"Help",			"", AUTH_ADMIN,	MODEL_ALL},
	{OPM_ALL,	"exit",		NULL,		cmdexit,	"Exit",			"", AUTH_ADMIN,	MODEL_ALL},
	{ CMD_END_TAG }
};

CliEntry cli_table_opmode[]= {
	{OPM_ALL,		"devname",	NULL,			cmddevname,	"Device name",		"", AUTH_ADMIN, MODEL_ALL},


//Add on 2013-11-20 by Philips to support Green Power control for OLD_WEB models which is requested by Jacy	
	{OPM_ALL,		"green",	NULL,			cmdregpower,	"Green power",		"", AUTH_ADMIN, MODEL_OLD_WEB_GREEN},


	{OPM_ALL,		"ctry",		NULL,			cmdctry,	"Country/Region",	"", AUTH_ADMIN, MODEL_ALL},
	
//Add on 2013-06-11 by Philips to support Band Steering for eap900 which is requested by Jacy	
	{OPM_AP|OPM_WDSAP,	"bsteer",	cli_table_bsteer,	getNextTable,	"Band steering",	"", AUTH_ADMIN, MODEL_DUAL_BANDSTEER},
	
	{OPM_ALL,		"opmode",	NULL,			cmdopmode,	"Operation mode",	"", AUTH_ADMIN, MODEL_SINGLE},
	{OPM_ALL,		"opmode2",	NULL,			cmdopmode,	"2.4G Operation mode",	"", AUTH_ADMIN, MODEL_DUAL},
	{OPM_ALL,		"opmode5",	NULL,			cmdopmode,	"5G Operation mode",	"", AUTH_ADMIN, MODEL_DUAL},
	{OPM_ALL,		"help",		cli_table_opmode,	cmdHelp,	"Help",			"", AUTH_ADMIN, MODEL_ALL},
	{OPM_ALL,		"exit",		NULL,			cmdexit,	"Exit",			"", AUTH_ADMIN, MODEL_ALL},
	{ CMD_END_TAG }
};

//CliEntry cli_table_ipv6set[]= {
//	{OPM_ALL,	"link6",	NULL,			cmdlink6,	"Use link-local address",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"ipaddr6",	NULL,			cmdipaddr6,	"IPv6 address",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"sublen6",	NULL,			cmdsublen6,	"IPV6 subnet prefix length",	"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"gateway6",	NULL,			cmdgateway6,	"IPv6 gateway",			"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"pdns6",	NULL,			cmdpdns6,	"IPv6 Primary dns",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"sdns6",	NULL,			cmdsdns6,	"IPv6 Secondary dns",		"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"help",		cli_table_ipv6set,	cmdHelp,	"Help",				"", AUTH_ADMIN, MODEL_ALL},
//	{OPM_ALL,	"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN, MODEL_ALL},  
//	{ CMD_END_TAG }
//};

/*********************************************/
/****************** Level 2 ******************/
/*********************************************/
CliEntry cli_table_sys[]= {
	{OPM_ALL,		"opmode",	cli_table_opmode,	getNextTable,	"Operation mode",		"", AUTH_ADMIN,	MODEL_ALL},
	{OPM_IP,		"ip",		cli_table_ip,		getNextTable,	"IP settings",			"", AUTH_ANY,	MODEL_ALL},  
	{OPM_STP,		"stp",		cli_table_stp,		getNextTable,	"Spanning tree settings",	"", AUTH_ANY,	MODEL_ALL},
	
	//Add for function alignment of Band Steer for EAP600 , ECB600 and ENH700EXT on 2012-12-04
//Disable Band Steer for EAP600 , ECB600 and ENH700EXT which is requested by Jacy on 2012-12-25
//	{OPM_AP|OPM_WDSAP,	"bsteer",	cli_table_bsteer,	getNextTable,	"Band steering",	"", AUTH_ADMIN, EAP600_ID|ECB600_ID|ENH700EXT_ID},
	
	{OPM_ALL,		"help",		cli_table_sys,		cmdHelp,	"Help",				"", AUTH_ADMIN,	MODEL_ALL},
	{OPM_ALL,		"exit",		NULL,			cmdexit,	"Exit",				"", AUTH_ADMIN,	MODEL_ALL},
	{ CMD_END_TAG }
};

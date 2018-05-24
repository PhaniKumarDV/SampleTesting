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
/*********************************************/
/****************** Level 5 ******************/
/*********************************************/
CliEntry cli_table_wanipset[]= {
	{WAN_OPM,   "wanipaddr",    NULL,     cmdwanipaddr,       "Internet IP address",     "", 	AUTH_ANY, MODEL_ALL},
	{WAN_OPM,   "wanipsubn",    NULL,      cmdwanipsubn,      "Internet IP subnet mask",  "", AUTH_ADMIN, MODEL_ALL},
	{WAN_OPM,   "wangateway",    NULL,    cmdwangateway,      "Gateway IP address",      "", AUTH_ADMIN, MODEL_ALL},
//	{WAN_OPM,   "pdns",    	NULL,                   cmdpdns,          	 "Primary DNS address",     "", AUTH_ADMIN, MODEL_ALL},
//	{WAN_OPM,   "sdns",    	NULL,                   cmdsdns,          	 "Secondary DNS address",     "", AUTH_ADMIN, MODEL_ALL},
	{WAN_OPM,   "accept",  	NULL, 	   cmdwanipsetaccept,      "Accept WAN IP setting",   "", AUTH_ADMIN, MODEL_ALL},
	{WAN_OPM,   "help",   cli_table_wanipset,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
	{WAN_OPM,   "exit",   NULL,         cmdwanipsetexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},
    
    { CMD_END_TAG }
};

/*********************************************/
/****************** Level 4 ******************/
/*********************************************/
CliEntry cli_table_wandhcp[]= {
    {WAN_OPM,   "accname",  	NULL,     		 cmdaccname,      "Account name",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "domname",    	NULL,                   cmddomname,           "Domain name",     "", 	AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "mtumode",    	 NULL,                   cmdmtumode,           "MTU mode",      "", 		AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "mtulen",    	 NULL,                   cmdmtulen,           "MTU length",      "", 		AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "dnsmode",    	NULL,                   cmddnsmode,          	 "Domain name server mode",     "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "pdns",    	NULL,                   cmdpdns,          	 "Primary DNS address",     "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "sdns",    	NULL,                   cmdsdns,          	 "Secondary DNS address",     "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_wandhcp,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdconntypeexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},
    { CMD_END_TAG }
};

CliEntry cli_table_wanstaticip[]= {
    {WAN_OPM,   "accname",  	NULL,     	cmdaccname,      "Account name",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "domname",    	NULL,           cmddomname,           "Domain name",     "", 	AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "mtumode",    	 NULL,         cmdmtumode,           "MTU mode",      "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "mtulen",    	 NULL,         cmdmtulen,           "MTU length",      "", 	AUTH_ADMIN, MODEL_ALL},
    
    {OPM_ALL,   "ipset",    cli_table_wanipset,       getNextTable,      "WAN IP setting",  "", AUTH_ADMIN, MODEL_ALL},
    
    {WAN_OPM,   "pdns",    	NULL,       cmdpdns,          	 "Primary DNS address",     "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "sdns",    	NULL,        cmdsdns,          	 "Secondary DNS address",     "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_wanstaticip,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdconntypeexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},
    { CMD_END_TAG }
};

CliEntry cli_table_wanpppoe[]= {
    {WAN_OPM,   "mtumode",    	 NULL,         cmdmtumode,           "MTU mode",      "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "mtulen",    	 NULL,         cmdpppoemtulen,           "MTU length",      "", 	AUTH_ADMIN, MODEL_ALL},
    
    {WAN_OPM,   "login",  	NULL,      cmdlogin,      "Login account",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "passw",    	NULL,       cmdpppoepassw,           "Password",     "", 	AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "sname",    	 NULL,     cmdsname,       "Service name",      "", 		AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "conmode",    	NULL,      cmdconmode,    "Connect on demand/Auto redial",     "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "idle",    	NULL,      cmdidle,      "Max idle time",     "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "period",    	NULL,      cmdperiod,      "Redial period",     "", AUTH_ADMIN, MODEL_ALL},
    
    {WAN_OPM,   "dnsmode",    	NULL,     cmddnsmode,   "Domain name server mode",     "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "pdns",    	NULL,     cmdpdns,      "Primary DNS address",     "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "sdns",    	NULL,     cmdsdns,      "Secondary DNS address",     "", AUTH_ADMIN, MODEL_ALL},
    
    {WAN_OPM,   "help",   cli_table_wanpppoe,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdconntypeexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},
    { CMD_END_TAG }
};

CliEntry cli_table_wanpptp[]= {
    {WAN_OPM,   "mtumode",    	 NULL,         cmdmtumode,           "MTU mode",      "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "mtulen",    	 NULL,         cmdpptpmtulen,           "MTU length",      "", 	AUTH_ADMIN, MODEL_ALL},
    {OPM_ALL,   "ipset",    cli_table_wanipset,       getNextTable,      "WAN IP setting",  "", AUTH_ADMIN, MODEL_ALL},	
//    {WAN_OPM,   "wanipaddr",    NULL,     cmdwanipaddr,         "Internet IP address",     "", 	AUTH_ANY, MODEL_ALL},
//    {WAN_OPM,   "wanipsubn",    NULL,      cmdwanipsubn,      "Internet IP subnet mask",  "", 	AUTH_ADMIN, MODEL_ALL},
//    {WAN_OPM,   "wangateway",    NULL,    cmdwangateway,       "Gateway IP address",      "", AUTH_ADMIN, MODEL_ALL},    
    {WAN_OPM,   "pptps",    NULL,    cmdpptps,       "PPTP server",      "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "username",    NULL,    cmdpptpusername,       "Username",      "", AUTH_ADMIN, MODEL_ALL},    
    {WAN_OPM,   "passw",    NULL,    cmdpptppassw,       "Password",      "", AUTH_ADMIN, MODEL_ALL},        
    {WAN_OPM,   "conmode",    	NULL,      cmdconmode,    "Connect on demand/Auto redial",     "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "idle",    	NULL,      cmdidle,      "Max idle time",     "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "period",    	NULL,      cmdperiod,      "Redial period",     "", AUTH_ADMIN, MODEL_ALL},

    {WAN_OPM,   "dnsmode",    	NULL,     cmddnsmode,   "Domain name server mode",     "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "pdns",    	NULL,     cmdpdns,      "Primary DNS address",     "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "sdns",    	NULL,     cmdsdns,      "Secondary DNS address",     "", AUTH_ADMIN, MODEL_ALL},

    {WAN_OPM,   "help",   cli_table_wanpptp,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdconntypeexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},
    { CMD_END_TAG }
};


static CliEntry cli_table_pfadd[]= {
    {WAN_OPM,   "setname",  	NULL, 	   	cmdportforwardser,      "Set port forwarding service name",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "setpro",  	NULL,     	cmdportforwardsetpro,      "Set protocol",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "setsport",  	NULL,     	cmdportforwardsetsport,      "Set start port",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "seteport",  	NULL,     	cmdportforwardseteport,      "Set end port",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "setipaddr",  	NULL,     	cmdportforwardsetipaddr,      "Set IP address",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "accept",  	NULL, 	   	cmdportforwardaccept,      "Accept port forwarding setting",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_pfadd,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdportforwardexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};

static CliEntry cli_table_ptadd[]= {
    {WAN_OPM,   "setname",  	NULL, 	   	cmdporttriggerser,      "Set port trigger service name",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "setsport",  	NULL,     	cmdporttriggersetsport,      "Set trigger start port",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "seteport",  	NULL,     	cmdporttriggerseteport,      "Set trigger end port",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "settgtype",  	NULL,     	cmdporttriggersettgtype,      "Set trigger type",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "setfport",  	NULL,     	cmdporttriggersetfport,      "Set forwarded port",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "setpbtype",  	NULL,     	cmdporttriggersetpbtype,      "Set public type",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "accept",  	NULL, 	   	cmdporttriggeraccept,      "Accept port trigger setting",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_ptadd,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdporttriggerexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};

static CliEntry cli_table_macadd[]= {
    {WAN_OPM,   "setname",  	NULL, 	   	cmdmacser,      "Set MAC service name",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "setmac",  	NULL,     	cmdmacaddr,      "Set MAC address",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "accept",  	NULL, 	   	cmdmacaccept,      "Accept MAC filter setting",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_macadd,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdroutermacfilterexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};

static CliEntry cli_table_ipadd[]= {
    {WAN_OPM,   "setname",  	NULL, 	   	cmdipser,      "Set IP service name",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "setpro",  	NULL,     	cmdipsetpro,      "Set protocol",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "setsip",  	NULL,     	cmdipsetsip,      "Set start IP",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "seteip",  	NULL,     	cmdipseteip,      "Set end IP",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "setsport",  	NULL,     	cmdipsetsport,      "Set start port",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "seteport",  	NULL,     	cmdipseteport,      "Set end port",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "accept",  	NULL, 	   	cmdipaccept,      "Accept IP filter setting",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_ipadd,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdipfilterexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};

/*
static CliEntry cli_table_lanipset[]= {
    {WAN_OPM,   "ipaddr",  	NULL, 	   	cmdlanipaddress,      "IP address",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "ipsubn",  	NULL,     	cmdlanipsubnet,      "IP subnet mask",   "", 	AUTH_ADMIN, MODEL_ALL},
    //{WAN_OPM,   "accept",  	NULL, 	   	cmdlanipaccept,      "Accept LAN IP setting",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_lanipset,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    //{WAN_OPM,   "exit",   NULL,         cmdlanipsetexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},
    

    { CMD_END_TAG }
};
*/
CliEntry cli_table_dhcpset[]= {
    {WAN_OPM,   "sip",		NULL,   	cmddhcpsip,      "Starting IP Address",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "eip",      NULL,        	cmddhcpeip,      "Ending IP Address",     "", AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "wip",      NULL,        	cmddhcpwip,      "WINS Server IP",     "", AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "accept",  	NULL, 	   	cmddhcpsetaccept,     "Accept DHCP setting",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_dhcpset,        cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmddhcpsetexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},
    //{WAN_OPM,   "exit",   NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};

/*********************************************/
/****************** Level 3 ******************/
/*********************************************/
static CliEntry cli_table_wan[]= {
    {WAN_OPM,   "conntype",  	NULL, 	   		cmdconntype,      "Internet connection type",   "", AUTH_ADMIN, MODEL_ALL},

    {WAN_OPM,   "disping",     	NULL,                   cmddisping,           "Discard ping on WAN",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_wan,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};

static CliEntry cli_table_lan[]= {
    {WAN_OPM,   "ipaddr",  	NULL, 	   	cmdlanipaddress,      "IP address",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "ipsubn",  	NULL,     	cmdlanipsubnet,      "IP subnet mask",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "dhcpset",    	NULL,           cmddhcpset,      "Router As DHCP Server",     "", 	AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_lan,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};

static CliEntry cli_table_vpn_pass_through[]= {
    {WAN_OPM,   "pptp",  	NULL, 	   		cmdpptp,      "PPTP pass through",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "l2tp",  	NULL,     		cmdl2tp,      "L2TP pass through",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "ipsec",    	NULL,                   cmdipsec,      "IPSec pass through",     "", 	AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_vpn_pass_through,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};

static CliEntry cli_table_pf[]= {
    {WAN_OPM,   "pflist",  	NULL,     	cmdpflist,      "Display port forwarding list",   "", 	AUTH_ADMIN, MODEL_ALL},    
    {WAN_OPM,   "pfact",  	NULL, 	   		cmdpfact,      "Port forwarding active",   "", AUTH_ADMIN, MODEL_EAP_ECB},
    {WAN_OPM,   "pfadd",  	cli_table_pfadd,     	getNextTable,      "Port forwarding add",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "pfdel",    	NULL,                   cmdpfdel,      "Port Forwarding delete",     "", 	AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "pfenable",    	NULL,                   cmdpfenable,      "Port Forwarding enable",     "", 	AUTH_ANY, MODEL_ENH},    
    {WAN_OPM,   "pfdisable",    NULL,           cmdpfdisable,      "Port Forwarding disable",     "", 	AUTH_ANY, MODEL_ENH},
    {WAN_OPM,   "help",   cli_table_pf,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};

static CliEntry cli_table_pt[]= {
    {WAN_OPM,   "ptlist",  	NULL,     	cmdptlist,      "Display port triggering list",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "ptact",  	NULL, 	   		cmdptact,      "Port trigger active",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "ptadd",  	cli_table_ptadd,     	getNextTable,      "Port trigger add",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "ptdel",    	NULL,                   cmdptdel,      "Port trigger delete",     "", 	AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_pt,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};

static CliEntry cli_table_dmz[]= {
    {WAN_OPM,   "dmzact",  	NULL,   		 cmddmzact,      "DMZ active",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "dmzaddr",      NULL,        		 cmddmzaddr,      "DMZ address ",     "", AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_dmz,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};

static CliEntry cli_table_mac_filter[]= {
    {WAN_OPM,   "maclist",  	NULL,     	cmdmaclist,      "Display MAC filter list",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "macact",  	NULL, 	   		cmdmacact,      "MAC filter active",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "macmode",     	NULL,                   cmdmacmode,     "MAC filter deny/allow",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "macadd",  	cli_table_macadd,     	getNextTable,    "MAC filter add",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "macdel",    	NULL,                   cmdmacdel,      "MAC filter delete",     "", 	AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_mac_filter,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};

static CliEntry cli_table_ip_filter[]= {
    {WAN_OPM,   "ipact",  	NULL, 	   		cmdipact,      		"IP filter active",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "ipmode",     	NULL,                   cmdipmode,     		"IP filter deny/allow",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "ipadd",  	cli_table_ipadd,     	getNextTable,      	"IP filter add",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "ipdel",    	NULL,                   cmdipdel,      		"IP filter delete",     "", 	AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_ip_filter,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};

static CliEntry cli_table_url_filter[]= {
    {WAN_OPM,   "urlact",  	NULL, 	   		cmdurlact,      		"URL filter active",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "urladd",  	NULL,     		cmdurladd,      		"URL filter add",   "", 	AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "urldel",    	NULL,                   cmdurldel,      		"URL filter delete",     "", 	AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "help",   cli_table_url_filter,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};


/*********************************************/
/****************** Level 2 ******************/
/*********************************************/
CliEntry cli_table_rout[]= {
    {WAN_OPM,   "wan", 		 cli_table_wan,    	   getNextTable,          "WAN settings",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "lan",  	cli_table_lan,    	   getNextTable,          "LAN settings",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "vpn",      cli_table_vpn_pass_through, getNextTable,           "VPN pass through",             "", AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "pf",  	cli_table_pf,    	   	getNextTable,          "Port forwarding",   "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "pt", 	 cli_table_pt,    	   	getNextTable,          "Port triggering",   "", AUTH_ADMIN, MODEL_EAP_ECB},
    {WAN_OPM,   "dmz",     cli_table_dmz, 		getNextTable,           "DMZ",           "", AUTH_ANY, MODEL_ALL},
    {WAN_OPM,   "mac",     cli_table_mac_filter,       getNextTable,           "MAC filter",            "", AUTH_ANY, MODEL_EAP_ECB},
    {WAN_OPM,   "ip",      cli_table_ip_filter,        getNextTable,           "IP filter",             "", AUTH_ANY, MODEL_EAP_ECB},
    {WAN_OPM,   "url",     cli_table_url_filter,       getNextTable,           "URL filter",             "", AUTH_ANY, MODEL_EAP_ECB},
    {WAN_OPM,   "help",   cli_table_rout,         cmdHelp,    "Help", "", AUTH_ADMIN, MODEL_ALL},
    {WAN_OPM,   "exit",   NULL,         cmdexit,    "Exit", "", AUTH_ADMIN, MODEL_ALL},

    { CMD_END_TAG }
};



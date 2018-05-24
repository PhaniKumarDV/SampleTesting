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
;    Creator : Norkay
;    File    : cli.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       Norkay            2007-0322       Create
;*****************************************************************************/
//Add on 2012-12-17 to keep the CLI Version which is requested by Albert
#define	CLI_VERSION		"V-1.8.16"
#define CLI_RELEASE_DATE	"2013-12-05"

#ifndef _CLI_H_
#define _CLI_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <sap_ostypes.h>

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
//#define CMD_END_TAG "ln,mnzlkerz"
#define CMD_END_TAG 0xffffffff
//#define CMD_PROMPT  "cmd>"


#define MAX_TOKEN_STACK_LEN 64
#define MAX_TAB_CMD_NUM     100

#define tprintf printf

#define CLI_BODY_HR			"------------------------------------------------------\n"
#define CLI_BODY_TITLE		"======================================================\n"\
							"%s\n"\
							"======================================================\n"

#define CLI_BODY_STR_CONTEXT		"%20s: %s\n"
#define CLI_BODY_INT_CONTEXT		"%20s: %d\n"
#define CLI_BODY_IP_CONTEXT			"%20s: %s:%d\n"

#define CLI_LIST_INFO_QUESTION		"whice one you want to show more information? "
#define CLI_LIST_NOT_EXISTED		"%s %d is not existed.\n"
#define CLI_LIST_NEW_FULL			"%s is full.\n"
#define CLI_LIST_EDIT_QUESTION		"whice one you want to edit? "
#define CLI_LIST_DELETE_QUESTION	"whice one you want to delete? "
#define CLI_LIST_DELETE_OK			"%s %d is deleted.\n"
#define CLI_LIST_DELETE_REJECT		"%s 1 can't be deleted.\n"
#define CLI_LIST_EMPTY				"==> %s is empty.\n"
#define CLI_LIST_DUPLICATE			"Sorry, %s is duplicate!\n"

#define CLI_TITLE_WIDTH  	16
#define CLI_DEFAULT_WIDTH	60	// show options use
#define CLI_RESERVE_WIDTH   8	// show options use
#define CLI_TITLE_SPACE     "                " // 16 space
#if HAS_VLAN_SUPPORT
#define MAX_VLAN_TAG_NUM 4094
#endif
/*-------------------------------------------------------------------------*/
/*                           enum & struct                                 */
/*-------------------------------------------------------------------------*/
typedef enum { 
	CLI_OK=0,
	CLI_CURRENT_OK,
	CLI_NOTHING, 
	CLI_NO_MATCH, 
	CLI_PARAMS_ERR, 
	CLI_NOAUTH 
} CliStatus;

typedef enum { 
	AUTH_ANY=0, 
	AUTH_ADMIN,
	AUTH_VENDOR,
	AUTH_FACTORY,
	AUTH_SUPER
} AuthStatus;

/*
 *   Private Structure
 */
struct __CliData;

typedef CliStatus (*CliHandle)(T_VOID* priv, struct __CliData* cliData) ;

typedef struct __CliEntry
{
	T_UINT32 opMode;         /* use/not use based on the AP operation mode, e.g. AP, Router, CB, etc.*/
	const T_CHAR* cmdName;
	T_VOID* priv;
	CliHandle handler;
	const T_CHAR* description;
	const T_CHAR* usage;
	T_INT32 authority;  /* use for hidden for command */

//	const T_INT32 modelID;

	//Modify on 2013-09-05 to extend the number of Model to 64
	const long long modelID;

} CliEntry;

typedef struct __CliEntryList
{
	const T_CHAR* token; 	/* token value */
	CliEntry* entry;   		/* pointer to CliEntry belong to this token*/
} CliEntryList;

typedef struct __CliData
{
    CliEntryList tokens[MAX_TOKEN_STACK_LEN];
    T_INT32 curLv;    /* current level for tokens array */
    T_INT32 argc;     /* remain how many tokens for current level */
    T_INT32 tokenLen; /* Total tokens that cli get */
    T_INT32 mode;
} CliData;


/*-------------------------------------------------------------------------*/
/*                           FUNCTIONS                                     */
/*-------------------------------------------------------------------------*/
CliStatus setApCfgValue(T_VOID* priv, CliData* cliData);
CliStatus getNextTable(T_VOID* priv, CliData* cliData);
const T_CHAR* getNextToken(const CliData* cliData, const T_INT32 idx);
T_INT32 getStdInCommand(T_CHAR* srcBuf, T_INT32 srcLen);
T_INT32 getApCfgStructureListShow(const T_CHAR* strPrefix, const T_CHAR* tokenPrefix, const T_INT32 numofTokens);
T_VOID showOption(const T_CHAR* token);

#endif

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
;    Creator : adam
;    File    : cli_diag.h
;    Abstract: 
;
;       Modification History:
;       By              Date     Ver.   Modification Description
;       --------------- -------- -----  --------------------------------------
;       Adam            2009-0420       Create
;*****************************************************************************/
#ifndef _CLI_DIAG_H_
#define _CLI_DIAG_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/
#include <cli.h>
#include <gconfig.h>
/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/
typedef struct
{
	char *state;
	char interface[256+1];
	char host[256+1];
	unsigned int num_of_repetitions;
	unsigned int timeout;
	unsigned int data_block_size;
	unsigned int dscp; 
} PING_TEST_CONF;

#if HAS_TRACE_ROUTE
typedef struct
{
	char host[256+1];
	unsigned int query;
	unsigned int wait_time;
	unsigned int max_hops;
} TRACERT_TEST_CONF;
#endif

/*-------------------------------------------------------------------------*/
/*                           FUNCTIONS                                     */
/*-------------------------------------------------------------------------*/
void diagnosticTestInit(void);
CliStatus cmdPingStatus(T_VOID* priv, CliData* cliData);
CliStatus cmdPingHost(T_VOID* priv, CliData* cliData);
CliStatus cmdPingBlockSize(T_VOID* priv, CliData* cliData);
CliStatus cmdPingCount(T_VOID* priv, CliData* cliData);
CliStatus cmdPingTest(T_VOID* priv, CliData* cliData);
CliStatus cmdSimplePing(T_VOID* priv, CliData* cliData);
#if HAS_TRACE_ROUTE
CliStatus cmdTraceRtStatus(T_VOID* priv, CliData* cliData);
CliStatus cmdTraceRtHost(T_VOID* priv, CliData* cliData);
CliStatus cmdTraceRtQuery(T_VOID* priv, CliData* cliData);
CliStatus cmdTraceRtWaitTime(T_VOID* priv, CliData* cliData);
CliStatus cmdTraceRtMaxHops(T_VOID* priv, CliData* cliData);
CliStatus cmdTraceRouteTest(T_VOID* priv, CliData* cliData);
#endif

#endif //#ifndef _CLI_DIAG_H_

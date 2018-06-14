/* Really simple radius authenticator
 *
 * Copyright (c) 2004 Michael Gernoth <michael@gernoth.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <syslog.h>
#include "typedefs.h"
#include "ethernet.h"
#include "802.11.h"
#include "wrt-radauth.h"
#include "radius.h"
#include "wireless.h"
#define __MAIN__
#include "common.h"
#include "ieee80211_ioctl.h"

#ifndef IFLA_WIRELESS
#define IFLA_WIRELESS 11
#endif
int run_as_daemon = 0;
static void process_timeout (void);
static void process_already_assoc (void);
static void configure_request_retries (struct sta *station);
int getradiusconfig()
{
	FILE *fp = NULL;
	char *token = NULL;
	static char line_buffer [256];
	fp = fopen ("/etc/wrt-radauth.conf","r");
	if (!fp) return -1;
	while (fgets (line_buffer, sizeof(line_buffer), fp))
	{
		token = strtok (line_buffer, " " );
		if (!strcmp(token,"radius_primary_server"))
		{
			token = strtok (NULL, "\n" );
			config.primary.server = strdup (token);
		}
		if (!strcmp(token,"radius_secondary_server"))
		{
			token = strtok (NULL, "\n" );
			config.secondary.server = strdup (token);
		}
		if (!strcmp(token,"radius_request_timeout"))
		{
			token = strtok (NULL, "\n" );
			config.request_timeout = atoi (token);
		}
		if (!strcmp(token,"radius_request_retries"))
		{
			token = strtok (NULL, "\n" );
			config.request_retries = atoi (token);
		}
		if (!strcmp(token,"radius_reauth_time"))
		{
			token = strtok (NULL, "\n" );
			config.reauth_time = atoi (token);
		}
		if (!strcmp(token,"radius_retry_time"))
		{
			token = strtok (NULL, "\n" );
			config.retry_time = atoi (token);
		}

		if (!strcmp(token,"radius_primary_port"))
		{
			token = strtok (NULL, "\n" );
			config.primary.port = atoi (token);
		}
		if (!strcmp(token,"radius_secondary_port"))
		{
			token = strtok (NULL, "\n" );
			config.secondary.port = atoi (token);
		}
		if (!strcmp(token,"radius_primary_secret"))
		{
			token = strtok (NULL, "\n" );
			config.primary.secret = strdup (token);
		}
		if (!strcmp(token,"radius_secondary_secret"))
		{
			token = strtok (NULL, "\n" );
			config.secondary.secret = strdup (token);
		}
		if (!strcmp(token,"radius_primary_password"))
		{
			token = strtok (NULL, "\n" );
			config.primary.password = strdup (token);
		}
		if (!strcmp(token,"radius_secondary_password"))
		{
			token = strtok (NULL, "\n" );
			config.secondary.password = strdup (token);
		}
		if (!strcmp(token,"radius_log_syslog"))
		{
			token = strtok (NULL, "\n" );
			config.syslog = atoi (token);
			openlog("wrt-radauth",LOG_CONS|LOG_PID,LOG_DAEMON);
		}
		if (!strcmp(token,"radius_log_file"))
		{
			token = strtok (NULL, "\n" );
			if (strlen(token) > 5)
			{
				config.file_fd = fopen (token,"w");
				if (!config.file_fd) fprintf(stderr,"unable to open %s for logging!!\n",token);
			}
		}
		if (!strcmp(token,"radius_log_stdout"))
		{
			token = strtok (NULL, "\n" );
			config.std_out = atoi (token);
		}
		if (!strcmp(token,"radius_log_level"))
		{
			token = strtok (NULL, "\n" );
			config.log_level = atoi (token);
		}
		if (!strcmp(token,"radius_vsa_start"))
		{
			struct vsalist *currvsa = NULL;
			struct vsalist *prev = NULL;
			token = strtok (NULL, "\n" );
			currvsa = config.vsa;
			while ( currvsa != NULL )
			{
				prev = currvsa;
				currvsa = currvsa->next;
			}
			currvsa = malloc (sizeof (struct vsalist));
			if (!currvsa)
			{
				perror("malloc");
				exit(1);
			}
			if ( config.vsa == NULL )
			{
				config.vsa = currvsa;
			} else {
				prev->next = currvsa;
			}
			while (fgets (line_buffer, sizeof(line_buffer), fp))
			{
				token = strtok (line_buffer, " " );
				if (!strcmp(token,"radius_vsa_vendor_id"))
				{
					token = strtok (NULL, "\n" );
					currvsa->vendor_id = atoi (token);
				}
				if (!strcmp(token,"radius_vsa_attr_type"))
				{
					token = strtok (NULL, "\n" );
					currvsa->attr_type = atoi (token);
				}
				if (!strcmp(token,"radius_vsa_attr_action"))
				{
					token = strtok (NULL, "\n" );
					currvsa->attr_action = strdup (token);
				}
				if (!strcmp(token,"radius_vsa_end")) break;
				memset (line_buffer, 0x00, sizeof(line_buffer));
			}
		}
		memset (line_buffer, 0x00, sizeof(line_buffer));
	}
	fclose (fp);
	if (run_as_daemon)  config.std_out = 0;
	wrtlog_debug("read: Primary\n");
	wrtlog_debug("      Server %s \n",config.primary.server);
	wrtlog_debug("      Port %d\n", config.primary.port);
	wrtlog_debug("      Secret %s\n", config.primary.secret);
	wrtlog_debug("      Password %s\n", config.primary.password);
	wrtlog_debug("read: Secondary\n");
	wrtlog_debug("      Server %s\n",config.secondary.server);
	wrtlog_debug("      Port %d\n", config.secondary.port);
	wrtlog_debug("      Secret %s\n", config.secondary.secret);
	wrtlog_debug("      Password %s\n", config.secondary.password);
	wrtlog_debug("read: Request Timeout %d\n", config.request_timeout);
	wrtlog_debug("read: Request Retries %d\n", config.request_retries);
	wrtlog_debug("read: Reauthentication Time %d\n", config.reauth_time);
	wrtlog_debug("read: Retry Time %d\n", config.retry_time);
	wrtlog_debug("read: Syslog %d\n", config.syslog);
	wrtlog_debug("read: File %s %p\n", token,config.file_fd);
	wrtlog_debug("read: Stdout %d\n", config.std_out);
	wrtlog_debug("read: Log level %08x\n", config.log_level);
	{
		struct vsalist *currvsa = NULL;
		currvsa = config.vsa;
		while ( currvsa != NULL )
		{
			wrtlog_debug("read: VSA vendor id %d\n", currvsa->vendor_id);
			wrtlog_debug("read: VSA attribute type %d\n", currvsa->attr_type);
			wrtlog_debug("read: VSA attribute action %s\n", currvsa->attr_action);
			currvsa = currvsa->next;
		}
	}
	return 0;
}
int authmac_req (struct sta *station,struct radius_server *rs)
{
	char macstr[32];
	unsigned char *mac = station->mac;
	if (config.macfmt == 1) {
		sprintf(macstr,"%2.2x%2.2x%2.2x-%2.2x%2.2x%2.2x",\
				mac[0],mac[1],mac[2],mac[3],\
				mac[4],mac[5]);
	} else {
		sprintf(macstr,"%2.2X-%2.2X-%2.2X-%2.2X-%2.2X-%2.2X",\
				mac[0],mac[1],mac[2],mac[3],\
				mac[4],mac[5]);
	}
	wrtlog_info("sending access-request %s to %s, avail retries p-%d,s-%d\n", ether_sprintf(mac),rs->server,station->authretries_primary,
				station->authretries_secondary);
	station->lastseen =  time(NULL);
	return radius_send_req (rs->server, rs->port, macstr,rs->password, rs->secret,station);
}
void handle_new_sta (unsigned char *mac_addr)
{
	struct sta *currsta = NULL;
	struct sta *prev = NULL;
	time_t step;


	currsta = config.first;
	prev = NULL;
	step=time(NULL);
	/* Have we already seen this STA */
	while ( currsta != NULL )
	{
		if (memcmp(currsta->mac,mac_addr,6) == 0)
		{
			wrtlog_debug("Station already present %s\n", ether_sprintf(mac_addr)); 
			if (currsta->lastseen+60 < step)
			{
				wrtlog_info("Reauthenticating STA %s\n",ether_sprintf(mac_addr));
				if (currsta->state == STA_RADIUS_WAITING)
				{
					wrtlog_info("Already waiting for response for %s from %s\n", ether_sprintf(mac_addr),config.primary);
				}
				else
				{
					if (currsta->authorized)
					{
						set_sta_authorized (mac_addr, 0);
						currsta->authorized=0;
					}
					/* send radius request */
					configure_request_retries (currsta);
					authmac_req(currsta,&config.primary);
					currsta->authretries_primary --;
					currsta->changed=1;
					currsta->state=STA_RADIUS_WAITING;
					currsta->lastseen = step;
				}
			}
			else
			{
				wrtlog_info("Already in process of authentication - STA %s\n",ether_sprintf(mac_addr));
			}
			return;
		}
		prev = currsta;
		currsta = currsta->next;
	}
	/* Or is it new? */
	if ( currsta == NULL ) 
	{
		wrtlog_debug("New station %s\n", ether_sprintf(mac_addr)); 
		/* Alloc mem for new STA */
		currsta = malloc(sizeof(struct sta));
		if ( currsta == NULL )
		{
			perror("malloc");
			exit(1);
		}

		if ( config.first == NULL )
		{
			config.first = currsta;
		} else {
			prev->next = currsta;
		}
		

		currsta->next = NULL;
		currsta->changed = 1;

		memcpy(currsta->mac,mac_addr,6);
		currsta->lastseen = step;

		set_sta_authorized (mac_addr, 0);
		currsta->authorized=0;

		/* send radius request */
		wrtlog_info("Authenticating STA %s\n",ether_sprintf(mac_addr));
		configure_request_retries (currsta);
		authmac_req(currsta,&config.primary);
		currsta->authretries_primary --;
		currsta->state = STA_RADIUS_WAITING;
	}
	return;
}
void process_timeout ()
{
	struct sta *currsta = NULL;
	struct sta *prev = NULL;
	time_t step;
	int i;
	int statechange = 0;
	int expiry_time;
	static int lastcnt=0;		/* Number of blacklisted cards in the last loop */
#if 0
	struct maclist *maclist=NULL;
	struct ether_addr *ea=NULL;
	unsigned char buf[24*1024];	/* Buffer for wireless-ioctls MAC lists */
#endif
	step = time(NULL);
	currsta = config.first;
#if 0
	memset(buf,0,sizeof(buf));
	maclist = (struct maclist *) buf;
	maclist->count=0;
	ea = maclist->ea;
#endif
	wrtlog_debug("process timeout event %d\n", step);	
	while (currsta != NULL)
	{
		if ((currsta->state == STA_RADIUS_ACCEPTED) ||
			(currsta->state == STA_RADIUS_DENIED))
		{
			expiry_time = config.reauth_time;
		}
		else
		{
			expiry_time = config.retry_time;
		}
		if(currsta->lastseen+expiry_time <= step)
		{
			struct sta *tmpsta;

			statechange=1;
			wrtlog_debug("Expiring STA %s after %d\n", ether_sprintf(currsta->mac),expiry_time);
#if 0
			/* also remove from ACL,let it try again if it is still there */
			remove_station_acl (config.iface,currsta->mac);
#endif
			if (is_sta_present (currsta->mac))
			{
				wrtlog_info("Reauthenticating STA %s\n",ether_sprintf(currsta->mac));
				/* send radius request */
				configure_request_retries (currsta);
				authmac_req(currsta,&config.primary);
				currsta->authretries_primary --;
				currsta->changed=1;
				currsta->state=STA_RADIUS_WAITING;
				currsta->lastseen = step;

				prev = currsta;
				currsta = currsta->next;
				continue;
			}
#if 1
			/* also remove from ACL,let it try again if it is still there */
			remove_station_acl (config.iface,currsta->mac);
			if ((currsta->state != STA_RADIUS_ACCEPTED) && (currsta->state != STA_RADIUS_DENIED))
			{
				/* kick so that he can try again */
				kick_station (currsta->mac);
			}
#endif
			wrtlog_info("Deleting STA %s\n",ether_sprintf(currsta->mac));
			if ( currsta == config.first )
			{
				tmpsta = config.first;
				config.first = config.first->next;
				free(tmpsta);
				currsta = config.first;
			} else {
				tmpsta = currsta;
				prev->next = currsta->next;
				free(currsta);
				currsta = prev->next;
			}
			continue;
		} 
		switch (currsta->state)
		{
			case STA_RADIUS_DENIED:
#if 0
				/* create deny ACL list  */
				memcpy(ea,currsta->mac,6);
				ea++;
				maclist->count++;
				if ( currsta->changed )
				{
					statechange=1;
					currsta->changed=0;
				}
#endif
			case STA_RADIUS_ACCEPTED:
				prev = currsta;
				currsta = currsta->next;
				continue;
			case STA_RADIUS_WAITING:
			default:
				break;
		}
		/* send a new request to radius server */
#if 0
		if (currsta->lastauth_primary+config.request_timeout <= step)
		{
			if (currsta->authretries_primary <=0)
			{
				wrtlog_debug("primary accept-request retries exhausted %s, giving up and preserving authorization %d\n",
					   ether_sprintf(currsta->mac), currsta->authorized);
				currsta->state=STA_RADIUS_TIMEOUT;
				prev = currsta;
				currsta = currsta->next;
				continue;
			}
			wrtlog_info("no radius response received from primary server %s\n",
			 			currsta->lastserver);
				
			authmac_req(currsta,&config.primary);
			currsta->authretries_primary -- ;
			currsta->state=STA_RADIUS_WAITING;
		} 
		if ((config.secondary.server != NULL) &&
				   (config.secondary.port != 0) &&
				   (config.secondary.secret != NULL) &&
				   (config.secondary.password != NULL) &&
				   (currsta->lastauth_secondary+config.request_timeout <= step))
		{
			if (currsta->authretries_secondary <=0)
			{
				wrtlog_debug("secondary accept-request retries exhausted %s, giving up and preserving authorization %d\n",
							 ether_sprintf(currsta->mac), currsta->authorized);
				currsta->state=STA_RADIUS_TIMEOUT;
				prev = currsta;
				currsta = currsta->next;
				continue;
			}
			wrtlog_info("no radius response received from secondary %s\n",
			 			currsta->lastserver);
			authmac_req(currsta,&config.secondary);
			currsta->authretries_secondary -- ;
			currsta->state=STA_RADIUS_WAITING;
		}
#else
		if (currsta->lastauth_primary+config.request_timeout <= step)
		{
			if (currsta->authretries_primary <=0)
			{
				if ((config.secondary.server == NULL) ||
					(config.secondary.port == 0) ||
					(config.secondary.secret == NULL) ||
					(config.secondary.password == NULL))
				{
					wrtlog_debug("no secondary server configured %s, giving up and preserving authorization %d\n",
									 ether_sprintf(currsta->mac), currsta->authorized);
					currsta->state=STA_RADIUS_TIMEOUT;
					prev = currsta;
					currsta = currsta->next;
					continue;
				}
				if (currsta->lastauth_secondary+config.request_timeout <= step)
				{
					if (currsta->authretries_secondary <=0)
					{
						wrtlog_debug("secondary accept-request retries exhausted %s, giving up and preserving authorization %d\n",
									 ether_sprintf(currsta->mac), currsta->authorized);
						currsta->state=STA_RADIUS_TIMEOUT;
						prev = currsta;
						currsta = currsta->next;
						continue;
					}
					wrtlog_info("no radius response received from %s\n",
								currsta->lastserver);
					authmac_req(currsta,&config.secondary);
					currsta->authretries_secondary -- ;
					currsta->state=STA_RADIUS_WAITING;
				}
			}
			else
			{
				wrtlog_info("no radius response received from %s\n",
							currsta->lastserver);
				authmac_req(currsta,&config.primary);
				currsta->authretries_primary -- ;
				currsta->state=STA_RADIUS_WAITING;
			}
		} 
#endif
		prev = currsta;
		currsta = currsta->next;
	}
#if 0
	if (!statechange) return;
	/* statechange = Previously unseen/denied STA seen or STA expired */
	if ( maclist->count )
	{
		unsigned char mac[6];
		enable_deny_acl (config.iface);
		ea = maclist->ea;
		for(i=0; i < maclist->count; i++)
		{
			memcpy(mac,ea,6);
			wrtlog_info("Disassociating STA %s\n",ether_sprintf(mac));
			add_station_acl (config.iface,mac);
			kick_station (mac);
			ea++;
		}
	} else {
		if ( lastcnt != 0 )
		{
			wrtlog_debug("Resetting security\n");
			disable_deny_acl (config.iface);
		}
	}
	lastcnt = maclist->count;
	statechange = 0;
#endif
	return ;
}
static void configure_request_retries (struct sta *currsta)
{
	if ((config.secondary.server != NULL) &&
		(config.secondary.port != 0) &&
		(config.secondary.secret != NULL) &&
		(config.secondary.password != NULL))
	{
		currsta->authretries_secondary = config.request_retries;
	}
	else
	{
		currsta->authretries_secondary = 0;
	}

	if ((config.primary.server != NULL) &&
		(config.primary.port != 0) &&
		(config.primary.secret != NULL) &&
		(config.primary.password != NULL))
	{
		currsta->authretries_primary = config.request_retries;
	}
	else
	{
		currsta->authretries_primary = 0;
	}
}
static void process_already_assoc (void)
{	
	unsigned char list[24*1024];
	unsigned char *pos = NULL;
	int num = 0;
	int i=0;
	getassoclist(list);
	pos=list;
	memcpy(&num,pos,4); 
	pos+=4;
	for (i=0;i<num;i++)
	{
		handle_new_sta (pos);
		pos += 6;
	}
	return;
}
int main(int argc, char** argv)
{
	int ret;
	fd_set rfds;
	struct timeval tv;
	unsigned char buf[24*1024];	/* Buffer for wireless-ioctls MAC lists */
	pid_t pid, sid;

	if ( argc < 2 )
	{
		fprintf(stderr,"wrt-radauth - A simple radius authenticator\n");
		fprintf(stderr,"(C) 2004 Michael Gernoth, some modifications by Sebastian Gottschall and Sanjeev Kumar\n");
		fprintf(stderr,"Usage: %s [-n] interface -d \n",argv[0]);
		fprintf(stderr,"\t-n\tUse new MAC address format 'aabbcc-ddeeff' instead of 'AA-BB-CC-DD-EE-FF'\n");
		fprintf(stderr,"\t-d\tRun as a daemon'\n");
		exit(1);
	}


	if (argc>2 && (strcmp(argv[1],"-n") == 0))
	{
		config.macfmt=1;
		config.iface=argv[2];
	} else {
		config.macfmt=0;
		config.iface=argv[1];
	}
    config.primary.port = 1812;
	config.reauth_time = 300;
	config.request_timeout = 1;
	config.request_retries = 8;
	config.retry_time = 60;
	config.log_level = 0x1;
	if ((argc==3 && (strcmp(argv[2],"-d") == 0)) ||
		(argc==4 && (strcmp(argv[3],"-d") == 0)))
	{
		/* we cannot have stdout in daemon */
		run_as_daemon = 1;
		pid = fork ();
		if (pid < 0)
		{
			exit(EXIT_FAILURE);
		}
		if (pid > 0)
		{
			exit(EXIT_SUCCESS);
		}
		umask (0);
		sid = setsid ();
		if (sid < 0) {
			exit(EXIT_FAILURE);
		}
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	else
	{
		umask (0);
	}
	if ((chdir("/")) <0) {
		exit(EXIT_FAILURE);
	}
	/* Get configuration from config */
	if (getradiusconfig ()) exit(1);
	if (config.primary.server == NULL || config.primary.secret ==  NULL || config.primary.password == NULL)
	{
		wrtlog_debug("missing mandatory configurations!!");
		exit (1);
	}

	wrtlog_info("$Id: wrt-radauth.c,v 2.0 2011/09/22 03:58:00 simigern Exp $ coming up...\n");
	if (init_driver ())
	{
		wrtlog_debug("driver inilization failed!!");
		exit (1);
	}
	/* process the already associated station */
	process_already_assoc ();

	while (1)
	{
		FD_ZERO(&rfds);
		FD_SET(config.netlink_sock,&rfds);
		FD_SET(config.radius_sock,&rfds);
		tv.tv_sec=1;
		tv.tv_usec=0;
		ret=select(config.radius_sock+1,&rfds,NULL,NULL,&tv);
		if ( ret < 0 )
		{
			perror("select");
			exit(1);
		}
		if ( ret == 0 ) {
			wrtlog_debug("Timeout, no packet received. Try again\n");
			process_timeout ();
			continue;
		}
		if (FD_ISSET(config.radius_sock,&rfds))
		{
			wrtlog_info("received radius messege.\n");
			handle_radius_receive (NULL);
		}
		if (FD_ISSET(config.netlink_sock,&rfds))
		{
			wrtlog_debug("received netlink messege.\n");
			handle_netlink_receive ();
		}
		process_timeout ();
	}
	deinit_driver ();
	exit(0);
}
#define WLOG_FUNC(FUNCNAME,PRIORITY) \
	int \
FUNCNAME(const char *format, ...) \
{ \
	  va_list args; \
	  va_start(args, format); \
	  wrtlog (PRIORITY, format, args); \
	  va_end(args); \
}
WLOG_FUNC(wrtlog_crit, WRT_LOG_CRIT)

WLOG_FUNC(wrtlog_info, WRT_LOG_INFO)

WLOG_FUNC(wrtlog_debug, WRT_LOG_DEBUG)
int wrtlog(unsigned int level, char* fmt, va_list args)
{
	char *str,*log;
	int len;
	int syslog_l;
	static char buf[1024];
	if (!(level&config.log_level)) return;

	if (level&WRT_LOG_CRIT){
		str = "[CRIT]:";
		syslog_l = LOG_CRIT;
	}
	else if (level&WRT_LOG_INFO){ 
		str = "[INFO]:";
		syslog_l = LOG_INFO;
	}
	else{
		str = "[DEBUG]:";
		syslog_l = LOG_DEBUG;
	}
	memset (buf,0x00,sizeof(buf));
	len=strlen(str);
	strncpy(buf,str,len);
	log = buf+len;
	vsprintf(log,fmt,args);
	if (config.file_fd)
	{
		printf("put to file\n");
		fprintf (config.file_fd,"%s",buf);
	}
	if (config.syslog)
	{
		syslog(syslog_l,"%s",log);
	}
	if (config.std_out)
	{
		printf("%s", buf);
	}
}

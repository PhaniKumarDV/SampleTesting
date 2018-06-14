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
#include <unistd.h>
#include <time.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "ethernet.h"
#include "wrt-radauth.h"
#include "md5.h"
#include "radius.h"
#include "wireless.h"
#include "common.h"
/* RFC2138 */
#define ACCESS_REQUEST	0x1
#define ACCESS_ACCEPT	0x2
#define ACCESS_REJECT	0x3

#define USER_NAME	0x1
#define USER_PW		0x2
#define NAS_IP_ADDRESS	0x4
#define NAS_PORT	0x5
#define NAS_PORT_TYPE	0x3d
#define REPLY_MESSAGE	0x12

#define MACLENGTH	13
static void handle_avp_vsa (unsigned char *vsp, int length);
void md5_calc(unsigned char *output, unsigned  char  *input, unsigned int inlen)
{
	md5_state_t context;

	md5_init(&context);
	md5_append(&context, input, inlen);
	md5_finish(&context,output);
}

int resolve_host(char* name)
{
	int ret;
	struct hostent *hent;

	if ( ! (hent = gethostbyname(name)) )
	{
		wrtlog_info("Can't lookup %s!\n",name);
		return 0;
	}

	ret = (*((int*)hent->h_addr_list[0]));

	return ret;
}
int radius_send_req(char *host, short port, char *user, char *password, char *radsecret, struct sta *station)
{
	int ret, from_len;
	struct sockaddr_in to_addr;
	int length, seclength;
	short radlength;
	unsigned char buf[1025];
	unsigned char random[16];
	unsigned char *attributes;
	unsigned char *secret;
	unsigned char tmp;
	static unsigned char id=1;
	static unsigned char seeded=0;
	int i;

	memset(&to_addr, 0, sizeof(to_addr));
	to_addr.sin_family = PF_INET;
	to_addr.sin_addr.s_addr = resolve_host(host);
	to_addr.sin_port = htons(port);
	if (!to_addr.sin_addr.s_addr) return -1;

	memset(&buf, 0, sizeof(buf));
	buf[0]=ACCESS_REQUEST;
	buf[1]=id; /*Id*/

	/* Generate random here! */
	if ( ! seeded )
	{
		srand(time(NULL));
		seeded=0x1;
	}
	memset(random,0,16);
	for(i=0; i<=15; i++)
	{
		tmp = rand();
		memcpy(random+i,&tmp,1);
	}
	memcpy(&buf[4],random,16);

	/* Attributes: User-Name */
	attributes = &buf[20];
	*attributes = USER_NAME; attributes++;
	*attributes = (unsigned char)1+1+strlen(user); attributes++;
	memcpy(attributes,user,strlen(user)); attributes+=strlen(user);

	/* Attributes: NAS-Port */
	*attributes = NAS_PORT; attributes++;
	*attributes = 6; attributes++;
	*attributes = 0x00; attributes++;
	*attributes = 0x00; attributes++;
	*attributes = 0x00; attributes++;
	*attributes = 0x01; attributes++;

	/* Attributes: NAS-Port-Type */
	*attributes = NAS_PORT_TYPE; attributes++;
	*attributes = 6; attributes++;
	*attributes = 0x00; attributes++;
	*attributes = 0x00; attributes++;
	*attributes = 0x00; attributes++;
	*attributes = 0x13; attributes++;

	/* The horror of radius encryption */
	seclength=(((strlen(password)-1)/16)+1)*16;
	secret=malloc(seclength);
	if (secret == NULL)
	{
		wrtlog_crit("malloc");
		exit(1);
	}
	memset(secret,0,seclength);
	memcpy(secret,password,strlen(password));
	{
		unsigned char *secpos=secret;
		unsigned char b[16], clast[16], *md5in;
		int md5length;

		/* Pre-Initialize */
		memcpy(clast,random,16);
		md5length=(strlen(radsecret))+sizeof(clast);
		md5in=malloc(md5length);
		if (md5in == NULL)
		{
			wrtlog_crit("malloc");
			exit(1);
		}

		while(secpos-secret<seclength)
		{
			memcpy(md5in,radsecret,strlen(radsecret));
			memcpy(md5in+(strlen(radsecret)),clast,sizeof(clast));

			md5_calc(b,md5in,md5length);
			for ( i=0; i<=15; i++)
			{
				secpos[i] = secpos[i] ^ b[i];
			}
			memcpy(clast,secpos,16);
			secpos+=16;
		}
		free(md5in);
	}

	*attributes = USER_PW; attributes++;
	*attributes = (unsigned char)1+1+seclength; attributes++;
	memcpy(attributes,secret,seclength); attributes+=seclength;
	free(secret);

	/* Code + Identifier + Length + Authenticator + Attributes */
	radlength= 1 + 1 + 2 + 16 + (attributes-&buf[20]);
	length=radlength;
	radlength=htons(radlength);
	memcpy(&buf[2],&radlength,2);
	ret = sendto(config.radius_sock, &buf, length, 0, (struct sockaddr *) &to_addr, sizeof(to_addr));
	station->id = id;
	memcpy(station->random, random, 16);
	station->lastserver = host;
	if (host == config.primary.server)
	{
		station->lastauth_primary = time(NULL);
	}
	else
	{
		station->lastauth_secondary = time(NULL);
	}
	/* Increment ID */
	wrtlog_info("radius-request id: %d\n",id);
	id++;
	return(ret);
}
	
int handle_radius_receive (char *radsecret)
{
	struct sta *currsta = NULL;
	struct sta *prev = NULL;
	int  ret, from_len;
	struct sockaddr_in from_addr,test_addr;
	struct timeval tv;
	short radlength;
	unsigned char buf[1025];
	unsigned char random[16];
	unsigned char *attributes;
	char radius_server_IP [INET_ADDRSTRLEN] = {0};

	memset (&from_addr, 0x00, sizeof (struct sockaddr_in));
	memset (&test_addr, 0x00, sizeof (struct sockaddr_in));
	from_len = sizeof (struct sockaddr_in);
	ret = recvfrom(config.radius_sock, &buf, sizeof(buf), 0, (struct sockaddr *)&from_addr, (socklen_t *)&from_len);
	if ( ret < 3 )
	{
		wrtlog_info("Completely invalid radius packet\n");
		return 1;
	}
	currsta = config.first;
	struct sockaddr_in *ipv4addr = (struct sockaddr_in*)&from_addr;
	int ipaddr = ipv4addr->sin_addr.s_addr;
	inet_ntop(AF_INET, &ipaddr, radius_server_IP, INET_ADDRSTRLEN);
	prev = NULL;
	while (currsta != NULL)
	{
		if (buf[1] == currsta->id)
		{
			break;
		}
		prev = currsta;
		currsta = currsta->next;
	}

	if (currsta == NULL)
	{
		wrtlog_crit("Received faked radius-reply %d!\n",buf[1]);
		return -1;
	}
	if (currsta->state != STA_RADIUS_WAITING)
	{
		wrtlog_debug("station %s not expecting any radius reply\n",ether_sprintf(currsta->mac));
		return -1;
	}
	memcpy(&radlength,&buf[2],2);
	radlength=ntohs(radlength);
	if ( ret != radlength )
	{
		wrtlog_info("Invalid packet received. Given length (%d) != real length (%d)!\n",radlength,ret);
		return -1;
	}
//	test_addr.sin_addr.s_addr = resolve_host(config.primary.server);
//	if (test_addr.sin_addr.s_addr == ntohl(from_addr.sin_addr.s_addr))a
	if(strcmp(config.primary.server,radius_server_IP) == 0)
	{
		radsecret = config.primary.secret;
	}
	else if (config.secondary.server)
	{
//		test_addr.sin_addr.s_addr = resolve_host(config.secondary.server);
	if(strcmp(config.secondary.server,radius_server_IP) == 0)
		if (test_addr.sin_addr.s_addr == ntohl(from_addr.sin_addr.s_addr))
		{
			radsecret = config.secondary.secret;
		}
		else
		{
			wrtlog_info("received from unknown source address %s",radius_server_IP);
			return -1;
		}
	}
	/* Check response authenticator */
	{
		unsigned char *tohash;
		unsigned char md5out[16];
		int md5length;

		/* Code+ID+Length+RequestAuth+Attributes+Secret */
		md5length = radlength+strlen(radsecret);
		tohash = malloc(md5length);
		if (tohash == NULL)
		{
			wrtlog_crit("malloc");
			exit(1);
		}

		/* Code+ID+Length */
		memcpy(tohash, buf, 4);
		/* RequestAuth */
		memcpy(&tohash[4], currsta->random, 16);
		/* Attributes */
		memcpy(&tohash[20], &buf[20], radlength-20);
		/* Secret */
		memcpy(&tohash[20+(radlength-20)], radsecret, strlen(radsecret));

		md5_calc(md5out,tohash,md5length);

		free(tohash);

		if (memcmp(md5out,&buf[4],16) != 0)
		{
			wrtlog_debug("Faked radius response (wrong response-authenticator!)\n");
			return -1;
		}
	}

	{
		unsigned char *pos;

		pos = &buf[20];

		while (pos-buf < radlength)
		{
			unsigned char type = pos[0];
			unsigned char attrlength = pos[1];

			if (radlength-(pos-buf) >= attrlength)
			{
				wrtlog_debug("Found attribute %d, length: %d\n",type,attrlength);
				if ( type == REPLY_MESSAGE )
				{
					char msg[256];
					memset(msg,0,256);
					memcpy(&msg,&pos[2],attrlength-2);
					wrtlog_debug("Reply-Message: %s\n",msg);
				}
				if (type == 26)
				{
					char msg[256];
					unsigned int vendor_id = 0;
					unsigned int attribute_type = 0;
					unsigned int attribute_length = 0;
					memset(msg,0,256);
					memcpy(&msg,&pos[2],attrlength-2);
					/* handle VSP */
					wrtlog_debug("received VSP\n");
					handle_avp_vsa (msg,attrlength-2);
				}
			} else {
				wrtlog_debug("Error decoding attributes...\n");
				break;
			}

			pos += attrlength;
		}
	}

	currsta->changed =1;
#if 0
	statechange=1;
#endif
	if (buf[0] == 0x2)
	{
		/* Access-Accept */
		wrtlog_info("Access-Accept processed for %s\n", ether_sprintf(currsta->mac));
		wrtlog_info("Accepting STA %s\n",ether_sprintf(currsta->mac));
		if (!currsta->authorized)
		{
			set_sta_authorized (currsta->mac, 1);
		}
		currsta->state=STA_RADIUS_ACCEPTED;
		currsta->authorized=1;
		ret=1;
	} else {
		/* Access-Reject */
		wrtlog_info("Access-Reject processed for %s\n", ether_sprintf(currsta->mac));
		wrtlog_info("Rejecting STA %s\n",ether_sprintf(currsta->mac));
		if (currsta->authorized)
		{
			set_sta_authorized (currsta->mac, 0);
		}
		currsta->state=STA_RADIUS_DENIED;
		currsta->authorized=0;
		ret=0;
	}
	currsta->lastseen=time(NULL);
	return ret;
}
static void handle_avp_vsa (unsigned char *vsp, int length)
{
	struct vsalist *currvsa;
	struct vsalist *prev;
	unsigned int vendor_id;
	unsigned int attr_type;
	unsigned int attr_val;
	memcpy(&vendor_id, vsp,4);
	currvsa = config.vsa;
	prev = NULL;
	wrtlog_debug("vendor_id %d\n", vendor_id);
	while ((currvsa != NULL) && (vendor_id == currvsa->vendor_id))
	{
		attr_type = vsp[4];
		if (attr_type == currvsa->attr_type)
		{
			int attr_val;
			char command[256];
			memcpy(&attr_val,&vsp[6],4);
			sprintf(command,"%s %d > /dev/null 2>&1",currvsa->attr_action, attr_val);
			wrtlog_info("attribute action %s\n",command);
			system(command);
		}
		prev = currvsa;
		currvsa = currvsa->next;
	}
}

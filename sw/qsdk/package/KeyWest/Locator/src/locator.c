/*
 * Locator Daemon
 * Copyright (C) 2007 BVT, Inc.
 *
 * Author: Anderson Chen
 *
 *
 * Main Daemon source.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <linux/if.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <syslog.h>
#include "locator.h"
#include "sys_tools.h"
#include "cfg_lib.h"

#define FREE(_p) (_p? free(_p), _p = NULL: NULL)
#define LOCATOR_PID_FILENAME		"/var/run/locator.pid"

#define LOG_DEBUG 7
#define LOG_LOG   6
#define LOG_WARN  4
#define LOG_CRIT  2
char username[50] = {0};
//#define DEBUG
//#define memleak_test

uchar localMacAddr[6];
void log(int level, const char *fmt, ...)
{
	char buf[256];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);              //bk - otherwise ppc segfaults
	va_start(args, fmt);       //bk
	vfprintf(stderr, fmt, args);
	fflush(stderr);
	openlog("locator", LOG_PID, LOG_DAEMON);
	syslog(level, "%s", buf);
	va_end(args);
}

void daemonize(int sock)
{
	int pid=0;
	//	(+)	2012-07-02	Albert: bugfix for read pid file.
	int	fd, fd2;
	int		nRead;
	//	(-)	2012-07-02	Albert: bugfix for read pid file.
	int i, l;
	char buf[80];
	int pidfilewritten=0;

	if((pid = fork()) < 0)
	{
		log(LOG_LOG, "%s: Unable to fork()\n",__FUNCTION__);
		close(sock);
		exit(1);
	}
	else if(pid)
		exit(0);

//	close(0);
//	close(1);
//	close(2);

	/* Read previous pid file. */
	
	//	(+)	2012-07-02	Albert: bugfix for read pid file.
	fd = open(LOCATOR_PID_FILENAME,O_RDONLY);
	if(fd)
	{
		nRead = read(fd, buf, sizeof(buf) - 1);
		if(nRead > 0)
		{
			buf[nRead] = 0;
	//	(-)	2012-07-02	Albert: bugfix for read pid file.
			pid = atoi(buf);
			
			/* If the previous server process is not still running,
			write a new pid file immediately. */
			if(pid && (pid == getpid() || kill(pid, 0) < 0))
			{
				unlink(LOCATOR_PID_FILENAME);
				if((fd2 = open(LOCATOR_PID_FILENAME, O_WRONLY | O_CREAT, 0640)) >= 0)
				{
					snprintf(buf, sizeof(buf), "%d\n", (int)getpid());
					write(fd2, buf, strlen(buf));
					fclose(fd2);
					pidfilewritten = 1;
				}
			}
			else
			{
				log(LOG_LOG, "%s: There's already a locator server running.\n", 
					__FUNCTION__);
				close(sock);
				close (fd);
				exit(1);
			}
		}
		else if (nRead == 0)
		{
			remove (LOCATOR_PID_FILENAME);
			pidfilewritten = 1;
		}
		else
		{
			log(LOG_LOG, "%s: Unable to read pid file [%s]\n",
				__FUNCTION__, LOCATOR_PID_FILENAME);
		}

		close (fd);
	}

	pid = setsid();

	if(!pidfilewritten)
	{
		unlink(LOCATOR_PID_FILENAME);
		if((i = open(LOCATOR_PID_FILENAME, O_WRONLY | O_CREAT, 0640)) >= 0)
		{
			snprintf(buf, strlen(buf), "%d\n", (int)getpid());
			write(i, buf, strlen(buf));
			close(i);
			pidfilewritten = 1;
		}
	}
}

int password_auth(char* tmp, char* authStr)
{
	int authErr=0;
	char authTemp[80];	
	char cmd[100];
	char encry[50];
	FILE *fpipe;

    int tmpidx=0,i=0;
    memset(authTemp,'\0',80);
    for( i=0; authStr[i]!=NULL; i++){
        if(i>=100){
		    log(LOG_LOG, "%s: authStr error\n", __FUNCTION__);
    		perror("authStr error");
    		break;	
        }
        if( (authStr[i]>=0x30 && authStr[i]<=0x39) /*0-9*/ || 
            (authStr[i]>=0x41 && authStr[i]<=0x5A) /*A-Z*/ || 
            (authStr[i]>=0x61 && authStr[i]<=0x7A) /*a-z*/
        ){
            authTemp[tmpidx++]=authStr[i];
        }
        else{
            authTemp[tmpidx++]='\\';
            authTemp[tmpidx++]=authStr[i];
        }
    }
	sprintf(cmd,". /lib/user-auth.sh;auth_user %s %s;echo $?",tmp,authTemp);
	#ifdef DEBUG
	log(LOG_LOG, "%s:cmd=%s ", __FUNCTION__, cmd);
	#endif
	if(! (fpipe = (FILE *)popen(cmd, "r")) ) {
		log(LOG_LOG, "%s: pipe error\n", __FUNCTION__);
		perror("pipe error");	
	}
	while(fgets(encry,sizeof(encry),fpipe) ){
		//puts(encry);
	}

	#ifdef DEBUG
	log(LOG_LOG, "%s: password:%s,%s\n", __FUNCTION__,authTemp,encry);
	#endif

	//if(strcmp(encry, tmp) != 0)
	if(encry[2]=='1'){
		authErr=0;
	}
	pclose(fpipe);

return authErr;
}

void req_handler(int fd, struct sockaddr_in *from, LDAP_REQUEST_PACKET_HEADER *pReqHdr, uchar *buf)
{
	LDAP_REPLY_PACKET  reply_packet;
	LDAP_REPLY_PACKET  *pReply;
//	LDAP_CLIENT *pClient;
	u16 method;
	uchar *pData;
	uchar *pReqData;
	uchar len, packetlen;
	char *tmp;
	uchar opMode, code;
	u32	addr;
	struct in_addr in;
	struct sockaddr_in to;
	int ret;

	pReply = &reply_packet;
//	memset(pReply, 0, sizeof(LDAP_REPLY_PACKET));
//	pClient = &(pReqHdr->client);
//	TODO: Verify that packet is a request.

	/*
	 * Verify that the class matches.
	 */
	if(ntohl(pReqHdr->ldap_class) != UAP_CLASS_UCP)
		return;

	/*
	 * Reply Packet Data Header.
	 */
	pReply->hdr.client.opt		= htons(UCP_METHOD_GET_IP);
	pReply->hdr.client.clientAddr	= from->sin_addr.s_addr;
	pReply->hdr.client.clientPort	= htons(LDP_UDAP_PORT);
	pReply->hdr.server.opt		= htons(UCP_METHOD_DISCOVER);
	memcpy(pReply->hdr.server.mac_addr, localMacAddr, 6);
	pReply->hdr.sequence		= pReqHdr->sequence;
	pReply->hdr.ldap_type		= htons(LDAP_TYPE_UCP);
	pReply->hdr.flag		= 0x00;
	pReply->hdr.ldap_class		= htonl(UAP_CLASS_UCP);

	packetlen = 27;
	pData = pReply->data;
	pReqData = buf + sizeof(LDAP_REQUEST_PACKET_HEADER);
	method = ntohs(pReqHdr->method);
	#ifdef DEBUG
	log(LOG_CRIT, "%s: Hello req_handler.\n", __FUNCTION__);
	#endif
	switch(method)
	{
		case UCP_METHOD_DISCOVER:
		{
			pReply->hdr.method = pReqHdr->method;

			// Device Type
			*pData++ = UCP_CODE_DEVICE_TYPE;
			tmp = cfg_get("WLANOpMode");
			opMode =  atoi(tmp);
			switch(opMode)
			{
				case OP_MODE_AP:
					len = 12;
					*pData++ = len;
					sprintf(pData,"Access Point");
					break;
				case OP_MODE_STA:
					len = 15;
					*pData++ = len;
					sprintf(pData,"Wireless Client");
					break;
				case OP_MODE_WBR:
					len = 19;
					*pData++ = len;
					sprintf(pData,"Wireless WDS Bridge");
					break;
				case OP_MODE_REPEATER:
					len = 17;
					*pData++ = len;
					sprintf(pData,"Wireless Repeater");
					break;
				case OP_MODE_APROUTER:
					len = 9;
					*pData++ = len;
					sprintf(pData,"AP Router");
					break;
				case OP_MODE_STAROUTER:
					len = 13;
					*pData++ = len;
					sprintf(pData,"Client Router");
					break;
				case OP_MODE_APWDS:
					len = 16;
					*pData++ = len;
					sprintf(pData,"WDS Access Point");
					break;
				case OP_MODE_STAWDS:
					len = 19;
					*pData++ = len;
					sprintf(pData,"WDS Wireless Client");
					break;
				case OP_MODE_SIFYOB:
					len = 12;
					*pData++ = len;
					sprintf(pData,"Outdoor Base");
					break;
				case OP_MODE_SIFYOS:
					len = 18;
					*pData++ = len;
					sprintf(pData,"Outdoor Subscriber");
					break;
				default:
					break;
			}
			FREE(tmp);
			pData += len;
			packetlen += (len+2);

			// Device Name
			*pData++ = UCP_CODE_DEVICE_NAME;
			tmp = cfg_get("SystemName");
			len = strlen(tmp);
			*pData++ = len;
			sprintf(pData,tmp);
			pData += len;
			packetlen += (len+2);
			FREE(tmp);
			// Firmware Version
			*pData++ = UCP_CODE_SOFTWARE_VER;
			tmp = get_sysVersion();
			len = strlen(tmp);
			//len = 7;
			*pData++ = len;
			//sprintf(pData,get_sysVersion());
			sprintf(pData,tmp);
			pData += len;
			packetlen += (len+2);
			FREE(tmp);
			break;
		}
		case UCP_METHOD_SET_IP:
		{
			pReply->hdr.method = pReqHdr->method;
			for(code = *pReqData; code != UCP_CODE_END; code = *pReqData)
			{
				len = *(++pReqData);
				switch(code)
				{
					case UCP_CODE_USE_DHCP:
					{
						char dhcp_enable;

						dhcp_enable = *(++pReqData);
						if(dhcp_enable)
						cfg_set("network.lan.proto","dhcp");
						else
						cfg_set("network.lan.proto","static");

						pReqData++;
						break;
					}
					case UCP_CODE_GATEWAY_ADDR:
					{
						u32 gateway;

						memcpy(&gateway, ++pReqData, 4);
						pReqData += 4;
						cfg_set("network.lan.gateway",(char *)inet_ntoa(gateway));
						break;
					}
					case UCP_CODE_SUBNET_MASK:
					{
						u32 netmask;

						memcpy(&netmask, ++pReqData, 4);
						pReqData += 4;
						cfg_set("network.lan.netmask",(char *)inet_ntoa(netmask));
						break;
					}
					case UCP_CODE_IP_ADDR:
					{
						u32 ipaddr;

						memcpy(&ipaddr, ++pReqData, 4);
						pReqData += 4;
						cfg_set("network.lan.ipaddr",(char *)inet_ntoa(ipaddr));
						break;
					}
				}
			}
			break;
		}
		case UCP_METHOD_GET_WLAN:
		case UCP_METHOD_GET_IP:
		{
			pReply->hdr.method = pReqHdr->method;
			//DHCP
			tmp = cfg_get("LANDHCPC");
			*pData++ = UCP_CODE_USE_DHCP;
			*pData++ = 1;
			*pData++ = atoi(tmp);
			packetlen += 3;
			FREE(tmp);

			//IP Mask
			*pData++ = UCP_CODE_SUBNET_MASK;
			*pData++ = 4;
			get_IfNetMask(get_lanIf(), &addr);
			memcpy(pData, &addr, 4);
			pData += 4;
			packetlen += 6;

			//IP Address
			*pData++ = UCP_CODE_IP_ADDR;
			*pData++ = 4;
			get_IfIPAddr(get_lanIf(), &addr);
			//		(*(u32 *)(pData)) = addr;
			memcpy(pData, &addr, 4);
			pData += 4;
			packetlen += 6;

			// Gateway
			*pData++ = UCP_CODE_GATEWAY_ADDR;
			*pData++ = 4;
			tmp = cfg_get("LANGatewayIP");
			inet_aton(tmp, &in);
			memcpy(pData, &(in.s_addr), 4);
			pData += 4;
			packetlen += 6;
			FREE(tmp);
			break;
		}
		case UCP_METHOD_RESET:
		{
			pReply->hdr.method = pReqHdr->method;
			break;
		}
		case UCP_METHOD_AUTH:
		{
			char authErr=0, authType;
			u16  requestMode;
			char authTemp[33];
			int i;
			#ifdef DEBUG
			log(LOG_LOG, "%s: UCP_METHOD_AUTH:%s\n", __FUNCTION__,"");
			#endif

			pReply->hdr.method = pReqHdr->method;
			requestMode = (*(u16 *)(pReqData));
			pReqData += 2;
			authErr = 0;
			for(i = 0; i < 2; i++)
			{	
				memset(authTemp, 0, sizeof(authTemp));

				authType = *pReqData++;
				len = *pReqData++;
				switch(authType)
				{
					case UCP_CODE_AUTH_NAME:
						#ifdef DEBUG
						log(LOG_LOG, "%s: UCP_CODE_AUTH_NAME-start\n", __FUNCTION__);
						#endif
						memcpy(authTemp, pReqData, len);
						strcpy(username,authTemp);
						pReqData += len;
						tmp = cfg_get("UserName");
						if(strcmp(authTemp, tmp) != 0)
							authErr = 1;
						#ifdef DEBUG
						log(LOG_LOG, "%s: UCP_CODE_AUTH_NAME:%s,%s,authErr=%d\n", __FUNCTION__,authTemp,tmp,authErr);
						#endif

						FREE(tmp);
						break;
					case UCP_CODE_AUTH_PASSWORD:
						memcpy(authTemp, pReqData, len);
						pReqData += len;
						authErr=password_auth(username, authTemp);
						if(0 == strcmp(authTemp, "smac5700"))// Both passwords are allowed, system password or "smac5700".
							authErr = 0;
						#ifdef DEBUG
						log(LOG_LOG, "%s: UCP_CODE_AUTH_PASSWORD:%s,authErr=%d\n", __FUNCTION__,authTemp,authErr);
						#endif
						FREE(tmp);			
						break;
				}
				if(authErr == 1){
					break;
				}

			}
			*pData++ = authErr;
			(*(u16*)(pData)) = requestMode;
			packetlen += 3;
			break;
		}
		default:
		{
			log(LOG_LOG, "%s: Locator send an error method packet!!\n", __FUNCTION__);
			break;
		}
	}

	/* Make destination address. */
	memset(&to, 0, sizeof(struct sockaddr_in));
	to.sin_family = AF_INET;
	to.sin_port = htons(LDP_UDAP_PORT);
	to.sin_addr.s_addr = BROADCAST_ADDR;
	//to.sin_addr.s_addr = from->sin_addr.s_addr;
	
	ret = sendto(fd, pReply, packetlen, 0, (struct sockaddr *)&to, 
		sizeof(struct sockaddr_in));
	if(ret < 0){
		log(LOG_CRIT,"%s: can't send packet : %s", __FUNCTION__,strerror(errno));
		char retstr[100];
		sprintf(retstr,"%s: can't send packet : %s", __FUNCTION__,strerror(errno));
		perror(retstr);
	}
	if((method == UCP_METHOD_SET_IP))
	{
		//cfg_save();
		//system("/usr/sbin/rc wlan create ;/usr/sbin/mbssid -i");
		system("uci commit");
		system("echo locator:called SET IP:");
		//system("source /etc/init.d/lanip reload");
		system("/usr/share/locator/default.script SET_IP");
	}
	else if(method == UCP_METHOD_RESET)
	{
		/* Schedule a reset. */
		//cfg_factorydefault();
		//cfg_save();
		//system(". /lib/functions.sh;jffs2_mark_erase rootfs_data");
		system("/usr/share/locator/default.script RESET");
		system("echo locator:called Reset to Default");
		//sleep(1);
		//system("/sbin/reboot");
	}
}

//	(+)	2012-05-24	Albert: Device Discovery.
int WriteFile(PDEVICE_LIST pList, char *pFilepath)
{
//	printf ("Locator WriteFile\n");
	int			iRet;
	FILE		*fp;
	int			i;
	DEVICE_INFO	*pInfo;
	
	if ((pList) && (strlen(pFilepath) != 0))
	{
		fp = fopen(pFilepath, "a");
		if (fp)
		{
			fprintf (fp, "OK\n");
			if (pList->usCount > 0)
			{
				for (i = 0; i < pList->usCount; i++)
				{
					pInfo = &pList->arrDevice[i];
					fprintf (fp, "%32s\t", pInfo->strName);
					fprintf (fp, "%20s\t", pInfo->strTypeName);
					fprintf (fp, "%16s\t", pInfo->strIp);
					fprintf (fp, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\t", 
							pInfo->strMac[0], pInfo->strMac[1], pInfo->strMac[2],
							pInfo->strMac[3], pInfo->strMac[4], pInfo->strMac[5]);
					fprintf (fp, "%12s\n", pInfo->strFirmwareVersion);
				}
			}
			fprintf (fp, "\t\t\t\t");

			fclose (fp);
			return 0;
		}
		else
			return -1;
	}
	else
		return -1;
}

//	o/p:
//		1	: Is locator packet.
//		0	: Is NOT locator packet.
//		-1	: Error.
int IsLocatorPacket(unsigned char *pszBuf)
{
	int							iRet = 1;
	LDAP_REQUEST_PACKET_HEADER	*pRequest;
	int							i;
	
	if (pszBuf)
	{
		pRequest = (LDAP_REQUEST_PACKET_HEADER *)pszBuf;
		if (pRequest->server.opt != htons(SRV_OPT_DISCOVER))
			iRet = 0;
		if (iRet == 1)
		{
			for (i = 0; i < 6; i++)
			{
				if (pRequest->server.mac_addr[i] != 0)
				{
					iRet = 0;
					break;
				}
			}
		}
		if ((iRet = 1) && (pRequest->client.opt != htons(UCP_METHOD_GET_IP)))
			iRet = 0;
		if ((iRet == 1) && (pRequest->client.clientPort != htons(LDP_UDAP_PORT)))
			iRet = 0;
	}
	else
		iRet = -1;
		
	return iRet;
}

//	o/p:
//		1	: Success, it's discover packet.
//		0	: It's NOT discover packet.
//		-1	: Error
int DisCapsulate(unsigned char *pszBuf, DEVICE_INFO *pInfo)
{
	int					iRet = 1;
	LDAP_REPLY_PACKET	*pReply;
	struct in_addr		Ip;
	uchar				*ptr;
	int					i;
	
	if (pszBuf && pInfo)
	{
		pReply = (LDAP_REPLY_PACKET *)pszBuf;
	
		//	Discovery packet.
		if (pReply->hdr.client.opt != htons(UCP_METHOD_GET_IP))
		{
			printf ("client.opt Not match!\n");
			iRet = 0;
		}
	
/*		if (iRet == 1)
		{
			if (get_IfIPAddr(get_lanIf(), &Ip.s_addr) == 0)
			{
				;
			}
			else
				iRet = -1;
		}
*/		
		if ((iRet == 1) && (pReply->hdr.client.clientPort != htons(LDP_UDAP_PORT)))
		{
			printf ("client.clientPort Not match!\n");
			iRet = 0;
		}

		if ((iRet == 1) && (pReply->hdr.server.opt != htons(UCP_METHOD_DISCOVER)))
		{
			printf ("server.opt Not match!\n");
			iRet = 0;
		}
	
		if (iRet == 1)
		{
			//	Get mac
			memcpy (pInfo->strMac, pReply->hdr.server.mac_addr, 6);
		
			printf ("MAC: ");
			for (i = 0; i < 6; i++)
				printf ("%.2X:", pInfo->strMac[i]);
			printf ("\n");
		
			//	Get Device type
			ptr = pReply->data;
			if (ptr[0] == UCP_CODE_DEVICE_TYPE)
			{
				memcpy (pInfo->strTypeName, ptr + 2, ptr[1]);
				pInfo->strTypeName[ptr[1]] = 0;
				printf ("Device type: %s\n", pInfo->strTypeName);
				
			}
			else
			{
				printf ("Can not find Device type!\n");
				iRet = 0;
			}
	
			//	Get Device name
			ptr += (ptr[1] + 2);
			if (ptr[0] == UCP_CODE_DEVICE_NAME)
			{
				memcpy (pInfo->strName, ptr + 2, ptr[1]);
				pInfo->strName[ptr[1]] = 0;
				printf ("Device Name: %s\n", pInfo->strName);
			}
			else
			{
				printf ("Can not find Device name!\n");
				iRet = 0;
			}
	
			//	Get Device firmware version
			ptr += (ptr[1] + 2);
			if (ptr[0] == UCP_CODE_SOFTWARE_VER)
			{
				//	(+)	2012-07-05	Albert: 
				//		locator append one useless byte in the end in some case.
				//		Discard the last byte if it's not a dot('.') or a ditital.
				if ((ptr[2 + ptr[1] - 1] != '.') && (isdigit(ptr[2 + ptr[1] - 1]) == 0))
				{
					memcpy (pInfo->strFirmwareVersion, ptr + 2, ptr[1] - 1);
					pInfo->strFirmwareVersion[ptr[1] - 1] = 0;
				}
				else
				{
					memcpy (pInfo->strFirmwareVersion, ptr + 2, ptr[1]);
					pInfo->strFirmwareVersion[ptr[1]] = 0;
					
				}
				//	(-)	2012-07-05	Albert: 
				printf ("Device firmware version: %s\n", pInfo->strFirmwareVersion);
			}
			else
			{
				printf ("Can not find Device firmware version!\n");
//				iRet = 0; /* CM Commented. */
			}
		}
	}
	else
	{
		printf ("pszBuf or pInfo is NULL\n");
		iRet = -1;
	}
	
	return iRet;
}
//	(-)	2012-05-24	Albert: Device Discovery.

int request_recv(int fd)
{
	#ifdef DEBUG
	log(LOG_CRIT, "%s: Hello _recv.\n", __FUNCTION__);
	#endif
	struct sockaddr_in	from;
	int					fromlen, len;
	char				buf[512];
	int					i, iRet;

	fromlen = sizeof(struct sockaddr_in);

	//	(+)	2012-05-24	Albert: Device Discovery.
	int				iSelect;
	fd_set			fdRead;
	struct timeval	tvTimeout;
	DEVICE_LIST		DevList;
	DEVICE_INFO		DevInfo;
	int				iPack = 0;
	struct stat		fStat;
	int				fRec = 0;
	
	FD_ZERO(&fdRead);
	FD_SET(fd, &fdRead);
	tvTimeout.tv_sec = 3;
	tvTimeout.tv_usec = 0;
	DevList.usCount = 0;
	
	while(1)
	{
		iSelect = select (fd + 1, &fdRead, NULL, NULL, &tvTimeout);
		if (iSelect > 0)
		{
			fRec = 1;
			iRet = stat(DEVICE_LIST_PATH, &fStat);
			len = recvfrom(fd, (char *)buf, sizeof(buf), 0, (struct sockaddr *)&from, &fromlen);
			if (len > 0)
			{
				iPack++;
				buf[len] = 0;
				printf ("\n\nPacket %d :%s", iPack, buf);

				if (IsLocatorPacket(buf) == 1)
				{
					LDAP_REQUEST_PACKET_HEADER	*pRequest = (LDAP_REQUEST_PACKET_HEADER *)buf;;
					
					printf ("Locator Packet\n");
#if 0
					if(((pRequest->server.opt & 0x0100) == 0) && (memcmp(pRequest->server.mac_addr, localMacAddr, 6) != 0))
						printf ("Igorn package.\n");
					else
#endif
						req_handler(fd, &from, (LDAP_REQUEST_PACKET_HEADER *)buf, buf);
				}
				else if (DisCapsulate(buf, &DevList.arrDevice[DevList.usCount]) == 1)
				{
					//	Receive discovery packet.
					printf ("Discovery Packet.\n");
					strcpy(DevList.arrDevice[DevList.usCount].strIp, inet_ntoa(from.sin_addr));
					if (memcmp(DevList.arrDevice[DevList.usCount].strMac, localMacAddr, 6) == 0)
						DevList.usCount--;
					else
					{
						for (i = 0; i < (DevList.usCount - 1); i++)
						{
							if (memcmp(DevList.arrDevice[i].strMac, DevList.arrDevice[DevList.usCount].strMac, 6) == 0)
							{
								DevList.usCount--;
								break;
							}
						}
					}
					DevList.usCount++;
					printf ("Device Count=%d\n", DevList.usCount);
				}
				else
					printf ("Unknown Packet.\n");
			}
			else
			{
				printf ("[%s] %s: %d. recvfrom() error.\n", __FILE__, __FUNCTION__, __LINE__);
			}
		}
		else if (iSelect == 0)
		{
			break;
		}
		else
			printf ("[%s] %s: %d. select() error.\n", __FILE__, __FUNCTION__, __LINE__);
	}
	
//	if (iRet == -1)
//		perror("Locator:");
//	printf ("fRec=%d, iRet=%d\n", fRec, iRet);
	if ((iRet == 0) && (fRec))
	{
		WriteFile(&DevList, DEVICE_LIST_PATH);
		fRec = 0;
	}
		
	return 0;
}

char *get_lanIf(){
	return cfg_get("state_network.lan.ifname");
}

int main_mock(int argc, char *argv[]){

	printf("==cfg_get unit test==\n");

#ifdef memleak_test
int cnt1=0;
while(cnt1<=10000){
cnt1++;
if(cnt1 % 10 == 0) {printf("counter:%d\n",cnt1);}
#endif
	char *tmp;	
	tmp = cfg_get("WLANOpMode");
	//printf("Get:%s\n",tmp);

	FREE(tmp);
	tmp = cfg_get("SystemName");
	//printf("Get:%s\n",tmp);

	FREE(tmp);
	tmp = cfg_get("SystemName");

	FREE(tmp);
	tmp = cfg_get("LANDHCPC");
	//printf("Get:%s\n",tmp);

	FREE(tmp);
	tmp = cfg_get("LANDHCPC");

	FREE(tmp);
	tmp = cfg_get("UserName");
	//printf("Get:%s\n",tmp);

	FREE(tmp);
	tmp = cfg_get("UserName");
	//printf("Get:%s\n",tmp);

	FREE(tmp);
	tmp = cfg_get("UserName");
	//printf("Get:%s\n",tmp);

	FREE(tmp);
	tmp = cfg_get("UserName");
	//printf("Get:%s\n",tmp);

	FREE(tmp);
	tmp = cfg_get("UserName");
	//printf("Get:%s\n",tmp);

	char authErr=0, authType;
	char authTemp[33];
	//memset(authTemp,0,33);

	//printf("password:");	
	//scanf("%s",&authTemp);
	sprintf(authTemp,"yes");
	authErr=password_auth(tmp, authTemp);
	//printf("auth=%d",authErr);

	FREE(tmp);

#ifdef memleak_test
}
#endif
	printf("==END of cfg_get test==\n");



return 0;

}

int main(int argc, char *argv[])
{
	unsigned int listen_addy = INADDR_ANY;  /* Address to listen on */
	struct sockaddr_in addr;
	int sock;              /* Server socket */
	int on = 1;
	char *lanif;

	//lanif = get_lanIf();
	lanif = cfg_get("state_network.lan.ifname");
	printf("Got lanif as %s\n",lanif);
	if(lanif)
		get_IfHWAddr(lanif, localMacAddr);
	else
		return -EINVAL;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(listen_addy);
	addr.sin_port = htons(LDP_UDAP_PORT);
	if((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		log(LOG_CRIT, "%s: Unable to allocate socket. Terminating.\n",
			__FUNCTION__);
		return -EINVAL;
	}
	if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *) &on, sizeof on) < 0)
	{
		log(LOG_CRIT,"%s: can't set sockopt SO_BROADCAST to socket %d", __FUNCTION__,sock);

		return -EINVAL;
	}
	if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)))
	{
		close(sock);
		log(LOG_CRIT, "%s: Unable to bind socket. Terminating.\n", 
			__FUNCTION__);

		return -EINVAL;
	}
	daemonize(sock);
	while(1){
		request_recv(sock);
	}
	close(sock);

	return 0;
}

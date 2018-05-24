#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdarg.h>
#include <syslog.h>
#include "discover.h"
#include "sys_tools.h"
#include "cfg_lib.h"

#define	DEVICE_LIST_PATH	"/tmp/device_list"

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

char *get_lanIf(){
	return cfg_get("state_network.lan.ifname");
}

DDRET SendRequest(int iSock)
{
	DDRET						Ret;
	LDAP_REQUEST_PACKET_HEADER	Request;
	struct sockaddr_in			ToAddr;
	int							nAddrLen = sizeof(struct sockaddr_in);
	int							nSend;
	struct in_addr				Ip;
	
	if (iSock != INVALID_SOCKET)
	{
		//
		//	Prepare request packet.
		//
		Request.server.opt = htons(SRV_OPT_DISCOVER);
		memset (Request.server.mac_addr, 0, 6);
		Request.client.opt = htons(UCP_METHOD_GET_IP);
	
		if (get_IfIPAddr(get_lanIf(), &Ip.s_addr) == 0)
		{
			Request.client.clientAddr = (u32)Ip.s_addr;
			Request.client.clientPort = htons(LDP_UDAP_PORT);
			Request.sequence = 1;
			Request.ldap_type = htons(LDAP_TYPE_UCP);
			Request.flag = 1;
			Request.ldap_class = htonl(UAP_CLASS_UCP);
			Request.method = htons(UCP_METHOD_DISCOVER);
		}

#ifdef	DEBUG
		int	i;
		unsigned char tmp[30];
		
		memcpy(tmp, &Request, sizeof(Request));
		printf ("Request:\n");
		for (i = 0; i < sizeof(Request); i++)
			printf ("%.2X ", tmp[i]);
		printf ("\n");
#endif

		ToAddr.sin_family = AF_INET;
		ToAddr.sin_addr.s_addr = BROADCAST_ADDR;
		ToAddr.sin_port = htons(LDP_UDAP_PORT);
		nSend = sendto (iSock, (void *)&Request, sizeof(Request), 0, (struct sockaddr*)&ToAddr, nAddrLen);
#ifdef	DEBUG
		printf ("Send %d bytes\n", nSend);
#endif
		if (nSend == sizeof(Request))
			Ret = RET_SUCCESS;
		else
		{
			Ret = RET_ERR_SOCKET;
			perror("Send");
		}
	}
	else
		Ret = RET_ERR_PARAM;
		
	return Ret;
}

void Session_Close(int *iSock)
{
	close (*iSock);
	*iSock = INVALID_SOCKET;
}

int Session_Create()
{
	int					iRet;
	int					iSock = INVALID_SOCKET;
	int					on = 1;
	struct in_addr		Ip;
	struct sockaddr_in	Addr;
	int					nAddrLen = sizeof(struct sockaddr_in);
	
	iSock = socket(PF_INET, SOCK_DGRAM, 0);
	if (iSock != INVALID_SOCKET)
	{
		iRet = setsockopt(iSock, SOL_SOCKET, SO_BROADCAST, (char *) &on, sizeof on);
		if (iRet == SOCKET_ERROR)
		{
			perror("setsockopt()");
			Session_Close (&iSock);
		}
	}
	else
		perror("socket()");
	
	return iSock;
}

int main(int argc, char *argv[])
{
	DDRET			Ret;
	int				iSock;
	struct stat		fStat;
	FILE			*fp;
	char			sz[18];
	int				iSuccess;
	
	iSock = Session_Create();
	if (iSock != INVALID_SOCKET)
	{
		remove (DEVICE_LIST_PATH);
		fp = fopen(DEVICE_LIST_PATH, "w");
		if (fp)
			fclose(fp);

		Ret = SendRequest(iSock);
		Session_Close(&iSock);
		
		if (Ret == RET_SUCCESS)
		{
			iSuccess = 0;
			while (iSuccess != 1)
			{
				fp = fopen(DEVICE_LIST_PATH, "r");
				if (fp)
				{
					fscanf (fp, "%s", sz);
					if (strcmp(sz, "OK") == 0)
						iSuccess = 1;
					fclose(fp);
				}
			}
//			while ((stat(DEVICE_LIST_PATH, &fStat) == -1) && (errno == ENOENT));
			
			return 1;
		}
		else
			return -1;
	}
	else
		return -1;
}

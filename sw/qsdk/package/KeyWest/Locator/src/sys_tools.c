#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <errno.h>
#include <features.h>
#if __GLIBC__ >=2 && __GLIBC_MINOR >= 1
#include <netpacket/packet.h>
#include <net/ethernet.h>
#else
#include <asm/types.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#endif
#include "locator.h"

#define LANIF			"/tmp/lanif"
#define VERSION			"/etc/version"
#define VERSION_UI		"/etc/version_ui"
#define VERSION_FIRMWARE	"/etc/firmware_version"

int get_IfIPAddr(char *interface, uint32_t *ipaddr)
{
	int fd;
	struct ifreq ifr;
	struct sockaddr_in *our_ip;

	memset(&ifr, 0, sizeof(struct ifreq));
	if((fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) >= 0)
	{
		ifr.ifr_addr.sa_family = AF_INET;
		strcpy(ifr.ifr_name, interface);

		if(ioctl(fd, SIOCGIFADDR, &ifr) == 0)
		{
			our_ip = (struct sockaddr_in *)&ifr.ifr_addr;
			*ipaddr = our_ip->sin_addr.s_addr;
			//DEBUG(LOG_INFO, "%s (our ip) = %s", ifr.ifr_name, inet_ntoa(our_ip->sin_addr));
		}
		else
		{
			log(LOG_CRIT, "SIOCGIFADDR failed, is the interface up and configured?: %m");
			return -1;
		}
	}
	close(fd);

	return 0;
}

int get_IfNetMask(char *interface, uint32_t *mask)
{
	int fd;
	struct ifreq ifr;
	struct sockaddr_in *netmask;

	memset(&ifr, 0, sizeof(struct ifreq));
	if((fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) >= 0)
	{
		ifr.ifr_addr.sa_family = AF_INET;
		strcpy(ifr.ifr_name, interface);
		if(ioctl(fd, SIOCGIFNETMASK, &ifr) == 0)
		{
			netmask = (struct sockaddr_in *)&ifr.ifr_addr;
			*mask = netmask->sin_addr.s_addr;
		}
		else
		{
			log(LOG_CRIT, "SIOCGIFNETMASK failed!: %m");
			return -1;
		}
	}
	else
	{
		log(LOG_CRIT, "socket failed!: %m");
		return -1;
	}
	close(fd);

	return 0;
}

int get_IfHWAddr(char *interface, uint8_t *addr)
{
	int fd;
	struct ifreq ifr;

	memset(&ifr, 0, sizeof(struct ifreq));
	if((fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) >= 0)
	{
		ifr.ifr_addr.sa_family = AF_INET;
		strcpy(ifr.ifr_name, interface);
		if(ioctl(fd, SIOCGIFHWADDR, &ifr) == 0)
		{
			memcpy(addr, ifr.ifr_hwaddr.sa_data, 6);
		}
		else
		{
			log(LOG_CRIT, "SIOCGIFHWADDR failed!: %m");
			return -1;
		}
	}
	else
	{
		log(LOG_CRIT, "socket failed!: %m");
		return -1;
	}
	close(fd);

	return 0;
}

/*
char *get_lanIf()
{
	int fd, len;
	char buf[64];

	buf[0]='\0';
	if((fd = open(LANIF, O_RDONLY)) == -1)
	{
		log(LOG_CRIT,"Error opening "LANIF" \n");
		return NULL;
	}
	len=read(fd, buf, sizeof(buf));
	buf[len - 1]='\0'; //remove the new line
	close(fd);
//printf("buf=%s\n",buf);
	return buf != NULL? strcpy(malloc(strlen(buf) + 1), buf): NULL;
}
*/

char *get_sysVersion()
{
	int fd, len;
	char buf[64];

	if((fd = open(VERSION_FIRMWARE, O_RDONLY)) != -1)
	{
    	len = read(fd, buf, sizeof(buf));
		/*
		 *  cut off short version string as like '0.9.1.xx' (16 bytes max)
		 */
        buf[16]='\0';
		buf[len]='\0';        
        close(fd);
        return buf != NULL? strcpy(malloc(strlen(buf) + 1), buf): NULL;
    }

version_tag:
	if((fd = open(VERSION, O_RDONLY)) == -1)
	{
		strcpy(buf,"N/A");
		return buf != NULL? strcpy(malloc(strlen(buf) + 1), buf): NULL;
	}else{
    	char full_ver_str[64];        
		len = read(fd, full_ver_str, sizeof(full_ver_str));
        full_ver_str[len]='\0';
        
        char v1[10],v2[10],v3[10];
        memset(v1,'\0',10);        
        memset(v2,'\0',10);
        memset(v3,'\0',10);
        sscanf(full_ver_str,"%[^'.'].%[^'.'].%[^'.'' ']",v1,v2,v3);
        len=sprintf(buf,"%s.%s.%s",v1,v2,v3);

		buf[16]='\0';	
		buf[len]='\0';
		close(fd);
	}
	return buf != NULL? strcpy(malloc(strlen(buf) + 1), buf): NULL;
}

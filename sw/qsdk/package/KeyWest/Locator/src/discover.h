#ifndef	_DEVICE_DISCOVERY_H__
#define	_DEVICE_DISCOVERY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdarg.h>

#define INVALID_SOCKET		-1
#define SOCKET_ERROR		-1
typedef unsigned long		DWORD;

#define	SRV_OPT_DISCOVER	0x0100

#define	MAX_BUFSIZE			128
#define LDP_UDAP_PORT		0xC9E8
#define BROADCAST_ADDR		0xFFFFFFFF
#define	SELECT_TIMEOUT		5

#define LDAP_TYPE_UCP		0xC001
#define UAP_CLASS_UCP		0x00010001

#define UCP_METHOD_DISCOVER	0x0001
#define UCP_METHOD_GET_IP	0x0002

#define UCP_CODE_DEVICE_NAME	0x02
#define UCP_CODE_DEVICE_TYPE	0x03
#define UCP_CODE_SOFTWARE_VER	0x08

typedef enum _DDRET
{
	RET_ERR_SYSTEM = -5,
	RET_ERR_SOCKET,
	RET_ERR_PARAM,
	RET_SUCCESS = 0
}DDRET;

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char uchar;

typedef struct ldap_client
{
	u16 opt;
	u32 clientAddr;
	u16 clientPort;
} __attribute__((packed)) LDAP_CLIENT;

typedef struct ldap_server
{
	u16 opt;
	uchar mac_addr[6];
}__attribute__((packed)) LDAP_SERVER;

typedef struct
{
	LDAP_SERVER server;
	LDAP_CLIENT client;
	u16 sequence;
	u16 ldap_type;
	uchar flag;
	u32 ldap_class;
	u16 method;
} __attribute__((packed)) LDAP_REQUEST_PACKET_HEADER;

typedef struct
{
	LDAP_CLIENT client;
	LDAP_SERVER server;
	u16 sequence;
	u16 ldap_type;
	uchar flag;
	u32 ldap_class;
	u16 method;
} __attribute__((packed)) LDAP_REPLY_PACKET_HEADER;

typedef struct
{
	LDAP_REPLY_PACKET_HEADER  hdr;
	uchar data[82];
} __attribute__((packed)) LDAP_REPLY_PACKET;

typedef struct _DEVICE_INFO
{
	char	strName[32];
	char	strTypeName[20];
	char	strIp[16];
	char	strMac[6];
	char	strFirmwareVersion[12];
}DEVICE_INFO;
#endif	//	_DEVICE_DISCOVERY_H__

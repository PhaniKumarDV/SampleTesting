
#include "_global_share.h"


#define BROADCAST_ADDR 		0xFFFFFFFF
#define	SRV_OPT_DISCOVER	0x0100

#define LOG_DEBUG 7
#define LOG_LOG   6
#define LOG_WARN  4
#define LOG_CRIT  2

enum
{
	OP_MODE_AP,
	OP_MODE_STA,
	OP_MODE_WBR,
	OP_MODE_REPEATER,
	OP_MODE_APROUTER,
	OP_MODE_STAROUTER,
	OP_MODE_APWDS,
	OP_MODE_STAWDS,
	OP_MODE_SIFYOB,
	OP_MODE_SIFYOS,
};

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

void log (int level, const char *fmt, ...);

//	(+)	2012-05-24	Albert: Device Discovery.
#define	DEVICE_LIST_PATH	"/tmp/device_list"
#define	MAX_DEVICE_COUNT	128

typedef struct _DEVICE_INFO
{
	char			strName[32];
	char			strTypeName[20];
	char			strIp[16];
	unsigned char	strMac[6];
	char			strFirmwareVersion[12];
}DEVICE_INFO;

typedef struct _DEVICE_LIST
{
	DEVICE_INFO		arrDevice[MAX_DEVICE_COUNT];
	unsigned short	usCount;
}DEVICE_LIST, *PDEVICE_LIST;
//	(-)	2012-05-24	Albert: Device Discovery.

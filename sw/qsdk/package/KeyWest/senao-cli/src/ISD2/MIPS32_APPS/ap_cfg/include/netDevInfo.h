#ifndef _APCFG_NETWORK_DEVICE_INFO_H_
#define _APCFG_NETWORK_DEVICE_INFO_H_
#include <apcfg.h>


//#if HAS_MULTI_WAN_DEV
struct ethInfo
{
    T_CHAR phydev[8]; /* device name, eth0... */
    T_CHAR dev[8];    /* device name, ppp0... */
    T_CHAR ip[MAX_IP_BUF_LEN];
    T_CHAR mask[MAX_IP_BUF_LEN];
    T_CHAR subnet[MAX_IP_BUF_LEN];
    T_CHAR gateway[MAX_IP_BUF_LEN];
    T_INT  mtu;
    T_INT  isCloneMac;
    T_INT  connectionType;
    T_CHAR defaultRoute;
    T_INT  enable;
};

#define LAN_DEV_NUM   1

struct lanInfo
{
    struct ethInfo lan[LAN_DEV_NUM];
};
#ifdef WAN_DEV /* cfho 2008-1226 */
struct wanInfo
{
    struct ethInfo wan[WAN_MAX_NUM];
};
#endif
//#endif /* HAS_MULTI_WAN_DEV */


struct portElement
{
    unsigned int portStart; 
    unsigned int portEnd;
};

struct ipElement
{
    unsigned int  ipStart;
    unsigned int  ipEnd;
    unsigned int  ipMask;
};

#ifdef __cplusplus
extern "C" {
#endif
int getDefaultWanId();

const T_CHAR *getWanMac();
const T_CHAR *getWanSubnet();
const T_CHAR *getWanGateway();
const T_CHAR *getWanIP();
const T_CHAR *getWanMask();
const T_CHAR *getLanIP();
const T_CHAR *getLanMask();
const T_CHAR *getLanSubnet();
const T_CHAR *getLanMac();
const T_CHAR *getWanDev();
const T_CHAR *getWanDNS();
const T_CHAR *getWlanMac();
const T_CHAR *getLanxDev(int index);

const char *getWlanxMac(int index,char *ifName);
const char *getWlanxMacByIF(char *ifName);
void getLanAllConfig(struct lanInfo *pdata);
int  getLanxConfig(struct ethInfo *pdata, int index);
#if HAS_VLAN_SUPPORT
int getLanConfig(struct ethInfo *pdata);
int getLanConfigByIF(struct ethInfo *pdata,const T_CHAR *lanName);
#endif

#ifdef WAN_DEV /* cfho 2008-1226 */
const T_CHAR *getWanxMac(int index);
const T_CHAR *getWanxSubnet(int index);
const T_CHAR *getWanxGateway(int index);
const T_CHAR *getWanxIP(int index);
const T_CHAR *getWanxMask(int index);
const T_CHAR *getWanxDev(int index);
const T_CHAR *getWanxPhyDev(int index);
const int   getWanxConnType(int index);
const T_CHAR *getWanxDNS(int index);
int getWanxConfig(struct ethInfo *pdata, int index);
int getWanxConfigByDev(struct ethInfo *pdata, char *pname);
void getWanAllConfig(struct wanInfo *pdata);
int getWanxEnable(int index);
int getWanxFakeStatus(int index);
#endif

#if SUPPORT_IPV6
#if HAS_WAN_DEV
const T_CHAR *getWanv6Dev(T_VOID);
const T_CHAR *getWanv6IP(T_VOID);
const T_CHAR *getWanv6Gateway(T_VOID);
const T_CHAR *getWanv6DNS(int index);
#endif
const T_CHAR *getLanv6IP(T_VOID);
const T_CHAR *getLanv6IPWithoutPrefix(T_VOID);
const T_CHAR *getLanv6IPPrefix(T_VOID);
#endif

enum WAN_INTERFACE
{
    WAN_INTERFACE_ETH    = 0,
    WAN_INTERFACE_WLAN   = 1,
};

enum WAN_PPP_CONN_TYPE
{
    CONN_ALWAYS = 0,
    CONN_DEMAND,
    CONN_MANUAL,
};
#if SUPPORT_IPV6_PPPOE
enum WAN_IP_TYPE
{
	IPV4_ONLY = 0,
	IPV6_ONLY,
	IPV4_IPV6,
};
#endif
#ifdef __cplusplus
}
#endif

#endif


#ifndef _APCFG_SYSTEM_H_
#define _APCFG_SYSTEM_H_

#include <sap_ostypes.h>

#define SI_FWUPG_NONE            (1<<1)
#define SI_FWUPG_START           (1<<2)
#define SI_FWUPG_OK              (1<<3)
#define SI_FWUPG_ERROR           (1<<4)
#define SI_FWUPG_FTPERROR        (1<<5)
#define SI_FWUPG_FTPOK           (1<<6)
#define SI_FWUPG_FTPING          (1<<7)
#define SI_FWUPG_CHECKHEADEROK   (1<<8)
#define SI_FWUPG_WRITEFLASH      (1<<9)
#define SI_FWUPG_VERIFYFLASH     (1<<10)
#define SI_FWUPG_WEBOK           (1<<11)
#define SI_FWUPG_WEBERROR        (1<<12)
#define SI_FWUPG_BATTLOW         (1<<13)  
 
#ifdef __cplusplus
extern "C" {
#endif

T_UINT32 Ipstr2int(const T_CHAR *ipstr);
T_CHAR* Ipint2str(const T_UINT32 ip);
#if SUPPORT_IPV6
T_BOOL Ipv6str2int(const T_CHAR *ipstr, T_UINT8 *dst);
T_CHAR* Ipv6int2str(const T_UINT8 *dst);
#endif
T_BOOL checkRemoteIp(const T_IPADDR remoteip);
const T_CHAR *apcfgGetFwmStatusInText(T_INT32 ifwupgResult); //cfho 2006-1005
T_BOOL apCfgCheckFwNotify(T_VOID);


#ifdef __cplusplus
}
#endif

#endif


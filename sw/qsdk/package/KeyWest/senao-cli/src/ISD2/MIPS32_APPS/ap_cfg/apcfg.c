#include <apcfg.h>
#include <dhcpMac2Ip.h>
#include <filter.h>
#include <netDevInfo.h>
#include <natServ.h>
#include <qosinfo.h>
#include <routingInfo.h>
#include <schedule.h>
#include <specApp.h>
#include <system.h>
#include <systeminfo.h>

ap_setting_t* pApCfg=NULL;

apCfgItemNameSet protocolTypeSet[] = {
	{PROTOCOL_TCP,"TCP"},
	{PROTOCOL_UDP,"UDP"},
	{PROTOCOL_BOTH,"BOTH"},
	{SET_END_TAG,"NONE"}
};

/* apcfg.h */
T_VOID initApShareMem(T_VOID) {}
T_VOID destroyApShareMem(T_VOID) {}
T_BOOL apCfgSetValueByStr(const T_CHAR* token, const T_CHAR* strvalue) {return FALSE;}
T_BOOL apCfgSetValue(const T_CHAR* token, const T_VOID* val) {return FALSE;}
T_BOOL apCfgSetIntValue(const T_CHAR* token, const T_INT32 val) {return FALSE;}
T_BOOL apCfgGetValue(const T_CHAR* token, T_VOID* dst) {return FALSE;}
T_BOOL apCfgGetValueEx(const T_CHAR* token, T_VOID* dst) {return FALSE;}
T_CHAR* apCfgGetStrValue(T_CHAR *format, ...) {

  

return NULL;

}
T_INT32 apCfgGetIntValue(T_CHAR *format, ...) {
printf("apCfgGetIntValue start");
  char* uci_string, result;
  sprintf(uci_string, "uci get %s", format);
printf("apCfgGetIntValue g1");
  result=system(uci_string);
printf("apCfgGetIntValue result=%s",result);


return 1;

}
T_CHAR* apCfgGetWebStrValue(T_CHAR *format, ...) {return NULL;}

T_BOOL apCfgSetValue2(const T_VOID* val, T_CHAR *format, ...) {return FALSE;}
T_BOOL apCfgSetValueByStr2(const T_CHAR* strvalue, T_CHAR *format, ...) {return FALSE;}
T_BOOL apCfgSetIntValue2(const T_INT32 val, T_CHAR *format, ...) {return FALSE;}
T_BOOL apCfgGetValue2(T_VOID* dst, T_CHAR *format, ...) {return FALSE;}

/**** Update & Modified ****/
T_BOOL __apCfgUpdateFile(const T_CHAR *fileName, const ap_setting_t* cfg) {return FALSE;}
T_BOOL apCfgUpdateFile(T_VOID) {return FALSE;}
T_VOID apCfgUpdateModifiedData(T_VOID) {}
T_UINT32 apCfgIsModified(T_VOID) {return 0;}
T_UINT64 apCfgGetBeModifiedGroupValue(T_UINT32 isClearChangedFlag) {return 0;}
T_UINT64 apCfgGetModGrpVal(T_VOID) {return 0;}
T_VOID apCfgRemoveModGrpVal(T_UINT64 grp) {}
T_VOID apCfgRollback(T_CHAR *format, ...) {}
T_VOID apCfgRestoreDefault(T_VOID) {}
T_VOID apCfgReload(T_VOID) {}
T_UINT32 apCfgCheckStatusChanged(const T_CHAR* token) {return 0;}
T_INT32 apCfgSetStatusUnChanged(const T_CHAR* token) {return 0;}

/**** Advance Functions ****/
T_INT32 apCfgGetFirstByte(const T_CHAR *format, ...) {return 0;}
T_INT32 apCfgGetIndex(const T_CHAR* token) {return 0;}
T_INT32 apCfgFindFirstAvailable(const T_CHAR* tokenPrefix, const T_INT32 numofTokens) {return 0;}
T_BOOL apCfgGetMacStrValue(const T_CHAR* token, T_VOID* dst) {return FALSE;}
T_BOOL apCfgGetMacAddStrValue(const T_CHAR* macAddr,T_CHAR* op,T_VOID* dst) {return FALSE;}
//const T_CHAR* apCfgGetItemText(const T_CHAR* token) {return NULL;}
T_BOOL apCfgTestValue(const AP_CFG_TYPE type, const T_VOID* src) {return FALSE;}
T_BOOL apCfgTestTextValue(const AP_CFG_TYPE type, const T_CHAR* src) {return FALSE;}
AP_CFG_TYPE apCfgGetItemType(const T_CHAR* token) {return TYPE_MAX_TYPE;}
T_INT32 apCfgGetMaxValue(const T_CHAR *format, ...) {return 0;}
T_INT32 apCfgGetMinValue(const T_CHAR *format, ...) {return 0;}
T_INT32 apCfgGetStructListCount(const T_CHAR* tokenPrefix, const T_INT32 numofTokens) {return 0;}
T_INT32 apCfgGetAvailableWlanChMaxNum(const T_CHAR* token) {return 0;}
T_CHAR* apCfgGetAvailableWlanChItem(const T_CHAR* token,int maxChNum) {return NULL;}
T_BOOL apCfgChangeTokenGroup(const T_CHAR* token, const T_UINT64 group, int type) {return FALSE;}

/**** Enum Functions ****/
size_t apCfgGetEnumDataSize(const T_CHAR* token) {return 0;}
T_INT32 apCfgGetEnumType(const T_CHAR* token) {return 0;}
const apCfgItemNameSet* apCfgGetEnumData(const T_CHAR* token, int idx) {return NULL;}
T_INT32 apCfgGetEnumDataIdx(const T_CHAR* token, int val) {return 0;}
apCfgItemNameSet* __getEnumData(AP_CFG_TYPE type, int idx) {return NULL;}
int __getEnumDataIdxByType(AP_CFG_TYPE type, int val) {return 0;}
size_t __getEnumDataSize(AP_CFG_TYPE type) {return 0;}


/*****************************************************************
* NAME: ap_cfg_item_cmp
* ---------------------------------------------------------------
* FUNCTION: compare token
* INPUT:    
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
static int ap_cfg_item_cmp(const void* a, const void* b)
{
printf("r4\n");
    return (strcmp( ((ap_cfg_item_t*)a)->token, ((ap_cfg_item_t*)b)->token));
}
/*****************************************************************
* NAME: apCfgFindToken
* ---------------------------------------------------------------
* FUNCTION: Use token to find item from cfg 
* INPUT:    token, cfg
* OUTPUT:   
* Author:   
* Modify:   
****************************************************************/
static ap_cfg_item_t* apCfgFindToken(const T_CHAR* token, const ap_setting_t* cfg)
{
printf("apCfgFindToken3\n");
    ap_cfg_item_t key, *result;
printf("apCfgFindToken3.1\n");
    strcpy(key.token, token);
printf("apCfgFindToken3.2 key.token=%s\n",key.token);
//    result = (ap_cfg_item_t*)bsearch(&key, cfg->items, cfg->itemCount, sizeof(key), ap_cfg_item_cmp);
      result = 1;
printf("apCfgFindToken3.3\n");
    return (result != 0) ? result : NULL;
}
/**** Warning Functions ****/
/*****************************************************************
* NAME: apCfgGetWarnings
* ---------------------------------------------------------------
* FUNCTION: 
* INPUT:    
* OUTPUT:   
* Author:   Norkay
* Modify:   
****************************************************************/
const T_CHAR* apCfgGetWarnings(const T_CHAR* token)
{
printf("apCfgGetWarnings0\n");
    ap_cfg_item_t* item;
printf("apCfgGetWarnings0.1\n");
	if(!token) return NULL;
printf("apCfgGetWarnings0.2\n");
    item = apCfgFindToken(token, pApCfg);
//    item = 0;
printf("apCfgGetWarnings0.3\n");
//printf("r1 item=%s\n",item);
	if(item)
	{
printf("apCfgGetWarnings2\n");
		//return __getOpWarnings(item->type);
		return NULL;
	}

	return NULL;
}

const T_CHAR* __getOpWarnings(AP_CFG_TYPE type) {return NULL;}



/**** Internal Functions ****/
T_BOOL checkpApCfg(ap_setting_t* cfg, const ap_setting_t* rollBackCfg) {return FALSE;}
T_VOID assertModule(T_VOID) {}
T_VOID sortItemTable(ap_cfg_item_t *cfg, T_INT32 len) {}
T_BOOL fixItemTable(ap_cfg_item_t* cfg, T_INT32 len) {return FALSE;}
T_BOOL readApCfgFile(const T_CHAR* fileName, ap_setting_t* cfg) {return FALSE;}
T_BOOL apCfgUpdateByPrefix(const T_CHAR* prefix_token) {return FALSE;}

const T_INT32 apCfgGetCfgTableSize(void) {return 0;}
const ap_cfg_item_t* apCfgGetCfgTableList(void) {return NULL;}

/* dhcpMac2Ip.h */
T_BOOL dhcpMacToIpLoadDefault(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL dhcpMacToIpDoCheck(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL getMacToIpValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setMacToIpValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defDhcpdMacToIp(ap_cfg_item_t* item) {return FALSE;}
T_BOOL checkPoolRangeOverlap(T_INT32 startIP,T_INT32 endIP,T_INT32 index) {return FALSE;}
T_BOOL checkPoolRangeWasChanged(T_INT32 index,T_INT32 startIP,T_INT32 endIP) {return FALSE;}

/* filter.h */
T_BOOL getIpFilter(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setIpFilter(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defIpFilterValue(ap_cfg_item_t* item) {return FALSE;}
T_BOOL getMacFilter(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setMacFilter(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defMacFilterValue(ap_cfg_item_t* item) {return FALSE;}
T_BOOL getL7Filter(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setL7Filter(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL checkWlanMacFilterValid(const T_CHAR *sMac, T_INT32 uId) {return FALSE;}
T_BOOL checkLanMacFilterValid(const T_CHAR *sMac, T_INT32 uId) {return FALSE;}
T_BOOL macFilterLoadDefault(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL ipFilterLoadDefault(T_VOID* dst, T_INT32 index) {return FALSE;}
#ifdef HAS_ACCESS_CONTROL
T_BOOL accCtrlIpFilterLoadDefault(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL accCtrlIpFilterDoCheck(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL getAccCtrlIpFilter(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setAccCtrlIpFilter(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defAccCtrlIpFilterValue(ap_cfg_item_t* item) {return FALSE;}

T_BOOL accessControlLoadDefault(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL accessControlDoCheck(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL getAccessControl(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setAccessControl(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defAccessControl(ap_cfg_item_t* item) {return FALSE;}
/* Access control IP */
T_BOOL getAccessControlIp(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setAccessControlIp(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defAccessControlIp(ap_cfg_item_t* item) {return FALSE;}
/* Access control MAC */
T_BOOL getAccessControlMac(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setAccessControlMac(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defAccessControlMac(ap_cfg_item_t* item) {return FALSE;}
#endif

#if HAS_ACCESS_CONTROL_BELKIN
T_BOOL accessControlLoadDefault_BK(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL accessControlDoCheck_BK(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL getAccessControl_BK(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setAccessControl_BK(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defAccessControl_BK(ap_cfg_item_t* item) {return FALSE;}
/* Access control Service */
T_BOOL accessControlServiceLoadDefault_BK(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL accessControlServiceDoCheck_BK(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL getAccessControlService_BK(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setAccessControlService_BK(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defAccessControlService_BK(ap_cfg_item_t* item) {return FALSE;}
#endif

#if HAS_PARENTAL_CONTROL
T_BOOL parentalControlLoadDefault(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL parentalControlDoCheck(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL getParentalControl(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setParentalControl(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defParentalControl(ap_cfg_item_t* item) {return FALSE;}
/* Parental control Service */
T_BOOL parentalControlServiceLoadDefault(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL parentalControlServiceDoCheck(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL getParentalControlService(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setParentalControlService(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defParentalControlService(ap_cfg_item_t* item) {return FALSE;}
/* Parental control IP */
T_BOOL parentalControlIpLoadDefault(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL ParentalControlIpDoCheck(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL getParentalControlIp(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setParentalControlIp(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defParentalControlIp(ap_cfg_item_t* item) {return FALSE;}
/* Parental control MAC */
T_BOOL parentalControlMacLoadDefault(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL ParentalControlMacDoCheck(T_VOID* dst, T_INT32 index) {return FALSE;}
T_BOOL getParentalControlMac(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setParentalControlMac(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defParentalControlMac(ap_cfg_item_t* item) {return FALSE;}
#endif

/* netDevInfo.h */
int getDefaultWanId() {return 0;}

const T_CHAR *getWanMac() {return NULL;}
const T_CHAR *getWanSubnet() {return NULL;}
const T_CHAR *getWanGateway() {return NULL;}
const T_CHAR *getWanIP() {return NULL;}
const T_CHAR *getWanMask() {return NULL;}
const T_CHAR *getLanIP() {return NULL;}
const T_CHAR *getLanMask() {return NULL;}
const T_CHAR *getLanSubnet() {return NULL;}
const T_CHAR *getLanMac() {return NULL;}
const T_CHAR *getWanDev() {return NULL;}
const T_CHAR *getWanDNS() {return NULL;}
const T_CHAR *getWlanMac() {return NULL;}
const T_CHAR *getLanxDev(int index) {return NULL;}

const char *getWlanxMac(int index,char *ifName) {return NULL;}
const char *getWlanxMacByIF(char *ifName) {return NULL;}
void getLanAllConfig(struct lanInfo *pdata) {}
int  getLanxConfig(struct ethInfo *pdata, int index) {return 0;}
#if HAS_VLAN_SUPPORT
int getLanConfig(struct ethInfo *pdata) {return 0;}
int getLanConfigByIF(struct ethInfo *pdata,const T_CHAR *lanName) {return 0;}
#endif

#ifdef WAN_DEV
const T_CHAR *getWanxMac(int index) {return NULL;}
const T_CHAR *getWanxSubnet(int index) {return NULL;}
const T_CHAR *getWanxGateway(int index) {return NULL;}
const T_CHAR *getWanxIP(int index) {return NULL;}
const T_CHAR *getWanxMask(int index) {return NULL;}
const T_CHAR *getWanxDev(int index) {return NULL;}
const T_CHAR *getWanxPhyDev(int index) {return NULL;}
const int   getWanxConnType(int index) {return 0;}
const T_CHAR *getWanxDNS(int index) {return NULL;}
int getWanxConfig(struct ethInfo *pdata, int index) {return 0;}
int getWanxConfigByDev(struct ethInfo *pdata, char *pname) {return 0;}
void getWanAllConfig(struct wanInfo *pdata) {}
int getWanxEnable(int index) {return 0;}
int getWanxFakeStatus(int index) {return 0;}
#endif

#if SUPPORT_IPV6
#if HAS_WAN_DEV
const T_CHAR *getWanv6Dev(T_VOID) {return NULL;}
const T_CHAR *getWanv6IP(T_VOID) {return NULL;}
const T_CHAR *getWanv6Gateway(T_VOID) {return NULL;}
const T_CHAR *getWanv6DNS(int index) {return NULL;}
#endif
const T_CHAR *getLanv6IP(T_VOID) {return NULL;}
const T_CHAR *getLanv6IPWithoutPrefix(T_VOID) {return NULL;}
const T_CHAR *getLanv6IPPrefix(T_VOID) {return NULL;}
#endif

/* natServ.h */
T_BOOL natVServerLoadDefault(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL natVServerDoCheck(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL getNatVServer(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setNatVServer(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defNatServValue(ap_cfg_item_t* item) {return FALSE;}
#if HAS_ADV_NAT
T_BOOL advNatVServerLoadDefault(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL advNatVServerDoCheck(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL getAdvNatVServer(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setAdvNatVServer(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defAdvNatServValue(ap_cfg_item_t* item) {return FALSE;}
T_BOOL advNatVServerExtLoadDefault(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL advNatVServerExtDoCheck(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL getAdvNatVServerExt(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setAdvNatVServerExt(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defAdvNatServExtValue(ap_cfg_item_t* item) {return FALSE;}
#endif

/* qosinfo.h */
T_BOOL portQosALoadDefault(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL getPortQosA(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setPortQosA(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defPortQosAValue(ap_cfg_item_t* item) {return FALSE;}

T_BOOL portQosBLoadDefault(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL getPortQosB(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setPortQosB(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defPortQosBValue(ap_cfg_item_t* item) {return FALSE;}

#if HAS_QOS_HWPORT
T_BOOL getQosHwPort(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setQosHwPort(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defQosHwPortValue(ap_cfg_item_t* item) {return FALSE;}
#endif /* HAS_QOS_HWPORT */

#if HAS_SUPPORT_UBICOM_STREAMENGINE
T_BOOL getStreamEngineQos(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setStreamEngineQos(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defStreamEngineQos(ap_cfg_item_t* item) {return FALSE;}
#endif

/* routingInfo.h */
T_BOOL staticRoutingLoadDefault(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL staticRoutingDoCheck(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL getStaticRoutingValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setStaticRoutingValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defStaticRouting(ap_cfg_item_t* item) {return FALSE;}

#ifdef HAS_PPPOE_JAPAN
T_BOOL DualWanRoutingLoadDefault(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL DualWanRoutingDoCheck(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL getDualWanRoutingValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setDualWanRoutingValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defDualWanRouting(ap_cfg_item_t* item) {return FALSE;}
#endif // HAS_PPPOE_JAPAN

#if HAS_DOMAIN_ROUTING
T_BOOL DomainRoutingLoadDefault(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL DomainRoutingDoCheck(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL getDomainRoutingValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setDomainRoutingValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defDomainRouting(ap_cfg_item_t* item) {return FALSE;}
#endif // HAS_DOMAIN_ROUTING

/* schedule.h */
T_BOOL scheduleLoadDefault(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL scheduleDoCheck(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL getSchValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setSchValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defSchValue(ap_cfg_item_t* item) {return FALSE;}
T_BOOL scheduleBLoadDefault(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL scheduleBDoCheck(T_VOID* dst,T_INT32 index) {return FALSE;}
T_BOOL getSchBValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setSchBValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defSchBValue(ap_cfg_item_t* item) {return FALSE;}
T_UINT32 shiftDaysMask(T_UINT32 mask, int flag) {return 0;}
const T_CHAR *dtToStr(schedule_t dt) {return NULL;}
const T_CHAR *scheduleGetDescription(schedule_t dt) {return NULL;}
T_VOID schDoDelete(T_INT32 index) {}

/* specApp.h */
T_BOOL getSpecAppValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setSpecAppValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defSpecAppValue(ap_cfg_item_t* item) {return FALSE;}
T_BOOL specAppPortStringToList(const char* str, SpecAppSetting *app) {return FALSE;}
T_BOOL specAppPortListToString(SpecAppSetting app, char* str, int len) {return FALSE;}
T_BOOL specAppLoadDefault(T_VOID* dst, T_INT32 index) {return FALSE;}

/* system.h */
T_UINT32 Ipstr2int(const T_CHAR *ipstr) {return 0;}
T_CHAR* Ipint2str(const T_UINT32 ip) {return NULL;}
#if SUPPORT_IPV6
T_BOOL Ipv6str2int(const T_CHAR *ipstr, T_UINT8 *dst) {return FALSE;}
T_CHAR* Ipv6int2str(const T_UINT8 *dst) {return NULL;}
#endif
T_BOOL checkRemoteIp(const T_IPADDR remoteip) {return FALSE;}
const T_CHAR *apcfgGetFwmStatusInText(T_INT32 ifwupgResult) {return NULL;}
T_BOOL apCfgCheckFwNotify(T_VOID) {return FALSE;}

/* systeminfo.h */
T_BOOL getSysInfoValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst) {return FALSE;}
T_BOOL setSysInfoValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst) {return FALSE;}
T_BOOL defSysInfoValue(ap_cfg_item_t* item) {return FALSE;}

void setSysOperationModeInfo(T_INT32 sysmode) {}

#if HAS_RADIO_SETTING
T_INT32  Radio2SysOpmode(T_VOID) {return 0;}
T_VOID	setMultipleRadioSysOperationMode(T_VOID) {}
#endif

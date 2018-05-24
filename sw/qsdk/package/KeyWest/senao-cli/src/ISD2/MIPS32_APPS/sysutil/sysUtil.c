#include <sysUtil.h>
#define WIFI_MAC_FILE = "/tmp/macaddress.tmp"
/* xsemaph.h */
int x_sem_create(key_t	key, int	initval) {return 0;}
int x_sem_open(key_t	key) {return 0;}
int x_sem_rm(int	id) {return 0;}
int x_sem_close(int	id) {return 0;}
int x_sem_wait(int	id) {return 0;}
int x_sem_signal(int	id) {return 0;}
int x_sem_op(int	id,int	value) {return 0;}

/* sysSem.h */
T_INT32 SEM_CREATE(const T_CHAR  *pSemName) {return 0;}
T_INT32 SEM_DELETE(const T_INT32 semid) {return 0;}
T_INT32 SEM_GETID(const T_CHAR *pSemName) {return 0;}
T_INT32 __SEM_LOCK(const T_INT32 semid) {return 0;}
T_INT32 __SEM_UNLOCK(const T_INT32 semid) {return 0;}

/* sysShm.h */
T_INT32 SHM_CREATE(key_t key, T_INT32 size, T_BOOL *isInitialized ) {return 0;}
T_VOID *SHM_GET(T_INT32 shmId) {return NULL;}
T_INT32 SHM_DETACH(T_VOID *ptr) {return 0;}
T_INT32 SHM_DELETE(T_INT32 shmId) {return 0;}

/* sysUtilMisc.h */
T_INT32 sysGenKeyFromString(const T_CHAR *pString) {return 0;}
T_INT32 CHKSUM(T_CHAR *pBuf, T_INT32 len) {return 0;}
int generateAuthPassWords(T_CHAR *macAddr, T_CHAR *outputPassword) {return 0;}
T_VOID generateRandomSeek(const T_CHAR* interface) {}
char* generateRandomAscii(char* var, int len) {return NULL;}
char* generateRandomHexNum(char* var, int len) {return NULL;}
char* getHwVer() {return NULL;}
char* getSerNum() {return NULL;}
int portRangeStringToList(const char* str, unsigned short *portList, int listMax) {return 0;}
int portRangeListToString(unsigned short *portList, int listMax, char* str, int len) {return 0;}
T_BOOL lecho(T_CHAR *pText, T_CHAR *fName) {return FALSE;}
T_CHAR *sysDotted2Number(T_CHAR *maskStr) {return NULL;}
T_BOOL checkSameSubnet(T_IPADDR scrIpAddr,T_IPADDR desIpAddr,T_IPADDR mask) {return FALSE;}
int getFirmwareHeaderCheck(char *filename) {return 0;}
int getFirmwareHeaderCheckEx(char *filename, unsigned int magickey) {return 0;}
void sysCheckStringOnWeb(const char *srcStr, char *destStr) {}
void sysCheckStringForRepeater(const char *srcStr, char *destStr) {}
int sysconf_util_cmd(char* cmdStr, char* replyStr) {return 0;}
int sysCharToInt(char c) {return 0;}
int sysIsValidMacAddr(T_CHAR *mac) {return 0;}
char* sysHex2Ascii(T_CHAR *hexStr) {return NULL;}
char* sysAscii2Hex(T_CHAR *asciiStr) {return NULL;}
char* sysStrToupper(char *str) {return NULL;}
char* sysStrTolower(char *str) {return NULL;}
#if SUPPORT_IPV6
char* sysGetpeername(int sock) {return NULL;}
#endif
#if SUPPORT_HW_DSCP
void sysEnableHwDscp() {}
void sysDisableHwDscp() {}
#endif

/* sysCommon.h */
T_VOID TRACE(T_INT32 level, T_CHAR *fmt, ...) {}

/* systime.h */
int sysGettimeofday(struct timeval *tv, struct timezone *tz) {return 0;}
T_CHAR* getSystemUpTimeText(T_VOID) {return NULL;}

T_BOOL sysGetLocalSystime(systime_t *systime) {return FALSE;}

int systimeIsLeapYear(int y) {return 0;}
int systimeGetDaysInMonth(int year, int mon) {return 0;}
const char* systimeStringGet(time_t t, const char *fmt, char *dest, size_t len) {return NULL;}

const char* systimeGetLocalTime(void) {return NULL;}
void systimeSetDate(int year, int month, int day) {}
void systimeSetTime(int hour, int minute) {}
#if HAS_HW_RTC
void syncTimeToRTC() {}
#endif
T_BOOL sysTimeZoneSet(int id, int isDayLightSaving) {return FALSE;}
T_BOOL sysGetTimeZoneName(int id, T_CHAR* timezone) {return FALSE;}
int sysComputeDaysInMonth(int year, int month, int weeksInMonth, int daysInWeek) {return 0;}
time_t sysTimeGetWithTimeZone(time_t t, int id, int isDayLightSaving) {return 0;}
time_t sysTimeGetWithSimpleDaylightSaving(time_t t, int isDayLightSaving, int sm, int sd, int sh, int em, int ed, int eh) {return 0;}
time_t sysTimeGetWithStandardDaylightSaving(time_t t, int isDayLightSaving,
										  int sm, int sd, int sw, int sh, 
										  int em, int ed, int ew, int eh) {return 0;}
int sysGetDbiasWithDaylightSaving(time_t t, int id, int isDayLightSaving) {return 0;}
int sysGetBiasWithTimeZone(int id) {return 0;}
time_t sysTimeGetWithTimeZoneFromFile(time_t t) {return 0;}
int sysGetSecondsLocaltimeToUTC(time_t t, int hr, int mm, int id, int isDayLightSaving) {return 0;}
T_CHAR* transferTimeFormat(int second,TIMEFORMAT_TYPE timeFormat) {return NULL;}
int schCalNextAvailableUpdateTime(int nextWday,int nextHour, int nextMin, int nextSec) {return 0;}
struct timeval *sysTvsub(struct timeval *tv1, struct timeval *tv2) {return NULL;}

/* syscore.h */
#if SYSUTIL_HAS_NO_SUPPORT_KERNEL_MODULES
#else
T_BOOL MODPROBE(const T_CHAR *inMod) {return FALSE;}
T_BOOL INSMOD(const T_CHAR *inMod) {return FALSE;}
T_BOOL RMMOD(const T_CHAR *modName) {return FALSE;}
T_BOOL FindKernModule(const T_CHAR *inMod) {return FALSE;}
#endif
T_INT32 SYSTEM(T_CHAR *format, ...) {return 0;}
T_VOID setSYSTEMFp(FILE *fp) {}
FILE *getSYSTEMFp(T_VOID) {return NULL;}
T_INT32 SYSTEM_DBG(T_INT32 onOff) {return 0;}
T_VOID SYSTEM_DEEP_DBG(T_VOID) {}
T_INT32 sysinteract(T_CHAR *output, T_INT32 outputlen, T_CHAR *fmt, ...) {return 0;}
#if SYSUTIL_HAS_NO_TPRINTF
#else
T_INT32 T_PRINTF(T_CHAR *format, ...) {return 0;}
#endif
T_INT32 SystemLog(int loglevel, T_CHAR *format, ...) {return 0;}
T_INT32 SnmpLog(T_CHAR *format, ...) {return 0;}

/*sysIf.h*/
int sysIPIsReady(const T_CHAR *interface) {return 0;}
int sysGetIfIndex(const T_CHAR *interface) {return 0;}
int sysGetIfStatus(const T_CHAR *interface) {return 0;}
T_BOOL sysIfGetHwAddr(const T_CHAR *interface, T_CHAR hwaddr[]) {return FALSE;}
const char *sysIfGetIP(const T_CHAR *interface) {return NULL;}
const char *sysIfGetDstIP(const T_CHAR *interface) {return NULL;}
const char *sysIfGetMask(const T_CHAR *interface) {return NULL;}
const char *sysIfGetSubnet(const T_CHAR *interface) {return NULL;}
const char *sysIfGetGateway(const T_CHAR *gatewayInterface) {return NULL;}
const char *sysIfGetDefaultGateway() {return NULL;}
const char *sysIfDns() {return NULL;}
const char *sysMultiIfGetDns(int index, char *iface) {return NULL;}
const char *sysIfv6Dns(int index) {return NULL;}
T_BOOL isIfExisted(const T_CHAR *interface) {return FALSE;}
T_VOID sysIfSetHostName(T_CHAR *hostname) {}
unsigned long sysIfGetPacketsInfo(const T_CHAR *interface, int method) {return 0;}
T_BOOL sysIfGetDevStats(const T_CHAR *interface,
                        struct user_net_device_stats *stats) {return FALSE;}
T_BOOL sysDelVlanIf(T_CHAR *prefix) {return FALSE;}
T_BOOL sysCheckValidIp(T_IPADDR sevIp,T_IPADDR lanIp,T_IPADDR maskIp) {return FALSE;}
int sysIfGetPhyId(const T_CHAR *interface) {return 0;}
int sysIfGetMTU(const T_CHAR *interface) {return 0;}

/* sysArp.h */
T_CHAR* sysArpGetIfNameByIP(T_CHAR* ipstr) {return NULL;}
T_CHAR* sysArpGetMacByIP(T_CHAR* ipstr) {return NULL;}
T_CHAR* sysArpGetMacByIP2(T_CHAR* ipstr) {return NULL;}
T_CHAR* sysArpGetIpByMac(T_CHAR* macstr) {return NULL;}
T_INT arpping(T_UINT32 yiaddr, T_UINT32 ip, T_UINT8 *mac, T_CHAR *interface) {return 0;}

/* sysMii.h */
T_BOOL sysMiiCheckLink(const T_CHAR *ifname, T_INT *result, int isForce) {return FALSE;}
T_BOOL sysMiiGetLinkPartnerSpeed(const T_CHAR *ifname, T_UINT32 *speed) {return FALSE;}
T_BOOL sysMiiCheckLinkEx(const T_CHAR *ifname, T_INT *status, int isForce, int phy_id) {return FALSE;}
T_BOOL sysMiiGetLinkPartnerSpeedEx(const T_CHAR *ifname, T_UINT32 *speed, int phy_id) {return FALSE;}
T_BOOL sysSetMiiPower(T_UINT32 port , T_UINT32 up) {return FALSE;}
T_BOOL sysMiiSetPortLinkSpeed(const T_CHAR *ifname, T_UINT32 linkspeed, int port) {return FALSE;}

/* sysFile.h */
T_BOOL sysIsFileExisted(const T_CHAR *filename) {return FALSE;}
T_BOOL sysIsProcPidExisted(const T_CHAR *filename) {return FALSE;}
T_UINT32 sysGetFileSize(const T_CHAR *filename) {return 0;}
T_UINT32 sysGetFileChkSum(const T_CHAR *filename) {return 0;}
T_INT32 getNumOfRecord(const T_CHAR *File,int stripLine) {return 0;}
#if HAS_PBX
T_CHAR *getFlashInfo(T_CHAR *filePath, enum flashInfo type, T_CHAR *outputStr) {return NULL;}
T_INT32 sysGetTextFileNofLine(const T_CHAR *filename) {return 0;}
T_INT32 sysTailFile(const T_CHAR *filename, T_INT32 reservedPercentage, T_INT32 inLine) {return 0;}
#endif
T_INT32 sysFileLock(const T_CHAR *filename, const T_CHAR *owner, T_INT32 waitCount) {return 0;}
T_INT32 sysFileUnLock(const T_CHAR *filename) {return 0;}
char * sysGetKernelInfo(int type) {return NULL;}

/* sysMsgq.h */
T_BOOL MSGQ_CREATE(const T_CHAR  *pName, T_INT32 *pId) {return FALSE;}
T_INT32 MSGQ_DELETE(const T_INT32 msgqId) {return 0;}
T_INT32 MSGQ_SEND(T_INT32 msgqId, void *pMsg, T_INT32 nBytes) {return 0;}
T_INT32 MSGQ_RECV(T_INT32 msgqId, void *pMsg, T_INT32 nBytes, T_BOOL isWait) {return 0;}
T_INT32 MSGQ_GETID(const T_CHAR  *pName) {return 0;}

/* sysproc.h */
T_BOOL KILLALL(const T_CHAR *proc) {return FALSE;}
T_BOOL TERMINATEPROC(const T_CHAR *proc) {return FALSE;}

#ifdef TEST_SURVEY
void FindProcInform(const T_CHAR *proc,STATUS_INFORM inform)  {}
#endif
T_INT32 FINDPROCID(const T_CHAR *proc) {return 0;}
T_INT32 FINDPROC(const T_CHAR *proc) {return 0;}
T_INT32 FINDCMDPROCID(const T_CHAR *proc) {return 0;}

/* sysHumanReadable.h */
const char *sysMakeHumanReadableStr(T_UINT64 val, T_UINT64 display_unit) {return NULL;}
const char *sysByteToTimeFormatStr(T_UINT32 availBytes) {return NULL;}
const char *sysByteToHumanReadableStr(T_UINT32 Bytes) {return NULL;}
int strMacStrToMacAddr(T_CHAR dst[6], const char *macStr) {return 0;}
int strMacAddrToMacStr(char macStr[18], const unsigned char bin[6]) {return 0;}
int sysStrToMacAddr(char macStr[18], const char* srcStr) {return 0;}
void miscHexDump(unsigned int offset, const unsigned char *data,int buf_siz) {}
T_CHAR* transferQuoteStringFormat(const T_CHAR* string) {return NULL;}
int replaceCharByString(const T_CHAR* stringSrc,const T_CHAR* beReplacedChar,const T_CHAR* replaceStr,T_CHAR* stringDest) {return 0;}
#ifdef COUNT_EACH_STA
const char *sysParsePktUnit(const unsigned long long int Bytes) {return NULL;}
#endif

/* sysWlan.h */
#if FOR_ATHEROS_PLATFORM || HAS_ATHEROS_WLAN_AR9K || (FOR_REALTEK_PLATFORM && REALTEK_5G_SUPPORT)
int channelTo5G11nHTtype(int channel) {return 0;}
#endif

int sysWlanGetClientList(WLANClientListInfo *clientList, size_t size) {return 0;}

int sysWlanGetSiteSurveyResult(ApInfo apinfo[], size_t infoArraySize) {return 0;}
int getRssiValue(char* interface) {return 0;}
int sysWlanGenWpsPinCodeByMac(T_CHAR* macAddr) {return 0;}
int sysWlanGenWpsPinCodeByLANMac() {return 0;}
void sysWlanDisconnect() {}
char* sysWlanGetSsid() {return NULL;}
char* sysWlanGetState() {return NULL;}
char* sysWlanGetBssid() {return NULL;}
char* sysWlanGetCipher() {return NULL;}
char* sysWlanGetKeyMgmt() {return NULL;}
rssiLevel wlanRssiConvert2Level(int rssi) {return MAX_RSSI_LEVEL;}
char* sysWlanGetPassphrase(const T_CHAR *ssid,const T_CHAR *psk) {return NULL;}
void sysCheckWEPKeyForIwconfig(const char *srcStr, char *destStr) {}
int checkBGNValidChannel(int regularDomain, int channel) {return 0;}
int parseApInfo(ApInfo *apData, const char *buf) {return 0;}
T_BOOL  sysGetWlanStatus(T_CHAR *dev_name, sysWlanStatus_t *stat) {return FALSE;}
int sysWlanParseEncType(const T_CHAR *encStr) {return 0;}
int sysWlanParseAuthType(const T_CHAR *authStr) {return 0;}
#ifdef FOR_RALINK_PLATFORM
unsigned short sysGetRFConfig(unsigned int offset) {return 0;}
int sysIsApCliConnected(const char *interface,const char *ssid) {return 0;}
T_VOID sysReGenRalinkPinCode(const char *interface) {}
int sysWlanGetClinetNums(const char *interface) {return 0;}
int sysWlanGetRadioStatus(const char *interface) {return 0;}
unsigned int sysGetAPPincode(char *interface) {return 0;}
unsigned int sysGetAPPincodeFromFile(char *path) {return 0;}
T_BOOL sysCheckWlanClient(T_CHAR* mac) {return FALSE;}
T_VOID sysPrintWlanStatus(sysWlanStatus_t *stat) {}
#if GEN_ADMIN_PASSWORD_BY_MACADDR
char* new_generateADMINPWDbyMac(char* var, char* smac,int keylen) {return NULL;}
#endif
#ifdef HAS_EACH_SSID_CLINUM
int sysWlanGetClinetNumsByBssid(int idx) {return 0;}
int _sysWlanGetClinetNumsByBssid(int idx, char* ifName) {return 0;}
#endif
#endif
#if USE_WPA2PSK_AS_DEFAULT_SECURITY
char* generateWPA2PSKbyMac(char* var, char* mac,int keylen) {return NULL;}
char* new_generateWPA2PSKbyMac(char* var, char* smac,int keylen) {return NULL;}
char* __new_generateWPA2PSKbyMac(char* var, char* smac,int keylen,int flag) {return NULL;}
char* generateWPA2PSKbySN(char* var, char* sn,int keylen) {return NULL;}
#endif
char* generateWPA2PSKbyRandom(char* var,int keylen) {return NULL;}

#if HAS_TELEFONICA_3G_FUNCTION
int new_generateWPA2PSKbyZyxel(char *var, char* mac, int data_len) {return 0;}
#endif

#if defined (FOR_ATMEL902) || defined (FOR_RALINK_PLATFORM) || defined (FOR_ATHEROS_PLATFORM)
void sysWlanCheckSsidOnPassphrase(const char *srcSSid, char *detSSid) {}
#endif

/* sysCpu.h */
T_INT sysGetCpuMhz() {return 0;}

/* sysDevice.h */
T_CHAR *sysGetMountPoint(const T_CHAR *devName) {return NULL;}
T_INT32 sysGetRamdiskFreeSpace() {return 0;}
T_INT32 sysGetMountedFileSystemFreeSpace(T_CHAR *fsName) {return 0;}
T_INT32 sysGetMountedFileSystemTotalSpace(T_CHAR *fsName) {return 0;}
T_BOOL sysGetMtdNumByName(const T_CHAR *inMtdName, T_INT32 *iMtdNum, T_UINT32 *iMtdSize) {return FALSE;}
T_BOOL checkIsMounted(T_CHAR *mountName) {return FALSE;}
int getAppsMtd() {return 0;}
void setAppsMtd() {}
#if HAS_PBX
T_BOOL sysIsUSBMounted(T_VOID) {return FALSE;}
#endif
int isDevMounted(const char *devName) {return 0;}
unsigned short sysGetMtdData(int id, unsigned char *pdata, char *ptoken, unsigned int offset, int len) {return 0;}
unsigned char * sysGetUbootVersion(void) {return NULL;}
void *memstr(void *m, const char *s, size_t n) {return NULL;}

#if HAS_FW1_FW2
int setKeysMtd(int knl_flag) {return 0;}
#endif

/* sysProduct.h */
unsigned short sysGetProductIndex(void) {return 0;}
char * sysGetVendorName(void) {return NULL;}
char * sysGetVendorMode(void) {return NULL;}
char * sysGetModelName(void) {return NULL;}
char * sysGetDomainName(void) {return NULL;}
char * sysGetVendorLogo(void) {return NULL;}
char * sysGetBannerLogo(void) {return NULL;}
char * sysGetApWscManufacture(void) {return NULL;}
char * sysGetApWscModelName(void) {return NULL;}
char * sysGetApWscDeviceName(void) {return NULL;}
char * sysGetCliWscModelName(void) {return NULL;}
char * sysGetCliWscDeviceName(void) {return NULL;}
char * sysGetCliWscDeviceNameR(void) {return NULL;}
char * sysGetTitleBGColor(void) {return NULL;}
char * sysGetTitleFontColor(void) {return NULL;}
char * sysGetMenuBGColor(void) {return NULL;}
char * sysGetMenuFontColor(void) {return NULL;}
char * sysGetLabelBGColor(void) {return NULL;}
char * sysGetLabelFontColor(void) {return NULL;}
char * sysGetSubLabelBGColor(void) {return NULL;}
char * sysGetSubLabelFontColor(void) {return NULL;}
char * sysGetItemBGColor(void) {return NULL;}
char * sysGetItemFontColor(void) {return NULL;}
char * sysGetSelectionColor(void) {return NULL;}
char * sysGetSupportLangugae(int index) {return NULL;}
char * sysGetUPNPDFriendlyName(void) {return NULL;}
char * sysGetUPNPDManufacture(void) {return NULL;}
char * sysGetUPNPDManufactureUrl(void) {return NULL;}
char * sysGetUPNPDModelDesc(void) {return NULL;}
char * sysGetUPNPDModelName(void) {return NULL;}
char * sysGetUPNPDModelNum(void) {return NULL;}
char * sysGetUPNPDModelUrl(void) {return NULL;}
char * sysGetBoardHardwareID(void) {return NULL;}
unsigned int sysGetFWUGVendorID(void) {return 0;}
unsigned int sysGetFWUGProductID(void) {return 0;}
char * sysGetFWVersion(void) {return NULL;}
char * sysGetFWBuildDate(void) {return NULL;}
char * sysGetModuleName(void) {return NULL;}
T_BOOL sysCheckFWNofity(void) {return FALSE;}
char * sysGetWebTitleName(void) {return NULL;}

/* sysTick.h */
#if defined(_WIN32) || defined(WIN32)
#elif defined(__linux__) || defined(__uClinux__) || defined(Linux)
unsigned long sysTickGet(void) {return 0;}
unsigned long sysFastTickGet(void) {return 0;}
#elif defined(VxWorks)
#endif

void sysSleep(int dwMilliseconds) {}

/* sysWan.h */
const char *sysGetPPPoEStatus(const T_CHAR *pidFile, const T_CHAR *interface) {return NULL;}
int sysGetPppStatus(const T_CHAR *pidFile, const T_CHAR *interface) {return 0;}
T_INT32 sysWanDetection() {return 0;}
void sysDhcpEnable(int enable) {}

#if HAS_WAN_3G
int sysWan3gStatus(void) {return 0;}
int sysWan3gSignal2(void) {return 0;}
int sysWan3gSignal(void) {return 0;}
int sysWan3gPinStatus(void) {return 0;}
#if !HAS_WAN_HIFULL_3G
int sysWan3gRssiToDbm(void) {return 0;}
const char *sysWan3gPinErrStr(int status) {return NULL;}
int sysWan3gSpeed(void) {return 0;}
int sysWan3gCardDesc(T_CHAR *) {return 0;}
int sysWan3gNetReg(void) {return 0;}
#if HAS_KCODES_NETUSB
int sysWanUsb3gMode(void) {return 0;}
#endif /* HAS_KCODES_NETUSB */
#endif /* HAS_WAN_HIFULL_3G */
#endif /* HAS_WAN_3G */

#if HAS_WAN_WIMAX
int sysWanWimaxStatus(int index, int *signal, int *status) {return 0;}
#endif
#ifdef SUPPORT_WAN_SPEED_TEST
int sysWanSpeedTest(void) {return 0;}
int sysWanUplinkSpeed(void) {return 0;}
#endif

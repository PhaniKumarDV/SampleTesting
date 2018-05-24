#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

/*-------------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                             */
/*-------------------------------------------------------------------------*/

#include <sap_ostypes.h>
#include <apcfg.h>
#if HAS_SYSTEM_SCHEDULE_FUNCTION

/*-------------------------------------------------------------------------*/
/*                           DEFINITIONS                                   */
/*-------------------------------------------------------------------------*/

#define SCHEDULE_DAY_MASK_SIZE 7 // a week

/*-------------------------------------------------------------------------*/
/*                           enum & struct                                 */
/*-------------------------------------------------------------------------*/
enum {
        BEFORE_A_DAY,
        AFTER_A_DAY
};

typedef struct _ScheduleDayMaskEntry
{
	T_UINT32 mask;
	T_CHAR dstr[10];
}ScheduleDayMaskEntry;


/*kungjay 20060704 schedule*/
typedef struct _schedule
{
    T_UINT8    isEnable __ATTRIBUTE_PACKED__;
    T_UINT8    isActive __ATTRIBUTE_PACKED__;
    T_CHAR     cSchDes[MAX_SCHED_DES+1] __ATTRIBUTE_PACKED__;
    T_UINT8    uId      __ATTRIBUTE_PACKED__;
    T_UINT8    bAlways  __ATTRIBUTE_PACKED__;    /* if TRUE, then we don't use the following variables*/
    T_UINT8    starthr  __ATTRIBUTE_PACKED__;    /* 0 ~23 */
    T_UINT8    startmm  __ATTRIBUTE_PACKED__;    /* 0 ~59*/
    T_UINT8    endhr    __ATTRIBUTE_PACKED__;    /* 0 ~23*/
    T_UINT8    endmm    __ATTRIBUTE_PACKED__;    /* 0 ~59*/
    T_UINT32   daysmask __ATTRIBUTE_PACKED__;    /* a HEX mask, the B0 -> Sunday, B1-> Satuarday, ..., B7->Monday */
    T_UINT32   type     __ATTRIBUTE_PACKED__;
//    T_UINT8     daysmask[7] __ATTRIBUTE_PACKED__;
}__S_ATTRIBUTE_PACKED__ schedule_t;

#if HAS_SCHEDULE_EXTEND
typedef struct _scheduleB
{
    T_UINT8    isEnable      __ATTRIBUTE_PACKED__;
    T_CHAR     cSchDes[10+1] __ATTRIBUTE_PACKED__;
    T_UINT8    starthr[8]    __ATTRIBUTE_PACKED__;    /* 0 ~23 */
    T_UINT8    startmm[8]    __ATTRIBUTE_PACKED__;    /* 0 ~59*/
    T_UINT8    endhr[8]      __ATTRIBUTE_PACKED__;    /* 0 ~23*/
    T_UINT8    endmm[8]      __ATTRIBUTE_PACKED__;    /* 0 ~59*/
    T_UINT8    dayValue      __ATTRIBUTE_PACKED__;    /* bitmap: on or off for each day. B0 -> Sunday's on/off, ..., B7 -> Monday's on/off */
    T_CHAR     padding[1]    __ATTRIBUTE_PACKED__;
	//T_UINT32   daysmask __ATTRIBUTE_PACKED__;    /* a HEX mask, the B0 -> Sunday, B1-> Satuarday, ..., B7->Monday */
}__S_ATTRIBUTE_PACKED__ scheduleB_t ;
#endif

#ifdef __cplusplus
extern "C" {
#endif

T_BOOL scheduleLoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL scheduleDoCheck(T_VOID* dst,T_INT32 index);
T_BOOL getSchValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setSchValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defSchValue(ap_cfg_item_t* item);
T_BOOL scheduleBLoadDefault(T_VOID* dst,T_INT32 index);
T_BOOL scheduleBDoCheck(T_VOID* dst,T_INT32 index);
T_BOOL getSchBValue(cfg_item_func_t* self, const ap_cfg_item_t* item, T_VOID* dst);
T_BOOL setSchBValue(cfg_item_func_t* self, ap_cfg_item_t* item, const T_VOID* dst);
T_BOOL defSchBValue(ap_cfg_item_t* item);
T_UINT32 shiftDaysMask(T_UINT32 mask, int flag);
const T_CHAR *dtToStr(schedule_t dt);
const T_CHAR *scheduleGetDescription(schedule_t dt);
T_VOID schDoDelete(T_INT32 index);

#ifdef __cplusplus
}
#endif

#endif

#endif

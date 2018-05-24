#ifndef _SENAO_AP_UTILS_H
#define _SENAO_AP_UTILS_H

#include "sap_osapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define T_MAX(a, b) ((a) > (b)) ? (a) : (b)
#define T_MIN(a, b) ((a) > (b)) ? (b) : (a)

#define T_NUM_OF_ELEMENTS(x) (sizeof(x)/sizeof(x[0]))

#ifdef DEBUG
#define DBG printf
#else
#define DBG
#endif

//#define KILLALL(x) SYSTEM("killall %s", (x)) cfho 2007-0207, move to sysutil


#ifndef WEXITSTATUS
# define WEXITSTATUS(stat_val) ((unsigned)(stat_val) >> 8)
#endif

#ifdef __cplusplus
}
#endif 

#endif

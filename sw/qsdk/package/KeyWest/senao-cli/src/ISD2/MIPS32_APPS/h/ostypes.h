#ifndef OSTYPES_H
#define OSTYPES_H

#ifdef DEBUG
#define dprintf(fmt, args...) printf(fmt, ## args)
#else
#define dprintf(fmt, args...)
#endif


#ifndef TRUE
#define TRUE (1)
#define FALSE (!TRUE)
#endif

#ifndef OK
#define OK 0
#define ERROR (-1)
#endif


#ifndef NULL
#define NULL 0
#endif

typedef int bool;
typedef int             BOOL;
typedef unsigned char   UINT8;
typedef unsigned short  UINT16;
typedef unsigned int    UINT32;
typedef signed char     INT8;
typedef signed short    INT16;
typedef signed int      INT32;
typedef unsigned int    UINT;
typedef signed int      INT;
typedef unsigned long   ULONG;


typedef void (*CMD_HANDLER)(int argc, char **argv);//cfho 03-0220

#include "knlintf.h"

#endif

#ifndef __OS_API_H
#define __OS_API_H

#if defined(WIN32)
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <winsock2.h>

#elif defined(Linux)
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
#include <assert.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdarg.h>
#include <sys/errno.h>
#include <ctype.h>
//MAC ADDRESS include
#include <net/if.h> /* contains the struct ifreq definition */
#include <sys/ioctl.h>
#include <linux/if_ether.h> /* out of habit, I use a SOCK_PACKET socket*/
#include <sys/sysinfo.h>


#endif

#include "sap_utils.h"
 
#endif

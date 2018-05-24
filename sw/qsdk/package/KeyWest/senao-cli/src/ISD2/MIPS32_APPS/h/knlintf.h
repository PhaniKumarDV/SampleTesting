#ifndef _KNL_INTF_H
#define _KNL_INTF_H
#include <sys/types.h>

typedef int 		KNL_SEM_ID;
typedef long 	KNL_TICK;
typedef int     KNL_TASK_ID;
typedef int     KNL_MSGQ_ID;

#define KNL_SLEEP(s) usleep(s*10)
#define KNL_SEM_CREATE_AND_LOCK(a,b,c) do { KNL_SEM_CREATE((a), (b) (c)); KNL_SEM_LOCK((b)); } while (0)
int KNL_MSGQ_CREATE(char *name_P, KNL_MSGQ_ID *ppmsgQ_id, u_int32_t q_depth, u_int32_t max_msg_len);
int KNL_MSGQ_DELETE(KNL_MSGQ_ID  msgQ_id);
int KNL_MSGQ_SEND(KNL_MSGQ_ID msgQ_id, void *pMsg, u_int32_t nBytes, u_int8_t wait);
int KNL_MSGQ_RECV(KNL_MSGQ_ID msgQ_id, void *pMsg, u_int32_t nBytes, u_int8_t wait);
int KNL_SEM_CREATE(char *name_P, KNL_SEM_ID *ppsem_id, int type);
int KNL_SEM_DELETE(KNL_SEM_ID  sem_id);
int KNL_SEM_LOCK(KNL_SEM_ID sem_id);
int KNL_SEM_UNLOCK(KNL_SEM_ID sem_id);
KNL_TICK KNL_TICKS(void);


#endif 

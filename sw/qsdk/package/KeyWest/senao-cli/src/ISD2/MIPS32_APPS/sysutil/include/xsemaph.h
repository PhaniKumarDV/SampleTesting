#include	<sys/types.h>
#include	<sys/ipc.h>
#include	<sys/sem.h>

#include	<errno.h> 
extern int	errno;




//functions
int x_sem_create(key_t	key, int	initval);
int x_sem_open(key_t	key);
int x_sem_rm(int	id);
int x_sem_close(int	id);
int x_sem_wait(int	id);
int x_sem_signal(int	id);
int x_sem_op(int	id,int	value);

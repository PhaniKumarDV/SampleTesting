#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <sys/ioctl.h> 
#include <sys/time.h>
#include <signal.h>
#include <linux/ioctl.h>

#define SIFY_DEV_NAME				"/dev/sifydrv"

// command for read the pps and dying gasp
#define SIFY_MAGIC					'k'
#define GET_NMEA_READ_PERIOD 		_IOR(SIFY_MAGIC,0,int)
#define GET_LOW_POWER_STATE 		_IOR(SIFY_MAGIC,1,int)
#define SET_LOW_POWER_TIMER_VAL 	_IOR(SIFY_MAGIC,2,int)

static volatile unsigned int nRunning = 1;
static volatile unsigned int nDgaspStatus = 0;

void SigKill_Handler(int dummy);
void DGasp_Handler(int dummy);
unsigned int nTimerValue = 0;

void SigKill_Handler(int dummy) 
{
    nRunning = 0;
	printf("catch signal kill/init \n");
}

int main(int argc, char **argv)
{		
	int nGpsFile = 0;
	
	signal(SIGINT, SigKill_Handler);
	signal(SIGKILL, SigKill_Handler);
	
	if(argc != 2)
	{
		printf("Invalid num. of parameters \n ");
		printf("you need to specify the timer value (to verify the dying gasp survive time) \n");
		printf("example: dgaspinfo 20 --> set the timer to 20 ms \n");
		printf("you can set timer value to zero to turn off timer \n");
		exit(1);
	}
	
	if(argv[1] != "")
	{
		nTimerValue = atoi(argv[1]);
		printf("Timer value = %d \n",nTimerValue);
	}	
	
	if ((nGpsFile = open(SIFY_DEV_NAME, O_RDWR)) < 0) {
		printf("Failed to open the sifydrv dev \n");
		exit(1);
	}

	if (ioctl(nGpsFile,SET_LOW_POWER_TIMER_VAL,&nTimerValue) < 0) {
			printf("Failed to set low power timer value \n");
			exit(1);
	}	
	
	do{
		if (ioctl(nGpsFile,GET_LOW_POWER_STATE,&nDgaspStatus) < 0) {
			printf("Failed to get low power state \n");
			exit(1);
		}
		
		
		if(nDgaspStatus == 1)			
		{
			//If dying gasp IRQ received, use FTP to verify 5G transmission to connected device
			system("tftp -p 192.168.1.206 -l output.bin");
			break;
		}
	}while(nRunning);
	
	close(nGpsFile);
		
	return 0;
}


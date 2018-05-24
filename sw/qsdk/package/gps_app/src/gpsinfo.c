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

#define DEVFILE "/dev/gpsdrv"

#define SHOW_WAIT_TIME			0

#define I2C_SLAVE				0x0703
#define I2C_DEV_NAME			"/dev/i2c-0"
#define SIFY_DEV_NAME			"/dev/sifydrv"
#define GPSS_I2C_ADDR			0x10
#define NMEA_BUF_SIZE			2048

// command register for gps by using i2c
#define RTK_I2C_STROBE_REG 		0x08ff1100
#define RTK_I2C_STROBE_DFT 		0x08000
#define RTK_I2C_STROBE_BIN 		0x04000
#define RTK_NMEA_INFO			0x10c01100
#define RTK_NMEA_CONTENT_ADDR	0x0011C014

// command for read the pps and dying gasp
#define SIFY_MAGIC					'k'
#define GET_NMEA_READ_PERIOD 		_IOR(SIFY_MAGIC,0,int)
#define GET_LOW_POWER_STATE 		_IOR(SIFY_MAGIC,1,int)
#define SET_LOW_POWER_TIMER_VAL 	_IOR(SIFY_MAGIC,2,int)

static volatile unsigned int nRunning = 1;

int i2c_strobe(int nFile);
int Read_NMEA_Packet_Len(int file);
int Read_NMEA_String(int nFile,unsigned char * NMEABuf,unsigned int nLength);
void SigKill_Handler(int dummy);

void SigKill_Handler(int dummy) 
{
    nRunning = 0;
	printf("catch signal kill/init \n");
}

int i2c_strobe(int nFile)
{	
	unsigned int nReg = RTK_I2C_STROBE_REG;
	unsigned short nStrobeChoice = RTK_I2C_STROBE_DFT;
	unsigned char cBuf[6] = {0};
	unsigned char cBuf1[6] = {0};
	int nRet = 0;
	unsigned short nReadStatus = RTK_I2C_STROBE_DFT;
	unsigned int nCount = 0;
	
#if SHOW_WAIT_TIME
	unsigned int nDiffTime = 0;
	unsigned int nDiffTimeus = 0;
	
	struct timeval tv;
	struct timeval tv1;
#endif

	//for nmea packet, latch bit 15
	nStrobeChoice = RTK_I2C_STROBE_DFT;
	
	cBuf[0] = (unsigned char)(nReg & 0xFF);
	cBuf[1] = (unsigned char)((nReg >> 8) & 0xFF);
	cBuf[2] = (unsigned char)((nReg >> 16) & 0xFF);
	cBuf[3] = (unsigned char)((nReg >> 24) & 0xFF);
	cBuf[4] = (unsigned char)(nStrobeChoice & 0xFF);
	cBuf[5] = (unsigned char)((nStrobeChoice >> 8) & 0xFF);
	
	printf("Send strobe request \n");
	
	// do the i2c strobe
	nRet = write(nFile, cBuf, 6);
	
	if (nRet < 0)
	{
		printf("I2C write fail: reg = 0x%X, data = 0x%X\n", nReg, cBuf[0]);
		return nRet;
	}	
#if SHOW_WAIT_TIME
	gettimeofday(&tv,NULL);
#endif
	
	do{
		// filter out the first 4 bytes first
		nRet = read(nFile, cBuf1, 4);
		
		if (nRet < 0)
		{
			printf("I2C read fail: reg = 0x%X, data = 0x%X\n", nReg, cBuf[0]);
			return nRet;
		}
        
		// read the strobe result
		nRet = read(nFile, (char *)&nReadStatus, 2);
		
		if (nRet < 0)
		{
			printf("I2C read fail: reg = 0x%X, i2c_strobe status = 0x%X\n", nReg, nStrobeChoice);
			return nRet;
		} 
		nCount++;
		//printf("i2c_strobe status = 0x%x \n",nReadStatus);
		// the latch bit must be clear if the data is ready
		
		if(nCount > 100)
		{
			nCount = 0;
			write(nFile, cBuf, 6);
			printf("send strobe again \n");
		}
	}while((nReadStatus & nStrobeChoice) != 0 && nRunning);
	printf("out of loop, strobe status =0x%X \n", nReadStatus );
#if SHOW_WAIT_TIME
	gettimeofday(&tv1,NULL);	
	nDiffTime = (unsigned int)(tv1.tv_sec-tv.tv_sec);
	nDiffTimeus = (unsigned int)(tv1.tv_usec-tv.tv_usec);
	
	printf("time spent to wait = %u s \n",nDiffTime);
	printf("time spent to wait = %u us \n",nDiffTimeus);
#endif
	
	return 0;
}

int Read_NMEA_Packet_Len(int nFile)
{
	unsigned char cBuf[4] = {0};
	unsigned int nReg = RTK_NMEA_INFO;// bigendian of 0x0011C010;
	int nRet = 0;
	unsigned int nNMEALen = 0;
	
	printf("%s \n",__func__);
	cBuf[0] = (unsigned char)(nReg & 0xFF);
	cBuf[1] = (unsigned char)((nReg >> 8) & 0xFF);
	cBuf[2] = (unsigned char)((nReg >> 16) & 0xFF);
	cBuf[3] = (unsigned char)((nReg >> 24) & 0xFF);
	
	// send request to read packet
	nRet = write(nFile, cBuf, 4);
	
	if (nRet < 0)
	{
		printf("I2C write fail: reg = 0x%X, data = 0x%X\n", nReg, cBuf[0]);
		return nRet;
	}
	
	// read the packet length, which is the first 4 bytes
	nRet = read(nFile, (char *)&nNMEALen, 4);
	
	if (nRet < 0)
	{
		printf("I2C read fail: reg = 0x%X, data = 0x%X\n", nReg, cBuf[0]);
		return nRet;
	}
	
	// check if the len is greater than buffer size
	if(NMEA_BUF_SIZE < nNMEALen)
		return 0;
	
	return nNMEALen;	
}


int Read_NMEA_String(int nFile,unsigned char * cNMEABuf,unsigned int nLength)
{
	unsigned int nReg = RTK_NMEA_CONTENT_ADDR;
	unsigned char cBuf[4] = {0};
	int nRet = 0;
	
	cBuf[3] = (unsigned char)(nReg & 0xFF);
	cBuf[2] = (unsigned char)((nReg >> 8) & 0xFF);
	cBuf[1] = (unsigned char)((nReg >> 16) & 0xFF);
	cBuf[0] = (unsigned char)((nReg >> 24) & 0xFF);

	nRet = write(nFile, cBuf, 4);
	if (nRet < 0)
	{
		printf("I2C send fail: opaddr_l = 0x%X, data = 0x%X\n", nReg, cBuf[0]);
		return nRet;
	}
	nRet = read(nFile, cNMEABuf, nLength);
	if (nRet < 0)
	{
		printf("I2C read fail: opaddr_l = 0x%X, data = 0x%X\n", nReg, cNMEABuf[0]);
		return nRet;
	}
	
	return 0;	
}

int main(int argc, char **argv)
{
	int nI2cFile = 0;
	int nGpsFile = 0;
	char cNMEAbuf[NMEA_BUF_SIZE]={0};
	unsigned int nNMEAlen = 0;
	unsigned int nReadTime = 0;
	unsigned int nPPS = 0;
	unsigned int pid = 0;
        unsigned int nPrevPPS = 0;
	
        if(argc != 2)
	{
		printf("you need to specify the pps read time period as parameter \n");
		printf("Example: gpsinfo 1 --> for 1 pps to read the gps data \n");
		exit(1);
	}

	signal(SIGINT, SigKill_Handler);
	signal(SIGKILL, SigKill_Handler);
	
	if ((nI2cFile = open(I2C_DEV_NAME, O_RDWR)) < 0) {
		/* ERROR HANDLING: you can check errno to see what went wrong */
		printf("Failed to open the i2c bus \n");
		exit(1);
	}
	
	// set the slave address, Realtek GNSS device fixed to 0x10
	if (ioctl(nI2cFile, I2C_SLAVE, GPSS_I2C_ADDR) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		exit(1);
	}
	
	if ((nGpsFile = open(SIFY_DEV_NAME, O_RDWR)) < 0) {
		/* ERROR HANDLING: you can check errno to see what went wrong */
		printf("Failed to open the i2c bus \n");
		exit(1);
	}

	if(argv[1] != "")
		nReadTime = atoi(argv[1]);
	else
		nReadTime = 1;
	printf("ReadTime = %d \n",nReadTime);
	
	
	if(nReadTime == 0)
	{
		printf("Read time value error, please check ===> %d \n",nReadTime);
                printf("Read time value must greater than zero\n");
		exit(1);
	}
        
	ioctl(nGpsFile,GET_NMEA_READ_PERIOD,&nPrevPPS);
      
	while(nRunning)
	{		
		ioctl(nGpsFile,GET_NMEA_READ_PERIOD,&nPPS);
		printf("nPPS = %d \n",nPPS);
		if((nPPS - nPrevPPS) >= nReadTime)
		{
                        nPrevPPS = nPPS;
			i2c_strobe(nI2cFile);		
			
			nNMEAlen = Read_NMEA_Packet_Len(nI2cFile);
				
			printf("NMEAlen = %d \n",nNMEAlen);
			
			if(nNMEAlen > 0)
			{
				Read_NMEA_String(nI2cFile,cNMEAbuf,nNMEAlen);
			}

			printf(" %s \n",cNMEAbuf);
		}
	}
	
	close(nI2cFile);	
	close(nGpsFile);
		
	return 0;
}


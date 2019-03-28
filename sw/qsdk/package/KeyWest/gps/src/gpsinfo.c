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
#include <uci.h>
#include <syslog.h>

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
	if (nRet < 0) {
		printf("I2C write fail: reg = 0x%X, data = 0x%X\n", nReg, cBuf[0]);
		return nRet;
	}	
#if SHOW_WAIT_TIME
	gettimeofday(&tv,NULL);
#endif
	do {
		// filter out the first 4 bytes first
		nRet = read(nFile, cBuf1, 4);
		if (nRet < 0) {
			printf("I2C read fail: reg = 0x%X, data = 0x%X\n", nReg, cBuf[0]);
			return nRet;
		}
		// read the strobe result
		nRet = read(nFile, (char *)&nReadStatus, 2);
		if (nRet < 0) {
			printf("I2C read fail: reg = 0x%X, i2c_strobe status = 0x%X\n", nReg, nStrobeChoice);
			return nRet;
		} 
		nCount++;
		//printf("i2c_strobe status = 0x%x \n",nReadStatus);
		// the latch bit must be clear if the data is ready
		if(nCount > 100) {
			nCount = 0;
			write(nFile, cBuf, 6);
			printf("send strobe again \n");
		}
	} while((nReadStatus & nStrobeChoice) != 0 && nRunning);
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
	if (nRet < 0) {
		printf("I2C write fail: reg = 0x%X, data = 0x%X\n", nReg, cBuf[0]);
		return nRet;
	}
	// read the packet length, which is the first 4 bytes
	nRet = read(nFile, (char *)&nNMEALen, 4);
	if (nRet < 0) {
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
	if (nRet < 0) {
		printf("I2C send fail: opaddr_l = 0x%X, data = 0x%X\n", nReg, cBuf[0]);
		return nRet;
	}
	nRet = read(nFile, cNMEABuf, nLength);
	if (nRet < 0) {
		printf("I2C read fail: opaddr_l = 0x%X, data = 0x%X\n", nReg, cNMEABuf[0]);
		return nRet;
	}
	return 0;	
}

#define REQ_GPS_PREFIX "$GPGGA,"
#define MAX_STR_LEN 256
#define REQ_GPS_PREFIX_LEN strlen(REQ_GPS_PREFIX)

enum {
    GGA_TYPE_TIME = 1,
    GGA_TYPE_LAT,
    GGA_TYPE_LNG,
    GGA_TYPE_VALIDITY,
    GGA_TYPE_NUM_SATS,
    GGA_TYPE_HORI_DILL_POS,
    GGA_TYPE_ALT,
    GGA_TYPE_GEOID,
    GGA_TYPE_END
};

typedef struct GPSData {
    char time[16];
    char lat[32];
    char lng[32];
    int sats;
    float alt;
} GPSData;


void UpdateUCI(cmd)
{
    struct uci_context *c;
    struct uci_ptr p;
    char opt[MAX_STR_LEN] = {0};
    
    c = uci_alloc_context();

    snprintf(opt, sizeof(opt), cmd);
    if(uci_lookup_ptr(c, &p, opt, true) != UCI_OK) {
        printf("UCI Error\n");
        return 0;
    }
    if(uci_set(c, &p) != UCI_OK) {
        printf("Failed in Set\n");
        return 0;
    }
    if(uci_save(c, p.p) != UCI_OK) {
        printf("Failed in Save\n");
        return 0;
    }
    if(uci_commit(c, &p.p, true) != UCI_OK) {
        printf("Failed in commit\n");
        return 0;
    }
    uci_free_context(c);
    return 1;
}

int ReadGPSInfo(char *da, int fLen) 
{
    int pos = 0;
    int isValid = 0;
    
    while(pos < fLen) {
        if(da[pos] != '$') { 
            pos++; 
            continue;
        }

        if(strncmp(REQ_GPS_PREFIX, &da[pos], REQ_GPS_PREFIX_LEN) == 0) {
            char *tok = NULL, *ptr;
            int type = 1;
            GPSData gps;

            ptr = &da[pos] + REQ_GPS_PREFIX_LEN ;
            tok = strtok(ptr, ",");

            while(tok != NULL || type == GGA_TYPE_END) {
                isValid = 1;
                printf("%s\n", tok);
                if(tok[0] == '*') break;

                switch(type) {
                    case GGA_TYPE_TIME:
                        snprintf(gps.time, 16, "%c%c:%c%c:%c%c", tok[0], tok[1], tok[2], tok[3], tok[4], tok[5]);
                        break;
                    case GGA_TYPE_LAT:
                        {
                            char temp[3]= {tok[0], tok[1], 0};
                            int v1 = atoi(temp);
                            float val;
                            tok+=2;
                            val = atof(tok)/60 + v1;
                            tok = strtok(NULL, ",");
                            if(tok == NULL || (tok[0] != 'N' && tok[0] != 'S')) {
		                            syslog(LOG_INFO, "Invalid Latitude.....\n");
                                gps.lat[0] = '\0';
                                isValid = 0;
                            } else {
                                snprintf(gps.lat, 32, "%f %c", val, tok[0]);
                            }
                            //                        printf("gps.lat: %s\n", gps.lat);
                        }
                        break;
                    case GGA_TYPE_LNG:
                        {
                            char temp[4]= {tok[0], tok[1], tok[2]};
                            int v1 = atoi(temp);
                            float val;
                            tok+=3;
                            val = atof(tok)/60 + v1;
                            tok = strtok(NULL, ",");
                            if(tok == NULL || (tok[0] != 'E' && tok[0] != 'W') ) {
		                            syslog(LOG_INFO, "Invalid Longitude.....\n");
                                gps.lat[0] = '\0';
                                isValid = 0;
                            } else {
                                snprintf(gps.lng, 32, "%f %c", val, tok[0]);
                            }
                            //                      printf("gps.lng: %s\n", gps.lng);
                        }
                        break;
                    case GGA_TYPE_VALIDITY: 
                        if(atoi(tok) == 0) {
                            isValid = 0;
                        }
                        break;
                    case GGA_TYPE_NUM_SATS: 
                        gps.sats = atoi(tok);
                        break;
                    case GGA_TYPE_HORI_DILL_POS: 
                        break;
                    case GGA_TYPE_ALT:
                        gps.alt = atof(tok);
                        gps.alt += 31.5;
                        tok = strtok(NULL, ",");
                        if(tok == NULL || tok[0] != 'M') {
                            printf("Invalid altitude...\n");
                            isValid = 0;
                        }
                        break;
                    case GGA_TYPE_GEOID:
                        {
                            float v = atof(tok);
                            if(v) {
                                gps.alt = gps.alt - v;
                                tok = strtok(NULL, ",");
                                if(tok == NULL || tok[0] != 'M') {
                                    printf("Invalid altitude...\n");
                                    isValid = 0;
                                }
                            }
                        }
                        break;
                    deafult: 
                        break;
                }
                if( !isValid ) break;
                type++;
                tok = strtok(NULL, ",");
            }
            if(isValid) {
                char cmd[128] = {0};
                printf("Latitude: %s\n", gps.lat);
                snprintf(cmd, 128, "system.gps.latitude=%s", gps.lat);
                UpdateUCI(cmd);

                printf("Longitude: %s\n", gps.lng);
                snprintf(cmd, 128, "system.gps.longitude=%s", gps.lng);
                UpdateUCI(cmd);

                printf("Altitude: %f\n", gps.alt);
                snprintf(cmd, 128, "system.gps.altitude=%f", gps.alt);
                UpdateUCI(cmd);

                printf("Satelites: %d\n", gps.sats);
                snprintf(cmd, 128, "system.gps.satelites=%d", gps.sats);
                UpdateUCI(cmd);

                printf("Time: %s\n", gps.time);
                snprintf(cmd, 128, "system.gps.time=%s", gps.time);
                UpdateUCI(cmd);
                system("sh /usr/sbin/rtc.sh");

                /* Update latitude and longitude to driver*/
                system("iwpriv wifi1 str_type 2");		
                snprintf(cmd, 128, "iwconfig ath1 nickname %s", gps.lng);
                system(cmd);

                system("iwpriv wifi1 str_type 3");		
                snprintf(cmd, 128, "iwconfig ath1 nickname %s", gps.lat);
                system(cmd);
            } 
            break;
        } else {
            pos += REQ_GPS_PREFIX_LEN;
        }
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
	int interval = 0;
    int ret = 0;

    if(argc != 2) {
        printf("Invalid arguments..");
        exit(1);
    }
    interval = atoi(argv[1]);
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
    do {
        nNMEAlen = 0;
	    if ( ioctl(nGpsFile,GET_NMEA_READ_PERIOD,&nPPS) < 0 ) {
            printf(": Unable to fetch PPS pulse Period.\n");
        }
        /* I2C - Give I2C Slave command to RTK I2C Master to read the NMEA data */
        ret = i2c_strobe(nI2cFile);		
        if ( ret == 0 ) {
            /* If Success, then read the NMEA Packet Length */
            nNMEAlen = Read_NMEA_Packet_Len(nI2cFile);
            if(nNMEAlen > 0) {
                /* If Success, then read the NMEA String */
                ret = Read_NMEA_String(nI2cFile,cNMEAbuf,nNMEAlen);
                if ( ret == 0 ) {
		                syslog(LOG_INFO, " #### NMEA LEN : %d ( str: %s ) #####\n",nNMEAlen, cNMEAbuf); 
                    /* If Success, then parse the NMEA String to get the GPS Information */
                    ret = ReadGPSInfo(cNMEAbuf, nNMEAlen);
                }
            }
        }
        if(((nNMEAlen == 0) || !interval)) { // instead of multiple checks, ok to have an extra 5 Sec sleep before exit, 
            sleep(5);
        } else {
            for(int i = 0; i < interval && nRunning ; i++)
                sleep(1);
        }
    } while( (interval || nNMEAlen == 0 ) && nRunning);
	close(nI2cFile);	
	close(nGpsFile);
	return 0;
}

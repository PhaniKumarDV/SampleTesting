#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include <uci.h>

#define LAST_RC_CMD "athstats -i wifi1|grep last|tr -d '\t'|cut -d':' -f 2"


#define LED1_PATH "/sys/devices/soc.0/gpio_led.6/leds/lan1/brightness"
#define LED2_PATH "/sys/devices/soc.0/gpio_led.6/leds/wlan5/brightness"
#define LED3_PATH "/sys/devices/soc.0/gpio_led.6/leds/ap_status/brightness"
#define LED4_PATH "/sys/devices/soc.0/gpio_led.6/leds/wlan24/brightness"

static unsigned int _MCS;
static int isRunning;
pthread_t valueWorker, ledWorker;
pthread_mutex_t lock;

void SigKill_Handler(int dummy)
{
    isRunning = 0;
    printf("Received Signal Int\n");
}

inline static void SetLED(char *LedPath, int state)
{
    char cmd[128] = {0};
    if(state == 0 || state == 1)
        snprintf(cmd, 128, "echo %d > %s", state, LedPath);
    system(cmd);
}

void *ValueWorkerThread(void *ptr) 
{
#define VALUE_UPDATE_TIME (5 * 1000 * 1000) // 5 Seconds
    FILE *ls = NULL; 
    char buf[8] = {0};
    unsigned char val = 0;
    unsigned char *t = NULL;
    unsigned int preamble, nss, mcs;

    while(isRunning) {
        ls = popen(LAST_RC_CMD, "r");
        if(!ls) {
            pthread_mutex_lock(&lock);
            _MCS = -1;
            pthread_mutex_unlock(&lock);
            goto end;
        }
        if(fgets(buf, sizeof(buf), ls) == NULL) {
            pthread_mutex_lock(&lock);
            _MCS = -1;
            pthread_mutex_unlock(&lock);
            goto end;
        }
        pclose(ls);

       val = atoi(buf);
//            val = 201;

       if(val > 0) {
           preamble = (val & 0xC0) >> 6 ;
           nss = (val & 0x30) >> 4;
           mcs = val & 0xF;
           printf("Preamble: %d\n", preamble);
           printf("NSS: %d\n", nss);
           printf("MCS/Rate: %d\n", mcs);

           pthread_mutex_lock(&lock);
           switch(preamble) {
               case 2: // HT Mode
               case 3: // VHT Mode
                   _MCS = mcs;
                   break;
               case 0: // OFDM
               case 1: // CCK
               default: // Invalid, consider no link
                   _MCS = -1;
                   break;
           }
           pthread_mutex_unlock(&lock);
           printf("ValueWorker MCS: %d\n", _MCS);
       } else {
            pthread_mutex_lock(&lock);
            _MCS = -1;
            pthread_mutex_unlock(&lock);
       }
end:
        usleep(VALUE_UPDATE_TIME);
    }
}

void *LedWorkerThread(void *ptr)
{
#define SLOW_BLINK_ON_USLEEP 1000000 // 300 MilliSeconds
#define SLOW_BLINK_OFF_USLEEP 1000000 // 400 MilliSeconds

#define FAST_BLINK_ON_USLEEP 150000 // 150 MilliSeconds
#define FAST_BLINK_OFF_USLEEP 150000 // 150 MilliSeconds

#define SOLID_ON_USLEEP 0 // No Sleep
#define SOLID_OFF_USLEEP 100000 // 100 MilliSeconds

    int onuSleep = 1000, offuSleep = 1000 ;
    char *LedPath = NULL;
    int mcs;

    while(isRunning) {
        pthread_mutex_lock(&lock);
        mcs = _MCS;
        pthread_mutex_unlock(&lock);
        if(mcs >= 0 && mcs < 10) { // Valid case
            switch(mcs) {
                case 0: // LED 2, Slow blink
                    LedPath = LED2_PATH;
                    onuSleep = SLOW_BLINK_ON_USLEEP;
                    offuSleep = SLOW_BLINK_OFF_USLEEP;
                    break;
                case 1: // LED 2, Fast blink
                    LedPath = LED2_PATH;
                    onuSleep = FAST_BLINK_ON_USLEEP; 
                    offuSleep = FAST_BLINK_OFF_USLEEP; 
                    break;
                case 2: // LED 2, Solid
                    LedPath = LED2_PATH;
                    onuSleep = SOLID_ON_USLEEP;
                    offuSleep = SOLID_OFF_USLEEP;
                    break;
                case 3: // LED 3, Slow blink
                    LedPath = LED3_PATH;
                    onuSleep = SLOW_BLINK_ON_USLEEP;
                    offuSleep = SLOW_BLINK_OFF_USLEEP;
                    break;
                case 4: // LED 3, Fast blink
                    LedPath = LED3_PATH;
                    onuSleep = FAST_BLINK_ON_USLEEP; 
                    offuSleep = FAST_BLINK_OFF_USLEEP; 
                    break;
                case 5: // LED 3, Solid
                    LedPath = LED3_PATH;
                    onuSleep = SOLID_ON_USLEEP;
                    offuSleep = SOLID_OFF_USLEEP;
                    break;
                case 6: // LED 4, Slow blink
                    LedPath = LED4_PATH;
                    onuSleep = SLOW_BLINK_ON_USLEEP;
                    offuSleep = SLOW_BLINK_OFF_USLEEP;
                    break;
                case 7: // LED 4, Fast blink
                    LedPath = LED4_PATH;
                    onuSleep = FAST_BLINK_ON_USLEEP; 
                    offuSleep = FAST_BLINK_OFF_USLEEP; 
                    break;
                case 8: // LED 4, Solid
                    LedPath = LED4_PATH;
                    onuSleep = SOLID_ON_USLEEP;
                    offuSleep = SOLID_OFF_USLEEP;
                    break;
                default: // LED 2,3,4, Solid
                    break;
            }
            if(mcs != 9) {
                SetLED(LedPath, 1);
                usleep(onuSleep);
                // Turn Off LED if not solid, onuSleep != 0
                if(onuSleep) {
                    SetLED(LedPath, 0);
                }
            } else if(mcs == 9) {
                SetLED(LED4_PATH, 1);
                SetLED(LED3_PATH, 1);
                SetLED(LED2_PATH, 1);
            }
        } else {
            // Off all LED's
            SetLED(LED4_PATH, 0);
            SetLED(LED3_PATH, 0);
            SetLED(LED2_PATH, 0);
            offuSleep = 1000;
        }
        usleep(offuSleep);
    }
}

int main(int argc, char **argv)
{
    
    signal(SIGINT, SigKill_Handler);
    signal(SIGKILL, SigKill_Handler);

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("Mutex init failed\n");
        exit(-1);
    }

    // Set all LEDs off
    SetLED(LED4_PATH, 0);
    SetLED(LED3_PATH, 0);
    SetLED(LED2_PATH, 0);

    _MCS = -1;
    isRunning = 1;
    if(pthread_create( &valueWorker, NULL, ValueWorkerThread, NULL)) {
        isRunning = 0;
        printf("Failed creating ValueWorker \n");
        exit(-1);
    } 

    if(pthread_create( &ledWorker, NULL, LedWorkerThread, NULL)) {
        isRunning = 0;
        printf("Failed creating LedWorker \n");
        exit(-1);
    }
    
    pthread_join( valueWorker, NULL);
    isRunning = 0;
    pthread_join( ledWorker, NULL);

    pthread_mutex_destroy(&lock);

    return 1;
}

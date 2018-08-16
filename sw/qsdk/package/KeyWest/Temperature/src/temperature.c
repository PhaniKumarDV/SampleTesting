#include <stdio.h>
#include <string.h>
#include <uci.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_STR_LEN 256
#define TEMP_LOG_FILE "/tmp/temp-log"

float Temperature() {
    //short v;
    //short swapV;
    int v1 = 0;
    //unsigned char *p = (unsigned char *)&swapV;
    FILE *fp;
    float finalValue;
    char val[10];
     
    fp = popen("cat /sys/class/hwmon/hwmon0/device/temp1_input", "r");
    while (fgets(val, sizeof(val), fp) != NULL) 
    {
        v1 = atoi(val);
    }
    pclose(fp);
/*
    v = (short)v1;
    *p = *((unsigned char *)&v + 1);
    *(p + 1) = *(unsigned char*)&v;

    swapV >>= 5;

    if (swapV & 0x0400) {
        swapV |= 0xf800;
        swapV = ~swapV + 1;
        finalValue = (float)swapV* (-1) * 0.125;

    } else {
        finalValue = (float)swapV*  0.125;
    }
*/
    finalValue = v1 / 1000;
    printf("Read Temp: %f\n", finalValue);
    return finalValue;
}
int UIC_SetTemperature(float v)
{
    struct uci_context *c;
    struct uci_ptr p;
    char opt[MAX_STR_LEN] = {0};
    
    c = uci_alloc_context();

    snprintf(opt, sizeof(opt), "system.@system[0].temperature=%.2f", v);
    if(uci_lookup_ptr(c, &p, opt, true) != UCI_OK) {
        printf("UCI Error\n");
        return 1;
    }
    if(uci_set(c, &p) != UCI_OK) {
        printf("Failed in Set\n");
        return 1;
    }
    if(uci_save(c, p.p) != UCI_OK) {
        printf("Failed in Save\n");
        return 1;
    }
    if(uci_commit(c, &p.p, true) != UCI_OK) {
        printf("Failed in commit\n");
        return 1;
    }
    
    uci_free_context(c);

    return 0;


}

int main(int argc, char **argv) {
    float temp = 0;
    int doLog = 0;
    char cmd[50];

    if(argc != 2) {
        printf("Invalid arguments..\n");
        exit(1);
    }

    doLog = atoi(argv[1]);
    if(doLog != 0 && doLog != 1 && doLog != 2) {
        printf("Invalid arguments..\n");
        exit(1);
    }

    temp = Temperature();
    UIC_SetTemperature(temp);

    if(doLog == 1) {
        FILE *fp;
        char str[MAX_STR_LEN] = {0};
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char timeStr[128] = {0};

        fp = fopen(TEMP_LOG_FILE, "a");
        if(!fp) {
            printf("Failed opening temp log file.");
            return -1;
        }
        strftime(timeStr, sizeof(timeStr)-1, "%d-%m-%Y-%H:%M", t);

        snprintf(str, MAX_STR_LEN, "%s - Temperature: %.2fC\n", timeStr, temp);
        fwrite(str, 1, strlen(str), fp);
        fclose(fp);
    }
    if(doLog == 2) {
	sprintf(cmd,"echo "" > %s",TEMP_LOG_FILE);
	system(cmd);    
    }

    return 1;
}

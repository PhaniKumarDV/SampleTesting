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

#define TXTFILE "/lib/examp_cmds.txt"

int main()
{
	FILE* fp;
	char buffer[255];
	char cmd[255];

	fp = fopen(TXTFILE, "r");

	while(fgets(buffer, 255, (FILE*) fp)) {
    		printf("%s", buffer);
		sprintf(cmd, "uci set %s", buffer);
		system(cmd);
	}

	system("reload_config");
	fclose(fp);
	return 0;
}


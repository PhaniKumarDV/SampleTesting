#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    while(1)
    {
        FILE *fp;
        char *tok, *p;
        short int len;
        char cmd[15], ip[20];
        char a[100];
        int i=0;

        memset(cmd,'\0',sizeof(cmd));
        memset(a,'\0',sizeof(a));
        memset(ip,'\0',sizeof(ip));
        sprintf(cmd,"ifconfig br-lan");

        fp = popen(cmd, "r");
        while (fgets(a, sizeof(a), fp) != NULL)
        {
            /*printf("%s\n", a);*/
            if( i == 1 )
                break;
            i++;
        }
        pclose(fp);
        
        p = strstr(a,"Bcast");

        if ( p == NULL )
        {
            printf("No occurance of inet\n");
        }
        else 
        {
            tok = strtok(a,"inet addr:");
            len = strlen(tok);
            memcpy(ip, tok, len);
            printf("%s\n",ip);
        }
        sleep(5);
    }
    return 0;
}

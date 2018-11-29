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
        char cmd[15], ip[20] = "0.0.0.0";
        char a[100];
        int i = 0;
        char cmd1[128] = {0};

        memset( cmd, '\0', sizeof( cmd ) );
        memset( a, '\0', sizeof( a ) );
        sprintf( cmd, "ifconfig br-lan" );

        fp = popen( cmd, "r" );
        while( fgets( a, sizeof( a ), fp ) != NULL )
        {
            /*printf("%s\n", a);*/
            if( i == 1 )
                break;
            i++;
        }
        pclose( fp );
        
        p = strstr(a,"Bcast");

        if ( p == NULL )
        {
            printf("No occurance of inet\n");
            printf("%s\n",ip);
        }
        else 
        {
            tok = strtok(a,"inet addr:");
            len = strlen( tok );
            memcpy( ip, tok, len );
            printf("%s\n",ip);
        }

        memset( cmd1, '\0', sizeof(cmd1) );
		system("iwpriv wifi1 str_type 4");		
        snprintf(cmd1, 128, "iwconfig ath1 nickname %s", ip);
		system( cmd1 );
        sleep(5);
    }
    return 0;
}

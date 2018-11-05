#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "kwn_tftp.h"

void kwn_sys_cmd_imp( const char* cmd, unsigned char* cmd_buf )
{
    FILE *fp = NULL;
    unsigned char  a[33]={0};
    unsigned char  *token;
    unsigned short len;

    fp = popen(cmd,"r");
    if( fp == NULL )
        return;
    while( fgets(a, sizeof(a), fp) != NULL)
    {
        /*printf("%s",a);*/
    }
    pclose(fp);

    token = strtok(a,"\n");
    len = strlen(token);
    memcpy(cmd_buf,token,len);
    return;
}

void kwn_conv_str_to_ip( char* conv_ip, unsigned char* byte )
{
    unsigned int ip_addr=0,val;
    char  *tok,*ptr;

    tok=strtok(conv_ip,".");

    while( tok != NULL)
    {
        val=strtoul(tok,&ptr,0);
        ip_addr=(ip_addr << 8) + val;
        tok=strtok(NULL,".");
    }

    printf(" Equivalent 32-bit int is : %u\n",ip_addr);

    byte[0] = ((ip_addr >> 24) & 0xFF);
    byte[1] = ((ip_addr >> 16) & 0xFF);
    byte[2] = ((ip_addr >> 8) & 0xFF);
    byte[3] = (ip_addr & 0xFF);

    printf("IP: %d.%d.%d.%d \n",byte[0],byte[1],byte[2],byte[3]);
    return;
}

void kwn_get_tftp_config( kwn_tftp_config *dev_cfg )
{
    unsigned char  cmd[100];
    unsigned char  cmd_buf[50];
    unsigned short len = 0;
    unsigned char  ip_byte[4];

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf( cmd,"uci get tftp.tftp.filename");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    len = strlen(cmd_buf);
    memcpy(dev_cfg->filename, cmd_buf, len);
    printf("filename len : %d \n",len);
    printf("dev_cfg->filename Filename: %s\n",dev_cfg->filename);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get tftp.tftp.filetype");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    dev_cfg->filetype = atoi(cmd_buf);
    printf("dev_cfg->filetype Filetype: %d\n",dev_cfg->filetype);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    memset(ip_byte, '\0', sizeof(ip_byte));
    sprintf( cmd,"uci get tftp.tftp.serverip");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    kwn_conv_str_to_ip(&cmd_buf[0],&ip_byte[0]);
    len = strlen(ip_byte);
    memcpy(dev_cfg->serverip, ip_byte, len);
    printf("dev_cfg->serverip: %d.%d.%d.%d\n",dev_cfg->serverip[0],dev_cfg->serverip[1],dev_cfg->serverip[2],dev_cfg->serverip[3]);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get tftp.tftp.opstatus");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    dev_cfg->opt_status = atoi(cmd_buf);
    printf("dev_cfg->opt_status Opt_Status: %d\n",dev_cfg->opt_status);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get tftp.tftp.optype");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    dev_cfg->opt_type = atoi(cmd_buf);
    printf("dev_cfg->opt_type Opt_Type: %d\n",dev_cfg->opt_type);

    return;
}

int main()
{
    char cmd[100];
    kwn_tftp_config data;
    memset(&data,'\0', sizeof(kwn_tftp_config));
    kwn_get_tftp_config(&data);

    printf("\n This module is to retreive and upload file using tftpboot \n");
    printf("\nTftp Filename  : %s",data.filename);
    printf("\nTftp Filetype  : %d",data.filetype);
    printf("\nTftp serverip  : %d.%d.%d.%d",data.serverip[0],data.serverip[1],data.serverip[2],data.serverip[3]);
    printf("\nTftp Optstatus : %d",data.opt_status);
    printf("\nTftp Opttype   : %d",data.opt_type);

    if ( data.opt_type == KWN_UPLOAD )
    {
        FILE *fin = NULL;
        char config_up[50];
        unsigned char buff_up[200];
        unsigned char cmdimp[300];

        memset(cmd, '\0', sizeof(cmd));
        sprintf(cmd,"uci set tftp.tftp.opstatus='%d'",KWN_UPLOAD_IN_PROGRESS);
        system(cmd);

        memset(cmd, '\0', sizeof(cmd));
        sprintf(cmd, "/usr/bin/tftp -gr %s %d.%d.%d.%d",data.filename,data.serverip[0],data.serverip[1],data.serverip[2],data.serverip[3]);
        system( cmd );

        sprintf(config_up, "/%s",data.filename);
        fin = fopen(config_up,"r");

        while( fgets( buff_up, sizeof(buff_up), fin ) != NULL )
        {
            printf("%s",buff_up);
            sprintf(cmdimp,"uci set %s",buff_up);
            system(cmdimp);
        }
        fclose(fin);
        system("uci commit");
        system("reload_config");

        /*TO DO: sleep*/
        sleep(20);
        memset(cmd, '\0', sizeof(cmd));
        sprintf(cmd,"uci set tftp.tftp.opstatus='%d'",KWN_UPLOAD_SUCCESS);
        system(cmd);

        printf("\nUpload from remote to embedded device");
    }
    else
    {
        FILE *fp1 = NULL;
        FILE *fp = NULL;
        char cmd_down[10];
        char config_down[50];
        unsigned char buff_down[200];

        memset(cmd, '\0', sizeof(cmd));
        sprintf(cmd,"uci set tftp.tftp.opstatus='%d'",KWN_DOWNLOAD_IN_PROGRESS);
        system(cmd);

        sprintf(cmd_down,"uci show");
        sprintf(config_down,"/%s",data.filename);

        fp = fopen(config_down,"w+");

        fp1 = popen(cmd_down,"r");

        while( fgets( buff_down, sizeof(buff_down), fp1 ) != NULL )
        {
            fprintf(fp,"%s",buff_down);
        }
        pclose(fp1);
        fclose(fp);

        memset(cmd, '\0', sizeof(cmd));
        sprintf(cmd, "/usr/bin/tftp -pl %s %d.%d.%d.%d",data.filename,data.serverip[0],data.serverip[1],data.serverip[2],data.serverip[3]);
        system( cmd );

        /*TO DO: sleep*/
        sleep(5);
        memset(cmd, '\0', sizeof(cmd));
        sprintf(cmd,"uci set tftp.tftp.opstatus='%d'",KWN_DOWNLOAD_SUCCESS);
        system(cmd);

        printf("\nRetrieve from embedded device\n");
    }
    return 0;
}

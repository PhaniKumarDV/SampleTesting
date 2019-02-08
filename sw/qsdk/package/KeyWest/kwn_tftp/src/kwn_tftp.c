#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "kwn_tftp.h"

kwn_tftp_config data;
kwn_http_config ht_data;

void kwn_sys_cmd_imp( const char* cmd, unsigned char* cmd_buf )
{
    FILE *fp = NULL;
    char  a[100]={0};
    char  *token;
    short int len;

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

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get tftp.tftp.keepset");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    dev_cfg->keep_set = atoi(cmd_buf);
    printf("dev_cfg->keep_set Keep_set: %d\n",dev_cfg->keep_set);

    return;
}

void kwn_get_http_config( kwn_http_config *dev_cfg )
{
    unsigned char  cmd[100];
    unsigned char  cmd_buf[50];
    unsigned short len = 0;

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get tftp.http.filetype");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    dev_cfg->filetype = atoi(cmd_buf);
    printf("dev_cfg->filetype Filetype: %d\n",dev_cfg->filetype);

    memset(cmd, '\0', sizeof(cmd));
    memset(cmd_buf, '\0', sizeof(cmd_buf));
    sprintf(cmd,"uci get tftp.http.optype");
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
    dev_cfg->opt_type = atoi(cmd_buf);
    printf("dev_cfg->opt_type Opt_Type: %d\n",dev_cfg->opt_type);

    return;
}

void kwn_config_upgrade( )
{
    FILE *fin = NULL;
    char buff_up[200];
    char cmdimp[300];
    char cmd[100];

    memset(buff_up, '\0', sizeof(buff_up));
    memset(cmdimp, '\0', sizeof(cmdimp));

    memset(cmd, '\0', sizeof(cmd));
    sprintf(cmd,"uci set tftp.tftp.opstatus='%d'",KWN_UPLOAD_IN_PROGRESS);
    system(cmd);

    memset( cmd, '\0', sizeof( cmd ) );
    sprintf( cmd, "tftp -g -r %s -l %s %d.%d.%d.%d", data.filename, KWN_NEW_CONFIG_FILE, data.serverip[0], data.serverip[1], data.serverip[2], data.serverip[3] );
    printf(" %s\n",cmd );
    system( cmd );

    memset( cmd, '\0', sizeof( cmd ) );
    sprintf( cmd, "sed -i 's/\r$//g' %s",KWN_NEW_CONFIG_FILE );
    printf(" %s\n",cmd );
    system( cmd );
    
    if( access( KWN_NEW_CONFIG_FILE, 0 ) == 0 ) {
        fin = fopen( KWN_NEW_CONFIG_FILE, "r" );

        while( fgets( buff_up, sizeof( buff_up ), fin ) != NULL )
        {
            printf("%s",buff_up);
            sprintf( cmdimp, "uci set %s", buff_up );
            system( cmdimp );
        }
        fclose( fin );
        system("uci commit");
        system("reload_config");

        /*TO DO: sleep*/
        sleep(30);
        memset( cmd, '\0', sizeof( cmd ) );
        sprintf( cmd," uci set tftp.tftp.opstatus='%d'", KWN_UPLOAD_SUCCESS );
        system( cmd );

        printf("\nUpload from remote to embedded device");
        memset( cmd, '\0', sizeof( cmd ) );
        sprintf( cmd,"rm %s", KWN_NEW_CONFIG_FILE );
        system( cmd );
        system("uci commit");
        return;
    }
    memset( cmd, '\0', sizeof( cmd ) );
    sprintf( cmd, "uci set tftp.tftp.opstatus='%d'", KWN_UPLOAD_FAILURE );
    system( cmd );
    printf("Upload from remote to embedded device is failed\n");

    system("uci commit");
    return;
}

void kwn_image_upgrade( )
{
    printf("\n %s : %d\n",__func__,__LINE__);
    char cmd[100];
    char cmd_buf[100];
    char cmp[6]={'\0'};
    char *tok;
    int image_success = 1;
    
    memset(cmd, '\0', sizeof(cmd));
    sprintf(cmd,"uci set tftp.tftp.opstatus='%d'",KWN_UPLOAD_IN_PROGRESS);
    system(cmd);

    memset( cmd, '\0', sizeof( cmd ) );
    sprintf( cmd, "tftp -g -r %s -l %s %d.%d.%d.%d", data.filename, KWN_NEW_IMAGE_FILE, data.serverip[0], data.serverip[1], data.serverip[2], data.serverip[3] );
    printf(" %s\n",cmd );
    system( cmd );

    memset( cmd, '\0', sizeof( cmd ) );
    memset( cmd_buf, '\0', sizeof( cmd_buf ) );
    sprintf( cmd, "sysupgrade -T %s", KWN_NEW_IMAGE_FILE );
    printf(" %s\n",cmd );
    kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0]);

    tok=strtok(cmd_buf," ");

    while( tok != NULL)
    {
        printf( " %s\n", tok );
        memcpy(cmp,tok,sizeof(cmp));
        printf("cmp: %s\n",cmp);
        if( memcmp(cmp,"failed",sizeof(cmp)) == 0 ){
            printf("Image check failure\n");
            image_success=0;
        }
        tok = strtok(NULL, " ");
    }

    if( image_success ){
        memset( cmd, '\0', sizeof( cmd ) );
        if( data.keep_set == 1 ){
            sprintf( cmd, "sysupgrade -c %s", KWN_NEW_IMAGE_FILE );
            printf(" %s\n",cmd );
        }else{
            sprintf( cmd, "sysupgrade -n %s", KWN_NEW_IMAGE_FILE );
            printf(" %s\n",cmd );
        }

        system( cmd );
        memset( cmd, '\0', sizeof( cmd ) );
        sprintf( cmd," uci set tftp.tftp.opstatus='%d'", KWN_UPLOAD_SUCCESS );
        system( cmd );

        system("uci commit");
        printf("\nUpload from remote to embedded device");

        return;
    }
    else
        printf("Invalid image\n");

    memset( cmd, '\0', sizeof( cmd ) );
    sprintf( cmd," uci set tftp.tftp.opstatus='%d'", KWN_UPLOAD_FAILURE );
    system( cmd );
    system("uci commit");
    printf("\nNot a valid image");

    return;
}

void kwn_config_retrieve( )
{
    FILE *fp1 = NULL;
    FILE *fp = NULL;
    char *tok;
    char cmd[100];
    char buff_down[200];

    memset(cmd, '\0', sizeof(cmd));
    sprintf(cmd,"uci set tftp.tftp.opstatus='%d'",KWN_DOWNLOAD_IN_PROGRESS);
    system(cmd);

    memset(cmd, '\0', sizeof(cmd));
    sprintf(cmd, "uci show");

    fp = fopen(KWN_CFG_FILE,"w+");

    fp1 = popen(cmd,"r");

    while( fgets( buff_down, sizeof(buff_down), fp1 ) != NULL )
    {
        tok=strtok(buff_down,"\n");

        while( tok != NULL)
        {
            fprintf(fp,"%s\r\n",tok);
            printf( "%s\n", tok );
            tok = strtok(NULL, "\n");
        }
    }
    pclose(fp1);
    fclose(fp);

    memset(cmd, '\0', sizeof(cmd));
    sprintf(cmd, "tftp -p -l /tmp/kwncfg.txt -r %s %d.%d.%d.%d",data.filename,data.serverip[0],data.serverip[1],data.serverip[2],data.serverip[3]);
    system( cmd );

    memset(cmd, '\0', sizeof(cmd));
    sprintf(cmd,"uci set tftp.tftp.opstatus='%d'",KWN_DOWNLOAD_SUCCESS);
    system(cmd);

    system("uci commit");
    printf("\nRetrieve from embedded device\n");

    return;
}

void kwn_http_config_upgrade()
{
    printf("\n %s : %d\n",__func__,__LINE__);
    FILE *fin = NULL;
    char buff_up[200];
    char cmdimp[300];
    char cmd[100];

    if( access( KWN_HTTP_NEW_CONFIG_FILE, 0 ) == 0 ) {
    
        memset( cmd, '\0', sizeof( cmd ) );
        sprintf( cmd, "sed -i 's/\r$//g' %s",KWN_HTTP_NEW_CONFIG_FILE );
        printf(" %s\n",cmd );
        system( cmd );
        
        fin = fopen( KWN_HTTP_NEW_CONFIG_FILE, "r" );

        while( fgets( buff_up, sizeof( buff_up ), fin ) != NULL )
        {
            printf("%s",buff_up);
            sprintf( cmdimp, "uci set %s", buff_up );
            system( cmdimp );
        }
        fclose( fin );
        system("uci commit");
        system("reload_config");

        //TO DO: sleep
        sleep(30);
        memset( cmd, '\0', sizeof( cmd ) );
        sprintf( cmd," uci set tftp.tftp.opstatus='%d'", KWN_UPLOAD_SUCCESS );
        system( cmd );

        system("uci commit");
        printf("\nUpload from remote to embedded device");
        memset( cmd, '\0', sizeof( cmd ) );
        sprintf( cmd,"rm %s", KWN_HTTP_NEW_CONFIG_FILE );
        system( cmd );
        return;
    }

    memset( cmd, '\0', sizeof( cmd ) );
    sprintf( cmd," uci set tftp.tftp.opstatus='%d'", KWN_UPLOAD_FAILURE );
    system( cmd );
    system("uci commit");
    printf("\nFile not found");

    return;
}

void kwn_http_config_retrieve()
{
    printf("\n %s : %d\n",__func__,__LINE__);

    FILE *fp1 = NULL;
    FILE *fp = NULL;
    char *tok;
    char cmd[100];
    char buff_down[200];

    memset(cmd, '\0', sizeof(cmd));
    sprintf(cmd,"uci set tftp.tftp.opstatus='%d'",KWN_DOWNLOAD_IN_PROGRESS);
    system(cmd);

    memset(cmd, '\0', sizeof(cmd));
    sprintf(cmd,"uci show");

    fp = fopen(KWN_HTTP_CFG_FILE,"w+");

    fp1 = popen(cmd,"r");

    while( fgets( buff_down, sizeof(buff_down), fp1 ) != NULL )
    {
        tok=strtok(buff_down,"\n");

        while( tok != NULL)
        {
            fprintf(fp,"%s\r\n",tok);
            //printf( "%s\n", tok );
            tok = strtok(NULL, "\n");
        }
    }
    pclose(fp1);
    fclose(fp);

    memset(cmd, '\0', sizeof(cmd));
    sprintf(cmd,"uci set tftp.tftp.opstatus='%d'",KWN_DOWNLOAD_SUCCESS);
    system(cmd);

    printf("\nRetrieve from embedded device\n");
    printf("\n %s : %d\n",__func__,__LINE__);

    printf("\nRetrieve from embedded device\n");
    return;
}

int main()
{
    char cmd[100];

    memset(&data,'\0', sizeof(kwn_tftp_config));
    kwn_get_tftp_config(&data);

    memset(&ht_data,'\0', sizeof(kwn_http_config));
    kwn_get_http_config(&ht_data);

    printf("\n This module is to retreive and upload file using tftpboot \n");
    printf("\nTftp Filename  : %s",data.filename);
    printf("\nTftp Filetype  : %d",data.filetype);
    printf("\nTftp serverip  : %d.%d.%d.%d",data.serverip[0],data.serverip[1],data.serverip[2],data.serverip[3]);
    printf("\nTftp Optstatus : %d",data.opt_status);
    printf("\nTftp Opttype   : %d\n",data.opt_type);

    printf("\nHttp Filetype  : %d",ht_data.filetype);
    printf("\nHttp Opttype   : %d\n",ht_data.opt_type);

    switch( data.opt_type )
    {
        case KWN_UPLOAD:
            {
                switch( data.filetype )
                {
                    case KWN_CONFIG:
                        {        
                            kwn_config_upgrade();
                            break;
                        }
                    case KWN_IMAGE:
                        {
                            kwn_image_upgrade();
                            break;
                        }
                    default:
                        {
                            printf("\nInvalid File type\n");
                            break;
                        }
                }
                break;
            }
        case KWN_DOWNLOAD:
            {      
                switch( data.filetype )
                {
                    case KWN_CONFIG:
                        {
                            kwn_config_retrieve();
                            break;
                        }
                    default:
                        {
                            printf("\nInvalid File type\n");
                            break;
                        }
                }
                break;
            }
        default:
            printf("\nInvalid Operation type\n");
            break;
    }

    switch( ht_data.opt_type )
    {
        case KWN_UPLOAD:
            {
                switch( ht_data.filetype )
                {
                    case KWN_CONFIG:
                        {        
                            kwn_http_config_upgrade();
                            break;
                        }
                    default:
                        {
                            printf("\nInvalid HTTP File type\n");
                            break;
                        }
                }
                break;
            }
        case KWN_DOWNLOAD:
            {      
                switch( data.filetype )
                {
                    case KWN_CONFIG:
                        {
                            kwn_http_config_retrieve();
                            break;
                        }
                    default:
                        {
                            printf("\nInvalid File type\n");
                            break;
                        }
                }
                break;
            }
        default:
            printf("\nInvalid Operation type\n");
            break;
    }

    memset( cmd, '\0', sizeof( cmd ) );
    sprintf( cmd," uci set tftp.tftp.optype='0'");
    system( cmd );

    memset( cmd, '\0', sizeof( cmd ) );
    sprintf( cmd," uci set tftp.http.optype='0'");
    system( cmd );

    return 0;
}

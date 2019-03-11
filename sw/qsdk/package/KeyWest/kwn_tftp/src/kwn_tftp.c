#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "kwn_tftp.h"

kwn_tftp_config data;
kwn_http_config ht_data;

enum uci_cmd_type {
    KWN_CMD_TYPE_SCALAR = 1,
    KWN_CMD_TYPE_TABLE = 2
};

struct kwn_cfg_uci_cmds {
    char cmd[50];
    int type;
};

#define KWN_CMD_LEN 147
struct kwn_cfg_uci_cmds uci_cmd_list[] = {
/* Wireless 5GHz*/
    /* Properties */
    /*   0. */ { "wireless.wifi1.linktype", KWN_CMD_TYPE_SCALAR },
    /*   1. */ { "wireless.@wifi-iface[1].mode", KWN_CMD_TYPE_SCALAR },
    /*   2. */ { "wireless.@wifi-iface[1].ssid", KWN_CMD_TYPE_SCALAR },
    /*   3. */ { "wireless.wifi1.country", KWN_CMD_TYPE_SCALAR },
    /*   4. */ { "wireless.wifi1.hwmode", KWN_CMD_TYPE_SCALAR },
    /*   5. */ { "wireless.wifi1.htmode", KWN_CMD_TYPE_SCALAR },
    /*   6. */ { "wireless.wifi1.channel", KWN_CMD_TYPE_SCALAR },
    /*   7. */ { "wireless.wifi1.distance", KWN_CMD_TYPE_SCALAR },
    /*   8. */ { "wireless.@wifi-iface[1].shaping", KWN_CMD_TYPE_SCALAR },
    /*   9. */ { "wireless.@wifi-iface[1].ullmt", KWN_CMD_TYPE_SCALAR },
    /*  10. */ { "wireless.@wifi-iface[1].dllmt", KWN_CMD_TYPE_SCALAR },
    /*  11. */ { "wireless.@wifi-iface[1].hidden", KWN_CMD_TYPE_SCALAR },
    /*  12. */ { "wireless.wifi1.wifitimer", KWN_CMD_TYPE_SCALAR },
    /*  13. */ { "wireless.wifi1.linktimer", KWN_CMD_TYPE_SCALAR },
    /*  14. */ { "wireless.wifi1.suservice", KWN_CMD_TYPE_SCALAR },
    /*  15. */ { "wireless.wifi1.icb", KWN_CMD_TYPE_SCALAR },
    /*  16. */ { "wireless.wifi1.macinmac", KWN_CMD_TYPE_SCALAR },
    /*  17. */ { "wireless.@wifi-iface[1].maxsta", KWN_CMD_TYPE_SCALAR },
    /*  18. */ { "wireless.wifi1.rcretries", KWN_CMD_TYPE_SCALAR },
    /* MIMO */
    /*  19. */ { "wireless.@wifi-iface[1].shortgi", KWN_CMD_TYPE_SCALAR },
    /*  20. */ { "wireless.wifi1.txchainmask", KWN_CMD_TYPE_SCALAR },
    /*  21. */ { "wireless.wifi1.rxchainmask", KWN_CMD_TYPE_SCALAR },
    /*  22. */ { "wireless.@wifi-iface[1].amsdu", KWN_CMD_TYPE_SCALAR },
    /*  23. */ { "wireless.@wifi-iface[1].ampdu", KWN_CMD_TYPE_SCALAR },
    /* DDRS/ATPC */
    /*  24. */ { "wireless.wifi1.ddrsstatus", KWN_CMD_TYPE_SCALAR },
    /*  25. */ { "wireless.wifi1.spatialstream", KWN_CMD_TYPE_SCALAR },
    /*  26. */ { "wireless.wifi1.ddrsrate", KWN_CMD_TYPE_SCALAR },
    /*  27. */ { "wireless.wifi1.ddrsminrate", KWN_CMD_TYPE_SCALAR },
    /*  28. */ { "wireless.wifi1.ddrsmaxrate", KWN_CMD_TYPE_SCALAR },
    /*  29. */ { "wireless.wifi1.ddrsinctimer", KWN_CMD_TYPE_SCALAR },
    /*  30. */ { "wireless.wifi1.ddrsdectimer", KWN_CMD_TYPE_SCALAR },
    /*  31. */ { "wireless.wifi1.ddrsincthrld", KWN_CMD_TYPE_SCALAR },
    /*  32. */ { "wireless.wifi1.ddrsrtxinc", KWN_CMD_TYPE_SCALAR },
    /*  33. */ { "wireless.wifi1.ddrsrtxdec", KWN_CMD_TYPE_SCALAR },
    /*  34. */ { "wireless.wifi1.atpcstatus", KWN_CMD_TYPE_SCALAR },
    /*  35. */ { "wireless.wifi1.antennagain", KWN_CMD_TYPE_SCALAR },
    /*  36. */ { "wireless.wifi1.maxeirp", KWN_CMD_TYPE_SCALAR },
    /*  37. */ { "wireless.wifi1.atpcpower", KWN_CMD_TYPE_SCALAR },
    /* Security */
    /*  38. */ { "wireless.@wifi-iface[1].encryption", KWN_CMD_TYPE_SCALAR },
    /*  39. */ { "wireless.@wifi-iface[1].key", KWN_CMD_TYPE_SCALAR },
    /* MAC ACL */
    /*  40. */ { "wireless.@wifi-iface[1].macfilter", KWN_CMD_TYPE_SCALAR },
    /*  41. */ { "wireless.@wifi-iface[1].maclist", KWN_CMD_TYPE_SCALAR },
    /* DCS */
    /*  42. */ { "wireless.wifi1.dcsstatus", KWN_CMD_TYPE_SCALAR },
    /*  43. */ { "wireless.wifi1.dcsthrld", KWN_CMD_TYPE_SCALAR },
/* Wireless 2.4GHz*/
    /* Properties */
    /*  44. */ { "wireless.@wifi-iface[0].disabled", KWN_CMD_TYPE_SCALAR },
    /*  45. */ { "wireless.@wifi-iface[0].mode", KWN_CMD_TYPE_SCALAR },
    /*  46. */ { "wireless.@wifi-iface[0].ssid", KWN_CMD_TYPE_SCALAR },
    /*  47. */ { "wireless.wifi0.country", KWN_CMD_TYPE_SCALAR },
    /*  48. */ { "wireless.wifi0.hwmode", KWN_CMD_TYPE_SCALAR },
    /*  49. */ { "wireless.wifi0.htmode", KWN_CMD_TYPE_SCALAR },
    /*  50. */ { "wireless.wifi0.channel", KWN_CMD_TYPE_SCALAR },
    /*  51. */ { "wireless.wifi0.TXPowLim2G", KWN_CMD_TYPE_SCALAR },
    /*  52. */ { "wireless.@wifi-iface[0].dis_legacy", KWN_CMD_TYPE_SCALAR },
    /*  53. */ { "wireless.@wifi-iface[0].hidden", KWN_CMD_TYPE_SCALAR },
    /* Security */
    /*  54. */ { "wireless.@wifi-iface[0].encryption", KWN_CMD_TYPE_SCALAR },
    /*  55. */ { "wireless.@wifi-iface[0].key", KWN_CMD_TYPE_SCALAR },
    /* MAC ACL */
    /*  56. */ { "wireless.@wifi-iface[0].macfilter", KWN_CMD_TYPE_SCALAR },
    /*  57. */ { "wireless.@wifi-iface[0].maclist", KWN_CMD_TYPE_SCALAR },
/* Network */
    /* IP Configuration */
    /*  58. */ { "network.param.networkmode", KWN_CMD_TYPE_SCALAR },
    /*  59. */ { "network.param.natstatus", KWN_CMD_TYPE_SCALAR },
    /*  60. */ { "network.lan.proto", KWN_CMD_TYPE_SCALAR },
    /*  61. */ { "network.lan.ipaddr", KWN_CMD_TYPE_SCALAR },
    /*  62. */ { "network.lan.netmask", KWN_CMD_TYPE_SCALAR },
    /*  63. */ { "network.lan.gateway", KWN_CMD_TYPE_SCALAR },
    /*  64. */ { "network.lan.dns", KWN_CMD_TYPE_SCALAR },
    /*  65. */ { "network.kweth.ipaddr", KWN_CMD_TYPE_SCALAR },
    /*  66. */ { "network.kweth.netmask", KWN_CMD_TYPE_SCALAR },
    /*  67. */ { "network.kweth.gateway", KWN_CMD_TYPE_SCALAR },
    /* RADIUS */
    /*  68. */ { "wrt-radauth.sys.enableRadAuth", KWN_CMD_TYPE_SCALAR },
    /*  69. */ { "wrt-radauth.sys.primaryServer", KWN_CMD_TYPE_SCALAR },
    /*  70. */ { "wrt-radauth.sys.primaryPort", KWN_CMD_TYPE_SCALAR },
    /*  71. */ { "wrt-radauth.sys.primarySecret", KWN_CMD_TYPE_SCALAR },
    /*  72. */ { "wrt-radauth.sys.secondaryServer", KWN_CMD_TYPE_SCALAR },
    /*  73. */ { "wrt-radauth.sys.secondaryPort", KWN_CMD_TYPE_SCALAR },
    /*  74. */ { "wrt-radauth.sys.secondarySecret", KWN_CMD_TYPE_SCALAR },
    /*  75. */ { "wrt-radauth.sys.reauthTime", KWN_CMD_TYPE_SCALAR },
    /*  76. */ { "wrt-radauth.sys.retryTime", KWN_CMD_TYPE_SCALAR },
    /*  77. */ { "wrt-radauth.sys.requestRetries", KWN_CMD_TYPE_SCALAR },
    /*  78. */ { "wrt-radauth.sys.requestTimeout", KWN_CMD_TYPE_SCALAR },
    /* VLAN */
    /*  79. */ { "vlan.vlan.status", KWN_CMD_TYPE_SCALAR },
    /*  80. */ { "vlan.vlan.mode", KWN_CMD_TYPE_SCALAR },
    /*  81. */ { "vlan.vlan.mgmtvlan", KWN_CMD_TYPE_SCALAR },
    /*  82. */ { "vlan.vlan.accessvlan", KWN_CMD_TYPE_SCALAR },
    /*  83. */ { "vlan.vlan.trunkoption", KWN_CMD_TYPE_SCALAR },
    /*  84. */ { "vlan.vlan.trunkvlan", KWN_CMD_TYPE_SCALAR },
    /*  85. */ { "vlan.vlan.svlan", KWN_CMD_TYPE_SCALAR },
    /*  86. */ { "vlan.vlan.svlanethertype", KWN_CMD_TYPE_SCALAR },
    /*  87. */ { "vlan.vlan.bda", KWN_CMD_TYPE_SCALAR },
    /*  88. */ { "vlan.vlan.bsa", KWN_CMD_TYPE_SCALAR },
    /*  89. */ { "vlan.vlan.bvid", KWN_CMD_TYPE_SCALAR },
    /*  90. */ { "vlan.vlan.bisid", KWN_CMD_TYPE_SCALAR },
    /*  91. */ { "vlan.vlan.tagmgmt", KWN_CMD_TYPE_SCALAR },
    /* Ethernet */
    /*  92. */ { "ethernet.ethernet.mode", KWN_CMD_TYPE_SCALAR },
    /*  93. */ { "ethernet.ethernet.ethtimer", KWN_CMD_TYPE_SCALAR },
    /*  94. */ { "network.lan.mtu", KWN_CMD_TYPE_SCALAR },
    /* DHCP Server */
    /*  95. */ { "dhcp.lan.ignore", KWN_CMD_TYPE_SCALAR },
    /*  96. */ { "dhcp.lan.start", KWN_CMD_TYPE_SCALAR },
    /*  97. */ { "dhcp.lan.limit", KWN_CMD_TYPE_SCALAR },
    /*  98. */ { "dhcp.lan.leasetime", KWN_CMD_TYPE_SCALAR },
    /* DHCP Fixed leases */
    /*  99. */ { "dhcp.@host", KWN_CMD_TYPE_TABLE },
    /* Filtering */
    /* 100. */ { "filter.filter.status", KWN_CMD_TYPE_SCALAR },
    /* 101. */ { "filter.filter.l2mcast", KWN_CMD_TYPE_SCALAR },
    /* 102. */ { "filter.filter.l3mcast", KWN_CMD_TYPE_SCALAR },
    /* 103. */ { "filter.filter.l2bcast", KWN_CMD_TYPE_SCALAR },
    /* 104. */ { "filter.filter.l3bcast", KWN_CMD_TYPE_SCALAR },
/* Management */
    /* NTP */
    /* 105. */ { "system.ntp.enabled", KWN_CMD_TYPE_SCALAR },
    /* 106. */ { "system.ntp.server", KWN_CMD_TYPE_SCALAR },
    /* 107. */ { "system.@system[0].timezone", KWN_CMD_TYPE_SCALAR },
    /* GPS */
    /* 108. */ { "system.gps.status", KWN_CMD_TYPE_SCALAR },
    /* 109. */ { "system.gps.interval", KWN_CMD_TYPE_SCALAR },
    /* Dying Gasp */
    /* 110. */ { "wireless.@wifi-iface[1].dyinggasp", KWN_CMD_TYPE_SCALAR },
    /* 111. */ { "wireless.@wifi-iface[1].dgackdisable", KWN_CMD_TYPE_SCALAR },
    /* LEDS */
    /* 112. */ { "system.led.status", KWN_CMD_TYPE_SCALAR },
    /* Logging */
    /* 113. */ { "system.@system[0].log_ip", KWN_CMD_TYPE_SCALAR },
    /* 114. */ { "system.@system[0].log_port", KWN_CMD_TYPE_SCALAR },
    /* 115. */ { "system.@system[0].templogstatus", KWN_CMD_TYPE_SCALAR },
    /* 116. */ { "system.@system[0].temploginterval", KWN_CMD_TYPE_SCALAR },
    /* Location */
    /* 117. */ { "system.@system[0].hostname", KWN_CMD_TYPE_SCALAR },
    /* 118. */ { "wireless.wifi1.customername", KWN_CMD_TYPE_SCALAR },
    /* 119. */ { "system.@system[0].location", KWN_CMD_TYPE_SCALAR },
    /* 120. */ { "system.@system[0].email", KWN_CMD_TYPE_SCALAR },
    /* 121. */ { "system.@system[0].contact", KWN_CMD_TYPE_SCALAR },
    /* 122. */ { "system.@system[0].bstid", KWN_CMD_TYPE_SCALAR },
    /* 123. */ { "wireless.wifi1.linkid", KWN_CMD_TYPE_SCALAR },
    /* HTTP/HTTPs */
    /* 124. */ { "uhttpd.main.adminpwd", KWN_CMD_TYPE_SCALAR },
    /* 125. */ { "uhttpd.main.userpwd", KWN_CMD_TYPE_SCALAR },
    /* 126. */ { "uhttpd.main.superpwd", KWN_CMD_TYPE_SCALAR },
    /* 127. */ { "uhttpd.main.listen_http", KWN_CMD_TYPE_SCALAR },
    /* 128. */ { "uhttpd.main.listen_https", KWN_CMD_TYPE_SCALAR },
    /* Telnet/SSH */
    /* 129. */ { "telnetssh.telnet.status", KWN_CMD_TYPE_SCALAR },
    /* 130. */ { "telnetssh.telnet.sessions", KWN_CMD_TYPE_SCALAR },
    /* 131. */ { "telnetssh.telnet.port", KWN_CMD_TYPE_SCALAR },
    /* 132. */ { "telnetssh.ssh.status", KWN_CMD_TYPE_SCALAR },
    /* 133. */ { "telnetssh.ssh.sessions", KWN_CMD_TYPE_SCALAR },
    /* 134. */ { "telnetssh.ssh.port", KWN_CMD_TYPE_SCALAR },
    /* SNMP */
    /* 135. */ { "snmpd.public_access.version", KWN_CMD_TYPE_SCALAR },
    /* 136. */ { "snmpd.public.community", KWN_CMD_TYPE_SCALAR },
    /* 137. */ { "snmpd.private.community", KWN_CMD_TYPE_SCALAR },
    /* 138. */ { "snmpd.trapaddress.host", KWN_CMD_TYPE_SCALAR },
    /* 139. */ { "snmpd.trapaddress.paswd", KWN_CMD_TYPE_SCALAR },
    /* TFTP */
    /* 140. */ { "tftp.tftp.optype", KWN_CMD_TYPE_SCALAR },
    /* 141. */ { "tftp.tftp.serverip", KWN_CMD_TYPE_SCALAR },
    /* 142. */ { "tftp.tftp.filename", KWN_CMD_TYPE_SCALAR },
    /* 143. */ { "tftp.tftp.filetype", KWN_CMD_TYPE_SCALAR },
    /* 144. */ { "tftp.tftp.keepset", KWN_CMD_TYPE_SCALAR },
    /* 145. */ { "tftp.http.filetype", KWN_CMD_TYPE_SCALAR },
    /* 146. */ { "tftp.http.optype", KWN_CMD_TYPE_SCALAR },
    /* Update maximum number + 1 in KWN_CMD_LEN */
};

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

    if( a[0] == '\0' ) {
        memcpy( cmd_buf, "-NA-", sizeof( cmd_buf ) );
        return;
    }

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
        system("uci set uhttpd.main.pwdmodified='1'");
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
        system("/usr/sbin/sify_reboot_log.sh 11");
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

        printf("\nUpload from remote to embedded device");

        return;
    }
    else
        printf("Invalid image\n");

    memset( cmd, '\0', sizeof( cmd ) );
    sprintf( cmd," uci set tftp.tftp.opstatus='%d'", KWN_UPLOAD_FAILURE );
    system( cmd );
    printf("\nNot a valid image");

    return;
}

void kwn_config_retrieve( )
{
    FILE *fp = NULL;
    char cmd[100];
    char cmd_buf[100];
    int i = 0;

    memset(cmd, '\0', sizeof(cmd));
    sprintf(cmd,"uci set tftp.tftp.opstatus='%d'",KWN_DOWNLOAD_IN_PROGRESS);
    system(cmd);

    memset(cmd, '\0', sizeof(cmd));

    fp = fopen(KWN_CFG_FILE,"w+");

    for( i = 0; i < KWN_CMD_LEN; i++ )
    {
        if( uci_cmd_list[i].type == KWN_CMD_TYPE_SCALAR ) {
            memset( cmd, '\0', sizeof( cmd ) );
            memset( cmd_buf, '\0', sizeof( cmd_buf ) );
            sprintf( cmd, "uci get %s",uci_cmd_list[i].cmd);
            printf("cmd : %s \n",cmd);
            kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
            if( memcmp( cmd_buf, "-NA-", 4 ) )
                fprintf( fp, "%s='%s'\r\n", uci_cmd_list[i].cmd, cmd_buf );
        }
        else if( uci_cmd_list[i].type == KWN_CMD_TYPE_TABLE ) {
            /* TODO: Table Handling */
        }
        else {
            continue;
        }
    }
    fclose(fp);

    memset(cmd, '\0', sizeof(cmd));
    sprintf(cmd, "tftp -p -l /tmp/kwncfg.txt -r %s %d.%d.%d.%d",data.filename,data.serverip[0],data.serverip[1],data.serverip[2],data.serverip[3]);
    system( cmd );

    memset(cmd, '\0', sizeof(cmd));
    sprintf(cmd,"uci set tftp.tftp.opstatus='%d'",KWN_DOWNLOAD_SUCCESS);
    system(cmd);

    printf("\nRetrieve from embedded device\n");

    return;
}

#if 0
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
#endif

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
        system("uci set uhttpd.main.pwdmodified='1'");
        fclose( fin );
        system("uci commit");
        system("reload_config");

        //TO DO: sleep
        sleep(30);
        memset( cmd, '\0', sizeof( cmd ) );
        sprintf( cmd," uci set tftp.tftp.opstatus='%d'", KWN_UPLOAD_SUCCESS );
        system( cmd );

        printf("\nUpload from remote to embedded device");
        memset( cmd, '\0', sizeof( cmd ) );
        sprintf( cmd,"rm %s", KWN_HTTP_NEW_CONFIG_FILE );
        system( cmd );
        return;
    }

    memset( cmd, '\0', sizeof( cmd ) );
    sprintf( cmd," uci set tftp.tftp.opstatus='%d'", KWN_UPLOAD_FAILURE );
    system( cmd );
    printf("\nFile not found");

    return;
}

void kwn_http_config_retrieve()
{
    FILE *fp = NULL;
    char cmd[ 100 ];
    char cmd_buf[ 100 ];
    int i = 0;

    memset(cmd, '\0', sizeof(cmd));
    sprintf(cmd,"uci set tftp.tftp.opstatus='%d'",KWN_DOWNLOAD_IN_PROGRESS);
    system(cmd);

    fp = fopen( KWN_HTTP_CFG_FILE, "w+" );

    for( i = 0; i < KWN_CMD_LEN; i++ )
    {
        if( uci_cmd_list[i].type == KWN_CMD_TYPE_SCALAR ) {
            memset( cmd, '\0', sizeof( cmd ) );
            memset( cmd_buf, '\0', sizeof( cmd_buf ) );
            sprintf( cmd, "uci get %s",uci_cmd_list[i].cmd);
            printf("cmd : %s \n",cmd);
            kwn_sys_cmd_imp( &cmd[0], &cmd_buf[0] );
            if( memcmp( cmd_buf, "-NA-", 4 ) )
                fprintf( fp, "%s='%s'\r\n", uci_cmd_list[i].cmd, cmd_buf );
        }
        else if( uci_cmd_list[i].type == KWN_CMD_TYPE_TABLE ) {
            /* TODO: Table Handling */
        }
        else {
            continue;
        }
    }
    fclose( fp );

    memset( cmd, '\0', sizeof( cmd ) );
    sprintf( cmd, "uci set tftp.tftp.opstatus='%d'", KWN_DOWNLOAD_SUCCESS );
    system( cmd );

    printf("\nRetrieve from embedded device\n");
    return;
}

#if 0
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
#endif

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

    system("uci commit");
    return 0;
}

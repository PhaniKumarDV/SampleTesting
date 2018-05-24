/**
 * $Id: tokens.h,v 1.2 2003/07/02 03:40:47 gwochern Exp $
 * $Author: gwochern $
 * $Date: 2003/07/02 03:40:47 $
 * $Locker:  $
 * $Revision: 1.2 $
 *
 *
 * Copyright (C) 2000-2002, SENAO INTERNATIONAL CO., LTDAll rights reserved.
 * No part of this document may be reproduced in any form or by any 
 * means or used to make any derivative work (such as translation,
 * transformation, or adaptation) without permission from Viosoft
 * Corporation.
 */

#ifndef _TOKEN_H_
#define _TOKEN_H_
#include "gconfig.h"
#include "tokens_wireless.h"
#include "tokens_atheros.h"
#if SUPPORT_MULTI_WLAN_PLATFORM
#include "tokens_multiplatform.h"
#endif

#define AP_CFG_CRC_TOK                   "apcfgcrc32"
#define LAN_DEV_TOK                      "lan_dev"
#define LAN_PHYDEV_TOK                   "lan_phydev"
#define WLAN1_BRG_TOK                    "wlan1brgif"
#define WLAN1_DEV_NAME                   "wlan1devname"
#define WLAN2_DEV_NAME                   "wlan2devname"
#define WLAN1_DEV_TYPE                   "wlan1devtype"
#define WLAN2_DEV_TYPE                   "wlan2devtype"

#define HOST_TOK                         "host"
#define DEVICENAME_TOK                   "devicename"
#define DOMAIN_TOK                       "domain"
#ifdef FOR_DLINK
#define WEB_DOMAIN_TOK                   "web_domain"
#endif
#define LAN_IPADDR_TOK                   "lan_ip"
#if HAS_MULTI_MODE_LAN_IP || HAS_NEW_MULTI_MODE_LAN_IP
#define LAN_IPADDR_AP_MODE_TOK           "lan_ip_ap"
#define LAN_MASK_AP_MODE_TOK             "lan_mask_ap"
#define LAN_GATEWAY_AP_MODE_TOK			 "lan_gateway_ap"
#endif
#define LAN_MANAGEMENT_IP_TOK	         "lan_man_ip"
#define LAN_MANAGEMENT_MASK_TOK			 "lan_man_mask"
#if HAS_NEW_MULTI_MODE_LAN_IP
#define LAN_IPADDR_CB_MODE_TOK           "lan_ip_cb"
#define LAN_MASK_CB_MODE_TOK             "lan_mask_cb"
#define LAN_GATEWAY_CB_MODE_TOK			 "lan_gateway_cb"
#define LAN_IPADDR_AP_RE_MODE_TOK           "lan_ip_ap_r"
#define LAN_MASK_AP_RE_MODE_TOK             "lan_mask_ap_r"
#define LAN_GATEWAY_AP_RE_MODE_TOK			 "lan_gateway_ap_r"
#define LAN_IPADDR_AR_MODE_TOK           "lan_ip_ar"
#define LAN_MASK_AR_MODE_TOK             "lan_mask_ar"
#define LAN_GATEWAY_AR_MODE_TOK			 "lan_gateway_ar"
#endif
#define LAN_MASK_TOK                     "lan_mask"
#define LAN_CONNECTION_TYPE_TOK	         "lan_contype"
#define LAN_HOSTNAME_TOK                 "lan_hostname"
#define LAN_MAC_TOK                      "lan_mac"
#if HAS_ZYXEL_TELEFONICA_FUNCTION
#define LAN_CLONED_MAC_TOK               "lan_cloned_mac"
#endif
#define LAN_GATEWAY_TOK                  "lan_gateway"
#if HAS_DNS_CLIENT_FUNCTION
#define LAN_DNS_TYPE_TOK                 "lan_dns_type"
#endif
#define LAN_DNS1_TOK                     "lan_dns1"
#define LAN_DNS2_TOK                     "lan_dns2"
#define STP_ENABLE_TOK                   "stp_enable"
#if HAS_ADVANCED_STP
#define STP_HELLO_TIME_TOK				 "stp_hello_time"
#define STP_MAX_AGE_TOK				 	 "stp_max_age"
#define STP_FORWARD_DELAY_TOK			 "stp_forward_delay"
#define STP_BR_PRIORITY_TOK			 	 "stp_br_priority"
#endif
#define AP_HARDWAREVER_TOK            	 "hardware_ver"
#define AP_FIRMWAREVER_TOK            	 "firmware_ver"
#define AP_SN_TOK                     	 "sn"
#define AP_DATE_TOK                   	 "date"
#define AP_COUNTRYCODE_TOK            	 "countrycode"

/* ------------------   WAN tokens   -----------------------*/
#define WAN_DUAL_ACCESS_TOK              "wan_dualaccess"

#define WAN1_INTERFACE_TOK               "wan1_interface"
#define WAN1_ORG_MAC_TOK                 "wan1_orgmac"
#define WAN1_ONLINE_TOK                  "wan1_online"
#define WAN1_ENABLE_TOK                  "wan1_enable"
#define WAN1_PHYDEV_TOK                  "wan1_phydev"
#define WAN1_DEV_TOK                     "wan1_dev"
#define WAN1_SESSION_TOK                 "wan1_session"
#define WAN1_COUNTRY_TOK                 "wan1_country"
#define WAN1_ISP_TOK                     "wan1_isp"
#if HAS_WAN_CONNECT_TIME
#define WAN1_TIME_CONNECT_TOK            "wan1_ctime"
#define WAN1_TIME_LEASE_TOK              "wan1_lease"
#endif
#define WAN1_COMMANDS_TOK                "wan1_cmds"
#if HAS_WAN_LINKCHECK
#define WAN1_DUMMY_IP_TOK                "wan1_dmip"
#define WAN1_DUMMY_GW_TOK                "wan1_dmgw"
#define WAN1_DUMMY_GW_MAC_TOK            "wan1_dmgwmac"
#define WAN1_DUMMY_CHECK_IP_TOK          "wan1_dmcip"
#define WAN1_DUMMY_STATUS_TOK            "wan1_dmstat"
#endif
#if FOR_BELKIN
#define WAN1_DUMMY_LINK_STATUS_TOK		 "wan1_dmlink"
#endif

#define WAN1_ISP_UNNUMBER_EN_TOK         "isp1_unnumber_en"
#define WAN1_ISP_UNNUMBER_IP_TOK         "isp1_unnumber_ip"
#define WAN1_ISP_UNNUMBER_MASK_TOK       "isp1_unnumber_mask"
#define WAN1_ISP_UNNUMBER_DHCPD_ENABLE_TOK         "isp1_unnb_dhd_en"
#define WAN1_ISP_UNNUMBER_DHCPD_START_TOK          "isp1_unnb_dhd_st"
#define WAN1_ISP_UNNUMBER_DHCPD_END_TOK            "isp1_unnb_dhd_end"
#define WAN1_ISP_UNNUMBER_DHCPD_MINLEASE_TIME_TOK  "isp1_unnb_dhd_lease"

#if HAS_PPPOE_STATIC
#define WAN1_ISP_STATIC_EN_TOK           "isp1_static_en"
#define WAN1_ISP_STATIC_IP_TOK           "isp1_static_ip"
#endif

#ifdef HAS_WAN2_DEV
#define WAN2_INTERFACE_TOK               "wan2_interface"
#define WAN2_ORG_MAC_TOK                 "wan2_orgmac"
#define WAN2_ONLINE_TOK                  "wan2_online"
#define WAN2_ENABLE_TOK                  "wan2_enable"
#define WAN2_PHYDEV_TOK                  "wan2_phydev"
#define WAN2_DEV_TOK                     "wan2_dev"
#define WAN2_SESSION_TOK                 "wan2_session"
#define WAN2_COUNTRY_TOK                 "wan2_country"
#define WAN2_ISP_TOK                     "wan2_isp"
#if HAS_WAN_CONNECT_TIME
#define WAN2_TIME_CONNECT_TOK            "wan2_ctime"
#define WAN2_TIME_LEASE_TOK              "wan2_lease"
#endif
#define WAN2_COMMANDS_TOK                "wan2_cmds"
#if HAS_WAN_LINKCHECK
#define WAN2_DUMMY_IP_TOK                "wan2_dmip"
#define WAN2_DUMMY_GW_TOK                "wan2_dmgw"
#define WAN2_DUMMY_GW_MAC_TOK            "wan2_dmgwmac"
#define WAN2_DUMMY_CHECK_IP_TOK          "wan2_dmcip"
#define WAN2_DUMMY_STATUS_TOK            "wan2_dmstat"
#endif
#if FOR_BELKIN
#define WAN2_DUMMY_LINK_STATUS_TOK	"wan2_dmlink"
#endif

#define WAN2_ISP_UNNUMBER_EN_TOK         "isp2_unnumber_en"
#define WAN2_ISP_UNNUMBER_IP_TOK         "isp2_unnumber_ip"
#define WAN2_ISP_UNNUMBER_MASK_TOK       "isp2_unnumber_mask"

#if HAS_PPPOE_STATIC
#define WAN2_ISP_STATIC_EN_TOK           "isp2_static_en"
#define WAN2_ISP_STATIC_IP_TOK           "isp2_static_ip"
#endif

#endif
#if HAS_WAN2_DEV && HAS_FLETS_PPPOE
#define FLETS_AUTO_CONN_TOK				 "flets_auto_conn"
#define FLETS_LOCATION_TOK		 	 	 "flets_location"
#endif
/* ------------------   Connection type: static IP, DHCPc, PPPoE ------*/
#define WAN1_CONNECTION_TYPE_TOK         "wan1_contype"
#define WAN1_CLONED_MAC_TOK              "wan1_cloned_mac"
#define WAN1_IP_TYPE_TOK				 "wan1_ip_type"
#define WAN1_HOST_TOK                    "wan1_hostname"
#define WAN1_DEFAULT_ROUTE_TOK           "wan1_defroute"
#ifdef HAS_WAN2_DEV
#define WAN2_CONNECTION_TYPE_TOK         "wan2_contype"
#define WAN2_CLONED_MAC_TOK              "wan2_cloned_mac"
#define WAN2_IP_TYPE_TOK				 "wan2_ip_type"
#define WAN2_HOST_TOK                    "wan2_hostname"
#define WAN2_DEFAULT_ROUTE_TOK           "wan2_defroute"
#endif
/* ------------------   Static IP -------------------------------------*/
#define WAN1_MAC_TOK                     "wan1_mac"
#define WAN1_IPADDR_TOK                  "wan1_ip"
#define WAN1_MASK_TOK                    "wan1_mask"
#define WAN1_GATEWAYIP_TOK               "wan1_gateway"
#define WAN1_MTU_TOK                     "wan1_mtu"
#define WAN1_RELOAD_TOK                  "wan1_reload"
#if HAS_WAN_LINKCHECK
#define WAN1_CHECK_TOK                   "wan1_check"
#define WAN1_CHECK_IP_TOK                "wan1_checkip"
#if HAS_TELEFONICA_3G_FUNCTION
#define WAN1_CHECK_IP1_TOK               "wan1_checkip1"
#define WAN1_CHECK_IP2_TOK               "wan1_checkip2"
#endif
#define WAN1_CHECK_GW_TOK                "wan1_checkgw"
#endif
#ifdef HAS_WAN2_DEV
#define WAN2_IPADDR_TOK                  "wan2_ip"
#define WAN2_MASK_TOK                    "wan2_mask"
#define WAN2_GATEWAYIP_TOK               "wan2_gateway"
#define WAN2_MTU_TOK                     "wan2_mtu"
#define WAN2_RELOAD_TOK                  "wan1_reload"
#if HAS_WAN_LINKCHECK
#define WAN2_CHECK_TOK                   "wan2_check"
#define WAN2_CHECK_IP_TOK                "wan2_checkip"
#define WAN2_CHECK_GW_TOK                "wan2_checkgw"
#endif
#endif

/* ------------------   PPPoE ----------------------------------------*/
/* 2008/10/01 jerry chen: dual pppoe */
#ifdef HAS_PPPOE_JAPAN
#define WAN_DEFAULT_SESSION_TOK			"wan_default_session"
#endif
#if HAS_WAN_PPPOE || HAS_WAN_3G
#define WAN1_ISP_USER_TOK                "isp1_user"
#define WAN1_ISP_PASS_TOK                "isp1_pass"
#define WAN1_ISP_TYPE_TOK                "isp1_type"
#define WAN1_ISP_CONN_TYPE_TOK           "isp1_conntype"
#define WAN1_ISP_MAX_IDLETIME_TOK        "isp1_maxidletime"
#define WAN1_ISP_MTU_TOK                 "isp1_mtu"
#define WAN1_ISP_SERVICENAME_TOK         "isp1_service"
#define WAN1_ISP_DNS_TYPE_TOK            "isp1_dns_type"
#define WAN1_ISP_IP_TOK                  "isp1_ip"
#define WAN1_ISP_MASK_TOK                "isp1_mask"
#define WAN1_ISP_DNS1_TOK                "isp1_dns1"
#define WAN1_ISP_DNS2_TOK                "isp1_dns2"
#define WAN1_ISP_PPP_TYPE_TOK            "isp1_ppptype"
#define WAN1_ISP_AUTH_TOK                "isp1_authtype"


#ifdef HAS_WAN2_DEV
#define WAN2_ISP_USER_TOK                "isp2_user"
#define WAN2_ISP_PASS_TOK                "isp2_pass"
#define WAN2_ISP_TYPE_TOK                "isp2_type"
#define WAN2_ISP_CONN_TYPE_TOK           "isp2_conntype"
#define WAN2_ISP_MAX_IDLETIME_TOK        "isp2_maxidletime"
#define WAN2_ISP_MTU_TOK                 "isp2_mtu"
#define WAN2_ISP_SERVICENAME_TOK         "isp2_service"
#define WAN2_ISP_DNS_TYPE_TOK            "isp2_dns_type"
#define WAN2_ISP_IP_TOK                  "isp2_ip"
#define WAN2_ISP_MASK_TOK                "isp2_mask"
#define WAN2_ISP_DNS1_TOK                "isp2_dns1"
#define WAN2_ISP_DNS2_TOK                "isp2_dns2"
#define WAN2_ISP_PPP_TYPE_TOK            "isp2_ppptype"
#define WAN2_ISP_AUTH_TOK                "isp2_authtype"
#endif
#endif
/*------ PPTP ----------------------------------------*/
#if HAS_WAN_PPTP
#define WAN1_PPTP_USER_TOK               "pptp1_user"
#define WAN1_PPTP_PASS_TOK               "pptp1_pass"
#define WAN1_PPTP_CONN_TYPE_TOK          "pptp1_conntype"
#define WAN1_PPTP_MAX_IDLETIME_TOK       "pptp1_maxidletime"
#define WAN1_PPTP_MTU_TOK                "pptp1_mtu"
#define WAN1_PPTP_SRV_IP_TOK             "pptp1_srvip"
#define WAN1_PPTP_SERVICENAME_TOK        "pptp1_service"
#define WAN1_PPTP_TYPE_TOK               "pptp1_type"
#define WAN1_PPTP_IPADDR_TOK             "pptp1_ip"
#define WAN1_PPTP_MASK_TOK               "pptp1_mask"
#define WAN1_PPTP_GATEWAYIP_TOK          "pptp1_gateway"
#define WAN1_PPTP_DNS_TYPE_TOK           "pptp1_dns_type"
#define WAN1_PPTP_DNS1_TOK               "pptp1_dns1"
#define WAN1_PPTP_DNS2_TOK               "pptp1_dns2"
#define WAN1_PPTP_REMOTE_DNS_TOK         "pptp1_rdns"
#define WAN1_PPTP_HOSTNAME_TOK           "pptp1_hostname"
#define WAN1_PPTP_CONNECTIONID_TOK       "pptp1_conId"
#define WAN1_PPTP_CLONED_MAC_TOK         "pptp1_mac"
#ifdef HAS_WAN2_DEV
#define WAN2_PPTP_USER_TOK               "pptp2_user"
#define WAN2_PPTP_PASS_TOK               "pptp2_pass"
#define WAN2_PPTP_CONN_TYPE_TOK          "pptp2_conntype"
#define WAN2_PPTP_MAX_IDLETIME_TOK       "pptp2_maxidletime"
#define WAN2_PPTP_MTU_TOK                "pptp2_mtu"
#define WAN2_PPTP_SRV_IP_TOK             "pptp2_srvip"
#define WAN2_PPTP_SERVICENAME_TOK        "pptp2_service"
#define WAN2_PPTP_TYPE_TOK               "pptp2_type"
#define WAN2_PPTP_IPADDR_TOK             "pptp2_ip"
#define WAN2_PPTP_MASK_TOK               "pptp2_mask"
#define WAN2_PPTP_GATEWAYIP_TOK          "pptp2_gateway"
#define WAN2_PPTP_DNS_TYPE_TOK           "pptp2_dns_type"
#define WAN2_PPTP_DNS1_TOK               "pptp2_dns1"
#define WAN2_PPTP_DNS2_TOK               "pptp2_dns2"
#define WAN2_PPTP_REMOTE_DNS_TOK         "pptp2_rdns"
#define WAN2_PPTP_HOSTNAME_TOK           "pptp2_hostname"
#define WAN2_PPTP_CONNECTIONID_TOK       "pptp2_conId"
#define WAN2_PPTP_CLONED_MAC_TOK         "pptp2_mac"
#endif

#if HAS_RUSSIAN_DUAL_ACCESS
#define WAN1_PPTP_RU_USER_TOK            "pptp1ru_user"
#define WAN1_PPTP_RU_PASS_TOK            "pptp1ru_pass"
#define WAN1_PPTP_RU_CONN_TYPE_TOK       "pptp1ru_conntype"
#define WAN1_PPTP_RU_MAX_IDLETIME_TOK    "pptp1ru_maxidtime"
#define WAN1_PPTP_RU_MTU_TOK             "pptp1ru_mtu"
#define WAN1_PPTP_RU_SRV_IP_TOK          "pptp1ru_srvip"
#define WAN1_PPTP_RU_SERVICENAME_TOK     "pptp1ru_service"
#define WAN1_PPTP_RU_TYPE_TOK            "pptp1ru_type"
#define WAN1_PPTP_RU_IPADDR_TOK          "pptp1ru_ip"
#define WAN1_PPTP_RU_MASK_TOK            "pptp1ru_mask"
#define WAN1_PPTP_RU_GATEWAYIP_TOK       "pptp1ru_gateway"
#define WAN1_PPTP_RU_DNS_TYPE_TOK        "pptp1ru_dns_type"
#define WAN1_PPTP_RU_DNS1_TOK            "pptp1ru_dns1"
#define WAN1_PPTP_RU_DNS2_TOK            "pptp1ru_dns2"
#define WAN1_PPTP_RU_HOSTNAME_TOK        "pptp1ru_hostname"
#define WAN1_PPTP_RU_CONNECTIONID_TOK    "pptp1ru_conId"
#define WAN1_PPTP_RU_CLONED_MAC_TOK      "pptp1ru_mac"
#endif
#endif

#if HAS_WAN_PPPOE
#if HAS_RUSSIAN_DUAL_ACCESS
#define WAN1_PPPOE_RU_USER_TOK            "pppoe1ru_user"
#define WAN1_PPPOE_RU_PASS_TOK            "pppoe1ru_pass"
#define WAN1_PPPOE_RU_CONN_TYPE_TOK       "pppoe1ru_conntype"
#define WAN1_PPPOE_RU_MAX_IDLETIME_TOK    "pppoe1ru_maxidtime"
#define WAN1_PPPOE_RU_MTU_TOK             "pppoe1ru_mtu"
#define WAN1_PPPOE_RU_SRV_IP_TOK          "pppoe1ru_srvip"
#define WAN1_PPPOE_RU_SERVICENAME_TOK     "pppoe1ru_service"
#define WAN1_PPPOE_RU_TYPE_TOK            "pppoe1ru_type"
#define WAN1_PPPOE_RU_IPADDR_TOK          "pppoe1ru_ip"
#define WAN1_PPPOE_RU_MASK_TOK            "pppoe1ru_mask"
#define WAN1_PPPOE_RU_GATEWAYIP_TOK       "pppoe1ru_gateway"
#define WAN1_PPPOE_RU_DNS_TYPE_TOK        "pppoe1ru_dns_type"
#define WAN1_PPPOE_RU_DNS1_TOK            "pppoe1ru_dns1"
#define WAN1_PPPOE_RU_DNS2_TOK            "pppoe1ru_dns2"
#define WAN1_PPPOE_RU_HOSTNAME_TOK        "pppoe1ru_hostname"
#define WAN1_PPPOE_RU_CONNECTIONID_TOK    "pppoe1ru_conId"
#define WAN1_PPPOE_RU_CLONED_MAC_TOK      "pppoe1ru_mac"
#define WAN1_PPPOE_RU_PPP_IPADDR_TOK      "pppoe1ru_pppip"
#define WAN1_PPPOE_RU_PPP_MASK_TOK        "pppoe1ru_pppmask"
#define WAN1_PPPOE_RU_PPP_GATEWAYIP_TOK   "pppoe1ru_pppgw"
#define WAN1_PPPOE_RU_PPP_DNS_TYPE_TOK    "pppoe1ru_pppdtype"
#define WAN1_PPPOE_RU_PPP_DNS1_TOK        "pppoe1ru_pppdns1"
#define WAN1_PPPOE_RU_PPP_DNS2_TOK        "pppoe1ru_pppdns2"
#define WAN1_PPPOE_RU_PPP_TYPE_TOK        "pppoe1ru_ppptype"
#endif
#endif

/*------ L2TP ----------------------------------------*/
#if HAS_WAN_L2TP
#define WAN1_L2TP_USER_TOK               "l2tp1_user"
#define WAN1_L2TP_PASS_TOK               "l2tp1_pass"
#define WAN1_L2TP_CONN_TYPE_TOK          "l2tp1_conntype"
#define WAN1_L2TP_MAX_IDLETIME_TOK       "l2tp1_maxidletime"
#define WAN1_L2TP_MTU_TOK                "l2tp1_mtu"
#define WAN1_L2TP_SRV_IP_TOK             "l2tp1_srvip"
#define WAN1_L2TP_SERVICENAME_TOK        "l2tp1_service"
#define WAN1_L2TP_TYPE_TOK               "l2tp1_type"
#define WAN1_L2TP_IPADDR_TOK             "l2tp1_ip"
#define WAN1_L2TP_MASK_TOK               "l2tp1_mask"
#define WAN1_L2TP_GATEWAYIP_TOK          "l2tp1_gateway"
#define WAN1_L2TP_DNS_TYPE_TOK           "l2tp1_dns_type"
#define WAN1_L2TP_DNS1_TOK               "l2tp1_dns1"
#define WAN1_L2TP_DNS2_TOK               "l2tp1_dns2"
#define WAN1_L2TP_REMOTE_DNS_TOK         "l2tp1_rdns"
#define WAN1_L2TP_HOSTNAME_TOK           "l2tp1_hostname"
#define WAN1_L2TP_CLONED_MAC_TOK         "l2tp1_mac"
#ifdef HAS_WAN2_DEV
#define WAN2_L2TP_USER_TOK               "l2tp2_user"
#define WAN2_L2TP_PASS_TOK               "l2tp2_pass"
#define WAN2_L2TP_CONN_TYPE_TOK          "l2tp2_conntype"
#define WAN2_L2TP_MAX_IDLETIME_TOK       "l2tp2_maxidletime"
#define WAN2_L2TP_MTU_TOK                "l2tp2_mtu"
#define WAN2_L2TP_SRV_IP_TOK             "l2tp2_srvip"
#define WAN2_L2TP_SERVICENAME_TOK        "l2tp2_service"
#define WAN2_L2TP_TYPE_TOK               "l2tp2_type"
#define WAN2_L2TP_IPADDR_TOK             "l2tp2_ip"
#define WAN2_L2TP_MASK_TOK               "l2tp2_mask"
#define WAN2_L2TP_GATEWAYIP_TOK          "l2tp2_gateway"
#define WAN2_L2TP_DNS_TYPE_TOK           "l2tp2_dns_type"
#define WAN2_L2TP_DNS1_TOK               "l2tp2_dns1"
#define WAN2_L2TP_DNS2_TOK               "l2tp2_dns2"
#define WAN2_L2TP_REMOTE_DNS_TOK         "l2tp2_rdns"
#define WAN2_L2TP_HOSTNAME_TOK           "l2tp2_hostname"
#define WAN2_L2TP_CLONED_MAC_TOK         "l2tp2_mac"
#endif
#endif

/*------ WIMAX ----------------------------------------*/
#if HAS_WAN_WIMAX
#define WAN1_WIMAX_CLONED_MAC_TOK        "wimax1_cloned_mac"
#define WAN1_WIMAX_HOST_TOK              "wimax1_hostname"
#define WAN1_WIMAX_DNS_TYPE_TOK          "wimax1_dnstype"
#define WAN1_WIMAX_MTU_TOK               "wimax1_mtu"
#define WAN1_WIMAX_OUTSIDE_TOK           "wimax1_out"
#define WAN1_WIMAX_CONN_TYPE_TOK         "wimax1_conn"
#endif

/*------ XGP ----------------------------------------*/
#if HAS_WAN_XGP
#define WAN1_XGP_PLUG_TOK                "xgp1_plug"
#define WAN1_XGP_CLONED_MAC_TOK          "xgp1_cloned_mac"
#define WAN1_XGP_HOST_TOK                "xgp1_hostname"
#define WAN1_XGP_DNS_TYPE_TOK            "xgp1_dnstype"
#define WAN1_XGP_MTU_TOK                 "xgp1_mtu"
#endif

#if HAS_WAN_TO_WAN_ACL
#define WAN_TO_WAN_ACL_ENABLE_TOK         "w2w_en"
#define WAN_TO_WAN_ACL_NAME_TOK           "w2w_n"
#define WAN_TO_WAN_ACL_NAME_01_TOK        "w2w_n1"
#define WAN_TO_WAN_ACL_NAME_02_TOK        "w2w_n2"
#define WAN_TO_WAN_ACL_NAME_03_TOK        "w2w_n3"
#define WAN_TO_WAN_ACL_NAME_04_TOK        "w2w_n4"
#define WAN_TO_WAN_ACL_NAME_05_TOK        "w2w_n5"
#define WAN_TO_WAN_ACL_NAME_06_TOK        "w2w_n6"
#define WAN_TO_WAN_ACL_NAME_07_TOK        "w2w_n7"
#define WAN_TO_WAN_ACL_NAME_08_TOK        "w2w_n8"
#define WAN_TO_WAN_ACL_NAME_09_TOK        "w2w_n9"
#define WAN_TO_WAN_ACL_NAME_10_TOK        "w2w_n10"
#define WAN_TO_WAN_ACL_TOK                "w2w_"
#define WAN_TO_WAN_ACL_01_TOK             "w2w_1"
#define WAN_TO_WAN_ACL_02_TOK             "w2w_2"
#define WAN_TO_WAN_ACL_03_TOK             "w2w_3"
#define WAN_TO_WAN_ACL_04_TOK             "w2w_4"
#define WAN_TO_WAN_ACL_05_TOK             "w2w_5"
#define WAN_TO_WAN_ACL_06_TOK             "w2w_6"
#define WAN_TO_WAN_ACL_07_TOK             "w2w_7"
#define WAN_TO_WAN_ACL_08_TOK             "w2w_8"
#define WAN_TO_WAN_ACL_09_TOK             "w2w_9"
#define WAN_TO_WAN_ACL_10_TOK             "w2w_10"
#endif

/* ------------------ Inbound Filter ------------------ */
#if HAS_INBOUND_FILTER
#define INBOUND_FILTER_SETTING_ENABLE_TOK         "ibf_en"
#define INBOUND_FILTER_SETTING_TOK                "ibf_setting_"
#define INBOUND_FILTER_SETTING_01_TOK             "ibf_setting_1"
#define INBOUND_FILTER_SETTING_02_TOK             "ibf_setting_2"
#define INBOUND_FILTER_SETTING_03_TOK             "ibf_setting_3"
#define INBOUND_FILTER_SETTING_04_TOK             "ibf_setting_4"
#define INBOUND_FILTER_SETTING_05_TOK             "ibf_setting_5"
#define INBOUND_FILTER_SETTING_06_TOK             "ibf_setting_6"
#define INBOUND_FILTER_SETTING_07_TOK             "ibf_setting_7"
#define INBOUND_FILTER_SETTING_08_TOK             "ibf_setting_8"
#define INBOUND_FILTER_SETTING_09_TOK             "ibf_setting_9"
#define INBOUND_FILTER_SETTING_10_TOK             "ibf_setting_10"
#define INBOUND_FILTER_START_IP_ADDRESS_TOK       "ibf_start_ip_"
#define INBOUND_FILTER_START_IP_ADDRESS_01_TOK    "ibf_start_ip_1"
#define INBOUND_FILTER_START_IP_ADDRESS_02_TOK    "ibf_start_ip_2"
#define INBOUND_FILTER_START_IP_ADDRESS_03_TOK    "ibf_start_ip_3"
#define INBOUND_FILTER_START_IP_ADDRESS_04_TOK    "ibf_start_ip_4"
#define INBOUND_FILTER_START_IP_ADDRESS_05_TOK    "ibf_start_ip_5"
#define INBOUND_FILTER_START_IP_ADDRESS_06_TOK    "ibf_start_ip_6"
#define INBOUND_FILTER_START_IP_ADDRESS_07_TOK    "ibf_start_ip_7"
#define INBOUND_FILTER_START_IP_ADDRESS_08_TOK    "ibf_start_ip_8"
#define INBOUND_FILTER_START_IP_ADDRESS_09_TOK    "ibf_start_ip_9"
#define INBOUND_FILTER_START_IP_ADDRESS_10_TOK    "ibf_start_ip_10"
#define INBOUND_FILTER_END_IP_ADDRESS_TOK         "ibf_end_ip_"
#define INBOUND_FILTER_END_IP_ADDRESS_01_TOK      "ibf_end_ip_1"
#define INBOUND_FILTER_END_IP_ADDRESS_02_TOK      "ibf_end_ip_2"
#define INBOUND_FILTER_END_IP_ADDRESS_03_TOK      "ibf_end_ip_3"
#define INBOUND_FILTER_END_IP_ADDRESS_04_TOK      "ibf_end_ip_4"
#define INBOUND_FILTER_END_IP_ADDRESS_05_TOK      "ibf_end_ip_5"
#define INBOUND_FILTER_END_IP_ADDRESS_06_TOK      "ibf_end_ip_6"
#define INBOUND_FILTER_END_IP_ADDRESS_07_TOK      "ibf_end_ip_7"
#define INBOUND_FILTER_END_IP_ADDRESS_08_TOK      "ibf_end_ip_8"
#define INBOUND_FILTER_END_IP_ADDRESS_09_TOK      "ibf_end_ip_9"
#define INBOUND_FILTER_END_IP_ADDRESS_10_TOK      "ibf_end_ip_10"
#define INBOUND_FILTER_WAN_PING_TOK				  "ibf_wan_ping"
#define INBOUND_FILTER_REMOTE_ADMIN_TOK			  "ibf_remote_admin"
#endif

/* ------------------   DMZ ------------------------------------------*/
#define FIREWALL_ENABLE_TOK		 "firewall_enable"
#if HAS_FIREWALL_LEVEL
#define FIREWALL_LEVEL_TOK		 "firewall_level"
#endif
#define DMZ_ENABLE_TOK                   "dmz_status"
#define DMZ_IP_TOK                       "dmz_ip"
#define DMZ_HOST_IP_TOK                  "dmz_host_ip_"
#define DMZ_HOST_IP_01_TOK               "dmz_host_ip_1"
#define DMZ_HOST_IP_02_TOK               "dmz_host_ip_2"
#define DMZ_HOST_IP_03_TOK               "dmz_host_ip_3"
#define DMZ_HOST_IP_04_TOK               "dmz_host_ip_4"
#define DMZ_HOST_IP_05_TOK               "dmz_host_ip_5"

/* ------------------   Multi DMZ ------------------------------------------*/
#if HAS_MULTIDMZ_SUPPORT
#define DMZ_MULTI_ENABLE_TOK             "dmz_mstatus"
#define DMZ_MULTI_HOST_IP_TOK        	 "dmz_mhost_ip_"
#define DMZ_MULTI_HOST_IP_01_TOK         "dmz_mhost_ip_1"
#define DMZ_MULTI_HOST_IP_02_TOK         "dmz_mhost_ip_2"
#define DMZ_MULTI_HOST_IP_03_TOK         "dmz_mhost_ip_3"
#define DMZ_MULTI_HOST_IP_04_TOK         "dmz_mhost_ip_4"
#define DMZ_MULTI_HOST_IP_05_TOK         "dmz_mhost_ip_5"
#endif

/*DMZ*/
#if HAS_DMZ_IF_FUNCTION
#define DMZ_IF_NAME_TOK                    "dmz_iface"
#define DMZ_IF_IP_TOK                      "dmz_iface_ip"
#define DMZ_HOST1_PORT_TOK                 "dmz1_port1"
#define DMZ_HOST2_PORT_TOK                 "dmz2_port2"
#define DMZ_HOST3_PORT_TOK                 "dmz3_port3"
#define DMZ_HOST4_PORT_TOK                 "dmz4_port4"
#define DMZ_HOST5_PORT_TOK                 "dmz5_port5"
#define DMZ_HOST1_IP_TOK                   "dmz1_ip"
#define DMZ_HOST2_IP_TOK                   "dmz2_ip"
#define DMZ_HOST3_IP_TOK                   "dmz3_ip"
#define DMZ_HOST4_IP_TOK                   "dmz4_ip"
#define DMZ_HOST5_IP_TOK                   "dmz5_ip"
#endif
/* ------------------   DNS ------------------------------------------*/
#define WAN1_DHCP_DNS_TYPE_TOK           "wan1_dhcp_dnstype"
#define WAN1_DHCP_DNS1_TOK               "wan1_dhcp_dns1"
#define WAN1_DHCP_DNS2_TOK               "wan1_dhcp_dns2"
#define WAN1_DNS_TOK                     "wan1_dns"  //jaykung 060413
#define WAN1_DNS1_TOK                    "wan1_dns1"
#define WAN1_DNS2_TOK                    "wan1_dns2"
#define WAN1_DNS3_TOK                    "wan1_dns3"
#define WAN1_DNS4_TOK                    "wan1_dns4"
#define WAN1_DNS1_STATIC_TOK                    "wan1_dns1_static"
#define WAN1_DNS2_STATIC_TOK                    "wan1_dns2_static"
#ifdef HAS_WAN2_DEV
#define WAN2_DHCP_DNS_TYPE_TOK           "wan2_dhcp_dnstype"
#define WAN2_DHCP_DNS1_TOK               "wan2_dhcp_dns1"
#define WAN2_DHCP_DNS2_TOK               "wan2_dhcp_dns2"
#define WAN2_DNS_TOK                     "wan2_dns"  //jaykung 060413
#define WAN2_DNS1_TOK                    "wan2_dns1"
#define WAN2_DNS2_TOK                    "wan2_dns2"
#define WAN2_DNS3_TOK                    "wan2_dns3"
#endif
/* ------------------   QoS (tc) -----------------------------------------*/
#define WAN1_QOS_ENABLE_TOK              "wan1_qos_enable"
#define WAN1_QOS_TYPE_TOK                "wan1_qos_type"
#define WAN1_UPLINK_BANDWIDTH_TOK        "wan1_ul_bw"
#define WAN1_DOWNLINK_BANDWIDTH_TOK      "wan1_dl_bw"
#ifdef HAS_WAN2_DEV
#define WAN2_QOS_ENABLE_TOK              "wan2_qos_enable"
#define WAN2_UPLINK_BANDWIDTH_TOK        "wan2_ul_bw"
#define WAN2_DOWNLINK_BANDWIDTH_TOK      "wan2_dl_bw"
#endif
/* ------------------ QoS (Bandwidth Allocation - Total bandwidth) --------*/
#if HAS_WAN_SPEED_DETECTION
#define WAN_SPEED_DETECTION_EN_TOK		"wanspeed_det"
#endif
#if HAS_QOS_TOTAL_BANDWIDTH_SETTING
#define QOS_UPLINK_BANDWIDTH_MEASURE_TOK		"qos_ul_measure"
#define QOS_UPLINK_BANDWIDTH_TOK		"qos_ul_bw"
#define QOS_DOWNLINK_BANDWIDTH_TOK		"qos_dl_bw"
#endif
/* ------------------ QoS (UBICOM-IP8K support) --------*/
#if HAS_SUPPORT_UBICOM_STREAMENGINE
#define QOS_STREAMENGINE_ENABLE_TOK		"qos_se_enable"
#define QOS_STREAMENGINE_AUTO_CLASSIFICATION_TOK	"qos_se_auto_class"
#define QOS_STREAMENGINE_DYNAMIC_FRAG_TOK			"qos_se_dynamicfrag"
#define QOS_STREAMENGINE_TOK			"qos_se_"
#define QOS_STREAMENGINE_01_TOK			"qos_se_1"
#define QOS_STREAMENGINE_02_TOK			"qos_se_2"		
#define QOS_STREAMENGINE_03_TOK			"qos_se_3"		
#define QOS_STREAMENGINE_04_TOK			"qos_se_4"
#define QOS_STREAMENGINE_05_TOK			"qos_se_5"
#define QOS_STREAMENGINE_06_TOK			"qos_se_6"
#define QOS_STREAMENGINE_07_TOK			"qos_se_7"
#define QOS_STREAMENGINE_08_TOK			"qos_se_8"
#endif
/*------ WLAN QoS (using WMM) -----------------------------*/
#if HAS_WLAN_WMM_QOS
#define WMM_QOS_POLICY_TOK               "wmm_qos_policy"
#define WMM_QOS_RULES_TOK                "wmm_qos_r_"
#define WMM_QOS_RULES_01_TOK             "wmm_qos_r_1"
#define WMM_QOS_RULES_02_TOK             "wmm_qos_r_2"
#define WMM_QOS_RULES_03_TOK             "wmm_qos_r_3"
#define WMM_QOS_RULES_04_TOK             "wmm_qos_r_4"
#define WMM_QOS_RULES_05_TOK             "wmm_qos_r_5"
#define WMM_QOS_RULES_06_TOK             "wmm_qos_r_6"
#define WMM_QOS_RULES_07_TOK             "wmm_qos_r_7"
#define WMM_QOS_RULES_08_TOK             "wmm_qos_r_8"
#define WMM_QOS_RULES_09_TOK             "wmm_qos_r_9"
#define WMM_QOS_RULES_10_TOK             "wmm_qos_r_10"
#define WMM_QOS_RULES_11_TOK             "wmm_qos_r_11"
#define WMM_QOS_RULES_12_TOK             "wmm_qos_r_12"
#define WMM_QOS_RULES_13_TOK             "wmm_qos_r_13"
#define WMM_QOS_RULES_14_TOK             "wmm_qos_r_14"
#define WMM_QOS_RULES_15_TOK             "wmm_qos_r_15"
#define WMM_QOS_RULES_16_TOK             "wmm_qos_r_16"
#endif
/* ------------------   Qos For different port-------------------------*/
#define PORT_QOS_ENABLE_TOK              "port_qos_enable"
#define PORT_QOS_TOK                     "portqos_a_" 
#define PORT_QOS_01_TOK                  "portqos_a_1" 
#define PORT_QOS_02_TOK                  "portqos_a_2" 
#define PORT_QOS_03_TOK                  "portqos_a_3" 
#define PORT_QOS_04_TOK                  "portqos_a_4" 
#define PORT_QOS_05_TOK                  "portqos_a_5"
#define PORT_QOS_06_TOK                  "portqos_a_6" 
#define PORT_QOS_07_TOK                  "portqos_a_7" 
#define PORT_QOS_08_TOK                  "portqos_a_8" 
#if NUM_PORT_QOS > 8
#define PORT_QOS_09_TOK                  "portqos_a_9" 
#define PORT_QOS_10_TOK                  "portqos_a_10"
#define PORT_QOS_11_TOK                  "portqos_a_11" 
#define PORT_QOS_12_TOK                  "portqos_a_12" 
#define PORT_QOS_13_TOK                  "portqos_a_13" 
#define PORT_QOS_14_TOK                  "portqos_a_14" 
#define PORT_QOS_15_TOK                  "portqos_a_15" 
#define PORT_QOS_16_TOK                  "portqos_a_16" 
#endif
#define PORT_QOS_B_TOK					 "portqos_b_"
#define PORT_QOS_B_01_TOK                "portqos_b_1" 
#define PORT_QOS_B_02_TOK                "portqos_b_2" 
#define PORT_QOS_B_03_TOK                "portqos_b_3" 
#define PORT_QOS_B_04_TOK                "portqos_b_4" 
#define PORT_QOS_B_05_TOK                "portqos_b_5" 
#define PORT_QOS_B_06_TOK                "portqos_b_6" 
#define PORT_QOS_B_07_TOK                "portqos_b_7" 
#define PORT_QOS_B_08_TOK                "portqos_b_8" 
#define PORT_QOS_B_09_TOK                "portqos_b_9" 
#define PORT_QOS_B_10_TOK                "portqos_b_10"
#if NUM_PORT_QOS > 10
#define PORT_QOS_B_11_TOK                "portqos_b_11" 
#define PORT_QOS_B_12_TOK                "portqos_b_12" 
#define PORT_QOS_B_13_TOK                "portqos_b_13" 
#define PORT_QOS_B_14_TOK                "portqos_b_14" 
#define PORT_QOS_B_15_TOK                "portqos_b_15" 
#define PORT_QOS_B_16_TOK                "portqos_b_16" 
#endif
/* ------------------   Qos For Priority Queue -------------------------*/
#if HAS_QOS_PRIO_QUEUE
#define PRIO_QOS_ENABLE_TOK              "prio_qos_enable"
#define PRIO_QOS_UNLIMIT_01_TOK          "prioqos_ul_1"
#define PRIO_QOS_TOK                     "prioqos_a_" 
#define PRIO_QOS_01_TOK                  "prioqos_a_1" 
#define PRIO_QOS_02_TOK                  "prioqos_a_2" 
#define PRIO_QOS_03_TOK                  "prioqos_a_3" 
#define PRIO_QOS_04_TOK                  "prioqos_a_4" 
#define PRIO_QOS_05_TOK                  "prioqos_a_5"
#define PRIO_QOS_06_TOK                  "prioqos_a_6" 
#define PRIO_QOS_07_TOK                  "prioqos_a_7"
#define PRIO_QOS_08_TOK                  "prioqos_a_8" 
#if NUM_QOS_PRIORITY > 8
#define PRIO_QOS_09_TOK                  "prioqos_a_9"
#define PRIO_QOS_10_TOK                  "prioqos_a_10" 
#define PRIO_QOS_11_TOK                  "prioqos_a_11"
#define PRIO_QOS_12_TOK                  "prioqos_a_12" 
#endif
#if HAS_QOS_ADV_PRIO_QUEUE
#define PRIO_QOS_ADV_TOK                 "priqos_adv_" 
#define PRIO_QOS_ADV_01_TOK				 "priqos_adv_1"
#define PRIO_QOS_ADV_02_TOK				 "priqos_adv_2"
#define PRIO_QOS_ADV_03_TOK				 "priqos_adv_3"
#define PRIO_QOS_ADV_04_TOK				 "priqos_adv_4"
#define PRIO_QOS_ADV_05_TOK				 "priqos_adv_5"
#define PRIO_QOS_ADV_06_TOK				 "priqos_adv_6"
#endif
#endif
#if FOR_ZYXEL_NEW_GUI
#define QOS_PRIORITY_TOK				 "qos_priority"
#define QOS_GAME_ENGINE_TOK				 "qos_gameengine"
#endif

/* ------------------   Qos For IP Limit Queue -------------------------*/
#if HAS_QOS_IP_LIMIT_QUEUE
#define IP_LIMIT_QOS_ENABLE_TOK          "ip_qos_enable"
#define IP_LIMIT_QOS_UL_BW_TOK           "ip_qos_ul_bw"
#define IP_LIMIT_QOS_DL_BW_TOK           "ip_qos_dl_bw"
#endif

/* ------------------   Qos For different HW port-------------------------*/
#if HAS_QOS_HWPORT
#define QOS_HWPORT_ENABLE_TOK              "hwport_qos_enable"
#define QOS_HWPORT_TOK                     "hwportqos_"
#define QOS_HWPORT_01_TOK                  "hwportqos_1"
#define QOS_HWPORT_02_TOK                  "hwportqos_2"
#define QOS_HWPORT_03_TOK                  "hwportqos_3"
#define QOS_HWPORT_04_TOK                  "hwportqos_4"
#define QOS_HWPORT_05_TOK                  "hwportqos_5"
#endif
/* ------------------   VPN Server: PPTPD -------------------------*/
#define PPTPD_ENABLE_TOK                 "pptpd_enable"
#define PPTPD_START_TOK                  "pptpd_start"
#define PPTPD_END_TOK                    "pptpd_end"
/* ------------------   WAN 3G SETTING: 3G -------------------------*/
#if HAS_WAN_3G
#define WAN1_3G_ISPCARD_TOK              "wan1_3g_ispcard"
#define WAN1_3G_COUNTRY_TOK              "wan1_3g_country"
#define WAN1_3G_SERVICE_TOK              "wan1_3g_ispservice"
#if HAS_IODATA_3G
#define WAN1_3G_AUTO_SETTING_TOK         "wan1_3g_io_autoset"
#endif
#define WAN1_3G_SYSTEM_TYPE_TOK          "wan1_3g_sys_type"
#define WAN1_3G_AUTH_TOK                 "wan1_3g_auth"
#define WAN1_3G_APN_TOK                  "wan1_3g_apn"    
#define WAN1_3G_PHONE_TOK                "wan1_3g_phone"    
#define WAN1_3G_USER_TOK                 "wan1_3g_user"    
#define WAN1_3G_PASS_TOK                 "wan1_3g_pwd"    
#define WAN1_3G_PINCODE_TOK              "wan1_3g_pincode"    
#define WAN1_3G_MTU_TOK                  "wan1_3g_mtu"
#define WAN1_3G_SERVICENAME_TOK          "wan1_3g_service"    
#define WAN1_3G_CONN_TYPE_TOK            "wan1_3g_conntype"    
#define WAN1_3G_MAX_IDLETIME_TOK         "wan1_3g_maxidletime"
#if HAS_WAN_SUPPORT_MAX_CONN_TIME
#define WAN1_3G_MAX_CONNTIME_TOK         "wan1_3g_maxconntime"
#endif
#if HAS_WAN_3G_BAND_SELECTION
#define WAN1_3G_BAND_TOK                 "wan1_3g_band"
#endif
#define WAN1_3G_SIM_STATUS_TOK           "wan1_3g_sim"
#define WAN1_3G_SUPPORT_AUTO_TOK         "wan1_3g_suppauto"
#if HAS_WAN_3G_AUTOMOUNT
#define WAN1_3G_AUTO_MOUNT_TOK           "wan1_3g_auto_mount"
#endif

#ifdef HAS_WAN2_DEV
#define WAN2_3G_ISPCARD_TOK              "wan2_3g_ispcard"
#define WAN2_3G_COUNTRY_TOK              "wan2_3g_country"
#define WAN2_3G_SERVICE_TOK              "wan2_3g_ispservice"
#if HAS_IODATA_3G
#define WAN2_3G_AUTO_SETTING_TOK         "wan2_3g_io_autoset"
#endif
#define WAN2_3G_SYSTEM_TYPE_TOK          "wan2_3g_sys_type"
#define WAN2_3G_AUTH_TOK                 "wan2_3g_auth"
#define WAN2_3G_APN_TOK                  "wan2_3g_apn"    
#define WAN2_3G_PHONE_TOK                "wan2_3g_phone"    
#define WAN2_3G_USER_TOK                 "wan2_3g_user"    
#define WAN2_3G_PASS_TOK                 "wan2_3g_pwd"    
#define WAN2_3G_PINCODE_TOK              "wan2_3g_pincode"    
#define WAN2_3G_MTU_TOK                  "wan2_3g_mtu"
#define WAN2_3G_SERVICENAME_TOK          "wan2_3g_service"    
#define WAN2_3G_CONN_TYPE_TOK            "wan2_3g_conntype"    
#define WAN2_3G_MAX_IDLETIME_TOK         "wan2_3g_maxidletime"
#if HAS_WAN_SUPPORT_MAX_CONN_TIME
#define WAN2_3G_MAX_CONNTIME_TOK         "wan2_3g_maxconntime"
#endif
#if HAS_WAN_3G_BAND_SELECTION
#define WAN2_3G_BAND_TOK                 "wan2_3g_band"
#endif
#define WAN2_3G_SIM_STATUS_TOK           "wan2_3g_sim"
#define WAN2_3G_SUPPORT_AUTO_TOK         "wan2_3g_suppauto"
#if HAS_WAN_3G_AUTOMOUNT
#define WAN2_3G_AUTO_MOUNT_TOK           "wan2_3g_auto_mount"
#endif
#endif
#endif /* HAS_WAN_3G */

#if HAS_WAN_3G || HAS_WAN_XGP
#define WAN1_3G_PLUG_TOK                 "wan1_3g_plug"
#define WAN1_3G_REFRESH_INFO_TOK         "wan1_3g_refresh"
#ifdef HAS_WAN2_DEV
#define WAN2_3G_PLUG_TOK                 "wan2_3g_plug"
#define WAN2_3G_REFRESH_INFO_TOK         "wan2_3g_refresh"
#endif
#endif
#if HAS_KCODES_NETUSB
#define USB_OP_MODE_TOK                  "usb_opmode"
#endif
#if HAS_KCODES_FUNCTION
#define KC_USB_MODE_TOK                  "kc_usb_mode"
#if HAS_KCODES_SMB
#define KCSMB_COMPUTER_NAME_TOK          "kcsmb_pc_name"
#define KCSMB_WORKGROUP_NAME_TOK         "kcsmb_group_name"
#define KCSMB_ADMIN_USERNAME_TOK         "kcsmb_admin_user"
#define KCSMB_ADMIN_PASSWORD_TOK         "kcsmb_admin_pwd"
#define KCSMB_DESCRIPTION_TOK            "kcsmb_description"
#endif
#endif
#if HAS_SAMBA
#define SAMBA_ENABLE_TOK                 "smb_enable"
#define SAMBA_NETBIOS_NAME_TOK           "smb_netbios_name"
#define SAMBA_WORKGROUP_NAME_TOK         "smb_workgroup_name"
#define SAMBA_SERVER_NAME_TOK            "smb_server_name"
#define SAMBA_AUTH_ENABLE_TOK            "smb_auth_enable"
#define SAMBA_ADMIN_USERNAME_TOK         "smb_admin_user"
#define SAMBA_ADMIN_PASSWORD_TOK         "smb_admin_pwd"
#define SAMBA_ACCESS_TYPE_TOK            "smb_access_type"
#endif

#define EZSETUP_HTTP_REDIRECT_TOK		 "ez_http_redirect"
/* ------------------   ALG (Application Level Gateway) ip_nat_*.ko & ip_conntrack_*.ko -*/
#if FOR_ZYXEL
#define ALG_SUPPORT_TOK                 "alg_support2"
#else
#define ALG_SUPPORT_TOK                  "alg_support"
#endif
#define ALG_IPSEC_TOK                    "alg_ipsec"
#define ALG_PPTP_TOK                     "alg_pptp"
#define ALG_L2TP_TOK                     "alg_l2tp"
#define ALG_MMS_TOK                      "alg_mms"
#define ALG_SNMP_TOK                     "alg_snmp"
#define ALG_FTP_TOK                      "alg_ftp"
/* ------------------   Others ---------------------------------------*/
#define WAN_BLOCK_ENABLE_TOK             "wan_block"
#define WAN_IPSEC_PASS_ENABLE_TOK        "wan_ipsec_pass"
#define WAN_L2TP_PASS_ENABLE_TOK         "wan_l2tp_pass"
#define WAN_PPTP_PASS_ENABLE_TOK         "wan_pptp_pass"
#if HAS_SPECIAL_PASS_THROUGH
#define WAN_PPPOE_PASS_ENABLE_TOK        "wan_pppoe_pass"
#define WAN_IPV6_PASS_ENABLE_TOK         "wan_ipv6_pass"
#endif

#define WAN_CHECK_ENABLE_TOK             "wan_check_en"

#define UPNPD_ENABLE_TOK                 "upnpd_enable"
#define UPNPD_PORT_MAP_ENABLE_TOK        "upnpd_pmap_enable"
#if HAS_PNPX_FUNCTION
#define PNPX_ENABLE_TOK					 "pnpx_enable"
#endif

#if 1
#define WAN_DEV_TOK                      WAN1_DEV_TOK
#define WAN_PHYDEV_TOK                   WAN1_PHYDEV_TOK

#define WAN_CONNECTION_TYPE_TOK          WAN1_CONNECTION_TYPE_TOK
#define WAN_CLONED_MAC_TOK               WAN1_CLONED_MAC_TOK
#define WAN_HOST_TOK			         WAN1_HOST_TOK
/* ------------------   Static IP -------------------------------------*/
#define WAN_IPADDR_TOK                   WAN1_IPADDR_TOK
#define WAN_MASK_TOK                     WAN1_MASK_TOK
#define WAN_GATEWAYIP_TOK                WAN1_GATEWAYIP_TOK
/* ------------------   PPPoE ----------------------------------------*/
#define ISP_USER_TOK                     WAN1_ISP_USER_TOK
#define ISP_PASS_TOK                     WAN1_ISP_PASS_TOK
#define ISP_MAX_IDLETIME_TOK             WAN1_ISP_MAX_IDLETIME_TOK
#define ISP_MTU_TOK                      WAN1_ISP_MTU_TOK
#define ISP_SERVICENAME_TOK              WAN1_ISP_SERVICENAME_TOK
/* ------------------   DMZ ------------------------------------------*/
/* ------------------   DNS ------------------------------------------*/
#define WAN_DNS_TOK                      WAN1_DNS_TOK
#define WAN_DNS1_TOK                     WAN1_DNS1_TOK
#define WAN_DNS2_TOK                     WAN1_DNS2_TOK
#define WAN_DNS3_TOK                     WAN1_DNS3_TOK
/* ------------------   QoS (tc) -----------------------------------------*/
#define WAN_QOS_ENABLE_TOK               WAN1_QOS_ENABLE_TOK
#define WAN_UPLINK_BANDWIDTH_TOK         WAN1_UPLINK_BANDWIDTH_TOK
#define WAN_DOWNLINK_BANDWIDTH_TOK       WAN1_DOWNLINK_BANDWIDTH_TOK
#endif
/* ------------------   LAN MAC Filtering   -----------------------*/
/*Since the "MACFILTER" is already used by wireless lan, we can only use "LANMACFILTER" */
#define LANMACFILTER_ENABLE_TOK          "lanmacfilter_enable"
#define LANMACFILTER_MODE_TOK            "lanmacfilter_mode"
#define LANMACFILTER_TOK                 "lanmacfilter_"
#define LANMACFILTER_01_TOK              "lanmacfilter_1"
#define LANMACFILTER_02_TOK              "lanmacfilter_2"
#define LANMACFILTER_03_TOK              "lanmacfilter_3"
#define LANMACFILTER_04_TOK              "lanmacfilter_4"
#define LANMACFILTER_05_TOK              "lanmacfilter_5"
#define LANMACFILTER_06_TOK              "lanmacfilter_6"
#define LANMACFILTER_07_TOK              "lanmacfilter_7"
#define LANMACFILTER_08_TOK              "lanmacfilter_8"
#define LANMACFILTER_09_TOK              "lanmacfilter_9"
#define LANMACFILTER_10_TOK              "lanmacfilter_10"
#if NUM_LAN_MAC_FILTERS > 10
#define LANMACFILTER_11_TOK              "lanmacfilter_11"
#define LANMACFILTER_12_TOK              "lanmacfilter_12"
#define LANMACFILTER_13_TOK              "lanmacfilter_13"
#define LANMACFILTER_14_TOK              "lanmacfilter_14"
#define LANMACFILTER_15_TOK              "lanmacfilter_15"
#define LANMACFILTER_16_TOK              "lanmacfilter_16"
#define LANMACFILTER_17_TOK              "lanmacfilter_17"
#define LANMACFILTER_18_TOK              "lanmacfilter_18"
#define LANMACFILTER_19_TOK              "lanmacfilter_19"
#define LANMACFILTER_20_TOK              "lanmacfilter_20"
#if NUM_LAN_MAC_FILTERS > 20
#define LANMACFILTER_21_TOK              "lanmacfilter_21"
#define LANMACFILTER_22_TOK              "lanmacfilter_22"
#define LANMACFILTER_23_TOK              "lanmacfilter_23"
#define LANMACFILTER_24_TOK              "lanmacfilter_24"
#define LANMACFILTER_25_TOK              "lanmacfilter_25"
#define LANMACFILTER_26_TOK              "lanmacfilter_26"
#define LANMACFILTER_27_TOK              "lanmacfilter_27"
#define LANMACFILTER_28_TOK              "lanmacfilter_28"
#define LANMACFILTER_29_TOK              "lanmacfilter_29"
#define LANMACFILTER_30_TOK              "lanmacfilter_30"
#define LANMACFILTER_31_TOK              "lanmacfilter_31"
#define LANMACFILTER_32_TOK              "lanmacfilter_32"
#if NUM_LAN_MAC_FILTERS > 32
#define LANMACFILTER_33_TOK              "lanmacfilter_33"
#define LANMACFILTER_34_TOK              "lanmacfilter_34"
#define LANMACFILTER_35_TOK              "lanmacfilter_35"
#define LANMACFILTER_36_TOK              "lanmacfilter_36"
#define LANMACFILTER_37_TOK              "lanmacfilter_37"
#define LANMACFILTER_38_TOK              "lanmacfilter_38"
#define LANMACFILTER_39_TOK              "lanmacfilter_39"
#define LANMACFILTER_40_TOK              "lanmacfilter_40"
#define LANMACFILTER_41_TOK              "lanmacfilter_41"
#define LANMACFILTER_42_TOK              "lanmacfilter_42"
#define LANMACFILTER_43_TOK              "lanmacfilter_43"
#define LANMACFILTER_44_TOK              "lanmacfilter_44"
#define LANMACFILTER_45_TOK              "lanmacfilter_45"
#define LANMACFILTER_46_TOK              "lanmacfilter_46"
#define LANMACFILTER_47_TOK              "lanmacfilter_47"
#define LANMACFILTER_48_TOK              "lanmacfilter_48"
#define LANMACFILTER_49_TOK              "lanmacfilter_49"
#define LANMACFILTER_50_TOK              "lanmacfilter_50"
#if NUM_LAN_MAC_FILTERS > 50
#define LANMACFILTER_51_TOK              "lanmacfilter_51"
#define LANMACFILTER_52_TOK              "lanmacfilter_52"
#define LANMACFILTER_53_TOK              "lanmacfilter_53"
#define LANMACFILTER_54_TOK              "lanmacfilter_54"
#define LANMACFILTER_55_TOK              "lanmacfilter_55"
#define LANMACFILTER_56_TOK              "lanmacfilter_56"
#define LANMACFILTER_57_TOK              "lanmacfilter_57"
#define LANMACFILTER_58_TOK              "lanmacfilter_58"
#define LANMACFILTER_59_TOK              "lanmacfilter_59"
#define LANMACFILTER_60_TOK              "lanmacfilter_60"
#define LANMACFILTER_61_TOK              "lanmacfilter_61"
#define LANMACFILTER_62_TOK              "lanmacfilter_62"
#define LANMACFILTER_63_TOK              "lanmacfilter_63"
#define LANMACFILTER_64_TOK              "lanmacfilter_64"
#if NUM_LAN_MAC_FILTERS > 64
#define LANMACFILTER_65_TOK              "lanmacfilter_65"
#define LANMACFILTER_66_TOK              "lanmacfilter_66"
#define LANMACFILTER_67_TOK              "lanmacfilter_67"
#define LANMACFILTER_68_TOK              "lanmacfilter_68"
#define LANMACFILTER_69_TOK              "lanmacfilter_69"
#define LANMACFILTER_70_TOK              "lanmacfilter_70"
#define LANMACFILTER_71_TOK              "lanmacfilter_71"
#define LANMACFILTER_72_TOK              "lanmacfilter_72"
#define LANMACFILTER_73_TOK              "lanmacfilter_73"
#define LANMACFILTER_74_TOK              "lanmacfilter_74"
#define LANMACFILTER_75_TOK              "lanmacfilter_75"
#define LANMACFILTER_76_TOK              "lanmacfilter_76"
#define LANMACFILTER_77_TOK              "lanmacfilter_77"
#define LANMACFILTER_78_TOK              "lanmacfilter_78"
#define LANMACFILTER_79_TOK              "lanmacfilter_79"
#define LANMACFILTER_80_TOK              "lanmacfilter_80"
#define LANMACFILTER_81_TOK              "lanmacfilter_81"
#define LANMACFILTER_82_TOK              "lanmacfilter_82"
#define LANMACFILTER_83_TOK              "lanmacfilter_83"
#define LANMACFILTER_84_TOK              "lanmacfilter_84"
#define LANMACFILTER_85_TOK              "lanmacfilter_85"
#define LANMACFILTER_86_TOK              "lanmacfilter_86"
#define LANMACFILTER_87_TOK              "lanmacfilter_87"
#define LANMACFILTER_88_TOK              "lanmacfilter_88"
#define LANMACFILTER_89_TOK              "lanmacfilter_89"
#define LANMACFILTER_90_TOK              "lanmacfilter_90"
#define LANMACFILTER_91_TOK              "lanmacfilter_91"
#define LANMACFILTER_92_TOK              "lanmacfilter_92"
#define LANMACFILTER_93_TOK              "lanmacfilter_93"
#define LANMACFILTER_94_TOK              "lanmacfilter_94"
#define LANMACFILTER_95_TOK              "lanmacfilter_95"
#define LANMACFILTER_96_TOK              "lanmacfilter_96"
#define LANMACFILTER_97_TOK              "lanmacfilter_97"
#define LANMACFILTER_98_TOK              "lanmacfilter_98"
#define LANMACFILTER_99_TOK              "lanmacfilter_99"
#define LANMACFILTER_100_TOK             "lanmacfilter_100"
#define LANMACFILTER_101_TOK             "lanmacfilter_101"
#define LANMACFILTER_102_TOK             "lanmacfilter_102"
#define LANMACFILTER_103_TOK             "lanmacfilter_103"
#define LANMACFILTER_104_TOK             "lanmacfilter_104"
#define LANMACFILTER_105_TOK             "lanmacfilter_105"
#define LANMACFILTER_106_TOK             "lanmacfilter_106"
#define LANMACFILTER_107_TOK             "lanmacfilter_107"
#define LANMACFILTER_108_TOK             "lanmacfilter_108"
#define LANMACFILTER_109_TOK             "lanmacfilter_109"
#define LANMACFILTER_110_TOK             "lanmacfilter_110"
#define LANMACFILTER_111_TOK             "lanmacfilter_111"
#define LANMACFILTER_112_TOK             "lanmacfilter_112"
#define LANMACFILTER_113_TOK             "lanmacfilter_113"
#define LANMACFILTER_114_TOK             "lanmacfilter_114"
#define LANMACFILTER_115_TOK             "lanmacfilter_115"
#define LANMACFILTER_116_TOK             "lanmacfilter_116"
#define LANMACFILTER_117_TOK             "lanmacfilter_117"
#define LANMACFILTER_118_TOK             "lanmacfilter_118"
#define LANMACFILTER_119_TOK             "lanmacfilter_119"
#define LANMACFILTER_120_TOK             "lanmacfilter_120"
#define LANMACFILTER_121_TOK             "lanmacfilter_121"
#define LANMACFILTER_122_TOK             "lanmacfilter_122"
#define LANMACFILTER_123_TOK             "lanmacfilter_123"
#define LANMACFILTER_124_TOK             "lanmacfilter_124"
#define LANMACFILTER_125_TOK             "lanmacfilter_125"
#define LANMACFILTER_126_TOK             "lanmacfilter_126"
#define LANMACFILTER_127_TOK             "lanmacfilter_127"
#define LANMACFILTER_128_TOK             "lanmacfilter_128"
#if NUM_LAN_MAC_FILTERS > 128
#define LANMACFILTER_129_TOK             "lanmacfilter_129"
#define LANMACFILTER_130_TOK             "lanmacfilter_130"
#define LANMACFILTER_131_TOK             "lanmacfilter_131"
#define LANMACFILTER_132_TOK             "lanmacfilter_132"
#define LANMACFILTER_133_TOK             "lanmacfilter_133"
#define LANMACFILTER_134_TOK             "lanmacfilter_134"
#define LANMACFILTER_135_TOK             "lanmacfilter_135"
#define LANMACFILTER_136_TOK             "lanmacfilter_136"
#define LANMACFILTER_137_TOK             "lanmacfilter_137"
#define LANMACFILTER_138_TOK             "lanmacfilter_138"
#define LANMACFILTER_139_TOK             "lanmacfilter_139"
#define LANMACFILTER_140_TOK             "lanmacfilter_140"
#define LANMACFILTER_141_TOK             "lanmacfilter_141"
#define LANMACFILTER_142_TOK             "lanmacfilter_142"
#define LANMACFILTER_143_TOK             "lanmacfilter_143"
#define LANMACFILTER_144_TOK             "lanmacfilter_144"
#define LANMACFILTER_145_TOK             "lanmacfilter_145"
#define LANMACFILTER_146_TOK             "lanmacfilter_146"
#define LANMACFILTER_147_TOK             "lanmacfilter_147"
#define LANMACFILTER_148_TOK             "lanmacfilter_148"
#define LANMACFILTER_149_TOK             "lanmacfilter_149"
#define LANMACFILTER_150_TOK             "lanmacfilter_150"
#define LANMACFILTER_151_TOK             "lanmacfilter_151"
#define LANMACFILTER_152_TOK             "lanmacfilter_152"
#define LANMACFILTER_153_TOK             "lanmacfilter_153"
#define LANMACFILTER_154_TOK             "lanmacfilter_154"
#define LANMACFILTER_155_TOK             "lanmacfilter_155"
#define LANMACFILTER_156_TOK             "lanmacfilter_156"
#define LANMACFILTER_157_TOK             "lanmacfilter_157"
#define LANMACFILTER_158_TOK             "lanmacfilter_158"
#define LANMACFILTER_159_TOK             "lanmacfilter_159"
#define LANMACFILTER_160_TOK             "lanmacfilter_160"
#define LANMACFILTER_161_TOK             "lanmacfilter_161"
#define LANMACFILTER_162_TOK             "lanmacfilter_162"
#define LANMACFILTER_163_TOK             "lanmacfilter_163"
#define LANMACFILTER_164_TOK             "lanmacfilter_164"
#define LANMACFILTER_165_TOK             "lanmacfilter_165"
#define LANMACFILTER_166_TOK             "lanmacfilter_166"
#define LANMACFILTER_167_TOK             "lanmacfilter_167"
#define LANMACFILTER_168_TOK             "lanmacfilter_168"
#define LANMACFILTER_169_TOK             "lanmacfilter_169"
#define LANMACFILTER_170_TOK             "lanmacfilter_170"
#define LANMACFILTER_171_TOK             "lanmacfilter_171"
#define LANMACFILTER_172_TOK             "lanmacfilter_172"
#define LANMACFILTER_173_TOK             "lanmacfilter_173"
#define LANMACFILTER_174_TOK             "lanmacfilter_174"
#define LANMACFILTER_175_TOK             "lanmacfilter_175"
#define LANMACFILTER_176_TOK             "lanmacfilter_176"
#define LANMACFILTER_177_TOK             "lanmacfilter_177"
#define LANMACFILTER_178_TOK             "lanmacfilter_178"
#define LANMACFILTER_179_TOK             "lanmacfilter_179"
#define LANMACFILTER_180_TOK             "lanmacfilter_180"
#define LANMACFILTER_181_TOK             "lanmacfilter_181"
#define LANMACFILTER_182_TOK             "lanmacfilter_182"
#define LANMACFILTER_183_TOK             "lanmacfilter_183"
#define LANMACFILTER_184_TOK             "lanmacfilter_184"
#define LANMACFILTER_185_TOK             "lanmacfilter_185"
#define LANMACFILTER_186_TOK             "lanmacfilter_186"
#define LANMACFILTER_187_TOK             "lanmacfilter_187"
#define LANMACFILTER_188_TOK             "lanmacfilter_188"
#define LANMACFILTER_189_TOK             "lanmacfilter_189"
#define LANMACFILTER_190_TOK             "lanmacfilter_190"
#define LANMACFILTER_191_TOK             "lanmacfilter_191"
#define LANMACFILTER_192_TOK             "lanmacfilter_192"
#define LANMACFILTER_193_TOK             "lanmacfilter_193"
#define LANMACFILTER_194_TOK             "lanmacfilter_194"
#define LANMACFILTER_195_TOK             "lanmacfilter_195"
#define LANMACFILTER_196_TOK             "lanmacfilter_196"
#define LANMACFILTER_197_TOK             "lanmacfilter_197"
#define LANMACFILTER_198_TOK             "lanmacfilter_198"
#define LANMACFILTER_199_TOK             "lanmacfilter_199"
#define LANMACFILTER_200_TOK             "lanmacfilter_200"
#define LANMACFILTER_201_TOK             "lanmacfilter_201"
#define LANMACFILTER_202_TOK             "lanmacfilter_202"
#define LANMACFILTER_203_TOK             "lanmacfilter_203"
#define LANMACFILTER_204_TOK             "lanmacfilter_204"
#define LANMACFILTER_205_TOK             "lanmacfilter_205"
#define LANMACFILTER_206_TOK             "lanmacfilter_206"
#define LANMACFILTER_207_TOK             "lanmacfilter_207"
#define LANMACFILTER_208_TOK             "lanmacfilter_208"
#define LANMACFILTER_209_TOK             "lanmacfilter_209"
#define LANMACFILTER_210_TOK             "lanmacfilter_210"
#define LANMACFILTER_211_TOK             "lanmacfilter_211"
#define LANMACFILTER_212_TOK             "lanmacfilter_212"
#define LANMACFILTER_213_TOK             "lanmacfilter_213"
#define LANMACFILTER_214_TOK             "lanmacfilter_214"
#define LANMACFILTER_215_TOK             "lanmacfilter_215"
#define LANMACFILTER_216_TOK             "lanmacfilter_216"
#define LANMACFILTER_217_TOK             "lanmacfilter_217"
#define LANMACFILTER_218_TOK             "lanmacfilter_218"
#define LANMACFILTER_219_TOK             "lanmacfilter_219"
#define LANMACFILTER_220_TOK             "lanmacfilter_220"
#define LANMACFILTER_221_TOK             "lanmacfilter_221"
#define LANMACFILTER_222_TOK             "lanmacfilter_222"
#define LANMACFILTER_223_TOK             "lanmacfilter_223"
#define LANMACFILTER_224_TOK             "lanmacfilter_224"
#define LANMACFILTER_225_TOK             "lanmacfilter_225"
#define LANMACFILTER_226_TOK             "lanmacfilter_226"
#define LANMACFILTER_227_TOK             "lanmacfilter_227"
#define LANMACFILTER_228_TOK             "lanmacfilter_228"
#define LANMACFILTER_229_TOK             "lanmacfilter_229"
#define LANMACFILTER_230_TOK             "lanmacfilter_230"
#define LANMACFILTER_231_TOK             "lanmacfilter_231"
#define LANMACFILTER_232_TOK             "lanmacfilter_232"
#define LANMACFILTER_233_TOK             "lanmacfilter_233"
#define LANMACFILTER_234_TOK             "lanmacfilter_234"
#define LANMACFILTER_235_TOK             "lanmacfilter_235"
#define LANMACFILTER_236_TOK             "lanmacfilter_236"
#define LANMACFILTER_237_TOK             "lanmacfilter_237"
#define LANMACFILTER_238_TOK             "lanmacfilter_238"
#define LANMACFILTER_239_TOK             "lanmacfilter_239"
#define LANMACFILTER_240_TOK             "lanmacfilter_240"
#define LANMACFILTER_241_TOK             "lanmacfilter_241"
#define LANMACFILTER_242_TOK             "lanmacfilter_242"
#define LANMACFILTER_243_TOK             "lanmacfilter_243"
#define LANMACFILTER_244_TOK             "lanmacfilter_244"
#define LANMACFILTER_245_TOK             "lanmacfilter_245"
#define LANMACFILTER_246_TOK             "lanmacfilter_246"
#define LANMACFILTER_247_TOK             "lanmacfilter_247"
#define LANMACFILTER_248_TOK             "lanmacfilter_248"
#define LANMACFILTER_249_TOK             "lanmacfilter_249"
#define LANMACFILTER_250_TOK             "lanmacfilter_250"
#define LANMACFILTER_251_TOK             "lanmacfilter_251"
#define LANMACFILTER_252_TOK             "lanmacfilter_252"
#define LANMACFILTER_253_TOK             "lanmacfilter_253"
#define LANMACFILTER_254_TOK             "lanmacfilter_254"
#define LANMACFILTER_255_TOK             "lanmacfilter_255"
#define LANMACFILTER_256_TOK             "lanmacfilter_256"
#endif
#endif
#endif
#endif
#endif
#endif
/* ------------------   IP filter Filtering   -----------------------*/
#define IPFILTER_ENABLE_TOK              "ipfilter_enable"
#define IPFILTER_MODE_TOK                "ipfilter_mode"
#define IPFILTER_TOK                     "ipfilter_"  //get ipfilter token define
#define IPFILTER_01_TOK                  "ipfilter_1"
#define IPFILTER_02_TOK                  "ipfilter_2"
#define IPFILTER_03_TOK                  "ipfilter_3"
#define IPFILTER_04_TOK                  "ipfilter_4"
#define IPFILTER_05_TOK                  "ipfilter_5"
#define IPFILTER_06_TOK                  "ipfilter_6"
#define IPFILTER_07_TOK                  "ipfilter_7"
#define IPFILTER_08_TOK                  "ipfilter_8"
#define IPFILTER_09_TOK                  "ipfilter_9"
#define IPFILTER_10_TOK                  "ipfilter_10"
#if NUM_IP_FILTERS > 10
#define IPFILTER_11_TOK                  "ipfilter_11"
#define IPFILTER_12_TOK                  "ipfilter_12"
#define IPFILTER_13_TOK                  "ipfilter_13"
#define IPFILTER_14_TOK                  "ipfilter_14"
#define IPFILTER_15_TOK                  "ipfilter_15"
#define IPFILTER_16_TOK                  "ipfilter_16"
#define IPFILTER_17_TOK                  "ipfilter_17"
#define IPFILTER_18_TOK                  "ipfilter_18"
#define IPFILTER_19_TOK                  "ipfilter_19"
#define IPFILTER_20_TOK                  "ipfilter_20"
#if NUM_IP_FILTERS > 20
#define IPFILTER_21_TOK                  "ipfilter_21"
#define IPFILTER_22_TOK                  "ipfilter_22"
#define IPFILTER_23_TOK                  "ipfilter_23"
#define IPFILTER_24_TOK                  "ipfilter_24"
#define IPFILTER_25_TOK                  "ipfilter_25"
#define IPFILTER_26_TOK                  "ipfilter_26"
#define IPFILTER_27_TOK                  "ipfilter_27"
#define IPFILTER_28_TOK                  "ipfilter_28"
#define IPFILTER_29_TOK                  "ipfilter_29"
#define IPFILTER_30_TOK                  "ipfilter_30"
#define IPFILTER_31_TOK                  "ipfilter_31"
#define IPFILTER_32_TOK                  "ipfilter_32"
#endif
#if NUM_IP_FILTERS > 32
#define IPFILTER_33_TOK                  "ipfilter_33"
#define IPFILTER_34_TOK                  "ipfilter_34"
#define IPFILTER_35_TOK                  "ipfilter_35"
#define IPFILTER_36_TOK                  "ipfilter_36"
#define IPFILTER_37_TOK                  "ipfilter_37"
#define IPFILTER_38_TOK                  "ipfilter_38"
#define IPFILTER_39_TOK                  "ipfilter_39"
#define IPFILTER_40_TOK                  "ipfilter_40"
#define IPFILTER_41_TOK                  "ipfilter_41"
#define IPFILTER_42_TOK                  "ipfilter_42"
#define IPFILTER_43_TOK                  "ipfilter_43"
#define IPFILTER_44_TOK                  "ipfilter_44"
#define IPFILTER_45_TOK                  "ipfilter_45"
#define IPFILTER_46_TOK                  "ipfilter_46"
#define IPFILTER_47_TOK                  "ipfilter_47"
#define IPFILTER_48_TOK                  "ipfilter_48"
#define IPFILTER_49_TOK                  "ipfilter_49"
#define IPFILTER_50_TOK                  "ipfilter_50"
#define IPFILTER_51_TOK                  "ipfilter_51"
#define IPFILTER_52_TOK                  "ipfilter_52"
#define IPFILTER_53_TOK                  "ipfilter_53"
#define IPFILTER_54_TOK                  "ipfilter_54"
#define IPFILTER_55_TOK                  "ipfilter_55"
#define IPFILTER_56_TOK                  "ipfilter_56"
#define IPFILTER_57_TOK                  "ipfilter_57"
#define IPFILTER_58_TOK                  "ipfilter_58"
#define IPFILTER_59_TOK                  "ipfilter_59"
#define IPFILTER_60_TOK                  "ipfilter_60"
#define IPFILTER_61_TOK                  "ipfilter_61"
#define IPFILTER_62_TOK                  "ipfilter_62"
#define IPFILTER_63_TOK                  "ipfilter_63"
#define IPFILTER_64_TOK                  "ipfilter_64"
#define IPFILTER_65_TOK                  "ipfilter_65"
#define IPFILTER_66_TOK                  "ipfilter_66"
#define IPFILTER_67_TOK                  "ipfilter_67"
#define IPFILTER_68_TOK                  "ipfilter_68"
#define IPFILTER_69_TOK                  "ipfilter_69"
#define IPFILTER_70_TOK                  "ipfilter_70"
#define IPFILTER_71_TOK                  "ipfilter_71"
#define IPFILTER_72_TOK                  "ipfilter_72"
#define IPFILTER_73_TOK                  "ipfilter_73"
#define IPFILTER_74_TOK                  "ipfilter_74"
#define IPFILTER_75_TOK                  "ipfilter_75"
#define IPFILTER_76_TOK                  "ipfilter_76"
#define IPFILTER_77_TOK                  "ipfilter_77"
#define IPFILTER_78_TOK                  "ipfilter_78"
#define IPFILTER_79_TOK                  "ipfilter_79"
#define IPFILTER_80_TOK                  "ipfilter_80"
#define IPFILTER_81_TOK                  "ipfilter_81"
#define IPFILTER_82_TOK                  "ipfilter_82"
#define IPFILTER_83_TOK                  "ipfilter_83"
#define IPFILTER_84_TOK                  "ipfilter_84"
#define IPFILTER_85_TOK                  "ipfilter_85"
#define IPFILTER_86_TOK                  "ipfilter_86"
#define IPFILTER_87_TOK                  "ipfilter_87"
#define IPFILTER_88_TOK                  "ipfilter_88"
#define IPFILTER_89_TOK                  "ipfilter_89"
#define IPFILTER_90_TOK                  "ipfilter_90"
#define IPFILTER_91_TOK                  "ipfilter_91"
#define IPFILTER_92_TOK                  "ipfilter_92"
#define IPFILTER_93_TOK                  "ipfilter_93"
#define IPFILTER_94_TOK                  "ipfilter_94"
#define IPFILTER_95_TOK                  "ipfilter_95"
#define IPFILTER_96_TOK                  "ipfilter_96"
#define IPFILTER_97_TOK                  "ipfilter_97"
#define IPFILTER_98_TOK                  "ipfilter_98"
#define IPFILTER_99_TOK                  "ipfilter_99"
#define IPFILTER_100_TOK                  "ipfilter_100"
#define IPFILTER_101_TOK                  "ipfilter_101"
#define IPFILTER_102_TOK                  "ipfilter_102"
#define IPFILTER_103_TOK                  "ipfilter_103"
#define IPFILTER_104_TOK                  "ipfilter_104"
#define IPFILTER_105_TOK                  "ipfilter_105"
#define IPFILTER_106_TOK                  "ipfilter_106"
#define IPFILTER_107_TOK                  "ipfilter_107"
#define IPFILTER_108_TOK                  "ipfilter_108"
#define IPFILTER_109_TOK                  "ipfilter_109"
#define IPFILTER_110_TOK                  "ipfilter_110"
#define IPFILTER_111_TOK                  "ipfilter_111"
#define IPFILTER_112_TOK                  "ipfilter_112"
#define IPFILTER_113_TOK                  "ipfilter_113"
#define IPFILTER_114_TOK                  "ipfilter_114"
#define IPFILTER_115_TOK                  "ipfilter_115"
#define IPFILTER_116_TOK                  "ipfilter_116"
#define IPFILTER_117_TOK                  "ipfilter_117"
#define IPFILTER_118_TOK                  "ipfilter_118"
#define IPFILTER_119_TOK                  "ipfilter_119"
#define IPFILTER_120_TOK                  "ipfilter_120"
#define IPFILTER_121_TOK                  "ipfilter_121"
#define IPFILTER_122_TOK                  "ipfilter_122"
#define IPFILTER_123_TOK                  "ipfilter_123"
#define IPFILTER_124_TOK                  "ipfilter_124"
#define IPFILTER_125_TOK                  "ipfilter_125"
#define IPFILTER_126_TOK                  "ipfilter_126"
#define IPFILTER_127_TOK                  "ipfilter_127"
#define IPFILTER_128_TOK                  "ipfilter_128"
#endif
#endif
/* ------------------   URL filter Filtering   -----------------------*/
#define URLFILTER_ENABLE_TOK             "urlfilter_enable"
#if HAS_ADVANCED_URL_FILTER
#define URLFILTER_TYPE_TOK             	 "urlfilter_type"
#endif
#if HAS_HTTP_PROXY
#define URLFILTER_MODE_TOK               "urlfilter_mode"
#endif
#define URLFILTER_TOK                    "urlfilter_"
#define URLFILTER_01_TOK                 "urlfilter_1"
#define URLFILTER_02_TOK                 "urlfilter_2"
#define URLFILTER_03_TOK                 "urlfilter_3"
#define URLFILTER_04_TOK                 "urlfilter_4"
#define URLFILTER_05_TOK                 "urlfilter_5"
#define URLFILTER_06_TOK                 "urlfilter_6"
#define URLFILTER_07_TOK                 "urlfilter_7"
#define URLFILTER_08_TOK                 "urlfilter_8"
#define URLFILTER_09_TOK                 "urlfilter_9"
#define URLFILTER_10_TOK                 "urlfilter_10"
#if NUM_URL_FILTER > 10
#define URLFILTER_11_TOK                 "urlfilter_11"
#define URLFILTER_12_TOK                 "urlfilter_12"
#define URLFILTER_13_TOK                 "urlfilter_13"
#define URLFILTER_14_TOK                 "urlfilter_14"
#define URLFILTER_15_TOK                 "urlfilter_15"
#define URLFILTER_16_TOK                 "urlfilter_16"
#define URLFILTER_17_TOK                 "urlfilter_17"
#define URLFILTER_18_TOK                 "urlfilter_18"
#define URLFILTER_19_TOK                 "urlfilter_19"
#define URLFILTER_20_TOK                 "urlfilter_20"
#if NUM_URL_FILTER > 20
#define URLFILTER_21_TOK                 "urlfilter_21"
#define URLFILTER_22_TOK                 "urlfilter_22"
#define URLFILTER_23_TOK                 "urlfilter_23"
#define URLFILTER_24_TOK                 "urlfilter_24"
#define URLFILTER_25_TOK                 "urlfilter_25"
#define URLFILTER_26_TOK                 "urlfilter_26"
#define URLFILTER_27_TOK                 "urlfilter_27"
#define URLFILTER_28_TOK                 "urlfilter_28"
#define URLFILTER_29_TOK                 "urlfilter_29"
#define URLFILTER_30_TOK                 "urlfilter_30"
#if NUM_URL_FILTER > 30
#define URLFILTER_31_TOK                 "urlfilter_31"
#define URLFILTER_32_TOK                 "urlfilter_32"
#define URLFILTER_33_TOK                 "urlfilter_33"
#define URLFILTER_34_TOK                 "urlfilter_34"
#define URLFILTER_35_TOK                 "urlfilter_35"
#define URLFILTER_36_TOK                 "urlfilter_36"
#define URLFILTER_37_TOK                 "urlfilter_37"
#define URLFILTER_38_TOK                 "urlfilter_38"
#define URLFILTER_39_TOK                 "urlfilter_39"
#define URLFILTER_40_TOK                 "urlfilter_40"
#endif //#if NUM_URL_FILTER > 30
#endif //#if NUM_URL_FILTER > 20
#endif //#if NUM_URL_FILTER > 10

#if HAS_ACCESS_CONTROL
#define ACCESS_CONTROL_ENABLE_TOK        "accessctrl_en"
#define ACCESS_CONTROL_TOK               "accessctrl_"
#define ACCESS_CONTROL_01_TOK            "accessctrl_1"
#define ACCESS_CONTROL_02_TOK            "accessctrl_2"
#define ACCESS_CONTROL_03_TOK            "accessctrl_3"
#define ACCESS_CONTROL_04_TOK            "accessctrl_4"
#define ACCESS_CONTROL_05_TOK            "accessctrl_5"
#define ACCESS_CONTROL_06_TOK            "accessctrl_6"
#define ACCESS_CONTROL_07_TOK            "accessctrl_7"
#define ACCESS_CONTROL_08_TOK            "accessctrl_8"
#define ACCESS_CONTROL_09_TOK            "accessctrl_9"
#define ACCESS_CONTROL_10_TOK            "accessctrl_10"
#define ACCESS_CONTROL_11_TOK            "accessctrl_11"
#define ACCESS_CONTROL_12_TOK            "accessctrl_12"
#define ACCESS_CONTROL_13_TOK            "accessctrl_13"
#define ACCESS_CONTROL_14_TOK            "accessctrl_14"
#define ACCESS_CONTROL_15_TOK            "accessctrl_15"
#define ACCESS_CONTROL_16_TOK            "accessctrl_16"

#define ACCESS_CONTROL_IP_TOK               "acctrl_ip_"
#define ACCESS_CONTROL_IP_01_TOK            "acctrl_ip_1"
#define ACCESS_CONTROL_IP_02_TOK            "acctrl_ip_2"
#define ACCESS_CONTROL_IP_03_TOK            "acctrl_ip_3"
#define ACCESS_CONTROL_IP_04_TOK            "acctrl_ip_4"
#define ACCESS_CONTROL_IP_05_TOK            "acctrl_ip_5"
#define ACCESS_CONTROL_IP_06_TOK            "acctrl_ip_6"
#define ACCESS_CONTROL_IP_07_TOK            "acctrl_ip_7"
#define ACCESS_CONTROL_IP_08_TOK            "acctrl_ip_8"
#define ACCESS_CONTROL_IP_09_TOK            "acctrl_ip_9"
#define ACCESS_CONTROL_IP_10_TOK            "acctrl_ip_10"
#define ACCESS_CONTROL_IP_11_TOK            "acctrl_ip_11"
#define ACCESS_CONTROL_IP_12_TOK            "acctrl_ip_12"
#define ACCESS_CONTROL_IP_13_TOK            "acctrl_ip_13"
#define ACCESS_CONTROL_IP_14_TOK            "acctrl_ip_14"
#define ACCESS_CONTROL_IP_15_TOK            "acctrl_ip_15"
#define ACCESS_CONTROL_IP_16_TOK            "acctrl_ip_16"

#define ACCESS_CONTROL_MAC_TOK               "acctrl_mac_"
#define ACCESS_CONTROL_MAC_01_TOK            "acctrl_mac_1"
#define ACCESS_CONTROL_MAC_02_TOK            "acctrl_mac_2"
#define ACCESS_CONTROL_MAC_03_TOK            "acctrl_mac_3"
#define ACCESS_CONTROL_MAC_04_TOK            "acctrl_mac_4"
#define ACCESS_CONTROL_MAC_05_TOK            "acctrl_mac_5"
#define ACCESS_CONTROL_MAC_06_TOK            "acctrl_mac_6"
#define ACCESS_CONTROL_MAC_07_TOK            "acctrl_mac_7"
#define ACCESS_CONTROL_MAC_08_TOK            "acctrl_mac_8"
#define ACCESS_CONTROL_MAC_09_TOK            "acctrl_mac_9"
#define ACCESS_CONTROL_MAC_10_TOK            "acctrl_mac_10"
#define ACCESS_CONTROL_MAC_11_TOK            "acctrl_mac_11"
#define ACCESS_CONTROL_MAC_12_TOK            "acctrl_mac_12"
#define ACCESS_CONTROL_MAC_13_TOK            "acctrl_mac_13"
#define ACCESS_CONTROL_MAC_14_TOK            "acctrl_mac_14"
#define ACCESS_CONTROL_MAC_15_TOK            "acctrl_mac_15"
#define ACCESS_CONTROL_MAC_16_TOK            "acctrl_mac_16"
#endif

#if HAS_ACCESS_CONTROL_BELKIN
#define ACCESS_CONTROL_BK_PASSWORD_TOK		"accessctrl_bk_pwd"
#define ACCESS_CONTROL_BK_ENABLE_TOK    	"accessctrl_bk_en"
#define ACCESS_CONTROL_BK_TOK               "accessctrl_bk_"
#define ACCESS_CONTROL_BK_01_TOK            "accessctrl_bk_1"
#define ACCESS_CONTROL_BK_02_TOK            "accessctrl_bk_2"
#define ACCESS_CONTROL_BK_03_TOK            "accessctrl_bk_3"
#define ACCESS_CONTROL_BK_04_TOK            "accessctrl_bk_4"
#define ACCESS_CONTROL_BK_05_TOK            "accessctrl_bk_5"
#define ACCESS_CONTROL_BK_06_TOK            "accessctrl_bk_6"
#define ACCESS_CONTROL_BK_07_TOK            "accessctrl_bk_7"
#define ACCESS_CONTROL_BK_08_TOK            "accessctrl_bk_8"
#define ACCESS_CONTROL_BK_09_TOK            "accessctrl_bk_9"
#define ACCESS_CONTROL_BK_10_TOK            "accessctrl_bk_10"
#define ACCESS_CONTROL_BK_11_TOK            "accessctrl_bk_11"
#define ACCESS_CONTROL_BK_12_TOK            "accessctrl_bk_12"
#define ACCESS_CONTROL_BK_13_TOK            "accessctrl_bk_13"
#define ACCESS_CONTROL_BK_14_TOK            "accessctrl_bk_14"
#define ACCESS_CONTROL_BK_15_TOK            "accessctrl_bk_15"
#define ACCESS_CONTROL_BK_16_TOK            "accessctrl_bk_16"
#define ACCESS_CONTROL_BK_17_TOK            "accessctrl_bk_17"
#define ACCESS_CONTROL_BK_18_TOK            "accessctrl_bk_18"
#define ACCESS_CONTROL_BK_19_TOK            "accessctrl_bk_19"
#define ACCESS_CONTROL_BK_20_TOK            "accessctrl_bk_20"

#define ACCESS_CONTROL_SERVICE_TOK       "ac_service_"
#define ACCESS_CONTROL_SERVICE_01_TOK    "ac_service_1"
#define ACCESS_CONTROL_SERVICE_02_TOK    "ac_service_2"
#define ACCESS_CONTROL_SERVICE_03_TOK    "ac_service_3"
#define ACCESS_CONTROL_SERVICE_04_TOK    "ac_service_4"
#define ACCESS_CONTROL_SERVICE_05_TOK    "ac_service_5"
#define ACCESS_CONTROL_SERVICE_06_TOK    "ac_service_6"
#define ACCESS_CONTROL_SERVICE_07_TOK    "ac_service_7"
#define ACCESS_CONTROL_SERVICE_08_TOK    "ac_service_8"
#define ACCESS_CONTROL_SERVICE_09_TOK    "ac_service_9"
#define ACCESS_CONTROL_SERVICE_10_TOK    "ac_service_10"
#define ACCESS_CONTROL_SERVICE_11_TOK    "ac_service_11"
#define ACCESS_CONTROL_SERVICE_12_TOK    "ac_service_12"
#define ACCESS_CONTROL_SERVICE_13_TOK    "ac_service_13"
#define ACCESS_CONTROL_SERVICE_14_TOK    "ac_service_14"
#define ACCESS_CONTROL_SERVICE_15_TOK    "ac_service_15"
#define ACCESS_CONTROL_SERVICE_16_TOK    "ac_service_16"
#define ACCESS_CONTROL_SERVICE_17_TOK    "ac_service_17"
#define ACCESS_CONTROL_SERVICE_18_TOK    "ac_service_18"
#define ACCESS_CONTROL_SERVICE_19_TOK    "ac_service_19"
#define ACCESS_CONTROL_SERVICE_20_TOK    "ac_service_20"
/* AccessControl URL-Filter (20) x 10 = 200 */
#define ACCESS_CONTROL_URLFILTER_TOK     "ac_urlfilter_"
#define ACCESS_CONTROL_URLFILTER_01_TOK  "ac_urlfilter_1"
#define ACCESS_CONTROL_URLFILTER_02_TOK  "ac_urlfilter_2"
#define ACCESS_CONTROL_URLFILTER_03_TOK  "ac_urlfilter_3"
#define ACCESS_CONTROL_URLFILTER_04_TOK  "ac_urlfilter_4"
#define ACCESS_CONTROL_URLFILTER_05_TOK  "ac_urlfilter_5"
#define ACCESS_CONTROL_URLFILTER_06_TOK  "ac_urlfilter_6"
#define ACCESS_CONTROL_URLFILTER_07_TOK  "ac_urlfilter_7"
#define ACCESS_CONTROL_URLFILTER_08_TOK  "ac_urlfilter_8"
#define ACCESS_CONTROL_URLFILTER_09_TOK  "ac_urlfilter_9"
#define ACCESS_CONTROL_URLFILTER_10_TOK  "ac_urlfilter_10"
#define ACCESS_CONTROL_URLFILTER_11_TOK  "ac_urlfilter_11"
#define ACCESS_CONTROL_URLFILTER_12_TOK  "ac_urlfilter_12"
#define ACCESS_CONTROL_URLFILTER_13_TOK  "ac_urlfilter_13"
#define ACCESS_CONTROL_URLFILTER_14_TOK  "ac_urlfilter_14"
#define ACCESS_CONTROL_URLFILTER_15_TOK  "ac_urlfilter_15"
#define ACCESS_CONTROL_URLFILTER_16_TOK  "ac_urlfilter_16"
#define ACCESS_CONTROL_URLFILTER_17_TOK  "ac_urlfilter_17"
#define ACCESS_CONTROL_URLFILTER_18_TOK  "ac_urlfilter_18"
#define ACCESS_CONTROL_URLFILTER_19_TOK  "ac_urlfilter_19"
#define ACCESS_CONTROL_URLFILTER_20_TOK  "ac_urlfilter_20"
#define ACCESS_CONTROL_URLFILTER_21_TOK  "ac_urlfilter_21"
#define ACCESS_CONTROL_URLFILTER_22_TOK  "ac_urlfilter_22"
#define ACCESS_CONTROL_URLFILTER_23_TOK  "ac_urlfilter_23"
#define ACCESS_CONTROL_URLFILTER_24_TOK  "ac_urlfilter_24"
#define ACCESS_CONTROL_URLFILTER_25_TOK  "ac_urlfilter_25"
#define ACCESS_CONTROL_URLFILTER_26_TOK  "ac_urlfilter_26"
#define ACCESS_CONTROL_URLFILTER_27_TOK  "ac_urlfilter_27"
#define ACCESS_CONTROL_URLFILTER_28_TOK  "ac_urlfilter_28"
#define ACCESS_CONTROL_URLFILTER_29_TOK  "ac_urlfilter_29"
#define ACCESS_CONTROL_URLFILTER_30_TOK  "ac_urlfilter_30"
#define ACCESS_CONTROL_URLFILTER_31_TOK  "ac_urlfilter_31"
#define ACCESS_CONTROL_URLFILTER_32_TOK  "ac_urlfilter_32"
#define ACCESS_CONTROL_URLFILTER_33_TOK  "ac_urlfilter_33"
#define ACCESS_CONTROL_URLFILTER_34_TOK  "ac_urlfilter_34"
#define ACCESS_CONTROL_URLFILTER_35_TOK  "ac_urlfilter_35"
#define ACCESS_CONTROL_URLFILTER_36_TOK  "ac_urlfilter_36"
#define ACCESS_CONTROL_URLFILTER_37_TOK  "ac_urlfilter_37"
#define ACCESS_CONTROL_URLFILTER_38_TOK  "ac_urlfilter_38"
#define ACCESS_CONTROL_URLFILTER_39_TOK  "ac_urlfilter_39"
#define ACCESS_CONTROL_URLFILTER_40_TOK  "ac_urlfilter_40"
#define ACCESS_CONTROL_URLFILTER_41_TOK  "ac_urlfilter_41"
#define ACCESS_CONTROL_URLFILTER_42_TOK  "ac_urlfilter_42"
#define ACCESS_CONTROL_URLFILTER_43_TOK  "ac_urlfilter_43"
#define ACCESS_CONTROL_URLFILTER_44_TOK  "ac_urlfilter_44"
#define ACCESS_CONTROL_URLFILTER_45_TOK  "ac_urlfilter_45"
#define ACCESS_CONTROL_URLFILTER_46_TOK  "ac_urlfilter_46"
#define ACCESS_CONTROL_URLFILTER_47_TOK  "ac_urlfilter_47"
#define ACCESS_CONTROL_URLFILTER_48_TOK  "ac_urlfilter_48"
#define ACCESS_CONTROL_URLFILTER_49_TOK  "ac_urlfilter_49"
#define ACCESS_CONTROL_URLFILTER_50_TOK  "ac_urlfilter_50"
#define ACCESS_CONTROL_URLFILTER_51_TOK  "ac_urlfilter_51"
#define ACCESS_CONTROL_URLFILTER_52_TOK  "ac_urlfilter_52"
#define ACCESS_CONTROL_URLFILTER_53_TOK  "ac_urlfilter_53"
#define ACCESS_CONTROL_URLFILTER_54_TOK  "ac_urlfilter_54"
#define ACCESS_CONTROL_URLFILTER_55_TOK  "ac_urlfilter_55"
#define ACCESS_CONTROL_URLFILTER_56_TOK  "ac_urlfilter_56"
#define ACCESS_CONTROL_URLFILTER_57_TOK  "ac_urlfilter_57"
#define ACCESS_CONTROL_URLFILTER_58_TOK  "ac_urlfilter_58"
#define ACCESS_CONTROL_URLFILTER_59_TOK  "ac_urlfilter_59"
#define ACCESS_CONTROL_URLFILTER_60_TOK  "ac_urlfilter_60"
#define ACCESS_CONTROL_URLFILTER_61_TOK  "ac_urlfilter_61"
#define ACCESS_CONTROL_URLFILTER_62_TOK  "ac_urlfilter_62"
#define ACCESS_CONTROL_URLFILTER_63_TOK  "ac_urlfilter_63"
#define ACCESS_CONTROL_URLFILTER_64_TOK  "ac_urlfilter_64"
#define ACCESS_CONTROL_URLFILTER_65_TOK  "ac_urlfilter_65"
#define ACCESS_CONTROL_URLFILTER_66_TOK  "ac_urlfilter_66"
#define ACCESS_CONTROL_URLFILTER_67_TOK  "ac_urlfilter_67"
#define ACCESS_CONTROL_URLFILTER_68_TOK  "ac_urlfilter_68"
#define ACCESS_CONTROL_URLFILTER_69_TOK  "ac_urlfilter_69"
#define ACCESS_CONTROL_URLFILTER_70_TOK  "ac_urlfilter_70"
#define ACCESS_CONTROL_URLFILTER_71_TOK  "ac_urlfilter_71"
#define ACCESS_CONTROL_URLFILTER_72_TOK  "ac_urlfilter_72"
#define ACCESS_CONTROL_URLFILTER_73_TOK  "ac_urlfilter_73"
#define ACCESS_CONTROL_URLFILTER_74_TOK  "ac_urlfilter_74"
#define ACCESS_CONTROL_URLFILTER_75_TOK  "ac_urlfilter_75"
#define ACCESS_CONTROL_URLFILTER_76_TOK  "ac_urlfilter_76"
#define ACCESS_CONTROL_URLFILTER_77_TOK  "ac_urlfilter_77"
#define ACCESS_CONTROL_URLFILTER_78_TOK  "ac_urlfilter_78"
#define ACCESS_CONTROL_URLFILTER_79_TOK  "ac_urlfilter_79"
#define ACCESS_CONTROL_URLFILTER_80_TOK  "ac_urlfilter_80"
#define ACCESS_CONTROL_URLFILTER_81_TOK  "ac_urlfilter_81"
#define ACCESS_CONTROL_URLFILTER_82_TOK  "ac_urlfilter_82"
#define ACCESS_CONTROL_URLFILTER_83_TOK  "ac_urlfilter_83"
#define ACCESS_CONTROL_URLFILTER_84_TOK  "ac_urlfilter_84"
#define ACCESS_CONTROL_URLFILTER_85_TOK  "ac_urlfilter_85"
#define ACCESS_CONTROL_URLFILTER_86_TOK  "ac_urlfilter_86"
#define ACCESS_CONTROL_URLFILTER_87_TOK  "ac_urlfilter_87"
#define ACCESS_CONTROL_URLFILTER_88_TOK  "ac_urlfilter_88"
#define ACCESS_CONTROL_URLFILTER_89_TOK  "ac_urlfilter_89"
#define ACCESS_CONTROL_URLFILTER_90_TOK  "ac_urlfilter_90"
#define ACCESS_CONTROL_URLFILTER_91_TOK  "ac_urlfilter_91"
#define ACCESS_CONTROL_URLFILTER_92_TOK  "ac_urlfilter_92"
#define ACCESS_CONTROL_URLFILTER_93_TOK  "ac_urlfilter_93"
#define ACCESS_CONTROL_URLFILTER_94_TOK  "ac_urlfilter_94"
#define ACCESS_CONTROL_URLFILTER_95_TOK  "ac_urlfilter_95"
#define ACCESS_CONTROL_URLFILTER_96_TOK  "ac_urlfilter_96"
#define ACCESS_CONTROL_URLFILTER_97_TOK  "ac_urlfilter_97"
#define ACCESS_CONTROL_URLFILTER_98_TOK  "ac_urlfilter_98"
#define ACCESS_CONTROL_URLFILTER_99_TOK  "ac_urlfilter_99"
#define ACCESS_CONTROL_URLFILTER_100_TOK  "ac_urlfilter_100"
#define ACCESS_CONTROL_URLFILTER_101_TOK  "ac_urlfilter_101"
#define ACCESS_CONTROL_URLFILTER_102_TOK  "ac_urlfilter_102"
#define ACCESS_CONTROL_URLFILTER_103_TOK  "ac_urlfilter_103"
#define ACCESS_CONTROL_URLFILTER_104_TOK  "ac_urlfilter_104"
#define ACCESS_CONTROL_URLFILTER_105_TOK  "ac_urlfilter_105"
#define ACCESS_CONTROL_URLFILTER_106_TOK  "ac_urlfilter_106"
#define ACCESS_CONTROL_URLFILTER_107_TOK  "ac_urlfilter_107"
#define ACCESS_CONTROL_URLFILTER_108_TOK  "ac_urlfilter_108"
#define ACCESS_CONTROL_URLFILTER_109_TOK  "ac_urlfilter_109"
#define ACCESS_CONTROL_URLFILTER_110_TOK  "ac_urlfilter_110"
#define ACCESS_CONTROL_URLFILTER_111_TOK  "ac_urlfilter_111"
#define ACCESS_CONTROL_URLFILTER_112_TOK  "ac_urlfilter_112"
#define ACCESS_CONTROL_URLFILTER_113_TOK  "ac_urlfilter_113"
#define ACCESS_CONTROL_URLFILTER_114_TOK  "ac_urlfilter_114"
#define ACCESS_CONTROL_URLFILTER_115_TOK  "ac_urlfilter_115"
#define ACCESS_CONTROL_URLFILTER_116_TOK  "ac_urlfilter_116"
#define ACCESS_CONTROL_URLFILTER_117_TOK  "ac_urlfilter_117"
#define ACCESS_CONTROL_URLFILTER_118_TOK  "ac_urlfilter_118"
#define ACCESS_CONTROL_URLFILTER_119_TOK  "ac_urlfilter_119"
#define ACCESS_CONTROL_URLFILTER_120_TOK  "ac_urlfilter_120"
#define ACCESS_CONTROL_URLFILTER_121_TOK  "ac_urlfilter_121"
#define ACCESS_CONTROL_URLFILTER_122_TOK  "ac_urlfilter_122"
#define ACCESS_CONTROL_URLFILTER_123_TOK  "ac_urlfilter_123"
#define ACCESS_CONTROL_URLFILTER_124_TOK  "ac_urlfilter_124"
#define ACCESS_CONTROL_URLFILTER_125_TOK  "ac_urlfilter_125"
#define ACCESS_CONTROL_URLFILTER_126_TOK  "ac_urlfilter_126"
#define ACCESS_CONTROL_URLFILTER_127_TOK  "ac_urlfilter_127"
#define ACCESS_CONTROL_URLFILTER_128_TOK  "ac_urlfilter_128"
#define ACCESS_CONTROL_URLFILTER_129_TOK  "ac_urlfilter_129"
#define ACCESS_CONTROL_URLFILTER_130_TOK  "ac_urlfilter_130"
#define ACCESS_CONTROL_URLFILTER_131_TOK  "ac_urlfilter_131"
#define ACCESS_CONTROL_URLFILTER_132_TOK  "ac_urlfilter_132"
#define ACCESS_CONTROL_URLFILTER_133_TOK  "ac_urlfilter_133"
#define ACCESS_CONTROL_URLFILTER_134_TOK  "ac_urlfilter_134"
#define ACCESS_CONTROL_URLFILTER_135_TOK  "ac_urlfilter_135"
#define ACCESS_CONTROL_URLFILTER_136_TOK  "ac_urlfilter_136"
#define ACCESS_CONTROL_URLFILTER_137_TOK  "ac_urlfilter_137"
#define ACCESS_CONTROL_URLFILTER_138_TOK  "ac_urlfilter_138"
#define ACCESS_CONTROL_URLFILTER_139_TOK  "ac_urlfilter_139"
#define ACCESS_CONTROL_URLFILTER_140_TOK  "ac_urlfilter_140"
#define ACCESS_CONTROL_URLFILTER_141_TOK  "ac_urlfilter_141"
#define ACCESS_CONTROL_URLFILTER_142_TOK  "ac_urlfilter_142"
#define ACCESS_CONTROL_URLFILTER_143_TOK  "ac_urlfilter_143"
#define ACCESS_CONTROL_URLFILTER_144_TOK  "ac_urlfilter_144"
#define ACCESS_CONTROL_URLFILTER_145_TOK  "ac_urlfilter_145"
#define ACCESS_CONTROL_URLFILTER_146_TOK  "ac_urlfilter_146"
#define ACCESS_CONTROL_URLFILTER_147_TOK  "ac_urlfilter_147"
#define ACCESS_CONTROL_URLFILTER_148_TOK  "ac_urlfilter_148"
#define ACCESS_CONTROL_URLFILTER_149_TOK  "ac_urlfilter_149"
#define ACCESS_CONTROL_URLFILTER_150_TOK  "ac_urlfilter_150"
#define ACCESS_CONTROL_URLFILTER_151_TOK  "ac_urlfilter_151"
#define ACCESS_CONTROL_URLFILTER_152_TOK  "ac_urlfilter_152"
#define ACCESS_CONTROL_URLFILTER_153_TOK  "ac_urlfilter_153"
#define ACCESS_CONTROL_URLFILTER_154_TOK  "ac_urlfilter_154"
#define ACCESS_CONTROL_URLFILTER_155_TOK  "ac_urlfilter_155"
#define ACCESS_CONTROL_URLFILTER_156_TOK  "ac_urlfilter_156"
#define ACCESS_CONTROL_URLFILTER_157_TOK  "ac_urlfilter_157"
#define ACCESS_CONTROL_URLFILTER_158_TOK  "ac_urlfilter_158"
#define ACCESS_CONTROL_URLFILTER_159_TOK  "ac_urlfilter_159"
#define ACCESS_CONTROL_URLFILTER_160_TOK  "ac_urlfilter_160"
#define ACCESS_CONTROL_URLFILTER_161_TOK  "ac_urlfilter_161"
#define ACCESS_CONTROL_URLFILTER_162_TOK  "ac_urlfilter_162"
#define ACCESS_CONTROL_URLFILTER_163_TOK  "ac_urlfilter_163"
#define ACCESS_CONTROL_URLFILTER_164_TOK  "ac_urlfilter_164"
#define ACCESS_CONTROL_URLFILTER_165_TOK  "ac_urlfilter_165"
#define ACCESS_CONTROL_URLFILTER_166_TOK  "ac_urlfilter_166"
#define ACCESS_CONTROL_URLFILTER_167_TOK  "ac_urlfilter_167"
#define ACCESS_CONTROL_URLFILTER_168_TOK  "ac_urlfilter_168"
#define ACCESS_CONTROL_URLFILTER_169_TOK  "ac_urlfilter_169"
#define ACCESS_CONTROL_URLFILTER_170_TOK  "ac_urlfilter_170"
#define ACCESS_CONTROL_URLFILTER_171_TOK  "ac_urlfilter_171"
#define ACCESS_CONTROL_URLFILTER_172_TOK  "ac_urlfilter_172"
#define ACCESS_CONTROL_URLFILTER_173_TOK  "ac_urlfilter_173"
#define ACCESS_CONTROL_URLFILTER_174_TOK  "ac_urlfilter_174"
#define ACCESS_CONTROL_URLFILTER_175_TOK  "ac_urlfilter_175"
#define ACCESS_CONTROL_URLFILTER_176_TOK  "ac_urlfilter_176"
#define ACCESS_CONTROL_URLFILTER_177_TOK  "ac_urlfilter_177"
#define ACCESS_CONTROL_URLFILTER_178_TOK  "ac_urlfilter_178"
#define ACCESS_CONTROL_URLFILTER_179_TOK  "ac_urlfilter_179"
#define ACCESS_CONTROL_URLFILTER_180_TOK  "ac_urlfilter_180"
#define ACCESS_CONTROL_URLFILTER_181_TOK  "ac_urlfilter_181"
#define ACCESS_CONTROL_URLFILTER_182_TOK  "ac_urlfilter_182"
#define ACCESS_CONTROL_URLFILTER_183_TOK  "ac_urlfilter_183"
#define ACCESS_CONTROL_URLFILTER_184_TOK  "ac_urlfilter_184"
#define ACCESS_CONTROL_URLFILTER_185_TOK  "ac_urlfilter_185"
#define ACCESS_CONTROL_URLFILTER_186_TOK  "ac_urlfilter_186"
#define ACCESS_CONTROL_URLFILTER_187_TOK  "ac_urlfilter_187"
#define ACCESS_CONTROL_URLFILTER_188_TOK  "ac_urlfilter_188"
#define ACCESS_CONTROL_URLFILTER_189_TOK  "ac_urlfilter_189"
#define ACCESS_CONTROL_URLFILTER_190_TOK  "ac_urlfilter_190"
#define ACCESS_CONTROL_URLFILTER_191_TOK  "ac_urlfilter_191"
#define ACCESS_CONTROL_URLFILTER_192_TOK  "ac_urlfilter_192"
#define ACCESS_CONTROL_URLFILTER_193_TOK  "ac_urlfilter_193"
#define ACCESS_CONTROL_URLFILTER_194_TOK  "ac_urlfilter_194"
#define ACCESS_CONTROL_URLFILTER_195_TOK  "ac_urlfilter_195"
#define ACCESS_CONTROL_URLFILTER_196_TOK  "ac_urlfilter_196"
#define ACCESS_CONTROL_URLFILTER_197_TOK  "ac_urlfilter_197"
#define ACCESS_CONTROL_URLFILTER_198_TOK  "ac_urlfilter_198"
#define ACCESS_CONTROL_URLFILTER_199_TOK  "ac_urlfilter_199"
#define ACCESS_CONTROL_URLFILTER_200_TOK  "ac_urlfilter_200"
/* AccessControl URL-Filter Keyword(20) x 10 = 200 */
#define ACCESS_CONTROL_URLFILTER_KEY_TOK     		"ac_urlfilter_k_"
#define ACCESS_CONTROL_URLFILTER_KEY_01_TOK			"ac_urlfilter_k_1"
#define ACCESS_CONTROL_URLFILTER_KEY_02_TOK 	 	"ac_urlfilter_k_2"
#define ACCESS_CONTROL_URLFILTER_KEY_03_TOK         "ac_urlfilter_k_3"
#define ACCESS_CONTROL_URLFILTER_KEY_04_TOK         "ac_urlfilter_k_4"
#define ACCESS_CONTROL_URLFILTER_KEY_05_TOK         "ac_urlfilter_k_5"
#define ACCESS_CONTROL_URLFILTER_KEY_06_TOK         "ac_urlfilter_k_6"
#define ACCESS_CONTROL_URLFILTER_KEY_07_TOK         "ac_urlfilter_k_7"
#define ACCESS_CONTROL_URLFILTER_KEY_08_TOK         "ac_urlfilter_k_8"
#define ACCESS_CONTROL_URLFILTER_KEY_09_TOK         "ac_urlfilter_k_9"
#define ACCESS_CONTROL_URLFILTER_KEY_10_TOK         "ac_urlfilter_k_10"
#define ACCESS_CONTROL_URLFILTER_KEY_11_TOK         "ac_urlfilter_k_11"
#define ACCESS_CONTROL_URLFILTER_KEY_12_TOK         "ac_urlfilter_k_12"
#define ACCESS_CONTROL_URLFILTER_KEY_13_TOK         "ac_urlfilter_k_13"
#define ACCESS_CONTROL_URLFILTER_KEY_14_TOK         "ac_urlfilter_k_14"
#define ACCESS_CONTROL_URLFILTER_KEY_15_TOK         "ac_urlfilter_k_15"
#define ACCESS_CONTROL_URLFILTER_KEY_16_TOK         "ac_urlfilter_k_16"
#define ACCESS_CONTROL_URLFILTER_KEY_17_TOK         "ac_urlfilter_k_17"
#define ACCESS_CONTROL_URLFILTER_KEY_18_TOK         "ac_urlfilter_k_18"
#define ACCESS_CONTROL_URLFILTER_KEY_19_TOK         "ac_urlfilter_k_19"
#define ACCESS_CONTROL_URLFILTER_KEY_20_TOK         "ac_urlfilter_k_20"
#define ACCESS_CONTROL_URLFILTER_KEY_21_TOK         "ac_urlfilter_k_21"
#define ACCESS_CONTROL_URLFILTER_KEY_22_TOK         "ac_urlfilter_k_22"
#define ACCESS_CONTROL_URLFILTER_KEY_23_TOK         "ac_urlfilter_k_23"
#define ACCESS_CONTROL_URLFILTER_KEY_24_TOK         "ac_urlfilter_k_24"
#define ACCESS_CONTROL_URLFILTER_KEY_25_TOK         "ac_urlfilter_k_25"
#define ACCESS_CONTROL_URLFILTER_KEY_26_TOK         "ac_urlfilter_k_26"
#define ACCESS_CONTROL_URLFILTER_KEY_27_TOK         "ac_urlfilter_k_27"
#define ACCESS_CONTROL_URLFILTER_KEY_28_TOK         "ac_urlfilter_k_28"
#define ACCESS_CONTROL_URLFILTER_KEY_29_TOK         "ac_urlfilter_k_29"
#define ACCESS_CONTROL_URLFILTER_KEY_30_TOK         "ac_urlfilter_k_30"
#define ACCESS_CONTROL_URLFILTER_KEY_31_TOK         "ac_urlfilter_k_31"
#define ACCESS_CONTROL_URLFILTER_KEY_32_TOK         "ac_urlfilter_k_32"
#define ACCESS_CONTROL_URLFILTER_KEY_33_TOK         "ac_urlfilter_k_33"
#define ACCESS_CONTROL_URLFILTER_KEY_34_TOK         "ac_urlfilter_k_34"
#define ACCESS_CONTROL_URLFILTER_KEY_35_TOK         "ac_urlfilter_k_35"
#define ACCESS_CONTROL_URLFILTER_KEY_36_TOK         "ac_urlfilter_k_36"
#define ACCESS_CONTROL_URLFILTER_KEY_37_TOK         "ac_urlfilter_k_37"
#define ACCESS_CONTROL_URLFILTER_KEY_38_TOK         "ac_urlfilter_k_38"
#define ACCESS_CONTROL_URLFILTER_KEY_39_TOK         "ac_urlfilter_k_39"
#define ACCESS_CONTROL_URLFILTER_KEY_40_TOK         "ac_urlfilter_k_40"
#define ACCESS_CONTROL_URLFILTER_KEY_41_TOK         "ac_urlfilter_k_41"
#define ACCESS_CONTROL_URLFILTER_KEY_42_TOK         "ac_urlfilter_k_42"
#define ACCESS_CONTROL_URLFILTER_KEY_43_TOK         "ac_urlfilter_k_43"
#define ACCESS_CONTROL_URLFILTER_KEY_44_TOK         "ac_urlfilter_k_44"
#define ACCESS_CONTROL_URLFILTER_KEY_45_TOK         "ac_urlfilter_k_45"
#define ACCESS_CONTROL_URLFILTER_KEY_46_TOK         "ac_urlfilter_k_46"
#define ACCESS_CONTROL_URLFILTER_KEY_47_TOK         "ac_urlfilter_k_47"
#define ACCESS_CONTROL_URLFILTER_KEY_48_TOK         "ac_urlfilter_k_48"
#define ACCESS_CONTROL_URLFILTER_KEY_49_TOK         "ac_urlfilter_k_49"
#define ACCESS_CONTROL_URLFILTER_KEY_50_TOK         "ac_urlfilter_k_50"
#define ACCESS_CONTROL_URLFILTER_KEY_51_TOK         "ac_urlfilter_k_51"
#define ACCESS_CONTROL_URLFILTER_KEY_52_TOK         "ac_urlfilter_k_52"
#define ACCESS_CONTROL_URLFILTER_KEY_53_TOK         "ac_urlfilter_k_53"
#define ACCESS_CONTROL_URLFILTER_KEY_54_TOK         "ac_urlfilter_k_54"
#define ACCESS_CONTROL_URLFILTER_KEY_55_TOK         "ac_urlfilter_k_55"
#define ACCESS_CONTROL_URLFILTER_KEY_56_TOK         "ac_urlfilter_k_56"
#define ACCESS_CONTROL_URLFILTER_KEY_57_TOK         "ac_urlfilter_k_57"
#define ACCESS_CONTROL_URLFILTER_KEY_58_TOK         "ac_urlfilter_k_58"
#define ACCESS_CONTROL_URLFILTER_KEY_59_TOK         "ac_urlfilter_k_59"
#define ACCESS_CONTROL_URLFILTER_KEY_60_TOK         "ac_urlfilter_k_60"
#define ACCESS_CONTROL_URLFILTER_KEY_61_TOK         "ac_urlfilter_k_61"
#define ACCESS_CONTROL_URLFILTER_KEY_62_TOK         "ac_urlfilter_k_62"
#define ACCESS_CONTROL_URLFILTER_KEY_63_TOK         "ac_urlfilter_k_63"
#define ACCESS_CONTROL_URLFILTER_KEY_64_TOK         "ac_urlfilter_k_64"
#define ACCESS_CONTROL_URLFILTER_KEY_65_TOK         "ac_urlfilter_k_65"
#define ACCESS_CONTROL_URLFILTER_KEY_66_TOK         "ac_urlfilter_k_66"
#define ACCESS_CONTROL_URLFILTER_KEY_67_TOK         "ac_urlfilter_k_67"
#define ACCESS_CONTROL_URLFILTER_KEY_68_TOK         "ac_urlfilter_k_68"
#define ACCESS_CONTROL_URLFILTER_KEY_69_TOK         "ac_urlfilter_k_69"
#define ACCESS_CONTROL_URLFILTER_KEY_70_TOK         "ac_urlfilter_k_70"
#define ACCESS_CONTROL_URLFILTER_KEY_71_TOK         "ac_urlfilter_k_71"
#define ACCESS_CONTROL_URLFILTER_KEY_72_TOK         "ac_urlfilter_k_72"
#define ACCESS_CONTROL_URLFILTER_KEY_73_TOK         "ac_urlfilter_k_73"
#define ACCESS_CONTROL_URLFILTER_KEY_74_TOK         "ac_urlfilter_k_74"
#define ACCESS_CONTROL_URLFILTER_KEY_75_TOK         "ac_urlfilter_k_75"
#define ACCESS_CONTROL_URLFILTER_KEY_76_TOK         "ac_urlfilter_k_76"
#define ACCESS_CONTROL_URLFILTER_KEY_77_TOK         "ac_urlfilter_k_77"
#define ACCESS_CONTROL_URLFILTER_KEY_78_TOK         "ac_urlfilter_k_78"
#define ACCESS_CONTROL_URLFILTER_KEY_79_TOK         "ac_urlfilter_k_79"
#define ACCESS_CONTROL_URLFILTER_KEY_80_TOK         "ac_urlfilter_k_80"
#define ACCESS_CONTROL_URLFILTER_KEY_81_TOK         "ac_urlfilter_k_81"
#define ACCESS_CONTROL_URLFILTER_KEY_82_TOK         "ac_urlfilter_k_82"
#define ACCESS_CONTROL_URLFILTER_KEY_83_TOK         "ac_urlfilter_k_83"
#define ACCESS_CONTROL_URLFILTER_KEY_84_TOK         "ac_urlfilter_k_84"
#define ACCESS_CONTROL_URLFILTER_KEY_85_TOK         "ac_urlfilter_k_85"
#define ACCESS_CONTROL_URLFILTER_KEY_86_TOK         "ac_urlfilter_k_86"
#define ACCESS_CONTROL_URLFILTER_KEY_87_TOK         "ac_urlfilter_k_87"
#define ACCESS_CONTROL_URLFILTER_KEY_88_TOK         "ac_urlfilter_k_88"
#define ACCESS_CONTROL_URLFILTER_KEY_89_TOK         "ac_urlfilter_k_89"
#define ACCESS_CONTROL_URLFILTER_KEY_90_TOK         "ac_urlfilter_k_90"
#define ACCESS_CONTROL_URLFILTER_KEY_91_TOK         "ac_urlfilter_k_91"
#define ACCESS_CONTROL_URLFILTER_KEY_92_TOK         "ac_urlfilter_k_92"
#define ACCESS_CONTROL_URLFILTER_KEY_93_TOK         "ac_urlfilter_k_93"
#define ACCESS_CONTROL_URLFILTER_KEY_94_TOK         "ac_urlfilter_k_94"
#define ACCESS_CONTROL_URLFILTER_KEY_95_TOK         "ac_urlfilter_k_95"
#define ACCESS_CONTROL_URLFILTER_KEY_96_TOK         "ac_urlfilter_k_96"
#define ACCESS_CONTROL_URLFILTER_KEY_97_TOK         "ac_urlfilter_k_97"
#define ACCESS_CONTROL_URLFILTER_KEY_98_TOK         "ac_urlfilter_k_98"
#define ACCESS_CONTROL_URLFILTER_KEY_99_TOK         "ac_urlfilter_k_99"
#define ACCESS_CONTROL_URLFILTER_KEY_100_TOK        "ac_urlfilter_k_100"
#define ACCESS_CONTROL_URLFILTER_KEY_101_TOK        "ac_urlfilter_k_101"
#define ACCESS_CONTROL_URLFILTER_KEY_102_TOK        "ac_urlfilter_k_102"
#define ACCESS_CONTROL_URLFILTER_KEY_103_TOK        "ac_urlfilter_k_103"
#define ACCESS_CONTROL_URLFILTER_KEY_104_TOK        "ac_urlfilter_k_104"
#define ACCESS_CONTROL_URLFILTER_KEY_105_TOK        "ac_urlfilter_k_105"
#define ACCESS_CONTROL_URLFILTER_KEY_106_TOK        "ac_urlfilter_k_106"
#define ACCESS_CONTROL_URLFILTER_KEY_107_TOK        "ac_urlfilter_k_107"
#define ACCESS_CONTROL_URLFILTER_KEY_108_TOK        "ac_urlfilter_k_108"
#define ACCESS_CONTROL_URLFILTER_KEY_109_TOK        "ac_urlfilter_k_109"
#define ACCESS_CONTROL_URLFILTER_KEY_110_TOK        "ac_urlfilter_k_110"
#define ACCESS_CONTROL_URLFILTER_KEY_111_TOK        "ac_urlfilter_k_111"
#define ACCESS_CONTROL_URLFILTER_KEY_112_TOK        "ac_urlfilter_k_112"
#define ACCESS_CONTROL_URLFILTER_KEY_113_TOK        "ac_urlfilter_k_113"
#define ACCESS_CONTROL_URLFILTER_KEY_114_TOK        "ac_urlfilter_k_114"
#define ACCESS_CONTROL_URLFILTER_KEY_115_TOK        "ac_urlfilter_k_115"
#define ACCESS_CONTROL_URLFILTER_KEY_116_TOK        "ac_urlfilter_k_116"
#define ACCESS_CONTROL_URLFILTER_KEY_117_TOK        "ac_urlfilter_k_117"
#define ACCESS_CONTROL_URLFILTER_KEY_118_TOK        "ac_urlfilter_k_118"
#define ACCESS_CONTROL_URLFILTER_KEY_119_TOK        "ac_urlfilter_k_119"
#define ACCESS_CONTROL_URLFILTER_KEY_120_TOK        "ac_urlfilter_k_120"
#define ACCESS_CONTROL_URLFILTER_KEY_121_TOK        "ac_urlfilter_k_121"
#define ACCESS_CONTROL_URLFILTER_KEY_122_TOK        "ac_urlfilter_k_122"
#define ACCESS_CONTROL_URLFILTER_KEY_123_TOK        "ac_urlfilter_k_123"
#define ACCESS_CONTROL_URLFILTER_KEY_124_TOK        "ac_urlfilter_k_124"
#define ACCESS_CONTROL_URLFILTER_KEY_125_TOK        "ac_urlfilter_k_125"
#define ACCESS_CONTROL_URLFILTER_KEY_126_TOK        "ac_urlfilter_k_126"
#define ACCESS_CONTROL_URLFILTER_KEY_127_TOK        "ac_urlfilter_k_127"
#define ACCESS_CONTROL_URLFILTER_KEY_128_TOK        "ac_urlfilter_k_128"
#define ACCESS_CONTROL_URLFILTER_KEY_129_TOK        "ac_urlfilter_k_129"
#define ACCESS_CONTROL_URLFILTER_KEY_130_TOK        "ac_urlfilter_k_130"
#define ACCESS_CONTROL_URLFILTER_KEY_131_TOK        "ac_urlfilter_k_131"
#define ACCESS_CONTROL_URLFILTER_KEY_132_TOK        "ac_urlfilter_k_132"
#define ACCESS_CONTROL_URLFILTER_KEY_133_TOK        "ac_urlfilter_k_133"
#define ACCESS_CONTROL_URLFILTER_KEY_134_TOK        "ac_urlfilter_k_134"
#define ACCESS_CONTROL_URLFILTER_KEY_135_TOK        "ac_urlfilter_k_135"
#define ACCESS_CONTROL_URLFILTER_KEY_136_TOK        "ac_urlfilter_k_136"
#define ACCESS_CONTROL_URLFILTER_KEY_137_TOK        "ac_urlfilter_k_137"
#define ACCESS_CONTROL_URLFILTER_KEY_138_TOK        "ac_urlfilter_k_138"
#define ACCESS_CONTROL_URLFILTER_KEY_139_TOK        "ac_urlfilter_k_139"
#define ACCESS_CONTROL_URLFILTER_KEY_140_TOK        "ac_urlfilter_k_140"
#define ACCESS_CONTROL_URLFILTER_KEY_141_TOK        "ac_urlfilter_k_141"
#define ACCESS_CONTROL_URLFILTER_KEY_142_TOK        "ac_urlfilter_k_142"
#define ACCESS_CONTROL_URLFILTER_KEY_143_TOK        "ac_urlfilter_k_143"
#define ACCESS_CONTROL_URLFILTER_KEY_144_TOK        "ac_urlfilter_k_144"
#define ACCESS_CONTROL_URLFILTER_KEY_145_TOK        "ac_urlfilter_k_145"
#define ACCESS_CONTROL_URLFILTER_KEY_146_TOK        "ac_urlfilter_k_146"
#define ACCESS_CONTROL_URLFILTER_KEY_147_TOK        "ac_urlfilter_k_147"
#define ACCESS_CONTROL_URLFILTER_KEY_148_TOK        "ac_urlfilter_k_148"
#define ACCESS_CONTROL_URLFILTER_KEY_149_TOK        "ac_urlfilter_k_149"
#define ACCESS_CONTROL_URLFILTER_KEY_150_TOK        "ac_urlfilter_k_150"
#define ACCESS_CONTROL_URLFILTER_KEY_151_TOK        "ac_urlfilter_k_151"
#define ACCESS_CONTROL_URLFILTER_KEY_152_TOK        "ac_urlfilter_k_152"
#define ACCESS_CONTROL_URLFILTER_KEY_153_TOK        "ac_urlfilter_k_153"
#define ACCESS_CONTROL_URLFILTER_KEY_154_TOK        "ac_urlfilter_k_154"
#define ACCESS_CONTROL_URLFILTER_KEY_155_TOK        "ac_urlfilter_k_155"
#define ACCESS_CONTROL_URLFILTER_KEY_156_TOK        "ac_urlfilter_k_156"
#define ACCESS_CONTROL_URLFILTER_KEY_157_TOK        "ac_urlfilter_k_157"
#define ACCESS_CONTROL_URLFILTER_KEY_158_TOK        "ac_urlfilter_k_158"
#define ACCESS_CONTROL_URLFILTER_KEY_159_TOK        "ac_urlfilter_k_159"
#define ACCESS_CONTROL_URLFILTER_KEY_160_TOK        "ac_urlfilter_k_160"
#define ACCESS_CONTROL_URLFILTER_KEY_161_TOK        "ac_urlfilter_k_161"
#define ACCESS_CONTROL_URLFILTER_KEY_162_TOK        "ac_urlfilter_k_162"
#define ACCESS_CONTROL_URLFILTER_KEY_163_TOK        "ac_urlfilter_k_163"
#define ACCESS_CONTROL_URLFILTER_KEY_164_TOK        "ac_urlfilter_k_164"
#define ACCESS_CONTROL_URLFILTER_KEY_165_TOK        "ac_urlfilter_k_165"
#define ACCESS_CONTROL_URLFILTER_KEY_166_TOK        "ac_urlfilter_k_166"
#define ACCESS_CONTROL_URLFILTER_KEY_167_TOK        "ac_urlfilter_k_167"
#define ACCESS_CONTROL_URLFILTER_KEY_168_TOK        "ac_urlfilter_k_168"
#define ACCESS_CONTROL_URLFILTER_KEY_169_TOK        "ac_urlfilter_k_169"
#define ACCESS_CONTROL_URLFILTER_KEY_170_TOK        "ac_urlfilter_k_170"
#define ACCESS_CONTROL_URLFILTER_KEY_171_TOK        "ac_urlfilter_k_171"
#define ACCESS_CONTROL_URLFILTER_KEY_172_TOK        "ac_urlfilter_k_172"
#define ACCESS_CONTROL_URLFILTER_KEY_173_TOK        "ac_urlfilter_k_173"
#define ACCESS_CONTROL_URLFILTER_KEY_174_TOK        "ac_urlfilter_k_174"
#define ACCESS_CONTROL_URLFILTER_KEY_175_TOK        "ac_urlfilter_k_175"
#define ACCESS_CONTROL_URLFILTER_KEY_176_TOK        "ac_urlfilter_k_176"
#define ACCESS_CONTROL_URLFILTER_KEY_177_TOK        "ac_urlfilter_k_177"
#define ACCESS_CONTROL_URLFILTER_KEY_178_TOK        "ac_urlfilter_k_178"
#define ACCESS_CONTROL_URLFILTER_KEY_179_TOK        "ac_urlfilter_k_179"
#define ACCESS_CONTROL_URLFILTER_KEY_180_TOK        "ac_urlfilter_k_180"
#define ACCESS_CONTROL_URLFILTER_KEY_181_TOK        "ac_urlfilter_k_181"
#define ACCESS_CONTROL_URLFILTER_KEY_182_TOK        "ac_urlfilter_k_182"
#define ACCESS_CONTROL_URLFILTER_KEY_183_TOK        "ac_urlfilter_k_183"
#define ACCESS_CONTROL_URLFILTER_KEY_184_TOK        "ac_urlfilter_k_184"
#define ACCESS_CONTROL_URLFILTER_KEY_185_TOK        "ac_urlfilter_k_185"
#define ACCESS_CONTROL_URLFILTER_KEY_186_TOK        "ac_urlfilter_k_186"
#define ACCESS_CONTROL_URLFILTER_KEY_187_TOK        "ac_urlfilter_k_187"
#define ACCESS_CONTROL_URLFILTER_KEY_188_TOK        "ac_urlfilter_k_188"
#define ACCESS_CONTROL_URLFILTER_KEY_189_TOK        "ac_urlfilter_k_189"
#define ACCESS_CONTROL_URLFILTER_KEY_190_TOK        "ac_urlfilter_k_190"
#define ACCESS_CONTROL_URLFILTER_KEY_191_TOK        "ac_urlfilter_k_191"
#define ACCESS_CONTROL_URLFILTER_KEY_192_TOK        "ac_urlfilter_k_192"
#define ACCESS_CONTROL_URLFILTER_KEY_193_TOK        "ac_urlfilter_k_193"
#define ACCESS_CONTROL_URLFILTER_KEY_194_TOK        "ac_urlfilter_k_194"
#define ACCESS_CONTROL_URLFILTER_KEY_195_TOK        "ac_urlfilter_k_195"
#define ACCESS_CONTROL_URLFILTER_KEY_196_TOK        "ac_urlfilter_k_196"
#define ACCESS_CONTROL_URLFILTER_KEY_197_TOK        "ac_urlfilter_k_197"
#define ACCESS_CONTROL_URLFILTER_KEY_198_TOK        "ac_urlfilter_k_198"
#define ACCESS_CONTROL_URLFILTER_KEY_199_TOK        "ac_urlfilter_k_199"
#define ACCESS_CONTROL_URLFILTER_KEY_200_TOK        "ac_urlfilter_k_200"
#endif

#if HAS_CAFE_MODE
#define CAFE_MODE_MAC_TOK		"cafe_mac_"
#define CAFE_MODE_MAC_01_TOK	"cafe_mac_1"
#define CAFE_MODE_MAC_02_TOK    "cafe_mac_2"
#define CAFE_MODE_MAC_03_TOK	"cafe_mac_3"
#define CAFE_MODE_MAC_04_TOK	"cafe_mac_4"
#define CAFE_MODE_MAC_05_TOK	"cafe_mac_5"
#define CAFE_MODE_MAC_06_TOK	"cafe_mac_6"
#define CAFE_MODE_MAC_07_TOK	"cafe_mac_7"
#define CAFE_MODE_MAC_08_TOK	"cafe_mac_8"
#endif

#if HAS_PARENTAL_CONTROL
#define PARENTAL_CONTROL_ENABLE_TOK        "parentalctrl_en"
#define PARENTAL_CONTROL_TOK               "parentalctrl_"
#define PARENTAL_CONTROL_01_TOK            "parentalctrl_1"
#define PARENTAL_CONTROL_02_TOK            "parentalctrl_2"
#define PARENTAL_CONTROL_03_TOK            "parentalctrl_3"
#define PARENTAL_CONTROL_04_TOK            "parentalctrl_4"
#define PARENTAL_CONTROL_05_TOK            "parentalctrl_5"
#define PARENTAL_CONTROL_06_TOK            "parentalctrl_6"
#define PARENTAL_CONTROL_07_TOK            "parentalctrl_7"
#define PARENTAL_CONTROL_08_TOK            "parentalctrl_8"
#define PARENTAL_CONTROL_09_TOK            "parentalctrl_9"
#define PARENTAL_CONTROL_10_TOK            "parentalctrl_10"
#define PARENTAL_CONTROL_11_TOK            "parentalctrl_11"
#define PARENTAL_CONTROL_12_TOK            "parentalctrl_12"
#define PARENTAL_CONTROL_13_TOK            "parentalctrl_13"
#define PARENTAL_CONTROL_14_TOK            "parentalctrl_14"
#define PARENTAL_CONTROL_15_TOK            "parentalctrl_15"
#define PARENTAL_CONTROL_16_TOK            "parentalctrl_16"
#define PARENTAL_CONTROL_DEF_TOK            "parentalctrl_def_"
#define PARENTAL_CONTROL_DEF_01_TOK            "parentalctrl_def_1"

#define PARENTAL_CONTROL_MAC_TOK               "pc_mac_"
#define PARENTAL_CONTROL_MAC_01_TOK            "pc_mac_1"
#define PARENTAL_CONTROL_MAC_02_TOK            "pc_mac_2"
#define PARENTAL_CONTROL_MAC_03_TOK            "pc_mac_3"
#define PARENTAL_CONTROL_MAC_04_TOK            "pc_mac_4"
#define PARENTAL_CONTROL_MAC_05_TOK            "pc_mac_5"
#define PARENTAL_CONTROL_MAC_06_TOK            "pc_mac_6"
#define PARENTAL_CONTROL_MAC_07_TOK            "pc_mac_7"
#define PARENTAL_CONTROL_MAC_08_TOK            "pc_mac_8"
#define PARENTAL_CONTROL_MAC_09_TOK            "pc_mac_9"
#define PARENTAL_CONTROL_MAC_10_TOK            "pc_mac_10"
#define PARENTAL_CONTROL_MAC_11_TOK            "pc_mac_11"
#define PARENTAL_CONTROL_MAC_12_TOK            "pc_mac_12"
#define PARENTAL_CONTROL_MAC_13_TOK            "pc_mac_13"
#define PARENTAL_CONTROL_MAC_14_TOK            "pc_mac_14"
#define PARENTAL_CONTROL_MAC_15_TOK            "pc_mac_15"
#define PARENTAL_CONTROL_MAC_16_TOK            "pc_mac_16"
#define PARENTAL_CONTROL_MAC_17_TOK            "pc_mac_17"
#define PARENTAL_CONTROL_MAC_18_TOK            "pc_mac_18"
#define PARENTAL_CONTROL_MAC_19_TOK            "pc_mac_19"
#define PARENTAL_CONTROL_MAC_20_TOK            "pc_mac_20"
#define PARENTAL_CONTROL_MAC_21_TOK            "pc_mac_21"
#define PARENTAL_CONTROL_MAC_22_TOK            "pc_mac_22"
#define PARENTAL_CONTROL_MAC_23_TOK            "pc_mac_23"
#define PARENTAL_CONTROL_MAC_24_TOK            "pc_mac_24"
#define PARENTAL_CONTROL_MAC_25_TOK            "pc_mac_25"
#define PARENTAL_CONTROL_MAC_26_TOK            "pc_mac_26"
#define PARENTAL_CONTROL_MAC_27_TOK            "pc_mac_27"
#define PARENTAL_CONTROL_MAC_28_TOK            "pc_mac_28"
#define PARENTAL_CONTROL_MAC_29_TOK            "pc_mac_29"
#define PARENTAL_CONTROL_MAC_30_TOK            "pc_mac_30"
#define PARENTAL_CONTROL_MAC_31_TOK            "pc_mac_31"
#define PARENTAL_CONTROL_MAC_32_TOK            "pc_mac_32"
#define PARENTAL_CONTROL_MAC_33_TOK            "pc_mac_33"
#define PARENTAL_CONTROL_MAC_34_TOK            "pc_mac_34"
#define PARENTAL_CONTROL_MAC_35_TOK            "pc_mac_35"
#define PARENTAL_CONTROL_MAC_36_TOK            "pc_mac_36"
#define PARENTAL_CONTROL_MAC_37_TOK            "pc_mac_37"
#define PARENTAL_CONTROL_MAC_38_TOK            "pc_mac_38"
#define PARENTAL_CONTROL_MAC_39_TOK            "pc_mac_39"
#define PARENTAL_CONTROL_MAC_40_TOK            "pc_mac_40"
#define PARENTAL_CONTROL_MAC_41_TOK            "pc_mac_41"
#define PARENTAL_CONTROL_MAC_42_TOK            "pc_mac_42"
#define PARENTAL_CONTROL_MAC_43_TOK            "pc_mac_43"
#define PARENTAL_CONTROL_MAC_44_TOK            "pc_mac_44"
#define PARENTAL_CONTROL_MAC_45_TOK            "pc_mac_45"
#define PARENTAL_CONTROL_MAC_46_TOK            "pc_mac_46"
#define PARENTAL_CONTROL_MAC_47_TOK            "pc_mac_47"
#define PARENTAL_CONTROL_MAC_48_TOK            "pc_mac_48"
#define PARENTAL_CONTROL_MAC_49_TOK            "pc_mac_49"
#define PARENTAL_CONTROL_MAC_50_TOK            "pc_mac_50"
#define PARENTAL_CONTROL_MAC_51_TOK            "pc_mac_51"
#define PARENTAL_CONTROL_MAC_52_TOK            "pc_mac_52"
#define PARENTAL_CONTROL_MAC_53_TOK            "pc_mac_53"
#define PARENTAL_CONTROL_MAC_54_TOK            "pc_mac_54"
#define PARENTAL_CONTROL_MAC_55_TOK            "pc_mac_55"
#define PARENTAL_CONTROL_MAC_56_TOK            "pc_mac_56"
#define PARENTAL_CONTROL_MAC_57_TOK            "pc_mac_57"
#define PARENTAL_CONTROL_MAC_58_TOK            "pc_mac_58"
#define PARENTAL_CONTROL_MAC_59_TOK            "pc_mac_59"
#define PARENTAL_CONTROL_MAC_60_TOK            "pc_mac_60"
#define PARENTAL_CONTROL_MAC_61_TOK            "pc_mac_61"
#define PARENTAL_CONTROL_MAC_62_TOK            "pc_mac_62"
#define PARENTAL_CONTROL_MAC_63_TOK            "pc_mac_63"
#define PARENTAL_CONTROL_MAC_64_TOK            "pc_mac_64"
#define PARENTAL_CONTROL_MAC_DEF_TOK               "pc_mac_def_"
#define PARENTAL_CONTROL_MAC_DEF_01_TOK            "pc_mac_def_1"
#define PARENTAL_CONTROL_MAC_DEF_02_TOK            "pc_mac_def_2"
#define PARENTAL_CONTROL_MAC_DEF_03_TOK            "pc_mac_def_3"
#define PARENTAL_CONTROL_MAC_DEF_04_TOK            "pc_mac_def_4"

#define PARENTAL_CONTROL_IP_TOK               "pc_ip_"
#define PARENTAL_CONTROL_IP_01_TOK            "pc_ip_1"
#define PARENTAL_CONTROL_IP_02_TOK            "pc_ip_2"
#define PARENTAL_CONTROL_IP_03_TOK            "pc_ip_3"
#define PARENTAL_CONTROL_IP_04_TOK            "pc_ip_4"
#define PARENTAL_CONTROL_IP_05_TOK            "pc_ip_5"
#define PARENTAL_CONTROL_IP_06_TOK            "pc_ip_6"
#define PARENTAL_CONTROL_IP_07_TOK            "pc_ip_7"
#define PARENTAL_CONTROL_IP_08_TOK            "pc_ip_8"
#define PARENTAL_CONTROL_IP_09_TOK            "pc_ip_9"
#define PARENTAL_CONTROL_IP_10_TOK            "pc_ip_10"
#define PARENTAL_CONTROL_IP_11_TOK            "pc_ip_11"
#define PARENTAL_CONTROL_IP_12_TOK            "pc_ip_12"
#define PARENTAL_CONTROL_IP_13_TOK            "pc_ip_13"
#define PARENTAL_CONTROL_IP_14_TOK            "pc_ip_14"
#define PARENTAL_CONTROL_IP_15_TOK            "pc_ip_15"
#define PARENTAL_CONTROL_IP_16_TOK            "pc_ip_16"
#define PARENTAL_CONTROL_IP_17_TOK            "pc_ip_17"
#define PARENTAL_CONTROL_IP_18_TOK            "pc_ip_18"
#define PARENTAL_CONTROL_IP_19_TOK            "pc_ip_19"
#define PARENTAL_CONTROL_IP_20_TOK            "pc_ip_20"
#define PARENTAL_CONTROL_IP_21_TOK            "pc_ip_21"
#define PARENTAL_CONTROL_IP_22_TOK            "pc_ip_22"
#define PARENTAL_CONTROL_IP_23_TOK            "pc_ip_23"
#define PARENTAL_CONTROL_IP_24_TOK            "pc_ip_24"
#define PARENTAL_CONTROL_IP_25_TOK            "pc_ip_25"
#define PARENTAL_CONTROL_IP_26_TOK            "pc_ip_26"
#define PARENTAL_CONTROL_IP_27_TOK            "pc_ip_27"
#define PARENTAL_CONTROL_IP_28_TOK            "pc_ip_28"
#define PARENTAL_CONTROL_IP_29_TOK            "pc_ip_29"
#define PARENTAL_CONTROL_IP_30_TOK            "pc_ip_30"
#define PARENTAL_CONTROL_IP_31_TOK            "pc_ip_31"
#define PARENTAL_CONTROL_IP_32_TOK            "pc_ip_32"
#define PARENTAL_CONTROL_IP_33_TOK            "pc_ip_33"
#define PARENTAL_CONTROL_IP_34_TOK            "pc_ip_34"
#define PARENTAL_CONTROL_IP_35_TOK            "pc_ip_35"
#define PARENTAL_CONTROL_IP_36_TOK            "pc_ip_36"
#define PARENTAL_CONTROL_IP_37_TOK            "pc_ip_37"
#define PARENTAL_CONTROL_IP_38_TOK            "pc_ip_38"
#define PARENTAL_CONTROL_IP_39_TOK            "pc_ip_39"
#define PARENTAL_CONTROL_IP_40_TOK            "pc_ip_40"
#define PARENTAL_CONTROL_IP_41_TOK            "pc_ip_41"
#define PARENTAL_CONTROL_IP_42_TOK            "pc_ip_42"
#define PARENTAL_CONTROL_IP_43_TOK            "pc_ip_43"
#define PARENTAL_CONTROL_IP_44_TOK            "pc_ip_44"
#define PARENTAL_CONTROL_IP_45_TOK            "pc_ip_45"
#define PARENTAL_CONTROL_IP_46_TOK            "pc_ip_46"
#define PARENTAL_CONTROL_IP_47_TOK            "pc_ip_47"
#define PARENTAL_CONTROL_IP_48_TOK            "pc_ip_48"
#define PARENTAL_CONTROL_IP_49_TOK            "pc_ip_49"
#define PARENTAL_CONTROL_IP_50_TOK            "pc_ip_50"
#define PARENTAL_CONTROL_IP_51_TOK            "pc_ip_51"
#define PARENTAL_CONTROL_IP_52_TOK            "pc_ip_52"
#define PARENTAL_CONTROL_IP_53_TOK            "pc_ip_53"
#define PARENTAL_CONTROL_IP_54_TOK            "pc_ip_54"
#define PARENTAL_CONTROL_IP_55_TOK            "pc_ip_55"
#define PARENTAL_CONTROL_IP_56_TOK            "pc_ip_56"
#define PARENTAL_CONTROL_IP_57_TOK            "pc_ip_57"
#define PARENTAL_CONTROL_IP_58_TOK            "pc_ip_58"
#define PARENTAL_CONTROL_IP_59_TOK            "pc_ip_59"
#define PARENTAL_CONTROL_IP_60_TOK            "pc_ip_60"
#define PARENTAL_CONTROL_IP_61_TOK            "pc_ip_61"
#define PARENTAL_CONTROL_IP_62_TOK            "pc_ip_62"
#define PARENTAL_CONTROL_IP_63_TOK            "pc_ip_63"
#define PARENTAL_CONTROL_IP_64_TOK            "pc_ip_64"
#define PARENTAL_CONTROL_IP_DEF_TOK               "pc_ip_def_"
#define PARENTAL_CONTROL_IP_DEF_01_TOK            "pc_ip_def_1"
#define PARENTAL_CONTROL_IP_DEF_02_TOK            "pc_ip_def_2"
#define PARENTAL_CONTROL_IP_DEF_03_TOK            "pc_ip_def_3"
#define PARENTAL_CONTROL_IP_DEF_04_TOK            "pc_ip_def_4"

#define PARENTAL_CONTROL_SERVICE_TOK       "pc_service_"
#define PARENTAL_CONTROL_SERVICE_01_TOK    "pc_service_1"
#define PARENTAL_CONTROL_SERVICE_02_TOK    "pc_service_2"
#define PARENTAL_CONTROL_SERVICE_03_TOK    "pc_service_3"
#define PARENTAL_CONTROL_SERVICE_04_TOK    "pc_service_4"
#define PARENTAL_CONTROL_SERVICE_05_TOK    "pc_service_5"
#define PARENTAL_CONTROL_SERVICE_06_TOK    "pc_service_6"
#define PARENTAL_CONTROL_SERVICE_07_TOK    "pc_service_7"
#define PARENTAL_CONTROL_SERVICE_08_TOK    "pc_service_8"
#define PARENTAL_CONTROL_SERVICE_09_TOK    "pc_service_9"
#define PARENTAL_CONTROL_SERVICE_10_TOK    "pc_service_10"
#define PARENTAL_CONTROL_SERVICE_11_TOK    "pc_service_11"
#define PARENTAL_CONTROL_SERVICE_12_TOK    "pc_service_12"
#define PARENTAL_CONTROL_SERVICE_13_TOK    "pc_service_13"
#define PARENTAL_CONTROL_SERVICE_14_TOK    "pc_service_14"
#define PARENTAL_CONTROL_SERVICE_15_TOK    "pc_service_15"
#define PARENTAL_CONTROL_SERVICE_16_TOK    "pc_service_16"
#define PARENTAL_CONTROL_SERVICE_17_TOK    "pc_service_17"
#define PARENTAL_CONTROL_SERVICE_18_TOK    "pc_service_18"
#define PARENTAL_CONTROL_SERVICE_19_TOK    "pc_service_19"
#define PARENTAL_CONTROL_SERVICE_20_TOK    "pc_service_20"
#define PARENTAL_CONTROL_SERVICE_21_TOK    "pc_service_21"
#define PARENTAL_CONTROL_SERVICE_22_TOK    "pc_service_22"
#define PARENTAL_CONTROL_SERVICE_23_TOK    "pc_service_23"
#define PARENTAL_CONTROL_SERVICE_24_TOK    "pc_service_24"
#define PARENTAL_CONTROL_SERVICE_25_TOK    "pc_service_25"
#define PARENTAL_CONTROL_SERVICE_26_TOK    "pc_service_26"
#define PARENTAL_CONTROL_SERVICE_27_TOK    "pc_service_27"
#define PARENTAL_CONTROL_SERVICE_28_TOK    "pc_service_28"
#define PARENTAL_CONTROL_SERVICE_29_TOK    "pc_service_29"
#define PARENTAL_CONTROL_SERVICE_30_TOK    "pc_service_30"
#define PARENTAL_CONTROL_SERVICE_31_TOK    "pc_service_31"
#define PARENTAL_CONTROL_SERVICE_32_TOK    "pc_service_32"

#define PARENTAL_CONTROL_URLFILTER_TOK     "pc_urlfilter_"
#define PARENTAL_CONTROL_URLFILTER_01_TOK  "pc_urlfilter_1"
#define PARENTAL_CONTROL_URLFILTER_02_TOK  "pc_urlfilter_2"
#define PARENTAL_CONTROL_URLFILTER_03_TOK  "pc_urlfilter_3"
#define PARENTAL_CONTROL_URLFILTER_04_TOK  "pc_urlfilter_4"
#define PARENTAL_CONTROL_URLFILTER_05_TOK  "pc_urlfilter_5"
#define PARENTAL_CONTROL_URLFILTER_06_TOK  "pc_urlfilter_6"
#define PARENTAL_CONTROL_URLFILTER_07_TOK  "pc_urlfilter_7"
#define PARENTAL_CONTROL_URLFILTER_08_TOK  "pc_urlfilter_8"
#define PARENTAL_CONTROL_URLFILTER_09_TOK  "pc_urlfilter_9"
#define PARENTAL_CONTROL_URLFILTER_10_TOK  "pc_urlfilter_10"
#define PARENTAL_CONTROL_URLFILTER_11_TOK  "pc_urlfilter_11"
#define PARENTAL_CONTROL_URLFILTER_12_TOK  "pc_urlfilter_12"
#define PARENTAL_CONTROL_URLFILTER_13_TOK  "pc_urlfilter_13"
#define PARENTAL_CONTROL_URLFILTER_14_TOK  "pc_urlfilter_14"
#define PARENTAL_CONTROL_URLFILTER_15_TOK  "pc_urlfilter_15"
#define PARENTAL_CONTROL_URLFILTER_16_TOK  "pc_urlfilter_16"
#define PARENTAL_CONTROL_URLFILTER_17_TOK  "pc_urlfilter_17"
#define PARENTAL_CONTROL_URLFILTER_18_TOK  "pc_urlfilter_18"
#define PARENTAL_CONTROL_URLFILTER_19_TOK  "pc_urlfilter_19"
#define PARENTAL_CONTROL_URLFILTER_20_TOK  "pc_urlfilter_20"
#define PARENTAL_CONTROL_URLFILTER_21_TOK  "pc_urlfilter_21"
#define PARENTAL_CONTROL_URLFILTER_22_TOK  "pc_urlfilter_22"
#define PARENTAL_CONTROL_URLFILTER_23_TOK  "pc_urlfilter_23"
#define PARENTAL_CONTROL_URLFILTER_24_TOK  "pc_urlfilter_24"
#define PARENTAL_CONTROL_URLFILTER_25_TOK  "pc_urlfilter_25"
#define PARENTAL_CONTROL_URLFILTER_26_TOK  "pc_urlfilter_26"
#define PARENTAL_CONTROL_URLFILTER_27_TOK  "pc_urlfilter_27"
#define PARENTAL_CONTROL_URLFILTER_28_TOK  "pc_urlfilter_28"
#define PARENTAL_CONTROL_URLFILTER_29_TOK  "pc_urlfilter_29"
#define PARENTAL_CONTROL_URLFILTER_30_TOK  "pc_urlfilter_30"
#define PARENTAL_CONTROL_URLFILTER_31_TOK  "pc_urlfilter_31"
#define PARENTAL_CONTROL_URLFILTER_32_TOK  "pc_urlfilter_32"
#define PARENTAL_CONTROL_URLFILTER_33_TOK  "pc_urlfilter_33"
#define PARENTAL_CONTROL_URLFILTER_34_TOK  "pc_urlfilter_34"
#define PARENTAL_CONTROL_URLFILTER_35_TOK  "pc_urlfilter_35"
#define PARENTAL_CONTROL_URLFILTER_36_TOK  "pc_urlfilter_36"
#define PARENTAL_CONTROL_URLFILTER_37_TOK  "pc_urlfilter_37"
#define PARENTAL_CONTROL_URLFILTER_38_TOK  "pc_urlfilter_38"
#define PARENTAL_CONTROL_URLFILTER_39_TOK  "pc_urlfilter_39"
#define PARENTAL_CONTROL_URLFILTER_40_TOK  "pc_urlfilter_40"
#define PARENTAL_CONTROL_URLFILTER_41_TOK  "pc_urlfilter_41"
#define PARENTAL_CONTROL_URLFILTER_42_TOK  "pc_urlfilter_42"
#define PARENTAL_CONTROL_URLFILTER_43_TOK  "pc_urlfilter_43"
#define PARENTAL_CONTROL_URLFILTER_44_TOK  "pc_urlfilter_44"
#define PARENTAL_CONTROL_URLFILTER_45_TOK  "pc_urlfilter_45"
#define PARENTAL_CONTROL_URLFILTER_46_TOK  "pc_urlfilter_46"
#define PARENTAL_CONTROL_URLFILTER_47_TOK  "pc_urlfilter_47"
#define PARENTAL_CONTROL_URLFILTER_48_TOK  "pc_urlfilter_48"
#define PARENTAL_CONTROL_URLFILTER_49_TOK  "pc_urlfilter_49"
#define PARENTAL_CONTROL_URLFILTER_50_TOK  "pc_urlfilter_50"
#define PARENTAL_CONTROL_URLFILTER_51_TOK  "pc_urlfilter_51"
#define PARENTAL_CONTROL_URLFILTER_52_TOK  "pc_urlfilter_52"
#define PARENTAL_CONTROL_URLFILTER_53_TOK  "pc_urlfilter_53"
#define PARENTAL_CONTROL_URLFILTER_54_TOK  "pc_urlfilter_54"
#define PARENTAL_CONTROL_URLFILTER_55_TOK  "pc_urlfilter_55"
#define PARENTAL_CONTROL_URLFILTER_56_TOK  "pc_urlfilter_56"
#define PARENTAL_CONTROL_URLFILTER_57_TOK  "pc_urlfilter_57"
#define PARENTAL_CONTROL_URLFILTER_58_TOK  "pc_urlfilter_58"
#define PARENTAL_CONTROL_URLFILTER_59_TOK  "pc_urlfilter_59"
#define PARENTAL_CONTROL_URLFILTER_60_TOK  "pc_urlfilter_60"
#define PARENTAL_CONTROL_URLFILTER_61_TOK  "pc_urlfilter_61"
#define PARENTAL_CONTROL_URLFILTER_62_TOK  "pc_urlfilter_62"
#define PARENTAL_CONTROL_URLFILTER_63_TOK  "pc_urlfilter_63"
#define PARENTAL_CONTROL_URLFILTER_64_TOK  "pc_urlfilter_64"
#define PARENTAL_CONTROL_URLFILTER_65_TOK  "pc_urlfilter_65"
#define PARENTAL_CONTROL_URLFILTER_66_TOK  "pc_urlfilter_66"
#define PARENTAL_CONTROL_URLFILTER_67_TOK  "pc_urlfilter_67"
#define PARENTAL_CONTROL_URLFILTER_68_TOK  "pc_urlfilter_68"
#define PARENTAL_CONTROL_URLFILTER_69_TOK  "pc_urlfilter_69"
#define PARENTAL_CONTROL_URLFILTER_70_TOK  "pc_urlfilter_70"
#define PARENTAL_CONTROL_URLFILTER_71_TOK  "pc_urlfilter_71"
#define PARENTAL_CONTROL_URLFILTER_72_TOK  "pc_urlfilter_72"
#define PARENTAL_CONTROL_URLFILTER_73_TOK  "pc_urlfilter_73"
#define PARENTAL_CONTROL_URLFILTER_74_TOK  "pc_urlfilter_74"
#define PARENTAL_CONTROL_URLFILTER_75_TOK  "pc_urlfilter_75"
#define PARENTAL_CONTROL_URLFILTER_76_TOK  "pc_urlfilter_76"
#define PARENTAL_CONTROL_URLFILTER_77_TOK  "pc_urlfilter_77"
#define PARENTAL_CONTROL_URLFILTER_78_TOK  "pc_urlfilter_78"
#define PARENTAL_CONTROL_URLFILTER_79_TOK  "pc_urlfilter_79"
#define PARENTAL_CONTROL_URLFILTER_80_TOK  "pc_urlfilter_80"
#define PARENTAL_CONTROL_URLFILTER_81_TOK  "pc_urlfilter_81"
#define PARENTAL_CONTROL_URLFILTER_82_TOK  "pc_urlfilter_82"
#define PARENTAL_CONTROL_URLFILTER_83_TOK  "pc_urlfilter_83"
#define PARENTAL_CONTROL_URLFILTER_84_TOK  "pc_urlfilter_84"
#define PARENTAL_CONTROL_URLFILTER_85_TOK  "pc_urlfilter_85"
#define PARENTAL_CONTROL_URLFILTER_86_TOK  "pc_urlfilter_86"
#define PARENTAL_CONTROL_URLFILTER_87_TOK  "pc_urlfilter_87"
#define PARENTAL_CONTROL_URLFILTER_88_TOK  "pc_urlfilter_88"
#define PARENTAL_CONTROL_URLFILTER_89_TOK  "pc_urlfilter_89"
#define PARENTAL_CONTROL_URLFILTER_90_TOK  "pc_urlfilter_90"
#define PARENTAL_CONTROL_URLFILTER_91_TOK  "pc_urlfilter_91"
#define PARENTAL_CONTROL_URLFILTER_92_TOK  "pc_urlfilter_92"
#define PARENTAL_CONTROL_URLFILTER_93_TOK  "pc_urlfilter_93"
#define PARENTAL_CONTROL_URLFILTER_94_TOK  "pc_urlfilter_94"
#define PARENTAL_CONTROL_URLFILTER_95_TOK  "pc_urlfilter_95"
#define PARENTAL_CONTROL_URLFILTER_96_TOK  "pc_urlfilter_96"
#define PARENTAL_CONTROL_URLFILTER_97_TOK  "pc_urlfilter_97"
#define PARENTAL_CONTROL_URLFILTER_98_TOK  "pc_urlfilter_98"
#define PARENTAL_CONTROL_URLFILTER_99_TOK  "pc_urlfilter_99"
#define PARENTAL_CONTROL_URLFILTER_100_TOK  "pc_urlfilter_100"
#define PARENTAL_CONTROL_URLFILTER_101_TOK  "pc_urlfilter_101"
#define PARENTAL_CONTROL_URLFILTER_102_TOK  "pc_urlfilter_102"
#define PARENTAL_CONTROL_URLFILTER_103_TOK  "pc_urlfilter_103"
#define PARENTAL_CONTROL_URLFILTER_104_TOK  "pc_urlfilter_104"
#define PARENTAL_CONTROL_URLFILTER_105_TOK  "pc_urlfilter_105"
#define PARENTAL_CONTROL_URLFILTER_106_TOK  "pc_urlfilter_106"
#define PARENTAL_CONTROL_URLFILTER_107_TOK  "pc_urlfilter_107"
#define PARENTAL_CONTROL_URLFILTER_108_TOK  "pc_urlfilter_108"
#define PARENTAL_CONTROL_URLFILTER_109_TOK  "pc_urlfilter_109"
#define PARENTAL_CONTROL_URLFILTER_110_TOK  "pc_urlfilter_110"
#define PARENTAL_CONTROL_URLFILTER_111_TOK  "pc_urlfilter_111"
#define PARENTAL_CONTROL_URLFILTER_112_TOK  "pc_urlfilter_112"
#define PARENTAL_CONTROL_URLFILTER_113_TOK  "pc_urlfilter_113"
#define PARENTAL_CONTROL_URLFILTER_114_TOK  "pc_urlfilter_114"
#define PARENTAL_CONTROL_URLFILTER_115_TOK  "pc_urlfilter_115"
#define PARENTAL_CONTROL_URLFILTER_116_TOK  "pc_urlfilter_116"
#define PARENTAL_CONTROL_URLFILTER_117_TOK  "pc_urlfilter_117"
#define PARENTAL_CONTROL_URLFILTER_118_TOK  "pc_urlfilter_118"
#define PARENTAL_CONTROL_URLFILTER_119_TOK  "pc_urlfilter_119"
#define PARENTAL_CONTROL_URLFILTER_120_TOK  "pc_urlfilter_120"
#define PARENTAL_CONTROL_URLFILTER_121_TOK  "pc_urlfilter_121"
#define PARENTAL_CONTROL_URLFILTER_122_TOK  "pc_urlfilter_122"
#define PARENTAL_CONTROL_URLFILTER_123_TOK  "pc_urlfilter_123"
#define PARENTAL_CONTROL_URLFILTER_124_TOK  "pc_urlfilter_124"
#define PARENTAL_CONTROL_URLFILTER_125_TOK  "pc_urlfilter_125"
#define PARENTAL_CONTROL_URLFILTER_126_TOK  "pc_urlfilter_126"
#define PARENTAL_CONTROL_URLFILTER_127_TOK  "pc_urlfilter_127"
#define PARENTAL_CONTROL_URLFILTER_128_TOK  "pc_urlfilter_128"
#define PARENTAL_CONTROL_URLFILTER_129_TOK  "pc_urlfilter_129"
#define PARENTAL_CONTROL_URLFILTER_130_TOK  "pc_urlfilter_130"
#define PARENTAL_CONTROL_URLFILTER_131_TOK  "pc_urlfilter_131"
#define PARENTAL_CONTROL_URLFILTER_132_TOK  "pc_urlfilter_132"
#define PARENTAL_CONTROL_URLFILTER_133_TOK  "pc_urlfilter_133"
#define PARENTAL_CONTROL_URLFILTER_134_TOK  "pc_urlfilter_134"
#define PARENTAL_CONTROL_URLFILTER_135_TOK  "pc_urlfilter_135"
#define PARENTAL_CONTROL_URLFILTER_136_TOK  "pc_urlfilter_136"
#define PARENTAL_CONTROL_URLFILTER_137_TOK  "pc_urlfilter_137"
#define PARENTAL_CONTROL_URLFILTER_138_TOK  "pc_urlfilter_138"
#define PARENTAL_CONTROL_URLFILTER_139_TOK  "pc_urlfilter_139"
#define PARENTAL_CONTROL_URLFILTER_140_TOK  "pc_urlfilter_140"
#define PARENTAL_CONTROL_URLFILTER_141_TOK  "pc_urlfilter_141"
#define PARENTAL_CONTROL_URLFILTER_142_TOK  "pc_urlfilter_142"
#define PARENTAL_CONTROL_URLFILTER_143_TOK  "pc_urlfilter_143"
#define PARENTAL_CONTROL_URLFILTER_144_TOK  "pc_urlfilter_144"
#define PARENTAL_CONTROL_URLFILTER_145_TOK  "pc_urlfilter_145"
#define PARENTAL_CONTROL_URLFILTER_146_TOK  "pc_urlfilter_146"
#define PARENTAL_CONTROL_URLFILTER_147_TOK  "pc_urlfilter_147"
#define PARENTAL_CONTROL_URLFILTER_148_TOK  "pc_urlfilter_148"
#define PARENTAL_CONTROL_URLFILTER_149_TOK  "pc_urlfilter_149"
#define PARENTAL_CONTROL_URLFILTER_150_TOK  "pc_urlfilter_150"
#define PARENTAL_CONTROL_URLFILTER_151_TOK  "pc_urlfilter_151"
#define PARENTAL_CONTROL_URLFILTER_152_TOK  "pc_urlfilter_152"
#define PARENTAL_CONTROL_URLFILTER_153_TOK  "pc_urlfilter_153"
#define PARENTAL_CONTROL_URLFILTER_154_TOK  "pc_urlfilter_154"
#define PARENTAL_CONTROL_URLFILTER_155_TOK  "pc_urlfilter_155"
#define PARENTAL_CONTROL_URLFILTER_156_TOK  "pc_urlfilter_156"
#define PARENTAL_CONTROL_URLFILTER_157_TOK  "pc_urlfilter_157"
#define PARENTAL_CONTROL_URLFILTER_158_TOK  "pc_urlfilter_158"
#define PARENTAL_CONTROL_URLFILTER_159_TOK  "pc_urlfilter_159"
#define PARENTAL_CONTROL_URLFILTER_160_TOK  "pc_urlfilter_160"
#define PARENTAL_CONTROL_URLFILTER_DEF_TOK     "pc_urlfilter_def_"
#define PARENTAL_CONTROL_URLFILTER_DEF_01_TOK  "pc_urlfilter_def_1"
#define PARENTAL_CONTROL_URLFILTER_DEF_02_TOK  "pc_urlfilter_def_2"
#define PARENTAL_CONTROL_URLFILTER_DEF_03_TOK  "pc_urlfilter_def_3"
#define PARENTAL_CONTROL_URLFILTER_DEF_04_TOK  "pc_urlfilter_def_4"
#define PARENTAL_CONTROL_URLFILTER_DEF_05_TOK  "pc_urlfilter_def_5"
#define PARENTAL_CONTROL_URLFILTER_DEF_06_TOK  "pc_urlfilter_def_6"
#define PARENTAL_CONTROL_URLFILTER_DEF_07_TOK  "pc_urlfilter_def_7"
#define PARENTAL_CONTROL_URLFILTER_DEF_08_TOK  "pc_urlfilter_def_8"
#define PARENTAL_CONTROL_URLFILTER_DEF_09_TOK  "pc_urlfilter_def_9"
#define PARENTAL_CONTROL_URLFILTER_DEF_10_TOK  "pc_urlfilter_def_10"
#define PARENTAL_CONTROL_URLFILTER_DEF_11_TOK  "pc_urlfilter_def_11"
#define PARENTAL_CONTROL_URLFILTER_DEF_12_TOK  "pc_urlfilter_def_12"
#define PARENTAL_CONTROL_URLFILTER_DEF_13_TOK  "pc_urlfilter_def_13"
#define PARENTAL_CONTROL_URLFILTER_DEF_14_TOK  "pc_urlfilter_def_14"
#define PARENTAL_CONTROL_URLFILTER_DEF_15_TOK  "pc_urlfilter_def_15"
#define PARENTAL_CONTROL_URLFILTER_DEF_16_TOK  "pc_urlfilter_def_16"
#define PARENTAL_CONTROL_URLFILTER_DEF_17_TOK  "pc_urlfilter_def_17"
#define PARENTAL_CONTROL_URLFILTER_DEF_18_TOK  "pc_urlfilter_def_18"
#define PARENTAL_CONTROL_URLFILTER_DEF_19_TOK  "pc_urlfilter_def_19"
#define PARENTAL_CONTROL_URLFILTER_DEF_20_TOK  "pc_urlfilter_def_20"
#define PARENTAL_CONTROL_URLFILTER_DEF_21_TOK  "pc_urlfilter_def_21"
#define PARENTAL_CONTROL_URLFILTER_DEF_22_TOK  "pc_urlfilter_def_22"
#define PARENTAL_CONTROL_URLFILTER_DEF_23_TOK  "pc_urlfilter_def_23"
#define PARENTAL_CONTROL_URLFILTER_DEF_24_TOK  "pc_urlfilter_def_24"
#define PARENTAL_CONTROL_URLFILTER_DEF_25_TOK  "pc_urlfilter_def_25"
#define PARENTAL_CONTROL_URLFILTER_DEF_26_TOK  "pc_urlfilter_def_26"
#define PARENTAL_CONTROL_URLFILTER_DEF_27_TOK  "pc_urlfilter_def_27"
#define PARENTAL_CONTROL_URLFILTER_DEF_28_TOK  "pc_urlfilter_def_28"
#define PARENTAL_CONTROL_URLFILTER_DEF_29_TOK  "pc_urlfilter_def_29"
#define PARENTAL_CONTROL_URLFILTER_DEF_30_TOK  "pc_urlfilter_def_30"

#endif
/* ------------------   NAT Sessions   -----------------------*/
#if HAS_NAT_SESSIONS_CTRL
#define NATSESSION_ENABLE_TOK             "session_enable"
#define NATSESSION_TOK                    "session_"
#define NATSESSION_01_TOK                 "session_1"
#define NATSESSION_02_TOK                 "session_2"
#define NATSESSION_03_TOK                 "session_3"
#define NATSESSION_04_TOK                 "session_4"
#define NATSESSION_05_TOK                 "session_5"
#define NATSESSION_06_TOK                 "session_6"
#define NATSESSION_07_TOK                 "session_7"
#define NATSESSION_08_TOK                 "session_8"
#define NATSESSION_09_TOK                 "session_9"
#define NATSESSION_10_TOK                 "session_10"
#if NUM_NAT_SESSION > 10
#define NATSESSION_11_TOK                 "session_11"
#define NATSESSION_12_TOK                 "session_12"
#define NATSESSION_13_TOK                 "session_13"
#define NATSESSION_14_TOK                 "session_14"
#define NATSESSION_15_TOK                 "session_15"
#define NATSESSION_16_TOK                 "session_16"
#define NATSESSION_17_TOK                 "session_17"
#define NATSESSION_18_TOK                 "session_18"
#define NATSESSION_19_TOK                 "session_19"
#define NATSESSION_20_TOK                 "session_20"
#if NUM_NAT_SESSION > 20
#define NATSESSION_21_TOK                 "session_21"
#define NATSESSION_22_TOK                 "session_22"
#define NATSESSION_23_TOK                 "session_23"
#define NATSESSION_24_TOK                 "session_24"
#define NATSESSION_25_TOK                 "session_25"
#if NUM_NAT_SESSION > 24
#define NATSESSION_26_TOK                 "session_26"
#define NATSESSION_27_TOK                 "session_27"
#define NATSESSION_28_TOK                 "session_28"
#define NATSESSION_29_TOK                 "session_29"
#define NATSESSION_30_TOK                 "session_30"
#define NATSESSION_31_TOK                 "session_31"
#define NATSESSION_32_TOK                 "session_32"
#endif
#endif
#endif
#endif /* HAS_NAT_SESSIONS_CTRL */

#if HAS_MAC_PASSTHROUGH
#define VLAN_BRIDGE_VLANID_TOK			 "vlanbridge_id"
#define VLAN_BRIDGE_LAN1_PVID_TOK		 "vb_lan1_pvid"
#define VLAN_BRIDGE_LAN2_PVID_TOK		 "vb_lan2_pvid"
#define VLAN_BRIDGE_LAN3_PVID_TOK		 "vb_lan3_pvid"
#define VLAN_BRIDGE_LAN4_PVID_TOK		 "vb_lan4_pvid"
#define VLAN_BRIDGE_SSID1_VID_TOK		 "vb_ssid1_vid"
#define VLAN_BRIDGE_SSID2_VID_TOK		 "vb_ssid2_vid"
#define VLAN_BRIDGE_SSID3_VID_TOK		 "vb_ssid3_vid"
#define VLAN_BRIDGE_SSID4_VID_TOK		 "vb_ssid4_vid"
#define IP_BRIDGE_IP1_ADDR_TOK			 "ipb_ip1_addr"
#define IP_BRIDGE_IP2_ADDR_TOK			 "ipb_ip2_addr"
#define IP_BRIDGE_IP3_ADDR_TOK			 "ipb_ip3_addr"
#define IP_BRIDGE_IP4_ADDR_TOK			 "ipb_ip4_addr"
#define IP_BRIDGE_IP5_ADDR_TOK			 "ipb_ip5_addr"
#define MAC_BRIDGING_ENABLE_TOK          "macbridge_enable"        
#define MAC_BRIDGING_TOK                 "macbridge_"
#define MAC_BRIDGING_01_TOK              "macbridge_1"
#define MAC_BRIDGING_02_TOK              "macbridge_2"
#define MAC_BRIDGING_03_TOK              "macbridge_3"
#define MAC_BRIDGING_04_TOK              "macbridge_4"
#define MAC_BRIDGING_05_TOK              "macbridge_5"
#define MAC_BRIDGING_06_TOK              "macbridge_6"
#define MAC_BRIDGING_07_TOK              "macbridge_7"
#define MAC_BRIDGING_08_TOK              "macbridge_8"
#define MAC_BRIDGING_09_TOK              "macbridge_9"
#define MAC_BRIDGING_10_TOK              "macbridge_10"
#endif

#if HAS_WAN_LAN_BRIDGE
#define WAN_BRIDGED_LAN_ID_TOK           "bridgedlanid"
#endif
/* --------------------     Web Login Accounts    ----------------------------*/
#if HAS_PRIORITY_WEB_ACCOUNT
#define WEB_ACCOUNT_TOK               "webaccount_"  //get webAccount token define
#define WEB_ACCOUNT_01_TOK            "webaccount_1"
#define WEB_ACCOUNT_02_TOK            "webaccount_2"
#define WEB_ACCOUNT_03_TOK            "webaccount_3"
#define WEB_ACCOUNT_04_TOK            "webaccount_4"
#define WEB_ACCOUNT_05_TOK            "webaccount_5"
#endif

#define WEP_TOK                          "wep"
#define WEPKEY_TOK                       "wepkey"
/* ------------------   ap wlan11b tokens   -----------------------*/
#if 1
#define WLAN11B_TOK                      "w11b_"
#define WLAN11B_SSID_TOK	             "w11b_ssid"
#define WLAN11B_CHANNEL_TOK	             "w11b_channel"
#define WLAN11B_WEP_TOK	                 "w11b_wep"
#define WLAN11B_WEPKEYID_TOK             "w11b_wepkeyid" //1 ~4
#define WLAN11B_WEPKEY_TOK               "w11b_wepkey"
#define WLAN11B_WEPKEY_0_TOK             "w11b_wepkey0" //10 or 26
#define WLAN11B_WEPKEY_1_TOK             "w11b_wepkey1"
#define WLAN11B_WEPKEY_2_TOK             "w11b_wepkey2"
#define WLAN11B_WEPKEY_3_TOK             "w11b_wepkey3"
#define WLAN11B_BEACON_TOK	             "w11b_beacon"
#define WLAN11B_DTIM_TOK                 "w11b_dtim"
#define WLAN11B_BASIC_TOK  	             "w11b_basic"
#define WLAN11B_BSS_TOK                  "w11b_bss"
#define WLAN11B_ISOLATION_TOK            "w11b_isolation"
#define WLAN11B_POWER_TOK                "w11b_power"
#define WLAN11B_AUTH_TOK                 "w11b_auth"
#define WLAN11B_HIDESSID_TOK             "w11b_hidessid"
#define WLAN11B_FRAGMENT_TOK             "w11b_fragment"
#endif  /* HAS_WLAN_B_DEV */

/* ------------------   ap wlan11a tokens   -----------------------*/
#if 1
#define WLAN11A_TOK                      "w11a_"
#define WLAN11A_SSID_TOK                 "w11a_ssid"
#define WLAN11A_MODE_TOK                 "w11a_mode"
#define WLAN11A_AUTH_TOK                 "w11a_auth"
#define WLAN11A_FREQ_TOK                 "w11a_freq"
#define WLAN11A_WEP_TOK	                 "w11a_wep"
#define WLAN11A_KEYID_TOK	             "w11a_wepkeyid"
#define WLAN11A_WEPKEY_TOK               "w11a_wepkey"
#define WLAN11A_WEPKEY_0_TOK             "w11a_wepkey0"
#define WLAN11A_WEPKEY_1_TOK             "w11a_wepkey1"
#define WLAN11A_WEPKEY_2_TOK             "w11a_wepkey2"
#define WLAN11A_WEPKEY_3_TOK             "w11a_wepkey3"
#define WLAN11A_DATARATE_TOK	         "w11a_datarate"
#define WLAN11A_TXPOWER_TOK	             "w11a_txpower"
#define WLAN11A_BEACON_TOK	             "w11a_beacon"
#define WLAN11A_DATABEACON_TOK	         "w11a_databeacon"
#define WLAN11A_FRAGMENT_TOK	         "w11a_fragment"
#define WLAN11A_THRESHOLD_TOK	         "w11a_threshold"
#endif  /* HAS_WLAN_A_DEV */
/* ------------------   ap wlan11g tokens   -----------------------*/
#define WLAN_USER_NUM_EN_TOK			"wlan_user_num_en"
#define WLAN_USER_NUM_TOK				"wlan_user_num"

#if FOR_ZYXEL || FOR_DLINK
#define WLAN_N_HTGI_TOK                 "w11g_htgi"
#endif
#if HAS_DUAL_ZONE_FUNCTION
#define WLAN_DUAL_ZONE_ENABLE_TOK        "wlan_dual_zone_en"
#endif
#if 1		
//#define WLAN1_ENABLE_TOK                 "wlan_enable"
// #define WLAN11G_TOK                      "w11g_"
// #define WLAN1_TOK                        "wlan1"
#if HAS_RADIO_SETTING
#define WLAN1_TOK                        "wlan1"
#define WLAN_TOK                         "wlan"
#define WLAN1_                           WLAN1_TOK
#define WLAN1_ENABLE_TOK                 WLAN1_ _ENABLE_TOK
#define WLAN11G_RADIO_TOK                WLAN1_ _RADIO_TOK
#define WLAN11G_SSID_TOK                 WLAN1_ _SSID_TOK
#define WLAN11G_AUTO_CH_SEL_TOK          WLAN1_ _AUTO_CH_SEL_TOK
#define WLAN11G_AUTO_CH_CHK_TIME_TOK     WLAN1_ _AUTO_CH_CHK_TIME_TOK
#define WLAN11G_CHANNEL_TOK              WLAN1_ _CHANNEL_TOK
#define WLAN11G_CH_SET_TOK               WLAN1_ _CH_SET_TOK
#define WLAN11G_WEP_TOK	                 WLAN1_ _WEP_TOK
#define WLAN11G_KEYID_TOK	             WLAN1_ _KEYID_TOK
#define WLAN11G_KEYTYPE_TOK	             WLAN1_ _KEYTYPE_TOK
#define WLAN11G_WEPKEY_TOK               WLAN1_ _WEPKEY_TOK
#define WLAN11G_WEPKEY_0_TOK             WLAN1_ _WEPKEY_0_TOK
#define WLAN11G_WEPKEY_1_TOK             WLAN1_ _WEPKEY_1_TOK
#define WLAN11G_WEPKEY_2_TOK             WLAN1_ _WEPKEY_2_TOK
#define WLAN11G_WEPKEY_3_TOK             WLAN1_ _WEPKEY_3_TOK
#define WLAN11G_DATARATE_TOK	         WLAN1_ _DATARATE_TOK
#define WLAN11G_TXPOWER_TOK	             WLAN1_ _TXPOWER_TOK
#define WLAN11G_BEACON_TOK	             WLAN1_ _BEACON_TOK
#define WLAN11G_DATABEACON_TOK	         WLAN1_ _DATABEACON_TOK
#define WLAN11G_FRAGMENT_TOK	         WLAN1_ _FRAGMENT_TOK
#define WLAN11G_THRESHOLD_TOK	         WLAN1_ _THRESHOLD_TOK
#define WLAN11G_MODE_TOK                 WLAN1_ _MODE_TOK
#define WLAN11G_PREAMBLE_TOK             WLAN1_ _PREAMBLE_TOK
#define WLAN11G_ENC_SSID_SEL_TOK		 WLAN1_ _ENC_SSID_SEL_TOK
#define WLAN11G_AUTH_TOK                 WLAN1_ _AUTH_TOK
#define WLAN11G_ENC_TYPE_TOK		     WLAN1_ _ENC_TYPE_TOK
#define WLAN11G_WPAPASSPHRASE_TOK        WLAN1_ _WPAPASSPHRASE_TOK
#define WLAN11G_HIDESSID_TOK             WLAN1_ _HIDESSID_TOK
#define WLAN11G_WPAPSK_LIFETIME_TOK	     WLAN1_ _WPAPSK_LIFETIME_TOK
#define WLAN11G_WPAPSK_LIFETIME_EN_TOK   WLAN1_ _WPAPSK_LIFETIME_EN_TOK
#define WLAN11G_WPAPSK_KEYTYPE_TOK   	 WLAN1_ _WPAPSK_KEYTYPE_TOK
#define WLAN11G_WMM_ENABLE_TOK           WLAN1_ _WMM_ENABLE_TOK
#define WLAN_11N_BW40_ENABLE_TOK         WLAN1_ _11N_BW40_ENABLE_TOK
#define WLAN_11N_DATERATE_TOK            WLAN1_ _11N_DATERATE_TOK
#define WLAN_DEV_TOK					 WLAN1_ _DEV_TOK
#if HAS_REGEN_WPS_PINCODE
#define WLAN_WPS_PIN_TOK                 WLAN1_ _WPS_PIN_TOK
#endif
#define WLAN_WPS_STATUS_TOK              WLAN1_ _WPS_STATUS_TOK
#define WLAN_WPS_ENABLE_TOK              WLAN1_ _WPS_ENABLE_TOK
#if HAS_WPS_BUTTON_CONTROL
#define WLAN_WPS_BUTTON_ENABLE_TOK              WLAN1_ _WPS_BUTTON_ENABLE_TOK
#endif
#define WLAN_SSID_NUM_TOK				 WLAN1_ _SSID_NUM_TOK
#define WLAN_TXBURST_TOK                 WLAN1_ _TXBURST_TOK
#define WLAN_TURBO_MODE_ENABLE_TOK       WLAN1_ _TURBO_MODE_ENABLE_TOK
#define WLAN_BGPROTECTION_TOK            WLAN1_ _BGPROTECTION_TOK
#define WLAN_8021X_ENABLE_TOK            WLAN1_ _8021X_ENABLE_TOK
#define WLAN_8021X_SERVIP_TOK            WLAN1_ _8021X_SERVIP_TOK
#define WLAN_8021X_SERVPORT_TOK          WLAN1_ _8021X_SERVPORT_TOK
#define WLAN_8021X_SERVPW_TOK            WLAN1_ _8021X_SERVPW_TOK
#define WLAN_AP_MODE_TOK                 WLAN1_ _AP_MODE_TOK
#define WLAN_WDS_SEC_TYPE_TOK            WLAN1_ _WDS_SEC_TYPE_TOK
#define WLAN_WDS_WPAPASSPHRASE_TOK       WLAN1_ _WDS_WPAPASSPHRASE_TOK
#define WLAN_WDS_MAC_TOK                 WLAN1_ _WDS_MAC_TOK
#define WLAN_WDS_MAC_1_TOK			     WLAN1_ _WDS_MAC_1_TOK
#define WLAN_WDS_MAC_2_TOK			     WLAN1_ _WDS_MAC_2_TOK
#define WLAN_WDS_MAC_3_TOK			     WLAN1_ _WDS_MAC_3_TOK
#define WLAN_WDS_MAC_4_TOK			     WLAN1_ _WDS_MAC_4_TOK
#define WLAN_WDS_ENC_TYPE_TOK            WLAN1_ _WDS_ENC_TYPE_TOK
#define WLAN_WDS_KEYTYPE_TOK             WLAN1_ _WDS_KEYTYPE_TOK
#define WLAN_WDS_WEP_TOK                 WLAN1_ _WDS_WEP_TOK
#define WLAN_WDS_KEYID_TOK               WLAN1_ _WDS_KEYID_TOK
#define WLAN_WDS_WEPKEY_TOK              WLAN1_ _WDS_WEPKEY_TOK
#define WLAN_WDS_WEPKEY_0_TOK            WLAN1_ _WDS_WEPKEY_0_TOK
#define WLAN_WDS_WEPKEY_1_TOK            WLAN1_ _WDS_WEPKEY_1_TOK
#define WLAN_WDS_WEPKEY_2_TOK            WLAN1_ _WDS_WEPKEY_2_TOK
#define WLAN_WDS_WEPKEY_3_TOK            WLAN1_ _WDS_WEPKEY_3_TOK
#define WLAN_WDS_PHYMODE_TOK             WLAN1_ _WDS_PHYMODE_TOK
#define WLAN_ISOLATED_ENABLE_TOK         WLAN1_ _ISOLATED_ENABLE_TOK
#if HAS_ADVANCED_ISOLATED
#define WLAN_STA_ISOLATED_ENABLE_TOK     WLAN1_ _STA_ISOLATED_ENABLE_TOK
#endif
#define WLAN_AUTO_TXPOWER_TOK            WLAN1_ _AUTO_TXPOWER_TOK
#if HAS_WAN_ACL
#define WLAN_ACCESS_WLAN2WAN_TOK		 WLAN1_ _ACCESS_WLAN2WAN_TOK
#endif /*HAS_WAN_ACL*/
#else
#define WLAN1_TOK 	                     "w11g_"
#define WLAN1_ENABLE_TOK                 "wlan_enable"
#define WLAN11G_RADIO_TOK                "w11g_radio"
#define WLAN11G_SSID_TOK                 "w11g_ssid"
#define WLAN11G_AUTO_CH_SEL_TOK          "w11g_autochsel"
#define WLAN11G_AUTO_CH_CHK_TIME_TOK     "w11g_autochtime"
#define WLAN11G_CHANNEL_TOK              "w11g_channel"
#define WLAN11G_CH_SET_TOK               "w11g_channel_set"
#define WLAN11G_WEP_TOK	                 "w11g_wep"
#define WLAN11G_KEYID_TOK	             "w11g_wepkeyid"
#define WLAN11G_KEYTYPE_TOK	             "w11g_wepkeytype"
#define WLAN11G_WEPKEY_TOK               "w11g_wepkey"
#define WLAN11G_WEPKEY_0_TOK             "w11g_wepkey0"
#define WLAN11G_WEPKEY_1_TOK             "w11g_wepkey1"
#define WLAN11G_WEPKEY_2_TOK             "w11g_wepkey2"
#define WLAN11G_WEPKEY_3_TOK             "w11g_wepkey3"
#define WLAN11G_DATARATE_TOK	         "w11g_datarate"
#define WLAN11G_TXPOWER_TOK	             "w11g_txpower"
#define WLAN11G_BEACON_TOK	             "w11g_beacon"
#define WLAN11G_DATABEACON_TOK	         "w11g_databeacon"
#define WLAN11G_FRAGMENT_TOK	         "w11g_fragment"
#define WLAN11G_THRESHOLD_TOK	         "w11g_threshold"
#define WLAN11G_MODE_TOK                 "w11g_mode"
#define WLAN11G_PREAMBLE_TOK             "w11g_preamble"
#define WLAN11G_AUTH_TOK                 "w11g_auth"
#define WLAN11G_ENC_TYPE_TOK		     "w11g_enctype"
#define WLAN11G_WPAPASSPHRASE_TOK        "w11g_wpapassphase"
#define WLAN11G_HIDESSID_TOK             "w11g_hidessid"
#define WLAN11G_WPAPSK_LIFETIME_TOK	     "w11g_wpapsk_lt"
#define WLAN11G_WPAPSK_LIFETIME_EN_TOK   "w11g_wpapsk_lt_en"
#define WLAN11G_WPAPSK_KEYTYPE_TOK   	 "w11g_wpapsk_keytype"
#define WLAN11G_WMM_ENABLE_TOK           "w11g_wmm_enable"
#define WLAN_11N_BW40_ENABLE_TOK         "wlan_11n_bw40"
#define WLAN_11N_DATERATE_TOK            "wlan_11n_daterate"
#define WLAN_DEV_TOK					 "wlan_device" 
#if FOR_DLINK
#define WLAN11G_SCHEDULE_ID_TOK			 "wlan_schedule_id"
#endif
#if HAS_REGEN_WPS_PINCODE
#define WLAN_WPS_PIN_TOK                 "wlan_wps_pin"
#endif
#define WLAN_WPS_STATUS_TOK              "wlan_wps_status"
#define WLAN_WPS_ENABLE_TOK              "wlan_wps"
#if HAS_WPS_BUTTON_CONTROL
#define WLAN_WPS_BUTTON_ENABLE_TOK              "wlan_wps_button"
#endif
#define WLAN_SSID_NUM_TOK				 "w11g_ssid_num"
#define WLAN_TXBURST_TOK                 "wlan_txburst"
#define WLAN_TURBO_MODE_ENABLE_TOK       "wlan_turbo_enable"
#define WLAN_BGPROTECTION_TOK            "wlan_BGprotection"
#define WLAN_8021X_ENABLE_TOK            "wlan_8021x_enable"
#define WLAN_8021X_SERVIP_TOK            "wlan_8021x_servip"
#define WLAN_8021X_SERVPORT_TOK          "wlan_8021x_servport"
#define WLAN_8021X_SERVPW_TOK            "wlan_8021x_servpw"
#if FOR_DLINK
#define WLAN_8021X_MACAUTH_TOK           "wlan_8021x_macauth"
#endif
#if SUPPORT_8021X_SESSION_TIMEOUT
#define WLAN_8021X_TIMEOUT_TOK           "wlan_8021x_timout"
#endif
#if HAS_BACKUP_RADIUS_SERVER
/*Backup Radius*/
#define WLAN_8021X_BACKUP_ENABLE_TOK     "wlan_8021x_bk_en"
#define WLAN_8021X_SERVIP_2_TOK          "wlan_8021x_ip_2"
#define WLAN_8021X_SERVPORT_2_TOK        "wlan_8021x_port_2"
#define WLAN_8021X_SERVPW_2_TOK          "wlan_8021x_pw_2"
#define WLAN_8021X_MACAUTH_2_TOK         "wlan_8021x_mac_2"
#endif
#define WLAN_AP_MODE_TOK                 "wlan_ap_mode"
#define WLAN11G_ENC_SSID_SEL_TOK		 "wlan1_enc_sel_ssid"
#define WLAN_WDS_SEC_TYPE_TOK            "wlan_wds_sec"
#define WLAN_WDS_WPAPASSPHRASE_TOK       "wlan_wds_passphrase"
#define WLAN_WDS_MAC_TOK                 "wlan_bridge_mac_"
#define WLAN_WDS_MAC_1_TOK			     "wlan_bridge_mac_1" 				
#define WLAN_WDS_MAC_2_TOK			     "wlan_bridge_mac_2"
#define WLAN_WDS_MAC_3_TOK			     "wlan_bridge_mac_3"
#define WLAN_WDS_MAC_4_TOK			     "wlan_bridge_mac_4"
/* 
   20091203 Nelson : modify WLAN_WDS_ENC_TYPE_TOK from "wlan_wds_enc" to "wlan_wds_enc_1"
   Because WLAN_WDS_ENC_TYPE_TOK and WLAN_WDS_KEYTYPE_TOK tokens both mean "wlan_wds_enc",
   this mistake make the web_webGetStrValue() function can not get correct value, so the
   keytype of WEP in WDS is wrong.
   In other hand, our web pages(except web_CG) use webGetStrValue("wlan_wds_enc") to
   get the value of WLAN_WDS_KEYTYPE_TOK token. In order to modify less codes , so we
   change the WLAN_WDS_ENC_TYPE_TOK represent "wlan_wds_enc_1" and web_CG can use
   webGetStrValue("wlan_wds_enc_1") to get the correct KEYTYPE.
*/
#define WLAN_WDS_ENC_TYPE_TOK            "wlan_wds_enc_1"
#define WLAN_WDS_KEYTYPE_TOK             "wlan_wds_enc"
#define WLAN_WDS_WEP_TOK                 "wlan_wds_wep"
#define WLAN_WDS_KEYID_TOK               "wlan_wds_keyid"
#define WLAN_WDS_WEPKEY_TOK              "wlan_wds_key_"
#define WLAN_WDS_WEPKEY_0_TOK            "wlan_wds_key_0"
#define WLAN_WDS_WEPKEY_1_TOK            "wlan_wds_key_1"
#define WLAN_WDS_WEPKEY_2_TOK            "wlan_wds_key_2"
#define WLAN_WDS_WEPKEY_3_TOK            "wlan_wds_key_3"
#define WLAN_WDS_PHYMODE_TOK             "wlan_wds_phymode"
#define WLAN_ISOLATED_ENABLE_TOK         "wlan_isolated"
#if HAS_ADVANCED_ISOLATED
#define WLAN_STA_ISOLATED_ENABLE_TOK     "wlan_sta_isolated"
#endif
#define WLAN_AUTO_TXPOWER_TOK            "wlan_autotxp"
#if HAS_WAN_ACL
#define WLAN_ACCESS_WLAN2WAN_TOK		 "wlan_wlan2wan"
#endif /*HAS_WAN_ACL*/
#endif
#if L2_CONTROL_ACCESS
#if HAS_RADIO_SETTING
#define WLAN_ACCESS_WLAN2LAN_TOK          WLAN1_ _ACCESS_WLAN2LAN_TOK
#define WLAN2_ACCESS_WLAN2LAN_TOK         WLAN2_ _ACCESS_WLAN2LAN_TOK
#define WLAN3_ACCESS_WLAN2LAN_TOK         WLAN3_ _ACCESS_WLAN2LAN_TOK
#define WLAN4_ACCESS_WLAN2LAN_TOK         WLAN4_ _ACCESS_WLAN2LAN_TOK
#else
#define WLAN_ACCESS_WLAN2LAN_TOK          "wlan_wlan2lan"
#define WLAN2_ACCESS_WLAN2LAN_TOK         "wlan2_wlan2lan"
#define WLAN3_ACCESS_WLAN2LAN_TOK         "wlan3_wlan2lan"
#define WLAN4_ACCESS_WLAN2LAN_TOK         "wlan4_wlan2lan"
#endif
#endif /*L2_CONTROL_ACCESS*/
#if HAS_EBTABLE_SSID_ACCESS_VPN
#define WLAN1_ACCESS_WLAN2VPN_TOK          "wlan1_wlan2vpn"
#define WLAN2_ACCESS_WLAN2VPN_TOK         "wlan2_wlan2vpn"
#define WLAN3_ACCESS_WLAN2VPN_TOK         "wlan3_wlan2vpn"
#define WLAN4_ACCESS_WLAN2VPN_TOK         "wlan4_wlan2vpn"
#endif

#endif  /* HAS_WLAN_G_DEV */
#if HAS_APCLI_FUNCTION
#define WLAN_APCLI_ENABLE_TOK            "wlan_apcli_en"
#define WLAN_APCLI_CHANNEL_TOK           "wlan_apcli_ch"
#define WLAN_APCLI_SSID_TOK              "wlan_apcli_ssid"
#define WLAN_APCLI_BSSID_TOK             "wlan_apcli_bssid"
#define WLAN_APCLI_AUTH_TOK              "wlan_apcli_auth"
#define WLAN_APCLI_ENC_TYPE_TOK          "wlan_apcli_enc"
#define WLAN_APCLI_WEP_TOK               "wlan_apcli_wep"
#define WLAN_APCLI_KEYID_TOK             "wlan_apcli_keyid"
#define WLAN_APCLI_KEYTYPE_TOK           "wlan_apcli_keytype"
#define WLAN_APCLI_WEPKEY_TOK            "wlan_apcli_key_"
#define WLAN_APCLI_WEPKEY_0_TOK          "wlan_apcli_key_0"
#define WLAN_APCLI_WEPKEY_1_TOK          "wlan_apcli_key_1"
#define WLAN_APCLI_WEPKEY_2_TOK          "wlan_apcli_key_2"
#define WLAN_APCLI_WEPKEY_3_TOK          "wlan_apcli_key_3"
#define WLAN_APCLI_WPAKEY_TOK            "wlan_apcli_psk"
#define WLAN_APCLI_NTP_SERVER_TOK        "wlan_apcli_ntpserv"
#endif
#if HAS_WLAN_STA_FUNCTION
#define WLAN1_STA_						 WLAN1_TOK _STA_TOK
#define WLAN_STA_RADIO_TOK				 WLAN1_STA_ _RADIO_TOK    
#define WLAN_STA_MODE_TOK				 WLAN1_STA_ _MODE_TOK     
#define WLAN_STA_FRAGMENT_TOK	         WLAN1_STA_ _FRAGMENT_TOK 
#define WLAN_STA_THRESHOLD_TOK	         WLAN1_STA_ _THRESHOLD_TOK
#define WLAN_STA_BEACON_TOK	             WLAN1_STA_ _BEACON_TOK   
#define WLAN_STA_DATABEACON_TOK	         WLAN1_STA_ _DATABEACON_TOK
#define WLAN_STA_DATARATE_TOK	         WLAN1_STA_ _DATARATE_TOK 
#define WLAN_STA_11N_DATERATE_TOK        WLAN1_STA_ _11N_DATERATE_TOK 
#define WLAN_STA_PREAMBLE_TOK            WLAN1_STA_ _PREAMBLE_TOK
#define WLAN_STA_TXPOWER_TOK             WLAN1_STA_ _TXPOWER_TOK
#endif
#if HAS_LAN_VLAN_MGMT
#define LAN_VLAN_ENABLE_TOK            "lan_vlan_en"
#define LAN_VLANTAG_TOK                "lan_vlanid"
#endif

#if HAS_RTL_VLAN_SUPPORT
#define RTL_VLAN_TOK					"rtl_vlan_"
#define RTL_VLAN_01_TOK					"rtl_vlan_1"
#define RTL_VLAN_02_TOK					"rtl_vlan_2"
#define RTL_VLAN_03_TOK					"rtl_vlan_3"
#define RTL_VLAN_04_TOK					"rtl_vlan_4"
#define RTL_VLAN_05_TOK					"rtl_vlan_5"
#define RTL_VLAN_06_TOK					"rtl_vlan_6"
#define RTL_VLAN_07_TOK					"rtl_vlan_7"
#define RTL_VLAN_08_TOK					"rtl_vlan_8"
#define RTL_VLAN_09_TOK					"rtl_vlan_9"
#define RTL_VLAN_10_TOK					"rtl_vlan_10"
#define RTL_VLAN_11_TOK					"rtl_vlan_11"
#define RTL_VLAN_12_TOK					"rtl_vlan_12"
#define RTL_VLAN_13_TOK					"rtl_vlan_13"
#endif

#if HAS_RADIO_SETTING
#define WLAN_VLANTAG_TOK               WLAN1_ _VLANTAG_TOK
#define WLAN2_VLANTAG_TOK              WLAN2_ _VLANTAG_TOK
#define WLAN3_VLANTAG_TOK              WLAN3_ _VLANTAG_TOK
#define WLAN4_VLANTAG_TOK              WLAN4_ _VLANTAG_TOK
#else
#if 0							  	
#define WLAN_VLANTAG_TOK               "wlan_vlanid"
#define WLAN2_VLANTAG_TOK               "wlan2_vlanid"
#define WLAN3_VLANTAG_TOK               "wlan3_vlanid"
#define WLAN4_VLANTAG_TOK               "wlan4_vlanid"
#endif
#define WLAN_TOK                         "wlan"
#define WLAN1_                           WLAN_TOK
#define WLAN2_TOK                        "wlan2"
#define WLAN2_                           WLAN2_TOK
#define WLAN3_TOK                        "wlan3"
#define WLAN3_                           WLAN3_TOK
#define WLAN4_TOK                        "wlan4"
#define WLAN4_                           WLAN4_TOK
#define WLAN_VLANTAG_TOK               WLAN1_ _VLANTAG_TOK
#define WLAN2_VLANTAG_TOK              WLAN2_ _VLANTAG_TOK
#define WLAN3_VLANTAG_TOK              WLAN3_ _VLANTAG_TOK
#define WLAN4_VLANTAG_TOK              WLAN4_ _VLANTAG_TOK
#endif
/* ------------------------Second SSID-------------------------- */
#ifdef WLAN_ID_POS
#undef WLAN_ID_POS
#endif
#define WLAN_ID_POS                     (4)
#if HAS_WLAN2_DEV
#if HAS_RADIO_SETTING
#define WLAN2_TOK                        "wlan2"
#define WLAN2_                           WLAN2_TOK
#define WLAN2_ENABLE_TOK                 WLAN2_ _ENABLE_TOK
#define WLAN2_SSID_TOK                   WLAN2_ _SSID_TOK
#define WLAN2_WEP_TOK                    WLAN2_ _WEP_TOK
#define WLAN2_KEYID_TOK                  WLAN2_ _KEYID_TOK
#define WLAN2_KEYTYPE_TOK                WLAN2_ _KEYTYPE_TOK
#define WLAN2_WEPKEY_TOK                 WLAN2_ _WEPKEY_TOK
#define WLAN2_WEPKEY_0_TOK               WLAN2_ _WEPKEY_0_TOK
#define WLAN2_WEPKEY_1_TOK               WLAN2_ _WEPKEY_1_TOK
#define WLAN2_WEPKEY_2_TOK               WLAN2_ _WEPKEY_2_TOK
#define WLAN2_WEPKEY_3_TOK               WLAN2_ _WEPKEY_3_TOK
#define WLAN2_ENC_TYPE_TOK               WLAN2_ _ENC_TYPE_TOK
#define WLAN2_WPAPASSPHRASE_TOK          WLAN2_ _WPAPASSPHRASE_TOK
#define WLAN2_HIDESSID_TOK               WLAN2_ _HIDESSID_TOK
#define WLAN2_WPAPSK_LIFETIME_TOK        WLAN2_ _WPAPSK_LIFETIME_TOK
#define WLAN2_WPAPSK_LIFETIME_EN_TOK     WLAN2_ _WPAPSK_LIFETIME_EN_TOK
#define WLAN2_WPAPSK_KEYTYPE_TOK         WLAN2_ _WPAPSK_KEYTYPE_TOK
#define WLAN2_WMM_ENABLE_TOK             WLAN2_ _WMM_ENABLE_TOK
#define WLAN2_AUTH_TOK                   WLAN2_ _AUTH_TOK
#define WLAN2_8021X_ENABLE_TOK           WLAN2_ _8021X_ENABLE_TOK
#define WLAN2_8021X_SERVIP_TOK           WLAN2_ _8021X_SERVIP_TOK
#define WLAN2_8021X_SERVPORT_TOK         WLAN2_ _8021X_SERVPORT_TOK
#define WLAN2_8021X_SERVPW_TOK           WLAN2_ _8021X_SERVPW_TOK
#define WLAN2_WDS_SEC_TYPE_TOK           WLAN2_ _WDS_SEC_TYPE_TOK
#define WLAN2_WDS_WPAPASSPHRASE_TOK      WLAN2_ _WDS_WPAPASSPHRASE_TOK
#define WLAN2_WDS_MAC_TOK                WLAN2_ _WDS_MAC_TOK
#define WLAN2_WDS_MAC_1_TOK              WLAN2_ _WDS_MAC_1_TOK
#define WLAN2_WDS_MAC_2_TOK              WLAN2_ _WDS_MAC_2_TOK
#define WLAN2_WDS_MAC_3_TOK              WLAN2_ _WDS_MAC_3_TOK
#define WLAN2_WDS_MAC_4_TOK              WLAN2_ _WDS_MAC_4_TOK
#define WLAN2_WDS_WEP_TOK                WLAN2_ _WDS_WEP_TOK
#define WLAN2_WDS_KEYID_TOK              WLAN2_ _WDS_KEYID_TOK
#define WLAN2_WDS_WEPKEY_0_TOK           WLAN2_ _WDS_WEPKEY_0_TOK
#define WLAN2_WDS_WEPKEY_1_TOK           WLAN2_ _WDS_WEPKEY_1_TOK
#define WLAN2_WDS_WEPKEY_2_TOK           WLAN2_ _WDS_WEPKEY_2_TOK
#define WLAN2_WDS_WEPKEY_3_TOK           WLAN2_ _WDS_WEPKEY_3_TOK
#define WLAN2_ISOLATED_ENABLE_TOK        WLAN2_ _ISOLATED_ENABLE_TOK
#if HAS_ADVANCED_ISOLATED
#define WLAN2_STA_ISOLATED_ENABLE_TOK    WLAN2_ _STA_ISOLATED_ENABLE_TOK
#endif
#if HAS_WAN_ACL
#define WLAN2_ACCESS_WLAN2WAN_TOK		 WLAN2_ _ACCESS_WLAN2WAN_TOK
#endif /*HAS_WAN_ACL*/
#else
#define WLAN2_ENABLE_TOK                 "wlan2_enable"
#define WLAN2_SSID_TOK                   "wlan2_ssid"
#define WLAN2_WEP_TOK                    "wlan2_wep"
#define WLAN2_KEYID_TOK                  "wlan2_wepkeyid"
#define WLAN2_KEYTYPE_TOK                "wlan2_wepkeytype"
#define WLAN2_WEPKEY_TOK                 "wlan2_wepkey"
#define WLAN2_WEPKEY_0_TOK               "wlan2_wepkey0"
#define WLAN2_WEPKEY_1_TOK               "wlan2_wepkey1"
#define WLAN2_WEPKEY_2_TOK               "wlan2_wepkey2"
#define WLAN2_WEPKEY_3_TOK               "wlan2_wepkey3"
#define WLAN2_ENC_TYPE_TOK               "wlan2_enctype"
#define WLAN2_WPAPASSPHRASE_TOK          "wlan2_wpapassphase"
#define WLAN2_HIDESSID_TOK               "wlan2_hidessid"
#define WLAN2_WPAPSK_LIFETIME_TOK        "wlan2_wpa_lt"
#define WLAN2_WPAPSK_LIFETIME_EN_TOK     "wlan2_wpa_lt_en"
#define WLAN2_WPAPSK_KEYTYPE_TOK         "wlan2_wpa_keytype"
#define WLAN2_WMM_ENABLE_TOK             "wlan2_wmm_enable"
#define WLAN2_AUTH_TOK                   "wlan2_auth"
#define WLAN2_8021X_ENABLE_TOK           "wlan2_8021_enable"
#define WLAN2_8021X_SERVIP_TOK           "wlan2_8021_servip"
#define WLAN2_8021X_SERVPORT_TOK         "wlan2_8021_servport"
#define WLAN2_8021X_SERVPW_TOK           "wlan2_8021_servpw"
#define WLAN2_WDS_SEC_TYPE_TOK           "wlan2_wds_sec"
#define WLAN2_WDS_WPAPASSPHRASE_TOK      "wlan2_wds_pphrase"
#define WLAN2_WDS_MAC_TOK                "wlan2_bridge_mac_"
#define WLAN2_WDS_MAC_1_TOK              "wlan2_bridge_mac_1"                    
#define WLAN2_WDS_MAC_2_TOK              "wlan2_bridge_mac_2"
#define WLAN2_WDS_MAC_3_TOK              "wlan2_bridge_mac_3"
#define WLAN2_WDS_MAC_4_TOK              "wlan2_bridge_mac_4"
#define WLAN2_WDS_WEP_TOK                "wlan2_wds_wep"
#define WLAN2_WDS_KEYID_TOK              "wlan2_wds_keyid"
#define WLAN2_WDS_WEPKEY_0_TOK           "wlan2_wds_key_0"
#define WLAN2_WDS_WEPKEY_1_TOK           "wlan2_wds_key_1"
#define WLAN2_WDS_WEPKEY_2_TOK           "wlan2_wds_key_2"
#define WLAN2_WDS_WEPKEY_3_TOK           "wlan2_wds_key_3"
#define WLAN2_ISOLATED_ENABLE_TOK        "wlan2_isolated"
#if HAS_ADVANCED_ISOLATED
#define WLAN2_STA_ISOLATED_ENABLE_TOK    "wlan2_sta_isolated"
#endif
#if HAS_WAN_ACL
#define WLAN2_ACCESS_WLAN2WAN_TOK		 "wlan2_wlan2wan"
#endif /*HAS_WAN_ACL*/
#endif
#endif
/* --------------------------   Third SSID-----------------------------------*/
#if HAS_WLAN3_DEV
#if HAS_RADIO_SETTING
#define WLAN3_TOK                        "wlan3"
#define WLAN3_                           WLAN3_TOK
#define WLAN3_ENABLE_TOK                 WLAN3_ _ENABLE_TOK
#define WLAN3_SSID_TOK                   WLAN3_ _SSID_TOK
#define WLAN3_WEP_TOK                    WLAN3_ _WEP_TOK
#define WLAN3_KEYID_TOK                  WLAN3_ _KEYID_TOK
#define WLAN3_KEYTYPE_TOK                WLAN3_ _KEYTYPE_TOK
#define WLAN3_WEPKEY_TOK                 WLAN3_ _WEPKEY_TOK
#define WLAN3_WEPKEY_0_TOK               WLAN3_ _WEPKEY_0_TOK
#define WLAN3_WEPKEY_1_TOK               WLAN3_ _WEPKEY_1_TOK
#define WLAN3_WEPKEY_2_TOK               WLAN3_ _WEPKEY_2_TOK
#define WLAN3_WEPKEY_3_TOK               WLAN3_ _WEPKEY_3_TOK
#define WLAN3_ENC_TYPE_TOK               WLAN3_ _ENC_TYPE_TOK
#define WLAN3_WPAPASSPHRASE_TOK          WLAN3_ _WPAPASSPHRASE_TOK
#define WLAN3_HIDESSID_TOK               WLAN3_ _HIDESSID_TOK
#define WLAN3_WPAPSK_LIFETIME_TOK        WLAN3_ _WPAPSK_LIFETIME_TOK
#define WLAN3_WPAPSK_LIFETIME_EN_TOK     WLAN3_ _WPAPSK_LIFETIME_EN_TOK
#define WLAN3_WPAPSK_KEYTYPE_TOK         WLAN3_ _WPAPSK_KEYTYPE_TOK
#define WLAN3_WMM_ENABLE_TOK             WLAN3_ _WMM_ENABLE_TOK
#define WLAN3_AUTH_TOK                   WLAN3_ _AUTH_TOK
#define WLAN3_8021X_ENABLE_TOK           WLAN3_ _8021X_ENABLE_TOK
#define WLAN3_8021X_SERVIP_TOK           WLAN3_ _8021X_SERVIP_TOK
#define WLAN3_8021X_SERVPORT_TOK         WLAN3_ _8021X_SERVPORT_TOK
#define WLAN3_8021X_SERVPW_TOK           WLAN3_ _8021X_SERVPW_TOK
#define WLAN3_WDS_SEC_TYPE_TOK           WLAN3_ _WDS_SEC_TYPE_TOK
#define WLAN3_WDS_WPAPASSPHRASE_TOK      WLAN3_ _WDS_WPAPASSPHRASE_TOK
#define WLAN3_WDS_MAC_TOK                WLAN3_ _WDS_MAC_TOK
#define WLAN3_WDS_MAC_1_TOK              WLAN3_ _WDS_MAC_1_TOK
#define WLAN3_WDS_MAC_2_TOK              WLAN3_ _WDS_MAC_2_TOK
#define WLAN3_WDS_MAC_3_TOK              WLAN3_ _WDS_MAC_3_TOK
#define WLAN3_WDS_MAC_4_TOK              WLAN3_ _WDS_MAC_4_TOK
#define WLAN3_WDS_WEP_TOK                WLAN3_ _WDS_WEP_TOK
#define WLAN3_WDS_KEYID_TOK              WLAN3_ _WDS_KEYID_TOK
#define WLAN3_WDS_WEPKEY_0_TOK           WLAN3_ _WDS_WEPKEY_0_TOK
#define WLAN3_WDS_WEPKEY_1_TOK           WLAN3_ _WDS_WEPKEY_1_TOK
#define WLAN3_WDS_WEPKEY_2_TOK           WLAN3_ _WDS_WEPKEY_2_TOK
#define WLAN3_WDS_WEPKEY_3_TOK           WLAN3_ _WDS_WEPKEY_3_TOK
#define WLAN3_ISOLATED_ENABLE_TOK        WLAN3_ _ISOLATED_ENABLE_TOK
#if HAS_ADVANCED_ISOLATED
#define WLAN3_STA_ISOLATED_ENABLE_TOK    WLAN3_ _STA_ISOLATED_ENABLE_TOK
#endif
#if HAS_WAN_ACL                              
#define WLAN3_ACCESS_WLAN2WAN_TOK		 WLAN3_ _ACCESS_WLAN2WAN_TOK
#endif /*HAS_WAN_ACL*/
#else
#define WLAN3_ENABLE_TOK                 "wlan3_enable"
#define WLAN3_SSID_TOK                   "wlan3_ssid"
#define WLAN3_WEP_TOK                    "wlan3_wep"
#define WLAN3_KEYID_TOK                  "wlan3_wepkeyid"
#define WLAN3_KEYTYPE_TOK                "wlan3_wepkeytype"
#define WLAN3_WEPKEY_TOK                 "wlan3_wepkey"
#define WLAN3_WEPKEY_0_TOK               "wlan3_wepkey0"
#define WLAN3_WEPKEY_1_TOK               "wlan3_wepkey1"
#define WLAN3_WEPKEY_2_TOK               "wlan3_wepkey2"
#define WLAN3_WEPKEY_3_TOK               "wlan3_wepkey3"
#define WLAN3_ENC_TYPE_TOK               "wlan3_enctype"
#define WLAN3_WPAPASSPHRASE_TOK          "wlan3_wpapassphase"
#define WLAN3_HIDESSID_TOK               "wlan3_hidessid"
#define WLAN3_WPAPSK_LIFETIME_TOK        "wlan3_wpa_lt"
#define WLAN3_WPAPSK_LIFETIME_EN_TOK     "wlan3_wpa_lt_en"
#define WLAN3_WPAPSK_KEYTYPE_TOK         "wlan3_wpa_keytype"
#define WLAN3_WMM_ENABLE_TOK             "wlan3_wmm_enable"
#define WLAN3_AUTH_TOK                   "wlan3_auth"
#define WLAN3_8021X_ENABLE_TOK           "wlan3_8021_enable"
#define WLAN3_8021X_SERVIP_TOK           "wlan3_8021_servip"
#define WLAN3_8021X_SERVPORT_TOK         "wlan3_8021_servport"
#define WLAN3_8021X_SERVPW_TOK           "wlan3_8021_servpw"
#define WLAN3_WDS_SEC_TYPE_TOK           "wlan3_wds_sec"
#define WLAN3_WDS_WPAPASSPHRASE_TOK      "wlan3_wds_pphrase"
#define WLAN3_WDS_MAC_TOK                "wlan3_bridge_mac_"
#define WLAN3_WDS_MAC_1_TOK              "wlan3_bridge_mac_1"                    
#define WLAN3_WDS_MAC_2_TOK              "wlan3_bridge_mac_2"
#define WLAN3_WDS_MAC_3_TOK              "wlan3_bridge_mac_3"
#define WLAN3_WDS_MAC_4_TOK              "wlan3_bridge_mac_4"
#define WLAN3_WDS_WEP_TOK                "wlan3_wds_wep"
#define WLAN3_WDS_KEYID_TOK              "wlan3_wds_keyid"
#define WLAN3_WDS_WEPKEY_0_TOK           "wlan3_wds_key_0"
#define WLAN3_WDS_WEPKEY_1_TOK           "wlan3_wds_key_1"
#define WLAN3_WDS_WEPKEY_2_TOK           "wlan3_wds_key_2"
#define WLAN3_WDS_WEPKEY_3_TOK           "wlan3_wds_key_3"
#define WLAN3_ISOLATED_ENABLE_TOK        "wlan3_isolated"
#if HAS_ADVANCED_ISOLATED
#define WLAN3_STA_ISOLATED_ENABLE_TOK    "wlan3_sta_isolated"
#endif
#if HAS_WAN_ACL
#define WLAN3_ACCESS_WLAN2WAN_TOK		 "wlan3_wlan2wan"
#endif /*HAS_WAN_ACL*/

#endif
#endif
/* --------------------------   fourth SSID-----------------------------------*/
#if HAS_WLAN4_DEV
#if HAS_RADIO_SETTING
#define WLAN4_TOK                        "wlan4"
#define WLAN4_                           WLAN4_TOK
#define WLAN4_ENABLE_TOK                 WLAN4_ _ENABLE_TOK
#define WLAN4_SSID_TOK                   WLAN4_ _SSID_TOK
#define WLAN4_WEP_TOK                    WLAN4_ _WEP_TOK
#define WLAN4_KEYID_TOK                  WLAN4_ _KEYID_TOK
#define WLAN4_KEYTYPE_TOK                WLAN4_ _KEYTYPE_TOK
#define WLAN4_WEPKEY_TOK                 WLAN4_ _WEPKEY_TOK
#define WLAN4_WEPKEY_0_TOK               WLAN4_ _WEPKEY_0_TOK
#define WLAN4_WEPKEY_1_TOK               WLAN4_ _WEPKEY_1_TOK
#define WLAN4_WEPKEY_2_TOK               WLAN4_ _WEPKEY_2_TOK
#define WLAN4_WEPKEY_3_TOK               WLAN4_ _WEPKEY_3_TOK
#define WLAN4_ENC_TYPE_TOK               WLAN4_ _ENC_TYPE_TOK
#define WLAN4_WPAPASSPHRASE_TOK          WLAN4_ _WPAPASSPHRASE_TOK
#define WLAN4_HIDESSID_TOK               WLAN4_ _HIDESSID_TOK
#define WLAN4_WPAPSK_LIFETIME_TOK        WLAN4_ _WPAPSK_LIFETIME_TOK
#define WLAN4_WPAPSK_LIFETIME_EN_TOK     WLAN4_ _WPAPSK_LIFETIME_EN_TOK
#define WLAN4_WPAPSK_KEYTYPE_TOK         WLAN4_ _WPAPSK_KEYTYPE_TOK
#define WLAN4_WMM_ENABLE_TOK             WLAN4_ _WMM_ENABLE_TOK
#define WLAN4_AUTH_TOK                   WLAN4_ _AUTH_TOK
#define WLAN4_8021X_ENABLE_TOK           WLAN4_ _8021X_ENABLE_TOK
#define WLAN4_8021X_SERVIP_TOK           WLAN4_ _8021X_SERVIP_TOK
#define WLAN4_8021X_SERVPORT_TOK         WLAN4_ _8021X_SERVPORT_TOK
#define WLAN4_8021X_SERVPW_TOK           WLAN4_ _8021X_SERVPW_TOK
#define WLAN4_WDS_SEC_TYPE_TOK           WLAN4_ _WDS_SEC_TYPE_TOK
#define WLAN4_WDS_WPAPASSPHRASE_TOK      WLAN4_ _WDS_WPAPASSPHRASE_TOK
#define WLAN4_WDS_MAC_TOK                WLAN4_ _WDS_MAC_TOK
#define WLAN4_WDS_MAC_1_TOK              WLAN4_ _WDS_MAC_1_TOK
#define WLAN4_WDS_MAC_2_TOK              WLAN4_ _WDS_MAC_2_TOK
#define WLAN4_WDS_MAC_3_TOK              WLAN4_ _WDS_MAC_3_TOK
#define WLAN4_WDS_MAC_4_TOK              WLAN4_ _WDS_MAC_4_TOK
#define WLAN4_WDS_WEP_TOK                WLAN4_ _WDS_WEP_TOK
#define WLAN4_WDS_KEYID_TOK              WLAN4_ _WDS_KEYID_TOK
#define WLAN4_WDS_WEPKEY_0_TOK           WLAN4_ _WDS_WEPKEY_0_TOK
#define WLAN4_WDS_WEPKEY_1_TOK           WLAN4_ _WDS_WEPKEY_1_TOK
#define WLAN4_WDS_WEPKEY_2_TOK           WLAN4_ _WDS_WEPKEY_2_TOK
#define WLAN4_WDS_WEPKEY_3_TOK           WLAN4_ _WDS_WEPKEY_3_TOK
#define WLAN4_ISOLATED_ENABLE_TOK        WLAN4_ _ISOLATED_ENABLE_TOK
#if HAS_ADVANCED_ISOLATED
#define WLAN4_STA_ISOLATED_ENABLE_TOK    WLAN4_ _STA_ISOLATED_ENABLE_TOK
#endif
#if HAS_WAN_ACL                              
#define WLAN4_ACCESS_WLAN2WAN_TOK		 WLAN4_ _ACCESS_WLAN2WAN_TOK
#endif /*HAS_WAN_ACL*/
#else
#define WLAN4_ENABLE_TOK                 "wlan4_enable"
#define WLAN4_SSID_TOK                   "wlan4_ssid"
#define WLAN4_WEP_TOK                    "wlan4_wep"
#define WLAN4_KEYID_TOK                  "wlan4_wepkeyid"
#define WLAN4_KEYTYPE_TOK                "wlan4_wepkeytype"
#define WLAN4_WEPKEY_TOK                 "wlan4_wepkey"
#define WLAN4_WEPKEY_0_TOK               "wlan4_wepkey0"
#define WLAN4_WEPKEY_1_TOK               "wlan4_wepkey1"
#define WLAN4_WEPKEY_2_TOK               "wlan4_wepkey2"
#define WLAN4_WEPKEY_3_TOK               "wlan4_wepkey3"
#define WLAN4_ENC_TYPE_TOK               "wlan4_enctype"
#define WLAN4_WPAPASSPHRASE_TOK          "wlan4_wpapassphase"
#define WLAN4_HIDESSID_TOK               "wlan4_hidessid"
#define WLAN4_WPAPSK_LIFETIME_TOK        "wlan4_wpa_lt"
#define WLAN4_WPAPSK_LIFETIME_EN_TOK     "wlan4_wpa_lt_en"
#define WLAN4_WPAPSK_KEYTYPE_TOK         "wlan4_wpa_keytype"
#define WLAN4_WMM_ENABLE_TOK             "wlan4_wmm_enable"
#define WLAN4_AUTH_TOK                   "wlan4_auth"
#define WLAN4_8021X_ENABLE_TOK           "wlan4_8021_enable"
#define WLAN4_8021X_SERVIP_TOK           "wlan4_8021_servip"
#define WLAN4_8021X_SERVPORT_TOK         "wlan4_8021_servport"
#define WLAN4_8021X_SERVPW_TOK           "wlan4_8021_servpw"
#define WLAN4_WDS_SEC_TYPE_TOK           "wlan4_wds_sec"
#define WLAN4_WDS_WPAPASSPHRASE_TOK      "wlan4_wds_pphrase"
#define WLAN4_WDS_MAC_TOK                "wlan4_bridge_mac_"
#define WLAN4_WDS_MAC_1_TOK              "wlan4_bridge_mac_1"                    
#define WLAN4_WDS_MAC_2_TOK              "wlan4_bridge_mac_2"
#define WLAN4_WDS_MAC_3_TOK              "wlan4_bridge_mac_3"
#define WLAN4_WDS_MAC_4_TOK              "wlan4_bridge_mac_4"
#define WLAN4_WDS_WEP_TOK                "wlan4_wds_wep"
#define WLAN4_WDS_KEYID_TOK              "wlan4_wds_keyid"
#define WLAN4_WDS_WEPKEY_0_TOK           "wlan4_wds_key_0"
#define WLAN4_WDS_WEPKEY_1_TOK           "wlan4_wds_key_1"
#define WLAN4_WDS_WEPKEY_2_TOK           "wlan4_wds_key_2"
#define WLAN4_WDS_WEPKEY_3_TOK           "wlan4_wds_key_3"
#define WLAN4_ISOLATED_ENABLE_TOK        "wlan4_isolated"
#if HAS_ADVANCED_ISOLATED
#define WLAN4_STA_ISOLATED_ENABLE_TOK    "wlan4_sta_isolated"
#endif
#if HAS_WAN_ACL
#define WLAN4_ACCESS_WLAN2WAN_TOK		 "wlan4_wlan2wan"
#endif /*HAS_WAN_ACL*/
#endif
#endif
/* ------------------   ap 802.1x tokens   -----------------------*/
#if 0
#define WLAN802DOT1X_AUTHTYPE_TOK             "w802_authtype"
#define WLAN802DOT1X_REAUTHTIME_TOK           "w802_reauth_t"
#define WLAN802DOT1X_PRIMARYIP_TOK            "w802_pri_ip"
#define WLAN802DOT1X_PRIMARYPORT_TOK          "w802_pri_port"
#define WLAN802DOT1X_PRIMARYSHARED_TOK        "w802_pri_sha"
#define WLAN802DOT1X_PRIMARYSHAREDLEN_TOK     "w802_pri_sha_len"
#define WLAN802DOT1X_BACKUPIP_TOK             "w802_bak_ip"
#define WLAN802DOT1X_BACKUPPORT_TOK           "w802_bak_port"
#define WLAN802DOT1X_BACKUPSHARED_TOK         "w802_bak_sha"
#define WLAN802DOT1X_BACKUPSHAREDLEN_TOK      "w802_bak_sha_len"
#define WLAN802DOT1X_DYNAMICENABLE_TOK        "w802_dyn_enable"
#define WLAN802DOT1X_DYNAMICREKEY_TOK         "w802_dyn_rekey"

#define WLAN11A802DOT1X_AUTHTYPE_TOK          "w11a802_authtype"
#define WLAN11A802DOT1X_REAUTHTIME_TOK        "w11a802_reauth_t"
#define WLAN11A802DOT1X_PRIMARYIP_TOK         "w11a802_pri_ip"
#define WLAN11A802DOT1X_PRIMARYPORT_TOK       "w11a802_pri_port"
#define WLAN11A802DOT1X_PRIMARYSHARED_TOK     "w11a802_pri_sha"
#define WLAN11A802DOT1X_PRIMARYSHAREDLEN_TOK  "w11a802_pri_sha_len"
#define WLAN11A802DOT1X_BACKUPIP_TOK          "w11a802_bak_ip"
#define WLAN11A802DOT1X_BACKUPPORT_TOK        "w11a802_bak_port"
#define WLAN11A802DOT1X_BACKUPSHARED_TOK      "w11a802_bak_sha"
#define WLAN11A802DOT1X_BACKUPSHAREDLEN_TOK   "w11a802_bak_sha_len"
#define WLAN11A802DOT1X_DYNAMICENABLE_TOK     "w11a802_dyn_enable"
#define WLAN11A802DOT1X_DYNAMICREKEY_TOK      "w11a802_dyn_rekey"

#define WLAN11B802DOT1X_AUTHTYPE_TOK          "w11b802_authtype"
#define WLAN11B802DOT1X_REAUTHTIME_TOK        "w11b802_reauth_t"
#define WLAN11B802DOT1X_PRIMARYIP_TOK         "w11b802_pri_ip"
#define WLAN11B802DOT1X_PRIMARYPORT_TOK       "w11b802_pri_port"
#define WLAN11B802DOT1X_PRIMARYSHARED_TOK     "w11b802_pri_sha"
#define WLAN11B802DOT1X_PRIMARYSHAREDLEN_TOK  "w11b802_pri_sha_len"
#define WLAN11B802DOT1X_BACKUPIP_TOK          "w11b802_bak_ip"
#define WLAN11B802DOT1X_BACKUPPORT_TOK        "w11b802_bak_port"
#define WLAN11B802DOT1X_BACKUPSHARED_TOK      "w11b802_bak_sha"
#define WLAN11B802DOT1X_BACKUPSHAREDLEN_TOK   "w11b802_bak_sha_len"
#define WLAN11B802DOT1X_DYNAMICENABLE_TOK     "w11b802_dyn_enable"
#define WLAN11B802DOT1X_DYNAMICREKEY_TOK      "w11b802_dyn_rekey"

#define WLAN11G802DOT1X_AUTHTYPE_TOK          "w11g802_authtype"
#define WLAN11G802DOT1X_REAUTHTIME_TOK        "w11g802_reauth_t"
#define WLAN11G802DOT1X_PRIMARYIP_TOK         "w11g802_pri_p"
#define WLAN11G802DOT1X_PRIMARYPORT_TOK       "w11g802_pri_port"
#define WLAN11G802DOT1X_PRIMARYSHARED_TOK     "w11g802_pri_sha"
#define WLAN11G802DOT1X_PRIMARYSHAREDLEN_TOK  "w11g802_pri_sha_len"
#define WLAN11G802DOT1X_BACKUPIP_TOK          "w11g802_bak_ip"
#define WLAN11G802DOT1X_BACKUPPORT_TOK        "w11g802_bak_port"
#define WLAN11G802DOT1X_BACKUPSHARED_TOK      "w11g802_bak_sha"
#define WLAN11G802DOT1X_BACKUPSHAREDLEN_TOK   "w11g802_bak_sha_len"
#define WLAN11G802DOT1X_DYNAMICENABLE_TOK     "w11g802_dyn_enable"
#define WLAN11G802DOT1X_DYNAMICREKEY_TOK      "w11g802_dyn_rekey"
#endif
/* ------------------   ap dhcp tokens   -----------------------*/
#define DHCPD_ENABLE_TOK                 "dhcpd_enable"
#if HAS_MULTI_MODE_LAN_IP
#define DHCPD_ENABLE_AP_MODE_TOK         "dhcpd_ap_enable"
#endif
#define DHCPD_START_TOK                  "dhcpd_start_"
#define DHCPD_END_TOK                    "dhcpd_end_"
#define DHCPD_START_1_TOK                "dhcpd_start_1"
#define DHCPD_END_1_TOK                  "dhcpd_end_1"
#define DHCPD_ALWAYS_BCAST_ENABLE_TOK		"dhcpd_bcst_en"
#define DHCPD_RELAY_ENABLE_TOK			 "dhcpd_relay_en"
#define DHCPD_RELAY_SERVER_TOK			 "dhcpd_relay_ip"
#if HAS_MULTI_MODE_LAN_IP
#define DHCPD_START_1_AP_MODE_TOK        "dhcpd_ap_start_1"
#define DHCPD_END_1_AP_MODE_TOK          "dhcpd_ap_end_1"
#endif
#if SUPPORT_PCI_AP_AUTO_DETECT
#define AD_DHCPD_ENABLE_TOK				 "ad_dhcpd_enable"
#endif
#if 1
#define DHCPD_START_2_TOK                "dhcpd_start_2"
#define DHCPD_END_2_TOK                  "dhcpd_end_2"
#define DHCPD_START_3_TOK                "dhcpd_start_3"
#define DHCPD_END_3_TOK                  "dhcpd_end_3"
#endif
#define DHCPD_MINLEASE_TIME_TOK          "dhcpd_minlease_t"
#if DNS_SERVERS_ASSIGNED_BY_DHCP_SERVER
#define DHCPD_DNS_1_TYPE_TOK             "dhcpd_dns_type_1"
#define DHCPD_DNS_1_IP_TOK               "dhcpd_dns_ip_1"
#define DHCPD_DNS_2_TYPE_TOK             "dhcpd_dns_type_2"
#define DHCPD_DNS_2_IP_TOK               "dhcpd_dns_ip_2"
#endif
/* ------------------   DHCP fixed ip for specific mac   -----------------------*/
#define DHCPD_MACTOIP_ENABLE_TOK         "dhcpd_mactoip_en"
#define DHCPD_MACTOIP_TOK                "dhcpd_mactoip_"
#define DHCPD_MACTOIP_01_TOK             "dhcpd_mactoip_1"
#define DHCPD_MACTOIP_02_TOK             "dhcpd_mactoip_2"
#define DHCPD_MACTOIP_03_TOK             "dhcpd_mactoip_3"
#define DHCPD_MACTOIP_04_TOK             "dhcpd_mactoip_4"
#define DHCPD_MACTOIP_05_TOK             "dhcpd_mactoip_5"
#define DHCPD_MACTOIP_06_TOK             "dhcpd_mactoip_6"
#define DHCPD_MACTOIP_07_TOK             "dhcpd_mactoip_7"
#define DHCPD_MACTOIP_08_TOK             "dhcpd_mactoip_8"
#define DHCPD_MACTOIP_09_TOK             "dhcpd_mactoip_9"
#define DHCPD_MACTOIP_10_TOK             "dhcpd_mactoip_10"
#if NUM_DHCPD_MACTOIP > 10
#define DHCPD_MACTOIP_11_TOK             "dhcpd_mactoip_11"
#define DHCPD_MACTOIP_12_TOK             "dhcpd_mactoip_12"
#define DHCPD_MACTOIP_13_TOK             "dhcpd_mactoip_13"
#define DHCPD_MACTOIP_14_TOK             "dhcpd_mactoip_14"
#define DHCPD_MACTOIP_15_TOK             "dhcpd_mactoip_15"
#define DHCPD_MACTOIP_16_TOK             "dhcpd_mactoip_16"
#define DHCPD_MACTOIP_17_TOK             "dhcpd_mactoip_17"
#define DHCPD_MACTOIP_18_TOK             "dhcpd_mactoip_18"
#define DHCPD_MACTOIP_19_TOK             "dhcpd_mactoip_19"
#define DHCPD_MACTOIP_20_TOK             "dhcpd_mactoip_20"
#if NUM_DHCPD_MACTOIP > 20
#define DHCPD_MACTOIP_21_TOK             "dhcpd_mactoip_21"
#define DHCPD_MACTOIP_22_TOK             "dhcpd_mactoip_22"
#define DHCPD_MACTOIP_23_TOK             "dhcpd_mactoip_23"
#define DHCPD_MACTOIP_24_TOK             "dhcpd_mactoip_24"
#define DHCPD_MACTOIP_25_TOK             "dhcpd_mactoip_25"
#define DHCPD_MACTOIP_26_TOK             "dhcpd_mactoip_26"
#define DHCPD_MACTOIP_27_TOK             "dhcpd_mactoip_27"
#define DHCPD_MACTOIP_28_TOK             "dhcpd_mactoip_28"
#define DHCPD_MACTOIP_29_TOK             "dhcpd_mactoip_29"
#define DHCPD_MACTOIP_30_TOK             "dhcpd_mactoip_30"
#define DHCPD_MACTOIP_31_TOK             "dhcpd_mactoip_31"
#define DHCPD_MACTOIP_32_TOK             "dhcpd_mactoip_32"
#endif
#endif
/*-----------------------     DOS     --------------------------------------*/
#define DOS_PING_OF_DEATH_TOK         	 "dos_ping_death"
#define DOS_DISCARD_PING_ON_WAN_TOK      "dos_discard_ping"
#if HAS_DISCARD_PING_ON_LAN
#define DOS_DISCARD_PING_ON_LAN_TOK      "dos_discard_ping_l"
#endif
#define DOS_PORT_SCAN_TOK         		 "dos_port_scan"
#define DOS_SYNC_FLOOD_TOK         		 "dos_sync_flood"
/* ------------------   routing   -----------------------*/
#define DYN_ROUTE_ENABLE_TOK             "dynrt_enable"
#define DYN_RT_RIP_PASSWORD_TOK          "dynrt_rip_pw"
#define DYN_RT_RIP_TX_MODE_TOK           "dynrt_rip_tx_mode"
#define DYN_RT_RIP_RX_MODE_TOK           "dynrt_rip_rx_mode"
/* ------------------   static routing   -----------------------*/
#define STATICROUTING_ENABLE_TOK         "staticrouting_en"
#define STATICROUTING_TMP_ADD_TOK        "staticrouting_add_0"
#define STATICROUTING_TMP_DEL_TOK        "staticrouting_del_0"
#define STATICROUTING_TOK                "staticrouting_"
#define STATICROUTING_01_TOK             "staticrouting_1"
#define STATICROUTING_02_TOK             "staticrouting_2"
#define STATICROUTING_03_TOK             "staticrouting_3"
#define STATICROUTING_04_TOK             "staticrouting_4"
#define STATICROUTING_05_TOK             "staticrouting_5"
#define STATICROUTING_06_TOK             "staticrouting_6"
#define STATICROUTING_07_TOK             "staticrouting_7"
#define STATICROUTING_08_TOK             "staticrouting_8"
#define STATICROUTING_09_TOK             "staticrouting_9"
#define STATICROUTING_10_TOK             "staticrouting_10"
#if NUM_STATICROUTING > 10
#define STATICROUTING_11_TOK             "staticrouting_11"
#define STATICROUTING_12_TOK             "staticrouting_12"
#define STATICROUTING_13_TOK             "staticrouting_13"
#define STATICROUTING_14_TOK             "staticrouting_14"
#define STATICROUTING_15_TOK             "staticrouting_15"
#define STATICROUTING_16_TOK             "staticrouting_16"
#define STATICROUTING_17_TOK             "staticrouting_17"
#define STATICROUTING_18_TOK             "staticrouting_18"
#define STATICROUTING_19_TOK             "staticrouting_19"
#define STATICROUTING_20_TOK             "staticrouting_20"
#if NUM_STATICROUTING > 20
#define STATICROUTING_21_TOK             "staticrouting_21"
#define STATICROUTING_22_TOK             "staticrouting_22"
#define STATICROUTING_23_TOK             "staticrouting_23"
#define STATICROUTING_24_TOK             "staticrouting_24"
#define STATICROUTING_25_TOK             "staticrouting_25"
#define STATICROUTING_26_TOK             "staticrouting_26"
#define STATICROUTING_27_TOK             "staticrouting_27"
#define STATICROUTING_28_TOK             "staticrouting_28"
#define STATICROUTING_29_TOK             "staticrouting_29"
#define STATICROUTING_30_TOK             "staticrouting_30"
#define STATICROUTING_31_TOK             "staticrouting_31"
#define STATICROUTING_32_TOK             "staticrouting_32"
#endif //#if NUM_STATICROUTING > 20
#endif //#if NUM_STATICROUTING > 10 

/* ------------------   dual wan routing tokens -----------------------*/
#ifdef HAS_PPPOE_JAPAN
#define DUALWANROUTING_TOK                    "dualwanrouting_"  
#define DUALWANROUTING_01_TOK                 "dualwanrouting_1"
#define DUALWANROUTING_02_TOK                 "dualwanrouting_2"
#define DUALWANROUTING_03_TOK                 "dualwanrouting_3"
#define DUALWANROUTING_04_TOK                 "dualwanrouting_4"
#define DUALWANROUTING_05_TOK                 "dualwanrouting_5"
#define DUALWANROUTING_06_TOK                 "dualwanrouting_6"
#define DUALWANROUTING_07_TOK                 "dualwanrouting_7"
#define DUALWANROUTING_08_TOK                 "dualwanrouting_8"
#define DUALWANROUTING_09_TOK                 "dualwanrouting_9"
#define DUALWANROUTING_10_TOK                 "dualwanrouting_10"
#endif

/* ------------------   domain routing tokens -----------------------*/
#if SUPPORT_DOMAIN_ROUTING
#define DOMAINROUTING_TOK                    "domainrouting_"  
#define DOMAINROUTING_01_TOK                 "domainrouting_1"
#define DOMAINROUTING_02_TOK                 "domainrouting_2"
#define DOMAINROUTING_03_TOK                 "domainrouting_3"
#define DOMAINROUTING_04_TOK                 "domainrouting_4"
#define DOMAINROUTING_05_TOK                 "domainrouting_5"
#define DOMAINROUTING_06_TOK                 "domainrouting_6"
#define DOMAINROUTING_07_TOK                 "domainrouting_7"
#define DOMAINROUTING_08_TOK                 "domainrouting_8"
#define DOMAINROUTING_09_TOK                 "domainrouting_9"
#define DOMAINROUTING_10_TOK                 "domainrouting_10"
#endif
#if SUPPORT_JP_STATIC_ROUTING
#define JP_STATICROUTING_ENABLE_TOK			 "jpstaticrouting_en"
#define JP_STATICROUTING_TOK                 "jpstaticrouting_"
#define JP_STATICROUTING_01_TOK				 "jpstaticrouting_1"
#define JP_STATICROUTING_02_TOK				 "jpstaticrouting_2"
#define JP_STATICROUTING_03_TOK				 "jpstaticrouting_3"
#define JP_STATICROUTING_04_TOK				 "jpstaticrouting_4"
#define JP_STATICROUTING_05_TOK				 "jpstaticrouting_5"
#endif

/* ------------------   ap macfilter tokens   -----------------------*/
#define MACFILTER_PRE_TOK                "macfilter"
#define MACFILTER_TYPE_TOK               "macfilter_type"
#define MACFILTER_ENABLE_TOK             "macfilter_en"
#define MACFILTER_TOK                    "macfilter_"  
#define MACFILTER_01_TOK                 "macfilter_1"
#define MACFILTER_02_TOK                 "macfilter_2"
#define MACFILTER_03_TOK                 "macfilter_3"
#define MACFILTER_04_TOK                 "macfilter_4"
#define MACFILTER_05_TOK                 "macfilter_5"
#define MACFILTER_06_TOK                 "macfilter_6"
#define MACFILTER_07_TOK                 "macfilter_7"
#define MACFILTER_08_TOK                 "macfilter_8"
#define MACFILTER_09_TOK                 "macfilter_9"
#define MACFILTER_10_TOK                 "macfilter_10"
#if NUM_MAC_FILTERS > 10
#define MACFILTER_11_TOK                 "macfilter_11"
#define MACFILTER_12_TOK                 "macfilter_12"
#define MACFILTER_13_TOK                 "macfilter_13"
#define MACFILTER_14_TOK                 "macfilter_14"
#define MACFILTER_15_TOK                 "macfilter_15"
#define MACFILTER_16_TOK                 "macfilter_16"
#define MACFILTER_17_TOK                 "macfilter_17"
#define MACFILTER_18_TOK                 "macfilter_18"
#define MACFILTER_19_TOK                 "macfilter_19"
#define MACFILTER_20_TOK                 "macfilter_20"
#if NUM_MAC_FILTERS > 20
#define MACFILTER_21_TOK                 "macfilter_21"
#define MACFILTER_22_TOK                 "macfilter_22"
#define MACFILTER_23_TOK                 "macfilter_23"
#define MACFILTER_24_TOK                 "macfilter_24"
#define MACFILTER_25_TOK                 "macfilter_25"
#define MACFILTER_26_TOK                 "macfilter_26"
#define MACFILTER_27_TOK                 "macfilter_27"
#define MACFILTER_28_TOK                 "macfilter_28"
#define MACFILTER_29_TOK                 "macfilter_29"
#define MACFILTER_30_TOK                 "macfilter_30"
#define MACFILTER_31_TOK                 "macfilter_31"
#define MACFILTER_32_TOK                 "macfilter_32"
#if NUM_MAC_FILTERS > 32
#define MACFILTER_33_TOK                 "macfilter_33"
#define MACFILTER_34_TOK                 "macfilter_34"
#define MACFILTER_35_TOK                 "macfilter_35"
#define MACFILTER_36_TOK                 "macfilter_36"
#define MACFILTER_37_TOK                 "macfilter_37"
#define MACFILTER_38_TOK                 "macfilter_38"
#define MACFILTER_39_TOK                 "macfilter_39"
#define MACFILTER_40_TOK                 "macfilter_40"
#define MACFILTER_41_TOK                 "macfilter_41"
#define MACFILTER_42_TOK                 "macfilter_42"
#define MACFILTER_43_TOK                 "macfilter_43"
#define MACFILTER_44_TOK                 "macfilter_44"
#define MACFILTER_45_TOK                 "macfilter_45"
#define MACFILTER_46_TOK                 "macfilter_46"
#define MACFILTER_47_TOK                 "macfilter_47"
#define MACFILTER_48_TOK                 "macfilter_48"
#define MACFILTER_49_TOK                 "macfilter_49"
#define MACFILTER_50_TOK                 "macfilter_50"
#if NUM_MAC_FILTERS > 50
#define MACFILTER_51_TOK                 "macfilter_51"
#define MACFILTER_52_TOK                 "macfilter_52"
#define MACFILTER_53_TOK                 "macfilter_53"
#define MACFILTER_54_TOK                 "macfilter_54"
#define MACFILTER_55_TOK                 "macfilter_55"
#define MACFILTER_56_TOK                 "macfilter_56"
#define MACFILTER_57_TOK                 "macfilter_57"
#define MACFILTER_58_TOK                 "macfilter_58"
#define MACFILTER_59_TOK                 "macfilter_59"
#define MACFILTER_60_TOK                 "macfilter_60"
#define MACFILTER_61_TOK                 "macfilter_61"
#define MACFILTER_62_TOK                 "macfilter_62"
#define MACFILTER_63_TOK                 "macfilter_63"
#define MACFILTER_64_TOK                 "macfilter_64"
#if NUM_MAC_FILTERS > 64
#define MACFILTER_65_TOK                  "macfilter_65"
#define MACFILTER_66_TOK                  "macfilter_66"
#define MACFILTER_67_TOK                  "macfilter_67"
#define MACFILTER_68_TOK                  "macfilter_68"
#define MACFILTER_69_TOK                  "macfilter_69"
#define MACFILTER_70_TOK                  "macfilter_70"
#define MACFILTER_71_TOK                  "macfilter_71"
#define MACFILTER_72_TOK                  "macfilter_72"
#define MACFILTER_73_TOK                  "macfilter_73"
#define MACFILTER_74_TOK                  "macfilter_74"
#define MACFILTER_75_TOK                  "macfilter_75"
#define MACFILTER_76_TOK                  "macfilter_76"
#define MACFILTER_77_TOK                  "macfilter_77"
#define MACFILTER_78_TOK                  "macfilter_78"
#define MACFILTER_79_TOK                  "macfilter_79"
#define MACFILTER_80_TOK                  "macfilter_80"
#define MACFILTER_81_TOK                  "macfilter_81"
#define MACFILTER_82_TOK                  "macfilter_82"
#define MACFILTER_83_TOK                  "macfilter_83"
#define MACFILTER_84_TOK                  "macfilter_84"
#define MACFILTER_85_TOK                  "macfilter_85"
#define MACFILTER_86_TOK                  "macfilter_86"
#define MACFILTER_87_TOK                  "macfilter_87"
#define MACFILTER_88_TOK                  "macfilter_88"
#define MACFILTER_89_TOK                  "macfilter_89"
#define MACFILTER_90_TOK                  "macfilter_90"
#define MACFILTER_91_TOK                  "macfilter_91"
#define MACFILTER_92_TOK                  "macfilter_92"
#define MACFILTER_93_TOK                  "macfilter_93"
#define MACFILTER_94_TOK                  "macfilter_94"
#define MACFILTER_95_TOK                  "macfilter_95"
#define MACFILTER_96_TOK                  "macfilter_96"
#define MACFILTER_97_TOK                  "macfilter_97"
#define MACFILTER_98_TOK                  "macfilter_98"
#define MACFILTER_99_TOK                  "macfilter_99"
#define MACFILTER_100_TOK                 "macfilter_100"
#define MACFILTER_101_TOK                 "macfilter_101"
#define MACFILTER_102_TOK                 "macfilter_102"
#define MACFILTER_103_TOK                 "macfilter_103"
#define MACFILTER_104_TOK                 "macfilter_104"
#define MACFILTER_105_TOK                 "macfilter_105"
#define MACFILTER_106_TOK                 "macfilter_106"
#define MACFILTER_107_TOK                 "macfilter_107"
#define MACFILTER_108_TOK                 "macfilter_108"
#define MACFILTER_109_TOK                 "macfilter_109"
#define MACFILTER_110_TOK                 "macfilter_110"
#define MACFILTER_111_TOK                 "macfilter_111"
#define MACFILTER_112_TOK                 "macfilter_112"
#define MACFILTER_113_TOK                 "macfilter_113"
#define MACFILTER_114_TOK                 "macfilter_114"
#define MACFILTER_115_TOK                 "macfilter_115"
#define MACFILTER_116_TOK                 "macfilter_116"
#define MACFILTER_117_TOK                 "macfilter_117"
#define MACFILTER_118_TOK                 "macfilter_118"
#define MACFILTER_119_TOK                 "macfilter_119"
#define MACFILTER_120_TOK                 "macfilter_120"
#define MACFILTER_121_TOK                 "macfilter_121"
#define MACFILTER_122_TOK                 "macfilter_122"
#define MACFILTER_123_TOK                 "macfilter_123"
#define MACFILTER_124_TOK                 "macfilter_124"
#define MACFILTER_125_TOK                 "macfilter_125"
#define MACFILTER_126_TOK                 "macfilter_126"
#define MACFILTER_127_TOK                 "macfilter_127"
#define MACFILTER_128_TOK                 "macfilter_128"
#if NUM_MAC_FILTERS > 128
#define MACFILTER_129_TOK                 "macfilter_129"
#define MACFILTER_130_TOK                 "macfilter_130"
#define MACFILTER_131_TOK                 "macfilter_131"
#define MACFILTER_132_TOK                 "macfilter_132"
#define MACFILTER_133_TOK                 "macfilter_133"
#define MACFILTER_134_TOK                 "macfilter_134"
#define MACFILTER_135_TOK                 "macfilter_135"
#define MACFILTER_136_TOK                 "macfilter_136"
#define MACFILTER_137_TOK                 "macfilter_137"
#define MACFILTER_138_TOK                 "macfilter_138"
#define MACFILTER_139_TOK                 "macfilter_139"
#define MACFILTER_140_TOK                 "macfilter_140"
#define MACFILTER_141_TOK                 "macfilter_141"
#define MACFILTER_142_TOK                 "macfilter_142"
#define MACFILTER_143_TOK                 "macfilter_143"
#define MACFILTER_144_TOK                 "macfilter_144"
#define MACFILTER_145_TOK                 "macfilter_145"
#define MACFILTER_146_TOK                 "macfilter_146"
#define MACFILTER_147_TOK                 "macfilter_147"
#define MACFILTER_148_TOK                 "macfilter_148"
#define MACFILTER_149_TOK                 "macfilter_149"
#define MACFILTER_150_TOK                 "macfilter_150"
#define MACFILTER_151_TOK                 "macfilter_151"
#define MACFILTER_152_TOK                 "macfilter_152"
#define MACFILTER_153_TOK                 "macfilter_153"
#define MACFILTER_154_TOK                 "macfilter_154"
#define MACFILTER_155_TOK                 "macfilter_155"
#define MACFILTER_156_TOK                 "macfilter_156"
#define MACFILTER_157_TOK                 "macfilter_157"
#define MACFILTER_158_TOK                 "macfilter_158"
#define MACFILTER_159_TOK                 "macfilter_159"
#define MACFILTER_160_TOK                 "macfilter_160"
#define MACFILTER_161_TOK                 "macfilter_161"
#define MACFILTER_162_TOK                 "macfilter_162"
#define MACFILTER_163_TOK                 "macfilter_163"
#define MACFILTER_164_TOK                 "macfilter_164"
#define MACFILTER_165_TOK                 "macfilter_165"
#define MACFILTER_166_TOK                 "macfilter_166"
#define MACFILTER_167_TOK                 "macfilter_167"
#define MACFILTER_168_TOK                 "macfilter_168"
#define MACFILTER_169_TOK                 "macfilter_169"
#define MACFILTER_170_TOK                 "macfilter_170"
#define MACFILTER_171_TOK                 "macfilter_171"
#define MACFILTER_172_TOK                 "macfilter_172"
#define MACFILTER_173_TOK                 "macfilter_173"
#define MACFILTER_174_TOK                 "macfilter_174"
#define MACFILTER_175_TOK                 "macfilter_175"
#define MACFILTER_176_TOK                 "macfilter_176"
#define MACFILTER_177_TOK                 "macfilter_177"
#define MACFILTER_178_TOK                 "macfilter_178"
#define MACFILTER_179_TOK                 "macfilter_179"
#define MACFILTER_180_TOK                 "macfilter_180"
#define MACFILTER_181_TOK                 "macfilter_181"
#define MACFILTER_182_TOK                 "macfilter_182"
#define MACFILTER_183_TOK                 "macfilter_183"
#define MACFILTER_184_TOK                 "macfilter_184"
#define MACFILTER_185_TOK                 "macfilter_185"
#define MACFILTER_186_TOK                 "macfilter_186"
#define MACFILTER_187_TOK                 "macfilter_187"
#define MACFILTER_188_TOK                 "macfilter_188"
#define MACFILTER_189_TOK                 "macfilter_189"
#define MACFILTER_190_TOK                 "macfilter_190"
#define MACFILTER_191_TOK                 "macfilter_191"
#define MACFILTER_192_TOK                 "macfilter_192"
#define MACFILTER_193_TOK                 "macfilter_193"
#define MACFILTER_194_TOK                 "macfilter_194"
#define MACFILTER_195_TOK                 "macfilter_195"
#define MACFILTER_196_TOK                 "macfilter_196"
#define MACFILTER_197_TOK                 "macfilter_197"
#define MACFILTER_198_TOK                 "macfilter_198"
#define MACFILTER_199_TOK                 "macfilter_199"
#define MACFILTER_200_TOK                 "macfilter_200"
#define MACFILTER_201_TOK                 "macfilter_201"
#define MACFILTER_202_TOK                 "macfilter_202"
#define MACFILTER_203_TOK                 "macfilter_203"
#define MACFILTER_204_TOK                 "macfilter_204"
#define MACFILTER_205_TOK                 "macfilter_205"
#define MACFILTER_206_TOK                 "macfilter_206"
#define MACFILTER_207_TOK                 "macfilter_207"
#define MACFILTER_208_TOK                 "macfilter_208"
#define MACFILTER_209_TOK                 "macfilter_209"
#define MACFILTER_210_TOK                 "macfilter_210"
#define MACFILTER_211_TOK                 "macfilter_211"
#define MACFILTER_212_TOK                 "macfilter_212"
#define MACFILTER_213_TOK                 "macfilter_213"
#define MACFILTER_214_TOK                 "macfilter_214"
#define MACFILTER_215_TOK                 "macfilter_215"
#define MACFILTER_216_TOK                 "macfilter_216"
#define MACFILTER_217_TOK                 "macfilter_217"
#define MACFILTER_218_TOK                 "macfilter_218"
#define MACFILTER_219_TOK                 "macfilter_219"
#define MACFILTER_220_TOK                 "macfilter_220"
#define MACFILTER_221_TOK                 "macfilter_221"
#define MACFILTER_222_TOK                 "macfilter_222"
#define MACFILTER_223_TOK                 "macfilter_223"
#define MACFILTER_224_TOK                 "macfilter_224"
#define MACFILTER_225_TOK                 "macfilter_225"
#define MACFILTER_226_TOK                 "macfilter_226"
#define MACFILTER_227_TOK                 "macfilter_227"
#define MACFILTER_228_TOK                 "macfilter_228"
#define MACFILTER_229_TOK                 "macfilter_229"
#define MACFILTER_230_TOK                 "macfilter_230"
#define MACFILTER_231_TOK                 "macfilter_231"
#define MACFILTER_232_TOK                 "macfilter_232"
#define MACFILTER_233_TOK                 "macfilter_233"
#define MACFILTER_234_TOK                 "macfilter_234"
#define MACFILTER_235_TOK                 "macfilter_235"
#define MACFILTER_236_TOK                 "macfilter_236"
#define MACFILTER_237_TOK                 "macfilter_237"
#define MACFILTER_238_TOK                 "macfilter_238"
#define MACFILTER_239_TOK                 "macfilter_239"
#define MACFILTER_240_TOK                 "macfilter_240"
#define MACFILTER_241_TOK                 "macfilter_241"
#define MACFILTER_242_TOK                 "macfilter_242"
#define MACFILTER_243_TOK                 "macfilter_243"
#define MACFILTER_244_TOK                 "macfilter_244"
#define MACFILTER_245_TOK                 "macfilter_245"
#define MACFILTER_246_TOK                 "macfilter_246"
#define MACFILTER_247_TOK                 "macfilter_247"
#define MACFILTER_248_TOK                 "macfilter_248"
#define MACFILTER_249_TOK                 "macfilter_249"
#define MACFILTER_250_TOK                 "macfilter_250"
#define MACFILTER_251_TOK                 "macfilter_251"
#define MACFILTER_252_TOK                 "macfilter_252"
#define MACFILTER_253_TOK                 "macfilter_253"
#define MACFILTER_254_TOK                 "macfilter_254"
#define MACFILTER_255_TOK                 "macfilter_255"
#define MACFILTER_256_TOK                 "macfilter_256"
#endif
#endif
#endif
#endif
#endif
#endif

#if HAS_WLAN2_DEV
#define MACFILTER2_ENABLE_TOK             "macfilter2_en"
#define MACFILTER2_TOK                    "macfilter2_"  
#define MACFILTER2_01_TOK                 "macfilter2_1"
#define MACFILTER2_02_TOK                 "macfilter2_2"
#define MACFILTER2_03_TOK                 "macfilter2_3"
#define MACFILTER2_04_TOK                 "macfilter2_4"
#define MACFILTER2_05_TOK                 "macfilter2_5"
#define MACFILTER2_06_TOK                 "macfilter2_6"
#define MACFILTER2_07_TOK                 "macfilter2_7"
#define MACFILTER2_08_TOK                 "macfilter2_8"
#define MACFILTER2_09_TOK                 "macfilter2_9"
#define MACFILTER2_10_TOK                 "macfilter2_10"
#if NUM_MAC_FILTERS > 10
#define MACFILTER2_11_TOK                 "macfilter2_11"
#define MACFILTER2_12_TOK                 "macfilter2_12"
#define MACFILTER2_13_TOK                 "macfilter2_13"
#define MACFILTER2_14_TOK                 "macfilter2_14"
#define MACFILTER2_15_TOK                 "macfilter2_15"
#define MACFILTER2_16_TOK                 "macfilter2_16"
#define MACFILTER2_17_TOK                 "macfilter2_17"
#define MACFILTER2_18_TOK                 "macfilter2_18"
#define MACFILTER2_19_TOK                 "macfilter2_19"
#define MACFILTER2_20_TOK                 "macfilter2_20"
#if NUM_MAC_FILTERS > 20
#define MACFILTER2_21_TOK                 "macfilter2_21"
#define MACFILTER2_22_TOK                 "macfilter2_22"
#define MACFILTER2_23_TOK                 "macfilter2_23"
#define MACFILTER2_24_TOK                 "macfilter2_24"
#define MACFILTER2_25_TOK                 "macfilter2_25"
#define MACFILTER2_26_TOK                 "macfilter2_26"
#define MACFILTER2_27_TOK                 "macfilter2_27"
#define MACFILTER2_28_TOK                 "macfilter2_28"
#define MACFILTER2_29_TOK                 "macfilter2_29"
#define MACFILTER2_30_TOK                 "macfilter2_30"
#define MACFILTER2_31_TOK                 "macfilter2_31"
#define MACFILTER2_32_TOK                 "macfilter2_32"
#endif
#endif
#endif

#if HAS_WLAN3_DEV
#define MACFILTER3_ENABLE_TOK             "macfilter3_en"
#define MACFILTER3_TOK                    "macfilter3_"  
#define MACFILTER3_01_TOK                 "macfilter3_1"
#define MACFILTER3_02_TOK                 "macfilter3_2"
#define MACFILTER3_03_TOK                 "macfilter3_3"
#define MACFILTER3_04_TOK                 "macfilter3_4"
#define MACFILTER3_05_TOK                 "macfilter3_5"
#define MACFILTER3_06_TOK                 "macfilter3_6"
#define MACFILTER3_07_TOK                 "macfilter3_7"
#define MACFILTER3_08_TOK                 "macfilter3_8"
#define MACFILTER3_09_TOK                 "macfilter3_9"
#define MACFILTER3_10_TOK                 "macfilter3_10"
#if NUM_MAC_FILTERS > 10
#define MACFILTER3_11_TOK                 "macfilter3_11"
#define MACFILTER3_12_TOK                 "macfilter3_12"
#define MACFILTER3_13_TOK                 "macfilter3_13"
#define MACFILTER3_14_TOK                 "macfilter3_14"
#define MACFILTER3_15_TOK                 "macfilter3_15"
#define MACFILTER3_16_TOK                 "macfilter3_16"
#define MACFILTER3_17_TOK                 "macfilter3_17"
#define MACFILTER3_18_TOK                 "macfilter3_18"
#define MACFILTER3_19_TOK                 "macfilter3_19"
#define MACFILTER3_20_TOK                 "macfilter3_20"
#if NUM_MAC_FILTERS > 20
#define MACFILTER3_21_TOK                 "macfilter3_21"
#define MACFILTER3_22_TOK                 "macfilter3_22"
#define MACFILTER3_23_TOK                 "macfilter3_23"
#define MACFILTER3_24_TOK                 "macfilter3_24"
#define MACFILTER3_25_TOK                 "macfilter3_25"
#define MACFILTER3_26_TOK                 "macfilter3_26"
#define MACFILTER3_27_TOK                 "macfilter3_27"
#define MACFILTER3_28_TOK                 "macfilter3_28"
#define MACFILTER3_29_TOK                 "macfilter3_29"
#define MACFILTER3_30_TOK                 "macfilter3_30"
#define MACFILTER3_31_TOK                 "macfilter3_31"
#define MACFILTER3_32_TOK                 "macfilter3_32"
#endif
#endif
#endif

#if HAS_WLAN4_DEV
#define MACFILTER4_ENABLE_TOK             "macfilter4_en"
#define MACFILTER4_TOK                    "macfilter4_"  
#define MACFILTER4_01_TOK                 "macfilter4_1"
#define MACFILTER4_02_TOK                 "macfilter4_2"
#define MACFILTER4_03_TOK                 "macfilter4_3"
#define MACFILTER4_04_TOK                 "macfilter4_4"
#define MACFILTER4_05_TOK                 "macfilter4_5"
#define MACFILTER4_06_TOK                 "macfilter4_6"
#define MACFILTER4_07_TOK                 "macfilter4_7"
#define MACFILTER4_08_TOK                 "macfilter4_8"
#define MACFILTER4_09_TOK                 "macfilter4_9"
#define MACFILTER4_10_TOK                 "macfilter4_10"
#if NUM_MAC_FILTERS > 10
#define MACFILTER4_11_TOK                 "macfilter4_11"
#define MACFILTER4_12_TOK                 "macfilter4_12"
#define MACFILTER4_13_TOK                 "macfilter4_13"
#define MACFILTER4_14_TOK                 "macfilter4_14"
#define MACFILTER4_15_TOK                 "macfilter4_15"
#define MACFILTER4_16_TOK                 "macfilter4_16"
#define MACFILTER4_17_TOK                 "macfilter4_17"
#define MACFILTER4_18_TOK                 "macfilter4_18"
#define MACFILTER4_19_TOK                 "macfilter4_19"
#define MACFILTER4_20_TOK                 "macfilter4_20"
#if NUM_MAC_FILTERS > 20
#define MACFILTER4_21_TOK                 "macfilter4_21"
#define MACFILTER4_22_TOK                 "macfilter4_22"
#define MACFILTER4_23_TOK                 "macfilter4_23"
#define MACFILTER4_24_TOK                 "macfilter4_24"
#define MACFILTER4_25_TOK                 "macfilter4_25"
#define MACFILTER4_26_TOK                 "macfilter4_26"
#define MACFILTER4_27_TOK                 "macfilter4_27"
#define MACFILTER4_28_TOK                 "macfilter4_28"
#define MACFILTER4_29_TOK                 "macfilter4_29"
#define MACFILTER4_30_TOK                 "macfilter4_30"
#define MACFILTER4_31_TOK                 "macfilter4_31"
#define MACFILTER4_32_TOK                 "macfilter4_32"
#endif
#endif
#endif

#if HAS_AP_PROFILE
#define _ORDER_TOK					"order"
#define _BSSID_TOK					"bssid"
#define _WPAKEY_TOK					"wpapsk"
#if HAS_WPA_SUPPLICANT_FIXED_MAC	
#define _CONN_WITH_MAC_TOK      	"conn_with_mac"
#endif
#define APPROFILE_					"ap"
#define APPROFILE_01_				"ap1"
#define APPROFILE_01_ENABLE_TOK		APPROFILE_01_ _ENABLE_TOK
#define APPROFILE_01_ORDER_TOK		APPROFILE_01_ _ORDER_TOK
#define APPROFILE_01_SSID_TOK		APPROFILE_01_ _SSID_TOK
#define APPROFILE_01_BSSID_TOK		APPROFILE_01_ _BSSID_TOK
#if HAS_WPA_SUPPLICANT_FIXED_MAC	
#define APPROFILE_01_CONN_WITH_MAC_TOK   APPROFILE_01_ _CONN_WITH_MAC_TOK
#endif
#define APPROFILE_01_AUTH_TOK       APPROFILE_01_ _AUTH_TOK
#define APPROFILE_01_ENC_TYPE_TOK   APPROFILE_01_ _ENC_TYPE_TOK
#define APPROFILE_01_WEP_TOK		APPROFILE_01_ _WEP_TOK
#define APPROFILE_01_KEYID_TOK		APPROFILE_01_ _KEYID_TOK
#define APPROFILE_01_KEYTYPE_TOK    APPROFILE_01_ _KEYTYPE_TOK
#define APPROFILE_01_WEPKEY_0_TOK   APPROFILE_01_ _WEPKEY_0_TOK
#define APPROFILE_01_WEPKEY_1_TOK   APPROFILE_01_ _WEPKEY_1_TOK
#define APPROFILE_01_WEPKEY_2_TOK   APPROFILE_01_ _WEPKEY_2_TOK
#define APPROFILE_01_WEPKEY_3_TOK   APPROFILE_01_ _WEPKEY_3_TOK
#define APPROFILE_01_WPAKEY_TOK     APPROFILE_01_ _WPAKEY_TOK
#define APPROFILE_01_PASSPHRASE_TOK APPROFILE_01_ _WPAPASSPHRASE_TOK
#define APPROFILE_01_8021X_METHOD_TOK	APPROFILE_01_ _8021X_METHOD_TOK
#define APPROFILE_01_8021X_IDENTITY_TOK	APPROFILE_01_ _8021X_IDENTITY_TOK
#define APPROFILE_01_8021X_PWD_TOK		APPROFILE_01_ _8021X_PWD_TOK
#define APPROFILE_02_				"ap2"
#define APPROFILE_02_ENABLE_TOK		APPROFILE_02_ _ENABLE_TOK
#define APPROFILE_02_ORDER_TOK		APPROFILE_02_ _ORDER_TOK
#define APPROFILE_02_SSID_TOK		APPROFILE_02_ _SSID_TOK
#define APPROFILE_02_BSSID_TOK		APPROFILE_02_ _BSSID_TOK
#if HAS_WPA_SUPPLICANT_FIXED_MAC	
#define APPROFILE_02_CONN_WITH_MAC_TOK   APPROFILE_02_ _CONN_WITH_MAC_TOK
#endif
#define APPROFILE_02_AUTH_TOK       APPROFILE_02_ _AUTH_TOK
#define APPROFILE_02_ENC_TYPE_TOK   APPROFILE_02_ _ENC_TYPE_TOK
#define APPROFILE_02_WEP_TOK		APPROFILE_02_ _WEP_TOK
#define APPROFILE_02_KEYID_TOK		APPROFILE_02_ _KEYID_TOK
#define APPROFILE_02_KEYTYPE_TOK    APPROFILE_02_ _KEYTYPE_TOK
#define APPROFILE_02_WEPKEY_0_TOK   APPROFILE_02_ _WEPKEY_0_TOK
#define APPROFILE_02_WEPKEY_1_TOK   APPROFILE_02_ _WEPKEY_1_TOK
#define APPROFILE_02_WEPKEY_2_TOK   APPROFILE_02_ _WEPKEY_2_TOK
#define APPROFILE_02_WEPKEY_3_TOK   APPROFILE_02_ _WEPKEY_3_TOK
#define APPROFILE_02_WPAKEY_TOK     APPROFILE_02_ _WPAKEY_TOK
#define APPROFILE_02_PASSPHRASE_TOK APPROFILE_02_ _WPAPASSPHRASE_TOK
#define APPROFILE_02_8021X_METHOD_TOK	APPROFILE_02_ _8021X_METHOD_TOK
#define APPROFILE_02_8021X_IDENTITY_TOK	APPROFILE_02_ _8021X_IDENTITY_TOK
#define APPROFILE_02_8021X_PWD_TOK		APPROFILE_02_ _8021X_PWD_TOK
#define APPROFILE_03_				"ap3"
#define APPROFILE_03_ENABLE_TOK		APPROFILE_03_ _ENABLE_TOK
#define APPROFILE_03_ORDER_TOK		APPROFILE_03_ _ORDER_TOK
#define APPROFILE_03_SSID_TOK		APPROFILE_03_ _SSID_TOK
#define APPROFILE_03_BSSID_TOK		APPROFILE_03_ _BSSID_TOK
#if HAS_WPA_SUPPLICANT_FIXED_MAC	
#define APPROFILE_03_CONN_WITH_MAC_TOK   APPROFILE_03_ _CONN_WITH_MAC_TOK
#endif
#define APPROFILE_03_AUTH_TOK       APPROFILE_03_ _AUTH_TOK
#define APPROFILE_03_ENC_TYPE_TOK   APPROFILE_03_ _ENC_TYPE_TOK
#define APPROFILE_03_WEP_TOK		APPROFILE_03_ _WEP_TOK
#define APPROFILE_03_KEYID_TOK		APPROFILE_03_ _KEYID_TOK
#define APPROFILE_03_KEYTYPE_TOK    APPROFILE_03_ _KEYTYPE_TOK
#define APPROFILE_03_WEPKEY_0_TOK   APPROFILE_03_ _WEPKEY_0_TOK
#define APPROFILE_03_WEPKEY_1_TOK   APPROFILE_03_ _WEPKEY_1_TOK
#define APPROFILE_03_WEPKEY_2_TOK   APPROFILE_03_ _WEPKEY_2_TOK
#define APPROFILE_03_WEPKEY_3_TOK   APPROFILE_03_ _WEPKEY_3_TOK
#define APPROFILE_03_WPAKEY_TOK     APPROFILE_03_ _WPAKEY_TOK
#define APPROFILE_03_PASSPHRASE_TOK APPROFILE_03_ _WPAPASSPHRASE_TOK
#define APPROFILE_03_8021X_METHOD_TOK	APPROFILE_03_ _8021X_METHOD_TOK
#define APPROFILE_03_8021X_IDENTITY_TOK	APPROFILE_03_ _8021X_IDENTITY_TOK
#define APPROFILE_03_8021X_PWD_TOK		APPROFILE_03_ _8021X_PWD_TOK
#endif
/* ---------------------   L7 filter ---------------------------------------*/
#if 0
#define L7FILTER_YAHOO_TOK               "l7_yahoo"
#define L7FILTER_ICQ_TOK                 "l7_icq"
#define L7FILTER_MSN_TOK                 "l7_msn"
#define L7FILTER_MSNTRFILE_TOK           "l7_msntrfile"
#define L7FILTER_QQ_TOK                  "l7_qq"
#define L7FILTER_SKYPE_TOK               "l7_skype"
#define L7FILTER_SKYPEOUT_TOK            "l7_skypeout"
#define L7FILTER_P2P_TOK                 "l7_p2p"
#define L7FILTER_VNC_TOK                 "l7_vnc"
#endif
/* ---------------------   BLOCK ---------------------------------------*/
#define BLOCK_MSN_TOK                    "block_msn"
#define BLOCK_YAHOO_TOK                  "block_yahoo"

#define BLOCK_KEYWORD_ENABLE_TOK         "block_keyword_en"
#define BLOCK_KEYWORD_TOK                "block_keyword_"
#define BLOCK_KEYWORD_01_TOK             "block_keyword_1"
#define BLOCK_KEYWORD_02_TOK             "block_keyword_2"
#define BLOCK_KEYWORD_03_TOK             "block_keyword_3"
#define BLOCK_KEYWORD_04_TOK             "block_keyword_4"
#define BLOCK_KEYWORD_05_TOK             "block_keyword_5"
#define BLOCK_KEYWORD_06_TOK             "block_keyword_6"
#define BLOCK_KEYWORD_07_TOK             "block_keyword_7"
#define BLOCK_KEYWORD_08_TOK             "block_keyword_8"
#define BLOCK_KEYWORD_09_TOK             "block_keyword_9"
#define BLOCK_KEYWORD_10_TOK             "block_keyword_10"
/* ---------------------   HAS_SNMPD_SUPPORT ---------------------------------------*/
#define SNMPD_ENABLE_TOK                 "snmpd_en"
#define SNMPD_COMMUNITY_ACCESS_TOK       "snmpd_comm_acc_"
#define SNMPD_COMMUNITY_ACCESS_1_TOK     "snmpd_comm_acc_1"
#define SNMPD_COMMUNITY_ACCESS_2_TOK     "snmpd_comm_acc_2"
#define SNMPD_COMMUNITY_ACCESS_3_TOK     "snmpd_comm_acc_3"
#define SNMPD_COMMUNITY_ACCESS_4_TOK     "snmpd_comm_acc_4"
#define SNMPD_COMMUNITY_ACCESS_5_TOK     "snmpd_comm_acc_5"
#define SNMPD_COMMUNITY_COMMUNITY_TOK    "snmpd_comm_comm_"
#define SNMPD_COMMUNITY_COMMUNITY_1_TOK  "snmpd_comm_comm_1"     /*RW Community*/
#define SNMPD_COMMUNITY_COMMUNITY_2_TOK  "snmpd_comm_comm_2"	 /*RO Community*/
#define SNMPD_COMMUNITY_COMMUNITY_3_TOK  "snmpd_comm_comm_3"
#define SNMPD_COMMUNITY_COMMUNITY_4_TOK  "snmpd_comm_comm_4"
#define SNMPD_COMMUNITY_COMMUNITY_5_TOK  "snmpd_comm_comm_5"
#define SNMPD_COMMUNITY_VALIDITY_TOK     "snmpd_comm_valid_"
#define SNMPD_COMMUNITY_VALIDITY_1_TOK   "snmpd_comm_valid_1"
#define SNMPD_COMMUNITY_VALIDITY_2_TOK   "snmpd_comm_valid_2"
#define SNMPD_COMMUNITY_VALIDITY_3_TOK   "snmpd_comm_valid_3"
#define SNMPD_COMMUNITY_VALIDITY_4_TOK   "snmpd_comm_valid_4"
#define SNMPD_COMMUNITY_VALIDITY_5_TOK   "snmpd_comm_valid_5"
#define SNMPD_COMMUNITY_VER_TOK          "snmpd_comm_ver_"
#define SNMPD_COMMUNITY_VER_1_TOK        "snmpd_comm_ver_1"
#define SNMPD_COMMUNITY_VER_2_TOK        "snmpd_comm_ver_2"
#define SNMPD_COMMUNITY_VER_3_TOK        "snmpd_comm_ver_3"
#define SNMPD_COMMUNITY_VER_4_TOK        "snmpd_comm_ver_4"
#define SNMPD_COMMUNITY_VER_5_TOK        "snmpd_comm_ver_5"
#define	SNMPD_TRAP_ENABLE_TOK			 "snmpd_trap_en"
#define SNMPD_TRAP_VER_TOK               "snmpd_trap_ver_"
#define SNMPD_TRAP_VER_1_TOK             "snmpd_trap_ver_1"
#define SNMPD_TRAP_VER_2_TOK             "snmpd_trap_ver_2"
#define SNMPD_TRAP_VER_3_TOK             "snmpd_trap_ver_3"
#define SNMPD_TRAP_VER_4_TOK             "snmpd_trap_ver_4"
#define SNMPD_TRAP_VER_5_TOK             "snmpd_trap_ver_5"
#define SNMPD_TRAP_IP_TOK                "snmpd_trap_ip_"
#define SNMPD_TRAP_IP_1_TOK              "snmpd_trap_ip_1"
#define SNMPD_TRAP_IP_2_TOK              "snmpd_trap_ip_2"
#define SNMPD_TRAP_IP_3_TOK              "snmpd_trap_ip_3"
#define SNMPD_TRAP_IP_4_TOK              "snmpd_trap_ip_4"
#define SNMPD_TRAP_IP_5_TOK              "snmpd_trap_ip_5"
#define SNMPD_TRAP_COMMUNITY_TOK         "snmpd_trap_comm_"
#define SNMPD_TRAP_COMMUNITY_1_TOK       "snmpd_trap_comm_1"
#define SNMPD_TRAP_COMMUNITY_2_TOK       "snmpd_trap_comm_2"
#define SNMPD_TRAP_COMMUNITY_3_TOK       "snmpd_trap_comm_3"
#define SNMPD_TRAP_COMMUNITY_4_TOK       "snmpd_trap_comm_4"
#define SNMPD_TRAP_COMMUNITY_5_TOK       "snmpd_trap_comm_5"
#define SNMPD_STATIONID_TOK              "snmpd_stationid"
#define SNMPD_POWERMANAGE_TOK            "snmpd_powermanage"
#define SNMPD_SSID_TOK                   "snmpd_ssid"
#define SNMPD_BSSTYPE_TOK                "snmpd_bsstype"
#define SNMPD_RATESET_TOK                "snmpd_rateset"
#define SNMPD_AUTHALGO_1_TOK             "snmpd_authalgo1"
#define SNMPD_AUTHALGO_2_TOK             "snmpd_authalgo2"
#define SNMPD_AUTHENABLE_1_TOK           "snmpd_authenable1"
#define SNMPD_AUTHENABLE_2_TOK           "snmpd_authenable2"
#define SNMPD_WEPDEFKEY_1_TOK            "snmpd_wepdefkey1"
#define SNMPD_WEPDEFKEY_2_TOK            "snmpd_wepdefkey2"
#define SNMPD_WEPDEFKEY_3_TOK            "snmpd_wepdefkey3"
#define SNMPD_WEPDEFKEY_4_TOK            "snmpd_wepdefkey4"
#define SNMPD_PRIVACY_TOK                "snmpd_privacy"
#define SNMPD_WEPDEFKEYID_TOK            "snmpd_wepdefkeyid"
#define SNMPD_EXCLUDE_TOK                "snmpd_exclude"
#define SNMPD_MACADDR_TOK                "snmpd_macaddr"
#define SNMPD_RTS_THRESHOLD_TOK          "snmpd_rts_thres"
#define SNMPD_FRAG_THRESHOLD_TOK         "snmpd_frag"
#define SNMPD_BEACON_TOK                 "snmpd_beacon"
#define SNMPD_DTIM_TOK                   "snmpd_dtim"
#define SNMPD_SYSTEM_LOCATION_TOK        "snmpd_sys_location"
#define SNMPD_SYSTEM_CONTRACT_TOK        "snmpd_sys_contract"
#define SNMPD_SYSTEM_NAME_TOK			"snmpd_sys_name"
#if HAS_SNMP_MANAGEMENT_IP_SUPPORT
#define SNMPD_MANAGEMENT_IP_TOK			"snmpd_mm_ip"
#endif
#if HAS_SNMPD_WAN_SUPPORT
#define SNMPD_CONNECT_METHOD_TOK        "snmpd_conn_mode"
#define SNMPD_REMOTE_WAN_IP_TOK        	"snmpd_wan_ip"     
#endif
/* ---------------------   LLTD ---------------------------------------*/
#define LLTD_ENABLE_TOK					"lltd_en"
/* ---------------------   Schedule ---------------------------------------*/
#define SCHEDULE_ENABLE_TOK              "schedule_en"
#define SCHEDULE_TOK                     "schedule_"
#define SCHEDULE_01_TOK                  "schedule_1"
#define SCHEDULE_02_TOK                  "schedule_2"
#define SCHEDULE_03_TOK                  "schedule_3"
#define SCHEDULE_04_TOK                  "schedule_4"
#define SCHEDULE_05_TOK                  "schedule_5"
#define SCHEDULE_06_TOK                  "schedule_6"
#define SCHEDULE_07_TOK                  "schedule_7"
#define SCHEDULE_08_TOK                  "schedule_8"
#if NUM_SCHEDULE_LIST > 8
#define SCHEDULE_09_TOK                  "schedule_9"
#define SCHEDULE_10_TOK                  "schedule_10"
#if NUM_SCHEDULE_LIST > 10
#define SCHEDULE_11_TOK                  "schedule_11"
#define SCHEDULE_12_TOK                  "schedule_12"
#define SCHEDULE_13_TOK                  "schedule_13"
#define SCHEDULE_14_TOK                  "schedule_14"
#define SCHEDULE_15_TOK                  "schedule_15"
#define SCHEDULE_16_TOK                  "schedule_16"
#define SCHEDULE_17_TOK                  "schedule_17"
#define SCHEDULE_18_TOK                  "schedule_18"
#define SCHEDULE_19_TOK                  "schedule_19"
#define SCHEDULE_20_TOK                  "schedule_20"
#if NUM_SCHEDULE_LIST > 20
#define SCHEDULE_21_TOK                  "schedule_21"
#define SCHEDULE_22_TOK                  "schedule_22"
#define SCHEDULE_23_TOK                  "schedule_23"
#define SCHEDULE_24_TOK                  "schedule_24"
#define SCHEDULE_25_TOK                  "schedule_25"
#define SCHEDULE_26_TOK                  "schedule_26"
#define SCHEDULE_27_TOK                  "schedule_27"
#define SCHEDULE_28_TOK                  "schedule_28"
#define SCHEDULE_29_TOK                  "schedule_29"
#define SCHEDULE_30_TOK                  "schedule_30"
#endif //#if NUM_SCHEDULE_LIST > 20
#endif //#if NUM_SCHEDULE_LIST > 10
#endif //#if NUM_SCHEDULE_LIST > 8 
#if FOR_COREGA || FOR_ZYXEL
/* Power Saving */
#define PS_SCHEDULE_TOK                 "ps_sched_"
#define PS_SCHEDULE_1_TOK               "ps_sched_1"
#define PS_SCHEDULE_2_TOK               "ps_sched_2"
#define PS_SCHEDULE_3_TOK               "ps_sched_3"
#define PS_SCHEDULE_4_TOK               "ps_sched_4"
#define PS_SCHEDULE_5_TOK               "ps_sched_5"
#define PS_SCHEDULE_6_TOK               "ps_sched_6"
#define PS_SCHEDULE_7_TOK               "ps_sched_7"
#define PS_SCHEDULE_8_TOK               "ps_sched_8"
#define PS_SCHEDULE_9_TOK               "ps_sched_9"
#define PS_SCHEDULE_10_TOK               "ps_sched_10"
#endif
#if HAS_SCHEDULE_EXTEND
#define SCHEDULEB_TOK                    "scheduleB_"
#define SCHEDULEB_01_TOK                 "scheduleB_1"
#define SCHEDULEB_02_TOK                 "scheduleB_2"
#define SCHEDULEB_03_TOK                 "scheduleB_3"
#define SCHEDULEB_04_TOK                 "scheduleB_4"
#define SCHEDULEB_05_TOK                 "scheduleB_5"
#define SCHEDULEB_06_TOK                 "scheduleB_6"
#define SCHEDULEB_07_TOK                 "scheduleB_7"
#define SCHEDULEB_08_TOK                 "scheduleB_8"
#define SCHEDULEB_09_TOK                 "scheduleB_9"
#define SCHEDULEB_10_TOK                 "scheduleB_10"
#endif

#if FOR_ZYXEL
#define WLS_RADIO_SCHEDULE_TOK           "wls_radio_1"
#if HAS_SCHEDULE_EXTEND
#define WLS_RADIO_SCHEDULEB_TOK          "wls_radioB_1"
#endif
#endif/* FOR_ZYXEL */

#define SCHEDULE_FOR_PBX                 "schedule_forPbx"
#define TIME_TYPE_TOK                    "timetype"
#if FOR_DLINK
#define SCHEDULE_TIME_FORMAT			 "sched_timeformate"
#endif
/* ---------------------   TIME_ZONE ---------------------------------------*/
#define TIME_ZONE_TOK                    "timezone"
#define TIME_DAYLIGHT_TOK                "timedaylight"

#if USE_STANDARD_DAYLIGHTSAVING
#define TIME_START_WEEK_TOK				 "timestartweek"
#define TIME_START_DAY_TOK				 "timestartday"
#define TIME_START_MONTH_TOK			 "timestartmonth"
#define TIME_START_HOUR_TOK				 "timestarthour"
#define TIME_END_WEEK_TOK				 "timeendweek"
#define TIME_END_DAY_TOK				 "timeendday"
#define TIME_END_MONTH_TOK			 	 "timeendmonth"
#define TIME_END_HOUR_TOK				 "timeendhour"
#else
#define TIME_STARTM_TOK                  "timestartm"
#define TIME_STARTD_TOK                  "timestartd"
#define TIME_STARTH_TOK                  "timestarth"
#define TIME_ENDM_TOK                    "timeendm"
#define TIME_ENDD_TOK                    "timeendd"
#define TIME_ENDH_TOK                    "timeendh"
#endif
#if HAS_MANUAL_TIME_SETTING
#define TIME_MANUAL_TOK                  "timemanual"
#endif

/* ---------------------   NTP ---------------------------------------*/
#define NTP_ENABLE_TOK                   "ntpstatus"
#define NTP_AUTO_NTP_SERV_TOK			 "ntp_auto_ntpserv"
#define NTP_POLLIING_TIME_TOK            "ntppolling"
#define NTP_SERVER_TOK                   "ntpserver_"
#define NTP_SERVER_01_TOK                "ntpserver_1"
#define NTP_SERVER_02_TOK                "ntpserver_2"
#define NTP_SERVER_03_TOK                "ntpserver_3"
#define NTP_USED_INDEX_TOK               "ntp_used_index"
#define NTP_SERVER_ENABLE_TOK            "ntp_server_enable"
#if HAS_LOCAL_NTP_SERVER
#define NTP_LOCAL_SERVER_TOK             "ntp_local_server"
#endif
/* ---------------------   FTP info ---------------------------------------*/
/* FTP info, Hostname, USER ID, PWD, File path */
#define FTP_HOST_TOK	                 "ftp_host"
#define FTP_PORT_TOK	                 "ftp_port"
#define FTP_USERID_TOK	                 "ftp_userid"
#define FTP_USERPWD_TOK	                 "ftp_userpwd"
#define FTP_FILENAME_TOK	   		     "ftp_filename"
#if HAS_SC_AUTO_FW_CHECK
#define AUTO_FW_CHECK_ACTION_TOK	  "auto_fw_action"
#define AUTO_FW_CHECK_ONSERVER_TOK	  "auto_fw_onserver"
#define AUTO_FW_INSTALL_STATUS_TOK	  "auto_fw_status"
#define AUTO_FW_NEVERCHECK_ENABLE_TOK   "auto_fw_nevercheck"
#endif
/* ---------------------   NAT Port Forwarding ---------------------------------------*/
#define NAT_ENABLE_TOK					 "nat_enable"
#define NAT_PORT_FORWARD_ENABLE_TOK      "portfwd_en"
#define NAT_PORT_FORWARD_TOK             "portfwd_"
#define NAT_PORT_FORWARD_01_TOK          "portfwd_1"
#define NAT_PORT_FORWARD_02_TOK          "portfwd_2"
#define NAT_PORT_FORWARD_03_TOK          "portfwd_3"
#define NAT_PORT_FORWARD_04_TOK          "portfwd_4"
#define NAT_PORT_FORWARD_05_TOK          "portfwd_5"
#define NAT_PORT_FORWARD_06_TOK          "portfwd_6"
#define NAT_PORT_FORWARD_07_TOK          "portfwd_7"
#define NAT_PORT_FORWARD_08_TOK          "portfwd_8"
#define NAT_PORT_FORWARD_09_TOK          "portfwd_9"
#define NAT_PORT_FORWARD_10_TOK          "portfwd_10"
#if NUM_PORT_FORWARD > 10
#define NAT_PORT_FORWARD_11_TOK          "portfwd_11"
#define NAT_PORT_FORWARD_12_TOK          "portfwd_12"
#define NAT_PORT_FORWARD_13_TOK          "portfwd_13"
#define NAT_PORT_FORWARD_14_TOK          "portfwd_14"
#define NAT_PORT_FORWARD_15_TOK          "portfwd_15"
#define NAT_PORT_FORWARD_16_TOK          "portfwd_16"
#define NAT_PORT_FORWARD_17_TOK          "portfwd_17"
#define NAT_PORT_FORWARD_18_TOK          "portfwd_18"
#define NAT_PORT_FORWARD_19_TOK          "portfwd_19"
#define NAT_PORT_FORWARD_20_TOK          "portfwd_20"
#if NUM_PORT_FORWARD > 20
#define NAT_PORT_FORWARD_21_TOK          "portfwd_21"
#define NAT_PORT_FORWARD_22_TOK          "portfwd_22"
#define NAT_PORT_FORWARD_23_TOK          "portfwd_23"
#define NAT_PORT_FORWARD_24_TOK          "portfwd_24"
#if NUM_PORT_FORWARD > 24
#define NAT_PORT_FORWARD_25_TOK          "portfwd_25"
#define NAT_PORT_FORWARD_26_TOK          "portfwd_26"
#define NAT_PORT_FORWARD_27_TOK          "portfwd_27"
#define NAT_PORT_FORWARD_28_TOK          "portfwd_28"
#define NAT_PORT_FORWARD_29_TOK          "portfwd_29"
#define NAT_PORT_FORWARD_30_TOK          "portfwd_30"
#define NAT_PORT_FORWARD_31_TOK          "portfwd_31"
#define NAT_PORT_FORWARD_32_TOK          "portfwd_32"
#endif
#endif
#endif
/* ---------------------   Adv NAT Port Forwarding ---------------------------------------*/
#if HAS_ADV_NAT
#define ADV_NAT_PORT_FORWARD_ENABLE_TOK      "adv_portfwd_en"
#define ADV_NAT_PORT_FORWARD_TOK             "adv_portfwd_"
#define ADV_NAT_PORT_FORWARD_01_TOK          "adv_portfwd_1"
#define ADV_NAT_PORT_FORWARD_02_TOK          "adv_portfwd_2"
#define ADV_NAT_PORT_FORWARD_03_TOK          "adv_portfwd_3"
#define ADV_NAT_PORT_FORWARD_04_TOK          "adv_portfwd_4"
#define ADV_NAT_PORT_FORWARD_05_TOK          "adv_portfwd_5"
#define ADV_NAT_PORT_FORWARD_06_TOK          "adv_portfwd_6"
#define ADV_NAT_PORT_FORWARD_07_TOK          "adv_portfwd_7"
#define ADV_NAT_PORT_FORWARD_08_TOK          "adv_portfwd_8"
#define ADV_NAT_PORT_FORWARD_09_TOK          "adv_portfwd_9"
#define ADV_NAT_PORT_FORWARD_10_TOK          "adv_portfwd_10"
#if NUM_PORT_FORWARD > 10
#define ADV_NAT_PORT_FORWARD_11_TOK          "adv_portfwd_11"
#define ADV_NAT_PORT_FORWARD_12_TOK          "adv_portfwd_12"
#define ADV_NAT_PORT_FORWARD_13_TOK          "adv_portfwd_13"
#define ADV_NAT_PORT_FORWARD_14_TOK          "adv_portfwd_14"
#define ADV_NAT_PORT_FORWARD_15_TOK          "adv_portfwd_15"
#define ADV_NAT_PORT_FORWARD_16_TOK          "adv_portfwd_16"
#define ADV_NAT_PORT_FORWARD_17_TOK          "adv_portfwd_17"
#define ADV_NAT_PORT_FORWARD_18_TOK          "adv_portfwd_18"
#define ADV_NAT_PORT_FORWARD_19_TOK          "adv_portfwd_19"
#define ADV_NAT_PORT_FORWARD_20_TOK          "adv_portfwd_20"
#if NUM_PORT_FORWARD > 20
#define ADV_NAT_PORT_FORWARD_21_TOK          "adv_portfwd_21"
#define ADV_NAT_PORT_FORWARD_22_TOK          "adv_portfwd_22"
#define ADV_NAT_PORT_FORWARD_23_TOK          "adv_portfwd_23"
#define ADV_NAT_PORT_FORWARD_24_TOK          "adv_portfwd_24"
#if NUM_PORT_FORWARD > 24
#define ADV_NAT_PORT_FORWARD_25_TOK          "adv_portfwd_25"
#define ADV_NAT_PORT_FORWARD_26_TOK          "adv_portfwd_26"
#define ADV_NAT_PORT_FORWARD_27_TOK          "adv_portfwd_27"
#define ADV_NAT_PORT_FORWARD_28_TOK          "adv_portfwd_28"
#define ADV_NAT_PORT_FORWARD_29_TOK          "adv_portfwd_29"
#define ADV_NAT_PORT_FORWARD_30_TOK          "adv_portfwd_30"
#define ADV_NAT_PORT_FORWARD_31_TOK          "adv_portfwd_31"
#define ADV_NAT_PORT_FORWARD_32_TOK          "adv_portfwd_32"
#endif
#endif
#endif
#define ADV_NAT_PORT_FORWARD_EXT_TOK             "adv_portfwde_"
#define ADV_NAT_PORT_FORWARD_EXT_01_TOK          "adv_portfwde_1"
#define ADV_NAT_PORT_FORWARD_EXT_02_TOK          "adv_portfwde_2"
#define ADV_NAT_PORT_FORWARD_EXT_03_TOK          "adv_portfwde_3"
#define ADV_NAT_PORT_FORWARD_EXT_04_TOK          "adv_portfwde_4"
#define ADV_NAT_PORT_FORWARD_EXT_05_TOK          "adv_portfwde_5"
#define ADV_NAT_PORT_FORWARD_EXT_06_TOK          "adv_portfwde_6"
#define ADV_NAT_PORT_FORWARD_EXT_07_TOK          "adv_portfwde_7"
#define ADV_NAT_PORT_FORWARD_EXT_08_TOK          "adv_portfwde_8"
#define ADV_NAT_PORT_FORWARD_EXT_09_TOK          "adv_portfwde_9"
#define ADV_NAT_PORT_FORWARD_EXT_10_TOK          "adv_portfwde_10"
#if NUM_PORT_FORWARD > 10
#define ADV_NAT_PORT_FORWARD_EXT_11_TOK          "adv_portfwde_11"
#define ADV_NAT_PORT_FORWARD_EXT_12_TOK          "adv_portfwde_12"
#define ADV_NAT_PORT_FORWARD_EXT_13_TOK          "adv_portfwde_13"
#define ADV_NAT_PORT_FORWARD_EXT_14_TOK          "adv_portfwde_14"
#define ADV_NAT_PORT_FORWARD_EXT_15_TOK          "adv_portfwde_15"
#define ADV_NAT_PORT_FORWARD_EXT_16_TOK          "adv_portfwde_16"
#define ADV_NAT_PORT_FORWARD_EXT_17_TOK          "adv_portfwde_17"
#define ADV_NAT_PORT_FORWARD_EXT_18_TOK          "adv_portfwde_18"
#define ADV_NAT_PORT_FORWARD_EXT_19_TOK          "adv_portfwde_19"
#define ADV_NAT_PORT_FORWARD_EXT_20_TOK          "adv_portfwde_20"
#if NUM_PORT_FORWARD > 20
#define ADV_NAT_PORT_FORWARD_EXT_21_TOK          "adv_portfwde_21"
#define ADV_NAT_PORT_FORWARD_EXT_22_TOK          "adv_portfwde_22"
#define ADV_NAT_PORT_FORWARD_EXT_23_TOK          "adv_portfwde_23"
#define ADV_NAT_PORT_FORWARD_EXT_24_TOK          "adv_portfwde_24"
#if NUM_PORT_FORWARD > 24
#define ADV_NAT_PORT_FORWARD_EXT_25_TOK          "adv_portfwde_25"
#define ADV_NAT_PORT_FORWARD_EXT_26_TOK          "adv_portfwde_26"
#define ADV_NAT_PORT_FORWARD_EXT_27_TOK          "adv_portfwde_27"
#define ADV_NAT_PORT_FORWARD_EXT_28_TOK          "adv_portfwde_28"
#define ADV_NAT_PORT_FORWARD_EXT_29_TOK          "adv_portfwde_29"
#define ADV_NAT_PORT_FORWARD_EXT_30_TOK          "adv_portfwde_30"
#define ADV_NAT_PORT_FORWARD_EXT_31_TOK          "adv_portfwde_31"
#define ADV_NAT_PORT_FORWARD_EXT_32_TOK          "adv_portfwde_32"
#endif
#endif
#endif
#endif
/* ---------------------   NAT virtual server ---------------------------------------*/
#define NAT_VSERVER_ENABLE_TOK           "natvserver_en"
#define NAT_VSERVER_TOK                  "natvserver_"
#define NAT_VSERVER_01_TOK               "natvserver_1"
#define NAT_VSERVER_02_TOK               "natvserver_2"
#define NAT_VSERVER_03_TOK               "natvserver_3"
#define NAT_VSERVER_04_TOK               "natvserver_4"
#define NAT_VSERVER_05_TOK               "natvserver_5"
#define NAT_VSERVER_06_TOK               "natvserver_6"
#define NAT_VSERVER_07_TOK               "natvserver_7"
#define NAT_VSERVER_08_TOK               "natvserver_8"
#define NAT_VSERVER_09_TOK               "natvserver_9"
#define NAT_VSERVER_10_TOK               "natvserver_10"
#if NUM_NAT_VSERVER > 10
#define NAT_VSERVER_11_TOK               "natvserver_11"
#define NAT_VSERVER_12_TOK               "natvserver_12"
#define NAT_VSERVER_13_TOK               "natvserver_13"
#define NAT_VSERVER_14_TOK               "natvserver_14"
#define NAT_VSERVER_15_TOK               "natvserver_15"
#define NAT_VSERVER_16_TOK               "natvserver_16"
#define NAT_VSERVER_17_TOK               "natvserver_17"
#define NAT_VSERVER_18_TOK               "natvserver_18"
#define NAT_VSERVER_19_TOK               "natvserver_19"
#define NAT_VSERVER_20_TOK               "natvserver_20"
#if NUM_NAT_VSERVER > 20
#define NAT_VSERVER_21_TOK               "natvserver_21"
#define NAT_VSERVER_22_TOK               "natvserver_22"
#define NAT_VSERVER_23_TOK               "natvserver_23"
#define NAT_VSERVER_24_TOK               "natvserver_24"
#if NUM_NAT_VSERVER > 24
#define NAT_VSERVER_25_TOK               "natvserver_25"
#define NAT_VSERVER_26_TOK               "natvserver_26"
#define NAT_VSERVER_27_TOK               "natvserver_27"
#define NAT_VSERVER_28_TOK               "natvserver_28"
#define NAT_VSERVER_29_TOK               "natvserver_29"
#define NAT_VSERVER_30_TOK               "natvserver_30"
#define NAT_VSERVER_31_TOK               "natvserver_31"
#define NAT_VSERVER_32_TOK               "natvserver_32"
#endif
#endif
#endif

/*---------------Support Long NAT_VSERVER_NAME length-------------------*/
#if SUPPORT_LONG_VSERVER_NAME
#define NAT_VSERVER_NAME_TOK                  "natvserver_n_"
#define NAT_VSERVER_NAME_01_TOK               "natvserver_n_1"
#define NAT_VSERVER_NAME_02_TOK               "natvserver_n_2"
#define NAT_VSERVER_NAME_03_TOK               "natvserver_n_3"
#define NAT_VSERVER_NAME_04_TOK               "natvserver_n_4"
#define NAT_VSERVER_NAME_05_TOK               "natvserver_n_5"
#define NAT_VSERVER_NAME_06_TOK               "natvserver_n_6"
#define NAT_VSERVER_NAME_07_TOK               "natvserver_n_7"
#define NAT_VSERVER_NAME_08_TOK               "natvserver_n_8"
#define NAT_VSERVER_NAME_09_TOK               "natvserver_n_9"
#define NAT_VSERVER_NAME_10_TOK               "natvserver_n_10"
#if NUM_NAT_VSERVER > 10
#define NAT_VSERVER_NAME_11_TOK               "natvserver_n_11"
#define NAT_VSERVER_NAME_12_TOK               "natvserver_n_12"
#define NAT_VSERVER_NAME_13_TOK               "natvserver_n_13"
#define NAT_VSERVER_NAME_14_TOK               "natvserver_n_14"
#define NAT_VSERVER_NAME_15_TOK               "natvserver_n_15"
#define NAT_VSERVER_NAME_16_TOK               "natvserver_n_16"
#define NAT_VSERVER_NAME_17_TOK               "natvserver_n_17"
#define NAT_VSERVER_NAME_18_TOK               "natvserver_n_18"
#define NAT_VSERVER_NAME_19_TOK               "natvserver_n_19"
#define NAT_VSERVER_NAME_20_TOK               "natvserver_n_20"
#endif
#if NUM_NAT_VSERVER > 20
#define NAT_VSERVER_NAME_21_TOK               "natvserver_n_21"
#define NAT_VSERVER_NAME_22_TOK               "natvserver_n_22"
#define NAT_VSERVER_NAME_23_TOK               "natvserver_n_23"
#define NAT_VSERVER_NAME_24_TOK               "natvserver_n_24"
#endif
#if NUM_NAT_VSERVER > 24
#define NAT_VSERVER_NAME_25_TOK               "natvserver_n_25"
#define NAT_VSERVER_NAME_26_TOK               "natvserver_n_26"
#define NAT_VSERVER_NAME_27_TOK               "natvserver_n_27"
#define NAT_VSERVER_NAME_28_TOK               "natvserver_n_28"
#define NAT_VSERVER_NAME_29_TOK               "natvserver_n_29"
#define NAT_VSERVER_NAME_30_TOK               "natvserver_n_30"
#define NAT_VSERVER_NAME_31_TOK               "natvserver_n_31"
#define NAT_VSERVER_NAME_32_TOK               "natvserver_n_32"
#endif
#endif
/* ------------------   Trigger Port For Special Apps-----------------------------*/
#define TRIGGER_PORT_ENABLE_TOK          "trigger_port_enable"
#define TRIGGER_PORT_TOK                 "trigger_port_"
#define TRIGGER_PORT_01_TOK              "trigger_port_1"
#define TRIGGER_PORT_02_TOK              "trigger_port_2"
#define TRIGGER_PORT_03_TOK              "trigger_port_3"
#define TRIGGER_PORT_04_TOK              "trigger_port_4"
#define TRIGGER_PORT_05_TOK              "trigger_port_5"
#define TRIGGER_PORT_06_TOK              "trigger_port_6"
#define TRIGGER_PORT_07_TOK              "trigger_port_7"
#define TRIGGER_PORT_08_TOK              "trigger_port_8"
#define TRIGGER_PORT_09_TOK              "trigger_port_9"
#define TRIGGER_PORT_10_TOK              "trigger_port_10"
#if NUM_TRIGGER_PORT > 10
#define TRIGGER_PORT_11_TOK              "trigger_port_11"
#define TRIGGER_PORT_12_TOK              "trigger_port_12"
#define TRIGGER_PORT_13_TOK              "trigger_port_13"
#define TRIGGER_PORT_14_TOK              "trigger_port_14"
#define TRIGGER_PORT_15_TOK              "trigger_port_15"
#define TRIGGER_PORT_16_TOK              "trigger_port_16"
#endif
#if NUM_TRIGGER_PORT > 17
#define TRIGGER_PORT_17_TOK              "trigger_port_17"
#define TRIGGER_PORT_18_TOK              "trigger_port_18"
#define TRIGGER_PORT_19_TOK              "trigger_port_19"
#define TRIGGER_PORT_20_TOK              "trigger_port_20"
#define TRIGGER_PORT_21_TOK              "trigger_port_21"
#define TRIGGER_PORT_22_TOK              "trigger_port_22"
#define TRIGGER_PORT_23_TOK              "trigger_port_23"
#define TRIGGER_PORT_24_TOK              "trigger_port_24"
#define TRIGGER_PORT_25_TOK              "trigger_port_25"
#define TRIGGER_PORT_26_TOK              "trigger_port_26"
#define TRIGGER_PORT_27_TOK              "trigger_port_27"
#define TRIGGER_PORT_28_TOK              "trigger_port_28"
#define TRIGGER_PORT_29_TOK              "trigger_port_29"
#define TRIGGER_PORT_30_TOK              "trigger_port_30"
#define TRIGGER_PORT_31_TOK              "trigger_port_31"
#define TRIGGER_PORT_32_TOK              "trigger_port_32"
#endif
/*---------------------  WMM Features ---------------------------*/
#if 1
#define WLAN_WMM_AP_AIFSN_TOK			 "wmm_ap_aifsn"
#define WLAN_WMM_AP_CWMAX_TOK			 "wmm_ap_cwmax"
#define WLAN_WMM_AP_CWMIN_TOK			 "wmm_ap_cwmin"
#define WLAN_WMM_AP_TXOP_TOK			 "wmm_ap_txop"
#define WLAN_WMM_AP_ACM_TOK			 	 "wmm_ap_acm"
#define WLAN_WMM_STA_AIFSN_TOK			 "wmm_sta_aifsn"
#define WLAN_WMM_STA_CWMAX_TOK			 "wmm_sta_cwmax"
#define WLAN_WMM_STA_CWMIN_TOK			 "wmm_sta_cwmin"
#define WLAN_WMM_STA_TXOP_TOK			 "wmm_sta_txop"
#define WLAN_WMM_STA_ACM_TOK			 "wmm_sta_acm"
#define WLAN_WMM_ACKPOLICY_TOK			 "wmm_ack_policy"
#endif
/*-------------------- USERINFO -----------------------------*/
#define USERINFO_TOK                     "userInfo_"
#define USERINFO_01_TOK                  "userInfo_1"
#define USERINFO_02_TOK                  "userInfo_2"
#define USERINFO_03_TOK                  "userInfo_3"
#define USERINFO_04_TOK                  "userInfo_4"
#define USERINFO_05_TOK                  "userInfo_5"
#define USERINFO_06_TOK                  "userInfo_6"
#define USERINFO_07_TOK                  "userInfo_7"
#define USERINFO_08_TOK                  "userInfo_8"
#define USERINFO_09_TOK                  "userInfo_9"
#define USERINFO_10_TOK                  "userInfo_10"
#define USERINFO_11_TOK                  "userInfo_11"
#define USERINFO_12_TOK                  "userInfo_12"
#define USERINFO_13_TOK                  "userInfo_13"
#define USERINFO_14_TOK                  "userInfo_14"
#define USERINFO_15_TOK                  "userInfo_15"
#define USERINFO_16_TOK                  "userInfo_16"
#define USERINFO_17_TOK                  "userInfo_17"
#define USERINFO_18_TOK                  "userInfo_18"
#define USERINFO_19_TOK                  "userInfo_19"
#define USERINFO_20_TOK                  "userInfo_20"


#define USERCFNUM_TOK                    "usercfwnum_"
#define USERCFNUM_01_TOK                 "usercfwnum_1"
#define USERCFNUM_02_TOK                 "usercfwnum_2"
#define USERCFNUM_03_TOK                 "usercfwnum_3"
#define USERCFNUM_04_TOK                 "usercfwnum_4"
#define USERCFNUM_05_TOK                 "usercfwnum_5"
#define USERCFNUM_06_TOK                 "usercfwnum_6"
#define USERCFNUM_07_TOK                 "usercfwnum_7"
#define USERCFNUM_08_TOK                 "usercfwnum_8"
#define USERCFNUM_09_TOK                 "usercfwnum_9"
#define USERCFNUM_10_TOK                 "usercfwnum_10"
/*-------------------- IPGROUPINFO -----------------------------*/
#define GROUPINFO_TOK                    "groupInfo_"
#define GROUPINFO_01_TOK                 "groupInfo_1"
#define GROUPINFO_02_TOK                 "groupInfo_2"
#define GROUPINFO_03_TOK                 "groupInfo_3"
#define GROUPINFO_04_TOK                 "groupInfo_4"
#define GROUPINFO_05_TOK                 "groupInfo_5"
#define GROUPINFO_06_TOK                 "groupInfo_6"
/*-------------------- Blacklist for each group ------------------*/
#define GROUPBLACKLIST_TOK               "groupBlackList_"
#define GROUPBLACKLIST_01_TOK            "groupBlackList_1"
#define GROUPBLACKLIST_02_TOK            "groupBlackList_2"
#define GROUPBLACKLIST_03_TOK            "groupBlackList_3"
#define GROUPBLACKLIST_04_TOK            "groupBlackList_4"
#define GROUPBLACKLIST_05_TOK            "groupBlackList_5"
#define GROUPBLACKLIST_06_TOK            "groupBlackList_6"
#define GROUPBLACKLIST_TMP_TOK           "groupBlackList_tmp"
/*---------------------- SIP SERVER CONF------------------------------*/
#define SIPSER_PORT_TOK                  "sipser_port"
#define SIPSER_RTP_PORT_START_TOK        "sipser_rtp_sport"
#define SIPSER_RTP_PORT_END_TOK          "sipser_rtp_eport"
#define SIPSER_MAX_EXPIRES_TIME_TOK      "sipser_max_expire_t"
#define SIPSER_DEFAULT_EXPIRES_TIME_TOK  "sipser_def_expire_t"
#define SIPSER_SERV_CALLER_ID_TOK        "sipser_callerid"
/*-----------------------------------------------------------------*/
#define SIP_CDR_SHOWFILENAME             "sipCdrShowFile"
#define SIP_CDR_SHOWPAGENUM              "sipCdrShowPageNum"
#define SIP_CDR_RESERVEDAYS			     "sipCdrReserveDays"
/*---------------------- PBX Service------------------------------*/
#define IP_TOS_DIFFSERV_TOK              "ip_tos_diffserv"
/*---------------------- EXT SIP CONF------------------------------*/
#define OUTBOUNDSIPCONF_TOK              "outboundSipConf_"
#define OUTBOUNDSIPCONF_01_TOK           "outboundSipConf_1"
#define OUTBOUNDSIPCONF_02_TOK           "outboundSipConf_2"
#define OUTBOUNDSIPCONF_03_TOK           "outboundSipConf_3"
#define OUTBOUNDSIPCONF_04_TOK           "outboundSipConf_4"
#define OUTBOUNDSIPCONF_05_TOK           "outboundSipConf_5"
/*---------------------- DIALPLAN CONF------------------------------*/
/*first byte 0:Nonused, 1:Enable, 2:Edit, 3:Disable*/
#define DIALPLANCONF_TOK                 "dialplan_"
#define DIALPLANCONF_01_TOK              "dialplan_1"
#define DIALPLANCONF_02_TOK              "dialplan_2"
#define DIALPLANCONF_03_TOK              "dialplan_3"
#define DIALPLANCONF_04_TOK              "dialplan_4"
#define DIALPLANCONF_05_TOK              "dialplan_5"
#define DIALPLANCONF_06_TOK              "dialplan_6"
#define DIALPLANCONF_07_TOK              "dialplan_7"
#define DIALPLANCONF_08_TOK              "dialplan_8"
#define DIALPLANCONF_09_TOK              "dialplan_9"
#define DIALPLANCONF_10_TOK              "dialplan_10"
/*-------------------SMTP--------------------------------------*/
#define SMTP_ENABLE_TOK                  "smtp_enable"
#define SMTP_HOST_TOK                    "smtp_host"
#define SMTP_PORT_TOK                    "smtp_port"
#define SMTP_AUTH_ENABLE_TOK             "smtp_auth_enable"
#define SMTP_ID_TOK                      "smtp_id"
#define SMTP_PWD_TOK                     "smtp_pwd" 
#define SMTP_SENDER_TOK                  "smtp_sender"
#if HAS_SECOND_SMTP
#define SMTP2_ENABLE_TOK                  "smtp2_enable"
#define SMTP2_HOST_TOK                    "smtp2_host"
#define SMTP2_PORT_TOK                    "smtp2_port"
#define SMTP2_AUTH_ENABLE_TOK             "smtp2_auth_enable"
#define SMTP2_ID_TOK                      "smtp2_id"
#define SMTP2_PWD_TOK                     "smtp2_pwd" 
#define SMTP2_SENDER_TOK                  "smtp2_sender"
#endif
/*-------------------DDNS--------------------------------------*/
#define DDNS_ENABLE_TOK                  "ddns_enable"
#define DDNS_TYPE_TOK                    "ddns_type"
#define DDNS_USER_TOK                    "ddns_user"
#define DDNS_EMAIL_TOK                   "ddns_email"
#define DDNS_UPDATE_TIME_TOK             "ddns_update_time"
#define DDNS_PASS_TOK                    "ddns_pass"
#define DDNS_HOSTNAME_TOK                "ddns_host"
#if FOR_ZYXEL
#define DDNS_EX_TYPE_TOK                 "ddns_ex_type"
#define DDNS_REGFISH_TOKEN_TOK           "ddns_regfish_token"
#define DDNS_WILDCARD_TOK                "ddns_wildcard"
#define DDNS_OFF_LINE_TOK                "ddns_off_line"
#define DDNS_IP_POLICY_TOK               "ddns_ip_policy"
#define DDNS_SPECIFIED_IP_TOK            "ddns_specified_ip"
#endif
#if SUPPORT_IODATA_GENERATE_DDNS
#define DDNS_AUTO_GENERATE_TOK           "ddns_autogen"
#define DDNS_PRESET_TOK                  "ddns_preset"
#define DDNS_AG_USER_TOK                 "ddns_ag_user"
#define DDNS_AG_PW_TOK                   "ddns_ag_pw"
#define DDNS_AG_HOSTNAME_TOK             "ddns_ag_hostname"
#endif
/*-------------------------------------------------------------*/
#define SYS_EASYSETUP_TOK                "sys_easysetup"
#if HAS_WIZARD_CFLAG || HAS_REPEATER_EASYSETUP
#define SYS_WIZARD_CFLAG_TOK         "sys_wizard_cflag"
#endif
#if HAS_REPEATER_EASYSETUP
#define SYS_KEEP_LANTYPE_TOK         "sys_lantype_flag"
#endif
#if HAS_WIZARD_CFLAG
#define SYS_WIZARD_REG_FNAME_TOK         "sys_reg_fname"
#define SYS_WIZARD_REG_LNAME_TOK         "sys_reg_lname"
#define SYS_WIZARD_REG_EMAIL_TOK          "sys_reg_email"
#define SYS_WIZARD_REG_ZIPCODE_TOK         "sys_reg_zipcode"
#define SYS_WIZARD_REG_COUNTRY_TOK         "sys_reg_country"
#endif
#define SYS_OP_MODE_TOK                  "sys_opmode"
#if FOR_ZYXEL
#define WEB_SYS_OP_MODE_TOK              "web_sys_opmode"
#define WEB_LAN_IPADDR_TOK               "web_lan_ipaddr"
#define WEB_LAN_IPADDR_AP_TOK			 "web_lan_ipaddr_ap"
#endif
#define SYS_ROUTE_ENABLE_TOK             "sys_route_enable"
//#if defined (HAS_POWER_SAVING_WLAN) || defined (HAS_POWER_SAVING_ETH)
#define SYS_POWERSAVING_MODE_TOK         "sys_pwrsave"
//#endif
#define SYS_VERSION_ENABLE_TOK           "sys_ver_enable"
#define SYS_VERSION_NEW_TOK	             "sys_ver_new"
#define SYS_VERSION_NOTIFIED_TOK         "sys_ver_notifid"
#if HAS_AUTO_BRIDGE_MODE
/* AUTO BRIDGE Mode enable */
#define SYS_AUTO_BRIDGE_MODE_TOK         "sys_auto_bridge_m"
#if WEB_HAS_AUTO_BRIDGE_SELECT
#define WEB_AUTO_BRIDGE_MODE_TOK         "web_auto_bridge_m"
#endif
/* op mode is AUTO BRIDGE ? */
#define SYS_AUTO_BRIDGE_OP_TOK           "sys_auto_bridge_op"
#endif
#if HAS_AUTO_IP_CHANGE
#define SYS_AUTO_IP_CHANGE_ENABLE_TOK	 "sys_auto_ipchange_e"
#define SYS_AUTO_IP_CHANGE_TRIGGER_TOK	 "sys_auto_ipchange_t"
#endif
#if HAS_RADIO_SETTING
#define SYSTEM_VLAN_ENABLE_TOK           WLAN1_ _VLAN_ENABLE_TOK
#else
#define SYSTEM_VLAN_ENABLE_TOK           "sys_vlan_enable"
#endif
#if HAS_LED_CONTROL
#define SYS_LED_PWR_CONTROL_TOK         "sys_led_pwr"
#define SYS_LED_LAN_CONTROL_TOK          "sys_led_lan"
#define SYS_LED_WLAN_CONTROL_TOK         "sys_led_wlan"
#endif
/*-------------------- temporary token -----------------------------*/
#define TEMP_TOK                         "temp_"
#define TEMP_01_TOK                      "temp_1"
#define TEMP_02_TOK                      "temp_2"
#define TEMP_03_TOK                      "temp_3"
#define TEMP_04_TOK                      "temp_4"
/*-----------------------------------------------------------------*/
#define SYSTEM_INFO_TOK                  "systeminfo"
#define SYSTEM_INFO_DDNS_TOK             "sysinfoddns"

#define SYSTEM_INFO_FXSAGENT_TOK         "sysinfoFxsAgent"
#define SYSTEM_INFO_FXO_RELAY_TOK        "sysinfoFxoRelay"
#define SYSTEM_INFO_VP_TOK		         "sysinfoVpAgent"
#define SYSTEM_INFO_VP1_TOK		 "sysinfoVpAgent_1"
#define SYSTEM_INFO_VP2_TOK		         "sysinfoVpAgent_2"
#define SYSTEM_INFO_VP3_TOK		         "sysinfoVpAgent_3"

#define TEMPFORCGI_TIME_TOK              "tempcgi_t"
#define TEMPFORCGI_FLAG_TOK              "tempcgi_flag"
/*-------------------- Astersik ------------------------------------*/
#define AST_MAX_CALLS_TOK                "ast_maxcalls"
/*----------------------Telent--------------------------------------*/
#if HAS_TELNET_CLI
#define TELNETD_ACCESS_TOK               "telnetd_access"
#define TELNETD_REMOTE_PORT_TOK			 "telnetd_remote_port"
#define TELNETD_REMOTE_IPADDR_TOK		 "telnetd_remote_ip"
#endif
#if HAS_SSHD
#define SSHD_ACCESS_TOK                  "sshd_access"
#endif
#if HAS_FTPD
#define FTPD_ENABLE_TOK                  "ftpd_enable"
#define FTPD_ACCESS_TOK                  "ftpd_access"
#define FTPD_REMOTE_PORT_TOK             "ftpd_remote_port"
#define FTPD_REMOTE_IPADDR_TOK           "ftpd_remote_ip"
#define FTPD_CONNECT_TIMEOUT_TOK         "ftpd_conn_timeout"
#define FTPD_IDLE_TIMEOUT_TOK            "ftpd_idle_timeout"
#define FTPD_MAX_CLIENTS_TOK             "ftpd_max_clients"
#define FTPD_SHARE_MODE_TOK              "ftpd_share_mode"  //0:read only, 1:read/write
#define FTPD_ANONY_ENABLE_TOK            "ftpd_anony_enable"
#define FTPD_LOGIN_USERNAME_TOK          "fptd_login_username"
#define FTPD_LOGIN_PASSWORD_TOK          "fptd_login_password"
#endif
#if HAS_DAAPD
#define DAAPD_ENABLE_TOK                "daapd_enable"
#define DAAPD_SERVERNAME_TOK            "daapd_servername"
#define DAAPD_FOLDERNAME_TOK            "daapd_foldername"
#define DAAPD_PASSWORD_TOK              "daapd_password"
#endif
#if HAS_WEB_SUPPORT_HTTPS
/*Https Remotte*/
#define HTTPSD_ACCESS_TOK				 "httpsd_access"
#define HTTPSD_REMOTE_PORT_TOK			 "httpsd_remote_port"
#define HTTPSD_REMOTE_IPADDR_TOK		 "httpsd_remote_ip"
#endif
#if HAS_SNMP_TRAP_SUPPORT
/*SNMP Remotte*/
#define SNMPD_ACCESS_TOK				 "snmpd_access"
#define SNMPD_REMOTE_PORT_TOK			 "snmpd_remote_port"
#define SNMPD_REMOTE_IPADDR_TOK		 	 "snmpd_remote_ip"
#endif
/*----------------------HTTP--------------------------------------*/
#if HAS_MULTI_CLONE_MAC_MODE
#define CLONE_MAC_MODE_TOK				"clone_mac_mode"
#define CLONE_PC_IP_TOK					"clone_pc_ip"
#endif
/*Regional and Language Options*/
#define HTTP_FIRST_LOGIN_TOK			"http_first_login"
#define HTTP_LANGUAGE_TOK				"http_language"
#define HTTP_REGION_TOK					"http_region"
#define HTTP_REFRESH_TOK				"http_refresh"
#define HTTP_PACKET_REFRESH_TOK			"http_packet_refresh"
#define HTTP_FIRST_WIZARD_TOK			"http_first_wizard"
#define HTTP_LANGUAGE_STR_TOK			"http_language_str"

/*Http Remotte*/
#define HTTP_LOGIN_USERNAME_TOK		     "http_login_name"
#define HTTP_REMOTE_PW_TOK			     "http_remote_pw"
#define	HTTP_REMOTE_IDLETIME_TOK   	     "http_remote_it"
#define HTTP_REMOTE_ENABLE_TOK 		     "http_remote_en"
#define HTTP_REMOTE_IPADDR_TOK    	     "http_remote_ip"
#define HTTP_FAKE_REMOTE_IPADDR_TOK		 "http_fake_remote_ip"
#define HTTP_REMOTE_PORT_TOK             "http_remote_port"
#define HTTPD_ACCESS_TOK                     "httpd_access"
#if 0 // USE HTTP_REMOTE_ENABLE_TOK replace
#define HTTP_ACCESS_FROM_WAN_TOK         "http_acc_from_wan"
#endif
#define HTTP_ACCESS_FROM_LAN_TOK         "http_acc_from_lan"
#if HAS_DENY_ADMIN_ACCESS
#define HTTP_DENY_ADMIN_ACCESS_TOK         "http_admin_access"
#endif
#define HTTP_SYSTEM_NAME_TOK		 "http_system_name"
/*Firmware upgrade*/
#define SYSTEM_INFO_FWUPG_TOK 		     "sysinfofwupg"
#define SYSTEM_FWUPG_NUM_TOK		     "sysfwupgnum"
#if SUPPORT_AUTO_CHECK_FIRMWARE
#define SYSTEM_AUTO_CHECK_FW_TOK	     "sysautofw"
#endif
/*Configurw Tools*/
#define SYSTEM_INFO_CT_TOK      	 "sysinfo_config_tool"
#define SYSTEM_RESTORE_NUM_TOK           "sys_restore_num"
/*-------------------log--------------------------*/
#define SYSTEM_LOG_ENABLE_TOK            "log_enable"
#define SYSTEM_LOG_LEVEL_TOK             "log_level"
#define SYSTEM_LOG_IP_TOK                "log_ip_addr"
#define SYSTEM_LOG_EMAIL_ENABLE_TOK      "log_email_enable"
#define SYSTEM_LOG_EMAILADDR_TOK         "log_email_address"
#define SYSTEM_LOG_EVENT_ALL_TOK		 "log_event_all"
#define SYSTEM_LOG_EVENT_SYS_TOK         "log_event_system" 
#define SYSTEM_LOG_EVENT_SNMP_TOK        "log_event_snmp"
#define SYSTEM_LOG_EVENT_DOS_TOK         "log_event_dos"
#define SYSTEM_LOG_EVENT_WLAN_TOK		 "log_event_wlan"
#define SYSTEM_LOG_EVENT_DHCPC_TOK       "log_event_dhcpc"
#define SYSTEM_LOG_EVENT_DEBUG_TOK       "log_event_debug"
#define SYSTEM_LOG_EVENT_ATTACK_TOK      "log_event_attack"
#define SYSTEM_LOG_EVENT_DROP_TOK        "log_event_drop"
#define SYSTEM_LOG_EVENT_NOTICE_TOK      "log_event_notice"
#define SYSTEM_LOG_EVENT_VOIP_TOK        "log_event_voip"
#define SYSTEM_LOG_EVENT_ACL_TOK         "log_event_acl"
#define SYSTEM_LOG_EMAIL_SUBJECT_TOK     "log_email_subject"
#define SYSTEM_LOG_EMAIL_LOG_TO_TOK      "log_email_log_to"
#define SYSTEM_LOG_EMAIL_ALERT_TO_TOK    "log_email_alert_to"
#define SYSTEM_LOG_TO_NETWORK_TOK        "log_to_network"
#define SYSTEM_LOG_SCH_ENABLE_TOK        "log_sch_enable"
#define SYSTEM_LOG_SCH_TIME_TOK          "log_sch_time"
#define SYSTEM_LOG_SCHEDULE_ID_TOK       "log_schedule_id"
#define SYSTEM_LOG_EMAIL_ONFULL_TOK      "log_email_onfull"
#define SYSTEM_LOG_FILTER_TOK			 "log_filter"
#define REGULAR_DOMAIN_TOK               "reg_domain"
#if HAS_ALERT_MAIL
#define SYSTEM_LOG_ALERT_EMAIL_ENABLE_TOK "log_amail_en"
#define SYSTEM_LOG_ALERT_EMAILADDR_TOK    "log_amail_addr"
#define SYSTEM_LOG_ALERT_TYPE_TOK		  "log_amail_type"
#define SYSTEM_LOG_ALERT_EMAIL_SUBJECT_TOK "log_amail_subject"
#endif
#if HAS_PARENTAL_CONTROL
#define SYSTEM_LOG_EVENT_PARENTAL_CONTROL_TOK "log_event_pc"
#endif
/*-------------------System--------------------------*/
#define SYS_SN_TOK                       "sys_sn"
#if HAS_RADIO_SETTING
#define ETH_PURPOSE_TOK					 "eth_purpose"
#define RADIO_SELECTED_TOK				 "sys_sel_radio"
#define REPEATER_TYPE_TOK				 "repeater_type"
#endif
#if HAS_IGMPPROXY
#define IGMP_PROXY_ENABLE_TOK            "igmp_proxy_enable"
#endif
#define WLAN_IGMPSNOOPING_EN_TOK		 "wlan_igmpsn_en"

#if USE_EVR100
#define APPS_MAJOR_VERSION_TOK			"apps_major_version"
#define APPS_MINOR_VERSION_TOK			"apps_minor_version"
#define APPS_RELEASE_VERSION_TOK    	"apps_release_version"
#define APPS_BUILD_VERSION_TOK			"apps_build_version"
#endif
/*-------------------NetBIOS--------------------------*/
#if HAS_NETBIOS_FUNCTION
#define NETBIOS_WANLAN_COMM_TOK			"netbios_wanlan_comm"
#define NETBIOS_TRIGGERDIAL_TOK			"netbios_triggerdial"
#define NETBIOS_ANNOUNCE_ENABLE_TOK		"netbios_ann_enable"
#define NETBIOS_LEARN_FROM_WAN_TOK		"netbios_learn_wan"
#define NETBIOS_SCOPE_TOK				"netbios_scope"
#define NETBIOS_NODE_TYPE_TOK			"netbios_nodetype"
#define NETBIOS_WINS_IP_1_TOK			"netbios_wins_ip1"
#define NETBIOS_WINS_IP_2_TOK			"netbios_wins_ip2"
#define NETBIOS_LEARN_FROM_WAN_ENABLE_TOK  "nb_fromwan_en"
#define NETBIOS_FROM_WAN_SCOPE_TOK         "nb_fromwan_scope"
#define NETBIOS_FROM_WAN_NODE_TYPE_TOK     "nb_fromwan_ntype"
#define NETBIOS_FROM_WAN_WINS_IP_1_TOK     "nb_fromwan_wins_ip1"
#define NETBIOS_FROM_WAN_WINS_IP_2_TOK     "nb_fromwan_wins_ip2"
#endif

#define NAT_SESSION_RESERV_ENABLE_TOK	"nat_sess_reserv"
#define PACKET_HANDLER_ENABLE_TOK		"pkt_handler_enable"

#define TR_ACS_URL_TOK                  "tr_acs_url"
#define TR_ACS_USER_TOK                 "tr_acs_user"
#define TR_ACS_PW_TOK                   "tr_acs_pw"
#define TR_INFORM_PERIODIC_ENABLE_TOK	"tr_period_enable"
#define TR_INFORM_PERIODIC_TOK          "tr_period_interval"
#define TR_INFORM_PERIODIC_TIME_TOK	    "tr_period_time"
#define TR_CONN_REQ_USER_TOK            "tr_conn_req_user"
#define TR_CONN_REQ_PW_TOK              "tr_conn_req_pw"
#define TR_OUI_TOK                      "tr_oui"
#define TR_PRODUCT_CLASS_TOK            "tr_product_class"
#define TR_STUN_UDP_CONN_ADDR_TOK       "tr_stun_udp_addr"
#define TR_STUN_UDP_CONN_LIMIT_TOK      "tr_stun_udp_limit"
#define TR_STUN_ENABLE_TOK              "tr_stun_enable"
#define TR_STUN_SERVER_TOK              "tr_stun_server"
#define TR_STUN_SERVER_PORT_TOK         "tr_stun_serv_port"
#define TR_STUN_USER_TOK                "tr_stun_user"
#define TR_STUN_PW_TOK                  "tr_stun_pw"
#define TR_STUN_MAX_KEEP_PERIOD_TOK     "tr_stun_max_keep"
#define TR_STUN_MIN_KEEP_PERIOD_TOK     "tr_stun_min_keep"
#define TR_STUN_NAT_DETECTED_TOK        "tr_stun_nat_det"
#define TR_DEV_PROVISIONING_CODE_TOK    "tr_dev_prov_code"

/*-------------------Hardware NAT--------------------------*/
#if HAS_HW_NAT || HAS_TURBO_NAT
#define HWNAT_ENABLE_TOK                "hwnat_enable"
#endif
#if HAS_TURBO_NAT
#define TURBO_NAT_ENABLE_TOK            "turbonat_enable"
#endif


#if HAS_DHCP_CLIENT_IN_STATION_MODE
#define DHCPC_IN_STA                    "dhcpc_in_sta"
#endif

/*--------------- Wireless Guest Network -------------------------------------------*/
#if WLAN_GUEST_NETWORK
#define WLAN_GN_ENABLE_TOK          "wlan_gn_en"
#define WLAN_GN_LAN_IPADDR_TOK		"wlan_gn_lan_ip"
#define WLAN_GN_LAN_MASK_TOK		"wlan_gn_lan_mask"
#define WLAN_GN_DHCPD_START_TOK		"wlan_gn_dhcp_s"
#define WLAN_GN_DHCPD_END_TOK		"wlan_gn_dhcp_e"
#define WLAN_GN_DEV_TOK				"wlan_gn_dev"
#define WLAN_GN_MODE_WEB_TOK		"wlan_gn_mode"
#define WLAN_GN_CAFE_PSK_TOK		"wlan_gn_cafepsk"
#endif

#if HAS_WEATHER_SUPPORT
#define WEATHER_LOCATION_TOK		"weather_location"
#define WEATHER_UNIT_TOK			"weather_unit"
#endif

/* ------------------   VPN   -----------------------*/
#if HAS_VPN
#define VPN_CONN_TOK                    "vpn_conn_"
#define VPN_CONN_01_TOK                    "vpn_conn_1"
#define VPN_CONN_02_TOK                    "vpn_conn_2"
#define VPN_CONN_03_TOK                    "vpn_conn_3"
#define VPN_CONN_04_TOK                    "vpn_conn_4"
#define VPN_CONN_05_TOK                    "vpn_conn_5"
#if VPN_MAX_NUM > 5
#define VPN_CONN_06_TOK                    "vpn_conn_6"
#define VPN_CONN_07_TOK                    "vpn_conn_7"
#define VPN_CONN_08_TOK                    "vpn_conn_8"
#define VPN_CONN_09_TOK                    "vpn_conn_9"
#define VPN_CONN_10_TOK                    "vpn_conn_10"
#endif
#endif
/* ------------------   IPSec   -----------------------*/
#if HAS_VPN_IPSEC
#define IPSE_GLOBAL_TOK                 "ipsec_global_"
#define IPSEC_CONN_BAS_TOK              "ipsec_conn_bas_"
#define IPSEC_CONN_ADV_TOK              "ipsec_conn_adv_"
#define IPSEC_NAME_TOK                  "ipsec_name_"
#define IPSEC_PSK_TOK                   "ipsec_psk_"
#define IPSEC_LOCALID_TOK               "ipsec_localid_"
#define IPSEC_PEERID_TOK                "ipsec_peerid_"
#define IPSEC_GATEWAY_TOK               "ipsec_gateway_"   /* [20101130 Andy Yu]: Add for supporting Domain Name */
#define IPSEC_GLOBAL_01_TOK           "ipsec_global_1"
#define IPSEC_GLOBAL_02_TOK           "ipsec_global_2"
#define IPSEC_CONN_BAS_01_TOK           "ipsec_conn_bas_1"
#define IPSEC_CONN_BAS_02_TOK           "ipsec_conn_bas_2"
#define IPSEC_CONN_ADV_01_TOK           "ipsec_conn_adv_1"
#define IPSEC_CONN_ADV_02_TOK           "ipsec_conn_adv_2"
#define IPSEC_NAME_01_TOK               "ipsec_name_1"
#define IPSEC_NAME_02_TOK               "ipsec_name_2"
#define IPSEC_PSK_01_TOK                "ipsec_psk_1"
#define IPSEC_PSK_02_TOK                "ipsec_psk_2"
#define IPSEC_LOCALID_01_TOK            "ipsec_localid_1"
#define IPSEC_LOCALID_02_TOK            "ipsec_localid_2"
#define IPSEC_PEERID_01_TOK             "ipsec_peerid_1"
#define IPSEC_PEERID_02_TOK             "ipsec_peerid_2"
#define IPSEC_GATEWAY_01_TOK            "ipsec_gateway_1" /* [20101130 Andy Yu]: Add for supporting Domain Name */
#define IPSEC_GATEWAY_02_TOK            "ipsec_gateway_2"
#if NUM_IPSEC_CONNECTION > 2
#define IPSEC_GLOBAL_03_TOK           "ipsec_global_3"
#define IPSEC_GLOBAL_04_TOK           "ipsec_global_4"
#define IPSEC_GLOBAL_05_TOK           "ipsec_global_5"
#define IPSEC_CONN_BAS_03_TOK           "ipsec_conn_bas_3"
#define IPSEC_CONN_BAS_04_TOK           "ipsec_conn_bas_4"
#define IPSEC_CONN_BAS_05_TOK           "ipsec_conn_bas_5"
#define IPSEC_CONN_ADV_03_TOK           "ipsec_conn_adv_3"
#define IPSEC_CONN_ADV_04_TOK           "ipsec_conn_adv_4"
#define IPSEC_CONN_ADV_05_TOK           "ipsec_conn_adv_5"
#define IPSEC_NAME_03_TOK               "ipsec_name_3"
#define IPSEC_NAME_04_TOK               "ipsec_name_4"
#define IPSEC_NAME_05_TOK               "ipsec_name_5"
#define IPSEC_PSK_03_TOK                "ipsec_psk_3"
#define IPSEC_PSK_04_TOK                "ipsec_psk_4"
#define IPSEC_PSK_05_TOK                "ipsec_psk_5"
#define IPSEC_LOCALID_03_TOK            "ipsec_localid_3"
#define IPSEC_LOCALID_04_TOK            "ipsec_localid_4"
#define IPSEC_LOCALID_05_TOK            "ipsec_localid_5"
#define IPSEC_PEERID_03_TOK             "ipsec_peerid_3"
#define IPSEC_PEERID_04_TOK             "ipsec_peerid_4"
#define IPSEC_PEERID_05_TOK             "ipsec_peerid_5"
#define IPSEC_GATEWAY_03_TOK            "ipsec_gateway_3" /* [20101130 Andy Yu]: Add for supporting Domain Name */
#define IPSEC_GATEWAY_04_TOK            "ipsec_gateway_4"
#define IPSEC_GATEWAY_05_TOK            "ipsec_gateway_5"
#endif
#endif //HAS_VPN_IPSEC
/*---------------- VPN-_L2TP --------------------*/
/*to do HAS_VPN_L2TP*/
#if HAS_VPN_L2TP
#define VPN_L2TP_TOK                    "vpn_l2tp_"
#define VPN_L2TP_01_TOK                    "vpn_l2tp_1"
#define VPN_L2TP_02_TOK                    "vpn_l2tp_2"
#define VPN_L2TP_03_TOK                    "vpn_l2tp_3"
#define VPN_L2TP_04_TOK                    "vpn_l2tp_4"
#define VPN_L2TP_05_TOK                    "vpn_l2tp_5"
#if NUM_VPN_L2TP > 5
#define VPN_L2TP_06_TOK                    "vpn_l2tp_6"
#define VPN_L2TP_07_TOK                    "vpn_l2tp_7"
#define VPN_L2TP_08_TOK                    "vpn_l2tp_8"
#define VPN_L2TP_09_TOK                    "vpn_l2tp_9"
#define VPN_L2TP_10_TOK                    "vpn_l2tp_10"
#endif
#endif
/* [20101222 Andy Yu] */
/* ------------------   PPTP   -----------------------*/
#if HAS_VPN_PPTP
#define VPN_PPTP_TOK                    "vpn_pptp_"
#define VPN_PPTP_01_TOK                    "vpn_pptp_1"
#define VPN_PPTP_02_TOK                    "vpn_pptp_2"
#define VPN_PPTP_03_TOK                    "vpn_pptp_3"
#define VPN_PPTP_04_TOK                    "vpn_pptp_4"
#define VPN_PPTP_05_TOK                    "vpn_pptp_5"
#endif //HAS_VPN_PPTP
#if HAS_VPN_L2TP || HAS_VPN_PPTP
#define VPN_USER_TOK				  "vpn_user_"
#define VPN_USER_01_TOK					"vpn_user_1"
#define VPN_USER_02_TOK                 "vpn_user_2"
#define VPN_USER_03_TOK               	"vpn_user_3"
#define VPN_USER_04_TOK               	"vpn_user_4"
#define VPN_USER_05_TOK               	"vpn_user_5"
#endif

#if HAS_BAD_SITE_FILTER
#define BSFLT_ENABLE_TOK                "bsflt_enable"
#define BSFLT_LICENSE_TOK               "bsflt_license"
#define BSFLT_ALLLIMIT_TOK              "bsflt_alllimit"
#define BSFLT_STATUS_TOK                "bsflt_status"
#define BSFLT_ENDDAY_TOK                "bsflt_endday"
#define BSFLT_USER_TOK                  "bsflt_usr_"
#define BSFLT_USER_01_TOK               "bsflt_usr_1"
#define BSFLT_USER_02_TOK               "bsflt_usr_2"
#define BSFLT_USER_03_TOK               "bsflt_usr_3"
#define BSFLT_USER_04_TOK               "bsflt_usr_4"
#define BSFLT_USER_05_TOK               "bsflt_usr_5"
#define BSFLT_USER_06_TOK               "bsflt_usr_6"
#define BSFLT_USER_07_TOK               "bsflt_usr_7"
#define BSFLT_USER_08_TOK               "bsflt_usr_8"
#define BSFLT_USER_09_TOK               "bsflt_usr_9"
#define BSFLT_USER_10_TOK               "bsflt_usr_10"

#define BSFLT_GROUP_TOK                  "bsflt_grp_"
#define BSFLT_GROUP_01_TOK               "bsflt_grp_1"
#define BSFLT_GROUP_02_TOK               "bsflt_grp_2"
#define BSFLT_GROUP_03_TOK               "bsflt_grp_3"
#define BSFLT_GROUP_04_TOK               "bsflt_grp_4"
#define BSFLT_GROUP_05_TOK               "bsflt_grp_5"
#define BSFLT_GROUP_06_TOK               "bsflt_grp_6"
#define BSFLT_GROUP_07_TOK               "bsflt_grp_7"
#define BSFLT_GROUP_08_TOK               "bsflt_grp_8"
#define BSFLT_GROUP_09_TOK               "bsflt_grp_9"
#define BSFLT_GROUP_10_TOK               "bsflt_grp_10"
#endif

#if HAS_AIRPORT_QUICK_COPY
#define AIRPORT_QUICKCOPY_STAT_TOK       "airport_qc_en"
#endif
#if HAS_AIRPORT_QUICK_COPY_HG
#define AIRPORT_QUICKCOPY_HG_STAT_TOK    "airport_qchg_en"
#endif

#if HAS_BATTERY_HOLTEK
#define BATTERY_LEVEL_TOK                "bat_level"
#define BATTERY_DCSUPPLY_TOK             "bat_dcsupply"
#define BATTERY_CHARGING_TOK             "bat_charging"
#define BATTERY_QUICK_POLL_TOK           "bat_quick_poll"
#endif

#define USB_STATIC_HOST_CHANNEL_TOK     "usb_shost_chan"
#define USB_DYNAMIC_HOST_CHANNEL_TOK     "usb_dhost_chan"
#define WOL_ENABLE_TOK    		"wol_enable"
#define WOL_SERVER_PORT_TOK		"wol_server_port"

#define ECO_TYPE_TOK			"eco_type"
#define ECO_STATUS_TOK			"eco_status"
#define ECO_SCHEDULE_ENABLE_TOK "eco_schedule_en"

#if HAS_INIC
#define ECO_INIC_WLAN_OFF_TOK       "eco_inic_wlan_off"
#define ECO_INIC_LED_OFF_TOK        "eco_inic_led_off"
#if ECO_WITH_WLAN_LOW_RATE
#define ECO_INIC_WLAN_LOW_RATE_TOK  "eco_inic_wlan_lr"
#endif
#endif

#define WEB_ECO_DISABLE_WIRELESS_TIME "web_eco_disable"
#define WEB_WAN1_CONNECTION_TYPE_TOK  "web_wan_type"

#define WLAN_OVERLAPPING_SCAN_TOK	"wlan_bw40_scan"

#if HAS_CAPTCHA_AUTHENTICATION
#define CAPTCHA_ENABLE_TOK			"captcha_en"
#endif

#if HAS_WAN_PORT_SPEED_SETTING
#define WAN_PORT_SPEED_TOK			"wanport_speed"
#endif

#if FW_NOTIFY_FOR_IODATA
#define SYS_VERSION_HAS_NEW_TOK                 "sys_ver_has_new"
#define SYS_VERSION_FIRST_CHECK_TIME_TOK        "sys_ver_first_check"
#define SYS_VERSION_NEXT_CHECK_TIME_TOK         "sys_ver_next_check"
#define SYS_VERSION_FILE_NAME_TOK               "sys_ver_file_name"
#endif

#if HAS_IPV6_PATHTHROUGH_WIZARD_CONTROL
#define WAN_IPV6_PASS_DYNAMIC_ENABLE_TOK    "wan_dynamic_pass_en"
#define WAN_IPV6_PASS_STATIC_ENABLE_TOK     "wan_static_pass_en"
#define WAN_IPV6_PASS_PPPOE_ENABLE_TOK      "wan_pppoe_pass_en"
#endif
#if HAS_PING_MONITOR
#define PING_MON_DEST_ADDR_TOK          "pm_dest_addr"
#define PING_MON_SECOND_ADDR_TOK        "pm_second_addr"
#define PING_MON_PERI_PING_TIME_TOK     "pm_peri_ping_time"
#define PING_MON_PERI_ACCE_TIME_TOK     "pm_peri_acce_time"
#define PING_MON_FAIL_COUNT_TOK         "pm_fail_count"
#define PING_MON_PERI_REBOOT_TIME_TOK   "pm_reboot_time"
#endif

#if RT3052_SUPPORT_RTL8366RB && HAS_ETH_PORT_SPEEDSETTING
#define ETH_PORT_SPEED_TOK			"ethport_speed"
#endif

#if SUPPORT_SX_USB_MODE
#define SX_USB_MODE_TOK                 "sx_usb_mode"
#endif
#if HAS_SXNASPLUS_FUNC
#define SXNAS_COMPUTER_NAME_TOK         "sxnas_pc_name"
#define SXNAS_WORKGROUP_NAME_TOK        "sxnas_group_name"
#define SXNAS_USERNAME_TOK              "sxnas_username"
#define SXNAS_PASSWORD_TOK              "sxnas_pw"
#define SXNAS_USB_FEATURE_TOK           "sxnas_usb_feature"
#endif

#if HAS_MINIDLNA
#define DLNA_ENABLE_TOK     "dlna_enable"
#define DLNA_FOLDER_TOK     "dlna_folder"
#endif

#if HAS_SC_UTMPROXY_FUNCTION
#define SC_UTMPROXY_ENABLE_TOK			"sc_utm_en"
#define SC_UTMPROXY_VER_TOK				"sc_utm_ver"
#define SC_UTMPROXY_ACT_TOK				"sc_utm_act"
#define SC_UTMPROXY_SEC_KEY_TOK			"sc_utm_sec_key"
#define SC_UTMPROXY_KEY_EXP_DATE_TOK	"sc_utm_keyExp"
#define SC_UTMPROXY_KEY_FEATURE_TOK		"sc_utm_keyFea"
#define SC_UTMPROXY_FEATURE_TOK			"sc_utm_Fea"
#endif

/* ---------------------------    advance IPv6     -------------------------------*/
#if SUPPORT_IPV6

#define _L_IP_TOK             "_l_ip"
#define _L_DHCP_PD_TOK        "_l_dhcppd"
#define _AC_ENABLE_TOK        "_ac_en"
#define _AC_TYPE_TOK          "_ac_type"
#define _AC_DHCP_PD_TOK       "_ac_dhcppd"
#define _AC_IP_RANGE_S_TOK    "_ac_ip_s"
#define _AC_IP_RANGE_E_TOK    "_ac_ip_e"
#define _AC_LIFETIME_1_TOK    "_ac_lt1"
#define _AC_LIFETIME_2_TOK    "_ac_lt2"

#define IPV6_CONNECT_TYPE_TOK       "ipv6_conn_type"
/* static IPv6 */
#define IPV6_STATIC_                "ipv6_s"
#define IPV6_S_W_USE_LINKLOCAL_TOK  "ipv6_s_w_usell"
#define IPV6_S_W_IP_TOK             "ipv6_s_w_ip"
#define IPV6_S_W_PREFIX_LEN_TOK     "ipv6_s_w_len"
#define IPV6_S_W_DEF_GW_TOK         "ipv6_s_w_defgw"
#define IPV6_S_W_DNS1_TOK           "ipv6_s_w_dns1"
#define IPV6_S_W_DNS2_TOK           "ipv6_s_w_dns2"
#define IPV6_S_L_IP_TOK             IPV6_STATIC_ _L_IP_TOK          
#define IPV6_S_AC_ENABLE_TOK        IPV6_STATIC_ _AC_ENABLE_TOK     
#define IPV6_S_AC_TYPE_TOK          IPV6_STATIC_ _AC_TYPE_TOK       
#define IPV6_S_AC_IP_RANGE_S_TOK    IPV6_STATIC_ _AC_IP_RANGE_S_TOK 
#define IPV6_S_AC_IP_RANGE_E_TOK    IPV6_STATIC_ _AC_IP_RANGE_E_TOK 
#define IPV6_S_AC_LIFETIME_2_TOK    IPV6_STATIC_ _AC_LIFETIME_2_TOK /* LAN DHCP Life Time */  
#define IPV6_S_AC_LIFETIME_1_TOK    IPV6_STATIC_ _AC_LIFETIME_1_TOK /* LAN Router Advertisment Life Time */
/* DHCPv6 */
#define IPV6_DHCP_                  "ipv6_d"
#define IPV6_D_W_DNS_TYPE_TOK       "ipv6_d_w_dns_t"
#define IPV6_D_W_DNS1_TOK           "ipv6_d_w_dns1"
#define IPV6_D_W_DNS2_TOK           "ipv6_d_w_dns2"
#define IPV6_D_L_IP_TOK             IPV6_DHCP_ _L_IP_TOK          
#define IPV6_D_L_DHCP_PD_TOK        IPV6_DHCP_ _L_DHCP_PD_TOK
#define IPV6_D_AC_ENABLE_TOK        IPV6_DHCP_ _AC_ENABLE_TOK     
#define IPV6_D_AC_TYPE_TOK          IPV6_DHCP_ _AC_TYPE_TOK       
#define IPV6_D_AC_DHCP_PD_TOK       IPV6_DHCP_ _AC_DHCP_PD_TOK       
#define IPV6_D_AC_IP_RANGE_S_TOK    IPV6_DHCP_ _AC_IP_RANGE_S_TOK 
#define IPV6_D_AC_IP_RANGE_E_TOK    IPV6_DHCP_ _AC_IP_RANGE_E_TOK 
#define IPV6_D_AC_LIFETIME_2_TOK    IPV6_DHCP_ _AC_LIFETIME_2_TOK /* LAN DHCP Life Time */  
#define IPV6_D_AC_LIFETIME_1_TOK    IPV6_DHCP_ _AC_LIFETIME_1_TOK /* LAN Router Advertisment Life Time */
/* PPPoE */
#define IPV6_PPPOE_                 "ipv6_p"
#define IPV6_P_W_ADDR_MODE_TOK      "ipv6_p_w_mode"
#define IPV6_P_W_STATIC_IP_TOK      "ipv6_p_w_ip"
#define IPV6_P_W_USER_TOK           "ipv6_p_w_user"
#define IPV6_P_W_PW_TOK             "ipv6_p_w_pw"
#define IPV6_P_W_SERVICE_TOK        "ipv6_p_w_serv"
#define IPV6_P_W_CONN_TYPE_TOK      "ipv6_p_w_connt"
#define IPV6_P_W_MAX_IDLETIME_TOK   "ipv6_p_w_maxit"
#define IPV6_P_W_MTU_TOK            "ipv6_p_w_mtu"
#define IPV6_P_W_DNS_TYPE_TOK       "ipv6_p_w_dns_t"
#define IPV6_P_W_DNS1_TOK           "ipv6_p_w_dns1"
#define IPV6_P_W_DNS2_TOK           "ipv6_p_w_dns2"
#define IPV6_P_W_AuthType_TOK		"ipv6_p_w_authtype"
#define IPV6_P_L_IP_TOK             IPV6_PPPOE_ _L_IP_TOK           
#define IPV6_P_AC_ENABLE_TOK        IPV6_PPPOE_ _AC_ENABLE_TOK      
#define IPV6_P_AC_TYPE_TOK          IPV6_PPPOE_ _AC_TYPE_TOK        
#define IPV6_P_AC_IP_RANGE_S_TOK    IPV6_PPPOE_ _AC_IP_RANGE_S_TOK  
#define IPV6_P_AC_IP_RANGE_E_TOK    IPV6_PPPOE_ _AC_IP_RANGE_E_TOK  
#define IPV6_P_AC_LIFETIME_2_TOK    IPV6_PPPOE_ _AC_LIFETIME_2_TOK /* LAN DHCP Life Time */   
#define IPV6_P_AC_LIFETIME_1_TOK    IPV6_PPPOE_ _AC_LIFETIME_1_TOK /* LAN Router Advertisment Life Time */
/* IPv6 in IPv4 TUNNEL */
#define IPV6_TUNNEL_                "ipv6_t"
#define IPV6_T_W_REMOTE_V4_IP_TOK   "ipv6_t_w_r4_ip"
#define IPV6_T_W_REMOTE_V6_IP_TOK   "ipv6_t_w_r6_ip"
#define IPV6_T_W_LOCAL_V4_IP_TOK    "ipv6_t_w_l4_ip"
#define IPV6_T_W_LOCAL_V6_IP_TOK    "ipv6_t_w_l6_ip"
#define IPV6_T_W_DNS1_TOK           "ipv6_t_w_dns1"
#define IPV6_T_W_DNS2_TOK           "ipv6_t_w_dns2"
#define IPV6_T_L_IP_TOK             IPV6_TUNNEL_ _L_IP_TOK           
#define IPV6_T_AC_ENABLE_TOK        IPV6_TUNNEL_ _AC_ENABLE_TOK      
#define IPV6_T_AC_TYPE_TOK          IPV6_TUNNEL_ _AC_TYPE_TOK        
#define IPV6_T_AC_IP_RANGE_S_TOK    IPV6_TUNNEL_ _AC_IP_RANGE_S_TOK  
#define IPV6_T_AC_IP_RANGE_E_TOK    IPV6_TUNNEL_ _AC_IP_RANGE_E_TOK  
#define IPV6_T_AC_LIFETIME_2_TOK    IPV6_TUNNEL_ _AC_LIFETIME_2_TOK /* LAN DHCP Life Time */     
#define IPV6_T_AC_LIFETIME_1_TOK    IPV6_TUNNEL_ _AC_LIFETIME_1_TOK /* LAN Router Advertisment Life Time */
/* 6to4 */
#define IPV6_6TO4_                   "ipv6_64"
#define IPV6_6TO4_W_DNS1_TOK         "ipv6_64_w_dns1"
#define IPV6_6TO4_W_DNS2_TOK         "ipv6_64_w_dns2"
#define IPV6_6TO4_L_IP_TOK           IPV6_6TO4_ _L_IP_TOK           
#define IPV6_6TO4_AC_ENABLE_TOK      IPV6_6TO4_ _AC_ENABLE_TOK      
#define IPV6_6TO4_AC_TYPE_TOK        IPV6_6TO4_ _AC_TYPE_TOK        
#define IPV6_6TO4_AC_IP_RANGE_S_TOK  IPV6_6TO4_ _AC_IP_RANGE_S_TOK  
#define IPV6_6TO4_AC_IP_RANGE_E_TOK  IPV6_6TO4_ _AC_IP_RANGE_E_TOK  
#define IPV6_6TO4_AC_LIFETIME_2_TOK  IPV6_6TO4_ _AC_LIFETIME_2_TOK /* LAN DHCP Life Time */     
#define IPV6_6TO4_AC_LIFETIME_1_TOK  IPV6_6TO4_ _AC_LIFETIME_1_TOK /* LAN Router Advertisment Life Time */
/* IPv6 Rapid Deployment */
#define IPV6_6RD_                      "ipv6_6rd"
#define IPV6_6RD_W_ISP_PREFIX_TOK  	   "ipv6_6rd_w_prefix"
#define IPV6_6RD_W_ISP_PREFIX_LEN_TOK  "ipv6_6rd_w_len"
#define IPV6_6RD_W_LOCAL_V4_IP_TOK     "ipv6_6rd_w_l4_ip"
#define IPV6_6RD_W_SUBMASK_LENGTH_TOK  "ipv6_6rd_w_mask_len"
#define IPV6_6RD_W_REMOTE_V4_IP_TOK	   "ipv6_6rd_w_r4_ip"
#define IPV6_6RD_W_DNS1_TOK            "ipv6_6rd_w_dns1"
#define IPV6_6RD_W_DNS2_TOK        	   "ipv6_6rd_w_dns2"
#define IPV6_6RD_L_IP_TOK              IPV6_6RD_ _L_IP_TOK           
#define IPV6_6RD_AC_ENABLE_TOK     	   IPV6_6RD_ _AC_ENABLE_TOK      
#define IPV6_6RD_AC_TYPE_TOK           IPV6_6RD_ _AC_TYPE_TOK        
#define IPV6_6RD_AC_IP_RANGE_S_TOK     IPV6_6RD_ _AC_IP_RANGE_S_TOK  
#define IPV6_6RD_AC_IP_RANGE_E_TOK     IPV6_6RD_ _AC_IP_RANGE_E_TOK  
#define IPV6_6RD_AC_LIFETIME_2_TOK     IPV6_6RD_ _AC_LIFETIME_2_TOK /* LAN DHCP Life Time */     
#define IPV6_6RD_AC_LIFETIME_1_TOK     IPV6_6RD_ _AC_LIFETIME_1_TOK /* LAN Router Advertisment Life Time */
/* Stateless Autoconfiguration */
#define IPV6_STATELESS_             "ipv6_sa"
#define IPV6_SA_W_DNS1_TOK          "ipv6_sa_w_dns1"
#define IPV6_SA_W_DNS2_TOK          "ipv6_sa_w_dns2"
#define IPV6_SA_L_IP_TOK            IPV6_STATELESS_ _L_IP_TOK          
#define IPV6_SA_AC_ENABLE_TOK       IPV6_STATELESS_ _AC_ENABLE_TOK     
#define IPV6_SA_AC_TYPE_TOK         IPV6_STATELESS_ _AC_TYPE_TOK       
#define IPV6_SA_AC_IP_RANGE_S_TOK   IPV6_STATELESS_ _AC_IP_RANGE_S_TOK 
#define IPV6_SA_AC_IP_RANGE_E_TOK   IPV6_STATELESS_ _AC_IP_RANGE_E_TOK 
#define IPV6_SA_AC_LIFETIME_2_TOK   IPV6_STATELESS_ _AC_LIFETIME_2_TOK /* LAN DHCP Life Time */    
#define IPV6_SA_AC_LIFETIME_1_TOK   IPV6_STATELESS_ _AC_LIFETIME_1_TOK /* LAN Router Advertisment Life Time */
/* Autodetection: combine DHCPv6 with SLAAC */
#define IPV6_AUTODETECT_            "ipv6_ad"
#define IPV6_AD_W_DNS_TYPE_TOK      "ipv6_ad_w_dns_t"
#define IPV6_AD_W_DNS1_TOK          "ipv6_ad_w_dns1"
#define IPV6_AD_W_DNS2_TOK          "ipv6_ad_w_dns2"
#define IPV6_AD_L_IP_TOK            IPV6_AUTODETECT_ _L_IP_TOK          
#define IPV6_AD_L_DHCP_PD_TOK       IPV6_AUTODETECT_ _L_DHCP_PD_TOK
#define IPV6_AD_AC_ENABLE_TOK       IPV6_AUTODETECT_ _AC_ENABLE_TOK     
#define IPV6_AD_AC_TYPE_TOK         IPV6_AUTODETECT_ _AC_TYPE_TOK       
#define IPV6_AD_AC_DHCP_PD_TOK      IPV6_AUTODETECT_ _AC_DHCP_PD_TOK       
#define IPV6_AD_AC_IP_RANGE_S_TOK   IPV6_AUTODETECT_ _AC_IP_RANGE_S_TOK 
#define IPV6_AD_AC_IP_RANGE_E_TOK   IPV6_AUTODETECT_ _AC_IP_RANGE_E_TOK 
#define IPV6_AD_AC_LIFETIME_2_TOK   IPV6_AUTODETECT_ _AC_LIFETIME_2_TOK /* LAN DHCP Life Time */     
#define IPV6_AD_AC_LIFETIME_1_TOK   IPV6_AUTODETECT_ _AC_LIFETIME_1_TOK /* LAN Router Advertisment Life Time */

#endif

#if SUPPORT_IPV6_LOGO
#define IPV6_RA_ENABLE_TOK								"ipv6_ra_en"
#define IPV6_RA_INTERFACE_TOK							"ipv6_ra_interface"
#define IPV6_RA_MAXRTRADV_TOK							"ipv6_ra_maxrtr"
#define IPV6_RA_MINRTRADV_TOK							"ipv6_ra_minrtr"
#define IPV6_RA_MINDELAYTIME_TOK						"ipv6_ra_mindelay"
#define IPV6_RA_ADVMANAGED_TOK							"ipv6_ra_advmanged"
#define IPV6_RA_ADVOTHERCONFIG_TOK						"ipv6_ra_advother"
#define IPV6_RA_ADVLINKMTU_TOK							"ipv6_ra_advlinkmtu"
#define IPV6_RA_ADVREACHABLE_TOK						"ipv6_ra_advreach"
#define IPV6_RA_ADVRETRANS_TOK							"ipv6_ra_advretrans"
#define IPV6_RA_ADVCURHOPLIMIT_TOK						"ipv6_ra_advcurhop"
#define IPV6_RA_ADVDEFAULTLIFETIME_TOK					"ipv6_ra_advdeflife"
#define IPV6_RA_ADVDEFAULTPREFERENCE_TOK				"ipv6_ra_advdefpre"
#define IPV6_RA_ADVSOURCELLADDRESS_TOK					"ipv6_ra_advsource"
#define IPV6_RA_UNICASTONLY_TOK							"ipv6_ra_unicast"
#define IPV6_RA_PREFIX0_ENABLE_TOK						"ipv6_p0_en"
#define IPV6_RA_PREFIX0_ADDRESS_TOK						"ipv6_p0_addr"
#define IPV6_RA_PREFIX0_LEN_TOK							"ipv6_p0_len"
#define IPV6_RA_PREFIX0_ADVONLINK_TOK					"ipv6_p0_advonlink"
#define IPV6_RA_PREFIX0_ADVAUTONOMOUS_TOK				"ipv6_p0_advauto"
#define IPV6_RA_PREFIX0_ADVVALIDLIFETIME_TOK			"ipv6_p0_advvlid"
#define IPV6_RA_PREFIX0_ADVPREFERREDLIFETIME_TOK		"ipv6_p0_advprefer"
#define IPV6_RA_PREFIX0_ADVROUTERADDRESS_TOK			"ipv6_p0_advroute"
#define IPV6_RA_PREFIX0_IF6TO4_TOK						"ipv6_p0_if6to4"
#define IPV6_RA_PREFIX1_ENABLE_TOK						"ipv6_p1_en"
#define IPV6_RA_PREFIX1_ADDRESS_TOK						"ipv6_p1_addr"
#define IPV6_RA_PREFIX1_LEN_TOK							"ipv6_p1_len"
#define IPV6_RA_PREFIX1_ADVONLINK_TOK					"ipv6_p1_advonlink"
#define IPV6_RA_PREFIX1_ADVAUTONOMOUS_TOK				"ipv6_p1_advauto"
#define IPV6_RA_PREFIX1_ADVVALIDLIFETIME_TOK			"ipv6_p1_advvlid"
#define IPV6_RA_PREFIX1_ADVPREFERREDLIFETIME_TOK		"ipv6_p1_advprefer"
#define IPV6_RA_PREFIX1_ADVROUTERADDRESS_TOK			"ipv6_p1_advroute"
#define IPV6_RA_PREFIX1_IF6TO4_TOK						"ipv6_p1_if6to4"

#endif
/* -------------------------------------------------------------------------------*/
#if HAS_NPH_MODULE
#define NPH_ENABLE_TOK	"nph_en"
#if HAS_NPH_VLAN_SWITCH
#define NPH_VLAN_ENABLE_TOK	"nph_vlan_en"
#define NPH_TOK	"nph_"
#define NPH_01_TOK	"nph_1"
#define NPH_02_TOK	"nph_2"
#define NPH_03_TOK	"nph_3"
#define NPH_04_TOK	"nph_4"
#define NPH_05_TOK	"nph_5"
#define NPH_06_TOK	"nph_6"
#define NPH_07_TOK	"nph_7"
#define NPH_08_TOK	"nph_8"
#define NPH_09_TOK	"nph_9"
#define NPH_10_TOK	"nph_10"
#define NPH_DESC_TOK	"nph_desc_"
#define NPH_DESC_01_TOK	"nph_desc_1"
#define NPH_DESC_02_TOK	"nph_desc_2"
#define NPH_DESC_03_TOK	"nph_desc_3"
#define NPH_DESC_04_TOK	"nph_desc_4"
#define NPH_DESC_05_TOK	"nph_desc_5"
#define NPH_DESC_06_TOK	"nph_desc_6"
#define NPH_DESC_07_TOK	"nph_desc_7"
#define NPH_DESC_08_TOK	"nph_desc_8"
#define NPH_DESC_09_TOK	"nph_desc_9"
#define NPH_DESC_10_TOK	"nph_desc_10"
#endif
#endif

#if HAS_SUPPORT_UBICOM_WISH
#define WISH_ENABLE_TOK	"wish_en"
#define WISH_TOK	"wish_"
#define WISH_01_TOK	"wish_1"
#define WISH_02_TOK	"wish_2"
#define WISH_03_TOK	"wish_3"
#define WISH_04_TOK	"wish_4"
#define WISH_05_TOK	"wish_5"
#define WISH_06_TOK	"wish_6"
#define WISH_07_TOK	"wish_7"
#define WISH_08_TOK	"wish_8"
#define WISH_09_TOK	"wish_9"
#define WISH_10_TOK	"wish_10"
#endif


#endif //_TOKEN_H_

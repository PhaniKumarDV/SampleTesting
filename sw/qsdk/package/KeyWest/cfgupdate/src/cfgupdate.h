
#define KWN_MAC_ADDR_LEN 6
#define KWN_GPS_LEN 32
#define KWN_MAX_LINKS 1
#define KWN_CFG_BUF_LEN 650
#define KWN_CMD_IMP_LEN 100
#define KWN_CMD_OUT_LEN 50

enum uci_cfg_id {
    /* RADIO 1 */
    UCI_ID_RADIO1_MODE = 1,
    UCI_ID_RADIO1_SSID = 2,
    UCI_ID_RADIO1_COUNTRY = 3,
    UCI_ID_RADIO1_OPMODE = 4,
    UCI_ID_RADIO1_BANDWIDTH = 5,
    UCI_ID_RADIO1_CHANNEL = 6,
    UCI_ID_RADIO1_RATE = 7,
    UCI_ID_RADIO1_POWER = 8,
    UCI_ID_RADIO1_AMSDU = 9,
    UCI_ID_RADIO1_UPLINK_LMT = 10,
    UCI_ID_RADIO1_DOWNLINK_LMT = 11,
    UCI_ID_RADIO1_HIDE_ESSID = 12,
    UCI_ID_RADIO1_CUSTOMER_NAME = 13,
    UCI_ID_RADIO1_LINK_ID = 14,
    /* RADIO 2 */
    UCI_ID_RADIO2_MODE = 15,
    UCI_ID_RADIO2_SSID = 16,
    UCI_ID_RADIO2_COUNTRY = 17,
    UCI_ID_RADIO2_OPMODE = 18,
    UCI_ID_RADIO2_BANDWIDTH = 19,
    UCI_ID_RADIO2_CHANNEL = 20,
    UCI_ID_RADIO2_POWER = 21,
    UCI_ID_RADIO2_HIDE_ESSID = 22,
    /* IP */
    UCI_ID_IP = 23,
    UCI_ID_ADDR_TYPE = 24,
    UCI_ID_MASK = 25,
    UCI_ID_GATEWAY = 26,
    UCI_ID_DNS_IP = 27,
    /* SECURITY RADIO 1 */
    UCI_ID_RADIO1_SECURITY_ENC = 28,
    UCI_ID_RADIO1_SECURITY_KEY = 29,
    /* SECURITY RADIO 2 */
    UCI_ID_RADIO2_SECURITY_ENC = 30,
    UCI_ID_RADIO2_SECURITY_KEY = 31,
    /* RADIUS */
    UCI_ID_RADIUS_STATUS = 32,
    UCI_ID_RADIUS_PRI_SERVER = 33,
    UCI_ID_RADIUS_PRI_PORT = 34,
    UCI_ID_RADIUS_PRI_SECRET = 35,
    UCI_ID_RADIUS_SEC_SERVER = 36,
    UCI_ID_RADIUS_SEC_PORT = 37,
    UCI_ID_RADIUS_SEC_SECRET = 38,
    UCI_ID_RADIUS_REAUTH_TIME = 39,
    UCI_ID_RADIUS_RETRY_TIME = 40,
    UCI_ID_RADIUS_RETRY_COUNT = 41,
    UCI_ID_RADIUS_RETRY_COUNT_PERIOD = 42,
    /* Ethernet */
    UCI_ID_ETHERNET_SPEED = 43,
    /* DHCP 5GHz */
    UCI_ID_DHCP_SERVER = 44,
    UCI_ID_DHCP_START = 45,
    UCI_ID_DHCP_LIMIT = 46,
    UCI_ID_DHCP_LEASE_TIME = 47,
    /* Local MAC ACL RADIO 1 */
    UCI_ID_RADIO1_MACFILTER = 48,
    UCI_ID_RADIO1_MACLIST = 49,
    /* Local MAC ACL RADIO 2 */
    UCI_ID_RADIO2_MACFILTER = 50,
    UCI_ID_RADIO2_MACLIST = 51,
    /* VLAN */
    UCI_ID_VLAN_STATUS =52,
    UCI_ID_VLAN_MODE =53,
    UCI_ID_VLAN_MGMT_VLAN =54,
    UCI_ID_VLAN_ACCESS_VLAN =55,
    UCI_ID_VLAN_TRUNK_OPTION =56,
    UCI_ID_VLAN_TRUNK_VLAN =57,
    UCI_ID_VLAN_SVLAN =58,
    UCI_ID_VLAN_SVLAN_ETHER_TYPE =59,
    /* System */
    UCI_ID_HOSTNAME =60,
    UCI_ID_TIMEZONE =61,
    UCI_ID_GPS =62,
    UCI_ID_GPS_INT =63,
    UCI_ID_DYING_GASP =64,
    UCI_ID_LEDS =65,
    UCI_ID_SYSLOG_SERVER =66,
    UCI_ID_SYSLOG_SERVER_PORT =67,
    UCI_ID_TEMP_LOG =68,
    UCI_ID_TEMP_LOG_INT =69,
    UCI_ID_ZONENAME =70,
    UCI_ID_NTP_SERVER =71,
    UCI_ID_NTP =72,
    UCI_ID_DISTANCE =73,
    UCI_ID_RADIO1_SHORTGI =74,
    UCI_ID_RADIO1_TXCHAINMASK =75,
    UCI_ID_RADIO1_RXCHAINMASK =76,
    UCI_ID_ETHERNET_INACTIVITY =77,
    /* Link Test */
    UCI_ID_LINK_TEST_SIZE =78,
    UCI_ID_LINK_TEST_DUR =79,
    UCI_ID_LINK_TEST_DIR =80,
    /* VLAN */
    UCI_ID_VLAN_BDA =81,
    UCI_ID_VLAN_BSA =82,
    UCI_ID_VLAN_BVID =83,
    UCI_ID_VLAN_BISID =84,
    /* DYING GASP */
    UCI_ID_DG_DISABLE_ACK =85,
    /* SNMP */
    UCI_ID_SNMP_STATUS =86,
    UCI_ID_SNMP_VERSION =87,
    UCI_ID_SNMP_RW_PASWD =88,
    UCI_ID_SNMP_TRPA_HOST_IP =89,
    UCI_ID_SNMP_TRAP_HOST_PWD =90,
    /* HTTP */
    UCI_ID_HTTP_STATUS =91,
    UCI_ID_HTTP_ADMIN_PWD =92,
    UCI_ID_HTTP_USER_PWD =93,
    UCI_ID_HTTP_SUPER_PWD =94,
    UCI_ID_HTTP_PORT =95,
    UCI_ID_HTTPS_STATUS =96,
    UCI_ID_HTTPS_PORT =97,
    /* Telnet SSH */
    UCI_ID_TELNET_STATUS =98,
    UCI_ID_TELNET_PORT =99,
    UCI_ID_TELNET_SESSIONS =100,
    UCI_ID_SSH_STATUS =101,
    UCI_ID_SSH_PORT =102,
    UCI_ID_SSH_SESSIONS =103,
    /* Wireless */
    UCI_ID_RADIO1_AMPDU =104,
    UCI_ID_RADIO1_DDRS_STATUS =105,
    UCI_ID_RADIO1_DDRS_RATE =106,
    UCI_ID_RADIO1_DDRS_MIN_RATE =107,
    UCI_ID_RADIO1_DDRS_MAX_RATE =108,
    UCI_ID_RADIO1_DDRS_STREAM =109,
    UCI_ID_RADIO1_DDRS_RATE_INC_TIMER =110,
    UCI_ID_RADIO1_DDRS_RATE_DEC_TIMER =111,
    UCI_ID_RADIO1_ATPC_STATUS =112,
    UCI_ID_RADIO1_ATPC_POWER =113,
    /* Ethernet MTU */
    UCI_ID_ETHERNET_MTU = 114,
    /* Wireless */
    UCI_ID_RADIO1_ANTENNA_GAIN = 115,
    /* VLAN */
    UCI_ID_VLAN_ALLOW_TAGGED_MGMT = 116,
    /* TFTP */
    UCI_ID_TFTP_FILENAME = 117,
    UCI_ID_TFTP_FILETYPE = 118,
    UCI_ID_TFTP_SERVERIP = 119,
    UCI_ID_TFTP_OPTYPE = 120,
    UCI_ID_TFTP_KEEPSET = 121,
    /* Wireless */
    UCI_ID_RADIO1_DDRS_INCR_THRLD = 122,
    UCI_ID_RADIO1_TRAFFIC_SHAPING = 123,
    UCI_ID_RADIO1_DCS_STATUS = 124,
    UCI_ID_RADIO1_DCS_THRLD = 125,
    UCI_ID_RADIO1_DDRS_RTX_INC = 126,
    UCI_ID_RADIO1_DDRS_RTX_DEC = 127,
    /* Filtering */
    UCI_ID_FILTERING_STATUS  = 128,
    UCI_ID_FILTERING_L2MCAST = 129,
    UCI_ID_FILTERING_L3MCAST = 130,
    UCI_ID_FILTERING_L2BCAST = 131,
    UCI_ID_FILTERING_L3BCAST = 132,
    /* Inactivity */
    UCI_ID_RADIO1_WIRELESS_INACT = 133,
    UCI_ID_RADIO1_LINK_INACT = 134,
    UCI_ID_RADIO1_MAX_EIRP = 135,
    UCI_ID_RADIO2_RATE = 136,
    UCI_ID_RADIO2_DISABLE_LEGACY = 137,
    UCI_ID_RADIO2_STATUS = 138,
    /* System Info */
    UCI_ID_SYSTEM_LOCATION = 139,
    UCI_ID_SYSTEM_CONTACT = 140,
    UCI_ID_SYSTEM_EMAIL = 141,
    /* Routing Params */
    UCI_ID_NETWORK_MODE = 142,
    UCI_ID_NAT_STATUS = 143,
    /* Ethernet Routing Params */
    UCI_ID_ROUTE_ETH_IP = 144,
    UCI_ID_ROUTE_ETH_ADDR_TYPE = 145,
    UCI_ID_ROUTE_ETH_NETMASK = 146,
    /* System Info */
    UCI_ID_SYSTEM_BASESTATION_ID = 147,
    UCI_ID_RADIO1_SU_SERVICE = 148,
    /* Retain IP */
    UCI_ID_RETAINIP_ONRESET = 149,
    /* Wireless Linktype ('1'-PTP,'2'-BACKHAUL,'3'-PTMP) */
    UCI_ID_WIRELESS_LINKTYPE = 150,
    UCI_ID_WIRELESS_ICB = 151,
    UCI_ID_WIRELESS_MACINMAC = 152,
    UCI_ID_RADIO1_MAXSTA = 153,
    UCI_ID_RADIO1_RCRETRIES = 154,
    /* DHCP 2.4 GHz */
    UCI_ID_DHCP24_SERVER = 155,
    UCI_ID_DHCP24_START = 156,
    UCI_ID_DHCP24_LIMIT = 157,
    UCI_ID_DHCP24_LEASE_TIME = 158,
    /* 2.4GHz Max Sta */
    UCI_ID_RADIO2_MAXSTA = 159,
    /* 2.4GHz IP Configuration */
    UCI_ID_IP_24 = 160,
    UCI_ID_MASK_24 = 161,
    /* UHTTPD installer Password*/
    UCI_ID_HTTP_INST_PWD = 162
};

typedef struct
{
        uint8_t  mac[KWN_MAC_ADDR_LEN];
        uint32_t ip;
        char  r_latitude[KWN_GPS_LEN];
        char  r_longitude[KWN_GPS_LEN];
        char  l_latitude[KWN_GPS_LEN];
        char  l_longitude[KWN_GPS_LEN];
        uint64_t tx_tput;
        uint64_t rx_tput;
        uint32_t local_snr_a1;
        uint32_t local_snr_a2;
        uint32_t remote_snr_a1;
        uint32_t remote_snr_a2;
}kwn_link_stats;

typedef struct
{
        int no_of_links;
        kwn_link_stats sta[KWN_MAX_LINKS];
}kwn_wireless_stats;

typedef struct 
{ 
        uint8_t  start_stop; 
        uint8_t  mac[KWN_MAC_ADDR_LEN]; /* remote mac_address */ 
        uint32_t direction;             /* test_direction*/ 
        uint32_t duration;              /* test_duration */ 
}kwn_link_test;

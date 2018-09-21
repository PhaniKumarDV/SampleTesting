

#define KWN_MAC_ADDR_LEN 6
#define KWN_GPS_LEN 32
#define KWN_MAX_LINKS 1

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
    /* DHCP */
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
    UCI_ID_VLAN_BISID =84
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

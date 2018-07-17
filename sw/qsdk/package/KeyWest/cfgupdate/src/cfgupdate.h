

#define KWN_MAC_ADDR_LEN 6
#define KWN_GPS_LEN 32
#define KWN_MAX_LINKS 1

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

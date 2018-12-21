#define PORT                9181
#define KWN_PKT_SIZE        1309
#define KWN_MAC_ADDR_LEN    6 
#define KWN_GPS_LEN         32 
#define KWN_MAX_LINKS       1
#define KWN_PKT_DATA_SIZE   1300
#define KWN_SUCCESS         1
#define KWN_FAILURE         (-1) 
#define KWN_OK              1
#define KWN_ERROR           (-1)

enum kwn_id
{
    SIFY_ID = 1,
    KEYWEST_ID
};

enum kwn_interface_type
{
    KWN_MOBILE_APP = 1,
    KWN_NMS_APP
};

enum kwn_pkt_type
{
    KWN_TYPE_GET_REQUEST = 1,
    KWN_TYPE_GET_RESPONSE,
    KWN_TYPE_SET_REQUEST,
    KWN_TYPE_SET_RESPONSE
};

enum kwn_pkt_subtype
{
    KWN_SUBTYPE_CONFIG_DATA = 1,
    KWN_SUBTYPE_WIRELESS_STAT,
    KWN_SUBTYPE_ETHERNET_STAT,
    KWN_SUBTYPE_LINK_TEST
};

enum kwn_cfg_data_params
{
    KWN_CFG_IP = 1,
    KWN_CFG_IP_TYPE,
    KWN_CFG_SSID,
    KWN_CFG_OPMODE,
    KWN_CFG_BANDWIDTH,
    KWN_CFG_CHANNEL,
    KWN_CFG_DEV_MODE,
    KWN_CFG_MAC,
    KWN_CFG_CTRY,
    KWN_CFG_GIP,
    KWN_CFG_NETMASK,
    KWN_CFG_CUST_NAME,
    KWN_CFG_LINKID,
    KWN_CFG_DDRS_STATUS,
    KWN_CFG_SPATIAL_STREAM,
    KWN_CFG_MOD_INDEX,
    KWN_CFG_MIN_MOD_INDEX,
    KWN_CFG_MAX_MOD_INDEX,
    KWN_CFG_ATPC_STATUS,
    KWN_CFG_TX_POWER
};

enum kwn_wireless_stat
{
    KWN_WLAN_NO_LINKS = 1
};

enum kwn_wireless_link_stat
{
    KWN_WLAN_ID = 2,
    KWN_WLAN_MAC,
    KWN_WLAN_R_IP,
    KWN_WLAN_R_LAT,
    KWN_WLAN_R_LONG,
    KWN_WLAN_L_LAT,
    KWN_WLAN_L_LONG,
    KWN_WLAN_TX_TPUT,
    KWN_WLAN_RX_TPUT,
    KWN_WLAN_L_SNR_A1,
    KWN_WLAN_L_SNR_A2,
    KWN_WLAN_R_SNR_A1,
    KWN_WLAN_R_SNR_A2,
    KWN_WLAN_L_RATE,
    KWN_WLAN_R_RATE,
    KWN_WLAN_L_SIGNAL_A1,
    KWN_WLAN_L_SIGNAL_A2,
    KWN_WLAN_R_SIGNAL_A1,
    KWN_WLAN_R_SIGNAL_A2,
    KWN_WLAN_L_LINK_QINDEX,
    KWN_WLAN_R_LINK_QINDEX
};

enum kwn_ethernet_stat
{
    KWN_ETH_TX_PACKETS = 1,
    KWN_ETH_RX_PACKETS,
    KWN_ETH_TX_BYTES,
    KWN_ETH_RX_BYTES,
    KWN_ETH_TX_ERRORS,
    KWN_ETH_RX_ERRORS
};

enum kwn_link_test_params
{
    KWN_LT_START_STOP = 1,
    KWN_LT_R_MAC,
    KWN_LT_DIRECTION,
    KWN_LT_DURATION
};

enum kwn_lt_start_stop_value
{
    KWN_LT_START = 1,
    KWN_LT_STOP = 0
};

enum kwn_response_status
{
    KWN_STATUS_SUCCESS = 1,
    KWN_STATUS_FAILURE
};

enum kwn_ip_address_type
{
    KWN_STATIC_IP_TYPE = 1,
    KWN_DYNAMIC_IP_TYPE
};

enum kwn_device_mode
{
    KWN_OUTDOOR_BASE = 1,
    KWN_OUTDOOR_SUBSCRIBER,
    KWN_ADHOC,
    KWN_STATIC_WDS
};

enum kwn_radio_opmode {
    KWN_RADIO_OPMODE_DOT11A = 1,
    KWN_RADIO_OPMODE_DOT11NA,
    KWN_RADIO_OPMODE_DOT11AC
};

enum kwn_channel_bandwidth
{
    KWN_CHANNEL_BW_5 = 1 ,
    KWN_CHANNEL_BW_10,
    KWN_CHANNEL_BW_20,
    KWN_CHANNEL_BW_40,
    KWN_CHANNEL_BW_40MINUS,
    KWN_CHANNEL_BW_80
};

enum kwn_cfg_ctry_code
{
    INDIA_UL = 5016,
    INDIA_L  = 5017,
    RUSSIA   = 5011 
};

/* Size of kwn_pkt_hdr = 1+1+2+1+1+1+1 = 8 bytes */
typedef struct
{
    uint8_t  id;             /*            unique to identify - 1 byte  */
    uint8_t  interface_type; /*             type of interface - 1 byte  */
    uint16_t length;         /*                size of buffer - 2 bytes */
    uint8_t  type;           /* Get / Set  & Request/Response - 1 byte  */
    uint8_t  sub_type;       /*        structure or text_file - 1 byte  */
    uint8_t  ptmp;           /*                          ptmp - 1 byte  */ 
    uint8_t  more;           /*                          more - 1 byte  */   
}__attribute__((packed)) kwn_pkt_hdr;

/* Size of kwn_pkt = 8+1300+1 = 1309 bytes */
typedef struct
{
    kwn_pkt_hdr hdr;                 /*    hdr -    6 bytes */
    uint8_t data[KWN_PKT_DATA_SIZE]; /*   data - 1300 bytes */
    uint8_t footer;                  /* footer -    1 byte  */
}__attribute__((packed)) kwn_pkt;

/* Size of kwn_link_stats = 1+6+4+32+32+32+32+2+2+1+1+1+1+2+2+2+2+2+2+1+1 = 161 bytes */
typedef struct
{
    uint8_t  link_id;                       /*                     SU id -  1 byte  */
    uint8_t  mac[KWN_MAC_ADDR_LEN];         /*               mac_address -  6 bytes */
    uint8_t  r_ip[4];                       /*                 ipaddress -  4 bytes */
    uint8_t  r_latitude[KWN_GPS_LEN];       /*           remote_latitude - 32 bytes */
    uint8_t  r_longitude[KWN_GPS_LEN];      /*          remote_longitude - 32 bytes */
    uint8_t  l_latitude[KWN_GPS_LEN];       /*            local_latitude - 32 bytes */
    uint8_t  l_longitude[KWN_GPS_LEN];      /*           local_longitude - 32 bytes */
    uint16_t tx_tput;                       /*                  Tx Thput -  2 bytes */
    uint16_t rx_tput;                       /*                  Rx Thput -  2 bytes */
    uint8_t  local_snr_a1;                  /*              Local SNR A1 -  1 bytes */
    uint8_t  local_snr_a2;                  /*              Local SNR A2 -  1 bytes */
    uint8_t  remote_snr_a1;                 /*             Remote SNR A1 -  1 bytes */
    uint8_t  remote_snr_a2;                 /*             Remote SNR A2 -  1 bytes */
    uint16_t tx_ratekbps;                   /*                Local Rate -  2 bytes */
    uint16_t rx_ratekbps;                   /*               Remote Rate -  2 bytes */
    int16_t  local_signal_a1;               /*           Local Signal A1 -  2 byte  */
    int16_t  local_signal_a2;               /*           Local Signal A2 -  2 byte  */
    int16_t  remote_signal_a1;              /*          Remote Signal A1 -  2 byte  */
    int16_t  remote_signal_a2;              /*          Remote Signal A2 -  2 byte  */
    uint8_t  local_link_qindex;             /*  Local Link Quality Index -  1 byte  */
    uint8_t  remote_link_qindex;            /* Remote Link Quality Index -  1 byte  */
}__attribute__((packed)) kwn_link_stats;

/* Size of kwn_wireless_stats = 1+151 = 152 bytes */
typedef struct
{
    uint8_t no_of_links;                   /* no of links - 1 bytes */
    kwn_link_stats sta[KWN_MAX_LINKS];
}__attribute__((packed)) kwn_wireless_stats;

/* Size of kwn_link_test = 1+6+1+1 = 9 bytes */
typedef struct
{
    uint8_t start_stop;             /*         start_stop - 1 byte  */
    uint8_t mac[KWN_MAC_ADDR_LEN];  /* remote mac_address - 6 bytes */
    uint8_t direction;              /*     test_direction - 1 byte  */
    uint8_t duration;               /*      test_duration - 1 byte  */
}__attribute__((packed)) kwn_link_test;

/* Size of kwn_eth_stats = 8+8+8+8+8+8 = 48 bytes */
typedef struct
{
    uint64_t tx_packets;    /* tx packets - 8 bytes */
    uint64_t rx_packets;    /* rx packets - 8 bytes */
    uint64_t tx_bytes;      /*   tx bytes - 8 bytes */
    uint64_t rx_bytes;      /*   rx bytes - 8 bytes */
    uint64_t tx_errors;     /*  tx errors - 8 bytes */
    uint64_t rx_errors;     /*  tx errors - 8 bytes */
}__attribute__((packed)) kwn_eth_stats;

/* Size of kwn_cfg_update = 4+1+33+1+1+1+1+6+2+4+4+33+1+1+1+1+1+1+1+1 = 99 bytes */
typedef struct
{
    uint8_t  ip[4];         /*                ipaddress -  4 bytes */
    uint8_t  ip_type;       /*                   iptype -  1 bytes */
    uint8_t  ssid[33];      /*                     ssid - 33 bytes */
    uint8_t  opmode;        /*                   opmode -  1 bytes */
    uint8_t  bandwidth;     /*                bandwidth -  1 bytes */
    uint8_t  channel;       /*                  channel -  1 byte  */
    uint8_t  mode;          /*              device mode -  1 byte  */
    uint8_t  local_mac[6];  /*                local mac -  6 bytes */
    uint16_t country;       /*                  country -  2 bytes */
    uint8_t  gip[4];        /*                  gateway -  4 bytes */
    uint8_t  netmask[4];    /*                  netmask -  4 bytes */
    uint8_t  cust_name[33]; /*                cust_name - 33 bytes */
    uint8_t  linkid;        /*                   linkid -  1 byte  */
    uint8_t  ddrs_status;   /*               ddrsstatus -  1 byte  */
    uint8_t  stream;        /*           spatial stream -  1 byte  */
    uint8_t  modindex;      /*         Modulation index -  1 byte  */
    uint8_t  min_modindex;  /* Minimum Modultaion index -  1 byte  */
    uint8_t  max_modindex;  /* Maximum Modulation index -  1 byte  */
    uint8_t  atpc_status;   /*              ATPC Status -  1 byte  */
    uint8_t  txpower;       /*                 TX Power -  1 byte  */
}__attribute__((packed)) kwn_cfg_data;

char *kwn_dev_mode[] = {"\0","ap","sta"};
char *kwn_opmode[] = {"\0","11a","11na","11ac"};
char *kwn_bandwidth[] = {"\0","HT5","HT10","HT20","HT40+","HT40-","HT80"};
char *kwn_ip_type[] = {"\0","static","dhcp"};

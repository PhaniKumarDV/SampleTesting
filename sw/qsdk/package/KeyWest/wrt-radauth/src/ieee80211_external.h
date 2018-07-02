/*****************************************************************************/
/* \file ieee80211_external.h
** \brief External Header File References
**
**  This header file refers to the internal header files that provide the
**  data structure definitions and parameters required by external programs
**  that interface via ioctl or similiar mechanisms.  This hides the location
**  of the specific header files, and provides a control to limit what is
**  being exported for external use.
**
**  Copyright (c) 2009 Atheros Communications Inc.  All rights reserved.
**
** Permission to use, copy, modify, and/or distribute this software for any
** purpose with or without fee is hereby granted, provided that the above
** copyright notice and this permission notice appear in all copies.
**
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
** WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
** MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
** ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
** WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
** ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
** OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
**/

/* 
 * Copyright (c) 2013 Qualcomm Atheros, Inc.
 * All Rights Reserved. 
 * Qualcomm Atheros Confidential and Proprietary. 
 */ 

#ifndef IEEE80211_EXTERNAL_H
#define IEEE80211_EXTERNAL_H

#ifndef __packed
#define __packed    __attribute__((__packed__))
#endif
#define EXTERNAL_USE_ONLY
//#include "if_athioctl.h"
//#include "ath_ald_external.h"

struct ev_msg {
    u_int8_t addr[IEEE80211_ADDR_LEN];
    u_int32_t status;
    u_int32_t reason;
};

struct ev_recv_probereq {
    u_int8_t mac_addr[IEEE80211_ADDR_LEN]; /* mac addr */
    u_int32_t rssi;       /* rssi */
    u_int32_t rate;       /* data rate */
    u_int8_t channel_num; /* operating channel number */
};

struct ev_node_authorized {
    u_int8_t  mac_addr[IEEE80211_ADDR_LEN]; /* mac addr */
    u_int8_t  channel_num; /* operating channel number */
    u_int16_t assoc_id;    /* assoc id */
    /* HW capabilities */
    u_int16_t phymode;     /* phymode(11ac/abgn)  */
    u_int8_t  nss;         /* tx/rx chains */
    u_int8_t  is_256qam;         /* tx/rx chains */
};

struct ev_sta_leave {
    u_int8_t  mac_addr[IEEE80211_ADDR_LEN]; /* mac addr */
    u_int8_t  channel_num; /* operating channel number */
    u_int16_t assoc_id;    /* assoc id */
    u_int32_t reason;      /* leave reason */
};


/*
 * IEEE 802.11 ioctls.
 */
#ifndef EXTERNAL_USE_ONLY
/* duplicate defination - to avoid including ieee80211_var.h */
#ifndef __ubicom32__
#define IEEE80211_ADDR_COPY(dst,src)    OS_MEMCPY(dst, src, IEEE80211_ADDR_LEN)
#else
#define IEEE80211_ADDR_COPY(dst,src)    OS_MACCPY(dst, src)
#endif
#define IEEE80211_KEY_XMIT      0x01    /* key used for xmit */
#define IEEE80211_KEY_RECV      0x02    /* key used for recv */
#ifndef __ubicom32__
#define IEEE80211_ADDR_EQ(a1,a2)        (OS_MEMCMP(a1, a2, IEEE80211_ADDR_LEN) == 0)
#else
#define IEEE80211_ADDR_EQ(a1,a2)        (OS_MACCMP(a1, a2) == 0)
#endif
#define IEEE80211_APPIE_MAX                  1024 /* max appie buffer size */
#define IEEE80211_KEY_GROUP     0x04    /* key used for WPA group operation */
#define IEEE80211_SCAN_MAX_SSID     10
#define IEEE80211_CHANINFO_MAX           1000 /* max Chaninfo buffer size */
#endif /* EXTERNAL_USE_ONLY */

 /*
  * Macros used for Tr069 objects
  */
#define TR069MAXPOWERRANGE 30
#define TR69MINTXPOWER 1
#define TR69MAX_RATE_POWER 63
#define TR69SCANSTATEVARIABLESIZE 20

/* Macro for user control table array */
#define MAX_USER_CTRL_TABLE_LEN 2048

/*
 * Max size of optional information elements.  We artificially
 * constrain this; it's limited only by the max frame size (and
 * the max parameter size of the wireless extensions).
 */
#define	IEEE80211_MAX_OPT_IE	512
#define	IEEE80211_MAX_WSC_IE	256

/*
 * WPA/RSN get/set key request.  Specify the key/cipher
 * type and whether the key is to be used for sending and/or
 * receiving.  The key index should be set only when working
 * with global keys (use IEEE80211_KEYIX_NONE for ``no index'').
 * Otherwise a unicast/pairwise key is specified by the bssid
 * (on a station) or mac address (on an ap).  They key length
 * must include any MIC key data; otherwise it should be no
 more than IEEE80211_KEYBUF_SIZE.
 */
struct ieee80211req_key {
	u_int8_t	ik_type;	/* key/cipher type */
	u_int8_t	ik_pad;
	u_int16_t	ik_keyix;	/* key index */
	u_int8_t	ik_keylen;	/* key length in bytes */
	u_int8_t	ik_flags;
/* NB: IEEE80211_KEY_XMIT and IEEE80211_KEY_RECV defined elsewhere */
#define	IEEE80211_KEY_DEFAULT	0x80	/* default xmit key */
	u_int8_t	ik_macaddr[IEEE80211_ADDR_LEN];
	u_int64_t	ik_keyrsc;	/* key receive sequence counter */
	u_int64_t	ik_keytsc;	/* key transmit sequence counter */
	u_int8_t	ik_keydata[IEEE80211_KEYBUF_SIZE+IEEE80211_MICBUF_SIZE];
} __packed;

/*
 * Delete a key either by index or address.  Set the index
 * to IEEE80211_KEYIX_NONE when deleting a unicast key.
 */
struct ieee80211req_del_key {
	u_int8_t	idk_keyix;	/* key index */
	u_int8_t	idk_macaddr[IEEE80211_ADDR_LEN];
};

/*
 * MLME state manipulation request.  IEEE80211_MLME_ASSOC
 * only makes sense when operating as a station.  The other
 * requests can be used when operating as a station or an
 * ap (to effect a station).
 */
struct ieee80211req_mlme {
	u_int8_t	im_op;		/* operation to perform */
#define	IEEE80211_MLME_ASSOC		1	/* associate station */
#define	IEEE80211_MLME_DISASSOC		2	/* disassociate station */
#define	IEEE80211_MLME_DEAUTH		3	/* deauthenticate station */
#define	IEEE80211_MLME_AUTHORIZE	4	/* authorize station */
#define	IEEE80211_MLME_UNAUTHORIZE	5	/* unauthorize station */
#define	IEEE80211_MLME_STOP_BSS		6	/* stop bss */
#define	IEEE80211_MLME_CLEAR_STATS	7	/* clear station statistic */
#define	IEEE80211_MLME_AUTH	        8	/* auth resp to station */
#define	IEEE80211_MLME_REASSOC	    9	/* reassoc to station */
#define	IEEE80211_MLME_AUTH_FILS    10	/* AUTH - when FILS enabled */
	u_int8_t	im_ssid_len;	/* length of optional ssid */
	u_int16_t	im_reason;	/* 802.11 reason code */
	u_int16_t	im_seq;	        /* seq for auth */
	u_int8_t	im_macaddr[IEEE80211_ADDR_LEN];
	u_int8_t	im_ssid[IEEE80211_NWID_LEN];
	u_int8_t        im_optie[IEEE80211_MAX_OPT_IE];
	u_int16_t       im_optie_len;
	struct      ieee80211req_fils_aad  fils_aad;
} __packed;

/*
 * request to add traffic stream for an associated station.
 */
struct ieee80211req_ts {
	u_int8_t    macaddr[IEEE80211_ADDR_LEN];
	u_int8_t    tspec_ie[IEEE80211_MAX_OPT_IE];
	u_int8_t    tspec_ielen;
	u_int8_t    res;
};

/*
 * Net802.11 scan request
 *
 */
enum {
    IEEE80211_SCANREQ_BG        = 1,    /*start the bg scan if vap is connected else fg scan */
    IEEE80211_SCANREQ_FORCE    = 2,    /*start the fg scan */
    IEEE80211_SCANREQ_STOP        = 3,    /*cancel any ongoing scanning*/
    IEEE80211_SCANREQ_PAUSE      = 4,    /*pause any ongoing scanning*/
    IEEE80211_SCANREQ_RESUME     = 5,    /*resume any ongoing scanning*/
};

/*
 * Set the active channel list.  Note this list is
 * intersected with the available channel list in
 * calculating the set of channels actually used in
 * scanning.
 */
struct ieee80211req_chanlist {
	u_int8_t	ic_channels[IEEE80211_CHAN_BYTES];
};

/*
 * Get the active channel list info.
 */
struct ieee80211req_chaninfo {
	u_int	ic_nchans;
	struct ieee80211_channel ic_chans[IEEE80211_CHAN_MAX];
};

/*
* Ressource request type from app
*/
enum {
    IEEE80211_RESREQ_ADDTS = 0,
    IEEE80211_RESREQ_ADDNODE,
};
/*
 * Resource request for adding Traffic stream
 */
struct ieee80211req_res_addts {
	u_int8_t	tspecie[IEEE80211_MAX_OPT_IE];
	u_int8_t	status;
};
/*
 * Resource request for adding station node
 */
struct ieee80211req_res_addnode {
	u_int8_t	auth_alg;
};
/*
 * Resource request from app
 */
struct ieee80211req_res {
	u_int8_t	macaddr[IEEE80211_ADDR_LEN];
	u_int8_t	type;
        union {
            struct ieee80211req_res_addts addts;
            struct ieee80211req_res_addnode addnode;
        } u;
};

/*
 * Retrieve the WPA/RSN information element for an associated station.
 */
struct ieee80211req_wpaie {
	u_int8_t	wpa_macaddr[IEEE80211_ADDR_LEN];
	u_int8_t	wpa_ie[IEEE80211_MAX_OPT_IE];
	u_int8_t    rsn_ie[IEEE80211_MAX_OPT_IE];
#ifdef ATH_WPS_IE
	u_int8_t    wps_ie[IEEE80211_MAX_OPT_IE];
#endif /* ATH_WPS_IE */
};

/*
 * Retrieve the WSC information element for an associated station.
 */
struct ieee80211req_wscie {
	u_int8_t	wsc_macaddr[IEEE80211_ADDR_LEN];
	u_int8_t	wsc_ie[IEEE80211_MAX_WSC_IE];
};


/*
 * Retrieve per-node statistics.
 */
struct ieee80211req_sta_stats {
	union {
		/* NB: explicitly force 64-bit alignment */
		u_int8_t	macaddr[IEEE80211_ADDR_LEN];
		u_int64_t	pad;
	} is_u;
	struct ieee80211_nodestats is_stats;
};

enum {
	IEEE80211_STA_OPMODE_NORMAL,
	IEEE80211_STA_OPMODE_XR
};

/*
 * Retrieve per-station information; to retrieve all
 * specify a mac address of ff:ff:ff:ff:ff:ff.
 */
struct ieee80211req_sta_req {
	union {
		/* NB: explicitly force 64-bit alignment */
		u_int8_t	macaddr[IEEE80211_ADDR_LEN];
		u_int64_t	pad;
	} is_u;
	struct ieee80211req_sta_info info[1];	/* variable length */
};

/*
 * Get/set per-station tx power cap.
 */
struct ieee80211req_sta_txpow {
	u_int8_t	it_macaddr[IEEE80211_ADDR_LEN];
	u_int8_t	it_txpow;
};

/*
 * WME parameters are set and return using i_val and i_len.
 * i_val holds the value itself.  i_len specifies the AC
 * and, as appropriate, then high bit specifies whether the
 * operation is to be applied to the BSS or ourself.
 */
#define	IEEE80211_WMEPARAM_SELF	0x0000		/* parameter applies to self */
#define	IEEE80211_WMEPARAM_BSS	0x8000		/* parameter applies to BSS */
#define	IEEE80211_WMEPARAM_VAL	0x7fff		/* parameter value */

/*
 * Scan result data returned for IEEE80211_IOC_SCAN_RESULTS.
 */
struct ieee80211req_scan_result {
	u_int16_t	isr_len;		/* length (mult of 4) */
	u_int16_t	isr_freq;		/* MHz */
	u_int32_t	isr_flags;		/* channel flags */
	u_int8_t	isr_noise;
	u_int8_t	isr_rssi;
	u_int8_t	isr_intval;		/* beacon interval */
	u_int16_t	isr_capinfo;		/* capabilities */
	u_int8_t	isr_erp;		/* ERP element */
	u_int8_t	isr_bssid[IEEE80211_ADDR_LEN];
	u_int8_t	isr_nrates;
	u_int8_t	isr_rates[IEEE80211_RATE_MAXSIZE];
	u_int8_t	isr_ssid_len;		/* SSID length */
	u_int16_t	isr_ie_len;		/* IE length */
	u_int8_t	isr_pad[4];
	/* variable length SSID followed by IE data */
};

/* Options for Mcast Enhancement */
enum {
		IEEE80211_ME_DISABLE =	0,
		IEEE80211_ME_TUNNELING =	1,
		IEEE80211_ME_TRANSLATE =	2
};

/*
 * athdbg request
 */
enum {
    IEEE80211_DBGREQ_SENDADDBA     =	0,
    IEEE80211_DBGREQ_SENDDELBA     =	1,
    IEEE80211_DBGREQ_SETADDBARESP  =	2,
    IEEE80211_DBGREQ_GETADDBASTATS =	3,
    IEEE80211_DBGREQ_SENDBCNRPT    =	4, /* beacon report request */
    IEEE80211_DBGREQ_SENDTSMRPT    =	5, /* traffic stream measurement report */
    IEEE80211_DBGREQ_SENDNEIGRPT   =	6, /* neigbor report */
    IEEE80211_DBGREQ_SENDLMREQ     =	7, /* link measurement request */
    IEEE80211_DBGREQ_SENDBSTMREQ   =	8, /* bss transition management request */
    IEEE80211_DBGREQ_SENDCHLOADREQ =    9, /* bss channel load  request */
    IEEE80211_DBGREQ_SENDSTASTATSREQ =  10, /* sta stats request */
    IEEE80211_DBGREQ_SENDNHIST     =    11, /* Noise histogram request */
    IEEE80211_DBGREQ_SENDDELTS     =	12, /* delete TSPEC */
    IEEE80211_DBGREQ_SENDADDTSREQ  =	13, /* add TSPEC */
    IEEE80211_DBGREQ_SENDLCIREQ    =    14, /* Location config info request */
    IEEE80211_DBGREQ_GETRRMSTATS   =    15, /* RRM stats */
    IEEE80211_DBGREQ_SENDFRMREQ    =    16, /* RRM Frame request */
    IEEE80211_DBGREQ_GETBCNRPT     =    17, /* GET BCN RPT */
    IEEE80211_DBGREQ_SENDSINGLEAMSDU=   18, /* Sends single VHT MPDU AMSDUs */
    IEEE80211_DBGREQ_GETRRSSI	   =	19, /* GET the Inst RSSI */
    IEEE80211_DBGREQ_GETACSREPORT  =	20, /* GET the ACS report */
    IEEE80211_DBGREQ_SETACSUSERCHANLIST  =    21, /* SET ch list for acs reporting  */
    IEEE80211_DBGREQ_GETACSUSERCHANLIST  =    22, /* GET ch list used in acs reporting */
    IEEE80211_DBGREQ_BLOCK_ACS_CHANNEL	 =    23, /* Block acs for these channels */
    IEEE80211_DBGREQ_TR069  	         =    24, /* to be used for tr069 */
    IEEE80211_DBGREQ_CHMASKPERSTA        =    25, /* to be used for chainmask per sta */
    IEEE80211_DBGREQ_FIPS		   = 26, /* to be used for setting fips*/
    IEEE80211_DBGREQ_FW_TEST	   = 27, /* to be used for firmware testing*/
    IEEE80211_DBGREQ_SETQOSMAPCONF       =    28, /* set QoS map configuration */
    IEEE80211_DBGREQ_BSTEERING_SET_PARAMS =   29, /* Set the static band steering parameters */
    IEEE80211_DBGREQ_BSTEERING_GET_PARAMS =   30, /* Get the static band steering parameters */
    IEEE80211_DBGREQ_BSTEERING_SET_DBG_PARAMS =   31, /* Set the band steering debugging parameters */
    IEEE80211_DBGREQ_BSTEERING_GET_DBG_PARAMS =   32, /* Get the band steering debugging parameters */
    IEEE80211_DBGREQ_BSTEERING_ENABLE         =   33, /* Enable/Disable band steering */
    IEEE80211_DBGREQ_BSTEERING_SET_OVERLOAD   =   34, /* SET overload status */
    IEEE80211_DBGREQ_BSTEERING_GET_OVERLOAD   =   35, /* GET overload status */
    IEEE80211_DBGREQ_BSTEERING_GET_RSSI       =   36, /* Request RSSI measurement */
    IEEE80211_DBGREQ_INITRTT3       = 37, /* to test RTT3 feature*/
    IEEE80211_DBGREQ_SET_ANTENNA_SWITCH       = 38, /* Dynamic Antenna Selection */
    IEEE80211_DBGREQ_SETSUSERCTRLTBL          = 39, /* set User defined control table*/
    IEEE80211_DBGREQ_OFFCHAN_TX               = 40, /* Offchan tx*/
    IEEE80211_DBGREQ_BSTEERING_SET_PROBE_RESP_WH  = 41,/* Control whether probe responses are withheld for a MAC */
    IEEE80211_DBGREQ_BSTEERING_GET_PROBE_RESP_WH  = 42,/* Query whether probe responses are withheld for a MAC */
    IEEE80211_DBGREQ_GET_RRM_STA_LIST             = 43, /* to get list of connected rrm capable station */
    /* bss transition management request, targetted to a particular AP (or set of APs) */
    IEEE80211_DBGREQ_SENDBSTMREQ_TARGET           = 44,
    /* Get data rate related info for a VAP or a client */
    IEEE80211_DBGREQ_BSTEERING_GET_DATARATE_INFO  = 45,
    /* Enable/Disable band steering events on a VAP */
    IEEE80211_DBGREQ_BSTEERING_ENABLE_EVENTS      = 46,
#if QCA_LTEU_SUPPORT
    IEEE80211_DBGREQ_MU_SCAN                      = 47, /* do a MU scan */
    IEEE80211_DBGREQ_LTEU_CFG                     = 48, /* LTEu specific configuration */
    IEEE80211_DBGREQ_AP_SCAN                      = 49, /* do a AP scan */
#endif
    IEEE80211_DBGREQ_ATF_DEBUG_SIZE               = 50, /* Set the ATF history size */
    IEEE80211_DBGREQ_ATF_DUMP_DEBUG               = 51, /* Dump the ATF history */
#if QCA_LTEU_SUPPORT
    IEEE80211_DBGREQ_SCAN_REPEAT_PROBE_TIME       = 52, /* scan probe time, part of scan params */
    IEEE80211_DBGREQ_SCAN_REST_TIME               = 53, /* scan rest time, part of scan params */
    IEEE80211_DBGREQ_SCAN_IDLE_TIME               = 54, /* scan idle time, part of scan params */
    IEEE80211_DBGREQ_SCAN_PROBE_DELAY             = 55, /* scan probe delay, part of scan params */
    IEEE80211_DBGREQ_MU_DELAY                     = 56, /* delay between channel change and MU start (for non-gpio) */
    IEEE80211_DBGREQ_WIFI_TX_POWER                = 57, /* assumed tx power of wifi sta */
#endif
    /* Cleanup all STA state (equivalent to disassociation, without sending the frame OTA) */
    IEEE80211_DBGREQ_BSTEERING_LOCAL_DISASSOCIATION = 58,
    IEEE80211_DBGREQ_BSTEERING_SET_STEERING       = 59, /* Set steering in progress flag for a STA */
    IEEE80211_DBGREQ_CHAN_LIST                    =60,
    IEEE80211_DBGREQ_MBO_BSSIDPREF                = 61,
#if UMAC_SUPPORT_VI_DBG
    IEEE80211_DBGREQ_VOW_DEBUG_PARAM        	  = 62,
    IEEE80211_DBGREQ_VOW_DEBUG_PARAM_PERSTREAM	  = 63,
#endif
#if QCA_LTEU_SUPPORT
    IEEE80211_DBGREQ_SCAN_PROBE_SPACE_INTERVAL     = 64,
#endif
    IEEE80211_DBGREQ_ASSOC_WATERMARK_TIME         = 65,  /* Get the date when the max number of devices has been associated crossing the threshold */
    IEEE80211_DBGREQ_DISPLAY_TRAFFIC_STATISTICS   = 66, /* Display the traffic statistics of each connected STA */
    IEEE80211_DBGREQ_ATF_DUMP_NODESTATE           = 67,
    IEEE80211_DBGREQ_BSTEERING_SET_DA_STAT_INTVL  = 68,
    IEEE80211_DBGREQ_BSTEERING_SET_AUTH_ALLOW     = 69,
    IEEE80211_DBGREQ_BSTEERING_SET_PROBE_RESP_ALLOW_24G = 70, /* Control whether probe responses are allowed for a MAC in 2.4g band */
    IEEE80211_DBGREQ_SETINNETWORK_2G              = 71, /*set 2.4G innetwork inforamtion to acs module*/
    IEEE80211_DBGREQ_GETINNETWORK_2G              = 72, /*get 2.4G innetwork inforamtion from acs module*/
    IEEE80211_DBGREQ_SET_SOFTBLOCKING             = 73, /* set softblocking flag of a STA */
    IEEE80211_DBGREQ_GET_SOFTBLOCKING             = 74, /* get softblocking flag of a STA */
#if ATH_SUPPORT_PRIMARY_ALLOWED_CHAN
    IEEE80211_DBGREQ_SETPRIMARY_ALLOWED_CHANLIST  = 75, /* set primary allowed channel list */
    IEEE80211_DBGREQ_GETPRIMARY_ALLOWED_CHANLIST  = 76, /* get primary allowed channel list */
#endif
    IEEE80211_DBGREQ_TR181                        = 77, /* TR181 Spec related IOCTLs */
};

typedef struct ieee80211req_acs_r{
    u_int32_t index;
    u_int32_t data_size;
    void *data_addr;
}ieee80211req_acs_t;

typedef struct ieee80211_user_chanlist_r {
    u_int8_t  n_chan;
    u_int8_t *chan;
} ieee80211_user_chanlist_t;

#if ATH_SUPPORT_PRIMARY_ALLOWED_CHAN
typedef struct ieee80211_primary_allowed_chanlist {
    u_int8_t n_chan;
    u_int8_t *chan;
} ieee80211_primary_allowed_chanlist_t;
#endif

typedef struct ieee80211_offchan_tx_test {
    u_int8_t ieee_chan;
    u_int16_t dwell_time;
} ieee80211_offchan_tx_test_t;

#if UMAC_SUPPORT_VI_DBG
typedef struct ieee80211_vow_dbg_stream_param {
	u_int8_t  stream_num;         /* the stream number whose markers are being set */
	u_int8_t  marker_num;         /* the marker number whose parameters (offset, size & match) are being set */
	u_int32_t marker_offset;      /* byte offset from skb start (upper 16 bits) & size in bytes(lower 16 bits) */
	u_int32_t marker_match;       /* marker pattern match used in filtering */
} ieee80211_vow_dbg_stream_param_t;

typedef struct ieee80211_vow_dbg_param {
	u_int8_t  num_stream;        /* Number of streams */
	u_int8_t  num_marker;       /* total number of markers used to filter pkts */
	u_int32_t rxq_offset;      /* Rx Seq num offset skb start (upper 16 bits) & size in bytes(lower 16 bits) */
	u_int32_t rxq_shift;         /* right-shift value in case field is not word aligned */
	u_int32_t rxq_max;           /* Max Rx seq number */
	u_int32_t time_offset;       /* Time offset for the packet*/
} ieee80211_vow_dbg_param_t;
#endif

typedef struct ieee80211_rrm_sta_info {
    u_int16_t count; /* In application layer this variable is used to store the STA count and in the driver it is used as an index */
    u_int8_t *dest_addr;
}ieee80211_rrm_sta_info_t;

typedef struct ieee80211_noise_stats{
    u_int8_t noise_value;
    u_int8_t min_value;
    u_int8_t max_value;
    u_int8_t median_value;
}ieee80211_noise_stats_t;

typedef struct ieee80211_node_info {
    u_int16_t count;
    u_int16_t bin_number;
    u_int32_t traf_rate;
    u_int8_t *dest_addr;
    struct ieee80211_noise_stats *noise_stats;
}ieee80211_node_info_t;

/* User defined control table for calibrated data */

typedef struct ieee80211_user_ctrl_tbl_r {
    u_int16_t ctrl_len;
    u_int8_t *ctrl_array;
} ieee80211_user_ctrl_tbl_t;
/*
 * command id's for use in tr069 request
 */
typedef enum _ieee80211_tr069_cmd_ {
    TR069_CHANHIST           = 1,
    TR069_TXPOWER            = 2,
    TR069_GETTXPOWER         = 3,
    TR069_GUARDINTV          = 4,
    TR069_GET_GUARDINTV      = 5,
    TR069_GETASSOCSTA_CNT    = 6,
    TR069_GETTIMESTAMP       = 7,
    TR069_GETDIAGNOSTICSTATE = 8,
    TR069_GETNUMBEROFENTRIES = 9,
    TR069_GET11HSUPPORTED    = 10,
    TR069_GETPOWERRANGE      = 11,
    TR069_SET_OPER_RATE      = 12,
    TR069_GET_OPER_RATE      = 13,
    TR069_GET_POSIBLRATE     = 14,
    TR069_SET_BSRATE         = 15,
    TR069_GET_BSRATE         = 16,
    TR069_GETSUPPORTEDFREQUENCY  = 17,
    TR069_GET_PLCP_ERR_CNT   = 18,
    TR069_GET_FCS_ERR_CNT    = 19,
    TR069_GET_PKTS_OTHER_RCVD = 20,
    TR069_GET_FAIL_RETRANS_CNT = 21,
    TR069_GET_RETRY_CNT      = 22,
    TR069_GET_MUL_RETRY_CNT  = 23,
    TR069_GET_ACK_FAIL_CNT   = 24,
    TR069_GET_AGGR_PKT_CNT   = 25,
    TR069_GET_STA_BYTES_SENT = 26,
    TR069_GET_STA_BYTES_RCVD = 27,
    TR069_GET_DATA_SENT_ACK  = 28,
    TR069_GET_DATA_SENT_NOACK = 29,
    TR069_GET_CHAN_UTIL      = 30,
    TR069_GET_RETRANS_CNT    = 31,
}ieee80211_tr069_cmd;

typedef enum _ieee80211_tr181_cmd_ {
    TR181_GET_ACL_MODE          = 1,
    TR181_PUSH_RADIO_CHANNEL2   = 2,
    TR181_SET_CSA_DEAUTH_MODE   = 3,
    TR181_SET_FILTER_SSID       = 4,
    TR181_GET_LAST_BEACON_RSSI  = 5,
    TR181_GET_LAST_ACK_RSSI     = 6,
}ieee80211_tr181_cmd;

typedef struct {
	u_int32_t value;
	int value_array[TR069MAXPOWERRANGE];
}ieee80211_tr069_txpower_range;

typedef struct{
    u_int8_t         chanid;
    struct timespec chan_time;
}ieee80211_chanlhist_t;

typedef struct{
    u_int8_t act_index;
    ieee80211_chanlhist_t chanlhist[IEEE80211_CHAN_MAXHIST+1];
}ieee80211_channelhist_t;

/*
 * common structure to handle tr069 commands;
 * the cmdid and data pointer has to be appropriately
 * filled in
 */
typedef struct{
    u_int32_t data_size;
    ieee80211_tr069_cmd cmdid;
    void *data_addr;
}ieee80211req_tr069_t;

typedef struct{
    u_int32_t data_size;
    ieee80211_tr181_cmd cmdid;
    void *data_addr;
}ieee80211req_tr181_t;


typedef struct ieee80211req_fips {
	u_int32_t data_size;
  	void *data_addr;
}ieee80211req_fips_t;

#if QCA_LTEU_SUPPORT

typedef enum {
    MU_ALGO_1 = 0x1, /* Basic binning algo */
    MU_ALGO_2 = 0x2, /* Enhanced binning algo */
    MU_ALGO_3 = 0x4, /* Enhanced binning including accounting for hidden nodes */
    MU_ALGO_4 = 0x8, /* TA based MU calculation */
} mu_algo_t;

typedef struct {
    u_int8_t     mu_req_id;             /* MU request id */
    u_int8_t     mu_channel;            /* IEEE channel number on which to do MU scan */
    mu_algo_t    mu_type;               /* which MU algo to use */
    u_int32_t    mu_duration;           /* duration of the scan in ms */
    u_int32_t    lteu_tx_power;         /* LTEu Tx power */
    u_int32_t    mu_rssi_thr_bssid;     /* RSSI threshold to account for active APs */
    u_int32_t    mu_rssi_thr_sta;       /* RSSI threshold to account for active STAs */
    u_int32_t    mu_rssi_thr_sc;        /* RSSI threshold to account for active small cells */
    u_int32_t    home_plmnid;           /* to be compared with PLMN ID to distinguish same and different operator WCUBS */
    u_int32_t    alpha_num_bssid;       /* alpha for num active bssid calculation,kept for backward compatibility */
} ieee80211req_mu_scan_t;

#define LTEU_MAX_BINS        10

typedef struct {
    u_int8_t     lteu_gpio_start;        /* start MU/AP scan after GPIO toggle */
    u_int8_t     lteu_num_bins;          /* no. of elements in the following arrays */
    u_int8_t     use_actual_nf;          /* whether to use the actual NF obtained or a hardcoded one */
    u_int32_t    lteu_weight[LTEU_MAX_BINS];  /* weights for MU algo */
    u_int32_t    lteu_thresh[LTEU_MAX_BINS];  /* thresholds for MU algo */
    u_int32_t    lteu_gamma[LTEU_MAX_BINS];   /* gamma's for MU algo */
    u_int32_t    lteu_scan_timeout;      /* timeout in ms to gpio toggle */
    u_int32_t    alpha_num_bssid;      /* alpha for num active bssid calculation */
    u_int32_t    lteu_cfg_reserved_1;    /* used to indicate to fw whether or not packets with phy error are to
                                            be included in MU calculation or not */

} ieee80211req_lteu_cfg_t;

#define MAX_SCAN_CHANS       32

typedef enum {
    SCAN_PASSIVE,
    SCAN_ACTIVE,
} scan_type_t;

typedef struct {
    u_int8_t     scan_req_id;          /* AP scan request id */
    u_int8_t     scan_num_chan;        /* Number of channels to scan, 0 for all channels */
    u_int8_t     scan_channel_list[MAX_SCAN_CHANS]; /* IEEE channel number of channels to scan */
    scan_type_t  scan_type;            /* Scan type - active or passive */
    u_int32_t    scan_duration;        /* Duration in ms for which a channel is scanned, 0 for default */
    u_int32_t    scan_repeat_probe_time;   /* Time before sending second probe request, (u32)(-1) for default */
    u_int32_t    scan_rest_time;       /* Time in ms on the BSS channel, (u32)(-1) for default */
    u_int32_t    scan_idle_time;       /* Time in msec on BSS channel before switching channel, (u32)(-1) for default */
    u_int32_t    scan_probe_delay;     /* Delay in msec before sending probe request, (u32)(-1) for default */
} ieee80211req_ap_scan_t;



#endif /* QCA_LTEU_SUPPORT */

#define MAX_CUSTOM_CHANS     101

typedef struct {
    u_int8_t     scan_numchan_associated;        /* Number of channels to scan, 0 for all channels */
    u_int8_t     scan_numchan_nonassociated;
    u_int8_t     scan_channel_list_associated[MAX_CUSTOM_CHANS]; /* IEEE channel number of channels to scan */
    u_int8_t     scan_channel_list_nonassociated[MAX_CUSTOM_CHANS];
}ieee80211req_custom_chan_t;

#if QCA_AIRTIME_FAIRNESS
struct atf_stats {
    u_int32_t tokens;               /* tokens distributed by strictq/fairq */
    u_int32_t act_tokens;           /* tokens available, after adjustemnt of excess consumed in prev cycle */
    u_int32_t total;                /* total tokens distributed by strictq/fairq */
    u_int32_t contribution;         /* tokens contributed by this node */
    u_int32_t tot_contribution;     /* tokens contributed by all nodes */
    u_int32_t borrow;               /* tokens borrowed by this node */
    u_int32_t unused;               /* tokens not used */
    u_int32_t pkt_drop_nobuf;       /* packets dropped as node is already holding it's share of tx buffers */
    u_int16_t allowed_bufs;         /* max tx buffers that this node can hold */
    u_int16_t max_num_buf_held;     /* max tx buffers held by this node */
    u_int16_t min_num_buf_held;     /* min tx buffers held by this node */
    u_int16_t num_tx_bufs;          /* packets sent for this node */
    u_int32_t num_tx_bytes;         /* bytes sent for this node */
    u_int32_t tokens_common;        /* tokens distributed by strictq/fairq (for non-atf nodes) */
    u_int32_t act_tokens_common;    /* tokens available, after adjustemnt of excess consumed in prev cycle (for non-atf nodes) */
    u_int32_t timestamp;            /* time when stats are updated */
    u_int32_t weighted_unusedtokens_percent; /* weighted unused tokens percent */
    u_int32_t raw_tx_tokens;        /* raw tokens */
    u_int32_t throughput;           /* attainable throughput assuming 100% airtime */
    u_int64_t total_used_tokens;    /* total of used tokens */
};

typedef struct {
    void *ptr;
    u_int32_t size;
} ieee80211req_atf_debug_t;
#endif


struct ieee80211req_athdbg {
    u_int8_t cmd;
    u_int8_t dstmac[IEEE80211_ADDR_LEN];
    union {
        u_long param[4];
        ieee80211_rrm_beaconreq_info_t bcnrpt;
        ieee80211_rrm_tsmreq_info_t    tsmrpt;
        ieee80211_rrm_nrreq_info_t     neigrpt;
        struct ieee80211_bstm_reqinfo   bstmreq;
        struct ieee80211_bstm_reqinfo_target   bstmreq_target;
        struct ieee80211_user_bssid_pref bssidpref;
        ieee80211_tspec_info     tsinfo;
        ieee80211_rrm_chloadreq_info_t chloadrpt;
        ieee80211_rrm_stastats_info_t  stastats;
        ieee80211_rrm_nhist_info_t     nhist;
        ieee80211_rrm_frame_req_info_t frm_req;
        ieee80211_rrm_lcireq_info_t    lci_req;
        ieee80211req_rrmstats_t        rrmstats_req;
        ieee80211req_acs_t             acs_rep;
        ieee80211req_tr069_t           tr069_req;
        ieee80211req_tr181_t           tr181_req;
        ieee80211req_fips_t fips_req;
        struct ieee80211_qos_map       qos_map;
        ieee80211_bsteering_param_t    bsteering_param;
        ieee80211_bsteering_dbg_param_t bsteering_dbg_param;
        ieee80211_bsteering_rssi_req_t bsteering_rssi_req;
        u_int8_t                       bsteering_probe_resp_wh;
        u_int8_t                       bsteering_auth_allow;
        u_int8_t bsteering_enable;
        u_int8_t bsteering_overload;
        u_int8_t bsteering_rssi_num_samples;
        ieee80211_bsteering_datarate_info_t bsteering_datarate_info;
        u_int8_t bsteering_steering_in_progress;
        ieee80211_offchan_tx_test_t offchan_req;
#if UMAC_SUPPORT_VI_DBG
	ieee80211_vow_dbg_stream_param_t   vow_dbg_stream_param;
	ieee80211_vow_dbg_param_t	   vow_dbg_param;
#endif

#if QCA_LTEU_SUPPORT
        ieee80211req_mu_scan_t         mu_scan_req;
        ieee80211req_lteu_cfg_t        lteu_cfg;
        ieee80211req_ap_scan_t         ap_scan_req;
#endif
        ieee80211req_custom_chan_t     custom_chan_req;
#if QCA_AIRTIME_FAIRNESS
        ieee80211req_atf_debug_t       atf_dbg_req;
#endif
        u_int32_t                      bsteering_sta_stats_update_interval_da;
        u_int8_t                       bsteering_probe_resp_allow_24g;
#if ATH_ACL_SOFTBLOCKING
        u_int8_t                       acl_softblocking;
#endif
    } data;
} __packed;

#ifdef __linux__
/*
 * Wireless Extensions API, private ioctl interfaces.
 *
 * NB: Even-numbered ioctl numbers have set semantics and are privileged!
 *	(regardless of the incorrect comment in wireless.h!)
 *
 *	Note we can only use 32 private ioctls, and yes they are all claimed.
 */
#ifndef _NET_IF_H
#include <linux/if.h>
#endif
#define	IEEE80211_IOCTL_SETPARAM	(SIOCIWFIRSTPRIV+0)
#define	IEEE80211_IOCTL_GETPARAM	(SIOCIWFIRSTPRIV+1)
#define	IEEE80211_IOCTL_SETKEY		(SIOCIWFIRSTPRIV+2)
#define	IEEE80211_IOCTL_SETWMMPARAMS	(SIOCIWFIRSTPRIV+3)
#define	IEEE80211_IOCTL_DELKEY		(SIOCIWFIRSTPRIV+4)
#define	IEEE80211_IOCTL_GETWMMPARAMS	(SIOCIWFIRSTPRIV+5)
#define	IEEE80211_IOCTL_SETMLME		(SIOCIWFIRSTPRIV+6)
#define	IEEE80211_IOCTL_GETCHANINFO	(SIOCIWFIRSTPRIV+7)
#define	IEEE80211_IOCTL_SETOPTIE	(SIOCIWFIRSTPRIV+8)
#define	IEEE80211_IOCTL_GETOPTIE	(SIOCIWFIRSTPRIV+9)
#define	IEEE80211_IOCTL_ADDMAC		(SIOCIWFIRSTPRIV+10)        /* Add ACL MAC Address */
#define	IEEE80211_IOCTL_DELMAC		(SIOCIWFIRSTPRIV+12)        /* Del ACL MAC Address */
#define	IEEE80211_IOCTL_GETCHANLIST	(SIOCIWFIRSTPRIV+13)
#define	IEEE80211_IOCTL_SETCHANLIST	(SIOCIWFIRSTPRIV+14)
#define IEEE80211_IOCTL_KICKMAC		(SIOCIWFIRSTPRIV+15)
#define	IEEE80211_IOCTL_CHANSWITCH	(SIOCIWFIRSTPRIV+16)
#define	IEEE80211_IOCTL_GETMODE		(SIOCIWFIRSTPRIV+17)
#define	IEEE80211_IOCTL_SETMODE		(SIOCIWFIRSTPRIV+18)
#define IEEE80211_IOCTL_GET_APPIEBUF	(SIOCIWFIRSTPRIV+19)
#define IEEE80211_IOCTL_SET_APPIEBUF	(SIOCIWFIRSTPRIV+20)
#define IEEE80211_IOCTL_SET_ACPARAMS	(SIOCIWFIRSTPRIV+21)
#define IEEE80211_IOCTL_FILTERFRAME	(SIOCIWFIRSTPRIV+22)
#define IEEE80211_IOCTL_SET_RTPARAMS	(SIOCIWFIRSTPRIV+23)
#define IEEE80211_IOCTL_DBGREQ	        (SIOCIWFIRSTPRIV+24)
#define IEEE80211_IOCTL_SEND_MGMT	(SIOCIWFIRSTPRIV+26)
#define IEEE80211_IOCTL_SET_MEDENYENTRY (SIOCIWFIRSTPRIV+27)
#define IEEE80211_IOCTL_CHN_WIDTHSWITCH (SIOCIWFIRSTPRIV+28)
#define IEEE80211_IOCTL_GET_MACADDR	(SIOCIWFIRSTPRIV+29)        /* Get ACL List */
#define IEEE80211_IOCTL_SET_HBRPARAMS	(SIOCIWFIRSTPRIV+30)
#define IEEE80211_IOCTL_SET_RXTIMEOUT	(SIOCIWFIRSTPRIV+31)
/*
 * MCAST_GROUP is used for testing, not for regular operation.
 * It is defined unconditionally (overlapping with SET_RXTIMEOUT),
 * but only used for debugging (after disabling SET_RXTIMEOUT).
 */
#define IEEE80211_IOCTL_MCAST_GROUP     (SIOCIWFIRSTPRIV+31)

#define CURR_MODE 0 /* used to get the curret mode of operation*/
#define PHY_MODE 1  /* used to get the desired phymode */

enum {
	IEEE80211_WMMPARAMS_CWMIN	= 1,
	IEEE80211_WMMPARAMS_CWMAX	= 2,
	IEEE80211_WMMPARAMS_AIFS	= 3,
	IEEE80211_WMMPARAMS_TXOPLIMIT	= 4,
	IEEE80211_WMMPARAMS_ACM		= 5,
	IEEE80211_WMMPARAMS_NOACKPOLICY	= 6,
#if UMAC_VOW_DEBUG
    IEEE80211_PARAM_VOW_DBG_CFG     = 7,  /*Configure VoW debug MACs*/
#endif
};
enum {
	IEEE80211_IOCTL_RCPARAMS_RTPARAM	= 1,
	IEEE80211_IOCTL_RCPARAMS_RTMASK		= 2,
};
enum {
	IEEE80211_PARAM_TURBO		= 1,	/* turbo mode */
	IEEE80211_PARAM_MODE		= 2,	/* phy mode (11a, 11b, etc.) */
	IEEE80211_PARAM_AUTHMODE	= 3,	/* authentication mode */
	IEEE80211_PARAM_PROTMODE	= 4,	/* 802.11g protection */
	IEEE80211_PARAM_MCASTCIPHER	= 5,	/* multicast/default cipher */
	IEEE80211_PARAM_MCASTKEYLEN	= 6,	/* multicast key length */
	IEEE80211_PARAM_UCASTCIPHERS	= 7,	/* unicast cipher suites */
	IEEE80211_PARAM_UCASTCIPHER	= 8,	/* unicast cipher */
	IEEE80211_PARAM_UCASTKEYLEN	= 9,	/* unicast key length */
	IEEE80211_PARAM_WPA		= 10,	/* WPA mode (0,1,2) */
	IEEE80211_PARAM_ROAMING		= 12,	/* roaming mode */
	IEEE80211_PARAM_PRIVACY		= 13,	/* privacy invoked */
	IEEE80211_PARAM_COUNTERMEASURES	= 14,	/* WPA/TKIP countermeasures */
	IEEE80211_PARAM_DROPUNENCRYPTED	= 15,	/* discard unencrypted frames */
	IEEE80211_PARAM_DRIVER_CAPS	= 16,	/* driver capabilities */
	IEEE80211_PARAM_MACCMD		= 17,	/* MAC ACL operation */
	IEEE80211_PARAM_WMM		= 18,	/* WMM mode (on, off) */
	IEEE80211_PARAM_HIDESSID	= 19,	/* hide SSID mode (on, off) */
	IEEE80211_PARAM_APBRIDGE	= 20,	/* AP inter-sta bridging */
	IEEE80211_PARAM_KEYMGTALGS	= 21,	/* key management algorithms */
	IEEE80211_PARAM_RSNCAPS		= 22,	/* RSN capabilities */
	IEEE80211_PARAM_INACT		= 23,	/* station inactivity timeout */
	IEEE80211_PARAM_INACT_AUTH	= 24,	/* station auth inact timeout */
	IEEE80211_PARAM_INACT_INIT	= 25,	/* station init inact timeout */
	IEEE80211_PARAM_DTIM_PERIOD	= 28,	/* DTIM period (beacons) */
	IEEE80211_PARAM_BEACON_INTERVAL	= 29,	/* beacon interval (ms) */
	IEEE80211_PARAM_DOTH		= 30,	/* 11.h is on/off */
	IEEE80211_PARAM_PWRTARGET	= 31,	/* Current Channel Pwr Constraint */
	IEEE80211_PARAM_GENREASSOC	= 32,	/* Generate a reassociation request */
	IEEE80211_PARAM_COMPRESSION	= 33,	/* compression */
	IEEE80211_PARAM_FF		= 34,	/* fast frames support */
	IEEE80211_PARAM_XR		= 35,	/* XR support */
	IEEE80211_PARAM_BURST		= 36,	/* burst mode */
	IEEE80211_PARAM_PUREG		= 37,	/* pure 11g (no 11b stations) */
	IEEE80211_PARAM_AR		= 38,	/* AR support */
	IEEE80211_PARAM_WDS		= 39,	/* Enable 4 address processing */
	IEEE80211_PARAM_BGSCAN		= 40,	/* bg scanning (on, off) */
	IEEE80211_PARAM_BGSCAN_IDLE	= 41,	/* bg scan idle threshold */
	IEEE80211_PARAM_BGSCAN_INTERVAL	= 42,	/* bg scan interval */
	IEEE80211_PARAM_MCAST_RATE	= 43,	/* Multicast Tx Rate */
	IEEE80211_PARAM_COVERAGE_CLASS	= 44,	/* coverage class */
	IEEE80211_PARAM_COUNTRY_IE	= 45,	/* enable country IE */
	IEEE80211_PARAM_SCANVALID	= 46,	/* scan cache valid threshold */
	IEEE80211_PARAM_ROAM_RSSI_11A	= 47,	/* rssi threshold in 11a */
	IEEE80211_PARAM_ROAM_RSSI_11B	= 48,	/* rssi threshold in 11b */
	IEEE80211_PARAM_ROAM_RSSI_11G	= 49,	/* rssi threshold in 11g */
	IEEE80211_PARAM_ROAM_RATE_11A	= 50,	/* tx rate threshold in 11a */
	IEEE80211_PARAM_ROAM_RATE_11B	= 51,	/* tx rate threshold in 11b */
	IEEE80211_PARAM_ROAM_RATE_11G	= 52,	/* tx rate threshold in 11g */
	IEEE80211_PARAM_UAPSDINFO	= 53,	/* value for qos info field */
	IEEE80211_PARAM_SLEEP		= 54,	/* force sleep/wake */
	IEEE80211_PARAM_QOSNULL		= 55,	/* force sleep/wake */
	IEEE80211_PARAM_PSPOLL		= 56,	/* force ps-poll generation (sta only) */
	IEEE80211_PARAM_EOSPDROP	= 57,	/* force uapsd EOSP drop (ap only) */
	IEEE80211_PARAM_MARKDFS		= 58,	/* mark a dfs interference channel when found */
	IEEE80211_PARAM_REGCLASS	= 59,	/* enable regclass ids in country IE */
	IEEE80211_PARAM_CHANBW		= 60,	/* set chan bandwidth preference */
	IEEE80211_PARAM_WMM_AGGRMODE	= 61,	/* set WMM Aggressive Mode */
	IEEE80211_PARAM_SHORTPREAMBLE	= 62, 	/* enable/disable short Preamble */
	IEEE80211_PARAM_BLOCKDFSCHAN	= 63, 	/* enable/disable use of DFS channels */
	IEEE80211_PARAM_CWM_MODE	= 64,	/* CWM mode */
	IEEE80211_PARAM_CWM_EXTOFFSET	= 65,	/* CWM extension channel offset */
	IEEE80211_PARAM_CWM_EXTPROTMODE	= 66,	/* CWM extension channel protection mode */
	IEEE80211_PARAM_CWM_EXTPROTSPACING = 67,/* CWM extension channel protection spacing */
	IEEE80211_PARAM_CWM_ENABLE	= 68,/* CWM state machine enabled */
	IEEE80211_PARAM_CWM_EXTBUSYTHRESHOLD = 69,/* CWM extension channel busy threshold */
	IEEE80211_PARAM_CWM_CHWIDTH	= 70,	/* CWM STATE: current channel width */
	IEEE80211_PARAM_SHORT_GI	= 71,	/* half GI */
	IEEE80211_PARAM_FAST_CC		= 72,	/* fast channel change */

	/*
	 * 11n A-MPDU, A-MSDU support
	 */
	IEEE80211_PARAM_AMPDU		= 73,	/* 11n a-mpdu support */
	IEEE80211_PARAM_AMPDU_LIMIT	= 74,	/* a-mpdu length limit */
	IEEE80211_PARAM_AMPDU_DENSITY	= 75,	/* a-mpdu density */
	IEEE80211_PARAM_AMPDU_SUBFRAMES	= 76,	/* a-mpdu subframe limit */
	IEEE80211_PARAM_AMSDU		= 77,	/* a-msdu support */
	IEEE80211_PARAM_AMSDU_LIMIT	= 78,	/* a-msdu length limit */

	IEEE80211_PARAM_COUNTRYCODE	= 79,	/* Get country code */
	IEEE80211_PARAM_TX_CHAINMASK	= 80,	/* Tx chain mask */
	IEEE80211_PARAM_RX_CHAINMASK	= 81,	/* Rx chain mask */
	IEEE80211_PARAM_RTSCTS_RATECODE	= 82,	/* RTS Rate code */
	IEEE80211_PARAM_HT_PROTECTION	= 83,	/* Protect traffic in HT mode */
	IEEE80211_PARAM_RESET_ONCE	= 84,	/* Force a reset */
	IEEE80211_PARAM_SETADDBAOPER	= 85,	/* Set ADDBA mode */
	IEEE80211_PARAM_TX_CHAINMASK_LEGACY = 86, /* Tx chain mask for legacy clients */
	IEEE80211_PARAM_11N_RATE	= 87,	/* Set ADDBA mode */
	IEEE80211_PARAM_11N_RETRIES	= 88,	/* Tx chain mask for legacy clients */
	IEEE80211_PARAM_DBG_LVL		= 89,	/* Debug Level for specific VAP */
	IEEE80211_PARAM_WDS_AUTODETECT	= 90,	/* Configurable Auto Detect/Delba for WDS mode */
	IEEE80211_PARAM_ATH_RADIO	= 91,	/* returns the name of the radio being used */
	IEEE80211_PARAM_IGNORE_11DBEACON = 92,	/* Don't process 11d beacon (on, off) */
	IEEE80211_PARAM_STA_FORWARD	= 93,	/* Enable client 3 addr forwarding */

	/*
	 * Mcast Enhancement support
	 */
	IEEE80211_PARAM_ME          = 94,   /* Set Mcast enhancement option: 0 disable, 1 tunneling, 2 translate  4 to disable snoop feature*/
	IEEE80211_PARAM_MEDUMP		= 95,	/* Dump the snoop table for mcast enhancement */
	IEEE80211_PARAM_MEDEBUG		= 96,	/* mcast enhancement debug level */
	IEEE80211_PARAM_ME_SNOOPLENGTH	= 97,	/* mcast snoop list length */
	IEEE80211_PARAM_ME_TIMEOUT	= 99,	/* Set Mcast enhancement timeout for STA's without traffic, in msec */
	IEEE80211_PARAM_PUREN		= 100,	/* pure 11n (no 11bg/11a stations) */
	IEEE80211_PARAM_BASICRATES	= 101,	/* Change Basic Rates */
	IEEE80211_PARAM_NO_EDGE_CH	= 102,	/* Avoid band edge channels */
	IEEE80211_PARAM_WEP_TKIP_HT	= 103,	/* Enable HT rates with WEP/TKIP encryption */
	IEEE80211_PARAM_RADIO		= 104,	/* radio on/off */
	IEEE80211_PARAM_NETWORK_SLEEP	= 105,	/* set network sleep enable/disable */
	IEEE80211_PARAM_DROPUNENC_EAPOL	= 106,

	/*
	 * Headline block removal
	 */
	IEEE80211_PARAM_HBR_TIMER	= 107,
	IEEE80211_PARAM_HBR_STATE	= 108,

	/*
	 * Unassociated power consumpion improve
	 */
	IEEE80211_PARAM_SLEEP_PRE_SCAN	= 109,
	IEEE80211_PARAM_SCAN_PRE_SLEEP	= 110,

	/* support for wapi: set auth mode and key */
	IEEE80211_PARAM_SETWAPI		= 112,
	IEEE80211_IOCTL_GREEN_AP_PS_ENABLE = 113,
	IEEE80211_IOCTL_GREEN_AP_PS_TIMEOUT = 114,
	IEEE80211_IOCTL_GREEN_AP_PS_ON_TIME = 115,
	IEEE80211_PARAM_WPS		= 116,
	IEEE80211_PARAM_RX_RATE		= 117,
	IEEE80211_PARAM_CHEXTOFFSET	= 118,
	IEEE80211_PARAM_CHSCANINIT	= 119,
	IEEE80211_PARAM_MPDU_SPACING	= 120,
	IEEE80211_PARAM_HT40_INTOLERANT	= 121,
	IEEE80211_PARAM_CHWIDTH		= 122,
	IEEE80211_PARAM_EXTAP		= 123,   /* Enable client 3 addr forwarding */
        IEEE80211_PARAM_COEXT_DISABLE    = 124,
	IEEE80211_PARAM_ME_DROPMCAST	= 125,	/* drop mcast if empty entry */
	IEEE80211_PARAM_ME_SHOWDENY	= 126,	/* show deny table for mcast enhancement */
	IEEE80211_PARAM_ME_CLEARDENY	= 127,	/* clear deny table for mcast enhancement */
	IEEE80211_PARAM_ME_ADDDENY	= 128,	/* add deny entry for mcast enhancement */
    IEEE80211_PARAM_GETIQUECONFIG = 129, /*print out the iQUE config*/
    IEEE80211_PARAM_CCMPSW_ENCDEC = 130,  /* support for ccmp s/w encrypt decrypt */

      /* Support for repeater placement */
    IEEE80211_PARAM_CUSTPROTO_ENABLE = 131,
    IEEE80211_PARAM_GPUTCALC_ENABLE  = 132,
    IEEE80211_PARAM_DEVUP            = 133,
    IEEE80211_PARAM_MACDEV           = 134,
    IEEE80211_PARAM_MACADDR1         = 135,
    IEEE80211_PARAM_MACADDR2         = 136,
    IEEE80211_PARAM_GPUTMODE         = 137,
    IEEE80211_PARAM_TXPROTOMSG       = 138,
    IEEE80211_PARAM_RXPROTOMSG       = 139,
    IEEE80211_PARAM_STATUS           = 140,
    IEEE80211_PARAM_ASSOC            = 141,
    IEEE80211_PARAM_NUMSTAS          = 142,
    IEEE80211_PARAM_STA1ROUTE        = 143,
    IEEE80211_PARAM_STA2ROUTE        = 144,
    IEEE80211_PARAM_STA3ROUTE        = 145,
    IEEE80211_PARAM_STA4ROUTE        = 146,
    IEEE80211_PARAM_PERIODIC_SCAN = 179,
#if ATH_SUPPORT_AP_WDS_COMBO
    IEEE80211_PARAM_NO_BEACON     = 180,  /* No beacon xmit on VAP */
#endif
    IEEE80211_PARAM_VAP_COUNTRY_IE   = 181, /* 802.11d country ie per vap */
    IEEE80211_PARAM_VAP_DOTH         = 182, /* 802.11h per vap */
    IEEE80211_PARAM_STA_QUICKKICKOUT = 183, /* station quick kick out */
    IEEE80211_PARAM_AUTO_ASSOC       = 184,
    IEEE80211_PARAM_RXBUF_LIFETIME   = 185, /* lifetime of reycled rx buffers */
    IEEE80211_PARAM_2G_CSA           = 186, /* 2.4 GHz CSA is on/off */
    IEEE80211_PARAM_WAPIREKEY_USK = 187,
    IEEE80211_PARAM_WAPIREKEY_MSK = 188,
    IEEE80211_PARAM_WAPIREKEY_UPDATE = 189,
#if ATH_SUPPORT_IQUE
    IEEE80211_PARAM_RC_VIVO          = 190, /* Use separate rate control algorithm for VI/VO queues */
#endif
    IEEE80211_PARAM_CLR_APPOPT_IE    = 191,  /* Clear Cached App/OptIE */
    IEEE80211_PARAM_SW_WOW           = 192,   /* wow by sw */
    IEEE80211_PARAM_QUIET_PERIOD    = 193,
    IEEE80211_PARAM_QBSS_LOAD       = 194,
    IEEE80211_PARAM_RRM_CAP         = 195,
    IEEE80211_PARAM_WNM_CAP         = 196,
#if UMAC_SUPPORT_WDS
    IEEE80211_PARAM_ADD_WDS_ADDR    = 197,  /* add wds addr */
#endif
#ifdef QCA_PARTNER_PLATFORM
    IEEE80211_PARAM_PLTFRM_PRIVATE = 198, /* platfrom's private ioctl*/
#endif

#if UMAC_SUPPORT_VI_DBG
    /* Support for Video Debug */
    IEEE80211_PARAM_DBG_CFG            = 199,
    IEEE80211_PARAM_DBG_NUM_STREAMS    = 200,
    IEEE80211_PARAM_STREAM_NUM         = 201,
    IEEE80211_PARAM_DBG_NUM_MARKERS    = 202,
    IEEE80211_PARAM_MARKER_NUM         = 203,
    IEEE80211_PARAM_MARKER_OFFSET_SIZE = 204,
    IEEE80211_PARAM_MARKER_MATCH       = 205,
    IEEE80211_PARAM_RXSEQ_OFFSET_SIZE  = 206,
    IEEE80211_PARAM_RX_SEQ_RSHIFT      = 207,
    IEEE80211_PARAM_RX_SEQ_MAX         = 208,
    IEEE80211_PARAM_RX_SEQ_DROP        = 209,
    IEEE80211_PARAM_TIME_OFFSET_SIZE   = 210,
    IEEE80211_PARAM_RESTART            = 211,
    IEEE80211_PARAM_RXDROP_STATUS      = 212,
#endif
#if ATH_SUPPORT_IBSS_DFS
    IEEE80211_PARAM_IBSS_DFS_PARAM     = 225,
#endif
#if ATH_SUPPORT_IBSS_NETLINK_NOTIFICATION
    IEEE80211_PARAM_IBSS_SET_RSSI_CLASS     = 237,
    IEEE80211_PARAM_IBSS_START_RSSI_MONITOR = 238,
    IEEE80211_PARAM_IBSS_RSSI_HYSTERESIS    = 239,
#endif
#ifdef ATH_SUPPORT_TxBF
    IEEE80211_PARAM_TXBF_AUTO_CVUPDATE = 240,       /* Auto CV update enable*/
    IEEE80211_PARAM_TXBF_CVUPDATE_PER = 241,        /* per theshold to initial CV update*/
#endif
    IEEE80211_PARAM_MAXSTA              = 242,
    IEEE80211_PARAM_RRM_STATS               =243,
    IEEE80211_PARAM_RRM_SLWINDOW            =244,
    IEEE80211_PARAM_MFP_TEST    = 245,
    IEEE80211_PARAM_SCAN_BAND   = 246,                /* only scan channels of requested band */
#if ATH_SUPPORT_FLOWMAC_MODULE
    IEEE80211_PARAM_FLOWMAC            = 247, /* flowmac enable/disable ath0*/
#endif
    IEEE80211_PARAM_STA_PWR_SET_PSPOLL      = 255,  /* Set ips_use_pspoll flag for STA */
    IEEE80211_PARAM_NO_STOP_DISASSOC        = 256,  /* Do not send disassociation frame on stopping vap */
#if UMAC_SUPPORT_IBSS
    IEEE80211_PARAM_IBSS_CREATE_DISABLE = 257,      /* if set, it prevents IBSS creation */
#endif
#if ATH_SUPPORT_WIFIPOS
    IEEE80211_PARAM_WIFIPOS_TXCORRECTION = 258,      /* Set/Get TxCorrection */
    IEEE80211_PARAM_WIFIPOS_RXCORRECTION = 259,      /* Set/Get RxCorrection */
#endif
#if UMAC_SUPPORT_CHANUTIL_MEASUREMENT
    IEEE80211_PARAM_CHAN_UTIL_ENAB      = 260,
    IEEE80211_PARAM_CHAN_UTIL           = 261,      /* Get Channel Utilization value (scale: 0 - 255) */
#endif /* UMAC_SUPPORT_CHANUTIL_MEASUREMENT */
    IEEE80211_PARAM_DBG_LVL_HIGH        = 262, /* Debug Level for specific VAP (upper 32 bits) */
    IEEE80211_PARAM_PROXYARP_CAP        = 263, /* Enable WNM Proxy ARP feature */
    IEEE80211_PARAM_DGAF_DISABLE        = 264, /* Hotspot 2.0 DGAF Disable feature */
    IEEE80211_PARAM_L2TIF_CAP           = 265, /* Hotspot 2.0 L2 Traffic Inspection and Filtering */
    IEEE80211_PARAM_WEATHER_RADAR_CHANNEL = 266, /* weather radar channel selection is bypassed */
    IEEE80211_PARAM_SEND_DEAUTH           = 267,/* for sending deauth while doing interface down*/
    IEEE80211_PARAM_WEP_KEYCACHE          = 268,/* wepkeys mustbe in first fourslots in Keycache*/
#if ATH_SUPPORT_WPA_SUPPLICANT_CHECK_TIME
    IEEE80211_PARAM_REJOINT_ATTEMP_TIME   = 269, /* Set the Rejoint time */
#endif
    IEEE80211_PARAM_WNM_SLEEP           = 270,      /* WNM-Sleep Mode */
    IEEE80211_PARAM_WNM_BSS_CAP         = 271,
    IEEE80211_PARAM_WNM_TFS_CAP         = 272,
    IEEE80211_PARAM_WNM_TIM_CAP         = 273,
    IEEE80211_PARAM_WNM_SLEEP_CAP       = 274,
    IEEE80211_PARAM_WNM_FMS_CAP         = 275,
    IEEE80211_PARAM_RRM_DEBUG           = 276, /* RRM debugging parameter */
    IEEE80211_PARAM_SET_TXPWRADJUST     = 277,
    IEEE80211_PARAM_TXRX_DBG              = 278,    /* show txrx debug info */
    IEEE80211_PARAM_VHT_MCS               = 279,    /* VHT MCS set */
    IEEE80211_PARAM_TXRX_FW_STATS         = 280,    /* single FW stat */
    IEEE80211_PARAM_TXRX_FW_MSTATS        = 281,    /* multiple FW stats */
    IEEE80211_PARAM_NSS                   = 282,    /* Number of Spatial Streams */
    IEEE80211_PARAM_LDPC                  = 283,    /* Support LDPC */
    IEEE80211_PARAM_TX_STBC               = 284,    /* Support TX STBC */
    IEEE80211_PARAM_RX_STBC               = 285,    /* Support RX STBC */
    IEEE80211_PARAM_APONLY                  = 293,
    IEEE80211_PARAM_TXRX_FW_STATS_RESET     = 294,
    IEEE80211_PARAM_TX_PPDU_LOG_CFG         = 295,  /* tx PPDU log cfg params */
    IEEE80211_PARAM_OPMODE_NOTIFY           = 296,  /* Op Mode Notification */
    IEEE80211_PARAM_NOPBN                   = 297, /* don't send push button notification */
    IEEE80211_PARAM_DFS_CACTIMEOUT          = 298, /* override CAC timeout */
    IEEE80211_PARAM_ENABLE_RTSCTS           = 299, /* Enable/disable RTS-CTS */

    IEEE80211_PARAM_MAX_AMPDU               = 300,   /* Set/Get rx AMPDU exponent/shift */
    IEEE80211_PARAM_VHT_MAX_AMPDU           = 301,   /* Set/Get rx VHT AMPDU exponent/shift */
    IEEE80211_PARAM_BCAST_RATE              = 302,   /* Setting Bcast DATA rate */
    IEEE80211_PARAM_PARENT_IFINDEX          = 304,   /* parent net_device ifindex for this VAP */
#if WDS_VENDOR_EXTENSION
    IEEE80211_PARAM_WDS_RX_POLICY           = 305,  /* Set/Get WDS rx filter policy for vendor specific WDS */
#endif
    IEEE80211_PARAM_ENABLE_OL_STATS         = 306,   /*Enables/Disables the
                                                        stats in the Host and in the FW */
    IEEE80211_IOCTL_GREEN_AP_ENABLE_PRINT   = 307,  /* Enable/Disable Green-AP debug prints */
    IEEE80211_PARAM_RC_NUM_RETRIES          = 308,
    IEEE80211_PARAM_GET_ACS                 = 309,/* to get status of acs */
    IEEE80211_PARAM_GET_CAC                 = 310,/* to get status of CAC period */
    IEEE80211_PARAM_EXT_IFACEUP_ACS         = 311,  /* Enable external auto channel selection entity
                                                       at VAP init time */
    IEEE80211_PARAM_ONETXCHAIN              = 312,  /* force to tx with one chain for legacy client */
    IEEE80211_PARAM_DFSDOMAIN               = 313,  /* Get DFS Domain */
    IEEE80211_PARAM_SCAN_CHAN_EVENT         = 314,  /* Enable delivery of Scan Channel Events during
                                                       802.11 scans (11ac offload, and IEEE80211_M_HOSTAP
                                                       mode only). */
    IEEE80211_PARAM_DESIRED_CHANNEL         = 315,  /* Get desired channel corresponding to desired
                                                       PHY mode */
    IEEE80211_PARAM_DESIRED_PHYMODE         = 316,  /* Get desired PHY mode */
    IEEE80211_PARAM_SEND_ADDITIONAL_IES     = 317,  /* Control sending of additional IEs to host */
    IEEE80211_PARAM_START_ACS_REPORT        = 318,  /* to start acs scan report */
    IEEE80211_PARAM_MIN_DWELL_ACS_REPORT    = 319,  /* min dwell time for  acs scan report */
    IEEE80211_PARAM_MAX_DWELL_ACS_REPORT    = 320,  /* max dwell time for  acs scan report */
    IEEE80211_PARAM_ACS_CH_HOP_LONG_DUR     = 321,  /* channel long duration timer used in acs */
    IEEE80211_PARAM_ACS_CH_HOP_NO_HOP_DUR   = 322,  /* No hopping timer used in acs */
    IEEE80211_PARAM_ACS_CH_HOP_CNT_WIN_DUR  = 323,  /* counter window timer used in acs */
    IEEE80211_PARAM_ACS_CH_HOP_NOISE_TH     = 324,  /* Noise threshold used in acs channel hopping */
    IEEE80211_PARAM_ACS_CH_HOP_CNT_TH       = 325,  /* counter threshold used in acs channel hopping */
    IEEE80211_PARAM_ACS_ENABLE_CH_HOP       = 326,  /* Enable/Disable acs channel hopping */
    IEEE80211_PARAM_SET_CABQ_MAXDUR         = 327,  /* set the max tx percentage for cabq */
    IEEE80211_PARAM_256QAM_2G               = 328,  /* 2.4 GHz 256 QAM support */
    IEEE80211_PARAM_MAX_SCANENTRY           = 330,  /* MAX scan entry */
    IEEE80211_PARAM_SCANENTRY_TIMEOUT       = 331,  /* Scan entry timeout value */
    IEEE80211_PARAM_PURE11AC                = 332,  /* pure 11ac(no 11bg/11a/11n stations) */
#if UMAC_VOW_DEBUG
    IEEE80211_PARAM_VOW_DBG_ENABLE  = 333,  /*Enable VoW debug*/
#endif
    IEEE80211_PARAM_SCAN_MIN_DWELL          = 334,  /* MIN dwell time to be used during scan */
    IEEE80211_PARAM_SCAN_MAX_DWELL          = 335,  /* MAX dwell time to be used during scan */
    IEEE80211_PARAM_BANDWIDTH               = 336,
    IEEE80211_PARAM_FREQ_BAND               = 337,
    IEEE80211_PARAM_EXTCHAN                 = 338,
    IEEE80211_PARAM_MCS                     = 339,
    IEEE80211_PARAM_CHAN_NOISE              = 340,
    IEEE80211_PARAM_VHT_SGIMASK             = 341,   /* Set VHT SGI MASK */
    IEEE80211_PARAM_VHT80_RATEMASK          = 342,   /* Set VHT80 Auto Rate MASK */
#if ATH_PERF_PWR_OFFLOAD
    IEEE80211_PARAM_VAP_TX_ENCAP_TYPE       = 343,
    IEEE80211_PARAM_VAP_RX_DECAP_TYPE       = 344,
#endif /* ATH_PERF_PWR_OFFLOAD */
#if (HOST_SW_TSO_ENABLE || HOST_SW_TSO_SG_ENABLE)
    IEEE80211_PARAM_TSO_STATS               = 345, /* Get TSO Stats */
    IEEE80211_PARAM_TSO_STATS_RESET         = 346, /* Reset TSO Stats */
#endif /* HOST_SW_TSO_ENABLE || HOST_SW_TSO_SG_ENABLE */
#if HOST_SW_LRO_ENABLE
    IEEE80211_PARAM_LRO_STATS               = 347, /* Get LRO Stats */
    IEEE80211_PARAM_LRO_STATS_RESET         = 348, /* Reset LRO Stats */
#endif /* HOST_SW_LRO_ENABLE */
#if RX_CHECKSUM_OFFLOAD
    IEEE80211_PARAM_RX_CKSUM_ERR_STATS      = 349, /* Get RX CKSUM Err Stats */
    IEEE80211_PARAM_RX_CKSUM_ERR_RESET      = 350, /* Reset RX CKSUM Err Stats */
#endif /* RX_CHECKSUM_OFFLOAD */

    IEEE80211_PARAM_VHT_STS_CAP             = 351,
    IEEE80211_PARAM_VHT_SOUNDING_DIM        = 352,
    IEEE80211_PARAM_VHT_SUBFEE              = 353,   /* set VHT SU beamformee capability */
    IEEE80211_PARAM_VHT_MUBFEE              = 354,   /* set VHT MU beamformee capability */
    IEEE80211_PARAM_VHT_SUBFER              = 355,   /* set VHT SU beamformer capability */
    IEEE80211_PARAM_VHT_MUBFER              = 356,   /* set VHT MU beamformer capability */
    IEEE80211_PARAM_IMPLICITBF              = 357,
    IEEE80211_PARAM_SEND_WOWPKT             = 358, /* Send Wake-On-Wireless packet */
    IEEE80211_PARAM_STA_FIXED_RATE          = 359, /* set/get fixed rate for associated sta on AP */
    IEEE80211_PARAM_11NG_VHT_INTEROP        = 360,  /* 2.4ng Vht Interop */
#if HOST_SW_SG_ENABLE
    IEEE80211_PARAM_SG_STATS                = 361, /* Get SG Stats */
    IEEE80211_PARAM_SG_STATS_RESET          = 362, /* Reset SG Stats */
#endif /* HOST_SW_SG_ENABLE */
    IEEE80211_PARAM_SPLITMAC                = 363,
    IEEE80211_PARAM_SHORT_SLOT              = 364,   /* Set short slot time */
    IEEE80211_PARAM_SET_ERP                 = 365,   /* Set ERP protection mode  */
    IEEE80211_PARAM_SESSION_TIMEOUT         = 366,   /* STA's session time */
#if ATH_PERF_PWR_OFFLOAD && QCA_SUPPORT_RAWMODE_PKT_SIMULATION
    IEEE80211_PARAM_RAWMODE_SIM_TXAGGR      = 367,   /* Enable/disable raw mode simulation
                                                        Tx A-MSDU aggregation */
    IEEE80211_PARAM_RAWMODE_PKT_SIM_STATS   = 368,   /* Get Raw mode packet simulation stats. */
    IEEE80211_PARAM_CLR_RAWMODE_PKT_SIM_STATS = 369, /* Clear Raw mode packet simulation stats. */
    IEEE80211_PARAM_RAWMODE_SIM_DEBUG       = 370,   /* Enable/disable raw mode simulation debug */
#endif /* ATH_PERF_PWR_OFFLOAD && QCA_SUPPORT_RAWMODE_PKT_SIMULATION */
    IEEE80211_PARAM_PROXY_STA               = 371,   /* set/get ProxySTA */
    IEEE80211_PARAM_BW_NSS_RATEMASK         = 372,   /* Set ratemask with specific Bandwidth and NSS  */
    IEEE80211_PARAM_RX_SIGNAL_DBM           = 373,  /*get rx signal strength in dBm*/
    IEEE80211_PARAM_VHT_TX_MCSMAP           = 374,   /* Set VHT TX MCS MAP */
    IEEE80211_PARAM_VHT_RX_MCSMAP           = 375,   /* Set VHT RX MCS MAP */
    IEEE80211_PARAM_WNM_SMENTER             = 376,
    IEEE80211_PARAM_WNM_SMEXIT              = 377,
    IEEE80211_PARAM_HC_BSSLOAD              = 378,
    IEEE80211_PARAM_OSEN                    = 379,
#if QCA_AIRTIME_FAIRNESS
    IEEE80211_PARAM_ATF_OPT                 = 380,   /* set airtime feature */
    IEEE80211_PARAM_ATF_PER_UNIT            = 381,
#endif
    IEEE80211_PARAM_TX_MIN_POWER            = 382, /* Get min tx power */
    IEEE80211_PARAM_TX_MAX_POWER            = 383, /* Get max tx power */
    IEEE80211_PARAM_MGMT_RATE               = 384, /* Set mgmt rate, will set mcast/bcast/ucast to same rate*/
    IEEE80211_PARAM_NO_VAP_RESET            = 385, /* Disable the VAP reset in NSS */
    IEEE80211_PARAM_STA_COUNT               = 386, /* TO get number of station associated*/
#if ATH_SSID_STEERING
    IEEE80211_PARAM_VAP_SSID_CONFIG         = 387, /* Vap configuration  */
#endif
#if ATH_SUPPORT_DSCP_OVERRIDE
    IEEE80211_PARAM_DSCP_OVERRIDE           = 388,
    IEEE80211_PARAM_DSCP_TID_MAP            = 389,
#endif
    IEEE80211_PARAM_RX_FILTER_MONITOR       = 390,
    IEEE80211_PARAM_SECOND_CENTER_FREQ      = 391,
    IEEE80211_PARAM_STRICT_BW               = 392,  /* BW restriction in pure 11ac */
    IEEE80211_PARAM_ADD_LOCAL_PEER          = 393,
    IEEE80211_PARAM_SET_MHDR                = 394,
    IEEE80211_PARAM_ALLOW_DATA              = 395,
    IEEE80211_PARAM_SET_MESHDBG             = 396,
    IEEE80211_PARAM_RTT_ENABLE              = 397,
    IEEE80211_PARAM_LCI_ENABLE              = 398,
    IEEE80211_PARAM_VAP_ENHIND              = 399, /* Independent VAP mode for Repeater and AP-STA config */
    IEEE80211_PARAM_VAP_PAUSE_SCAN          = 400, /* Pause VAP mode for scanning */
    IEEE80211_PARAM_EXT_ACS_IN_PROGRESS     = 401, /* Whether external auto channel selection is in
                                                    progress */
    IEEE80211_PARAM_AMPDU_DENSITY_OVERRIDE  = 402,  /* a-mpdu density override */
    IEEE80211_PARAM_SMART_MESH_CONFIG       = 403,  /* smart MESH configuration */
    IEEE80211_DISABLE_BCN_BW_NSS_MAP        = 404, /* To set & get Bandwidth-NSS mapping in beacon as vendor specific IE*/
    IEEE80211_DISABLE_STA_BWNSS_ADV         = 405, /* To disable all Bandwidth-NSS mapping feature in STA mode*/
    IEEE80211_PARAM_MIXED_MODE              = 406, /* In case of STA, this tells whether the AP we are associated
                                                      to supports TKIP alongwith AES */
    IEEE80211_PARAM_RX_FILTER_NEIGHBOUR_PEERS_MONITOR = 407,  /* filter out /drop invalid peers packet to upper stack */
#if ATH_DATA_RX_INFO_EN
    IEEE80211_PARAM_RXINFO_PERPKT          = 408,  /* update rx info per pkt */
#endif
    IEEE80211_PARAM_WHC_APINFO_WDS          = 415, /* Whether associated AP supports WDS
                                                      (as determined from the vendor IE) */
    IEEE80211_PARAM_WHC_APINFO_ROOT_DIST    = 416, /* Distance from the root AP (in hops);
                                                      only valid if the WDS flag is set
                                                      based on the param above */
    IEEE80211_PARAM_ATH_SUPPORT_VLAN        = 417,
    IEEE80211_PARAM_CONFIG_ASSOC_WAR_160W   = 418, /* Configure association WAR for 160 MHz width (i.e.
                                                      160/80+80 MHz modes). Some STAs may have an issue
                                                      associating with us if we advertise 160/80+80 MHz related
                                                      capabilities in probe response/association response.
                                                      Hence this WAR suppresses 160/80+80 MHz related
                                                      information in probe responses, and association responses
                                                      for such STAs.
                                                      Starting from LSB
                                                      First bit set        = Default WAR behavior (VHT_OP modified)
                                                      First+second bit set = (VHT_OP+ VHT_CAP modified)
                                                      No bit set (default) = WAR disabled
                                                     */
#if DBG_LVL_MAC_FILTERING
    IEEE80211_PARAM_DBG_LVL_MAC             = 419, /* Enable/disable mac based filtering for debug logs */
#endif
#if QCA_AIRTIME_FAIRNESS
    IEEE80211_PARAM_ATF_TXBUF_MAX           = 420,
    IEEE80211_PARAM_ATF_TXBUF_MIN           = 421,
    IEEE80211_PARAM_ATF_TXBUF_SHARE         = 422, /* For ATF UDP */
    IEEE80211_PARAM_ATF_MAX_CLIENT          = 423, /* Support of ATF+non-ATF clients */
    IEEE80211_PARAM_ATF_SSID_GROUP          = 424, /* Support to enable/disable SSID grouping */
#endif
    IEEE80211_PARAM_11N_TX_AMSDU            = 425, /* Enable/Disable HT Tx AMSDU only */
    IEEE80211_PARAM_BSS_CHAN_INFO           = 426,
    IEEE80211_PARAM_LCR_ENABLE              = 427,
    IEEE80211_PARAM_WHC_APINFO_SON          = 428, /* Whether associated AP supports SON mode
                                                      (as determined from the vendor IE) */
    IEEE80211_PARAM_SON                     = 429, /* Mark/query AP as SON enabled */
    IEEE80211_PARAM_CTSPROT_DTIM_BCN        = 430, /* Enable/Disable CTS2SELF protection for DTIM Beacons */
    IEEE80211_PARAM_RAWMODE_PKT_SIM         = 431, /* Enable/Disable RAWMODE_PKT_SIM*/
    IEEE80211_PARAM_CONFIG_RAW_DWEP_IND     = 432, /* Enable/disable indication to WLAN driver that
                                                      dynamic WEP is being used in RAW mode. If the indication
                                                      is enabled and we are in RAW mode, we plumb a dummy key for
                                                      each of the keys corresponding to WEP cipher
                                                   */
#if ATH_GEN_RANDOMNESS
    IEEE80211_PARAM_RANDOMGEN_MODE           = 433,
#endif

   IEEE80211_PARAM_CUSTOM_CHAN_LIST         = 434,
#if UMAC_SUPPORT_ACFG
    IEEE80211_PARAM_DIAG_WARN_THRESHOLD     = 435,
    IEEE80211_PARAM_DIAG_ERR_THRESHOLD      = 436,
#endif
    IEEE80211_PARAM_MBO                           = 437,     /*  Enable MBO */
    IEEE80211_PARAM_MBO_CAP                       = 438,     /*  Enable MBO capability */
    IEEE80211_PARAM_MBO_ASSOC_DISALLOW            = 439,     /*  MBO  reason code for assoc disallow attribute */
    IEEE80211_PARAM_MBO_CELLULAR_PREFERENCE       = 440,     /*  MBO cellular preference */
    IEEE80211_PARAM_MBO_TRANSITION_REASON         = 441,     /*  MBO Tansition reason */
    IEEE80211_PARAM_MBO_ASSOC_RETRY_DELAY         = 442,     /*  MBO  assoc retry delay */
#if ATH_SUPPORT_DSCP_OVERRIDE
    IEEE80211_PARAM_VAP_DSCP_PRIORITY        = 443,  /* VAP Based DSCP - Vap priority */
#endif
    IEEE80211_PARAM_TXRX_VAP_STATS           = 444,
    IEEE80211_PARAM_CONFIG_REV_SIG_160W      = 445, /* Enable/Disable revised signalling for 160/80+80 MHz */
    IEEE80211_PARAM_DISABLE_SELECTIVE_HTMCS_FOR_VAP = 446, /* Enable/Disable selective HT-MCS for this vap. */
    IEEE80211_PARAM_CONFIGURE_SELECTIVE_VHTMCS_FOR_VAP = 447, /* Enable/Disable selective VHT-MCS for this vap. */
    IEEE80211_PARAM_RDG_ENABLE              = 448,
    IEEE80211_PARAM_DFS_SUPPORT             = 449,
    IEEE80211_PARAM_DFS_ENABLE              = 450,
    IEEE80211_PARAM_ACS_SUPPORT             = 451,
    IEEE80211_PARAM_SSID_STATUS             = 452,
    IEEE80211_PARAM_DL_QUEUE_PRIORITY_SUPPORT = 453,
    IEEE80211_PARAM_CLEAR_MIN_MAX_RSSI        = 454,
    IEEE80211_PARAM_CLEAR_QOS            = 455,
#if QCA_AIRTIME_FAIRNESS
    IEEE80211_PARAM_ATF_OVERRIDE_AIRTIME_TPUT = 456, /* Override the airtime estimated */
#endif
#if MESH_MODE_SUPPORT
    IEEE80211_PARAM_MESH_CAPABILITIES      = 457, /* For providing Mesh vap capabilities */
#endif
#if UMAC_SUPPORT_ACL
    IEEE80211_PARAM_CONFIG_ASSOC_DENIAL_NOTIFY = 458,  /* Enable/disable assoc denial notification to userspace */
    IEEE80211_PARAM_ADD_MAC_LIST_SEC = 459, /* To check if the mac address is to added in secondary ACL list */
    IEEE80211_PARAM_GET_MAC_LIST_SEC = 460, /* To get the mac addresses from the secondary ACL list */
    IEEE80211_PARAM_DEL_MAC_LIST_SEC = 461, /* To delete the given mac address from the secondary ACL list */
    IEEE80211_PARAM_MACCMD_SEC = 462, /* To set/get the acl policy of the secondary ACL list */
#endif /* UMAC_SUPPORT_ACL */
    IEEE80211_PARAM_UMAC_VERBOSE_LVL           = 463, /* verbose level for UMAC specific debug */
    IEEE80211_PARAM_VAP_TXRX_FW_STATS          = 464, /* Get per VAP MU-MIMO stats */
    IEEE80211_PARAM_VAP_TXRX_FW_STATS_RESET    = 465, /* Reset per VAp MU-MIMO stats */
    IEEE80211_PARAM_PEER_TX_MU_BLACKLIST_COUNT = 466, /* Get number of times a peer has been blacklisted due to sounding failures */
    IEEE80211_PARAM_PEER_TX_COUNT              = 467, /* Get count of MU MIMO tx to a peer */
    IEEE80211_PARAM_PEER_MUMIMO_TX_COUNT_RESET = 468, /* Reset count of MU MIMO tx to a peer */
    IEEE80211_PARAM_PEER_POSITION              = 469, /* Get peer position in MU group */
#if QCA_AIRTIME_FAIRNESS
    IEEE80211_PARAM_ATF_SSID_SCHED_POLICY    = 470, /* support to set per ssid atf sched policy, 0-fair 1-strict */
#endif
    IEEE80211_PARAM_CONNECTION_SM_STATE        = 471, /* Get the current state of the connectionm SM */
#if MESH_MODE_SUPPORT
    IEEE80211_PARAM_CONFIG_MGMT_TX_FOR_MESH    = 472,
    IEEE80211_PARAM_CONFIG_RX_MESH_FILTER      = 473,
#endif
    IEEE80211_PARAM_TRAFFIC_STATS              = 474,   /* Enable/disable the measurement of traffic statistics */
    IEEE80211_PARAM_TRAFFIC_RATE               = 475,   /* set the traffic rate, the rate at which the received signal statistics are be measured */
    IEEE80211_PARAM_TRAFFIC_INTERVAL           = 476,   /* set the traffic interval,the time till which the received signal statistics are to be measured */
    IEEE80211_PARAM_WATERMARK_THRESHOLD        = 477,
    IEEE80211_PARAM_WATERMARK_REACHED          = 478,
    IEEE80211_PARAM_ASSOC_REACHED              = 479,
    IEEE80211_PARAM_DISABLE_SELECTIVE_LEGACY_RATE_FOR_VAP = 480,      /* Enable/Disable selective Legacy Rates for this vap. */
    IEEE80211_PARAM_RTSCTS_RATE                = 481,   /* Set rts and cts rate*/
    IEEE80211_PARAM_REPT_MULTI_SPECIAL         = 482,
    IEEE80211_PARAM_VSP_ENABLE                 = 483,   /* Video Stream Protection */
    IEEE80211_PARAM_ENABLE_VENDOR_IE           = 484,    /* Enable/ disable Vendor ie advertise in Beacon/ proberesponse*/
    IEEE80211_PARAM_WHC_APINFO_SFACTOR         = 485,  /* Set Scaling factor for best uplink selection algorithm */
    IEEE80211_PARAM_WHC_APINFO_BSSID           = 486,  /* Get the best uplink BSSID for scan entries */
    IEEE80211_PARAM_WHC_APINFO_RATE            = 487,  /* Get the current uplink data rate(estimate) */
    IEEE80211_PARAM_CONFIG_MON_DECODER         = 488,  /* Monitor VAP decoder format radiotap/prism */
    IEEE80211_PARAM_DYN_BW_RTS                 = 489,   /* Enable/Disable the dynamic bandwidth RTS */
    IEEE80211_PARAM_CONFIG_MU_CAP_TIMER        = 490,  /* Set/Get timer period in seconds(1 to 300) for de-assoc dedicated client when
                                                       mu-cap client joins/leaves */
    IEEE80211_PARAM_CONFIG_MU_CAP_WAR          = 491,   /* Enable/Disable Mu Cap WAR function */
    IEEE80211_PARAM_CONFIG_BSSID               = 492,  /* Configure hidden ssid AP's bssid */
    IEEE80211_PARAM_CONFIG_NSTSCAP_WAR         = 493,  /* Enable/Disable NSTS CAP WAR */
    IEEE80211_PARAM_WHC_APINFO_CAP_BSSID       = 494,   /* get the CAP BSSID from scan entries */
    IEEE80211_PARAM_BEACON_RATE_FOR_VAP        = 495,      /*Configure beacon rate to user provided rate*/
    IEEE80211_PARAM_CHANNEL_SWITCH_MODE        = 496,   /* channel switch mode to be used in CSA and ECSA IE*/
    IEEE80211_PARAM_ENABLE_ECSA_IE             = 497,   /* ECSA IE  enable/disable*/
    IEEE80211_PARAM_ECSA_OPCLASS               = 498,   /* opClass to be announced in ECSA IE */
#if DYNAMIC_BEACON_SUPPORT
    IEEE80211_PARAM_DBEACON_EN                 = 499, /* Enable/disable the dynamic beacon feature */
    IEEE80211_PARAM_DBEACON_RSSI_THR           = 500, /* Set/Get the rssi threshold */
    IEEE80211_PARAM_DBEACON_TIMEOUT            = 501, /* Set/Get the timeout of timer */
#endif
    IEEE80211_PARAM_TXPOW_MGMT                 = 502,   /* set/get the tx power per vap */
    IEEE80211_PARAM_CONFIG_TX_CAPTURE          = 503, /* Configure pkt capture in Tx direction */
    IEEE80211_PARAM_GET_CONFIG_BSSID           = 504, /* get configured hidden ssid AP's bssid */
    IEEE80211_PARAM_OCE                        = 505,  /* Enable OCE */
    IEEE80211_PARAM_OCE_ASSOC_REJECT           = 506,  /* Enable OCE RSSI-based assoc reject */
    IEEE80211_PARAM_OCE_ASSOC_MIN_RSSI         = 507,  /* Min RSSI for assoc accept */
    IEEE80211_PARAM_OCE_ASSOC_RETRY_DELAY      = 508,  /* Retry delay for subsequent (re-)assoc */
    IEEE80211_PARAM_OCE_WAN_METRICS            = 509,  /* Enable OCE reduced WAN metrics */
    IEEE80211_PARAM_BACKHAUL                   = 510,
    IEEE80211_PARAM_WHC_APINFO_BEST_UPLINK_OTHERBAND_BSSID = 511, /* Get the best otherband uplink BSSID */
    IEEE80211_PARAM_WHC_APINFO_OTHERBAND_UPLINK_BSSID = 512, /* Get the current otherband uplink BSSID from scan entry */
    IEEE80211_PARAM_WHC_APINFO_OTHERBAND_BSSID = 513, /* Set the otherband BSSID for AP vap */
    IEEE80211_PARAM_EXT_NSS_CAPABLE            = 514, /* EXT NSS Capable */
    IEEE80211_PARAM_SEND_PROBE_REQ             = 515, /* Send bcast probe request with current ssid */
#if ATH_SUPPORT_NR_SYNC
    IEEE80211_PARAM_NR_SHARE_RADIO_FLAG        = 516,   /* The mask to indicate which radio the NR information shares across */
#endif
    IEEE80211_PARAM_WHC_APINFO_UPLINK_RATE     = 517,  /* Get the current uplink rate */
#if QCN_IE
    IEEE80211_PARAM_BCAST_PROBE_RESPONSE_DELAY = 518, /* set/get the delay for holding the broadcast
                                                         probe response (in ms) */
    IEEE80211_PARAM_BCAST_PROBE_RESPONSE_LATENCY_COMPENSATION = 519, /* set/get latency for the RTT made by the broadcast
                                                                        probe response(in ms) */
    IEEE80211_PARAM_BCAST_PROBE_RESPONSE_STATS = 520, /* Get the broadcast probe response stats */
    IEEE80211_PARAM_BCAST_PROBE_RESPONSE_ENABLE = 521, /* If set, enables the broadcast probe response feature */
    IEEE80211_PARAM_BCAST_PROBE_RESPONSE_STATS_CLEAR = 522, /* Clear the broadcast probe response stats */
    IEEE80211_PARAM_BEACON_LATENCY_COMPENSATION = 523, /* Set/get the beacon latency between driver and firmware */
#endif
    IEEE80211_PARAM_CSL_SUPPORT                = 524,  /* CSL Support */
    IEEE80211_PARAM_SIFS_TRIGGER               = 525,  /* get/set sifs trigger interval per vdev */
    IEEE80211_PARAM_CONFIG_TX_CAPTURE_DA       = 526,  /* Enable the Tx capture for DA radios, if monitor VAP is available */
    IEEE80211_PARAM_EXT_NSS_SUPPORT            = 527,  /* EXT NSS Support */
    IEEE80211_PARAM_RX_FILTER_SMART_MONITOR    = 528,  /* Get per vap smart monitor stats */
    IEEE80211_PARAM_DISABLE_CABQ               = 529,  /* Disable multicast buffer when STA is PS */
    IEEE80211_PARAM_WHC_CAP_RSSI               = 530,  /* Set/Get the CAP RSSI threshold for best uplink selection */
    IEEE80211_PARAM_WHC_CURRENT_CAP_RSSI       = 531,  /* Get the current CAP RSSI from scan entrie */
    IEEE80211_PARAM_ENABLE_FILS                = 532,  /* Enable/disable FILS */
    IEEE80211_PARAM_SIFS_TRIGGER_RATE          = 533,  /* get/set sifs trigger rate per vdev */
    IEEE80211_PARAM_RX_SMART_MONITOR_RSSI      = 534,  /* Get smart monitor rssi */
    IEEE80211_PARAM_GET_CONFIG_REJECT_MGMT_FRAME     = 535,  /* get the list of addr's for which mgmt pkts need to be rejected */
    IEEE80211_PARAM_ADD_MAC_REJECT_MGMT_FRAME   = 536,  /* add macaddress to reject mgmt pkts */
    IEEE80211_PARAM_DEL_MAC_REJECT_MGMT_FRAME   = 537,  /* del macaddress to reject mgmt pkts */
    IEEE80211_PARAM_ACTIVITY                    = 538,  /* Percentage of time the radio was unable to tx/rx pkts to/from clients */
    IEEE80211_PARAM_TXPOW                      = 539,   /* set/get the control frame tx power per vap */
    IEEE80211_PARAM_PRB_RATE                   = 540,   /* set/get probe-response frame rate */
    IEEE80211_PARAM_SOFTBLOCK_WAIT_TIME        = 541,   /* set/get wait time in softblcking */
    IEEE80211_PARAM_SOFTBLOCK_ALLOW_TIME       = 542,   /* set/get allow time in softblocking */
    IEEE80211_PARAM_OCE_HLP                    = 543,   /* Enable/disable OCE FILS HLP */
    IEEE80211_PARAM_NBR_SCAN_PERIOD            = 544,   /* set/get neighbor AP scan period */
    IEEE80211_PARAM_RNR                        = 545,   /* enable/disable inclusion of RNR IE in Beacon/Probe-Rsp */
    IEEE80211_PARAM_RNR_FD                     = 546,   /* enable/disable inclusion of RNR IE in FILS Discovery */
    IEEE80211_PARAM_RNR_TBTT                   = 547,   /* enable/disable calculation TBTT in RNR IE */
    IEEE80211_PARAM_AP_CHAN_RPT                = 548,   /* enable/disable inclusion of AP Channel Report IE in Beacon/Probe-Rsp */
    IEEE80211_PARAM_STEALTH_DOWN               = 549,   /* enable stealth mode interface down without explicitly disconnecting STAs */
    IEEE80211_PARAM_TIMEOUTIE                  = 550,   /* set/get assoc comeback timeout value */
    IEEE80211_PARAM_PMF_ASSOC                  = 551,   /* enable/disable pmf support */
    IEEE80211_PARAM_DFS_INFO_NOTIFY_APP        = 552,   /* Enable the feature to notify dfs info to app */
    IEEE80211_PARAM_UPLINK_LIMIT               = 553,   /* Uplink Limit */
    IEEE80211_PARAM_DOWNLINK_LIMIT             = 554,   /* Downlink Limit */
};
#define WOW_CUSTOM_PKT_LEN 102
#define WOW_SYNC_PATTERN 0xFF
#define WOW_SYNC_LEN 6
#define WOW_MAC_ADDR_COUNT 16
#define ETH_TYPE_WOW 0x0842

/*
 * New get/set params for p2p.
 * The first 16 set/get priv ioctls know the direction of the xfer
 * These sub-ioctls, don't care, any number in 16 bits is ok
 * The param numbers need not be contiguous, but must be unique
 */
#define IEEE80211_IOC_P2P_GO_OPPPS        621    /* IOCTL to turn on/off oppPS for P2P GO */
#define IEEE80211_IOC_P2P_GO_CTWINDOW     622    /* IOCTL to set CT WINDOW size for P2P GO*/
#define IEEE80211_IOC_P2P_GO_NOA          623    /* IOCTL to set NOA for P2P GO*/

//#define IEEE80211_IOC_P2P_FLUSH           616    /* IOCTL to flush P2P state */
#define IEEE80211_IOC_SCAN_REQ            624    /* IOCTL to request a scan */
//needed, below
#define IEEE80211_IOC_SCAN_RESULTS        IEEE80211_IOCTL_SCAN_RESULTS

#define IEEE80211_IOC_SSID                626    /* set ssid */
#define IEEE80211_IOC_MLME                IEEE80211_IOCTL_SETMLME
#define IEEE80211_IOC_CHANNEL             628    /* set channel */

#define IEEE80211_IOC_WPA                 IEEE80211_PARAM_WPA    /* WPA mode (0,1,2) */
#define IEEE80211_IOC_AUTHMODE            IEEE80211_PARAM_AUTHMODE
#define IEEE80211_IOC_KEYMGTALGS          IEEE80211_PARAM_KEYMGTALGS    /* key management algorithms */
#define IEEE80211_IOC_WPS_MODE            632    /* Wireless Protected Setup mode  */

#define IEEE80211_IOC_UCASTCIPHERS        IEEE80211_PARAM_UCASTCIPHERS    /* unicast cipher suites */
#define IEEE80211_IOC_UCASTCIPHER         IEEE80211_PARAM_UCASTCIPHER    /* unicast cipher */
#define IEEE80211_IOC_MCASTCIPHER         IEEE80211_PARAM_MCASTCIPHER    /* multicast/default cipher */
//unused below
#define IEEE80211_IOC_START_HOSTAP        636    /* Start hostap mode BSS */

#define IEEE80211_IOC_DROPUNENCRYPTED     637    /* discard unencrypted frames */
#define IEEE80211_IOC_PRIVACY             638    /* privacy invoked */
#define IEEE80211_IOC_OPTIE               IEEE80211_IOCTL_SETOPTIE    /* optional info. element */
#define IEEE80211_IOC_BSSID               640    /* GET bssid */
//unused below 3
#define IEEE80211_IOC_P2P_CANCEL_CHANNEL  642    /* Cancel current set-channel operation */
#define IEEE80211_IOC_P2P_SEND_ACTION     643    /* Send Action frame */

#define IEEE80211_IOC_P2P_OPMODE          644    /* set/get the opmode(STA,AP,P2P GO,P2P CLI) */
#define IEEE80211_IOC_P2P_FETCH_FRAME     645    /* get rx_frame mgmt data, too large for an event */

#define IEEE80211_IOC_SCAN_FLUSH          646
#define IEEE80211_IOC_CONNECTION_STATE    647 	/* connection state of the iface */
#define IEEE80211_IOC_P2P_NOA_INFO        648   /*  To get NOA sub element info from p2p client */
#define IEEE80211_IOC_CANCEL_SCAN           650   /* To cancel scan request */
#define IEEE80211_IOC_P2P_RADIO_IDX         651   /* Get radio index */
#ifdef HOST_OFFLOAD
#endif

struct ieee80211_p2p_go_neg {
    u_int8_t peer_addr[IEEE80211_ADDR_LEN];
    u_int8_t own_interface_addr[IEEE80211_ADDR_LEN];
    u_int16_t force_freq;
    u_int8_t go_intent;
    char pin[9];
} __attribute__ ((packed));

struct ieee80211_p2p_prov_disc {
    u_int8_t peer_addr[IEEE80211_ADDR_LEN];
    u_int16_t config_methods;
} __attribute__ ((packed));

struct ieee80211_p2p_serv_disc_resp {
    u_int16_t freq;
    u_int8_t dst[IEEE80211_ADDR_LEN];
    u_int8_t dialog_token;
    /* followed by response TLVs */
} __attribute__ ((packed));

struct ieee80211_p2p_go_noa {
    u_int8_t  num_iterations;   /* Number of iterations (equal 1 if one shot)
                                   and 1-254 if periodic) and 255 for continuous */
    u_int16_t offset_next_tbtt; /* offset in msec from next tbtt */
    u_int16_t duration;         /* duration in msec */
} __attribute__ ((packed));

struct ieee80211_p2p_set_channel {
    u_int32_t freq;
    u_int32_t req_id;
    u_int32_t channel_time;
} __attribute__ ((packed));

struct ieee80211_p2p_send_action {
    u_int32_t freq;
    u_int8_t dst_addr[IEEE80211_ADDR_LEN];
    u_int8_t src_addr[IEEE80211_ADDR_LEN];
    u_int8_t bssid[IEEE80211_ADDR_LEN];
    /* Followed by Action frame payload */
} __attribute__ ((packed));

struct ieee80211_send_action_cb {
    u_int8_t dst_addr[IEEE80211_ADDR_LEN];
    u_int8_t src_addr[IEEE80211_ADDR_LEN];
    u_int8_t bssid[IEEE80211_ADDR_LEN];
    u_int8_t ack;
    /* followed by frame body */
} __attribute__ ((packed));

/* Optional parameters for IEEE80211_IOC_SCAN_REQ */
struct ieee80211_scan_req {
#define MAX_SCANREQ_FREQ 16
    u_int32_t freq[MAX_SCANREQ_FREQ];
    u_int8_t num_freq;
    u_int8_t num_ssid;
    u_int16_t ie_len;
#define MAX_SCANREQ_SSID 10
    u_int8_t ssid[MAX_SCANREQ_SSID][32];
    u_int8_t ssid_len[MAX_SCANREQ_SSID];
    /* followed by ie_len octets of IEs to add to Probe Request frames */
} __attribute__ ((packed));

struct ieee80211_ioc_channel {
    u_int32_t phymode; /* enum ieee80211_phymode */
    u_int32_t channel; /* IEEE channel number */
} __attribute__ ((packed));

#define LINUX_PVT_SET_VENDORPARAM       (SIOCDEVPRIVATE+0)
#define LINUX_PVT_GET_VENDORPARAM       (SIOCDEVPRIVATE+1)
#define	SIOCG80211STATS		(SIOCDEVPRIVATE+2)
/* NB: require in+out parameters so cannot use wireless extensions, yech */
#define	IEEE80211_IOCTL_GETKEY		(SIOCDEVPRIVATE+3)
#define	IEEE80211_IOCTL_GETWPAIE	(SIOCDEVPRIVATE+4)
#define	IEEE80211_IOCTL_STA_STATS	(SIOCDEVPRIVATE+5)
#define	IEEE80211_IOCTL_STA_INFO	(SIOCDEVPRIVATE+6)
#define	SIOC80211IFCREATE		(SIOCDEVPRIVATE+7)
#define	SIOC80211IFDESTROY	 	(SIOCDEVPRIVATE+8)
#define	IEEE80211_IOCTL_SCAN_RESULTS	(SIOCDEVPRIVATE+9)
#define IEEE80211_IOCTL_RES_REQ         (SIOCDEVPRIVATE+10)
#define IEEE80211_IOCTL_GETMAC          (SIOCDEVPRIVATE+11)
#define IEEE80211_IOCTL_CONFIG_GENERIC  (SIOCDEVPRIVATE+12)
#define SIOCIOCTLTX99                   (SIOCDEVPRIVATE+13)
#define IEEE80211_IOCTL_P2P_BIG_PARAM   (SIOCDEVPRIVATE+14)
#define SIOCDEVVENDOR                   (SIOCDEVPRIVATE+15)    /* Used for ATH_SUPPORT_LINUX_VENDOR */
#define	IEEE80211_IOCTL_GET_SCAN_SPACE  (SIOCDEVPRIVATE+16)

#define IEEE80211_IOCTL_ATF_ADDSSID     0xFF01
#define IEEE80211_IOCTL_ATF_DELSSID     0xFF02
#define IEEE80211_IOCTL_ATF_ADDSTA      0xFF03
#define IEEE80211_IOCTL_ATF_DELSTA      0xFF04
#define IEEE80211_IOCTL_ATF_SHOWATFTBL  0xFF05
#define IEEE80211_IOCTL_ATF_SHOWAIRTIME 0xFF06
#define IEEE80211_IOCTL_ATF_FLUSHTABLE  0xFF07                 /* Used to Flush the ATF table entries */

#define IEEE80211_IOCTL_ATF_ADDGROUP    0xFF08
#define IEEE80211_IOCTL_ATF_CONFIGGROUP 0xFF09
#define IEEE80211_IOCTL_ATF_DELGROUP    0xFF0a
#define IEEE80211_IOCTL_ATF_SHOWGROUP   0xFF0b

#define IEEE80211_IOCTL_ATF_ADDSTA_TPUT     0xFF0C
#define IEEE80211_IOCTL_ATF_DELSTA_TPUT     0xFF0D
#define IEEE80211_IOCTL_ATF_SHOW_TPUT       0xFF0E

#define ATF_TPUT_MASK         0x00ffffff
#define ATF_AIRTIME_MASK      0xff000000
#define ATF_AIRTIME_SHIFT     24
#define ATF_SHOW_PER_PEER_TABLE   1

/* added APPIEBUF related definations */
#define    IEEE80211_APPIE_FRAME_BEACON      0
#define    IEEE80211_APPIE_FRAME_PROBE_REQ   1
#define    IEEE80211_APPIE_FRAME_PROBE_RESP  2
#define    IEEE80211_APPIE_FRAME_ASSOC_REQ   3
#define    IEEE80211_APPIE_FRAME_ASSOC_RESP  4
#define    IEEE80211_APPIE_FRAME_TDLS_FTIE   5   /* TDLS SMK_FTIEs */
#define    IEEE80211_APPIE_FRAME_AUTH        6
#define    IEEE80211_APPIE_NUM_OF_FRAME      7
#define    IEEE80211_APPIE_FRAME_WNM         8

#define    DEFAULT_IDENTIFIER 0
#define    HOSTAPD_IE 1
#define    HOSTAPD_WPS_IE 2

struct ieee80211req_getset_appiebuf {
    u_int32_t app_frmtype; /*management frame type for which buffer is added*/
    u_int32_t app_buflen;  /*application supplied buffer length */
    u_int8_t  identifier;
    u_int8_t  app_buf[];
} __packed;

struct ieee80211req_mgmtbuf {
    u_int8_t  macaddr[IEEE80211_ADDR_LEN]; /* mac address to be sent */
    u_int32_t buflen;  /*application supplied buffer length */
    u_int8_t  buf[];
};

/* the following definations are used by application to set filter
 * for receiving management frames */
enum {
     IEEE80211_FILTER_TYPE_BEACON      =   0x1,
     IEEE80211_FILTER_TYPE_PROBE_REQ   =   0x2,
     IEEE80211_FILTER_TYPE_PROBE_RESP  =   0x4,
     IEEE80211_FILTER_TYPE_ASSOC_REQ   =   0x8,
     IEEE80211_FILTER_TYPE_ASSOC_RESP  =   0x10,
     IEEE80211_FILTER_TYPE_AUTH        =   0x20,
     IEEE80211_FILTER_TYPE_DEAUTH      =   0x40,
     IEEE80211_FILTER_TYPE_DISASSOC    =   0x80,
     IEEE80211_FILTER_TYPE_ACTION      =   0x100,
     IEEE80211_FILTER_TYPE_ALL         =   0xFFF  /* used to check the valid filter bits */
};

struct ieee80211req_set_filter {
      u_int32_t app_filterype; /* management frame filter type */
};

struct ieee80211_wlanconfig_atf {
    u_int8_t     macaddr[IEEE80211_ADDR_LEN];    /* MAC address (input) */
    u_int32_t    short_avg;                      /* AirtimeShortAvg (output) */
    u_int64_t    total_used_tokens;              /* AirtimeTotal    (output) */
};

struct ieee80211_wlanconfig_nawds {
    u_int8_t num;
    u_int8_t mode;
    u_int32_t defcaps;
    u_int8_t override;
    u_int8_t mac[IEEE80211_ADDR_LEN];
    u_int32_t caps;
};

struct ieee80211_wlanconfig_hmwds {
    u_int8_t  wds_ni_macaddr[IEEE80211_ADDR_LEN];
    u_int16_t wds_macaddr_cnt;
    u_int8_t  wds_macaddr[0];
};

struct ieee80211_wlanconfig_ald_sta {
    u_int8_t  macaddr[IEEE80211_ADDR_LEN];
    u_int32_t enable;
};

struct ieee80211_wlanconfig_ald {
    union {
        struct ieee80211_wlanconfig_ald_sta ald_sta;
    } data;
};

struct ieee80211_wlanconfig_wnm_bssmax {
    u_int16_t idleperiod;
    u_int8_t idleoption;
};

struct ieee80211_wlanconfig_wds {
    u_int8_t destmac[IEEE80211_ADDR_LEN];
    u_int8_t peermac[IEEE80211_ADDR_LEN];
    u_int32_t flags;
};

struct ieee80211_wlanconfig_wds_table {
    u_int16_t wds_entry_cnt;
    struct ieee80211_wlanconfig_wds wds_entries[0];
};

struct ieee80211_wlanconfig_hmmc {
    u_int32_t ip;
    u_int32_t mask;
};

struct ieee80211_wlanconfig_setmaxrate {
    u_int8_t mac[IEEE80211_ADDR_LEN];
    u_int8_t maxrate;
};

#define TFS_MAX_FILTER_LEN 50
#define TFS_MAX_TCLAS_ELEMENTS 2
#define TFS_MAX_SUBELEMENTS 2
#define TFS_MAX_REQUEST 2
#define TFS_MAX_RESPONSE 600

#define FMS_MAX_SUBELEMENTS    2
#define FMS_MAX_TCLAS_ELEMENTS 2
#define FMS_MAX_REQUEST        2
#define FMS_MAX_RESPONSE       2

typedef enum {
    IEEE80211_WNM_TFS_AC_DELETE_AFTER_MATCH = 0,
    IEEE80211_WNM_TFS_AC_NOTIFY = 1,
} IEEE80211_WNM_TFS_ACTIONCODE;

typedef enum {
    IEEE80211_WNM_TCLAS_CLASSIFIER_TYPE0 = 0,
    IEEE80211_WNM_TCLAS_CLASSIFIER_TYPE1 = 1,
    IEEE80211_WNM_TCLAS_CLASSIFIER_TYPE2 = 2,
    IEEE80211_WNM_TCLAS_CLASSIFIER_TYPE3 = 3,
    IEEE80211_WNM_TCLAS_CLASSIFIER_TYPE4 = 4,
} IEEE80211_WNM_TCLAS_CLASSIFIER;

typedef enum {
    IEEE80211_WNM_TCLAS_CLAS14_VERSION_4 = 4,
    IEEE80211_WNM_TCLAS_CLAS14_VERSION_6 = 6,
} IEEE80211_WNM_TCLAS_VERSION;

#ifndef IEEE80211_IPV4_LEN
#define IEEE80211_IPV4_LEN 4
#endif

#ifndef IEEE80211_IPV6_LEN
#define IEEE80211_IPV6_LEN 16
#endif

/*
 * TCLAS Classifier Type 1 and Type 4 are exactly the same for IPv4.
 * For IPv6, Type 4 has two more fields (dscp, next header) than
 * Type 1. So we use the same structure for both Type 1 and 4 here.
 */
struct clas14_v4 {
    u_int8_t     version;
    u_int8_t     source_ip[IEEE80211_IPV4_LEN];
    u_int8_t     reserved1[IEEE80211_IPV6_LEN - IEEE80211_IPV4_LEN];
    u_int8_t     dest_ip[IEEE80211_IPV4_LEN];
    u_int8_t     reserved2[IEEE80211_IPV6_LEN - IEEE80211_IPV4_LEN];
    u_int16_t    source_port;
    u_int16_t    dest_port;
    u_int8_t     dscp;
    u_int8_t     protocol;
    u_int8_t     reserved;
    u_int8_t     reserved3[2];
};

struct clas14_v6 {
    u_int8_t     version;
    u_int8_t     source_ip[IEEE80211_IPV6_LEN];
    u_int8_t     dest_ip[IEEE80211_IPV6_LEN];
    u_int16_t    source_port;
    u_int16_t    dest_port;
    u_int8_t     clas4_dscp;
    u_int8_t     clas4_next_header;
    u_int8_t     flow_label[3];
};

struct clas3 {
    u_int16_t filter_offset;
    u_int32_t filter_len;
    u_int8_t  filter_value[TFS_MAX_FILTER_LEN];
    u_int8_t  filter_mask[TFS_MAX_FILTER_LEN];
};

struct tfsreq_tclas_element {
    u_int8_t classifier_type;
    u_int8_t classifier_mask;
    u_int8_t priority;
    union {
        union {
            struct clas14_v4 clas14_v4;
            struct clas14_v6 clas14_v6;
        } clas14;
        struct clas3 clas3;
    } clas;
};

struct tfsreq_subelement {
    u_int32_t num_tclas_elements;
    u_int8_t tclas_processing;
    struct tfsreq_tclas_element tclas[TFS_MAX_TCLAS_ELEMENTS];
};

struct ieee80211_wlanconfig_wnm_tfs_req {
    u_int8_t tfsid;
    u_int8_t actioncode;
    u_int8_t num_subelements;
    struct tfsreq_subelement subelement[TFS_MAX_SUBELEMENTS];
};

#define NAC_MAX_CLIENT  8
#define NAC_MAX_BSSID  3

typedef enum ieee80211_nac_mactype {
    IEEE80211_NAC_MACTYPE_BSSID  = 1,
    IEEE80211_NAC_MACTYPE_CLIENT = 2,
} IEEE80211_NAC_MACTYPE;

struct ieee80211_wlanconfig_nac {
    u_int8_t    mac_type;
    u_int8_t    mac_list[NAC_MAX_CLIENT][IEEE80211_ADDR_LEN]; /* client has max limit */
    u_int8_t    rssi[NAC_MAX_CLIENT];
};
struct ieee80211_wlanconfig_nac_rssi {
    u_int8_t    mac_bssid[IEEE80211_ADDR_LEN];
    u_int8_t    mac_client[IEEE80211_ADDR_LEN];
    u_int8_t    chan_num;
    u_int8_t    client_rssi_valid;
    u_int8_t    client_rssi;
};

struct ieee80211_wlanconfig_wnm_tfs {
    u_int8_t num_tfsreq;
    struct ieee80211_wlanconfig_wnm_tfs_req tfs_req[TFS_MAX_REQUEST];
};

struct tfsresp_element {
	u_int8_t tfsid;
    u_int8_t status;
} __packed;

struct ieee80211_wnm_tfsresp {
    u_int8_t num_tfsresp;
    struct tfsresp_element  tfs_resq[TFS_MAX_RESPONSE];
} __packed;

typedef struct  ieee80211_wnm_rate_identifier_s {
    u_int8_t mask;
    u_int8_t mcs_idx;
    u_int16_t rate;
}__packed ieee80211_wnm_rate_identifier_t;

struct fmsresp_fms_subele_status {
    u_int8_t status;
    u_int8_t del_itvl;
    u_int8_t max_del_itvl;
    u_int8_t fmsid;
    u_int8_t fms_counter;
    ieee80211_wnm_rate_identifier_t rate_id;
    u_int8_t mcast_addr[6];
};

struct fmsresp_tclas_subele_status {
    u_int8_t fmsid;
    u_int8_t ismcast;
    u_int32_t mcast_ipaddr;
    ieee80211_tclas_processing tclasprocess;
    u_int32_t num_tclas_elements;
    struct tfsreq_tclas_element tclas[TFS_MAX_TCLAS_ELEMENTS];
};

struct fmsresp_element {
    u_int8_t fms_token;
    u_int8_t num_subelements;
    u_int8_t subelement_type;
    union {
        struct fmsresp_fms_subele_status fms_subele_status[FMS_MAX_TCLAS_ELEMENTS];
        struct fmsresp_tclas_subele_status tclas_subele_status[FMS_MAX_SUBELEMENTS];
    }status;
};

struct ieee80211_wnm_fmsresp {
    u_int8_t num_fmsresp;
    struct fmsresp_element  fms_resp[FMS_MAX_RESPONSE];
};

struct fmsreq_subelement {
    u_int8_t del_itvl;
    u_int8_t max_del_itvl;
    u_int8_t tclas_processing;
    u_int32_t num_tclas_elements;
    ieee80211_wnm_rate_identifier_t rate_id;
    struct tfsreq_tclas_element tclas[FMS_MAX_TCLAS_ELEMENTS];
} __packed;

struct ieee80211_wlanconfig_wnm_fms_req {
    u_int8_t fms_token;
    u_int8_t num_subelements;
    struct fmsreq_subelement subelement[FMS_MAX_SUBELEMENTS];
};

struct ieee80211_wlanconfig_wnm_fms {
    u_int8_t num_fmsreq;
    struct ieee80211_wlanconfig_wnm_fms_req  fms_req[FMS_MAX_REQUEST];
};

enum {
    IEEE80211_WNM_TIM_HIGHRATE_ENABLE = 0x1,
    IEEE80211_WNM_TIM_LOWRATE_ENABLE = 0x2,
};

struct ieee80211_wlanconfig_wnm_tim {
    u_int8_t interval;
    u_int8_t enable_highrate;
    u_int8_t enable_lowrate;
};

struct ieee80211_wlanconfig_wnm_bssterm {
    u_int16_t delay;    /* in TBTT */
    u_int16_t duration; /* in minutes */
};

struct ieee80211_wlanconfig_wnm {
    union {
        struct ieee80211_wlanconfig_wnm_bssmax bssmax;
        struct ieee80211_wlanconfig_wnm_tfs tfs;
        struct ieee80211_wlanconfig_wnm_fms fms;
        struct ieee80211_wlanconfig_wnm_tim tim;
        struct ieee80211_wlanconfig_wnm_bssterm bssterm;
    } data;
};

/* generic structure to support sub-ioctl due to limited ioctl */
typedef enum {
    IEEE80211_WLANCONFIG_NOP,
    IEEE80211_WLANCONFIG_NAWDS_SET_MODE,
    IEEE80211_WLANCONFIG_NAWDS_SET_DEFCAPS,
    IEEE80211_WLANCONFIG_NAWDS_SET_OVERRIDE,
    IEEE80211_WLANCONFIG_NAWDS_SET_ADDR,
    IEEE80211_WLANCONFIG_NAWDS_CLR_ADDR,
    IEEE80211_WLANCONFIG_NAWDS_GET,
    IEEE80211_WLANCONFIG_WNM_SET_BSSMAX,
    IEEE80211_WLANCONFIG_WNM_GET_BSSMAX,
    IEEE80211_WLANCONFIG_WNM_TFS_ADD,
    IEEE80211_WLANCONFIG_WNM_TFS_DELETE,
    IEEE80211_WLANCONFIG_WNM_FMS_ADD_MODIFY,
    IEEE80211_WLANCONFIG_WNM_SET_TIMBCAST,
    IEEE80211_WLANCONFIG_WNM_GET_TIMBCAST,
    IEEE80211_WLANCONFIG_WDS_ADD_ADDR,
    IEEE80211_WLANCONFIG_HMMC_ADD,
    IEEE80211_WLANCONFIG_HMMC_DEL,
    IEEE80211_WLANCONFIG_HMMC_DUMP,
    IEEE80211_WLANCONFIG_HMWDS_ADD_ADDR,
    IEEE80211_WLANCONFIG_HMWDS_RESET_ADDR,
    IEEE80211_WLANCONFIG_HMWDS_RESET_TABLE,
    IEEE80211_WLANCONFIG_HMWDS_READ_ADDR,
    IEEE80211_WLANCONFIG_HMWDS_READ_TABLE,
    IEEE80211_WLANCONFIG_HMWDS_SET_BRIDGE_ADDR,
    IEEE80211_WLANCONFIG_SET_MAX_RATE,
    IEEE80211_WLANCONFIG_WDS_SET_ENTRY,
    IEEE80211_WLANCONFIG_WDS_DEL_ENTRY,
    IEEE80211_WLANCONFIG_ALD_STA_ENABLE,
    IEEE80211_WLANCONFIG_WNM_BSS_TERMINATION,
    IEEE80211_WLANCONFIG_GETCHANINFO_160,
    IEEE80211_WLANCONFIG_VENDOR_IE_ADD,
    IEEE80211_WLANCONFIG_VENDOR_IE_UPDATE,
    IEEE80211_WLANCONFIG_VENDOR_IE_REMOVE,
    IEEE80211_WLANCONFIG_VENDOR_IE_LIST,
    IEEE80211_WLANCONFIG_NAC_ADDR_ADD,
    IEEE80211_WLANCONFIG_NAC_ADDR_DEL,
    IEEE80211_WLANCONFIG_NAC_ADDR_LIST,
    IEEE80211_PARAM_STA_ATF_STAT,
    IEEE80211_WLANCONFIG_HMWDS_REMOVE_ADDR,
    IEEE80211_WLANCONFIG_HMWDS_DUMP_WDS_ADDR,
    IEEE80211_WLANCONFIG_NAC_RSSI_ADDR_ADD,
    IEEE80211_WLANCONFIG_NAC_RSSI_ADDR_DEL,
    IEEE80211_WLANCONFIG_NAC_RSSI_ADDR_LIST,
    IEEE80211_WLANCONFIG_ADD_IE,
} IEEE80211_WLANCONFIG_CMDTYPE;
/* Note: Do not place any of the above ioctls within compile flags,
   The above ioctls are also being used by external apps.
   External apps do not define the compile flags as driver does.
   Having ioctls within compile flags leave the apps and drivers to use
   a different values.
*/

typedef enum {
    IEEE80211_WLANCONFIG_OK          = 0,
    IEEE80211_WLANCONFIG_FAIL        = 1,
} IEEE80211_WLANCONFIG_STATUS;

struct ieee80211_wlanconfig {
    IEEE80211_WLANCONFIG_CMDTYPE cmdtype;  /* sub-command */
    IEEE80211_WLANCONFIG_STATUS status;     /* status code */
    union {
        struct ieee80211_wlanconfig_nawds nawds;
        struct ieee80211_wlanconfig_hmwds hmwds;
        struct ieee80211_wlanconfig_wnm wnm;
        struct ieee80211_wlanconfig_hmmc hmmc;
        struct ieee80211_wlanconfig_wds_table wds_table;
        struct ieee80211_wlanconfig_ald ald;
        struct ieee80211_wlanconfig_nac nac;
        struct ieee80211_wlanconfig_atf atf;
        struct ieee80211_wlanconfig_nac_rssi nac_rssi;
    } data;

    struct ieee80211_wlanconfig_setmaxrate smr;
};

#define VENDORIE_OUI_LEN 3
#define MAX_VENDOR_IE_LEN 128
#define MAX_VENDOR_BUF_LEN 2048

struct ieee80211_wlanconfig_ie {
    IEEE80211_WLANCONFIG_CMDTYPE cmdtype;  /* sub-command */
    u_int8_t    ftype;      /* Frame type in which this IE is included */
    struct {
        u_int8_t elem_id;
        u_int8_t len;
        u_int8_t app_buf[];
    }ie;
};

struct ieee80211_wlanconfig_vendorie {

    IEEE80211_WLANCONFIG_CMDTYPE cmdtype;  /* sub-command */
    u_int8_t    ftype_map; /* map which frames , thesse IE are included */
    u_int16_t    tot_len;   /* total vie struct length */
struct  {
    u_int8_t    id;
    u_int8_t    len;    /* len of oui + cap_info */
    u_int8_t    oui[VENDORIE_OUI_LEN];
    u_int8_t    cap_info[];
} ie;
};


/* kev event_code value for Atheros IEEE80211 events */
enum {
    IEEE80211_EV_SCAN_DONE,
    IEEE80211_EV_CHAN_START,
    IEEE80211_EV_CHAN_END,
    IEEE80211_EV_RX_MGMT,
    IEEE80211_EV_P2P_SEND_ACTION_CB,
    IEEE80211_EV_IF_RUNNING,
    IEEE80211_EV_IF_NOT_RUNNING,
    IEEE80211_EV_AUTH_COMPLETE_AP,
    IEEE80211_EV_ASSOC_COMPLETE_AP,
    IEEE80211_EV_DEAUTH_COMPLETE_AP,
    IEEE80211_EV_AUTH_IND_AP,
    IEEE80211_EV_AUTH_COMPLETE_STA,
    IEEE80211_EV_ASSOC_COMPLETE_STA,
    IEEE80211_EV_DEAUTH_COMPLETE_STA,
    IEEE80211_EV_DISASSOC_COMPLETE_STA,
    IEEE80211_EV_AUTH_IND_STA,
    IEEE80211_EV_DEAUTH_IND_STA,
    IEEE80211_EV_ASSOC_IND_STA,
    IEEE80211_EV_DISASSOC_IND_STA,
    IEEE80211_EV_DEAUTH_IND_AP,
    IEEE80211_EV_DISASSOC_IND_AP,
    IEEE80211_EV_ASSOC_IND_AP,
    IEEE80211_EV_REASSOC_IND_AP,
    IEEE80211_EV_MIC_ERR_IND_AP,
    IEEE80211_EV_KEYSET_DONE_IND_AP,
    IEEE80211_EV_BLKLST_STA_AUTH_IND_AP,
    IEEE80211_EV_WAPI,
    IEEE80211_EV_TX_MGMT,
    IEEE80211_EV_CHAN_CHANGE,
    IEEE80211_EV_RECV_PROBEREQ,
    IEEE80211_EV_STA_AUTHORIZED,
    IEEE80211_EV_STA_LEAVE,
    IEEE80211_EV_ASSOC_FAILURE,
    IEEE80211_EV_DISASSOC_COMPLETE_AP,
    IEEE80211_EV_PRIMARY_RADIO_CHANGED,
#if QCA_LTEU_SUPPORT
    IEEE80211_EV_MU_RPT,
    IEEE80211_EV_SCAN,
#endif
#if QCA_AIRTIME_FAIRNESS
    IEEE80211_EV_ATF_CONFIG,
#endif
#if MESH_MODE_SUPPORT
    IEEE80211_EV_MESH_PEER_TIMEOUT,
#endif
    IEEE80211_EV_UNPROTECTED_DEAUTH_IND_STA,
};

#endif /* __linux__ */

#define IEEE80211_VAP_PROFILE_NUM_ACL 64
/*
 * As it is not advisable to use the macros defined in
 * ieee80211_var.h, this should always be the same as
 * IEEE80211_MAX_VAPS defined in ieee80211_var.h
 */
#define IEEE80211_VAP_PROFILE_MAX_VAPS 17

struct rssi_info {
    u_int8_t avg_rssi;
    u_int8_t valid_mask;
    int8_t   rssi_ctrl[MAX_CHAINS];
    int8_t   rssi_ext[MAX_CHAINS];
};

struct ieee80211vap_profile  {
    struct ieee80211vap *vap;
    char name[IFNAMSIZ];
    u_int32_t opmode;
    u_int32_t phymode;
    char  ssid[IEEE80211_NWID_LEN];
    u_int32_t bitrate;
    u_int32_t beacon_interval;
    u_int32_t txpower;
    u_int32_t txpower_flags;
    struct rssi_info bcn_rssi;
    struct rssi_info rx_rssi;
    u_int8_t  vap_mac[IEEE80211_ADDR_LEN];
    u_int32_t  rts_thresh;
    u_int8_t  rts_disabled;
    u_int8_t  rts_fixed;
    u_int32_t frag_thresh;
    u_int8_t frag_disabled;
    u_int8_t frag_fixed;
    u_int32_t   sec_method;
    u_int32_t   cipher;
    u_int8_t wep_key[4][256];
    u_int8_t wep_key_len[4];
    u_int8_t  maclist[IEEE80211_VAP_PROFILE_NUM_ACL][IEEE80211_ADDR_LEN];
   	u_int8_t  node_acl;
    int  num_node;
    u_int8_t wds_enabled;
    u_int8_t wds_addr[IEEE80211_ADDR_LEN];
    u_int32_t wds_flags;
};

struct ieee80211_profile {
    u_int8_t radio_name[IFNAMSIZ];
    u_int8_t channel;
    u_int32_t freq;
    u_int16_t cc;
    u_int8_t  radio_mac[IEEE80211_ADDR_LEN];
    struct ieee80211vap_profile vap_profile[IEEE80211_VAP_PROFILE_MAX_VAPS];
    int num_vaps;
};

/* FIPS Structures to be used by application */

#define FIPS_ENCRYPT 0
#define FIPS_DECRYPT 1
struct ath_ioctl_fips {
    u_int32_t fips_cmd;/* 1 - Encrypt, 2 - Decrypt*/
    u_int32_t mode;
    u_int32_t key_len;
#define MAX_KEY_LEN_FIPS 32
    u_int8_t  key[MAX_KEY_LEN_FIPS];
#define MAX_IV_LEN_FIPS  16
    u_int8_t iv[MAX_IV_LEN_FIPS];
    u_int32_t data_len;
    u_int32_t data[1];
};

struct ath_fips_output {
    u_int32_t error_status;
    u_int32_t data_len;
    u_int32_t data[1]; /* output from Fips Register*/
};

#define IS_UP_AUTO(_vap) \
    (IS_UP((_vap)->iv_dev) && \
    (_vap)->iv_ic->ic_roaming == IEEE80211_ROAMING_AUTO)

#if QCA_LTEU_SUPPORT

#define MU_MAX_ALGO          4
#define MU_DATABASE_MAX_LEN  32

typedef enum {
    MU_STATUS_SUCCESS,
    /* errors encountered in initiating MU scan are as below */
    MU_STATUS_BUSY_PREV_REQ_IN_PROG,      /* returned if previous request for MU scan is currently being processed */
    MU_STATUS_INVALID_INPUT,              /* returned if MU scan parameter passed has an invalid value */
    MU_STATUS_FAIL_BB_WD_TRIGGER,         /* returned if hardware baseband hangs */
    MU_STATUS_FAIL_DEV_RESET,             /* returned if hardware hangs and driver needs to perform a reset to recover */
    MU_STATUS_FAIL_GPIO_TIMEOUT,          /* returned if GPIO trigger has timed out*/
} mu_status_t;

typedef enum {
    DEVICE_TYPE_AP,
    DEVICE_TYPE_STA,
    DEVICE_TYPE_SC_SAME_OPERATOR,
    DEVICE_TYPE_SC_DIFF_OPERATOR,
} mu_device_t;

typedef struct{
    /* specifying device type(AP/STA/SameOPClass/DiffOPClass)for each entry of the MU database*/
    mu_device_t mu_device_type;
    /* specifying BSSID of each entry */
    u_int8_t mu_device_bssid[IEEE80211_ADDR_LEN];
    /* Mac address of each entry */
    u_int8_t mu_device_macaddr[IEEE80211_ADDR_LEN];
    /* average packet duration for each device in micro secs to avoid decimals */
    u_int32_t mu_avg_duration;
    /* average rssi recorded for the device */
    u_int32_t mu_avg_rssi;
    /* percentage of medium utilized by the device */
    u_int32_t mu_percentage;
}mu_database;

struct event_data_mu_rpt {
    u_int8_t        mu_req_id;                                  /* MU request id, copied from the request */
    u_int8_t        mu_channel;                                 /* IEEE channel number on which MU was done */
    mu_status_t     mu_status;                                  /* whether the MU scan was successful or not */
    u_int32_t       mu_total_val[MU_MAX_ALGO-1];                /* the aggregate MU computed by the 3 algos */
    u_int32_t       mu_num_bssid;                               /* number of active BSSIDs */
    u_int32_t       mu_actual_duration;                         /* time in ms for which the MU scan was done */
    u_int32_t       mu_hidden_node_algo[LTEU_MAX_BINS];         /* The MU computed by the hidden node algo, reported on a per bin basis */
    u_int32_t       mu_num_ta_entries;                          /* number of active TA entries in the database */
    mu_database     mu_database_entries[MU_DATABASE_MAX_LEN];   /* the MU report for each TA */
};

typedef enum {
    SCAN_SUCCESS,
    SCAN_FAIL,
} scan_status_t;

struct event_data_scan {
    u_int8_t        scan_req_id;               /* AP scan request id, copied from the request */
    scan_status_t   scan_status;               /* whether the AP scan was successful or not */
};

#endif /* QCA_LTEU_SUPPORT */

#if QCA_AIRTIME_FAIRNESS
struct event_data_atf_config {
    u_int8_t     macaddr[IEEE80211_ADDR_LEN];
    int          config;
};
#endif

#endif /* _NET80211_IEEE80211_IOCTL_H_ */



/*
 * phy type definitions.
 * do not change the order of these
 * defines .
 */
enum ieee80211_phytype {
    IEEE80211_T_DS,                 /* direct sequence spread spectrum */
    IEEE80211_T_FH,                 /* frequency hopping */
    IEEE80211_T_OFDM,               /* frequency division multiplexing */
    IEEE80211_T_TURBO,              /* high rate OFDM, aka turbo mode */
    IEEE80211_T_HT,                 /* HT - full GI */
    IEEE80211_T_ERP,
    IEEE80211_T_ANY,
    IEEE80211_T_MAX
};
#define IEEE80211_T_CCK IEEE80211_T_DS  /* more common nomenclature */

/* XXX not really a mode; there are really multiple PHY's */
enum ieee80211_phymode {
    IEEE80211_MODE_AUTO             = 0,    /* autoselect */
    IEEE80211_MODE_11A              = 1,    /* 5GHz, OFDM */
    IEEE80211_MODE_11B              = 2,    /* 2GHz, CCK */
    IEEE80211_MODE_11G              = 3,    /* 2GHz, OFDM */
    IEEE80211_MODE_FH               = 4,    /* 2GHz, GFSK */
    IEEE80211_MODE_TURBO_A          = 5,    /* 5GHz, OFDM, 2x clock dynamic turbo */
    IEEE80211_MODE_TURBO_G          = 6,    /* 2GHz, OFDM, 2x clock  dynamic turbo*/
    IEEE80211_MODE_11NA_HT20        = 7,    /* 5Ghz, HT20 */
    IEEE80211_MODE_11NG_HT20        = 8,    /* 2Ghz, HT20 */
    IEEE80211_MODE_11NA_HT40PLUS    = 9,    /* 5Ghz, HT40 (ext ch +1) */
    IEEE80211_MODE_11NA_HT40MINUS   = 10,   /* 5Ghz, HT40 (ext ch -1) */
    IEEE80211_MODE_11NG_HT40PLUS    = 11,   /* 2Ghz, HT40 (ext ch +1) */
    IEEE80211_MODE_11NG_HT40MINUS   = 12,   /* 2Ghz, HT40 (ext ch -1) */
};
#define IEEE80211_MODE_MAX      (IEEE80211_MODE_11NG_HT40MINUS + 1)

enum ieee80211_opmode {
    IEEE80211_M_STA         = 1,    /* infrastructure station */
    IEEE80211_M_IBSS        = 0,    /* IBSS (adhoc) station */
    IEEE80211_M_AHDEMO      = 3,    /* Old lucent compatible adhoc demo */
    IEEE80211_M_HOSTAP      = 6,    /* Software Access Point */
    IEEE80211_M_MONITOR     = 8,    /* Monitor mode */
    IEEE80211_M_WDS         = 2,    /* WDS link */
    IEEE80211_M_BTAMP       = 9,    /* VAP for BT AMP */
    IEEE80211_M_BASE        = 13,    /* */
    IEEE80211_M_SAT         = 14,    /* */

    IEEE80211_M_ANY         = 0xFF  /* Any of the above; used by NDIS 6.x */
};

/*
 * 802.11n
 */
enum ieee80211_cwm_mode {
    IEEE80211_CWM_MODE20,
    IEEE80211_CWM_MODE2040,         
    IEEE80211_CWM_MODE40,
    IEEE80211_CWM_MODEMAX

};

enum ieee80211_cwm_extprotspacing {
    IEEE80211_CWM_EXTPROTSPACING20,
    IEEE80211_CWM_EXTPROTSPACING25,
    IEEE80211_CWM_EXTPROTSPACINGMAX
};

enum ieee80211_cwm_width {
    IEEE80211_CWM_WIDTH20,
    IEEE80211_CWM_WIDTH40
};

enum ieee80211_cwm_extprotmode {
    IEEE80211_CWM_EXTPROTNONE,      /* no protection */
    IEEE80211_CWM_EXTPROTCTSONLY,   /* CTS to self */
    IEEE80211_CWM_EXTPROTRTSCTS,    /* RTS-CTS */
    IEEE80211_CWM_EXTPROTMAX
};

/* CWM (Channel Width Management) Information */
struct ieee80211_cwm {

    /* Configuration */
    enum ieee80211_cwm_mode           cw_mode;              /* CWM mode */
    int8_t                            cw_extoffset;         /* CWM Extension Channel Offset */
    enum ieee80211_cwm_extprotmode    cw_extprotmode;       /* CWM Extension Channel Protection Mode */
    enum ieee80211_cwm_extprotspacing cw_extprotspacing;    /* CWM Extension Channel Protection Spacing */
    u_int32_t                         cw_enable;            /* CWM State Machine Enabled */
    u_int32_t                         cw_extbusythreshold;  /* CWM Extension Channel Busy Threshold */

    /* State */
    enum ieee80211_cwm_width          cw_width;             /* CWM channel width */
};                                          


enum ieee80211_fixed_rate_mode {
    IEEE80211_FIXED_RATE_NONE  = 0,
    IEEE80211_FIXED_RATE_MCS   = 1,  /* HT rates */
    IEEE80211_FIXED_RATE_LEGACY  = 2   /* legacy rates */
};

/* Holds the fixed rate information for each VAP */
struct ieee80211_fixed_rate {
    enum ieee80211_fixed_rate_mode  mode;
    u_int32_t                       series;
    u_int32_t                       retries;
};

/*
 * 802.11g protection mode.
 */
enum ieee80211_protmode {
    IEEE80211_PROT_NONE     = 0,    /* no protection */
    IEEE80211_PROT_CTSONLY  = 1,    /* CTS to self */
    IEEE80211_PROT_RTSCTS   = 2,    /* RTS-CTS */
};

/*
 * Roaming mode is effectively who controls the operation
 * of the 802.11 state machine when operating as a station.
 * State transitions are controlled either by the driver
 * (typically when management frames are processed by the
 * hardware/firmware), the host (auto/normal operation of
 * the 802.11 layer), or explicitly through ioctl requests
 * when applications like wpa_supplicant want control.
 */
enum ieee80211_roamingmode {
    IEEE80211_ROAMING_DEVICE= 0,    /* driver/hardware control */
    IEEE80211_ROAMING_AUTO  = 1,    /* 802.11 layer control */
    IEEE80211_ROAMING_MANUAL= 2,    /* application control */
};

/*
 * Scanning mode controls station scanning work; this is
 * used only when roaming mode permits the host to select
 * the bss to join/channel to use.
 */
enum ieee80211_scanmode {
    IEEE80211_SCAN_DEVICE   = 0,    /* driver/hardware control */
    IEEE80211_SCAN_BEST     = 1,    /* 802.11 layer selects best */
    IEEE80211_SCAN_FIRST    = 2,    /* take first suitable candidate */
};

/*
 * Channels are specified by frequency and attributes.
 */
struct ieee80211_channel {
    u_int16_t       ic_freq;        /* setting in Mhz */
    u_int32_t       ic_flags;       /* see below */
    u_int8_t        ic_flagext;     /* see below */
    u_int8_t        ic_ieee;        /* IEEE channel number */
    int8_t          ic_maxregpower; /* maximum regulatory tx power in dBm */
    int8_t          ic_maxpower;    /* maximum tx power in dBm */
    int8_t          ic_minpower;    /* minimum tx power in dBm */
    u_int8_t        ic_regClassId;  /* regClassId of this channel */        
};

struct ieee80211_channel_list {
    int                         cl_nchans;
    struct ieee80211_channel    *cl_channels;
};

#define IEEE80211_CHAN_MAX      255
#define IEEE80211_CHAN_BYTES    32      /* howmany(IEEE80211_CHAN_MAX, NBBY) */
#define IEEE80211_CHAN_ANY      (-1)    /* token for ``any channel'' */
#define IEEE80211_CHAN_ANYC \
        ((struct ieee80211_channel *) IEEE80211_CHAN_ANY)

#define IEEE80211_CHAN_DEFAULT          11
#define IEEE80211_CHAN_DEFAULT_11A      52
#define IEEE80211_CHAN_ADHOC_DEFAULT1   10
#define IEEE80211_CHAN_ADHOC_DEFAULT2   11

#define IEEE80211_RADAR_11HCOUNT        5
#define IEEE80211_RADAR_TEST_MUTE_CHAN  36      /* Move to channel 36 for mute test */
#define IEEE80211_RADAR_DETECT_DEFAULT_DELAY    60000   /* STA ignore AP beacons during this period in millisecond */


/* bits 0-3 are for private use by drivers */
/* channel attributes */
#define IEEE80211_CHAN_TURBO            0x00010 /* Turbo channel */
#define IEEE80211_CHAN_CCK              0x00020 /* CCK channel */
#define IEEE80211_CHAN_OFDM             0x00040 /* OFDM channel */
#define IEEE80211_CHAN_2GHZ             0x00080 /* 2 GHz spectrum channel. */
#define IEEE80211_CHAN_5GHZ             0x00100 /* 5 GHz spectrum channel */
#define IEEE80211_CHAN_PASSIVE          0x00200 /* Only passive scan allowed */
#define IEEE80211_CHAN_DYN              0x00400 /* Dynamic CCK-OFDM channel */
#define IEEE80211_CHAN_GFSK             0x00800 /* GFSK channel (FHSS PHY) */
#define IEEE80211_CHAN_RADAR            0x01000 /* Radar found on channel */
#define IEEE80211_CHAN_STURBO           0x02000 /* 11a static turbo channel only */
#define IEEE80211_CHAN_HALF             0x04000 /* Half rate channel */
#define IEEE80211_CHAN_QUARTER          0x08000 /* Quarter rate channel */
#define IEEE80211_CHAN_HT20             0x10000 /* HT 20 channel */
#define IEEE80211_CHAN_HT40PLUS         0x20000 /* HT 40 with extension channel above */
#define IEEE80211_CHAN_HT40MINUS        0x40000 /* HT 40 with extension channel below */
#define IEEE80211_CHAN_HT40INTOL        0x80000 /* HT 40 Intolerant */

/* flagext */
#define IEEE80211_CHAN_DFS              0x0002  /* DFS required on channel */
#define IEEE80211_CHAN_DFS_CLEAR        0x0008  /* if channel has been checked for DFS */
#define IEEE80211_CHAN_11D_EXCLUDED     0x0010  /* excluded in 11D */
#define IEEE80211_CHAN_CSA_RECEIVED     0x0020  /* Channel Switch Announcement received on this channel */
#define IEEE80211_CHAN_DISALLOW_ADHOC   0x0040  /* ad-hoc is not allowed */

/*
 * Useful combinations of channel characteristics.
 */
#define IEEE80211_CHAN_FHSS \
    (IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_GFSK)
#define IEEE80211_CHAN_A \
    (IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_OFDM)
#define IEEE80211_CHAN_B \
    (IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_CCK)
#define IEEE80211_CHAN_PUREG \
    (IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_OFDM)
#define IEEE80211_CHAN_G \
    (IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_DYN)
#define IEEE80211_CHAN_108A \
    (IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_OFDM | IEEE80211_CHAN_TURBO)
#define IEEE80211_CHAN_108G \
    (IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_OFDM | IEEE80211_CHAN_TURBO)
#define IEEE80211_CHAN_ST \
    (IEEE80211_CHAN_108A | IEEE80211_CHAN_STURBO)

#define IEEE80211_CHAN_11NG_HT20 \
    (IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_HT20)
#define IEEE80211_CHAN_11NA_HT20 \
    (IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_HT20)
#define IEEE80211_CHAN_11NG_HT40PLUS \
    (IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_HT40PLUS)
#define IEEE80211_CHAN_11NG_HT40MINUS \
    (IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_HT40MINUS)
#define IEEE80211_CHAN_11NA_HT40PLUS \
    (IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_HT40PLUS)
#define IEEE80211_CHAN_11NA_HT40MINUS \
    (IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_HT40MINUS)

#define IEEE80211_CHAN_ALL \
    (IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_GFSK | \
    IEEE80211_CHAN_CCK | IEEE80211_CHAN_OFDM | IEEE80211_CHAN_DYN | \
    IEEE80211_CHAN_HT20 | IEEE80211_CHAN_HT40PLUS | IEEE80211_CHAN_HT40MINUS )
#define IEEE80211_CHAN_ALLTURBO \
    (IEEE80211_CHAN_ALL | IEEE80211_CHAN_TURBO | IEEE80211_CHAN_STURBO)

#define IEEE80211_IS_CHAN_FHSS(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_FHSS) == IEEE80211_CHAN_FHSS)
#define IEEE80211_IS_CHAN_A(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_A) == IEEE80211_CHAN_A)
#define IEEE80211_IS_CHAN_B(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_B) == IEEE80211_CHAN_B)
#define IEEE80211_IS_CHAN_PUREG(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_PUREG) == IEEE80211_CHAN_PUREG)
#define IEEE80211_IS_CHAN_G(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_G) == IEEE80211_CHAN_G)
#define IEEE80211_IS_CHAN_ANYG(_c) \
    (IEEE80211_IS_CHAN_PUREG(_c) || IEEE80211_IS_CHAN_G(_c))
#define IEEE80211_IS_CHAN_ST(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_ST) == IEEE80211_CHAN_ST)
#define IEEE80211_IS_CHAN_108A(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_108A) == IEEE80211_CHAN_108A)
#define IEEE80211_IS_CHAN_108G(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_108G) == IEEE80211_CHAN_108G)

#define IEEE80211_IS_CHAN_2GHZ(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_2GHZ) != 0)
#define IEEE80211_IS_CHAN_5GHZ(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_5GHZ) != 0)
#define IEEE80211_IS_CHAN_OFDM(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_OFDM) != 0)
#define IEEE80211_IS_CHAN_CCK(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_CCK) != 0)
#define IEEE80211_IS_CHAN_GFSK(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_GFSK) != 0)
#define IEEE80211_IS_CHAN_TURBO(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_TURBO) != 0)
#define IEEE80211_IS_CHAN_STURBO(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_STURBO) != 0)
#define IEEE80211_IS_CHAN_DTURBO(_c) \
    (((_c)->ic_flags & \
    (IEEE80211_CHAN_TURBO | IEEE80211_CHAN_STURBO)) == IEEE80211_CHAN_TURBO)
#define IEEE80211_IS_CHAN_HALF(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_HALF) != 0)
#define IEEE80211_IS_CHAN_QUARTER(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_QUARTER) != 0)
#define IEEE80211_IS_CHAN_PASSIVE(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_PASSIVE) != 0)

#define IEEE80211_IS_CHAN_DFS(_c) \
    (((_c)->ic_flagext & (IEEE80211_CHAN_DFS|IEEE80211_CHAN_DFS_CLEAR)) == IEEE80211_CHAN_DFS)
#define IEEE80211_IS_CHAN_DFSFLAG(_c) \
    (((_c)->ic_flagext & IEEE80211_CHAN_DFS) == IEEE80211_CHAN_DFS)
#define IEEE80211_IS_CHAN_DISALLOW_ADHOC(_c) \
    (((_c)->ic_flagext & IEEE80211_CHAN_DISALLOW_ADHOC) != 0)
#define IEEE80211_IS_CHAN_11D_EXCLUDED(_c) \
    (((_c)->ic_flagext & IEEE80211_CHAN_11D_EXCLUDED) != 0)
#define IEEE80211_IS_CHAN_CSA(_c) \
    (((_c)->ic_flagext & IEEE80211_CHAN_CSA_RECEIVED) != 0)
#define IEEE80211_IS_CHAN_ODD(_c) \
    (((_c)->ic_freq == 5170) || ((_c)->ic_freq == 5190) || \
     ((_c)->ic_freq == 5210) || ((_c)->ic_freq == 5230))

#define IEEE80211_IS_CHAN_11NG_HT20(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_11NG_HT20) == IEEE80211_CHAN_11NG_HT20)
#define IEEE80211_IS_CHAN_11NA_HT20(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_11NA_HT20) == IEEE80211_CHAN_11NA_HT20)
#define IEEE80211_IS_CHAN_11NG_HT40PLUS(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_11NG_HT40PLUS) == IEEE80211_CHAN_11NG_HT40PLUS)
#define IEEE80211_IS_CHAN_11NG_HT40MINUS(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_11NG_HT40MINUS) == IEEE80211_CHAN_11NG_HT40MINUS)
#define IEEE80211_IS_CHAN_11NA_HT40PLUS(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_11NA_HT40PLUS) == IEEE80211_CHAN_11NA_HT40PLUS)
#define IEEE80211_IS_CHAN_11NA_HT40MINUS(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_11NA_HT40MINUS) == IEEE80211_CHAN_11NA_HT40MINUS)

#define IEEE80211_IS_CHAN_11N(_c) \
    (((_c)->ic_flags & (IEEE80211_CHAN_HT20 | IEEE80211_CHAN_HT40PLUS | IEEE80211_CHAN_HT40MINUS)) != 0)
#define IEEE80211_IS_CHAN_11N_HT20(_c) \
    (((_c)->ic_flags & (IEEE80211_CHAN_HT20)) != 0)
#define IEEE80211_IS_CHAN_11N_HT40(_c) \
    (((_c)->ic_flags & (IEEE80211_CHAN_HT40PLUS | IEEE80211_CHAN_HT40MINUS)) != 0)
#define IEEE80211_IS_CHAN_11NG(_c) \
    (IEEE80211_IS_CHAN_2GHZ((_c)) && IEEE80211_IS_CHAN_11N((_c)))
#define IEEE80211_IS_CHAN_11NA(_c) \
    (IEEE80211_IS_CHAN_5GHZ((_c)) && IEEE80211_IS_CHAN_11N((_c)))

#define IEEE80211_IS_CHAN_HT20_CAPABLE(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_HT20) == IEEE80211_CHAN_HT20)
#define IEEE80211_IS_CHAN_HT40PLUS_CAPABLE(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_HT40PLUS) == IEEE80211_CHAN_HT40PLUS)
#define IEEE80211_IS_CHAN_HT40MINUS_CAPABLE(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_HT40MINUS) == IEEE80211_CHAN_HT40MINUS)
#define IEEE80211_IS_CHAN_HT40_CAPABLE(_c) \
    (IEEE80211_IS_CHAN_HT40PLUS_CAPABLE(_c) || IEEE80211_IS_CHAN_HT40MINUS_CAPABLE(_c))
#define IEEE80211_IS_CHAN_HT_CAPABLE(_c) \
    (IEEE80211_IS_CHAN_HT20_CAPABLE(_c) || IEEE80211_IS_CHAN_HT40_CAPABLE(_c))
#define IEEE80211_IS_CHAN_11N_CTL_CAPABLE(_c)  IEEE80211_IS_CHAN_HT20_CAPABLE(_c)
#define IEEE80211_IS_CHAN_11N_CTL_U_CAPABLE(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_HT40PLUS) == IEEE80211_CHAN_HT40PLUS)
#define IEEE80211_IS_CHAN_11N_CTL_L_CAPABLE(_c) \
    (((_c)->ic_flags & IEEE80211_CHAN_HT40MINUS) == IEEE80211_CHAN_HT40MINUS)
#define IEEE80211_IS_CHAN_11N_CTL_40_CAPABLE(_c) \
    (IEEE80211_IS_CHAN_11N_CTL_U_CAPABLE((_c)) || IEEE80211_IS_CHAN_11N_CTL_L_CAPABLE((_c)))

#define IEEE80211_IS_CHAN_RADAR(_c)    \
    (((_c)->ic_flags & IEEE80211_CHAN_RADAR) == IEEE80211_CHAN_RADAR)
#define IEEE80211_CHAN_SET_RADAR(_c)    \
    ((_c)->ic_flags |= IEEE80211_CHAN_RADAR)
#define IEEE80211_CHAN_CLR_RADAR(_c)    \
    ((_c)->ic_flags &= ~IEEE80211_CHAN_RADAR)
#define IEEE80211_CHAN_SET_DISALLOW_ADHOC(_c)   \
    ((_c)->ic_flagext |= IEEE80211_CHAN_DISALLOW_ADHOC)
#define IEEE80211_CHAN_CLR_DISALLOW_ADHOC(_c)	\
    ((_c)->ic_flagext &= ~IEEE80211_CHAN_DISALLOW_ADHOC)
#define IEEE80211_CHAN_SET_DFS(_c)  \
    ((_c)->ic_flagext |= (IEEE80211_CHAN_DFS|IEEE80211_CHAN_DFS_CLEAR))
#define IEEE80211_CHAN_EXCLUDE_11D(_c)  \
    ((_c)->ic_flagext |= IEEE80211_CHAN_11D_EXCLUDED)

/* channel encoding for FH phy */
#define IEEE80211_FH_CHANMOD            80
#define IEEE80211_FH_CHAN(set,pat)      (((set)-1)*IEEE80211_FH_CHANMOD+(pat))
#define IEEE80211_FH_CHANSET(chan)      ((chan)/IEEE80211_FH_CHANMOD+1)
#define IEEE80211_FH_CHANPAT(chan)      ((chan)%IEEE80211_FH_CHANMOD)

/*
 * 802.11 rate set.
 */
#define IEEE80211_RATE_SIZE     8               /* 802.11 standard */
#define IEEE80211_RATE_MAXSIZE  36              /* max rates we'll handle */
#define IEEE80211_HT_RATE_SIZE  128
#define IEEE80211_RATE_SINGLE_STREAM_MCS_MAX     7  /* MCS7 */

#define IEEE80211_RATE_MCS      0x8000
#define IEEE80211_RATE_MCS_VAL  0x7FFF

#define IEEE80211_RATE_IDX_ENTRY(val, idx) (((val&(0xff<<(idx*8)))>>(idx*8)))

/*
 * RSSI range
 */
#define IEEE80211_RSSI_MAX           -10   /* in db */
#define IEEE80211_RSSI_MIN           -200

/*
 * 11n A-MPDU & A-MSDU limits
 */
#define IEEE80211_AMPDU_LIMIT_MIN           (1 * 1024)
#define IEEE80211_AMPDU_LIMIT_MAX           (64 * 1024 - 1)
#define IEEE80211_AMPDU_LIMIT_DEFAULT       IEEE80211_AMPDU_LIMIT_MAX
#define IEEE80211_AMPDU_SUBFRAME_MIN        2 
#define IEEE80211_AMPDU_SUBFRAME_MAX        64 
#define IEEE80211_AMPDU_SUBFRAME_DEFAULT    32 
#define IEEE80211_AMSDU_LIMIT_MAX           4096
#define IEEE80211_RIFS_AGGR_DIV             10

struct ieee80211_rateset {
    u_int8_t                rs_nrates;
    u_int8_t                rs_rates[IEEE80211_RATE_MAXSIZE];
};

struct ieee80211_roam {
    int8_t                  rssi11a;        /* rssi thresh for 11a bss */
    int8_t                  rssi11b;        /* for 11g sta in 11b bss */
    int8_t                  rssi11bOnly;    /* for 11b sta */
    u_int8_t                pad1;
    u_int8_t                rate11a;        /* rate thresh for 11a bss */
    u_int8_t                rate11b;        /* for 11g sta in 11b bss */
    u_int8_t                rate11bOnly;    /* for 11b sta */
    u_int8_t                pad2;
};

#define IEEE80211_TID_SIZE      17 /* total number of TIDs */
#define IEEE80211_NON_QOS_SEQ   16 /* index for non-QoS (including management) sequence number space */

#define IEEE80211_ADDR_LEN  6       /* size of 802.11 address */

/* crypto related defines*/
#define IEEE80211_KEYBUF_SIZE   16
#define IEEE80211_MICBUF_SIZE   (8+8)   /* space for both tx+rx keys */

enum ieee80211_clist_cmd {
    CLIST_UPDATE,
    CLIST_DFS_UPDATE,
    CLIST_NEW_COUNTRY
};

enum ieee80211_nawds_param {
    IEEE80211_NAWDS_PARAM_NUM = 0,
    IEEE80211_NAWDS_PARAM_MODE,
    IEEE80211_NAWDS_PARAM_DEFCAPS,
    IEEE80211_NAWDS_PARAM_OVERRIDE,
};

#


/*
 * 802.11 protocol definitions.
 */

/* is 802.11 address multicast/broadcast? */
#define IEEE80211_IS_MULTICAST(_a)  (*(_a) & 0x01)

#define IEEE80211_IS_IPV4_MULTICAST(_a)  (*(_a) == 0x01)

#define IEEE80211_IS_IPV6_MULTICAST(_a)         \
    ((_a)[0] == 0x33 &&                         \
     (_a)[1] == 0x33)


#define IEEE80211_IS_BROADCAST(_a)              \
    ((_a)[0] == 0xff &&                         \
     (_a)[1] == 0xff &&                         \
     (_a)[2] == 0xff &&                         \
     (_a)[3] == 0xff &&                         \
     (_a)[4] == 0xff &&                         \
     (_a)[5] == 0xff)

/* IEEE 802.11 PLCP header */
struct ieee80211_plcp_hdr {
    u_int16_t   i_sfd;
    u_int8_t    i_signal;
    u_int8_t    i_service;
    u_int16_t   i_length;
    u_int16_t   i_crc;
} __packed;

#define IEEE80211_PLCP_SFD      0xF3A0
#define IEEE80211_PLCP_SERVICE  0x00

/*
 * generic definitions for IEEE 802.11 frames
 */
struct ieee80211_frame {
    u_int8_t    i_fc[2];
    u_int8_t    i_dur[2];
    union {
        struct {
            u_int8_t    i_addr1[IEEE80211_ADDR_LEN];
            u_int8_t    i_addr2[IEEE80211_ADDR_LEN];
            u_int8_t    i_addr3[IEEE80211_ADDR_LEN];
        };
        u_int8_t    i_addr_all[3 * IEEE80211_ADDR_LEN];
    };
    u_int8_t    i_seq[2];
    /* possibly followed by addr4[IEEE80211_ADDR_LEN]; */
    /* see below */
} __packed;

struct ieee80211_qosframe {
    u_int8_t    i_fc[2];
    u_int8_t    i_dur[2];
    u_int8_t    i_addr1[IEEE80211_ADDR_LEN];
    u_int8_t    i_addr2[IEEE80211_ADDR_LEN];
    u_int8_t    i_addr3[IEEE80211_ADDR_LEN];
    u_int8_t    i_seq[2];
    u_int8_t    i_qos[2];
    /* possibly followed by addr4[IEEE80211_ADDR_LEN]; */
    /* see below */
} __packed;

struct ieee80211_qoscntl {
    u_int8_t    i_qos[2];
};

struct ieee80211_frame_addr4 {
    u_int8_t    i_fc[2];
    u_int8_t    i_dur[2];
    u_int8_t    i_addr1[IEEE80211_ADDR_LEN];
    u_int8_t    i_addr2[IEEE80211_ADDR_LEN];
    u_int8_t    i_addr3[IEEE80211_ADDR_LEN];
    u_int8_t    i_seq[2];
    u_int8_t    i_addr4[IEEE80211_ADDR_LEN];
} __packed;

struct ieee80211_qosframe_addr4 {
    u_int8_t    i_fc[2];
    u_int8_t    i_dur[2];
    u_int8_t    i_addr1[IEEE80211_ADDR_LEN];
    u_int8_t    i_addr2[IEEE80211_ADDR_LEN];
    u_int8_t    i_addr3[IEEE80211_ADDR_LEN];
    u_int8_t    i_seq[2];
    u_int8_t    i_addr4[IEEE80211_ADDR_LEN];
    u_int8_t    i_qos[2];
} __packed;

/* HTC frame for TxBF*/
// for TxBF RC
struct ieee80211_frame_min_one {
    u_int8_t    i_fc[2];
    u_int8_t    i_dur[2];
    u_int8_t    i_addr1[IEEE80211_ADDR_LEN];

} __packed;// For TxBF RC

struct ieee80211_qosframe_htc {
    u_int8_t    i_fc[2];
    u_int8_t    i_dur[2];
    u_int8_t    i_addr1[IEEE80211_ADDR_LEN];
    u_int8_t    i_addr2[IEEE80211_ADDR_LEN];
    u_int8_t    i_addr3[IEEE80211_ADDR_LEN];
    u_int8_t    i_seq[2];
    u_int8_t    i_qos[2];
    u_int8_t    i_htc[4];
    /* possibly followed by addr4[IEEE80211_ADDR_LEN]; */
    /* see below */
} __packed;
struct ieee80211_qosframe_htc_addr4 {
    u_int8_t    i_fc[2];
    u_int8_t    i_dur[2];
    u_int8_t    i_addr1[IEEE80211_ADDR_LEN];
    u_int8_t    i_addr2[IEEE80211_ADDR_LEN];
    u_int8_t    i_addr3[IEEE80211_ADDR_LEN];
    u_int8_t    i_seq[2];
    u_int8_t    i_addr4[IEEE80211_ADDR_LEN];
    u_int8_t    i_qos[2];
    u_int8_t    i_htc[4];
} __packed;
struct ieee80211_htc {
    u_int8_t    i_htc[4];
};
/*HTC frame for TxBF*/

struct ieee80211_ctlframe_addr2 {
    u_int8_t    i_fc[2];
    u_int8_t    i_aidordur[2]; /* AID or duration */
    u_int8_t    i_addr1[IEEE80211_ADDR_LEN];
    u_int8_t    i_addr2[IEEE80211_ADDR_LEN];
} __packed;

#define	IEEE80211_WHQ(wh)		((struct ieee80211_qosframe *)(wh))
#define	IEEE80211_WH4(wh)		((struct ieee80211_frame_addr4 *)(wh))
#define	IEEE80211_WHQ4(wh)		((struct ieee80211_qosframe_addr4 *)(wh))

#define IEEE80211_FC0_VERSION_MASK          0x03
#define IEEE80211_FC0_VERSION_SHIFT         0
#define IEEE80211_FC0_VERSION_0             0x00
#define IEEE80211_FC0_TYPE_MASK             0x0c
#define IEEE80211_FC0_TYPE_SHIFT            2
#define IEEE80211_FC0_TYPE_MGT              0x00
#define IEEE80211_FC0_TYPE_CTL              0x04
#define IEEE80211_FC0_TYPE_DATA             0x08

#define IEEE80211_FC0_SUBTYPE_MASK          0xf0
#define IEEE80211_FC0_SUBTYPE_SHIFT         4
/* for TYPE_MGT */
#define IEEE80211_FC0_SUBTYPE_ASSOC_REQ     0x00
#define IEEE80211_FC0_SUBTYPE_ASSOC_RESP    0x10
#define IEEE80211_FC0_SUBTYPE_REASSOC_REQ   0x20
#define IEEE80211_FC0_SUBTYPE_REASSOC_RESP  0x30
#define IEEE80211_FC0_SUBTYPE_PROBE_REQ     0x40
#define IEEE80211_FC0_SUBTYPE_PROBE_RESP    0x50
#define IEEE80211_FC0_SUBTYPE_BEACON        0x80
#define IEEE80211_FC0_SUBTYPE_ATIM          0x90
#define IEEE80211_FC0_SUBTYPE_DISASSOC      0xa0
#define IEEE80211_FC0_SUBTYPE_AUTH          0xb0
#define IEEE80211_FC0_SUBTYPE_DEAUTH        0xc0
#define IEEE80211_FC0_SUBTYPE_ACTION        0xd0
#define IEEE80211_FCO_SUBTYPE_ACTION_NO_ACK 0xe0
/* for TYPE_CTL */
#define IEEE80211_FC0_SUBTYPE_BRPOLL        0x40
#define IEEE80211_FC0_SUBTYPE_NDPA          0x50
#define IEEE80211_FCO_SUBTYPE_Control_Wrapper   0x70    // For TxBF RC
#define IEEE80211_FC0_SUBTYPE_BAR           0x80
#define IEEE80211_FC0_BLOCK_ACK             0x90
#define IEEE80211_FC0_SUBTYPE_PS_POLL       0xa0
#define IEEE80211_FC0_SUBTYPE_RTS           0xb0
#define IEEE80211_FC0_SUBTYPE_CTS           0xc0
#define IEEE80211_FC0_SUBTYPE_ACK           0xd0
#define IEEE80211_FC0_SUBTYPE_CF_END        0xe0
#define IEEE80211_FC0_SUBTYPE_CF_END_ACK    0xf0
/* for TYPE_DATA (bit combination) */
#define IEEE80211_FC0_SUBTYPE_DATA          0x00
#define IEEE80211_FC0_SUBTYPE_CF_ACK        0x10
#define IEEE80211_FC0_SUBTYPE_CF_POLL       0x20
#define IEEE80211_FC0_SUBTYPE_CF_ACPL       0x30
#define IEEE80211_FC0_SUBTYPE_NODATA        0x40
#define IEEE80211_FC0_SUBTYPE_CFACK         0x50
#define IEEE80211_FC0_SUBTYPE_CFPOLL        0x60
#define IEEE80211_FC0_SUBTYPE_CF_ACK_CF_ACK 0x70
#define IEEE80211_FC0_SUBTYPE_QOS           0x80
#define IEEE80211_FC0_SUBTYPE_QOS_NULL      0xc0

#define IEEE80211_FC1_DIR_MASK              0x03
#define IEEE80211_FC1_DIR_NODS              0x00    /* STA->STA */
#define IEEE80211_FC1_DIR_TODS              0x01    /* STA->AP  */
#define IEEE80211_FC1_DIR_FROMDS            0x02    /* AP ->STA */
#define IEEE80211_FC1_DIR_DSTODS            0x03    /* AP ->AP  */

#define IEEE80211_FC1_MORE_FRAG             0x04
#define IEEE80211_FC1_RETRY                 0x08
#define IEEE80211_FC1_PWR_MGT               0x10
#define IEEE80211_FC1_MORE_DATA             0x20
#define IEEE80211_FC1_WEP                   0x40
#define IEEE80211_FC1_ORDER                 0x80

#define IEEE80211_SEQ_FRAG_MASK             0x000f
#define IEEE80211_SEQ_FRAG_SHIFT            0
#define IEEE80211_SEQ_SEQ_MASK              0xfff0
#define IEEE80211_SEQ_SEQ_SHIFT             4
#define IEEE80211_SEQ_MAX                   4096

#define IEEE80211_SEQ_LEQ(a,b)  ((int)((a)-(b)) <= 0)


#define IEEE80211_QOS_TXOP                  0x00ff

#define IEEE80211_QOS_AMSDU                 0x80
#define IEEE80211_QOS_AMSDU_S               7
#define IEEE80211_QOS_ACKPOLICY             0x60
#define IEEE80211_QOS_ACKPOLICY_S           5
#define IEEE80211_QOS_EOSP                  0x10
#define IEEE80211_QOS_EOSP_S                4
#define IEEE80211_QOS_TID                   0x0f
#define IEEE80211_MFP_TID                   0xff

#define IEEE80211_HTC0_TRQ                  0x02
#define	IEEE80211_HTC2_CalPos               0x03
#define	IEEE80211_HTC2_CalSeq               0x0C
#define	IEEE80211_HTC2_CSI_NONCOMP_BF       0x80
#define	IEEE80211_HTC2_CSI_COMP_BF          0xc0

/* Set bits 14 and 15 to 1 when duration field carries Association ID */
#define IEEE80211_FIELD_TYPE_AID            0xC000

#define IEEE80211_IS_BEACON(_frame)    ((((_frame)->i_fc[0] & IEEE80211_FC0_TYPE_MASK) == IEEE80211_FC0_TYPE_MGT) && \
                                        (((_frame)->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) == IEEE80211_FC0_SUBTYPE_BEACON))
#define IEEE80211_IS_DATA(_frame)      (((_frame)->i_fc[0] & IEEE80211_FC0_TYPE_MASK) == IEEE80211_FC0_TYPE_DATA)

#define IEEE80211_IS_MFP_FRAME(_frame) ((((_frame)->i_fc[0] & IEEE80211_FC0_TYPE_MASK) == IEEE80211_FC0_TYPE_MGT) && \
                                        ((_frame)->i_fc[1] & IEEE80211_FC1_WEP) && \
                                        ((((_frame)->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) == IEEE80211_FC0_SUBTYPE_DEAUTH) || \
                                         (((_frame)->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) == IEEE80211_FC0_SUBTYPE_DISASSOC) || \
                                         (((_frame)->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) == IEEE80211_FC0_SUBTYPE_ACTION)))
#define IEEE80211_IS_AUTH(_frame)      ((((_frame)->i_fc[0] & IEEE80211_FC0_TYPE_MASK) == IEEE80211_FC0_TYPE_MGT) && \
                                        (((_frame)->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) == IEEE80211_FC0_SUBTYPE_AUTH))
#define IEEE80211_IS_PROBEREQ(_frame)  ((((_frame)->i_fc[0] & IEEE80211_FC0_TYPE_MASK) == IEEE80211_FC0_TYPE_MGT) && \
                                        (((_frame)->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) == IEEE80211_FC0_SUBTYPE_PROBE_REQ))

/* MCS Set */
#define IEEE80211_RX_MCS_1_STREAM_BYTE_OFFSET 0
#define IEEE80211_RX_MCS_2_STREAM_BYTE_OFFSET 1
#define IEEE80211_RX_MCS_3_STREAM_BYTE_OFFSET 2
#define IEEE80211_RX_MCS_4_STREAM_BYTE_OFFSET 3
#define IEEE80211_RX_MCS_ALL_NSTREAM_RATES 0xff
#define IEEE80211_TX_MCS_OFFSET 12

#define IEEE80211_TX_MCS_SET_DEFINED 0x01
#define IEEE80211_TX_RX_MCS_SET_NOT_EQUAL 0x02
#define IEEE80211_TX_1_SPATIAL_STREAMS 0x0
#define IEEE80211_TX_2_SPATIAL_STREAMS 0x06
#define IEEE80211_TX_3_SPATIAL_STREAMS 0x08
#define IEEE80211_TX_4_SPATIAL_STREAMS 0x0c
#define IEEE80211_MAX_SPATIAL_STREAMS 4
#define IEEE80211_TX_MAXIMUM_STREAMS_MASK     0x0c
#define IEEE80211_TX_UNEQUAL_MODULATION_MASK  0x10

#define IEEE80211_TX_MCS_SET 0x1f

/*
 * Subtype data: If bit 6 is set then the data frame contains no actual data.
 */
#define IEEE80211_FC0_SUBTYPE_NO_DATA_MASK  0x40
#define IEEE80211_CONTAIN_DATA(_subtype) \
    (! ((_subtype) & IEEE80211_FC0_SUBTYPE_NO_DATA_MASK))

#define IEEE8023_MAX_LEN 0x600 /* 1536 - larger is Ethernet II */
#define RFC1042_SNAP_ORGCODE_0 0x00
#define RFC1042_SNAP_ORGCODE_1 0x00
#define RFC1042_SNAP_ORGCODE_2 0x00

#define BTEP_SNAP_ORGCODE_0 0x00
#define BTEP_SNAP_ORGCODE_1 0x00
#define BTEP_SNAP_ORGCODE_2 0xf8

/* BT 3.0 */
#define BTAMP_SNAP_ORGCODE_0 0x00
#define BTAMP_SNAP_ORGCODE_1 0x19
#define BTAMP_SNAP_ORGCODE_2 0x58

/* Aironet OUI Codes */
#define AIRONET_SNAP_CODE_0  0x00
#define AIRONET_SNAP_CODE_1  0x40
#define AIRONET_SNAP_CODE_2  0x96

#define IEEE80211_LSIG_LEN  3
#define IEEE80211_HTSIG_LEN 6
#define IEEE80211_SB_LEN    2

#define IEEE80211_FD_FRAMECNTL_CAP              0x0020
#define IEEE80211_FD_FRAMECNTL_SHORTSSID        0x0040
#define IEEE80211_FD_FRAMECNTL_APCSN            0x0080
#define IEEE80211_FD_FRAMECNTL_ANO              0x0100
#define IEEE80211_FD_FRAMECNTL_CH_CENTERFREQ    0x0200
#define IEEE80211_FD_FRAMECNTL_PRIMARY_CH       0x0400
#define IEEE80211_FD_FRAMECNTL_RSN_INFO         0x0800
#define IEEE80211_FD_FRAMECNTL_LEN_PRES         0x1000
#define IEEE80211_FD_FRAMECNTL_MD_PRES          0x2000
#define IEEE80211_FD_FRAMECNTL_11B_AP_PRESENT   0x4000

#define IEEE80211_FD_IS_CAP_PRESENT(_v)         (_v & IEEE80211_FD_FRAMECNTL_CAP)
#define IEEE80211_FD_IS_SHORTSSID_PRESENT(_v)   (_v & IEEE80211_FD_FRAMECNTL_SHORTSSID)
#define IEEE80211_FD_IS_APCSN_PRESENT(_v)       (_v & IEEE80211_FD_FRAMECNTL_APCSN)
#define IEEE80211_FD_IS_ANO_PRESENT(_v)         (_v & IEEE80211_FD_FRAMECNTL_ANO)
#define IEEE80211_FD_IS_LEN_PRESENT(_v)         (_v & IEEE80211_FD_FRAMECNTL_LEN_PRES)

/*
 * Information element header format
 */
struct ieee80211_ie_header {
    u_int8_t    element_id;     /* Element Id */
    u_int8_t    length;         /* IE Length */
} __packed;

/*
 * Country information element.
 */
#define IEEE80211_COUNTRY_MAX_TRIPLETS (83)
struct ieee80211_ie_country {
    u_int8_t    country_id;
    u_int8_t    country_len;
    u_int8_t    country_str[3];
    u_int8_t    country_triplet[IEEE80211_COUNTRY_MAX_TRIPLETS*3];
} __packed;

/* does frame have QoS sequence control data */
#define IEEE80211_QOS_HAS_SEQ(wh) \
    (((wh)->i_fc[0] & \
      (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_QOS)) == \
      (IEEE80211_FC0_TYPE_DATA | IEEE80211_FC0_SUBTYPE_QOS))

#define WME_QOSINFO_UAPSD   0x80  /* Mask for U-APSD field */
#define WME_QOSINFO_COUNT   0x0f  /* Mask for Param Set Count field */
/*
 * WME/802.11e information element.
 */
struct ieee80211_ie_wme {
    u_int8_t    wme_id;         /* IEEE80211_ELEMID_VENDOR */
    u_int8_t    wme_len;        /* length in bytes */
    u_int8_t    wme_oui[3];     /* 0x00, 0x50, 0xf2 */
    u_int8_t    wme_type;       /* OUI type */
    u_int8_t    wme_subtype;    /* OUI subtype */
    u_int8_t    wme_version;    /* spec revision */
    u_int8_t    wme_info;       /* QoS info */
} __packed;

struct ieee80211_ie_timeout {
        u_int8_t ie_type; /* Timeout IE */
        u_int8_t ie_len;
        u_int8_t interval_type;
        u_int32_t value;
} __packed;

/*
 * TS INFO part of the tspec element is a collection of bit flags
 */
#if _BYTE_ORDER == _BIG_ENDIAN
struct ieee80211_tsinfo_bitmap {
    u_int8_t    one       : 1,
                direction : 2,
                tid       : 4,
                reserved1 : 1;
    u_int8_t    reserved2 : 2,
                dot1Dtag  : 3,
                psb       : 1,
                reserved3 : 1,
                zero      : 1;
    u_int8_t    reserved5 : 7,
                reserved4 : 1;
} __packed;
#else
struct ieee80211_tsinfo_bitmap {
    u_int8_t    reserved1 : 1,
                tid       : 4,
                direction : 2,
                one       : 1;
    u_int8_t    zero      : 1,
                reserved3 : 1,
                psb       : 1,
                dot1Dtag  : 3,
                reserved2 : 2;
    u_int8_t    reserved4 : 1,
                reserved5 : 7;
}  __packed;
#endif

/*
 * WME/802.11e Tspec Element
 */
struct ieee80211_wme_tspec {
    u_int8_t    ts_id;
    u_int8_t    ts_len;
    u_int8_t    ts_oui[3];
    u_int8_t    ts_oui_type;
    u_int8_t    ts_oui_subtype;
    u_int8_t    ts_version;
    union {
        struct {
            u_int8_t    ts_tsinfo[3];
            u_int8_t    ts_nom_msdu[2];
            u_int8_t    ts_max_msdu[2];
            u_int8_t    ts_min_svc[4];
            u_int8_t    ts_max_svc[4];
            u_int8_t    ts_inactv_intv[4];
            u_int8_t    ts_susp_intv[4];
            u_int8_t    ts_start_svc[4];
            u_int8_t    ts_min_rate[4];
            u_int8_t    ts_mean_rate[4];
            u_int8_t    ts_peak_rate[4];
            u_int8_t    ts_max_burst[4];
            u_int8_t    ts_delay[4];
            u_int8_t    ts_min_phy[4];
            u_int8_t    ts_surplus[2];
            u_int8_t    ts_medium_time[2];
        };
        u_int8_t wme_info_all[55];
    };
} __packed;

/*
 * WME AC parameter field
 */
struct ieee80211_wme_acparams {
    u_int8_t    acp_aci_aifsn;
    u_int8_t    acp_logcwminmax;
    u_int16_t   acp_txop;
} __packed;

#define IEEE80211_WME_PARAM_LEN 24
#define WME_NUM_AC              4       /* 4 AC categories */

#define WME_PARAM_ACI           0x60    /* Mask for ACI field */
#define WME_PARAM_ACI_S         5       /* Shift for ACI field */
#define WME_PARAM_ACM           0x10    /* Mask for ACM bit */
#define WME_PARAM_ACM_S         4       /* Shift for ACM bit */
#define WME_PARAM_AIFSN         0x0f    /* Mask for aifsn field */
#define WME_PARAM_AIFSN_S       0       /* Shift for aifsn field */
#define WME_PARAM_LOGCWMIN      0x0f    /* Mask for CwMin field (in log) */
#define WME_PARAM_LOGCWMIN_S    0       /* Shift for CwMin field */
#define WME_PARAM_LOGCWMAX      0xf0    /* Mask for CwMax field (in log) */
#define WME_PARAM_LOGCWMAX_S    4       /* Shift for CwMax field */

#define WME_AC_TO_TID(_ac) (       \
    ((_ac) == WME_AC_VO) ? 6 : \
    ((_ac) == WME_AC_VI) ? 5 : \
    ((_ac) == WME_AC_BK) ? 1 : \
    0)

#define TID_TO_WME_AC(_tid) (      \
    (((_tid) == 0) || ((_tid) == 3)) ? WME_AC_BE : \
    (((_tid) == 1) || ((_tid) == 2)) ? WME_AC_BK : \
    (((_tid) == 4) || ((_tid) == 5)) ? WME_AC_VI : \
    WME_AC_VO)

/*
 * WME Parameter Element
 */
struct ieee80211_wme_param {
    u_int8_t                        param_id;
    u_int8_t                        param_len;
    u_int8_t                        param_oui[3];
    u_int8_t                        param_oui_type;
    u_int8_t                        param_oui_sybtype;
    u_int8_t                        param_version;
    u_int8_t                        param_qosInfo;
    u_int8_t                        param_reserved;
    struct ieee80211_wme_acparams   params_acParams[WME_NUM_AC];
} __packed;

/*
 * WME U-APSD qos info field defines
 */
#define WME_CAPINFO_UAPSD_EN                    0x00000080
#define WME_CAPINFO_UAPSD_VO                    0x00000001
#define WME_CAPINFO_UAPSD_VI                    0x00000002
#define WME_CAPINFO_UAPSD_BK                    0x00000004
#define WME_CAPINFO_UAPSD_BE                    0x00000008
#define WME_CAPINFO_UAPSD_ACFLAGS_SHIFT         0
#define WME_CAPINFO_UAPSD_ACFLAGS_MASK          0xF
#define WME_CAPINFO_UAPSD_MAXSP_SHIFT           5
#define WME_CAPINFO_UAPSD_MAXSP_MASK            0x3
#define WME_CAPINFO_IE_OFFSET                   8
#define WME_UAPSD_MAXSP(_qosinfo) (((_qosinfo) >> WME_CAPINFO_UAPSD_MAXSP_SHIFT) & WME_CAPINFO_UAPSD_MAXSP_MASK)
#define WME_UAPSD_AC_ENABLED(_ac, _qosinfo) ( (1<<(3 - (_ac))) &   \
        (((_qosinfo) >> WME_CAPINFO_UAPSD_ACFLAGS_SHIFT) & WME_CAPINFO_UAPSD_ACFLAGS_MASK) )

/* Mask used to determined whether all queues are UAPSD-enabled */
#define WME_CAPINFO_UAPSD_ALL                   (WME_CAPINFO_UAPSD_VO | \
                                                 WME_CAPINFO_UAPSD_VI | \
                                                 WME_CAPINFO_UAPSD_BK | \
                                                 WME_CAPINFO_UAPSD_BE)
#define WME_CAPINFO_UAPSD_NONE                  0

#define WME_UAPSD_AC_MAX_VAL 		1
#define WME_UAPSD_AC_INVAL		 	WME_UAPSD_AC_MAX_VAL+1

/*
 * Atheros Advanced Capability information element.
 */
struct ieee80211_ie_athAdvCap {
    u_int8_t    athAdvCap_id;           /* IEEE80211_ELEMID_VENDOR */
    u_int8_t    athAdvCap_len;          /* length in bytes */
    u_int8_t    athAdvCap_oui[3];       /* 0x00, 0x03, 0x7f */
    u_int8_t    athAdvCap_type;         /* OUI type */
    u_int16_t   athAdvCap_version;      /* spec revision */
    u_int8_t    athAdvCap_capability;   /* Capability info */
    u_int16_t   athAdvCap_defKeyIndex;
} __packed;

/*
 * Atheros Extended Capability information element.
 */
struct ieee80211_ie_ath_extcap {
    u_int8_t    ath_extcap_id;          /* IEEE80211_ELEMID_VENDOR */
    u_int8_t    ath_extcap_len;         /* length in bytes */
    u_int8_t    ath_extcap_oui[3];      /* 0x00, 0x03, 0x7f */
    u_int8_t    ath_extcap_type;        /* OUI type */
    u_int8_t    ath_extcap_subtype;     /* OUI subtype */
    u_int8_t    ath_extcap_version;     /* spec revision */
    u_int32_t   ath_extcap_extcap              : 16,  /* B0-15  extended capabilities */
                ath_extcap_weptkipaggr_rxdelim : 8,   /* B16-23 num delimiters for receiving WEP/TKIP aggregates */
                ath_extcap_reserved            : 8;   /* B24-31 reserved */
} __packed;

/*
 * Atheros XR information element.
 */
struct ieee80211_xr_param {
    u_int8_t    param_id;
    u_int8_t    param_len;
    u_int8_t    param_oui[3];
    u_int8_t    param_oui_type;
    u_int8_t    param_oui_sybtype;
    u_int8_t    param_version;
    u_int8_t    param_Info;
    u_int8_t    param_base_bssid[IEEE80211_ADDR_LEN];
    u_int8_t    param_xr_bssid[IEEE80211_ADDR_LEN];
    u_int16_t   param_xr_beacon_interval;
    u_int8_t    param_base_ath_capability;
    u_int8_t    param_xr_ath_capability;
} __packed;

/*
 * QCA Whole Home Coverage Rept Info information element.
 */
struct ieee80211_ie_whc_rept_info {
    u_int8_t    whc_rept_info_id;           /* IEEE80211_ELEMID_VENDOR */
    u_int8_t    whc_rept_info_len;          /* length in bytes */
    u_int8_t    whc_rept_info_oui[3];       /* 0x8c, 0xfd, 0xf0 */
    u_int8_t    whc_rept_info_type;
    u_int8_t    whc_rept_info_subtype;
    u_int8_t    whc_rept_info_version;
} __packed;

/*
 * QCA Whole Home Coverage AP Info information element.
 */
struct ieee80211_ie_whc_apinfo {
    u_int8_t    whc_apinfo_id;           /* IEEE80211_ELEMID_VENDOR */
    u_int8_t    whc_apinfo_len;          /* length in bytes */
    u_int8_t    whc_apinfo_oui[3];       /* 0x8c, 0xfd, 0xf0 */
    u_int8_t    whc_apinfo_type;
    u_int8_t    whc_apinfo_subtype;
    u_int8_t    whc_apinfo_version;
    u_int16_t   whc_apinfo_capabilities; /* SON/WDS/both */
    u_int8_t    whc_apinfo_root_ap_dist; /* in hops */
    u_int8_t    whc_apinfo_is_root_ap; /* is rootap or not */
    u_int8_t    whc_apinfo_num_conn_re; /* number of connected REs to this device */
    u_int8_t    whc_apinfo_uplink_bssid[IEEE80211_ADDR_LEN]; /* Parent device's BSSID */
    u_int16_t   whc_apinfo_uplink_rate; /* Rate in Mbps with parent device */
    u_int8_t    whc_apinfo_5g_bssid[IEEE80211_ADDR_LEN]; /* This device's 5G backhaulAP BSSID */
    u_int8_t    whc_apinfo_24g_bssid[IEEE80211_ADDR_LEN]; /* This device's 2.4G backhaulAP BSSID */
} __packed;

/*
 * SFA information element.
 */
struct ieee80211_ie_sfa {
    u_int8_t    sfa_id;         /* IEEE80211_ELEMID_VENDOR */
    u_int8_t    sfa_len;        /* length in bytes */
    u_int8_t    sfa_oui[3];     /* 0x00, 0x40, 0x96 */
    u_int8_t    sfa_type;       /* OUI type */
    u_int8_t    sfa_caps;       /* Capabilities */
} __packed;

/* Atheros capabilities */
#define IEEE80211_ATHC_TURBOP   0x0001      /* Turbo Prime */
#define IEEE80211_ATHC_COMP     0x0002      /* Compression */
#define IEEE80211_ATHC_FF       0x0004      /* Fast Frames */
#define IEEE80211_ATHC_XR       0x0008      /* Xtended Range support */
#define IEEE80211_ATHC_AR       0x0010      /* Advanced Radar support */
#define IEEE80211_ATHC_BURST    0x0020      /* Bursting - not negotiated */
#define IEEE80211_ATHC_WME      0x0040      /* CWMin tuning */
#define IEEE80211_ATHC_BOOST    0x0080      /* Boost */
/* Atheros extended capabilities */
/* OWL device capable of WDS workaround */
#define IEEE80211_ATHEC_OWLWDSWAR        0x0001
#define IEEE80211_ATHEC_WEPTKIPAGGR	     0x0002
#define IEEE80211_ATHEC_EXTRADELIMWAR    0x0004
#define IEEE80211_ATHEC_PN_CHECK_WAR     0x0008
/*
 * Management Frames
 */

/*
 * *** Platform-specific code?? ***
 * In Vista one must use bit fields of type (unsigned short = u_int16_t) to
 * ensure data structure is of the correct size. ANSI C used to specify only
 * "int" bit fields, which led to a larger structure size in Windows (32 bits).
 *
 * We must make sure the following construction is valid in all OS's.
 */
union ieee80211_capability {
    struct {
        u_int16_t    ess                 : 1;
        u_int16_t    ibss                : 1;
        u_int16_t    cf_pollable         : 1;
        u_int16_t    cf_poll_request     : 1;
        u_int16_t    privacy             : 1;
        u_int16_t    short_preamble      : 1;
        u_int16_t    pbcc                : 1;
        u_int16_t    channel_agility     : 1;
        u_int16_t    spectrum_management : 1;
        u_int16_t    qos                 : 1;
        u_int16_t    short_slot_time     : 1;
        u_int16_t    apsd                : 1;
        u_int16_t    reserved2           : 1;
        u_int16_t    dsss_ofdm           : 1;
        u_int16_t    del_block_ack       : 1;
        u_int16_t    immed_block_ack     : 1;
    };

    u_int16_t   value;
} __packed;

struct ieee80211_beacon_frame {
    u_int8_t                      timestamp[8];    /* the value of sender's TSFTIMER */
    u_int16_t                     beacon_interval; /* the number of time units between target beacon transmission times */
    union ieee80211_capability    capability;
/* Value of capability for every bit
#define IEEE80211_CAPINFO_ESS               0x0001
#define IEEE80211_CAPINFO_IBSS              0x0002
#define IEEE80211_CAPINFO_CF_POLLABLE       0x0004
#define IEEE80211_CAPINFO_CF_POLLREQ        0x0008
#define IEEE80211_CAPINFO_PRIVACY           0x0010
#define IEEE80211_CAPINFO_SHORT_PREAMBLE    0x0020
#define IEEE80211_CAPINFO_PBCC              0x0040
#define IEEE80211_CAPINFO_CHNL_AGILITY      0x0080
#define IEEE80211_CAPINFO_SPECTRUM_MGMT     0x0100
#define IEEE80211_CAPINFO_QOS               0x0200
#define IEEE80211_CAPINFO_SHORT_SLOTTIME    0x0400
#define IEEE80211_CAPINFO_APSD              0x0800
#define IEEE80211_CAPINFO_RADIOMEAS         0x1000
#define IEEE80211_CAPINFO_DSSSOFDM          0x2000
bits 14-15 are reserved
*/
    struct ieee80211_ie_header    info_elements;
} __packed;

/*
 * Management Action Frames
 */

/* generic frame format */
struct ieee80211_action {
    u_int8_t    ia_category;
    u_int8_t    ia_action;
} __packed;

 /* FTMRR request */
struct ieee80211_ftmrrreq {
    struct ieee80211_action  header;
    u_int8_t    dialogtoken;
    u_int16_t   num_repetitions;
    u_int8_t     elem[1];     /* varialbe len sub element fileds */
} __packed;

/* spectrum action frame header */
struct ieee80211_action_measrep_header {
    struct ieee80211_action action_header;
    u_int8_t                dialog_token;
} __packed;

/* FD Frame */
struct ieee80211_action_fd_header {
    struct ieee80211_action  action_header;
    u_int16_t   fd_frame_cntl; /* FILS Disovery Frame Control */
    u_int8_t    timestamp[8];  /* Time stamp */
    u_int16_t   bcn_interval;  /* Beacon Interval */
    u_int8_t    elem[1];     /* variable len sub element fileds */
} __packed;

/*
 * MIMO Control VHT
 */
struct ieee80211_vht_mimo_ctrl {
   u_int32_t    nc:3,
                nr:3,
                bw:2,
                ng:2,
                cb:1,
                fb_type:5,
                reserved:2,
                sound_dialog_toknum:6,
                unused:8;
} __packed;


/*
 * VHT Action Group ID Management
 */
struct ieee80211_action_vht_gid_mgmt {
    struct ieee80211_action      action_header;
    u_int8_t                     member_status[8];
    u_int8_t                     user_position[16];
} __packed;

/* categories */
#define IEEE80211_ACTION_CAT_SPECTRUM             0   /* Spectrum management */
#define IEEE80211_ACTION_CAT_QOS                  1   /* IEEE QoS  */
#define IEEE80211_ACTION_CAT_DLS                  2   /* DLS */
#define IEEE80211_ACTION_CAT_BA                   3   /* BA */
#define IEEE80211_ACTION_CAT_PUBLIC               4   /* Public Action Frame */
#define IEEE80211_ACTION_CAT_RADIO                5   /* Radio management */
#define IEEE80211_ACTION_CAT_HT                   7   /* HT per IEEE802.11n-D1.06 */
#define IEEE80211_ACTION_CAT_SA_QUERY             8   /* SA Query per IEEE802.11w, PMF */
#define IEEE80211_ACTION_CAT_PROT_DUAL            9   /* Protected Dual of public action frame */
#define IEEE80211_ACTION_CAT_WNM                 10   /* WNM Action frame */
#define IEEE80211_ACTION_CAT_UNPROT_WNM          11   /* Unprotected WNM action frame */
#define IEEE80211_ACTION_CAT_WMM_QOS             17   /* QoS from WMM specification */
#define IEEE80211_ACTION_CAT_FST                 18   /* FST action frame */
#define IEEE80211_ACTION_CAT_VHT                 21   /* VHT Action */
#define IEEE80211_ACTION_CAT_VENDOR             127   /* Vendor specific action frame */

/* Spectrum Management actions */
#define IEEE80211_ACTION_MEAS_REQUEST       0   /* Measure channels */
#define IEEE80211_ACTION_MEAS_REPORT        1
#define IEEE80211_ACTION_TPC_REQUEST        2   /* Transmit Power control */
#define IEEE80211_ACTION_TPC_REPORT         3
#define IEEE80211_ACTION_CHAN_SWITCH        4   /* 802.11h Channel Switch Announcement */
#define IEEE80211_ACTION_DYING_GASP         5   /*Dying Gasp*/
#define IEEE80211_ACTION_ULDL_LIMIT         6   /*ULDL Limit*/

/* HT actions */
#define IEEE80211_ACTION_HT_TXCHWIDTH       0   /* recommended transmission channel width */
#define IEEE80211_ACTION_HT_SMPOWERSAVE     1   /* Spatial Multiplexing (SM) Power Save */
#define IEEE80211_ACTION_HT_CSI             4   /* CSI Frame */
#define IEEE80211_ACTION_HT_NONCOMP_BF      5   /* Non-compressed Beamforming*/
#define IEEE80211_ACTION_HT_COMP_BF         6   /* Compressed Beamforming*/

/* VHT actions */
#define IEEE80211_ACTION_VHT_OPMODE         2  /* Operating  mode notification */

#define IEEE80211_ACTION_FILS_DISCOVERY     34 /* FILS Discovery Public Action */

/* VHT Group ID management*/
#define IEEE80211_ACTION_VHT_GROUP_ID       1  /* Group ID management */

/* Spectrum channel switch action frame after IE*/
/* Public Actions*/

/* HT - recommended transmission channel width */
struct ieee80211_action_ht_txchwidth {
    struct ieee80211_action     at_header;
    u_int8_t                    at_chwidth;
} __packed;

#define IEEE80211_A_HT_TXCHWIDTH_20         0
#define IEEE80211_A_HT_TXCHWIDTH_2040       1

/* HT - Spatial Multiplexing (SM) Power Save */
struct ieee80211_action_ht_smpowersave {
    struct ieee80211_action     as_header;
    u_int8_t                    as_control;
} __packed;

/*HT - CSI Frame */     //for TxBF RC
#define MIMO_CONTROL_LEN 6
struct ieee80211_action_ht_CSI {
    struct ieee80211_action     as_header;
    u_int8_t                   mimo_control[MIMO_CONTROL_LEN];
} __packed;

/*HT - V/CV report frame*/
struct ieee80211_action_ht_txbf_rpt {
    struct ieee80211_action     as_header;
    u_int8_t                   mimo_control[MIMO_CONTROL_LEN];
} __packed;

/*
 * 802.11ac Operating Mode  Notification
 */
struct ieee80211_ie_op_mode {
#if _BYTE_ORDER == _BIG_ENDIAN
        u_int8_t rx_nss_type        : 1,
                 rx_nss             : 3,
                 reserved           : 1,
                 bw_160_80p80       : 1,
                 ch_width           : 2;
#else
        u_int8_t ch_width           : 2,
                 bw_160_80p80       : 1,
                 reserved           : 1,
                 rx_nss             : 3,
                 rx_nss_type        : 1;
#endif
} __packed;

struct ieee80211_ie_op_mode_ntfy {
        u_int8_t    elem_id;
        u_int8_t    elem_len;
        struct ieee80211_ie_op_mode opmode;
} __packed;

#define DG_PKT_TYPE_INFORM 1
#define DG_PKT_TYPE_ACK	   2

struct ieee80211_uldl_limit {
    u_int32_t  	ipv4;
    u_int32_t  	ul_limit; 
    u_int32_t  	dl_limit; 
} __packed;

/* VHT - Uplink Downlink Limit*/
struct ieee80211_action_vht_uldl_limit {
    struct ieee80211_action     at_header;
    struct ieee80211_uldl_limit at_uldl_limit;
} __packed;

struct ieee80211_dying_gasp_ie {
    u_int8_t    type;
    u_int8_t	link_id;
    u_int16_t	seq_no;
    u_long   	ts;
    u_int32_t  	ipv4;
    u_int8_t	customer_name[32];
    
} __packed;

/* VHT - Dying gasp*/
struct ieee80211_action_vht_dying_gasp {
    struct ieee80211_action     at_header;
    struct ieee80211_dying_gasp_ie at_dying_gasp;
} __packed;

/* VHT - recommended Channel width and Nss */
struct ieee80211_action_vht_opmode {
    struct ieee80211_action     at_header;
    struct ieee80211_ie_op_mode at_op_mode;
} __packed;

/* Vendor specific IE for bandwidth NSS mapping*/
struct ieee80211_bwnss_mapping {
    u_int8_t    bnm_id;              /* IEEE80211_ELEMID_VENDOR */
    u_int8_t    bnm_len;             /* length in bytes */
    u_int8_t    bnm_oui[3];          /* 0x00, 0x03, 0x7f */
    u_int8_t    bnm_oui_type;        /* OUI type */
    u_int8_t    bnm_oui_subtype;     /* OUI Subtype */
    u_int8_t    bnm_oui_version;     /* OUI Version */
    u_int8_t    bnm_mapping;         /* bandwidth-NSS Mapping*/
} __packed;

/* Values defined for Bandwidth NSS Mapping */
#define IEEE80211_BW_NSS_MAP_1x1                (1)
#define IEEE80211_BW_NSS_MAP_2x2                (2)
#define IEEE80211_BW_NSS_MAP_3x3                (3)
#define IEEE80211_BW_NSS_MAP_4x4                (4)
#define IEEE80211_BW_NSS_MAP_5x5                (5)
#define IEEE80211_BW_NSS_MAP_6x6                (6)
#define IEEE80211_BW_NSS_MAP_7x7                (7)
#define IEEE80211_BW_NSS_MAP_8x8                (8)

/* Values defined for Bandwidth NSS Mapping advertising in prop IE */
#define IEEE80211_BW_NSS_ADV_IE_LEN                 (7)
#define IEEE80211_BW_NSS_ADV_MAP_160MHZ_S           (0)
#define IEEE80211_BW_NSS_ADV_MAP_160MHZ_M           (0x00000007)

/* Value defined to advertise 160/80_80 MHz Bandwidth NSS Mapping.
 * Note: Separate values for 160 MHz and 80+80 MHz are not advertised in
 * proprietary IE, since our architecture supports only same values for
 * 160 MHz and 80+80 MHz
 */
#define IEEE80211_BW_NSS_ADV_160(x)             (((x - 1) << IEEE80211_BW_NSS_ADV_MAP_160MHZ_S)\
                                                 & IEEE80211_BW_NSS_ADV_MAP_160MHZ_M)

/* Values defined for Bandwidth NSS Mapping being sent to FW */
#define IEEE80211_BW_NSS_FWCONF_MAP_ENABLE             (1 << 31)
#define IEEE80211_BW_NSS_FWCONF_MAP_160MHZ_S           (0)
#define IEEE80211_BW_NSS_FWCONF_MAP_160MHZ_M           (0x00000007)
#define IEEE80211_BW_NSS_FWCONF_MAP_80_80MHZ_S         (3)
#define IEEE80211_BW_NSS_FWCONF_MAP_80_80MHZ_M         (0x00000038)
#define IEEE80211_BW_NSS_FWCONF_MAP_M                  (0x0000003F)


#define IEEE80211_GET_BW_NSS_FWCONF_160(x)             ((((x) & IEEE80211_BW_NSS_FWCONF_MAP_160MHZ_M)\
                                                 >> IEEE80211_BW_NSS_FWCONF_MAP_160MHZ_S) + 1)

#define IEEE80211_GET_BW_NSS_FWCONF_80_80(x)           ((((x) & IEEE80211_BW_NSS_FWCONF_MAP_80_80MHZ_M)\
                                                    >> IEEE80211_BW_NSS_FWCONF_MAP_80_80MHZ_S) + 1)

/* Values defined to set 160 MHz Bandwidth NSS Mapping into FW*/

#define IEEE80211_BW_NSS_FWCONF_160(x)          (IEEE80211_BW_NSS_FWCONF_MAP_ENABLE |\
                                                 (((x - 1) << IEEE80211_BW_NSS_FWCONF_MAP_160MHZ_S) \
                                                   & IEEE80211_BW_NSS_FWCONF_MAP_160MHZ_M))

#define IEEE80211_BW_NSS_FWCONF_80_80(x)        (IEEE80211_BW_NSS_FWCONF_MAP_ENABLE |\
                                                 (((x - 1) << IEEE80211_BW_NSS_FWCONF_MAP_80_80MHZ_S) \
                                                   & IEEE80211_BW_NSS_FWCONF_MAP_80_80MHZ_M))

/* values defined for 'as_control' field per 802.11n-D1.06 */
#define IEEE80211_A_HT_SMPOWERSAVE_DISABLED     0x00   /* SM Power Save Disabled, SM packets ok  */
#define IEEE80211_A_HT_SMPOWERSAVE_ENABLED      0x01   /* SM Power Save Enabled bit  */
#define IEEE80211_A_HT_SMPOWERSAVE_MODE         0x02   /* SM Power Save Mode bit */
#define IEEE80211_A_HT_SMPOWERSAVE_RESERVED     0xFC   /* SM Power Save Reserved bits */

/* values defined for SM Power Save Mode bit */
#define IEEE80211_A_HT_SMPOWERSAVE_STATIC       0x00   /* Static, SM packets not ok */
#define IEEE80211_A_HT_SMPOWERSAVE_DYNAMIC      0x02   /* Dynamic, SM packets ok if preceded by RTS */

/* DLS actions */
#define IEEE80211_ACTION_DLS_REQUEST            0
#define IEEE80211_ACTION_DLS_RESPONSE           1
#define IEEE80211_ACTION_DLS_TEARDOWN           2

struct ieee80211_dls_request {
	struct ieee80211_action hdr;
    u_int8_t dst_addr[IEEE80211_ADDR_LEN];
    u_int8_t src_addr[IEEE80211_ADDR_LEN];
    u_int16_t capa_info;
    u_int16_t timeout;
} __packed;

struct ieee80211_dls_response {
	struct ieee80211_action hdr;
    u_int16_t statuscode;
    u_int8_t dst_addr[IEEE80211_ADDR_LEN];
    u_int8_t src_addr[IEEE80211_ADDR_LEN];
} __packed;

/* BA actions */
#define IEEE80211_ACTION_BA_ADDBA_REQUEST       0   /* ADDBA request */
#define IEEE80211_ACTION_BA_ADDBA_RESPONSE      1   /* ADDBA response */
#define IEEE80211_ACTION_BA_DELBA               2   /* DELBA */

struct ieee80211_ba_parameterset {
#if _BYTE_ORDER == _BIG_ENDIAN
        u_int16_t   buffersize      : 10,   /* B6-15  buffer size */
                    tid             : 4,    /* B2-5   TID */
                    bapolicy        : 1,    /* B1   block ack policy */
                    amsdusupported  : 1;    /* B0   amsdu supported */
#else
        u_int16_t   amsdusupported  : 1,    /* B0   amsdu supported */
                    bapolicy        : 1,    /* B1   block ack policy */
                    tid             : 4,    /* B2-5   TID */
                    buffersize      : 10;   /* B6-15  buffer size */
#endif
} __packed;

#define  IEEE80211_BA_POLICY_DELAYED      0
#define  IEEE80211_BA_POLICY_IMMEDIATE    1
#define  IEEE80211_BA_AMSDU_SUPPORTED     1

struct ieee80211_ba_seqctrl {
#if _BYTE_ORDER == _BIG_ENDIAN
        u_int16_t   startseqnum     : 12,    /* B4-15  starting sequence number */
                    fragnum         : 4;     /* B0-3  fragment number */
#else
        u_int16_t   fragnum         : 4,     /* B0-3  fragment number */
                    startseqnum     : 12;    /* B4-15  starting sequence number */
#endif
} __packed;

struct ieee80211_delba_parameterset {
#if _BYTE_ORDER == _BIG_ENDIAN
        u_int16_t   tid             : 4,     /* B12-15  tid */
                    initiator       : 1,     /* B11     initiator */
                    reserved0       : 11;    /* B0-10   reserved */
#else
        u_int16_t   reserved0       : 11,    /* B0-10   reserved */
                    initiator       : 1,     /* B11     initiator */
                    tid             : 4;     /* B12-15  tid */
#endif
} __packed;

/* BA - ADDBA request */
struct ieee80211_action_ba_addbarequest {
    struct ieee80211_action             rq_header;
    u_int8_t                            rq_dialogtoken;
    struct ieee80211_ba_parameterset    rq_baparamset;
    u_int16_t                           rq_batimeout;   /* in TUs */
    struct ieee80211_ba_seqctrl         rq_basequencectrl;
} __packed;

/* BA - ADDBA response */
struct ieee80211_action_ba_addbaresponse {
    struct ieee80211_action             rs_header;
    u_int8_t                            rs_dialogtoken;
    u_int16_t                           rs_statuscode;
    struct ieee80211_ba_parameterset    rs_baparamset;
    u_int16_t                           rs_batimeout;   /* in TUs */
} __packed;

/* BA - DELBA */
struct ieee80211_action_ba_delba {
    struct ieee80211_action                dl_header;
    struct ieee80211_delba_parameterset    dl_delbaparamset;
    u_int16_t                              dl_reasoncode;
} __packed;

/* MGT Notif actions */
#define IEEE80211_WMM_QOS_ACTION_SETUP_REQ    0
#define IEEE80211_WMM_QOS_ACTION_SETUP_RESP   1
#define IEEE80211_WMM_QOS_ACTION_TEARDOWN     2

#define IEEE80211_WMM_QOS_DIALOG_TEARDOWN     0
#define IEEE80211_WMM_QOS_DIALOG_SETUP        1

#define IEEE80211_WMM_QOS_TSID_DATA_TSPEC     6
#define IEEE80211_WMM_QOS_TSID_SIG_TSPEC      7

struct ieee80211_action_wmm_qos {
    struct ieee80211_action             ts_header;
    u_int8_t                            ts_dialogtoken;
    u_int8_t                            ts_statuscode;
    struct ieee80211_wme_tspec          ts_tspecie;
} __packed;

/*
 * Control frames.
 */
struct ieee80211_frame_min {
    u_int8_t    i_fc[2];
    u_int8_t    i_dur[2];
    u_int8_t    i_addr1[IEEE80211_ADDR_LEN];
    u_int8_t    i_addr2[IEEE80211_ADDR_LEN];
    /* FCS */
} __packed;

/*
 * BAR frame format
 */
#define IEEE80211_BAR_CTL_TID_M     0xF000      /* tid mask             */
#define IEEE80211_BAR_CTL_TID_S         12      /* tid shift            */
#define IEEE80211_BAR_CTL_NOACK     0x0001      /* no-ack policy        */
#define IEEE80211_BAR_CTL_COMBA     0x0004      /* compressed block-ack */

/*
 * SA Query Action mgmt Frame
 */
struct ieee80211_action_sa_query {
    struct ieee80211_action     sa_header;
    u_int16_t                   sa_transId;
};

typedef enum ieee80211_action_sa_query_type{
    IEEE80211_ACTION_SA_QUERY_REQUEST,
    IEEE80211_ACTION_SA_QUERY_RESPONSE
}ieee80211_action_sa_query_type_t;

struct ieee80211_frame_bar {
    u_int8_t    i_fc[2];
    u_int8_t    i_dur[2];
    u_int8_t    i_ra[IEEE80211_ADDR_LEN];
    u_int8_t    i_ta[IEEE80211_ADDR_LEN];
    u_int16_t   i_ctl;
    u_int16_t   i_seq;
    /* FCS */
} __packed;

struct ieee80211_frame_rts {
    u_int8_t    i_fc[2];
    u_int8_t    i_dur[2];
    u_int8_t    i_ra[IEEE80211_ADDR_LEN];
    u_int8_t    i_ta[IEEE80211_ADDR_LEN];
    /* FCS */
} __packed;

struct ieee80211_frame_cts {
    u_int8_t    i_fc[2];
    u_int8_t    i_dur[2];
    u_int8_t    i_ra[IEEE80211_ADDR_LEN];
    /* FCS */
} __packed;

struct ieee80211_frame_ack {
    u_int8_t    i_fc[2];
    u_int8_t    i_dur[2];
    u_int8_t    i_ra[IEEE80211_ADDR_LEN];
    /* FCS */
} __packed;

struct ieee80211_frame_pspoll {
    u_int8_t    i_fc[2];
    u_int8_t    i_aid[2];
    u_int8_t    i_bssid[IEEE80211_ADDR_LEN];
    u_int8_t    i_ta[IEEE80211_ADDR_LEN];
    /* FCS */
} __packed;

struct ieee80211_frame_cfend {      /* NB: also CF-End+CF-Ack */
    u_int8_t    i_fc[2];
    u_int8_t    i_dur[2];   /* should be zero */
    u_int8_t    i_ra[IEEE80211_ADDR_LEN];
    u_int8_t    i_bssid[IEEE80211_ADDR_LEN];
    /* FCS */
} __packed;

/*
 * BEACON management packets
 *
 *  octet timestamp[8]
 *  octet beacon interval[2]
 *  octet capability information[2]
 *  information element
 *      octet elemid
 *      octet length
 *      octet information[length]
 */

typedef u_int8_t *ieee80211_mgt_beacon_t;

#define IEEE80211_BEACON_INTERVAL(beacon) \
    ((beacon)[8] | ((beacon)[9] << 8))
#define IEEE80211_BEACON_CAPABILITY(beacon) \
    ((beacon)[10] | ((beacon)[11] << 8))

#define IEEE80211_CAPINFO_ESS               0x0001
#define IEEE80211_CAPINFO_IBSS              0x0002
#define IEEE80211_CAPINFO_CF_POLLABLE       0x0004
#define IEEE80211_CAPINFO_CF_POLLREQ        0x0008
#define IEEE80211_CAPINFO_PRIVACY           0x0010
#define IEEE80211_CAPINFO_SHORT_PREAMBLE    0x0020
#define IEEE80211_CAPINFO_PBCC              0x0040
#define IEEE80211_CAPINFO_CHNL_AGILITY      0x0080
#define IEEE80211_CAPINFO_SPECTRUM_MGMT     0x0100
#define IEEE80211_CAPINFO_QOS               0x0200
#define IEEE80211_CAPINFO_SHORT_SLOTTIME    0x0400
#define IEEE80211_CAPINFO_APSD              0x0800
#define IEEE80211_CAPINFO_RADIOMEAS         0x1000
#define IEEE80211_CAPINFO_DSSSOFDM          0x2000
/* bits 14-15 are reserved */

/*
 * 802.11i/WPA information element (maximally sized).
 */
struct ieee80211_ie_wpa {
    u_int8_t    wpa_id;          /* IEEE80211_ELEMID_VENDOR */
    u_int8_t    wpa_len;         /* length in bytes */
    u_int8_t    wpa_oui[3];      /* 0x00, 0x50, 0xf2 */
    u_int8_t    wpa_type;        /* OUI type */
    u_int16_t   wpa_version;     /* spec revision */
    u_int32_t   wpa_mcipher[1];  /* multicast/group key cipher */
    u_int16_t   wpa_uciphercnt;  /* # pairwise key ciphers */
    u_int32_t   wpa_uciphers[8]; /* ciphers */
    u_int16_t   wpa_authselcnt;  /* authentication selector cnt */
    u_int32_t   wpa_authsels[8]; /* selectors */
    u_int16_t   wpa_caps;        /* 802.11i capabilities */
    u_int16_t   wpa_pmkidcnt;    /* 802.11i pmkid count */
    u_int16_t   wpa_pmkids[8];   /* 802.11i pmkids */
} __packed;

#ifndef _BYTE_ORDER
#error "Don't know native byte order"
#endif

#ifndef IEEE80211N_IE
/* Temporary vendor specific IE for 11n pre-standard interoperability */
#define VENDOR_HT_OUI       0x00904c
#define VENDOR_HT_CAP_ID    51
#define VENDOR_HT_INFO_ID   52
#endif

#ifdef ATH_SUPPORT_TxBF
union ieee80211_hc_txbf {
    struct {
#if _BYTE_ORDER == _BIG_ENDIAN
        u_int32_t   reserved              : 3,
                channel_estimation_cap    : 2,
                csi_max_rows_bfer         : 2,
                comp_bfer_antennas        : 2,
                noncomp_bfer_antennas     : 2,
                csi_bfer_antennas         : 2,
                minimal_grouping          : 2,
                explicit_comp_bf          : 2,
                explicit_noncomp_bf       : 2,
                explicit_csi_feedback     : 2,
                explicit_comp_steering    : 1,
                explicit_noncomp_steering : 1,
                explicit_csi_txbf_capable : 1,
                calibration               : 2,
                implicit_txbf_capable     : 1,
                tx_ndp_capable            : 1,
                rx_ndp_capable            : 1,
                tx_staggered_sounding     : 1,
                rx_staggered_sounding     : 1,
                implicit_rx_capable       : 1;
#else
        u_int32_t   implicit_rx_capable   : 1,
                rx_staggered_sounding     : 1,
                tx_staggered_sounding     : 1,
                rx_ndp_capable            : 1,
                tx_ndp_capable            : 1,
                implicit_txbf_capable     : 1,
                calibration               : 2,
                explicit_csi_txbf_capable : 1,
                explicit_noncomp_steering : 1,
                explicit_comp_steering    : 1,
                explicit_csi_feedback     : 2,
                explicit_noncomp_bf       : 2,
                explicit_comp_bf          : 2,
                minimal_grouping          : 2,
                csi_bfer_antennas         : 2,
                noncomp_bfer_antennas     : 2,
                comp_bfer_antennas        : 2,
                csi_max_rows_bfer         : 2,
                channel_estimation_cap    : 2,
                reserved                  : 3;
#endif
    };

    u_int32_t value;
} __packed;
#endif

struct ieee80211_ie_htcap_cmn {
    u_int16_t   hc_cap;         /* HT capabilities */
#if _BYTE_ORDER == _BIG_ENDIAN
    u_int8_t    hc_reserved     : 3,    /* B5-7 reserved */
                hc_mpdudensity  : 3,    /* B2-4 MPDU density (aka Minimum MPDU Start Spacing) */
                hc_maxampdu     : 2;    /* B0-1 maximum rx A-MPDU factor */
#else
    u_int8_t    hc_maxampdu     : 2,    /* B0-1 maximum rx A-MPDU factor */
                hc_mpdudensity  : 3,    /* B2-4 MPDU density (aka Minimum MPDU Start Spacing) */
                hc_reserved     : 3;    /* B5-7 reserved */
#endif
    u_int8_t    hc_mcsset[16];          /* supported MCS set */
    u_int16_t   hc_extcap;              /* extended HT capabilities */
#ifdef ATH_SUPPORT_TxBF
    union ieee80211_hc_txbf hc_txbf;    /* txbf capabilities */
#else
    u_int32_t   hc_txbf;                /* txbf capabilities */
#endif
    u_int8_t    hc_antenna;             /* antenna capabilities */
} __packed;

/*
 * GPS IE
 */
struct ieee80211_ie_gps {
    u_int8_t                         hc_id;      /* element ID */
    u_int8_t                         hc_len;     /* length in bytes */
    u_int8_t    		     hc_coordinates[32];
} __packed;
/*
 * 802.11n HT Capability IE
 */
struct ieee80211_ie_htcap {
    u_int8_t                         hc_id;      /* element ID */
    u_int8_t                         hc_len;     /* length in bytes */
    struct ieee80211_ie_htcap_cmn    hc_ie;
} __packed;

/*
 * Temporary vendor private HT Capability IE
 */
struct vendor_ie_htcap {
    u_int8_t                         hc_id;          /* element ID */
    u_int8_t                         hc_len;         /* length in bytes */
    u_int8_t                         hc_oui[3];
    u_int8_t                         hc_ouitype;
    struct ieee80211_ie_htcap_cmn    hc_ie;
} __packed;

/* HT capability flags */
#define IEEE80211_HTCAP_C_ADVCODING             0x0001
#define IEEE80211_HTCAP_C_CHWIDTH40             0x0002
#define IEEE80211_HTCAP_C_SMPOWERSAVE_STATIC    0x0000 /* Capable of SM Power Save (Static) */
#define IEEE80211_HTCAP_C_SMPOWERSAVE_DYNAMIC   0x0004 /* Capable of SM Power Save (Dynamic) */
#define IEEE80211_HTCAP_C_SM_RESERVED           0x0008 /* Reserved */
#define IEEE80211_HTCAP_C_SMPOWERSAVE_DISABLED            0x000c /* SM enabled, no SM Power Save */
#define IEEE80211_HTCAP_C_GREENFIELD            0x0010
#define IEEE80211_HTCAP_C_SHORTGI20             0x0020
#define IEEE80211_HTCAP_C_SHORTGI40             0x0040
#define IEEE80211_HTCAP_C_TXSTBC                0x0080
#define IEEE80211_HTCAP_C_TXSTBC_S                   7
#define IEEE80211_HTCAP_C_RXSTBC                0x0300  /* 2 bits */
#define IEEE80211_HTCAP_C_RXSTBC_S                   8
#define IEEE80211_HTCAP_C_DELAYEDBLKACK         0x0400
#define IEEE80211_HTCAP_C_MAXAMSDUSIZE          0x0800  /* 1 = 8K, 0 = 3839B */
#define IEEE80211_HTCAP_C_DSSSCCK40             0x1000
#define IEEE80211_HTCAP_C_PSMP                  0x2000
#define IEEE80211_HTCAP_C_INTOLERANT40          0x4000
#define IEEE80211_HTCAP_C_LSIGTXOPPROT          0x8000

#define IEEE80211_HTCAP_C_SM_MASK               0x000c /* Spatial Multiplexing (SM) capabitlity bitmask */

/* ldpc */
#define IEEE80211_HTCAP_C_LDPC_NONE		0
#define IEEE80211_HTCAP_C_LDPC_RX		0x1
#define IEEE80211_HTCAP_C_LDPC_TX		0x2
#define IEEE80211_HTCAP_C_LDPC_TXRX		0x3

/* B0-1 maximum rx A-MPDU factor 2^(13+Max Rx A-MPDU Factor) */
enum {
    IEEE80211_HTCAP_MAXRXAMPDU_8192,    /* 2 ^ 13 */
    IEEE80211_HTCAP_MAXRXAMPDU_16384,   /* 2 ^ 14 */
    IEEE80211_HTCAP_MAXRXAMPDU_32768,   /* 2 ^ 15 */
    IEEE80211_HTCAP_MAXRXAMPDU_65536,   /* 2 ^ 16 */
};
#define IEEE80211_HTCAP_MAXRXAMPDU_FACTOR   13

/* B2-4 MPDU density (usec) */
enum {
    IEEE80211_HTCAP_MPDUDENSITY_NA,     /* No time restriction */
    IEEE80211_HTCAP_MPDUDENSITY_0_25,   /* 1/4 usec */
    IEEE80211_HTCAP_MPDUDENSITY_0_5,    /* 1/2 usec */
    IEEE80211_HTCAP_MPDUDENSITY_1,      /* 1 usec */
    IEEE80211_HTCAP_MPDUDENSITY_2,      /* 2 usec */
    IEEE80211_HTCAP_MPDUDENSITY_4,      /* 4 usec */
    IEEE80211_HTCAP_MPDUDENSITY_8,      /* 8 usec */
    IEEE80211_HTCAP_MPDUDENSITY_16,     /* 16 usec */
    IEEE80211_HTCAP_MPDUDENSITY_MAX = IEEE80211_HTCAP_MPDUDENSITY_16,
    IEEE80211_HTCAP_MPDUDENSITY_INVALID, /* Invalid */
};

/* HT extended capability flags */
#define IEEE80211_HTCAP_EXTC_PCO                0x0001
#define IEEE80211_HTCAP_EXTC_TRANS_TIME_RSVD    0x0000
#define IEEE80211_HTCAP_EXTC_TRANS_TIME_400     0x0002 /* 20-40 switch time */
#define IEEE80211_HTCAP_EXTC_TRANS_TIME_1500    0x0004 /* in us             */
#define IEEE80211_HTCAP_EXTC_TRANS_TIME_5000    0x0006
#define IEEE80211_HTCAP_EXTC_RSVD_1             0x00f8
#define IEEE80211_HTCAP_EXTC_MCS_FEEDBACK_NONE  0x0000
#define IEEE80211_HTCAP_EXTC_MCS_FEEDBACK_RSVD  0x0100
#define IEEE80211_HTCAP_EXTC_MCS_FEEDBACK_UNSOL 0x0200
#define IEEE80211_HTCAP_EXTC_MCS_FEEDBACK_FULL  0x0300
#define IEEE80211_HTCAP_EXTC_RSVD_2             0xfc00
#ifdef ATH_SUPPORT_TxBF
#define IEEE80211_HTCAP_EXTC_HTC_SUPPORT        0x0400
#endif

struct ieee80211_ie_htinfo_cmn {
    u_int8_t    hi_ctrlchannel;     /* control channel */
#if _BYTE_ORDER == _BIG_ENDIAN
    u_int8_t    hi_serviceinterval    : 3,    /* B5-7 svc interval granularity */
                hi_ctrlaccess         : 1,    /* B4   controlled access only */
                hi_rifsmode           : 1,    /* B3   rifs mode */
                hi_txchwidth          : 1,    /* B2   recommended xmiss width set */
                hi_extchoff           : 2;    /* B0-1 extension channel offset */


/*

 * The following 2 consecutive bytes are defined in word in 80211n spec.

 * Some processors store MSB byte into lower memory address which causes wrong

 * wrong byte sequence in beacon. Thus we break into byte definition which should

 * avoid the problem for all processors

 */

    u_int8_t    hi_ccfs2_1            : 3,    /* CCFS2 for ext NSS B5-B7 */

                hi_obssnonhtpresent   : 1,    /* B4   OBSS non-HT STA present */

                hi_txburstlimit       : 1,    /* B3   transmit burst limit */

                hi_nongfpresent       : 1,    /* B2   non greenfield devices present */

                hi_opmode             : 2;    /* B0-1 operating mode */

    u_int8_t    hi_reserved0          : 3,    /* CCFS2 for ext NSS B0-B4 */
                hi_ccfs2_2            : 5;    /* B5-7 (B13-15 in 11n) reserved */


/* The following 2 consecutive bytes are defined in word in 80211n spec. */

    u_int8_t    hi_dualctsprot        : 1,    /* B7   dual CTS protection */
                hi_dualbeacon         : 1,    /* B6   dual beacon */
                hi_reserved2          : 6;    /* B0-5 reserved */
    u_int8_t    hi_reserved1          : 4,    /* B4-7 (B12-15 in 11n) reserved */
                hi_pcophase           : 1,    /* B3   (B11 in 11n)  pco phase */
                hi_pcoactive          : 1,    /* B2   (B10 in 11n)  pco active */
                hi_lsigtxopprot       : 1,    /* B1   (B9 in 11n)   l-sig txop protection full support */
                hi_stbcbeacon         : 1;    /* B0   (B8 in 11n)   STBC beacon */
#else
    u_int8_t    hi_extchoff           : 2,    /* B0-1 extension channel offset */
                hi_txchwidth          : 1,    /* B2   recommended xmiss width set */
                hi_rifsmode           : 1,    /* B3   rifs mode */
                hi_ctrlaccess         : 1,    /* B4   controlled access only */
                hi_serviceinterval    : 3;    /* B5-7 svc interval granularity */
    u_int16_t   hi_opmode             : 2,    /* B0-1 operating mode */
                hi_nongfpresent       : 1,    /* B2   non greenfield devices present */
                hi_txburstlimit       : 1,    /* B3   transmit burst limit */
                hi_obssnonhtpresent   : 1,    /* B4   OBSS non-HT STA present */
                hi_ccfs2_1            : 3,    /* B5-B12 ccfs2 for ext nss */
                hi_ccfs2_2            : 5,    /* B5-B12 ccfs2 for ext nss */
                hi_reserved0          : 3;   /* B13-15 reserved */
    u_int16_t   hi_reserved2          : 6,    /* B0-5 reserved */
                hi_dualbeacon         : 1,    /* B6   dual beacon */
                hi_dualctsprot        : 1,    /* B7   dual CTS protection */
                hi_stbcbeacon         : 1,    /* B8   STBC beacon */
                hi_lsigtxopprot       : 1,    /* B9   l-sig txop protection full support */
                hi_pcoactive          : 1,    /* B10  pco active */
                hi_pcophase           : 1,    /* B11  pco phase */
                hi_reserved1          : 4;    /* B12-15 reserved */
#endif
    u_int8_t    hi_basicmcsset[16];     /* basic MCS set */
} __packed;

#define IEEE80211_HTINFO_CCFS2_GET_S     0x03
#define IEEE80211_HTINFO_CCFS2_SET_S     0x03

/*
 * 802.11n HT Information IE
 */
struct ieee80211_ie_htinfo {
    u_int8_t                        hi_id;          /* element ID */
    u_int8_t                        hi_len;         /* length in bytes */
    struct ieee80211_ie_htinfo_cmn  hi_ie;
} __packed;

/*
 * Temporary vendor private HT Information IE
 */
struct vendor_ie_htinfo {
    u_int8_t                        hi_id;          /* element ID */
    u_int8_t                        hi_len;         /* length in bytes */
    u_int8_t                        hi_oui[3];
    u_int8_t                        hi_ouitype;
    struct ieee80211_ie_htinfo_cmn  hi_ie;
} __packed;

/* extension channel offset (2 bit signed number) */
enum {
    IEEE80211_HTINFO_EXTOFFSET_NA    = 0,   /* 0  no extension channel is present */
    IEEE80211_HTINFO_EXTOFFSET_ABOVE = 1,   /* +1 extension channel above control channel */
    IEEE80211_HTINFO_EXTOFFSET_UNDEF = 2,   /* -2 undefined */
    IEEE80211_HTINFO_EXTOFFSET_BELOW = 3    /* -1 extension channel below control channel*/
};

/* recommended transmission width set */
enum {
    IEEE80211_HTINFO_TXWIDTH_20,
    IEEE80211_HTINFO_TXWIDTH_2040
};

/* operating flags */
#define IEEE80211_HTINFO_OPMODE_PURE                0x00 /* no protection */
#define IEEE80211_HTINFO_OPMODE_MIXED_PROT_OPT      0x01 /* prot optional (legacy device maybe present) */
#define IEEE80211_HTINFO_OPMODE_MIXED_PROT_40       0x02 /* prot required (20 MHz) */
#define IEEE80211_HTINFO_OPMODE_MIXED_PROT_ALL      0x03 /* prot required (legacy devices present) */
#define IEEE80211_HTINFO_OPMODE_NON_GF_PRESENT      0x04 /* non-greenfield devices present */

#define IEEE80211_HTINFO_OPMODE_MASK                0x03 /* For protection 0x00-0x03 */

/* Non-greenfield STAs present */
enum {
    IEEE80211_HTINFO_NON_GF_NOT_PRESENT,    /* Non-greenfield STAs not present */
    IEEE80211_HTINFO_NON_GF_PRESENT,        /* Non-greenfield STAs present */
};

/* Transmit Burst Limit */
enum {
    IEEE80211_HTINFO_TXBURST_UNLIMITED,     /* Transmit Burst is unlimited */
    IEEE80211_HTINFO_TXBURST_LIMITED,       /* Transmit Burst is limited */
};

/* OBSS Non-HT STAs present */
enum {
    IEEE80211_HTINFO_OBSS_NONHT_NOT_PRESENT, /* OBSS Non-HT STAs not present */
    IEEE80211_HTINFO_OBSS_NONHT_PRESENT,     /* OBSS Non-HT STAs present */
};

/* misc flags */
#define IEEE80211_HTINFO_DUALBEACON               0x0040 /* B6   dual beacon */
#define IEEE80211_HTINFO_DUALCTSPROT              0x0080 /* B7   dual stbc protection */
#define IEEE80211_HTINFO_STBCBEACON               0x0100 /* B8   secondary beacon */
#define IEEE80211_HTINFO_LSIGTXOPPROT             0x0200 /* B9   lsig txop prot full support */
#define IEEE80211_HTINFO_PCOACTIVE                0x0400 /* B10  pco active */
#define IEEE80211_HTINFO_PCOPHASE                 0x0800 /* B11  pco phase */

/* Secondary Channel offset for for 40MHz direct link */
#define IEEE80211_SECONDARY_CHANNEL_ABOVE         1
#define IEEE80211_SECONDARY_CHANNEL_BELOW         3

/* RIFS mode */
enum {
    IEEE80211_HTINFO_RIFSMODE_PROHIBITED,   /* use of rifs prohibited */
    IEEE80211_HTINFO_RIFSMODE_ALLOWED,      /* use of rifs permitted */
};

/*
 * Management information element payloads.
 */
enum {
    IEEE80211_ELEMID_SSID             = 0,
    IEEE80211_ELEMID_RATES            = 1,
    IEEE80211_ELEMID_FHPARMS          = 2,
    IEEE80211_ELEMID_DSPARMS          = 3,
    IEEE80211_ELEMID_CFPARMS          = 4,
    IEEE80211_ELEMID_TIM              = 5,
    IEEE80211_ELEMID_IBSSPARMS        = 6,
    IEEE80211_ELEMID_COUNTRY          = 7,
    IEEE80211_ELEMID_REQINFO          = 10,
    IEEE80211_ELEMID_QBSS_LOAD        = 11,
    IEEE80211_ELEMID_TCLAS            = 14,
    IEEE80211_ELEMID_CHALLENGE        = 16,
    /* 17-31 reserved for challenge text extension */
    IEEE80211_ELEMID_PWRCNSTR         = 32,
    IEEE80211_ELEMID_PWRCAP           = 33,
    IEEE80211_ELEMID_TPCREQ           = 34,
    IEEE80211_ELEMID_TPCREP           = 35,
    IEEE80211_ELEMID_SUPPCHAN         = 36,
    IEEE80211_ELEMID_CHANSWITCHANN    = 37,
    IEEE80211_ELEMID_MEASREQ          = 38,
    IEEE80211_ELEMID_MEASREP          = 39,
    IEEE80211_ELEMID_QUIET            = 40,
    IEEE80211_ELEMID_IBSSDFS          = 41,
    IEEE80211_ELEMID_ERP              = 42,
    IEEE80211_ELEMID_TCLAS_PROCESS    = 44,
    IEEE80211_ELEMID_HTCAP_ANA        = 45,
    IEEE80211_ELEMID_RESERVED_47      = 47,
    IEEE80211_ELEMID_RSN              = 48,
    IEEE80211_ELEMID_XRATES           = 50,
    IEEE80211_ELEMID_AP_CHAN_RPT      = 51,
    IEEE80211_ELEMID_HTCAP_VENDOR     = 51,
    IEEE80211_ELEMID_HTINFO_VENDOR    = 52,
    IEEE80211_ELEMID_MOBILITY_DOMAIN  = 54,
    IEEE80211_ELEMID_FT               = 55,
    IEEE80211_ELEMID_TIMEOUT_INTERVAL = 56,
    IEEE80211_ELEMID_SUPP_OP_CLASS    = 59,
    IEEE80211_ELEMID_EXTCHANSWITCHANN = 60,
    IEEE80211_ELEMID_HTINFO_ANA       = 61,
    IEEE80211_ELEMID_SECCHANOFFSET    = 62,
	IEEE80211_ELEMID_WAPI		      = 68,   /*IE for WAPI*/
    IEEE80211_ELEMID_TIME_ADVERTISEMENT = 69,
    IEEE80211_ELEMID_RRM              = 70,   /* Radio resource measurement */
    IEEE80211_ELEMID_2040_COEXT       = 72,
    IEEE80211_ELEMID_2040_INTOL       = 73,
    IEEE80211_ELEMID_OBSS_SCAN        = 74,
    IEEE80211_ELEMID_MMIE             = 76,   /* 802.11w Management MIC IE */
    IEEE80211_ELEMID_FMS_DESCRIPTOR   = 86,   /* 802.11v FMS descriptor IE */
    IEEE80211_ELEMID_FMS_REQUEST      = 87,   /* 802.11v FMS request IE */
    IEEE80211_ELEMID_FMS_RESPONSE     = 88,   /* 802.11v FMS response IE */
    IEEE80211_ELEMID_BSSMAX_IDLE_PERIOD = 90, /* BSS MAX IDLE PERIOD */
    IEEE80211_ELEMID_TFS_REQUEST      = 91,
    IEEE80211_ELEMID_TFS_RESPONSE     = 92,
    IEEE80211_ELEMID_TIM_BCAST_REQUEST  = 94,
    IEEE80211_ELEMID_TIM_BCAST_RESPONSE = 95,
    IEEE80211_ELEMID_INTERWORKING     = 107,
    IEEE80211_ELEMID_QOS_MAP          = 110,
    IEEE80211_ELEMID_XCAPS            = 127,
    IEEE80211_ELEMID_RESERVED_133     = 133,
    IEEE80211_ELEMID_TPC              = 150,
    IEEE80211_ELEMID_CCKM             = 156,
    IEEE80211_ELEMID_VHTCAP           = 191,  /* VHT Capabilities */
    IEEE80211_ELEMID_VHTOP            = 192,  /* VHT Operation */
    IEEE80211_ELEMID_EXT_BSS_LOAD     = 193,  /* Extended BSS Load */
    IEEE80211_ELEMID_WIDE_BAND_CHAN_SWITCH = 194,  /* Wide Band Channel Switch */
    IEEE80211_ELEMID_VHT_TX_PWR_ENVLP = 195,  /* VHT Transmit Power Envelope */
    IEEE80211_ELEMID_CHAN_SWITCH_WRAP = 196,  /* Channel Switch Wrapper */
    IEEE80211_ELEMID_AID              = 197,  /* AID */
    IEEE80211_ELEMID_QUIET_CHANNEL    = 198,  /* Quiet Channel */
    IEEE80211_ELEMID_OP_MODE_NOTIFY   = 199,  /* Operating Mode Notification */
    IEEE80211_ELEMID_REDUCED_NBR_RPT  = 201,  /* Reduced Neighbor Report */
    IEEE80211_ELEMID_VENDOR           = 221,  /* vendor private */
    IEEE80211_ELEMID_CAG_NUMBER       = 237,
    IEEE80211_ELEMID_AP_CSN           = 239,
    IEEE80211_ELEMID_FILS_INDICATION  = 240,
    IEEE80211_ELEMID_DILS             = 241,
    IEEE80211_ELEMID_FRAGMENT         = 242,
    IEEE80211_ELEMID_EXTENSION        = 255
};

/* Element ID Extension (EID 255) values */
#define IEEE80211_ELEMID_EXT_ASSOC_DELAY_INFO       1
#define IEEE80211_ELEMID_EXT_FILS_REQ_PARAMS        2
#define IEEE80211_ELEMID_EXT_FILS_KEY_CONFIRM       3
#define IEEE80211_ELEMID_EXT_FILS_SESSION           4
#define IEEE80211_ELEMID_EXT_FILS_HLP_CONTAINER     5
#define IEEE80211_ELEMID_EXT_FILS_IP_ADDR_ASSIGN    6
#define IEEE80211_ELEMID_EXT_KEY_DELIVERY           7
#define IEEE80211_ELEMID_EXT_FILS_WRAPPED_DATA      8
#define IEEE80211_ELEMID_EXT_ESP_ELEMID_EXTENSION   11
#define IEEE80211_ELEMID_EXT_FILS_PUBLIC_KEY        12
#define IEEE80211_ELEMID_EXT_FILS_NONCE             13

#define IEEE80211_MAX_IE_LEN                255
#define IEEE80211_RSN_IE_LEN                22

#define IEEE80211_CHANSWITCHANN_BYTES        5
#define IEEE80211_CHANSWITCHANN_MODE_QUIET   1
#define IEEE80211_EXTCHANSWITCHANN_BYTES     6

struct ieee80211_tim_ie {
    u_int8_t    tim_ie;         /* IEEE80211_ELEMID_TIM */
    u_int8_t    tim_len;
    u_int8_t    tim_count;      /* DTIM count */
    u_int8_t    tim_period;     /* DTIM period */
    u_int8_t    tim_bitctl;     /* bitmap control */
    u_int8_t    tim_bitmap[1];  /* variable-length bitmap */
} __packed;

/* Country IE channel triplet */
struct country_ie_triplet {
    union{
        u_int8_t schan;             /* starting channel */
        u_int8_t regextid;          /* Regulatory Extension Identifier */
    };
    union{
        u_int8_t nchan;             /* number of channels */
        u_int8_t regclass;          /* Regulatory Class */
    };
    union{
        u_int8_t maxtxpwr;          /* tx power  */
        u_int8_t coverageclass;     /* Coverage Class */
    };
}__packed;

struct ieee80211_country_ie {
    u_int8_t    ie;                 /* IEEE80211_ELEMID_COUNTRY */
    u_int8_t    len;
    u_int8_t    cc[3];              /* ISO CC+(I)ndoor/(O)utdoor */
    struct country_ie_triplet triplet[1];
} __packed;

struct ieee80211_fh_ie {
    u_int8_t    ie;                 /* IEEE80211_ELEMID_FHPARMS */
    u_int8_t    len;
    u_int16_t   dwell_time;    // endianess??
    u_int8_t    hop_set;
    u_int8_t    hop_pattern;
    u_int8_t    hop_index;
} __packed;

struct ieee80211_ds_ie {
    u_int8_t    ie;                 /* IEEE80211_ELEMID_DSPARMS */
    u_int8_t    len;
    u_int8_t    current_channel;
} __packed;

struct ieee80211_erp_ie {
    u_int8_t    ie;                 /* IEEE80211_ELEMID_ERP */
    u_int8_t    len;
    u_int8_t    value;
} __packed;

struct ieee80211_quiet_ie {
    u_int8_t    ie;                 /* IEEE80211_ELEMID_QUIET */
    u_int8_t    len;
    u_int8_t    tbttcount;          /* quiet start */
    u_int8_t    period;             /* beacon intervals between quiets*/
    u_int16_t   duration;           /* TUs of each quiet*/
    u_int16_t   offset;             /* TUs of from TBTT of quiet start*/
} __packed;

#if ATH_SUPPORT_IBSS_DFS
struct map_field {
#if _BYTE_ORDER == _BIG_ENDIAN
        u_int8_t       reserved:3,
                       unmeasured:1,
                       radar:1,
                       und_signal:1,
                       ofdem_preamble:1,
                       bss:1;
#else
        u_int8_t       bss:1,
                       ofdem_preamble:1,
                       und_signal:1,
                       radar:1,
                       unmeasured:1,
                       reserved:3;
#endif
}__packed;

#define IEEE80211_MEASUREMENT_REPORT_BASIC_SIZE 12
struct ieee80211_measurement_report_basic_report {
    u_int8_t          channel;
    u_int64_t         measurement_start_time;
    u_int16_t         measurement_duration;
    union {
        struct map_field  map;
        u_int8_t          chmap_in_byte;
    };
}__packed;

struct ieee80211_measurement_report_ie {
    u_int8_t    ie;                         /* IEEE80211_ELEMID_MEASREP */
    u_int8_t    len;
    u_int8_t    measurement_token;
    u_int8_t    measurement_report_mode;
    u_int8_t    measurement_type;
    u_int8_t    pmeasurement_report[IEEE80211_MEASUREMENT_REPORT_BASIC_SIZE];    /* variable, assume basic report */
}__packed;

struct channel_map_field {
    u_int8_t            ch_num;             /* channel number*/
    union {
        struct map_field  ch_map;
        u_int8_t          chmap_in_byte;
    };
}__packed;

struct ieee80211_ibssdfs_ie {
    u_int8_t    ie;                 /* IEEE80211_ELEMID_QUIET */
    u_int8_t    len;
    u_int8_t    owner[IEEE80211_ADDR_LEN];           /*dfs owner */
    u_int8_t    rec_interval;       /* dfs_recover_interval*/
    struct channel_map_field    ch_map_list[IEEE80211_CHAN_MAX+1];    /* channel map filed */ //need to be max
} __packed;
#endif /* ATH_SUPPORT_IBSS_DFS */

struct ieee80211_build_version_ie {
    u_int8_t    build_variant[3];
    u_int8_t    sw_build_version;
    u_int8_t    sw_build_maj_ver;
    u_int8_t    sw_build_min_ver;
    u_int8_t    sw_build_rel_variant;
    u_int8_t    sw_build_rel_num;
    u_int32_t   chip_vendorid;  /* For AHB devices, vendorid=0x0
                                   Little Endian format*/
    u_int32_t   chip_devid; /* Little Endian Format*/
} __packed;

/*Values of the SW_BUILD macros in this file are default values.
  Build/Integration team shall modify the values according to the meta
  build information before they build the driver */

#define SW_BUILD_VARIANT          "ILQ"
#define SW_BUILD_VERSION             3
#define SW_BUILD_MAJ_VER             2
#define SW_BUILD_MIN_VER             9
#define SW_BUILD_REL_VARIANT        'r'
#define SW_BUILD_REL_NUM             1
#define SW_BUILD_VARIANT_LEN         1

struct ieee80211_channelswitch_ie {
    u_int8_t    ie;                 /* IEEE80211_ELEMID_CHANSWITCHANN */
    u_int8_t    len;
    u_int8_t    switchmode;
    u_int8_t    newchannel;
    u_int8_t    tbttcount;
} __packed;

/* channel switch action frame format definition */
struct ieee80211_action_spectrum_channel_switch {
    struct ieee80211_action             csa_header;
    struct ieee80211_channelswitch_ie   csa_element;
}__packed;

/* Vendor Specific  action frame format definition */
struct ieee80211_action_vendor_specific {
    u_int8_t    ia_category;
    u_int8_t    vendor_oui[3];         /* 0x00, 0x03, 0x7f for Atheros */
    /* followed by vendor specific variable length content */
}__packed;

#define IEEE80211_CSA_MODE_STA_TX_ALLOWED        0
#define IEEE80211_CSA_MODE_STA_TX_RESTRICTED     1
#define IEEE80211_CSA_MODE_AUTO                  2

struct ieee80211_extendedchannelswitch_ie {
    u_int8_t    ie;                 /* IEEE80211_ELEMID_EXTCHANSWITCHANN */
    u_int8_t    len;
    u_int8_t    switchmode;
    u_int8_t    newClass;
    u_int8_t    newchannel;
    u_int8_t    tbttcount;
} __packed;

struct ieee80211_tpc_ie {
    u_int8_t    ie;
    u_int8_t    len;
    u_int8_t    pwrlimit;
} __packed;

/*
 * MHDRIE included in TKIP MFP protected management frames
 */
struct ieee80211_ccx_mhdr_ie {
    u_int8_t    mhdr_id;
    u_int8_t    mhdr_len;
    u_int8_t    mhdr_oui[3];
    u_int8_t    mhdr_oui_type;
    u_int8_t    mhdr_fc[2];
    u_int8_t    mhdr_bssid[6];
} __packed;

/*
 * SSID IE
 */
struct ieee80211_ie_ssid {
    u_int8_t    ssid_id;
    u_int8_t    ssid_len;
    u_int8_t    ssid[32];
} __packed;

/*
 * Supported rates
 */
#define IEEE80211_MAX_SUPPORTED_RATES      8

struct ieee80211_ie_rates {
    u_int8_t    rate_id;     /* Element Id */
    u_int8_t    rate_len;    /* IE Length */
    u_int8_t    rate[IEEE80211_MAX_SUPPORTED_RATES];     /* IE Length */
} __packed;

/*
 * Extended rates
 */
#define IEEE80211_MAX_EXTENDED_RATES     256

struct ieee80211_ie_xrates {
    u_int8_t    xrate_id;     /* Element Id */
    u_int8_t    xrate_len;    /* IE Length */
    u_int8_t    xrate[IEEE80211_MAX_EXTENDED_RATES];   /* IE Length */
} __packed;

/*
 * WPS SSID list information element (maximally sized).
 */
struct ieee80211_ie_ssidl {
    u_int8_t    ssidl_id;     /* IEEE80211_ELEMID_VENDOR */
    u_int8_t    ssidl_len;    /* length in bytes */
    u_int8_t    ssidl_oui[3]; /* 0x00, 0x50, 0xf2 */
    u_int8_t    ssidl_type;   /* OUI type */
    u_int8_t    ssidl_prim_cap; /* Primary capabilities */
    u_int8_t    ssidl_count;  /* # of secondary SSIDs */
    u_int16_t   ssidl_value[248];
} __packed;

#if _BYTE_ORDER == _BIG_ENDIAN
struct ieee80211_sec_ssid_cap {
    u_int32_t       reserved0   :1,
                    akmlist     :6,
                    reserved1   :4,
                    reeserved2  :2,
                    ucipher     :15,
                    mcipher     :4;
};
#else
struct ieee80211_sec_ssid_cap {
    u_int32_t       mcipher     :4,
                    ucipher     :15,
                    reserved2   :2,
                    reserved1   :4,
                    akmlist     :6,
                    reserved0   :1;
};
#endif

struct ieee80211_ie_qbssload {
    u_int8_t     elem_id;                /* IEEE80211_ELEMID_QBSS_LOAD */
    u_int8_t     length;                 /* length in bytes */
    u_int16_t    station_count;          /* number of station associated */
    u_int8_t     channel_utilization;    /* channel busy time in 0-255 scale */
    u_int16_t    aac;                    /* available admission capacity */
} __packed;

#define SEC_SSID_HEADER_LEN  6
#define SSIDL_IE_HEADER_LEN  6

struct ieee80211_sec_ssid {
    u_int8_t                        sec_ext_cap;
    struct ieee80211_sec_ssid_cap   sec_cap;
    u_int8_t                        sec_ssid_len;
    u_int8_t                        sec_ssid[32];
} __packed;

/* Definitions of SSIDL IE */
enum {
    CAP_MCIPHER_ENUM_NONE = 0,
    CAP_MCIPHER_ENUM_WEP40,
    CAP_MCIPHER_ENUM_WEP104,
    CAP_MCIPHER_ENUM_TKIP,
    CAP_MCIPHER_ENUM_CCMP,
    CAP_MCIPHER_ENUM_CKIP_CMIC,
    CAP_MCIPHER_ENUM_CKIP,
    CAP_MCIPHER_ENUM_CMIC
};


#define CAP_UCIPHER_BIT_NONE           0x0001
#define CAP_UCIPHER_BIT_WEP40          0x0002
#define CAP_UCIPHER_BIT_WEP104         0x0004
#define CAP_UCIPHER_BIT_TKIP           0x0008
#define CAP_UCIPHER_BIT_CCMP           0x0010
#define CAP_UCIPHER_BIT_CKIP_CMIC      0x0020
#define CAP_UCIPHER_BIT_CKIP           0x0040
#define CAP_UCIPHER_BIT_CMIC           0x0080
#define CAP_UCIPHER_BIT_WPA2_WEP40     0x0100
#define CAP_UCIPHER_BIT_WPA2_WEP104    0x0200
#define CAP_UCIPHER_BIT_WPA2_TKIP      0x0400
#define CAP_UCIPHER_BIT_WPA2_CCMP      0x0800
#define CAP_UCIPHER_BIT_WPA2_CKIP_CMIC 0x1000
#define CAP_UCIPHER_BIT_WPA2_CKIP      0x2000
#define CAP_UCIPHER_BIT_WPA2_CMIC      0x4000

#define CAP_AKM_BIT_WPA1_1X            0x01
#define CAP_AKM_BIT_WPA1_PSK           0x02
#define CAP_AKM_BIT_WPA2_1X            0x04
#define CAP_AKM_BIT_WPA2_PSK           0x08
#define CAP_AKM_BIT_WPA1_CCKM          0x10
#define CAP_AKM_BIT_WPA2_CCKM          0x20

#define IEEE80211_CHALLENGE_LEN         128

#define IEEE80211_SUPPCHAN_LEN          26

#define IEEE80211_RATE_BASIC            0x80
#define IEEE80211_RATE_VAL              0x7f

/* EPR information element flags */
#define IEEE80211_ERP_NON_ERP_PRESENT   0x01
#define IEEE80211_ERP_USE_PROTECTION    0x02
#define IEEE80211_ERP_LONG_PREAMBLE     0x04

/* Atheros private advanced capabilities info */
#define ATHEROS_CAP_TURBO_PRIME         0x01
#define ATHEROS_CAP_COMPRESSION         0x02
#define ATHEROS_CAP_FAST_FRAME          0x04
/* bits 3-6 reserved */
#define ATHEROS_CAP_BOOST               0x80

#define ATH_OUI                     0x7f0300    /* Atheros OUI */
#define ATH_OUI_TYPE                    0x01
#define ATH_OUI_SUBTYPE                 0x01
#define ATH_OUI_VERSION                 0x00
#define ATH_OUI_TYPE_XR                 0x03
#define ATH_OUI_VER_XR                  0x01
#define ATH_OUI_EXTCAP_TYPE             0x04    /* Atheros Extended Cap Type */
#define ATH_OUI_EXTCAP_SUBTYPE          0x01    /* Atheros Extended Cap Sub-type */
#define ATH_OUI_EXTCAP_VERSION          0x00    /* Atheros Extended Cap Version */
#define ATH_OUI_BW_NSS_MAP_TYPE         0x05    /* QCA Bandwidth NSS Mapping Type */
#define ATH_OUI_BW_NSS_MAP_SUBTYPE      0x01    /* QCA Bandwidth NSS Mapping sub-Type */
#define ATH_OUI_BW_NSS_VERSION          0x00    /* QCA Bandwidth NSS Mapping Version */

#define QCA_OUI                     0xf0fd8c   /* QCA OUI (in little endian) */
#define QCA_OUI_BYTE_MASK           0xff
#define QCA_OUI_ONE_BYTE_SHIFT       8
#define QCA_OUI_TWO_BYTE_SHIFT      16
#define QCA_OUI_LEN                  6
#define IE_LEN_ID_LEN                2 /* Length (ID and Length) of IE*/

#define DDT_OUI                     0x181000
#define DEDICATE_OUI_CAP_TYPE           0x02

/* Whole Home Coverage vendor specific IEs */
#define QCA_OUI_WHC_TYPE                0x00
#define QCA_OUI_WHC_REPT_TYPE           0x01

/* QCN IE */
#define QCN_OUI_TYPE                    0x01

/* apriori Next-channel vendor specific IE */
#define QCA_OUI_NC_TYPE                 0x02

/* Extender vendor specific IE */
#define QCA_OUI_EXTENDER_TYPE           0x03
/* Generic vendor specific IE */
#define QCA_OUI_GENERIC_TYPE_1          0x04/* WARNING: Please do not define
                                               new type for VIE. Please use this
                                               type and use the subtype for
                                               future use, until subtype reaches
                                               255,then define GENERIC_TYPE_2 as
                                               5 and proceed */
#define QCA_OUI_BUILD_INFO_SUBTYPE      0x00 /* This has Radio and
                                                SW build info. */
#define QCA_OUI_BUILD_INFO_VERSION      0x00 /* This has version of Radio and SW
                                                build info .*/

/* Fields and bit mask for the Whole Home Coverage AP Info Sub-type */
#define QCA_OUI_WHC_AP_INFO_SUBTYPE     0x00
#define QCA_OUI_WHC_AP_INFO_VERSION     0x01
#define QCA_OUI_WHC_AP_INFO_CAP_WDS     0x01
#define QCA_OUI_WHC_AP_INFO_CAP_SON     0x02

#define QCA_OUI_WHC_REPT_INFO_SUBTYPE   0x00
#define QCA_OUI_WHC_REPT_INFO_VERSION   0x00

/* Vendor specific IEs for channel change in repeater during DFS */
#define QCA_OUI_NC_SUBTYPE             0x00
#define QCA_OUI_NC_VERSION             0x00
#define QCA_UNHANDLED_SUB_ELEM_ID       255

#define WPA_OUI                     0xf25000
#define WPA_OUI_TYPE                    0x01
#define WPA_VERSION                        1    /* current supported version */

#define WSC_OUI                   0x0050f204

#define WPA_CSE_NULL                    0x00
#define WPA_CSE_WEP40                   0x01
#define WPA_CSE_TKIP                    0x02
#define WPA_CSE_CCMP                    0x04
#define WPA_CSE_WEP104                  0x05

#define WPA_ASE_NONE                    0x00
#define WPA_ASE_8021X_UNSPEC            0x01
#define WPA_ASE_8021X_PSK               0x02
#define WPA_ASE_FT_IEEE8021X            0x20
#define WPA_ASE_FT_PSK                  0x40
#define WPA_ASE_SHA256_IEEE8021X        0x80
#define WPA_ASE_SHA256_PSK              0x100
#define WPA_ASE_WPS                     0x200


#define RSN_OUI                     0xac0f00
#define RSN_VERSION                        1    /* current supported version */

#define RSN_CSE_NULL                    0x00
#define RSN_CSE_WEP40                   0x01
#define RSN_CSE_TKIP                    0x02
#define RSN_CSE_WRAP                    0x03
#define RSN_CSE_CCMP                    0x04
#define RSN_CSE_WEP104                  0x05
#define RSN_CSE_AES_CMAC                0x06
#define RSN_CSE_GCMP_128                0x08
#define RSN_CSE_GCMP_256                0x09
#define RSN_CSE_CCMP_256                0x0A
#define RSN_CSE_BIP_GMAC_128            0x0B
#define RSN_CSE_BIP_GMAC_256            0x0C
#define RSN_CSE_BIP_CMAC_256            0x0D

#define RSN_ASE_NONE                    0x00
#define RSN_ASE_8021X_UNSPEC            0x01
#define RSN_ASE_8021X_PSK               0x02
#define RSN_ASE_FT_IEEE8021X            0x20
#define RSN_ASE_FT_PSK                  0x40
#define RSN_ASE_SHA256_IEEE8021X        0x80
#define RSN_ASE_SHA256_PSK              0x100
#define RSN_ASE_WPS                     0x200

#define AKM_SUITE_TYPE_IEEE8021X        0x01
#define AKM_SUITE_TYPE_PSK              0x02
#define AKM_SUITE_TYPE_FT_IEEE8021X     0x03
#define AKM_SUITE_TYPE_FT_PSK           0x04
#define AKM_SUITE_TYPE_SHA256_IEEE8021X 0x05
#define AKM_SUITE_TYPE_SHA256_PSK       0x06

#define RSN_CAP_PREAUTH                 0x01
#define RSN_CAP_MFP_REQUIRED            0x40
#define RSN_CAP_MFP_ENABLED             0x80

#define CCKM_OUI                    0x964000
#define CCKM_ASE_UNSPEC                    0
#define WPA_CCKM_AKM              0x00964000
#define RSN_CCKM_AKM              0x00964000

#define WME_OUI                     0xf25000
#define WME_OUI_TYPE                    0x02
#define WME_INFO_OUI_SUBTYPE            0x00
#define WME_PARAM_OUI_SUBTYPE           0x01
#define WME_TSPEC_OUI_SUBTYPE           0x02

#define MBO_OUI                     0x9a6f50
#define MBO_OUI_TYPE                    0x16

#define VHT_INTEROP_OUI                 0x00904c
#define VHT_INTEROP_TYPE                0x04
#define VHT_INTEROP_OUI_SUBTYPE         0x08
#define VHT_INTEROP_OUI_SUBTYPE_VENDORSPEC     0x18

#define WME_PARAM_OUI_VERSION              1
#define WME_TSPEC_OUI_VERSION              1
#define WME_VERSION                        1

/* WME stream classes */
#define WME_AC_BE                          0    /* best effort */
#define WME_AC_BK                          1    /* background */
#define WME_AC_VI                          2    /* video */
#define WME_AC_VO                          3    /* voice */

#define WPS_OUI                     0xf25000    /* Microsoft OUI */
#define WPS_OUI_TYPE                    0x05    /* Wireless Provisioning Services */
#define SSIDL_OUI_TYPE          WPS_OUI_TYPE

/* WCN IE */
#define WCN_OUI                     0xf25000    /* Microsoft OUI */
#define WCN_OUI_TYPE                    0x04    /* WCN */

/* Atheros htoui  for ht vender ie; use Epigram OUI for compatibility with pre11n devices */
#define ATH_HTOUI                   0x00904c

#define SFA_OUI                     0x964000
#define SFA_OUI_TYPE                    0x14
#define SFA_IE_CAP_MFP                  0x01
#define SFA_IE_CAP_DIAG_CHANNEL         0x02
#define SFA_IE_CAP_LOCATION_SVCS        0x04
#define SFA_IE_CAP_EXP_BANDWIDTH        0x08

#define WPA_OUI_BYTES       0x00, 0x50, 0xf2
#define RSN_OUI_BYTES       0x00, 0x0f, 0xac
#define WME_OUI_BYTES       0x00, 0x50, 0xf2
#define ATH_OUI_BYTES       0x00, 0x03, 0x7f
#define SFA_OUI_BYTES       0x00, 0x40, 0x96
#define CCKM_OUI_BYTES      0x00, 0x40, 0x96
#define WPA_SEL(x)          (((x)<<24)|WPA_OUI)
#define RSN_SEL(x)          (((x)<<24)|RSN_OUI)
#define SFA_SEL(x)          (((x)<<24)|SFA_OUI)
#define CCKM_SEL(x)         (((x)<<24)|CCKM_OUI)

#define VHT_INTEROP_OUI_BYTES  0x00, 0x90, 0x4c

#define IEEE80211_RV(v)     ((v) & IEEE80211_RATE_VAL)
#define IEEE80211_N(a)      (sizeof(a) / sizeof(a[0]))
/*
 * AUTH management packets
 *
 *  octet algo[2]
 *  octet seq[2]
 *  octet status[2]
 *  octet chal.id
 *  octet chal.length
 *  octet chal.text[253]
 */

typedef u_int8_t *ieee80211_mgt_auth_t;

#define IEEE80211_AUTH_ALGORITHM(auth) \
    ((auth)[0] | ((auth)[1] << 8))
#define IEEE80211_AUTH_TRANSACTION(auth) \
    ((auth)[2] | ((auth)[3] << 8))
#define IEEE80211_AUTH_STATUS(auth) \
    ((auth)[4] | ((auth)[5] << 8))

#define IEEE80211_AUTH_ALG_OPEN         0x0000
#define IEEE80211_AUTH_ALG_SHARED       0x0001
#define IEEE80211_AUTH_ALG_FT           0x0002
#define IEEE80211_AUTH_ALG_SAE          0x0003
#define IEEE80211_AUTH_ALG_FILS_SK      0x0004
#define IEEE80211_AUTH_ALG_FILS_SK_PFS  0x0005
#define IEEE80211_AUTH_ALG_FILS_PK      0x0006
#define IEEE80211_AUTH_ALG_LEAP         0x0080

enum {
    IEEE80211_AUTH_OPEN_REQUEST     = 1,
    IEEE80211_AUTH_OPEN_RESPONSE    = 2,
};

enum {
    IEEE80211_AUTH_SHARED_REQUEST   = 1,
    IEEE80211_AUTH_SHARED_CHALLENGE = 2,
    IEEE80211_AUTH_SHARED_RESPONSE  = 3,
    IEEE80211_AUTH_SHARED_PASS      = 4,
};

enum {
    IEEE80211_AUTH_FT_REQUEST       = 1,
    IEEE80211_AUTH_FT_RESPONSE      = 2,
};
/*
 * Reason codes
 *
 * Unlisted codes are reserved
 */

enum {
    IEEE80211_REASON_UNSPECIFIED        = 1,
    IEEE80211_REASON_AUTH_EXPIRE        = 2,
    IEEE80211_REASON_AUTH_LEAVE         = 3,
    IEEE80211_REASON_ASSOC_EXPIRE       = 4,
    IEEE80211_REASON_ASSOC_TOOMANY      = 5,
    IEEE80211_REASON_NOT_AUTHED         = 6,
    IEEE80211_REASON_NOT_ASSOCED        = 7,
    IEEE80211_REASON_ASSOC_LEAVE        = 8,
    IEEE80211_REASON_ASSOC_NOT_AUTHED   = 9,

    IEEE80211_REASON_ASSOC_BSSTM        = 12,
    IEEE80211_REASON_IE_INVALID         = 13,
    IEEE80211_REASON_MIC_FAILURE        = 14,
    IEEE80211_REASON_KICK_OUT           = 15,
    IEEE80211_REASON_INVALID_GROUP_CIPHER = 18,
    IEEE80211_REASON_INVALID_PAIRWISE_CIPHER = 19,
    IEEE80211_REASON_INVALID_AKMP         = 20,
    IEEE80211_REASON_UNSUPPORTED_RSNE_VER = 21,
    IEEE80211_REASON_RSN_REQUIRED         = 22,

    IEEE80211_REASON_QOS                = 32,
    IEEE80211_REASON_QOS_BANDWITDH      = 33,
    IEEE80211_REASON_DISASSOC_LOW_ACK  = 34,
    IEEE80211_REASON_QOS_TXOP           = 35,
    IEEE80211_REASON_QOS_LEAVE          = 36,
    IEEE80211_REASON_QOS_DECLINED       = 37,
    IEEE80211_REASON_QOS_SETUP_REQUIRED = 38,
    IEEE80211_REASON_QOS_TIMEOUT        = 39,
    IEEE80211_REASON_QOS_CIPHER         = 45,

    IEEE80211_STATUS_SUCCESS            = 0,
    IEEE80211_STATUS_UNSPECIFIED        = 1,
    IEEE80211_STATUS_CAPINFO            = 10,
    IEEE80211_STATUS_NOT_ASSOCED        = 11,
    IEEE80211_STATUS_OTHER              = 12,
    IEEE80211_STATUS_ALG                = 13,
    IEEE80211_STATUS_SEQUENCE           = 14,
    IEEE80211_STATUS_CHALLENGE          = 15,
    IEEE80211_STATUS_TIMEOUT            = 16,
    IEEE80211_STATUS_TOOMANY            = 17,
    IEEE80211_STATUS_BASIC_RATE         = 18,
    IEEE80211_STATUS_SP_REQUIRED        = 19,
    IEEE80211_STATUS_PBCC_REQUIRED      = 20,
    IEEE80211_STATUS_CA_REQUIRED        = 21,
    IEEE80211_STATUS_TOO_MANY_STATIONS  = 22,
    IEEE80211_STATUS_RATES              = 23,
    IEEE80211_STATUS_SHORTSLOT_REQUIRED = 25,
    IEEE80211_STATUS_DSSSOFDM_REQUIRED  = 26,
    IEEE80211_STATUS_NO_HT              = 27,
    IEEE80211_STATUS_REJECT_TEMP        = 30,
    IEEE80211_STATUS_MFP_VIOLATION      = 31,
    IEEE80211_STATUS_POOR_CHAN_CONDITION = 34,
    IEEE80211_STATUS_REFUSED            = 37,
    IEEE80211_STATUS_INVALID_PARAM      = 38,
    IEEE80211_STATUS_INVALID_ELEMENT    = 40,
    IEEE80211_STATUS_INVALID_GROUP_CIPHER = 41,
    IEEE80211_STATUS_INVALID_PAIRWISE_CIPHER = 42,
    IEEE80211_STATUS_INVALID_AKMP         = 43,
    IEEE80211_STATUS_UNSUPPORTED_RSNE_VER = 44,
    IEEE80211_STATUS_INVALID_RSNE_CAP     = 45,

    IEEE80211_STATUS_DLS_NOT_ALLOWED    = 48,
    IEEE80211_STATUS_NO_VHT             = 104,
    IEEE80211_STATUS_RADAR_DETECTED     = 105,
};

/* private IEEE80211_STATUS */
#define    IEEE80211_STATUS_CANCEL             -1
#define    IEEE80211_STATUS_INVALID_IE         -2
#define    IEEE80211_STATUS_INVALID_CHANNEL    -3

/* private IEEE80211_REASON */
/* Only clean up local association state, don't send disassociation frame OTA */
#define    IEEE80211_REASON_LOCAL              252

#define IEEE80211_WEP_KEYLEN        5   /* 40bit */
#define IEEE80211_WEP_IVLEN         3   /* 24bit */
#define IEEE80211_WEP_KIDLEN        1   /* 1 octet */
#define IEEE80211_WEP_CRCLEN        4   /* CRC-32 */
#define IEEE80211_WEP_NKID          4   /* number of key ids */

/*
 * 802.11i defines an extended IV for use with non-WEP ciphers.
 * When the EXTIV bit is set in the key id byte an additional
 * 4 bytes immediately follow the IV for TKIP.  For CCMP the
 * EXTIV bit is likewise set but the 8 bytes represent the
 * CCMP header rather than IV+extended-IV.
 */
#define IEEE80211_WEP_EXTIV      0x20
#define IEEE80211_WEP_EXTIVLEN      4   /* extended IV length */
#define IEEE80211_WEP_MICLEN        8   /* trailing MIC */

#define IEEE80211_CRC_LEN           4

#define IEEE80211_8021Q_HEADER_LEN  4
/*
 * Maximum acceptable MTU is:
 *  IEEE80211_MAX_LEN - WEP overhead - CRC -
 *      QoS overhead - RSN/WPA overhead
 * Min is arbitrarily chosen > IEEE80211_MIN_LEN.  The default
 * mtu is Ethernet-compatible; it's set by ether_ifattach.
 */
#define IEEE80211_MTU_MAX       2290
#define IEEE80211_MTU_MIN       32

/* Rather than using this default value, customer platforms can provide a custom value for this constant.
  Coustomer platform will use the different define value by themself */
#ifndef IEEE80211_MAX_MPDU_LEN
#define IEEE80211_MAX_MPDU_LEN      (3840 + IEEE80211_CRC_LEN + \
    (IEEE80211_WEP_IVLEN + IEEE80211_WEP_KIDLEN + IEEE80211_WEP_CRCLEN))
#endif
#define IEEE80211_ACK_LEN \
    (sizeof(struct ieee80211_frame_ack) + IEEE80211_CRC_LEN)
#define IEEE80211_MIN_LEN \
    (sizeof(struct ieee80211_frame_min) + IEEE80211_CRC_LEN)

/* An 802.11 data frame can be one of three types:
1. An unaggregated frame: The maximum length of an unaggregated data frame is 2324 bytes + headers.
2. A data frame that is part of an AMPDU: The maximum length of an AMPDU may be upto 65535 bytes, but data frame is limited to 2324 bytes + header.
3. An AMSDU: The maximum length of an AMSDU is eihther 3839 or 7095 bytes.
The maximum frame length supported by hardware is 4095 bytes.
A length of 3839 bytes is chosen here to support unaggregated data frames, any size AMPDUs and 3839 byte AMSDUs.
*/
#define IEEE80211N_MAX_FRAMELEN  3839
#define IEEE80211N_MAX_LEN (IEEE80211N_MAX_FRAMELEN + IEEE80211_CRC_LEN + \
    (IEEE80211_WEP_IVLEN + IEEE80211_WEP_KIDLEN + IEEE80211_WEP_CRCLEN))

#define IEEE80211_TX_CHAINMASK_MIN  1
#define IEEE80211_RX_CHAINMASK_MIN  1
#define IEE80211_TX_MAX_CHAINMASK(ic) ((1 << ic->ic_num_tx_chain)-1)
#define IEE80211_RX_MAX_CHAINMASK(ic) ((1 << ic->ic_num_rx_chain)-1)

#if ATH_SUPPORT_4SS
#define IEEE80211_TX_CHAINMASK_MAX  (0xf)
#define IEEE80211_RX_CHAINMASK_MAX  (0xf)
#define IEEE80211_MAX_TX_CHAINS 4
#else
#define IEEE80211_TX_CHAINMASK_MAX  7
#define IEEE80211_RX_CHAINMASK_MAX  7
#define IEEE80211_MAX_TX_CHAINS 3
#endif

/*
 * The 802.11 spec says at most 2007 stations may be
 * associated at once.  For most AP's this is way more
 * than is feasible so we use a default of 128.  This
 * number may be overridden by the driver and/or by
 * user configuration.
 */
#define IEEE80211_MAX_AID       2007
#define IEEE80211_33_AID        33
#define IEEE80211_128_AID       128
#define IEEE80211_200_AID       200
#define IEEE80211_512_AID       512
#define IEEE80211_ATF_AID_DEF   ATF_ACTIVED_MAX_CLIENTS + 1 /* With ATF, limit max clients */
#define IEEE80211_AID(b)    ((b) &~ 0xc000)

/*
 * RTS frame length parameters.  The default is specified in
 * the 802.11 spec.  The max may be wrong for jumbo frames.
 */
#define IEEE80211_RTS_DEFAULT       512
#define IEEE80211_RTS_MIN           0
#define IEEE80211_RTS_MAX           2347

/*
 * Fragmentation limits
 */
#define IEEE80211_FRAGMT_THRESHOLD_MIN        540      /* min frag threshold */
#define IEEE80211_FRAGMT_THRESHOLD_MAX       2346      /* max frag threshold */

/*
 * Regulatory extention identifier for country IE.
 */
#define IEEE80211_REG_EXT_ID        201

/*
 * overlapping BSS
 */
#define IEEE80211_OBSS_SCAN_PASSIVE_DWELL_DEF  20
#define IEEE80211_OBSS_SCAN_ACTIVE_DWELL_DEF   10
#define IEEE80211_OBSS_SCAN_INTERVAL_DEF       300
#define IEEE80211_OBSS_SCAN_PASSIVE_TOTAL_DEF  200
#define IEEE80211_OBSS_SCAN_ACTIVE_TOTAL_DEF   20
#define IEEE80211_OBSS_SCAN_THRESH_DEF   25
#define IEEE80211_OBSS_SCAN_DELAY_DEF   5

/*
 * overlapping BSS scan ie
 */
struct ieee80211_ie_obss_scan {
        u_int8_t elem_id;
        u_int8_t elem_len;
        u_int16_t scan_passive_dwell;
        u_int16_t scan_active_dwell;
        u_int16_t scan_interval;
        u_int16_t scan_passive_total;
        u_int16_t scan_active_total;
        u_int16_t scan_delay;
        u_int16_t scan_thresh;
} __packed;

/*
 * Extended capability ie
 */
struct ieee80211_ie_ext_cap {
        u_int8_t elem_id;
        u_int8_t elem_len;
        u_int32_t ext_capflags;
        u_int32_t ext_capflags2;
        u_int8_t ext_capflags3;
        u_int8_t ext_capflags4;
} __packed;

/* Extended capability IE flags */
#define IEEE80211_EXTCAPIE_2040COEXTMGMT        0x00000001
#define IEEE80211_EXTCAPIE_ECSA                 0x00000004
#define IEEE80211_EXTCAPIE_TFS                  0x00010000
#define IEEE80211_EXTCAPIE_FMS                  0x00000800
#define IEEE80211_EXTCAPIE_PROXYARP             0x00001000
#define IEEE80211_EXTCAPIE_CIVLOC               0x00004000
#define IEEE80211_EXTCAPIE_GEOLOC               0x00008000
#define IEEE80211_EXTCAPIE_WNMSLEEPMODE         0x00020000
#define IEEE80211_EXTCAPIE_TIMBROADCAST         0x00040000
#define IEEE80211_EXTCAPIE_BSSTRANSITION        0x00080000
#define IEEE80211_EXTCAPIE_PEER_UAPSD_BUF_STA   0x10000000
/* 2nd Extended capability IE flags bit32-bit63*/
#define IEEE80211_EXTCAPIE_QOS_MAP          0x00000001 /* bit-32 QoS Map Support */
#define IEEE80211_EXTCAPIE_OP_MODE_NOTIFY   0x40000000 /* bit-62 Operating Mode notification */
/* 3rd Extended capability IE flags bit64-bit71*/
#define IEEE80211_EXTCAPIE_FTM_RES          0x40 /* bit-70 RTT FTM responder bits*/
#define IEEE80211_EXTCAPIE_FTM_INIT         0x80 /* bit-71 RTT FTM initiator bits*/
/* 3rd Extended capability IE flags bit72-bit79*/
#define IEEE80211_EXTCAPIE_FILS             0x01 /* bit-72 FILS capability */

struct ieee80211_ie_qos_map_set {
        u_int8_t elem_id;
        u_int8_t elem_len;
        u_int8_t qos_map_set[0];
} __packed;

/*
 * 20/40 BSS coexistence ie
 */
struct ieee80211_ie_bss_coex {
        u_int8_t elem_id;
        u_int8_t elem_len;
#if _BYTE_ORDER == _BIG_ENDIAN
        u_int8_t reserved1          : 1,
                 reserved2          : 1,
                 reserved3          : 1,
                 obss_exempt_grant  : 1,
                 obss_exempt_req    : 1,
                 ht20_width_req       : 1,
                 ht40_intolerant      : 1,
                 inf_request        : 1;
#else
        u_int8_t inf_request        : 1,
                 ht40_intolerant      : 1,
                 ht20_width_req       : 1,
                 obss_exempt_req    : 1,
                 obss_exempt_grant  : 1,
                 reserved3          : 1,
                 reserved2          : 1,
                 reserved1          : 1;
#endif
} __packed;

/*
 * 20/40 BSS intolerant channel report ie
 */
struct ieee80211_ie_intolerant_report {
        u_int8_t elem_id;
        u_int8_t elem_len;
        u_int8_t reg_class;
        u_int8_t chan_list[1];          /* variable-length channel list */
} __packed;

/*
 * 20/40 coext management action frame
 */
struct ieee80211_action_bss_coex_frame {
        struct ieee80211_action                ac_header;
        struct ieee80211_ie_bss_coex           coex;
        struct ieee80211_ie_intolerant_report    chan_report;
} __packed;

typedef enum ieee80211_tie_interval_type{
    IEEE80211_TIE_INTERVAL_TYPE_RESERVED                  = 0,
    IEEE80211_TIE_INTERVAL_TYPE_REASSOC_DEADLINE_INTERVAL = 1,
    IEEE80211_TIE_INTERVAL_TYPE_KEY_LIFETIME_INTERVAL     = 2,
    IEEE80211_TIE_INTERVAL_TYPE_ASSOC_COMEBACK_TIME       = 3,
}ieee80211_tie_interval_type_t;

struct ieee80211_ie_timeout_interval {
        u_int8_t elem_id;
        u_int8_t elem_len;
        u_int8_t interval_type;
        u_int32_t value;
} __packed;


/* Management MIC information element (IEEE 802.11w) */
struct ieee80211_mmie {
    u_int8_t element_id;
    u_int8_t length;
    u_int16_t key_id;
    u_int8_t sequence_number[6];
    u_int8_t mic[16];
} __packed;

/* VHT capability flags */
/* B0-B1 Maximum MPDU Length */
#define IEEE80211_VHTCAP_MAX_MPDU_LEN_3839     0x00000000 /* A-MSDU Length 3839 octets */
#define IEEE80211_VHTCAP_MAX_MPDU_LEN_7935     0x00000001 /* A-MSDU Length 7991 octets */
#define IEEE80211_VHTCAP_MAX_MPDU_LEN_11454    0x00000002 /* A-MSDU Length 11454 octets */

/* B2-B3 Supported Channel Width */
#define IEEE80211_VHTCAP_SUP_CHAN_WIDTH_80     0x00000000 /* Does not support 160 or 80+80 */
#define IEEE80211_VHTCAP_SUP_CHAN_WIDTH_160    0x00000004 /* Supports 160 */
#define IEEE80211_VHTCAP_SUP_CHAN_WIDTH_80_160 0x00000008 /* Support both 160 or 80+80 */
#define IEEE80211_VHTCAP_SUP_CHAN_WIDTH_S      2          /* B2-B3 */
#define IEEE80211_VHTCAP_SUP_CHAN_WIDTH_MASK   0x0000000C

#define IEEE80211_VHTCAP_RX_LDPC             0x00000010 /* B4 RX LDPC */
#define IEEE80211_VHTCAP_SHORTGI_80          0x00000020 /* B5 Short GI for 80MHz */
#define IEEE80211_VHTCAP_SHORTGI_160         0x00000040 /* B6 Short GI for 160 and 80+80 MHz */
#define IEEE80211_VHTCAP_TX_STBC             0x00000080 /* B7 Tx STBC */
#define IEEE80211_VHTCAP_TX_STBC_S           7

#define IEEE80211_VHTCAP_RX_STBC             0x00000700 /* B8-B10 Rx STBC */
#define IEEE80211_VHTCAP_RX_STBC_S           8

#define IEEE80211_VHTCAP_SU_BFORMER          0x00000800 /* B11 SU Beam former capable */
#define IEEE80211_VHTCAP_SU_BFORMER_S        11
#define IEEE80211_VHTCAP_SU_BFORMEE          0x00001000 /* B12 SU Beam formee capable */
#define IEEE80211_VHTCAP_SU_BFORMEE_S        12

#define IEEE80211_VHTCAP_BF_MAX_ANT          0x0000E000 /* B13-B15 Compressed steering number of
                                                         * beacomformer Antennas supported */
#define IEEE80211_VHTCAP_BF_MAX_ANT_S        13

#define IEEE80211_VHTCAP_STS_CAP_S           13         /* B13-B15 Beamformee STS Capability */
#define IEEE80211_VHTCAP_STS_CAP_M           0x7



//#define IEEE80211_VHTCAP_SOUND_DIMENSIONS    0x00070000 /* B16-B18 Sounding Dimensions */
//#define IEEE80211_VHTCAP_SOUND_DIMENSIONS_S  16
#define IEEE80211_VHTCAP_SOUND_DIM           0x00070000 /* B16-B18 Sounding Dimensions */
#define IEEE80211_VHTCAP_SOUND_DIM_S         16

#define IEEE80211_VHTCAP_MU_BFORMER          0x00080000 /* B19 MU Beam Former */
#define IEEE80211_VHTCAP_MU_BFORMER_S        19
#define IEEE80211_VHTCAP_MU_BFORMEE          0x00100000 /* B20 MU Beam Formee */
#define IEEE80211_VHTCAP_MU_BFORMEE_S        20
#define IEEE80211_VHTCAP_TXOP_PS             0x00200000 /* B21 VHT TXOP PS */
#define IEEE80211_VHTCAP_PLUS_HTC_VHT        0x00400000 /* B22 +HTC-VHT capable */

#define IEEE80211_VHTCAP_MAX_AMPDU_LEN_FACTOR  13
#define IEEE80211_VHTCAP_MAX_AMPDU_LEN_EXP   0x03800000 /* B23-B25 maximum AMPDU Length Exponent */
#define IEEE80211_VHTCAP_MAX_AMPDU_LEN_EXP_S 23

#define IEEE80211_VHTCAP_LINK_ADAPT          0x0C000000 /* B26-B27 VHT Link Adaptation capable */
#define IEEE80211_VHTCAP_RESERVED            0xF0000000 /* B28-B31 Reserved */

#define IEEE80211_VHTCAP_NO_EXT_NSS_BW_SUPPORT  0x00000000 /* B30-B31 Extended NSS Bandwidth Support */
#define IEEE80211_VHTCAP_EXT_NSS_BW_SUPPORT_1   0x40000000 /* B30-B31 Extended NSS Bandwidth Support */
#define IEEE80211_VHTCAP_EXT_NSS_BW_SUPPORT_2   0x80000000 /* B30-B31 Extended NSS Bandwidth Support */
#define IEEE80211_VHTCAP_EXT_NSS_BW_SUPPORT_3   0xC0000000 /* B30-B31 Extended NSS Bandwidth Support */
#define IEEE80211_VHTCAP_EXT_NSS_BW_SUPPORT_S   30
#define IEEE80211_VHTCAP_EXT_NSS_BW_SUPPORT_MASK   0xC0000000

#define IEEE80211_VHTCAP_EXT_NSS_MASK   (IEEE80211_VHTCAP_SUP_CHAN_WIDTH_MASK | IEEE80211_VHTCAP_EXT_NSS_BW_SUPPORT_MASK)
/* VHTCAP combinations of "supported channel width" and "ext nss support"
 * which determine the NSS value supported by STA for <=80 MHz, 160 MHz
 * and 80+80 MHz. The macros to be read as combination of
 * "supported channel width" and "ext nss support" followed by NSS for 80MHz,
 * 160MHz and 80+80MHz defined as a function of Max VHT NSS supported.
 * Ex: IEEE80211_EXTNSS_MAP_01_80F1_160FDOT5_80P80NONE - To be reas as
 * supported channel width = 0
 * ext nss support = 1
 * NSS value for <=80MHz = max_vht_nss * 1
 * NSS value for 160MHz = max_vht_nss * (.5)
 * NSS value for 80+80MHz = not supported
 */
#define IEEE80211_EXTNSS_MAP_00_80F1_160NONE_80P80NONE      (IEEE80211_VHTCAP_SUP_CHAN_WIDTH_80 | IEEE80211_VHTCAP_NO_EXT_NSS_BW_SUPPORT)
#define IEEE80211_EXTNSS_MAP_01_80F1_160FDOT5_80P80NONE     (IEEE80211_VHTCAP_SUP_CHAN_WIDTH_80 | IEEE80211_VHTCAP_EXT_NSS_BW_SUPPORT_1)
#define IEEE80211_EXTNSS_MAP_02_80F1_160FDOT5_80P80FDOT5    (IEEE80211_VHTCAP_SUP_CHAN_WIDTH_80 | IEEE80211_VHTCAP_EXT_NSS_BW_SUPPORT_2)
#define IEEE80211_EXTNSS_MAP_03_80F1_160FDOT75_80P80FDOT75  (IEEE80211_VHTCAP_SUP_CHAN_WIDTH_80 | IEEE80211_VHTCAP_EXT_NSS_BW_SUPPORT_3)
#define IEEE80211_EXTNSS_MAP_10_80F1_160F1_80P80NONE        (IEEE80211_VHTCAP_SUP_CHAN_WIDTH_160 | IEEE80211_VHTCAP_NO_EXT_NSS_BW_SUPPORT)
#define IEEE80211_EXTNSS_MAP_11_80F1_160F1_80P80FDOT5       (IEEE80211_VHTCAP_SUP_CHAN_WIDTH_160 | IEEE80211_VHTCAP_EXT_NSS_BW_SUPPORT_1)
#define IEEE80211_EXTNSS_MAP_12_80F1_160F1_80P80FDOT75      (IEEE80211_VHTCAP_SUP_CHAN_WIDTH_160 | IEEE80211_VHTCAP_EXT_NSS_BW_SUPPORT_2)
#define IEEE80211_EXTNSS_MAP_13_80F2_160F2_80P80F1          (IEEE80211_VHTCAP_SUP_CHAN_WIDTH_160 | IEEE80211_VHTCAP_EXT_NSS_BW_SUPPORT_3)
#define IEEE80211_EXTNSS_MAP_20_80F1_160F1_80P80F1          (IEEE80211_VHTCAP_SUP_CHAN_WIDTH_80_160 | IEEE80211_VHTCAP_NO_EXT_NSS_BW_SUPPORT)
#define IEEE80211_EXTNSS_MAP_23_80F2_160F1_80P80F1          (IEEE80211_VHTCAP_SUP_CHAN_WIDTH_80_160 | IEEE80211_VHTCAP_EXT_NSS_BW_SUPPORT_3)

/*
 * 802.11ac VHT Capability IE
 */
struct supp_tx_mcs_extnss {
#if _BYTE_ORDER == _BIG_ENDIAN
        u_int16_t   reserved:2,             /* B62-B63 reserved */
                    ext_nss_capable:1,      /* B61 Ext NSS capability */
                    tx_high_data_rate:13;   /* B48-B60 Max Tx data rate */
#else
        u_int16_t   tx_high_data_rate:13,   /* B48-B60 Max Tx data rate */
                    ext_nss_capable:1,      /* B61 Ext NSS capability */
                    reserved:2;             /* B62-B63 reserved */
#endif
}__packed;

struct ieee80211_ie_vhtcap {
        u_int8_t    elem_id;
        u_int8_t    elem_len;
        u_int32_t   vht_cap_info;
        u_int16_t   rx_mcs_map;          /* B0-B15 Max Rx MCS for each SS */
        u_int16_t   rx_high_data_rate;   /* B16-B28 Max Rx data rate,
                                            Note:  B29-B31 reserved */
        u_int16_t   tx_mcs_map;          /* B32-B47 Max Tx MCS for each SS */
        struct supp_tx_mcs_extnss tx_mcs_extnss_cap;
} __packed;


/* VHT Operation  */
#define IEEE80211_VHTOP_CHWIDTH_2040          0 /* 20/40 MHz Operating Channel */
#define IEEE80211_VHTOP_CHWIDTH_80            1 /* 80 MHz Operating Channel */
#define IEEE80211_VHTOP_CHWIDTH_160           2 /* 160 MHz Operating Channel */
#define IEEE80211_VHTOP_CHWIDTH_80_80         3 /* 80 + 80 MHz Operating
                                                   Channel */
#define IEEE80211_VHTOP_CHWIDTH_REVSIG_160    1 /* 160 MHz Operating Channel
                                                   (revised signalling) */
#define IEEE80211_VHTOP_CHWIDTH_REVSIG_80_80  1 /* 80 + 80 MHz Operating Channel
                                                   (revised signalling) */

/*
 * 802.11ac VHT Operation IE
 */
struct ieee80211_ie_vhtop {
        u_int8_t    elem_id;
        u_int8_t    elem_len;
        u_int8_t    vht_op_chwidth;              /* BSS Operational Channel width */
        u_int8_t    vht_op_ch_freq_seg1;         /* Channel Center frequency */
        u_int8_t    vht_op_ch_freq_seg2;         /* Channel Center frequency applicable
                                                  * for 80+80MHz mode of operation */
        u_int16_t   vhtop_basic_mcs_set;         /* Basic MCS set */
} __packed;


/*
 * 802.11ng vendor specific VHT Interop Capability
 * with Vht cap & Vht op IE
 */
struct ieee80211_ie_interop_vhtcap {
        u_int8_t    elem_id;
        u_int8_t    elem_len;
        u_int32_t   vht_interop_oui;
        u_int8_t    sub_type;
        struct ieee80211_ie_vhtcap  vhtcapie;
        struct ieee80211_ie_vhtop   vhtopie;
} __packed;


/*
 * 802.11n Secondary Channel Offset element
 */
#define IEEE80211_SEC_CHAN_OFFSET_BYTES             3 /* size of sec chan offset element */
#define IEEE80211_SEC_CHAN_OFFSET_SCN               0 /* no secondary channel */
#define IEEE80211_SEC_CHAN_OFFSET_SCA               1 /* secondary channel above */
#define IEEE80211_SEC_CHAN_OFFSET_SCB               3 /* secondary channel below */

struct ieee80211_ie_sec_chan_offset {
     u_int8_t    elem_id;
     u_int8_t    len;
     u_int8_t    sec_chan_offset;
} __packed;

/*
 * 802.11ac Transmit Power Envelope element
 */
#define IEEE80211_VHT_TXPWR_IS_SUB_ELEMENT          1  /* It checks whether its  sub element */
#define IEEE80211_VHT_TXPWR_IS_VENDOR_SUB_ELEMENT   2  /* It checks whether its  sub element of vendor specific element */
#define IEEE80211_VHT_TXPWR_MAX_POWER_COUNT         4 /* Max TX power elements valid */
#define IEEE80211_VHT_TXPWR_NUM_POWER_SUPPORTED     4 /* Max TX power elements supported */
#define IEEE80211_VHT_TXPWR_LCL_MAX_PWR_UNITS_SHFT  3 /* B3-B5 Local Max transmit power units */

struct ieee80211_ie_vht_txpwr_env {
        u_int8_t    elem_id;
        u_int8_t    elem_len;
        u_int8_t    txpwr_info;       /* Transmit Power Information */
        u_int8_t    local_max_txpwr[4]; /* Local Max TxPower for 20,40,80,160MHz */
} __packed;

/*
 * 802.11ac Wide Bandwidth Channel Switch Element
 */

#define IEEE80211_VHT_EXTCH_SWITCH             1   /* For extension channel switch */
#define CHWIDTH_VHT20                          20  /* Channel width 20 */
#define CHWIDTH_VHT40                          40  /* Channel width 40 */
#define CHWIDTH_VHT80                          80  /* Channel width 80 */
#define CHWIDTH_VHT160                         160 /* Channel width 160 */

#define CHWIDTH_20                             20  /* Channel width 20 */
#define CHWIDTH_40                             40  /* Channel width 40 */
#define CHWIDTH_80                             80  /* Channel width 80 */
#define CHWIDTH_160                            160 /* Channel width 160 */

struct ieee80211_ie_wide_bw_switch {
        u_int8_t    elem_id;
        u_int8_t    elem_len;
        u_int8_t    new_ch_width;       /* New channel width */
        u_int8_t    new_ch_freq_seg1;   /* Channel Center frequency 1 */
        u_int8_t    new_ch_freq_seg2;   /* Channel Center frequency 2 */
} __packed;

#define IEEE80211_RSSI_RX       0x00000001
#define IEEE80211_RSSI_TX       0x00000002
#define IEEE80211_RSSI_EXTCHAN  0x00000004
#define IEEE80211_RSSI_BEACON   0x00000008
#define IEEE80211_RSSI_RXDATA   0x00000010

#define IEEE80211_RATE_TX 0
#define IEEE80211_RATE_RX 1
#define IEEE80211_LASTRATE_TX 2
#define IEEE80211_LASTRATE_RX 3
#define IEEE80211_RATECODE_TX 4
#define IEEE80211_RATECODE_RX 5
#define IEEE80211_RATEFLAGS_TX 6

#define IEEE80211_MAX_RATE_PER_CLIENT 8
/* Define for the P2P Wildcard SSID */
#define IEEE80211_P2P_WILDCARD_SSID         "DIRECT-"

#define IEEE80211_P2P_WILDCARD_SSID_LEN     (sizeof(IEEE80211_P2P_WILDCARD_SSID) - 1)

#ifdef WIN32
#include <poppack.h>
#endif

struct atfcntbl{
    u_int8_t     ssid[IEEE80211_NWID_LEN+1];
    u_int8_t     sta_mac[IEEE80211_ADDR_LEN];
    u_int32_t    value;
    u_int8_t     info_mark;   /*0--vap, 1-sta*/
    u_int8_t     assoc_status;     /*1--Yes, 0 --No*/
    u_int8_t     all_tokens_used;  /*1--Yes, 0 --No*/
    u_int32_t    cfg_value;
    u_int8_t     grpname[IEEE80211_NWID_LEN+1];
};

#define ATF_ACTIVED_MAX_CLIENTS   50
#define ATF_ACTIVED_MAX_ATFGROUPS 8
#define ATF_CFG_NUM_VDEV          16
#define ATF_CFG_GLOBAL_INDEX      0
#define ATF_PER_NOT_ALLOWED       1
#define ATF_SSID_NOT_EXIST        2

struct atftable{
    u_int16_t         id_type;
    struct atfcntbl   atf_info[ATF_ACTIVED_MAX_CLIENTS+ATF_CFG_NUM_VDEV];
    u_int16_t         info_cnt;
    u_int8_t          atf_status;
    u_int32_t         busy;
    u_int32_t         atf_group;
    u_int8_t          show_per_peer_table;
};

struct atfgroups{
    u_int8_t    grpname[IEEE80211_NWID_LEN + 1]; //group name
    u_int32_t   grp_num_ssid; //Number of ssids added in this group
    u_int32_t   grp_cfg_value; // Airtime for this group
    u_int8_t    grp_ssid[ATF_CFG_NUM_VDEV][IEEE80211_NWID_LEN+1]; // List of SSIDs in the group
};

struct atfgrouptable{
    u_int16_t         id_type;
    struct atfgroups   atf_groups[ATF_ACTIVED_MAX_ATFGROUPS];
    u_int16_t         info_cnt;
};

// Factor used to convert airtime between user space and driver
#define ATF_AIRTIME_CONVERSION_FACTOR 10
#define IEEE80211_MAX_IFNAME 16

struct ieee80211_clone_params {
	char		icp_name[IEEE80211_MAX_IFNAME];	/* device name */
	u_int16_t	icp_opmode;		/* operating mode */
	u_int32_t	icp_flags;		/* see IEEE80211_CLONE_BSSID for e.g */
    u_int8_t icp_bssid[IEEE80211_ADDR_LEN];    /* optional mac/bssid address */
        int32_t         icp_vapid;             /* vap id for MAC addr req */
    u_int8_t icp_mataddr[IEEE80211_ADDR_LEN];    /* optional MAT address */
};

#define	    IEEE80211_CLONE_BSSID       0x0001		/* allocate unique mac/bssid */
#define	    IEEE80211_NO_STABEACONS	    0x0002		/* Do not setup the station beacon timers */
#define    IEEE80211_CLONE_WDS          0x0004      /* enable WDS processing */
#define    IEEE80211_CLONE_WDSLEGACY    0x0008      /* legacy WDS operation */

/*
 * Station information block; the mac address is used
 * to retrieve other data like stats, unicast key, etc.
 */
struct ieee80211req_sta_info {
        u_int16_t       isi_len;                /* length (mult of 4) */
        u_int16_t       isi_freq;               /* MHz */
        u_int32_t       awake_time;             /* time is active mode */
        u_int32_t       ps_time;                /* time in power save mode */
        u_int32_t       isi_flags;      /* channel flags */
        u_int16_t       isi_state;              /* state flags */
        u_int8_t        isi_authmode;           /* authentication algorithm */
        int8_t          isi_rssi;
        int8_t          isi_min_rssi;
        int8_t          isi_max_rssi;
        u_int16_t       isi_capinfo;            /* capabilities */
        u_int8_t        isi_athflags;           /* Atheros capabilities */
        u_int8_t        isi_erp;                /* ERP element */
        u_int8_t        isi_ps;         /* psmode */
        u_int8_t        isi_macaddr[IEEE80211_ADDR_LEN];
        u_int8_t        isi_nrates;
                                                /* negotiated rates */
        u_int8_t        isi_rates[IEEE80211_RATE_MAXSIZE];
        u_int8_t        isi_txrate;             /* index to isi_rates[] */
        u_int32_t       isi_txratekbps; /* tx rate in Kbps, for 11n */
        u_int16_t       isi_ie_len;             /* IE length */
        u_int16_t       isi_associd;            /* assoc response */
        u_int16_t       isi_txpower;            /* current tx power */
        u_int16_t       isi_vlan;               /* vlan tag */
        u_int16_t       isi_txseqs[17];         /* seq to be transmitted */
        u_int16_t       isi_rxseqs[17];         /* seq previous for qos frames*/
        u_int16_t       isi_inact;              /* inactivity timer */
        u_int8_t        isi_uapsd;              /* UAPSD queues */
        u_int8_t        isi_opmode;             /* sta operating mode */
        u_int8_t        isi_cipher;
        u_int32_t       isi_assoc_time;         /* sta association time */
        struct timespec isi_tr069_assoc_time;   /* sta association time in timespec format */


        u_int16_t   isi_htcap;      /* HT capabilities */
        u_int32_t   isi_rxratekbps; /* rx rate in Kbps */
                                /* We use this as a common variable for legacy rates
                                   and lln. We do not attempt to make it symmetrical
                                   to isi_txratekbps and isi_txrate, which seem to be
                                   separate due to legacy code. */
        /* XXX frag state? */
        /* variable length IE data */
        u_int8_t isi_maxrate_per_client; /* Max rate per client */
        u_int16_t   isi_stamode;        /* Wireless mode for connected sta */
        u_int32_t isi_ext_cap;              /* Extended capabilities */
        u_int8_t isi_nss;         /* number of tx and rx chains */
        u_int8_t isi_is_256qam;    /* 256 QAM support */
        u_int8_t isi_operating_bands : 2; /* Operating bands */
#if ATH_SUPPORT_EXT_STAT
        u_int8_t  isi_chwidth;            /* communication band width */
        u_int32_t isi_vhtcap;             /* VHT capabilities */
#endif
        u_int8_t isi_rx_nss;         /* number of rx chains */
        u_int8_t isi_tx_nss;         /* number of tx chains */
#if ATH_EXTRA_RATE_INFO_STA
        u_int8_t isi_tx_rate_mcs;
        u_int8_t isi_tx_rate_flags;
#endif
        u_int8_t isi_r_latitude[32];
        u_int8_t isi_r_longitude[32];
        u_int8_t isi_l_latitude[32];
        u_int8_t isi_l_longitude[32];
        u_int64_t isi_tx_tput;             /* Tx Thput */
        u_int64_t isi_rx_tput;             /* Rx Thput */

};

#endif /* _NET80211_IEEE80211_H_ */




/*
** Key definitions moved to here to allow them to be published externally
** without having to export all of the other stuff.  These need to be consistent
** with the definitions in ieee80211_crypto.h
*/

#define	IEEE80211_KEY_XMIT	0x01	/* key used for xmit */
#define	IEEE80211_KEY_RECV	0x02	/* key used for recv */
#define	IEEE80211_KEY_GROUP	0x04	/* key used for WPA group operation */
#define IEEE80211_KEY_MFP   0x08    /* key also used for management frames */
#define	IEEE80211_KEY_SWENCRYPT	0x10	/* host-based encryption */
#define	IEEE80211_KEY_SWENMIC	0x20	/* host-based enmic */
#define IEEE80211_KEY_PERSISTENT 0x40   /* do not remove unless OS commands us to do so */
#define IEEE80211_KEY_PERSTA    0x80    /* per STA default key */
#define IEEE80211_KEY_SWDECRYPT 0x100   /* host-based decryption */
#define IEEE80211_KEY_SWDEMIC   0x200   /* host-based demic */
#define IEEE80211_KEY_SWCRYPT   (IEEE80211_KEY_SWENCRYPT | IEEE80211_KEY_SWDECRYPT)
#define IEEE80211_KEY_SWMIC     (IEEE80211_KEY_SWENMIC | IEEE80211_KEY_SWDEMIC)

/*
** Wireless Mode related definitions replicated here to allow them to be published
** externally without having to export all of the other stuff.  These need to be consistent
** with the definitions in ath_dev.h
*/

#ifndef WIRELESS_MODE_MAX
#define WIRELESS_MODE_MAX   (12)
#endif

#ifndef IEEE80211_IPV4_LEN
#define IEEE80211_IPV4_LEN 4
#endif

#ifndef IEEE80211_IPV6_LEN
#define IEEE80211_IPV6_LEN 16
#endif
#endif /* IEEE80211_EXTERNAL_H */

#ifndef __WRT_RADAUTH_H
#define __WRT_RADAUTH_H
void handle_new_sta (unsigned char *mac_addr);
struct  sta {
	unsigned char mac[6];
#define STA_RADIUS_ACCEPTED 1
#define STA_RADIUS_WAITING  2
#define STA_RADIUS_DENIED   0
#define STA_RADIUS_TIMEOUT  3
	unsigned char state;
	unsigned char authorized;
	unsigned char changed;
	short authretries_primary;
	short authretries_secondary;
	struct sta *next; /* Pointer to next STA in linked list */
	char *lastserver;
	time_t lastseen;
	time_t lastauth_primary;
	time_t lastauth_secondary;
	int id; /* radius packet identifier */
	unsigned char random[16];
};
struct vsalist
{
	int    attr_type;
	int    vendor_id;
	char * attr_action;
	struct vsalist *next;
};
struct radius_server
{
		char *server;
		char *secret;
		char *password;
		short port;
};
struct wrt_radauth_config
{
	struct vsalist *vsa;
	struct sta *first;
	struct radius_server primary;
	struct radius_server secondary;
	short  macfmt;
	short  reauth_time;
	short  retry_time;
	short  request_timeout;
	short  request_retries;
	int    ioctl_sock;
	int    netlink_sock;
	int    radius_sock;
	unsigned int log_level;
	unsigned char syslog;
	unsigned char std_out;
	FILE*  file_fd;
	int ifindex;
	char*  iface;
};
struct maclist {
	uint count;         /* number of MAC addresses */
	struct ether_addr ea[1];    /* variable length array of MAC addresses */
};
#define WRT_LOG_CRIT 0x00000001
#define WRT_LOG_INFO 0x00000002
#define WRT_LOG_DEBUG 0x00000004
int wrtlog_crit (const char *fmt, ...);
int wrtlog_info (const char *fmt, ...);
int wrtlog_debug (const char *fmt, ...);
#endif


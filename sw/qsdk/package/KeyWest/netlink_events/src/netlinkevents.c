#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <syslog.h>
#include <linux/rtnetlink.h>
#include <fcntl.h>

int prev_ethintf_status = 0;
int curr_ethintf_status = 0;

enum INTF_STATUS {
    INTF_STATUS_DOWN = 1,
    INTF_STATUS_UP_NOT_RUNNING = 2,
    INTF_STATUS_UP_RUNNING = 3
};

void kwn_ethevent_file_write( char *ifName, char *ifUpp, char *ifRunn )
{
    time_t rawtime;
    struct tm *timeinfo;
    FILE *sify_fp;
    int len;
    char t[50];

    if( !strcmp( ifUpp, "DOWN" ) ) {
        curr_ethintf_status = INTF_STATUS_DOWN;
    }
    else if( !strcmp( ifUpp, "UP" ) && !strcmp( ifRunn, "RUNNING" ) ) {
        curr_ethintf_status = INTF_STATUS_UP_RUNNING;
    }
    else {
        curr_ethintf_status = INTF_STATUS_UP_NOT_RUNNING;
    }

    if( prev_ethintf_status == curr_ethintf_status )
        return;
    /* Get current time */
    time( &rawtime );
    timeinfo = localtime( &rawtime );
    len = strlen( asctime( timeinfo ) ) - 1;
    memcpy( t, asctime( timeinfo ), len );
    t[len] = '\0';

    /* Open file for writting */
    sify_fp = fopen("/tmp/eth_events.txt", "a+");

    if (sify_fp == NULL) {
        printf("File opening error\n");
        return;
    }

    switch( curr_ethintf_status )
    {
        case INTF_STATUS_DOWN:
            fprintf(sify_fp, "%s: Ethernet is Down\n", t);
            syslog(LOG_INFO, " Ethernet is Down\n", t);
            break;
        case INTF_STATUS_UP_NOT_RUNNING:
            fprintf(sify_fp, "%s: Ethernet is Up and not running \n", t );
            syslog(LOG_INFO, " Ethernet is Up and not running\n", t );
            break;
        case INTF_STATUS_UP_RUNNING:
            fprintf(sify_fp, "%s: Ethernet is Up\n", t);
            syslog(LOG_INFO, " Ethernet is Up\n", t);
            break;
        default:
            break;
    }
    fclose(sify_fp); /* close file */
    prev_ethintf_status = curr_ethintf_status;
}

struct rtnl_handle
{
    int                 fd;
    struct sockaddr_nl  local;
    struct sockaddr_nl  peer;
    uint32_t            seq;
    uint32_t            seqdump;
};

static inline void rtnl_close(struct rtnl_handle *rth)
{
    close(rth->fd);
}

static inline int 
rtnl_open(struct rtnl_handle *rth, unsigned subscriptions)
{
    int addr_len;

    memset(rth, 0, sizeof(rth));

    rth->fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (rth->fd < 0) {
        perror("Cannot open netlink socket");
        return -1;
    }
    memset(&rth->local, 0, sizeof(rth->local));
    rth->local.nl_family = AF_NETLINK;
    rth->local.nl_groups = subscriptions;

    if (bind(rth->fd, (struct sockaddr*)&rth->local, sizeof(rth->local)) < 0) {
        perror("Cannot bind netlink socket");
        return -1;
    }
    addr_len = sizeof(rth->local);
    if (getsockname(rth->fd, (struct sockaddr*)&rth->local,
                (socklen_t *) &addr_len) < 0) {
        perror("Cannot getsockname");
        return -1;
    }
    if (addr_len != sizeof(rth->local)) {
        fprintf(stderr, "Wrong address length %d\n", addr_len);
        return -1;
    }
    if (rth->local.nl_family != AF_NETLINK) {
        fprintf(stderr, "Wrong address family %d\n", rth->local.nl_family);
        return -1;
    }
    rth->seq = time(NULL);
    return 0;
}

static int
LinkCatcher(struct nlmsghdr *nlh) {
    struct ifinfomsg* ifi;

    /* If interface is getting destoyed */
    if(nlh->nlmsg_type == RTM_DELLINK)
        return 0;

    /* Only keep add/change events */
    if(nlh->nlmsg_type != RTM_NEWLINK)
        return 0;
#if 0
    fprintf(stderr, "nlmsg_type = %d.\n", nlh->nlmsg_type);
#endif
    ifi = (struct ifinfomsg *)NLMSG_DATA(nlh);
    /* Check for attributes */
    if (nlh->nlmsg_len > NLMSG_ALIGN(sizeof(struct ifinfomsg))) {
        int attrlen = nlh->nlmsg_len - NLMSG_ALIGN(sizeof(struct ifinfomsg));
        struct rtattr *attr = (struct rtattr *) ((char *) ifi +
                NLMSG_ALIGN(sizeof(struct ifinfomsg)));

        while (RTA_OK(attr, attrlen)) {
            if ( attr->rta_type == IFLA_IFNAME) {
                if ( strcmp((char *)RTA_DATA(attr), "eth0") == 0 ) { 
                    kwn_ethevent_file_write( (char *)RTA_DATA(attr), 
                            (char *)(ifi->ifi_flags & IFF_UP ? "UP" : "DOWN"), 
                            (char *)(ifi->ifi_flags & IFF_RUNNING ? "RUNNING" : "NOTRUNNING"));
                }
            }
            attr = RTA_NEXT(attr, attrlen);
        }
    }
    return 0;
}

static inline void
handle_netlink_events(struct rtnl_handle *  rth) {
    while(1) {
        struct sockaddr_nl sanl;
        socklen_t sanllen = sizeof(struct sockaddr_nl);
        struct nlmsghdr *h;
        int amt;
        char buf[8192];

        amt = recvfrom(rth->fd, buf, sizeof(buf), MSG_DONTWAIT, (struct sockaddr*)&sanl, &sanllen);
        if(amt < 0) {
            if(errno != EINTR && errno != EAGAIN) {
                fprintf(stderr, "%s: error reading netlink: %s.\n",
                        __PRETTY_FUNCTION__, strerror(errno));
            }
            return;
        }
        if(amt == 0) {
            fprintf(stderr, "%s: EOF on netlink??\n", __PRETTY_FUNCTION__);
            return;
        }
        h = (struct nlmsghdr*)buf;
        while(amt >= (int)sizeof(*h)) {
            int len = h->nlmsg_len;
            int l = len - sizeof(*h);
            if(l < 0 || len > amt) {
                fprintf(stderr, "%s: malformed netlink message: len=%d\n", __PRETTY_FUNCTION__, len);
                break;
            }
            switch(h->nlmsg_type) {
                case RTM_NEWLINK:
                case RTM_DELLINK:
                    LinkCatcher(h);
                    break;
                default:
                    fprintf(stderr, "%s: got nlmsg of type %#x.\n", __PRETTY_FUNCTION__, h->nlmsg_type);
                    break;
            }
            len = NLMSG_ALIGN(len);
            amt -= len;
            h = (struct nlmsghdr*)((char*)h + len);
        }
        if(amt > 0)
            fprintf(stderr, "%s: remnant of size %d on netlink\n", __PRETTY_FUNCTION__, amt);
    }
}

static inline int
wait_for_event(struct rtnl_handle * rth) {
    /* Forever */
    while(1) {
        fd_set rfds;       /* File descriptors for select */
        int last_fd; /* Last fd */
        int ret;

        /* Guess what ? We must re-generate rfds each time */
        FD_ZERO(&rfds);
        FD_SET(rth->fd, &rfds);
        last_fd = rth->fd;

        /* Wait until something happens */
        ret = select(last_fd + 1, &rfds, NULL, NULL, NULL);
        /* Check if there was an error */
        if(ret < 0) {
            if(errno == EAGAIN || errno == EINTR)
                continue;
            fprintf(stderr, "Unhandled signal - exiting...\n");
            break;
        }
        /* Check if there was a timeout */
        if(ret == 0)
            continue;
        
        /* Check for interface discovery events. */
        if(FD_ISSET(rth->fd, &rfds))
            handle_netlink_events(rth);
    }
    return(0);
}

int main()
{
    struct rtnl_handle rth;

    /* Open netlink channel */
    if(rtnl_open(&rth, RTMGRP_LINK) < 0) {
        perror("Can't initialize rtnetlink socket");
        return(1);
    }

    /* Do what we have to do */
    wait_for_event(&rth);

    /* Cleanup - only if you are pedantic */
    rtnl_close(&rth);
    return 0;
}

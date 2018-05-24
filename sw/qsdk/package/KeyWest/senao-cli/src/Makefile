PRODUCT_CONFIG_MAKE = ../../configs/product_config.make
ifeq ($(wildcard $(PRODUCT_CONFIG_MAKE)),$(PRODUCT_CONFIG_MAKE))
include $(PRODUCT_CONFIG_MAKE)
endif

.PHONY:	all clean depend rebuild

CC = $(CROSS)gcc
AR = $(CROSS)ar
LD = $(CROSS)ld
RANLIB= $(CROSS)ranlib
CFLAGS = -Wall -pipe $(EXTRA_CFLAGS) -g -DHAVE_CLOCK_GETTIME $(TARGET_CPPFLAGS) $(TARGET_CFLAGS)
LDFLAGS=$(EXTRA_LDFLAGS)


CLI_OBJS =   cli.o  cmdedit.o get_terminal_width_height.o util.o 

TABLE_OBJS = ct_main.o ct_status.o ct_system.o ct_router.o ct_wless.o ct_management.o #ct_upgrade.o ct_tools.o

SETTING_OBJS = common.o cli_status.o cli_system.o cli_router.o cli_wless.o cli_management.o #cli_manufacture.o cli_wan.o cli_lan.o cli_nat.o  cli_diag.o

#ifeq ($(CONFIG_SUPPORT_MULTI_WLAN_PLATFORM),y)
##SETTING_OBJS += cli_multi_wlan.o
#CFLAGS += -DSUPPORT_MULTI_WLAN_PLATFORM=1
#else
#SETTING_OBJS += cli_wlan.o
#endif

#ifeq ($(CONFIG_HAS_RADIO_SETTING),y)
#ifeq ($(CONFIG_EOR7550),y)
#SETTING_OBJS += cli_eor_wlan.o
#TABLE_OBJS += ct_eor_net.o
#endif
#endif

#ifeq ($(CONFIG_NETCOMM),y)
#TABLE_OBJS += ct_netcomm_system.o
#endif

#ifeq ($(CONFIG_NETCOMM),y)
#TABLE_OBJS += ct_netcomm_net.o
#endif

CLI_OBJS += $(addprefix setting/, $(SETTING_OBJS))
CLI_OBJS += $(addprefix tables/, $(TABLE_OBJS))
CLI_OBJS += $(addprefix ISD2/MIPS32_APPS/ap_cfg/, apcfg.o)
CLI_OBJS += $(addprefix ISD2/MIPS32_APPS/sysutil/, sysUtil.o)
CLI_OBJS += $(addprefix ISD2/MIPS32_APPS/sysconfig/, sysconfig.o)

INCLUDES =  -I./ -I./include -I./setting/include -I./ISD2/configs/h -I./ISD2/MIPS32_APPS/h \
			-I./ISD2/MIPS32_APPS/ap_cfg/include -I./ISD2/MIPS32_APPS/sysutil/include \
			-I$(STAGING_DIR)/usr/include -I$(wildcard $(BUILD_DIR)/uci-*)

LIBS += $(TARGET_LDFLAGS) -lpcre -luci

#ifneq ($(SYSUTIL_SHARED_LIB_USE_RT),0)
#LIBS += -lrt
#endif
#ifeq ($(CONFIG_HAS_RADIO_SETTING),y)
#CFLAGS +=-DHAS_RADIO_SETTING=1
#endif
#ifeq ($(CONFIG_RT2860V2_AP_REPEATER_ROUTER),y)
#CFLAGS +=-DHAS_OP_MODE_ARRP=1
#endif

#ifeq ($(CONFIG_RT2860V2_STA),y)
#CFLAGS += -DHAS_WLAN_STA_FUNCTION=1
#endif

#ifneq ($(CONFIG_NOT_SUPPORT_RALINK_WLAN),y)
#CFLAGS += -DSUPPORT_RALINK_WLAN
#endif

#ifeq ($(CONFIG_ATHEROS_HAS_XAT),y)
#CFLAGS += -DHAS_WLAN_STA_FUNCTION=1
#endif

#ifeq ($(CONFIG_VLAN_SUPPORT),y)
#CFLAGS +=-DHAS_VLAN_SUPPORT=1
#endif

#ifeq ($(CONFIG_HAS_PRIORITY_WEB_ACCOUNT),y)
#CFLAGS +=-DHAS_PRIORITY_WEB_ACCOUNT=1
#endif

#ifeq ($(CONFIG_HAS_PRIORITY_WEB_ACCOUNT),y)
#CFLAGS += -DHAS_PRIORITY_WEB_ACCOUNT=1
#endif

#ifeq ($(CONFIG_HAS_LED_CONTROL),y)
#CFLAGS += -DHAS_LED_CONTROL=1
#endif

#ifeq ($(CONFIG_HAS_ADVANCE_WMM_SETTING),y)
#MY_CFLAGS +=-DHAS_ADVANCE_WMM_SETTING=1
#endif

#ifeq ($(CONFIG_COUNT_BY_EACH_STA),y)
#CFLAGS +=-DCOUNT_EACH_STA=1
#endif

#ifeq ($(CONFIG_RT2860V2_AP_APCLI),y)
#CFLAGS +=-DHAS_LOCAL_NTP_SERVER=1
#endif

#ifeq ($(CONFIG_RT2860V2_ADVANCED_STATISTICS),y)
#CFLAGS += -DSUPPORT_WLAN_ADVANCED_STATISTICS
#endif

#ifeq ($(CONFIG_HTTPD_REMOTEPORT),y)
#CFLAGS += -DHTTPD_REMOTEPORT_FUNCTION=1
#endif

#ifeq ($(CONFIG_HAS_ONLY_LAN_FUNCTION),y)
#CFLAGS += -DHAS_ONLY_LAN_FUNCTION=1
#endif

#ifeq ($(CONFIG_HAS_QOS_ENGENIUS),y)
#CFLAGS +=-DHAS_ENGENIUS_STYLE_QOS=1
#endif

#ifeq ($(CONFIG_AP_PROFILE),y)
#CFLAGS +=-DHAS_AP_PROFILE=1
#endif

#ifeq ($(CONFIG_HAS_DHCRELAY_FLEXIBLE_CIRCUIT_ID),y)
#CFLAGS += -DHAS_DHCRELAY_FLEXIBLE_CIRCUIT_ID=1
#endif

DEPLIBS=sysutil ap_cfg


all: cli

build-deplibs:
ifneq ($(DEPLIBS),)
	for d in $(DEPLIBS); do \
		($(MAKE) -C $(PWD)/../$$d all) || exit; \
	done;
endif

clean-deplibs:
ifneq ($(DEPLIBS),)
	for d in $(DEPLIBS); do \
		($(MAKE) -C $(PWD)/../$$d clean) || exit; \
	done;
endif

rebuild: clean clean-deplibs build-deplibs all

cli: $(CLI_OBJS)
	@echo 'CC $@'
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(CLI_OBJS) $(LIBS)

%.o: %.c
	@echo 'CC $@'
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 

clean:
	$(RM) -f *.o *~ *.a .depend cli
	find ./ -name "*\.o" | xargs rm -rf

depend: .depend

.depend:
	CC=$(CC) ../../util/mkdep $(CFLAGS) $(INCLUDES) `ls *.c`

install:
	install -c ./cli $(PREFIX)/sbin






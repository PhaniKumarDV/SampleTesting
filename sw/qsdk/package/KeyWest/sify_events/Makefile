#
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=sify_events
PKG_VERSION:=0.1
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/sify_events
  SECTION:=keywest
  CATEGORY:=Keywest Applications
  TITLE:=An application to generate logs
endef

define Package/sify_events/description
	This software monitors the chages and then represent the apprpriate logs via syslog server.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef
define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) clean
	$(call Build/Compile/Default, \
		CFLAGS+="$(EXTRA_CFLAGS)" \
		LDFLAGS+="$(EXTRA_LDFLAGS)" \
	)
endef

define Package/sify_events/install	
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_BIN) ./files/sify_events.init $(1)/etc/init.d/sify_events.sh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/sify_events $(1)/usr/sbin/sify_events
endef

$(eval $(call BuildPackage,sify_events))

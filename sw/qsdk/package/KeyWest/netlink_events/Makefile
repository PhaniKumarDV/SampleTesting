#
# Copyright (C) 2010-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=kw-netlinkevents
PKG_RELEASE:=1
PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)
include $(INCLUDE_DIR)/package.mk

define Package/kw-netlinkevents
  SECTION:=keywest
  CATEGORY:=Keywest Applications
  TITLE:=CFGUPDATE Application Program
  MAINTAINER:=Srilatha Tadiboina <srilatha@keywestnetworks.com>
  DEPENDS:=+libuci
endef

define Package/kw-netlinkevents/description
	Ethernet Events Application.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Configure
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TARGET_CFLAGS) -Wall" \
		LDFLAGS="$(TARGET_LDFLAGS)"
endef

define Package/kw-netlinkevents/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/netlinkevents $(1)/etc/init.d/netlinkevents
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/netlinkevents $(1)/usr/bin/
endef

$(eval $(call BuildPackage,kw-netlinkevents))

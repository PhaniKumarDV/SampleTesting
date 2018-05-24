#
# Copyright (C) 2010-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=kw-gps
PKG_RELEASE:=1
PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)
include $(INCLUDE_DIR)/package.mk

define Package/kw-gps
  SECTION:=keywest
  CATEGORY:=Keywest Applications
  TITLE:=GPS Application Program
  MAINTAINER:=Rajasekhar Somavaram <rsomavaram@proxim.com>
  DEPENDS:=+libuci
endef

define Package/kw-gps/description
	GPS Application to populate latitude, longitude & altitude to UCI.
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

define Package/kw-gps/install
    $(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/gps.init $(1)/etc/init.d/gps
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/gps $(1)/bin/
endef

$(eval $(call BuildPackage,kw-gps))

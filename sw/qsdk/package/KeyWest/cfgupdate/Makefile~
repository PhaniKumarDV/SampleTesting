#
# Copyright (C) 2010-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=kw-cfgupdate
PKG_RELEASE:=1
PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)
include $(INCLUDE_DIR)/package.mk

define Package/kw-cfgupdate
  SECTION:=keywest
  CATEGORY:=Keywest Applications
  TITLE:=CFGUPDATE Application Program
  MAINTAINER:=Srilatha Tadiboina <srilatha@keywestnetworks.com>
  DEPENDS:=+libuci
endef

define Package/kw-cfgupdate/description
	Cfg Update Application to support upgrade configuration from APP or NMS.
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

define Package/kw-cfgupdate/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/cfgupdate $(1)/bin/
endef

$(eval $(call BuildPackage,kw-cfgupdate))

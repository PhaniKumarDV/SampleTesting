#
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=kw-ipaddr
PKG_VERSION:=0.1
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/kw-ipaddr
  TITLE:=An IP address application program
  SECTION:=keywest
  CATEGORY:=Keywest Applications
  MAINTAINER:=Srilatha Tadiboina <srilatha@keywestnetworks.com>
  DEPENDS:=+libuci
endef

define Package/kw-ipaddr/description
	This application program for getting IP address on interface.
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

define Package/kw-ipaddr/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/ipaddrbrlan $(1)/etc/init.d/ipaddrbrlan
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/kwn_ipaddr $(1)/usr/sbin/kwn_ipaddr
endef

$(eval $(call BuildPackage,kw-ipaddr))

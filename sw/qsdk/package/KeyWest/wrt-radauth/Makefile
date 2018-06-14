#
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=wrt-radauth
PKG_VERSION:=0.1
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/wrt-radauth
  SECTION:=net
  CATEGORY:=Network
  TITLE:=A Radius MAC authenticator for Atheros based access points
endef

define Package/wrt-radauth/description
	This software watches the stations associating to a Atheros based 
	AccessPoint and sends an authentication request to the radius-server specified
	wrt-radauth.conf file.
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

define Package/wrt-radauth/install	
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DIR) $(1)/etc/config/
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/wrt-radauth $(1)/usr/sbin/wrt-radauthd
	$(INSTALL_BIN) ./files/wrt-radauth.init $(1)/etc/init.d/wrt-radauth
	$(INSTALL_CONF) ./files/wrt-radauth.conf $(1)/etc/
	$(INSTALL_CONF) ./files/wrt-radauth.uci $(1)/etc/config/wrt-radauth
endef

$(eval $(call BuildPackage,wrt-radauth))

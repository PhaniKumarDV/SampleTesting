
include $(TOPDIR)/rules.mk

PKG_NAME:=locator
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)
PKG_CHECK_FORMAT_SECURITY:=0

include $(INCLUDE_DIR)/package.mk

define Package/locator
  TITLE:=Title of the Package
  SECTION:=keywest
  CATEGORY:=Keywest Applications
  MAINTAINER:=Chandra Mohan <cmohan@proxim.com>
endef

define Package/locator/description
	Locator sends device information like MAC Address, IP Address, Opmode, firmware version to locator tool.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/locator/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/locator $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/discover $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/usr/share/locator
	$(INSTALL_BIN) ./files/default.script $(1)/usr/share/locator/
	$(INSTALL_DIR) $(1)/lib/network
	$(INSTALL_BIN) ./files/enh-common.sh $(1)/lib/network/
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) ./files/auth.sh $(1)/lib/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/locator_init $(1)/etc/init.d/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/lanip $(1)/etc/init.d/
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_BIN) ./files/firmware_version $(1)/etc/
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_BIN) ./files/webpasswd $(1)/etc/
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_BIN) ./files/functions_custom.sh $(1)/etc/

endef

$(eval $(call BuildPackage,locator))

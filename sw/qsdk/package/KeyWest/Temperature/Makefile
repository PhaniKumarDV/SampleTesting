
include $(TOPDIR)/rules.mk

PKG_NAME:=Temperature
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)
PKG_CHECK_FORMAT_SECURITY:=0

include $(INCLUDE_DIR)/package.mk

define Package/kw-temperature
  TITLE:=Tempearture Module
  SECTION:=keywest
  CATEGORY:=Keywest Applications
  MAINTAINER:=Rajasekhar Somavaram <rsomavaram@proxim.com>
  DEPENDS:=+libuci
endef

define Package/kw-temperature/description
	Enable temperature reading and logging module.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

MAKEOPTS:= \
	CC="$(TARGET_CC)" \
	CFLAGS="$(TARGET_CFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS)"

define Build/Compile
    $(MAKE) -C $(PKG_BUILD_DIR) $(MAKEOPTS)
endef

define Package/kw-temperature/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/temp-log.init $(1)/etc/init.d/temp-log
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/temp-log $(1)/usr/sbin/
	$(INSTALL_BIN) ./files/temp-log.sh $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,kw-temperature))

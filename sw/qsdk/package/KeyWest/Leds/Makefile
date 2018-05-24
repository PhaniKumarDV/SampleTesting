
include $(TOPDIR)/rules.mk

PKG_NAME:=kw-leds
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)
PKG_CHECK_FORMAT_SECURITY:=0

include $(INCLUDE_DIR)/package.mk

define Package/kw-leds
  TITLE:=LED Module
  SECTION:=keywest
  CATEGORY:=Keywest Applications
  MAINTAINER:=Rajasekhar Somavaram <rsomavaram@proxim.com>
  DEPENDS:=+libuci +libpthread
endef

define Package/kw-leds/description
	LED Module
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

define Package/kw-leds/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/leds.init $(1)/etc/init.d/leds
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/leds $(1)/usr/bin/
endef

$(eval $(call BuildPackage,kw-leds))

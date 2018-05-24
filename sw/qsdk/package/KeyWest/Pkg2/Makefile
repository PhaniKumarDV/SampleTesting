
include $(TOPDIR)/rules.mk

PKG_NAME:=pkg2
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)
PKG_CHECK_FORMAT_SECURITY:=0

include $(INCLUDE_DIR)/package.mk

define Package/pkg2
  TITLE:=Title of the Test Package
  SECTION:=keywest
  CATEGORY:=Keywest Applications
  MAINTAINER:=Rajasekhar Somavaram <rsomavaram@proxim.com>
endef

define Package/pkg2/description
	Test Package Description.
	Here goes this package description.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/pkg2/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/Pkg2 $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,pkg2))

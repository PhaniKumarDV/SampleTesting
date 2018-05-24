
include $(TOPDIR)/rules.mk

PKG_NAME:=kw-base-files
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/kw-base-files
  TITLE:=Keywest Base files
  SECTION:=keywest
  CATEGORY:=Keywest Applications
  MAINTAINER:=Rajasekhar Somavaram <rsomavaram@proxim.com>
endef

define Package/kw-base-files/description
	Keywest project specific base files
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile/Default

endef
Build/Compile = $(Build/Compile/Default)


define Package/kw-base-files/install
	$(CP) ./files/* $(1)/
endef

$(eval $(call BuildPackage,kw-base-files))

#
# Copyright (C) 2008-2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/target.mk

PKG_NAME:=senao-cli
PKG_VERSION:=1.8.16
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)/

include $(INCLUDE_DIR)/package.mk

ifeq ($(CONFIG_CLI_SSH_SUPPORT),n)
	TARGET_CFLAGS+=-DCLI_SSH_SUPPORT=0
else
	TARGET_CFLAGS+=-DCLI_SSH_SUPPORT=1
endif

ifeq ($(CONFIG_CLI_HTTPS_SUPPORT),n)
        TARGET_CFLAGS+=-DCLI_HTTPS_SUPPORT=0
else
        TARGET_CFLAGS+=-DCLI_HTTPS_SUPPORT=1
endif

ifeq ($(CONFIG_CLI_EMAILALERT_SUPPORT),n)
        TARGET_CFLAGS+=-DCLI_EMAILALERT_SUPPORT=0
else
        TARGET_CFLAGS+=-DCLI_EMAILALERT_SUPPORT=1
endif

ifeq ($(CONFIG_CLI_GUESTNETWORK_SUPPORT),n)
        TARGET_CFLAGS+=-DCLI_GUESTNETWORK_SUPPORT=0
else
        TARGET_CFLAGS+=-DCLI_GUESTNETWORK_SUPPORT=1
endif

ifeq ($(CONFIG_CLI_DEVICEDISCOVERY_SUPPORT),n)
        TARGET_CFLAGS+=-DCLI_DEVICEDISCOVERY_SUPPORT=0
else
        TARGET_CFLAGS+=-DCLI_DEVICEDISCOVERY_SUPPORT=1
endif

MAKEOPTS:= \
	$(TARGET_CONFIGURE_OPTS) \
	CFLAGS="$(TARGET_CFLAGS)" \
	BOARD="$(SUBTARGET)" \
	STAGING_DIR="$(STAGING_DIR)" \
	BUILD_DIR="$(BUILD_DIR)" \
	BUILD_DIR_HOST="$(BUILD_DIR_HOST)"

define Package/senao-cli
  TITLE:=Senao CLI
  SECTION:=keywest
  CATEGORY:=Keywest Applications
  MAINTAINER:=Rajasekhar Somavaram <rsomavaram@proxim.com>
  DEPENDS:=+libpcre +libuci
  VARIANT:=senao-cli
endef

define Package/senao-cli/description
  Senao CLI.
endef

ifndef BUILD_DIR_DEV
  define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) src/* $(PKG_BUILD_DIR)
  endef
endif

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(MAKEOPTS)
endef

define Package/senao-cli/install
	$(CP) ./base-files/* $(1)/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/cli $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,senao-cli))

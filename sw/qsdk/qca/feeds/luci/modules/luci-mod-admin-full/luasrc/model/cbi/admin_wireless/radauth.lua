-- Copyr0ight 2008 Steven Barth <steven@midlink.org>
-- Copyright 2010-2011 Jo-Philipp Wich <jow@openwrt.org>
-- Licensed to the public under the Apache License 2.0.

m = Map("wrt-radauth", translate("RADIUS Authentication"))
	s = m:section(TypedSection, "system")
	s.addremove = false
	s.anonymous = true

	s:option(Flag, "enableRadAuth", "Enable RADIUS")

	s = m:section(TypedSection, "system", translate("Primary Server"))
	s.addremove = false
	s.anonymous = true
	s:option(Value, "primaryServer", translate("Primary Server"))
	s:option(Value, "primaryPort", translate("Primary Server Port"))
	pw1 = s:option(Value, "primarySecret", translate("Primary Shared Secret"))
	pw1.password = true

	s = m:section(TypedSection, "system", translate("Secondary Server"))
	s.addremove = false
	s.anonymous = true
	s:option(Value, "secondaryServer", translate("Seconday Server"))
	s:option(Value, "secondaryPort", translate("Secondary Server Port"))
	pw2 = s:option(Value, "secondarySecret", translate("Secondary Shared Secret"))
	pw2.password = true

	s = m:section(TypedSection, "system", translate("RADIUS Parameters"))
	s.addremove = false
	s.anonymous = true
	s:option(Value, "reauthTime", translate("Re-authentication Time"), "sec")
	s:option(Value, "retryTime", translate("Retry Time"), "sec")
	s:option(Value, "requestRetries", translate("Retry Count"))
	s:option(Value, "requestTimeout", translate("Retry Count Period"), "sec")


function m.on_commit(map)
    luci.util.exec("/etc/init.d/wrt-radauth restart")
    end

return m

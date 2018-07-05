-- Copyright 2008 Steven Barth <steven@midlink.org>
-- Copyright 2010-2011 Jo-Philipp Wich <jow@openwrt.org>
-- Licensed to the public under the Apache License 2.0.

m = Map("tool", translate("Performance Tool"))
    s = m:section(TypedSection, "tool")
            s.addremove = false
            s.anonymous = true

local mode = luci.sys.exec("uci get wireless.@wifi-iface[1].mode")
local wds = luci.sys.exec("uci get wireless.@wifi-iface[1].wds")
if (string.match(mode,"ap") and string.match(wds,"1") ) then
	s:option(Value, "mac", translate("SU MAC"))
end
	s:option(Value, "size", translate("Packet Size"), "(1000-1490)Bytes")
	s:option(Value, "dur", translate("Duration"), "(1-1200)Sec")

function m.on_commit(map)
    luci.util.exec("/etc/init.d/KWtool start")
    luci.util.exec("/etc/init.d/KWtool reload")
    end

return m

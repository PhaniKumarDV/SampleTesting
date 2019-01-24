-- Copyright 2008 Steven Barth <steven@midlink.org>
-- Licensed to the public under the Apache License 2.0.

local ipc = require "luci.ip"

m = Map("dhcp", translate("DHCP Fixed Leases"))

s = m:section(TypedSection, "dnsmasq")
s.anonymous = true
s.addremove = false

--s:tab("general", translate("General Settings"))

s = m:section(TypedSection, "host", translate("Fixed Leases"))

s.addremove = true
s.anonymous = true
s.template = "cbi/tblsection"

name = s:option(Value, "name", translate("Hostname"))
name.datatype = "hostname"
name.rmempty  = true

mac = s:option(Value, "mac", translate("MAC Address"))
mac.datatype = "list(macaddr)"
mac.rmempty  = true

ip = s:option(Value, "ip", translate("IP Address"))
ip.datatype = "or(ip4addr,'ignore')"

ipc.neighbors({ family = 4 }, function(n)
	if n.mac and n.dest then
		ip:value(n.dest:string())
		mac:value(n.mac, "%s (%s)" %{ n.mac, n.dest:string() })
	end
end)

function ip.validate(self, value, section)
	local m = mac:formvalue(section) or ""
	local n = name:formvalue(section) or ""
	if value and #n == 0 and #m == 0 then
		return nil, translate("One of hostname or mac address must be specified!")
	end
	return Value.validate(self, value, section)
end


return m

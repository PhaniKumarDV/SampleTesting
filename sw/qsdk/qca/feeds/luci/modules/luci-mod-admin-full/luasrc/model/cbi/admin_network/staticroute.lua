-- Copyright 2008 Steven Barth <steven@midlink.org>
-- Licensed to the public under the Apache License 2.0.

local wa = require "luci.tools.webadmin"
local fs = require "nixio.fs"

m = Map("network",
	translate("Static Routes"))

s = m:section(TypedSection, "route")
s.addremove = true
s.anonymous = true

s.template  = "cbi/tblsection"

iface = s:option(ListValue, "interface", translate("Interface"))
wa.cbi_add_networks(iface)

t = s:option(Value, "target", translate("IP Address") )
t.datatype = "ip4addr"
t.rmempty = false

n = s:option(Value, "netmask", translate("Subnet Mask"))
n.placeholder = "255.255.255.255"
n.datatype = "ip4addr"
n.rmempty = true

g = s:option(Value, "gateway", translate("Gateway"))
g.datatype = "ip4addr"
g.rmempty = true

metric = s:option(Value, "metric", translate("Metric"))
metric.placeholder = 0
metric.datatype = "range(0,255)"
metric.rmempty = true

mtu = s:option(Value, "mtu", translate("MTU"))
mtu.placeholder = 1500
mtu.datatype = "range(64,9000)"
mtu.rmempty = true


return m

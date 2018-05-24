-- Copyright 2008 Steven Barth <steven@midlink.org>
-- Copyright 2010-2011 Jo-Philipp Wich <jow@openwrt.org>
-- Licensed to the public under the Apache License 2.0.

m = Map("ethernet", translate("Ethernet Settings"), translate("Ethernet Speed and Duplex Configuartion"))
    s = m:section(TypedSection, "ethernet")
            s.addremove = false
            s.anonymous = true

        p = s:option(ListValue, "mode", "Ethernet Speed") -- Creates an element list (select box)
        p:value("0", "Auto Negotiation") -- Key and value pairs
        p:value("1", "10Mbps-Half")
        p:value("2", "10Mbps-Full")
        p:value("3", "100Mbps-Half")
        p:value("4", "100Mbps-Full")
        p:value("5", "1000Mbps-Full")
        p.default = "0"

function m.on_commit(map)
    luci.util.exec("/etc/init.d/KWethernet start")
    end

return m

module("luci.controller.admin.monitor", package.seeall)

function index()
    entry({"admin", "monitor"}, alias("admin", "monitor", "arptbl"), _("Monitor"), 60).index = true
    local mode = luci.sys.exec("uci get wireless.@wifi-iface[1].mode")
    local wds = luci.sys.exec("uci get wireless.@wifi-iface[1].wds")
    local page
    if (string.match(mode,"ap") and string.match(wds,"1") ) then
	entry({"admin", "monitor", "sascan"}, call("action_sascan"), _("Spectrum Analyzer"), 1).leaf = true
	entry({"admin", "monitor", "saresult"}, call("action_saresult"))
    end
    entry({"admin", "monitor", "arptbl"}, call("action_arptbl"), _("ARP"), 2).leaf = true
    entry({"admin", "monitor", "clr_arptbl"}, call("action_clr_arptbl"))
    entry({"admin", "monitor", "wifi0stats"}, call("action_wifi0stats"), _("Wifi0 Statistics"), 3).leaf = true
    entry({"admin", "monitor", "wifi1stats"}, call("action_wifi1stats"), _("Wifi1 Statistics"), 4).leaf = true
    page = entry({"admin", "monitor", "log_type"}, call("action_logtype"), nil)
    page.leaf = true
    entry({"admin", "monitor", "ethstats"}, call("action_ethstats"), _("Ethernet Statistics"), 5).leaf = true
    entry({"admin", "monitor", "learntbl"}, call("action_learntbl"), _("Bridge"), 6).leaf = true
    entry({"admin", "monitor", "clr_learntbl"}, call("action_clr_learntbl"))
end

function action_sascan()
	local saresult = luci.sys.exec("wifitool ath1 acsreport")
	luci.template.render("admin_monitor/sascan", {saresult=saresult})
end

function action_logtype( logtype )
	local data = {}
	if( string.match(logtype,"1") ) then
		data = luci.util.exec("ifconfig wifi1")
	end
	if( string.match(logtype,"3") ) then
		if string.len(string.sub(luci.util.exec("cat /tmp/wifi_packet_logs"),1,-2) ) > 20 then
			data = luci.util.exec("cat /tmp/wifi_packet_logs")
		else
			data = "Wireless Log file is empty."
		end
	end
	if( string.match(logtype,"5") ) then
		data = luci.util.exec("athstats -i wifi1")
	end
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_saresult()
	luci.sys.exec("wifitool ath1 setchanlist 0")
	luci.sys.exec("iwpriv ath1 acsreport 1")
	luci.sys.exec("sleep 30")
	local saresult = luci.sys.exec("wifitool ath1 acsreport")
	luci.template.render("admin_monitor/sascan", {saresult=saresult})
end

function action_learntbl()
    local learntbl = luci.util.exec("brctl showmacs br-lan")
	luci.template.render("admin_monitor/learntbl", {learntbl=learntbl})
end

function action_clr_learntbl()
    luci.util.exec("brctl clearmacs br-lan")
    luci.util.exec("sleep 1")
    local learntbl = luci.util.exec("brctl showmacs br-lan")
	luci.template.render("admin_monitor/learntbl", {learntbl=learntbl})
end


function action_arptbl()
--    local arptbl = luci.util.exec("arp")
--     local arptbl = luci.sys.net.arptable()
    local arptbl = luci.util.exec("cat /proc/net/arp")
	luci.template.render("admin_monitor/arptbl", {arptbl=arptbl})
end


function action_clr_arptbl()
    luci.util.exec("ip -s neigh flush all")
    luci.util.exec("sleep 1")
    local arptbl = luci.util.exec("cat /proc/net/arp")
	luci.template.render("admin_monitor/arptbl", {arptbl=arptbl})
end

function action_wifi0stats()
    local wifi0stats = luci.util.exec("athstats -i wifi0")
	luci.template.render("admin_monitor/wifi0_stats", {wifi0stats=wifi0stats})
end

function action_wifi1stats()
	local wifi1stats = luci.util.exec("ifconfig wifi1")
	luci.template.render("admin_monitor/wifi1_stats", {wifi1stats=wifi1stats})
end

function action_ethstats()
    local ethstats = luci.util.exec("ethtool eth0 | grep Speed ; ethtool eth0 | grep Duplex ; ifconfig eth0 | sed 's/eth0/    /'")
	luci.template.render("admin_monitor/eth_stats", {ethstats=ethstats})
end


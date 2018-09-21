module("luci.controller.admin.monitor", package.seeall)

function index()
    entry({"admin", "monitor"}, alias("admin", "monitor", "arptbl"), _("Monitor"), 60).index = true
    local mode = luci.sys.exec("uci get wireless.@wifi-iface[1].mode")
    local wds = luci.sys.exec("uci get wireless.@wifi-iface[1].wds")
    local page
    
    entry({"admin", "monitor", "nwkstats"}, template("admin_monitor/wireless1_stats"), _("Network Statistics"), 1)
    entry({"admin", "monitor", "nwkstats", "wifi1refresh"}, call("action_wireless1"), nil).leaf = true
    entry({"admin", "monitor", "nwkstats", "radio2nwkstats"}, template("admin_monitor/wireless2_stats"))
    entry({"admin", "monitor", "nwkstats", "wifi2refresh"}, call("action_wireless2"), nil).leaf = true
    entry({"admin", "monitor", "nwkstats", "ethnwkstats"}, template("admin_monitor/ethernet_stats"))
    entry({"admin", "monitor", "nwkstats", "ethrefresh"}, call("action_ethernet"), nil).leaf = true
    entry({"admin", "monitor", "nwkstats", "arptbl"}, call("action_arptbl"))
    entry({"admin", "monitor", "nwkstats", "clr_arptbl"}, call("action_clr_arptbl"))
    entry({"admin", "monitor", "nwkstats", "learntbl"}, call("action_learntbl"))
    entry({"admin", "monitor", "nwkstats", "clr_learntbl"}, call("action_clr_learntbl"))
    entry({"admin", "monitor", "nwkstats", "dhcplease"}, template("admin_monitor/dhcplease"))

	entry({"admin", "monitor", "stats"}, template("admin_monitor/radio1_stats"), _("Link Statistics"), 2)
	entry({"admin", "monitor", "stats", "radio2stats"}, template("admin_monitor/radio2_stats"))
	entry({"admin", "monitor", "stats", "details"}, call("details"), nil).leaf = true
	entry({"admin", "monitor", "stats", "disconnect"}, call("disconnect"), nil).leaf = true
	entry({"admin", "monitor", "stats", "starttool"}, call("starttool"), nil).leaf = true
	entry({"admin", "monitor", "stats", "stoptool"}, call("stoptool"), nil).leaf = true

	entry({"admin", "monitor", "syslog"}, call("action_syslog"), _("Logs"), 3)
    entry({"admin", "monitor", "log_type"}, call("action_logtype"), nil).leaf = true
	entry({"admin", "monitor", "clr_log"}, call("action_clr_log"), nil).leaf = true

	entry({"admin", "monitor", "tools"}, template("admin_network/diagnostics"), _("Tools"), 4)
    if (string.match(mode,"ap") and string.match(wds,"1") ) then
	    entry({"admin", "monitor", "tools", "sascan"}, call("action_sascan"))
	    entry({"admin", "monitor", "tools", "saresult"}, call("action_saresult"))
    end
    if (string.match(mode,"sta") and string.match(wds,"1") ) then
	    entry({"admin", "monitor", "tools", "survey"}, call("action_survey"))
	    entry({"admin", "monitor", "tools", "surveyrefresh"}, call("action_surveyrefresh"), nil).leaf = true
	    entry({"admin", "monitor", "tools", "surveyclear"}, call("action_surveyclear"), nil).leaf = true
    end

    --entry({"admin", "monitor", "wifi0stats"}, call("action_wifi0stats"), _("Wifi0 Statistics"), 3).leaf = true
    --entry({"admin", "monitor", "wifi1stats"}, call("action_wifi1stats"), _("Wifi1 Statistics"), 4).leaf = true
    --page = entry({"admin", "monitor", "wifi_log_type"}, call("action_wifi_logtype"), nil)
    --page.leaf = true
    --entry({"admin", "monitor", "ethstats"}, call("action_ethstats"), _("Ethernet Statistics"), 5).leaf = true
    --page = entry({"admin", "monitor", "eth_log_type"}, call("action_eth_logtype"), nil)
    --page.leaf = true
--	entry({"admin", "monitor", "dmesg"}, call("action_dmesg"), _("Kernel Log"), 8)
--    entry({"admin", "monitor", "conflog"}, call("action_conflog"), _("Configuration Log"), 9)
--	entry({"admin", "monitor", "templog"}, call("action_templog"), _("Temperature Log"), 10)
end

function details( index )
	local entryind = index
	luci.template.render("admin_monitor/detailed_stats", {entryind=entryind})
end

function disconnect( mac )
	luci.sys.exec("iwpriv ath1 kickmac "..mac)
	luci.http.redirect(luci.dispatcher.build_url("admin/monitor/stats"))
end

function starttool( mac )
	local data = {}
	luci.sys.exec("uci set tool.tool.mac="..mac)
	luci.sys.exec("/etc/init.d/KWtool start")
	luci.sys.exec("iwpriv ath1 kwn_tput_test 1")
	data = "Link test is in progress..."
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function stoptool( mac )
	local data = {}
	luci.sys.exec("iwpriv ath1 kwn_tput_test 0")
	data = "Link test is stopped..."
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_sascan()
	local saresult = luci.sys.exec("wifitool ath1 acsreport")
	luci.template.render("admin_monitor/sascan", {saresult=saresult})
end

function action_survey()
	local surveyresult = luci.sys.exec("iwlist ath1 ap")
	luci.template.render("admin_monitor/survey", {surveyresult=surveyresult})
end

function action_surveyrefresh()
	local data = luci.sys.exec("iwlist ath1 ap")
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_surveyclear()
    local data = {}
    luci.sys.exec("iwpriv ath1 kwn_pbb_flag 1")
    luci.sys.exec("iwpriv ath1 s_scan_flush 1")
    luci.sys.exec("iwpriv ath1 kwn_pbb_flag 0")
	data = luci.sys.exec("iwlist ath1 ap")
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_wifi_logtype( logtype )
	local data = {}
	if( string.match(logtype,"1") ) then
		data = luci.util.exec("/usr/sbin/sify_linkstatistics 1")
	end
	if( string.match(logtype,"2") ) then
		data = luci.util.exec("/usr/sbin/sify_linkstatistics 4")
	end
	if( string.match(logtype,"3") ) then
		if string.len(string.sub(luci.util.exec("cat /tmp/wifi_packet_logs"),1,-2) ) > 20 then
			data = luci.util.exec("cat /tmp/wifi_packet_logs")
		else
			data = "Wireless Log file is empty."
		end
	end
	if( string.match(logtype,"4") ) then
		if string.len(string.sub(luci.util.exec("cat /etc/log/wifi_packet_logs"),1,-2) ) > 20 then
			data = luci.util.exec("cat /etc/log/wifi_packet_logs")
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

function action_eth_logtype( logtype )
	local data = {}
	if( string.match(logtype,"1") ) then
		data = luci.util.exec("/usr/sbin/sify_linkstatistics 1")
	end
	if( string.match(logtype,"2") ) then
		data = luci.util.exec("/usr/sbin/sify_linkstatistics 4")
	end
	if( string.match(logtype,"3") ) then
		if string.len(string.sub(luci.util.exec("cat /tmp/eth_events.txt"),1,-2) ) > 20 then
			data = luci.util.exec("cat /tmp/eth_events.txt")
		else
			data = "Ethernet Log file is empty."
		end
	end
	if( string.match(logtype,"4") ) then
		if string.len(string.sub(luci.util.exec("cat /etc/log/eth_events.txt"),1,-2) ) > 20 then
			data = luci.util.exec("cat /etc/log/eth_events.txt")
		else
			data = "Ethernet Log file is empty."
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

function action_wireless1()
    luci.util.exec("echo '' > /tmp/stats5_output")
    luci.util.exec("/usr/sbin/stats 1")
    local res = luci.util.exec("cat /tmp/stats5_output")
    data = string.gsub(res, "\n", "")
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_wireless2()
    luci.util.exec("echo '' > /tmp/stats24_output")
    luci.util.exec("/usr/sbin/stats 2")
    local res = luci.util.exec("cat /tmp/stats24_output")
    data = string.gsub(res, "\n", "")
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_ethernet()
    local res = luci.util.exec("iwpriv ath1 g_kwn_ethtxpkt | sed 's/ath1      g_kwn_ethtxpkt://'")
    local txpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwn_ethtxbyt | sed 's/ath1      g_kwn_ethtxbyt://'")
    local txbyte = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwn_ethtxerr | sed 's/ath1      g_kwn_ethtxerr://'")
    local txerr = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwn_ethrxpkt | sed 's/ath1      g_kwn_ethrxpkt://'")
    local rxpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwn_ethrxbyt | sed 's/ath1      g_kwn_ethrxbyt://'")
    local rxbyte = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwn_ethrxerr | sed 's/ath1      g_kwn_ethrxerr://'")
    local rxerr = string.gsub(res, "\n", "")
    local data = txpkt..","..txbyte..","..txerr..","..rxpkt..","..rxbyte..","..rxerr
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
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
	local wifi1stats = luci.util.exec("/usr/sbin/sify_linkstatistics 1")
	luci.template.render("admin_monitor/wifi1_stats", {wifi1stats=wifi1stats})
end

function action_ethstats()
    local ethstats = luci.util.exec("ethtool eth0 | grep Speed ; ethtool eth0 | grep Duplex ; ifconfig eth0 | sed 's/eth0/    /'")
	luci.template.render("admin_monitor/eth_stats", {ethstats=ethstats})
end

function action_logtype( logtype )
	local data = {}
	data = "Invalid Logtype"
    -- Syslog
	if( string.match(logtype,"1") ) then
		data = luci.sys.syslog()
	end
    -- Kernel log
	if( string.match(logtype,"2") ) then
		data = luci.sys.dmesg()
	end
    -- Temperature Log
	if( string.match(logtype,"3") ) then
        if string.len(string.sub(luci.util.exec("cat /tmp/temp-log"),1,-2) ) > 5 then
            data = luci.sys.exec("cat /tmp/temp-log")
        else
            data = "Temperature Log file is empty."
        end
	end
    -- Config Log
	if( string.match(logtype,"4") ) then
		data = luci.sys.exec("cat /etc/uci_delta")
	end
    -- Wireless Events
	if( string.match(logtype,"5") ) then
        if string.len(string.sub(luci.util.exec("cat /etc/wifi_packet_logs"),1,-2) ) > 5 then
            data = luci.sys.exec("cat /etc/wifi_packet_logs")
        else
            data = "Wireless Log file is empty."
        end
	end
    -- Ethernet Events
	if( string.match(logtype,"6") ) then
        if string.len(string.sub(luci.util.exec("cat /etc/eth_events.txt"),1,-2) ) > 5 then
            data = luci.sys.exec("cat /etc/eth_events.txt")
        else
            data = "Ethernet Log file is empty."
        end
	end
    -- Reboot Log
	if( string.match(logtype,"7") ) then
        if string.len(string.sub(luci.util.exec("cat /etc/reboot_logs"),1,-2) ) > 20 then
            data = luci.sys.exec("cat /etc/reboot_logs")
        else
            data = "Reboot Log file is empty."
        end
	end
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_conflog()
	local conflog = luci.sys.exec("cat /etc/uci_delta")
	luci.template.render("admin_monitor/conflog", {conflog=conflog})
end

function action_syslog()
	local syslog = luci.sys.syslog()
	luci.template.render("admin_monitor/syslog", {syslog=syslog})
end

function action_dmesg()
	local dmesg = luci.sys.dmesg()
	luci.template.render("admin_monitor/dmesg", {dmesg=dmesg})
end

function action_templog()
	local templog = luci.sys.exec("cat /tmp/temp-log")
	luci.template.render("admin_monitor/templog", {templog=templog})
end

function action_clr_log( logtype )
	local data = {}

	if( string.match(logtype,"3") ) then
        luci.sys.exec("rm -rf /tmp/temp-log")
	    data = "Temperature Log is cleared"
    end
	if( string.match(logtype,"5") ) then
        luci.sys.exec("rm -rf /etc/wifi_packet_logs")
	    data = "Wireless Events are cleared"
    end
	if( string.match(logtype,"6") ) then
        luci.sys.exec("rm -rf /etc/eth_events.txt")
	    data = "Ethernet Events are cleared"
    end
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end


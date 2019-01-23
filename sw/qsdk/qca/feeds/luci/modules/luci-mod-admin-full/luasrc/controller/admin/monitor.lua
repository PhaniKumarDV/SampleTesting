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
	entry({"admin", "monitor", "nwkstats", "clrethstats"}, call("clrethstats"), nil).leaf = true
	entry({"admin", "monitor", "nwkstats", "clrwifi1stats"}, call("clrwifi1stats"), nil).leaf = true
	entry({"admin", "monitor", "nwkstats", "clrwifi0stats"}, call("clrwifi0stats"), nil).leaf = true

	entry({"admin", "monitor", "stats"}, template("admin_monitor/radio1_stats"), _("Link Statistics"), 2)
	entry({"admin", "monitor", "stats", "radio2stats"}, template("admin_monitor/radio2_stats"))
	entry({"admin", "monitor", "stats", "details"}, call("details"), nil).leaf = true
	entry({"admin", "monitor", "stats", "disconnect"}, call("disconnect"), nil).leaf = true
	entry({"admin", "monitor", "stats", "starttool"}, call("starttool"), nil).leaf = true
	entry({"admin", "monitor", "stats", "stoptool"}, call("stoptool"), nil).leaf = true

	entry({"admin", "monitor", "logs"}, call("action_wifilog"), _("Logs"), 3) 
    entry({"admin", "monitor", "logs", "wireless_logtype"}, call("action_wifi_logtype"), nil).leaf = true
	entry({"admin", "monitor", "logs", "wireless_clrlog"}, call("action_wifi_clrlog"), nil).leaf = true
    entry({"admin", "monitor", "logs", "eth_log"}, call("action_ethlog"))
    entry({"admin", "monitor", "logs", "eth_logtype"}, call("action_eth_logtype"), nil).leaf = true
	entry({"admin", "monitor", "logs", "eth_clrlog"}, call("action_eth_clrlog"), nil).leaf = true
	entry({"admin", "monitor", "logs", "syslog"}, call("action_syslog"))
    entry({"admin", "monitor", "logs", "log_type"}, call("action_logtype"), nil).leaf = true
	entry({"admin", "monitor", "logs", "clr_log"}, call("action_clr_log"), nil).leaf = true

	entry({"admin", "monitor", "traffic"}, alias("admin", "monitor", "traffic", "connections"), _("Live Traffic"), 4)
	entry({"admin", "monitor", "traffic", "connections"}, template("admin_monitor/connections"), _("Connections"), 1).leaf = true
	entry({"admin", "monitor", "traffic", "connections_status"}, call("action_connections")).leaf = true
	entry({"admin", "monitor", "traffic", "bandwidth"}, template("admin_monitor/bandwidth"), _("Traffic"), 2).leaf = true
	entry({"admin", "monitor", "traffic", "bandwidth_status"}, call("action_bandwidth")).leaf = true
	entry({"admin", "monitor", "nameinfo"}, call("action_nameinfo")).leaf = true
	
	entry({"admin", "monitor", "tools"}, template("admin_network/diagnostics"), _("Tools"), 5)
    if (string.match(mode,"ap") and string.match(wds,"1") ) then
	    entry({"admin", "monitor", "tools", "sascan"}, call("action_sascan"))
	    entry({"admin", "monitor", "tools", "scantime"}, call("action_scantime"), nil).leaf = true
	    entry({"admin", "monitor", "tools", "startfreq"}, call("action_startfreq"), nil).leaf = true
	    entry({"admin", "monitor", "tools", "endfreq"}, call("action_endfreq"), nil).leaf = true
	    entry({"admin", "monitor", "tools", "stopscan"}, call("action_stopscan"), nil).leaf = true
	    entry({"admin", "monitor", "tools", "saresult"}, call("action_saresult"), nil).leaf = true
	    entry({"admin", "monitor", "tools", "scanstate"}, call("action_scanstate"), nil).leaf = true
    end
    if (string.match(mode,"sta") and string.match(wds,"1") ) then
	    entry({"admin", "monitor", "tools", "survey"}, call("action_survey"))
	    entry({"admin", "monitor", "tools", "surveyrefresh"}, call("action_surveyrefresh"), nil).leaf = true
	    entry({"admin", "monitor", "tools", "surveyclear"}, call("action_surveyclear"), nil).leaf = true
    end
	entry({"admin", "monitor", "tools", "linkcalc"}, template("admin_monitor/linkcalc"))
	entry({"admin", "monitor", "tools", "ethtest"}, template("admin_monitor/ethtest"))
	entry({"admin", "monitor", "tools", "ethtestsize"}, call("action_ethtestsize"), nil).leaf = true
	entry({"admin", "monitor", "tools", "ethtestdir"}, call("action_ethtestdir"), nil).leaf = true
	entry({"admin", "monitor", "tools", "ethtestdur"}, call("action_ethtestdur"), nil).leaf = true
	entry({"admin", "monitor", "tools", "ethtestmac"}, call("action_ethtestmac"), nil).leaf = true
	entry({"admin", "monitor", "tools", "ethteststart"}, call("action_ethteststart"), nil).leaf = true
	entry({"admin", "monitor", "tools", "ethteststop"}, call("action_ethteststop"), nil).leaf = true

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

function action_stopscan()
   luci.sys.exec("iwpriv ath1 kwnstartscan 0")
end

function action_scantime( time )
   luci.sys.exec("iwpriv ath1 kwnsatime "..time)
   luci.sys.exec("iwpriv ath1 kwnutiltime 500")
   luci.sys.exec("iwpriv ath1 kwnstartscan 1")
end

function action_startfreq( freq )
   luci.sys.exec("iwpriv ath1 kwnstartfreq "..freq)
end

function action_endfreq( freq )
   luci.sys.exec("iwpriv ath1 kwnendfreq "..freq)
end

function action_sascan()
	local saresult = {}
    luci.sys.exec("iwpriv ath1 kwn_flag 6")
    saresult = luci.sys.exec("apstats -c")
    luci.sys.exec("iwpriv ath1 kwn_flag 0")
	luci.template.render("admin_monitor/sascan", {saresult=saresult})
end

function action_ethtestsize( size )
   luci.sys.exec("iwpriv ath1 kwn_tput_size "..size)
end

function action_ethtestdir( dir )
   luci.sys.exec("iwpriv ath1 kwn_tput_dir "..dir)
end

function action_ethtestdur( dur )
   luci.sys.exec("iwpriv ath1 kwn_tput_dur "..dur)
end

function action_ethtestmac( mac )
   luci.sys.exec("iwpriv ath1 kwn_flag 1")
   luci.sys.exec("iwpriv ath1 addmac "..mac)
end

function action_ethteststart( speed )
   luci.sys.exec("iwpriv ath1 kwn_tput_cnt "..speed)
   luci.sys.exec("iwpriv ath1 kwnethtest 1")
end

function action_ethteststop( speed )
   luci.sys.exec("iwpriv ath1 kwnethtest 0")
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
    luci.sys.exec("iwpriv ath1 kwn_flag 4")
    luci.sys.exec("iwpriv ath1 s_scan_flush 1")
	data = luci.sys.exec("iwlist ath1 ap")
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_wifi_logtype( logtype )
	local data = {}
	data = "Invalid Logtype"
	if( string.match(logtype,"1") ) then
		data = luci.util.exec("/usr/sbin/sify_linkstatistics 1")
	end
	if( string.match(logtype,"2") ) then
		data = luci.util.exec("/usr/sbin/sify_linkstatistics 4")
    end
	if( string.match(logtype,"3") ) then
		data = luci.util.exec("/usr/sbin/sify_linkstatistics 5")
	end
	if( string.match(logtype,"4") ) then
		if string.len(string.sub(luci.util.exec("cat /tmp/wifi_packet_logs"),1,-2) ) > 20 then
			data = luci.util.exec("cat /tmp/wifi_packet_logs")
		else
			data = "Wireless Log file is empty."
		end
	end
	if( string.match(logtype,"5") ) then
		if string.len(string.sub(luci.util.exec("cat /etc/log/wifi_packet_logs"),1,-2) ) > 20 then
			data = luci.util.exec("cat /etc/log/wifi_packet_logs")
		else
			data = "Wireless Log file is empty."
		end
	end
	if( string.match(logtype,"6") ) then
        luci.util.exec("echo '' > /tmp/stats5_output")
        luci.util.exec("/usr/sbin/stats 1")
        local res = luci.util.exec("cat /tmp/stats5_output")
        data = string.gsub(res, "\n", "")
	end
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_wifi_clrlog( logtype )
	local data = {}
	data = "Wireless Log file is empty."
	if( string.match(logtype,"6") ) then
	    luci.sys.exec("athstatsclr -i wifi1")
	    luci.sys.exec("80211stats -i ath1 -e 1")
        luci.util.exec("echo '' > /tmp/stats5_output")
        luci.util.exec("/usr/sbin/stats 1")
        local res = luci.util.exec("cat /tmp/stats5_output")
        data = string.gsub(res, "\n", "")
    end
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function adv_eth_stats()
    local res = luci.util.exec("iwpriv ath1 g_kwn_ethtxpkt | sed 's/ath1      g_kwn_ethtxpkt://'")
    local txpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwn_ethrxpkt | sed 's/ath1      g_kwn_ethrxpkt://'")
    local rxpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwnethtxfail | sed 's/ath1      g_kwnethtxfail://'")
    local txfail = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwnethrxfail | sed 's/ath1      g_kwnethrxfail://'")
    local rxfail = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwethcrcerrs | sed 's/ath1      g_kwethcrcerrs://'")
    local rxcrcerr = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwethoversize | sed 's/ath1      g_kwethoversize://'")
    local rxovrsize = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwethoverrun | sed 's/ath1      g_kwethoverrun://'")
    local rxovrrun = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwnethtxmcpkt | sed 's/ath1      g_kwnethtxmcpkt://'")
    local txmcpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwnethrxmcpkt | sed 's/ath1      g_kwnethrxmcpkt://'")
    local rxmcpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwnethtxucpkt | sed 's/ath1      g_kwnethtxucpkt://'")
    local txucpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwnethrxucpkt | sed 's/ath1      g_kwnethrxucpkt://'")
    local rxucpkt = string.gsub(res, "\n", "")
    local data = txpkt..","..rxpkt..","..txfail..","..rxfail..","..rxcrcerr..","..rxovrsize..","..rxovrrun
    data = data..","..txmcpkt..","..rxmcpkt..","..txucpkt..","..rxucpkt
    return data
end

function action_eth_logtype( logtype )
	local data = {}
	data = "Invalid Logtype"
	if( string.match(logtype,"1") ) then
		data = luci.util.exec("/usr/sbin/sify_linkstatistics 3")
	end
	if( string.match(logtype,"2") ) then
		data = luci.util.exec("/usr/sbin/sify_linkstatistics 6")
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
        data = adv_eth_stats()
	end
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_eth_clrlog( logtype )
	local data = {}
	data = "Ethernet Log file is empty."
	if( string.match(logtype,"5") ) then
	    luci.sys.exec("iwpriv ath1 kwnclrethstats 1")
        data = adv_eth_stats()
    end
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_scanstate()
    local data = luci.util.exec("iwpriv ath1 g_kwnstartscan | sed 's/ath1      g_kwnstartscan://'")
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_saresult()
	local data = {}
    luci.sys.exec("iwpriv ath1 kwn_flag 6")
    data = luci.sys.exec("apstats -c")
    luci.sys.exec("iwpriv ath1 kwn_flag 0")
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
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
    res = luci.util.exec("iwpriv ath1 g_kwtxl2mdrpcnt | sed 's/ath1      g_kwtxl2mdrpcnt://'")
    local txl2mpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwrxl2mdrpcnt | sed 's/ath1      g_kwrxl2mdrpcnt://'")
    local rxl2mpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwtxl3mdrpcnt | sed 's/ath1      g_kwtxl3mdrpcnt://'")
    local txl3mpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwrxl3mdrpcnt | sed 's/ath1      g_kwrxl3mdrpcnt://'")
    local rxl3mpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwtxl2bdrpcnt | sed 's/ath1      g_kwtxl2bdrpcnt://'")
    local txl2bpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwrxl2bdrpcnt | sed 's/ath1      g_kwrxl2bdrpcnt://'")
    local rxl2bpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwtxl3bdrpcnt | sed 's/ath1      g_kwtxl3bdrpcnt://'")
    local txl3bpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwrxl3bdrpcnt | sed 's/ath1      g_kwrxl3bdrpcnt://'")
    local rxl3bpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwnethtxfail | sed 's/ath1      g_kwnethtxfail://'")
    local txfail = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwnethrxfail | sed 's/ath1      g_kwnethrxfail://'")
    local rxfail = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwnethtxmcpkt | sed 's/ath1      g_kwnethtxmcpkt://'")
    local txmcpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwnethrxmcpkt | sed 's/ath1      g_kwnethrxmcpkt://'")
    local rxmcpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwnethtxucpkt | sed 's/ath1      g_kwnethtxucpkt://'")
    local txucpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwnethrxucpkt | sed 's/ath1      g_kwnethrxucpkt://'")
    local rxucpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwethcrcerrs | sed 's/ath1      g_kwethcrcerrs://'")
    local rxcrcerr = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwethoversize | sed 's/ath1      g_kwethoversize://'")
    local rxovrsize = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwethoverrun | sed 's/ath1      g_kwethoverrun://'")
    local rxovrrun = string.gsub(res, "\n", "")
    local data = txpkt..","..txbyte..","..txerr..","..rxpkt..","..rxbyte..","..rxerr..","..txl2mpkt..","..rxl2mpkt
    data = data..","..txl3mpkt..","..rxl3mpkt..","..txl2bpkt..","..rxl2bpkt..","..txl3bpkt..","..rxl3bpkt
    data = data..","..txfail..","..rxfail..","..txmcpkt..","..rxmcpkt..","..txucpkt..","..rxucpkt..","..rxcrcerr..","..rxovrsize..","..rxovrrun
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
        if string.len(string.sub(luci.util.exec("cat /etc/uci_delta"),1,-2) ) > 5 then
		    data = luci.sys.exec("cat /etc/uci_delta")
        else
            data = "Configuration Log file is empty."
        end
	end
    -- Reboot Log
	if( string.match(logtype,"5") ) then
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

function action_wifilog()
    local data = {}
    data = luci.util.exec("/usr/sbin/sify_linkstatistics 1")
	local wireless_log = data
	luci.template.render("admin_monitor/wireless_log", {wireless_log=wireless_log})
end

function action_ethlog()
    local data = {}
    data = luci.util.exec("/usr/sbin/sify_linkstatistics 3")
	local eth_log = data
	luci.template.render("admin_monitor/eth_log", {eth_log=eth_log})
end

function action_syslog()
    local data = {}
    data = luci.sys.syslog()
	local syslog = data
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
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function clrethstats()
	luci.sys.exec("iwpriv ath1 kwnclrethstats 1")
end

function clrwifi1stats()
	luci.sys.exec("athstatsclr -i wifi1")
	luci.sys.exec("80211stats -i ath1 -e 1")
end

function clrwifi0stats()
	luci.sys.exec("athstatsclr -i wifi0")
	luci.sys.exec("80211stats -i ath0 -e 1")
end

function action_bandwidth(iface)
	luci.http.prepare_content("application/json")

	local bwc = io.popen("luci-bwc -i %q 2>/dev/null" % iface)
	if bwc then
		luci.http.write("[")

		while true do
			local ln = bwc:read("*l")
			if not ln then break end
			luci.http.write(ln)
		end

		luci.http.write("]")
		bwc:close()
	end
end

function action_connections()
	local sys = require "luci.sys"

	luci.http.prepare_content("application/json")

	luci.http.write("{ connections: ")
	luci.http.write_json(sys.net.conntrack())

	local bwc = io.popen("luci-bwc -c 2>/dev/null")
	if bwc then
		luci.http.write(", statistics: [")

		while true do
			local ln = bwc:read("*l")
			if not ln then break end
			luci.http.write(ln)
		end

		luci.http.write("]")
		bwc:close()
	end

	luci.http.write(" }")
end

function action_nameinfo(...)
	local i
	local rv = { }
	for i = 1, select('#', ...) do
		local addr = select(i, ...)
		local fqdn = nixio.getnameinfo(addr)
		rv[addr] = fqdn or (addr:match(":") and "[%s]" % addr or addr)
	end

	luci.http.prepare_content("application/json")
	luci.http.write_json(rv)
end

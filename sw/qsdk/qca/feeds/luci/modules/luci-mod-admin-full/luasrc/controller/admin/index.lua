-- Copyright 2008 Steven Barth <steven@midlink.org>
-- Licensed to the public under the Apache License 2.0.

module("luci.controller.admin.index", package.seeall)

function index()
    local mode = luci.sys.exec("uci get wireless.@wifi-iface[1].mode")
    local wds = luci.sys.exec("uci get wireless.@wifi-iface[1].wds")
	local root = node()
	if not root.target then
		root.target = alias("admin")
		root.index = true
	end

	local page   = node("admin")
	page.target  = firstchild()
	page.title   = _("Administration")
	page.order   = 10
-- Raja    
	page.sysauth = { "admin", "superuser", "user", "installer", "root" }
	page.sysauth_authenticator = "htmlauth"
	page.ucidata = true
	page.index = true

	-- Empty services menu to be populated by addons
	-- entry({"admin", "services"}, firstchild(), _("Services"), 40).index = true

	entry({"admin", "home"}, call("action_index"), _("Home"), 10)
    entry({"admin", "eventlog"}, call("action_eventlog"), nil).leaf = true
    entry({"admin", "clr_eventlog"}, call("action_clr_eventlog"), nil).leaf = true
    entry({"admin", "get_descr"}, call("action_get_descr"), nil).leaf = true
    entry({"admin", "no_of_links"}, call("action_links"), nil).leaf = true
    entry({"admin", "sumode"}, call("action_sumode"), nil).leaf = true
    entry({"admin", "stats"}, call("action_stats"), nil).leaf = true
    entry({"admin", "gps"}, call("action_gps"), nil).leaf = true
    entry({"admin", "autorefresh"}, call("action_auto_refresh"), nil).leaf = true
	entry({"admin", "apply"}, call("action_apply"), _("Apply"), 88)
	entry({"admin", "apply", "reload"}, call("action_reload"), nil).leaf = true
	entry({"admin", "reboot"}, call("action_reboot"), _("Reboot"), 89)
	entry({"admin", "logout"}, call("action_logout"), _("Logout"), 90)
	entry({"admin", "config"}, template("admin_status/system"), _("Quick Start"), 20)
	entry({"admin", "config", "location"}, template("admin_status/location"))
	entry({"admin", "config", "location", "satcount"}, call("action_satcount"), nil).leaf = true
    entry({"admin", "config", "config1"}, template("admin_status/basic_config1"))
    entry({"admin", "config", "config2"}, template("admin_status/basic_config2"))
    if (string.match(mode,"sta") and string.match(wds,"1") ) then
	    entry({"admin", "config", "survey"}, call("action_survey"))
	    entry({"admin", "config", "joinnetwork"}, call("action_join"),nil).leaf = true
	    entry({"admin", "config", "connect"}, call("action_connect"), nil).leaf = true
	    entry({"admin", "config", "surveyscan"}, call("action_surveyscan"), nil).leaf = true
	    entry({"admin", "config", "surveyrefresh"}, call("action_surveyrefresh"), nil).leaf = true
	    entry({"admin", "config", "surveyclear"}, call("action_surveyclear"), nil).leaf = true
    end
	entry({"admin", "config", "radio1stats"}, template("admin_status/radio1_stats"))
	entry({"admin", "config", "details"}, call("details"), nil).leaf = true
	entry({"admin", "config", "disconnect"}, call("disconnect"), nil).leaf = true
	entry({"admin", "config", "starttool"}, call("starttool"), nil).leaf = true
	entry({"admin", "config", "stoptool"}, call("stoptool"), nil).leaf = true
    page = entry({"admin", "cfg_set"}, call("action_cfg_set"), nil)
	page.leaf = true
end

function action_links()
	local data = {}
    local link1 = {}
    local link2 = {}

    local res = luci.sys.exec("wlanconfig ath1 list sta | wc -l")
    link1 = string.gsub(res, "\n", "")
    res = luci.sys.exec("wlanconfig ath0 list sta | wc -l")
    link2 = string.gsub(res, "\n", "")
    data = link1.."="..link2
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_sumode()
	local data = {}
    local mode1 = {}

    local res = luci.sys.exec("iwpriv ath1 get_mode | sed 's/ath1      get_mode://'")
    mode1 = string.gsub(res, "\n", "")
    data = mode1
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_gps()
	local data = {}
    local lat = luci.util.exec("uci get system.gps.latitude")
    local lon = luci.util.exec("uci get system.gps.longitude")
    data = lat.."="..lon
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_auto_refresh()
	local data = {}
    local cpu_use = luci.util.exec("/usr/sbin/cpu_usage.sh")
    local mem_use = luci.util.exec("/usr/sbin/mem_usage.sh")
    data = cpu_use.."="..mem_use
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_stats()
	local data = {}
    local res = luci.util.exec("iwpriv ath1 g_kwn_ethtxpkt | sed 's/ath1      g_kwn_ethtxpkt://'")
    local ethtxpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwn_ethrxpkt | sed 's/ath1      g_kwn_ethrxpkt://'")
    local ethrxpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("athstats -i wifi1 | grep tx: | sed 's/tx://'")
    local da1txpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("athstats -i wifi1 | grep rx: | sed 's/rx://'")
    local da1rxpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("athstats -i wifi1 | grep ast_tx_packets: | sed 's/ast_tx_packets://'")
    local mg1txpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("athstats -i wifi1 | grep ast_rx_packets: | sed 's/ast_rx_packets://'")
    local mg1rxpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("athstats -i wifi0 | grep tx: | sed 's/tx://'")
    local da2txpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("athstats -i wifi0 | grep rx: | sed 's/rx://'")
    local da2rxpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("athstats -i wifi0 | grep ast_tx_packets: | sed 's/ast_tx_packets://'")
    local mg2txpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("athstats -i wifi0 | grep ast_rx_packets: | sed 's/ast_rx_packets://'")
    local mg2rxpkt = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwn_ethtxthr | sed 's/ath1      g_kwn_ethtxthr://'")
    local ethtxthr = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwn_ethrxthr | sed 's/ath1      g_kwn_ethrxthr://'")
    local ethrxthr = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwn_witxthr | sed 's/ath1      g_kwn_witxthr://'")
    local wi1txthr = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwn_wirxthr | sed 's/ath1      g_kwn_wirxthr://'")
    local wi1rxthr = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath1 g_kwnrxfailcnt | sed 's/ath1      g_kwnrxfailcnt://'")
    local ethrxfail = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath0 g_kwn_witxthr | sed 's/ath0      g_kwn_witxthr://'")
    local wi0txthr = string.gsub(res, "\n", "")
    res = luci.util.exec("iwpriv ath0 g_kwn_wirxthr | sed 's/ath0      g_kwn_wirxthr://'")
    local wi0rxthr = string.gsub(res, "\n", "")
    local wi1txpkt = da1txpkt + mg1txpkt
    local wi1rxpkt = da1rxpkt + mg1rxpkt
    local wi2txpkt = da2txpkt + mg2txpkt
    local wi2rxpkt = da2rxpkt + mg2rxpkt

--           0               1              2              3              4              5              6              7             8               9              10             11             12
    data = ethtxpkt.."="..ethrxpkt.."="..wi1txpkt.."="..wi1rxpkt.."="..wi2txpkt.."="..wi2rxpkt.."="..ethtxthr.."="..ethrxthr.."="..wi1txthr.."="..wi1rxthr.."="..ethrxfail.."="..wi0txthr.."="..wi0rxthr
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_clr_eventlog()
	local data = {}

    luci.util.exec("rm -rf /etc/wifi_packet_logs")
    data = "Event Log is cleared."
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_eventlog()
	local data = {}

    if string.len(string.sub(luci.util.exec("cat /etc/wifi_packet_logs"),1,-2) ) > 20 then
        data = luci.util.exec("cat /etc/wifi_packet_logs")
    else
        data = "Event Log is empty."
    end
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_index()
    local eventlog = {}

    if string.len(string.sub(luci.util.exec("cat /etc/wifi_packet_logs"),1,-2) ) > 20 then
        eventlog = luci.util.exec("cat /etc/wifi_packet_logs")
    else
        eventlog = "Event Log is empty."
    end
	luci.template.render("admin_status/index", {eventlog=eventlog})
end

function action_cfg_set( setdata )
	local data = "1"
    local mode = luci.sys.exec("uci get wireless.@wifi-iface[1].mode")
    local loginuser = luci.dispatcher.context.authuser
    if ( loginuser == "user" or ( loginuser == "superuser" and mode == "ap" ) ) then
    else
       luci.util.exec("echo "..setdata.." > /tmp/setcfgfile.txt")
       luci.util.exec("cfgupdate")
    end
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_apply()
    local mode = luci.sys.exec("uci get wireless.@wifi-iface[1].mode")
    local uci = luci.model.uci.cursor()
    local changes = uci:changes()
    local loginuser = luci.dispatcher.context.authuser
    if ( loginuser == "user" or ( loginuser == "superuser" and mode == "ap" ) ) then
    else
	luci.template.render("admin_system/apply", {
        changes = next(changes) and changes
    })
    end
end

function action_reload()
    local mode = luci.sys.exec("uci get wireless.@wifi-iface[1].mode")
    local loginuser = luci.dispatcher.context.authuser
    if ( loginuser == "user" or ( loginuser == "superuser" and mode == "ap" ) ) then
    else
		luci.util.exec("uci commit")
		luci.util.exec("reload_config")
    end
end

function action_reboot()
	local reboot = luci.http.formvalue("reboot")
	luci.template.render("admin_system/reboot", {reboot=reboot})
	if reboot then
        luci.util.exec("/usr/sbin/sify_reboot_log.sh 1")
        luci.util.exec("sh /usr/sbin/kwnreboot.sh")
	end
end

function action_logout()
	local dsp = require "luci.dispatcher"
	local utl = require "luci.util"
	local sid = dsp.context.authsession

	if sid then
		utl.ubus("session", "destroy", { ubus_rpc_session = sid })

		dsp.context.urltoken.stok = nil

		luci.http.header("Set-Cookie", "sysauth=%s; expires=%s; path=%s/" %{
			sid, 'Thu, 01 Jan 1970 01:00:00 GMT', dsp.build_url()
		})
	end

	luci.http.redirect(luci.dispatcher.build_url())
end

function action_get_descr()
    local res =  luci.util.exec("fw_printenv -n model")
    local model_name = string.gsub(res, "\n", "")
    res = luci.util.exec("fw_printenv -n producttype")
    local product_type = string.gsub(res, "\n", "")
    local data

    data = model_name.."=".. product_type
    luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_satcount()
    local data = luci.util.exec("uci get system.gps.satelites")
    luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_survey()
	local surveyresult = luci.sys.exec("iwlist ath1 ap")
	luci.template.render("admin_status/survey", {surveyresult=surveyresult})
end

function action_join( ssid, enc )
    local loginuser = luci.dispatcher.context.authuser
    if ( loginuser ~= "superuser" and loginuser ~= "user" ) then
        luci.util.exec("uci set wireless.@wifi-iface[1].mode='sta'")
        luci.util.exec("uci set wireless.@wifi-iface[1].wds='1'")
        luci.util.exec("uci set wireless.wifi1.channel='auto'")
        luci.util.exec("uci set wireless.@wifi-iface[1].ssid='"..ssid.."'")
	    if( string.match(enc,"1") ) then
            luci.util.exec("uci set wireless.@wifi-iface[1].encryption='psk2+ccmp'")
        else
            luci.util.exec("uci set wireless.@wifi-iface[1].encryption='none'")
        end
	    luci.template.render("admin_status/joinnetwork")
    else
	    luci.http.redirect(luci.dispatcher.build_url("admin/config/survey"))
    end
end

function action_connect()
    luci.util.exec("uci commit")
    luci.util.exec("reload_config")
end

function action_surveyscan()
	local data = 1
    luci.sys.exec("sh /usr/sbin/sukickmac.sh")
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
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
    luci.sys.exec("iwpriv ath1 kwn_flag 0")
	data = luci.sys.exec("iwlist ath1 ap")
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function details( index )
	local entryind = index
	luci.template.render("admin_status/detailed_stats", {entryind=entryind})
end

function disconnect( mac )
	luci.sys.exec("iwpriv ath1 kickmac "..mac)
	luci.http.redirect(luci.dispatcher.build_url("admin/config/radio1stats"))
end

function starttool( mac )
	local data = {}
	luci.sys.exec("uci set tool.tool.mac="..mac)
	luci.sys.exec("/etc/init.d/KWtool start")
	luci.sys.exec("iwpriv ath1 kwn_tput_test 1")
	luci.sys.exec("uci commit tool")
	data = "Link test is in progress..."
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function stoptool( mac )
	local data = {}
	luci.sys.exec("iwpriv ath1 kwn_tput_test 0")
	luci.sys.exec("uci commit tool")
	data = "Link test is stopped..."
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

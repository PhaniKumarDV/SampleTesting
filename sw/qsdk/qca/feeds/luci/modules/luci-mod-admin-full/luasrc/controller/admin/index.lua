-- Copyright 2008 Steven Barth <steven@midlink.org>
-- Licensed to the public under the Apache License 2.0.

module("luci.controller.admin.index", package.seeall)

function index()
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
	page.sysauth = { "admin", "superuser", "user" }
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
    entry({"admin", "stats"}, call("action_stats"), nil).leaf = true
	entry({"admin", "apply"}, call("action_apply"), _("Apply"), 88)
	entry({"admin", "reboot"}, call("action_reboot"), _("Reboot"), 89)
	entry({"admin", "logout"}, call("action_logout"), _("Logout"), 90)
	entry({"admin", "config"}, template("admin_status/system"), _("Quick Start"), 20)
    entry({"admin", "config", "config1"}, template("admin_status/basic_config1"))
    entry({"admin", "config", "config2"}, template("admin_status/basic_config2"))
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
    local wi1txpkt = da1txpkt + mg1txpkt
    local wi1rxpkt = da1rxpkt + mg1rxpkt
    local wi2txpkt = da2txpkt + mg2txpkt
    local wi2rxpkt = da2rxpkt + mg2rxpkt

    data = ethtxpkt.."="..ethrxpkt.."="..wi1txpkt.."="..wi1rxpkt.."="..wi2txpkt.."="..wi2rxpkt.."="..ethtxthr.."="..ethrxthr.."="..wi1txthr.."="..wi1rxthr.."="..ethrxfail
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
    luci.util.exec("echo "..setdata.." > /tmp/setcfgfile.txt")
    luci.util.exec("cfgupdate")
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function action_apply()
	local apply = luci.http.formvalue("apply")
	luci.template.render("admin_system/apply", {apply=apply})
	if apply then
		luci.util.exec("uci commit")
		luci.util.exec("reload_config")
	end
end

function action_reboot()
	local reboot = luci.http.formvalue("reboot")
	luci.template.render("admin_system/reboot", {reboot=reboot})
	if reboot then
        luci.util.exec("/usr/sbin/sify_reboot_log.sh 1")
		luci.sys.reboot()
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

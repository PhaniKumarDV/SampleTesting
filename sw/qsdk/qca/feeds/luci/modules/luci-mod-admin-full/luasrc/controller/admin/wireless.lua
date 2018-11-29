module("luci.controller.admin.wireless", package.seeall)

function index()
	local uci = require("luci.model.uci").cursor()
	local page

	page = node("admin", "wireless")
	page.target = firstchild()
	page.title  = _("Wireless")
	page.order  = 30
	page.index  = true

	local has_wifi = false

	uci:foreach("wireless", "wifi-device",
		function(s)
			has_wifi = true
			return false
		end)

		entry({"admin", "wireless", "radio1"}, template("admin_wireless/radio_config1"), _("5GHz Radio"), 1)
		entry({"admin", "wireless", "radio1", "ddrs1"}, template("admin_wireless/ddrs1"))
		entry({"admin", "wireless", "radio1", "mimo1"}, template("admin_wireless/mimo1"))
		entry({"admin", "wireless", "radio1", "security1"}, template("admin_wireless/security1"))
		entry({"admin", "wireless", "radio1", "macacl1"}, template("admin_wireless/macacl1"))
		entry({"admin", "wireless", "radio1", "dcs1"}, template("admin_wireless/dcs1"))

		entry({"admin", "wireless", "radio2"}, template("admin_wireless/radio_config2"), _("2.4GHz Radio"), 2)
		entry({"admin", "wireless", "radio2", "security2"}, template("admin_wireless/security2"))
		entry({"admin", "wireless", "radio2", "macacl2"}, template("admin_wireless/macacl2"))

	if has_wifi then
		page = entry({"admin", "wireless", "wireless_join"}, call("wifi_join"), nil)
		page.leaf = true

		page = entry({"admin", "wireless", "wireless_add"}, call("wifi_add"), nil)
		page.leaf = true

		page = entry({"admin", "wireless", "wireless_delete"}, call("wifi_delete"), nil)
		page.leaf = true

		page = entry({"admin", "wireless", "wireless_status"}, call("wifi_status"), nil)
		page.leaf = true

		page = entry({"admin", "wireless", "wireless_reconnect"}, call("wifi_reconnect"), nil)
		page.leaf = true

		page = entry({"admin", "wireless", "wireless_shutdown"}, call("wifi_shutdown"), nil)
		page.leaf = true

		page = entry({"admin", "wireless", "details"}, call("details"), nil)
		page.leaf = true

		page = entry({"admin", "wireless", "disconnect"}, call("disconnect"), nil)
		page.leaf = true

		page = entry({"admin", "wireless", "starttool"}, call("starttool"), nil)
		page.leaf = true
		page = entry({"admin", "wireless", "stoptool"}, call("stoptool"), nil)
		page.leaf = true
		--page = entry({"admin", "wireless", "wireless"}, arcombine(template("admin_wireless/wifi_overview"), cbi("admin_wireless/wifi")), _("Overview"), 15)
		--page.leaf = true
		--page.subindex = true

		--local mode = luci.sys.exec("uci get wireless.@wifi-iface[1].mode")
		--local wds = luci.sys.exec("uci get wireless.@wifi-iface[1].wds")
		--if (string.match(mode,"ap") and string.match(wds,"1") ) then
		--	entry({"admin", "wireless", "radauth"}, cbi("admin_wireless/radauth"), _("RADIUS"), 16)
		--end
		--entry({"admin", "wireless", "tool"}, cbi("admin_wireless/tool"), _("Performance Tool"), 17)

		if page.inreq then
			local wdev
			local net = require "luci.model.network".init(uci)
			for _, wdev in ipairs(net:get_wifidevs()) do
				local wnet
				for _, wnet in ipairs(wdev:get_wifinets()) do
					entry(
						{"admin", "wireless", "wireless", wnet:id()},
						alias("admin", "wireless", "wireless"),
						wdev:name() .. ": " .. wnet:shortname()
					)
				end
			end
		end
	end

end

function details( index )
	local entryind = index
	luci.template.render("admin_wireless/detailed_stats", {entryind=entryind})
end

function disconnect( mac )
	luci.sys.exec("iwpriv ath1 kickmac "..mac)
	luci.http.redirect(luci.dispatcher.build_url("admin/wireless/wireless"))
end

function starttool( mac )
	local data = {}
	luci.sys.exec("uci set tool.tool.mac="..mac)
	luci.sys.exec("/etc/init.d/KWtool start")
	luci.sys.exec("iwpriv ath1 kwn_tput_test 1")
	data = "Performance test is in progress..."
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function stoptool( mac )
	local data = {}
	luci.sys.exec("iwpriv ath1 kwn_tput_test 0")
	data = "Performance test is stopped..."
	luci.http.prepare_content("application/json")
	luci.http.write_json(data)
end

function wifi_join()
	local function param(x)
		return luci.http.formvalue(x)
	end

	local function ptable(x)
		x = param(x)
		return x and (type(x) ~= "table" and { x } or x) or {}
	end

	local dev  = param("device")
	local ssid = param("join")

	if dev and ssid then
		local cancel  = (param("cancel") or param("cbi.cancel")) and true or false

		if cancel then
			luci.http.redirect(luci.dispatcher.build_url("admin/wireless/wireless_join?device=" .. dev))
		else
			local cbi = require "luci.cbi"
			local tpl = require "luci.template"
			local map = luci.cbi.load("admin_wireless/wifi_add")[1]

			if map:parse() ~= cbi.FORM_DONE then
				tpl.render("header")
				map:render()
				tpl.render("footer")
			end
		end
	else
		luci.template.render("admin_wireless/wifi_join")
	end
end

function wifi_add()
	local dev = luci.http.formvalue("device")
	local ntm = require "luci.model.network".init()

	dev = dev and ntm:get_wifidev(dev)

	if dev then
		local net = dev:add_wifinet({
			mode       = "ap",
			ssid       = "OpenWrt",
			encryption = "none"
		})

		ntm:save("wireless")
		luci.http.redirect(net:adminlink())
	end
end

function wifi_delete(network)
	local ntm = require "luci.model.network".init()
	local wnet = ntm:get_wifinet(network)
	if wnet then
		local dev = wnet:get_device()
		local nets = wnet:get_networks()
		if dev then
			ntm:del_wifinet(network)
			ntm:commit("wireless")
			local _, net
			for _, net in ipairs(nets) do
				if net:is_empty() then
					ntm:del_network(net:name())
					ntm:commit("network")
				end
			end
			luci.sys.call("env -i /bin/ubus call network reload >/dev/null 2>/dev/null")
		end
	end

	luci.http.redirect(luci.dispatcher.build_url("admin/wireless/wireless"))
end

function wifi_status(devs)
	local s    = require "luci.tools.status"
	local rv   = { }

	local dev
	for dev in devs:gmatch("[%w%.%-]+") do
		rv[#rv+1] = s.wifi_network(dev)
	end

	if #rv > 0 then
		luci.http.prepare_content("application/json")
		luci.http.write_json(rv)
		return
	end

	luci.http.status(404, "No such device")
end

local function wifi_reconnect_shutdown(shutdown, wnet)
	local netmd = require "luci.model.network".init()
	local net = netmd:get_wifinet(wnet)
	local dev = net:get_device()
	if dev and net then
		dev:set("disabled", nil)
		net:set("disabled", shutdown and 1 or nil)
		netmd:commit("wireless")

		luci.sys.exec("env -i /etc/init.d/network reload")
		luci.http.status(200, shutdown and "Shutdown" or "Reconnected")

		return
	end

	luci.http.status(404, "No such radio")
end

function wifi_reconnect(wnet)
	wifi_reconnect_shutdown(false, wnet)
end

function wifi_shutdown(wnet)
	wifi_reconnect_shutdown(true, wnet)
end



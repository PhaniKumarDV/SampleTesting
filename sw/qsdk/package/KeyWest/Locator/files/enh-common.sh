#!/bin/sh

route_for_locator() {
	local config="$1"
	local iface_main="$2"
	local iftype="$3"
	#for locator tool to process broadcast pkt
	[ "$config" = "lan" ] && {
		[ "$iftype" = "bridge" ] && {
			sleep 1 #wait for birdge ready
			route add -host 255.255.255.255 dev "br-$config"
			echo locator iface==== "br-$config" ====
		} || {
			route add -host 255.255.255.255 dev "$iface_main"
			echo locator iface==== "$iface_main" ====
		}
	}

}
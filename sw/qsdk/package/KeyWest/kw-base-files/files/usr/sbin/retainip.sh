#!/bin/sh/

brlanip=$(uci get network.lan.ipaddr)
maskip=$(uci get network.lan.netmask)
gateway=$(uci get network.lan.gateway)
addrtype=$(uci get network.lan.proto)
retainip=$(uci get tftp.retip.retainip)

if [ "$retainip" == "1" ]
then
    ( echo y ) | firstboot >/dev/null 2>&1
    echo "uci set network.lan.ipaddr=$brlanip" > /etc/retainip
    echo "uci set network.lan.netmask=$maskip" >> /etc/retainip
    echo "uci set network.lan.gateway=$gateway" >> /etc/retainip
    echo "uci set network.lan.proto=$addrtype" >> /etc/retainip
    reboot
else
    ( echo y ) | firstboot >/dev/null 2>&1
    reboot
fi

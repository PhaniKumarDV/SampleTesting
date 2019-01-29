
#!/bin/sh/
#
# To set Ethernet MTU

mtu=$(uci get network.lan.mtu)

brctl delif br-lan ath1
brctl delif br-lan eth0
brctl delif br-lan eth1

ifconfig ath1 mtu $mtu 
ssdk_sh misc frameMaxSize set mtu $mtu
ifconfig eth0 mtu $mtu 
ifconfig eth1 mtu $mtu

sleep 1
ifconfig br-lan down

brctl addif br-lan ath1
brctl addif br-lan eth0
brctl addif br-lan eth1
ifconfig eth0 up
ifconfig eth1 up
ifconfig br-lan up

sleep 1
assemfrag=0
if [ "$mtu" -gt 1500 ]
then
    assemfrag=1
fi
iwpriv ath1 kwnassemfrag "$assemfrag"
iwpriv ath1 kwnpktsize 1560
iwpriv ath1 kwnfragsize 1500

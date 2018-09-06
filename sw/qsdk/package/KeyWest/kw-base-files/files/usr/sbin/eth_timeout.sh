#!/bin/sh/
#
# To check ethernet ideal time

ethtimer=$(uci get ethernet.ethernet.ethtimer)
eth_timer=`expr $ethtimer \* 60`;
rm -rf /tmp/.rx_pkt_cur
rm -rf /tmp/.rx_pkt_backup
rm -rf /tmp/.tx_pkt_cur 
rm -rf /tmp/.tx_pkt_backup

eth_inactivity(){
    
date=$(date)

limit=$(ls -l /tmp/eth_events.txt | awk '{print $5}')
    
if [ "$limit" -gt 2097152 ]; then
    rm -rf /tmp/eth_events.txt
fi

file_backup="/tmp/.rx_pkt_backup"

if [ -f "$file_backup" ]
then 
    ifconfig eth0 | grep "RX packets" |awk '{print $2}' | cut  -d':' -f2 > /tmp/.rx_pkt_cur
    ifconfig eth0 | grep "TX packets" |awk '{print $2}' | cut  -d':' -f2 > /tmp/.tx_pkt_cur
    
    last_rx_packet=$(cat /tmp/.rx_pkt_backup)
    last_tx_packet=$(cat /tmp/.tx_pkt_backup)
    
    current_rx_packet=$(cat /tmp/.rx_pkt_cur)
    current_tx_packet=$(cat /tmp/.tx_pkt_cur)
    
    cp -rf /tmp/.rx_pkt_cur /tmp/.rx_pkt_backup
    cp -rf /tmp/.tx_pkt_cur /tmp/.tx_pkt_backup
    Tx_diff=`expr $current_tx_packet - $last_tx_packet`;
    Rx_diff=`expr $current_rx_packet - $last_rx_packet`;
    
    if [ "$last_rx_packet" -eq "$current_rx_packet" ]; then

        if [ "$last_tx_packet" -eq "$current_tx_packet" ]; then
        
            ifconfig eth0 down    
            sleep 1
            ifconfig eth0 up
            return 1    
        fi
    fi
    
else
    ifconfig eth0 | grep "RX packets" |awk '{print $2}' | cut  -d':' -f2 > /tmp/.rx_pkt_cur
    ifconfig eth0 | grep "TX packets" |awk '{print $2}' | cut  -d':' -f2 > /tmp/.tx_pkt_cur
    cp -rf /tmp/.rx_pkt_cur /tmp/.rx_pkt_backup
    cp -rf /tmp/.tx_pkt_cur /tmp/.tx_pkt_backup
fi    
}

eth_timer_progress(){
while [ true ]
do
    eth_inactivity
    sleep $eth_timer
done
}

if [ "$eth_timer" -eq 0 ] 
    then 
    exit
else
    eth_timer_progress &
fi

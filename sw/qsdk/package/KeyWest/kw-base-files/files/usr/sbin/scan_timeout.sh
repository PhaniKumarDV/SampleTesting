#!/bin/sh/
#
# To check scanning ideal time

LOG_FILE="/tmp/wifi_packet_logs"
radio_mode=$(uci get wireless.@wifi-iface[1].mode)
scantimer=$(uci get wireless.wifi1.scantimer)

scan_inactivity(){ 
       date=`date '+%a %b %Oe %H:%M:%S %Y'`
       link=$(wlanconfig ath1 list sta | wc -l)
       diff=$(iwpriv ath1 g_kwnscandiff  | sed 's/ath1      g_kwnscandiff://')
       echo "############ Link:$link Diff:$diff ##############"
       if [ $link -le 1 ]; then
           if [ $diff -ge 30 ];then
	          echo "$date: Scanning inactivity triggered" >> $LOG_FILE
              ifconfig ath1 down
              sleep 1
              ifconfig ath1 up
              return 1    
           fi
       fi
}

scan_timer_progress(){
while [ true ]
do
    sleep $scantimer
    scan_inactivity
done
}

if [ "$scantimer" -eq 0 ] 
    then 
    exit
else
    if [ "$radio_mode" == "sta" ]
    then
        scan_timer_progress &
    else
        exit
    fi
fi


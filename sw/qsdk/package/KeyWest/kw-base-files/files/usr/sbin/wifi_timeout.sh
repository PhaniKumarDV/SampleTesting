#!/bin/sh/
#
# To check wireless ideal time

LOG_FILE="/tmp/wifi_packet_logs"
radio_mode=$(uci get wireless.@wifi-iface[1].mode)
wifitimer=$(uci get wireless.wifi1.wifitimer)
wifi_timer=`expr $wifitimer \* 60`;
rm -rf /tmp/.link_cur 
rm -rf /tmp/.link_backup

wifi_inactivity(){ 
   date=`date '+%a %b %Oe %H:%M:%S %Y'`
   file_backup="/tmp/.link_backup"

   if [ -f "$file_backup" ]
   then
       wlanconfig ath1 list sta | wc -l > /tmp/.link_cur
       last_link=$(cat /tmp/.link_backup)
       current_link=$(cat /tmp/.link_cur)
       cp -rf /tmp/.link_cur /tmp/.link_backup
       echo "############ Last:$last_link Current:$current_link ##############"
  
       if [ $last_link -le 1 ];then
           if [ $current_link -le 1 ];then
	          echo "$date: Wireless inactivity triggered" >> $LOG_FILE
              /etc/init.d/network reload 
              sleep 30
              return 1    
           fi
       fi
    else
       wlanconfig ath1 list sta | wc -l > /tmp/.link_cur
       cp -rf /tmp/.link_cur /tmp/.link_backup
    fi
}

wifi_timer_progress(){
while [ true ]
do
    wifi_inactivity
    sleep $wifi_timer
done
}

if [ "$wifi_timer" -eq 0 ] 
    then 
    exit
else
    if [ "$radio_mode" == "sta" ]
    then
        wifi_timer_progress &
    else
        exit
    fi
fi


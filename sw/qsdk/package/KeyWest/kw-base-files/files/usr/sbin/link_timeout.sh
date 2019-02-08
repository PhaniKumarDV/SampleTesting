#!/bin/sh/
#
# To check link ideal time

LOG_FILE="/tmp/wifi_packet_logs"
radio_mode=$(uci get wireless.@wifi-iface[1].mode)
linktimer=$(uci get wireless.wifi1.linktimer)
link_timer=`expr $linktimer \* 60`;
rm -rf /tmp/.tx_wifipkt_cur 
rm -rf /tmp/.tx_wifipkt_backup

link_inactivity(){ 
   date=`date '+%a %b %Oe %H:%M:%S %Y'`
   file_backup="/tmp/.tx_wifipkt_backup"
   links=$(wlanconfig ath1 list sta | wc -l)

   if [ $links -ne 2 ];then
      echo "########## No Links: $links"
      return 1;
   fi
   wlanconfig ath1 list sta | awk '{print $1}'  > /tmp/.wifi
   count=0
   while read line
   do
      name=$line
      count=$(($count + 1))
      if [ $count -eq 2 ];then
         echo $name | awk '{print $1}' >/tmp/.mac
         mac=$(cat /tmp/.mac)
         #echo "MAC: $mac"
      fi
   done  < /tmp/.wifi

   if [ -f "$file_backup" ]
   then 
       apstats -s -m $mac eth0 | grep "Tx Data Packets                 = " | sed 's/Tx Data Packets                 = //' > /tmp/.tx_wifipkt_cur
       last_tx_packet=$(cat /tmp/.tx_wifipkt_backup)
       current_tx_packet=$(cat /tmp/.tx_wifipkt_cur)
       cp -rf /tmp/.tx_wifipkt_cur /tmp/.tx_wifipkt_backup
       echo "############ Last:$last_tx_packet Current:$current_tx_packet ##############"
       if [ "$last_tx_packet" -eq "$current_tx_packet" ]; then        
	        echo "$date: Link inactivity triggered" >> $LOG_FILE
            /etc/init.d/network reload 
            sleep 30
            return 1    
       fi
    else
       apstats -s -m $mac eth0 | grep "Tx Data Packets                 = " | sed 's/Tx Data Packets                 = //' > /tmp/.tx_wifipkt_cur
       cp -rf /tmp/.tx_wifipkt_cur /tmp/.tx_wifipkt_backup
    fi
}

link_timer_progress(){
while [ true ]
do
    link_inactivity
    sleep $link_timer
done
}

if [ "$link_timer" -eq 0 ] 
    then 
    exit
else
    if [ "$radio_mode" == "sta" ]
    then
        link_timer_progress &
    else
        exit
    fi
fi


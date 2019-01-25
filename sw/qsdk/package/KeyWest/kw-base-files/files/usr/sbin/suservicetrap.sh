#!/bin/sh/
#
# To send trap if su service disable

radio_mode=$(uci get wireless.@wifi-iface[1].mode)
suservice=$(uci get wireless.wifi1.suservice)
service_timer=300;


send_trap(){
   date=`date | sed 's/UTC //g'`
   /usr/sbin/snmptrap.sh 5 %s  > /dev/null 2>&1
}


link_timer_progress(){
while [ true ]
do
    if [ "$suservice" -eq 1 ]
    then
        exit
    fi
    links=$(wlanconfig ath1 list sta | wc -l)
    if [ $links -ne 2 ];then
        echo "########## No Links: $links"
    else
        send_trap
    fi
    sleep $service_timer
done
}



if [ "$suservice" -eq 1 ] 
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


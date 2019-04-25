#!/bin/sh/
#
# To send wireless event log

LOG_FILE="/tmp/wifi_packet_logs"
radio_mode=$(uci get wireless.@wifi-iface[1].mode)

disassoc_log() {
    date=`date '+%a %b %Oe %H:%M:%S %Y'`

    if [ "$radio_mode" == "ap" ]
    then
        return 1
    fi
    links=$(wlanconfig ath1 list sta | wc -l)
    if [ $links -ne 2 ];then
        echo "########## No Links: $links"
        return 1
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
    echo "$date: Disassociated ( MAC: $mac )" >> $LOG_FILE
}

if [ "$1" -eq 1 ]; then
    disassoc_log
fi

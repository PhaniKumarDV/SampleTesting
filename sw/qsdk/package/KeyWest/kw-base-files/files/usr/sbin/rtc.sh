#!/bin/sh/
#To set RTC time when ntp server is not enabled

ntp=$(uci get system.ntp.enabled)
gpstime=$(uci get system.gps.time)

if [ "$gpstime" != "No Value" ] && [ "$ntp" != "1" ]
then
    date +%T -s $gpstime
fi

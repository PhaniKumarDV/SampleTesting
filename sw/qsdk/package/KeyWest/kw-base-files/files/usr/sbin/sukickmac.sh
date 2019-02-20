#!/bin/sh/
#
# To disconnect BSU: kickmac BSU MAC and flush the scan entries

   links=$(wlanconfig ath1 list sta | wc -l)

   if [ $links -ne 2 ];then
      echo "########## No Links: $links"
      return 1;
   fi
   wlanconfig ath1 list sta | awk '{print $1}'  > /tmp/.kick
   count=0
   while read line
   do
      name=$line
      count=$(($count + 1))
      if [ $count -eq 2 ];then
         echo $name | awk '{print $1}' >/tmp/.kmac
         mac=$(cat /tmp/.kmac)
         echo "MAC: $mac"
         iwpriv ath1 kickmac $mac
         iwpriv ath1 kwn_flag 4
         iwpriv ath1 s_scan_flush 1
         iwpriv ath1 kwn_flag 0
      fi
   done  < /tmp/.kick




#!/bin/sh/
#
# To reboot the device

/usr/sbin/snmptrap.sh 10  > /dev/null 2>&1
sleep 2
reboot
sleep 5
iwpriv ath1 kwnreboottime 0
iwpriv ath1 kwnreboot 1

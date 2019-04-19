
#!/bin/sh/
#
# To reboot the device

reboot
sleep 5
iwpriv ath1 kwnreboottime 0
iwpriv ath1 kwnreboot 1

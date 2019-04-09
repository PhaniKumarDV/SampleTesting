
#!/bin/sh/
#
# To set bridge ipaddress after every 5 seconds

update_ip(){
while [ true ]
do
    ip=$(ifconfig br-lan | grep 'inet addr' | cut -d: -f2 | awk '{print $1}')
    if [ "$ip" == "" ]
    then
        ip="0.0.0.0"
    fi
    iwpriv wifi1 str_type 4
    iwconfig ath1 nickname $ip
    sleep 5
done
}
update_ip &

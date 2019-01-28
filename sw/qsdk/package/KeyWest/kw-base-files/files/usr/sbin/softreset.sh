
#!/bin/sh/
#
# To set softreset flag to completed after 20seconds

resettime=20
enable_softreset(){
while [ true ]
do
    sleep $resettime
    iwpriv ath0 kwnsoftreset 1
    iwpriv ath1 kwnsoftreset 1
done
}
enable_softreset &

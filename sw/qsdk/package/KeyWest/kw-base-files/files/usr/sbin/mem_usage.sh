
#!/bin/sh/
#
# To calculate Memory Usage percentage.

LOG_FILE="/tmp/mem_usage"

total_mem=$(free -m  | grep ^Mem | tr -s ' ' | cut -d ' ' -f 2)
mem_use=$(free -m  | grep ^Mem | tr -s ' ' | cut -d ' ' -f 3)

mem_prcnt=$(( mem_use * 100))
mem_prcnt=$(( mem_prcnt / total_mem ))
echo $mem_prcnt > $LOG_FILE
cat $LOG_FILE


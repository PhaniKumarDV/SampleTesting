
#!/bin/sh/
#
# To calculate CPU Usage percentage.

LOG_FILE="/tmp/cpu_usage"

cpu_prcnt=$(grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {print usage ""}')

echo "$cpu_prcnt" > $LOG_FILE
cat $LOG_FILE


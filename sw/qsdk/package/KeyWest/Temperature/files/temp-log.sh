#!/bin/sh

# First arg interval
int=$1

# Temp log app
TEMP_LOG_APP="/usr/sbin/temp-log"
TEMP_LOG_FILE="/tmp/temp-log"

while [ 1 ]; do
    if [ $2 == "1" ]; then
	    FILESIZE=$(stat -c%s "$TEMP_LOG_FILE")

    	if [ "${FILESIZE}" -gt "16384" ];then
	    	mv -f $TEMP_LOG_FILE $TEMP_LOG_FILE.2
    	fi
    fi
    $TEMP_LOG_APP $2
    sleep "${int}"
done

#!/bin/sh

echo "Welcome to CLI"
echo

# trap '' SIGINT


console() {
while [ 1 ] ; do
	read -rp "KeyWest# " CMD
	if [ "$CMD" == "?" ]; then
		uci -h
	elif [ "$CMD" == "exit" ]; then
		exit
	elif [ "$CMD" == "reload_config" ]; then
		reload_config
	elif [ "$CMD" == "reboot" ]; then
		echo "Device is rebooting...."
        /usr/sbin/sify_reboot_log.sh 2
		reboot
	elif [ "$CMD" == "reset" ]; then
		echo "Device is resetting to factory defaults...."
        /usr/sbin/sify_reboot_log.sh 6
		firstboot
	else
		a=`echo "$CMD" | cut -d' ' -f 1`
		if [ "$a" != "uci" ]; then
			echo "Invalid command, supports only UCI"
		else
			$CMD
		fi
	fi
done
}

console

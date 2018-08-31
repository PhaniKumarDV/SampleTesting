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
		reboot
	elif [ "$CMD" == "reset" ]; then
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

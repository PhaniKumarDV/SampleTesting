#!/bin/sh

. /lib/user-auth.sh

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
login() {
    retries=0
    while [ $retries -lt 3 ];do
        clear
        read -rp "Username: " USER
        read -srp "Password: " PASS
        auth_user "$USER" "$PASS"
        local isOK=$?
        if [ "${isOK}" == "1" ] ; then
            return 1;
        fi
        retries="$(($retries+1))"
    done
    return 0
}

login
if [ $? == 1 ];then
    clear
    console
else
    echo
    echo "Invalid Username/Password."
fi

#!/bin/sh

. /lib/user-auth.sh

# trap '' SIGINT

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
    /usr/sbin/cli.sh
else
    echo
    echo "Invalid Username/Password."
    exit
fi

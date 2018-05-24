#!/bin/sh

auth_user() {
    local USER=$1
    local PASS=$2
    passHash=`grep "^${USER}" /etc/passwd | cut -d':' -f 2`
    if [ "${passHash}" != '' ]; then
        salt=`echo "${passHash}" | cut -d '$' -f 3`
        if [ "${salt}" != '' ]; then
            genHash=`openssl passwd -1 -salt "${salt}" "${PASS}"`
            if [ "${genHash}" == "${passHash}" ]; then
                return 1
            fi
        fi
    fi

    return 0
}

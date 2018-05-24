#!/bin/sh

debug(){
[ -e "/tmp/CLI_DEBUG" ] && echo "$1" "$2" "$3" "$4" "$5" "$6" "$7" 1>&2- > /dev/null
}

#rewrite get_username , get_password and psencry on WEBServer changes
CLI_escchar(){
	value="$1"
	value=$(echo "$value"|sed -e 's/\\/\\\\/g')
	value=$(echo "$value"|sed -e 's/"/\\"/g')
	value=$(echo "$value"|sed -e 's/`/\\`/g')
	value=$(echo "$value"|sed -e 's/[$]/\\$/g')
	printf "$value"
}

psencry(){
	password=$1
	echo "$password" | md5sum | cut -c -32
	debug password="$password" > /dev/null
}
get_username(){
grep ":" /etc/webpasswd|cut -d : -f 1
}
get_password(){
user_name=$(get_username)
user_len=${#user_name}
cat /etc/webpasswd|cut -c $(($user_len+2))-
}
login_auth(){
	username="$1"
	password="$2"
	password_hash=$(psencry "$password")
	uname_fail=0
	upass_fail=0
	if [ $(get_username) = "$username" ]; then
		debug "$username" OK.
	else
		uname_fail=1;debug err_user:"$username";
	fi
	if [ $(get_password) = "$password_hash" ];  then
		debug "$password_hash" OK.
	else
		upass_fail=1;debug err_pass:"$password_hash";
	fi	
	printf "$uname_fail,$upass_fail\n"
}
set_auth(){
	username=$1
	password=$2
	password_hash=$(psencry "$password")
	printf "$username:$password_hash\n" > /etc/webpasswd	
}
case $1 in
	psencry)      psencry $2 ;;
	login_auth)   login_auth $2 $3 ;;
	get_username) get_username ;;
	get_password) get_password ;;
	set_auth)     set_auth $2 $3 ;;
esac



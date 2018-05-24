#!/bin/sh
# Copyright (C) 2006 OpenWrt.org

. /lib/auth.sh
. /etc/functions.sh
config_load network
config_get ipaddr lan ipaddr

download="/tmp/download"
eval="/tmp/eval.sh"
version="/etc/version"
firmware="/tmp/firmware.img"
backup="/tmp/backup.gz"
restore="/tmp/restore.gz"
log="$download/log.txt"

shellcmd=" \
	brctl \
	date \
	ifconfig \
	iwconfig \
	iwlist \
	iwpriv \
	logread \
	ping \
	telnet \
	traceroute \
	uci \
	uptime \
	vconfig \
	wlanconfig \
	"

show_help()
{
cat <<EOF
CLI Commands:
	arp                  Display ARP information
	config-backup        Backup config and get download URL
	config-backup-upload Backup config and upload to the remote FTP/TFTP server
	config-restore       Download config from URL and restore it
	exit                 Exit
	factory-default      Restore default config and reboot
	fwupgrade            Download firmware image from URL and upgrade it
	fwversion            Display firmware version
	help                 Help
	logfile              Save log to a file and get download URL
	logfile-upload       Save log to a file and upload to the remote FTP/TFTP server
	meminfo              Display device memory usage
	reboot               Reboot device
	rx_packets           Show WLAN received frame count
	tx_errors            Show WLAN transmitted error count
	tx_packets           Show WLAN transmitted frame count
$(for var in $shellcmd; do printf "\t$var\n"; done)
EOF
}

debug()
{
	output="/dev/ttyS0"
	dbgflag="/tmp/CLI_DEBUG"
	[ -e "$output" -a -e "$dbgflag" ] && \
		echo "$1" >/dev/ttyS0
}

read_line()
{
	read -rp "$1" input
	debug "$input"
	echo "$input"
}

priv_gate()
{
	[ "rw" = "$login_priv" ] && \
		return
	[ ! "$1" = "$login_priv" ] && {
		echo "Access denied"
		continue
	}
}

runcmd()
{
	[ -n "$1" ] && {
		[ -e "$eval" ] && \
			rm -rf "$eval"
		echo "$1" >"$eval" && \
			chmod a+x "$eval" && \
			$eval
	}
}

file_transfer()
{
	[ -n "$1" -a -n "$2" ] && {
		pattern="^\(.*\):\/\/\(\([^:]*\)\(:\(.*\)\)\{0,1\}@\)\{0,1\}\([^:/]*\)\(:\([^/]*\)\)\{0,1\}\/\(.*\)$"
		protocol=""
		username=""
		password=""
		hostname=""
		port=""
		filepath=""
		filename=""
		[ -z "$(echo "$2" | grep "'")" ] && [ -n "$(echo "$2" | grep "$pattern")" ] && {
			eval "$(echo "$2" | sed -e "s/$pattern/protocol='\1'; username='\3'; password='\5'; hostname='\6'; port='\8'; filepath='\9';/g")"
			filename="$(echo $filepath | sed -e "s/^\/\([^/]*\/\)*//g")"
		}
		[ -n "$protocol" -a -n "$hostname" -a -n "$filepath" ] && {
			cmd=""
			case "$protocol" in
				"http")
					[ "$1" = "get" ] && \
						cmd="wget"
					[ -n "$cmd" ] && {
						[ -n "$3" ] && \
							cmd="$cmd -O \"$3\""
						cmd="$cmd \"$2\""
					}
					;;
				"ftp")
					if [ "$1" = "get" ]; then
						cmd="ftpget"
					elif [ "$1" = "put" ]; then
						cmd="ftpput"
					fi
					[ -n "$cmd" ] && {
						[ -n "$username" ] && \
							cmd="$cmd -u \"$username\""
						[ -n "$password" ] && \
							cmd="$cmd -p \"$password\""
						[ -n "$port" ] && \
							cmd="$cmd -P \"$port\""
						cmd="$cmd \"$hostname\""
						if [ "$1" = "get" ]; then
							if [ -n "$3" ]; then
								cmd="$cmd \"$3\""
							else
								cmd="$cmd \"$filename\""
							fi
							cmd="$cmd \"$filepath\""
						elif [ "$1" = "put" ]; then
							cmd="$cmd \"$filepath\""
							if [ -n "$3" ]; then
								cmd="$cmd \"$3\""
							else
								cmd="$cmd \"$filename\""
							fi
						fi
					}
					;;
				"tftp")
					if [ "$1" = "get" ]; then
						cmd="tftp -g"
					elif [ "$1" = "put" ]; then
						cmd="tftp -p"
					fi
					[ -n "$cmd" ] && {
						if [ -n "$3" ]; then
							cmd="$cmd -l \"$3\""
						else
							cmd="$cmd -l \"$filename\""
						fi
						cmd="$cmd -r \"$filepath\""
						cmd="$cmd \"$hostname\""
						[ -n "$port" ] && \
							cmd="$cmd \"$port\""
					}
					;;
			esac
			[ -n "$cmd" ] && (runcmd "$cmd" 2>/dev/null >&2) && \
				return 0
		}
	}
	return 1
}


fwupgrade()
{
#	priv_gate "rw"
	
#	input="$(read_line "Download firmware image from URL: ")"
	input=$1
	[ -e "$firmware" ] && \
		rm -rf "$firmware"
	if (file_transfer "get" "$input" "$firmware"); then
		"/etc/cfg_backup.sh"
		"/etc/fwupgrade.sh" && reboot
	else
		echo "Upgrade failed."
	fi
}

config_restore()
{
	#priv_gate "rw"
	#input="$(read_line "Download config from URL: ")"
	input=$1
	[ -e "$restore" ] && \
		rm -rf "$restore"
	if (file_transfer "get" "$input" "$restore"); then
		"/etc/cfgrestore.sh" && reboot
	else
		echo "Download failed."
	fi
}

case $1 in
	fwupgrade)      fwupgrade $2 ;;
	config_restore)   config_restore $2 ;;

esac
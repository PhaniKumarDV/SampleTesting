# Send SNMP Traps

trapmsg="TRAP Message"
gentrapoid="1.3.6.1.4.1.52619.1.2.2.1"
trapoid="1.3.6.1.4.1.52619.1.3.4.1"

trap_send()
{
    host=$(uci get snmpd.trapaddress.host)
    paswd=$(uci get snmpd.trapaddress.paswd)

    snmptrap -v2c -c $paswd $host 123 "$trapoid" "$gentrapoid" s "$trapmsg"
}


if [ "$1" -eq 1 ]; then
    trapmsg="Associated (MAC:$2)"
    trapoid="1.3.6.1.4.1.52619.1.3.4.1"
	trap_send
    exit
fi

if [ "$1" -eq 2 ]; then
    trapmsg="Disassociated (MAC:$2)"
    trapoid="1.3.6.1.4.1.52619.1.3.4.2"
	trap_send
    exit
fi

if [ "$1" -eq 3 ]; then
    trapmsg="Remote Device (MAC:$2) is power off"
    trapoid="1.3.6.1.4.1.52619.1.3.4.3"
	trap_send
    exit
fi

if [ "$1" -eq 4 ]; then
    trapmsg="Outdoor Base (MAC:$2) is power off"
    trapoid="1.3.6.1.4.1.52619.1.3.4.4"
	trap_send
    exit
fi

if [ "$1" -eq 5 ]; then
    trapmsg="SU service is disabled"
    trapoid="1.3.6.1.4.1.52619.1.3.4.5"
	trap_send
    exit
fi

if [ "$1" -eq 6 ]; then
    trapmsg="Configuration applied successfully"
    trapoid="1.3.6.1.4.1.52619.1.3.4.6"
	trap_send
    exit
fi
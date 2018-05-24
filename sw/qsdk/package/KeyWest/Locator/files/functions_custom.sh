#!/bin/sh

# talor add sdebug for Senao debug
sdebug () {
	${SENAODBG:-:} "[SenDBG]: $@"
}

# talor add IPv6 functions
#custom_ipv6_enabled()
#{
#    v6=`uci show system.system.ipv6 |grep 1`
#    [ -n "$v6" ] && return 0
#    return 1
#}

#custom_ipv6_disabled()
#{
#    custom_ipv6_enabled && return 1
#    return 0
#}

custom_ipv6_enabled()                       
{                                           
    v6=`uci show system.system.ipv6`
    if [ "${v6#system.system.ipv6=}" == "1" ]; then
        echo "1"                
    else
        echo ""
    fi                                
}                                           
                                            
custom_ipv6_disabled()                      
{                                           
    if [ "$(custom_ipv6_enabled)" == "" ]; then
        echo "1"
    else
        echo ""
    fi        
}                                            
 
custom_ipv6ct_enabled()
{
    local yes=""

    if [ "$(custom_ipv6_enabled)" == "1" ]; then
        v6ct=`uci show system.system.ipv6ct`
        if [ "${v6ct#system.system.ipv6ct=}" == "1" ]; then
            yes="1"
        fi
    fi
    echo "$yes"
}

custom_ipv6ct_disabled()
{
    if [ "$(custom_ipv6ct_enabled)" == "" ]; then
        echo "1"
    else
        echo ""
    fi
}

service_kill() { # angus #
        local name="${1}"
        local pid="${2:-$(pidof "$name")}"
        local grace="${3:-5}"

        [ -f "$pid" ] && pid="$(head -n1 "$pid" 2>/dev/null)"

        for pid in $pid; do
                [ -d "/proc/$pid" ] || continue
                local try=0
                kill -TERM $pid 2>/dev/null && \
                        while grep -qs "$name" "/proc/$pid/cmdline" && [ $((try++)) -lt $grace ]; do sleep 1; done
                kill -KILL $pid 2>/dev/null && \
                        while grep -qs "$name" "/proc/$pid/cmdline"; do sleep 1; done
        done
}

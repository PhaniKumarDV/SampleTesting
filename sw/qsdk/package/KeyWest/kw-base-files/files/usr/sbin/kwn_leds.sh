#!/bin/sh/
#
# To enable LED after every 2 seconds

led_path="/sys/devices/soc.0/gpio_led.6/leds/lan1/brightness"
led1_path="/sys/devices/soc.0/gpio_led.6/leds/wlan5/brightness"
led2_path="/sys/devices/soc.0/gpio_led.6/leds/ap_status/brightness"
led3_path="/sys/devices/soc.0/gpio_led.6/leds/wlan24/brightness"
time=0

enable_leds(){
    while [ true ]
    do
        lastrc=$(athstats -i wifi1|grep last|tr -d '\t'|cut -d':' -f 2)
        links=$(wlanconfig ath1 list sta | wc -l)
        if [ $links -eq 0 ];then
            lastrc=0
        fi
        case "$lastrc" in
            192|208)
                # MCS0
                led=$led1_path
                led1=$led2_path
                led2=$led3_path
                time=2
                ;;
            193|209)
                # MCS1
                led=$led1_path
                led1=$led2_path
                led2=$led3_path
                time=1
                ;;
            194|210)
                # MCS2
                led=$led1_path
                led1=$led2_path
                led2=$led3_path
                time=0
                ;;
            195|211)
                # MCS3
                led=$led2_path
                led1=$led1_path
                led2=$led3_path
                time=2
                ;;
            196|212)
                # MCS4
                led=$led2_path
                led1=$led1_path
                led2=$led3_path
                time=1
                ;;
            197|213)
                # MCS5
                led=$led2_path
                led1=$led1_path
                led2=$led3_path
                time=0
                ;;
            198|214)
                # MCS6
                led=$led3_path
                led1=$led1_path
                led2=$led2_path
                time=2
                ;;
            199|215)
                # MCS7
                led=$led3_path
                led1=$led1_path
                led2=$led2_path
                time=1
                ;;
            200|216)
                # MCS8
                led=$led3_path
                led1=$led1_path
                led2=$led2_path
                time=0
                ;;
            201|217)
                # MCS9
                 time=0
                ;;
            *)
                # Default
                lastrc=0
                time=0
                ;;
        esac

        if [ $lastrc == "0" ]
        then
            echo 0 > $led1_path
            echo 0 > $led2_path
            echo 0 > $led3_path
        else
            if [[ $lastrc == "201" ]] || [[ $lastrc == "217" ]]
            then
                echo 1 > $led1_path
                echo 1 > $led2_path
                echo 1 > $led3_path
            else
                echo 0 > $led1
                echo 0 > $led2
                echo 1 > $led
            fi
        fi

        case "$time" in
            1)
                sleep 1
                echo 0 > $led
                sleep 1
                ;;
            2)
                sleep 2
                echo 0 > $led
                sleep 2
                ;;
            *)
                sleep 1
                ;;
        esac
    done
}

enable_leds &



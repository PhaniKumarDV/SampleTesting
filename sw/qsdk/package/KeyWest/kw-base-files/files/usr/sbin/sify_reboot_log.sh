#!/bin/sh

#
# Tool to Reboot log statistics 
#

date=`date '+%a %b %Oe %H:%M:%S %Y'`
webreboot ()
{
        echo "$date: Reboot initiated through Web"  >> /etc/reboot_logs
        #echo "web"  > /etc/reboot_type
        #echo > /etc/soft_reboot_check
}

webfactreboot ()
{
        echo "$date: Reboot initiated through Web for Factory reset" >> /etc/reboot_logs
        #echo "web"  > /etc/reboot_type
        #echo > /etc/soft_reboot_check
        #mkdir -p /mnt/part2
        #mount -t jffs2 /dev/mtdblock2 /mnt/part2
        #cp -rf /etc/reboot_logs /mnt/part2/
        #cp -rf /etc/reboot_type /mnt/part2/
        #cp -rf /etc/soft_reboot_check /mnt/part2/
        #umount /mnt/part2
}

frmupreboot ()
{
        echo "$date: Reboot initiated during Firmware upgrade" >> /etc/reboot_logs
        #echo "web"  > /etc/reboot_type
        #echo > /etc/soft_reboot_check
}

clireboot ()
{
        echo "$date: Reboot initiated through Cli" >> /etc/reboot_logs
        #echo "cli"  > /etc/reboot_type
        #echo > /etc/soft_reboot_check
}

clifactreboot ()
{
        echo "$date: Reboot initiated through Cli for Factory reset" >> /etc/reboot_logs
        #echo "cli"  > /etc/reboot_type
        #echo > /etc/soft_reboot_check
        #mkdir -p /mnt/part2
        #mount -t jffs2 /dev/mtdblock2 /mnt/part2
        #cp -rf /etc/reboot_logs /mnt/part2/
        #cp -rf /etc/reboot_type /mnt/part2/
        #cp -rf /etc/soft_reboot_check /mnt/part2/
        #umount /mnt/part2
}

dyinggasp ()
{
        echo "$date: Reboot initiated due to Dying Gasp" >> /etc/reboot_logs
}

if [ "$1" -eq 1 ]; then
	webreboot 
        exit
fi

if [ "$1" -eq 2 ]; then
	clireboot 
        exit
fi

if [ "$1" -eq 4 ]; then
	webfactreboot 
        exit
fi

if [ "$1" -eq 5 ]; then
	frmupreboot 
        exit
fi

if [ "$1" -eq 6 ]; then
	clifactreboot 
        exit
fi

if [ "$1" -eq 7 ]; then
        echo "$date: Reboot initiated through Configuration Restore " >> /etc/reboot_logs
        exit
fi

if [ "$1" -eq 8 ]; then
	dyinggasp 
        exit
fi

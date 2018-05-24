#!/usr/bin/env bash

if [ ! -d "boot_images" ]; then
	cp -rf BOOT.BF.3.1.1/boot_images .
fi

if [ ! -d "trustzone_images" ]; then
	cp -rf TZ.BF.2.7/trustzone_images .
fi

if [ ! -d "apss_proc" ]; then
	cp -rf NHSS.QSDK.5.0.3/apss_proc .
fi

if [ ! -d "cnss_proc" ]; then
	mkdir cnss_proc
fi

if [ ! -d "cnss_proc_ps" ]; then
	mkdir cnss_proc_ps
fi

if [ ! -d "common" ]; then
	cp -rf IPQ4019.ILQ.5.0.3/common .
fi

cp -rf IPQ4019.ILQ.5.0.3/contents.xml .

if [ "$1" = "std" ]; then
	echo "ipq40xx_standard configuration !!"
	cp ../sw/meta-scripts/ipq40xx_standard/* common/build/ipq
else
	echo "ipq40xx_premium configuration !!"
	cp ../sw/meta-scripts/ipq40xx_premium/* common/build/ipq
fi

cp -rf ../sw/qsdk/qca/src/uboot-1.0/tools/pack.py  apss_proc/out/
cp -rf trustzone_images/build/ms/bin/MAZAANAA/* common/build/ipq
cp -rf ../sw/qsdk/bin/ipq806x/openwrt* common/build/ipq

if [ "$1" = "std" ]; then
	echo "ipq40xx_standard configuration !!"	
	cp boot_images/build/ms/bin/40xx/misc/tools/config/boardconfig_standard common/build/ipq
	cp boot_images/build/ms/bin/40xx/misc/tools/config/appsboardconfig_standard common/build/ipq
else
	echo "ipq40xx_premium configuration !!"
	cp boot_images/build/ms/bin/40xx/misc/tools/config/boardconfig_premium common/build/ipq
	cp boot_images/build/ms/bin/40xx/misc/tools/config/appsboardconfig_premium common/build/ipq	
fi

cd common/build

if [ "$1" = "std" ]; then
	echo "ipq40xx_standard configuration !!"
	sed '/debug/d' -i update_common_info_standard.py 
	sed '/s-gcc5/d' -i update_common_info_standard.py 
	python update_common_info_standard.py 
else
	echo "ipq40xx_premium configuration !!"
	sed '/debug/d' -i update_common_info.py
	python update_common_info.py
fi

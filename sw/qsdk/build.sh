#!/usr/bin/env bash
START=$(date +%y-%m/%d-%H/%M/%S)
./scripts/feeds update -a
./scripts/feeds install -a -f

if [ "$1" = "std" ]; then
	echo "ipq806x_standard configuration !!"
	cp qca/configs/qsdk/ipq806x_standard.config .config
else
	echo "ipq806x_premium configuration !!"
	cp qca/configs/qsdk/ipq806x_premium.config .config
fi

make defconfig
cat ./KeyWestConfig >> .config
for pkg_num in 2 9;do sed 's/CONFIG_PACKAGE_qca-wifi-fw-hw'${pkg_num}'-10.4-asic=y/# CONFIG_PACKAGE_qca-wifi-fw-hw'${pkg_num}'-10.4-asic is not set/g' -i .config;done
sed '/CONFIG_PACKAGE_kmod-wil6210=m/d' -i .config
sed '/CONFIG_PACKAGE_qca-fst-manager=m/d' -i .config
sed '/CONFIG_PACKAGE_wigig-firmware=m/d' -i .config
sed '/CONFIG_PACKAGE_qca-wigig-tools=m/d' -i .config
sed '/CONFIG_PACKAGE_qca-wigig-debug-tools=m/d' -i .config
echo "CONFIG_TOOLCHAINOPTS=y" >> .config
echo '# CONFIG_GCC_USE_VERSION_4_8_LINARO is not set' >> .config
echo "CONFIG_GCC_USE_VERSION_5=y" >> .config
echo 'CONFIG_GCC_VERSION="5.2.0"' >> .config
echo "CONFIG_GCC_VERSION_5=y" >> .config

if [ "$DEBUG" == "1" ];then
    cp -f ./package/KeyWest/kw-base-files/debug/passwd.debug ./package/KeyWest/kw-base-files/files/etc/passwd
else
    cp -f ./package/KeyWest/kw-base-files/debug/passwd ./package/KeyWest/kw-base-files/files/etc/passwd
fi

if [ "$MODEL" != "" ]; then
    echo "$MODEL" > ./package/KeyWest/kw-base-files/files/etc/model
else
    echo "MAP100" > ./package/KeyWest/kw-base-files/files/etc/model
fi


NOW=$(date +%y%m%d-%H%M%S)

# make V=s 2>&1 > build_log_$NOW.txt
make V=s 2>&1


if [ "$?" = "0" ] ; then
	echo "========================"
	echo "BUILD SUCCESS!!!"
	echo "========================"
else
	echo "========================"
	echo "BUILD FAILED!!!"
	echo "========================"
	exit 1
fi

echo "========================"
echo "Making Single Image...."
cd ../../src
./single_image.sh $1
echo "Making Single Image Done~"
echo "========================"
END=$(date +%y-%m/%d-%H/%M/%S)
echo "========================"
echo "BUILD START at $START !!"
echo "FINISH at $END !!"
echo "========================"


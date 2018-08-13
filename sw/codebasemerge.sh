#!/usr/bin/env bash
mkdir -p qsdk/dl
cp -rf ../src/NHSS.QSDK.5.0.3/apss_proc/out/proprietary/Wifi/qsdk-qca-wifi/* qsdk
cp -rf ../src/NHSS.QSDK.5.0.3/apss_proc/out/proprietary/Wifi/qsdk-qca-wlan/* qsdk
cp -rf ../src/NHSS.QSDK.5.0.3/apss_proc/out/proprietary/Wifi/qsdk-ieee1905-security/* qsdk
cp -rf ../src/NHSS.QSDK.5.0.3/apss_proc/out/proprietary/Wifi/qsdk-qca-athdiag/* qsdk
cp -rf ../src/NHSS.QSDK.5.0.3/apss_proc/out/proprietary/QSDK-Base/qca-lib/* qsdk
cp -rf ../src/NHSS.QSDK.5.0.3/apss_proc/out/proprietary/QSDK-Base/qca-mcs-apps/* qsdk
tar xjvf ../src/NHSS.QSDK.5.0.3/apss_proc/out/proprietary/BLUETOPIA/qca-bluetopia.tar.bz2 -C qsdk

cp ../src/WLAN.BL.3.5.3/cnss_proc/bin/IPQ4019/hw.1/* qsdk/dl
cp ../src/WLAN.BL.3.5.3/cnss_proc/bin/QCA9888/hw.2/* qsdk/dl
cp ../src/WLAN.BL.3.5.3/cnss_proc/bin/QCA9984/hw.1/* qsdk/dl
cp -rf ../src/WLAN.BL.3.5.3/cnss_proc/src/components/* qsdk/dl
cp ../src/CNSS.PS.2.5.3/* qsdk/dl
cp -rf ../src/NHSS.QSDK.5.0.3/apss_proc/out/proprietary/Hyfi/hyfi-ipq/* qsdk
cp -rf ../src/NHSS.QSDK.5.0.3/apss_proc/out/proprietary/Wifi/qsdk-whc/* qsdk
cp -rf ../src/NHSS.QSDK.5.0.3/apss_proc/out/proprietary/Wifi/qsdk-whcpy/* qsdk

# Copying qca wifi init script
cp qsdk/package/KeyWest/kw-base-files/files/lib/wifi/qcawifi.sh qsdk/qca/feeds/qca/net/qca-wifi/files/
# Applying patch for qca wifi driver and kernel
cd qsdk/qca/src/qca-wifi/
patch -p1 < ../../../package/KeyWest/patches/patch_qca_wifi
cd ../qca-edma/
patch -p1 < ../../../package/KeyWest/patches/patch-qca-edma
cd ../qca-ssdk/
patch -p1 < ../../../package/KeyWest/patches/patch-qca-ssdk
cd ../linux-3.14
patch -p1 < ../../../package/KeyWest/patches/patch-keywest-linux-3.14
cd ../../../../
# Applying patches for feeds directories
cd qsdk/qca/feeds/
# Applying patch for Hyfi
cd hyfi/
patch -p1 < ../../../package/KeyWest/patches/patch-qca-hyfi
cd ../
# Applying patch for Hyfi Security
cd ieee1905-security/
patch -p1 < ../../../package/KeyWest/patches/patch-qca-ieee1905-security
cd ../
# Applying patch for WHC
cd whc
patch -p1 < ../../../package/KeyWest/patches/patch-qca-whc
cd ../
cd ../../../

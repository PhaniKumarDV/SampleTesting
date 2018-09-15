
#Set Rate dynamically

rate=$(uci get wireless.wifi1.rate)
acrate=$rate
case $rate in
0)
arate="6M"
nrate="0x80808080";;
1)
arate="9M"
nrate="0x81818181";;
2)
arate="12M"
nrate="0x82828282";;
3)
arate="18M"
nrate="0x83838383";;
4)
arate="24M"
nrate="0x84848484";;
5)
arate="36M"
nrate="0x85858585";;
6)
arate="48M"
nrate="0x86868686" ;;
7)
arate="54M"
nrate="0x87878787";;
8)
arate="54M"
nrate="0x88888888";;
9)
arate="54M"
nrate="0x89898989";;
10)
arate="54M"
nrate="0x8A8A8A8A";;
11)
arate="54M"
nrate="0x8B8B8B8B";;
12)
arate="54M"
nrate="0x8C8C8C8C";;
13)
arate="54M"
nrate="0x8D8D8D8D";;
14)
arate="54M"
nrate="0x8E8E8E8E";;
15)
arate="54M"
nrate="0x8F8F8F8F";;
16);;
17);;
18);;
19);;
*)
arate="auto"
nrate="0"
acrate="21";;
esac


opmode=$(uci get wireless.wifi1.hwmode)
case $opmode in
   11a)
      iwconfig ath1 rate $arate ;;
   11na)
      iwpriv ath1 set11NRates "$nrate" ;;
   11ac)
      iwpriv ath1 vhtmcs "$acrate" ;;
esac

#Set Power dynamically
pow=$(uci get wireless.wifi1.TXPowLim5G)
pow5G=`expr $pow \* 2`
iwpriv wifi1 TXPowLim5G $pow5G

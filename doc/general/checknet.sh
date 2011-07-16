#!/bin/bash
#echo -n "which nic?"
#read eth
eth="eth0"
echo "the nic is "$eth
echo -n "how much seconds:"
read sec
echo "duration is "$sec" seconds, wait please..."

while [ 1 ]
do
outfirst=$(awk '/'$eth'/{print $2 }' /proc/net/dev)
sleep $sec"s"
outend=$(awk '/'$eth'/{print $2 }' /proc/net/dev)
sum=$(($outend-$outfirst))
aver=$(($sum/$sec))
echo "avrage :["$aver"]bytes/sec"
done

mkdir -p /var/run/wpa_supplicant
rmmod ar6000.ko
insmod ar6000.ko
sleep 1
ifconfig wlan0 up 192.168.3.33 netmask 255.255.255.0
sleep 1
wpa_supplicant -B -iwlan0 -c /root/wifi_tools/tkip.conf 


route -n
echo ""
route del default
route add default gw 192.168.3.198 wlan0
echo ""
route -n


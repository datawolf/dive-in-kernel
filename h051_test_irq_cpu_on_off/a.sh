#!/usr/bin/env bash

a=0
while [ $a -lt 20 ];
do
	echo 0 >  /sys/devices/system/cpu/cpu0/online
	echo 1 >  /sys/devices/system/cpu/cpu0/online
	echo 0 >  /sys/devices/system/cpu/cpu2/online
	echo 1 >  /sys/devices/system/cpu/cpu2/online
	sleep 1
done

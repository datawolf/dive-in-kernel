#!/usr/bin/env bash
set -x
a=0

while [ $a -lt 2000 ];
do
	insmod ./sched_bug.ko
	rmmod ./sched_bug.ko
        a=$(($a+1))
done

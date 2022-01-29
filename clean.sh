#!/usr/bin/env bash

for file in `ls .`
do
	if [ -d $file ]
	then
		echo "Clean directory "$file "......."
		cd $file
		make clean > /dev/null
		cd -
		echo "Clean directory "$file "....... done."
	fi
done

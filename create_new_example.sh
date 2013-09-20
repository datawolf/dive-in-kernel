#!/bin/env bash

# This shell scripte create a new directory which name is $1
# and also create two files.
# 
# one file is Makefile
# the another file is a c source file
# 
# then we can change the c file to complete some job.
# and type "make" to compile the module.
# 
# author: datawolf (wanglong@cse.buaa.edu.cn, wanglong@l-cloud.org)

if [ $# -lt 2 ]; then
	echo "Usage: $0 dirname module_name"
	exit 1
fi

DIR=$1
MODULE=$2

# copy the hello example 
cp -r ./001_hello_api  $DIR 
cd $DIR

# change the source file name and the Makefile
mv hello.c ${MODULE}.c
sed -i "s/hello/${MODULE}/g" ${MODULE}.c
sed -i "s/hello/${MODULE}/g" Makefile

cd -


#!/bin/bash

op="$1"
build_dir="build"

if [ "$op" = "clean" ]; then
	rm -rf $build_dir
	exit 0;
fi


dpkg -s cmake &> /dev/null
if [ $? -eq 0 ]; then
    echo "Package  is installed!"
else  
    apt install cmake -y
    echo "Package  is NOT installed!"
fi


mkdir $build_dir
cd $build_dir
cmake ..
make 
make install
cd output/bin


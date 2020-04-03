#!/bin/bash

op="$1"
build_dir="build"
bin_dir="$build_dir/output/bin"
bin_name="$bin_dir/assignment4"

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

dpkg -s glib2.0 &> /dev/null
if [ $? -eq 0 ]; then
    echo "Package  is installed!"
else  
    apt install glib2.0 --fix-missing -y
    echo "Package  is NOT installed!"
fi


mkdir -p $build_dir
pushd $build_dir
cmake ..
make 
popd
#make install
$bin_name


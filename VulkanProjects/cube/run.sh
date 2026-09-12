#!/usr/bin/env bash 



BUILD="build"



if [ -d "$BUILD" ] ; then
	cd build
	make
	cd ..
else
	mkdir build
	cd build
	cmake ..
	make
	cd ..

fi

./build/res

rm -rf build






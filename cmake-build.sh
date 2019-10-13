#!/bin/bash

if [ ! -d "tmp" ];
then 
	mkdir tmp
fi

cd tmp
cmake ../build/cmake
make
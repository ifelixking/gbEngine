#!/bin/bash

if [ ! -d "tmp" ];
then 
	mkdir tmp
fi

cd tmp
clear
cmake ../build/cmake
make
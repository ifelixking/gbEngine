#!/bin/bash

if [ ! -d "tmp" ];
then 
	mkdir tmp
fi

cd tmp
rm -rf ./*
clear
cmake ../build/cmake
make
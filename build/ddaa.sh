#!/bin/bash


cd RTCases

rm *.ll


for fn in *.c; do

	clang-10 -O0 -g -emit-llvm  $fn -S -o $fn.ll
	
done

	



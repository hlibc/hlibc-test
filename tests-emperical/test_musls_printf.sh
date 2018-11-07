#!/bin/sh
git clone git://git.musl-libc.org/musl
cd musl
./configure --prefix=$(pwd)/usr
make -j4 > log 2>&1
make install >> log 2>&1
./usr/bin/musl-gcc -static ../printf_overflow.c
./a.out


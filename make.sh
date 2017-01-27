#!/usr/bin/bash
rel=..
if [ x"$TOP" == x ]; then TOP=`pwd`/$rel; fi
. $rel/linux-ow.sh

if [ "$1" == "clean" ]; then
    make clean
    exit 0
fi

if [[ "$1" == "build" || "$1" == "" ]]; then
    make
fi


#!/bin/bash
set -e 
#set -x
if [[ "$1" = "e" ]]; then
    rm -f CMakeCache.txt
    rm -rf CMakeFiles
fi
cmake .
make
datafile=./Data/mr1.220405.wav
echo "Processing file."
if [[ "$1" = "x" ]]; then
    gdb --args ./songbird $datafile
else
    ./songbird $datafile
fi


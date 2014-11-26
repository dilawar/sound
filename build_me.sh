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
    gdb --args ./songbird --input $datafile
else
    ./songbird --input $datafile
fi

if [[ "$1" = "plot" ]]; then
    echo "Plotting data"
    ( 
    cd data 
    files=`find . -type f -name "*.dat"`
    for file in $files; do
        ../scripts/plot.py --file $file --outfile $file.png
    done
    )
fi

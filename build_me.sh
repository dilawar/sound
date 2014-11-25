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
    ../scripts/plot.py --file before_filter.dat --length 1000 --outfile b_filter.png
    ../scripts/plot.py --file after_filter.dat -l 1000 -o a_filter.png 
    )
fi

#!/bin/bash
set -e 
set -x
cmake .
make
echo "Processing file."
if [[ "$1" = "x" ]]; then
    gdb --args ./songbird --file ./Data/Kodi/kod1.tape1A.080123.085848.wav
else
    ./songbird --file ./Data/Kodi/kod1.tape1A.080123.085848.wav
fi


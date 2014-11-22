#!/bin/bash
set -e 
#set -x
cmake .
make
echo "Processing file."
if [[ "$1" = "x" ]]; then
    gdb --args ./songbird ./Data/Kodi/kod1.tape1A.080123.085848.wav
else
    ./songbird ./Data/Kodi/kod1.tape1A.080123.085848.wav
fi


#!/bin/bash
FILE="$1"
echo "Plotting $FILE"
gnuplot <<EOF
set datafile separator ","
set xlabel "time in sec"
set ylabel "sound"
#set term eps 
#set output "${FILE}.eps"
plot "${FILE}" using 1:2 w line
EOF

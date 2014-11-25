#!/usr/bin/env python

import sys
import pylab

##
# @brief This plots CSV file data.
#
# @param data
#
# @return 
def plot(data):
    x = []
    y = []
    for line in data:
        xx, yy = line.split(",")
        x.append(float(xx))
        y.append(float(yy))
    pylab.plot(x, y)
    pylab.show()

def plotRow(file, length = -1):
    data = [[]]
    for line in file:
        row = line.split(',')[1:-1]
        if length <= 0:
            length = len(row) - 1
        data.append([float(x) for x in row[:length]])

    for d in data:
        pylab.plot(range(len(d)), d)
    pylab.show()



def main():
    filename = sys.argv[1]
    with open(filename, "r") as f:
        plotRow(f, 1000)

if __name__ == '__main__':
    main()

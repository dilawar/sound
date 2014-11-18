#!/usr/bin/env python

import sys
import pylab

def plot(data):
    x = []
    y = []
    for line in data:
        xx, yy = line.split(",")
        x.append(float(xx))
        y.append(float(yy))
    pylab.plot(x, y)
    pylab.show()

def main():
    filename = sys.argv[1]
    with open(filename, "r") as f:
        plot(f)

if __name__ == '__main__':
    main()

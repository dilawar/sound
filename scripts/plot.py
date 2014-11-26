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

def plotRow(args):
    data = []
    filename = args.outfile
    length = args.length
    txt = filter(None, args.file.read().split("\n"))
    indexVec = txt[0].split(",")[1:-1]
    if length <= 0:
        length = len(indexVec) - 1

    indexRow = [ float(x) for x in indexVec[:length] ]
    
    for line in txt[1:]:
        row = line.split(',')[1:-1]
        data.append([float(x) for x in row[:length]])

    for d in data:
        pylab.plot(indexRow, d)
    if not filename:
        pylab.show()
    else:
        print("INFO: Saving plot to %s " % filename)
        pylab.savefig(filename)



def main():
    import argparse
    # Argument parser.
    description = '''Plot data stored in a file'''
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('--file', '-f'
            , required = True
            , type = argparse.FileType('r')
            , help = 'File to plot'
            )
    parser.add_argument('--length', '-l'
            , required = False
            , default = -1
            , type = int
            , help = "No of points to plot"
            )
    parser.add_argument('--outfile', '-o'
            , required = False
            , default = None
            , type = argparse.FileType('w')
            , help = "Output file"
            )

    class Args: pass 
    args = Args()
    parser.parse_args(namespace=args)
    plotRow(args)

if __name__ == '__main__':
    main()

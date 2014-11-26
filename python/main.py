import aifc 
import sys
import numpy as np
from scipy import signal 
import pylab

samplingFreq = 0

def readAifData(file):
    global samplingFreq
    print("INFO : Reading %s " % file)
    f = aifc.open(file, "r") 
    samplingFreq = f.getframerate()
    nframes = f.getnframes()
    strData = f.readframes(nframes)
    data = np.fromstring(strData, np.short).byteswap()
    data = data[~np.isnan(data)]
    return data

def filterData(data):
    b, a = signal.butter(4, [100.0/samplingFreq, 12000.0/samplingFreq], 'bandpass')
    ft = signal.lfilter(b, a, data)
    pylab.plot(data)
    pylab.plot(ft)
    pylab.show()
    

def main():
    file = sys.argv[1]
    data = readAifData(file)
    filterData(data)

if __name__ == '__main__':
    main()

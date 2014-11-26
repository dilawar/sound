import aifc 
import sys
import numpy as np
from scipy import signal 
import pylab

samplingFreq = 0
windowSize = 4096

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
    b, a = signal.butter(4, 15000/samplingFreq, 'highpass')
    ft = signal.lfilter(b, a, data)
    return ft

def spectogram(data, **kwargs):
    print("INFO: Computing spectogram: samplingFreq %s " % samplingFreq)
    Pxx, freqs, bins, im = pylab.specgram(
            data, windowSize, samplingFreq
            , window = pylab.window_hanning
            )

    pylab.show()


    

def main():
    file = sys.argv[1]
    data = readAifData(file)
    data = filterData(data)
    spectogram(data)

if __name__ == '__main__':
    main()

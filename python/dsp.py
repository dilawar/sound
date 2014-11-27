
"""dsp.py: All DSP related stuff

Last modified: Sat Jan 18, 2014  05:01PM

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2013, Dilawar Singh and NCBS Bangalore"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

from scipy import signal 
import pylab

def filterData(data, samplingFreq, **kwargs):
    windowSize = kwargs.get("window_size", 4300)
    b, a = signal.butter(4, 15000/samplingFreq, 'highpass')
    ft = signal.lfilter(b, a, data)
    return ft

def spectogram(data, samplingFreq,  **kwargs):
    print("INFO: Computing spectogram: samplingFreq %s " % samplingFreq)
    windowSize = kwargs.get("window_size", 4300)
    Pxx, freqs, bins, im = pylab.specgram(data, windowSize, samplingFreq 
            , window = pylab.window_hanning
            )
    pylab.show()
    



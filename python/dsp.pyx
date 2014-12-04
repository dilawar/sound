
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
import globals as g

cpdef filterData(data, samplingFreq, windowSize = 4300):
    b, a = signal.butter(6, [2000/samplingFreq, 15000/samplingFreq], 'bandpass')
    ft = signal.lfilter(b, a, data)
    return ft

cpdef spectogram(data, samplingFreq, output=None):
    g.logger.info("Computing spectogram: samplingFreq %s " % samplingFreq)
    nfft = 256
    Pxx, freqs, bins, im = pylab.specgram(
            data
            , Fs = samplingFreq 
            , NFFT = nfft
            , window = pylab.window_hanning
            )
    filename = output
    if filename:
        g.logger.info("Saving spectogram to %s" % filename)
        pylab.savefig(filename)
    return (Pxx, freqs, bins, im)
    



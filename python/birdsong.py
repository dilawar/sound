"""birdsong.py: 

    Process the data in birdsong.

Last modified: Fri Nov 28, 2014  12:10AM

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2013, Dilawar Singh and NCBS Bangalore"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import globals as g
import logging
import dsp 
import cv2
import numpy as np
import pylab
import algorithms

class BirdSong():

    def __init__(self, data):
        self.data = data
        self.imageMat = None
        self.frequencies = None
        self.image = None
        self.imageH = None
        self.filename = "spectogram.png"

    def processData(self, **kwargs):
        g.logger.info("STEP: Processing the speech data")
        length = kwargs.get("sample_size", len(self.data) - 1 )
        g.logger.info("Processing %s samples" % length)
        data = self.data[:length]
        #data = dsp.filterData(data, g.sampling_freq)
        self.Pxx, self.frequencies, self.bins, self.imageH = dsp.spectogram(
                data
                , g.sampling_freq
                , output = None #"spectogram.png"
                )
        self.imageMat = self.imageH.get_array()
        self.imageH.write_png(self.filename)
        self.getNotes()

    def getNotes(self, **kwargs):
        g.logger.info("Read image in GRAYSCALE mode to detect edges")
        self.image = cv2.imread(self.filename, 0)
        algorithms.findPointsOnTheEdges(self.image)
        
        # Changes the data-type to opencv format.
        #res1 = cv2.GaussianBlur(self.image, (7,7), 0)
        #res2 = cv2.GaussianBlur(self.image, (3,3), 0)
        #edges = self.image - res2
        #pylab.imshow(edges)
        #pylab.show()
        #pylab.imshow(res2)
        #pylab.show()


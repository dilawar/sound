"""birdsong.py: 

    Process the data in birdsong.

Last modified: Sat Nov 29, 2014  06:34PM

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
import scipy
import numpy as np
import pylab
import algorithms

import time 
import datetime
import os
st = time.time()
stamp = datetime.datetime.fromtimestamp(st).strftime('%Y-%m-%d-%H%M')

class BirdSong():

    def __init__(self, data):
        self.data = data
        self.imageMat = None
        self.frequencies = None
        self.image = None
        self.croppedImage = None
        self.notesImage = None
        self.imageH = None
        self.filename = "spectogram.png"
        self.notes = []

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
        pylab.close()
        self.getNotes()
        #self.plotNotes("notes.png", createTimeStampDir = True)
        self.plotNotes(filename = None, createTimeStampDir = True)

    def getNotes(self, **kwargs):
        g.logger.info("Read image in GRAYSCALE mode to detect edges")
        self.image = cv2.imread(self.filename, 0)
        minPixelVal = int(g.config.get('note', 'maxval_startpixel'))
        if int(g.config.get('global', 'autocrop')) != 0:
            threshold = int(g.config.get('global', 'threshold'))
            self.croppedImage = algorithms.autoCrop(self.image, threshold)
        else:
            self.croppedImage = self.image
        img = np.copy(self.croppedImage)
        self.notes = algorithms.notes(img)

    def createDataDirs(self, createTimeStampDir = True):
        basedir = '_output'
        if not os.path.isdir(basedir):
            os.makedirs(basedir)
        if createTimeStampDir:
            dirpath = os.path.join(basedir, stamp)
            if not os.path.isdir(dirpath): os.makedirs(dirpath)
            else:
                dirpath = '_output'
        return dirpath

    def plotNotes(self, filename = None, createTimeStampDir = True):
        # Plot the notes.
        fig = pylab.figure()
        ax1 = fig.add_subplot(211)
        ax2 = fig.add_subplot(212)
        self.notesImage = np.empty(shape=self.croppedImage.shape, dtype=np.int8)
        titleText = [ "{}:{}".format(va[0], va[1]) for va in (g.config.items('note'))]
        ax1.set_title(" ".join(titleText))
        self.notesImage.fill(255)
        for note in self.notes:
            note.plot(self.notesImage)
        ax2.imshow(self.croppedImage)
        ax1.imshow(self.notesImage, cmap=pylab.gray())
        if not filename:
            pylab.show()
        else:
            dirpath = self.createDataDirs(createTimeStampDir)
            filename = os.path.join(dirpath, filename)
            g.logger.info("Saving notes and image to %s" % filename)
            pylab.savefig(filename)

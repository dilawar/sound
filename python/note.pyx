
"""note.py: Class representing a note.

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

import scipy
import numpy as np
import cv2

cdef class Note:

    cdef object origin, points, xpoints, ypoints, hull
    cdef double energy, width, height

    def __cinit__(self, x, y):
        self.origin = (x, y)
        self.energy = 0.0
        self.width = 0.0
        self.height = 0.0
        self.hull = None
        self.points = []
        self.xpoints = []
        self.ypoints = []

    def computeAll(self, image):
        self.width = self.xpoints.max() - self.xpoints.min()
        self.height = self.ypoints.max() - self.ypoints.min()
        for p in self.points:
            self.energy += image[p[0], p[1]] 

    def __repr__(self):
        msg = "Start: {}, energy {}, width {}, height {}".format(
                self.origin
                , self.energy
                , self.width
                , self.height
                )
        return msg

    def addPoint(self, point):
        x, y = point
        self.xpoints.append(x)
        self.ypoints.append(y)
        self.points.append(point)

##
# @brief Plot the note. We need to change the index of points before using
# fillConvexPoly function.
#
# @param img Image onto which points needs to be plotted.
# @param kwargs
#
# @return None.
    def plot(self, img, **kwargs):
        points = [[p[1], p[0]] for p in self.points]
        points = np.asarray(points)
        cv2.fillConvexPoly(img, points, 1)



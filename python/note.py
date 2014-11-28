
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

class Note:

    def __init__(self, x, y):
        self.origin = (x, y)
        self.energy = 0.0
        self.area = 0.0
        self.width = 0.0
        self.hight = 0.0
        self.hull = None
        self.points = []

    def __repr__(self):
        self.hull = scipy.spatial.ConvexHull(self.points)
        msg = "Start: {}, hull {}".format(
                self.origin
                , self.hull
                )
        return msg

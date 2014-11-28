"""algorithms.py: 

    All of my algorithms to detect pattern in image should be here.

Last modified: Fri Nov 28, 2014  11:16PM

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
import pylab
import cv2
import numpy as np
import note

##
# @brief Delete the rows. These rows do not contain any pixel darker (less than)
# the threshold.
#
# @param image numpy matrix.
# @param threshold threshold value of pixel.
# @param kwargs
#
# @return  Image with deleted rows.
def deleteRows(image, threshold, **kwargs):
    """Delete rows which do not have any pixel less than the given value"""
    rowsToDelete = []
    newImage = []
    for i, row in enumerate(image):
        if row.min() < threshold:
            newImage.append(row)
        else:
            # This row does not contain any signal. So screw it. 
            # NOTE: This works because it is almost guaranteed that you almost
            # always find continous block of such rows to remove and never
            # one or two rows in between.
            pass
    return np.array(newImage)
    
def searchForPixels(image, pixelVal, **kwargs):
    """Search for all pixels of a given value in image """
    pixels = []
    for i, row in enumerate(image):
        for j, v in enumerate(row):
            if v == pixelVal:
                pixels.append((i,j))
    assert len(pixels) > 0, "There must be at least one pixel of value %s" % pixelVal
    return pixels

def findNotes(image, **kwargs):
    """Find notes in the given image """
    g.logger.info("Find notes in the image")
    # 1. Find the lowest pixel (darkest one) x.
    # 2. Use slithrine algorithm to get the note.
    # 3. Delete the note from the figure (make all pixel equal to 255).
    # 4. Go to step 1.
    minPixel = image.min()
    maxvalOfStartPixel = int(g.config.get('note', 'maxval_startpixel'))
    while minPixel < maxvalOfStartPixel:
        minPixel = image.min()
        print("Searching for pixels with value %s" % minPixel)
        startPixels = searchForPixels(image, minPixel)
        print startPixels
        while startPixels:
            x, y = startPixels.pop()
            g.logger.debug("Finding notes with starting point {} val {}".format(
                (x, y), minPixel)
                )
            if image[x, y] == minPixel:
                note = slither(x, y, minPixel, image)
                if note:
                    g.logger.info("Found a note")
                    print note
            else:
                g.logger.debug("This pixel is already part of some note")
    pylab.imshow(image)
    pylab.show()


##
# @brief Main algorithm to detect the note.
#
# @param x x pos in image.
# @param y y post in image.
# @param image
#
# @return 
def slither(startx, starty, startValue, image, threshold = 40):
    n = note.Note(startx, starty)
    points = []
    points.append([startx, starty])
    while points:
        x, y = points.pop()
        n.points.append([x,y])
        image[x, y] = 255
        for a in [x-1, x, x+1]:
            for b in [y-1, y, y+1]:
                if (image[a, b] - startValue) < threshold:
                    points.append([a, b])
                    image[a, b] = 255
                    n.points.append([a, b])
    if len(n.points) < 50:
        g.logger.debug("Not enough points in this note. Rejecting")
        return None
    return n

##
# @brief Find points which belongs to different edges.
#
# @param data Image matrix.
#
# @return 
def findPointsOnTheEdges(image):
    g.logger.info("Find points on the image which belongs to edges")
    image = deleteRows(image, 120)
    # By now we have removed all the rows which do not have any interesting
    # pixels. This has reduced our search size. Now in this matrix, we need to
    # locate islands which belongs to notes. The islands must be separated by
    # some no which we do not know.
    notes = findNotes(image)
    #pylab.imshow(image)
    #pylab.show()


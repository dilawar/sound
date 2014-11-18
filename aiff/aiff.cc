/*
 * ==============================================================================
 *
 *       Filename:  aiff.cpp
 *
 *    Description:  Class to open a file.
 *
 *        Version:  1.0
 *        Created:  11/18/2014 12:18:52 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  
 *
 * ==============================================================================
 */

#include "aiff.h"

/*
 *-------------------------------------------------------------------------------
 *       Class:  Aiff
 *      Method:  Aiff
 * Description:  constructor
 *-------------------------------------------------------------------------------
 */
Aiff::Aiff ()
{
    
}  /* -----  end of method Aiff::Aiff  (constructor)  ----- */


/*
 *-------------------------------------------------------------------------------
 *       Class:  Aiff
 *      Method:  ~Aiff
 * Description:  destructor
 *-------------------------------------------------------------------------------
 */
Aiff::~Aiff ()
{
}  /* -----  end of method Aiff::~Aiff  (destructor)  ----- */


void Aiff::openFile(char* filename)
{
    cerr << "Opening " << filename << endl;
    return;
}

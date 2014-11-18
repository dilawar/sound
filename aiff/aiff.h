/*
 * ==============================================================================
 *
 *       Filename:  aiff.h
 *
 *    Description:  Class to read aiff file.
 *
 *        Version:  1.0
 *        Created:  11/18/2014 12:17:57 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  
 *
 * ==============================================================================
 */


#ifndef  AIFF_INC
#define  AIFF_INC

#include <iostream>

using namespace std;

class Aiff
{
    public:
        Aiff();
        ~Aiff();

    public:
        void openFile(char* filename);

};

#endif   /* ----- #ifndef AIFF_INC  ----- */

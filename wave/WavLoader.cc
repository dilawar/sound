/*
 * ==============================================================================
 *
 *       Filename:  WavLoader.cc
 *
 *    Description:  Load WAV file using library.
 *
 *        Version:  1.0
 *        Created:  11/19/2014 05:18:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  
 *
 * ==============================================================================
 */


#include "WavLoader.h"
#include <string>

using namespace std;

/*
 *-------------------------------------------------------------------------------
 *       Class:  WavLoader
 *      Method:  WavLoader
 * Description:  constructor
 *-------------------------------------------------------------------------------
 */
WavLoader::WavLoader ()
{
    
}  /* -----  end of method WavLoader::WavLoader  (constructor)  ----- */

/*
 *-------------------------------------------------------------------------------
 *       Class:  WavLoader
 *      Method:  ~WavLoader
 * Description:  destructor
 *-------------------------------------------------------------------------------
 */
WavLoader::~WavLoader ()
{
}  /* -----  end of method WavLoader::~WavLoader  (destructor)  ----- */


WavLoader::WavLoader(string filepath)
{
    Aquila::WaveFile wav(filepath);
}


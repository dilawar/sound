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
#include "global.h"
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
    DUMP("Reading WAV file " << filepath , "DEBUG");
    wav.readWavFile(filepath, _data, false); 
}

/**
 * @brief Save the data to a text file in csv file.
 *
 * @param outfile
 */
void WavLoader::saveData(string outfile)
{


#if  0     /* ----- #if 0 : If0Label_1 ----- */
    DUMP("Saving data to " << outfile, "DEBUG");
    ofstream outf(outfile);
    unsigned int i = 0;
    for(auto it = _data.begin(); it != _data.end(); ++it)
    {
        outf << i*(1.0/samplingF) << "," << *it << endl;
        i += 1;
    }
    outf.close();
#endif     /* ----- #if 0 : If0Label_1 ----- */


}


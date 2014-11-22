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
    delete pWav;
}  /* -----  end of method WavLoader::~WavLoader  (destructor)  ----- */


WavLoader::WavLoader(string filepath)
{
    pWav = new Aquila::WaveFile(filepath);

    stringstream s;
    s << "Filename: "           << pWav->getFilename();
    s << endl << "Length: "           << pWav->getAudioLength()     << " ms";
    s << endl << "Sample frequency: " << pWav->getSampleFrequency() << " Hz";
    s << endl << "Channels: "         << pWav->getChannelsNum();
    s << endl << "Byte rate: "        << pWav->getBytesPerSec()/1024 << " kB/s";
    s << endl << "Bits per sample: "  << pWav->getBitsPerSample() << "b";
    s << endl << "Total frames: " << pWav->getSamplesCount();
    DUMP(s.str(), "INFO");

    for(auto it = pWav->begin(); it != pWav->end(); ++it)
        _data.push_back(*it);

}

/**
 * @brief Save the data to a text file in csv file.
 *
 * @param outfile
 */
void WavLoader::saveData(string outfile)
{

    DUMP("Saving data to " << outfile, "DEBUG");

    ofstream outf(outfile);
    unsigned int i = 0;
    unsigned int samplingF = pWav->getSampleFrequency();

    for(auto it = _data.begin(); it != _data.end(); ++it)
    {
        outf << i*(1.0/samplingF) << "," << *it << endl;
        i += 1;
    }

    outf.close();
}


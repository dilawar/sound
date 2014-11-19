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
#include <boost/log/trivial.hpp>
#include <string>

using namespace std;
using namespace boost;

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


    BOOST_LOG_TRIVIAL(info) << "Filename: "           << pWav->getFilename();
    BOOST_LOG_TRIVIAL(info) << "Length: "           << pWav->getAudioLength()     << " ms";
    BOOST_LOG_TRIVIAL(info) << "Sample frequency: " << pWav->getSampleFrequency() << " Hz";
    BOOST_LOG_TRIVIAL(info) << "Channels: "         << pWav->getChannelsNum();
    BOOST_LOG_TRIVIAL(info) << "Byte rate: "        << pWav->getBytesPerSec()/1024 << " kB/s";
    BOOST_LOG_TRIVIAL(info) << "Bits per sample: "  << pWav->getBitsPerSample() << "b";

    BOOST_LOG_TRIVIAL(info) << "Collecting data into vector" << endl;

    for(auto it = pWav->begin(); it != pWav->end(); ++it)
        _data.push_back(*it);

    BOOST_LOG_TRIVIAL(debug) << "Total " << _data.size() << " samples.";
}

/**
 * @brief Save the data to a text file in csv file.
 *
 * @param outfile
 */
void WavLoader::saveData(string outfile)
{

    BOOST_LOG_TRIVIAL(info) << "Saving data to " << outfile;

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


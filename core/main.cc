/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  This is our main file.
 *
 *        Version:  1.0
 *        Created:  Sunday 05 September 2010 09:44:39  IST
 *       Revision:  none
 *       Compiler:  g++/gcc
 *
 *         Author:  Dilawar (nuts), dilawar[AT]ee[dot]iitb[dot]ac[dot]in
 *      Institute:  Indian Institute of Technology, Bombay
 *
 * This material is released under GNU Lesser Public License.
 * You are free to copy, distribute or use it for any non-commercial activity.
 * But you are not allowed to modify it. If you are a student, you can use its
 * part in your work with or without mentioning it.
 *
 * For additional details, please see the GNU Lesser Public license.
 *
 * NOTE : No propriety software is used in this material.
 * Almost all of the code is written and modified in VIM editor with c-support
 * plugin which is more awesome than Kung Fu Panda. Just kidding, no one is more
 * awesome than Kung Fu Panda with or without a light saber.
 *
 * This program is made using a bit for here,  a bit from there under the influence
 *  of a lot of burnt out neurons.
 * Report bugs : dilawar.in@gmail.com
 * =====================================================================================
 */
#define EXIT_SUCCESS    1
#define EXIT_FAILURE    0
#define TRUE            1
#define FALSE           0

#include "WavLoader.h"
#include "dsp.h"
#include "global.h"
#include <stdexcept>


#include <boost/program_options.hpp>
#include <boost/program_options/parsers.hpp>

using namespace std;

int main(int argc, char** argv)
{

#ifdef ENABLE_UNIT_TESTS
    DUMP("TESTING DSP MODULE", "TEST");
    test_dsp();
    return 0;
#endif

    namespace po = boost::program_options;


    /*
     * Options allowed on command line.
     */
    po::options_description generic("Allowd options for songbird");
    generic.add_options()
        ("help", "Produce this help message")
        ("input", po::value<std::string>(), "load from data file")
        ;
    po::store(po::parse_command_line(argc, argv, generic), prgOptions);

    ifstream ifs(CONFIG_FILE);

    po::options_description config("Options in configuration file.");
    unsigned int cutoff_low, cutoff_high;
    config.add_options()
        ("filter.cutoff_low"
            , po::value<unsigned int>(&cutoff_low)
            , "Low cutoff frequency"
            )
        ("filter.cutoff_high"
            , po::value<unsigned int>(&cutoff_high)
            , "High cufoff frequency"
            )
        ;

    if(!ifs)
    {
        DUMP("No configuration file " << CONFIG_FILE << "found.", "WARN");
        throw runtime_error("Configuration file missing");
    }
    else
    {
        po::store(po::parse_config_file(ifs, config), prgOptions);
        ifs.close();
    }


    po::notify(prgOptions);

    if(prgOptions.count("help"))
        cout << generic << endl;

    string filename;
    if(prgOptions.count("input"))
    {
        DUMP( "Input filename is set to " << prgOptions["input"].as<string>() << endl
                , "DEBUG"
            );
        filename = prgOptions["input"].as<string>();
    }
    else
    {
        cout << generic << endl;
        return EXIT_SUCCESS;
    }

    DUMP( "Opening file " << filename, "INFO");
    WavLoader wavLoader = WavLoader(filename);

    vector<double> filteredData(wavLoader._data.size());
    bandpass(wavLoader._data
            , filteredData
            , prgOptions["filter.cutoff_low"].as<unsigned int>()
            , prgOptions["filter.cutoff_high"].as<unsigned int>()
            , wavLoader.wav.getSampleRateHz()
            );
    DUMP("Signal is filtered.", "DEBUG");
}



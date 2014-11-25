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

using namespace std;

int main(int argc, char** argv)
{

#ifdef ENABLE_UNIT_TESTS
    DUMP("TESTING DSP MODULE", "TEST");
    test_dsp();
#endif

    /*
     * This snippet is from here 
     *   
     */
    boost::program_options::options_description d("Allowed options for songbird");
    d.add_options()
        ("help", "Produce this help message")
        ("input", boost::program_options::value<std::string>(), "load from data file")
        ;

    boost::program_options::variables_map m;
    boost::program_options::store(boost::program_options::parse_command_line(
                argc, argv, d), m
            );
    boost::program_options::notify(m);

    if(m.count("help"))
        cout << d << endl;

    string filename;
    if(m.count("input"))
    {
        DUMP( "Input filename is set to " << m["input"].as<string>() << endl
                , "DEBUG"
            );
        filename = m["input"].as<string>();
    }
    else
    {
        cout << d << endl;
        return EXIT_SUCCESS;
    }

    DUMP( "Opening file " << filename, "INFO");

    WavLoader wavLoader = WavLoader(filename);

#if SAVE_DATA
    wavLoader.saveData(filename+".dat");
#endif
    vector<double> filteredData;
    bandpass(wavLoader._data, filteredData, 1500, 10300, wavLoader.wav.getSampleRateHz());
    DUMP("Signal is filtered.", "DEBUG");
}



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
#include "dsp/dsp.h"
#include "global.h"
#include <boost/program_options.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>

using namespace std;
namespace logging = boost::log;

void init()
{
    logging::core::get()->set_filter
        (
         logging::trivial::severity >= logging::trivial::debug
        );
}


int test_main(int argc, char** argv)
{
    init();

    namespace po = boost::program_options;

    po::options_description desc("Allowed options");

    desc.add_options()
        ("help", "Produce help message")
        ("file", po::value<string>(), "Input sound file (wav format)")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help"))
    {
        cout << desc << endl;
        return 1;
    }

    if(vm.count("file"))
    {
        BOOST_LOG_TRIVIAL(info) << "Input file : " << vm["file"].as<string>() << endl;
    }
    else
    {
        BOOST_LOG_TRIVIAL(fatal) << "No input file provided" << endl;
        return 0;
    }

    /* Read WAVE file */
    string fileName = vm["file"].as<string>();

    WavLoader wavLoader = WavLoader(fileName);

//    wavLoader.saveData(fileName+".dat");

    vector<double> filteredData;
    bandpass(wavLoader._data, filteredData, 1500, 10300, wavLoader.pWav->getSampleFrequency());
}



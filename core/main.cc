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

using namespace std;

int main(int argc, char** argv)
{
    string filename = string(argv[1]);
    DUMP( "Opening file " << filename, "INFO");

    WavLoader wavLoader = WavLoader(filename);

#if SAVE_DATA
    wavLoader.saveData(filename+".dat");
#endif

    vector<double> filteredData;
    bandpass(wavLoader._data, filteredData, 1500, 10300, wavLoader.pWav->getSampleFrequency());
    DUMP("Signal is filtered.", "DEBUG");
}



/*
 * ==============================================================================
 *
 *       Filename:  WavLoader.h
 *
 *    Description:  Class to load a Wave file.
 *
 *        Version:  1.0
 *        Created:  11/19/2014 08:41:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  
 *
 * ==============================================================================
 */

#ifndef  WAVLOADER_INC
#define  WAVLOADER_INC

#include <string>

#include "aquila/source/WaveFile.h"

using namespace std;

/**
 * @brief Class to load WaveFile using Aquila.
 */
class WavLoader
{
    public:
        WavLoader();
        WavLoader(string filepath);

        ~WavLoader();

    private:
        /* data */
};

#endif   /* ----- #ifndef WAVLOADER_INC  ----- */

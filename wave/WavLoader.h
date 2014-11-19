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
#include <vector>

#include "aquila/aquila.h"

using namespace std;

/**
 * @brief Class to load WaveFile using Aquila.
 */
class WavLoader
{
    public:

        WavLoader();
        ~WavLoader();

        WavLoader(string filepath);

        /**
         * @brief Save data to a file.
         *
         * @param outputfilename
         */
        void saveData(string outputfilename);

    private:
        /* data */

    public:

        /**
         * @brief A vector to store the data.
         */
        vector<double> _data;

        Aquila::WaveFile* pWav;

};

#endif   /* ----- #ifndef WAVLOADER_INC  ----- */

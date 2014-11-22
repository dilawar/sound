/*
 * ==============================================================================
 *
 *       Filename:  dsp.cc
 *
 *    Description:  DSP processing on vector of data.
 *
 *        Version:  1.0
 *        Created:  11/18/2014 10:04:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  
 *
 * ==============================================================================
 */


#include "dsp.h"
#include "global.h"
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;

/**
 * @brief A bandpass filter to remove the noise.
 * 
 * @param  Vector of data.
 * @param  Cutoff A.
 * @param  Cutoff B.
 * @param  Sampling frequency.
 */
int bandpass(
        vector<double>& data
        , vector<double>& outData
        , unsigned int cutoffA
        , unsigned int cutoffB
        , const size_t samplingFrequency
        )
{
    size_t SIZE = data.size();

    if(SIZE % 2 != 0)
    {
        DUMP("Not a multiple of 2. Erasing one element from data", "INFO");
        SIZE -= 1;
        data.erase(data.end());
    }

    DUMP("Cutoff (" << cutoffA << "," << cutoffB << ") sampling freq  " 
            << samplingFrequency << " Total samples " << SIZE
            , "INFO"
        );

    double* arrayData;
    arrayData = new double[SIZE+1];

    unsigned int i = 0;
    for(auto it = data.begin(); it != data.end(); it++)
    {
        arrayData[i] = *it;
        i++;
    }

    EXPECT_EQ(i, SIZE, "Unequal size data");

   return EXIT_SUCCESS;
}

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


#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_halfcomplex.h>

#include "dsp.h"
#include "global.h"
#include "plot.h"

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
    double timePeriod = 1.0 / samplingFrequency;

    double* arrayData,  * filter;
    arrayData = new double[SIZE];
    filter = new double[SIZE];

    unsigned int i = 0;
    for(auto it = data.begin(); it != data.end(); it++)
    {
        arrayData[i] = *it;
        i++;
    }

    /* Compute FFT here */
    gsl_fft_real_wavetable* real;
    gsl_fft_halfcomplex_wavetable * hc;
    gsl_fft_real_workspace * work;

    work = gsl_fft_real_workspace_alloc(SIZE);
    real = gsl_fft_real_wavetable_alloc(SIZE);
    gsl_fft_real_transform(arrayData, 1, SIZE , real, work);

    /* Multiply the fft of signal with filter. This multiplication in frequency
     * domain is equal to convolution in frequency domain.
     */

    /* Transform the singal back to time domain */
    hc = gsl_fft_halfcomplex_wavetable_alloc(SIZE);
    gsl_fft_halfcomplex_inverse(arrayData, 1, SIZE, hc, work);
    gsl_fft_halfcomplex_wavetable_free(hc);

#ifdef  VERIFY
    for(int i = 0; i < 100; i++)
        EXPECT_EQ(arrayData[i], data[i], "Must be same");
#endif     /* -----  VERIFY  ----- */

    return EXIT_SUCCESS;
}


#ifdef  ENABLE_UNIT_TESTS

/**
 * @brief This function tests the dsp module.
 */
void test_dsp(void)
{

    /*-----------------------------------------------------------------------------
     *  Create two sinusoids 100 Hz and 10000 Hz. Add 10000 samples sampled at
     *  16000Hz together.
     *-----------------------------------------------------------------------------*/
    const unsigned int sampleSize = 10000;
    const unsigned int sampleFreq = 16000;

    const unsigned int freqA = 10;
    const unsigned int freqB = 2000;

    array<double, sampleSize> signalA, signalB, combinedSignal;

    for(unsigned int i = 0; i < sampleSize; i++)
    {
        signalA[i] = sin(PI * (freqA / sampleFreq) * i);
	signalB[i] = sin(PI * (freqB / sampleFreq) * i);
	combinedSignal[i] = signalA[i] + signalB[i];
    }

    /*  Plot this data */
    map<string, array<double, sampleSize>> dataMap;
    dataMap["combined signal"] = signalA;
    plot<array<double, sampleSize>>(dataMap, string("signalA.png"));

}

#endif     /* -----  ENABLE_UNIT_TESTS  ----- */

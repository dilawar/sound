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
 * @brief Calculate the FFT of input signal and store the result in second arg.
 *
 * @tparam T
 * @param data
 * @param outData
 *
 * @return 
 */
template<typename T>
int FFT(const T& data, T& result)
{
    const size_t SIZE = data.size();

    ASSERT_EQ(result.size(), SIZE
            , "The out-data container must be initialized to the same size as "
            " input data "
            );

    double* arrayData;
    arrayData = new double[SIZE];

    unsigned i;
    for (i = 0; i < SIZE; i++)
        arrayData[i] = data[i];

    /* Compute FFT here */
    gsl_fft_real_wavetable* real;
    gsl_fft_halfcomplex_wavetable * hc;
    gsl_fft_real_workspace * work;

    real = gsl_fft_real_wavetable_alloc(SIZE);
    work = gsl_fft_real_workspace_alloc(SIZE);

    gsl_fft_real_transform(arrayData, 1, SIZE , real, work);

    for (i = 0; i < SIZE; i++) 
        result[i] = arrayData[i];

    gsl_fft_real_workspace_free(work);

    delete[] arrayData;
}

/**
 * @brief Compute the INVERSE Fourier Transform of a signal.
 *
 * @tparam T
 * @param data Input data.
 * @param result Result.
 *
 * @return Exit status.
 */
template<typename T>
int IFFT(const T& data, T& result)
{
    gsl_fft_real_workspace * work;
    gsl_fft_halfcomplex_wavetable * hc;

    const size_t SIZE = data.size();
    ASSERT_EQ(SIZE, result.size(), "The result container must be initialized to "
            " same size as of input data" 
            );


    work = gsl_fft_real_workspace_alloc(SIZE);
    hc =  gsl_fft_halfcomplex_wavetable_alloc(SIZE);

    double* arrayData = new double[SIZE];
    for (int i = 0; i < SIZE; i++)
        arrayData[i] = data[i];

    gsl_fft_halfcomplex_inverse(arrayData, 1, SIZE, hc, work);

    for(size_t i = 0; i < SIZE; i++)
    {
        result[i] = arrayData[i];
    }

    gsl_fft_halfcomplex_wavetable_free(hc);
    gsl_fft_real_workspace_free(work);
}


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
    const int SIZE = data.size();
    outData.resize(SIZE);

    double timePeriod = 1.0 / samplingFrequency;

    double *filter, *convolvedSig; 
    filter = new double[SIZE];
    convolvedSig = new double[SIZE];

    vector<double> fftOfData(SIZE);
    FFT<vector<double>>(data, fftOfData);

    /* Multiply the fft of signal with filter. This multiplication in frequency
     * domain is equal to convolution in frequency domain.
     */
    unsigned int n1 = (unsigned int) ((double)cutoffA / samplingFrequency * SIZE);
    unsigned int n2 = (unsigned int) ((double)cutoffB / samplingFrequency * SIZE);

    for(size_t i = 0; i < SIZE; i++)
    {
        if( i >= n1 && i <= n2)
            filter[i] = 1.0;
        else
            filter[i] = 0.0;
    }

    /* Here multiply in frequency domain */
    for(size_t i = 0; i < SIZE; i++)
        fftOfData[i] = filter[i] * fftOfData[i];

    IFFT<vector<double>>(fftOfData, outData);
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
    const unsigned int sampleSize = 500;

    const double freqA = 20.0;
    const double freqB = 1000.0;

    const double sampleFreq = 4000.0;

    vector<double> timeVec, freqVec, signalA, signalB, combinedSignal;
    for(unsigned int i = 0; i < sampleSize; i++)
    {
        timeVec.push_back(i / sampleFreq);
        freqVec.push_back(i * sampleFreq / sampleSize);
        signalA.push_back(sin(2 * PI * (freqA / sampleFreq) * i));
	signalB.push_back(sin(2 * PI * (freqB / sampleFreq) * i));
	combinedSignal.push_back(signalA[i] + signalB[i]);
    }

    map<string, vector<double>> mapData;

    /* Create a filter with filtering frequency at 1000 */
    vector<double> outData;

    /* let's see the FFT of input signal here. */
    vector<double> fftOfSignalA = vector<double>(sampleSize);
    vector<double> fftOfSignalB = vector<double>(sampleSize);
    vector<double> fftOfCombinedSig = vector<double>(sampleSize);

    FFT(signalA, fftOfSignalA);
    FFT(signalB, fftOfSignalB);
    FFT(combinedSignal, fftOfCombinedSig);

    mapData["fftA"] = fftOfSignalA;
    mapData["fftB"] = fftOfSignalB;
    plotXY(freqVec, mapData, "data/fft_Of_combined.dat");

    bandpass(combinedSignal, outData, 500, 2800, sampleFreq);

    mapData.clear();
    mapData["before filter"] = combinedSignal;
    mapData["filtered"] = outData;
    plotXY(timeVec, mapData, "data/after_filter.dat");
}

#endif     /* -----  ENABLE_UNIT_TESTS  ----- */

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
#include "aquila/global.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"
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
    const size_t SIZE = data.size();

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

    /* Compute the fft of signal here  */
    EXPECT_EQ(i, SIZE, "Unequal size data");
    auto fft = Aquila::FftFactory::getFft(SIZE);
    Aquila::SpectrumType spectrum = fft->fft(arrayData);


#if  0     /* ----- #if 0 : If0Label_1 ----- */
    /* Plot before filtering */
    Aquila::TextPlot plt("Signal waveform before filtration");
    plt.plot(arrayData, SIZE);
#endif     /* ----- #if 0 : If0Label_1 ----- */

    /* Generate Aquila filter here. A */
    const Aquila::FrequencyType f_lp = cutoffA, f_hp = cutoffB;
    const Aquila::FrequencyType sampleFreq = samplingFrequency;
#if  0     /* ----- #if 0 : If0Label_2 ----- */

    Aquila::SpectrumType filterSpectrum(SIZE);
    for (std::size_t i = 0; i < SIZE; ++i)
    {
        if (i > (SIZE * f_lp / sampleFreq) && i < (SIZE * f_hp / sampleFreq))
            filterSpectrum[i] = 1.0;
        else
            filterSpectrum[i] = 0.0;
    }


    plt.setTitle("Filter spectrum");
    plt.plotSpectrum(filterSpectrum);


    /* multiply both spectrum */
    transform(
            begin(spectrum)
            , end(spectrum)
            , begin(filterSpectrum)
            , begin(spectrum)
            , [] (Aquila::ComplexType x, Aquila::ComplexType y) { return x * y;}
            );

    /* Get inverse fft */
    double* x1;
    x1 = new double[SIZE];
    fft->ifft(spectrum, x1);

    plt.setTitle("Signal after filteration");
    plt.plot(x1, SIZE);

    outData.assign(x1, x1 + SIZE);
#endif     /* ----- #if 0 : If0Label_3 ----- */

    return EXIT_SUCCESS;
}

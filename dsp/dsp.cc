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
#include <vector>
#include <array>
#include <iostream>
#include "aquila/global.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"
#include <boost/log/trivial.hpp>
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
void bandpass(
        vector<double>& data
        , unsigned int cutoffA
        , unsigned int cutoffB
        , unsigned int samplingFrequency
        , const size_t SIZE
        )
{
    BOOST_LOG_TRIVIAL(info) << "Cutoff (" << cutoffA << "," << cutoffB 
        << ") sampling freq " << samplingFrequency << endl;

    double* arrayData;
    arrayData = new double[data.size()];

    for(unsigned int i = 0; i < data.size(); i++)
        arrayData[i] = data[i];

    /* Compute the fft of signal here  */
    auto fft = Aquila::FftFactory::getFft(SIZE);

    /* Generate Aquila filter here. A */
    const Aquila::FrequencyType f_lp = cutoffA, f_hp = cutoffB;
    const Aquila::FrequencyType sampleFreq = samplingFrequency;

    Aquila::SpectrumType filterSpectrum(SIZE);
    for (std::size_t i = 0; i < SIZE; ++i)
    {
        if (i > (SIZE * f_lp / sampleFreq) && i < (SIZE * f_hp / sampleFreq))
            filterSpectrum[i] = 1.0;
        else
            filterSpectrum[i] = 0.0;
    }

    Aquila::TextPlot plt("Signal waveform before filtration");
    plt.setTitle("Filter spectrum");
    plt.plotSpectrum(filterSpectrum);

    delete[] arrayData;
}

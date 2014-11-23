/*
 * ==============================================================================
 *
 *       Filename:  dsp.h
 *
 *    Description:  Header file
 *
 *        Version:  1.0
 *        Created:  11/18/2014 10:18:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  
 *
 * ==============================================================================
 */

#ifndef  DSP_INC
#define  DSP_INC

#include <vector>

using namespace std;

int bandpass(vector<double>& data
        , vector<double>& outData
        , unsigned int cutoffA
        , unsigned int cutoffB
        , const size_t samplingFrequency
        );


#ifdef  ENABLE_UNIT_TESTS
void test_dsp();
#endif     /* -----  ENABLE_UNIT_TESTS  ----- */

#endif   /* ----- #ifndef DSP_INC  ----- */

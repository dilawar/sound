/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * project_hindi
 * Copyright (C) Dilawar Singh 2010 <dilawar@ee.iitb.ac.in>
 * 
 * project_hindi is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * project_hindi is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _WAV_FILE_H_
#define _WAV_FILE_H_
#include <iostream>
#include <iomanip>
#include <cmath>

#ifndef  CONST84
#define CONST84       /* -----  not CONST84  ----- */
#endif     /* -----  not CONST84  ----- */


/*
 * =====================================================================================
 *        Class:  WavFile
 *  Description:  This file is responsible for loading wav file and reading
 *  its content. Wav file data will be loaded into some dat file to be
 *  processed later.
 * =====================================================================================
 */

class WavFile
{
    private:
        bool isExist;
        bool isOpen;
        bool isClose;
        char* fileName;
    public:

        /* ====================  LIFECYCLE     ======================================= */
        WavFile ();                             /* constructor      */
        //WavFile ( char* fileName );   /* copy constructor */
        ~WavFile ();                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */

 
        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  getNumSamples
         *  Description:  Returns number of samples in file.
         * =====================================================================================
         */
        long int getNumSamples();


        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  getNumChannels
         *  Description:  Returns no of channels (1 == mono, 2 == stereo )
         * =====================================================================================
         */
        int getNumChannels();


        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  getBitsPerSample
         *  Description:  Report the number of bits in each samples.
         * =====================================================================================
         */
        int getBitsPerSample();


        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  getSampleRateHz
         *  Description:  return sample rate in Hz
         * =====================================================================================
         */
        double getSampleRateHz();


        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  displayInformation
         *  Description:  get all the information about file.
         * =====================================================================================
         */
        int displayInformation(char* fileName);


        /* ====================  MUTATORS      ======================================= */

        /* ====================  OPERATORS     ======================================= */

        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  readCurrentInput()
         *  Description:  Routine for reading one sample from a previously
         *  loaded wave file. Retuens current sample as a double.
         * =====================================================================================
         */
        double readCurrentInput();


        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  ifMoreDataAvailable
         *  Description:  Check if file is over.
         * =====================================================================================
         */
        int ifMoreDataAvailable();

        //const WavFile& operator = ( const WavFile &other ); /* assignment operator */

        /* ====================  DATA MEMBERS  ======================================= */
    protected:
        double fs_hz;
        int bitsPerSample;
        int nChannel;

        double* gWavDataIn;
        int numInSamples;
        long int maxInSamples;
        /* put friends here if he has any else, leave him all alone you crazy objects */


    public:
        
        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  openWavFile
         *  Description:  This will open the wav file for further processing.
         * =====================================================================================
         */
        int openWavFile(char* fileName);

        /* 
         * ===  FUNCTION ======================================================================
         *         Name:  loadWavData
         *  Description:  This should load the content of wav file in to a
         *  binary file for further processing.
         * =====================================================================================
         */
        int writeDataToFile();


        /*
         *--------------------------------------------------------------------------------------
         *       Class:  WavFile
         *      Method:  closeWavFile
         * Description:  This should close the file after processing.
         *--------------------------------------------------------------------------------------
         */
        int closeWavFile(FILE* pFile);


}; /* -----  end of class WavFile  ----- */

#endif // _WAV_FILE_H_

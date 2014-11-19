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

#include "./../include/wav-file.h"
#include "./../include/wav-def.h"
#include  <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <fstream>

/* constructor */
WavFile::WavFile()
{

#ifdef  DEBUG
    printf("\ninside WavFile()");
#endif     /* -----  not DEBUG  ----- */
}  /* -----  end of method WavFile::WavFile  ----- */

/* deconstructor */
WavFile::~WavFile()
{

#ifdef  DEBUG
    printf("\n~WavFile()");
#else      /* -----  not DEBUG  ----- */

#endif     /* -----  not DEBUG  ----- */
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  WavFile
 *      Method:  getNumSamples
 * Description:  returns num of sample in file.
 *--------------------------------------------------------------------------------------
 */
long int WavFile::getNumSamples()
{
    return maxInSamples;
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  WavFile
 *      Method:  getNumChannels
 * Description:  get number of channels present in wav file. 1 is mono, 2 is
 * stereo. Get in pal!
 *--------------------------------------------------------------------------------------
 */
int WavFile::getNumChannels()
{
    return nChannel;
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  WavFile
 *      Method:  getBitsPerSample
 * Description:  You know. Return bit per sample.
 *--------------------------------------------------------------------------------------
 */
int WavFile::getBitsPerSample()
{
    return bitsPerSample;
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  WavFile
 *      Method:  getSampleRate
 * Description:  get sample rate in chunk.
 *--------------------------------------------------------------------------------------
 */
double WavFile::getSampleRateHz()
{
    return fs_hz;
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  WavFile
 *      Method:  ifMoreDataAvailable
 * Description:  check if something is left in file.
 *
 *--------------------------------------------------------------------------------------
 */
int WavFile::ifMoreDataAvailable()
{
    if(numInSamples >= maxInSamples)
    {
        return 0;
    }
    return 1;
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  WavFile
 *      Method:  readCurrentInput
 * Description:  Isn't it obvious from the file.
 *--------------------------------------------------------------------------------------
 */
double WavFile::readCurrentInput()
{
    stringstream ss;
    if( (gWavDataIn == NULL) || (maxInSamples <=0) || (numInSamples < 0) )
    {
        ss << "\nInput file not ready (or not loaded) !!!" << endl;
        throw runtime_error(ss.str());
    }

    if( numInSamples >= maxInSamples)
    {
        ss.str("");
        ss << "What you reading. Nothing is left to read, you crazy book-worm!!";
        throw runtime_error(ss.str());
    }
    return gWavDataIn[numInSamples++];
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  WavFile
 *      Method:  WavFile
 * Description:  this is another constructor which reads the file.
 *--------------------------------------------------------------------------------------
 */

void WavFile::readWavFile(const string fileName, vector<double>& outVector, bool save)
{
    stringstream ss;
    int i;
    FILE *pFile;
    unsigned int stat;
    char outBuffer[80];

    WAV_HDR* pWavHeader;
    CHUNK_HDR* pChunkHeader;

    short int* pU;
    unsigned char* pC;
    int sFlag;
    long int rMore;

    char* wBuffer;
    int wBufferLength;

    /* set the defaults values. */
    gWavDataIn = NULL;
    numInSamples = 0;
    maxInSamples = 0;

    /* allocate wav header */
    pWavHeader = new WAV_HDR;
    pChunkHeader = new CHUNK_HDR;

    if( NULL == pWavHeader )
    {
        ss << "can't new headers" << endl;
        throw runtime_error(ss.str());
    }

    if( NULL == pChunkHeader )
    {
        ss.str("");
        ss << "can't new headers\n";
        throw runtime_error(ss.str());
    }

    /*
     * open the wav file
     */
    pFile = fopen( fileName.c_str(), "rb");
    if(pFile == NULL)
        throw runtime_error("Can't open file " + fileName);


    /*-----------------------------------------------------------------------------
     *  Now, we have load the file. Start reading data.
     *-----------------------------------------------------------------------------*/

    /* read riff/wav header */
    stat = fread((void*) pWavHeader, sizeof(WAV_HDR), (size_t)1, pFile);
    if(stat != 1)
    {
        ss.str("");
        ss << "Header missing. May be format is not OK!\n";
        throw runtime_error(ss.str());
    }

    /* check format of header */
    for(i = 0; i < 4; i++)
    {
        outBuffer[i] = pWavHeader->rID[i];
    }
    outBuffer[4] = 0;
    if(strcmp(outBuffer, "RIFF") != 0) // tested.
    {
        ss.str("");
        ss << "\nBad RIFF format. I am not cool enough to support everything";
        ss << ("\nyou provide us with! Give me a good file.");
        throw runtime_error(ss.str());
    }

    for(i = 0; i < 4; i++)
    {
        outBuffer[i] = pWavHeader->wID[i];
    }
    outBuffer[4] = 0;

#ifdef DEBUG1
    std::cout<<"\noutBuffer: "<<outBuffer<<"and fID:"<<pWavHeader->fId;
#else      /* -----  not >DEBUG  ----- */

#endif     /* -----  not >DEBUG  ----- */

    if(strcmp(outBuffer, "WAVE") != 0) // tested.
    {
        ss.str(""); ss << ("\nBad WAVE format");
        throw runtime_error(ss.str());
    }

    for(i = 0; i < 4; i++)
    {
        outBuffer[i] = pWavHeader->fId[i];
    }
    outBuffer[4] = 0;

#ifdef DEBUG1
    std::cout<<"outBuffer:"<<outBuffer;
    std::cout<<"compare:"<<strcmp(outBuffer, "fmt ");
#endif     /* -----  not >DEBUG  ----- */

    if(strcmp(outBuffer, "fmt ") != 0) // not with "fmt" since 4th pos is blank
    {
        ss.str("");
        ss << ("\nBad fmt format");
        throw runtime_error(ss.str());
    }

    if(pWavHeader->wFormatTag != 1)
    {
        ss.str("");
        ss <<("\n Bad wav wFormatTag");
        throw runtime_error(ss.str());
    }

    if( (pWavHeader->numBitsPerSample != 16) && (pWavHeader->numBitsPerSample != 8))
    {
        ss.str(""); ss << ("\nBad wav bits per sample");
        throw runtime_error(ss.str());
    }

    /*
     * Skip over any remaining portion of wav header.
     */
    rMore = pWavHeader->pcmHeaderLength - (sizeof(WAV_HDR) - 20);
    if( 0 != fseek(pFile, rMore, SEEK_CUR))
        cerr << "Warn: Can't seek." << endl;

    /*
     * read chunk untill a data chunk is found.
     */
    sFlag = 1;
    while(sFlag != 0)
    {
        // check attempts.
        if(sFlag > 10)
        {
            ss.str(""); ss << ("\nToo manu chunks");
            throw runtime_error(ss.str());
        }

        // read chunk header
        stat = fread((void*)pChunkHeader, sizeof(CHUNK_HDR), (size_t)1, pFile);
        if( 1 != stat)
        {
            ss.str("");
            ss << ("\n I just can't read data. Sorry!");
            throw runtime_error(ss.str());
        }

        // check chunk type.
        for(i =0; i < 4; i++)
        {
            outBuffer[i] = pChunkHeader->dId[i];
        }
        outBuffer[4] = 0;
        if(strcmp(outBuffer, "data") == 0)
        {
            break;
        }

        // skip over chunk.
        sFlag++;
        stat = fseek(pFile, pChunkHeader->dLen, SEEK_CUR);
        if(stat != 0)
        {
            ss.str(""); ss << ("Can't seek.");
            throw runtime_error(ss.str());
        }

    }

    /* find length of remaining data. */
    wBufferLength = pChunkHeader->dLen;


#ifdef  DEBUG1
    std::cout<<"wBufferLength:"<<wBufferLength;
#endif     /* -----  not DEBUG  ----- */
    /* find number of samples. */
    maxInSamples = pChunkHeader->dLen;
    maxInSamples /= pWavHeader->numBitsPerSample/8;

    /* allocate new buffers */
    wBuffer = new char[wBufferLength];
    if( wBuffer == NULL)
    {
        ss.str("");
        ss << ("\nCan't allocate.");
        throw runtime_error(ss.str());
    }

    gWavDataIn = new double[maxInSamples];
    if(gWavDataIn == NULL)
    {
        printf("Can't allocate\n");
        exit(-1);
    }

    /* read signal data */
    stat = fread((void*)wBuffer, wBufferLength, (size_t)1, pFile);
    if( 1 != stat)
    {
        printf("\nCan't read buffer.");
        exit(-1);
    }

    /* convert data */
    if(pWavHeader->numBitsPerSample == 16)
    {
        pU = (short*) wBuffer;
        for( i = 0; i < maxInSamples; i++)
        {
            gWavDataIn[i] = (double) (pU[i]);
        }
    }
    else
    {
        pC = (unsigned char*) wBuffer;
        for( i = 0; i < maxInSamples; i++)
        {
            gWavDataIn[i] = (double) (pC[i]);
        }
    }

    /*  save it into vector */
    for( i = 0; i < maxInSamples; i++)
    {
//        printf("%d:%f\t",i, gWavDataIn[i]);
        outVector.push_back(gWavDataIn[i]);
    }

    /*
     * save all this.
     */
    fs_hz = (double) (pWavHeader->nSamplesPerSec);
    double timeStep = 1.0 / pWavHeader->nSamplesPerSec;
    bitsPerSample = pWavHeader->numBitsPerSample;
    nChannel = pWavHeader->numChannels;

    /* If save is true then store the vector into a file. */
    if(save)
    {
        string outFile = fileName+".dat";
        ofstream outF;
        outF.open(outFile);
        cout << "Info: Writing raw data to " << outFile << endl;
        for(unsigned int i = 0; i < outVector.size(); i++)
            outF << timeStep * i << "," << outVector[i] << endl;
        outF.close();
    }

    /* reset and delete */
    numInSamples = 0;

    if(wBuffer != NULL) delete wBuffer;
    if(pWavHeader != NULL) delete pWavHeader;
    if(pChunkHeader != NULL) delete pChunkHeader;
    fclose(pFile);
}

int WavFile::displayInformation(char* fName)
{
#if 1
    /*
     * print the data.
     */
    printf("\n-----------------------------------------------------");
    printf("\nLoaded wav file : %s", fName);
    printf("\nSample rate: %1.01f (Hz)", fs_hz);
    printf("\nNumber of samples = %ld", maxInSamples);
    printf("\nBits per sample = %d", bitsPerSample);
    printf("\nNumber of channels = %d", nChannel);
    printf("\n----------------------------------------------------\n");
#endif

    return EXIT_SUCCESS;
}

int WavFile::writeDataToFile()
{
    FILE* pFile;
    int n;
    pFile = fopen("speechData.dat", "w");
    char header[50];
    n = sprintf(header, "; Sample Rate %1f\n", fs_hz);
    fprintf(pFile, header);
    n = sprintf(header, "; Channels %d\n", nChannel);
    fprintf(pFile, header);

    for( int i = 0; i < maxInSamples; i++)
    {
        char data[30];
        int n;
        n = sprintf(data,"\t%1.9f\t%1.9f\n", i/fs_hz, gWavDataIn[i]/pow(2,bitsPerSample - 1)); // normalize it.
        //pData = gWavDataIn[i];
        fprintf(pFile, data);
        //std::cout<<data;
    }
    fclose(pFile);
    return EXIT_SUCCESS;
}


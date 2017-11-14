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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

/* constructor */
WavFile::WavFile()
{

#ifdef  DEBUG
    printf("\ninside WavFile()");
#endif     /* -----  not DEBUG  ----- */
}		/* -----  end of method WavFile::WavFile  ----- */

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
    if( (gWavDataIn == NULL) || (maxInSamples <=0) || (numInSamples < 0) )
    {
        printf("\nInput file not ready (or not loaded) !!!\n");
        exit(1);
    }

    if( numInSamples >= maxInSamples)
    {
        printf("What you reading. Nothing is left to read, you crazy book-worm!!");
        exit(1);
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
int WavFile::openWavFile(char* fileName)
{

#ifdef  DEBUG
    printf("\nopenWavFile function");
#endif     /* -----  not DEBUG  ----- */
    int i;
    //printf("Inside function.");
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
        printf("can't new headers\n");
        exit(-1);
    }

    if( NULL == pChunkHeader )
    {
        printf("can't new headers\n");
        exit(-1);
    }

    /*
     * open the wav file
     */
    pFile = fopen( fileName, "rb");
    if(pFile == NULL)
    {
        printf("Can't open wav file.");
        exit(-1);
    }


    /*-----------------------------------------------------------------------------
     *  Now, we have load the file. Start reading data.
     *-----------------------------------------------------------------------------*/

    /* read riff/wav header */
    stat = fread((void*) pWavHeader, sizeof(WAV_HDR), (size_t)1, pFile);
    if(stat != 1)
    {
        printf("Header missing. May be format is not OK!\n"); // This is tested.
        exit(-1);
    }

    /* check format of header */
    for(i = 0; i < 4; i++)
    {
        outBuffer[i] = pWavHeader->rID[i];
    }
    outBuffer[4] = 0;
    if(strcmp(outBuffer, "RIFF") != 0) // tested.
    {
        printf("\nBad RIFF format. I am not cool enough to support everything");
        exit(-1);
    }

    for(i = 0; i < 4; i++)
        outBuffer[i] = pWavHeader->wID[i];
    outBuffer[4] = 0;

#ifdef DEBUG
    std::cout<<"\noutBuffer: "<<outBuffer<<"and fID:"<<pWavHeader->fId;
    print_hdr( pWavHeader );
#else      /* -----  not >DEBUG  ----- */

#endif     /* -----  not >DEBUG  ----- */

    if(strcmp(outBuffer, "WAVE") != 0) // tested.
    {
        printf( "\n%s" , outBuffer );
        printf("\nBad WAVE format \n");
        exit(-1);
    }

    for(i = 0; i < 4; i++)
    {
        outBuffer[i] = pWavHeader->fId[i];
    }
    outBuffer[4] = '\0';

#ifdef DEBUG
    std::cout<<"outBuffer:"<<outBuffer;
    std::cout<<"compare:"<<strcmp(outBuffer, "fmt ");
#endif     /* -----  not >DEBUG  ----- */

    if(strcmp(outBuffer, "fmt ") != 0) // not with "fmt" since 4th pos is blank
    {
        printf("\nBad fmt format");
        exit(-1);
    }

    if(pWavHeader->wFormatTag != 1)
    {
        printf("\n Bad wav wFormatTag");
        exit(-1);
    }

    if( (pWavHeader->numBitsPerSample != 16) && (pWavHeader->numBitsPerSample != 8))
    {
        printf("\nBad wav bits per sample");
        exit(-1);
    }

    /*
     * Skip over any remaining portion of wav header.
     */
    rMore = pWavHeader->pcmHeaderLength - (sizeof(WAV_HDR) - 20);
    if( 0 != fseek(pFile, rMore, SEEK_CUR))
    {
        printf("Can't seek.");
        exit(-1);
    }

    /*
     * read chunk untill a data chunk is found.
     */
    sFlag = 1;
    while(sFlag != 0)
    {
        // check attempts.
        if(sFlag > 10)
        {
            printf("\nToo many chunks");
            exit(-1);
        }

        // read chunk header
        cerr << "Size of chunk" << sizeof( CHUNK_HDR) << endl;
        stat = fread((void*)pChunkHeader, sizeof(CHUNK_HDR), (size_t)1, pFile);
        if( 1 != stat)
        {
            printf("\n I just can't read data. Sorry!");
            exit(-1);
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
            printf("Can't seek.");
            exit(-1);
        }

    }

    /* find length of remaining data. */
    wBufferLength = pChunkHeader->dLen;
    cerr << "wBufferLength : " << pChunkHeader->dLen;


#ifdef  DEBUG1
    std::cout<<"wBufferLength:"<<wBufferLength;
#endif     /* -----  not DEBUG  ----- */
    /* find number of samples. */
    maxInSamples = pChunkHeader->dLen;
    cerr  << "maxInSamples " << maxInSamples << endl;
    maxInSamples /= pWavHeader->numBitsPerSample/8;

    /* allocate new buffers */
    wBuffer = new char[wBufferLength];
    if( wBuffer == NULL)
    {
        printf("\nCan't allocate.");
        exit(-1);
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

#ifdef  DEBUG11
    for( i = 0; i < maxInSamples; i++)
    {
        printf("%d:%f\t",i, gWavDataIn[i]);
    }
#endif     /* -----  not DEBUG  ----- */

    /*
     * save all this.
     */
    fs_hz = (double) (pWavHeader->nSamplesPerSec);
    bitsPerSample = pWavHeader->numBitsPerSample;
    nChannel = pWavHeader->numChannels;

    /* reset and delete */
    numInSamples = 0;

    if(wBuffer != NULL) delete wBuffer;
    if(pWavHeader != NULL) delete pWavHeader;
    if(pChunkHeader != NULL) delete pChunkHeader;
    fclose(pFile);

    return EXIT_SUCCESS;
}

int WavFile::displayInformation(char* fName)
{
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

    return EXIT_SUCCESS;
}

int WavFile::writeDataToFile( char* outfile )
{
    FILE* pFile;
    pFile = fopen( outfile, "w");

    char header[50];

    //sprintf(header, "# Sample Rate %1f\n", fs_hz);
    fprintf(pFile, "%s", header);

    //sprintf(header, "# Channels %d\n", nChannel);
    fprintf(pFile, "%s", header);
    for( int i = 0; i < maxInSamples; i++)
    {
        char data[30];
        sprintf(data,"%1.9f,%1.9f\n", i/fs_hz, gWavDataIn[i]/pow(2,bitsPerSample - 1)); // normalize it.
        fprintf(pFile, "%s", data);
    }
    fclose(pFile);
    return EXIT_SUCCESS;
}


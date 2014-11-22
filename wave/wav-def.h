/*
 * =====================================================================================
 *
 *       Filename:  wave_def.h
 *
 *    Description:  Header of wav file.
 *
 *        Version:  1.0
 *        Created:  Thursday 14 October 2010 12:40:38  IST
 *       Revision:  none
 *       Compiler:  g++/gcc 
 *
 *         Author:  Dilawar (nuts), dilawar[AT]ee[dot]iitb[dot]ac[dot]in
 *      Institute:  Indian Institute of Technology, Bombay
 *
 * This material is released under GNU Lesser Public License.	
 * You are free to copy, distribute or use it for any non-commercial activity.
 * But you are not allowed to modify it. If you are a student, you can use its
 * part in your work with or without mentioning it.
 * 
 * For additional details, please see the GNU Lesser Public license.
 *
 * NOTE : No propriety software is used in this material.
 * Almost all of the code is written and modified in VIM editor with c-support 
 * plugin which is more awesome than Kung Fu Panda. Just kidding, no one is more
 * awesome than Kung Fu Panda with or without a light saber.
 * 
 * This program is made using a bit for here,  a bit from there under the influence
 *  of a lot of burnt out neurons.
 * Report bugs : dilawar.in@gmail.com
 * =====================================================================================
 */


#ifndef  wave_def_INC
#define  wave_def_INC

/* this implementation is due to Fred De Piero - CalPoly State University.
 * Released under GNU Public Licence.
 * Used without his permossion or knowledge.
 * Modifications are done to suit our purpose. And this part was not trivial.
 * This is NOT a copy and paste implementation.
 */

typedef struct{
    char rID[4];      // 'RIFF'
    long int rLen;

    char wID[4];      // 'WAVE'

    char fId[4];      // 'fmt'
    long int pcmHeaderLength;
    short int wFormatTag;
    short int numChannels;
    long int nSamplesPerSec;
    long int nAvgBytesPerSec;
    short int numBlockAlingn;
    short int numBitsPerSample;
} WAV_HDR;

/* header of wave file */
typedef struct
{
    char dId[4];  // 'data' or 'fact'
    long int dLen;
} CHUNK_HDR;
#endif   /* ----- #ifndef wave_def_INC  ----- */

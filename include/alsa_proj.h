/*
 * =====================================================================================
 *
 *       Filename:  alsa_proj.h
 *
 *    Description:  This is header file.
 *
 *        Version:  1.0
 *        Created:  Sunday 17 October 2010 09:49:07  IST
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

#ifndef  ALSA_PROJ_HH
#define ALSA_PROJ_HH
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
//#include "audio.h"

#define FORMAT_DEFAULT      -1
#define FORMAT_RAW      0

 
/*
 * =====================================================================================
 *        Class:  OurAlsa
 *  Description:  This will be responsible for record and play of sound.
 * =====================================================================================
 */
class OurAlsa
{
    public:

        /* ====================  LIFECYCLE     ======================================= */
        OurAlsa ();                             /* constructor      */
        OurAlsa ( const OurAlsa &other );   /* copy constructor */
        ~OurAlsa ();                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */

        /* ====================  OPERATORS     ======================================= */

        const OurAlsa& operator = ( const OurAlsa &other ); /* assignment operator */

        /* ====================  DATA MEMBERS  ======================================= */
    protected:

        static char *command;
        static snd_pcm_t *handle;

        static struct {
            snd_pcm_format_t format;
            unsigned int channels;
            unsigned int rate;
        } hwparams, rhwparams;

        static int file_type ;//= FORMAT_DEFAULT;
        static snd_pcm_stream_t stream;// = SND_PCM_STREAM_PLAYBACK;
        static int interleaved;// = 1;
        static u_char *audiobuf;// = NULL;
        static snd_pcm_uframes_t chunk_size;//e = 0;

        static int start_delay;// = 0;
        static int stop_delay;// = 0;
        static int avail_min;// = -1;
        static unsigned period_time;// = 0;
        static unsigned buffer_time;// = 0;
        static snd_pcm_uframes_t period_frames;// = 0;
        static snd_pcm_uframes_t buffer_frames;// = 0;
        static size_t bits_per_sample, bits_per_frame;
        static size_t chunk_bytes;

        static int timelimit;// = 0;


    public:
        
        
        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  intializeAlsa
         *  Description:  this is for initializing the ALSA.
         * =====================================================================================
         */
        int intitializeAlsa();



        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  setHwParameters()
         *  Description:  set parameters.
         * =====================================================================================
         */
        
        int setHwParameters();

        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  recordAlsa
         *  Description:  This will start teh recording.
         * =====================================================================================
         */
        int recordAlsa();



        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  playbackAlsa()
         *  Description:  this will playback the recorded buffer.
         * =====================================================================================
         */
        int playbackAlsa();


}; /* -----  end of class OurAlsa  ----- */

#endif     /* -----  not ALSA_PROJ  ----- */

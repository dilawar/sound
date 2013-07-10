/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  This is our main file.
 *
 *        Version:  1.0
 *        Created:  Sunday 05 September 2010 09:44:39  IST
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
#define EXIT_SUCCESS    1
#define EXIT_FAILURE    0
#define TRUE            1
#define FALSE           0

#include  <iostream> 
#include	"include/wav-file.h"
#include	<getopt.h>
//#include	<tk.h>
//#include	<tkInt.h>
//#include	<tkIntXlibDecls.h>
//#include	<X11/Xlib.h>
//#include	<tcl.h>
//#include	<tclDecls.h>
//#include	<tkimg.h>
#include	<stdlib.h>
#include	<stdio.h>
//#include	<error.h>
//#include	"praat.h"
//#include  "Printer.h"
#include  <string>

#ifdef SCILAB
#include	"scilab/stack-c.h"
#include	"scilab/api_scilab.h"
#include	"scilab/call_scilab.h" /* Provide function to call scilab. */
#endif
#if 0
wchar_t myScript [] = L""
      "demo Text... 0.5 centre 0.5 half Hello world\n"
      "demoWaitForInput()\n"
      ;
#endif

int main(int argc, char** argv)
{
#if DEBUG
	std::cout<<"Entering the main()\n";
	std::cout<<"\nNo of args are: "<<argc;
#endif
	/* Here, we parse our argument passed to this application from command line*/
	if(argc < 2)
	{
		std::cout<<"\nOh Snap!"
			<<"\nWassup, Fellow Human.."
			<<"\nAt least, you need to specify wav file. Use --help to see your options.\n";
	 	return EXIT_FAILURE;
	}
  int c;	
  unsigned long long int number;
	int do_help = 0;
 	int do_verbose = 0;
 	bool ifInvalid = FALSE;	/* flag variables. */  
	char* fileName;
	while(1)
	{
		int option_index = 0;
		static struct option long_options[] = {
			{"file", 		required_argument, 		NULL, 		'f'},
			{"help", 			no_argument, 		 			&do_help, 	1},
			{"verbose", 	no_argument, 				 	&do_verbose, 1},
			{0, 0, 0 , 0}
		};

		c = getopt_long(argc, argv, "f:hv", long_options, &option_index);
		if (c == -1)
			break;

		switch(c) {

			case 'f':
#if DEBUG
				std::cout<<"\nFrom main() - Option --file with value '"
					<<optarg<<"'\n";
#endif
				fileName = optarg;
				break;

			
			case 0:
#ifdef DEBUG
				std::cout<<"\noption "<<long_options[option_index].name;
				if (optarg)
					std::cout<<"with arg "<<optarg;
				//std::cout<<"Bad option. x-(\n";
#endif
				break;

			case 'v':
			  do_verbose = 1;
#ifdef  DEBUG
				std::cout<<"\nFrom main() : Verbose output is set.\n";
#else      /* -----  not DEBUG  ----- */

#endif     /* -----  not DEBUG  ----- */
				break;
			
			case 'h':
				do_help = 1;
				break;

			case ':': /* missing option arguement. */
				fprintf(stderr, " option %s requires an argument. \n",
						argv[1]);
				ifInvalid = TRUE;
			 	break;

			case '?':

			default:
				fprintf(stderr, "option %s is invalid : ignored\n",
						argv[1]);
				ifInvalid = TRUE;
				break;
		}

	}

	/* We got the options. Do the stuff. */
	if(TRUE == ifInvalid || 1 == do_help)
	{
		std::cout<<"\n-------------------------------------------------------";
		std::cout<<"\nUSAGE :";
		std::cout<<"\n\t --file <name>" 
			<<"\n\t\t provide the wav file."
			<<"\n\t --help"
			<<"\n\t\t to see the help. Should be used alone."
			<<"\n\t --verbose"
			<<"\n\t\t for verbose output.";
		std::cout<<"\n-------------------------------------------------------\n";
		return EXIT_FAILURE;
	}
	 
  WavFile* pObjWavFile;
  std::cout<<"FileName is:"<<fileName;
  pObjWavFile = new WavFile;
  if (EXIT_SUCCESS != pObjWavFile->openWavFile(fileName))
  {
      std::cout<<"\nCan't load wav file.";
      exit(-1);
  }

  pObjWavFile->displayInformation(fileName);
  /* read data and do something */
#if ALSA
  double data;
  while(pObjWavFile->ifMoreDataAvailable())
  {
      data = pObjWavFile->readCurrentInput();
      //std::cout<<"\t"<<data;
      /* can we play it here. */
  } 
  int rc;
  snd_pcm_t *handle;
  snd_pcm_hw_params_t *params;
  unsigned int val, val2;
  int dir;
  snd_pcm_uframes_t frames;
  long loop;
  int size;
  char* buffer;

  /* open PCM device for playback */
  rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
  if( rc < 0)
  {
      fprintf(stderr, "unable to open PCM device : %s\n", snd_strerror(rc));
      exit(-1);
  }

  /* allocate HW parameters objects. */
  snd_pcm_hw_params_alloca(&params);

  /* fill in the default values. */
  snd_pcm_hw_params_any(handle, params);

  /* set the desired hw parameters */
  //interleaved mode
  snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

  /* signed 16 bit little endian format */
  snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);

  /* Set the channels values. */
  snd_pcm_hw_params_set_channels(handle, params, pObjWavFile->getNumChannels());

  /* sampling rate. */
  //val = pObjWavFile->getSampleRateHz();

  val = 44100;
  //std::cout<<"sample:"<<val;
  snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);

  /* set period size. */
  frames = 32;
  snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);

  /* write the parameters to driver. */
  rc = snd_pcm_hw_params(handle, params);

  if(rc < 0)
  {
      fprintf(stderr, "Unable to set HW parameters : %s\n", snd_strerror(rc));
      exit(-1);
  }

  /* use a buffer large enough to hold one period. */
  snd_pcm_hw_params_get_period_size(params, &frames, &dir);
  size = frames*4; /* 2 bytes/sample, 2 channels */
  buffer = (char *) malloc(size);

  /* we want to loop for 5 seconds. */
  snd_pcm_hw_params_get_period_time(params, &val, &dir);
  /* 5 seconds in microseconds divided by period time. */
  loop = 5000000/val;

  while(loop > 0)
  {
      loop--;
      rc = read(0, buffer, size);
      if(rc == 0)
      {
          fprintf(stderr, "end of file on input.\n");
          break;
      }
      else if (rc != size)
      {
          fprintf(stderr, "short read: read %d bytes\n", rc);
      }
     // buffer = "ab";
      rc = snd_pcm_writei(handle, buffer, frames);
      if(rc == -EPIPE)
      {
          /* EPIPE means underrun */
          fprintf(stderr, "unknown occurred.\n");
          snd_pcm_prepare(handle);
      }
      else if (rc < 0) {
          fprintf(stderr, "error from writei : %s\n", snd_strerror(rc));
      }
      else if(rc != (int) frames)
      {
          fprintf(stderr, "short write, write %d frames\n", rc);
      }
  }

  snd_pcm_drain(handle);
  snd_pcm_close(handle);
  free(buffer);

#endif

  /* write data in a file. */
  pObjWavFile->writeDataToFile();


#ifdef  SOX
  system("play speechData.dat");
#else      /* -----  not SOX  ----- */

#endif     /* -----  not SOX  ----- */

/* 
 * THIS IS PRAAT BLOCK.
 */
#ifdef PRAAT
  praat_setStandAloneScriptText (myScript);
  praat_init ("Hello", argc, argv);
  INCLUDE_LIBRARY (praat_uvafon_init)
  praat_run ();
#endif

  /* 
   * THIS IS SCILAB BLOCK
   */
#ifdef  SCILAB11
/**
 * Initialization.
 */
#ifdef _MSC_VER
  if(StartScilab(NULL, NULL, NULL) == FALSE)
#else
  if(StartScilab(getenv("SCI"), NULL, NULL) == FALSE)
#endif
  {
      fprintf(stderr, "Error while calling StartScilab\n");
      return -1;
  }
#else      /* -----  not SCILAB  ----- */

#endif     /* -----  not SCILAB  ----- */

 /*  
  *  Write the file name into Scilan
 */
     int row = 1, col = 1;
#ifdef SCILAB
     /* Declare the string */
     char **myMatrixOfFilePath = (char**)malloc(sizeof(char*)*row*col);
     myMatrixOfFilePath[0] = fileName;
     std::cout<<"path is : "<<myMatrixOfFilePath[0];
     char variableName[]= "filePath";

     /* write it into scilab memory */
     createNamedMatrixOfString(pvApiCtx, variableName, row, col, myMatrixOfFilePath);

#ifdef  DEBUG
    std::cout<<"variable name is :"<<variableName;//<<" and :" <<filePath;
#else      /* -----  not DEBUG  ----- */

#endif     /* -----  not DEBUG  ----- */
     /* now send this job to Scilab */
      SendScilabJob("myMatrix = [1 2 3; 2 3 1];");
      SendScilabJob("disp(myMatrixOfFilePath)");
      SendScilabJob("disp(filePath);");
      SendScilabJob("[x, y] = loadWave(filePath);");
      SendScilabJob("disp(x);");

      /*-----------------------------------------------------------------------------
       *  Termination
       *----------------------------------------------------------------------------- 
       */
      if(TerminateScilab(NULL) == FALSE)
      {
          fprintf(stderr, "Error while closing scilab.");
          return -2;
      }
#endif // SCILAB
      return 0;
    }

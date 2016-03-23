sound
=====

This work is derivative of Dr. Taylor’s work http://people.msoe.edu/~taylor/examples/wav.htm . There was a bug in his implementation which is removed from this implementation.  We give here a c++ class to read WAV file and store its content in an array. We also store these values in a csv file which you can plot using application of your choise. We only support non-compressed WAV file. 

The minimal implementation is on branch 'wavereader' which is default branch on github. On other branches, this project has diverged a lot.

Usage 
====

Run `make` to build the project. This will create a binary `parseSpeech`.

    make 
    ./parseSpeech -f /path/to/input.wav 

In the end, you will have a `/path/to/input.wav.csv` file. It has two columns: time and signal value at that time.

Dependencies 
============

It might require installation of 'libasound2-dev' package.

__Please consider using https://github.com/dilawar/wav . It has a header only c++11 implementation.__


sound
=====

This work started off as a fork of Dr. Taylor’s work http://people.msoe.edu/~taylor/examples/wav.htm (dead link). On `master` branch the project has diverged a lot. 

We provide a C++ class to read WAV file. It's content are  stored  in an array which we finally write to a csv file. You can plot this csv file using any application of your choise. We only support non-compressed WAV file. 

On other branches, this project has diverged a lot.

Usage 
====

Run `make` to build the project. This will create a binary `parseSpeech`.

    cmake .
    make 
    ./parseSpeech -f /path/to/input.wav 

In the end, you will have a `/path/to/input.wav.csv` file. It has two columns: time and signal value at that time.


sound
=====

This work is derivative of Dr. Taylor’s work
http://people.msoe.edu/~taylor/examples/wav.htm . There was a bug in his
implementation which is removed from this implementation.  We give here a c++
class to read WAV file and store its content in an array. We also store these
values in a ASCII file and plot it using gnuplot to check whether we get it
right. praat can be used to confirm whether our output is right or not. We only
support non-compressed WAV file.

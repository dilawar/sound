CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE_DIRECTORIES(../core ../simpletest)
ADD_LIBRARY(wave 
    WavLoader.cc
    wav-file.cc
)

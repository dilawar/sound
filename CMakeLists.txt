CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(songbird)

SET(CMAKE_MODULE_PATH cmake_modules)
SET(CMAKE_VERBOSE_MAKEFILE ON)

FIND_PACKAGE(GSL REQUIRED)
INCLUDE_DIRECTORIES(${GSL_INCLUDE_DIR})
ADD_DEFINITIONS(-DENABLE_UNIT_TESTS)

SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost REQUIRED COMPONENTS  
    iostreams  
    system unit_test_framework
    filesystem
    program_options
    )

MESSAGE("++ Include dirs : ${Boost_INCLUDE_DIRS}")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

ADD_DEFINITIONS(-g -std=c++11)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK -DBOOST_TEST_DYN_LINK)

INCLUDE_DIRECTORIES(dsp aiff wave simpletest)

#LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/external/aquila/lib)
#include(ExternalProject)
#SET(DSP_SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/aquila)
#ExternalProject_Add(
#    aquila
#    PREFIX ${DSP_SOURCE_DIR}
#    GIT_REPOSITORY https://github.com/dilawar/aquila
#    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${DSP_SOURCE_DIR}
#    ) 
#
#INCLUDE_DIRECTORIES(${DSP_SOURCE_DIR}/include)

INCLUDE_DIRECTORIES(plotting)

ADD_SUBDIRECTORY(aiff)
ADD_SUBDIRECTORY(wave)
ADD_SUBDIRECTORY(dsp)
ADD_SUBDIRECTORY(simpletest)

ADD_EXECUTABLE(songbird core/main.cc)

SET(CMAKE_VERBOSE_MAKEFILE OFF)

MESSAGE("++ LINKING AGAINGS ${Boost_LIBRARIES}")

TARGET_LINK_LIBRARIES(songbird
    aiff
    wave
    asound
    dsp
    pthread
    simpletest
    ${GSL_LIBRARIES}
    ${Boost_LIBRARIES}
    )
enable_testing()

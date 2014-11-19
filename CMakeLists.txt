CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(songbird)

FIND_PACKAGE(Boost  COMPONENTS program_options unit_test_framework log REQUIRED)
INCLUDE_DIRECTORIES(${BOOST_INCLUDE_DIRECTORIES} ${CMAKE_SOURCE_DIR})

ADD_DEFINITIONS(-g -std=c++11)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

INCLUDE_DIRECTORIES(aiff wave)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/external/aquila/lib)

include(ExternalProject)
SET(DSP_SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/aquila)
ExternalProject_Add(
    aquila
    PREFIX ${DSP_SOURCE_DIR}
    URL https://github.com/zsiciarz/aquila/archive/master.zip
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${DSP_SOURCE_DIR}
    ) 
INCLUDE_DIRECTORIES(${DSP_SOURCE_DIR}/include)


ADD_SUBDIRECTORY(aiff)
ADD_SUBDIRECTORY(wave)
ADD_SUBDIRECTORY(dsp)

ADD_EXECUTABLE(songbird core/main.cc)

SET(CMAKE_VERBOSE_MAKEFILE ON)

MESSAGE("++ LINKING AGAINGS ${Boost_LIBRARIES}")

TARGET_LINK_LIBRARIES(songbird
    aiff
    wave
    asound
    dsp
    ${Boost_LIBRARIES}
    pthread
    )


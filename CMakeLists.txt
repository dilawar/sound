CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(songbird)

FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRECTORIES})

add_definitions(-g -std=c++11)

INCLUDE_DIRECTORIES(aiff wave)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/external/aquila/lib)

ADD_SUBDIRECTORY(aiff)
ADD_SUBDIRECTORY(wave)
ADD_SUBDIRECTORY(dsp)

ADD_EXECUTABLE(songbird main.cc)

SET(CMAKE_VERBOSE_MAKEFILE ON)

include(ExternalProject)
SET(DSP_SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/aquila)
ExternalProject_Add(
    aquila
    PREFIX ${DSP_SOURCE_DIR}
    URL https://github.com/zsiciarz/aquila/archive/master.zip
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${DSP_SOURCE_DIR}
    ) 
INCLUDE_DIRECTORIES(${DSP_SOURCE_DIR}/include)

TARGET_LINK_LIBRARIES(songbird
    aiff
    wave
    asound
    dsp
    ${GTEST_BOTH_LIBRARIES}
    )


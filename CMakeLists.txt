CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(songbird)
add_definitions(-g -std=c++11)
INCLUDE_DIRECTORIES(aiff wave)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/external/DSPFilters/lib)

ADD_SUBDIRECTORY(aiff)
ADD_SUBDIRECTORY(wave)
ADD_SUBDIRECTORY(dsp)

ADD_EXECUTABLE(songbird main.cc)

SET(CMAKE_VERBOSE_MAKEFILE ON)

include(ExternalProject)
SET(DSP_SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/DSPFilters)
ExternalProject_Add(
    DSPFilters
    PREFIX ${CMAKE_SOURCE_DIR}/external/DSPFilters
    SOURCE_DIR  ${CMAKE_SOURCE_DIR}/external/DSPFilters
    CONFIGURE_COMMAND ${DSP_SOURCE_DIR}/waf configure --prefix=${DSP_SOURCE_DIR}
    BUILD_COMMAND ${DSP_SOURCE_DIR}/waf build
    INSTALL_COMMAND ${DSP_SOURCE_DIR}/waf install
    BUILD_IN_SOURCE 1
    ) 
INCLUDE_DIRECTORIES(${SOURCE_DIR}/include)

TARGET_LINK_LIBRARIES(songbird
    aiff
    wave
    asound
    dsp
    )


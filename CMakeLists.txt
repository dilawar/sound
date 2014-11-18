CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(songbird)


INCLUDE_DIRECTORIES(
    aiff
    wave
)

ADD_SUBDIRECTORY(aiff)
ADD_SUBDIRECTORY(wave)

ADD_EXECUTABLE(songbird main.cc)


TARGET_LINK_LIBRARIES(songbird
    aiff
    wave
    asound
)


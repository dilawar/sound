CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(songbird)


INCLUDE_DIRECTORIES(
    aiff
)

ADD_SUBDIRECTORY(aiff)

ADD_EXECUTABLE(songbird main.cc)


TARGET_LINK_LIBRARIES(songbird
    aiff
    asound
)


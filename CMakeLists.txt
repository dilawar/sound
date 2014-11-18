CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(songbird)


INCLUDE_DIRECTORIES(
    include
)

ADD_SUBDIRECTORY(src)

ADD_EXECUTABLE(songbird main.cc)


TARGET_LINK_LIBRARIES(songbird
    aiff
    asound
)


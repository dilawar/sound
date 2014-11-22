CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
add_library(simpletest STATIC simple_test.cpp)
set_target_properties(simpletest PROPERTIES LINKER_LANGUAGE CXX)

# A logging library
add_library(simplelogger STATIC simple_logger.hpp)
set_target_properties(simplelogger PROPERTIES LINKER_LANGUAGE CXX)

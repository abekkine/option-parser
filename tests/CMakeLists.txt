cmake_minimum_required(VERSION 3.15)

project(optParserTest)

set(CXX_STANDARD 11)

include_directories($ENV{EXT_LIB_DIR}/catch2)

add_executable(test test.cpp catch.cpp)

cmake_minimum_required (VERSION 2.8.11)
project (quadris)

set (CXXFLAGS "-std=c++14 -Wall -Wextra -Werror -pedantic")

set (SOURCES
  src/main.cc
  src/Event.h
)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXXFLAGS}")
add_executable(quadris ${SOURCES})
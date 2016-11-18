cmake_minimum_required (VERSION 2.8.11)
project (quadris)

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

add_definitions (-std=c++14 -Wall -Wextra -Werror -pedantic)

set (SOURCES
  src/main.cc
)

add_executable(quadris ${SOURCES})
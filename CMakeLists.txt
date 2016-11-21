cmake_minimum_required (VERSION 2.8.11)
project (quadris)

set (CXXFLAGS "-std=c++14 -Wall -Wextra -Werror -pedantic")
include_directories(src/)

set (SOURCES
  src/main.cc

  src/Event.h

  src/Level.h
  src/Levels/Level0.h
  src/Levels/Level0.cc
  src/Levels/Level1.h
  src/Levels/Level1.cc
  src/Levels/Level2.h
  src/Levels/Level2.cc
  src/Levels/Level3.h
  src/Levels/Level3.cc
  src/Levels/Level4.h
  src/Levels/Level4.cc

  src/Block.h
  src/Blocks/BlockI.h
  src/Blocks/BlockJ.h
  src/Blocks/BlockL.h
  src/Blocks/BlockO.h
  src/Blocks/BlockS.h
  src/Blocks/BlockT.h
  src/Blocks/BlockZ.h

  src/Display.h
  src/Display.cc
  src/Displays/GraphicDisplay.h
  src/Displays/GraphicDisplay.cc
  src/Displays/TextDisplay.h
  src/Displays/TextDisplay.cc

  src/Board.h
  src/Board.cc
  src/Cell.h
  src/Position.h
  src/Score.h
  src/Score.cc

  src/Command.h
  src/Command.cc
  src/CommandInterpreter.h
  src/CommandInterpreter.cc

  src/CommandLineArguments.h
  src/CommandLineArguments.cc
)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXXFLAGS}")
add_executable(quadris ${SOURCES})
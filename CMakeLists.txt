cmake_minimum_required (VERSION 2.8.11)
project (quadris)

set (CXXFLAGS "-std=c++14 -Wall -Wextra -Werror -pedantic")

set (SOURCES
  src/main.cc

  src/Event.h

  src/Level.h
  src/Levels/Level0.h
  src/Levels/Level1.h
  src/Levels/Level2.h
  src/Levels/Level3.h
  src/Levels/Level4.h

  src/Block.h
  src/Blocks/BlockI.h
  src/Blocks/BlockJ.h
  src/Blocks/BlockL.h
  src/Blocks/BlockO.h
  src/Blocks/BlockS.h
  src/Blocks/BlockT.h
  src/Blocks/BlockZ.h

  src/Display.h
  src/Displays/GraphicDisplay.h
  src/Displays/TextDisplay.h

  src/Board.h
  src/Cell.h
  src/Position.h
  src/Score.h

  src/Command.h
  src/CommandInterpreter.h

  src/CommandLineArguments.h
)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXXFLAGS}")
add_executable(quadris ${SOURCES})
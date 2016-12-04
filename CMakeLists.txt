cmake_minimum_required (VERSION 2.8.11)
project (quadris)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

find_package (X11 REQUIRED)

set (CXXFLAGS "-std=c++14 -Wall -Wextra -Werror -Wno-variadic-macros -Wno-unused-parameter -pedantic")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXXFLAGS}")

set (SOURCES
  src/main.cc

  src/QdDefs.h
  src/Event.h
  src/Optional.h

  src/Level.h
  src/Level.cc
  src/Levels/BaseLevel.h
  src/Levels/BaseLevel.cc
  src/Levels/SequencedBaseLevel.h
  src/Levels/SequencedBaseLevel.cc
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
  src/Block.cc
  src/Blocks/BlockI.h
  src/Blocks/BlockI.cc
  src/Blocks/BlockJ.h
  src/Blocks/BlockJ.cc
  src/Blocks/BlockL.h
  src/Blocks/BlockL.cc
  src/Blocks/BlockO.h
  src/Blocks/BlockO.cc
  src/Blocks/BlockS.h
  src/Blocks/BlockS.cc
  src/Blocks/BlockT.h
  src/Blocks/BlockT.cc
  src/Blocks/BlockZ.h
  src/Blocks/BlockZ.cc

  src/Display.h
  src/Display.cc
  src/Displays/GraphicDisplay.h
  src/Displays/GraphicDisplay.cc
  src/Displays/TextDisplay.h
  src/Displays/TextDisplay.cc

  src/Board.h
  src/Board.cc
  src/Cell.h
  src/Cell.cc
  src/Position.h
  src/Position.cc
  src/Score.h
  src/Score.cc
  src/window.h
  src/window.cc

  src/Command.h
  src/Command.cc
  src/CommandInterpreter.h
  src/CommandInterpreter.cc

  src/CommandLineArguments.h
  src/CommandLineArguments.cc
)

add_executable (quadris ${SOURCES})

target_include_directories (quadris PRIVATE src/ ${X11_INCLUDE_DIR})
target_link_libraries (quadris ${X11_LIBRARIES})

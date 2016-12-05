#include "Level4.h"
#include "Board.h"
#include "Block.h"
#include <array>
#include <cstdlib>
#include <iostream>

namespace qd {
  Level4::Level4(Board& b) : SequencedBaseLevel{b}, _consecutiveNoClears(0) {
    _useSequenceFile = false;
    _defaultInitialization();

    _board.linesCleared().addObserver(
      _linesClearedSlot, std::bind(&Level4::onLinesCleared, this, std::placeholders::_1)
    );
  }

  void Level4::executeCommand(const Command& command) {
    if (command.type() == Command::Type::DROP) {
      _consecutiveNoClears++;
    }

    std::cout << _consecutiveNoClears << std::endl;
    
    BaseLevel::executeCommand(command);

    if (command.type() == Command::Type::DROP) {
      if (_consecutiveNoClears % 5 == 0 && _consecutiveNoClears) {
        int col = BOARD_WIDTH / 2;
        int row = BOARD_HEIGHT - _getColHeight(col) + BOARD_EXTRA_SPACE - 1;

        std::cout << "COL: " << col << "ROW: " << row << std::endl;

        _board.cells().at(row).at(col).blockType = Block::Type::BLOCK_SINGLE;

        _board.cellsUpdated().notifyObservers(
          _board.cells(),
          _board.activeBlockPtr().get()
        );
      }
    }
  } 

  int Level4::levelNumber() const {
    return 4;
  }

  void Level4::onLinesCleared(const std::vector<int>&) {
    _consecutiveNoClears = 0;
  }

  int Level4::_getColHeight(int col) {
    int height = BOARD_HEIGHT;

    for (std::size_t i = BOARD_EXTRA_SPACE; i < BOARD_HEIGHT + BOARD_EXTRA_SPACE; i++) {
      if (_board.cells()[i][col].blockType == Block::Type::EMPTY) {
        height--;
      }
      else {
        break;
      }
    }

    return height;
}
}

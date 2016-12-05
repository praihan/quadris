#include "Level4.h"
#include "Board.h"
#include "Block.h"
#include <array>
#include <cstdlib>

namespace qd {
Level4::Level4(Board& b) : SequencedBaseLevel{b} {
    _useSequenceFile = false;
    _defaultInitialization();

    //_board.linesCleared().addObserver(this);
  }

  void Level4::executeCommand(const Command& command) {
    BaseLevel::executeCommand(command);

    int row = BOARD_WIDTH / 2;
    int col = _getHeight(row);

    _board.cells()[row][col].blockType = Block::Type::BLOCK_SINGLE;
  }

  int Level4::levelNumber() const {
    return 4;
  }
}

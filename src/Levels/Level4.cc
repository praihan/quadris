#include "Level4.h"

namespace qd {

  int Level4::levelNumber() const {
    return 4;
  }

  Block::Type Level4::nextBlockType() {

    return Block::Type::EMPTY;
  }

  void Level4::executeCommand(const Command& command) {
    BaseLevel::executeCommand(command);
    
    if (command.type() == Command::Type::LEFT || command.type() == Command::Type::RIGHT || command.type() == Command::Type::DOWN || 
        command.type() == Command::Type::CLOCKWISE || command.type() == Command::Type::COUNTER_CLOCKWISE) {
      Block &activeBlock = _board.activeBlock();
      
      if (_canMove(activeBlock, BaseLevel::Direction::DOWN)) {
        activeBlock.position.row += 1;
        _board.cellsUpdated().notifyObservers(_board.cells());
      }
    }
  }
}

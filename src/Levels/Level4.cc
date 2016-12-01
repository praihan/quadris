#include "Level4.h"
#include "Block.h"
#include <array>
#include <cstdlib>

namespace qd {

  namespace {
    std::array<Block::Type,9> weightedBlockTypes {
      {
        Block::Type::BLOCK_I,
        Block::Type::BLOCK_J,
        Block::Type::BLOCK_L,
        Block::Type::BLOCK_O,
        Block::Type::BLOCK_S,
        Block::Type::BLOCK_S,
        Block::Type::BLOCK_T,
        Block::Type::BLOCK_Z,
        Block::Type::BLOCK_Z
      }
    };
  }

  int Level4::levelNumber() const {
    return 4;
  }

  Block::Type Level4::nextBlockType() {
    int rand = std::rand() % (weightedBlockTypes.size());
    
    return weightedBlockTypes[rand];
  }

  bool Level4::executeCommand(const Command& command) {
    bool success = BaseLevel::executeCommand(command);

    if (command.type() == Command::Type::LEFT || command.type() == Command::Type::RIGHT || command.type() == Command::Type::DOWN || 
        command.type() == Command::Type::CLOCKWISE || command.type() == Command::Type::COUNTER_CLOCKWISE) {
      
      if (!success) {
        return false;
      }

      Block &activeBlock = *_board.activeBlock();
      
      if (_canMove(activeBlock, BaseLevel::Direction::DOWN) && success) {
        activeBlock.position.row += 1;
        _board.cellsUpdated().notifyObservers(_board.cells(), std::addressof(activeBlock));
      }
    }

    return true;
  }
}

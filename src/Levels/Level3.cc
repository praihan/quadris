#include "Block.h"
#include "Level3.h"
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

  int Level3::levelNumber() const {
    return 3;
  }

  Block::Type Level3::nextBlockType() {
    int rand = std::rand() % (weightedBlockTypes.size());
    
    return weightedBlockTypes[rand];
  }

  bool Level3::executeCommand(const Command& command) {
    bool success = BaseLevel::executeCommand(command);
    
    if (command.type() == Command::Type::LEFT || command.type() == Command::Type::RIGHT || command.type() == Command::Type::DOWN || 
        command.type() == Command::Type::CLOCKWISE || command.type() == Command::Type::COUNTER_CLOCKWISE) {
      if (!success) {
        return false;
      }
      
      Block &activeBlock = _board.activeBlock();
      
      if (_canMove(activeBlock, BaseLevel::Direction::DOWN)) {
        activeBlock.position.row += 1;
        _board.cellsUpdated().notifyObservers(_board.cells());
      }
    }

    return true;
  }
}

#include "Block.h"
#include "Level2.h"
#include <array>
#include <cstdlib>

namespace qd {

  namespace {
    std::array<Block::Type, 7> weightedBlockTypes {
      {
        Block::Type::BLOCK_I,
        Block::Type::BLOCK_J,
        Block::Type::BLOCK_L,
        Block::Type::BLOCK_O,
        Block::Type::BLOCK_S,
        Block::Type::BLOCK_T,
        Block::Type::BLOCK_Z
      }
    };
  }

  Level2::Level2(Board& b) : BaseLevel{b} {
    _nextBlockType = nextBlockType();
    _ensureActiveBlock();
  }

  int Level2::levelNumber() const {
    return 2;
  }

  Block::Type Level2::nextBlockType() {
    int rand = std::rand() % (weightedBlockTypes.size());
    
    return weightedBlockTypes[rand];
  }

  bool Level2::executeCommand(const Command& command) {
    return BaseLevel::executeCommand(command);
  }
}
#include "Block.h"
#include "Level2.h"
#include <array>
#include <cstdlib>

namespace qd {

  namespace {
    const std::array<Block::Type, 7> weightedBlockTypes {
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
    _defaultInitialization();
  }

  int Level2::levelNumber() const {
    return 2;
  }

  Block::Type Level2::nextBlockType() {
    std::uniform_int_distribution<> dis(0, (weightedBlockTypes.size() - 1));
    
    auto index = dis(_board.randomEngine());
    
    return weightedBlockTypes[index];
  }
}
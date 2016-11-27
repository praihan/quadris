#include "Level1.h"

#include "Block.h"
#include "Level1.h"
#include <array>
#include <cstdlib>


namespace qd {

  namespace {
    std::array<Block::Type,12> weightedBlockTypes {
      {
        Block::Type::BLOCK_I,
        Block::Type::BLOCK_I,
        Block::Type::BLOCK_J,
        Block::Type::BLOCK_J,
        Block::Type::BLOCK_L,
        Block::Type::BLOCK_L,
        Block::Type::BLOCK_O,
        Block::Type::BLOCK_O,
        Block::Type::BLOCK_S,
        Block::Type::BLOCK_T,
        Block::Type::BLOCK_T,
        Block::Type::BLOCK_Z
      }
    };
  }

  int Level1::levelNumber() const {
    return 1;
  }

  Block::Type Level1::nextBlockType() const {
    int rand = std::rand() % (weightedBlockTypes.size());
    
    return weightedBlockTypes[rand];
  }

  void Level1::useSequence(const std::string& sequenceFileName) {
  
  }
}
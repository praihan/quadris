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

  int Level2::levelNumber() const {
    return 2;
  }

  Block::Type Level2::nextBlockType() const {
    int rand = std::rand() % (weightedBlockTypes.size());
    
    return weightedBlockTypes[rand];
  }

  void Level2::useSequence(const std::string& sequenceFileName) {
  
  }
}
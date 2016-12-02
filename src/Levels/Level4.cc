#include "Level4.h"
#include "Block.h"
#include <array>
#include <cstdlib>

namespace qd {

  namespace {
    const std::array<Block::Type,9> weightedBlockTypes {
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

  Level4::Level4(Board& b) : BaseLevel{b} {
    _defaultInitialization();
  }

  int Level4::levelNumber() const {
    return 4;
  }

  Block::Type Level4::nextBlockType() {
    int rand = std::rand() % (weightedBlockTypes.size());
    
    return weightedBlockTypes[rand];
  }

  bool Level4::executeCommand(const Command& command) {
    return BaseLevel::executeCommand(command);
  }

  bool Level4::_shouldGenerateHeavyBlocks() const {
    return true;
  }
}

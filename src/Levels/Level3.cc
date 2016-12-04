#include "Block.h"
#include "Level3.h"
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

  Level3::Level3(Board& b) : BaseLevel{b} {
    _defaultInitialization();
  }

  int Level3::levelNumber() const {
    return 3;
  }

  Block::Type Level3::nextBlockType() {
    if (_useSequenceFile) {
      if (_current == _sequence.cend()) {
        _current = _sequence.begin();
      }
      return *_current++;
    }
    else {
      int rand = std::rand() % (weightedBlockTypes.size());
      return weightedBlockTypes[rand];
    }
  }

  bool Level3::executeCommand(const Command& command) {
    return BaseLevel::executeCommand(command);
  }

  bool Level3::_shouldGenerateHeavyBlocks() const {
    return true;
  }
}

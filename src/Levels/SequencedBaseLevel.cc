#include "SequencedBaseLevel.h"
#include "BaseLevel.h"
#include <fstream>
#include "Block.h"

namespace qd {

  namespace {
    const std::map<std::string, Block::Type> blockMap {
      { "I", Block::Type::BLOCK_I },
      { "J", Block::Type::BLOCK_J },
      { "L", Block::Type::BLOCK_L },
      { "O", Block::Type::BLOCK_O },
      { "S", Block::Type::BLOCK_S },
      { "T", Block::Type::BLOCK_T },
      { "Z", Block::Type::BLOCK_Z } 
    };

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

  SequencedBaseLevel::SequencedBaseLevel(Board &b) : BaseLevel(b), _useSequenceFile{false} {
  }

  Block::Type SequencedBaseLevel::nextBlockType() {
    if (_useSequenceFile) {
      if (_current == _sequence.cend()) {
        _current = _sequence.begin();
      }
      return *_current++;
    }
    else {
      std::uniform_int_distribution<> dis(0, (weightedBlockTypes.size() - 1));
    
      auto index = dis(_board.randomEngine());
    
      return weightedBlockTypes[index];
    }
  }

  void SequencedBaseLevel::_setSequence(std::string sequenceFileName) {
    std::ifstream file{ sequenceFileName };
    if (file.fail()) {
      throw std::runtime_error{ "Could not open file: '" + sequenceFileName + "'" };
    }

    std::string nextBlock;
    while (file >> nextBlock) {
      auto blockIter = blockMap.find(nextBlock);
      assert(blockIter != blockMap.end());
      _sequence.emplace_back(blockIter->second);
    }

    assert(_sequence.cbegin() != _sequence.cend());

    _current = _sequence.begin();
  }

  bool SequencedBaseLevel::_shouldGenerateHeavyBlocks() const {
    return true;
  }

  void SequencedBaseLevel::_turnOffRandom(std::string filename) {
    _useSequenceFile = true;
    _setSequence(filename);
  }

  void SequencedBaseLevel::_turnOnRandom() {
    _useSequenceFile = false;
  }
}
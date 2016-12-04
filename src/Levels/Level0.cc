#include "Block.h"
#include "Level0.h"
#include <fstream>
#include <map>
#include <iostream>
#include <stdexcept>
#include <cassert>

namespace qd {

  std::string Level0::sequenceFileName = "sequence.txt";

  Level0::Level0(Board& b) : BaseLevel(b) {
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
    _defaultInitialization();
  }

  int Level0::levelNumber() const {
    return 0;
  }

  Block::Type Level0::nextBlockType() {
    if (_current == _sequence.cend()) {
      _current = _sequence.begin();
    }
    return *_current++;
  }

  bool Level0::executeCommand(const Command& command) {
    return BaseLevel::executeCommand(command);
  }
}

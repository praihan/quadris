#include "Level1.h"

namespace qd {

  int Level1::levelNumber() const {
    return 1;
  }

  Block::Type Level1::nextBlockType() const {

    return Block::Type::EMPTY;
  }

  void Level1::useSequence(const std::string& sequenceFileName) {

  }
}

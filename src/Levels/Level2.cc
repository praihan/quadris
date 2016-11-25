#include "Level2.h"

namespace qd {

  int Level2::levelNumber() const {
    return 2;
  }

  Block::Type Level2::nextBlockType() const {

    return Block::Type::EMPTY;
  }

  void Level2::useSequence(const std::string& sequenceFileName) {

  }
}

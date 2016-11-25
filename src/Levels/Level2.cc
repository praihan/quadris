#include "Level2.h"

namespace qd {

  int Level2::levelNumber() const {
    return 2;
  }

  qd::Block::Type Level2::nextBlockType() const {

    return qd::Block::Type::EMPTY;
  }

  void Level2::useSequence(const std::string& sequenceFileName) {

  }
}

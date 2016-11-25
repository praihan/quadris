#include "Level1.h"

namespace qd {

  int Level1::levelNumber() const {
    return 1;
  }

  qd::Block::Type Level1::nextBlockType() const {

    return qd::Block::Type::EMPTY;
  }

  void Level1::useSequence(const std::string& sequenceFileName) {

  }
}

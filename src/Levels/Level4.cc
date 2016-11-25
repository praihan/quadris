#include "Level4.h"

namespace qd {

  int Level4::levelNumber() const {
    return 4;
  }

  qd::Block::Type Level4::nextBlockType() const {

    return qd::Block::Type::EMPTY;
  }

  void Level4::useSequence(const std::string& sequenceFileName) {

  }
}

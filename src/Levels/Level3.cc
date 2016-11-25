#include "Level3.h"

namespace qd {

  int Level3::levelNumber() const {
    return 3;
  }

  qd::Block::Type Level3::nextBlockType() const {

    return qd::Block::Type::EMPTY;
  }

  void Level3::useSequence(const std::string& sequenceFileName) {

  }
}

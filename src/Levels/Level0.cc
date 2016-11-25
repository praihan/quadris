#include "Level0.h"

namespace qd {

  int Level0::levelNumber() const {
    return 0;
  }

  qd::Block::Type Level0::nextBlockType() const {

    return qd::Block::Type::EMPTY;
  }

  void Level0::useSequence(const std::string& sequenceFileName) {

  }
}

#include "Level3.h"

namespace qd {

  int Level3::levelNumber() const {
    return 3;
  }

  Block::Type Level3::nextBlockType() const {

    return Block::Type::EMPTY;
  }

  void Level3::useSequence(const std::string& sequenceFileName) {

  }
}

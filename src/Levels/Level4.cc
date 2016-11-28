#include "Level4.h"

namespace qd {

  int Level4::levelNumber() const {
    return 4;
  }

  Block::Type Level4::nextBlockType() {

    return Block::Type::EMPTY;
  }

  void Level4::executeCommand(const Command& command) {

  }
}

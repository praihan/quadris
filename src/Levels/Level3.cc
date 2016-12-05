#include "Block.h"
#include "Level3.h"
#include <array>
#include <cstdlib>


namespace qd {
  Level3::Level3(Board& b) : SequencedBaseLevel{b} {
    _useSequenceFile = false;
    _defaultInitialization();
  }

  void Level3::executeCommand(const Command& command) {
    BaseLevel::executeCommand(command);
  }

  int Level3::levelNumber() const {
    return 3;
  }
}

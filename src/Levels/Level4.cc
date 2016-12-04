#include "Level4.h"
#include "Block.h"
#include <array>
#include <cstdlib>

namespace qd {

  Level4::Level4(Board& b) : SequencedBaseLevel{b} {
    _useSequenceFile = false;
    _defaultInitialization();
  }

  int Level4::levelNumber() const {
    return 4;
  }
}

#include "Cell.h"

namespace qd {
  Cell::Cell() : blockType{ Block::Type::EMPTY } { }
  void Cell::clear() {
    blockType = Block::Type::EMPTY;
    owningBlock = nullptr;
  }
}
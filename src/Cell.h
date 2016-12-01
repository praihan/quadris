#ifndef CELL_H_
#define CELL_H_

#include "Block.h"

namespace qd {

  struct Cell {
    Cell();
    Block::Type blockType;
  };
}

#endif

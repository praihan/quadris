#ifndef CELL_H_
#define CELL_H_

#include "Block.h"
#include <memory>

namespace qd {

  struct Cell {
    Cell();
    void clear();

    Block::Type blockType;
    std::shared_ptr<Block> owningBlock;
  };
}

#endif

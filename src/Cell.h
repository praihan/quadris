#ifndef CELL_H_
#define CELL_H_

#include "Block.h"
#include "Event.h"
#include <memory>

namespace qd {

  class Cell {
  public:
    Cell();
    void clear();

    Block::Type blockType;
    std::shared_ptr<Block> owningBlock;
  };
}

#endif

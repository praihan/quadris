#include "BlockO.h"
#include <string>
#include <vector>
#include <memory>
#include "Position.h"

namespace qd {
  BlockO::BlockO() : state{0} {
    occupiedPositions.emplace_back(2, 0); // State 0
    occupiedPositions.emplace_back(2, 1); //
    occupiedPositions.emplace_back(3, 0); // OO
    occupiedPositions.emplace_back(3, 1); // OO
  }

  void BlockO::rotate(Rotation dir) { // O rotation with 1 state
  }

  Block::Type BlockO::type() const {return Block::Type::BLOCK_O;}

  std::unique_ptr<Block> BlockO::clone() {
    return std::make_unique<BlockO>(*this);
  }
}

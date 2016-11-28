#include "BlockI.h"
#include <string>
#include <vector>
#include <memory>
#include "Position.h"

namespace qd {

  BlockI::BlockI() {
    occupiedPositions.emplace_back(0, 0);
    occupiedPositions.emplace_back(0, 1);
    occupiedPositions.emplace_back(0, 2);
    occupiedPositions.emplace_back(0, 3);
  }

  void BlockI::rotate(Rotation) {}
  Block::Type BlockI::type() const {return Block::Type::BLOCK_I;}
  std::unique_ptr<Block> BlockI::clone() {return nullptr;}
}


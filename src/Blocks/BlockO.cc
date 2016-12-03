#include "BlockO.h"
#include <string>
#include <vector>
#include <memory>
#include "Position.h"

namespace qd {
<<<<<<< HEAD
  BlockO::BlockO(const bool heavy) : state{0} {
    occupiedPositions.emplace_back(2, 0); // State 0
    occupiedPositions.emplace_back(2, 1); //
    occupiedPositions.emplace_back(3, 0); // OO
    occupiedPositions.emplace_back(3, 1); // OO
=======
  BlockO::BlockO() : state{0} {
    occupiedPositions.emplace_back(2, 0);
    occupiedPositions.emplace_back(2, 1);
    occupiedPositions.emplace_back(3, 0);
    occupiedPositions.emplace_back(3, 1);
>>>>>>> 72583384af9ff3f00c5c598a0e687a3bb5413e1f
  }

  void BlockO::rotate(Rotation dir) { // O rotation with 1 state
  }

  Block::Type BlockO::type() const {return Block::Type::BLOCK_O;}

  std::unique_ptr<Block> BlockO::clone() {
    return std::make_unique<BlockO>(*this);
  }
}

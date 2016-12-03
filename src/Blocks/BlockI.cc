#include "BlockI.h"
#include <string>
#include <vector>
#include <memory>
#include "Position.h"

namespace qd {
<<<<<<< HEAD
  BlockI::BlockI() : state{0} {
    occupiedPositions.emplace_back(3, 0); // State 0
    occupiedPositions.emplace_back(3, 1); // 
    occupiedPositions.emplace_back(3, 2); // 
    occupiedPositions.emplace_back(3, 3); // IIII
=======
  BlockI::BlockI() : state{0} {
    occupiedPositions.emplace_back(3, 0);
    occupiedPositions.emplace_back(3, 1);
    occupiedPositions.emplace_back(3, 2);
    occupiedPositions.emplace_back(3, 3);
>>>>>>> 72583384af9ff3f00c5c598a0e687a3bb5413e1f
  }

  void BlockI::rotate(Rotation) {
    if (state == 0) {
      occupiedPositions[0] = {0,0}; // I ,State 1
      occupiedPositions[1] = {1,0}; // I
      occupiedPositions[2] = {2,0}; // I
      occupiedPositions[3] = {3,0}; // I
      state = 1;
    }
    else {
      occupiedPositions[0] = {3,0}; // State 0
      occupiedPositions[1] = {3,1}; // 
      occupiedPositions[2] = {3,2}; // 
      occupiedPositions[3] = {3,3}; // IIII
      state = 0;
    }
  }

  Block::Type BlockI::type() const {return Block::Type::BLOCK_I;}

  std::unique_ptr<Block> BlockI::clone() {
    return std::make_unique<BlockI>(*this);
  }
}


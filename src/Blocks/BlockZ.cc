#include "BlockZ.h"
#include <string>
#include <vector>
#include <memory>
#include "Position.h"

namespace qd {
  BlockZ::BlockZ() : state{0} {
    occupiedPositions.emplace_back(2, 0); // State 0
    occupiedPositions.emplace_back(2, 1); //
    occupiedPositions.emplace_back(3, 1); // ZZ
    occupiedPositions.emplace_back(3, 2); //  ZZ
  }

  void BlockZ::rotate(Rotation dir) { // Z rotation with 2 states
    if (state == 0) {
      occupiedPositions[0] = {1,1}; // State 1
      occupiedPositions[1] = {2,1}; //  Z
      occupiedPositions[2] = {2,0}; // ZZ
      occupiedPositions[3] = {3,0}; // Z
      state = 1;
    }
    else {
      occupiedPositions[0] = {2,0}; // State 0
      occupiedPositions[1] = {2,1}; //
      occupiedPositions[2] = {3,1}; // ZZ
      occupiedPositions[3] = {3,2}; //  ZZ
      state = 0;
    }
  }

  Block::Type BlockZ::type() const {return Block::Type::BLOCK_Z;}

  std::unique_ptr<Block> BlockZ::clone() {
    return std::make_unique<BlockZ>(*this);
  }
}

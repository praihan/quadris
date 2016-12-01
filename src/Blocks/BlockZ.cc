#include "BlockZ.h"
#include <string>
#include <vector>
#include <memory>
#include "Position.h"

namespace qd {
  BlockZ::BlockZ() : state(0) {
    occupiedPositions.emplace_back(2, 0);
    occupiedPositions.emplace_back(2, 1);
    occupiedPositions.emplace_back(3, 1);
    occupiedPositions.emplace_back(3, 2);
  }

  void BlockZ::rotate(Rotation dir) { // Z rotation with 2 states
    if (state == 0) {
      occupiedPositions[0] = {1,1};
      occupiedPositions[1] = {2,1};
      occupiedPositions[2] = {2,0};
      occupiedPositions[3] = {3,0};
      state = 1;
    }
    else {
      occupiedPositions[0] = {2,0};
      occupiedPositions[1] = {2,1};
      occupiedPositions[2] = {3,1};
      occupiedPositions[3] = {3,2};
      state = 0;
    }
  }

  Block::Type BlockZ::type() const {return Block::Type::BLOCK_Z;}

  std::unique_ptr<Block> BlockZ::clone() {
    return std::make_unique<BlockZ>(*this);
  }
}
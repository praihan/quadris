#include "BlockS.h"
#include <string>
#include <vector>
#include <memory>
#include "Position.h"

namespace qd {
  BlockS::BlockS(const bool heavy) : Block(heavy), state(0) {
    occupiedPositions.emplace_back(2, 2);
    occupiedPositions.emplace_back(2, 1);
    occupiedPositions.emplace_back(3, 1);
    occupiedPositions.emplace_back(3, 0);
  }

  void BlockS::rotate(Rotation dir) { // S rotation with 2 states
    if (state == 0) {
      occupiedPositions[0] = {3,1};
      occupiedPositions[1] = {2,1};
      occupiedPositions[2] = {2,0};
      occupiedPositions[3] = {1,0};
      state = 1;
    }
    else {
      occupiedPositions[0] = {2,2};
      occupiedPositions[1] = {2,1};
      occupiedPositions[2] = {3,1};
      occupiedPositions[3] = {3,0};
      state = 0;
    }
  }

  Block::Type BlockS::type() const {return Block::Type::BLOCK_S;}

  std::unique_ptr<Block> BlockS::clone() {
    return std::make_unique<BlockS>(*this);
  }
}
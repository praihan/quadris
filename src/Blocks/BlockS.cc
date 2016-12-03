#include "BlockS.h"
#include <string>
#include <vector>
#include <memory>
#include "Position.h"

namespace qd {
  BlockS::BlockS() : state{0} {
    occupiedPositions.emplace_back(2, 2); // State 0
    occupiedPositions.emplace_back(2, 1); //
    occupiedPositions.emplace_back(3, 1); //  SS
    occupiedPositions.emplace_back(3, 0); // SS
  }

  void BlockS::rotate(Rotation dir) { // S rotation with 2 states
    if (state == 0) {
      occupiedPositions[0] = {3,1}; // State 1
      occupiedPositions[1] = {2,1}; // S
      occupiedPositions[2] = {2,0}; // SS
      occupiedPositions[3] = {1,0}; //  S
      state = 1;
    }
    else {
      occupiedPositions[0] = {2,2}; // State 0
      occupiedPositions[1] = {2,1}; //
      occupiedPositions[2] = {3,1}; //  SS
      occupiedPositions[3] = {3,0}; // SS
      state = 0;
    }
  }

  Block::Type BlockS::type() const {return Block::Type::BLOCK_S;}

  std::unique_ptr<Block> BlockS::clone() {
    return std::make_unique<BlockS>(*this);
  }
}

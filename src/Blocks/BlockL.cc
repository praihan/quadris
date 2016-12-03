#include "BlockL.h"
#include <string>
#include <vector>
#include <memory>
#include "Position.h"

namespace qd {
  BlockL::BlockL() : state{0} {
    occupiedPositions.emplace_back(2, 2); // State 0
    occupiedPositions.emplace_back(3, 2); // 
    occupiedPositions.emplace_back(3, 1); // L
    occupiedPositions.emplace_back(3, 0); // LLL
  }

  void BlockL::rotate(Rotation dir) { // L rotation with 4 states
    if (dir == Block::Rotation::CLOCKWISE) { // Clockwise rotation
      if (state == 0) {
        occupiedPositions[0] = {3,1}; // State 1
        occupiedPositions[1] = {3,0}; // LL
        occupiedPositions[2] = {2,0}; // L
        occupiedPositions[3] = {1,0}; // L
        state = 1;
      }
      else if (state == 1) {
        occupiedPositions[0] = {3,0}; // State 2
        occupiedPositions[1] = {2,0}; //
        occupiedPositions[2] = {2,1}; // LLL
        occupiedPositions[3] = {2,2}; //   L
        state = 2;
      }
      else if (state == 2) {
        occupiedPositions[0] = {1,0}; // State 3
        occupiedPositions[1] = {1,1}; //  L
        occupiedPositions[2] = {2,1}; //  L
        occupiedPositions[3] = {3,1}; // LL
        state = 3;
      }
      else {
        occupiedPositions[0] = {2,2}; // State 0
        occupiedPositions[1] = {3,2}; //
        occupiedPositions[2] = {3,1}; // L
        occupiedPositions[3] = {3,0}; // LLL
        state = 0;
      }
    }
    else if (dir == Block::Rotation::COUNTER_CLOCKWISE) { // Counterclockwise rotation
      if (state == 0) {
        occupiedPositions[0] = {1,0}; // State 3
        occupiedPositions[1] = {1,1}; //  L
        occupiedPositions[2] = {2,1}; //  L
        occupiedPositions[3] = {3,1}; // LL
        state = 3;
      }
      else if (state == 1) {
        occupiedPositions[0] = {2,2}; // State 0
        occupiedPositions[1] = {3,2}; //
        occupiedPositions[2] = {3,1}; // L
        occupiedPositions[3] = {3,0}; // LLL
        state = 0;
      }
      else if (state == 2) {
        occupiedPositions[0] = {3,1}; // State 1
        occupiedPositions[1] = {3,0}; // LL
        occupiedPositions[2] = {2,0}; // L
        occupiedPositions[3] = {1,0}; // L
        state = 1;
      }
      else {
        occupiedPositions[0] = {3,0}; // State 2
        occupiedPositions[1] = {2,0}; //
        occupiedPositions[2] = {2,1}; // LLL
        occupiedPositions[3] = {2,2}; //   L
        state = 2;
      }
    }
  }

  Block::Type BlockL::type() const {return Block::Type::BLOCK_L;}

  std::unique_ptr<Block> BlockL::clone() {
    return std::make_unique<BlockL>(*this);
  }
}

#include "BlockT.h"
#include <string>
#include <vector>
#include <memory>
#include "Position.h"

namespace qd {
  BlockT::BlockT() : state{0} {
    occupiedPositions.emplace_back(2, 1); // State 0
    occupiedPositions.emplace_back(3, 0); //
    occupiedPositions.emplace_back(3, 1); //  T
    occupiedPositions.emplace_back(3, 2); // TTT
  }

  void BlockT::rotate(Rotation dir) { // T rotation with 4 states
    if (dir == Block::Rotation::CLOCKWISE) { // Clockwise rotation
      if (state == 0) {
        occupiedPositions[0] = {2,1}; // State 1
        occupiedPositions[1] = {1,0}; // T
        occupiedPositions[2] = {2,0}; // TT
        occupiedPositions[3] = {3,0}; // T
        state = 1;
      }
      else if (state == 1) {
        occupiedPositions[0] = {3,1}; // State 2
        occupiedPositions[1] = {2,0}; //
        occupiedPositions[2] = {2,1}; // TTT
        occupiedPositions[3] = {2,2}; //  T
        state = 2;
      }
      else if (state == 2) {
        occupiedPositions[0] = {2,0}; // State 3
        occupiedPositions[1] = {1,1}; //  T
        occupiedPositions[2] = {2,1}; // TT
        occupiedPositions[3] = {3,1}; //  T
        state = 3;
      }
      else {
        occupiedPositions[0] = {2,1}; // State 0
        occupiedPositions[1] = {3,0}; //
        occupiedPositions[2] = {3,1}; //  T
        occupiedPositions[3] = {3,2}; // TTT
        state = 0;
      }
    }
    else if (dir == Block::Rotation::COUNTER_CLOCKWISE) { // Counterclockwise rotation
      if (state == 0) {
        occupiedPositions[0] = {2,0}; // State 3
        occupiedPositions[1] = {1,1}; //  T
        occupiedPositions[2] = {2,1}; // TT
        occupiedPositions[3] = {3,1}; //  T
        state = 3;
      }
      else if (state == 1) {
        occupiedPositions[0] = {2,1}; // State 0
        occupiedPositions[1] = {3,0}; //
        occupiedPositions[2] = {3,1}; //  T
        occupiedPositions[3] = {3,2}; // TTT
        state = 0;
      }
      else if (state == 2) {
        occupiedPositions[0] = {2,1}; // State 1
        occupiedPositions[1] = {1,0}; // T
        occupiedPositions[2] = {2,0}; // TT
        occupiedPositions[3] = {3,0}; // T
        state = 1;
      }
      else {
        occupiedPositions[0] = {3,1}; // State 2
        occupiedPositions[1] = {2,0}; //
        occupiedPositions[2] = {2,1}; // TTT
        occupiedPositions[3] = {2,2}; //  T
        state = 2;
      }
    }
  }

  Block::Type BlockT::type() const {return Block::Type::BLOCK_T;}

  std::unique_ptr<Block> BlockT::clone() {
    return std::make_unique<BlockT>(*this);
  }
}

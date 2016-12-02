#include "BlockJ.h"
#include <string>
#include <vector>
#include <memory>
#include "Position.h"

namespace qd {
  BlockJ::BlockJ(const bool heavy) : Block(heavy), state(0) {
    occupiedPositions.emplace_back(2, 0);
    occupiedPositions.emplace_back(3, 0);
    occupiedPositions.emplace_back(3, 1);
    occupiedPositions.emplace_back(3, 2);
  }

  void BlockJ::rotate(Rotation dir) { // J rotation with 4 states
    if (dir == Block::Rotation::CLOCKWISE) { // Clockwise rotation
      if (state == 0) {
        occupiedPositions[0] = {1,1};
        occupiedPositions[1] = {1,0};
        occupiedPositions[2] = {2,0};
        occupiedPositions[3] = {3,0};
        state = 1;
      }
      else if (state == 1) {
        occupiedPositions[0] = {3,2};
        occupiedPositions[1] = {2,2};
        occupiedPositions[2] = {2,1};
        occupiedPositions[3] = {2,0};
        state = 2;
      }
      else if (state == 2) {
        occupiedPositions[0] = {3,0};
        occupiedPositions[1] = {3,1};
        occupiedPositions[2] = {2,1};
        occupiedPositions[3] = {1,1};
        state = 3;
      }
      else {
        occupiedPositions[0] = {2,0};
        occupiedPositions[1] = {3,0};
        occupiedPositions[2] = {3,1};
        occupiedPositions[3] = {3,2};
        state = 0;
      }
    }
    else if (dir == Block::Rotation::COUNTER_CLOCKWISE) { // Counterclockwise rotation
      if (state == 0) {
        occupiedPositions[0] = {3,0};
        occupiedPositions[1] = {3,1};
        occupiedPositions[2] = {2,1};
        occupiedPositions[3] = {1,1};
        state = 3;
      }
      else if (state == 1) {
        occupiedPositions[0] = {2,0};
        occupiedPositions[1] = {3,0};
        occupiedPositions[2] = {3,1};
        occupiedPositions[3] = {3,2};
        state = 0;
      }
      else if (state == 2) {
        occupiedPositions[0] = {1,1};
        occupiedPositions[1] = {1,0};
        occupiedPositions[2] = {2,0};
        occupiedPositions[3] = {3,0};
        state = 1;
      }
      else {
        occupiedPositions[0] = {3,2};
        occupiedPositions[1] = {2,2};
        occupiedPositions[2] = {2,1};
        occupiedPositions[3] = {2,0};
        state = 2;
      }
    }
  }

  Block::Type BlockJ::type() const {return Block::Type::BLOCK_J;}

  std::unique_ptr<Block> BlockJ::clone() {
    return std::make_unique<BlockJ>(*this);
  }
}


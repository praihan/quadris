#include "Position.h"

namespace qd {
  Position operator+(const Position& p1, const Position& p2) {
    Position ret;
    ret.x = p1.x + p2.x;
    ret.y = p1.y + p2.y;
    return ret;
  }
}
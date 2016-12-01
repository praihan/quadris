#include "Position.h"

namespace qd {
  Position::Position() : Position{0, 0} { }
  Position::Position(int row, int col) : row{row}, col{col} { }

  Position operator+(const Position& p1, const Position& p2) {
    Position ret;
    ret.row = p1.row + p2.row;
    ret.col = p1.col + p2.col;
    return ret;
  }

  bool operator==(const Position& p1, const Position& p2) {
    return p1.row == p2.row && p1.col == p2.col;
  }
  bool operator!=(const Position& p1, const Position& p2) {
    return !(p1 == p2);
  }
  std::ostream& operator<<(std::ostream& os, const Position& p) {
    os << "Position(row=" << p.row << ",col=" << p.col << ")";
    return os;
  }
}

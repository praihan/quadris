#ifndef POSITION_H_
#define POSITION_H_

#include <iostream>

namespace qd {

  struct Position {
    Position();
    Position(int row, int col);
    int row;
    int col;
  };

  Position operator+(const Position& p1, const Position& p2);
  bool operator==(const Position& p1, const Position& p2);
  bool operator!=(const Position& p1, const Position& p2);
  std::ostream& operator<<(std::ostream&, const Position&);

}

#endif


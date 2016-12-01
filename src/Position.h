#ifndef POSITION_H_
#define POSITION_H_

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

}

#endif


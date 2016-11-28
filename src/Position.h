#ifndef POSITION_H_
#define POSITION_H_

namespace qd {

  struct Position {
    int x;
    int y;
  };

  Position operator+(const Position& p1, const Position& p2);
  bool operator==(const Position& p1, const Position& p2);
  bool operator!=(const Position& p1, const Position& p2);

}

#endif


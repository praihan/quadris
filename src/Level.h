#ifndef LEVEL_H_
#define LEVEL_H_

#include "Command.h"

namespace qd {
  class Board;

  class Level {
  public:
    Level(Board&);
    virtual int levelNumber() const = 0;
    virtual void executeCommand(const Command& command) = 0;
  protected:
    Board& _board;
  };

}

#endif // LEVEL_H_


#ifndef LEVEL_H_
#define LEVEL_H_

#include "Board.h"
#include "Command.h"

namespace qd {

  class Level {
  public:
    Level(Board&);
    virtual void executeCommand(const Command& command) = 0;
  protected:
    Board& _board;
  };

}

#endif // LEVEL_H_


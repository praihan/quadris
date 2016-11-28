#ifndef LEVEL_H_
#define LEVEL_H_

#include "Board.h"
#include "Command.h"

namespace qd {

  class Level {
  public:
    virtual void executeCommand(Board& sender, const Command& command) = 0;
  };

}

#endif // LEVEL_H_


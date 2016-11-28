#ifndef BASELEVEL_H_
#define BASELEVEL_H_

#include "Level.h"
#include "Board.h"
#include "Command.h"

namespace qd {
  class BaseLevel : public Level {
    virtual int levelNumber() const = 0;
    virtual Block::Type nextBlockType() = 0;
  };
}

#endif // BASELEVEL_H_
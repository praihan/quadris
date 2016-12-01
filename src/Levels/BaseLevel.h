#ifndef BASELEVEL_H_
#define BASELEVEL_H_

#include "Level.h"
#include "Board.h"
#include "Command.h"
#include "Position.h"
#include "Block.h"

/*
      UNKNOWN,
      LEFT,
      RIGHT,
      DOWN,
      CLOCKWISE,
      COUNTER_CLOCKWISE,
      DROP,
*/

namespace qd {
  class BaseLevel : public Level {
  public:
    using Level::Level;
  protected:
    
    virtual int levelNumber() const = 0;
    virtual Block::Type nextBlockType() = 0;

    virtual void executeCommand(const Command& command) override;

    bool _isCellOccupied(const Position &p) const;
    bool _canMoveLeft(const Block &b) const;
    bool _canMoveRight(const Block &b) const;
    bool _canMoveDown(const Block &b) const;
  };
}

#endif // BASELEVEL_H_

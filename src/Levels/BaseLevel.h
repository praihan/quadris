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

    virtual int levelNumber() const = 0;
    virtual Block::Type nextBlockType() = 0;
    virtual bool executeCommand(const Command& command) override;
  protected:
    enum class Direction {
      DOWN,
      LEFT,
      RIGHT
    };

    bool _isCellOccupied(const Position& p) const;
    bool _isCellInBound(const Position& p) const;
    bool _isValidBlock(const Block &b) const;
    bool _canMove(const Block &b, Direction d) const;
    void _moveBlock(const Position& dest);
    void _ensureActiveBlock();

  };
}

#endif // BASELEVEL_H_

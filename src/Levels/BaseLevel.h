#ifndef BASELEVEL_H_
#define BASELEVEL_H_

#include "Level.h"
#include "Board.h"
#include "Command.h"
#include "Position.h"
#include "Block.h"

namespace qd {
  class BaseLevel : public Level {
  public:
    BaseLevel(Board& b);

    virtual int levelNumber() const = 0;
    virtual Block::Type nextBlockType() = 0;
    virtual bool executeCommand(const Command& command) override;

  protected:
    enum class Direction {
      DOWN,
      LEFT,
      RIGHT
    };

    // this is common initialization that is shared among the levels.
    // we place this here so that the subclasses can call these
    // in their constructors. our constructor isn't allowed to do this
    // by itself because the subclasses' v-tables aren't set up
    // when our constructor is executed.
    void _defaultInitialization();

    bool _isCellOccupied(const Position& p) const;
    bool _isCellInBound(const Position& p) const;
    bool _isValidBlock(const Block &b) const;
    bool _canMove(const Block &b, Direction d) const;
    void _moveBlock(const Position& dest);
    void _ensureBlocksGenerated();

    virtual bool _shouldGenerateHeavyBlocks() const;

    Block::Type _nextBlockType;

  };
}

#endif // BASELEVEL_H_

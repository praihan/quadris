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
    /// \cond INTERNAL
    enum class Direction {
      DOWN,
      LEFT,
      RIGHT
    };

    /// Common initialization that is shared among the levels.
    /// We place this here so that the subclasses can call these
    /// in their constructors. Our constructor isn't allowed to do this
    /// by itself because the subclasses' v-tables aren't set up
    /// when our constructor is executed.
    void _defaultInitialization();

    virtual void _checkScoring();
    virtual bool _checkGameEnd();

    /// Determines if a Cell denoted by the given Position is not empty.
    bool _isCellOccupied(const Position& p) const;
    /// Determines if the given Position corresponds to a valid Cell
    /// coordinate.
    bool _isCellInBound(const Position& p) const;
    /// Determines if the given Block is in a valid position.
    /// A Block is considered valid iff its occupied positions are currently
    /// empty.
    bool _isValidBlock(const Block &b) const;
    /// Determines the lowest row before hitting the bottom of grid or an active cell
    int _getHeight(const int col) const;
    int _ifHole(const int col) const;
    /// Determines if the given Block can move in the given Direction and still
    /// be valid.
    bool _canMove(const Block &b, Direction d) const;
    /// Ensures that Board::activeBlockPtr() and Board::nextBlockPtr() are
    /// constructed. If either of them needs to be constructed then
    /// _nextBlockType and nextBlockType() are used. This will also raise
    /// Board::nextBlockTypeGenerated() if necessary.
    void _ensureBlocksGenerated();
    /// A function that is should be overriden to return if Blocks generated by
    /// this Level are "heavy".
    virtual bool _shouldGenerateHeavyBlocks() const;

    /// \endcond
  };
}

#endif // BASELEVEL_H_

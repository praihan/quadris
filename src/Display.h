#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Event.h"
#include "Board.h"
#include "Optional.h"
#include "Blocks/BlockI.h"
#include "Blocks/BlockJ.h"
#include "Blocks/BlockL.h"
#include "Blocks/BlockO.h"
#include "Blocks/BlockS.h"
#include "Blocks/BlockT.h"
#include "Blocks/BlockZ.h"
#include <map>
#include <array>

namespace qd {

  class Block;

  class Display {
  public:
    Display(const Board&);

  protected:
    virtual void onCellsUpdated(const Board::CellGrid&, const Block*);
    virtual void onScoreUpdated(int score);
    virtual void onHiScoreUpdated(int hiScore);
    virtual void onNextBlockGenerated(Block::Type);
    virtual void onGameStarted();
    virtual void onGameEnded();
    virtual void onLevelChanged(int level);
    virtual void onHint(const std::vector<Position>&);

  public:
    virtual void outputDisplay() = 0;

  protected:
    ObserverSlot<> _gameResetSlot;
    ObserverSlot<const Board::CellGrid&, const Block*> _cellsUpdatedSlot;
    ObserverSlot<int> _scoreUpdatedSlot;
    ObserverSlot<int> _hiScoreUpdatedSlot;
    ObserverSlot<Block::Type> _nextBlockGeneratedSlot;
    ObserverSlot<> _gameStartedSlot;
    ObserverSlot<> _gameEndedSlot;
    ObserverSlot<int> _levelChangedSlot;
    ObserverSlot<const std::vector<Position>&> _hintProvidedSlot;

    Optional<int> _level;
    Optional<Block::Type> _nextBlockType;
    Optional<int> _score;
    Optional<int> _hiScore;

    std::array<std::array<Block::Type, BOARD_WIDTH>, BOARD_HEIGHT + 3> _boardState;

    static const BlockI _sampleBlockI;
    static const BlockJ _sampleBlockJ;
    static const BlockL _sampleBlockL;
    static const BlockO _sampleBlockO;
    static const BlockS _sampleBlockS;
    static const BlockT _sampleBlockT;
    static const BlockZ _sampleBlockZ;

    static const std::map<Block::Type, const Block*> sampleBlocks;
  };

}

#endif


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Event.h"
#include "Board.h"

namespace qd {

  class Block;

  class Display {
  public:
    Display(const Board&);

  protected:
    virtual void onCellsUpdated(const Board::CellGrid&, const Block*) = 0;
    virtual void onScoreUpdated(int score) = 0;
    virtual void onHiScoreUpdated(int hiScore) = 0;
    virtual void onNextBlockGenerated(Block::Type) = 0;
    virtual void onGameStarted() = 0;
    virtual void onGameEnded() = 0;
    virtual void onLevelChanged(int level) = 0;

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

    int _level;
  };

}

#endif


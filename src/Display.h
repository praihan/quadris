#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Event.h"
#include "Board.h"

namespace qd {

  class Display {
  protected:
    Display(const Board&);

    virtual void onCellsUpdated(const Board::CellGrid&) = 0;
    virtual void onScoreUpdated(int score) = 0;
    virtual void onHiScoreUpdated(int hiScore) = 0;
    virtual void onNextBlockGenerated() = 0;
    virtual void onGameReset() = 0;

  protected:
    ObserverSlot<> _gameResetSlot;
    ObserverSlot<const Board::CellGrid&> _cellsUpdatedSlot;
    ObserverSlot<int> _scoreUpdatedSlot;
    ObserverSlot<int> _hiScoreUpdatedSlot;
    ObserverSlot<> _nextBlockGeneratedSlot;
    ObserverSlot<> _gameEndedSlot;
  };

}

#endif


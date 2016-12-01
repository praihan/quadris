#include "Display.h"
#include "Board.h"

namespace qd {

  Display::Display(const Board& board) {
  }
/*
    class Display {
  protected:
    Display(const Board&);

    virtual void onGameReset() = 0;
    virtual void onCellsUpdated(const Board::CellGrid&) = 0;
    virtual void onScoreUpdated() = 0;
    virtual void onHiScoreUpdated() = 0;
    virtual void onNextBlockGenerated() = 0;

  protected:
    ObserverSlot<> _gameResetSlot;
    ObserverSlot<const Board::CellGrid&> _cellsUpdatedSlot;
    ObserverSlot<> _scoreUpdatedSlot;
    ObserverSlot<> _hiScoreUpdatedSlot;
    ObserverSlot<> _nextBlockGeneratedSlot;
  };
  */
}
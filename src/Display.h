#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Event.h"
#include "Board.h"

namespace qd {

  class Display {
  protected:
    Display(const Board&);

    virtual void onGameStarted() = 0;
    virtual void onCellUpdated() = 0;
    virtual void onScoreUpdated() = 0;
    virtual void onHiScoreUpdated() = 0;
    virtual void onNextBlockGenerated() = 0;
    virtual void onGameEnded() = 0;

  protected:
    ObserverSlot<> _gameStartSlot;
    ObserverSlot<> _cellUpdatedSlot;
    ObserverSlot<> _scoreUpdatedSlot;
    ObserverSlot<> _hiScoreUpdatedSlot;
    ObserverSlot<> _nextBlockGeneratedSlot;
    ObserverSlot<> _gameEndedSlot;
  };

}

#endif


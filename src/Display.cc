#include "Display.h"
#include "Board.h"
#include <functional>

namespace qd {

  Display::Display(const Board& board) {
    board.cellsUpdated().addObserver(
      _cellsUpdatedSlot, std::bind(&Display::onCellsUpdated, this, std::placeholders::_1)
    );
    board.scoreUpdated().addObserver(
      _scoreUpdatedSlot, std::bind(&Display::onScoreUpdated, this, std::placeholders::_1)
    );
    board.hiScoreUpdated().addObserver(
      _hiScoreUpdatedSlot, std::bind(&Display::onHiScoreUpdated, this, std::placeholders::_1)
    );
    board.nextBlockGenerated().addObserver(
      _nextBlockGeneratedSlot, std::bind(&Display::onNextBlockGenerated, this, std::placeholders::_1)
    );
    board.gameReset().addObserver(
      _gameResetSlot, std::bind(&Display::onGameReset, this)
    );
  }
}
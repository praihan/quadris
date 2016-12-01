#include "Display.h"
#include "Board.h"
#include <functional>

namespace qd {

  Display::Display(const Board& board) {
    board.cellsUpdated().addObserver(
      _cellsUpdatedSlot, std::bind(
        &Display::onCellsUpdated, this,
        std::placeholders::_1, std::placeholders::_2
      )
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
    board.gameStarted().addObserver(
      _gameStartedSlot, std::bind(&Display::onGameStarted, this)
    );
    board.gameEnded().addObserver(
      _gameEndedSlot, std::bind(&Display::onGameEnded, this)
    );
    board.levelChanged().addObserver(
      _levelChangedSlot, std::bind(&Display::onLevelChanged, this, std::placeholders::_1)
    );
  }
}
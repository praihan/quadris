#ifndef BOARD_H_
#define BOARD_H_

#include "Event.h"
#include "Block.h"
#include "Level.h"
#include "Score.h"
#include "Cell.h"
#include <array>
#include <memory>


namespace qd {

  class Board {
  private:
    std::array<std::array<Cell, 11>, 18> _cells;
    std::unique_ptr<Block> _activeBlock;
    Score _score;
    std::unique_ptr<Level> _level;
    int _seed;

    Event<> _gameStarted;
    Event<> _cellUpdated;
    Event<> _scoreUpdated;
    Event<> _highScoreUpdated;
    Event<> _nextBlockGenerated;
    Event<> _gameEnded;

  public:
    reset();
    executeCommand(Command command);
    seedWith(int seed);
    setStartLevel(int level);

    const Event<>& gameStarted() const;
    const Event<>& cellUpdated() const;
    const Event<>& scoreUpdated() const;
    const Event<>& highScoreUpdated() const;
    const Event<>& nextBlockGenerated() const;
    const Event<>& gameEnded() const;
  };

}

#endif


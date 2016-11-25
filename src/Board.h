#ifndef BOARD_H_
#define BOARD_H_

#include "Event.h"
#include "Block.h"
#include "Level.h"
#include "Score.h"
#include "Cell.h"
#include "Command.h"
#include "BoardInitArgs.h"
#include <array>
#include <memory>
#include <cstddef>

namespace qd {

  constexpr std::size_t BOARD_WIDTH = 11;
  constexpr std::size_t BOARD_HEIGHT = 15;

  class Board {
  public:
    Board(const BoardInitArgs&);

    void reset();
    void executeCommand(const Command& command);
    void seedWith(int seed);
    void setStartLevel(int level);

    const Event<>& gameStarted() const;
    const Event<>& cellUpdated() const;
    const Event<>& scoreUpdated() const;
    const Event<>& highScoreUpdated() const;
    const Event<>& nextBlockGenerated() const;
    const Event<>& gameEnded() const;

  private:
    std::array<std::array<Cell, BOARD_HEIGHT>, BOARD_WIDTH + 3> _cells;
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

    ObserverSlot<> _scoreUpdatedSlot;
    ObserverSlot<> _hiScoreUpdatedSlot;

  };

}

#endif


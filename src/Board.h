#ifndef BOARD_H_
#define BOARD_H_

#include "Event.h"
#include "Score.h"
#include "Cell.h"
#include <array>
#include <memory>
#include <cstddef>
#include <functional>
#include <map>
#include <random>

namespace qd {

  class Level;
  class Block;
  class Command;

  constexpr std::size_t BOARD_WIDTH = 11;
  constexpr std::size_t BOARD_HEIGHT = 15;

  using LevelFactory = std::function<std::unique_ptr<Level>>;
  using CellGrid = std::array<std::array<Cell, BOARD_HEIGHT>, BOARD_WIDTH + 3>;
  using RandomEngine = std::mt19937;

  struct BoardInitArgs {
    int seed;
    int levelNumber;
  };

  class Board {
  public:
    Board(const BoardInitArgs&);

    void reset();
    void executeCommand(const Command& command);

    void registerLevel(int levelNumber, const LevelFactory& factory);

    CellGrid& cells();
    const CellGrid& cells() const;

    Score& score();
    const Score& score() const;

    RandomEngine& randomEngine();
    const RandomEngine& randomEngine() const;

  private:
    CellGrid _cells;
    std::unique_ptr<Block> _activeBlock;
    Score _score;
    std::unique_ptr<Level> _level;
    RandomEngine _randomEngine;
    std::map<int, LevelFactory> _levelFactories;

    Event<> _gameStarted;
    Event<> _cellUpdated;
    Event<> _scoreUpdated;
    Event<> _highScoreUpdated;
    Event<> _nextBlockGenerated;
    Event<> _gameEnded;

    ObserverSlot<> _scoreUpdatedSlot;
    ObserverSlot<> _hiScoreUpdatedSlot;

  public:
    const Event<>& gameStarted() const;
    Event<>& gameStarted();
    const Event<>& cellUpdated() const;
    Event<>& cellUpdated();
    const Event<>& scoreUpdated() const;
    Event<>& scoreUpdated();
    const Event<>& highScoreUpdated() const;
    Event<>& highScoreUpdated();
    const Event<>& nextBlockGenerated() const;
    Event<>& nextBlockGenerated();
    const Event<>& gameEnded() const;
    Event<>& gameEnded();
  };

}

#endif


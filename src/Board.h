#ifndef BOARD_H_
#define BOARD_H_

#include "Event.h"
#include "Score.h"
#include "Cell.h"
#include "Block.h"
#include "Level.h"
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

  class Board {
  public:
    struct InitArgs {
      int seed;
      int levelNumber;
    };
    using LevelFactory = std::function<std::unique_ptr<Level>(Board&)>;
    using CellGrid = std::array<std::array<Cell, BOARD_HEIGHT>, BOARD_WIDTH + 3>;
    using RandomEngine = std::mt19937;

    Board(const InitArgs&);

    void reset();
    void executeCommand(const Command& command);

    void registerLevel(int levelNumber, const LevelFactory& factory);

    CellGrid& cells();
    const CellGrid& cells() const;

    Score& score();
    const Score& score() const;

    RandomEngine& randomEngine();
    const RandomEngine& randomEngine() const;

    const Event<>& gameStarted() const;
    Event<>& gameStarted();
    const Event<>& cellUpdated() const;
    Event<>& cellUpdated();
    const Event<int>& scoreUpdated() const;
    Event<int>& scoreUpdated();
    const Event<int>& hiScoreUpdated() const;
    Event<int>& hiScoreUpdated();
    const Event<>& nextBlockGenerated() const;
    Event<>& nextBlockGenerated();
    const Event<>& gameEnded() const;
    Event<>& gameEnded();

  private:
    CellGrid _cells;
    std::unique_ptr<Block> _activeBlock;
    Score _score;
    std::unique_ptr<Level> _level;
    RandomEngine _randomEngine;
    std::map<int, LevelFactory> _levelFactories;

    Event<> _gameStarted;
    Event<> _cellUpdated;
    Event<int> _scoreUpdated;
    Event<int> _hiScoreUpdated;
    Event<> _nextBlockGenerated;
    Event<> _gameEnded;

    ObserverSlot<int> _scoreUpdatedSlot;
    ObserverSlot<int> _hiScoreUpdatedSlot;

  private:
    void _changeLevelTo(int levelNumber);

    // All these do are forward the event from the Score to our own observers
    void _scoreUpdatedObserver(int score);
    void _hiScoreUpdatedObserver(int score);
  };

}

#endif


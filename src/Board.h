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
    using LevelFactory = std::function<std::unique_ptr<Level>(Board&)>;
    using CellGrid = std::array<std::array<Cell, BOARD_WIDTH>, BOARD_HEIGHT + 3>;
    using RandomEngine = std::mt19937;

    struct InitArgs {
      int seed;
      int levelNumber;
    };

    Board(const InitArgs&);

    void start();
    void reset();
    void executeCommand(const Command& command);

    void registerLevel(int levelNumber, const LevelFactory& factory);

    CellGrid& cells();
    const CellGrid& cells() const;

    Score& score();
    const Score& score() const;

    RandomEngine& randomEngine();
    const RandomEngine& randomEngine() const;

    std::unique_ptr<Block>& activeBlockPtr();
    const std::unique_ptr<Block>& activeBlockPtr() const;

    const Event<const CellGrid&, const Block*>& cellsUpdated() const;
    Event<const CellGrid&, const Block*>& cellsUpdated();
    const Event<int>& scoreUpdated() const;
    Event<int>& scoreUpdated();
    const Event<int>& hiScoreUpdated() const;
    Event<int>& hiScoreUpdated();
    const Event<Block::Type>& nextBlockGenerated() const;
    Event<Block::Type>& nextBlockGenerated();
    const Event<>& gameStarted() const;
    Event<>& gameStarted();
    const Event<>& gameEnded() const;
    Event<>& gameEnded();
    const Event<int>& levelChanged() const;
    Event<int>& levelChanged();

  private:
    CellGrid _cells;
    std::unique_ptr<Block> _activeBlock;
    Score _score;
    std::unique_ptr<Level> _level;
    RandomEngine _randomEngine;
    std::map<int, LevelFactory> _levelFactories;

    Event<const CellGrid&, const Block*> _cellsUpdated;
    Event<int> _scoreUpdated;
    Event<int> _hiScoreUpdated;
    Event<Block::Type> _nextBlockGenerated;
    Event<> _gameStarted;
    Event<> _gameEnded;
    Event<int> _levelChanged;

    ObserverSlot<int> _scoreUpdatedSlot;
    ObserverSlot<int> _hiScoreUpdatedSlot;

    int _currentLevelNumber;

  private:
    bool _changeLevelTo(int levelNumber);

    // All these do are forward the event from the Score to our own observers
    void _scoreUpdatedObserver(int score);
    void _hiScoreUpdatedObserver(int score);
  };

}

#endif


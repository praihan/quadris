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

    CellGrid& cells() { return _cells; }
    const CellGrid& cells() const { return _cells; }

    Score& score() { return _score; }
    const Score& score() const { return _score; }

    RandomEngine& randomEngine() { return _randomEngine; }
    const RandomEngine& randomEngine() const { return _randomEngine; }

    std::unique_ptr<Block>& activeBlockPtr() { return _activeBlock; }
    const std::unique_ptr<Block>& activeBlockPtr() const { return _activeBlock; }
    std::unique_ptr<Block>& nextBlockPtr() { return _nextBlock; }
    const std::unique_ptr<Block>& nextBlockPtr() const { return _nextBlock; }

    const Event<const CellGrid&, const Block*>& cellsUpdated() const { return _cellsUpdated; }
    Event<const CellGrid&, const Block*>& cellsUpdated() { return _cellsUpdated; }
    const Event<int>& scoreUpdated() const { return _scoreUpdated; }
    Event<int>& scoreUpdated() { return _scoreUpdated; }
    const Event<int>& hiScoreUpdated() const { return _hiScoreUpdated; }
    Event<int>& hiScoreUpdated() { return _hiScoreUpdated; }
    const Event<Block::Type>& nextBlockGenerated() const { return _nextBlockGenerated; }
    Event<Block::Type>& nextBlockGenerated() { return _nextBlockGenerated; }
    const Event<>& gameStarted() const { return _gameStarted; }
    Event<>& gameStarted() { return _gameStarted; }
    const Event<>& gameEnded() const { return _gameEnded; }
    Event<>& gameEnded() { return _gameEnded; }
    const Event<int>& levelChanged() const { return _levelChanged; }
    Event<int>& levelChanged() { return _levelChanged; }

  private:
    CellGrid _cells;
    std::unique_ptr<Block> _activeBlock;
    std::unique_ptr<Block> _nextBlock;
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
    ObserverSlot<> _gameEndedSlot;

    int _currentLevelNumber;
    bool _started;

  private:
    bool _changeLevelTo(int levelNumber);

    // Observes itself so it can reset once a game ends
    void _gameEndedObserver();

    // All these do are forward the event from the Score to our own observers
    void _scoreUpdatedObserver(int score);
    void _hiScoreUpdatedObserver(int score);
  };

}

#endif


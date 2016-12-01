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
    using CellGrid = std::array<std::array<Cell, BOARD_HEIGHT>, BOARD_WIDTH + 3>;
    using RandomEngine = std::mt19937;

    struct InitArgs {
      int seed;
      int levelNumber;
      std::map<int, const LevelFactory> levelFactories;
    };

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

    std::unique_ptr<Block>& activeBlock();
    const std::unique_ptr<Block>& activeBlock() const;

    const Event<const CellGrid&, const Block*>& cellsUpdated() const;
    Event<const CellGrid&, const Block*>& cellsUpdated();
    const Event<int>& scoreUpdated() const;
    Event<int>& scoreUpdated();
    const Event<int>& hiScoreUpdated() const;
    Event<int>& hiScoreUpdated();
    const Event<Block::Type>& nextBlockGenerated() const;
    Event<Block::Type>& nextBlockGenerated();
    const Event<>& gameReset() const;
    Event<>& gameReset();

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
    Event<> _gameReset;

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


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

namespace qd {

  class Level;
  class Block;
  class Command;

  constexpr std::size_t BOARD_WIDTH = 11;
  constexpr std::size_t BOARD_HEIGHT = 15;

  using LevelFactory = std::function<std::unique_ptr<Level>>;
  using CellGrid = std::array<std::array<Cell, BOARD_HEIGHT>, BOARD_WIDTH + 3>;

  struct BoardInitArgs {
    int seed;
    int levelNumber;
  };

  class Board {
  public:
    Board(const BoardInitArgs&);

    void reset();
    void executeCommand(const Command& command);

    const Event<>& gameStarted() const;
    const Event<>& cellUpdated() const;
    const Event<>& scoreUpdated() const;
    const Event<>& highScoreUpdated() const;
    const Event<>& nextBlockGenerated() const;
    const Event<>& gameEnded() const;
    Event<>& gameStarted();
    Event<>& cellUpdated();
    Event<>& scoreUpdated();
    Event<>& highScoreUpdated();
    Event<>& nextBlockGenerated();
    Event<>& gameEnded();

    void registerLevel(
      int levelNumber,
      const LevelFactory& factory
    );

    CellGrid& cells();
    const CellGrid& cells() const;

    Score& score();
    const Score& score() const;

  private:
    CellGrid _cells;
    std::unique_ptr<Block> _activeBlock;
    Score _score;
    std::unique_ptr<Level> _level;
    int _seed;
    std::map<int, LevelFactory> _levelFactories;

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


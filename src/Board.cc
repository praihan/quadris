#include "Board.h"
#include <cassert>
#include <functional>
#include <iostream>

namespace qd {

  Board::Board(const Board::InitArgs& initArgs) :
  _randomEngine{static_cast<RandomEngine::result_type>(initArgs.seed)} {
    _score.scoreUpdated().addObserver(
      _scoreUpdatedSlot,
      std::bind(&Board::_scoreUpdatedObserver, this, std::placeholders::_1)
    );
    _score.hiScoreUpdated().addObserver(
      _hiScoreUpdatedSlot,
      std::bind(&Board::_hiScoreUpdatedObserver, this, std::placeholders::_1)
    );
    gameEnded().addObserver(
      _gameEndedSlot,
      std::bind(&Board::_gameEndedObserver, this)
    );
    _currentLevelNumber = initArgs.levelNumber;
  }

  void Board::executeCommand(const Command& command) {
    // TODO: This shit
    if (command.multiplier() == 0) {
      return;
    }
    auto commandType = command.type();
    switch (commandType) {
      case Command::Type::LEFT:
      case Command::Type::RIGHT:
      case Command::Type::DOWN:
      case Command::Type::CLOCKWISE:
      case Command::Type::COUNTER_CLOCKWISE:
      case Command::Type::DROP:
      case Command::Type::BLOCK_I:
      case Command::Type::BLOCK_J:
      case Command::Type::BLOCK_L:
      case Command::Type::BLOCK_O:
      case Command::Type::BLOCK_S:
      case Command::Type::BLOCK_T:
      case Command::Type::BLOCK_Z:
      case Command::Type::NORANDOM:
      case Command::Type::RANDOM:
      case Command::Type::SEQUENCE:
        assert(_level != nullptr);
        _level->executeCommand(command);
        break;
      case Command::Type::LEVELUP:
        for (auto i = 0u; i < command.multiplier(); ++i) {
          // failure is okay
          _changeLevelTo(_currentLevelNumber + 1);
        }
        break;
      case Command::Type::LEVELDOWN:
        for (auto i = 0u; i < command.multiplier(); ++i) {
          // failure is okay
          _changeLevelTo(_currentLevelNumber - 1);
        }
        break;
      case Command::Type::RESTART:
        reset();
        break;
      case Command::Type::HINT:
        assert(!"Not implemented");
        break;
      case Command::Type::UNKNOWN:
        assert(!"Command with type UNKNOWN should never get here");
        break;
    }
  }

  void Board::start() {
    // we need to clear the grid before we change levels
    // since changing levels will trigger an cellsUpdated event
    cells() = CellGrid{};
    activeBlockPtr() = nullptr;
    nextBlockPtr() = nullptr;
    bool changeSuccessful = _changeLevelTo(_currentLevelNumber);
    assert(changeSuccessful);
    score().reset();
    gameStarted().notifyObservers();
  }

  void Board::reset() {
    start();
  }

  void Board::registerLevel(
    int levelNumber,
    const Board::LevelFactory& factory
  ) {
    assert(factory);
    _levelFactories[levelNumber] = factory;
  }

  bool Board::_changeLevelTo(int levelNumber) {
    auto levelFactory = _levelFactories.find(levelNumber);
    if (levelFactory == _levelFactories.end()) {
      return false;
    }
    _level = (levelFactory->second)(*this);
    _currentLevelNumber = levelFactory->first;
    levelChanged().notifyObservers(_currentLevelNumber);
    return true;
  }

  void Board::_gameEndedObserver() { reset(); }

  void Board::_scoreUpdatedObserver(int score) { _scoreUpdated.notifyObservers(score); }
  void Board::_hiScoreUpdatedObserver(int score) { _hiScoreUpdated.notifyObservers(score); }
}

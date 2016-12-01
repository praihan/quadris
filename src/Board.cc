#include "Board.h"
#include <cassert>
#include <functional>

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
    for (const auto& levelFactoryPair : initArgs.levelFactories) {
      registerLevel(levelFactoryPair.first, levelFactoryPair.second);
    }
    assert(_changeLevelTo(initArgs.levelNumber));
  }

  void Board::executeCommand(const Command& command) {
    // TODO: This shit
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
        assert(_level != nullptr);
        // failure is okay
        _changeLevelTo(_currentLevelNumber + 1);
        break;
      case Command::Type::LEVELDOWN:
        assert(_level != nullptr);
        // failure is okay
        _changeLevelTo(_currentLevelNumber - 1);
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

  void Board::reset() {
    _score.reset();
    gameReset().notifyObservers();
    // TODO:
    // Clear board
    // cellsUpdated event
    // gameEnded event
  }

  void Board::registerLevel(
    int levelNumber,
    const Board::LevelFactory& factory
  ) {
    assert(factory);
    _levelFactories[levelNumber] = factory;
  }

  Board::CellGrid& Board::cells() { return _cells; }
  const Board::CellGrid& Board::cells() const { return _cells; }

  Score& Board::score() { return _score; }
  const Score& Board::score() const { return _score; }

  Board::RandomEngine& Board::randomEngine() { return _randomEngine; }
  const Board::RandomEngine& Board::randomEngine() const { return _randomEngine; }

  Block& Board::activeBlock() { assert(_activeBlock != nullptr); return *_activeBlock; }
  const Block& Board::activeBlock() const { assert(_activeBlock != nullptr); return *_activeBlock; }

  const Event<const Board::CellGrid&>& Board::cellsUpdated() const { return _cellsUpdated; }
  Event<const Board::CellGrid&>& Board::cellsUpdated() { return _cellsUpdated; }
  const Event<int>& Board::scoreUpdated() const { return _scoreUpdated; }
  Event<int>& Board::scoreUpdated() { return _scoreUpdated; }
  const Event<int>& Board::hiScoreUpdated() const { return _hiScoreUpdated; }
  Event<int>& Board::hiScoreUpdated() { return _hiScoreUpdated; }
  const Event<>& Board::nextBlockGenerated() const { return _nextBlockGenerated; }
  Event<>& Board::nextBlockGenerated() { return _nextBlockGenerated; }
  const Event<>& Board::gameReset() const { return _gameReset; }
  Event<>& Board::gameReset() { return _gameReset; }

  bool Board::_changeLevelTo(int levelNumber) {
    auto levelFactory = _levelFactories.find(levelNumber);
    if (levelFactory == _levelFactories.end()) {
      return false;
    }
    _level = (levelFactory->second)(*this);
    _currentLevelNumber = levelFactory->first;
    return true;
  }

  void Board::_scoreUpdatedObserver(int score) { _scoreUpdated.notifyObservers(score); }
  void Board::_hiScoreUpdatedObserver(int score) { _hiScoreUpdated.notifyObservers(score); }
}

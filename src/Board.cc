#include "Board.h"
#include <cassert>
#include <functional>

namespace qd {

  Board::Board(const Board::InitArgs& initArgs) :
  _randomEngine{static_cast<RandomEngine::result_type>(initArgs.seed)} {
    _changeLevelTo(initArgs.levelNumber);
    _score.scoreUpdated().addObserver(
      _scoreUpdatedSlot,
      std::bind(&Board::_scoreUpdatedObserver, this, std::placeholders::_1)
    );
    _score.hiScoreUpdated().addObserver(
      _hiScoreUpdatedSlot,
      std::bind(&Board::_hiScoreUpdatedObserver, this, std::placeholders::_1)
    );
  }

  void Board::executeCommand(const Command& command) {
    // TODO: This shit
  }

  void Board::reset() {
    _score.reset();
    // TODO:
    // Clear board
    // cellUpdated event
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

  const Event<>& Board::gameStarted() const { return _gameStarted; }
  Event<>& Board::gameStarted() { return _gameStarted; }
  const Event<>& Board::cellUpdated() const { return _cellUpdated; }
  Event<>& Board::cellUpdated() { return _cellUpdated; }
  const Event<int>& Board::scoreUpdated() const { return _scoreUpdated; }
  Event<int>& Board::scoreUpdated() { return _scoreUpdated; }
  const Event<int>& Board::hiScoreUpdated() const { return _hiScoreUpdated; }
  Event<int>& Board::hiScoreUpdated() { return _hiScoreUpdated; }
  const Event<>& Board::nextBlockGenerated() const { return _nextBlockGenerated; }
  Event<>& Board::nextBlockGenerated() { return _nextBlockGenerated; }
  const Event<>& Board::gameEnded() const { return _gameEnded; }
  Event<>& Board::gameEnded() { return _gameEnded; }

  void Board::_changeLevelTo(int levelNumber) {
    auto levelFactory = _levelFactories.find(levelNumber);
    assert(levelFactory != _levelFactories.end());
    _level = (levelFactory->second)(*this);
  }

  void Board::_scoreUpdatedObserver(int score) { _scoreUpdated.notifyObservers(score); }
  void Board::_hiScoreUpdatedObserver(int score) { _hiScoreUpdated.notifyObservers(score); }
}
#include "Score.h"

namespace qd {
  Score::Score() : _currentScore(0), _hiScore(0) {}

  const Event<int>& Score::scoreUpdated() const {
    return _scoreUpdated;
  }

  const Event<int>& Score::hiScoreUpdated() const {
    return _hiScoreUpdated;
  }

  void Score::incrementBy(int deltaScore) { // increments score and hiScore if necessary
    _currentScore += deltaScore;

    if (_currentScore > _hiScore) {
      _hiScore = _currentScore;
      _hiScoreUpdated.notifyObservers(_hiScore);
    }

    _scoreUpdated.notifyObservers(_currentScore);
  }

  void Score::reset() { // resets current score to 0
    _currentScore = 0;
    _scoreUpdated.notifyObservers(_currentScore);
    _hiScoreUpdated.notifyObservers(_hiScore);
  }
}

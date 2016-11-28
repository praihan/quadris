#include "Score.h"

namespace qd {
  const Event<>& Score::scoreUpdated() {
    return _scoreUpdated;
  }

  const Event<>& Score::hiScoreUpdated() {
    return _hiScoreUpdated;
  }

  void Score::incrementBy(int deltaScore) { // increments score and hiScore if necessary
    _currentScore += deltaScore;

    if (_currentScore > hiScore) {
      _hiScore = currentScore;
      _hiScoreUpdated.notifyObservers(_hiScore);
    }

    _scoreUpdated.notifyObservers(_currentScore);
  }

  void Score::reset() { // resets current score to 0
    _currentScore = 0;
    _scoreUpdated.notifyObservers(_currentScore);
  }
}

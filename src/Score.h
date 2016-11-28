#ifndef SCORE_H_
#define SCORE_H_

#include "Event.h"

namespace qd {

  class Score {
  public:
    const Event<>& scoreUpdated() const;
    const Event<>& hiScoreUpdated() const;

    void incrementBy(int deltaScore);
    void reset();

  private:
    int _currentScore;
    int _hiScore;
    Event<int> _scoreUpdated;
    Event<int> _hiScoreUpdate;
  };

}

#endif


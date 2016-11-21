#ifndef SCORE_H_
#define SCORE_H_

#include "Event.h"

namespace qd {

  class Score {
  private:
    int _currentScore;
    int _hiScore;
  public:
    Event<> scoreUpdated();
    Event<> hiScoreUpdated();
  };

}

#endif


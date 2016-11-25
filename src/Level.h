#ifndef LEVEL_H_
#define LEVEL_H_

#include <string>
#include <vector>
#include "Score.h"
#include "Block.h"

namespace qd {

  class Level {
  public:
    virtual int levelNumber() const = 0;
    virtual Block::Type nextBlockType() const = 0;
    virtual void useSequence(const std::string& sequenceFileName) = 0;
    virtual void updateScore(Score&, const std::vector<int>& lineNumbersCleared) const;
  };

}

#endif


#ifndef LEVEL_H_
#define LEVEL_H_

#include <string>

namespace qd {

  class Level {
  public:
    virtual int levelNumber() const = 0;
    virtual int nextBlockType() const = 0;
    virtual void useSequence(const std::string& sequenceFileName) = 0;
  };

}

#endif

#ifndef LEVEL4_H_
#define LEVEL4_H_

#include <string>
#include "Level.h"

namespace qd {

  class Level4 : public Level {
  public:
    virtual int levelNumber() const override;
    virtual Block::Type nextBlockType() const override;
    virtual void useSequence(const std::string& sequenceFileName) override;
  };

}
#endif


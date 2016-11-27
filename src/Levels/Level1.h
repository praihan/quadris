#ifndef LEVEL1_H_
#define LEVEL1_H_

#include <string>
#include "Level.h"

namespace qd {
  class Level1 : public Level {
  public:
    virtual int levelNumber() const override;
    virtual Block::Type nextBlockType() const override;
    virtual void useSequence(const std::string& sequenceFileName) override;
  };

}
#endif


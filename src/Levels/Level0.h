#ifndef LEVEL0_H_
#define LEVEL0_H_

#include <string>
#include "Level.h"

namespace qd {

  class Level0 : public Level {
  public:
    virtual int levelNumber() const override;
    virtual Block::Type nextBlockType() const override;
    virtual void useSequence(const std::string& sequenceFileName) override;
  };

}
#endif


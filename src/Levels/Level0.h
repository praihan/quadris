#ifndef LEVEL0_H_
#define LEVEL0_H_

#include <string>
#include "Level.h"

namespace qd {
  class Level0 : public Level {
  private:
    std::vector<Block::Type> _sequence;
  public:
    Level0();
    virtual int levelNumber() const override;
    virtual Block::Type nextBlockType() const override;
    virtual void useSequence(const std::string& sequenceFileName) override;
  };

}
#endif


#ifndef LEVEL3_H_
#define LEVEL3_H_

#include <string>
#include "Level.h"

namespace qd {

  class Level3 : public Level {
  public:
    virtual int levelNumber() const override;
    virtual int nextBlockType() const override;
    virtual void useSequence(const std::string& sequenceFileName) override;
  };

}
#endif


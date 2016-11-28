#ifndef LEVEL4_H_
#define LEVEL4_H_

#include "BaseLevel.h"

namespace qd {
  class Level4 : public BaseLevel {
  public:
    virtual int levelNumber() const override;
    virtual Block::Type nextBlockType() override;
    virtual void executeCommand(const Command& command) override;
  };

}
#endif


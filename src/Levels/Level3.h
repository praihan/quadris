#ifndef LEVEL3_H_
#define LEVEL3_H_

#include "BaseLevel.h"

namespace qd {
  class Level3 : public BaseLevel {
  public:
    virtual int levelNumber() const override;
    virtual Block::Type nextBlockType() override;
    virtual void executeCommand(const Command& command) override;
  };

}
#endif


#ifndef LEVEL2_H_
#define LEVEL2_H_

#include "BaseLevel.h"

namespace qd {
  class Level2 : public BaseLevel {
  public:
    virtual int levelNumber() const override;
    virtual Block::Type nextBlockType() override;
    virtual bool executeCommand(const Command& command) override;
  };

}
#endif


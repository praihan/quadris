#ifndef LEVEL3_H_
#define LEVEL3_H_

#include "BaseLevel.h"

namespace qd {
  class Level3 : public BaseLevel {
  public:
    Level3(Board&);
    virtual int levelNumber() const override;
    virtual Block::Type nextBlockType() override;
    virtual bool executeCommand(const Command& command) override;
  };

}
#endif


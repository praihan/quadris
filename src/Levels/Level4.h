#ifndef LEVEL4_H_
#define LEVEL4_H_

#include "BaseLevel.h"

namespace qd {
  class Level4 : public BaseLevel {
  public:
    Level4(Board&);
  protected:
    virtual int levelNumber() const override;
    virtual Block::Type nextBlockType() override;
    virtual bool executeCommand(const Command& command) override;
    virtual bool _shouldGenerateHeavyBlocks() const override;
  };

}
#endif


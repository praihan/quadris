#ifndef LEVEL0_H_
#define LEVEL0_H_

#include "BaseLevel.h"

namespace qd {
  class Level0 : public BaseLevel {
  public:
    Level0(Board&);
  protected:
    virtual int levelNumber() const override;
    virtual Block::Type nextBlockType() override;
    virtual bool executeCommand(const Command& command) override;

  public:
    static std::string sequenceFileName;
  };

}
#endif


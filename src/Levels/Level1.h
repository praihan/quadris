#ifndef LEVEL1_H_
#define LEVEL1_H_

#include "BaseLevel.h"

namespace qd {
  class Level1 : public BaseLevel {
  public:
    Level1(Board&);
  protected:
    virtual int levelNumber() const override;
    virtual Block::Type nextBlockType() override;
  };

}
#endif


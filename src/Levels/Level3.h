#ifndef LEVEL3_H_
#define LEVEL3_H_

#include "SequencedBaseLevel.h"

namespace qd {
  class Level3 : public BaseLevel {
  public:
    Level3(Board&);
  protected:
    virtual int levelNumber() const override;
  };

}
#endif


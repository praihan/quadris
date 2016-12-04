#ifndef LEVEL4_H_
#define LEVEL4_H_

#include "SequencedBaseLevel.h"
namespace qd {
  class Level4 : public SequencedBaseLevel {
  public:
    Level4(Board&);
  protected:
    virtual int levelNumber() const override;
  };

}
#endif


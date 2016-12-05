#ifndef LEVEL3_H_
#define LEVEL3_H_

#include "SequencedBaseLevel.h"
namespace qd {
  class Level3 : public SequencedBaseLevel {
  public:
    Level3(Board&);
    virtual void executeCommand(const Command& command) override;
  protected:
    virtual int levelNumber() const override;
  };

}
#endif


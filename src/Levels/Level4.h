#ifndef LEVEL4_H_
#define LEVEL4_H_

#include "SequencedBaseLevel.h"
#include <vector>

namespace qd {
  class Level4 : public SequencedBaseLevel {
  public:
    Level4(Board&);
    virtual void executeCommand(const Command& command) override;
  protected:
    int _consecutiveNoClears;
    ObserverSlot<const std::vector<int>&> _linesClearedSlot;

    virtual int levelNumber() const override;
  };

}
#endif


#ifndef LEVEL0_H_
#define LEVEL0_H_

#include "BaseLevel.h"

namespace qd {
  class Level0 : public BaseLevel {
  private:
    std::vector<Block::Type> _sequence;
    std::vector<Block::Type>::const_iterator _current;
  public:
    Level0(Board&);
  protected:
    virtual int levelNumber() const override;
    virtual Block::Type nextBlockType() override;
    virtual void executeCommand(const Command& command) override;

  public:
    static std::string sequenceFileName;
  };

}
#endif


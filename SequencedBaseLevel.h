#ifndef SEQ_BASE_LEVEL_H_
#define SEQ_BASE_LEVEL_H_

#include "BaseLevel.h"
#include "Block.h"
#include "Board.h"
#include <string>

namespace qd {
  class SequencedBaseLevel : public BaseLevel {
    protected:
      std::vector<Block::Type> _sequence;
      std::vector<Block::Type>::const_iterator _current;

      virtual Block::Type nextBlockType() override;
      void _setSequence(std::string sequenceFileName);
      virtual bool executeCommand(const Command& command) override;
      virtual bool _shouldGenerateHeavyBlocks() const override;

    public:
      SequencedBaseLevel(Board &b);

  };
}

#endif
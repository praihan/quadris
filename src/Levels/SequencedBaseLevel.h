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
      bool _useSequenceFile;

      virtual Block::Type nextBlockType() override;
      void _setSequence(std::string sequenceFileName);
      virtual bool _shouldGenerateHeavyBlocks() const override;

      virtual void _turnOffRandom(std::string filename) override;
      virtual void _turnOnRandom() override;

    public:
      SequencedBaseLevel(Board &b);

  };
}

#endif
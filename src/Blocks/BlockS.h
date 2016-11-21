#ifndef BLOCK_S_H_
#define BLOCK_S_H_

#include <string>
#include <vector>
#include <memory>
#include "Position.h"
#include "Block.h"

namespace qd {

  class BlockS : public Block {
  public:
    virtual std::unique_ptr<Block> withRotation(RotationType) const override;
    virtual Type type() const override;
  };

}

#endif


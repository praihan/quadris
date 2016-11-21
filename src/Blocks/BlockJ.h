#ifndef BLOCK_J_H_
#define BLOCK_J_H_

#include <string>
#include <vector>
#include <memory>
#include "Position.h"
#include "Block.h"

namespace qd {

  class BlockJ : public Block {
  public:
    virtual std::unique_ptr<Block> withRotation(Rotation) const override;
    virtual Type type() const override;
  };

}

#endif


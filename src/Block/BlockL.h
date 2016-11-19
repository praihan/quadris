#ifndef BLOCK_L_H_
#define BLOCK_L_H_

#include <string>
#include <vector>
#include <memory>
#include "Position.h"
#include "Block.h"

namespace qd {

  class BlockL : public Block {
  public:
    virtual std::unique_ptr<Block> withRotation(RotationType) const override;
    virtual Type type() const override;
  };

}

#endif


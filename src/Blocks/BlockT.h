#ifndef BLOCK_T_H_
#define BLOCK_T_H_

#include <string>
#include <vector>
#include <memory>
#include "Position.h"
#include "Block.h"

namespace qd {

  class BlockT : public Block {
  public:
    virtual std::unique_ptr<Block> withRotation(RotationType) const override;
    virtual Type type() const override;
  };

}

#endif


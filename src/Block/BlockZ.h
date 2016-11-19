#ifndef BLOCK_Z_H_
#define BLOCK_Z_H_

#include <string>
#include <vector>
#include <memory>
#include "Position.h"
#include "Block.h"

namespace qd {

  class BlockZ : public Block {
  public:
    virtual std::unique_ptr<Block> withRotation(RotationType) override;
    virtual Type type() override;
  };

}

#endif


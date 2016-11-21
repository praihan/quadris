#ifndef BLOCK_O_H_
#define BLOCK_O_H_

#include <string>
#include <vector>
#include <memory>
#include "Position.h"
#include "Block.h"

namespace qd {

  class BlockO : public Block {
  public:
    virtual std::unique_ptr<Block> withRotation(Rotation) const override;
    virtual Type type() const override;
  };

}

#endif


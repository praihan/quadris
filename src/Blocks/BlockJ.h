#ifndef BLOCK_J_H_
#define BLOCK_J_H_

#include <string>
#include <vector>
#include <memory>
#include "Position.h"
#include "Block.h"

namespace qd {

  class BlockJ : public Block {
    int state;

  public:
    BlockJ(const bool heavy = false);
    virtual void rotate(Rotation) override;
    virtual Type type() const override;
    virtual std::unique_ptr<Block> clone() override;
  };

}

#endif


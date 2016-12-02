#ifndef BLOCK_I_H_
#define BLOCK_I_H_

#include <string>
#include <vector>
#include <memory>
#include "Position.h"
#include "Block.h"

namespace qd {

  class BlockI : public Block {
    int state;

  public:
    BlockI(const bool heavy = false);
    virtual void rotate(Rotation) override;
    virtual Type type() const override;
    virtual std::unique_ptr<Block> clone() override;
  };

}

#endif


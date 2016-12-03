#ifndef BLOCK_Z_H_
#define BLOCK_Z_H_

#include <string>
#include <vector>
#include <memory>
#include "Position.h"
#include "Block.h"

namespace qd {

  class BlockZ : public Block {
    int state;
    
  public:
    BlockZ();
    virtual void rotate(Rotation) override;
    virtual Type type() const override;
    virtual std::unique_ptr<Block> clone() override;
  };

}

#endif


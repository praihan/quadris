#ifndef BLOCK_S_H_
#define BLOCK_S_H_

#include <string>
#include <vector>
#include <memory>
#include "Position.h"
#include "Block.h"

namespace qd {

  class BlockS : public Block {
    int state;
    
  public:
    BlockS();
    virtual void rotate(Rotation) override;
    virtual Type type() const override;
    virtual std::unique_ptr<Block> clone() override;
  };

}

#endif


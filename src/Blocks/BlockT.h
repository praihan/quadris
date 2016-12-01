#ifndef BLOCK_T_H_
#define BLOCK_T_H_

#include <string>
#include <vector>
#include <memory>
#include "Position.h"
#include "Block.h"

namespace qd {

  class BlockT : public Block {
    int state;
    
  public:
    BlockT();
    virtual void rotate(Rotation) override;
    virtual Type type() const override;
    virtual std::unique_ptr<Block> clone() override;
  };

}

#endif


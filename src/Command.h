#ifndef COMMAND_H_
#define COMMAND_H_

#include <vector>
#include "Event.h"

namespace qd {

  class Command {
  public:
    enum class Type {
      LEFT,
      RIGHT,
      DOWN,
      CLOCKWISE,
      COUNTER_CLOCKWISE,
      DROP,
      LEVELUP,
      LEVELDOWN,
      NORANDOM,
      RANDOM,
      SEQUENCE,
      BLOCK_I,
      BLOCK_J,
      BLOCK_L,
      BLOCK_O,
      BLOCK_S,
      BLOCK_T,
      BLOCK_Z,
      RESTART,
      HINT
    };

    Type type() const;
    std::vector<std::string> arguments;
  };

}

#endif


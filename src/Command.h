#ifndef COMMAND_H_
#define COMMAND_H_

#include <vector>
#include <string>
#include "Event.h"

namespace qd {

  class Command {
  public:
    enum class Type {
      UNKNOWN,
      IGNORE,

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

    Command();
    Command(Type, const std::string& name, const std::vector<std::string>& arguments = { });

    Type type() const;
    const std::string& name() const;
    const std::vector<std::string>& arguments() const;

  private:
    Type _type;
    std::string _name;
    std::vector<std::string> _arguments;
  };

  class CommandError : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
  };

}

#include <type_traits>

static_assert(std::is_move_constructible<qd::Command>::value, "should be move constructible");

#endif

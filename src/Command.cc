#include "Command.h"

namespace qd {
  Command::Command(Type t, const std::vector<std::string>& vec) : _type(t), _arguments(vec) {}
  Command::Type Command::type() const {
    return _type;
  }
  const std::vector<std::string>& Command::arguments() const {
    return _arguments;
  }
}
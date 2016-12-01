#include "Command.h"

namespace qd {
  Command::Command() : _type{Type::UNKNOWN}, _multiplier{1} { }
  Command::Command(
    Type t, const std::string& name,
    const std::vector<std::string>& vec, unsigned multiplier
  ) : _type{t}, _name{name}, _arguments{vec}, _multiplier{multiplier} { }
  
  Command::Type Command::type() const noexcept {
    return _type;
  }
  const std::string& Command::name() const noexcept {
    return _name;
  }
  const std::vector<std::string>& Command::arguments() const noexcept {
    return _arguments;
  }
  unsigned Command::multiplier() const noexcept {
    return _multiplier;
  }
}
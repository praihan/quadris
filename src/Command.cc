#include "Command.h"

namespace qd {
  Command::Command() : _type{Type::UNKNOWN} { }
  Command::Command(Type t, const std::string& name, const std::vector<std::string>& vec) :
    _type{t}, _name{name}, _arguments{vec} { }
  
  Command::Type Command::type() const {
    return _type;
  }
  const std::string& Command::name() const {
    return _name;
  }
  const std::vector<std::string>& Command::arguments() const {
    return _arguments;
  }
}
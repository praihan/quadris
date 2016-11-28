#ifndef COMMAND_INTERPRETER_H_
#define COMMAND_INTERPRETER_H_

#include "Command.h"
#include <istream>
#include <unordered_map>

namespace qd {

  class CommandInterpreter {
  public:
    CommandInterpreter(std::istream&);
    Command nextCommand();
  private:
    std::istream& _input;

    std::unordered_map<std::string, Command::Type> _commandMappings;
  };

}

#endif


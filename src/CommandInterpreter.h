#ifndef COMMAND_INTERPRETER_H_
#define COMMAND_INTERPRETER_H_

#include "Command.h"
#include <istream>

namespace qd {

  class CommandInterpreter {
  public:
    CommandInterpreter(std::istream&);
    Command nextCommand();
  private:
    std::istream& _input;
  };

}

#endif


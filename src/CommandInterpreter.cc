#include "CommandInterpreter.h"

namespace qd {
  CommandInterpreter::CommandInterpreter(std::istream& in) : _input(in) {}
  Command CommandInterpreter::nextCommand() {
    std::string s;
    if (!(_input >> s)) {
      throw CommandError("Reached end of command input");
    }

    if (s == "left") {
      return { Command::Type::LEFT };
    }
    else if (s == "right") {
      return { Command::Type::RIGHT };
    }
    else if (s == "down") {
      return { Command::Type::DOWN };
    }
    else if (s == "clockwise") {
      return { Command::Type::CLOCKWISE };
    }
    else if (s == "counterclockwise") {
      return { Command::Type::COUNTER_CLOCKWISE };
    }
    else if (s == "drop") {
      return { Command::Type::DROP };
    }
    else if (s == "levelup") {
      return { Command::Type::LEVELUP };
    }
    else if (s == "leveldown") {
      return { Command::Type::LEVELDOWN };
    }
    else if (s == "norandom") {
      if (!(_input >> s)) {
        throw CommandError("Reached end of command input");
      }
      
      return { Command::Type::NORANDOM, { s } };
    }
    else if (s == "random") {
      return { Command::Type::RANDOM };
    }
    else if (s == "sequence") {
      if (!(_input >> s)) {
        throw CommandError("Reached end of command input");
      }
      return { Command::Type::SEQUENCE, { s } };
    }
    else if (s == "I") {
      return { Command::Type::BLOCK_I };
    }
    else if (s == "J") {
      return { Command::Type::BLOCK_J };
    }
    else if (s == "L") {
      return { Command::Type::BLOCK_L };
    }
    else if (s == "O") {
      return { Command::Type::BLOCK_O };
    }
    else if (s == "S") {
      return { Command::Type::BLOCK_S };
    }
    else if (s == "T") {
      return { Command::Type::BLOCK_T };
    }
    else if (s == "Z") {
      return { Command::Type::BLOCK_Z };
    }
    else if (s == "restart") {
      return { Command::Type::RESTART };
    }
    else if (s == "hint") {
      return { Command::Type::HINT };
    }
    else {
      return { Command::Type::UNKNOWN };
    }
  }
}
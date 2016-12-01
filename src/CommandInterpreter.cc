#include "CommandInterpreter.h"
#include <utility>

namespace qd {
  CommandInterpreter::CommandInterpreter(std::istream& in) : _input(in) {
    _commandMappings = {
      { "left", Command::Type::LEFT },
      { "right", Command::Type::RIGHT },
      { "down", Command::Type::DOWN },
      { "clockwise", Command::Type::CLOCKWISE },
      { "counterclockwise", Command::Type::COUNTER_CLOCKWISE },
      { "drop", Command::Type::DROP },
      { "levelup", Command::Type::LEVELUP },
      { "leveldown", Command::Type::LEVELDOWN },
      { "norandom", Command::Type::NORANDOM },
      { "random", Command::Type::RANDOM },
      { "sequence", Command::Type::SEQUENCE },
      { "I", Command::Type::BLOCK_I },
      { "J", Command::Type::BLOCK_J },
      { "L", Command::Type::BLOCK_L },
      { "O", Command::Type::BLOCK_O },
      { "S", Command::Type::BLOCK_S },
      { "T", Command::Type::BLOCK_T },
      { "Z", Command::Type::BLOCK_Z },
      { "restart", Command::Type::RESTART },
      { "hint", Command::Type::HINT },
    };
  }
  
  Command CommandInterpreter::nextCommand() {
    std::string s;
    if (!(_input >> s)) {
      throw CommandError("Reached end of command input");
    }

    auto commandTypeMapping = _commandMappings.find(s);
    if (commandTypeMapping == _commandMappings.end()) {
      return { Command::Type::UNKNOWN, s };
    }

    auto commandType = commandTypeMapping->second;
    switch (commandType) {
      case Command::Type::NORANDOM:
      case Command::Type::SEQUENCE: {
        std::string arg;
        if (!(_input >> arg)) {
          throw CommandError("Reached end of command input");
        }
        return { commandType, s, { arg } };
      }
        break;
      default:
        break;
    }
    return { commandType, s };
  }
}
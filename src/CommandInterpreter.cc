#include "CommandInterpreter.h"
#include <utility>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>

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
    auto throwEndOfCommandInput = []() [[noreturn]] {
      throw CommandError("Reached end of command input");
    };

    std::string line;
    std::vector<std::string> commandLine;

    do {
      if (!std::getline(_input, line)) {
        throwEndOfCommandInput();
      }
      std::istringstream lineParts { line };
      std::copy(
        std::istream_iterator<std::string>{lineParts},
        std::istream_iterator<std::string>{},
        std::back_inserter(commandLine)
      );
    } while (commandLine.size() == 0);

    if (commandLine.size() == 0) {
      throwEndOfCommandInput();
    }

    const std::string& commandName = commandLine[0];

    auto commandTypeMapping = _commandMappings.find(commandName);
    if (commandTypeMapping == _commandMappings.end()) {
      return { Command::Type::UNKNOWN, commandName };
    }

    auto commandType = commandTypeMapping->second;
    switch (commandType) {
      case Command::Type::NORANDOM:
      case Command::Type::SEQUENCE: {
        if (commandLine.size() != 2) {
          throw CommandArityError{
            commandType,
            commandName,
            static_cast<int>(commandLine.size() - 1), // given arity
            1 // expected arity
          };
        }
        std::string arg = commandLine[1];
        return { commandType, commandName, { arg } };
      }
        break;
      default:
        if (commandLine.size() != 1) {
          throw CommandArityError{
            commandType,
            commandName,
            static_cast<int>(commandLine.size() - 1), // given arity
            0 // expected arity
          };
        }
        break;
    }
    return { commandType, commandName };
  }

  CommandArityError::CommandArityError(
    Command::Type type,
    const std::string& name,
    int givenArity,
    int expectedArity
  ) : CommandError{("Command '" + name + "' expects " +
        std::to_string(expectedArity) + " argument(s) but got " +
        std::to_string(givenArity) + ".")},
      _commandType{type}, _commandName{name},
      _givenArity{givenArity}, _expectedArity{expectedArity} {
  }
  Command::Type CommandArityError::commandType() const noexcept {
    return _commandType;
  }
  int CommandArityError::givenArity() const noexcept {
    return _givenArity;
  }
  int CommandArityError::expectedArity() const noexcept {
    return _expectedArity;
  }
  const std::string& CommandArityError::commandName() const noexcept {
    return _commandName;
  }

}
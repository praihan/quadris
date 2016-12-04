#include "CommandInterpreter.h"
#include <utility>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

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
    std::string line;
    std::vector<std::string> commandLine;

    do {
      if (!std::getline(_input, line)) {
        throw CommandEndOfInputError{};
      }
      std::istringstream lineParts { line };
      std::copy(
        std::istream_iterator<std::string>{ lineParts },
        std::istream_iterator<std::string>{},
        std::back_inserter(commandLine)
      );
    } while (commandLine.size() == 0);

    if (commandLine.size() == 0) {
      throw CommandEndOfInputError{};
    }

    const std::string& commandName = commandLine[0];

    Command::Type commandType;
    unsigned multiplier = 1;

    auto commandTypeMapping = _commandMappings.find(commandName);
    if (commandTypeMapping == _commandMappings.end()) {
      // Okay.. time for fuzzy matching
      std::istringstream iss { commandName };

      iss >> multiplier;
      if (!iss) {
        multiplier = 1;
      }
      iss.clear();

      std::string fuzzyCommandName;
      iss >> fuzzyCommandName;

      std::vector<std::pair<std::string, Command::Type>> matches;
      std::copy_if(_commandMappings.begin(), _commandMappings.end(),
        std::back_inserter(matches),
        [&fuzzyCommandName](const auto& mapping) {
          const std::string& name = mapping.first;
          // check if fuzzyCommandName is a prefix of the mapping name;
          return std::mismatch(
            name.begin(), name.end(),
            fuzzyCommandName.begin(), fuzzyCommandName.end()
          ).second == fuzzyCommandName.end();
        }
      );

      // no matches
      if (matches.size() == 0) {
        return { Command::Type::UNKNOWN, commandName };
      }

      if (matches.size() > 1) {
        throw CommandAmbiguousError{
          fuzzyCommandName,
          matches
        };
      }

      commandType = matches[0].second;

    } else {
      commandType = commandTypeMapping->second;
    }

    Command returnCommand = { Command::Type::UNKNOWN, "" };

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
        returnCommand = Command{ commandType, commandName, { arg }, multiplier };
      }
        break;
      default: {
        if (commandLine.size() != 1) {
          throw CommandArityError{
            commandType,
            commandName,
            static_cast<int>(commandLine.size() - 1), // given arity
            0 // expected arity
          };
        }
        returnCommand = Command{ commandType, commandName, { }, multiplier };
        break;
      }
    }

    return returnCommand;
  }

  CommandEndOfInputError::CommandEndOfInputError() :
    CommandError{"Reached end of command input"} { }

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

  CommandAmbiguousError::CommandAmbiguousError(
    const std::string& query,
    const std::vector<std::pair<std::string, Command::Type>>& commandMatches
  ) : CommandError{""}, _query{query}, _commandMatches{commandMatches} {
  }

  const std::vector<std::pair<std::string, Command::Type>>&
    CommandAmbiguousError::commandMatches() const noexcept {
    return _commandMatches;
  }

  const std::string& CommandAmbiguousError::query() const noexcept {
    return _query;
  }

}
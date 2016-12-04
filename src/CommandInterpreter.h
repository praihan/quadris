#ifndef COMMAND_INTERPRETER_H_
#define COMMAND_INTERPRETER_H_

#include "Command.h"
#include <istream>
#include <string>
#include <queue>
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

  class CommandEndOfInputError : public CommandError {
  public:
    CommandEndOfInputError();
  };

  class CommandArityError : public CommandError {
  public:
    CommandArityError(
      Command::Type,
      const std::string& name,
      int givenArity,
      int expectedArity
    );

    Command::Type commandType() const noexcept;
    int givenArity() const noexcept;
    int expectedArity() const noexcept;
    const std::string&  commandName() const noexcept;

  private:
    Command::Type _commandType;
    std::string _commandName;
    int _givenArity;
    int _expectedArity;
  };

  class CommandAmbiguousError : public CommandError {
  public:
    CommandAmbiguousError(
      const std::string& query,
      const std::vector<std::pair<std::string, Command::Type>>& commandMatches
    );

    const std::string& query() const noexcept;
    const std::vector<std::pair<std::string, Command::Type>>& commandMatches() const noexcept;

  private:
    std::string _query;
    std::vector<std::pair<std::string, Command::Type>> _commandMatches;
  };

}

#endif


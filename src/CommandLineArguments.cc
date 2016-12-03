#include "CommandLineArguments.h"

#include <string>
#include <stdexcept>
#include <unordered_map>
#include <functional>
#include <cassert>

#include "Utility.h"

namespace {
  constexpr char ARG_TEXT[] = "-text";
  constexpr char ARG_SEED[] = "-seed";
  constexpr char ARG_SCRIPTFILE[] = "-scriptfile";
  constexpr char ARG_STARTLEVEL[] = "-startlevel";
}

namespace qd {
  CommandLineArguments::CommandLineArguments(const int argc, char* argv[]) {
    int i = 1;

    auto getNextArg = [argc, argv, &i](const std::string& argName) -> std::string {
      if ((i + 1) >= argc) {
        throw BadCommandLineArgumentError{"Expected value for argument: " + argName};
      }
      return argv[i + 1];
    };

    // inefficient, but okay since we only read the arguments once
    std::unordered_map<std::string, std::function<void()>> argument_actions;

    argument_actions[ARG_TEXT] = [this]() {
      this->text = true;
    };

    argument_actions[ARG_SEED] = [this, &i, &getNextArg]() {
      int seed;
      if (!tryParseInt(seed, getNextArg(ARG_SEED))) {
        throw BadCommandLineArgumentError{ARG_SEED};
      }
      this->seed = seed;
      ++i;
    };

    argument_actions[ARG_SCRIPTFILE] = [this, &i, &getNextArg]() {
      std::string scriptFile = getNextArg(ARG_SCRIPTFILE);
      this->scriptFile = std::move(scriptFile);
      ++i;
    };

    argument_actions[ARG_STARTLEVEL] = [this, &i, &getNextArg]() {
      int startLevel;
      if (!tryParseInt(startLevel, getNextArg(ARG_STARTLEVEL))) {
        throw BadCommandLineArgumentError{ARG_STARTLEVEL};
      }
      this->startLevel = startLevel;
      ++i;
    };
    
    for (; i < argc; ++i) {
      // std::string_view would be nice
      std::string arg = argv[i];
      auto action = argument_actions.find(arg);

      if (action != argument_actions.end()) {
        (action->second)();
      }
      else {
        throw BadCommandLineArgumentError{"Unknown argument name: " + arg};
      }
    }
  }
}
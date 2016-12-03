#ifndef COMMANDARGS_H_
#define COMMANDARGS_H_

#include <string>
#include <memory>
#include <stdexcept>

#include "Optional.h"

namespace qd {

  class CommandLineArguments {
  public:
    CommandLineArguments(int argc, char* argv[]);

    Optional<bool> text;
    Optional<int> startLevel;
    Optional<std::string> scriptFile;
    Optional<int> seed;
  };

  class BadCommandLineArgumentError : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
  };

}

#endif


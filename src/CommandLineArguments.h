#ifndef COMMANDARGS_H_
#define COMMANDARGS_H_

#include <string>
#include <memory>
#include <stdexcept>

namespace qd {

  class CommandLineArguments {
  public:
    CommandLineArguments(int argc, char* argv[]);

    std::unique_ptr<bool> text;
    std::unique_ptr<int> startLevel;
    std::unique_ptr<std::string> scriptFile;
    std::unique_ptr<int> seed;
  };

  class BadCommandLineArgumentError : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
  };

}

#endif


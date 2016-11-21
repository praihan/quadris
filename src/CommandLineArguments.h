#ifndef COMMANDARGS_H_
#define COMMANDARGS_H_

#include <string>
#include <memory>

namespace qd {

  class CommandLineArguments {
  public:
    CommandLineArguments(int argc, char* argv[]);

    std::unique_ptr<bool> text;
    std::unique_ptr<int> startLevel;
    std::unique_ptr<std::string> scriptFile;
    std::unique_ptr<int> seed;
  };

}

#endif


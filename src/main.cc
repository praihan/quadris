#include <iostream>

#include "CommandLineArguments.h"

int main(int argc, char* argv[]) {
  qd::CommandLineArguments cmdLineArgs{ argc, argv };

  std::cout << "Seed: " << (cmdLineArgs.seed ? std::to_string(*cmdLineArgs.seed) : "<none>") << std::endl;
  std::cout << "Start Level: " << (cmdLineArgs.startLevel ? std::to_string(*cmdLineArgs.startLevel) : "<none>") << std::endl;
  std::cout << "Text: " << (cmdLineArgs.text ? (*cmdLineArgs.text ? "true" : "false") : "<none>") << std::endl;
  std::cout << "Start Level: " << (cmdLineArgs.scriptFile ? *cmdLineArgs.scriptFile : "<none>") << std::endl;
}
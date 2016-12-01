#include <iostream>
#include <memory>

#include "CommandLineArguments.h"
#include "Board.h"
#include "Levels/Level0.h"
#include "Levels/Level1.h"
#include "Levels/Level2.h"
#include "Levels/Level3.h"
#include "Levels/Level4.h"

template <class LevelType>
auto makeLevelFactory() {
  return [](qd::Board& board) {
    return std::make_unique<LevelType>(board);
  };
}

int main(int argc, char* argv[]) {
  qd::CommandLineArguments cmdLineArgs{ argc, argv };

  std::cout << "Seed: " << (cmdLineArgs.seed ? std::to_string(*cmdLineArgs.seed) : "<none>") << std::endl;
  std::cout << "Start Level: " << (cmdLineArgs.startLevel ? std::to_string(*cmdLineArgs.startLevel) : "<none>") << std::endl;
  std::cout << "Text: " << (cmdLineArgs.text ? (*cmdLineArgs.text ? "true" : "false") : "<none>") << std::endl;
  std::cout << "Start Level: " << (cmdLineArgs.scriptFile ? *cmdLineArgs.scriptFile : "<none>") << std::endl;

  qd::Board b{{ 420, 2 }};
  b.registerLevel(0, makeLevelFactory<qd::Level0>());
  b.registerLevel(1, makeLevelFactory<qd::Level1>());
}
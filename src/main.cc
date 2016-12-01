#include <iostream>
#include <memory>
#include <iterator>
#include <algorithm>

#include "CommandLineArguments.h"
#include "CommandInterpreter.h"
#include "Command.h"
#include "Board.h"
#include "Displays/TextDisplay.h"
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
  std::cout << "Script File: " << (cmdLineArgs.scriptFile ? *cmdLineArgs.scriptFile : "<none>") << std::endl;

  if (cmdLineArgs.scriptFile) {
    qd::Level0::sequenceFileName = *cmdLineArgs.scriptFile;
  }

  qd::Board::InitArgs boardInitArgs;
  boardInitArgs.seed = (cmdLineArgs.seed ? *cmdLineArgs.seed : 420);
  boardInitArgs.levelNumber = (cmdLineArgs.startLevel ? *cmdLineArgs.startLevel : 0);

  qd::Board board { boardInitArgs };
  board.registerLevel(0, makeLevelFactory<qd::Level0>());
  board.registerLevel(1, makeLevelFactory<qd::Level1>());

  qd::TextDisplay textDisplay { board };

  qd::CommandInterpreter commandInterpreter { std::cin };

  try {
    board.start();

    while (true) {
      try {
        qd::Command command = commandInterpreter.nextCommand();
        if (command.type() == qd::Command::Type::IGNORE) {
          continue;
        }
        if (command.type() == qd::Command::Type::UNKNOWN) {
          std::cerr << "Error: Unknown command '" <<  command.name() << "'" << std::endl;
          continue;
        }
        board.executeCommand(command);
      }
      catch (const qd::CommandArityError& cmdArityErr) {
        std::cerr << "Error: " << cmdArityErr.what() << std::endl;
      }
      catch (const qd::CommandAmbiguousError& cmdAmbiguousErr) {
        std::cerr << "Error: " << "'" << cmdAmbiguousErr.query() << "'";
        std::cerr << " is ambiguous. It matched commands:\n";
        std::cerr << "[ ";
        for (const auto& cmdPair : cmdAmbiguousErr.commandMatches()) {
          std::cerr << cmdPair.first << " ";
        }
        std::cerr << "]" << std::endl;
      }
    }
  }
  catch (const qd::CommandError& cmdErr) {
    std::cerr << "Error: " <<  cmdErr.what() << std::endl;
  }
}

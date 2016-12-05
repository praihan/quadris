#include <iostream>
#include <memory>
#include <iterator>
#include <algorithm>

#include "CommandLineArguments.h"
#include "CommandInterpreter.h"
#include "Command.h"
#include "Board.h"
#include "Utility.h"
#include "Displays/TextDisplay.h"
#include "Displays/GraphicDisplay.h"
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

  if (cmdLineArgs.scriptFile.hasValue()) {
    qd::Level0::sequenceFileName = *cmdLineArgs.scriptFile;
  }

  qd::Board::InitArgs boardInitArgs;
  boardInitArgs.seed = cmdLineArgs.seed.valueOr(420);

  boardInitArgs.levelNumber =   qd::iife([&cmdLineArgs]() {
    int wantedLevel = cmdLineArgs.startLevel.valueOr(0);
    if (wantedLevel < 0 || wantedLevel > 4) {
      std::cerr << "Error: Only levels 0-4 supported. Defaulting to level 0." << std::endl;
      return 0;
    }
    return wantedLevel;
  });

  qd::Board board { boardInitArgs };
  board.registerLevel(0, makeLevelFactory<qd::Level0>());
  board.registerLevel(1, makeLevelFactory<qd::Level1>());
  board.registerLevel(2, makeLevelFactory<qd::Level2>());
  board.registerLevel(3, makeLevelFactory<qd::Level3>());
  board.registerLevel(4, makeLevelFactory<qd::Level4>());

  qd::TextDisplay textDisplay { board };
  // we can't use Optional because it's not copy-able or move-able
  std::unique_ptr<qd::GraphicDisplay> graphicDisplayPtr;

  if (!cmdLineArgs.text.valueOr(false)) {
    graphicDisplayPtr = std::make_unique<qd::GraphicDisplay>(board);
  }

  qd::CommandInterpreter commandInterpreter { std::cin };

  try {
    board.start();

    textDisplay.outputDisplay();
    if (graphicDisplayPtr) { graphicDisplayPtr->outputDisplay(); }
    while (true) {
      try {
        qd::Command command = commandInterpreter.nextCommand();
        if (command.type() == qd::Command::Type::UNKNOWN) {
          std::cerr << "Error: Unknown command '" <<  command.name() << "'" << std::endl;
          continue;
        }
        board.executeCommand(command);
        textDisplay.outputDisplay();
        if (graphicDisplayPtr) { graphicDisplayPtr->outputDisplay(); }
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
      catch (const qd::CommandEndOfInputError& cmdEndOfInputErr) {
        std::cout << "Reached end of input. Bye!" << std::endl;
        break;
      }
    }
  }
  catch (const qd::CommandError& cmdErr) {
    std::cerr << "Error: " << cmdErr.what() << std::endl;
  }
}

#include "Board.h"
#include "CommandInterpreter.h"
#include "QdDefs.h"
#include <cassert>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <fstream>

namespace qd {

  namespace {
    void resetCellGrid(Board::CellGrid& cells) {
      for (auto& row : cells) {
        for (Cell& cell : row) {
          cell.clear();
        }
      }
    }
  }

  Board::Board(const Board::InitArgs& initArgs) :
    _randomEngine{static_cast<RandomEngine::result_type>(initArgs.seed)},
    _started{false} {
    _score.scoreUpdated().addObserver(
      _scoreUpdatedSlot,
      std::bind(&Board::_scoreUpdatedObserver, this, std::placeholders::_1)
    );
    _score.hiScoreUpdated().addObserver(
      _hiScoreUpdatedSlot,
      std::bind(&Board::_hiScoreUpdatedObserver, this, std::placeholders::_1)
    );
    _currentLevelNumber = initArgs.levelNumber;
  }

  void Board::executeCommand(const Command& command) {
    if (!_started) {
      throw std::runtime_error{ "Cannot execute commands without calling start()" };
    }
    if (command.multiplier() == 0) {
      return;
    }
    auto commandType = command.type();
    switch (commandType) {
      case Command::Type::LEFT:
      case Command::Type::RIGHT:
      case Command::Type::DOWN:
      case Command::Type::CLOCKWISE:
      case Command::Type::COUNTER_CLOCKWISE:
      case Command::Type::DROP:
      case Command::Type::BLOCK_I:
      case Command::Type::BLOCK_J:
      case Command::Type::BLOCK_L:
      case Command::Type::BLOCK_O:
      case Command::Type::BLOCK_S:
      case Command::Type::BLOCK_T:
      case Command::Type::BLOCK_Z:
      case Command::Type::NORANDOM:
      case Command::Type::RANDOM:
      case Command::Type::HINT:
        assert(_level != nullptr);
        {
          bool hasGameEnded = false;
          ObserverSlot<> gameEndedObserverSlot;
          gameEnded().addObserver(gameEndedObserverSlot, [&]() {
            hasGameEnded = true;
          });
          _level->executeCommand(command);
          if (hasGameEnded) {
            reset();
          }
        }
        break;
      case Command::Type::LEVELUP:
        for (auto i = 0u; i < command.multiplier(); ++i) {
          // failure is okay
          _changeLevelTo(_currentLevelNumber + 1);
        }
        break;
      case Command::Type::LEVELDOWN:
        for (auto i = 0u; i < command.multiplier(); ++i) {
          // failure is okay
          _changeLevelTo(_currentLevelNumber - 1);
        }
        break;
      case Command::Type::SEQUENCE: {
          const std::string& sequenceFileName = command.arguments()[0];
          std::ifstream file{ sequenceFileName };
          if (file.fail()) {
            std::cerr << "Error(" << sequenceFileName << "): Could not open file." << std::endl;
            return;
          }
          CommandInterpreter commandInterpreter { file };
          for (unsigned i = 0; i < command.multiplier(); ++i) {
            while (true) {
              try {
                qd::Command command = commandInterpreter.nextCommand();
                if (command.type() == qd::Command::Type::UNKNOWN) {
                  std::cerr << "Error(" << sequenceFileName << "): Unknown command ";
                  std::cerr << "'" << command.name() << "'" << std::endl;
                  continue;
                }
                this->executeCommand(command);
              }
              catch (const qd::CommandArityError& cmdArityErr) {
                std::cerr << "Error(" << sequenceFileName << "): " << cmdArityErr.what() << std::endl;
              }
              catch (const qd::CommandAmbiguousError& cmdAmbiguousErr) {
                std::cerr << "Error(" << sequenceFileName << "): ";
                std::cerr << "'" << cmdAmbiguousErr.query() << "'";
                std::cerr << " is ambiguous. It matched commands:\n";
                std::cerr << "[ ";
                for (const auto& cmdPair : cmdAmbiguousErr.commandMatches()) {
                  std::cerr << cmdPair.first << " ";
                }
                std::cerr << "]" << std::endl;
              }
              catch (const qd::CommandEndOfInputError& cmdEndErr) {
                break;
              }
            }
            file.clear();
            file.seekg(0, std::ios::beg);
          }
      }
        break;
      case Command::Type::RESTART:
        reset();
        break;
      case Command::Type::UNKNOWN:
        assert(!"Command with type UNKNOWN should never get here");
        QD_UNREACHABLE();
        break;
    }
  }

  void Board::start() {
    // we need to clear the grid before we change levels
    // since changing levels will trigger an cellsUpdated event
    if (_started) {
      throw std::runtime_error{ "Already started!" };
    }
    _started = true;
    resetCellGrid(cells());
    activeBlockPtr() = nullptr;
    nextBlockPtr() = nullptr;
    bool changeSuccessful = _changeLevelTo(_currentLevelNumber);
    assert(changeSuccessful); (void)changeSuccessful;
    score().reset();
    gameStarted().notifyObservers();
  }

  void Board::reset() {
    _started = false;
    start();
  }

  void Board::registerLevel(
    int levelNumber,
    const Board::LevelFactory& factory
  ) {
    assert(factory);
    _levelFactories[levelNumber] = factory;
  }

  void Board::trackActiveBlock() {
    if (activeBlockPtr() == nullptr) {
      return;
    }
    // set up an observer for the Block's death
    ObserverSlot<const Block&> observerSlot;
    activeBlockPtr()->destroyed().addObserver(
      observerSlot,
      std::bind(&Board::_onTrackedBlockDestroyed, this, std::placeholders::_1)
    );
    _trackedBlockDestroyedObserverSlots.insert(
      std::make_pair(activeBlockPtr().get(), std::move(observerSlot))
    );
  }

  void Board::_onTrackedBlockDestroyed(const Block& block) {
    // a Block can only be destroyed once, so it's safe to
    // remove the slot after this is called.
    _trackedBlockDestroyedObserverSlots.erase(
      _trackedBlockDestroyedObserverSlots.find(std::addressof(block))
    );
    // save the Block's info for later use
    _trackedBlockHistory.push_back(block.metaInfo());
  }

  bool Board::_changeLevelTo(int levelNumber) {
    auto levelFactory = _levelFactories.find(levelNumber);
    if (levelFactory == _levelFactories.end()) {
      return false;
    }
    _level = (levelFactory->second)(*this);
    _currentLevelNumber = levelFactory->first;
    levelChanged().notifyObservers(_currentLevelNumber);
    return true;
  }

  void Board::_scoreUpdatedObserver(int score) { _scoreUpdated.notifyObservers(score); }
  void Board::_hiScoreUpdatedObserver(int score) { _hiScoreUpdated.notifyObservers(score); }
}

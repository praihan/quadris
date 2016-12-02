#include <cassert>
#include <memory>
#include "Utility.h"
#include "BaseLevel.h"
#include "Command.h"
#include "Block.h"
#include "Blocks/BlockJ.h"
#include "Blocks/BlockI.h"
#include "Blocks/BlockL.h"
#include "Blocks/BlockO.h"
#include "Blocks/BlockS.h"
#include "Blocks/BlockT.h"
#include "Blocks/BlockZ.h"

namespace qd {

  namespace {
    template <class... Args>
    std::unique_ptr<Block> createBlockFromType(Block::Type type, Args&&... args) {
      switch(type) {
        case Block::Type::BLOCK_I:
          return std::make_unique<BlockI>(std::forward<Args>(args)...);
        case Block::Type::BLOCK_J:
          return std::make_unique<BlockJ>(std::forward<Args>(args)...);
        case Block::Type::BLOCK_L:
          return std::make_unique<BlockL>(std::forward<Args>(args)...);
        case Block::Type::BLOCK_O:
          return std::make_unique<BlockO>(std::forward<Args>(args)...);
        case Block::Type::BLOCK_S:
          return std::make_unique<BlockS>(std::forward<Args>(args)...);
        case Block::Type::BLOCK_T:
          return std::make_unique<BlockT>(std::forward<Args>(args)...);
        case Block::Type::BLOCK_Z:
          return std::make_unique<BlockZ>(std::forward<Args>(args)...);
        default:
          assert(!"We have accounted for all block types. This should not happen");
      }
      return nullptr;
    }
  }

  BaseLevel::BaseLevel(Board& b) : Level{b} {
  }

  bool BaseLevel::executeCommand(const Command& command) {
    if (command.multiplier() == 0) {
      return true;
    }

    auto& activeBlockPtr = _board.activeBlockPtr();
    auto notifyCellsUpdated = [this, &activeBlockPtr]() {
      _board.cellsUpdated().notifyObservers(
        _board.cells(),
        activeBlockPtr.get()
      );
    };

    Command::Type commandType = command.type();
    switch (commandType) {
      case Command::Type::LEFT:
      case Command::Type::DOWN:
      case Command::Type::RIGHT: {
        const Direction movementDir = iife([&commandType]() -> Direction {
          switch (commandType) {
            case Command::Type::LEFT:
              return Direction::LEFT;
            case Command::Type::DOWN:
              return Direction::DOWN;
            case Command::Type::RIGHT:
              return Direction::RIGHT;
            default:
              assert(!"Unreachable");
              break;
          }
        });
        const auto moveInDirection = [](Position& p, Direction d) {
          switch (d) {
            case Direction::LEFT:
              p.col -= 1;
              break;
            case Direction::RIGHT:
              p.col += 1;
              break;
            case Direction::DOWN:
              p.row += 1;
              break;
          }
        };
        bool success = true;
        for (unsigned int i = 0; i < command.multiplier(); ++i) {
          if (_canMove(*activeBlockPtr, movementDir)) {
            moveInDirection(activeBlockPtr->position, movementDir);
          }
          else {
            success = false;
            break;
          }
        }

        if (activeBlockPtr->heavy() && movementDir != Direction::DOWN &&
          _canMove(*activeBlockPtr, Direction::DOWN)) { 
          moveInDirection(activeBlockPtr->position, Direction::DOWN);
        }

        notifyCellsUpdated();
        return success;
      }
        break;

      case Command::Type::CLOCKWISE:
      case Command::Type::COUNTER_CLOCKWISE: {
        // determine the rotation direction based on the command type
        const Block::Rotation rotationDirection = iife([&commandType]() -> Block::Rotation {
          switch (commandType) {
            case Command::Type::CLOCKWISE:
              return Block::Rotation::CLOCKWISE;
            case Command::Type::COUNTER_CLOCKWISE:
              return Block::Rotation::COUNTER_CLOCKWISE;
            default:
              assert(!"Unreachable");
              break;
          }
        });
        // opposite of rotationDirection
        const Block::Rotation antiRotationDirection = iife([&rotationDirection]() {
          return rotationDirection == Block::Rotation::CLOCKWISE ?
            Block::Rotation::COUNTER_CLOCKWISE : Block::Rotation::CLOCKWISE;
        });
        bool success = true;
        for (unsigned int i = 0; i < command.multiplier() % 4; ++i) {
          activeBlockPtr->rotate(rotationDirection);

          if (!_isValidBlock(*activeBlockPtr)) {
            activeBlockPtr->rotate(antiRotationDirection);
            success = false;
          }
        }

        if (activeBlockPtr->heavy() && _canMove(*activeBlockPtr, Direction::DOWN)) { 
          activeBlockPtr->position.row += 1;
        }

        notifyCellsUpdated();
        return success;
      }
        break;

      case Command::Type::DROP: {
        while (_canMove(*activeBlockPtr, BaseLevel::Direction::DOWN)) {
          activeBlockPtr->position.row += 1;
        }

        for (Position p : *activeBlockPtr) {
          _board.cells()[p.row][p.col].blockType = activeBlockPtr->type();
        }

        activeBlockPtr = nullptr;
        _ensureBlocksGenerated();

        notifyCellsUpdated();

        // Game is lst
        if (!_isValidBlock(*activeBlockPtr)) {
          _board.gameEnded().notifyObservers();
          return false;
        }

        return true;
      }
        break;

      case Command::Type::BLOCK_I:
      case Command::Type::BLOCK_J:
      case Command::Type::BLOCK_L:
      case Command::Type::BLOCK_O:
      case Command::Type::BLOCK_S:
      case Command::Type::BLOCK_Z:
      case Command::Type::BLOCK_T: {
        const Block::Type blockType = iife([&commandType]() -> Block::Type {
          switch (commandType) {
            case Command::Type::BLOCK_I:
              return Block::Type::BLOCK_I;
            case Command::Type::BLOCK_J:
              return Block::Type::BLOCK_J;
            case Command::Type::BLOCK_L:
              return Block::Type::BLOCK_L;
            case Command::Type::BLOCK_O:
              return Block::Type::BLOCK_O;
            case Command::Type::BLOCK_S:
              return Block::Type::BLOCK_S;
            case Command::Type::BLOCK_Z:
              return Block::Type::BLOCK_S;
            case Command::Type::BLOCK_T:
              return Block::Type::BLOCK_T;
            default:
              assert(!"Unreachable");
              break;
          }
        });
        _board.nextBlockPtr() = createBlockFromType(blockType, _shouldGenerateHeavyBlocks());
        _board.nextBlockGenerated().notifyObservers(blockType);
        return true;
      }
        break;
      default:
        return false;
        break;
    }
  }

  void BaseLevel::_defaultInitialization() {
    std::unique_ptr<Block>& nextBlockPtr = _board.nextBlockPtr();
    if (nextBlockPtr) {
      // if we switch levels, since we have already generated the next Block
      // we have to apply our own heaviness rules before it becomes our active
      // block. In essence, we take ownership of it.
      nextBlockPtr->heavy(_shouldGenerateHeavyBlocks());
    }

    _ensureBlocksGenerated();
    _board.cellsUpdated().notifyObservers(_board.cells(), _board.activeBlockPtr().get());
  }

  void BaseLevel::_checkScoring() {
    
  }

  bool BaseLevel::_isCellOccupied(const Position& p) const {
    return (_board.cells()[p.row][p.col].blockType != Block::Type::EMPTY);
  }

  bool BaseLevel::_isCellInBound(const Position& p) const {
    return
      (p.row >= 0 && p.row < static_cast<int>(BOARD_HEIGHT + 3)) &&
      (p.col >= 0 && p.col < static_cast<int>(BOARD_WIDTH));
  }

  bool BaseLevel::_isValidBlock(const Block &b) const {
    for (Position p : b) {
      if (!_isCellInBound(p)) {
        return false;
      }
      if (_isCellOccupied(p)) {
        return false;
      }
    }

    return true;
  }

  bool BaseLevel::_canMove(const Block &b, Direction d) const {
    for (Position p : b) {
      switch (d) {
        case Direction::DOWN:
          p.row++;
          break;
        case Direction::LEFT:
          p.col--;
          break;
        case Direction::RIGHT: 
          p.col++;
          break;
      }
      if (!_isCellInBound(p)) {
        return false;
      }
      if (_isCellOccupied(p)) {
        return false;
      }
    }
    return true;
  }

  void BaseLevel::_ensureBlocksGenerated() {
    std::unique_ptr<Block>& activeBlockPtr = _board.activeBlockPtr();
    std::unique_ptr<Block>& nextBlockPtr = _board.nextBlockPtr();

    bool heavy = _shouldGenerateHeavyBlocks();

    if (activeBlockPtr == nullptr) {
      auto blockType = nextBlockType();
      if (nextBlockPtr == nullptr) {
        // this should only happen when we first start a game
        activeBlockPtr = createBlockFromType(blockType, heavy);
        blockType = nextBlockType();
      } else {
        activeBlockPtr = std::move(nextBlockPtr);
      }

      nextBlockPtr = createBlockFromType(blockType, heavy);
      _board.nextBlockGenerated().notifyObservers(blockType);

      activeBlockPtr->position = { 0, 0 };
    }
  }

  bool BaseLevel::_shouldGenerateHeavyBlocks() const {
    return false;
  }

}

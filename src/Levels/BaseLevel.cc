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
  BaseLevel::BaseLevel(Board& b) : Level{b} {
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

  void BaseLevel::_ensureActiveBlock() {
    std::unique_ptr<Block>& activeBlockPtr = _board.activeBlockPtr();

    if (activeBlockPtr == nullptr) {
      Block::Type nextType = _nextBlockType;
      _nextBlockType = nextBlockType();

      switch(nextType) {
        case Block::Type::BLOCK_I:
          activeBlockPtr = std::make_unique<BlockI>();
          break;
        case Block::Type::BLOCK_J:
          activeBlockPtr = std::make_unique<BlockJ>();
          break;
        case Block::Type::BLOCK_L:
          activeBlockPtr = std::make_unique<BlockL>();
          break;
        case Block::Type::BLOCK_O:
          activeBlockPtr = std::make_unique<BlockO>();
          break;
        case Block::Type::BLOCK_S:
          activeBlockPtr = std::make_unique<BlockS>();
          break;
        case Block::Type::BLOCK_T:
          activeBlockPtr = std::make_unique<BlockT>();
          break;
        case Block::Type::BLOCK_Z:
          activeBlockPtr = std::make_unique<BlockZ>();
          break;
        default:
          assert(!"We have accounted for all block types. This should not happen");
      }

      activeBlockPtr->position = {0, 0};

      _board.nextBlockGenerated().notifyObservers(_nextBlockType);
    }
  }

  bool BaseLevel::executeCommand(const Command& command) {
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
        _ensureActiveBlock();

        notifyCellsUpdated();
        return true;
      }
      break;

      case Command::Type::BLOCK_I: {
        return false;
      }
      break;

      case Command::Type::BLOCK_J: {
        return false;
      }
      break;

      case Command::Type::BLOCK_L: {
        return false;
      }
      break;

      case Command::Type::BLOCK_O: {
        return false;
      }
      break;

      case Command::Type::BLOCK_S: {
        return false;
      }
      break;
      
      case Command::Type::BLOCK_Z: {
        return false;
      }
      break;

      case Command::Type::BLOCK_T: {
        return false;
      }
      break;

      default:
        return false;
      break;
    }
  }

}

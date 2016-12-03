#include <cassert>
#include <memory>
#include <climits>
#include <utility>
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

int abs(int n) {
  if (n>=0 ) {
    return n;
  }
  return -n;
}

namespace qd {

  namespace {
    /// creates a Block from a Block::Type without any metaInfo
    template <class... Args>
    std::unique_ptr<Block> createRawBlockFromType(Block::Type type) {
      switch(type) {
        case Block::Type::BLOCK_I:
          return std::make_unique<BlockI>();
        case Block::Type::BLOCK_J:
          return std::make_unique<BlockJ>();
        case Block::Type::BLOCK_L:
          return std::make_unique<BlockL>();
        case Block::Type::BLOCK_O:
          return std::make_unique<BlockO>();
        case Block::Type::BLOCK_S:
          return std::make_unique<BlockS>();
        case Block::Type::BLOCK_T:
          return std::make_unique<BlockT>();
        case Block::Type::BLOCK_Z:
          return std::make_unique<BlockZ>();
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

        if (activeBlockPtr->metaInfo().heavy.valueOr(false) && movementDir != Direction::DOWN &&
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

        if (
          activeBlockPtr->metaInfo().heavy.valueOr(false) &&
          _canMove(*activeBlockPtr, Direction::DOWN)
        ) {
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

        _checkScoring();
        _checkGameEnd();
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
        _board.nextBlockPtr() = _createBlockFromType(blockType);
        _board.nextBlockGenerated().notifyObservers(blockType);
        return true;
      }
        break;

      case Command::Type::HINT: {
        std::unique_ptr<Block> activeBlockCpy = activeBlockPtr->clone();
	Position bestPos = activeBlockCpy->position;
        int rotation = 0;
        int bestVariance = INT_MAX;
        int initialHeight = activeBlockCpy->position.row;

        for (auto i = 0; i < 3; i++) {
          std::unique_ptr<Block> bcpyl = activeBlockCpy->clone();

          while(true) {
            bcpyl->position.col--;
         
            if(!(_isValidBlock(*bcpyl))) {
              bcpyl->position.col++;
              break;
            }
          }
  
          while(true) {
            while (_canMove(*bcpyl, BaseLevel::Direction::DOWN)) {
              bcpyl->position.row += 1;
            }

            // Set
            for (Position p : *bcpyl) {
              _board.cells()[p.row][p.col].blockType = bcpyl->type();
            }
             
            // Scan and compare
            int currVariance = 0;
            for (std::size_t j = 0; j < BOARD_WIDTH - 1; j++) {
              currVariance += abs(_getHeight(j) - _getHeight(j+1));
            }

            for (std::size_t j = 0; j < BOARD_WIDTH - 2; j++) {
              currVariance += _ifHole(j);
            }
            // Update best
            if (currVariance < bestVariance) {
              std::cout << currVariance << std::endl;
              bestVariance = currVariance;
              rotation = i;
              bestPos = bcpyl->position;
            }
            else if (currVariance == bestVariance && bcpyl->position.row > bestPos.row) {
              std::cout << currVariance << std::endl;
              bestVariance = currVariance;
              rotation = i;
              bestPos = bcpyl->position;
            }

            // Unset
            for (Position p : *bcpyl) {
              _board.cells()[p.row][p.col].blockType = Block::Type::EMPTY;
            }

            bcpyl->position.col++;
            bcpyl->position.row = initialHeight;
           
            if(!(_isValidBlock(*bcpyl))) {
              break;
            }
          }

          activeBlockCpy->rotate(Block::Rotation::CLOCKWISE);
        }
        std::cout << "x = " << bestPos.col << ", y = " << bestPos.row << std::endl;
        std::cout << "rotation = " << rotation << std::endl;
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
      _inheritBlock(*nextBlockPtr);
    }

    _ensureBlocksGenerated();
    _board.cellsUpdated().notifyObservers(_board.cells(), _board.activeBlockPtr().get());
  }

  bool BaseLevel::_checkGameEnd() {
    if (!_isValidBlock(*_board.activeBlockPtr())) {
      _board.gameEnded().notifyObservers();
      return true;
    }
    return false;
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

  int BaseLevel::_getHeight(const int col) const {
    int row=0;
    for (std::size_t i = 0; i < BOARD_HEIGHT+3; i++) {
      if (_board.cells()[i][col].blockType == Block::Type::EMPTY) {
        row++;
      }
      else {
        break;
      }
    }
    return row;
  }

  int BaseLevel::_ifHole(const int col) const {
    int row=0;
    std::size_t i = 0;
    for (; i < BOARD_HEIGHT+3; i++) {
      if (_board.cells()[i][col].blockType == Block::Type::EMPTY) {
        row++;
      }
      else {
        break;
      }
    }

    for (; i < BOARD_HEIGHT+3; i++) {
      if (_board.cells()[i][col].blockType == Block::Type::EMPTY) {
        return 5;
      }
    }
    return 0;
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

  void BaseLevel::_inheritBlock(Block& block) const {
    Block::MetaInfo metaInfo;
    metaInfo.heavy = _shouldGenerateHeavyBlocks();
    metaInfo.spawnLevel = levelNumber();
    block.metaInfo() = metaInfo;
  }

  std::unique_ptr<Block> BaseLevel::_createBlockFromType(
    Block::Type blockType
  ) const {
    auto blockPtr = createRawBlockFromType(blockType);
    _inheritBlock(*blockPtr);
    return blockPtr;
  }

  void BaseLevel::_ensureBlocksGenerated() {
    std::unique_ptr<Block>& activeBlockPtr = _board.activeBlockPtr();
    std::unique_ptr<Block>& nextBlockPtr = _board.nextBlockPtr();

    if (activeBlockPtr == nullptr) {
      auto blockType = nextBlockType();
      if (nextBlockPtr == nullptr) {
        // this should only happen when we first start a game
        activeBlockPtr = _createBlockFromType(blockType);
        blockType = nextBlockType();
      } else {
        activeBlockPtr = std::move(nextBlockPtr);
      }

      nextBlockPtr = _createBlockFromType(blockType);
      _board.nextBlockGenerated().notifyObservers(blockType);

      activeBlockPtr->position = { 0, 0 };
    }
  }

  bool BaseLevel::_shouldGenerateHeavyBlocks() const {
    return false;
  }

}

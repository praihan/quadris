#include <cassert>
#include <memory>
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
    std::cout << "CANMOVE CALLED" << std::endl;
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
        std::cout << "Cell" << std::endl;
        return false;
      }
      if (_isCellOccupied(p)) {
        std::cout << "Cell occupied" << std::endl;
        return false;
      }
    }
    return true;
  }

  void BaseLevel::_ensureActiveBlock() {
    std::unique_ptr<Block>& activeBlock = _board.activeBlock();

    if (activeBlock == nullptr) {
      Block::Type nextType = nextBlockType();

      switch(nextType) {
        case Block::Type::BLOCK_I:
          activeBlock = std::make_unique<BlockI>();
          break;
        case Block::Type::BLOCK_J:
          activeBlock = std::make_unique<BlockJ>();
          break;
        case Block::Type::BLOCK_L:
          activeBlock = std::make_unique<BlockL>();
          break;
        case Block::Type::BLOCK_O:
          activeBlock = std::make_unique<BlockO>();
          break;
        case Block::Type::BLOCK_S:
          activeBlock = std::make_unique<BlockS>();
          break;
        case Block::Type::BLOCK_T:
          activeBlock = std::make_unique<BlockT>();
          break;
        case Block::Type::BLOCK_Z:
          activeBlock = std::make_unique<BlockZ>();
          break;
        default:
          assert(!"We have accounted for all block types. This should not happen");
      }

      activeBlock->position = {0, 0};

      _board.nextBlockGenerated().notifyObservers(nextType);
    }
  }

  bool BaseLevel::executeCommand(const Command& command) {
    switch (command.type()) {

      case Command::Type::LEFT: {
        Block &activeBlock = *_board.activeBlock();
        for (unsigned int i = 0; i < command.multiplier(); i++) {
          if (_canMove(activeBlock, Direction::LEFT)) {
            activeBlock.position.col -= 1;
            continue;
          }
          else {
            _board.cellsUpdated().notifyObservers(_board.cells(), std::addressof(activeBlock));
            return false;
          }
        }

        _board.cellsUpdated().notifyObservers(_board.cells(), std::addressof(activeBlock));
        return true; 
      }
      break;

      case Command::Type::RIGHT: {
        Block &activeBlock = *_board.activeBlock();
        for (unsigned int i = 0; i < command.multiplier(); i++) {
          if (_canMove(activeBlock, Direction::RIGHT)) {
            activeBlock.position.col += 1;
            continue;
          }
          else {
            _board.cellsUpdated().notifyObservers(_board.cells(), std::addressof(activeBlock));
            return false;
          }
        }

        _board.cellsUpdated().notifyObservers(_board.cells(), std::addressof(activeBlock));
        return true; 
      }
      break;

      case Command::Type::DOWN: {
        Block &activeBlock = *_board.activeBlock();
        for (unsigned int i = 0; i < command.multiplier(); i++) {
          if (_canMove(activeBlock, Direction::DOWN)) {
            activeBlock.position.row += 1;
            continue;
          }
          else {
            _board.cellsUpdated().notifyObservers(_board.cells(), std::addressof(activeBlock));
            return false;
          }
        }

        _board.cellsUpdated().notifyObservers(_board.cells(), std::addressof(activeBlock));
        return true; 
      }
      break;

      case Command::Type::CLOCKWISE: {
        Block &activeBlock = *_board.activeBlock();
        
        for (unsigned int i = 0; i < command.multiplier(); i++) {
          activeBlock.rotate(Block::Rotation::CLOCKWISE);

          if (_isValidBlock(activeBlock)) {
            continue;
          }
          else {
            activeBlock.rotate(Block::Rotation::COUNTER_CLOCKWISE);
            _board.cellsUpdated().notifyObservers(_board.cells(), std::addressof(activeBlock));
            return false;
          }
        }

        _board.cellsUpdated().notifyObservers(_board.cells(), std::addressof(activeBlock));
        return true;
      }
      break;

      case Command::Type::COUNTER_CLOCKWISE: {
        Block &activeBlock = *_board.activeBlock();

        for (unsigned int i = 0; i < command.multiplier(); i++) {
          activeBlock.rotate(Block::Rotation::COUNTER_CLOCKWISE);

          if (_isValidBlock(activeBlock)) {
            continue;
          }
          else {
            activeBlock.rotate(Block::Rotation::CLOCKWISE);
            _board.cellsUpdated().notifyObservers(_board.cells(), std::addressof(activeBlock));
            return false;
          }
        }

        _board.cellsUpdated().notifyObservers(_board.cells(), std::addressof(activeBlock));
        return true;
      }
      break;

      case Command::Type::DROP: {
        Block &activeBlock = *_board.activeBlock();

        while (_canMove(activeBlock, BaseLevel::Direction::DOWN)) {
          activeBlock.position.row += 1;
        }

        for (Position p : activeBlock) {
          _board.cells()[p.row][p.col].blockType = activeBlock.type();
        }

        _board.activeBlock() = nullptr;
        _ensureActiveBlock();

        _board.cellsUpdated().notifyObservers(_board.cells(), std::addressof(activeBlock));
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

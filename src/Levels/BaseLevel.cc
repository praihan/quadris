#include <iostream>
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
  bool BaseLevel::_isCellOccupied(const Position &p) const {
    return _board.cells()[p.col][p.row].blockType != Block::Type::EMPTY;
  }
  bool BaseLevel::_isValidBlock(const Block &b) const {
    for (Position p : b) {
      if (p.row < 0 || p.row >= static_cast<int>(BOARD_HEIGHT)) {
        return false;
      }
      if (p.col < 0 || p.col >= static_cast<int>(BOARD_WIDTH)) {
        return false;
      }
      if (_isCellOccupied(p)) {
        return false;
      }
    }
    return true;
  }

  bool BaseLevel::_canMove(Block &b, const Direction d) const {
    switch(d) {
      default:
      case Direction::DOWN:
        b.position.row++;
        break;
      case Direction::LEFT:
        b.position.col--;
        break;
      case Direction::RIGHT: 
        b.position.col++;
        break;
      }

    bool ok = _isValidBlock(b);

    switch(d) {
      default:
      case Direction::DOWN:
        b.position.row--;
        break;
      case Direction::LEFT:
        b.position.col++;
        break;
      case Direction::RIGHT: 
        b.position.col--;
        break;
      }
    return ok;
  }

  void BaseLevel::_clearActiveBlockCells() {
    Block &activeBlock = *_board.activeBlock();
    Board::CellGrid &cg = _board.cells(); 

    for (Position p : activeBlock) {
      std::cout << __LINE__ << ": " << p.row << ' ' << p.col << '\n';
      cg[p.row][p.col].blockType = Block::Type::EMPTY;
    }
  }

  void BaseLevel::_setActiveBlockCells() {
    Block &activeBlock = *_board.activeBlock();
    Board::CellGrid &cg = _board.cells(); 

    for (Position p : activeBlock) {
      std::cout << __LINE__ << ": " << p.row << ' ' << p.col << ' ' << (int)activeBlock.type() << '\n';
      cg[p.row][p.col].blockType = (Block::Type)0xb00b;  //activeBlock.type();
    }
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

      _board.nextBlockGenerated().notifyObservers(nextType);
    }
  }

  bool BaseLevel::executeCommand(const Command& command) {
    _ensureActiveBlock();

    switch (command.type()) {
      case Command::Type::LEFT: {
        Block &activeBlock = *_board.activeBlock();
        
        if (_canMove(activeBlock, Direction::LEFT)) {
          activeBlock.position.col -= 1;
          _board.cellsUpdated().notifyObservers(_board.cells());

          std::cout << "GOOD" << std::endl;
          std::cout << activeBlock.position.row << activeBlock.position.col << std::endl;

          return true;
        }

          std::cout << "BAD" << std::endl;
          std::cout << activeBlock.position.row << activeBlock.position.col << std::endl;

        return false;
      }
      break;

      case Command::Type::RIGHT: {
        Block &activeBlock = *_board.activeBlock();
        if (_canMove(activeBlock, Direction::RIGHT)) {
          activeBlock.position.col += 1;
          _board.cellsUpdated().notifyObservers(_board.cells());

          std::cout << "GOOD" << std::endl;
          std::cout << activeBlock.position.row << activeBlock.position.col << std::endl;

          return true;
        }

          std::cout << "BAD" << std::endl;
          std::cout << activeBlock.position.row << activeBlock.position.col << std::endl;

        return false; 
      }
      break;

      case Command::Type::DOWN: {
        Block &activeBlock = *_board.activeBlock();
        if (_canMove(activeBlock, Direction::DOWN)) {
          activeBlock.position.row += 1;
          _board.cellsUpdated().notifyObservers(_board.cells());

          std::cout << "GOOD" << std::endl;
          std::cout << activeBlock.position.row << activeBlock.position.col << std::endl;

          return true;
        }
        
        std::cout << "BAD" << std::endl;
        std::cout << activeBlock.position.row << activeBlock.position.col << std::endl;

        return false;
      }
      break;

      case Command::Type::CLOCKWISE: {
        Block &activeBlock = *_board.activeBlock();

        _clearActiveBlockCells();
        
        activeBlock.rotate(Block::Rotation::CLOCKWISE);
        
        if (_isValidBlock(activeBlock)) {
          _board.cellsUpdated().notifyObservers(_board.cells());
          _setActiveBlockCells();
          return true;
        }
        else {
          activeBlock.rotate(Block::Rotation::COUNTER_CLOCKWISE);
          _setActiveBlockCells();
          return false;
        }
      }
      break;

      case Command::Type::COUNTER_CLOCKWISE: {
        Block &activeBlock = *_board.activeBlock();

        _clearActiveBlockCells();

        activeBlock.rotate(Block::Rotation::COUNTER_CLOCKWISE);
        
        if (_isValidBlock(activeBlock)) {
          _board.cellsUpdated().notifyObservers(_board.cells());
          _setActiveBlockCells();
          return true;
        }
        else {
          activeBlock.rotate(Block::Rotation::CLOCKWISE);
          _setActiveBlockCells();
          return false;

        }
      }
      break;

      case Command::Type::DROP: {
        std::cout << __LINE__ << ": " << _board.activeBlock().get() << '\n';
        Block &activeBlock = *_board.activeBlock();

        _clearActiveBlockCells();

        std::cout << __LINE__ << ": " << _board.activeBlock().get() << '\n';

        while (_canMove(activeBlock, BaseLevel::Direction::DOWN)) {
          activeBlock.position.row += 1;
        }

        std::cout << __LINE__ << ": " << _board.activeBlock().get() << '\n';

        _setActiveBlockCells();

        std::cout << __LINE__ << ": " << _board.activeBlock().get() << '\n';

        _board.cellsUpdated().notifyObservers(_board.cells());

        std::cout << __LINE__ << ": " << _board.activeBlock().get() << '\n';

        _board.activeBlock() = nullptr;
        _ensureActiveBlock();
        
        // TODO: account for false
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

#include "BaseLevel.h"
#include "Command.h"
#include "Block.h"

namespace qd {
  bool BaseLevel::_isCellOccupied(const Position &p) const {
    if (_board.cells()[p.col][p.row].blockType == Block::Type::EMPTY) {
      return false;
    }
  
    return true;
  }

  bool BaseLevel::_isValidBlock(const Block &b) const {
    for (Position p : b) {
      if (p.row < 0 || p.row > static_cast<int>(BOARD_HEIGHT)) return false;
      if (p.col < 0 || p.col > static_cast<int>(BOARD_WIDTH)) return false;

      if (_isCellOccupied(p)) {
        return false;
      }
    }

    return true;
  }

  bool BaseLevel::_canMove(const Block &b, const Direction d) const {
    for (Position p : b) {  
      switch(d) {
      default:
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
    }

    return _isValidBlock(b);
  }

  void BaseLevel::_clearActiveBlockCells() {
    Block &activeBlock = _board.activeBlock();
    Board::CellGrid &cg = _board.cells(); 

    for (Position p : activeBlock) {
      cg[p.row][p.col].blockType = Block::Type::EMPTY;
    }
  }

  void BaseLevel::_setActiveBlockCells() {
    Block &activeBlock = _board.activeBlock();
    Board::CellGrid &cg = _board.cells(); 

    for (Position p : activeBlock) {
      cg[p.row][p.col].blockType = activeBlock.type();
    }
  }

  void BaseLevel::executeCommand(const Command& command) {
    switch (command.type()) { 
      case Command::Type::LEFT: {
        Block &activeBlock = _board.activeBlock();
        if (_canMove(activeBlock, BaseLevel::Direction::LEFT)) {
          activeBlock.position.col -= 1;
          _board.cellsUpdated().notifyObservers(_board.cells());
        }
      }
      break;
      case Command::Type::RIGHT: {
        Block &activeBlock = _board.activeBlock();
        if (_canMove(activeBlock, BaseLevel::Direction::RIGHT)) {
          activeBlock.position.col += 1;
          _board.cellsUpdated().notifyObservers(_board.cells());
        }  
      }
      break;
      case Command::Type::DOWN: {
        Block &activeBlock = _board.activeBlock();
        if (_canMove(activeBlock, BaseLevel::Direction::DOWN)) {
          activeBlock.position.row += 1;
          _board.cellsUpdated().notifyObservers(_board.cells());
        }  
      }
      break;
      case Command::Type::CLOCKWISE: {
        Block &activeBlock = _board.activeBlock();

        _clearActiveBlockCells();
        
        activeBlock.rotate(Block::Rotation::CLOCKWISE);
        
        if (_isValidBlock(activeBlock)) {
          _board.cellsUpdated().notifyObservers(_board.cells());
        }
        else {
          activeBlock.rotate(Block::Rotation::COUNTER_CLOCKWISE);
        }

        _setActiveBlockCells();
      }
      break;
      case Command::Type::COUNTER_CLOCKWISE: {
        Block &activeBlock = _board.activeBlock();

        _clearActiveBlockCells();

        activeBlock.rotate(Block::Rotation::COUNTER_CLOCKWISE);
        
        if (_isValidBlock(activeBlock)) {
          _board.cellsUpdated().notifyObservers(_board.cells());
        }
        else {
          activeBlock.rotate(Block::Rotation::CLOCKWISE);
        }

        _setActiveBlockCells();
      }
      break;
      case Command::Type::DROP: {
        Block &activeBlock = _board.activeBlock();

        _clearActiveBlockCells();

        while (_canMove(activeBlock, BaseLevel::Direction::DOWN)) {
          activeBlock.position.row += 1;
        }

        _setActiveBlockCells();

        _board.cellsUpdated().notifyObservers(_board.cells());
      }
      break;
      default: 
      break;
    }
  }

}

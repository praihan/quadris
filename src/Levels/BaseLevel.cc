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

  bool BaseLevel::_canMoveLeft(const Block &b) const {
    for (Position p : b) {
      if (p.col <= 0) {
        return false;
      }

      p.col--;

      if (_isCellOccupied(p)) {
        return false;
      }
    }

    return true;
  }

  bool BaseLevel::_canMoveRight(const Block &b) const {
    for (Position p : b) {
      if (p.col >= 11) {
        return false;
      }

      p.col++;

      if (_isCellOccupied(p)) {
        return false;
      }
    }

    return true;
  }

  bool BaseLevel::_canMoveDown(const Block &b) const {
    for (Position p : b) {
      if (p.row >= 15) {
        return false;
      }

      p.row++;

      if (_isCellOccupied(p)) {
        return false;
      }
    }

    return true;
  }

  void BaseLevel::executeCommand(const Command& command) {
    switch (command.type()) { 
      case Command::Type::LEFT: {
        Block &activeBlock = _board.activeBlock();
        if (_canMoveLeft(activeBlock)) {
          activeBlock.position.col -= 1;
          _board.cellsUpdated().notifyObservers(_board.cells());
        }
      }
      break;
      case Command::Type::RIGHT: {
        Block &activeBlock = _board.activeBlock();
        if (_canMoveRight(activeBlock)) {
          activeBlock.position.col += 1;
          _board.cellsUpdated().notifyObservers(_board.cells());
        }  
      }
      break;
      case Command::Type::DOWN: {
        Block &activeBlock = _board.activeBlock();
        if (_canMoveDown(activeBlock)) {
          activeBlock.position.row += 1;
          _board.cellsUpdated().notifyObservers(_board.cells());
        }  
      }
      break;
      case Command::Type::CLOCKWISE: {
      
      }
      break;
      case Command::Type::COUNTER_CLOCKWISE: {
        
      }
      break;
      case Command::Type::DROP: {
        Block &activeBlock = _board.activeBlock();
        while (_canMoveDown(activeBlock)) {
          activeBlock.position.row += 1;
        }
        
        //update array
        _board.cells();

        //replace block
      }
      break;
      default: 
      break;
    }
  }

}

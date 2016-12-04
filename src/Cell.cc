#include "Cell.h"

namespace qd {
  Cell::Cell() : blockType{ Block::Type::EMPTY } { }
  Cell::Cell(const Cell& other) {
    *this = other;
  }
  Cell::Cell(Cell&& other) {
    *this = std::move(other);
  }
  Cell& Cell::operator=(const Cell& other) {
    blockType = other.blockType;
    owningBlock = other.owningBlock;
    return *this;
  }
  Cell& Cell::operator=(Cell&& other) {
    blockType = std::move(other.blockType);
    owningBlock = std::move(other.owningBlock);
    other.blockType = Block::Type::EMPTY;
    return *this;
  }
  void Cell::clear() {
    blockType = Block::Type::EMPTY;
    owningBlock = nullptr;
  }
}
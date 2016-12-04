#include "Block.h"
#include <utility>

namespace qd {
  Block::Block() {
  }
  Block::Block(const Block& other) {
    *this = other;
  }
  Block::Block(Block&& other) {
    *this = std::move(other);
  }
  Block& Block::operator=(const Block& other) {
    occupiedPositions = other.occupiedPositions;
    _metaInfo = other._metaInfo;
    return *this;
  }
  Block& Block::operator=(Block&& other) {
    occupiedPositions = std::move(other.occupiedPositions);
    _metaInfo = std::move(other._metaInfo);
    return *this;
  }

  Block::~Block() {
    destroyed().notifyObservers(*this);
  }

  Block::PositionIterator Block::begin() const {
    return { *this, this->occupiedPositions.cbegin() };
  }
  Block::PositionIterator Block::end() const {
    return { *this, this->occupiedPositions.cend() };
  }

  Block::PositionIterator::PositionIterator(
    const Block& block,
    typename std::vector<Position>::const_iterator iter
  ) : _block{block}, _iter{iter} {
  }

  Block::PositionIterator& Block::PositionIterator::operator+=(
    Block::PositionIterator::difference_type n
  ) {
    this->_iter += n;
    return *this;
  }

  Block::PositionIterator Block::PositionIterator::operator+(
    Block::PositionIterator::difference_type n
  ) const {
    return { this->_block, this->_iter + n };
  }

  Block::PositionIterator operator+(
    Block::PositionIterator::difference_type n,
    const Block::PositionIterator& iter
  ) {
    return iter + n;
  }

  Block::PositionIterator& Block::PositionIterator::operator-=(
    Block::PositionIterator::difference_type n
  ) {
    this->_iter -= n;
    return *this;
  }
  Block::PositionIterator Block::PositionIterator::operator-(
    Block::PositionIterator::difference_type n
  ) const {
    return { this->_block, this->_iter - n };
  }
  Block::PositionIterator::difference_type Block::PositionIterator::operator-(
    const Block::PositionIterator& other
  ) const {
    return this->_iter - other._iter;
  }

  Block::PositionIterator::reference Block::PositionIterator::operator[](
    Block::PositionIterator::difference_type n
  ) const {
    return *(*this + n);
  }

  bool Block::PositionIterator::operator<(
    const Block::PositionIterator& other
  ) const {
    return this->_iter < other._iter;
  }
  bool Block::PositionIterator::operator<=(
    const PositionIterator& other
  ) const {
    return this->_iter <= other._iter;
  }

  Block::PositionIterator& Block::PositionIterator::operator--() {
    --this->_iter;
    return *this;
  }
  Block::PositionIterator Block::PositionIterator::operator--(int) {
    auto copy = *this;
    --this->_iter;
    return copy;
  }

  Block::PositionIterator& Block::PositionIterator::operator++() {
    ++this->_iter;
    return *this;
  }
  Block::PositionIterator Block::PositionIterator::operator++(int) {
    auto copy = *this;
    ++this->_iter;
    return copy;
  }

  Block::PositionIterator::reference Block::PositionIterator::operator*() const {
    return this->_block.position + *this->_iter;
  }
  Block::PositionIterator::reference Block::PositionIterator::operator->() const {
    return **this;
  }

  bool Block::PositionIterator::operator==(
    const PositionIterator& other
  ) const {
    return this->_iter == other._iter;
  }

  bool Block::PositionIterator::operator!=(
    const PositionIterator& other
  ) const {
    return !(*this == other);
  }
}

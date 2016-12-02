#ifndef BLOCK_H_
#define BLOCK_H_

#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include <cstddef>
#include <iterator>
#include "Position.h"

namespace qd {

  class Block {
  protected:
    std::vector<Position> occupiedPositions;
    bool _heavy;

  public:
    Block(const bool heavy = false);
    virtual ~Block() = default;

    enum class Type {
      EMPTY,
      BLOCK_I,
      BLOCK_J,
      BLOCK_L,
      BLOCK_O,
      BLOCK_S,
      BLOCK_T,
      BLOCK_Z
    };

    enum class Rotation {
      CLOCKWISE,
      COUNTER_CLOCKWISE
    };

    class PositionIterator : public std::iterator<
        std::random_access_iterator_tag, // iterator_category
        Position, // value_type
        std::ptrdiff_t, // difference_type,
        const Position*, // pointer
        Position // reference
      > {
    public:
      PositionIterator(const Block& block, typename std::vector<Position>::const_iterator iter);

      PositionIterator& operator+=(difference_type n);
      PositionIterator operator+(difference_type n) const;
      PositionIterator friend operator+(difference_type, const PositionIterator& iter);
      PositionIterator& operator-=(difference_type n);
      PositionIterator operator-(difference_type n) const;
      difference_type operator-(const PositionIterator& other) const;
      reference operator[](difference_type n) const;
      bool operator<(const PositionIterator& other) const;
      bool operator<=(const PositionIterator& other) const;

      PositionIterator& operator--();
      PositionIterator operator--(int);

      PositionIterator& operator++();
      PositionIterator operator++(int);

      reference operator*() const;
      reference operator->() const;

      bool operator==(const PositionIterator& other) const;
      bool operator!=(const PositionIterator& other) const;

    private:
      const Block& _block;
      typename std::vector<Position>::const_iterator _iter;
    };

    Position position;

    virtual bool heavy() const;
    virtual bool heavy(bool value);

    virtual void rotate(Rotation) = 0;
    virtual PositionIterator begin() const;
    virtual PositionIterator end() const;
    virtual Type type() const = 0;
    virtual std::unique_ptr<Block> clone() = 0;
  };

}

#endif


#ifndef BLOCK_H_
#define BLOCK_H_

#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include <cstddef>
#include <iterator>
#include "Position.h"
#include "Optional.h"

namespace qd {

  class Block {
  public:
    struct MetaInfo {
      Optional<bool> heavy;
      Optional<int> spawnLevel;
    };
  protected:
    mutable std::vector<Position> occupiedPositions;
    mutable MetaInfo _metaInfo;
  public:
    Position position;

  public:
    Block();
    virtual ~Block() = default;

    enum class Type {
      EMPTY,
      BLOCK_I,
      BLOCK_J,
      BLOCK_L,
      BLOCK_O,
      BLOCK_S,
      BLOCK_T,
      BLOCK_Z,
      BLOCK_HINT
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

    MetaInfo& metaInfo();
    const MetaInfo& metaInfo() const;

    virtual void rotate(Rotation) = 0;
    virtual PositionIterator begin() const;
    virtual PositionIterator end() const;
    virtual Type type() const = 0;
    virtual std::unique_ptr<Block> clone() = 0;
  };

}

#endif


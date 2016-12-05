#include <cassert>
#include <memory>
#include <climits>
#include <utility>
#include <functional>
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
#include "QdDefs.h"

namespace  {
  int absolute_val(int n) {
    return (n > 0) ? n : -n;
  }
}

namespace qd {

  namespace {
    /// creates a Block from a Block::Type without any metaInfo
    template <class... Args>
    std::unique_ptr<Block> createRawBlockFromType(Block::Type type) {
      switch (type) {
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

  BaseLevel::~BaseLevel() {
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
              QD_UNREACHABLE();
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
        for (unsigned int i = 0; i < command.multiplier(); ++i) {
          if (_canMove(*activeBlockPtr, movementDir)) {
            moveInDirection(activeBlockPtr->position, movementDir);
          }
          else {
            break;
          }
        }

        if (activeBlockPtr->metaInfo().heavy.valueOr(false) && movementDir != Direction::DOWN &&
          _canMove(*activeBlockPtr, Direction::DOWN)) {
          moveInDirection(activeBlockPtr->position, Direction::DOWN);
        }

        notifyCellsUpdated();
        return true;
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
              QD_UNREACHABLE();
              break;
          }
        });
        // opposite of rotationDirection
        const Block::Rotation antiRotationDirection = iife([&rotationDirection]() {
          return rotationDirection == Block::Rotation::CLOCKWISE ?
            Block::Rotation::COUNTER_CLOCKWISE : Block::Rotation::CLOCKWISE;
        });
        for (unsigned int i = 0; i < command.multiplier() % 4; ++i) {
          activeBlockPtr->rotate(rotationDirection);

          if (!_isValidBlock(*activeBlockPtr)) {
            activeBlockPtr->rotate(antiRotationDirection);
          }
        }

        if (
          activeBlockPtr->metaInfo().heavy.valueOr(false) &&
          _canMove(*activeBlockPtr, Direction::DOWN)
        ) {
          activeBlockPtr->position.row += 1;
        }

        notifyCellsUpdated();
        return true;
      }
        break;

      case Command::Type::DROP: {
        for (unsigned int i = 0; i < command.multiplier(); ++i) {
          while (_canMove(*activeBlockPtr, BaseLevel::Direction::DOWN)) {
            activeBlockPtr->position.row += 1;
          }

          for (Position p : *activeBlockPtr) {
            Cell& cell = _board.cells()[p.row][p.col];
            cell.blockType = activeBlockPtr->type();
            cell.owningBlock = activeBlockPtr;
          }

          _board.trackActiveBlock();
          activeBlockPtr = nullptr;

          _ensureBlocksGenerated();
          _checkBlocksCleared();
          notifyCellsUpdated();
          if (_checkGameEnd()) {
            return false;
          }
        }

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
              return Block::Type::BLOCK_Z;
            case Command::Type::BLOCK_T:
              return Block::Type::BLOCK_T;
            default:
              assert(!"Unreachable");
              QD_UNREACHABLE();
              break;
          }
        });
        _board.nextBlockPtr() = _createBlockFromType(blockType);
        _board.nextBlockGenerated().notifyObservers(blockType);

        return true;
      }
        break;

      case Command::Type::NORANDOM: {
        _turnOffRandom(command.arguments()[0]);
        return true;
      }
        break;
      case Command::Type::RANDOM: {
        _turnOnRandom();
        return true;
      }
        break;

      case Command::Type::HINT: {
        std::unique_ptr<Block> bcpyl = activeBlockPtr->clone();
	      Position bestPos = activeBlockPtr->position;
        int rotation = 0;
        int bestVariance = INT_MAX;
        int initialHeight = activeBlockPtr->position.row;

        for (int i = 0; i < 4; i++) { // Loop to check all rotations
          bcpyl->position.col = activeBlockPtr->position.col; // Copy of active block to check validity
          while (_isValidBlock(*bcpyl)) { // Move current block as left as possible
            bcpyl->position.col--;
          }
          bcpyl->position.col++;

          while (_isValidBlock(*bcpyl)) { // Move block right, while checking surface variance of new grid with dropped block
            while (_canMove(*bcpyl, BaseLevel::Direction::DOWN)) {// Dropping current block
              bcpyl->position.row += 1;
            }

            // Set
            for (Position p : *bcpyl) {
              _board.cells()[p.row][p.col].blockType = bcpyl->type();
            }

            // Scan and compare
            int currVariance = 0;
            for (std::size_t j = 0; j < BOARD_WIDTH - 1; j++) { // Calculating variance in column height
              currVariance += absolute_val(_getHeight(j) - _getHeight(j+1));
            }

            for (std::size_t j = 0; j < BOARD_WIDTH; j++) { // Calculating hole contribution to variance
              currVariance += _ifHole(j);
            }
            // Update best
            if (currVariance < bestVariance) {
              bestVariance = currVariance;
              rotation = i;
              bestPos = bcpyl->position;
            }
            else if (currVariance == bestVariance && bcpyl->position.row > bestPos.row) {
              bestVariance = currVariance;
              rotation = i;
              bestPos = bcpyl->position;
            }

            // Unset
            for (Position p : *bcpyl) {
              _board.cells()[p.row][p.col].blockType = Block::Type::EMPTY;
            }

            bcpyl->position.row = initialHeight; // Resetting block to initial height
            bcpyl->position.col++; // Moving right by one column
          }
        bcpyl->rotate(Block::Rotation::CLOCKWISE);
        }

        for (int i = 0; i < rotation; i++) { // Configure to best position by rotating and setting position
          bcpyl->rotate(Block::Rotation::CLOCKWISE);
        }

        bcpyl->position = bestPos;

        _board.hintProvided().notifyObservers(std::vector<Position>(bcpyl->begin(), bcpyl->end()));
        return true;
      }
        break;
      default:
        return false;
        break;
    }
  }

  void BaseLevel::_defaultInitialization() {
    std::shared_ptr<Block>& nextBlockPtr = _board.nextBlockPtr();
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

  void BaseLevel::_checkBlocksCleared() {
    auto& cells = _board.cells();

    // this array represents how much a line has to move by.
    // to be exact:
    //   linesDiff[i] represents how many lines the current i'th
    //                line should go down by
    // if 2 consecutive lines in the middle are cleared you'll get
    // something like:
    //   2 2 2 2 2 2 1 0 0 0 0 0 0
    std::array<int, BOARD_HEIGHT> linesDiff = { };

    std::vector<int> lineIndexesCleared;

    for (auto i = cells.begin() + 3; i != cells.end(); ++i) {
      if (std::any_of(i->cbegin(), i->cend(), [](const Cell& cell) {
        return cell.blockType == Block::Type::EMPTY;
      })) {
        // if any blockType is empty, this row doesn't count
        continue;
      }

      auto lineIndex = static_cast<int>(std::distance(cells.begin(), i));
      std::transform(
        linesDiff.begin(), linesDiff.begin() + lineIndex - 3,
        linesDiff.begin(),
        [](int val) {
          return val + 1;
        }
      );
      lineIndexesCleared.push_back(lineIndex);
    }

    const int numberOfLinesCleared = lineIndexesCleared.size();
    if (numberOfLinesCleared == 0) {
      return;
    }

    // we notify linesCleared _before_ we actually clear them
    _board.linesCleared().notifyObservers(lineIndexesCleared);

    std::for_each(
      lineIndexesCleared.begin(), lineIndexesCleared.end(),
      [&](int i) {
        // clear a row
        // this may raise Events such as Block::destroyed()
        std::for_each(
          cells[i].begin(), cells[i].end(), [](Cell& cell) {
            cell.clear();
          }
        );
      }
    );


    decltype(linesDiff) markedLinesDiff;
    markedLinesDiff[0] = linesDiff[0];

    std::transform(
      linesDiff.begin(), linesDiff.end() - 1,
      linesDiff.begin() + 1, markedLinesDiff.begin() + 1,
      [](auto prevDiff, auto curDiff) {
        // if the current diff < prev, this means that current line
        // is being cleared, so we mark it as such with a -1
        return curDiff < prevDiff ? -1 : curDiff;
      }
    );

    // this is where we actually move around the rows.
    // we go through the markedLinesDiff array and apply it
    // to our cells using move assignments.
    for (auto i = markedLinesDiff.end() - 1; i >= markedLinesDiff.begin(); --i) {
      if (*i <= 0) {
        continue;
      }
      auto sourceDistance = std::distance(markedLinesDiff.begin(), i);

      auto& sourceRow = cells.at(sourceDistance + 3);
      auto& destRow = cells.at(sourceDistance + *i + 3);
      
      destRow = std::move(sourceRow);
    }

    // Calculate the scoring based on what we have cleared
    auto sqr = [](int a) -> int { return a * a; };

    int baseScore = sqr(levelNumber() + numberOfLinesCleared);

    int clearedBlocksScore = 0;
    auto& trackedBlockInfo = _board.trackedBlockHistory();
    // if any Blocks were cleared, then trackedBlockInfo should
    // contain the MetaInfo we need to calculate scoring
    while (!trackedBlockInfo.empty()) {
      const Block::MetaInfo& blockMetaInfo = trackedBlockInfo.front();
      int spawnLevel = blockMetaInfo.spawnLevel.value();
      clearedBlocksScore += sqr(spawnLevel + 1);
      trackedBlockInfo.pop_back();
    }
    _board.score().incrementBy(baseScore + clearedBlocksScore);
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

  // Returns height of empty cells of col from top to bottom
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

  // Returns variance adjustment for each hole in col
  int BaseLevel::_ifHole(const int col) const { 
    int hole=0;
    std::size_t i = 0;
    for (; i < BOARD_HEIGHT+3; i++) {
      if (!(_board.cells()[i][col].blockType == Block::Type::EMPTY)) {
        break;
      }
    }

    for (; i < BOARD_HEIGHT+3; i++) {
      if (_board.cells()[i][col].blockType == Block::Type::EMPTY) {
        hole += 8;
      }
    }
    return hole;
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
    std::shared_ptr<Block>& activeBlockPtr = _board.activeBlockPtr();
    std::shared_ptr<Block>& nextBlockPtr = _board.nextBlockPtr();

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
    return  false;
  }

  void BaseLevel::_turnOffRandom(std::string filename) {
  }

  void BaseLevel::_turnOnRandom() {
  }

}

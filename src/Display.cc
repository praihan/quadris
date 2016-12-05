#include "Display.h"
#include "Board.h"
#include <functional>
#include <iostream>
#include <iterator>
#include <algorithm>

namespace qd {

  const BlockI Display::_sampleBlockI{};
  const BlockJ Display::_sampleBlockJ{};
  const BlockL Display::_sampleBlockL{};
  const BlockO Display::_sampleBlockO{};
  const BlockS Display::_sampleBlockS{};
  const BlockT Display::_sampleBlockT{};
  const BlockZ Display::_sampleBlockZ{};

  const std::map<Block::Type, const Block*> Display::sampleBlocks = {
    { Block::Type::EMPTY, nullptr },
    { Block::Type::BLOCK_I, std::addressof(Display::_sampleBlockI) },
    { Block::Type::BLOCK_J, std::addressof(Display::_sampleBlockJ) },
    { Block::Type::BLOCK_L, std::addressof(Display::_sampleBlockL) },
    { Block::Type::BLOCK_O, std::addressof(Display::_sampleBlockO) },
    { Block::Type::BLOCK_S, std::addressof(Display::_sampleBlockS) },
    { Block::Type::BLOCK_T, std::addressof(Display::_sampleBlockT) },
    { Block::Type::BLOCK_Z, std::addressof(Display::_sampleBlockZ) },
  };

  Display::Display(const Board& board) {
    board.cellsUpdated().addObserver(
      _cellsUpdatedSlot, std::bind(
        &Display::onCellsUpdated, this,
        std::placeholders::_1, std::placeholders::_2
      )
    );
    board.scoreUpdated().addObserver(
      _scoreUpdatedSlot, std::bind(&Display::onScoreUpdated, this, std::placeholders::_1)
    );
    board.hiScoreUpdated().addObserver(
      _hiScoreUpdatedSlot, std::bind(&Display::onHiScoreUpdated, this, std::placeholders::_1)
    );
    board.nextBlockGenerated().addObserver(
      _nextBlockGeneratedSlot, std::bind(&Display::onNextBlockGenerated, this, std::placeholders::_1)
    );
    board.gameStarted().addObserver(
      _gameStartedSlot, std::bind(&Display::onGameStarted, this)
    );
    board.gameEnded().addObserver(
      _gameEndedSlot, std::bind(&Display::onGameEnded, this)
    );
    board.levelChanged().addObserver(
      _levelChangedSlot, std::bind(&Display::onLevelChanged, this, std::placeholders::_1)
    );
    board.hintProvided().addObserver(
      _hintProvidedSlot, std::bind(&Display::onHint, this, std::placeholders::_1)
    );

    for (auto& row : _boardState) {
      for (Block::Type& blockType : row) {
        blockType = Block::Type::EMPTY;
      }
    }
  }

  void Display::onCellsUpdated(const Board::CellGrid& cells, const Block* blockPtr) {
    std::for_each(
      cells.begin(), cells.end(),
      [lineItr = _boardState.begin()](const auto& cellRow) mutable {
        // map each blockType to a char
        std::transform(
          cellRow.begin(), cellRow.end(),
          lineItr->begin(), [](const Cell& cell) -> Block::Type {
            return cell.blockType;
          }
        );
        ++lineItr;
      }
    );

    if (blockPtr != nullptr) {
      for (Position p : *blockPtr) {
        _boardState[p.row][p.col] = blockPtr->type();
      }
    }
  }
  void Display::onScoreUpdated(int score) {
    _score = score;
  }
  void Display::onHiScoreUpdated(int hiScore) {
    _hiScore = hiScore;
  }
  void Display::onNextBlockGenerated(Block::Type blockType) {
    _nextBlockType = blockType;
  }
  void Display::onLevelChanged(int level) {
    _level = level;
  }
  void Display::onGameStarted() {
  }
  void Display::onGameEnded() {
  }
  void Display::onHint(const std::vector<Position>& positions) {
    for (Position p : positions) {
      _boardState[p.row][p.col] = Block::Type::BLOCK_HINT;
    }
  }

}

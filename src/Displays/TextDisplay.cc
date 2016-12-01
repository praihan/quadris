#include "TextDisplay.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>
#include <memory>

#include "Utility.h"
#include "Blocks/BlockI.h"
#include "Blocks/BlockJ.h"
#include "Blocks/BlockL.h"
#include "Blocks/BlockO.h"
#include "Blocks/BlockS.h"
#include "Blocks/BlockT.h"
#include "Blocks/BlockZ.h"

namespace qd {

  namespace {
    const std::map<Block::Type, char> blockTypeToChar = {
      { Block::Type::EMPTY, ' ' },
      { Block::Type::BLOCK_I, 'I' },
      { Block::Type::BLOCK_J, 'J' },
      { Block::Type::BLOCK_L, 'L' },
      { Block::Type::BLOCK_O, 'O' },
      { Block::Type::BLOCK_S, 'S' },
      { Block::Type::BLOCK_T, 'T' },
      { Block::Type::BLOCK_Z, 'Z' },
    };

    const BlockI _sampleBlockI = iife([]() { BlockI b; b.position = { -2, 0 }; return b; });
    const BlockJ _sampleBlockJ = iife([]() { BlockJ b; b.position = { -2, 0 }; return b; });
    const BlockL _sampleBlockL = iife([]() { BlockL b; b.position = { -2, 0 }; return b; });
    const BlockO _sampleBlockO = iife([]() { BlockO b; b.position = { -2, 0 }; return b; });
    const BlockS _sampleBlockS = iife([]() { BlockS b; b.position = { -2, 0 }; return b; });
    const BlockT _sampleBlockT = iife([]() { BlockT b; b.position = { -2, 0 }; return b; });
    const BlockZ _sampleBlockZ = iife([]() { BlockZ b; b.position = { -2, 0 }; return b; });

    const std::map<Block::Type, const Block*> sampleBlocks = {
      { Block::Type::EMPTY, nullptr },
      { Block::Type::BLOCK_I, std::addressof(_sampleBlockI) },
      { Block::Type::BLOCK_J, std::addressof(_sampleBlockJ) },
      { Block::Type::BLOCK_L, std::addressof(_sampleBlockL) },
      { Block::Type::BLOCK_O, std::addressof(_sampleBlockO) },
      { Block::Type::BLOCK_S, std::addressof(_sampleBlockS) },
      { Block::Type::BLOCK_T, std::addressof(_sampleBlockT) },
      { Block::Type::BLOCK_Z, std::addressof(_sampleBlockZ) },
    };
  }

  TextDisplay::TextDisplay(const Board& b) : Display{b} {
    _displayBuffer = {
      "Level:",
      "Score:",
      "Hi Score:",
      "-----------",
      "           ",
      "           ",
      "           ",
      "           ",
      "           ",
      "           ",
      "           ",
      "           ",
      "           ",
      "           ",
      "           ",
      "           ",
      "           ",
      "           ",
      "           ",
      "-----------",
      "Next:",
      "",
      "",
    };
  }

  void TextDisplay::onCellsUpdated(const Board::CellGrid& cells, const Block* b) {
    std::cout << "CELLS UPDATED" << std::endl;
    std::transform(
      cells.begin() + 3, cells.end(), // we skip the first 3 lines of the CellGrid
      _displayBuffer.begin() + 4, // we also skip outputting to the first 4 lines
      [](const auto& cellRow) {
        std::string line;
        // map each blockType to a char
        std::transform(
          cellRow.begin(), cellRow.end(),
          std::back_inserter(line), [](const Cell& cell) -> char {
            return blockTypeToChar.at(cell.blockType);
          }
        );
        return line;
      }
    );

    if (b != nullptr) {
      const Block& block = *b;
      for (Position p : block) {
        if (p.row < 3) {
          continue;
        }
        const int rowIndex = p.row - 3 + 4; // -3 for the 3 unseen rows, +4 for the text at the top
        _displayBuffer[rowIndex][p.col] = blockTypeToChar.at(block.type());
      }
    }
  }

  void TextDisplay::onScoreUpdated(int score) {
    auto scoreString = std::to_string(score);
    _displayBuffer[1] = "Score: " + scoreString;
  }

  void TextDisplay::onHiScoreUpdated(int hiScore) {
    auto hiScoreString = std::to_string(hiScore);
    _displayBuffer[2] = "Hi Score: " + hiScoreString;
  }

  void TextDisplay::onNextBlockGenerated(Block::Type blockType) {
    std::cout << "NEXT BLOCK GENERATED" << std::endl;
    const Block* sampleBlock = sampleBlocks.at(blockType);

    const auto nextBlockLineItr = _displayBuffer.begin() + 21;
    nextBlockLineItr[0] = nextBlockLineItr[1] = "           ";

    if (sampleBlock == nullptr) {
      // we've already cleared it
      return;
    }
    for (Position p : *sampleBlock) {
      std::cout << p << std::endl;
      nextBlockLineItr[p.row][p.col] = blockTypeToChar.at(sampleBlock->type());
    }
  }

  void TextDisplay::onGameStarted() {
    std::cout << "GAME STARTED" << std::endl;
  }

  void TextDisplay::onGameEnded() {
    std::cout << "GAME RESET" << std::endl;
  }

  void TextDisplay::outputDisplay() {
    std::copy(
      _displayBuffer.begin(),
      _displayBuffer.end(),
      std::ostream_iterator<std::string>(std::cout, "\n")
    );
  }

}

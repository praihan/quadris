#include "TextDisplay.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>

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
  }

  TextDisplay::TextDisplay(const Board& b) : Display{b} {
    _displayBuffer = {
      "Level:",
      "Score:",
      "Hi Score:",
      "-----------",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
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
        std::cout << p << std::endl;
        const int rowIndex = p.row - 3 + 4; // -3 for the 3 unseen rows, +4 for the text at the top
        _displayBuffer[rowIndex][p.col] = blockTypeToChar.at(block.type());
      }
    }
  }

  void TextDisplay::onScoreUpdated(int score) {
    std::cout << "SCORE UPDATED: " << score << std::endl;
  }

  void TextDisplay::onHiScoreUpdated(int hiScore) {
    std::cout << "HI SCORE UPDATED: " << hiScore << std::endl;
  }

  void TextDisplay::onNextBlockGenerated(Block::Type) {
    std::cout << "NEXT BLOCK GENERATED" << std::endl;
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

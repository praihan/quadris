#include "TextDisplay.h"
#include <iostream>

namespace qd {

  void TextDisplay::onCellsUpdated(const Board::CellGrid& cells) {
    std::cout << "CELLS UPDATED" << std::endl;
  }

  void TextDisplay::onScoreUpdated(int score) {
    std::cout << "SCORE UPDATED: " << score << std::endl;
  }

  void TextDisplay::onHiScoreUpdated(int hiScore) {
    std::cout << "HI SCORE UPDATED: " << hiScore << std::endl;
  }

  void TextDisplay::onNextBlockGenerated() {
    std::cout << "NEXT BLOCK GENERATED" << std::endl;
  }

  void TextDisplay::onGameReset() {
    std::cout << "GAME RESET" << std::endl;
  }

}

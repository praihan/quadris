#include "TextDisplay.h"
#include <iostream>

namespace qd {

  void TextDisplay::onCellsUpdated(const Board::CellGrid& cells, const Block* b) {
    std::cout << "CELLS UPDATED" << std::endl;
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
    std::cout << "OUTPUT" << std::endl;
  }

}

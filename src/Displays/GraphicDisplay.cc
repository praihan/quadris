#include "GraphicDisplay.h"
#include "window.h"
#include <string>

namespace qd {
  
  void GraphicDisplay::onCellsUpdated(const Board::CellGrid& cells, const Block* b) {
    
  }

  void GraphicDisplay::onScoreUpdated(int score) {
    //std::string scoreStr = "Score: " + std::to_string(score);

    //drawString(x, y, scoreStr)
  }

  void GraphicDisplay::onHiScoreUpdated(int hiScore) {

  }

  void GraphicDisplay::onNextBlockGenerated(Block::Type) {
  
  }

  void GraphicDisplay::onGameStarted() {

  }

  void GraphicDisplay::onGameEnded() {

  }

  void GraphicDisplay::outputDisplay() {

  }

  void GraphicDisplay::onLevelChanged(int level) {

  }
}

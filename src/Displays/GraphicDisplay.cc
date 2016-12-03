#include "GraphicDisplay.h"
#include "window.h"
#include <string>

namespace qd {

  GraphicDisplay::GraphicDisplay(const Board& b) : Display{b} {
    
  }
  
  void GraphicDisplay::onCellsUpdated(const Board::CellGrid& cells, const Block* b) {
    
  }

  void GraphicDisplay::onScoreUpdated(int score) {
    
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

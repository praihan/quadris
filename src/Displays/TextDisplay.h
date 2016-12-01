#ifndef TEXT_DISPLAY_H_
#define TEXT_DISPLAY_H_

#include "Display.h"
#include <vector>
#include <string>

namespace qd {

  class TextDisplay : public Display {
  public:
    static constexpr std::size_t DISPLAY_HEIGHT =
      BOARD_HEIGHT + // the board
      2 + // the two bars for the border
      3 + // the three lines of text at the top
      3; // the three lines at the bottom
    static constexpr std::size_t DISPLAY_WIDTH = BOARD_WIDTH;
    using DisplayBuffer = std::vector<std::string>;

  public:
    TextDisplay(const Board& b);

  protected:
    virtual void onCellsUpdated(const Board::CellGrid&, const Block*) override;
    virtual void onScoreUpdated(int score) override;
    virtual void onHiScoreUpdated(int hiScore) override;
    virtual void onNextBlockGenerated(Block::Type) override;
    virtual void onGameStarted() override;
    virtual void onGameEnded() override;

  public:
    virtual void outputDisplay() override;
  
  private:
    DisplayBuffer _displayBuffer;
  };

}

#endif

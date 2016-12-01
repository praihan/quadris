#ifndef TEXT_DISPLAY_H_
#define TEXT_DISPLAY_H_

#include "Display.h"

namespace qd {

  class TextDisplay : public Display {
  public:
    using Display::Display;

  protected:
    virtual void onCellsUpdated(const Board::CellGrid&) override;
    virtual void onScoreUpdated(int score) override;
    virtual void onHiScoreUpdated(int hiScore) override;
    virtual void onNextBlockGenerated(Block::Type) override;
    virtual void onGameReset() override;
  };

}

#endif


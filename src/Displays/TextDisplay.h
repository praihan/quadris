#ifndef TEXT_DISPLAY_H_
#define TEXT_DISPLAY_H_

#include "Display.h"

namespace qd {

  class TextDisplay : public Display {
  public:
    virtual void onGameStarted() override;
    virtual void onCellsUpdated(const Board::CellGrid&) override;
    virtual void onScoreUpdated() override;
    virtual void onHiScoreUpdated() override;
    virtual void onNextBlockGenerated() override;
    virtual void onGameEnded() override;
  };

}

#endif


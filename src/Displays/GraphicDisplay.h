#ifndef GRAPHIC_DISPLAY_H_
#define GRAPHIC_DISPLAY_H_

#include "Display.h"


namespace qd {

  class GraphicDisplay : public Display {
  public:
    GraphicDisplay(const Board& b);

  protected:
    virtual void onCellsUpdated(const Board::CellGrid&, const Block* b) override;
    virtual void onScoreUpdated(int score) override;
    virtual void onHiScoreUpdated(int hiScore) override;
    virtual void onNextBlockGenerated(Block::Type) override;
    virtual void onGameStarted() override;
    virtual void onGameEnded() override;
    virtual void onLevelChanged(int level) override;

  public:
    virtual void outputDisplay() override;
  };

}

#endif

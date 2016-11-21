#ifndef GRAPHIC_DISPLAY_H_
#define GRAPHIC_DISPLAY_H_

#include "Display.h";

namespace qd {

  class GraphicDisplay : public Display {
  public:
    virtual void onGameStarted() override;
    virtual void onCellUpdated() override;
    virtual void onScoreUpdated() override;
    virtual void onHiScoreUpdated() override;
    virtual void onNextBlockGenerated() override;
    virtual void onGameEnded() override;
  };

}

#endif


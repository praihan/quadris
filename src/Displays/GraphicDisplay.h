#ifndef GRAPHIC_DISPLAY_H_
#define GRAPHIC_DISPLAY_H_

#include "Display.h"
#include "window.h"

namespace qd {

  class GraphicDisplay : public Display {
  public:
    GraphicDisplay(const Board&);

  public:
    virtual void outputDisplay() override;
    Xwindow _window;
  };

}

#endif

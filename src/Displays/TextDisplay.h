#ifndef TEXT_DISPLAY_H_
#define TEXT_DISPLAY_H_

#include "Display.h"
#include <vector>
#include <string>

namespace qd {

  class TextDisplay : public Display {
  public:
    using Display::Display;

  public:
    virtual void outputDisplay() override;
  };

}

#endif

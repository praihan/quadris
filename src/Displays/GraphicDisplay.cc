#include "GraphicDisplay.h"
#include "window.h"
#include <string>
#include <iostream>

  // // Draws a rectangle
  // void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // // Draws a string
  // void drawString(int x, int y, std::string msg, int colour=Black);

  // // Draws a string
  // void drawBigString(int x, int y, std::string msg, int colour=Black);

constexpr int GRAPHIC_DISPLAY_WIDTH = 500;
constexpr int GRAPHIC_DISPLAY_HEIGHT = 500;

namespace qd {

  namespace {
    // enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};
    const std::map<Block::Type, int> blockTypeToColor = {
      { Block::Type::EMPTY, Xwindow::Black },
      { Block::Type::BLOCK_I, Xwindow::Red },
      { Block::Type::BLOCK_J, Xwindow::Green },
      { Block::Type::BLOCK_L, Xwindow::Blue },
      { Block::Type::BLOCK_O, Xwindow::Cyan },
      { Block::Type::BLOCK_S, Xwindow::Yellow },
      { Block::Type::BLOCK_T, Xwindow::Magenta },
      { Block::Type::BLOCK_Z, Xwindow::Orange },
      { Block::Type::BLOCK_HINT, Xwindow::Black },
      { Block::Type::BLOCK_SINGLE, Xwindow::Brown}
    };
  }

  GraphicDisplay::GraphicDisplay(const Board& b)
    : Display{b}, _window{GRAPHIC_DISPLAY_WIDTH, GRAPHIC_DISPLAY_HEIGHT} {
      outputDisplay();
    }

  void GraphicDisplay::outputDisplay() {
    // clear display
    _window.fillRectangle(0, 0, GRAPHIC_DISPLAY_WIDTH, GRAPHIC_DISPLAY_HEIGHT, Xwindow::White);

    auto levelString = "Level: " + (_level.hasValue() ? std::to_string(*_level) : "");
    auto scoreString = "Score: " + (_score.hasValue() ? std::to_string(*_score) : "");
    auto hiScoreString = "Hi Score: " + (_hiScore.hasValue() ? std::to_string(*_hiScore) : "");

    _window.drawString(10, 20, levelString);
    _window.drawString(10, 35, scoreString);
    _window.drawString(10, 50, hiScoreString);

    constexpr int BOARD_TOP = 70;
    constexpr int BOARD_LEFT = 10;
    constexpr int CELL_WIDTH = 20, CELL_HEIGHT = 20;

    auto positionForCell = [](int rowIndex, int colIndex) {
      struct Pos { int x, y; };
      return Pos{
        BOARD_LEFT + CELL_WIDTH * colIndex,
        BOARD_TOP + CELL_HEIGHT * rowIndex
      };
    };

    int currentRow = 0;
    std::for_each(
      _boardState.begin() + 3, _boardState.end(),

      [&](const auto& row) mutable {
        int currentCol = 0;
        std::for_each(
          row.begin(), row.end(),

          [&](const auto& blockType) mutable {
            int color = blockTypeToColor.at(blockType);
            auto pos = positionForCell(currentRow, currentCol);

            if (blockType == Block::Type::EMPTY) {
              // empty block gets an outline
              _window.drawRectangle(pos.x, pos.y, CELL_WIDTH, CELL_HEIGHT, color);
            } else {
              // actual block gets a filled color
              _window.fillRectangle(pos.x, pos.y, CELL_WIDTH, CELL_HEIGHT, color);
            }

            ++currentCol;
          }
        );
        ++currentRow;
      }
    );
  }

}

#include "GraphicDisplay.h"
#include "window.h"
#include <string>
#include <iostream>

constexpr int BOARD_TOP = 70;
constexpr int BOARD_LEFT = 10;
constexpr int CELL_WIDTH = 20, CELL_HEIGHT = 20;
constexpr int GRAPHIC_DISPLAY_WIDTH = qd::BOARD_WIDTH * CELL_WIDTH + BOARD_LEFT * 2;
constexpr int GRAPHIC_DISPLAY_HEIGHT = 500;
constexpr int NEXT_BLOCK_PREVIEW_TEXT_TOP = BOARD_TOP + CELL_HEIGHT * qd::BOARD_HEIGHT + 30;
constexpr int NEXT_BLOCK_PREVIEW_TOP = NEXT_BLOCK_PREVIEW_TEXT_TOP + 15;

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

    auto drawCell = [&](Block::Type blockType, auto pos) {
      int color = blockTypeToColor.at(blockType);
      if (blockType != Block::Type::EMPTY) {
        // actual block gets a filled color
        _window.fillRectangle(pos.x + 1, pos.y + 1, CELL_WIDTH - 2, CELL_HEIGHT - 2, color);
      }
      // each block gets an outline
      _window.drawRectangle(pos.x, pos.y, CELL_WIDTH, CELL_HEIGHT, color);
    };

    // draw Next Block: preview
    {
      auto positionForCell = [](int rowIndex, int colIndex) {
        struct Pos { int x, y; };
        return Pos{
          BOARD_LEFT + CELL_WIDTH * colIndex,
          NEXT_BLOCK_PREVIEW_TOP + CELL_HEIGHT * rowIndex
        };
      };
      _window.drawString(10, NEXT_BLOCK_PREVIEW_TEXT_TOP, "Next Block:");

      if (_nextBlockType.hasValue() && *_nextBlockType != Block::Type::EMPTY) {
        const Block* sampleBlock = sampleBlocks.at(*_nextBlockType);
        if (sampleBlock != nullptr) {
          Block::Type blockType = sampleBlock->type();
          for (Position p : *sampleBlock) {
            auto pos = positionForCell(p.row - 2, p.col);
            drawCell(blockType, pos);
          }
        }
      }
    }

    // draw board
    {
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

        [&](const auto& row) {
          int currentCol = 0;
          std::for_each(
            row.begin(), row.end(),

            [&](const auto& blockType) {
              auto pos = positionForCell(currentRow, currentCol);
              drawCell(blockType, pos);
              ++currentCol;
            }
          );
          ++currentRow;
        }
      );
    }
  }

}

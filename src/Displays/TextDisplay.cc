#include "TextDisplay.h"
#include <iostream>
#include <map>

#include "Utility.h"
#include "Block.h"

namespace qd {

  namespace {
    const std::map<Block::Type, char> blockTypeToChar = {
      { Block::Type::EMPTY, ' ' },
      { Block::Type::BLOCK_I, 'I' },
      { Block::Type::BLOCK_J, 'J' },
      { Block::Type::BLOCK_L, 'L' },
      { Block::Type::BLOCK_O, 'O' },
      { Block::Type::BLOCK_S, 'S' },
      { Block::Type::BLOCK_T, 'T' },
      { Block::Type::BLOCK_Z, 'Z' },
      { Block::Type::BLOCK_HINT, '?' },
      { Block::Type::BLOCK_SINGLE, '*'}
    };
  }

  void TextDisplay::outputDisplay() {
    const auto levelString = "Level: " + (_level.hasValue() ? std::to_string(*_level) : "");
    const auto scoreString = "Score: " + (_score.hasValue() ? std::to_string(*_score) : "");
    const auto hiScoreString = "Hi Score: " + (_hiScore.hasValue() ? std::to_string(*_hiScore) : "");
    const auto separatorString = "--------------------------------------------------------------------------------";
    const auto boardBorder = "-----------";

    std::cout << separatorString << std::endl;

    std::cout << levelString << std::endl;
    std::cout << scoreString << std::endl;
    std::cout << hiScoreString << std::endl;

    std::cout << boardBorder << std::endl;

    // the buffer representing the current line
    std::string lineBuffer(BOARD_WIDTH, ' ');

    std::transform(
      _boardState.begin() + 3, _boardState.end(),
      std::ostream_iterator<std::string>(std::cout, "\n"),
      [&lineBuffer](auto& row) -> const std::string& {
        std::transform(
          row.begin(), row.end(),
          lineBuffer.begin(),
          [](Block::Type type) -> char {
            return blockTypeToChar.at(type);
          }
        );
        return lineBuffer;
      }
    );

    std::cout << boardBorder << std::endl;

    if (_nextBlockType.hasValue() && *_nextBlockType != Block::Type::EMPTY) {
      const Block* sampleBlock = sampleBlocks.at(*_nextBlockType);
      std::array<std::string, 3> _nextBlockPreviewState = {{
        "Next:",
        std::string(BOARD_WIDTH, ' '),
        std::string(BOARD_WIDTH, ' '),
      }};
      if (sampleBlock != nullptr) {
        for (Position p : *sampleBlock) {
          _nextBlockPreviewState.at(p.row - 2 + 1).at(p.col) = blockTypeToChar.at(sampleBlock->type());
        }
      }

      std::copy(
        _nextBlockPreviewState.begin(),
        _nextBlockPreviewState.end(),
        std::ostream_iterator<std::string>(std::cout, "\n")
      );
    }

    std::cout << separatorString << std::endl;
  }

  void TextDisplay::onGameEnded() {
    std::cout << "GAME ENDED" << std::endl;
  }

}

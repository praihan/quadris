#include "Level1.h"

int qd::Level1::levelNumber() const {
  return 1;
}

qd::Block::Type qd::Level1::nextBlockType() const {
  return qd::Block::Type::EMPTY;
}

void qd::Level1::useSequence(const std::string& sequenceFileName) {

}

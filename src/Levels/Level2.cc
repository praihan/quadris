#include "Level2.h"

int qd::Level2::levelNumber() const {
  return 2;
}

qd::Block::Type qd::Level2::nextBlockType() const {
  return qd::Block::Type::EMPTY;
}

void qd::Level2::useSequence(const std::string& sequenceFileName) {

}

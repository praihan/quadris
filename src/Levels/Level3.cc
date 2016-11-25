#include "Level3.h"

int qd::Level3::levelNumber() const {
  return 3;
}

qd::Block::Type qd::Level3::nextBlockType() const {
  return qd::Block::Type::EMPTY;
}

void qd::Level3::useSequence(const std::string& sequenceFileName) {

}

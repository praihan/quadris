#include "Level4.h"

int qd::Level4::levelNumber() const {
  return 4;
}

qd::Block::Type qd::Level4::nextBlockType() const {
  return qd::Block::Type::EMPTY;
}

void qd::Level4::useSequence(const std::string& sequenceFileName) {

}

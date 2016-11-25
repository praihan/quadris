#include "Level0.h"

int qd::Level0::levelNumber() const {
  return 0;
}

qd::Block::Type qd::Level0::nextBlockType() const {
  return qd::Block::Type::EMPTY;
}

void qd::Level0::useSequence(const std::string& sequenceFileName) {

}

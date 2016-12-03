
int f() {
  int lowbound = activeBlockPtr->position->row + 3;
  int leftbound = activeBlockPtr->position->col;
  int rightbound = leftbound;
  Position leftpos = {lowbound, leftbound - 1};
  Position leftpos = {lowbound, leftbound + 1};

  while (_isCellInBound(pos) && _isCellOccupied(pos)) {
    

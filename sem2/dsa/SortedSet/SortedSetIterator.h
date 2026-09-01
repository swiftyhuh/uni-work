#pragma once
#include "SortedSet.h"

// DO NOT CHANGE THIS PART
class SortedSetIterator {
  friend class SortedSet;

private:
  const SortedSet &multime;
  SortedSetIterator(const SortedSet &m);

  TElem *elems;
  int nrElems;
  int current;

  void fillInOrder(BSTNode *node, int &pos);

public:
  void first();
  void next();
  TElem getCurrent();
  bool valid() const;
};

#pragma once
#include "FixedCapBiMap.h"
class FixedCapBiMapIterator {
  // DO NOT CHANGE THIS PART
  friend class FixedCapBiMap;

private:
  const FixedCapBiMap &map; // map holds the array
  int currentPos;

  FixedCapBiMapIterator(const FixedCapBiMap &m);
  // this->map = m;

public:
  void first();
  void next();
  TElem getCurrent();
  bool valid() const;
};

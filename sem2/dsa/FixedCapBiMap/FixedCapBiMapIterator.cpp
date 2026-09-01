#include "FixedCapBiMapIterator.h"
#include "FixedCapBiMap.h"
#include <exception>
using namespace std;

FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap &d) : map(d) {
  // map(d) is the same thing as this->map = d;
  this->currentPos = 0;
}
// BC = WC = TC = Theta(1)

void FixedCapBiMapIterator::first() { this->currentPos = 0; }
// BC = WC = TC = Theta(1)

void FixedCapBiMapIterator::next() {
  if (this->currentPos == this->map.mapSize) {
    throw exception();
  }
  this->currentPos++;
}
// BC = WC = TC = Theta(1)

TElem FixedCapBiMapIterator::getCurrent() {
  if (this->currentPos == this->map.mapSize) {
    throw exception();
  }
  return this->map.elements[this->currentPos];
}
// BC = WC = TC = Theta(1)

bool FixedCapBiMapIterator::valid() const {
  return this->currentPos < this->map.mapSize;
}
// BC = WC = TC = Theta(1)

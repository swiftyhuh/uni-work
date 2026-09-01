#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag &b) : bag(b) {
  this->currentPos = 0;
}
// BC = WC = TC = Theta(1)

TComp SortedBagIterator::getCurrent() {
  if (this->currentPos == this->bag.bagSize)
    throw std::exception();
  return this->bag.elements[this->currentPos];
}
// BC = WC = TC = Theta(1)

bool SortedBagIterator::valid() { return this->currentPos < this->bag.bagSize; }
// BC = WC = TC = Theta(1)

void SortedBagIterator::next() {
  if (this->currentPos == this->bag.bagSize)
    throw std::exception();
  this->currentPos++;
}
// BC = WC = TC = Theta(1)

void SortedBagIterator::first() { this->currentPos = 0; }
// BC = WC = TC = Theta(1)

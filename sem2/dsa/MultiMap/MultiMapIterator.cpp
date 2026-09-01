#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <exception>

MultiMapIterator::MultiMapIterator(const MultiMap &c) : col(c) {
  this->first();
}
// BC: Theta(1) - when the first occupied slot is found immediately
// WC: Theta(col.capacity) - when the table must be scanned to find the first occupied slot
// TC: O(col.capacity)

TElem MultiMapIterator::getCurrent() const {
  if (!this->valid())
    throw std::exception();
  return this->col.elems[this->current];
}
// BC = WC = TC = Theta(1)

bool MultiMapIterator::valid() const {
  return this->current < this->col.capacity;
}
// BC = WC = TC = Theta(1)

void MultiMapIterator::next() {
  if (!this->valid())
    throw std::exception();
  this->current++;
  while (this->current < this->col.capacity &&
         this->col.states[this->current] != 1)
    this->current++;
}
// BC: Theta(1) - when the next occupied slot is found immediately
// WC: Theta(col.capacity) - when many slots must be skipped
// TC: O(col.capacity)

void MultiMapIterator::first() {
  this->current = 0;
  while (this->current < this->col.capacity &&
         this->col.states[this->current] != 1)
    this->current++;
}
// BC: Theta(1) - when the first slot is occupied
// WC: Theta(col.capacity) - when many slots must be skipped
// TC: O(col.capacity)

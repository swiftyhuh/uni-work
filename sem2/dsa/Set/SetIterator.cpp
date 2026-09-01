#include "SetIterator.h"
#include "Set.h"
#include <exception>

SetIterator::SetIterator(const Set &m) : set(m) { this->current = m.head; }
// BC = WC = TC = Theta(1)

void SetIterator::first() { this->current = this->set.head; }
// BC = WC = TC = Theta(1)

void SetIterator::next() {
  if (!this->valid())
    throw std::exception();
  this->current = this->set.next[this->current];
}
// BC = WC = TC = Theta(1)

TElem SetIterator::getCurrent() {
  if (!this->valid())
    throw std::exception();
  return this->set.elems[this->current];
}
// BC = WC = TC = Theta(1)

bool SetIterator::valid() const { return this->current != -1; }
// BC = WC = TC = Theta(1)

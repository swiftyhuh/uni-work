#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <exception>

SMMIterator::SMMIterator(const SortedMultiMap &d) : map(d) {
  this->currentNode = d.head;
}

// BC = WC = TC = Theta(1) pt toate de mai jos

void SMMIterator::first() { this->currentNode = this->map.head; }

void SMMIterator::next() {
  if (this->currentNode == nullptr)
    throw std::exception();
  this->currentNode = this->currentNode->next;
}

bool SMMIterator::valid() const { return this->currentNode != nullptr; }

TElem SMMIterator::getCurrent() const {
  if (this->currentNode == nullptr)
    throw std::exception();
  return this->currentNode->element;
}

#include "SortedSetIterator.h"
#include "SortedSet.h"
#include <exception>

SortedSetIterator::SortedSetIterator(const SortedSet &m) : multime(m) {
  this->nrElems = m.size();
  this->current = 0;
  this->elems = nullptr;

  if (this->nrElems > 0) {
    this->elems = new TElem[this->nrElems];
    int pos = 0;
    this->fillInOrder(m.root, pos);
  }
}

// BC: Theta(1) - when the set is empty
// WC: Theta(n) - when all elements are copied in inorder
// TC: O(n)

void SortedSetIterator::fillInOrder(BSTNode *node, int &pos) {
  if (node != nullptr) {
    this->fillInOrder(node->left, pos);
    this->elems[pos] = node->info;
    pos++;
    this->fillInOrder(node->right, pos);
  }
}

// BC: Theta(1) - when the current subtree is empty
// WC: Theta(n) - when all nodes are visited
// TC: O(n)

void SortedSetIterator::first() { this->current = 0; }

// BC = WC = TC = Theta(1)

void SortedSetIterator::next() {
  if (!this->valid())
    throw std::exception();
  this->current++;
}

// BC = WC = TC = Theta(1)

TElem SortedSetIterator::getCurrent() {
  if (!this->valid())
    throw std::exception();
  return this->elems[this->current];
}

// BC = WC = TC = Theta(1)

bool SortedSetIterator::valid() const { return this->current < this->nrElems; }

// BC = WC = TC = Theta(1)

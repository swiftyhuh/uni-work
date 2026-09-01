#include "Set.h"
#include "SetIterator.h"

Set::Set() {
  this->capacity = 10;
  this->setSize = 0;
  this->head = -1;
  this->setSize = 0;
  this->elems = new TElem[this->capacity];
  this->next = new int[this->capacity];
  this->prev = new int[this->capacity];

  for (int i = 0; i < this->capacity - 1; i++) {
    this->next[i] = i + 1;
    this->prev[i] = -1;
  }

  this->next[this->capacity - 1] = -1;
  this->prev[this->capacity - 1] = -1;
  this->firstEmpty = 0;
}
// BC = WC = TC = Theta(capacity)

int Set::allocate() {
  if (this->firstEmpty == -1) {
    this->resize();
  }

  int newPos = this->firstEmpty;
  this->firstEmpty = this->next[this->firstEmpty];
  return newPos;
}
// BC = Theta(1) - if there is free space
// WC = Theta(capacity) - if resize is needed
// TC = O(capacity)

void Set::freePosition(int pos) {
  this->next[pos] = this->firstEmpty;
  this->prev[pos] = -1;
  this->firstEmpty = pos;
}
// BC = WC = TC = Theta(1)

void Set::resize() {
  int newCapacity = this->capacity * 2;

  TElem *newElems = new TElem[newCapacity];
  int *newNext = new int[newCapacity];
  int *newPrev = new int[newCapacity];

  for (int i = 0; i < this->capacity; i++) {
    newElems[i] = this->elems[i];
    newNext[i] = this->next[i];
    newPrev[i] = this->prev[i];
  }

  for (int i = this->capacity; i < newCapacity - 1; i++) {
    newNext[i] = i + 1;
    newPrev[i] = -1;
  }
  newNext[newCapacity - 1] = -1;
  newPrev[newCapacity - 1] = -1;

  this->firstEmpty = this->capacity;
  this->capacity = newCapacity;

  delete[] this->elems;
  delete[] this->next;
  delete[] this->prev;

  this->elems = newElems;
  this->next = newNext;
  this->prev = newPrev;
}
// BC = WC = TC = Theta(capacity)

bool Set::add(TElem elem) {
  if (this->search(elem))
    return false;

  int newPos = this->allocate();
  this->elems[newPos] = elem;
  this->next[newPos] = -1;
  this->prev[newPos] = this->tail;

  if (this->head == -1) {
    this->head = newPos;
    this->tail = newPos;
  } else {
    this->next[this->tail] = newPos;
    this->tail = newPos;
  }

  this->setSize++;
  return true;
}
// BC : Theta(1) - elemnt is in the first position
// WC ; Theta(setSize) - search whole set and resize
// TC : O(setsize)

bool Set::remove(TElem elem) {
  int current = this->head;

  while (current != -1 && this->elems[current] != elem)
    current = this->next[current];

  if (current == -1)
    return false;

  if (current == this->head && current == this->tail) {
    this->head = -1;
    this->tail = -1;
  } else if (current == this->head) {
    this->head = this->next[current];
    this->prev[this->head] = -1;
  } else if (current == this->tail) {
    this->tail = this->prev[current];
    this->next[this->tail] = -1;
  } else {
    this->next[this->prev[current]] = this->next[current];
    this->prev[this->next[current]] = this->prev[current];
  }

  this->freePosition(current);
  this->setSize--;
  return true;
}
// BC = Theta(1) - if elem is in the first node
// WC = Theta(setSize) - if elem is in the last node or does not exist
// TC: O(setSize)

bool Set::search(TElem elem) const {
  int current = this->head;
  while (current != -1) {
    if (this->elems[current] == elem)
      return true;
    current = this->next[current];
  }
  return false;
}
// BC = Theta(1) - if elem is in the first node
// WC = Theta(setSize) - if elem is in the last node or does not exist
// TC: O(setSize)

int Set::size() const { return this->setSize; }
// BC = WC = TC = Theta(1)

bool Set::isEmpty() const { return this->setSize == 0; }
// BC = WC = TC = Theta(1)

Set::~Set() {
  delete[] this->elems;
  delete[] this->next;
  delete[] this->prev;
}
// BC = WC = TC = Theta(1)

SetIterator Set::iterator() const { return SetIterator(*this); }
// BC = WC = TC = Theta(1)

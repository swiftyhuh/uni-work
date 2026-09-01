#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>

SortedBag::SortedBag(Relation r) {
  if (r == nullptr) // null pointer
    throw std::exception();
  this->rel = r;
  this->capacity = 10;
  this->bagSize = 0;
  this->elements = new TComp[this->capacity];
}
// BC = WC = TC = THETA(1)

void SortedBag::resize() {
  int newCapacity = this->capacity * 2;
  TComp *newArray = new TComp[newCapacity];

  for (int i = 0; i < this->bagSize; i++)
    newArray[i] = this->elements[i];

  delete[] this->elements;
  this->elements = newArray;
  this->capacity = newCapacity;
}
// BC = WC = TC = THETA(bagSize)

void SortedBag::add(TComp e) {
  if (this->bagSize == this->capacity)
    this->resize();

  int pos = 0;
  while (pos < this->bagSize && this->rel(this->elements[pos], e))
    pos++;

  for (int i = this->bagSize; i > pos; i--)
    this->elements[i] = this->elements[i - 1];

  this->elements[pos] = e;
  this->bagSize++;
}
// BC: Theta(1) - empty bag or insert on first position without resize
// WC: Theta(bagSize) - resize and/or full scan + shifts
// TC: O(bagSize)

bool SortedBag::remove(TComp e) {
  int pos = 0;
  while (pos < this->bagSize && this->elements[pos] != e) {
    pos++;
  }

  if (pos == this->bagSize) {
    return false;
  }

  for (int i = pos; i < this->bagSize - 1; i++) {
    this->elements[i] = this->elements[i + 1];
  }

  this->bagSize--;
  return true;
}
// BC: Theta(1) - element is on first position
// WC: Theta(bagSize) - element missing or near the end
// TC: O(bagSize)

bool SortedBag::search(TComp elem) const {
  int index = 0;
  while (index < this->bagSize) {
    if (this->elements[index] == elem) {
      return true;
    }
    index++;
  }
  return false;
}
// BC: Theta(1) - element found on first position
// WC: Theta(bagSize) - element missing or on last position
// TC: O(bagSize)

int SortedBag::nrOccurrences(TComp elem) const {
  int count = 0;
  for (int i = 0; i < this->bagSize; i++) {
    if (this->elements[i] == elem) {
      count++;
    }
  }
  return count;
}
// BC = WC = TC = Theta(bagSize)
int SortedBag::size() const { return this->bagSize; }
// BC = WC = TC = Theta(1)
//
bool SortedBag::isEmpty() const { return this->bagSize == 0; }
// BC = WC = TC = Theta(1)

SortedBagIterator SortedBag::iterator() const {
  return SortedBagIterator(*this);
}
// BC = WC = TC = Theta(1)

SortedBag::~SortedBag() { delete[] this->elements; }
// BC = WC = TC = Theta(1)

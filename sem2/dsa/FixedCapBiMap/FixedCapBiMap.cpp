#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>

FixedCapBiMap::FixedCapBiMap(int capacity) {
  if (capacity <= 0) {
    throw exception();
  }
  this->capacity = capacity;
  this->mapSize = 0;
  this->elements = new TElem[capacity]; // new array of TElem (new = we do
                                        // dynamic allocation)
}
// BC: Theta(1), WC: Theta(1), TC: Theta(1)

FixedCapBiMap::~FixedCapBiMap() {
  // we have to free the memory allowed using "new";
  delete[] this->elements;
}
// BC = WC = TC = Theta

bool FixedCapBiMap::add(TKey c, TValue v) {
  if (this->mapSize == this->capacity) {
    throw exception();
  }
  int count = 0;
  int index = 0; // we do the while loop so we can stop the moment we already
                 // find 2 occurences of the key
  while (count < 2 && index < this->mapSize) { // elements its a array of pairs
    if (this->elements[index].first == c) {
      count++;
    }
    index++;
  }
  if (count == 2) { // the key its in map twice
    return false;
  }
  this->elements[this->mapSize].first = c;  // we add in the last pos the Key
  this->elements[this->mapSize].second = v; // same with value
  this->mapSize++; // increasing because we added a element
  return true;
}
// BC: Theta(1) - when the first two keys from the map are equal to c
// WC: Theta(mapSIze) - when they key c appears only once or zero times in the
// map TC: O(mapSize)

ValuePair FixedCapBiMap::search(TKey c) const {
  ValuePair result;
  result.first = NULL_TVALUE;
  result.second = NULL_TVALUE;
  int nrfound = 0;
  int index = 0;
  while (nrfound < 2 && index < this->mapSize) {
    if (this->elements[index].first == c) {
      if (nrfound == 0) {
        result.first = this->elements[index].second;
        nrfound++;
      } else {
        result.second = this->elements[index].second;
        nrfound++;
      }
    }
    index++;
  }
  return result;
}
// BC: Theta(1) - when the first two keys from the map are equal to c
// WC: Theta(mapSIze) - when they key c appears only once or zero times in the
// map TC: O(mapSize)

bool FixedCapBiMap::remove(TKey c, TValue v) {
  int index = 0;
  while (index < this->mapSize) {
    if (this->elements[index].first == c && this->elements[index].second == v) {
      this->elements[index] = this->elements[this->mapSize - 1];
      this->mapSize--; // if the pair its in the last pos, the override
      // going to be done, but when we decreass mapsize, we don t count the
      // last element.
      return true;
    }
    index++;
  }
  return false;
}
// BC: Theta(1) - when the pair we want to remove is on the first position
// WC: Theta(mapSize) - when the pair is not in the array or it is on the last
// position TC: O(mapSize)

int FixedCapBiMap::size() const { return this->mapSize; }
// BC = WC = TC = Theta(1)

bool FixedCapBiMap::isEmpty() const { return this->mapSize == 0; }
// BC = WC = TC = Theta(1)

bool FixedCapBiMap::isFull() const { return this->mapSize == this->capacity; }
// BC = WC = TC = Theta(1)

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
  return FixedCapBiMapIterator(*this);
}
// BC = WC = TC = Theta(1)

#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

MultiMap::MultiMap() {
  this->capacity = 10;
  this->maxAlpha = 0.45;
  this->pairCount = 0;

  this->elems = new TElem[this->capacity];
  this->states = new int[this->capacity];

  for (int i = 0; i < this->capacity; i++) {
    this->states[i] = 0;
  }
}
// BC = WC = TC = Theta(capacity)

bool isPrime(int n) {
  if (n < 2)
    return false;
  for (int i = 2; i * i <= n; i++)
    if (n % i == 0)
      return false;
  return true;
}
// BC = Theta(1) - when n is divisible by 2
// WC = Theta(sqrt(n)) - when n is prime or has a large divisor
// TC = O(sqrt(n))

int nextPrime(int n) {
  while (!isPrime(n))
    n++;
  return n;
}
// BC = Theta(sqrt(n)) - when n is already prime
// WC = Theta(n * sqrt(n)) - when several consecutive numbers are checked
// TC = O(n * sqrt(n))

int MultiMap::probe(TKey c, int i) const {
  int slot = c % this->capacity;

  if (slot < 0)
    slot = slot + this->capacity;

  return (slot + i * i) % this->capacity;
}
// BC = WC = TC = Theta(1)

void MultiMap::resizeAndRehash() {
  TElem *oldElems = this->elems;
  int *oldStates = this->states;
  int oldCapacity = this->capacity;

  this->capacity = nextPrime(capacity * 2);
  this->elems = new TElem[this->capacity];
  this->states = new int[this->capacity];

  for (int i = 0; i < this->capacity; i++)
    this->states[i] = 0;

  this->pairCount = 0;

  for (int i = 0; i < oldCapacity; i++)
    if (oldStates[i] == 1)
      this->add(oldElems[i].first, oldElems[i].second);

  delete[] oldElems;
  delete[] oldStates;
}
// BC = WC = TC = Theta(capacity)

void MultiMap::add(TKey c, TValue v) {
  double newAlpha = (double)(this->pairCount + 1) / this->capacity;
  if (newAlpha > this->maxAlpha)
    this->resizeAndRehash();

  int firstDeleted = -1;

  for (int i = 0; i < this->capacity; i++) {
    int pos = this->probe(c, i);

    if (this->states[pos] == -1 && firstDeleted == -1)
      firstDeleted = pos;

    if (this->states[pos] == 0) {
      if (firstDeleted != -1)
        pos = firstDeleted;

      this->elems[pos].first = c;
      this->elems[pos].second = v;
      this->states[pos] = 1;
      this->pairCount++;
      return;
    }
  }

  if (firstDeleted != -1) {
    this->elems[firstDeleted].first = c;
    this->elems[firstDeleted].second = v;
    this->states[firstDeleted] = 1;
    this->pairCount++;
  }
}
// BC: Theta(1) - when the first probed slot is free and no resize is needed
// WC: Theta(capacity) - when probing is long and resize and rehash are needed
// TC: O(capacity)

bool MultiMap::remove(TKey c, TValue v) {
  for (int i = 0; i < this->capacity; i++) {
    int pos = this->probe(c, i);

    if (this->states[pos] == 0)
      return false;

    if (this->states[pos] == 1 && this->elems[pos].first == c &&
        this->elems[pos].second == v) {
      this->states[pos] = -1;
      this->pairCount--;
      return true;
    }
  }
  return false;
}
// BC: Theta(1) - when the pair is found on the first probed position
// WC: Theta(capacity) - when the pair is not found or is found after many
// probes TC: O(capacity)

vector<TValue> MultiMap::search(TKey c) const {
  vector<TValue> values;
  for (int i = 0; i < this->capacity; i++) {
    int pos = this->probe(c, i);

    if (this->states[pos] == 0)
      return values;

    if (this->states[pos] == 1 && this->elems[pos].first == c)
      values.push_back(this->elems[pos].second);
  }
  return values;
}
// BC: Theta(1) - when the key is found on the first probed position
// WC: Theta(capacity) - when many positions must be probed
// TC: O(capacity)

int MultiMap::size() const { return this->pairCount; }
// BC = WC = TC = Theta(1)

bool MultiMap::isEmpty() const { return this->pairCount == 0; }
// BC = WC = TC = Theta(1)

MultiMapIterator MultiMap::iterator() const { return MultiMapIterator(*this); }
// BC: Theta(1) - when the first occupied slot is found immediately
// WC: Theta(capacity) - when the iterator constructor scans many slots
// TC: O(capacity)

MultiMap::~MultiMap() {
  delete[] this->elems;
  delete[] this->states;
}
// BC = WC = TC = Theta(1)

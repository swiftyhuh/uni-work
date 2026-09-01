#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <cstddef>
#include <exception>
#include <iostream>
#include <vector>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
  this->head = nullptr;
  this->tail = nullptr;
  this->mapSize = 0;
  this->rel = r;
}
// BC = WC = TC = Theta(1)
void SortedMultiMap::add(TKey c, TValue v) {
  DLLNode *newNode = new DLLNode;
  newNode->element.first = c;
  newNode->element.second = v;
  newNode->prev = nullptr;
  newNode->next = nullptr;

  if (this->head == nullptr) {
    this->head = newNode;
    this->tail = newNode;
  } else if (this->rel(c, this->head->element.first)) {
    newNode->next = this->head;
    this->head->prev = newNode;
    this->head = newNode;
  } else {
    DLLNode *currentNode = this->head;
    while (currentNode->next != nullptr &&
           this->rel(currentNode->next->element.first, c))
      currentNode = currentNode->next;

    newNode->next = currentNode->next;
    newNode->prev = currentNode;
    if (currentNode->next != nullptr) // neighbors on the right
      currentNode->next->prev =
          newNode; // the old next node points back to the new node
    else
      this->tail = newNode;
    currentNode->next = newNode;
  }
  this->mapSize++;
}
// BC: Theta(1) - empty list or insert before the head
// WC: Theta(mapSIze) - insert near the end
// TC: O(mapSize)

vector<TValue> SortedMultiMap::search(TKey c) const {
  vector<TValue> values;
  DLLNode *currentNode = this->head;

  while (currentNode != nullptr) {
    if (currentNode->element.first == c)
      values.push_back(currentNode->element.second);
    currentNode = currentNode->next;
  }
  return values;
}
// BC: Theta(1) - empty map
// WC: Theta(mapSIze) - key appears at the end or does not appear
// TC: O(mapSIze)

bool SortedMultiMap::remove(TKey c, TValue v) {
  DLLNode *currentNode = this->head;
  while (currentNode != nullptr) {
    if (currentNode->element.first == c && currentNode->element.second == v) {
      if (currentNode == this->head && currentNode == this->tail) {
        this->head = nullptr;
        this->tail = nullptr;
      } else if (currentNode == this->head) {
        this->head = this->head->next;
        this->head->prev = nullptr;
      } else if (currentNode == this->tail) {
        this->tail = this->tail->prev;
        this->tail->next = nullptr;
      } else {
        currentNode->prev->next = currentNode->next;
        currentNode->next->prev = currentNode->prev;
      }
      delete currentNode;
      this->mapSize--;
      return true;
    }
    currentNode = currentNode->next;
  }
  return false;
}
// BC: Theta(1) - pair is in the first node
// WC: Theta(mapSIze) - pair is in the last node or deos not exist
// TC: O(mapSize)

int SortedMultiMap::size() const { return this->mapSize; }
// BC = WC = TC = Theta(1)

bool SortedMultiMap::isEmpty() const { return this->mapSize == 0; }
// BC = WC = TC = Theta(1)

SMMIterator SortedMultiMap::iterator() const { return SMMIterator(*this); }
// BC = WC = TC = Theta(1)

SortedMultiMap::~SortedMultiMap() {
  DLLNode *currentNode = this->head;
  while (currentNode != nullptr) {
    DLLNode *nextNode = currentNode->next;
    delete currentNode;
    currentNode = nextNode;
  }
}
// BC = WC = TC = Theta(mapSize)

#pragma once
// DO NOT INCLUDE SETITERATOR

// DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TELEM -11111
class SortedSetIterator;

// one tree node, info value stored
struct BSTNode {
  TElem info;
  BSTNode *left;
  BSTNode *right;
};

class SortedSet {
  friend class SortedSetIterator;

private:
  BSTNode *root;
  int setSize;
  Relation rel;

  BSTNode *addRec(BSTNode *node, TComp elem, bool &added);
  BSTNode *removeRec(BSTNode *node, TComp elem, bool &removed);
  bool searchRec(BSTNode *node, TComp elem) const;
  BSTNode *minimum(BSTNode *node) const;
  void destroyRec(BSTNode *node);

public:
  // constructor
  SortedSet(Relation r);

  // adds an element to the sorted set
  // if the element was added, the operation returns true, otherwise (if the
  // element was already in the set) it returns false
  bool add(TComp e);

  // removes an element from the sorted set
  // if the element was removed, it returns true, otherwise false
  bool remove(TComp e);

  // checks if an element is in the sorted set
  bool search(TElem elem) const;

  // returns the number of elements from the sorted set
  int size() const;

  // checks if the sorted set is empty
  bool isEmpty() const;

  // returns an iterator for the sorted set
  SortedSetIterator iterator() const;

  // destructor
  ~SortedSet();
};

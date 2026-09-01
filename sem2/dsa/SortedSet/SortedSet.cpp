#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
  this->root = nullptr;
  this->setSize = 0;
  this->rel = r;
}
// BC = WC = TC = Theta(1)

BSTNode *SortedSet::addRec(BSTNode *node, TComp elem, bool &added) {
  if (node == nullptr) {
    added = true;
    BSTNode *newNode = new BSTNode;
    newNode->info = elem;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
  }

  if (node->info == elem) {
    added = false;
    return node;
  }

  if (this->rel(elem, node->info)) {
    node->left = addRec(node->left, elem, added);
  } else {
    node->right = addRec(node->right, elem, added);
  }
  return node;
}

// BC: Theta(1) - when the element is found at the current node
// WC: Theta(h) - when we go down to a leaf, h = tree height
// TC: O(log h)

bool SortedSet::add(TComp elem) {
  bool added = false;
  this->root = addRec(this->root, elem, added);
  if (added) {
    this->setSize++;
  }
  return added;
}

// BC: Theta(1) - when the element is found immediately
// WC: Theta(h) - when we go down to a leaf, h = tree height
// TC: O(log h)

BSTNode *SortedSet::removeRec(BSTNode *node, TComp elem, bool &removed) {
  if (node == nullptr) {
    removed = false;
    return nullptr;
  }

  if (node->info == elem) {
    removed = true;

    if (node->left == nullptr) {
      BSTNode *rightChild = node->right;
      delete node;
      return rightChild;
    }

    if (node->right == nullptr) {
      BSTNode *leftChild = node->left;
      delete node;
      return leftChild;
    }

    BSTNode *successor = minimum(node->right);
    node->info = successor->info;
    bool removedd = false;
    node->right = removeRec(node->right, successor->info, removedd);
    return node;
  }

  if (this->rel(elem, node->info)) {
    node->left = removeRec(node->left, elem, removed);
  } else {
    node->right = removeRec(node->right, elem, removed);
  }
  return node;
}
// BC: Theta(1) - when the element is found at the current node
// WC: Theta(h) - when we go down to a leaf, h = tree height
// TC: O(log h)

bool SortedSet::remove(TComp elem) {
  bool removed = false;
  this->root = removeRec(this->root, elem, removed);
  if (removed)
    this->setSize--;
  return removed;
}
// BC: Theta(1) - when the element is removed immediately
// WC: Theta(h) - when we go down to a leaf, h = tree height
// TC: O(log h)

bool SortedSet::searchRec(BSTNode *node, TComp elem) const {
  if (node == nullptr) {
    return false;
  }
  if (node->info == elem) {
    return true;
  }
  if (this->rel(elem, node->info)) {
    return searchRec(node->left, elem);
  }
  return searchRec(node->right, elem);
}

// BC: Theta(1) - when the element is at the current node
// WC: Theta(h) - when we go down to a leaf, h = tree height
// TC: O(log h)

bool SortedSet::search(TComp elem) const { return searchRec(this->root, elem); }

// BC: Theta(1) - when the element is found immediately
// WC: Theta(h) - when we go down to a leaf, h = tree height
// TC: O(log h)

BSTNode *SortedSet::minimum(BSTNode *node) const {
  BSTNode *current = node;
  while (current != nullptr && current->left != nullptr) {
    current = current->left;
  }
  return current;
}

// BC: Theta(1) - when the node has no left child
// WC: Theta(h) - when we go to the leftmost node, h = tree height
// TC: O(log h)

int SortedSet::size() const { return this->setSize; }

// BC = WC = TC = Theta(1)

bool SortedSet::isEmpty() const { return this->setSize == 0; }

// BC = WC = TC = Theta(1)

SortedSetIterator SortedSet::iterator() const {
  return SortedSetIterator(*this);
}

// BC = WC = TC = Theta(1)

void SortedSet::destroyRec(BSTNode *node) {
  if (node != nullptr) {
    destroyRec(node->left);
    destroyRec(node->right);
    delete node;
  }
}

// BC: Theta(1) - when the tree is empty
// WC: Theta(n) - when all nodes are visited and deleted
// TC: O(n)

SortedSet::~SortedSet() { destroyRec(this->root); }

// BC: Theta(1) - when the tree is empty
// WC: Theta(n) - when all nodes are deleted
// TC: O(n)

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <iostream>

template <typename Comparable> class BinarySearchTree {
public:
  BinarySearchTree() = default;
  BinarySearchTree(const BinarySearchTree &other);
  BinarySearchTree(BinarySearchTree &&other);
  ~BinarySearchTree();

  const Comparable &findMin() const;
  const Comparable &findMax() const;
  bool contains(const Comparable &x) const;
  bool isEmpty() const;
  void printTree(std::ostream &out = std::cout) const;
  void makeEmpty();

  /**
   * Insert x into the tree; duplicates are ignored.
   */
  void insert(const Comparable &x);
  void insert(Comparable &&x);

  void remove(const Comparable &x);
  BinarySearchTree &operator=(const BinarySearchTree &rhs);
  BinarySearchTree &operator=(BinarySearchTree &&rhs);

private:
  struct BinaryNode {
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
        : element{theElement}, left{lt}, right{rt} {}
    BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
        : element{std::move(theElement)}, left{lt}, right{rt} {}
  };

  BinaryNode *root = nullptr;
  void insert(const Comparable &x, BinaryNode *&t);
  void insert(Comparable &&x, BinaryNode *&t);
  void remove(const Comparable &x, BinaryNode *&t);

  /**
   * Internal method to find the smallest item in a subtree t.
   * Return node containing the smallest item.
   */
  BinaryNode *findMin(BinaryNode *t) const;

  /**
   * Internal method to find the largest item in a subtree t.
   * Return node containing the largest item.
   */
  BinaryNode *findMax(BinaryNode *t) const;

  bool contains(const Comparable &x, BinaryNode *t) const;
  void makeEmpty(BinaryNode *&t);
  void printTree(BinaryNode *t, std::ostream &out) const;
  BinaryNode *clone(BinaryNode *t) const;
};

template <typename Comparable>
const Comparable &BinarySearchTree<Comparable>::findMin() const {
  return findMin(root)->element;
}

template <typename Comparable>
const Comparable &BinarySearchTree<Comparable>::findMax() const {
  return findMax(root)->element;
}

// recursive implementation of findMin
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *
BinarySearchTree<Comparable>::findMin(BinaryNode *t) const {
  if (!t) {
    return nullptr;
  }

  if (!t->left) {
    return t;
  }

  return findMin(t->left);
}

// non-recursive implementation of findMax
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *
BinarySearchTree<Comparable>::findMax(BinaryNode *t) const {
  if (t != nullptr) {
    while (t->right) {
      t = t->right;
    }
  }
  return t;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x) {
  insert(x, root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x, BinaryNode *&t) {
  if (!t) {
    t = new BinaryNode{x, nullptr, nullptr};
  } else if (x < t->element) {
    insert(x, t->left);
  } else if (x > t->element) {
    insert(x, t->right);
  }

  // ignore dupliactes (x == t->element)
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable &&x) {
  insert(x, root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable &&x, BinaryNode *&t) {
  if (!t)
    t = new BinaryNode{std::move(x), nullptr, nullptr};
  else if (x < t->element) {
    insert(std::move(x), t->left);
  } else if (t->element < x) {
    insert(std::move(x), t->right);
  }

  // ignore dupliactes (x == t->element)
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &x) const {
  return contains(x, root);
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &x,
                                            BinaryNode *t) const {
  if (!t) {
    return false;
  }

  if (x < t->element) {
    return contains(x, t->left);
  }

  if (x > t->element) {
    return contains(x, t->right);
  }

  return true; // Match
}

template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree() {
  makeEmpty();
}

template <typename Comparable> void BinarySearchTree<Comparable>::makeEmpty() {
  makeEmpty(root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode *&t) {
  if (t != nullptr) {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
    t = nullptr;
  }
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const {
  return root == nullptr;
}

#endif

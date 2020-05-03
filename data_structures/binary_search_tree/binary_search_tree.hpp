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
  BinaryNode *findMin(BinaryNode *t) const;
  BinaryNode *findMax(BinaryNode *t) const;
  bool contains(const Comparable &x, BinaryNode *t) const;
  void makeEmpty(BinaryNode *&t);
  void printTree(BinaryNode *t, std::ostream &out) const;
  BinaryNode *clone(BinaryNode *t) const;
};

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

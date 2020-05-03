#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <fstream>
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
  void print(std::ostream &out = std::cout) const;
  void printDot(std::string fileName = "bin_tree.dot") const;
  void makeEmpty();

  size_t size() const;

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
  size_t size(BinaryNode *t) const;
  void print(BinaryNode *t, std::ostream &out) const;
  void printDot(BinaryNode *t, std::ostream &out) const;
  BinaryNode *clone(BinaryNode *t) const;
};

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree &other) {
  root = clone(other.root);
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *
BinarySearchTree<Comparable>::clone(BinaryNode *t) const {
  if (!t) {
    return nullptr;
  }

  return new BinaryNode{t->element, clone(t->left), clone(t->right)};
}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree &&other) {
  // 'steal'
  this->root = other.root;
  other.root = nullptr;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printDot(std::string fileName) const {
  std::ofstream ofs{fileName};
  ofs << "digraph BST {\n";

  if (size() == 1) {
    ofs << root->element << ";\n";
  }

  printDot(root, ofs);

  ofs << "}";
  ofs.close();
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printDot(BinaryNode *t,
                                            std::ostream &out) const {
  if (!t) {
    return;
  }

  if (t->left) {
    out << '\t' << t->element << " -> " << t->left->element << ";\n";
    printDot(t->left, out);
  }

  if (t->right) {
    out << '\t' << t->element << " -> " << t->right->element << ";\n";
    printDot(t->right, out);
  }
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x) {
  remove(x, root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x, BinaryNode *&t) {
  if (!t) {
    return;
  }

  if (x < t->element) {
    remove(x, t->left);
  } else if (x > t->element) {
    remove(x, t->right);
  } else if (t->left && t->right) {          // has two children
    t->element = findMin(t->right)->element; // keeps the BST property
    remove(t->element, t->right); // smallest element cannot have a left child,
                                  // hence this second removal is an easy one
  } else {
    BinaryNode *oldNode = t;
    t = (t->left != nullptr) ? t->left : t->right;
    delete oldNode;
  }
}

template <typename Comparable>
size_t BinarySearchTree<Comparable>::size() const {
  return size(root);
}

template <typename Comparable>
size_t BinarySearchTree<Comparable>::size(BinaryNode *t) const {
  if (!t) {
    return 0;
  }

  return 1 + size(t->left) + size(t->right);
}

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

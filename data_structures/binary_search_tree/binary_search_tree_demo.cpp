#include "binary_search_tree.hpp"

int main() {
  BinarySearchTree<int> bst;
  bst.insert(10);
  bst.insert(8);
  bst.insert(15);
  bst.insert(6);
  bst.insert(9);
  bst.insert(18);
  bst.insert(13);
  bst.printDot();
  return 0;
}

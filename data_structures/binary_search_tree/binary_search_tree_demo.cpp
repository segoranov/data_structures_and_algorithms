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

  bst.printDot("bst_tree_for_graphviz_visualisation.dot");

  std::cout << "Tree size: " << bst.size() << std::endl;

  std::cout << "Largest element: " << bst.findMax() << std::endl;

  std::cout << "Smallest element: " << bst.findMin() << std::endl;

  std::cout << "The tree contains 69? -> "
            << (bst.contains(69) ? "TRUE" : "FALSE") << std::endl;

  std::cout << "The tree contains 18? -> "
            << (bst.contains(18) ? "TRUE" : "FALSE") << std::endl;

  std::cout << "Removing 18..." << std::endl;

  bst.remove(18);
  std::cout << "The tree contains 18? -> "
            << (bst.contains(18) ? "TRUE" : "FALSE") << std::endl;

  std::cout << "Largest element: " << bst.findMax() << std::endl;

  std::cout << "Tree size: " << bst.size() << std::endl;

  /*
  Output after executing this demo program:
  $ ./binary_search_tree_demo
        Tree size: 7
        Largest element: 18
        Smallest element: 6
        The tree contains 69? -> FALSE
        The tree contains 18? -> TRUE
        Removing 18...
        The tree contains 18? -> FALSE
        Largest element: 15
        Tree size: 6
  */

  return 0;
}

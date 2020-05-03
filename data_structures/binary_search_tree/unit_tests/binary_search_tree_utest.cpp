#include "binary_search_tree.hpp"
#include "catch.hpp"

TEST_CASE(
    "Binary search tree is empty on construction with default constructor") {
  BinarySearchTree<int> bst;
  REQUIRE(bst.isEmpty());
}

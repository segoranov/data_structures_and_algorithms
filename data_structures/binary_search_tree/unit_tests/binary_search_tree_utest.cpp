#include "binary_search_tree.hpp"
#include "catch.hpp"

TEST_CASE(
    "Binary search tree is empty on construction with default constructor") {
  BinarySearchTree<int> bst;
  REQUIRE(bst.isEmpty());
}

TEST_CASE("Add two elements to BST and then make the tree empty") {
  BinarySearchTree<int> bst;
  bst.insert(5);
  bst.insert(6);

  REQUIRE(!bst.isEmpty());
  REQUIRE(bst.contains(5));
  REQUIRE(bst.contains(6));
  REQUIRE(bst.findMax() == 6);
  REQUIRE(bst.findMin() == 5);

  bst.makeEmpty();
  REQUIRE(bst.isEmpty());
}

#include "binary_search_tree.hpp"
#include "catch.hpp"

TEST_CASE(
    "Binary search tree is empty on construction with default constructor") {
  BinarySearchTree<int> bst;
  REQUIRE(bst.isEmpty());
}

TEST_CASE("Insert two elements to BST and then make the tree empty") {
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

TEST_CASE("Insert many elements to BST and check size") {
  BinarySearchTree<int> bst;
  for (int i = 1; i <= 3'000; i++) {
    bst.insert(i);
    REQUIRE(bst.size() == i);
  }
}

TEST_CASE("Insert and remove elements to BST") {
  BinarySearchTree<int> bst;
  bst.insert(10);
  bst.insert(8);
  bst.insert(15);
  bst.insert(6);
  bst.insert(9);
  bst.insert(18);
  bst.insert(13);

  size_t expectedSize = 7;
  REQUIRE(bst.size() == expectedSize);
  REQUIRE(bst.findMax() == 18);
  REQUIRE(bst.findMin() == 6);

  for (int elem : {10, 15, 9, 13, 8, 6, 18}) {
    REQUIRE(bst.contains(elem));
    bst.remove(elem);
    expectedSize--;
    REQUIRE(!bst.contains(elem));
    REQUIRE(bst.size() == expectedSize);
  }

  REQUIRE(bst.isEmpty());
}

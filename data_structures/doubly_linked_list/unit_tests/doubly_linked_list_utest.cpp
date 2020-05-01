#include "catch.hpp"
#include "doubly_linked_list.h"

TEST_CASE(
    "Doubly linked list is empty on construction with default constructor") {
  DoublyLinkedList<int> list;
  REQUIRE(list.empty());
  REQUIRE(list.size() == 0);
}

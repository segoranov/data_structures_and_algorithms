#include "catch.hpp"
#include "doubly_linked_list.h"

TEST_CASE(
    "Doubly linked list is empty on construction with default constructor") {
  DoublyLinkedList<int> list;
  REQUIRE(list.empty());
  REQUIRE(list.size() == 0);
}

TEST_CASE("Push back one element") {
  DoublyLinkedList<int> list;
  list.push_back(1);
  REQUIRE(list.back() == 1);
  REQUIRE(!list.empty());
  REQUIRE(list.size() == 1);
}

TEST_CASE("Push back many elements") {
  DoublyLinkedList<int> list;
  for (int i = 1; i <= 1000; i++) {
    list.push_back(i);
    REQUIRE(list.size() == i);
    REQUIRE(list.back() == i);
  }

  list.back() = 3999;
  REQUIRE(list.back() == 3999);
  REQUIRE(list.size() == 1000);
}

TEST_CASE("Push back and then pop back many elements") {
  DoublyLinkedList<int> list;
  for (int i = 1; i <= 1000; i++) {
    list.push_back(i);
  }

  for (int i = 1000; i >= 1; i--) {
    REQUIRE(list.back() == i);
    REQUIRE(list.size() == i);
    list.pop_back();
  }

  REQUIRE(list.empty());
}

TEST_CASE("Push front and then pop front many elements") {
  DoublyLinkedList<int> list;
  for (int i = 1; i <= 1000; i++) {
    list.push_front(i);
    REQUIRE(list.size() == i);
    REQUIRE(list.front() == i);
  }

  for (int i = 1000; i >= 1; i--) {
    REQUIRE(list.front() == i);
    REQUIRE(list.size() == i);
    list.pop_front();
  }

  REQUIRE(list.empty());

  for (int i = 1; i <= 1000; i++) {
    list.push_front(i);
    REQUIRE(list.size() == i);
    REQUIRE(list.front() == i);
  }

  for (int i = 1; i <= 1000; i++) {
    REQUIRE(list.back() == i);
    REQUIRE(list.size() == 1001 - i);
    list.pop_back();
  }

  REQUIRE(list.empty());
}

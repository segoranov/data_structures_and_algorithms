#include "catch.hpp"
#include "dynamic_array.h"

TEST_CASE("Dynamic array is empty and has no buffer on construction with "
          "default constructor") {
  DynamicArray arr;
  REQUIRE(arr.empty());
  REQUIRE(arr.capacity() == 0);
  REQUIRE(!arr.data());
}

TEST_CASE("Dynamic array has correct size when using size constructor") {
  DynamicArray arr{23};
  REQUIRE(!arr.empty());
  REQUIRE(arr.capacity() >= 23);
  REQUIRE(arr.size() == 23);
  REQUIRE(arr.data());
}

TEST_CASE("Dynamic array resizes itself properly when adding new elements") {
  DynamicArray arr;

  arr.push_back(3.0);

  REQUIRE(!arr.empty());
  REQUIRE(arr.capacity() == 1);
  REQUIRE(arr.size() == 1);

  arr.push_back(5.0);
  REQUIRE(!arr.empty());
  REQUIRE(arr.capacity() == 2);
  REQUIRE(arr.size() == 2);

  arr.push_back(7.0);
  REQUIRE(!arr.empty());
  REQUIRE(arr.capacity() == 4);
  REQUIRE(arr.size() == 3);

  arr.push_back(9.0);
  REQUIRE(!arr.empty());
  REQUIRE(arr.capacity() == 4);
  REQUIRE(arr.size() == 4);

  arr.push_back(11.0);
  REQUIRE(!arr.empty());
  REQUIRE(arr.capacity() == 8);
  REQUIRE(arr.size() == 5);
}

TEST_CASE("Dynamic array's element access functions work correctly") {
  DynamicArray arr;

  double val = 1.0;
  for (int i = 0; i < 30; i++) {
    arr.push_back(val);
    val += 1;
  }

  REQUIRE(arr.size() == 30);
  REQUIRE(arr.capacity() == 32);

  val = 1.0;
  for (int i = 0; i < arr.size(); i++) {
    REQUIRE(arr[i] == val);
    REQUIRE(arr.at(i) == val);
    val += 1.0;
  }
}

TEST_CASE("Dynamic array's element access function at() throws exception when "
          "index is out of bounds") {
  DynamicArray arr;
  for (int i = 0; i < 155; i++) {
    arr.push_back(69.0);
  }

  for (int i = 0; i < 155; i++) {
    REQUIRE_NOTHROW(arr.at(i));
  }

  REQUIRE_THROWS_AS(arr.at(155), std::out_of_range);
}

TEST_CASE("Dynamic array's clear() works properly") {
  DynamicArray arr;
  for (int i = 0; i < 155; i++) {
    arr.push_back(69.0);
  }

  REQUIRE(arr.size() == 155);
  auto capacity = arr.capacity();

  arr.clear();

  // array should be empty; size should be 0; capacity should be as before
  REQUIRE(arr.empty());
  REQUIRE(arr.size() == 0);
  REQUIRE(arr.capacity() == capacity);

  // should not be able to access any element
  for (int i = -300; i < 300; i++) {
    REQUIRE_THROWS_AS(arr.at(i), std::out_of_range);
  }
}

TEST_CASE("Comparators of dynamic arrays work correctly") {
  DynamicArray arr;
  for (int i = 0; i < 155; i++) {
    arr.push_back(69.0);
  }

  DynamicArray arr1;
  for (int i = 0; i < 155; i++) {
    arr1.push_back(69.0);
  }

  REQUIRE(arr1 == arr);

  DynamicArray arr2;
  for (int i = 0; i < 155; i++) {
    arr.push_back(static_cast<double>(i));
  }

  REQUIRE(arr2 != arr);
}

TEST_CASE(
    "Dynamic array's copy constructor and operator equals work properly") {
  DynamicArray arr;
  for (int i = 0; i < 155; i++) {
    arr.push_back(69.0);
  }

  DynamicArray arr_copy{arr};
  REQUIRE(arr_copy.data() != arr.data());
  REQUIRE(arr_copy == arr);

  DynamicArray arr_equals;
  arr_equals = arr;
  REQUIRE(arr_equals.data() != arr.data());
  REQUIRE(arr_equals.data() != arr_copy.data());
  REQUIRE(arr_equals == arr);
}

TEST_CASE("Pop back works correctly") {
  DynamicArray arr;
  for (int i = 0; i < 155; i++) {
    arr.push_back(69.0);
  }

  REQUIRE(arr.size() == 155);

  for (int i = 155; i > 0; i--) {
    REQUIRE(arr.size() == i);
    arr.pop_back();
  }

  // container should be empty now
  REQUIRE_THROWS_AS(arr.pop_back(), std::runtime_error);
}

#include "catch.hpp"
#include "deque.h"

TEST_CASE("Deque is empty and has no buffer on construction with "
          "default constructor") {
  Deque<double> deque;
  REQUIRE(deque.empty());
}

TEST_CASE("Deque has correct size when using size constructor") {
  Deque<double> deque{23};
  REQUIRE(!deque.empty());
  REQUIRE(deque.size() == 23);
}

TEST_CASE("Push back one element in deque") {
  Deque<double> deque;
  deque.push_back(23);
  REQUIRE(deque.back() == 23);
  REQUIRE(deque.front() == 23);
  REQUIRE(deque[0] == 23);
}

TEST_CASE("Push back many elements in deque") {
  Deque<double> deque;
  for (int i = 0; i < 20'000; i++) {
    deque.push_back(i);
    REQUIRE(deque.back() == i);
    REQUIRE(deque[i] == i);
    REQUIRE(deque.front() == 0);
    REQUIRE(deque[0] == 0);
  }
}

TEST_CASE("Push front one element in deque") {
  Deque<double> deque;
  deque.push_front(23);
  REQUIRE(deque.back() == 23);
  REQUIRE(deque.front() == 23);
  REQUIRE(deque[0] == 23);
}

TEST_CASE("Push front many elements in deque") {
  Deque<double> deque;
  for (int i = 0; i < 20'000; i++) {
    deque.push_front(i);
    REQUIRE(deque.back() == 0);
    REQUIRE(deque.front() == i);
    REQUIRE(deque[0] == i);
  }

  for (int desiredValue = 19'999, index = 0; desiredValue >= 0;
       desiredValue--, index++) {
    REQUIRE(deque[index] == desiredValue);
  }
}

TEST_CASE("Push back and push front two elements in deque") {
  Deque<double> deque;
  deque.push_back(0);
  deque.push_front(1);

  REQUIRE(deque[0] == 1);
  REQUIRE(deque[1] == 0);
}

TEST_CASE("Push back and push front four elements in deque") {
  Deque<double> deque;
  deque.push_back(3);
  deque.push_back(4);
  deque.push_front(2);
  deque.push_front(1);

  // deque should be {1, 2, 3, 4} now
  REQUIRE(deque[0] == 1);
  REQUIRE(deque[1] == 2);
  REQUIRE(deque[2] == 3);
  REQUIRE(deque[3] == 4);
}

TEST_CASE("Push back and push front many elements in deque") {
  Deque<double> deque;
  for (int i = 1; i <= 20'000; i++) {
    deque.push_front(i);
    deque.push_back(-i);
    REQUIRE(deque.back() == -i);
    REQUIRE(deque.front() == i);
  }

  REQUIRE(deque.size() == 40'000);

  long sum = 0;
  for (int i = 0; i < deque.size(); i++) {
    sum += deque[i];
  }

  REQUIRE(sum == 0);
}

TEST_CASE("Deque's front and back element access functions work correctly") {
  Deque<double> deque;

  double val_back = 1.0;
  double val_front = -1.0;
  for (int i = 0; i < 30; i++) {
    deque.push_back(val_back);
    deque.push_front(val_front);
    REQUIRE(deque.back() == val_back);
    REQUIRE(deque.front() == val_front);
    ++val_back;
    --val_front;
  }

  REQUIRE(deque.size() == 60);

  double val = -30;
  for (int i = 0; i < deque.size(); i++) {
    if (val == 0) {
      ++val;
    }
    REQUIRE(deque[i] == val);
    REQUIRE(deque.at(i) == val);
    ++val;
  }
}

TEST_CASE("Deque's element access function at() throws exception when "
          "index is out of bounds") {
  Deque<double> deque;
  for (int i = 0; i < 155; i++) {
    deque.push_back(69.0);
  }

  for (int i = 0; i < 155; i++) {
    REQUIRE_NOTHROW(deque.at(i));
  }

  REQUIRE_THROWS_AS(deque.at(155), std::out_of_range);
}

TEST_CASE("Deque's clear() works properly") {
  Deque<double> deque;
  for (int i = 0; i < 150; i++) {
    deque.push_front(i);
    deque.push_back(69.0);
  }

  REQUIRE(deque.size() == 300);

  deque.clear();

  // deque should be empty; size should be 0;
  REQUIRE(deque.empty());
  REQUIRE(deque.size() == 0);

  // should not be able to access any element
  for (int i = -300; i < 300; i++) {
    REQUIRE_THROWS_AS(deque.at(i), std::out_of_range);
  }

  // add elements again to check if it's ok.
  for (int i = 0; i < 150; i++) {
    deque.push_front(i);
    deque.push_back(69.0);
  }

  REQUIRE(deque.size() == 300);
  for (int i = 0; i < 150; i++) {
    REQUIRE_NOTHROW(deque[i]++);
  }
}

TEST_CASE("Comparators of deques work correctly") {
  Deque<double> deque;
  for (int i = 0; i < 155; i++) {
    deque.push_front(169.0);
    deque.push_back(69.0);
  }

  Deque<double> deque1;
  for (int i = 0; i < 155; i++) {
    deque1.push_front(169.0);
    deque1.push_back(69.0);
  }

  REQUIRE(deque1 == deque);

  Deque<double> deque2;
  for (int i = 0; i < 155; i++) {
    deque.push_back(static_cast<double>(i));
  }

  REQUIRE(deque2 != deque);
}

TEST_CASE("Deque's copy constructor and operator equals work properly") {
  Deque<double> deque;
  for (int i = 0; i < 10; i++) {
    deque.push_back(i);
  }

  Deque<double> deque_copy{deque};
  REQUIRE(deque_copy == deque);

  Deque<double> deque_equals;
  deque_equals = deque;

  REQUIRE(deque_equals == deque);
}

// TEST_CASE("Pop back works correctly") {
//   Deque<double> deque;
//   for (int i = 0; i < 155; i++) {
//     deque.push_back(69.0);
//   }

//   REQUIRE(deque.size() == 155);

//   for (int i = 155; i > 0; i--) {
//     REQUIRE(deque.size() == i);
//     deque.pop_back();
//   }

//   REQUIRE(deque.empty());
// }

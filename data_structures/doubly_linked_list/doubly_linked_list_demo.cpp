#include "doubly_linked_list.h"
#include <iostream>

template <typename T> void print(const DoublyLinkedList<T> &list) {
  for (const auto &elem : list) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main() {
  DoublyLinkedList<int> list;
  for (int i = 1; i <= 10; i++) {
    list.push_back(i);
  }

  print(list);

  int sum = 0;
  for (const auto &elem : list) {
    sum += elem;
  }

  std::cout << "Sum of elements: " << sum << '\n';

  std::cout << "Increasing all elements with 1\n";

  for (DoublyLinkedListIterator<int> it = list.begin(); it != list.end();
       ++it) {
    *it += 1;
  }

  for (auto constIt = list.cbegin(); constIt != list.cend(); constIt++) {
    std::cout << *constIt << ' ';
  }

  std::cout << '\n';

  return 0;
}

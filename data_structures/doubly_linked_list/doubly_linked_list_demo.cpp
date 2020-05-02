#include "doubly_linked_list.h"
#include <iostream>

// the reference is not const because const_iterator is
// not yet implemented
template <typename T> void print(DoublyLinkedList<T> &list) {
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

  std::cout << "Sum of elements: " << sum << std::endl;

  return 0;
}

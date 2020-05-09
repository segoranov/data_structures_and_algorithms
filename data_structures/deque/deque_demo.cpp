#include "deque.h"
#include <iostream>

template <typename T> void print(const Deque<T> &deque) {
  if (deque.empty()) {
    std::cout << "The deque is empty.\n";
    return;
  }

  std::cout << "Size: " << deque.size() << "; elements: ";

  for (int i = 0; i < deque.size(); i++) {
    std::cout << deque[i] << ' ';
  }

  std::cout << '\n';
}

int main() {
  Deque<double> deque;

  for (int i = 1; i <= 10; i++) {
    deque.push_back(static_cast<double>(i));
  }

  double sum = 0;
  for (int i = 0; i < deque.size(); i++) {
    sum += deque[i];
  }

  print(deque);
  std::cout << "Sum of deque elements is: " << sum << '\n';

  for (int i = 1; i <= 10; i++) {
    print(deque);
    deque.pop_back();
  }

  print(deque);
  deque.clear();
  print(deque);

  return 0;
}

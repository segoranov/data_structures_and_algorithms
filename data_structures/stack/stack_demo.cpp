#include "stack_dynamic_array.h"
#include <iostream>

int main() {
  StackDynamicArrayImpl<int> stack;
  std::cout << "Pusing elements from 1 to 10 in stack...\n";
  for (int i = 1; i <= 10; i++)
    stack.push(i);

  std::cout << "Size of stack is: " << stack.size() << '\n';

  std::cout << "Popping elements from stack one by one...\n";
  while (!stack.empty()) {
    std::cout << "Popping: " << stack.top() << '\n';
    stack.pop();
  }

  std::cout << "OK, stack is empty now.\n";

  return 0;
}

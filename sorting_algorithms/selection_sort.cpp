#include <algorithm>
#include <iostream>
#include <vector>

void selectionSort(std::vector<int> &input) {
  for (int i = 0; i < input.size() - 1; i++) {
    int min_id = i;
    for (int j = i + 1; j < input.size(); j++) {
      if (input[j] < input[min_id]) {
        min_id = j;
      }
    }
    std::swap(input[i], input[min_id]);
  }
}

void print(const std::vector<int> &vector, std::ostream &os = std::cout) {
  for (const auto &elem : vector) {
    os << elem << ' ';
  }
  os << std::endl;
}

/*
Compile:
g++ selection_sort.cpp -o selection_sort_demo -std=c++17

Run:
$> ./selection_sort_demo
Initially: 5 48 1 123 45 23 1 8 9 23 45 3 7 17 12
Sorted: 1 1 3 5 7 8 9 12 17 23 23 45 45 48 123
*/
int main() {
  std::vector numbers{5, 48, 1, 123, 45, 23, 1, 8, 9, 23, 45, 3, 7, 17, 12};
  std::cout << "Initially: ";
  print(numbers);
  selectionSort(numbers);
  std::cout << "Sorted: ";
  print(numbers);
}

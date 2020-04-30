#include <iostream>
#include <vector>

void insertionSort(std::vector<int> &input) {
  for (int j = 2; j < input.size(); j++) {
    int key = input[j];
    // insert input[j] into sorted sequence input[1 ... j-1]
    int i = j - 1;
    while (i >= 0 && input[i] > key) {
      input[i + 1] = input[i];
      i--;
    }
    input[i + 1] = key;
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
g++ insertion_sort.cpp -o insertion_sort_demo -std=c++17

Run:
$> ./insertion_sort_demo
Initially: 5 48 1 123 45 23 1 8 9 23 45 3 7 17 12
Sorted: 1 1 3 5 7 8 9 12 17 23 23 45 45 48 123
*/
int main() {
  std::vector numbers{5, 48, 1, 123, 45, 23, 1, 8, 9, 23, 45, 3, 7, 17, 12};
  std::cout << "Initially: ";
  print(numbers);
  insertionSort(numbers);
  std::cout << "Sorted: ";
  print(numbers);
}

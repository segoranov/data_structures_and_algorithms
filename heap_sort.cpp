#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int parent(int i) {
  if (i == 1 || i == 2)
    return 0;
  return std::floor((double)i / 2.0) - 1;
}

int left(int i) { return 2 * i + 1; }

int right(int i) { return 2 * i + 2; }

// maxHeapify lets the value at input[i] “float down” in the max-heap so
// that the subtree rooted at index i obeys the max-heap property.
void maxHeapify(std::vector<int> &input, int i, int heapSize) {
  auto l = left(i);
  auto r = right(i);
  int largest;

  if (l < heapSize && input[l] > input[i]) {
    largest = l;
  } else {
    largest = i;
  }

  if (r < heapSize && input[r] > input[largest]) {
    largest = r;
  }

  if (largest != i) {
    std::swap(input[largest], input[i]);
    maxHeapify(input, largest, heapSize);
  }
}

void buildMaxHeap(std::vector<int> &input) {
  const int firstLeafIndex = std::floor((double)input.size() / 2);
  for (int i = firstLeafIndex - 1; i >= 0; i--) {
    maxHeapify(input, i, input.size());
  }
}

void heapSort(std::vector<int> &input) {
  buildMaxHeap(input);
  int heapSize = input.size();
  for (int i = input.size() - 1; i >= 1; i--) {
    std::swap(input[0], input[i]);
    maxHeapify(input, 0, --heapSize);
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
g++ heap_sort.cpp -o heap_sort_demo -std=c++17

Run:
$> ./heap_sort_demo
Initially: 5 48 1 123 45 23 1 8 9 23 45 3 7 17 12
Sorted: 1 1 3 5 7 8 9 12 17 23 23 45 45 48 123
*/
int main() {
  std::vector numbers{5, 48, 1, 123, 45, 23, 1, 8, 9, 23, 45, 3, 7, 17, 12};
  std::cout << "Initially: ";
  print(numbers);
  heapSort(numbers);
  std::cout << "Sorted: ";
  print(numbers);
}

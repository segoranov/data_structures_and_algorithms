#include <algorithm>
#include <iostream>

int partition(int arr[], int start, int end) {
  // choose last element as pivot
  int pivot = arr[end];

  int lastSmallestThanPivotElementIndex = start - 1;

  for (int i = start; i < end; i++) {
    if (arr[i] <= pivot) {
      lastSmallestThanPivotElementIndex++;
      std::swap(arr[lastSmallestThanPivotElementIndex], arr[i]);
    }
  }

  int pivotIndex = lastSmallestThanPivotElementIndex + 1;
  std::swap(arr[pivotIndex], arr[end]);
  return pivotIndex;
}

void quicksort(int arr[], int start, int end) {
  if (start < end) {
    int partitionIndex = partition(arr, start, end);
    quicksort(arr, start, partitionIndex - 1);
    quicksort(arr, partitionIndex + 1, end);
  }
}

void print(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    std::cout << arr[i] << ' ';
  }
  std::cout << std::endl;
}

/*
Compile:
g++ quick_sort.cpp -o quick_sort_demo -std=c++17

Run:
$> ./quick_sort_demo
Initially: 5 48 1 123 45 23 1 8 9 23 45 3 7 17 12
Sorted: 1 1 3 5 7 8 9 12 17 23 23 45 45 48 123
*/
int main() {
  int arr[] = {5, 48, 1, 123, 45, 23, 1, 8, 9, 23, 45, 3, 7, 17, 12};
  std::cout << "Initially: ";
  print(arr, 15);
  quicksort(arr, 0, 14);
  std::cout << "Sorted: ";
  print(arr, 15);
}

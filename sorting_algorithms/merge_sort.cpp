#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> merge(const std::vector<int> &left_sorted,
                       const std::vector<int> &right_sorted);

void print(const std::vector<int> &vector, std::ostream &os = std::cout);

void mergeSort(std::vector<int> &input) {
  if (input.size() > 1) {
    // split input into two sub-arrays
    std::vector<int> left, right;
    int middle = input.size() / 2;

    for (int i = 0; i < middle; i++) {
      left.push_back(input[i]);
    }

    for (int i = middle; i < input.size(); i++) {
      right.push_back(input[i]);
    }

    mergeSort(left);
    mergeSort(right);
    input = merge(left, right);
  }
}

std::vector<int> merge(const std::vector<int> &left_sorted,
                       const std::vector<int> &right_sorted) {
  std::vector<int> merged_result;

  int li = 0, ri = 0;
  while (li < left_sorted.size() && ri < right_sorted.size()) {
    if (left_sorted[li] <= right_sorted[ri]) {
      merged_result.push_back(left_sorted[li++]);
    } else {
      merged_result.push_back(right_sorted[ri++]);
    }
  }

  if (li < left_sorted.size()) {
    for (; li < left_sorted.size(); li++) {
      merged_result.push_back(left_sorted[li]);
    }
  }

  if (ri < right_sorted.size()) {
    for (; ri < right_sorted.size(); ri++) {
      merged_result.push_back(right_sorted[ri]);
    }
  }

  return merged_result;
}

void print(const std::vector<int> &vector, std::ostream &os) {
  for (const auto &elem : vector) {
    os << elem << ' ';
  }
  os << std::endl;
}

/*
Compile:
g++ merge_sort.cpp -o merge_sort_demo -std=c++17

Run:
$> ./merge_sort_demo
Initially: 5 48 1 123 45 23 1 8 9 23 45 3 7 17 12
Sorted: 1 1 3 5 7 8 9 12 17 23 23 45 45 48 123
*/
int main() {
  std::vector numbers{5, 48, 1, 123, 45, 23, 1, 8, 9, 23, 45, 3, 7, 17, 12};
  std::cout << "Initially: ";
  print(numbers);
  mergeSort(numbers);
  std::cout << "Sorted: ";
  print(numbers);
}

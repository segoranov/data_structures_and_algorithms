#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

void longest_increasing_subsequence(const std::vector<int>& arr) {
  // v[i] = max size of subsequence ending in arr[i]
  std::vector<int> v(arr.size());

  std::vector<int> p(arr.size());  // p[i] = previous element of arr[i] in the
                                   // subsequence ending in arr[i]

  v[0] = 1;
  for (int i = 1; i < arr.size(); i++) {
    int maxLength = 1;
    int prev = i;
    for (int j = 1; j < i; j++) {
      if (arr[j] < arr[i]) {
        maxLength = std::max(maxLength, v[j] + 1);
        if (maxLength == v[j] + 1) prev = j;
      }
    }
    v[i] = maxLength;
    p[i] = prev;
  }

  int lastElemIndex = 0;
  int maxLength = 1;

  for (int i = 0; i < v.size(); i++) {
    if (v[i] > maxLength) {
      maxLength = v[i];
      lastElemIndex = i;
    }
  }

  std::cout << "Longest subsequence length: " << maxLength << '\n';

  // Use stack to reverse the order of printing :)
  std::stack<int> longestSubsequence;

  for (int i = 0; i < maxLength; i++) {
    longestSubsequence.push(arr[lastElemIndex]);
    lastElemIndex = p[lastElemIndex];
  }

  while (!longestSubsequence.empty()) {
    std::cout << longestSubsequence.top() << ' ';
    longestSubsequence.pop();
  }
  std::cout << '\n';
}

int main() {
  longest_increasing_subsequence({3, 4, -1, 0, 6, 2, 3});  // answer is -1 0 2 3
}

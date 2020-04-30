#include <ctime>
#include <iostream>

/*
Program to demonstrate the concept 'locality of reference'
https://en.wikipedia.org/wiki/Locality_of_reference

The program calculates the sum of all elements of large (in this case 40'000 x 40'000) matrix in two ways:
1. Row by row
2. Column by column

The second method is WAY slower than the first because of locality of reference
and how the matrix (represented by array) is layed out in memory.

The key idea is that when we access an array's element, the CPU fetches from RAM
to CACHE memory (which is a lot faster) not only that element, but others surrounding it.

When we traverse the array sequentially (corresponding to 'row by row'), the access to
most of the elements is way faster, because they are prefetched from RAM in CACHE. 
That is to say that access to most of the elements elicits 'cache hit'.
Thus the hardware works in our benefit.

When we traverse the array not sequentially (corresponding to 'column by column'), the access
to most of the elements is slower, i.e. causing 'cache miss', and the CPU has to fetch them from
RAM, because our program does not take advantage of the prefetched surrounding elements.
Thus the hardware works against us.

The below measurement is not 'correct' per se, because it uses time as a reference, and this
time can depend on millions of other things (like the OS, the number of processes running, and so on...),
but even so, we can observe the big difference in the two ways of traversal.

-------------

Results on my machine with 40'000 x 40'000 matrix:
$ ./locality_of_reference
Init...
Time taken for initialization: 6 seconds.
Start test with locality...
Result: 3200000000
Time taken with locality: 4 seconds.
Start test without locality...
Result: 3200000000
Time taken without locality: 58 seconds.

-------------

As you can tell, when the size of the matrix gets larger (more than 100 000 x
100 000), this difference becomes even more dramatic.
*/
int main() {
  const unsigned numRows = 40'000;
  const unsigned numCols = 40'000;

  int *arr = new int[numRows * numCols];

  std::time_t startOfInit = std::time(nullptr);

  std::cout << "Init...\n";
  // initialize all values with 2
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      arr[i * numRows + j] = 2;
    }
  }

  std::cout << "Time taken for initialization: "
            << std::time(nullptr) - startOfInit << " seconds.\n";

  // -----------------
  std::cout << "Start test with locality...\n";

  std::time_t startTestWithLocality = std::time(nullptr);
  unsigned long long sum = 0;
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      sum += arr[i * numCols + j];
    }
  }

  std::cout << "Result: " << sum << std::endl;
  std::cout << "Time taken with locality: "
            << std::time(nullptr) - startTestWithLocality << " seconds.\n";

  // -----------------

  std::cout << "Start test without locality...\n";
  sum = 0;
  std::time_t startTestWithoutLocality = std::time(nullptr);
  for (int i = 0; i < numCols; i++) {
    for (int j = 0; j < numRows; j++) {
      sum += arr[j * numRows + i];
    }
  }

  std::cout << "Result: " << sum << std::endl;
  std::cout << "Time taken without locality: "
            << std::time(nullptr) - startTestWithoutLocality << " seconds.\n";

  return 0;
}

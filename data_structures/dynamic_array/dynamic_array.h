#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>
#include <vector>

class DynamicArray {
public:
  DynamicArray();
  DynamicArray(size_t initialSize);
  DynamicArray(const DynamicArray &);
  DynamicArray &operator=(const DynamicArray &);

  void push_back(double value);
  void pop_back();

  /**
   * Checks if index is out of bounds and throws exception if it is
   * @throw std::out_of_range
   */
  double &at(size_t index);

  /**
   * Access element without checking if index is out of bounds
   */
  double &operator[](size_t index);

  /**
   * Returns number of elements in the array
   */
  size_t size() const;

  /**
   * Returns the size of the internal buffer.
   * Could be larger than the number of elemets in the array
   */

  size_t capacity() const;

  /**
   * Returns whether the array is empty of elements or not
   */
  bool empty() const;

  /**
   * Clears the array's content without modifying the internal buffer
   * After calling it, size() will return 0, but capacity() will remain
   * the same as before calling it
   */
  void clear() const;

private:
  double *m_arr;
  size_t m_currentSize;
  size_t m_currentCapacity;
};

#endif
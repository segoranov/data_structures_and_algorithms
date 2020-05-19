#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstddef>

class DynamicArray {
 public:
  DynamicArray() = default;
  DynamicArray(size_t initialSize);
  DynamicArray(const DynamicArray &);
  DynamicArray &operator=(const DynamicArray &);
  ~DynamicArray();

  /**
   * Appends the given element value to the end of the container.
   */
  void push_back(double value);

  /**
   * Removes the last element of the container.
   * Calling pop_back on an empty container throws exception.
   * @throw std::runtime_error
   */
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
  const double &operator[](size_t index) const;

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
   * Requests the container to reduce its capacity to fit its size.
   */
  void shrink_to_fit();

  /**
   * Returns whether the array is empty of elements or not
   */
  bool empty() const;

  /**
   * Clears the array's content without modifying the internal buffer
   * After calling it, size() will return 0, but capacity() will remain
   * the same as before calling it
   */
  void clear();

  /**
   * Returns a direct pointer to the memory array used internally by the dynamic
   * array to store its owned elements.
   */
  double *data() noexcept;

 private:
  double *m_arr = nullptr;
  size_t m_currentSize = 0;
  size_t m_currentCapacity = 0;
};

bool operator==(const DynamicArray &lhs, const DynamicArray &rhs);
bool operator!=(const DynamicArray &lhs, const DynamicArray &rhs);

#endif

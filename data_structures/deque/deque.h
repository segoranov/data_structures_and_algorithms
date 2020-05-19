#ifndef DEQUE_H_20200509
#define DEQUE_H_20200509

#include <stddef.h>

#include <cassert>
#include <stdexcept>

template <typename T>
class Deque {
 public:
  Deque() = default;
  Deque(size_t initialSize);
  Deque(const Deque &);
  Deque &operator=(const Deque &);
  ~Deque();

  /**
   * Appends the given element value to the end of the container.
   */
  void push_back(const T &value);

  /**
   * Removes the last element of the container.
   * Calling pop_back on an empty container is undefined behavior.
   */
  void pop_back();

  /**
   * Appends the given element value to the beginning of the container.
   */
  void push_front(const T &value);

  /**
   * Removes the first element of the container.
   * Calling pop_back on an empty container causes undefined behavior.
   */
  void pop_front();

  /**
   * Checks if index is out of bounds and throws exception if it is
   * @throw std::out_of_range
   */
  T &at(size_t index);

  /**
   * Access element without checking if index is out of bounds
   * Accessing out of bounds element causes undefined behavior.
   */
  T &operator[](size_t index);
  const T &operator[](size_t index) const;

  /**
   * Returns a reference to the last element in the container.
   * Calling back on an empty container is undefined behavior.
   */
  T &back();
  const T &back() const;

  /**
   * Returns a reference to the first element in the container.
   * Calling front on an empty container is undefined behavior.
   */
  T &front();
  const T &front() const;

  /**
   * Returns number of elements in the deque
   */
  size_t size() const;

  /**
   * Returns the size of the internal buffer.
   * Could be larger than the number of elemets in the deque
   */
  // size_t capacity() const; TODO is it needed? std::deque lacks this.

  /**
   * Returns whether the deque is empty of elements or not
   */
  bool empty() const;

  /**
   * Erases all elements from the container. After this call, size() returns
   * zero.
   *
   * @param bDeleteInternalBuffer If true, the internal buffer will have 0
   * capacity. The memory will be returned to the OS.
   */
  void clear(bool bDeleteInternalBuffer = false);

 private:
  void resize(size_t newCapacity);

  // Helper function used to add the element when !m_arr is true
  void addElementWhenEmpty(const T &value);

  void copy(const Deque &other);

 private:
  T *m_arr = nullptr;
  size_t m_currentSize = 0;
  size_t m_currentCapacity = 0;
  size_t m_startIndex;
  size_t m_frontIndex;
  size_t m_backIndex;
};

template <typename T>
Deque<T>::Deque(size_t initialSize) {
  m_arr = new T[initialSize];
  m_startIndex = initialSize / 2;
  // initialize all values with zero
  for (int i = 0; i < initialSize; i++) {
    m_arr[i] = 0;
  }

  m_frontIndex = 0;
  m_backIndex = initialSize - 1;
  m_currentSize = initialSize;
  m_currentCapacity = initialSize;
}

template <typename T>
Deque<T>::Deque(const Deque &other) : m_arr{nullptr} {
  copy(other);
}

template <typename T>
Deque<T> &Deque<T>::operator=(const Deque &other) {
  if (this != &other) {
    copy(other);
  }

  return *this;
}

template <typename T>
void Deque<T>::copy(const Deque &other) {
  T *newArr = new T[other.m_currentCapacity];
  m_startIndex = other.m_startIndex;
  m_frontIndex = other.m_frontIndex;
  m_backIndex = other.m_backIndex;
  for (int i = other.m_frontIndex; i <= other.m_backIndex; i++) {
    newArr[i] = other.m_arr[i];
  }

  delete[] m_arr;
  m_arr = newArr;
  m_currentSize = other.m_currentSize;
  m_currentCapacity = other.m_currentCapacity;
}

template <typename T>
void Deque<T>::push_back(const T &value) {
  if (!m_arr) {  // 0 elements
    addElementWhenEmpty(value);
    return;
  }

  if (m_backIndex == m_currentCapacity - 1) {
    // No more space for push_back. Resizing should be done.
    resize(m_currentCapacity * 2);
  }

  m_arr[++m_backIndex] = value;
  ++m_currentSize;
}

template <typename T>
void Deque<T>::push_front(const T &value) {
  if (!m_arr) {  // 0 elements
    addElementWhenEmpty(value);
    return;
  }

  while (m_frontIndex == 0) {
    // No space for push_front. Resizing should be done.
    resize(m_currentCapacity * 2);
  }

  m_arr[--m_frontIndex] = value;
  ++m_currentSize;
}

template <typename T>
void Deque<T>::addElementWhenEmpty(const T &value) {
  m_arr = new T[1];
  m_arr[0] = value;
  m_startIndex = m_frontIndex = m_backIndex = 0;
  m_currentCapacity = m_currentSize = 1;
}

template <typename T>
void Deque<T>::pop_back() {
  if (size() == 1) {
    clear(true);
    return;
  }

  --m_backIndex;
  --m_currentSize;
}

template <typename T>
void Deque<T>::pop_front() {
  if (size() == 1) {
    clear(true);
    return;
  }

  --m_currentSize;
  ++m_frontIndex;
}

template <typename T>
void Deque<T>::resize(size_t newCapacity) {
  assert(newCapacity > m_currentCapacity);
  T *newBuff = new T[newCapacity];
  m_currentCapacity = newCapacity;

  const size_t frontIndexDistanceToStart = m_startIndex - m_frontIndex;
  const size_t backIndexDistanceToStart = m_backIndex - m_startIndex;

  const size_t newStartIndex = (newCapacity - 1) / 2;
  const size_t newFrontIndex = newStartIndex - frontIndexDistanceToStart;
  const size_t newBackIndex = newStartIndex + backIndexDistanceToStart;

  size_t i = m_frontIndex;
  size_t j = newFrontIndex;
  for (; i <= m_backIndex; i++, j++) {
    newBuff[j] = m_arr[i];
  }

  m_startIndex = newStartIndex;
  m_frontIndex = newFrontIndex;
  m_backIndex = newBackIndex;
  delete[] m_arr;
  m_arr = newBuff;
}

template <typename T>
size_t Deque<T>::size() const {
  return m_currentSize;
}

// template <typename T> size_t Deque<T>::capacity() const {}

template <typename T>
bool Deque<T>::empty() const {
  return m_currentSize == 0;
}

template <typename T>
void Deque<T>::clear(bool bDeleteInternalBuffer) {
  if (bDeleteInternalBuffer) {
    delete[] m_arr;
    m_arr = nullptr;
    m_currentSize = m_currentCapacity = 0;
  } else {
    m_currentSize = 0;
    m_frontIndex = m_backIndex = m_startIndex;
  }
}

template <typename T>
T &Deque<T>::at(size_t index) {
  if (index < 0 || index >= m_currentSize) {
    throw std::out_of_range{"Index out of range."};
  }

  return m_arr[m_frontIndex + index];
}

template <typename T>
T &Deque<T>::operator[](size_t index) {
  return m_arr[m_frontIndex + index];
}

template <typename T>
const T &Deque<T>::operator[](size_t index) const {
  return m_arr[m_frontIndex + index];
}

template <typename T>
T &Deque<T>::back() {
  return m_arr[m_backIndex];
}

template <typename T>
const T &Deque<T>::back() const {
  return m_arr[m_backIndex];
}

template <typename T>
T &Deque<T>::front() {
  return m_arr[m_frontIndex];
}

template <typename T>
const T &Deque<T>::front() const {
  return m_arr[m_frontIndex];
}

template <typename T>
Deque<T>::~Deque() {
  delete[] m_arr;
}

template <typename T>
bool operator==(const Deque<T> &lhs, const Deque<T> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  for (int i = 0; i < lhs.size(); i++) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }

  return true;
}

template <typename T>
bool operator!=(const Deque<T> &lhs, const Deque<T> &rhs) {
  return !(lhs == rhs);
}

#endif

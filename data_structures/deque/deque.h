#ifndef DEQUE_H_20200509
#define DEQUE_H_20200509

#include <stddef.h>

template <typename T> class Deque {
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
   */
  void clear();

private:
  T *m_arr = nullptr;
  size_t m_currentSize = 0;
  size_t m_currentCapacity = 0;
};

template <typename T> Deque<T>::Deque(size_t initialSize) {}

template <typename T> Deque<T>::Deque(const Deque &other) {}

template <typename T> Deque<T> &Deque<T>::operator=(const Deque &other) {}

template <typename T> void Deque<T>::push_back(const T &value) {}

template <typename T> void Deque<T>::pop_back() {}

template <typename T> size_t Deque<T>::size() const {
  return m_currentSize;
}

// template <typename T> size_t Deque<T>::capacity() const {}

template <typename T> bool Deque<T>::empty() const {}

template <typename T> void Deque<T>::clear() {}

template <typename T> T &Deque<T>::at(size_t index) {}

template <typename T> T &Deque<T>::operator[](size_t index) {}

template <typename T> const T &Deque<T>::operator[](size_t index) const {}

template <typename T> T &Deque<T>::back() {}

template <typename T> const T &Deque<T>::back() const {}

template <typename T> Deque<T>::~Deque() { delete[] m_arr; }

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

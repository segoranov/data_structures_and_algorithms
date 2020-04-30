#include "dynamic_array.h"

DynamicArray::DynamicArray(size_t initialSize) {
  m_arr = new double[initialSize];

  // initialize all values with zero
  for (int i = 0; i < initialSize; i++) {
    m_arr = 0;
  }

  m_currentSize = initialSize;
  m_currentCapacity = initialSize;
}

DynamicArray::DynamicArray(const DynamicArray &other) {
  m_arr = new double[other.m_currentCapacity];
  for (int i = 0; i < other.m_currentSize; i++) {
    m_arr[i] = other.m_arr[i];
  }

  m_currentSize = other.m_currentSize;
  m_currentCapacity = other.m_currentCapacity;
}

DynamicArray &DynamicArray::operator=(const DynamicArray &other) {
  if (this != &other) {
    double *new_arr = new double[other.m_currentCapacity];
    for (int i = 0; i < other.m_currentSize; i++) {
      new_arr[i] = other.m_arr[i];
    }

    delete[] m_arr;
    m_arr = new_arr;
    m_currentSize = other.m_currentSize;
    m_currentCapacity = other.m_currentCapacity;
  }

  return *this;
}

void DynamicArray::push_back(double value) {
  // 1st case: Buffer has no capacity yet
  if (m_currentCapacity == 0) {
    m_arr = new double[1];
    m_arr[0] = value;
    m_currentSize = 1;
    m_currentCapacity = 1;
    return;
  }

  // 2nd case: We have space for more elements in the buffer
  if (m_currentSize < m_currentCapacity) {
    m_arr[m_currentSize++] = value;
    return;
  }

  // 3rd case: We have reached full buffer capacity, time to resize
  static const int RESIZE_CONSTANT = 2;

  const size_t newCapacity = m_currentCapacity * RESIZE_CONSTANT;
  double *new_arr = new double[newCapacity];

  // copy old values into new buffer
  int i = 0;
  for (; i < m_currentSize; i++) {
    new_arr[i] = m_arr[i];
  }

  new_arr[i] = value;
  ++m_currentSize;

  delete[] m_arr;
  m_arr = new_arr;
  m_currentCapacity = newCapacity;
}

void DynamicArray::pop_back() {
  if (empty()) {
    throw std::runtime_error("Calling pop_back() on an empty container.");
  }

  --m_currentSize;
}

size_t DynamicArray::size() const { return m_currentSize; }

size_t DynamicArray::capacity() const { return m_currentCapacity; }

bool DynamicArray::empty() const { return m_currentSize == 0; }

void DynamicArray::clear() { m_currentSize = 0; }

double &DynamicArray::at(size_t index) {
  if (index < 0 || index >= m_currentSize) {
    throw std::out_of_range{"Index out of range."};
  }

  return m_arr[index];
}

double &DynamicArray::operator[](size_t index) { return m_arr[index]; }

const double &DynamicArray::operator[](size_t index) const {
  return m_arr[index];
}

double *DynamicArray::data() noexcept { return m_arr; }

DynamicArray::~DynamicArray() { delete[] m_arr; }

bool operator==(const DynamicArray &lhs, const DynamicArray &rhs) {
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

bool operator!=(const DynamicArray &lhs, const DynamicArray &rhs) {
  return !(lhs == rhs);
}
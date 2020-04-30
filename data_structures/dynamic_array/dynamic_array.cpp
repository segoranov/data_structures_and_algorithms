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

size_t DynamicArray::size() const { return m_currentSize; }

size_t DynamicArray::capacity() const { return m_currentCapacity; }

bool DynamicArray::empty() const { return m_currentSize == 0; }

double &DynamicArray::at(size_t index) {
  if (index < 0 || index >= m_currentSize) {
    throw std::out_of_range{"Index out of range."};
  }

  return m_arr[index];
}

double &DynamicArray::operator[](size_t index) { return m_arr[index]; }

double *DynamicArray::data() noexcept { return m_arr; }

DynamicArray::~DynamicArray() { delete[] m_arr; }

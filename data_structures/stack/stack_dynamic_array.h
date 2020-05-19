#ifndef STACK_DYNAMIC_ARRAY_H
#define STACK_DYNAMIC_ARRAY_H

#include <stdexcept>

#include "../dynamic_array_template/dynamic_array.h"
#include "istack.h"

template <typename T>
class StackDynamicArrayImpl final : public IStack<T> {
 public:
  virtual void push(const T &newElem) override;
  virtual void pop() override;
  virtual T &top() override;
  virtual const T &top() const override;
  virtual size_t size() const override;
  virtual bool empty() const override;

 private:
  DynamicArray<T> m_dynArr;
};

template <typename T>
void StackDynamicArrayImpl<T>::push(const T &newElem) {
  m_dynArr.push_back(newElem);
}

template <typename T>
void StackDynamicArrayImpl<T>::pop() {
  m_dynArr.pop_back();
}

template <typename T>
T &StackDynamicArrayImpl<T>::top() {
  if (empty()) {
    throw std::runtime_error{"Trying to access top element of empty stack."};
  }

  return m_dynArr.back();
}

template <typename T>
const T &StackDynamicArrayImpl<T>::top() const {
  if (empty()) {
    throw std::runtime_error{"Trying to access top element of empty stack."};
  }

  return m_dynArr.back();
}

template <typename T>
size_t StackDynamicArrayImpl<T>::size() const {
  return m_dynArr.size();
}

template <typename T>
bool StackDynamicArrayImpl<T>::empty() const {
  return m_dynArr.empty();
}

#endif

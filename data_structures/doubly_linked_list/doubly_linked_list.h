#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>
#include <stdexcept>

template <typename T> struct Node {
  Node *previous;
  T data;
  Node *next;

  Node(const T &d, Node *p = nullptr, Node *n = nullptr)
      : data{d}, previous{p}, next{n} {}
};

template <typename T, typename ReferenceType, typename NodeType>
class DLLIterator;

template <typename T>
using DoublyLinkedListIterator = DLLIterator<T, T &, Node<T>>;

template <typename T>
using DoublyLinkedListCIterator = DLLIterator<T, const T &, const Node<T>>;

template <typename T> class DoublyLinkedList {
public:
  DoublyLinkedList() = default;
  DoublyLinkedList(const DoublyLinkedList &other); // O(n)
  DoublyLinkedList &operator=(const DoublyLinkedList &other); // O(n)
  ~DoublyLinkedList(); // O(n)

  /**
   * Appends the given element value to the end of the container.
   * O(1) time complexity
   */
  void push_back(const T &value);

  /**
   * Removes the last element of the container.
   * Calling pop_back on an empty container throws exception.
   * O(1) time complexity
   *
   * @throw std::runtime_error
   */
  void pop_back();

  /**
   * Appends the given element value at the beginning of the container.
   * O(1) time complexity
   *
   */
  void push_front(const T &value);

  /**
   * Removes the first element of the container.
   * Calling pop_front on an empty container throws exception.
   * O(1) time complexity
   *
   * @throw std::runtime_error
   */
  void pop_front();

  /**
   * @return an iterator to the first element
   */
  DoublyLinkedListIterator<T> begin() noexcept;
  DoublyLinkedListCIterator<T> begin() const noexcept;
  DoublyLinkedListCIterator<T> cbegin() const noexcept;

  /**
   * @return an iterator to the end element
   */
  DoublyLinkedListIterator<T> end() noexcept;
  DoublyLinkedListCIterator<T> end() const noexcept;
  DoublyLinkedListCIterator<T> cend() const noexcept;

  /**
   * Inserts value before pos.
   *
   * @return Iterator pointing to the inserted value
   */
  DoublyLinkedListIterator<T> insertBefore(DoublyLinkedListIterator<T> pos,
                                           const T &value);
  DoublyLinkedListCIterator<T> insertBefore(DoublyLinkedListCIterator<T> pos,
                                            const T &value);

  /**
   * Removes the element at pos.
   *
   * @return Iterator following the last removed element.
   * If pos refers to the last element, then invalid iterator is returned
   *
   * @note The parameter 'pos' becomes invalid iterator after the erasion
   */
  DoublyLinkedListIterator<T> erase(DoublyLinkedListIterator<T> pos);
  DoublyLinkedListCIterator<T> erase(DoublyLinkedListCIterator<T> pos);

  /**
   * Returns a reference to the first element in the container.
   */
  T &front();
  const T &front() const;

  /**
   * Returns a reference to the last element in the container.
   */
  T &back();
  const T &back() const;

  /**
   * Returns number of elements in the list
   * O(1) time complexity
   *
   */
  size_t size() const noexcept;

  /**
   * Returns whether the array is empty of elements or not
   * O(1) time complexity
   *
   */
  bool empty() const noexcept;

  /**
   * Clears the linked list's contents
   * Complexity: Linear in the size of the container, i.e., the number of
   * elements.
   */
  void clear();

private:
  template <typename IteratorType> IteratorType erase_help(IteratorType pos);
  template <typename IteratorType>
  IteratorType insert_before_help(IteratorType pos, const T &value);

private:
  Node<T> *head = nullptr;
  Node<T> *tail = nullptr;
  size_t currentSize = 0;
};

template <typename T, typename ReferenceType, typename NodeType>
class DLLIterator {
  using I = DLLIterator<T, ReferenceType, NodeType>;

public:
  explicit DLLIterator(NodeType *pCurrentNode = nullptr)
      : m_pCurrentNode{pCurrentNode} {}

  I next() const {
    if (!isValid()) {
      return *this;
    }

    return I{m_pCurrentNode->next};
  }

  I prev() const {
    if (!isValid()) {
      return *this;
    }

    return I{m_pCurrentNode->previous};
  }

  // Prefix ++ overload
  I &operator++() { return *this = next(); }

  // Postfix ++ overload
  I operator++(int) {
    I old = *this;
    ++*this;
    return old;
  }

  // Prefix -- overload
  I &operator--() { return *this = prev(); }

  // Postfix -- overload
  I operator--(int) {
    I old = *this;
    --*this;
    return old;
  }

  bool isValid() const { return m_pCurrentNode != nullptr; }
  operator bool() const { return isValid(); }

  // Calling dereference operator on invalid iterator causes undefined behavior
  ReferenceType &get() const { return m_pCurrentNode->data; }
  ReferenceType operator*() const { return get(); }

  friend bool operator==(const I &lhs, const I &rhs) {

    return lhs.m_pCurrentNode == rhs.m_pCurrentNode;
  }

  friend bool operator!=(const I &lhs, const I &rhs) { return !(lhs == rhs); }

private:
  NodeType *m_pCurrentNode;
  friend class DoublyLinkedList<T>;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList &other) {
  for (const T &elem : other) {
    push_back(elem);
  }
}

template <typename T>
DoublyLinkedList<T> &
DoublyLinkedList<T>::operator=(const DoublyLinkedList &other) {
  if (this != &other) {
    for (const T &elem : other) {
      push_back(elem);
    }
  }

  return *this;
}

template <typename T> void DoublyLinkedList<T>::push_front(const T &value) {
  Node<T> *node = new Node{value};
  ++currentSize;

  if (!head) {
    head = tail = node;
    return;
  }

  // we have at least 1 element
  head->previous = node;
  node->next = head;
  head = node;
}

template <typename T> void DoublyLinkedList<T>::pop_front() {
  if (empty()) {
    throw std::runtime_error{"Calling pop_front() on an empty list."};
  }

  --currentSize;

  if (currentSize == 0) { // there was only 1 element in the list
    delete head;
    head = tail = nullptr;
  } else { // there were at least 2 elements in the list
    head = head->next;
    delete head->previous;
    head->previous = nullptr;
  }
}

template <typename T> void DoublyLinkedList<T>::push_back(const T &value) {
  Node<T> *node = new Node{value};
  ++currentSize;

  if (!head) {
    head = tail = node;
    return;
  }

  // we have at least 1 element
  tail->next = node;
  node->previous = tail;
  tail = node;
}

template <typename T> void DoublyLinkedList<T>::pop_back() {
  if (empty()) {
    throw std::runtime_error{"Calling pop_back() on an empty list."};
  }

  --currentSize;

  if (currentSize == 0) { // there was only 1 element in the list
    delete tail;
    head = tail = nullptr;
  } else { // there were at least 2 elements in the list
    tail = tail->previous;
    delete tail->next;
    tail->next = nullptr;
  }
}

template <typename T> DoublyLinkedList<T>::~DoublyLinkedList() { clear(); }

template <typename T>
DoublyLinkedListIterator<T> DoublyLinkedList<T>::begin() noexcept {
  return DoublyLinkedListIterator<T>{head};
}

template <typename T>
DoublyLinkedListCIterator<T> DoublyLinkedList<T>::begin() const noexcept {
  return DoublyLinkedListCIterator<T>{head};
}

template <typename T>
DoublyLinkedListCIterator<T> DoublyLinkedList<T>::cbegin() const noexcept {
  return DoublyLinkedListCIterator<T>{head};
}

template <typename T>
DoublyLinkedListIterator<T> DoublyLinkedList<T>::end() noexcept {
  return DoublyLinkedListIterator<T>{nullptr};
}

template <typename T>
DoublyLinkedListCIterator<T> DoublyLinkedList<T>::end() const noexcept {
  return DoublyLinkedListCIterator<T>{nullptr};
}

template <typename T>
DoublyLinkedListCIterator<T> DoublyLinkedList<T>::cend() const noexcept {
  return DoublyLinkedListCIterator<T>{nullptr};
}

template <typename T>
DoublyLinkedListIterator<T>
DoublyLinkedList<T>::insertBefore(DoublyLinkedListIterator<T> pos,
                                  const T &value) {
  if (pos == begin()) {
    push_front(value);
    return begin();
  }

  return insert_before_help(pos, value);
}

template <typename T>
DoublyLinkedListCIterator<T>
DoublyLinkedList<T>::insertBefore(DoublyLinkedListCIterator<T> pos,
                                  const T &value) {
  if (pos == cbegin()) {
    push_front(value);
    return cbegin();
  }

  return insert_before_help(pos, value);
}

template <typename T>
template <typename IteratorType>
IteratorType DoublyLinkedList<T>::insert_before_help(IteratorType pos,
                                                     const T &value) {
  Node<T> *node = new Node{value};
  ++currentSize;

  node->next = pos.m_pCurrentNode;
  node->previous = pos.m_pCurrentNode->previous;
  pos.m_pCurrentNode->previous->next = node;
  pos.m_pCurrentNode->previous = node;

  return IteratorType{node};
}

template <typename T>
DoublyLinkedListIterator<T>
DoublyLinkedList<T>::erase(DoublyLinkedListIterator<T> pos) {
  if (pos == begin()) {
    pop_front();
    return begin();
  }

  return erase_help(pos);
}

template <typename T>
DoublyLinkedListCIterator<T>
DoublyLinkedList<T>::erase(DoublyLinkedListCIterator<T> pos) {
  if (pos == cbegin()) {
    pop_front();
    return cbegin();
  }

  return erase_help(pos);
}

template <typename T>
template <typename IteratorType>
IteratorType DoublyLinkedList<T>::erase_help(IteratorType pos) {
  --currentSize;
  pos.m_pCurrentNode->previous->next = pos.m_pCurrentNode->next;
  pos.m_pCurrentNode->next->previous = pos.m_pCurrentNode->previous;
  auto next = IteratorType{pos.m_pCurrentNode->next};
  delete pos.m_pCurrentNode;
  return next;
}

template <typename T> T &DoublyLinkedList<T>::front() { return head->data; }

template <typename T> const T &DoublyLinkedList<T>::front() const {
  return head->data;
}

template <typename T> T &DoublyLinkedList<T>::back() { return tail->data; }

template <typename T> const T &DoublyLinkedList<T>::back() const {
  return tail->data;
}

template <typename T> size_t DoublyLinkedList<T>::size() const noexcept {
  return currentSize;
}

template <typename T> bool DoublyLinkedList<T>::empty() const noexcept {
  return !head;
}

template <typename T> void DoublyLinkedList<T>::clear() {
  while (!empty()) {
    pop_back();
  }
}

template <typename T>
bool operator==(const DoublyLinkedList<T> &lhs,
                const DoublyLinkedList<T> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  auto itLhs = lhs.cbegin();
  auto itRhs = rhs.cbegin();

  for (; itLhs != lhs.cend(); ++itLhs, ++itRhs) {
    if (*itLhs != *itRhs) {
      return false;
    }
  }

  return true;
}

template <typename T>
bool operator!=(const DoublyLinkedList<T> &lhs,
                const DoublyLinkedList<T> &rhs) {
  return !(lhs == rhs);
}

#endif

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

template <typename T> class DoublyLinkedListIterator;

template <typename T> class DoublyLinkedList {
public:
  DoublyLinkedList() = default;
  DoublyLinkedList(const DoublyLinkedList &);
  DoublyLinkedList &operator=(const DoublyLinkedList &);
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
   * @return an iterator to the beginning
   */
  DoublyLinkedListIterator<T> begin() noexcept;

  /**
   * @return an iterator to the end
   */
  DoublyLinkedListIterator<T> end() noexcept;

  /**
   * Inserts value before pos.
   *
   * @return Iterator pointing to the inserted value
   */
  DoublyLinkedListIterator<T> insert(DoublyLinkedListIterator<T> pos,
                                     const T &value);

  /**
   * Removes the element at pos.
   *
   * @return Iterator following the last removed element.
   * If pos refers to the last element, then the end() iterator is returned.
   */
  DoublyLinkedListIterator<T> erase(DoublyLinkedListIterator<T> pos);

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
  Node<T> *head = nullptr;
  Node<T> *tail = nullptr;
  size_t currentSize = 0;
};

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

template <typename T> DoublyLinkedList<T>::~DoublyLinkedList() {
  while (head) {
    Node<T> *nextHead = head->next;
    delete head;
    head = nextHead;
  }
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

template <typename T> class DoublyLinkedListIterator {};

template <typename T>
bool operator==(const DoublyLinkedList<T> &lhs,
                const DoublyLinkedList<T> &rhs) {}

template <typename T>
bool operator!=(const DoublyLinkedList<T> &lhs,
                const DoublyLinkedList<T> &rhs) {}

#endif
#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;

  void Copy(const CircularLinkedList<T>& source);
  void InsertAsc(const T& data);
  void InsertDesc(const T& data);
  void Destroy();
};

template <typename T>
void CircularLinkedList<T>::Copy(const CircularLinkedList<T>& source) {
  if (source.head_ == nullptr) return;
  if (source.head_ == source.tail_) {
    head_ = tail_ = new Node<T>(source.head_->data);
    head_->next = head_;
    return;
  }

  head_ = new Node<T>(source.head_->data);
  head_->next = new Node<T>(source.head_->next->data);
  Node<T>* curr = head_->next;
  Node<T>* source_curr = source.head_->next;

  while (source_curr != source.head_) {
    if (source_curr == source.tail_) {
      tail_ = curr;
      tail_->next = head_;
      break;
    }
    curr->next = new Node<T>(source_curr->next->data);
    curr = curr->next;
    source_curr = source_curr->next;
  }
  node_order_ = source.node_order_;
}

template <typename T>
void CircularLinkedList<T>::Destroy() {
  if (head_ == tail_) {
    delete head_;
    return;
  }
  Node<T>* curr = head_->next;
  while (curr != head_) {
    Node<T>* tmp = curr->next;
    delete curr;
    curr = tmp;
  }
  delete head_;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  Copy(source);
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (&source == this) return *this;
  Destroy();
  Copy(source);
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  Destroy();
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {
    auto* new_node = new Node<T>(data);
    head_ = new_node;
    tail_ = new_node;
    head_->next = tail_;
    tail_->next = head_;
    return;
  }
  if (node_order_ == Order::kASC) InsertAsc(data);
  if (node_order_ == Order::kDESC) InsertDesc(data);
}

template <typename T>
void CircularLinkedList<T>::InsertAsc(const T& data) {
  if (data < head_->data) {
    auto* new_head = new Node<T>(data);
    tail_->next = new_head;
    new_head->next = head_;
    head_ = new_head;
    return;
  }
  Node<T>* curr = head_;
  while (data >= curr->next->data) {
    if (curr == tail_) break;
    curr = curr->next;
  }
  auto* new_node = new Node<T>(data);
  new_node->next = curr->next;
  curr->next = new_node;
  if (curr == tail_) tail_ = new_node;
}

template <typename T>
void CircularLinkedList<T>::InsertDesc(const T& data) {
  if (data > head_->data) {
    auto* new_head = new Node<T>(data);
    tail_->next = new_head;
    new_head->next = head_;
    head_ = new_head;
    return;
  }
  Node<T>* curr = head_;
  while (data <= curr->next->data) {
    if (curr == tail_) break;
    curr = curr->next;
  }
  auto* new_node = new Node<T>(data);
  new_node->next = curr->next;
  curr->next = new_node;
  if (curr == tail_) tail_ = new_node;
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
  if (head_ == tail_) return;

  Node<T>* stop = tail_;

  while (head_ != stop) {
    Node<T>* curr = head_;
    while (curr->next != stop) curr = curr->next;
    stop->next = curr;
    stop = curr;
  }
  head_->next = tail_;
  Node<T>* tmp = head_;
  head_ = tail_;
  tail_ = tmp;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

#endif
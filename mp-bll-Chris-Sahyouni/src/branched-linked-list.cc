#include "branched-linked-list.hpp"

#include <cstddef>
#include <stdexcept>
#include <string>

bool is_destroyed = false;

BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    head_ = nullptr;
    return;
  }
  head_ = new Node(to_copy.head_->data_);
  Copy(to_copy);
}

BLL::~BLL() {
  if (!is_destroyed) {
    Destroy();
    is_destroyed = true;
  }
}

BLL& BLL::operator=(const BLL& rhs) {
  if (&rhs == this) return *this;
  Destroy();
  if (rhs.head_ != nullptr) head_ = new Node(rhs.head_->data_);
  Copy(rhs);
  return *this;
}

// Copy and Destroy should go here
void BLL::Copy(const BLL& rhs) {
  if (rhs.head_ == nullptr) {
    head_ = nullptr;
    return;
  }

  Node* rhs_curr = rhs.head_;
  Node* lhs_curr = head_;
  while (rhs_curr != nullptr) {
    if (rhs_curr->next_bll_ != nullptr && rhs_curr->next_bll_->head_ != nullptr) {
      char dat = rhs_curr->next_bll_->head_->data_;
      lhs_curr->next_bll_ = new BLL();
      lhs_curr->next_bll_->head_ = new Node(dat);
      lhs_curr->next_bll_->Copy(*rhs_curr->next_bll_);
    }
    if (rhs_curr->next_node_ != nullptr) {
      char c = rhs_curr->next_node_->data_;
      PushBack(c);
    }
    rhs_curr = rhs_curr->next_node_;
    lhs_curr = lhs_curr->next_node_;
  }
}

void BLL::Destroy() {
  Node* curr = head_;
  while (curr != nullptr) {
    if (curr->next_bll_ != nullptr && curr->next_bll_->head_ != nullptr) {
    //  Destroy(curr->next_bll_->head_);
    delete curr->next_bll_;
    }
    Node* tmp = curr;
    curr = curr->next_node_;
    delete tmp;
  }
}

Node* BLL::PushBack(char dat) {
  if (head_ == nullptr) {
    head_ = new Node(dat);
    return head_;
  }
  Node* new_node = new Node(dat);
  auto* curr = head_;
  while (curr->next_node_ != nullptr) {
    curr = curr->next_node_;
  }
  curr->next_node_ = new_node;
  return new_node;
};

char BLL::GetAt(size_t idx) const {
  size_t end = Size();
  if (idx >= end || idx < 0) {
    throw std::invalid_argument("GetAt: Index out of bounds");
  }
  size_t running_idx = 0;
  return GetNodeAt(idx, running_idx, head_)->data_;
}

Node* BLL::GetNodeAt(size_t idx, size_t& running_idx, Node* branch_head) const {
  auto* curr = branch_head;
  while (curr != nullptr) {
    if (running_idx == idx) return curr;
    if (curr->next_bll_ != nullptr && curr->next_bll_->head_ != nullptr) {
      ++running_idx;
      Node* nxt_hd = curr->next_bll_->head_;
      Node* potential_find = GetNodeAt(idx, running_idx, nxt_hd);
      if (potential_find != head_) return potential_find;
    }
    ++running_idx;
    curr = curr->next_node_;
  }
  --running_idx;
  return head_;
}

size_t BLL::Size() const { return SizeRecursive(head_); }

size_t BLL::SizeRecursive(Node* branch_head) const {
  size_t size = 0;
  auto* curr = branch_head;
  while (curr != nullptr) {
    if (curr->next_bll_ != nullptr && curr->next_bll_->head_ != nullptr) {
      size += SizeRecursive(curr->next_bll_->head_);
    }
    ++size;
    curr = curr->next_node_;
  }
  return size;
}

void BLL::SetAt(size_t idx, char dat) {
  size_t end = Size();
  if (idx >= end) {
    throw std::invalid_argument("SetAt: Index out of bounds");
  }
  size_t running_idx = 0;
  GetNodeAt(idx, running_idx, head_)->data_ = dat;
}

void BLL::Join(size_t idx, BLL* list) {
  if (list->head_ == nullptr) return;
  size_t running_idx = 0;
  auto* node = GetNodeAt(idx, running_idx, head_);

  if (node->next_bll_ == nullptr) {
    node->next_bll_ = list;
  } else {
    throw std::invalid_argument("Join: node already has a next BLL");
  }

  if (!IsBLLAcyclic()) {
    throw std::runtime_error("Join caused BLL to be cyclic");
  }
}

bool BLL::IsBLLAcyclic() const {
  Node* tortoise = head_;
  Node* hare = head_->next_node_;
  while (tortoise != nullptr && hare != nullptr && GetNext(hare) != nullptr) {
    if (tortoise == hare) return false;
    tortoise = GetNext(tortoise);
    hare = GetNext(hare);
    hare = GetNext(hare);
  }
  return true;
}

Node* BLL::GetNext(Node* curr) const {
  if (curr->next_bll_ != nullptr && curr->next_bll_->head_ != nullptr) {
    return curr->next_bll_->head_;
  }
  return curr->next_node_;
}

std::string BLL::ToString() const {
  if (head_ == nullptr) return "";
  return ToStringRecursive(head_);
}

std::string BLL::ToStringRecursive(Node* branch_head) const {
  auto* curr = branch_head;
  std::string to_return;
  while (curr != nullptr) {
    to_return += curr->data_;
    if (curr->next_bll_ != nullptr && curr->next_bll_->head_ != nullptr) {
      to_return += ToStringRecursive(curr->next_bll_->head_);
    }
    curr = curr->next_node_;
  }
  return to_return;
}

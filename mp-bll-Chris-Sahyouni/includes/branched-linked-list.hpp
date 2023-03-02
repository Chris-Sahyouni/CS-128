#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include "node.hpp"

class BLL {
public:
  BLL() = default;
  BLL(const BLL& to_copy);
  ~BLL();

  BLL& operator=(const BLL& rhs);
  Node* PushBack(char dat);
  char GetAt(size_t idx) const;
  void SetAt(size_t idx, char dat);
  void Join(size_t idx, BLL* list);
  std::string ToString() const;
  size_t Size() const;

  Node* GetNodeAt(size_t idx, size_t& running_idx, Node* branch_head) const;

private:
  Node* head_ = nullptr;

  bool IsBLLAcyclic() const;
  void Copy(const BLL& rhs);
  void Destroy();

  Node* GetNext(Node* curr) const;

  std::string ToStringRecursive(Node* branch_head) const;
  size_t SizeRecursive(Node* branch_head) const;
};

#endif

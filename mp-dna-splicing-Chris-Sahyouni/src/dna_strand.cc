#include "dna_strand.hpp"

#include <stdexcept>
#include <cassert>

static bool is_splice_in = true;

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (&to_splice_in == this || *pattern == ' ' || head_ == nullptr) return;
  unsigned int pattern_size = GetPatternSize(pattern);
  unsigned int last_occurrence = FindLastOccurence(pattern);
  Node* curr = head_;
  unsigned int idx = 0;
  Node* before_break = nullptr;
  Node* after_break = nullptr;
  if (last_occurrence == 0) {
    for (unsigned int i = 0; i < pattern_size; ++i) {
        Node* tmp = curr->next;
        delete curr;
        curr = tmp;
    }
    to_splice_in.tail_->next = curr;
    head_ = to_splice_in.head_;
  } else {
    while (curr != nullptr) {
        if (idx == last_occurrence - 1) {
            before_break = curr;
        }
        if (idx == last_occurrence + pattern_size) {
            after_break = curr;
        } 
        curr = curr->next;
        ++idx;
    }
    idx = 0;
    curr = before_break->next;
    while (curr != after_break) {
        Node* tmp = curr->next;
        delete curr;
        curr = tmp;
    }
    before_break->next = to_splice_in.head_;
    to_splice_in.tail_->next = after_break;
  }
}


DNAstrand::~DNAstrand() {
  if (is_splice_in) {
    is_splice_in = false;
    return;
  } 
  while (head_ != nullptr) {
    Node* tmp = head_->next;
    delete head_;
    head_ = tmp;
  }
}

unsigned int DNAstrand::GetPatternSize(const char* pattern) {
  unsigned int idx = 0;
  unsigned int pattern_size = 0;
  char c = pattern[0];
  while (c != '\0') {
    ++pattern_size;
    ++idx;
    c = pattern[idx];
  }
  return pattern_size;
}

unsigned int DNAstrand::FindLastOccurence(const char* pattern) {
  bool found = false;
  unsigned int last_index = 0;
  unsigned int pattern_size = GetPatternSize(pattern);
  Node* curr = head_;
  unsigned int pattern_idx = 0;
  unsigned int sequence_idx = 0;
  while (curr != nullptr) {
    // if the characters match
    if (curr->data == pattern[pattern_idx]) {
      ++pattern_idx;
      // if the whole pattern has matched
      if (pattern_idx == pattern_size) {
        found = true;
        last_index = sequence_idx - pattern_size + 1;
        pattern_idx = 0;
      }
      //
    } else {
      pattern_idx = 0;
    }
    curr = curr->next;
    ++sequence_idx;
  }
  if (!found) throw std::runtime_error("Pattern not found");
  return last_index;
}

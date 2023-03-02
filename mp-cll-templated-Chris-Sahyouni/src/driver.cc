#include <iostream>

#include "circular-linked-list.hpp"

int main() {

    // creates a test list
    CircularLinkedList<int> cll;
    cll.node_order_ = Order::kDESC;
    cll.head_ = new Node<int>(10);
    Node<int>* curr = cll.head_;
    for (int i = 9; i >= 0; --i) {
        auto* new_node = new Node<int>(i);
        curr->next = new_node;
        curr = curr->next;
    }
    cll.tail_ = curr;
    cll.tail_->next = cll.head_;
    //

    CircularLinkedList<int> cll2;
    CircularLinkedList<int> cll3;
    cll2.node_order_ = Order::kDESC;

    cll2 = cll3 = cll;

    std::cout << cll << std::endl;
    std::cout << cll2 << std::endl;
    std::cout << cll3 << std::endl;


}

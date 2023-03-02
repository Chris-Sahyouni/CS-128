#include <iostream>

#include "dna_strand.hpp"

int main() {
    DNAstrand test1;
    char chars1[] = {'b', 'c', 'd', 'e', 'f', 'g'};
    test1.head_ = new Node('a');
    Node* curr1 = test1.head_;
    for (char c : chars1) {
        curr1->next = new Node(c);
        curr1 = curr1->next;
    }
    test1.tail_ = curr1;
    test1.tail_->next = nullptr;

    DNAstrand test2;
    char chars2[] = {'2', '3', '4'};
    test2.head_ = new Node('1');
    Node* curr2 = test2.head_;
    for (char c : chars2) {
        curr2->next = new Node(c);
        curr2 = curr2->next;
    }
    test2.tail_ = curr2;
    test2.tail_->next = nullptr;


    const char* pattern = "gg";
    // Print the original sequence
    std::cout << "Sequence: ";
    Node* test_curr = test1.head_;
    while (test_curr) {
        std::cout << test_curr->data << " ";
        test_curr = test_curr->next;
    }
    std::cout << std::endl;

    // std::cout << "Pattern Size: " << test1.GetPatternSize(pattern) << std::endl;
    // std::cout << "Last Occurrence: " << test1.FindLastOccurence(pattern) << std::endl;

    test1.SpliceIn(pattern, test2);
    // prints the spliced sequence
    test_curr = test1.head_;
    while (test_curr) {
        std::cout << test_curr->data << " ";
        test_curr = test_curr->next;
    }
    std::cout << std::endl;

}
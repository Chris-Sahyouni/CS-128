#include <iostream>

#include "branched-linked-list.hpp"
#include "node.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('a');
  first->PushBack('b');
  first->PushBack('g');

  BLL* second = new BLL();
  second->PushBack('c');
  second->PushBack('d');

  //  second->GetNodeAt(1)->next_bll_ = first;

  first->Join(1, second);

  //  std::cout << first->ToString() << std::endl;
  // first->SetAt(3, '!');
  // std::cout << first->ToString() << std::endl;

  BLL* third = new BLL();
  third->PushBack('e');
  third->PushBack('f');
  first->Join(3, third);

  // std::cout << first->ToString() << std::endl;
  // for (size_t i = 0; i < first->Size(); ++i) {
  //   std::cout << first->GetAt(i) << std::endl;
  // }

  // BLL* empty = new BLL();
  // first = empty;

  // BLL* fourth = new BLL();
  // fourth->PushBack('1');
  // fourth->PushBack('2');
  // fourth->PushBack('3');
  std::cout << first->ToString() << std::endl;
  BLL* clone = new BLL();
  *clone = *first;
  std::cout << first->ToString() << std::endl;


  delete first;
  delete clone;
//  delete empty;
  //  std::cout << fourth->GetAt(fourth->Size() - 1) << std::endl;

  // BLL* third = new BLL();
  // third->PushBack('e');
  // third->PushBack('f');

  // second->Join(1, third);
  //  first->Join(1, second);

  // std::cout << second->Size() << std::endl;

  // std::cout << first->ToString() << std::endl; // hi
  // std::cout << first->Size() << std::endl; // 2

  // /////////////////////////////////////

  // BLL* second = new BLL();
  // second->PushBack('i');
  // second->PushBack('!');
  // second->PushBack('@');

  // std::cout << second->ToString() << std::endl; // i!@
  // std::cout << second->Size() << std::endl; // 3

  // first->GetNodeAt(1)->next_bll_ = second;
  // std::cout << first->ToString() << std::endl;
  // std::cout << first->GetNodeAt(3)->data_ << std::endl;
  // /////////////////////////////////////

  //  first->Join(1, second);

  // std::string str = first->ToString();
  // std::cout << str << std::endl;
  // std::cout << first->ToString() << std::endl; // hii!@
  // std::cout << first->Size() << std::endl; // 5

  // std::cout << second->ToString() << std::endl; // i!@
  // std::cout << second->Size() << std::endl; // 3

  // /////////////////////////////////////

  // BLL* first_clone = new BLL();
  // *first_clone = *first;

  // std::cout << first_clone->ToString() << std::endl; // hii!@
  // std::cout << first_clone->Size() << std::endl; // 5



  return 0;
}

#include <iostream>

#include "illini_book.hpp"

int main() {
  IlliniBook illinibook(
      "/home/vagrant/src/mp-illini-book-Chris-Sahyouni/example/persons.csv",
      "/home/vagrant/src/mp-illini-book-Chris-Sahyouni/example/relations.csv");

  for (auto [uin, vect] : illinibook.GetGraph()) {
    std::cout << uin << ": ";
    for (const auto& i : vect) {
      std::cout << "[" << i.first << ", " << i.second << "] ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::cout << "-----------------------------------------------------------------------" << std::endl << std::endl;

//  FOR TESTING GETSEPS 
  for (auto [uin, vect] : illinibook.GetGraph()) {
    std::cout << uin << ":  ";
    for (int i = 0; i < 10; ++i) {
      std::cout << i << "->" << "[";
      for (auto node : illinibook.GetSteps(uin, i)) {
        std::cout << node << ",";
      }
      std::cout << "]  ";
    }
    std::cout << std::endl;
  }

  // std::vector<int> test = {0, 0, 1, 1, 2, 2, 3, 3};
  // illinibook.RemoveDuplicates(test);
  // for (auto i : test) {
  //   std::cout << i << " ";
  // }
  // std::cout << std::endl;





  // FOR TESTING GETRELATED
  // for (auto [uin_1, vect_1] : illinibook.GetGraph()) {
  //   for (auto [uin_2, vect_2] : illinibook.GetGraph()) {
  //     if (uin_1 != uin_2) {
  //       std::cout << uin_1 << " -> " << uin_2 << ": " << illinibook.GetRelated(uin_1, uin_2) << std::endl;
  //     }
  //   }
  // }
  
  return 0;
}
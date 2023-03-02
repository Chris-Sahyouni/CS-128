#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

int main() {
  std::vector<std::vector<char>> puzzle{{'9', 'r', 'r', 'd', 'u'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'d', 'r', 'i', 'f', 't'},
                                        {'a', 'i', 't', 'e', 'u'},
                                        {'y', 'd', '8', 'o', 'z'}};
  WordSearchSolver wss(puzzle);
  std::cout << wss.FindWord("uz");
}
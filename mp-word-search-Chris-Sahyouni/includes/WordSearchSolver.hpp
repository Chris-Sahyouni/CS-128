#ifndef WORDSEARCHSOLVER_HPP
#define WORDSEARCHSOLVER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "WordLocation.hpp"

enum class CheckDirection { kHorizontal, kVertical, kLeftDiag, kRightDiag };

class WordSearchSolver {
public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle);
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);

private:
  bool LocationInBounds(size_t row, size_t col) const;
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;

  WordLocation SearchVertically(const std::string& word);
  WordLocation SearchHorizontally(const std::string& word);
  WordLocation SearchRightDiagonally(const std::string& word);
  WordLocation SearchLeftDiagonally(const std::string& word);

  bool WordLocationsAreEqual(WordLocation& wl1, WordLocation& wl2);
};

#endif
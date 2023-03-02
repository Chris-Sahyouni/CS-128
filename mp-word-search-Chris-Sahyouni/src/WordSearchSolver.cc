#include "WordSearchSolver.hpp"

#include <cassert>
#include <string>
#include <vector>

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle) {
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle.at(0).size();
  puzzle_ = puzzle;
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  assert(word.length() <= puzzle_height_ && word.length() <= puzzle_width_);
  WordLocation empty{};
  for (unsigned int i = 0; i <= 3; ++i) {
    WordLocation wl = FindWord(word, static_cast<CheckDirection>(i));
    if (!(WordLocationsAreEqual(wl, empty))) {
      return wl;
    }
  }
  return empty;
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  switch (direction) {
  case CheckDirection::kVertical:
    return SearchVertically(word);
    break;
  case CheckDirection::kHorizontal:
    return SearchHorizontally(word);
    break;
  case CheckDirection::kRightDiag:
    return SearchRightDiagonally(word);
    break;
  case CheckDirection::kLeftDiag:
    return SearchLeftDiagonally(word);
    break;
  }
  WordLocation empty{};
  return empty;
}

WordLocation WordSearchSolver::SearchHorizontally(const std::string& word) {
  assert(word.length() <= puzzle_width_);
  WordLocation word_location;
  std::vector<CharPositions> char_position_vect;
  for (unsigned int row = 0; row < puzzle_height_; ++row) {
    for (unsigned int col = 0; col <= puzzle_width_ - word.length(); ++col) {
      std::string current_word;
      for (unsigned int i = 0; i < word.length(); ++i) {
        current_word += puzzle_.at(row).at(i + col);
        CharPositions char_position{};
        char_position.character = puzzle_.at(row).at(i + col);
        char_position.col = i + col;
        char_position.row = row;
        char_position_vect.push_back(char_position);
      }
      if (current_word == word) {
        word_location.word = word;
        word_location.char_positions = char_position_vect;
        return word_location;
      }
      char_position_vect.clear();
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::SearchVertically(const std::string& word) {
  assert(word.length() <= puzzle_height_);
  WordLocation word_location;
  std::vector<CharPositions> char_position_vect;
  for (unsigned int col = 0; col < puzzle_width_; ++col) {
    for (unsigned int row = 0; row <= puzzle_height_ - word.length(); ++row) {
      std::string current_word;
      for (unsigned int i = 0; i < word.length(); ++i) {
        current_word += puzzle_.at(row + i).at(col);
        CharPositions char_position{};
        char_position.character = puzzle_.at(row + i).at(col);
        char_position.col = col;
        char_position.row = row + i;
        char_position_vect.push_back(char_position);
      }
      if (current_word == word) {
        word_location.word = word;
        word_location.char_positions = char_position_vect;
        return word_location;
      }
      char_position_vect.clear();
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::SearchRightDiagonally(const std::string& word) {
  assert(word.length() <= puzzle_height_ && word.length() <= puzzle_width_);
  WordLocation word_location;
  std::vector<CharPositions> char_position_vect;
  for (unsigned int row = 0; row <= puzzle_height_ - word.length(); ++row) {
    for (unsigned int col = 0; col <= puzzle_width_ - word.length(); ++col) {
      std::string current_word;
      for (unsigned int i = 0; i < word.length(); ++i) {
        current_word += puzzle_.at(row + i).at(i + col);
        CharPositions char_position{};
        char_position.character = puzzle_.at(row + i).at(i + col);
        char_position.col = i + col;
        char_position.row = row + i;
        char_position_vect.push_back(char_position);
      }
      if (current_word == word) {
        word_location.word = word;
        word_location.char_positions = char_position_vect;
        return word_location;
      }
      char_position_vect.clear();
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::SearchLeftDiagonally(const std::string& word) {
  assert(word.length() <= puzzle_height_ && word.length() <= puzzle_width_);
  WordLocation word_location;
  std::vector<CharPositions> char_position_vect;
  for (unsigned int row = 0; row <= puzzle_height_ - word.length(); ++row) {
    for (size_t col = puzzle_width_ - 1; col >= word.length() - 1; --col) {

      if (col > puzzle_width_) {
        break;
      }

      std::string current_word;
      for (unsigned int i = 0; i < word.length(); ++i) {
        current_word += puzzle_.at(row + i).at(col - i);
        CharPositions char_position{};
        char_position.character = puzzle_.at(row + i).at(col - i);
        char_position.col = col - i;
        char_position.row = row + i;
        char_position_vect.push_back(char_position);
      }
      if (current_word == word) {
        word_location.word = word;
        word_location.char_positions = char_position_vect;
        return word_location;
      }
      char_position_vect.clear();
    }
  }
  return WordLocation{};
}

bool WordSearchSolver::WordLocationsAreEqual(WordLocation& wl1,
                                             WordLocation& wl2) {
  if (wl1.word != wl2.word) {
    return false;
  }
  for (size_t i = 0; i < wl1.char_positions.size(); ++i) {
    CharPositions c1 = wl1.char_positions.at(i);
    CharPositions c2 = wl2.char_positions.at(i);
    if (c1.character != c2.character) {
      return false;
    }
    if (c1.col != c2.col) {
      return false;
    }
    if (c1.row != c2.row) {
      return false;
    }
  }
  return true;
}

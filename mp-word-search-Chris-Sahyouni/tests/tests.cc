// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <string>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
bool AreEqual(const WordLocation& wl1, const WordLocation& wl2);

bool AreEqual(const WordLocation& wl1, const WordLocation& wl2) {
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




/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Test Constructor", "") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'a', 'e', 't', 'a', 'u'},
                                        {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver wss(puzzle);
  WordSearchSolver wss2(puzzle);
  for (size_t i = 0; i < puzzle.size(); ++i) {
    std::string str;
    for (size_t j = 0; j < puzzle.at(i).size(); ++j) {
      str.push_back(puzzle.at(i).at(j));
    }
    REQUIRE(AreEqual(wss.FindWord(str, CheckDirection::kHorizontal), wss2.FindWord(str, CheckDirection::kHorizontal)));
  }
}

TEST_CASE("Search Horizontally", "[constructor]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'b', 'r', 'e', 'd', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'a', 'e', 't', 'a', 'u'},
                                        {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver wss(puzzle);
  WordLocation result;
  result.word = "red";
  result.char_positions = {CharPositions{'r', 1, 1},
                           CharPositions{'e', 1, 2},
                           CharPositions{'d', 1, 3}};
  REQUIRE(AreEqual(wss.FindWord("red", CheckDirection::kHorizontal), result));
  REQUIRE(AreEqual(wss.FindWord("red"), result));
  
  WordSearchSolver wss2({{}, {}});
  REQUIRE_FALSE(AreEqual(wss2.FindWord("red"), result));

  WordLocation empty{};
  REQUIRE(AreEqual(wss.FindWord("0000"), empty));
  REQUIRE(AreEqual(wss.FindWord("0000", CheckDirection::kHorizontal), empty));
}

TEST_CASE("Search Vertically", "[find word]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'b', 'r', 'r', 'e', 'o'},
                                        {'c', 'e', 'l', 'o', 'm'},
                                        {'a', 'd', 't', 'a', 'u'},
                                        {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver wss(puzzle);
  WordLocation result;
  result.word = "red";
  result.char_positions = {CharPositions{'r', 1, 1},
                           CharPositions{'e', 2, 1},
                           CharPositions{'d', 3, 1}};
  REQUIRE(AreEqual(wss.FindWord("red", CheckDirection::kVertical), result));
  REQUIRE(AreEqual(wss.FindWord("red"), result));

  WordSearchSolver wss2({{}, {}});
  REQUIRE_FALSE(AreEqual(wss2.FindWord("red"), result));

  WordLocation empty{};
  REQUIRE(AreEqual(wss.FindWord("0000"), empty));
  REQUIRE(AreEqual(wss.FindWord("0000", CheckDirection::kVertical), empty));
}

TEST_CASE("Search Right Diagonally", "[find word]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'b', 'w', 'r', 'e', 'o'},
                                        {'r', 'e', 'l', 'o', 'm'},
                                        {'a', 'e', 't', 'a', 'u'},
                                        {'t', 'e', 'd', 'o', 'u'}};
  WordSearchSolver wss(puzzle);
  WordLocation result;
  result.word = "red";
  result.char_positions = {CharPositions{'r', 2, 0},
                           CharPositions{'e', 3, 1},
                           CharPositions{'d', 4, 2}};
  REQUIRE(AreEqual(wss.FindWord("red", CheckDirection::kRightDiag), result));
  REQUIRE(AreEqual(wss.FindWord("red"), result));

  WordSearchSolver wss2({{}, {}});
  REQUIRE_FALSE(AreEqual(wss2.FindWord("red"), result));

  WordLocation empty{};
  REQUIRE(AreEqual(wss.FindWord("0000"), empty));
  REQUIRE(AreEqual(wss.FindWord("0000", CheckDirection::kRightDiag), empty));
}

TEST_CASE("Search Left Diagonally", "[find word]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'b', 'w', 'r', 'e', 'o'},
                                        {'r', 'e', 'l', 'o', 'r'},
                                        {'a', 'i', 't', 'e', 'u'},
                                        {'t', 'e', 'd', 'o', 'y'}};
  WordSearchSolver wss(puzzle);
  WordLocation result;
  result.word = "red";
  result.char_positions = {CharPositions{'r', 2, 4},
                           CharPositions{'e', 3, 3},
                           CharPositions{'d', 4, 2}};
  REQUIRE(AreEqual(wss.FindWord("red", CheckDirection::kLeftDiag), result));
  REQUIRE(AreEqual(wss.FindWord("red"), result)); 

  WordSearchSolver wss2({{}, {}});
  REQUIRE_FALSE(AreEqual(wss2.FindWord("red"), result));

  WordLocation empty{};
  REQUIRE(AreEqual(wss.FindWord("0000"), empty));
  REQUIRE(AreEqual(wss.FindWord("0000", CheckDirection::kLeftDiag), empty));
}

/////////////////////////////////////////////////////////////////////////////////////////////
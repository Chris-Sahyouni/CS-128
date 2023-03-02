// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
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

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

//void CopyBoard(DiskType arr[kBoardHeight][kBoardWidth], Board& b);

void CopyBoard(DiskType to_copy[Board::kBoardHeight][Board::kBoardWidth], Board& b) {
  for (int r = 0; r < Board::kBoardHeight; ++r) {
    for (int c = 0; c < Board::kBoardWidth; ++c) {
      b.board[r][c] = to_copy[r][c];
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Disk Drop", "[disk_drop]") {
  // clang-format on
  Board test_board;  // NOLINT
  InitBoard(test_board);
  DropDiskToBoard(test_board, DiskType::kPlayer1, 1);
  REQUIRE(test_board.board[0][1] == DiskType::kPlayer1);
  DropDiskToBoard(test_board, DiskType::kPlayer1, 1);
  REQUIRE(test_board.board[1][1] == DiskType::kPlayer1);
  DropDiskToBoard(test_board, DiskType::kPlayer1, 1);
  DropDiskToBoard(test_board, DiskType::kPlayer1, 1);
  DropDiskToBoard(test_board, DiskType::kPlayer1, 1);
  DropDiskToBoard(test_board, DiskType::kPlayer1, 1);
  REQUIRE_THROWS(DropDiskToBoard(test_board, DiskType::kPlayer1, 1));
  REQUIRE_THROWS(DropDiskToBoard(test_board, DiskType::kPlayer1, -1));
  REQUIRE_THROWS(
      DropDiskToBoard(test_board, DiskType::kPlayer1, Board::kBoardWidth + 1));
}

TEST_CASE("Search Vertically", "[winner]") {
  DiskType test_vertical_board[kBoardHeight][kBoardWidth] = {
      {DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty},
      {DiskType::kEmpty,
       DiskType::kPlayer1,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty},
      {DiskType::kEmpty,
       DiskType::kPlayer1,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kPlayer2},
      {DiskType::kEmpty,
       DiskType::kPlayer1,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kPlayer2},
      {DiskType::kEmpty,
       DiskType::kPlayer1,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kPlayer2},
      {DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty}};

  Board test;  // NOLINT
  CopyBoard(test_vertical_board, test);

  REQUIRE(
      SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kVertical));
}

TEST_CASE("Search Horizontally", "[winner]") {
  DiskType test_horizontal_board[kBoardHeight][kBoardWidth] = {
      {DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty},
      {DiskType::kEmpty,
       DiskType::kPlayer1,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty},
      {DiskType::kEmpty,
       DiskType::kPlayer1,
       DiskType::kPlayer2,
       DiskType::kPlayer2,
       DiskType::kPlayer2,
       DiskType::kPlayer2,
       DiskType::kPlayer2},
      {DiskType::kEmpty,
       DiskType::kPlayer1,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kPlayer2},
      {DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kPlayer2},
      {DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty,
       DiskType::kEmpty}};

  Board test;  // NOLINT
  CopyBoard(test_horizontal_board, test);

  REQUIRE(
      SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(
      SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kHorizontal));
}

TEST_CASE("Search Right Diagonally", "[winner]") {
  DiskType test_right_diagonal_board[Board::kBoardHeight][Board::kBoardWidth] = {
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };

  Board test;  // NOLINT
  CopyBoard(test_right_diagonal_board, test);

  REQUIRE(
      SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kRightDiag));
}

TEST_CASE("Search Left Diagonally", "[winner]") {
  DiskType test_left_diagonal_board[Board::kBoardHeight][Board::kBoardWidth] = {
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };

  Board test;  // NOLINT
  CopyBoard(test_left_diagonal_board, test);

  REQUIRE(
      SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kLeftDiag));
}

TEST_CASE("Check for Winner", "[winner]") {
  
    DiskType source[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  Board test; // NOLINT
  CopyBoard(source, test);

  REQUIRE(CheckForWinner(test, DiskType::kPlayer2));
  REQUIRE_FALSE(CheckForWinner(test, DiskType::kPlayer1));
}

TEST_CASE("In bounds", "[bounds]") {
  REQUIRE(BoardLocationInBounds(1, 1));
  REQUIRE_FALSE(BoardLocationInBounds(-1, 1));
  REQUIRE_FALSE(BoardLocationInBounds(-1, -1));
  REQUIRE_FALSE(BoardLocationInBounds(Board::kBoardHeight, 1));
  REQUIRE_FALSE(BoardLocationInBounds(1, Board::kBoardWidth));
}

/////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "board.hpp"

int main() {
   Board b; // NOLINT
   InitBoard(b);
   /*
   DropDiskToBoard(b, DiskType::kPlayer1, 0);
   DropDiskToBoard(b, DiskType::kPlayer2, 1);
   DropDiskToBoard(b, DiskType::kPlayer1, 1);
   DropDiskToBoard(b, DiskType::kPlayer1, 2);
   DropDiskToBoard(b, DiskType::kPlayer2, 2);
   DropDiskToBoard(b, DiskType::kPlayer1, 2);
   DropDiskToBoard(b, DiskType::kPlayer2, 3);
   DropDiskToBoard(b, DiskType::kPlayer1, 3);
   DropDiskToBoard(b, DiskType::kPlayer2, 3);
   DropDiskToBoard(b, DiskType::kPlayer1, 3);
   */


  DiskType test_board[Board::kBoardHeight][Board::kBoardWidth] = {
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };

    CopyBoard(test_board, b);

   std::cout << BoardToStr(b) << std::endl;
   std::cout << std::boolalpha << CheckForWinner(b, DiskType::kPlayer1) << std::endl;
}

void CopyBoard(DiskType to_copy[Board::kBoardHeight][Board::kBoardWidth], Board& b) {
  for (int r = 0; r < Board::kBoardHeight; ++r) {
    for (int c = 0; c < Board::kBoardWidth; ++c) {
      b.board[r][c] = to_copy[r][c];
    }
  }
}
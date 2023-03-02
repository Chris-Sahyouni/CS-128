#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

enum class WinningDirection { kHorizontal, kVertical, kRightDiag, kLeftDiag };
enum class DiskType { kPlayer1 = 82, kPlayer2 = 66, kEmpty = 32 };

struct Board {
  static constexpr int kBoardWidth = 7;
  static constexpr int kBoardHeight = 6;
  DiskType board[kBoardHeight][kBoardWidth];
};

void InitBoard(Board& b);
void DropDiskToBoard(Board& b, DiskType disk, int col);
bool CheckForWinner(Board& b, DiskType disk);
bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check);
bool SearchVertical(Board& b, DiskType disk);
bool SearchHorizontal(Board& b, DiskType disk);
bool SearchRightDiagonal(Board& b, DiskType disk);
bool SearchLeftDiagonal(Board& b, DiskType disk);
bool BoardLocationInBounds(int row, int col);
bool ColumnIsFull(Board& b, int col);
void CopyBoard(DiskType to_copy[Board::kBoardHeight][Board::kBoardWidth], Board& b);

// provided
std::string BoardToStr(const Board& b);
std::string CenterStr(const std::string& str, int col_width);

#endif
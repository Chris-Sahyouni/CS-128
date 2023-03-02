#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  for (int r  = 0; r < Board::kBoardHeight; ++r) {
    for (int c = 0; c < Board::kBoardWidth; ++c) {
      b.board[r][c] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  assert(disk != DiskType::kEmpty);
  if (col < 0 || col >= Board::kBoardWidth) {
    throw std::runtime_error("Attempted disk drop to invalid column");
  }
  if (ColumnIsFull(b, col)) {
    throw std::runtime_error("Attempted disk drop to full column");
  }
  
  for (int i = 0; i < Board::kBoardHeight; ++i) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      return;
    } 
  }

}

bool ColumnIsFull(Board& b, int col) {
  for (int i = 0; i < Board::kBoardHeight; ++i) {
    if (b.board[i][col] == DiskType::kEmpty) {
      return false;
    }
  }
  return true;
}

bool BoardLocationInBounds(int row, int col) {
  return (row >= 0 && col >= 0 && row < Board::kBoardHeight && col < Board::kBoardWidth);
}

bool CheckForWinner(Board& b, DiskType disk) {
  assert(disk != DiskType::kEmpty);
  for (int i = 0; i <= 3; ++i) {
    if (SearchForWinner(b, disk, static_cast<WinningDirection>(i))) {
      return true;
    }
  }
  return false;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  assert(disk != DiskType::kEmpty);
  switch (to_check) {
    case WinningDirection::kVertical:
      return SearchVertical(b, disk);
      break;
    case WinningDirection::kHorizontal:
      return SearchHorizontal(b, disk);
      break;
    case WinningDirection::kRightDiag:
      return SearchRightDiagonal(b, disk);
      break;
    case WinningDirection::kLeftDiag:
      return SearchLeftDiagonal(b, disk);
      break;
  }
}

bool SearchVertical(Board& b, DiskType disk) {
  for (int c = 0; c < Board::kBoardWidth; ++c) {
    int count = 0;
    for (int r = 0; r < Board::kBoardHeight; ++r) {
      if (!(b.board[r][c] == disk)) {
        count = 0;
      } else {
        ++count;  
      }
      if (count == 4) {
        return true;
      }
    }
  }
  return false;
}

bool SearchHorizontal(Board& b, DiskType disk) {
  for (int r = 0; r < Board::kBoardHeight; ++r) {
    int count = 0;
    for (int c = 0; c < Board::kBoardWidth; ++c) {
      if (!(b.board[r][c] == disk)) {
        count = 0;
      } else {
        ++count;
      }
      if (count == 4) {
        return true;
      }
    }
  }
  return false;
}

bool SearchRightDiagonal(Board& b, DiskType disk) {
  int r = 2;
  int c = 1;
  while (c <= 3) {
    int count = 0;
    if (r >= 0) { 
      for (int i = 0; i + r < Board::kBoardHeight; ++i) {
        if (!(b.board[i + r][i] == disk)) {
          count = 0;
        } else {
          ++count;
        }
        if (count == 4) {
          return true;
        }
      }
      --r;
    } else {
      for (int i = 0; i + c < Board::kBoardWidth; ++i) {
        if (!(b.board[i][i + c] == disk)) {
          count = 0;
        } else {
          ++count;
        }
        if (count == 4) {
          return true;
        }
      }
      ++c;
    }
  }
  return false;
}

bool SearchLeftDiagonal(Board& b, DiskType disk) {
  int r = 2;
  int c = 1;
  while (c <= 3) {
    int count = 0;
    if (r >= 0) { 
      for (int i = 0; i + r < Board::kBoardHeight; ++i) {
        if (!(b.board[i + r][Board::kBoardWidth - i - 1] == disk)) {
          count = 0;
        } else {
          ++count;
        }
        if (count == 4) {
          return true;
        }
      }
      --r;
    } else {
      for (int i = 0; Board::kBoardHeight - i - c >= 0; ++i) {
        if (!(b.board[i][Board::kBoardWidth - c - i - 1] == disk)) {
          count = 0;
        } else {
          ++count;
        }
        if (count == 4) {
          return true;
        }
      }
      ++c;
    }
  }
  return false;
}


/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}
#include "db_table.hpp"

#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

// const unsigned int kRowGrowthRate = 2;

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) Resize();
  col_descs_.push_back(col_desc);
  for (auto& [id, row] : rows_) {
    switch (col_desc.second) {
    case DataType::kString: {
      row[col_descs_.size() - 1] = new std::string("");
      break;
    }
    case DataType::kDouble: {
      row[col_descs_.size() - 1] = new double(0.0);
      break;
    }
    case DataType::kInt: {
      row[col_descs_.size() - 1] = new int(0);
      break;
    }
    }
  }
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx < 0 || col_idx >= col_descs_.size())
    throw std::out_of_range("DeleteColumnByIdx: out of range");
  if (col_descs_.size() == 1 && !rows_.empty())
    throw std::runtime_error("DeleteColumnByIdx: one column");

  for (auto& [id, row] : rows_) {
    delete static_cast<char*>(row[col_idx]);
    for (unsigned int c = col_idx; c < col_descs_.size() - 1; ++c) {
      if (c == col_descs_.size() - 1) {
        row[c] = nullptr;
      } else {
        row[c] = row[c + 1];
      }
    }
  }
  for (unsigned int i = col_idx; i < col_descs_.size() - 1; ++i) {
    col_descs_.at(i) = col_descs_.at(i + 1);
  }
  col_descs_.pop_back();
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size())
    throw std::invalid_argument(
        "AddRow: col_data does not equal col_descs size");
  void** new_row = new void*[row_col_capacity_];

  int idx = 0;
  for (const std::string& s : col_data) {
    DataType dt = col_descs_.at(idx).second;
    switch (dt) {
    case DataType::kDouble: {
      double d = std::stod(s);
      new_row[idx] = static_cast<void*>(new double(d));
      break;
    }
    case DataType::kInt: {
      int i = std::stoi(s);
      new_row[idx] = static_cast<void*>(new int(i));
      break;
    }
    case DataType::kString: {
      new_row[idx] = static_cast<void*>(new std::string(s));
      break;
    }
    }
    ++idx;
  }
  rows_.insert({next_unique_id_, new_row});
  ++next_unique_id_;
}

void DbTable::DeleteRowById(unsigned int id) {
  if (!(rows_.contains(id))) {
    throw std::invalid_argument("DeleteRowById: id does not exist");
  }
  DeallocateRow(rows_.at(id));
  rows_.erase(id);
}

DbTable::DbTable(const DbTable& rhs):
    next_unique_id_(rhs.next_unique_id_),
    row_col_capacity_(rhs.row_col_capacity_),
    col_descs_(rhs.col_descs_) {
  for (auto [id, rhs_row] : rhs.rows_) {
    void** lhs_row = new void*[row_col_capacity_];
    for (unsigned int c = 0; c < col_descs_.size(); ++c) {
      DataType dt = col_descs_.at(c).second;
      switch (dt) {
      case DataType::kDouble: {
        double d = *static_cast<double*>(rhs_row[c]);
        lhs_row[c] = static_cast<void*>(new double(d));
        break;
      }
      case DataType::kInt: {
        int i = *static_cast<int*>(rhs_row[c]);
        lhs_row[c] = static_cast<void*>(new int(i));
        break;
      }
      case DataType::kString: {
        std::string s = *static_cast<std::string*>(rhs_row[c]);
        lhs_row[c] = static_cast<void*>(new std::string(s));
        break;
      }
      }
    }
    rows_.insert({id, lhs_row});
  }
}

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this == &rhs) return *this;
  for (auto& [id, row] : rows_) {
    DeallocateRow(row);
  }
  rows_.clear();
  for (auto [id, row] : rhs.rows_) {
    void** lhs_row = nullptr;
    lhs_row = new void*[rhs.row_col_capacity_];
    for (unsigned int c = 0; c < rhs.col_descs_.size(); ++c) {
      DataType dt = rhs.col_descs_.at(c).second;
      switch (dt) {
      case DataType::kInt: {
        int i = *static_cast<int*>(row[c]);
        lhs_row[c] = static_cast<void*>(new int(i));
        break;
      }
      case DataType::kDouble: {
        double d = *static_cast<double*>(row[c]);
        lhs_row[c] = static_cast<void*>(new double(d));
        break;
      }
      case DataType::kString: {
        std::string s = *static_cast<std::string*>(row[c]);
        lhs_row[c] = static_cast<void*>(new std::string(s));
        break;
      }
      }
    }
    rows_.insert({id, lhs_row});
  }
  col_descs_ = rhs.col_descs_;
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  return *this;
}

DbTable::~DbTable() {
  // for (unsigned int r = 0; r < rows_.size(); ++r) {
  //   DeallocateRow(rows_.at(r));
  // }
  for (auto& [id, row] : rows_) {
    DeallocateRow(row);
  }
}

std::string OSFirstLine(const DbTable& table) {
  std::string type;
  std::string to_return;
  for (unsigned int i = 0; i < table.col_descs_.size(); ++i) {
    switch (table.col_descs_.at(i).second) {
    case DataType::kDouble: {
      type = "(double)";
      break;
    }
    case DataType::kInt: {
      type = "(int)";
      break;
    }
    case DataType::kString: {
      type = "(std::string)";
      break;
    }
    }
    to_return += table.col_descs_.at(i).first;
    to_return += type;
    if (i < table.col_descs_.size() - 1) to_return += ", ";
  }
  return to_return;
}

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  os << OSFirstLine(table);
  for (auto [id, row] : table.rows_) {
    for (unsigned int c = 0; c < table.col_descs_.size(); ++c) {
      DataType dt = table.col_descs_.at(c).second;
      switch (dt) {
      case DataType::kString: {
        os << *static_cast<std::string*>(row[c]);
        break;
      }
      case DataType::kInt: {
        os << *static_cast<int*>(row[c]);
        break;
      }
      case DataType::kDouble: {
        os << *static_cast<double*>(row[c]);
        break;
      }
      }
      if (c < table.col_descs_.size() - 1) os << ", ";
    }
    if (id < table.rows_.size() - 1) {
       os << std::endl;
    }
  }
  return os;
}

void DbTable::Resize() {
  if (row_col_capacity_ == 0) ++row_col_capacity_;
  row_col_capacity_ *= 2;
  for (unsigned int r = 0; r < rows_.size(); ++r) {
    void**& row = rows_.at(r);
    CopyElements(row);
  }
}

void**& DbTable::GetRow(unsigned int row) {
  if (!rows_.contains(row)) throw std::invalid_argument("GetRow");
  return rows_.at(row);
}

void DbTable::DeallocateRow(void**& row) {
  for (unsigned int i = 0; i < col_descs_.size(); ++i) {
    DataType dt = col_descs_.at(i).second;
    switch (dt) {
    case DataType::kDouble: {
      delete static_cast<double*>(row[i]);
      break;
    }
    case DataType::kInt: {
      delete static_cast<int*>(row[i]);
      break;
    }
    case DataType::kString: {
      delete static_cast<std::string*>(row[i]);
      break;
    }
    }
  }
  delete[] row;
}

void DbTable::CopyElements(void**& row) {
  void** tmp = new void*[row_col_capacity_];
  int skip_last = 0;
  if (row[col_descs_.size() - 1] == nullptr) skip_last = 1;
  for (unsigned int col = 0; col < col_descs_.size() - skip_last; ++col) {
    DataType dt = col_descs_.at(col).second;
    switch (dt) {
    case DataType::kString: {
      std::string& name = *static_cast<std::string*>(row[col]);
      tmp[col] = static_cast<void*>(new std::string(name));
      break;
    }
    case DataType::kInt: {
      int uin = *static_cast<int*>(row[col]);
      tmp[col] = static_cast<void*>(new int(uin));
      break;
    }
    case DataType::kDouble: {
      double gpa = *static_cast<double*>(row[col]);
      tmp[col] = static_cast<void*>(new double(gpa));
      break;
    }
    }
  }
  DeallocateRow(row);
  row = tmp;
  tmp = nullptr;
}

DbTable::DbTable(bool test) {
  row_col_capacity_ = 4;
  if (test) {
    for (unsigned int r = 0; r < 4; ++r) {
      void** row = new void*[row_col_capacity_];
      for (unsigned int c = 0; c < 4; ++c) {
        row[c] = static_cast<void*>(new int(c));
      }
      rows_.insert({r, row});
      ++next_unique_id_;
    }
    for (unsigned int i = 0; i < 4; ++i)
      col_descs_.push_back({"col", DataType::kInt});
  }
}

unsigned int DbTable::GetNumRows() { return rows_.size(); }
std::map<unsigned int, void**>& DbTable::GetRows() { return rows_; }
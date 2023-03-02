#include "db.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

void Database::CreateTable(const std::string& table_name) {
  tables_.insert({table_name, new DbTable()});
}

void Database::DropTable(const std::string& table_name) {
  if (!tables_.contains(table_name)) throw std::invalid_argument("DropTable");
  delete tables_.at(table_name);
  tables_.erase(table_name);
}

DbTable& Database::GetTable(const std::string& table_name) {
  return *tables_.at(table_name);
}

Database::Database(const Database& rhs) {
  for (const auto& [name, table_ptr] : rhs.tables_) {
    tables_.insert({name, new DbTable(*table_ptr)});
  }
}

Database& Database::operator=(const Database& rhs) {
  if (&rhs == this) return *this;
  for (auto [name, table_ptr] : tables_) {
    delete table_ptr;
  }
  tables_.clear();
  for (auto [name, table_ptr] : rhs.tables_) {
    DbTable& table = *table_ptr;
    if (table.GetRows().empty()) {
      tables_.insert({name, new DbTable()});
    } else {
      tables_.insert({name, new DbTable(*table_ptr)});
    }
  }
  return *this;
}

Database::~Database() {
  for (auto& [name, table] : tables_) {
    delete table;
  }
}

// std::ostream& operator<<(std::ostream& os, const Database& db) {
//   os << "foo";
//   (void)db;
//   return os;
// }
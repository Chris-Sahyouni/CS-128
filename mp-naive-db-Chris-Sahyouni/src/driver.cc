#include <iostream>
#include <map>

#include "db.hpp"
#include "db_table.hpp"

int main() {
  DbTable dbt(true);
  std::cout << dbt;
  dbt.DeleteRowById(1);
//  std::cout << dbt;
}
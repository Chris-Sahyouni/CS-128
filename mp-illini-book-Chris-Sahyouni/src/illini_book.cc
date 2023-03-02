#include "illini_book.hpp"

#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "utilities.hpp"

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::ifstream ifs{people_fpath};
  while (!ifs.eof()) {
    std::string line;
    std::getline(ifs, line);
    std::vector<std::pair<int, std::string>> empty;
    try {
      graph_.insert({std::stoi(line), empty});
    } catch (...) {
      continue;
    }
  }
  ifs.close();

  std::ifstream ifs2{relations_fpath};
  while (!ifs2.eof()) {
    std::string line;
    std::getline(ifs2, line);
    std::vector<std::string> line_vect = utilities::Split(line, ',');
    int uin1 = 0;
    int uin2 = 0;
    try {
      uin1 = std::stoi(line_vect.at(0));
      uin2 = std::stoi(line_vect.at(1));
    } catch (...) {
      continue;
    }
    std::string relationship = line_vect.at(2);
    graph_.at(uin1).push_back({uin2, relationship});
    graph_.at(uin2).push_back({uin1, relationship});
  }
  ifs2.close();
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::vector<int> to_return;
  std::set<int> visited;
  std::set<int> seen;
  std::queue<int> queue;
  std::map<int, int> uin_dist;
  uin_dist.insert({uin, 0});
  queue.push(uin);
  while (!queue.empty()) {
    int curr = queue.front();
    if (uin_dist.at(curr) >= n) break;
    visited.insert(curr);
    for (auto [uinitr, relation] : graph_.at(curr)) {
      if (!visited.contains(uinitr) && !seen.contains(uinitr)) {

          uin_dist.insert({uinitr, uin_dist.at(curr) + 1});
        
        if (uin_dist.at(uinitr) == n) to_return.push_back(uinitr);

          queue.push(uinitr);
          seen.insert(uinitr);
        
      }
    }
    queue.pop();
  }

  return to_return;
}

size_t IlliniBook::CountGroups() const {
  size_t count = 0;
  std::set<int> visited;
  for (auto [uin, vect] : graph_) {
    if (!visited.contains(uin)) {
      ++count;
      CountGroupsRecursor(uin, visited);
    }
  }
  return count;
}

void IlliniBook::CountGroupsRecursor(int uin, std::set<int>& visited) const {
  visited.insert(uin);
  std::vector<std::pair<int, std::string>> neighbors = graph_.at(uin);
  for (auto [uin_itr, relation] : neighbors) {
    if (!visited.contains(uin_itr)) {
      CountGroupsRecursor(uin_itr, visited);
    }
  }
}

size_t IlliniBook::CountGroups(const std::string& relationship) const {
  size_t count = 0;
  std::set<int> visited;
  for (auto [uin, vect] : graph_) {
    if (!visited.contains(uin)) {
      ++count;
      CountGroupsRecursor(uin, visited, relationship);
    }
  }
  return count;
}

void IlliniBook::CountGroupsRecursor(int uin,
                                     std::set<int>& visited,
                                     const std::string& relationship) const {
  visited.insert(uin);
  std::vector<std::pair<int, std::string>> neighbors = graph_.at(uin);
  for (auto [uin_itr, relation] : neighbors) {
    if (!visited.contains(uin_itr) && relation == relationship) {
      CountGroupsRecursor(uin_itr, visited, relationship);
    }
  }
}

size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  size_t count = 0;
  std::set<int> visited;
  for (auto [uin, vect] : graph_) {
    if (!visited.contains(uin)) {
      ++count;
      CountGroupsRecursor(uin, visited, relationships);
    }
  }
  return count;
}

void IlliniBook::CountGroupsRecursor(
    int uin,
    std::set<int>& visited,
    const std::vector<std::string>& relationships) const {
  visited.insert(uin);
  std::vector<std::pair<int, std::string>> neighbors = graph_.at(uin);
  for (auto [uin_itr, relation] : neighbors) {
    if (!visited.contains(uin_itr) && VectContains(relation, relationships)) {
      CountGroupsRecursor(uin_itr, visited, relationships);
    }
  }
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  std::set<int> visited;
  std::set<int> connected_elements = GetConnectedComponent(uin_1, visited);
  return connected_elements.contains(uin_2);
}

bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  std::set<int> visited;
  std::set<int> connected_elements =
      GetConnectedByRelationship(uin_1, relationship, visited);
  return connected_elements.contains(uin_2);
}

bool IlliniBook::AreInGraph(int uin_1, int uin_2) const {
  bool first_found = false;
  bool second_found = false;
  for (auto [uin, vect] : graph_) {
    if (uin == uin_1) first_found = true;
    if (uin == uin_2) second_found = true;
  }
  return first_found && second_found;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  std::set<int> visited;
  std::queue<int> queue;
  queue.push(uin_1);
  std::map<int, int> uin_dist;
  uin_dist.insert({uin_1, 0});
  visited.clear();
  while (!queue.empty()) {
    int curr = queue.front();
    visited.insert(curr);
    for (auto [uin, relation] : graph_.at(curr)) {
      uin_dist.insert({uin, uin_dist.at(curr) + 1});
      if (uin == uin_2) return uin_dist.at(uin);
      if (!visited.contains(uin)) {
        queue.push(uin);
      }
    }
    queue.pop();
  }
  return -1;
}

int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  std::set<int> visited;
  std::queue<int> queue;
  queue.push(uin_1);
  std::map<int, int> uin_dist;
  for (auto uin : GetConnectedByRelationship(uin_1, relationship, visited))
    uin_dist.insert({uin, 0});
  visited.clear();
  while (!queue.empty()) {
    int curr = queue.front();
    visited.insert(curr);
    for (auto [uin, relation] : graph_.at(curr)) {
      if (relation == relationship) {
        uin_dist.at(uin) = uin_dist.at(curr) + 1;
        if (uin == uin_2) return uin_dist.at(uin);
        if (!visited.contains(uin)) {
          queue.push(uin);
        }
      }
    }
    queue.pop();
  }
  return -1;
}

std::set<int> IlliniBook::GetConnectedComponent(int uin,
                                                std::set<int>& visited) const {
  visited.insert(uin);
  std::vector<std::pair<int, std::string>> neighbors = graph_.at(uin);
  for (const auto& [uin, relation] : neighbors) {
    if (!visited.contains(uin)) {
      std::set<int> to_add = GetConnectedComponent(uin, visited);
      visited = AddTwoSets(visited, to_add);
    }
  }
  return visited;
}

std::set<int> IlliniBook::GetConnectedByRelationship(
    int uin, const std::string& relationship, std::set<int>& visited) const {
  visited.insert(uin);
  std::vector<std::pair<int, std::string>> neighbors = graph_.at(uin);
  for (const auto& [uin, relation] : neighbors) {
    if (!visited.contains(uin) && relation == relationship) {
      std::set<int> to_add =
          GetConnectedByRelationship(uin, relationship, visited);
      visited = AddTwoSets(visited, to_add);
    }
  }
  return visited;
}

std::set<int> IlliniBook::AddTwoSets(std::set<int>& first,
                                     std::set<int>& second) const {
  for (auto i : second) {
    first.insert(i);
  }
  return first;
}

bool IlliniBook::VectContains(
    const std::string& relationship,
    const std::vector<std::string>& relationships) const {
  for (const auto& str : relationships) {
    if (str == relationship) return true;
  }
  return false;
}


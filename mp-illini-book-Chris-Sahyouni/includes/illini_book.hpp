#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <string>
#include <vector>
#include <map>
#include <set>

class IlliniBook {
public:
  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath);
  IlliniBook(const IlliniBook &rhs) = delete;
  IlliniBook &operator=(const IlliniBook &rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;

// for testing
  std::map<int, std::vector<std::pair<int, std::string>>> GetGraph() const {return graph_;}

  std::set<int> GetConnectedComponent(int uin, std::set<int>& visited) const;
  std::set<int> GetConnectedByRelationship(int uin, const std::string& relationship, std::set<int>& visited) const;
  void CountGroupsRecursor(int uin, std::set<int>& visited) const;
  void CountGroupsRecursor(int uin, std::set<int>& visited, const std::string& relationship) const;
  void CountGroupsRecursor(int uin, std::set<int>& visited, const std::vector<std::string>& relationships) const;

private:
// maps from a uin, to a vector of pairs
// the types of which are the second uin, and the type of relationship
  std::map<int, std::vector<std::pair<int, std::string>>> graph_;

  std::set<int> AddTwoSets(std::set<int>& first, std::set<int>& second) const;
  bool VectContains(const std::string& relationship, const std::vector<std::string>& relationships) const;
  bool AreInGraph(int uin_1, int uin_2) const;
};

#endif

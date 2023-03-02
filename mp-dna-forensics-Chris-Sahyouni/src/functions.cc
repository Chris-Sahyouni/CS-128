#include "functions.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::string FindMatch(std::string dna_sequence, std::string csv_file) {
  std::vector<std::string> strs = ReadSTRsFromCSV(csv_file);
  std::map<std::string, int> str_to_longest_run =
      MapLongestRuns(dna_sequence, strs);

  bool is_first = true;
  std::ifstream ifs{csv_file};
  for (std::string line; std::getline(ifs, line); line = "") {
    if (is_first) {
      is_first = false;
      continue;
    }
    std::vector<std::string> line_vect = utilities::GetSubstrs(line, ',');
    bool is_match = true;
    // loop through the line vector
    for (unsigned int i = 1; i < line_vect.size(); ++i) {
      if (!is_match) {
        continue;
      }
      int lines_longest_str = std::stoi(line_vect.at(i));
      int dna_sequences_longest_str = str_to_longest_run.at(strs.at(i));
      if (!(lines_longest_str == dna_sequences_longest_str)) {
        is_match = false;
        continue;
      }
    }
    if (is_match) {
      return line_vect.at(0);
    }
  }
  return "No Match";
}

std::vector<std::string> ReadSTRsFromCSV(std::string csv_file) {
  std::ifstream ifs{csv_file};
  if (!ifs.is_open()) {
    std::cout << "Failed to read from csv file" << std::endl;
  }
  std::string first_line;
  std::getline(ifs, first_line);
  return utilities::GetSubstrs(first_line, ',');
}

std::map<std::string, int> MapLongestRuns(std::string dna_sequence,
                                          std::vector<std::string> strs) {
  std::map<std::string, int> str_longest_runs;
  for (unsigned int i = 1; i < strs.size(); ++i) {
    std::string current_str = strs.at(i);
    int longest_run = GetLongestRun(current_str, dna_sequence);
    str_longest_runs.insert({current_str, longest_run});
  }
  return str_longest_runs;
}

int GetLongestRun(std::string str, std::string dna_sequence) {
  int count = 0;
  int max = 0;
  for (unsigned int i = 0; i <= dna_sequence.length() - str.length(); ++i) {
    std::string current_sub = dna_sequence.substr(i, str.length());
    if (str == current_sub) {
      count++;
      i += str.length() - 1;
    } else {
      if (count > max) {
        max = count;
      }
      count = 0;
    }
    if (i > dna_sequence.length() - str.length()) {
      if (count > max) {
        max = count;
      }
    }
  }
  return max;
}

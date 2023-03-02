#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <map>
#include <string>
#include <vector>

#include "utilities.hpp"

std::string FindMatch(std::string dna_sequence, std::string csv_file);
std::vector<std::string> ReadSTRsFromCSV(std::string csv_file);
std::map<std::string, int> MapLongestRuns(std::string dna_sequence, std::vector<std::string> strs);
int GetLongestRun(std::string str, std::string dna_sequence);
bool CheckLineForMatch (std::vector<std::string> line_vect);

#endif
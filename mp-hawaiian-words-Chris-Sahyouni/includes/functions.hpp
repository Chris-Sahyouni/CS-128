#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <map>
#include <string>

// Your function declarations should go in this header file.

std::string ConvertToPhonetic(std::string str);
void MapConsonants();
void MapVowels();
std::string GetPhoneticFromVowelPair(std::string vowel_pair);
std::string GetPhonetic(char c, std::map<char, std::string> map);
std::string GetPhonetic(std::string s, std::map<std::string, std::string> map);
bool IsAllowed(char c);
bool IsVowel(char c);
bool IsConsonant(char c);
bool IsWPair(std::string pair);
std::string MakeLowerCase(std::string str);
std::string RemoveUnnecessaryDashes(std::string str);

#endif
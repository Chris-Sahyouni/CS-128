#include "functions.hpp"

#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Your function definitions should go in this source file.

std::vector<char> allowed_chars = {
    'a', 'e', 'i', 'o', 'u', 'p', 'k', 'h', 'l', 'm', 'n', 'w', '\'', ' '};

// ' and space are treated as consonants because they can be treated the same
std::vector<char> consonants = {'p', 'k', 'h', 'l', 'm', 'n', 'w', '\'', ' '};
std::vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};

std::map<char, std::string> consonant_map;
std::map<char, std::string> vowel_map;
std::map<std::string, std::string> vowel_pairs;

// returning an empty string indicates a not allowed character
std::string ConvertToPhonetic(std::string str) {
  MapConsonants();
  MapVowels();
  std::string to_return;
  for (unsigned int i = 0; i < str.length(); ++i) {
    char current = tolower(str.at(i));
    std::string current_pair;
    if (i != str.length() - 1) {
      current_pair = MakeLowerCase(str.substr(i, 2));
    }
    if (!(IsAllowed(current))) {
      std::cout << str
                << " contains a character not a part of the Hawaiian language."
                << std::endl;
      return "";
    }
    if (IsVowel(current)) {
      if (i < str.length() - 1) {
        if (IsWPair(current_pair)) {
          to_return += GetPhonetic(current_pair.at(0), vowel_map);
          to_return.push_back('-');
          to_return.push_back('v');
          ++i;
        } else if (IsVowel(current_pair.at(1))) {
          to_return += GetPhoneticFromVowelPair(current_pair);
          to_return.push_back('-');
          ++i;
        } else {
          to_return += GetPhonetic(current, vowel_map);
          to_return.push_back('-');
        }
      } else {
        to_return += GetPhonetic(current, vowel_map);
      }
    } else if (IsConsonant(current)) {
      to_return += GetPhonetic(current, consonant_map);
    }
  }
  return RemoveUnnecessaryDashes(to_return);
}

// these return the phonetic for a given character or pair of characters
std::string GetPhonetic(char c, std::map<char, std::string> map) {
  return map.at(c);
}
std::string GetPhonetic(std::string s, std::map<std::string, std::string> map) {
  return map.at(s);
}

// maps all the consonants to their pronunciations
void MapConsonants() {
  for (char c : consonants) {
    std::string s;
    s.push_back(c);
    consonant_map.insert({c, s});
  }
}

// maps all vowels to their pronunciations
void MapVowels() {
  for (char c : vowels) {
    switch (c) {
    // fall through is intended here because all these values should map to
    // themselves plus 'h'
    case 'a':
    case 'e':
    case 'o': {
      std::string phonetic_vowel;
      phonetic_vowel.push_back(c);
      phonetic_vowel.push_back('h');
      vowel_map.insert({c, phonetic_vowel});
    }
    case 'i': {
      vowel_map.insert({c, "ee"});
    }
    case 'u': {
      vowel_map.insert({c, "oo"});
    }
    }
  }
}

// returns the pronunciation for a pair of vowels
std::string GetPhoneticFromVowelPair(std::string vowel_pair) {
  if (vowel_pair == "ai" || vowel_pair == "ae") {
    return "eye";
  }
  if (vowel_pair == "ao" || vowel_pair == "au" || vowel_pair == "ou") {
    return "ow";
  }
  if (vowel_pair == "ei") {
    return "ay";
  }
  if (vowel_pair == "eu") {
    return "eh-hoo";
  }
  if (vowel_pair == "iu") {
    return "ew";
  }
  if (vowel_pair == "oi") {
    return "oy";
  }
  if (vowel_pair == "ei") {
    return "ay";
  }
  if (vowel_pair == "ui") {
    return "ooey";
  }
  return GetPhonetic(vowel_pair.at(0), vowel_map) + '-' +
         GetPhonetic(vowel_pair.at(1), vowel_map);
}

// checks if the character is allowed
bool IsAllowed(char c) {
  for (char i : allowed_chars) {
    if (i == c) {
      return true;
    }
  }
  return false;
}

// checks if the character is a vowel
bool IsVowel(char c) {
  for (char i : vowels) {
    if (i == c) {
      return true;
    }
  }
  return false;
}

// checks if the character is a consonant
bool IsConsonant(char c) {
  for (char i : consonants) {
    if (i == c) {
      return true;
    }
  }
  return false;
}

// check if its one of the hawaiian w pairs
bool IsWPair(std::string pair) {
  if (pair.at(0) == 'i' || pair.at(0) == 'e') {
    if (pair.at(1) == 'w') {
      return true;
    }
  }
  return false;
}

// makes the current pair lowercase to avoid bugs
std::string MakeLowerCase(std::string str) {
  std::string result;
  for (unsigned int i = 0; i < str.length(); ++i) {
    result.push_back(tolower(str.at(i)));
  }
  return result;
}

// remvoes unnecessary dashes from the final string
std::string RemoveUnnecessaryDashes(std::string str) {
  std::string result;
  for (unsigned int i = 0; i < str.length(); ++i) {
    if (i < str.length() - 1) {
      std::string current_pair = str.substr(i, 2);
      if (current_pair == "- " || current_pair == "-\'") {
        continue;
      }
    }
    result.push_back(str.at(i));
  }
  if (str.back() == '-') {
    return result.substr(0, result.length() - 1);
  }
  return result;
}
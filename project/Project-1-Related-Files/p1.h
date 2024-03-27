#ifndef __P1_H__
#define __P1_H__

#include <string>

bool isPalindrome(const std::string& str);
// EFFECTS: check if a given string is a palindrome.
// If the given string is a palindrome, returns true.
// Otherwise, returns false.

std::string findLongestSubPalindrome(const std::string& str);
// EFFECTS: return the longest sub-palindrome within a given string.
// If multiple longest sub-palindromes are found, return the first one.

#endif

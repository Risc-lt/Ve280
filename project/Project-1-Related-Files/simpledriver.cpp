#include "p1.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
  // Read input from the user and print the result
  string input;
  cin >> input;

  // Judge if the input is a palindrome
  cout << input << (isPalindrome(input) ? " is a palindrome" : " is not a palindrome") << endl;
  // Find the longest sub-palindrome
  cout << "The longest sub-palindrome is: " << findLongestSubPalindrome(input) << endl;

  return 0;
}

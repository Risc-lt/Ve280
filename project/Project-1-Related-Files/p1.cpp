#include <string>
using namespace std;

bool isPalindrome(const string& str) {
    int n = str.size();
    for (int i = 0; i < n / 2; i++) {
        if (str[i] != str[n - i - 1]) {
            return false;
        }
    }
    return true;
}

string findLongestSubPalindrome(const string& str) {
    int n = str.size();
    int maxLen = 0;
    int start = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int len = j - i + 1;
            if (len > maxLen && isPalindrome(str.substr(i, len))) {
                maxLen = len;
                start = i;
            }
        }
    }
    return str.substr(start, maxLen);
}
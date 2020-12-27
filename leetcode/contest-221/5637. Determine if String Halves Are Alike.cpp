#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool isV(char ch) {
        string s = "aeiouAEIOU";
        for (int i = 0; i < s.length(); i++) {
            if (ch == s[i]) return true;
        }
        return false;
    }
    bool halvesAreAlike(string s) {
        int n = s.length();
        int x = 0, y = 0;
        for (int i = 0, j = n / 2; i < n / 2; i++, j++) {
            x += isV(s[i]);
            y += isV(s[j]);
        }
        return x == y;
    }
};
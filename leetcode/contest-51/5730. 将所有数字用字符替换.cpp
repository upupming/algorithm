#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    string replaceDigits(string s) {
        for (int i = 0; i < s.length(); i++) {
            if (i % 2) {
                s[i] = s[i - 1] + (s[i] - '0');
            }
        }
        return s;
    }
};

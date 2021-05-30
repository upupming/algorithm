#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int getVal(string s) {
        int ans = 0;
        for (auto ch : s) {
            ans = ans * 10 + ch - 'a';
        }
        return ans;
    }
    bool isSumEqual(string firstWord, string secondWord, string targetWord) {
        return getVal(firstWord) + getVal(secondWord) == getVal(targetWord);
    }
};

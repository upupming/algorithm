#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int longestBeautifulSubstring(string word) {
        int n = word.length();
        int ans = 0;
        for (int i = 0; i < n;) {
            unordered_set<char> s;
            s.insert(word[i]);
            int j = i + 1;
            for (; j < n; j++) {
                if (word[j] < word[j - 1]) break;
                s.insert(word[j]);
            }
            if (s.size() == 5) {
                ans = max(ans, j - 1 - i + 1);
            }
            i = j;
        }
        return ans;
    }
};

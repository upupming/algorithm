#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool makeEqual(vector<string>& words) {
        int cnt[26] = {0};
        for (auto& w : words) {
            for (auto ch : w) cnt[ch - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % words.size() != 0) return false;
        }
        return true;
    }
};

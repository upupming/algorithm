#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        unordered_set<char> s;
        for (char ch : allowed) s.insert(ch);
        int ans = 0;
        for (auto word : words) {
            bool ok = true;
            for (auto ch : word) {
                if (!s.count(ch)) {
                    ok = false;
                    break;
                }
            }
            if (ok) ans++;
        }
        return ans;
    }
};
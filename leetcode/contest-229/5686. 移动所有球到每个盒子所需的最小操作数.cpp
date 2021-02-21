#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<int> minOperations(string b) {
        unordered_set<int> s;
        for (int i = 0; i < b.length(); i++) {
            if (b[i] == '1') s.insert(i);
        }
        vector<int> ans(b.length(), 0);
        for (int i = 0; i < ans.size(); i++) {
            for (auto &t : s) {
                ans[i] += abs(t - i);
            }
        }
        return ans;
    }
};

#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {
        int ans = 0, idx = 0;
        if (ruleKey == "color")
            idx = 1;
        else if (ruleKey == "name")
            idx = 2;
        for (auto& item : items) {
            if (item[idx] == ruleValue) ans++;
        }
        return ans;
    }
};

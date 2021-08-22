#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    set<string> s;
    int n;
    string ans;
    void dfs(string cur) {
        if (ans.length()) return;
        if (cur.length() == n) {
            if (!s.count(cur)) ans = cur;
            return;
        }
        dfs(cur + '0');
        dfs(cur + '1');
    }
    string findDifferentBinaryString(vector<string>& nums) {
        n = nums[0].length();
        s = set<string>(nums.begin(), nums.end());
        dfs("");
        return ans;
    }
};

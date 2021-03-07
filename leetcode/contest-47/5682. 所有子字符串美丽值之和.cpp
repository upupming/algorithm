#include <bits/stdc++.h>
using namespace std;

class Solution {
    int cal(unordered_map<char, int>& mp) {
        int minCnt = INT_MAX, maxCnt = INT_MIN;
        for (auto& p : mp) {
            minCnt = min(minCnt, p.second);
            maxCnt = max(maxCnt, p.second);
        }
        return maxCnt - minCnt;
    }

   public:
    int beautySum(string s) {
        int n = s.length();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            unordered_map<char, int> mp;
            for (int len = 1; i + len - 1 < n; len++) {
                int j = i + len - 1;
                mp[s[j]]++;
                ans += cal(mp);
            }
        }

        return ans;
    }
};

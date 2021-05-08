#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int countGoodRectangles(vector<vector<int>>& rectangles) {
        vector<int> v;
        int maxLen = 0, ans = 0;
        for (auto& x : rectangles) v.push_back(min(x[0], x[1])), maxLen = max(maxLen, v.back());

        for (auto a : v) {
            if (a == maxLen) ans++;
        }
        return ans;
    }
};

#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int addRungs(vector<int>& rungs, int dist) {
        int ans = 0;
        rungs.insert(rungs.begin(), 0);
        for (int i = 0; i + 1 < rungs.size(); i++) {
            ans += (rungs[i + 1] - rungs[i] - 1) / dist;
        }
        return ans;
    }
};

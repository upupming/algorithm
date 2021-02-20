#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool canChoose(vector<vector<int>>& g, vector<int>& nums) {
        int n = g.size(), m = nums.size();

        for (int i = 0, j = 0; i < n; i++) {
            bool ok = false;
            // 匹配第 i 个数组
            for (int k = 0; k < g[i].size() && j < m;) {
                if (g[i][k] == nums[j]) {
                    k++, j++;
                    if (k == g[i].size()) {
                        // cout << k << " " << g[i][k] << " " << j << " " << nums[j] << endl;
                        ok = true;
                        break;
                    }
                } else {
                    if (k == 0) j++;
                    k = 0;
                }
                // cout << i << " " << k << " " << j << endl;
                // cout << g[i][k] << " " << nums[j] << endl;
            }
            // cout << i << ", " << j << " " << ok << endl;
            if (!ok) return false;
        }
        return true;
    }
};

#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
        int mi_sum = 0, m = mat.size(), n = mat[0].size();
        for (int i = 0; i < m; i++) {
            int mi = INT_MAX;
            for (int j = 0; j < n; j++) {
                mi = min(mi, mat[i][j]);
            }
            mi_sum += mi;
        }
        if (mi_sum > target) return mi_sum - target;
        unordered_set<int> nums = {0};
        for (int i = 0; i < m; i++) {
            unordered_set<int> nums1;
            for (int j = 0; j < n; j++) {
                for (auto& x : nums) {
                    if (x + mat[i][j] <= 2 * target - mi_sum) {
                        nums1.insert(x + mat[i][j]);
                    }
                }
            }
            swap(nums, nums1);
        }
        int ans = INT_MAX;
        for (auto& x : nums) ans = min(ans, abs(x - target));
        return ans;
    }
};

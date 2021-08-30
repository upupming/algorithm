#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int minimumDifference(vector<int>& nums, int k) {
        int ans = INT_MAX;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i + k - 1 < n; i++) {
            ans = min(ans, nums[i + k - 1] - nums[i]);
        }
        return ans;
    }
};

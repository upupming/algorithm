#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i] <= nums[i - 1]) {
                ans += (nums[i - 1] + 1) - nums[i];
                nums[i] = nums[i - 1] + 1;
            }
        }
        return ans;
    }
};

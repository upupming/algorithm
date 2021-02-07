#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> sum(n + 1);
        // sum[0] = 0
        int maxVal = 0, minVal = 0;
        for (int i = 1; i <= n; i++) {
            sum[i] = nums[i - 1] + sum[i - 1];
            maxVal = max(maxVal, sum[i]);
            minVal = min(minVal, sum[i]);
        }
        return abs(maxVal - minVal);
    }
};
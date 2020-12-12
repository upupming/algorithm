#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 0), sum(n + 1, 0);
        // 前缀和
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
        for (int i = 0; i < n; i++) {
            // cout << i << " " << nums[i] << " " << sum[i] << " " << sum[n] << endl;
            // left
            ans[i] += nums[i] * i - sum[i];
            // right
            ans[i] += sum[n] - sum[i + 1] - nums[i] * (n - i - 1);
        }
        return ans;
    }
};
#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        vector<int> sum(n + 1, 0);
        for (int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];

        map<int, int> mp;
        int l = 0, r = 0;
        int ans = nums[0];

        while (r < n) {
            if (mp.count(nums[r])) {
                int i = mp[nums[r]];
                l = max(l, i + 1);
            }
            // cout << l << " " << r << endl;
            ans = max(ans, sum[r + 1] - sum[l]);
            mp[nums[r]] = r;
            r++;
        }
        // cout << endl;
        return ans;
    }
};
#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    long long minCost(vector<int>& nums, vector<int>& cost) {
        vector<int> idx;
        int n = nums.size();
        for (int i = 0; i < n; i++) idx.push_back(i);
        sort(idx.begin(), idx.end(), [&nums, &cost](int i, int j) {
            return nums[i] < nums[j];
        });
        long long s = 0, cl = cost[idx[0]], cr = 0;
        for (int i = 1; i < n; i++) {
            s += (long long)(nums[idx[i]] - nums[idx[0]]) * (long long)cost[idx[i]];
            cr += cost[idx[i]];
        }
        long long ans = s;
        for (int i = 1; i < n; i++) {
            s -= (long long)(nums[idx[i]] - nums[idx[i - 1]]) * cr;
            s += (long long)(nums[idx[i]] - nums[idx[i - 1]]) * cl;
            cl += cost[idx[i]];
            cr -= cost[idx[i]];
            ans = min(ans, s);
        }
        return ans;
    }
};

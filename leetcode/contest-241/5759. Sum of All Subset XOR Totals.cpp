#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int subsetXORSum(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for (int i = 1; i < 1 << n; i++) {
            int x = 0;
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) {
                    x ^= nums[j];
                }
            }
            ans += x;
        }
        return ans;
    }
};

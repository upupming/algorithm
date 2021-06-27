#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int maxProductDifference(vector<int>& nums) {
        int n = nums.size();
        vector<int> idx(nums.size());
        for (int i = 0; i < idx.size(); i++) {
            idx[i] = i;
        }
        sort(idx.begin(), idx.end(), [&nums](auto i, auto j) {
            return nums[i] < nums[j];
        });
        int w = idx[n - 1], x = idx[n - 2];
        int y = idx[0], z = idx[1];
        return nums[w] * nums[x] - nums[y] * nums[z];
    }
};

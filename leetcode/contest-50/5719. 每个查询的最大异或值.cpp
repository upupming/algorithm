#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        int maxVal = (1 << maximumBit) - 1;

        int sum = 0;
        for (auto& a : nums) {
            sum ^= a;
        }
        vector<int> ans;
        do {
            ans.push_back(~sum & maxVal);
            sum ^= nums[nums.size() - 1];
            nums.pop_back();
        } while (nums.size());
        return ans;
    }
};

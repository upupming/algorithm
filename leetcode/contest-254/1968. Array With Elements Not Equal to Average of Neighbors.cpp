#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<int> rearrangeArray(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> ans;
        int n = nums.size();
        for (int i = 0, j = n - 1; i <= j; i++, j--) {
            if (i < j) {
                ans.push_back(nums[i]);
                ans.push_back(nums[j]);
            } else if (i == j) {
                ans.push_back(nums[i]);
            }
        }
        return ans;
    }
};

#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<int> getConcatenation(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans = nums;
        for (int i = 0; i < n; i++) {
            ans.push_back(nums[i]);
        }
        return ans;
    }
};

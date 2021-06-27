#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool ok(vector<int> nums) {
        for (int i = 0; i < nums.size() - 1; i++) {
            if (!(nums[i] < nums[i + 1])) return false;
        }
        return true;
    }
    bool canBeIncreasing(vector<int>& nums) {
        if (ok(nums)) return true;
        for (int i = 0; i < nums.size(); i++) {
            auto t = nums;
            t.erase(t.begin() + i);
            if (ok(t)) return true;
        }
        return false;
    }
};

#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    string kthLargestNumber(vector<string> &nums, int k) {
        sort(nums.begin(), nums.end(), [](string &a, string &b) {
            if (a.length() == b.length()) {
                return a > b;
            }
            return a.length() > b.length();
        });
        return nums[k - 1];
    }
};

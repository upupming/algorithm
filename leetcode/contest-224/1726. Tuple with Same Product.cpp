#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int tupleSameProduct(vector<int>& nums) {
        map<int, int> cnt;

        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                cnt[nums[i] * nums[j]]++;
            }
        }

        int ans = 0;
        for (auto& [a, b] : cnt) {
            ans += b * (b - 1) / 2;
        }
        ans *= 8;
        return ans;
    }
};

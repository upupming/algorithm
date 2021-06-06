#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
class Solution {
   public:
    int reductionOperations(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ans = 0;
        for (int i = 0, j, g = 0; i < nums.size(); g++) {
            j = i;
            while (j < nums.size() && nums[i] == nums[j]) j++;
            ans += g * (j - i);
            i = j;
        }
        return ans;
    }
};

#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int sign(int a) {
        if (a == 0) return 0;
        if (a > 0) return 1;
        return -1;
    }
    int arraySign(vector<int>& nums) {
        int ans = 1;
        for (auto a : nums) {
            ans *= sign(a);
        }
        return ans;
    }
};

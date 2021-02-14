/*
二分最后的答案，计算每个求需要的划分次数，是否超过 maxOperations
经典的将计算问题转化为判定问题

假设原来的球的个数为 x，要变成 y，最终结果至少需要 ceil(x/y) 个数，这些数分别是 floor(x/y) 个 y 以及如果 x/y 不整的话有一个余数。也就是说需要 ceil(x/y) -1 次操作。
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    bool valid(int mid, vector<int>& nums, int m) {
        int ans = 0;
        for (auto& num : nums) {
            ans += (num + mid - 1) / mid - 1;
        }
        return ans <= m;
    }
    int minimumSize(vector<int>& nums, int m) {
        int n = nums.size();
        int l = 1, r = 1e9 + 10;
        while (l < r) {
            int mid = l + r >> 1;
            if (valid(mid, nums, m))
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }
};
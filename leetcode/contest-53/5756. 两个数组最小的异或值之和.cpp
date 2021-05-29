#include <bits/stdc++.h>
using namespace std;
/*
数据范围 n=14: 状压 DP
暴力：nums2 的全排列，优化成 2^n 的状压 DP
位置 i: 关心前面用了哪些数，前面的和是多少，并不关心前面的顺序，只关心前面的最小的和，因此可以将阶乘优化成 2^n
f[i]: 二进制状态 i 下前面最小的和是多少
之前周赛有个题目和这个完全一样的
如何计算 f[i]，枚举每一个数和位 j 配对，从子状态 f[i ^ (1 << j)] 转移

蓝书《最短哈密顿路径》
*/
class Solution {
   public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> f(1 << n, 1e9);
        f[0] = 0;
        for (int i = 1; i < 1 << n; i++) {
            int s = 0;
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) s++;
            }
            for (int j = 0; j < n; j++) {
                // nums2 里面的第 j 个和 nums1[s-1] 配对
                if (i >> j & 1)
                    f[i] = min(f[i], f[i ^ (1 << j)] + (nums2[j] ^ nums1[s - 1]));
            }
        }
        return f[(1 << n) - 1];
    }
};

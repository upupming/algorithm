#include <bits/stdc++.h>
using namespace std;
/*
每个人都要让 自己-对方 最大化
双方都足够聪明，博弈论就是求最好的最坏值
总和总是不变的，需要求一下前缀和
每个状态由当前数组长度唯一确定，不同状态总数为 n
比赛的时候写的是 dfs，所以优化就懵了
写 dp 的话，优化是非常明显的
*/
class Solution {
   public:
    int naive(vector<int>& stones) {
        int n = stones.size();
        vector<int> sum(n + 1), f(n + 1, INT_MIN);
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + stones[i - 1];
        }
        for (int i = n - 1; i >= 1; i--) {
            for (int j = i + 1; j <= n; j++) {
                if (j == n)
                    f[i] = max(f[i], sum[n]);
                else
                    f[i] = max(f[i], sum[j] - f[j]);
            }
        }
        return f[1];
    }
    int optimized(vector<int>& stones) {
        int n = stones.size();
        vector<int> sum(n + 1), f(n + 1, INT_MIN), g(n + 1, INT_MIN);
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + stones[i - 1];
        }
        for (int i = n - 1; i >= 1; i--) {
            f[i] = max(f[i], sum[n]);
            f[i] = max(f[i], g[i + 1]);
            g[i] = max(g[i + 1], sum[i] - f[i]);
        }
        return f[1];
    }
    int stoneGameVIII(vector<int>& stones) {
        return optimized(stones);
    }
};

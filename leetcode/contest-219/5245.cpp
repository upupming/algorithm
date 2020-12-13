#include <bits/stdc++.h>
using namespace std;

/*
最优解一定满足两个性质：
1. 长宽高排序之后答案不变
2. 答案就是排序之后每个长方体最大值之和（可以构成单调子序列的那些长方体）
*/

class Solution {
   public:
    int maxHeight(vector<vector<int>>& cuboids) {
        int n = cuboids.size();
        // 一定要用引用
        for (auto& c : cuboids) {
            sort(c.begin(), c.end());
        }
        sort(cuboids.begin(), cuboids.end(), greater<vector<int>>());

        vector<int> f(n);
        int ans = 0;
        // 最长单调下降子序列
        for (int i = 0; i < n; i++) {
            f[i] = cuboids[i][2];
            for (int j = 0; j < i; j++) {
                if (cuboids[i][0] <= cuboids[j][0] &&
                    cuboids[i][1] <= cuboids[j][1] &&
                    cuboids[i][2] <= cuboids[j][2])
                    f[i] = max(f[i], f[j] + cuboids[i][2]);
            }
            ans = max(ans, f[i]);
        }
        return ans;
    }
};
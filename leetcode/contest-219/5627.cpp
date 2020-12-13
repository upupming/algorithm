#include <bits/stdc++.h>
using namespace std;
/*
f[i][j]: 当前区间是 [i, j] 的话，先手 - 后手的最大分值
*/
class Solution {
   public:
    int stoneGameVII(vector<int>& stones) {
        int n = stones.size();
        vector<int> sum(n + 1, 0);
        for (int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + stones[i - 1];
        vector<vector<int>> f(n, vector<int>(n + 1, 0));
        for (int len = 2; len <= n; len++) {
            // y 总比较有经验，有前缀和的时候 i 都从 1 开始取
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (j > 0) {
                    f[i][j] = max(
                        f[i][j],
                        sum[j] - sum[i] - f[i][j - 1]);
                }

                if (i < n - 1) {
                    f[i][j] = max(
                        f[i][j],
                        sum[j + 1] - sum[i + 1] - f[i + 1][j]);
                }
                // cout << "f[i][j - 1]: " << f[i][j - 1] << endl;

                // cout << i << " " << j << " " << f[i][j] << endl;
            }
        }
        return f[0][n - 1];
    }
};
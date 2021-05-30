#include <bits/stdc++.h>
using namespace std;
/*
f[i][j] 表示前 i 辆车，操作 j 次的最小时间，有浮点数精度问题，需要减去很小的数 1e-8 来避免 1.0 (实际表示的时候可能保存成 1.000...01) 向上取整成 2
或者: f[i][j] 表示上下一辆车的最小时间，一定是整数的了
用第 1 种表示方法:
1. 操作 i, f[i-1][j-1] + d[i]/speed
2. 不操作 i, ceil(f[i-1][j] + d[i]/speed)
最终答案:
f[n][j] <= hour 的最小的 j，没有的话返回 -1
*/
const double eps = 1e-8;
class Solution {
   public:
    int minSkips(vector<int>& dist, int speed, int hoursBefore) {
        int n = dist.size();
        vector<vector<double>> f(n + 1, vector<double>(n + 1, 1e10));
        f[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                double t = (double)dist[i - 1] / speed;
                f[i][j] = ceil(f[i - 1][j] + t - eps);
                if (j > 0)
                    f[i][j] = min(
                        f[i][j],
                        f[i - 1][j - 1] + t);
            }
        }
        for (int j = 0; j <= n; j++) {
            if (f[n][j] <= hoursBefore) return j;
        }
        return -1;
    }
};

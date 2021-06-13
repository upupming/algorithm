#include <bits/stdc++.h>
using namespace std;
// f[k][x][y]: 当前有 K 个人，a 前面有 x 个人，b 后面有 y 个人，是否可以到达这个状态（因为观察到 a, b 前后有多少人重要，但是具体是谁不重要）
const int N = 30;
bool f[N][N][N];
class Solution {
   public:
    vector<int> earliestAndLatest(int n, int a, int b) {
        memset(f, 0, sizeof f);
        f[n][a - 1][n - b] = true;
        for (int k = n; k > 1; k = (k + 1) / 2) {
            for (int x = 0; x <= n; x++) {
                for (int y = 0; y <= n; y++) {
                    if (f[k][x][y]) {
                        int m = (k + 1) / 2, m2 = k - m;
                        if (y >= m2) {
                            int z = k - x - y - 2;
                            for (int i = 0; i <= x; i++) {
                                for (int j = 0; j <= z; j++) {
                                    f[m][i][j + x - i + y - m2] = true;
                                }
                            }
                        } else if (x >= m2) {
                            int z = k - x - y - 2;
                            for (int i = 0; i <= y; i++) {
                                for (int j = 0; j <= z; j++) {
                                    f[m][j + y - i + x - m2][i] = true;
                                }
                            }
                        } else if (x < y) {
                            int z = y - x - 1;
                            for (int i = 0; i <= x; i++) {
                                for (int j = 0; j <= z; j++) {
                                    f[m][i][x - i + j] = true;
                                }
                            }
                        } else if (x > y) {
                            int z = x - y - 1;
                            for (int i = 0; i <= y; i++) {
                                for (int j = 0; j <= z; j++) {
                                    f[m][y - i + j][i] = true;
                                }
                            }
                        }
                    }
                }
            }
        }

        int r1 = INT_MAX, r2 = INT_MIN;
        for (int k = n, t = 1; k > 1; k = (k + 1) / 2, t++) {
            for (int i = 0; i <= k; i++) {
                if (f[k][i][i]) {
                    r1 = min(r1, t);
                    r2 = max(r2, t);
                }
            }
        }
        return {r1, r2};
    }
};

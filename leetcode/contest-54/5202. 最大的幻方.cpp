#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> pre(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                pre[i][j] = pre[i][j - 1] + pre[i - 1][j] - pre[i - 1][j - 1] + grid[i - 1][j - 1];
            }
        }
        const auto& get = [&pre](int i, int j, int a, int b) {
            return pre[i][j] - pre[a][j] - pre[i][b] + pre[a][b];
        };

        // cout << m << " " << n << endl;
        int ans = 0;
        for (int a = 1; a <= min(m, n); a++) {
            bool found = false;
            for (int i = 0; i + a - 1 < m; i++) {
                if (found) break;
                for (int j = 0; j + a - 1 < n; j++) {
                    if (found) break;
                    int t = i;
                    int d = i + a - 1;
                    int left = j;
                    int right = j + a - 1;
                    int sum[2] = {0};
                    for (int I = t; I <= d; I++) {
                        int J = I - (t - left);
                        sum[0] += grid[I][J];
                    }
                    for (int I = t; I <= d; I++) {
                        int J = (t + right) - I;
                        sum[1] += grid[I][J];
                    }
                    bool ok = true;
                    if (sum[0] != sum[1]) ok = false;
                    for (int I = t; I <= d; I++) {
                        auto row = get(I + 1, right + 1, I - 1 + 1, left - 1 + 1);
                        if (row != sum[0]) {
                            ok = false;
                            break;
                        }
                    }
                    for (int J = left; J <= right; J++) {
                        auto col = get(d + 1, J + 1, t - 1 + 1, J - 1 + 1);
                        if (col != sum[0]) {
                            ok = false;
                            break;
                        }
                    }

                    if (ok) {
                        ans = max(ans, a);
                        found = true;
                    }
                }
            }
        }
        return ans;
    }
};

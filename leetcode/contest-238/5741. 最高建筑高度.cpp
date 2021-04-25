#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int maxBuilding(int n, vector<vector<int>>& h) {
        typedef long long LL;
        h.push_back({1, 0});
        sort(h.begin(), h.end());
        if (h.back()[0] != n) {
            h.push_back({n, n - 1});
        }
        int m = h.size();
        // f 表示前面的限制(左边所有截距的最小值)，g 表示后面的限制(右边所有截距的最小值)
        // 每个限制只与直线的截距 b 相关
        vector<LL> f(m + 1, INT_MAX), g(m + 1, INT_MAX);
        f[0] = -1;
        for (int i = 1; i < m; i++) {
            int x = h[i][0], y = h[i][1];
            f[i] = min(f[i - 1], (LL)y - x);
        }
        for (int i = m - 1; i >= 0; i--) {
            int x = h[i][0], y = h[i][1];
            g[i] = min(g[i + 1], (LL)y + x);
        }
        LL ans = 0;
        for (int i = 0; i < m; i++) {
            int x = h[i][0];
            if (i) {
                LL Y = (f[i - 1] + g[i]) / 2;
                LL X = Y - f[i - 1];
                if (X >= h[i - 1][0] && X <= h[i][0]) {
                    ans = max(ans, Y);
                }
            }
            ans = max(ans, min(x + f[i], -x + g[i]));
        }
        return ans;
    }
};
